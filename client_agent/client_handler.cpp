/*
 * client_handler.cpp
 *
 *  Created on: 2014年5月7日
 *      Author: jimm
 */

#include "client_handler.h"
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

using namespace LOGGER;
using namespace FRAME;

int32_t CClientHandler::OnOpened(IIOSession *pIoSession)
{
	WRITE_DEBUG_LOG(SERVER_NAME, "new session!{peeraddress=%s, peerport=%d, socketfd=%d}\n",
			pIoSession->GetPeerAddressStr(), pIoSession->GetPeerPort(), pIoSession->GetSocketFD());

	CServerConfig *pServerConfig = (CServerConfig *)g_DataCenter.GetFrame()->GetConfig(CONFIG_SERVER);

	NetNode *pNetNode = pServerConfig->FindNetNode(pIoSession->GetPeerAddressStr(), pIoSession->GetPeerPort());
	if(pNetNode == NULL)
	{
		return 0;
	}

	int32_t nConnCount = g_DataCenter.IncConnCount();
	if(nConnCount > pServerConfig->GetMaxConnCount())
	{
		WRITE_DEBUG_LOG(SERVER_NAME, "current connections number is bigger than max_connections!"
				"{nConnCount=%d, nMaxConnCount=%d}\n", nConnCount, pServerConfig->GetMaxConnCount());
		pIoSession->Close();
		return 0;
	}

	return 0;
}

int32_t CClientHandler::OnRecved(IIOSession *pIoSession, uint8_t *pBuf, uint32_t nBufSize)
{
	//WRITE_DEBUG_LOG(SERVER_NAME, "recv message:[size=%d]:%s\n", nBufSize, (char *)pBuf);

	uint32_t nOffset = 0;
	uint8_t nHeadType = 0;
	int32_t nRet = CCodeEngine::Decode(pBuf, nBufSize, nOffset, nHeadType);
	if(nRet < 0)
	{
		return 0;
	}

	uint16_t nHeadSize = 0;
	//取出包头大小
	nOffset = 3;
	nRet = CCodeEngine::Decode(pBuf, nBufSize, nOffset, nHeadSize);
	if(nRet < 0)
	{
		return 0;
	}

	int16_t nMsgID = 0;
	//取出msgid
	nOffset = 5;
	nRet = CCodeEngine::Decode(pBuf, nBufSize, nOffset, nMsgID);
	if(nRet < 0)
	{
		return 0;
	}

	char arrRealBody[MAX_SERVER_MSG_LEN];
	int32_t nRealLen = CXTEA::Decrypt((char *)&pBuf[nHeadSize], nBufSize - nHeadSize, arrRealBody, sizeof(arrRealBody), "Authentic@51.COM");
	if(nRealLen <= 0)
	{
		return 0;
	}

	memcpy(pBuf + nHeadSize, arrRealBody, nBufSize - nHeadSize);
	nBufSize = nHeadSize + nRealLen;
	int16_t nTotalSize = nBufSize;
	//重新修改包的总长度值
	nOffset = 1;
	nRet = CCodeEngine::Encode(pBuf, nBufSize, nOffset, nTotalSize);

	nRet = g_DataCenter.GetFrame()->FrameCallBack(nMsgID, pIoSession, pBuf, nBufSize);
	if(nRet == -1)
	{
		WRITE_WARN_LOG(SERVER_NAME, "frame call back return fail!\n");
	}
	else if(nRet == 1)
	{
		WRITE_WARN_LOG(SERVER_NAME, "it's not found msg handler!{msgid=0x%04x}\n", nMsgID);
	}
	else if(nRet == 2)
	{
		WRITE_WARN_LOG(SERVER_NAME, "decode msg failed!{msgid=0x%04x}\n", nMsgID);
	}

	return 0;
}

int32_t CClientHandler::OnSent(IIOSession *pIoSession, uint8_t *pBuf, uint32_t nBufSize)
{
	//WRITE_DEBUG_LOG(SERVER_NAME, "send data!\n");
	return 0;
}

int32_t CClientHandler::OnClosed(IIOSession *pIoSession)
{
	WRITE_DEBUG_LOG(SERVER_NAME, "session closed!{peeraddress=%s, peerport=%d, socketfd=%d}\n",
			pIoSession->GetPeerAddressStr(), pIoSession->GetPeerPort(), pIoSession->GetSocketFD());

	CServerConfig *pServerConfig = (CServerConfig *)g_DataCenter.GetFrame()->GetConfig(CONFIG_SERVER);
	g_DataCenter.DecConnCount();


	NetNode *pNetNode = pServerConfig->FindNetNode(pIoSession->GetPeerAddressStr(), pIoSession->GetPeerPort());
	if(pNetNode != NULL)
	{
		m_pConnector->Connect(pIoSession->GetPeerAddressStr(), pIoSession->GetPeerPort());
	}

	return 0;
}

int32_t CClientHandler::OnError(IIOSession *pIoSession)
{
	WRITE_DEBUG_LOG(SERVER_NAME, "session error!{peeraddress=%s, peerport=%d, socketfd=%d}\n",
			pIoSession->GetPeerAddressStr(), pIoSession->GetPeerPort(), pIoSession->GetSocketFD());

	return 0;
}

int32_t CClientHandler::OnTimeout(IIOSession *pIoSession)
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

void CClientHandler::SetConnector(CConnector *pConnector)
{
	m_pConnector = pConnector;
}

