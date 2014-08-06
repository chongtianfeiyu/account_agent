/*
 * http_handler.cpp
 *
 *  Created on: Jul 29, 2014
 *      Author: jimm
 */

#include "http_handler.h"
#include "../server_typedef.h"
#include "../common/common_codeengine.h"
#include "../common/common_crypt.h"
#include "../logger/logger.h"
#include "../frame/frame.h"
#include "../frame/frame_typedef.h"
#include "../datacenter.h"
#include "../session_param.h"
#include "../server_config.h"
#include "../server_helper.h"
#include "../protocol_head.h"
#include "../message_define.h"
#include "http_process.h"

using namespace LOGGER;
using namespace FRAME;

int32_t CHttpHandler::OnOpened(IIOSession *pIoSession)
{
	WRITE_DEBUG_LOG(SERVER_NAME, "new session!{peeraddress=%s, peerport=%d, socketfd=%d}\n",
			pIoSession->GetPeerAddressStr(), pIoSession->GetPeerPort(), pIoSession->GetSocketFD());

	CServerConfig *pServerConfig = (CServerConfig *)g_DataCenter.GetFrame()->GetConfig(CONFIG_SERVER);

	NetNode *pNetNode = pServerConfig->FindNetNode(pIoSession->GetPeerAddressStr(), pIoSession->GetPeerPort());
	if(pNetNode == NULL)
	{
		return 0;
	}

	if(pNetNode->m_nPeerType == enmEntityType_Account)
	{
		uint8_t arrHttpReq[enmMaxMessageSize];
		int32_t nReqLen = g_DataCenter.GetHttpBusiness()->Read(arrHttpReq, sizeof(arrHttpReq));
		if(nReqLen <= 0)
		{
			return 0;
		}

		pIoSession->Write(arrHttpReq, nReqLen);
	}
	return 0;
}

int32_t CHttpHandler::OnRecved(IIOSession *pIoSession, uint8_t *pBuf, uint32_t nBufSize)
{
	//WRITE_DEBUG_LOG(SERVER_NAME, "recv message:[size=%d]:%s\n", nBufSize, (char *)pBuf);

	uint32_t nOffset = 0;
	WebHeader stWebHeader;
	int32_t nRet = stWebHeader.Decode(pBuf, nBufSize, nOffset);
	if(nRet == 1)
	{
		return 1;
	}

	switch(stWebHeader.m_nMsgID)
	{
	case MSGID_HTTPLOGIN_RESP:
	{
		CHttpLoginResp stHttpLoginResp;
		nRet = stHttpLoginResp.Decode(pBuf, nBufSize, nOffset);
		CHttpProcess::ProcessHttpLoginResp(&stWebHeader, &stHttpLoginResp);
	}
	break;
	}

	g_DataCenter.GetSessionMgt()->DestroySession(stWebHeader.m_nSessionIndex);

	pIoSession->Close();

	return 0;
}

int32_t CHttpHandler::OnSent(IIOSession *pIoSession, uint8_t *pBuf, uint32_t nBufSize)
{
	//WRITE_DEBUG_LOG(SERVER_NAME, "send data!\n");
	return 0;
}

int32_t CHttpHandler::OnClosed(IIOSession *pIoSession)
{
	WRITE_DEBUG_LOG(SERVER_NAME, "session closed!{peeraddress=%s, peerport=%d, socketfd=%d}\n",
			pIoSession->GetPeerAddressStr(), pIoSession->GetPeerPort(), pIoSession->GetSocketFD());

	return 0;
}

int32_t CHttpHandler::OnError(IIOSession *pIoSession)
{
	WRITE_DEBUG_LOG(SERVER_NAME, "session error!{peeraddress=%s, peerport=%d, socketfd=%d}\n",
			pIoSession->GetPeerAddressStr(), pIoSession->GetPeerPort(), pIoSession->GetSocketFD());

	return 0;
}

int32_t CHttpHandler::OnTimeout(IIOSession *pIoSession)
{
	WRITE_DEBUG_LOG(SERVER_NAME, "session timeout!{peeraddress=%s, peerport=%d, socketfd=%d}\n",
			pIoSession->GetPeerAddressStr(), pIoSession->GetPeerPort(), pIoSession->GetSocketFD());

	CServerConfig *pServerConfig = (CServerConfig *)g_DataCenter.GetFrame()->GetConfig(CONFIG_SERVER);
	NetNode *pNetNode = pServerConfig->FindNetNode(pIoSession->GetPeerAddressStr(), pIoSession->GetPeerPort());
	if(pNetNode != NULL)
	{
		m_pConnector->Connect(pIoSession->GetPeerAddressStr(), pIoSession->GetPeerPort());
	}

	return 0;
}

void CHttpHandler::SetConnector(CConnector *pConnector)
{
	m_pConnector = pConnector;
}




