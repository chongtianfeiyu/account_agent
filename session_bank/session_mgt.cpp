/*
 * session_mgt.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: jimm
 */

#include "session_mgt.h"
#include "../../frame/frame.h"
#include "../../common/common_memmgt.h"

using namespace FRAME;

CSessionData *CSessionMgt::CreateSession(CBaseObject *pHandler, SessionCallBack CallBack, CBaseObject *pParam, SessionID nSessionID, int64_t nTimeOut)
{
	CSessionData *pSessionData = NEW(CSessionData);

	SessionIndex nSessionIndex = NextSessionIndex();
	m_stSessionMgt[nSessionIndex] = pSessionData;

	pSessionData->SetSessionIndex(nSessionIndex);
	pSessionData->SetSessionID(nSessionID);
	pSessionData->SetHandler(pHandler);
	pSessionData->SetSessionCallBack(CallBack);
	pSessionData->SetParam(pParam);

	TimerIndex nTimerIndex = -1;
	int32_t nRet = g_Frame.CreateTimer(static_cast<TimerProc>(&CSessionTimerHandler::ProcessSessionTimeout), m_pSessionTimerHandler, pSessionData, nTimeOut, false, nTimerIndex);
	if(nRet < 0)
	{
		DestroySession(nSessionIndex);
		return NULL;
	}

	pSessionData->SetTimerIndex(nTimerIndex);

	return pSessionData;
}

void CSessionMgt::DestroySession(SessionIndex nSessionIndex)
{
	CSessionData *pSessionData = GetSessionData(nSessionIndex);
	if(pSessionData == NULL)
	{
		return;
	}

	DELETE(pSessionData);

	SessionMgt::iterator it = m_stSessionMgt.find(nSessionIndex);
	if(it != m_stSessionMgt.end())
	{
		m_stSessionMgt.erase(it);
	}

	g_Frame.RemoveTimer(it->second->GetTimerIndex());
}

CSessionData *CSessionMgt::GetSessionData(SessionIndex nSessionIndex)
{
	SessionMgt::iterator it = m_stSessionMgt.find(nSessionIndex);
	if(it != m_stSessionMgt.end())
	{
		return it->second;
	}

	return NULL;
}

SessionIndex CSessionMgt::NextSessionIndex()
{
	SessionIndex nSessionIndex = ++m_nSessionCounter;
	if(m_nSessionCounter >= 100 * 10000)
	{
		m_nSessionCounter = 0;
	}

	return nSessionIndex;
}
