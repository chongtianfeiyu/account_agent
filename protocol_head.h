/*
 * protocol_head.h
 *
 *  Created on: 2014年5月7日
 *      Author: jimm
 */

#ifndef PROTOCOL_HEAD_H_
#define PROTOCOL_HEAD_H_

#include "../common/common_codeengine.h"
#include "../common/common_errordef.h"
#include "../frame/frame_typedef.h"
#include "server_typedef.h"
#include <stdio.h>
#include <string>

using namespace std;
using namespace FRAME;

class PkgHead : public IMsgHead
{
public:
	PkgHead();
	virtual int32_t GetSize();

	int32_t Encode(uint8_t *pBuf, const int32_t nBufSize, uint32_t &nOffset);

	int32_t Decode(const uint8_t *pBuf, const int32_t nBufSize, uint32_t &nOffset);

	void Dump(char* buf, const uint32_t size, uint32_t& offset);

public:
	int8_t			m_nTag;
	int16_t			m_nTotalSize;	//数据包总大小
	int16_t			m_nHeadSize;	//包头大小
	int16_t			m_nMsgID;		//消息ID
	int16_t			m_nVersion;		//版本号
	int16_t			m_nFlag;
	int16_t			m_nOptionLen;	//选项内容大小
	uint8_t			m_arrOption[MAX_HEAD_OPTION_LEN];
};

class WebHeader : public IMsgHead
{
public:
	WebHeader();

	virtual int32_t GetSize();

	int32_t Encode(uint8_t *pBuf, const int32_t nBufSize, uint32_t &nOffset);

	int32_t Decode(const uint8_t *pBuf, const int32_t nBufSize, uint32_t &nOffset);

	void Dump(char* buf, const uint32_t size, uint32_t& offset);

	int32_t			m_nMsgID;
	int32_t			m_nRoomID;
	RoleID			m_nRoleID;
	SessionIndex	m_nSessionIndex;
};
#endif /* PROTOCOL_HEAD_H_ */

