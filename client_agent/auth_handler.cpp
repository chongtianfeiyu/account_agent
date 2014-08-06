/*
 * auth_handler.cpp
 *
 *  Created on: Jul 28, 2014
 *      Author: jimm
 */


#include "auth_handler.h"
#include "../../logger/logger.h"
#include "../../frame/frame.h"
#include "../server_typedef.h"
#include "../protocol_head.h"
#include "../message_define.h"
#include "../datacenter.h"
#include "../../common/common_crypt.h"

using namespace LOGGER;
using namespace FRAME;

int32_t CAuthHandler::OnAuthMessageEvent(CBaseObject *pObject, IMsgHead *pMsgHead, IMsgBody *pMsgBody)
{
	WRITE_DEBUG_LOG(SERVER_NAME, "recv auth message!\n");
	IIOSession *pIoSession = dynamic_cast<IIOSession *>(pObject);
	if(pIoSession == NULL)
	{
		WRITE_WARN_LOG(SERVER_NAME, "translate object to iosession error!\n");
		return 0;
	}

	PkgHead *pPkgHead = dynamic_cast<PkgHead *>(pMsgHead);
	if(pPkgHead == NULL)
	{
		WRITE_WARN_LOG(SERVER_NAME, "translate msghead to pkghead error!\n");
		return 0;
	}

	CAuthReq *pAuthReq = dynamic_cast<CAuthReq *>(pMsgBody);
	if(pAuthReq == NULL)
	{
		WRITE_WARN_LOG(SERVER_NAME, "translate msgbody to authreq error!\n");
		return 0;
	}

	SendAuthReq(pIoSession, pPkgHead, pAuthReq);

	return 0;
}

int32_t CAuthHandler::OnAuthTimeout(CBaseObject *pObject, CBaseObject *pParam)
{
	WRITE_DEBUG_LOG(SERVER_NAME, "auth timeout!\n");
	IIOSession *pIoSession = dynamic_cast<IIOSession *>(pObject);
	if(pIoSession == NULL)
	{
		WRITE_WARN_LOG(SERVER_NAME, "translate object to iosession error!\n");
		return 0;
	}

	CAuthParam *pAuthParam = (CAuthParam *)pParam;
	PkgHead stPkgHead;
	stPkgHead.m_nTag = 0;
	stPkgHead.m_nTotalSize = 0;
	stPkgHead.m_nHeadSize = stPkgHead.GetSize();
	stPkgHead.m_nMsgID = MSGID_CLIENTAUTH_RESP;
	stPkgHead.m_nFlag = 0;
	stPkgHead.m_nVersion = 0;
	stPkgHead.m_nOptionLen = 0;

	CAuthResp stAuthResp;
	stAuthResp.m_nResult = 1;

	uint8_t arrMsg[MAX_SERVER_MSG_LEN];
	uint32_t nOffset = 0;
	int32_t nRet = stPkgHead.Encode(arrMsg, sizeof(arrMsg), nOffset);
	if(nRet > 0)
	{
		return 0;
	}

	int16_t nHeadSize = nOffset;

	nRet = stAuthResp.Encode(arrMsg, sizeof(arrMsg) - nOffset, nOffset);
	if(nRet > 0)
	{
		return 0;
	}

	char arrRealBody[MAX_SERVER_MSG_LEN];
	int32_t nRealLen = CXTEA::Encrypt((char *)&arrMsg[nHeadSize], sizeof(arrMsg) - nOffset, arrRealBody, sizeof(arrRealBody), "Authentic@51.COM");
	if(nRealLen <= 0)
	{
		return 0;
	}

	memcpy(&arrMsg[nHeadSize], arrRealBody, nRealLen);

	int16_t nTotalSize = nRealLen + nHeadSize;
	nOffset = 1;
	nRet = CCodeEngine::Encode(arrMsg, nTotalSize, nOffset, nTotalSize);
	if(nRet > 0)
	{
		return 0;
	}

	pIoSession->Write(arrMsg, nTotalSize);

	return 0;
}

int32_t CAuthHandler::SendAuthReq(IIOSession *pIoSession, IMsgHead *pMsgHead, IMsgBody *pMsgBody)
{
	PkgHead *pPkgHead = dynamic_cast<PkgHead *>(pMsgHead);
	if(pPkgHead == NULL)
	{
		WRITE_WARN_LOG(SERVER_NAME, "translate msghead to pkghead error!\n");
		return 0;
	}

	CAuthReq *pAuthReq = dynamic_cast<CAuthReq *>(pMsgBody);
	if(pAuthReq == NULL)
	{
		WRITE_WARN_LOG(SERVER_NAME, "translate msgbody to authreq error!\n");
		return 0;
	}

	CAuthHandler::CAuthParam *pAuthParam = NEW(CAuthHandler::CAuthParam);
	pAuthParam->m_stPkgHead = *pPkgHead;
	pAuthParam->m_stAuthReq = *pAuthReq;

	CSessionData *pSessionData = g_DataCenter.GetSessionMgt()->CreateSession(this, static_cast<SessionCallBack>(&CAuthHandler::OnAuthTimeout),
			pAuthParam, pIoSession->GetSessionID(), 5000);
	if(pSessionData == NULL)
	{
		return 0;
	}

	uint8_t arrGetParam[1024];
	int32_t nParamLen = sprintf((char *)arrGetParam, "/request/auth/login?accountname=%s&password=%s&sessionindex=%d",
			pAuthReq->m_arrRoleID, pAuthReq->m_arrPassword, pSessionData->GetSessionIndex());
	if(nParamLen <= 0)
	{
		g_DataCenter.GetSessionMgt()->DestroySession(pSessionData->GetSessionIndex());
		return 0;
	}

	uint8_t arrMessage[enmMaxMessageSize];
	int32_t nMsgSize = sprintf((char *)arrMessage, HTTP_GET_REQ, arrGetParam);
	if(nMsgSize <= 0)
	{
		g_DataCenter.GetSessionMgt()->DestroySession(pSessionData->GetSessionIndex());
		return 0;
	}

	return g_DataCenter.GetHttpBusiness()->Write(arrMessage, nMsgSize);
}


