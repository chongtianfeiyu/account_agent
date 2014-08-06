/*
 * http_business.cpp
 *
 *  Created on: Jul 29, 2014
 *      Author: jimm
 */

#include "../../common/common_memmgt.h"
#include "../../frame/frame.h"
#include "../server_config.h"
#include "../datacenter.h"
#include "http_business.h"
#include <string.h>
using namespace FRAME;

void CHttpBusiness::SetConnector(CConnector *pConnector)
{
	m_pConnector = pConnector;
}

int32_t CHttpBusiness::Write(uint8_t *pBuf, int32_t nBufSize)
{
	CServerConfig *pServerConfig = (CServerConfig *)g_DataCenter.GetFrame()->GetConfig(CONFIG_SERVER);
	if(pServerConfig == NULL)
	{
		return 0;
	}

	NetNode *pNetNode = pServerConfig->GetOneNetNode(enmEntityType_Account);
	if(pNetNode == NULL)
	{
		return 0;
	}

	m_pConnector->Connect(pNetNode->m_szPeerAddress, pNetNode->m_nPeerPort);

	uint8_t *pMem = MALLOC(sizeof(HttpReq) + nBufSize);
	HttpReq *pHttpReq = new(pMem) HttpReq();
	pHttpReq->m_nHttpReqLen = nBufSize;
	memcpy(pHttpReq->m_pHttpReq, pBuf, nBufSize);
	//pHttpReq->m_pHttpReq[nBufSize] = '\0';
	m_stHttpReqQueue.push_back(pHttpReq);

	return nBufSize;
}

int32_t CHttpBusiness::Read(uint8_t arrBuf[], int32_t nBufSize)
{
	int32_t nDataSize = 0;
	if(m_stHttpReqQueue.empty())
	{
		return nDataSize;
	}

	HttpReq *pHttpReq = m_stHttpReqQueue.front();
	m_stHttpReqQueue.pop_front();

	if(nBufSize >= (int32_t)pHttpReq->m_nHttpReqLen)
	{
		memcpy(arrBuf, pHttpReq->m_pHttpReq, pHttpReq->m_nHttpReqLen);
		nDataSize = pHttpReq->m_nHttpReqLen;
	}

	DELETE(pHttpReq);

	return nDataSize;
}




