/*
 * message_define.h
 *
 *  Created on: 2014ƒÍ7‘¬22»’
 *      Author: jimm
 */

#ifndef MESSAGE_DEFINE_H_
#define MESSAGE_DEFINE_H_

#include "../frame/frame.h"
#include "server_typedef.h"
#include <stdio.h>
#include <string.h>
#include <string>

using namespace FRAME;
using namespace std;

#define MSGID_CLIENTAUTH_REQ				0x00000010
class CAuthReq : public IMsgBody
{
public:
	CAuthReq();

	int32_t Encode(uint8_t* buf, const int32_t size, uint32_t& offset);

	int32_t Decode(const uint8_t *buf, const int32_t size, uint32_t& offset);

	void Dump(char* buf, const uint32_t size, uint32_t& offset);

	int8_t			m_nRoleIDLen;
	char			m_arrRoleID[MAX_UID_LEN];
	int8_t			m_nIsFirst;
	int8_t			m_nIPLen;
	char			m_arrIP[MAX_IP_LEN];
	int8_t			m_nSourceLen;
	char			m_arrSource[MAX_SOURCE_LEN];
	int16_t			m_nAppID;
	char			m_arrPassword[MAX_PSWD_LEN];
};

#define MSGID_CLIENTAUTH_RESP				0x00000002
class CAuthResp : public IMsgBody
{
public:
	CAuthResp();

	int32_t Encode(uint8_t* buf, const int32_t size, uint32_t& offset);

	int32_t Decode(const uint8_t *buf, const int32_t size, uint32_t& offset);

	void Dump(char* buf, const uint32_t size, uint32_t& offset);

	int16_t			m_nResult;
	uint32_t		m_nRoleID;
	uint32_t		m_nAccountID;
	int8_t			m_nRoleIDLen;
	char			m_arrEmail[MAX_EMAIL_LEN];
	char			m_arrSessionKey[MAX_SESSIONKEY_LEN];
	int8_t			m_nTokenLen;
	char			m_arrToken[TOKEN_MAX_LEN];
};

#define MSGID_HTTPLOGIN_RESP				0x0000000A
class CHttpLoginResp : public IMsgBody
{
public:
	CHttpLoginResp();

	int32_t Encode(uint8_t* buf, const int32_t size, uint32_t& offset);

	int32_t Decode(const uint8_t *buf, const int32_t size, uint32_t& offset);

	void Dump(char* buf, const uint32_t size, uint32_t& offset);

public:
	int32_t				m_nResult;
};


//◊¢≤·’ ∫≈«Î«Û
#define MSGID_AGAS_REGISTACCOUNT_REQ	0x00111701
class CRegistAccountReq : public IMsgBody
{
public:
	string		m_strEmail;
	string		m_strPassword;
	string		m_strConfirmPassword;
	string		m_strChannelID;
	string		m_strMacAddr;
};

//◊¢≤·’ ∫≈œÏ”¶
#define MSGID_AGAS_REGISTACCOUNT_REQ	0x00111701
class CRegistAccountResp : public IMsgBody
{
public:
	string		m_strPassport;
	string		m_strPlatform;
};


#endif /* MESSAGE_DEFINE_H_ */
