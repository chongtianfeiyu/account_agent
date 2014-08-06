/*
 * http_packetparser.cpp
 *
 *  Created on: Jul 29, 2014
 *      Author: jimm
 */


#include "http_packetparser.h"
#include "../common/common_codeengine.h"
#include "../rapidjson/document.h"

using namespace rapidjson;

CHttpPacketParser::CHttpPacketParser()
{
	memset(m_arrFilterFlag, 0, sizeof(m_arrFilterFlag));
	strcpy(m_arrFilterFlag, "\r\n\r\n");
}

int32_t CHttpPacketParser::Init()
{
	return 0;
}

int32_t CHttpPacketParser::Uninit()
{
	return 0;
}

int32_t CHttpPacketParser::GetSize()
{
	return sizeof(*this);
}

int32_t CHttpPacketParser::Parser(const uint8_t arrBuf[], const uint32_t nBufSize, uint8_t arrPacket[], int32_t &nPacketSize)
{
	char *pFindEndFlag = strstr((char *)arrBuf, m_arrFilterFlag);
	if(pFindEndFlag == NULL)
	{
		return 0;
	}

	char *pFindStartFlag = strstr((char *)arrBuf, "{");
	if(pFindStartFlag == NULL)
	{
		return 0;
	}
	nPacketSize = pFindEndFlag - (char *)pFindStartFlag;
	if(nPacketSize < 0)
	{
		pFindStartFlag = (char *)arrBuf;
		nPacketSize = pFindEndFlag - (char *)arrBuf;
	}
	memcpy(arrPacket, pFindStartFlag, nPacketSize);

	arrPacket[nPacketSize] = '\0';

//	char *pHttpRespEndFlag = strstr((char *)arrBuf, m_arrFilterFlag);
//	if(pHttpRespEndFlag == NULL)
//	{
//		return 0;
//	}
//
//	pHttpRespEndFlag += strlen(m_arrFilterFlag);
//
//	int32_t nMsgSize = nBufSize - (pHttpRespEndFlag - (char *)arrBuf);
//	if(nMsgSize <= 0)
//	{
//		return 0;
//	}
//
//	char *pMsgRespEndFlag = strstr(pHttpRespEndFlag, m_arrFilterFlag);
//	if(pMsgRespEndFlag == NULL)
//	{
//		return 0;
//	}
//
//	nMsgSize -= strlen(m_arrFilterFlag);
//
//	nPacketSize = nMsgSize;
//	memcpy(arrPacket, pHttpRespEndFlag, nMsgSize);
//
//	arrPacket[nMsgSize] = 0;

	return nPacketSize + strlen(m_arrFilterFlag);
}


