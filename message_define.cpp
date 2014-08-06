/*
 * message_define.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: jimm
 */

#include "message_define.h"
#include "../common/common_codeengine.h"
#include "../rapidjson/document.h"
#include "../rapidjson/prettywriter.h"
#include "../rapidjson/filestream.h"
#include "../rapidjson/stringbuffer.h"
#include "server_helper.h"

using namespace rapidjson;

CAuthReq::CAuthReq()
{
	m_nRoleIDLen = 0;
	memset(m_arrRoleID, 0, sizeof(m_arrRoleID));
	m_nIsFirst = 0;
	m_nIPLen = 0;
	memset(m_arrIP, 0, sizeof(m_arrIP));
	m_nSourceLen = 0;
	memset(m_arrSource, 0, sizeof(m_arrSource));
	m_nAppID = 0;
	memset(m_arrPassword, 0, sizeof(m_arrPassword));
}
int32_t CAuthReq::Encode(uint8_t* buf, const int32_t size, uint32_t& offset)
{
	int32_t nRet = S_OK;
	nRet = CCodeEngine::Encode(buf, size, offset, m_nRoleIDLen);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Encode(buf, size, offset, (uint8_t *)m_arrRoleID, m_nRoleIDLen, MAX_UID_LEN);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Encode(buf, size, offset, m_nIsFirst);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Encode(buf, size, offset, m_nIPLen);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Encode(buf, size, offset, (uint8_t *)m_arrIP, m_nIPLen, MAX_IP_LEN);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Encode(buf, size, offset, m_nSourceLen);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Encode(buf, size, offset, (uint8_t *)m_arrSource, m_nSourceLen, MAX_SOURCE_LEN);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Encode(buf, size, offset, m_nAppID);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Encode(buf, size, offset, (uint8_t *)m_arrPassword, MAX_PSWD_LEN, MAX_PSWD_LEN);
	if (0 > nRet)
	{
		return nRet;
	}
	return S_OK;
}

int32_t CAuthReq::Decode(const uint8_t *buf, const int32_t size, uint32_t& offset)
{
	int32_t nRet = S_OK;
	nRet = CCodeEngine::Decode(buf, size, offset, m_nRoleIDLen);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Decode(buf, size, offset, (uint8_t *)m_arrRoleID, m_nRoleIDLen, MAX_UID_LEN);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Decode(buf, size, offset, m_nIsFirst);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Decode(buf, size, offset, m_nIPLen);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Decode(buf, size, offset, (uint8_t *)m_arrIP, m_nIPLen, MAX_IP_LEN);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Decode(buf, size, offset, m_nSourceLen);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Decode(buf, size, offset, (uint8_t *)m_arrSource, m_nSourceLen, MAX_SOURCE_LEN);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Decode(buf, size, offset, m_nAppID);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Decode(buf, size, offset, (uint8_t *)m_arrPassword, MAX_PSWD_LEN, MAX_PSWD_LEN);
	if (0 > nRet)
	{
		return nRet;
	}

	return S_OK;
}

void CAuthReq::Dump(char* buf, const uint32_t size, uint32_t& offset)
{
	sprintf(buf + offset, "{m_nRoleIDLen=%d,m_arrRoleID=%s,m_nIsFirst=%d,m_nIPLen=%d,"
			"m_arrIP=%s,m_nSourceLen=%d,m_nAppID=%d,m_arrPassword=%s}", m_nRoleIDLen, m_arrRoleID, m_nIsFirst,
			m_nIPLen, m_arrIP, m_nSourceLen, m_nAppID, m_arrPassword);
	offset = (uint32_t)strlen(buf);
}


CAuthResp::CAuthResp()
{
	m_nResult = 0;
	m_nRoleID = 0;
	m_nAccountID = 0;
	m_nRoleIDLen = 0;
	m_nTokenLen = 0;
}

