/*
 * main.cpp
 *
 *  Created on: 2014年7月21日
 *      Author: jimm
 */

#include <sys/stat.h>
#include <sys/types.h>
#include "../netevent/net_namespace.h"
#include "../netevent/net_impl.h"
#include "../netevent/net_typedef.h"
#include "../netevent/net_reactor.h"
#include "../netevent/net_handler.h"
#include "../netevent/net_connection.h"
#include "../netevent/net_acceptor.h"
#include "../netevent/net_connector.h"
#include "../logger/logger.h"
#include "../frame/frame.h"
#include "server_config.h"
#include "regist_message.h"
#include "server_typedef.h"
#include "client_agent/client_handler.h"
#include "client_agent/client_packetparser.h"
#include "client_agent/clientparser_factory.h"
#include "http_business/http_handler.h"
#include "http_business/http_packetparser.h"
#include "http_business/httpparser_factory.h"
#include "timer_handler.h"
#include "datacenter.h"
#include "session_bank/session_mgt.h"

using namespace LOGGER;
using namespace NETEVENT;
using namespace FRAME;

int32_t InitNet(CNetHandler *pNetHandler)
{
	CServerConfig *pServerConfig = (CServerConfig *)g_Frame.GetConfig(CONFIG_SERVER);
	if(pServerConfig == NULL)
	{
		return 1;
	}

	//创建包解析器工厂
	IPacketParserFactory *pParserFactory = new CClientParserFactory();

	CClientHandler *pClientHandler = new CClientHandler();

	//创建服务器
	CAcceptor *pAcceptor = new CAcceptor(pNetHandler, pParserFactory, pClientHandler);
	pAcceptor->Bind(pServerConfig->GetListenPort());

	NetNode arrNetNode[enmMaxNetNodeCount];
	int32_t nNetNodeCount = pServerConfig->GetAllNetNode(arrNetNode, enmMaxNetNodeCount);

	//创建连接器
	CConnector *pServerConnector = new CConnector(pNetHandler, pParserFactory, pClientHandler);
	pClientHandler->SetConnector(pServerConnector);

	for(int32_t i = 0; i < nNetNodeCount; ++i)
	{
		pServerConnector->Connect(arrNetNode[i].m_szPeerAddress, arrNetNode[i].m_nPeerPort);
	}

	CHttpBusiness *pHttpBusiness = new CHttpBusiness();
	CHttpHandler *pHttpHandler = new CHttpHandler();
	CConnector *pHttpConnector = new CConnector(pNetHandler, new CHttpParserFactory(), pHttpHandler);
	pHttpHandler->SetConnector(pHttpConnector);
	pHttpBusiness->SetConnector(pHttpConnector);

	g_DataCenter.SetHttpBusiness(pHttpBusiness);

	return 0;
}

int32_t InitTimer()
{
	CTimerHandler *pTimerHandler = new CTimerHandler();
	int32_t nTimerIndex = 0;
	g_Frame.CreateTimer(static_cast<TimerProc>(&CTimerHandler::HeartBeat),
		pTimerHandler, NULL, 60 * MS_PER_SECOND, true, nTimerIndex);

	g_DataCenter.SetTimerHandler(pTimerHandler);

	return 0;
}

int32_t main()
{
	//启动日志线程
	CLogger::Start();

	//创建网络事件处理器
	CNetHandler *pNetHandler = new CNetHandler();
	pNetHandler->CreateReactor();

	g_Frame.AddRunner(pNetHandler);

	if(g_Frame.Init(SERVER_NAME) != 0)
	{
		return 0;
	}

	g_DataCenter.SetFrame(&g_Frame);

	g_DataCenter.SetSessionMgt(new CSessionMgt());

	InitNet(pNetHandler);

	InitTimer();

	g_Frame.Run();

	g_Frame.Uninit();

	return 0;
}




