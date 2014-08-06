/*
 * datacenter.h
 *
 *  Created on: 2014年5月12日
 *      Author: jimm
 */

#ifndef DATACENTER_H_
#define DATACENTER_H_

#include "../common/common_singleton.h"
#include "../netevent/net_impl.h"
#include "../frame/frame.h"
#include "server_typedef.h"
#include "timer_handler.h"
#include "http_business/http_business.h"
#include "session_bank/session_mgt.h"

using namespace NETEVENT;
using namespace FRAME;

#include <map>
#include <string>
using namespace std;

typedef map<string, CMediaChannel *>	SessionChannelMap;

class CDataCenter
{
public:
	CDataCenter();

	void SetFrame(CFrame *pFrame);

	CFrame *GetFrame();

	void SetTimerHandler(CTimerHandler *pTimerHandler);

	CTimerHandler *GetTimerHandler();

	void SetHttpBusiness(CHttpBusiness *pHttpBusiness);

	CHttpBusiness *GetHttpBusiness();

	void SetSessionMgt(CSessionMgt *pSessionMgt);

	CSessionMgt *GetSessionMgt();

	int32_t IncConnCount();

	int32_t DecConnCount();

private:
	CFrame					*m_pFrame;
	int32_t					m_nConnCount;
	SessionChannelMap		m_stSessionChannelMap;
	CTimerHandler			*m_pTimerHandler;
	CHttpBusiness			*m_pHttpBusiness;
	CSessionMgt				*m_pSessionMgt;
};

#define g_DataCenter		CSingleton<CDataCenter>::GetInstance()

#endif /* DATACENTER_H_ */
