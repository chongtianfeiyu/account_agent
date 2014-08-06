/*
 * http_process.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: jimm
 */


#include "http_process.h"
#include "../protocol_head.h"
#include "../message_define.h"
#include "../datacenter.h"
#include "../session_bank/session_mgt.h"
#include "../session_bank/session_data.h"
#include "../../netevent/net_connmgt.h"
#include "../../common/common_crypt.h"

using namespace NETEVENT;

static char g_arrSSKey[1024] = {'v', 'd', 'c', '$', 'a', 'u', 't', 'h', '@', '1', '7','9','.', 'c', 'o', 'm'};

int32_t CHttpProcess::ProcessHttpLoginResp(IMsgHead *pMsgHead, IMsgBody *pMsgBody)
{
	WebHeader *pWebHeader = dynamic_cast<WebHeader *>(pMsgHead);
	if(pWebHeader == NULL)
	{
		return 0;
	}

	CHttpLoginResp *pHttpLoginResp = dynamic_cast<CHttpLoginResp *>(pMsgBody);
	if(pHttpLoginResp == NULL)
	{
		return 0;
	}

	CSessionData *pSessionData = g_DataCenter.GetSessionMgt()->GetSessionData(pWebHeader->m_nSessionIndex);
	if(pSessionData == NULL)
	{
		return 0;
	}

	IIOSession *pIoSession = g_ConnMgt.GetConnection(pSessionData->GetSessionID());
	if(pIoSession == NULL)
	{
		return 0;
	}

	uint8_t arrMsg[MAX_SERVER_MSG_LEN];

	PkgHead stPkgHead;
	stPkgHead.m_nTag = 0;
	stPkgHead.m_nHeadSize = stPkgHead.GetSize();
	stPkgHead.m_nTotalSize = 0;
	stPkgHead.m_nMsgID = MSGID_CLIENTAUTH_RESP;
	stPkgHead.m_nFlag = 0;
	stPkgHead.m_nVersion = 0;
	stPkgHead.m_nOptionLen = 0;

	uint32_t nOffset = 0;
	int32_t nRet = stPkgHead.Encode(arrMsg, sizeof(arrMsg), nOffset);
	if(nRet > 0)
	{
		return 0;
	}

	CAuthResp stAuthResp;
	stAuthResp.m_nResult = pHttpLoginResp->m_nResult;
	if(pHttpLoginResp->m_nResult == 200)
	{
		stAuthResp.m_nResult = 0;
		stAuthResp.m_nRoleID = pWebHeader->m_nRoleID;
		stAuthResp.m_nTokenLen = CServerHelper::MakeToken(stAuthResp.m_arrToken, pWebHeader->m_nRoleID);
	}
	else
	{
		pHttpLoginResp->m_nResult = 1;
	}

	int16_t nHeadSize = nOffset;
	nOffset = 0;
	uint8_t arrBody[MAX_SERVER_MSG_LEN];
	nRet = stAuthResp.Encode(arrBody, sizeof(arrBody), nOffset);
	if(nRet > 0)
	{
		return 0;
	}

	int32_t nRealLen = CXTEA::Encrypt((char *)arrBody, nOffset, (char *)&arrMsg[nHeadSize], sizeof(arrMsg) - nHeadSize, "Authentic@51.COM");
	if(nRealLen <= 0)
	{
		return 0;
	}

	uint16_t nTotalSize = nHeadSize + nRealLen;
	nOffset = 1;
	nRet = CCodeEngine::Encode(arrMsg, nTotalSize, nOffset, nTotalSize);
	if(nRet < 0)
	{
		return 0;
	}

	pIoSession->Write(arrMsg, nTotalSize);

	return 0;
}
