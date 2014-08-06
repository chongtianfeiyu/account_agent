/*
 * timer_handler.cpp
 *
 *  Created on: 2014年6月10日
 *      Author: jimm
 */

#include "timer_handler.h"
#include "../common/common_datetime.h"
#include "../netevent/net_impl.h"

using namespace NETEVENT;

int32_t CTimerHandler::HeartBeat(CTimer *pTimer)
{
	int64_t nCurTime = CTimeValue::CurrentTime().Seconds();

	int32_t nIndex = m_nCurIndex;
	m_nCurIndex = m_nIdleIndex;
	m_nIdleIndex = nIndex;

	return 0;
}


