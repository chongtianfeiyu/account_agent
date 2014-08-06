/*
 * session_mgt.h
 *
 *  Created on: Jul 30, 2014
 *      Author: jimm
 */

#ifndef SESSION_MGT_H_
#define SESSION_MGT_H_

#include "../server_typedef.h"
#include "session_data.h"
#include "session_timerhandler.h"
#include <map>

using namespace std;

typedef map<SessionIndex, CSessionData *> SessionMgt;

class CSessionMgt
{
public:
	CSessionMgt()
	{
		m_pSessionTimerHandler = new CSessionTimerHandler();
		m_nSessionCounter = 0;
	}

	~CSessionMgt()
	{
		if(m_pSessionTimerHandler != NULL)
		{
			delete m_pSessionTimerHandler;
		}
	}

	CSessionData * CreateSession(CBaseObject *pHandler, SessionCallBack CallBack, CBaseObject *pParam, SessionID nSessionID, int64_t nTimeOut);

	void DestroySession(SessionIndex nSessionIndex);

	CSessionData *GetSessionData(SessionIndex nSessionIndex);

protected:
	SessionIndex NextSessionIndex();

protected:
	CSessionTimerHandler	*m_pSessionTimerHandler;
	SessionIndex			m_nSessionCounter;
	SessionMgt				m_stSessionMgt;
};


#endif /* SESSION_MGT_H_ */
