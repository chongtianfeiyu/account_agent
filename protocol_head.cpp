/*
 * protocol_head.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: jimm
 */

#include "protocol_head.h"
#include "../rapidjson/document.h"
#include "../rapidjson/prettywriter.h"
#include "../rapidjson/filestream.h"
#include "../rapidjson/stringbuffer.h"
#include "server_helper.h"

using namespace rapidjson;

PkgHead::PkgHead()
{
	m_nTag = 0;
	m_nTotalSize = 0;
	m_nHeadSize = 0;
	m_nMsgID = 0;
	m_nVersion = 0;
	m_nFlag = 0;
	m_nOptionLen = 0;
}

int32_t PkgHead::GetSize()
{
	return sizeof(m_nTag) + sizeof(m_nTotalSize) + sizeof(m_nHeadSize) + sizeof(m_nMsgID) +
			sizeof(m_nVersion) + sizeof(m_nFlag);
}

int32_t PkgHead::Encode(uint8_t *pBuf, const int32_t nBufSize, uint32_t &nOffset)
{
	int32_t nRet = S_OK;
	nRet = CCodeEngine::Encode(pBuf, nBufSize, nOffset, m_nTag);
	if(nRet < 0)
	{
		return nRet;
	}

	nRet = CCodeEngine::Encode(pBuf, nBufSize, nOffset, m_nTotalSize);
	if(nRet < 0)
	{
		return nRet;
	}

	nRet = CCodeEngine::Encode(pBuf, nBufSize, nOffset, m_nHeadSize);
	if(nRet < 0)
	{
		return nRet;
	}

	nRet = CCodeEngine::Encode(pBuf, nBufSize, nOffset, m_nMsgID);
	if(nRet < 0)
	{
		return nRet;
	}

	nRet = CCodeEngine::Encode(pBuf, nBufSize, nOffset, m_nVersion);
	if(nRet < 0)
	{
		return nRet;
	}

	nRet = CCodeEngine::Encode(pBuf, nBufSize, nOffset, m_nFlag);
	if(nRet < 0)
	{
		return nRet;
	}

//		nRet = CCodeEngine::Encode(pBuf, nBufSize, nOffset, m_nOptionLen);
//		if(nRet < 0)
//		{
//			return nRet;
//		}
//
//		nRet = CCodeEngine::Encode(pBuf, nBufSize, nOffset, m_arrOption, m_nOptionLen, MAX_HEAD_OPTION_LEN);
//		if(nRet < 0)
//		{
//			return nRet;
//		}

	return S_OK;
}

int32_t PkgHead::Decode(const uint8_t *pBuf, const int32_t nBufSize, uint32_t &nOffset)
{
	int32_t nRet = S_OK;
	nRet = CCodeEngine::Decode(pBuf, nBufSize, nOffset, m_nTag);
	if(nRet < 0)
	{
		return nRet;
	}

	nRet = CCodeEngine::Decode(pBuf, nBufSize, nOffset, m_nTotalSize);
	if(nRet < 0)
	{
		return nRet;
	}

	nRet = CCodeEngine::Decode(pBuf, nBufSize, nOffset, m_nHeadSize);
	if(nRet < 0)
	{
		return nRet;
	}

	nRet = CCodeEngine::Decode(pBuf, nBufSize, nOffset, m_nMsgID);
	if(nRet < 0)
	{
		return nRet;
	}

	nRet = CCodeEngine::Decode(pBuf, nBufSize, nOffset, m_nVersion);
	if(nRet < 0)
	{
		return nRet;
	}

	nRet = CCodeEngine::Decode(pBuf, nBufSize, nOffset, m_nFlag);
	if(nRet < 0)
	{
		return nRet;
	}

	if(m_nHeadSize > GetSize())
	{
		nRet = CCodeEngine::Decode(pBuf, nBufSize, nOffset, m_nOptionLen);
		if(nRet < 0)
		{
			return nRet;
		}

		nRet = CCodeEngine::Decode(pBuf, nBufSize, nOffset, m_arrOption, m_nOptionLen, MAX_HEAD_OPTION_LEN);
		if(nRet < 0)
		{
			return nRet;
		}
	}

	return S_OK;
}

void PkgHead::Dump(char* buf, const uint32_t size, uint32_t& offset)
{
	int32_t len = sprintf(buf + offset, "{pkghead:{m_nTag=%d, m_nTotalSize=%d, m_nHeadSize=%d, m_nMsgID=0x%08x, "
		"m_nVersion=%d, m_nFlag=%d, m_nOptionLen=%d}, ",
		m_nTag, m_nTotalSize, m_nHeadSize, m_nMsgID, m_nVersion, m_nFlag, m_nOptionLen);
	offset += len;
}


WebHeader::WebHeader()
{
	m_nMsgID = 0;
	m_nRoomID = 0;
	m_nRoleID = 0;
	m_nSessionIndex = enmInvalidSessionIndex;
}

int32_t WebHeader::GetSize()
{
	return sizeof(m_nMsgID) + sizeof(m_nRoomID) + sizeof(m_nRoleID) + sizeof(m_nSessionIndex);
}

int32_t WebHeader::Encode(uint8_t *pBuf, const int32_t nBufSize, uint32_t &nOffset)
{
	return 0;
}

int32_t WebHeader::Decode(const uint8_t *pBuf, const int32_t nBufSize, uint32_t &nOffset)
{
	Document document;
	if(document.Parse<0>((char *)pBuf).HasParseError())
	{
		return 1;
	}

	if(!document.IsObject())
	{
		return 1;
	}

	Value stData;
	if(!CServerHelper::GetValue(document, "header", stData))
	{
		return 1;
	}
	if(!CServerHelper::GetInt(stData, "msgid", m_nMsgID))
	{
		return 1;
	}

	if(!CServerHelper::GetInt(stData, "rid", m_nRoomID))
	{
		return 1;
	}

	if(!CServerHelper::GetInt(stData, "uid", m_nRoleID))
	{
		return 1;
	}

	if(!CServerHelper::GetInt(stData, "sessionindex", m_nSessionIndex))
	{
		return 1;
	}

	return 0;
}

void WebHeader::Dump(char* buf, const uint32_t size, uint32_t& offset)
{
	sprintf(buf + offset, "{m_nMsgID=0x%08x, m_nRoomID=%d, m_nRoleID=%d, m_nSessionIndex=%d}",
			m_nMsgID, m_nRoomID, m_nRoleID, m_nSessionIndex);
	offset = (uint32_t)strlen(buf);
}

