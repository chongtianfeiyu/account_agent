/*
 * session_timerhandler.h
 *
 *  Created on: Jul 30, 2014
 *      Author: jimm
 */

#ifndef SESSION_TIMER_HANDLER_H_
#define SESSION_TIMER_HANDLER_H_

#include "../common/common_object.h"
#include "../frame/frame_timer.h"

using namespace FRAME;

class CSessionTimerHandler : public CBaseObject
{
public:

	CSessionTimerHandler()
	{
		Init();
	}

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
		return sizeof(*this);
	}

	int32_t ProcessSessionTimeout(CTimer *pTimer);
};


#endif /* SESSION_TIMER_HANDLER_H_ */
