/*
 * session_timerhandler.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: jimm
 */

#include "session_timerhandler.h"
#include "../../netevent/net_connmgt.h"
#include "../datacenter.h"

using namespace NETEVENT;

int32_t CSessionTimerHandler::ProcessSessionTimeout(CTimer *pTimer)
{
	CSessionData *pSessionData = (CSessionData *)pTimer->GetTimerData();
	CServerHelper *pServerHelper = (CServerHelper *)pSessionData->GetHandler();
	SessionCallBack CallBack = pSessionData->GetSessionCallBack();
	SessionID nSessionID = pSessionData->GetSessionID();

	IIOSession *pIoSession = g_ConnMgt.GetConnection(nSessionID);
	if(pIoSession != NULL)
	{
		(pServerHelper->*CallBack)(pIoSession, pSessionData->GetParam());
	}

	g_DataCenter.GetSessionMgt()->DestroySession(pSessionData->GetSessionIndex());

	return 0;
}


