/*
 * auth_handler.h
 *
 *  Created on: Jul 28, 2014
 *      Author: jimm
 */

#ifndef AUTH_HANDLER_H_
#define AUTH_HANDLER_H_

#include "../../common/common_object.h"
#include "../frame/frame_typedef.h"
#include "../server_helper.h"
#include "../session_bank/session_data.h"
#include "../message_define.h"

using namespace FRAME;

class CAuthHandler : public CServerHelper
{
public:
	class CAuthParam : public CBaseObject
	{
	public:
		virtual int32_t Init()
		{
			return 0;
		}

		virtual int32_t Uninit()
		{
			return 0;
		}

		virtual int32_t GetSize()
		{
			return 0;
		}

		PkgHead		m_stPkgHead;
		CAuthReq	m_stAuthReq;
	};

	int32_t OnAuthMessageEvent(CBaseObject *pObject, IMsgHead *pMsgHead, IMsgBody *pMsgBody);

	int32_t OnAuthTimeout(CBaseObject *pObject, CBaseObject *pParam);

private:
	int32_t SendAuthReq(IIOSession *pIoSession, IMsgHead *pMsgHead, IMsgBody *pMsgBody);
};


#endif /* AUTH_HANDLER_H_ */
