/*
 * session_data.h
 *
 *  Created on: Jul 30, 2014
 *      Author: jimm
 */

#ifndef SESSION_DATA_H_
#define SESSION_DATA_H_

#include "../../common/common_object.h"
#include "../../netevent/net_typedef.h"
#include "../../frame/frame_timer.h"
#include "../../frame/frame_typedef.h"
#include "../server_typedef.h"
#include "../server_helper.h"

using namespace FRAME;
using namespace NETEVENT;

class CSessionData : public CBaseObject
{
public:
	CSessionData()
	{
		Init();
	}

	virtual int32_t Init()
	{
		m_nTimerIndex = 0;
		m_nSessionIndex = enmInvalidSessionIndex;
		m_nSessionID = 0;
		m_pHandler = NULL;
		m_pCallBack = NULL;
		return 0;
	}

	virtual int32_t Uninit()
	{
		return 0;
	}

	virtual int32_t GetSize()
	{
		int32_t nParamSize = 0;
		if(m_pParam != NULL)
		{
			nParamSize = m_pParam->GetSize();
		}

		return sizeof(*this) + nParamSize;
	}

	void SetTimerIndex(TimerIndex nTimerIndex)
	{
		m_nTimerIndex = nTimerIndex;
	}

	TimerIndex GetTimerIndex()
	{
		return m_nTimerIndex;
	}

	void SetSessionIndex(SessionIndex nSessionIndex)
	{
		m_nSessionIndex = nSessionIndex;
	}

	SessionIndex GetSessionIndex()
	{
		return m_nSessionIndex;
	}

	void SetSessionID(SessionID nSessionID)
	{
		m_nSessionID = nSessionID;
	}

	SessionID GetSessionID()
	{
		return m_nSessionID;
	}

	void SetHandler(CBaseObject *pHandler)
	{
		m_pHandler = pHandler;
	}

	CBaseObject *GetHandler()
	{
		return m_pHandler;
	}

	void SetSessionCallBack(SessionCallBack CallBack)
	{
		m_pCallBack = CallBack;
	}

	SessionCallBack GetSessionCallBack()
	{
		return m_pCallBack;
	}

	void SetParam(CBaseObject *pParam)
	{
		m_pParam = pParam;
	}

	CBaseObject *GetParam()
	{
		return m_pParam;
	}

protected:
	TimerIndex		m_nTimerIndex;
	SessionIndex	m_nSessionIndex;
	SessionID		m_nSessionID;
	CBaseObject		*m_pHandler;
	SessionCallBack	m_pCallBack;
	CBaseObject		*m_pParam;
};


#endif /* SESSION_DATA_H_ */
