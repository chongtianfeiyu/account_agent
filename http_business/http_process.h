/*
 * http_process.h
 *
 *  Created on: Jul 30, 2014
 *      Author: jimm
 */

#ifndef HTTP_PROCESS_H_
#define HTTP_PROCESS_H_

#include "../frame/frame_typedef.h"

using namespace FRAME;

class CHttpProcess
{
public:
	static int32_t ProcessHttpLoginResp(IMsgHead *pMsgHead, IMsgBody *pMsgBody);
};



#endif /* HTTP_PROCESS_H_ */