int32_t CAuthResp::Encode(uint8_t* buf, const int32_t size, uint32_t& offset)
{
	int32_t nRet = S_OK;
	nRet = CCodeEngine::Encode(buf, size, offset, m_nResult);
	if (0 > nRet)
	{
		return nRet;
	}
	if(m_nResult != 0)
	{
		return 0;
	}
	nRet = CCodeEngine::Encode(buf, size, offset, m_nRoleID);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Encode(buf, size, offset, m_nAccountID);
	if (0 > nRet)
	{
		return nRet;
	}
//	nRet = CCodeEngine::Encode(buf, size, offset, m_nRoleIDLen);
//	if (0 > nRet)
//	{
//		return nRet;
//	}
//	nRet = CCodeEngine::Encode(buf, size, offset, (uint8_t *)m_arrEmail, MAX_EMAIL_LEN, MAX_EMAIL_LEN);
//	if (0 > nRet)
//	{
//		return nRet;
//	}
//	nRet = CCodeEngine::Encode(buf, size, offset, (uint8_t *)m_arrSessionKey, MAX_SESSIONKEY_LEN, MAX_SESSIONKEY_LEN);
//	if (0 > nRet)
//	{
//		return nRet;
//	}
	nRet = CCodeEngine::Encode(buf, size, offset, m_nTokenLen);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Encode(buf, size, offset, (uint8_t *)m_arrToken, m_nTokenLen, TOKEN_MAX_LEN);
	if (0 > nRet)
	{
		return nRet;
	}
	return S_OK;
}

int32_t CAuthResp::Decode(const uint8_t *buf, const int32_t size, uint32_t& offset)
{
	int32_t nRet = S_OK;
	nRet = CCodeEngine::Decode(buf, size, offset, m_nResult);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Decode(buf, size, offset, m_nRoleID);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Decode(buf, size, offset, m_nAccountID);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Decode(buf, size, offset, m_nRoleIDLen);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Decode(buf, size, offset, m_arrEmail, MAX_EMAIL_LEN);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Decode(buf, size, offset, m_arrSessionKey, MAX_SESSIONKEY_LEN);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Decode(buf, size, offset, m_nTokenLen);
	if (0 > nRet)
	{
		return nRet;
	}
	nRet = CCodeEngine::Decode(buf, size, offset, m_arrToken, TOKEN_MAX_LEN);
	if (0 > nRet)
	{
		return nRet;
	}

	return S_OK;
}

void CAuthResp::Dump(char* buf, const uint32_t size, uint32_t& offset)
{
	sprintf(buf + offset, "{m_nResult=%d,m_nRoleID=%d,m_nAccountID=%d,m_nRoleIDLen=%d,"
			"m_arrEmail=%s,m_arrSessionKey=%s,m_nTokenLen=%d,m_arrToken=%s}", m_nResult, m_nRoleID, m_nAccountID,
			m_nRoleIDLen, m_arrEmail, m_arrSessionKey, m_nTokenLen, m_arrToken);
	offset = (uint32_t)strlen(buf);
}



CHttpLoginResp::CHttpLoginResp()
{
	m_nResult = 0;
}

int32_t CHttpLoginResp::Encode(uint8_t* buf, const int32_t size, uint32_t& offset)
{
	return 0;
}

int32_t CHttpLoginResp::Decode(const uint8_t *buf, const int32_t size, uint32_t& offset)
{
	Document document;
	if(document.Parse<0>((char *)buf).HasParseError())
	{
		return 1;
	}

	if(!document.IsObject())
	{
		return 1;
	}

	Value stData;
	if(!CServerHelper::GetValue(document, "body", stData))
	{
		return 1;
	}

	if(!CServerHelper::GetInt(stData, "code", m_nResult))
	{
		return 1;
	}

	return 0;
}

void CHttpLoginResp::Dump(char* buf, const uint32_t size, uint32_t& offset)
{
	sprintf(buf + offset, "{m_nResult=%d}", m_nResult);
	offset = (uint32_t)strlen(buf);
}


