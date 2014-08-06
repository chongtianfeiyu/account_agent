/*
 * regist_message.h
 *
 *  Created on: 2014年1月22日
 *      Author: jimm
 */

#ifndef REGIST_MESSAGE_H_
#define REGIST_MESSAGE_H_

#include "../frame/frame.h"
#include "protocol_head.h"
#include "message_define.h"
#include "client_agent/auth_handler.h"

using namespace FRAME;

MSGMAP_BEGIN(msgmap)
ON_PROC_PMH_PMB(MSGID_CLIENTAUTH_REQ, PkgHead, CAuthReq, CAuthHandler, CAuthHandler::OnAuthMessageEvent);
MSGMAP_END(msgmap)


#endif /* REGIST_MESSAGE_H_ */

