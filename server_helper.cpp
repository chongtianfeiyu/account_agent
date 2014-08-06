/*
 * server_helper.cpp
 *
 *  Created on: 2014年5月14日
 *      Author: jimm
 */

#include "server_helper.h"
#include "server_typedef.h"
#include "../frame/frame.h"
#include "../frame/frame_typedef.h"
#include "server_config.h"
#include "session_param.h"
#include "../common/common_memmgt.h"
#include "../common/common_datetime.h"
#include "../common/common_crypt.h"
#include "datacenter.h"
#include "protocol_head.h"
#include "message_define.h"
#include "client_agent/auth_handler.h"

#define TOKEN_KEY  "9XiuMiMaJiaQiang"

#include <stdlib.h>

using namespace FRAME;

EntityMap CServerHelper::m_stEntityMap;

int32_t CServerHelper::SendMsg(uint8_t *pBuf, int32_t nBufSize, EntityType nEntityType, ServerID nServerID)
{
	IIOSession *pIoSession = GetIoSession(nEntityType, nServerID);
	if(pIoSession == NULL)
	{
		return 0;
	}

	return pIoSession->Write(pBuf, nBufSize);
}

void CServerHelper::RegistSessionInfo(EntityType nEntityType, int32_t nID, IIOSession *pIoSession)
{
	m_stEntityMap[nEntityType][nID] = pIoSession;

	CSessionParam *pSessionParam = (CSessionParam *)pIoSession->GetParamPtr();
	if(pSessionParam == NULL)
	{
		pSessionParam = NEW(CSessionParam);
		pIoSession->SetParamPtr(pSessionParam);
	}

	pSessionParam->SetParamInfo(nEntityType, nID);
}

void CServerHelper::UnregistSessionInfo(IIOSession *pIoSession)
{
	CSessionParam *pSessionParam = (CSessionParam *)pIoSession->GetParamPtr();
	if(pSessionParam == NULL)
	{
		return;
	}

	EntityType nEntityType = enmEntityType_None;
	int32_t nID = 0;

	pSessionParam->GetParamInfo(nEntityType, nID);

	EntityMap::iterator it = m_stEntityMap.find(nEntityType);
	if(it != m_stEntityMap.end())
	{
		IDMap::iterator et = it->second.find(nID);
		if(et != it->second.end())
		{
			it->second.erase(et);
		}
	}

	DELETE(pSessionParam);
}

IIOSession *CServerHelper::GetIoSession(EntityType nEntityType, int32_t nID)
{
	IIOSession *pIoSession = NULL;

	if(nID == 0)
	{
		pIoSession = GetOneIoSession(nEntityType);
	}
	else
	{
		EntityMap::iterator it = m_stEntityMap.find(nEntityType);
		if(it != m_stEntityMap.end())
		{
			IDMap::iterator et = it->second.find(nID);
			if(et != it->second.end())
			{
				pIoSession = et->second;
			}
		}
	}

	return pIoSession;
}

IIOSession *CServerHelper::GetOneIoSession(EntityType nEntityType)
{
	IIOSession *pIoSession = NULL;
	EntityMap::iterator it = m_stEntityMap.find(nEntityType);
	if(it != m_stEntityMap.end())
	{
		int32_t nServerCount = m_stEntityMap.count(nEntityType);
		if(nServerCount <= 0)
		{
			return pIoSession;
		}

		//随机出一个索引值
		int32_t nServerIndex = Random(nServerCount);
		int32_t nCount = 0;
		for(IDMap::iterator et = it->second.begin(); et != it->second.end(); ++et)
		{
			if(nCount >= nServerIndex)
			{
				pIoSession = et->second;
				break;
			}
			++nCount;
		}
	}

	return pIoSession;
}

bool CServerHelper::IsExist(Document &document, const char *szKey)
{
	return document.HasMember(szKey);
}

bool CServerHelper::IsExist(Value &value, const char *szKey)
{
	return value.HasMember(szKey);
}

bool CServerHelper::GetInt(Document &document, const char *szKey, int32_t &nValue)
{
	if(!document.HasMember(szKey))
	{
		return false;
	}

	nValue = 0;

	if(!document[szKey].IsInt())
	{
		if(!document[szKey].IsString())
		{
			return false;
		}
		nValue = atoi(document[szKey].GetString());
	}
	else
	{
		nValue = document[szKey].GetInt();
	}

	return true;
}

bool CServerHelper::GetString(Document &document, const char *szKey, string &nValue)
{
	if(!document.HasMember(szKey))
	{
		return false;
	}

	nValue = "";
	if(!document[szKey].IsString())
	{
		return false;
	}

	nValue = document[szKey].GetString();
	return true;
}

bool CServerHelper::GetInt(Value &value, const char *szKey, int32_t &nValue)
{
	if(!value.HasMember(szKey))
	{
		return false;
	}

	nValue = 0;

	if(!value[szKey].IsInt())
	{
		if(!value[szKey].IsString())
		{
			return false;
		}
		nValue = atoi(value[szKey].GetString());
	}
	else
	{
		nValue = value[szKey].GetInt();
	}

	return true;
}

bool CServerHelper::GetString(Value &value, const char *szKey, string &nValue)
{
	if(!value.HasMember(szKey))
	{
		return false;
	}

	nValue = "";
	if(!value[szKey].IsString())
	{
		return false;
	}

	nValue = value[szKey].GetString();
	return true;
}

bool CServerHelper::GetValue(Document &document, const char *szKey, Value &nValue)
{
	if(!document.HasMember(szKey))
	{
		return false;
	}

	nValue = "";

	if(!document[szKey].IsObject())
	{
		return false;
	}

	nValue = document[szKey];

	return true;
}

bool CServerHelper::GetValue(Value &value, const char *szKey, Value &nValue)
{
	if(!value.HasMember(szKey))
	{
		return false;
	}

	nValue = "";

	if(!value[szKey].IsObject())
	{
		return false;
	}

	nValue = value[szKey];

	return true;
}

int32_t CServerHelper::MakeToken(char arrToken[], int32_t nRoleID)
{
	int32_t nCurTime = CDateTime::CurrentDateTime().Seconds();
	int32_t nRandomKey = Random(999999);
	if(nRandomKey < 100000)
	{
		nRandomKey += 100000;
	}

	int32_t nRandomBit = Random(999999);
	if(nRandomBit < 100000)
	{
		nRandomBit += 100000;
	}

	PlayerSignature stPlayerSignature;

	char arrKey[max_encrypt_key_length];
	sprintf(arrKey, "%d%d", nRandomKey, nCurTime);
	memcpy(stPlayerSignature.m_arrKey, arrKey, max_encrypt_key_length);

	char arrBitMap[max_server_bitmap_length];
	sprintf(arrBitMap, "%d%d", nRandomBit, nCurTime);
	memcpy(stPlayerSignature.m_arrServerBitMap, arrBitMap, max_server_bitmap_length);

	stPlayerSignature.m_nRoleID = nRoleID;
	stPlayerSignature.m_nTimeStamp = nCurTime;

	uint32_t nOffset = 0;
	char arrCrypt[TOKEN_MAX_LEN];

	int32_t nRet = CCodeEngine::Encode((uint8_t *)arrCrypt, sizeof(arrCrypt) - nOffset, nOffset, (uint8_t *)stPlayerSignature.m_arrKey, sizeof(stPlayerSignature.m_arrKey), sizeof(stPlayerSignature.m_arrKey));
	if(nRet < 0)
	{
		return 0;
	}

	nRet = CCodeEngine::Encode((uint8_t *)arrCrypt, sizeof(arrCrypt) - nOffset, nOffset, stPlayerSignature.m_nRoleID);
	if(nRet < 0)
	{
		return 0;
	}

	nRet = CCodeEngine::Encode((uint8_t *)arrCrypt, sizeof(arrCrypt) - nOffset, nOffset, (uint8_t *)stPlayerSignature.m_arrServerBitMap, sizeof(stPlayerSignature.m_arrServerBitMap), sizeof(stPlayerSignature.m_arrServerBitMap));
	if(nRet < 0)
	{
		return 0;
	}

	nRet = CCodeEngine::Encode((uint8_t *)arrCrypt, sizeof(arrCrypt) - nOffset, nOffset, stPlayerSignature.m_nTimeStamp);
	if(nRet < 0)
	{
		return 0;
	}

	return CXTEA::Encrypt(arrCrypt, nOffset, arrToken, TOKEN_MAX_LEN, TOKEN_KEY);
}

