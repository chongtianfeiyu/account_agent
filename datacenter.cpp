/*
 * datacenter.cpp
 *
 *  Created on: 2014年5月13日
 *      Author: jimm
 */

#include "datacenter.h"
#include "server_config.h"

CDataCenter::CDataCenter()
{
	m_pFrame = NULL;
	m_nConnCount = 0;
	m_pTimerHandler = NULL;
	m_pHttpBusiness = NULL;
}

void CDataCenter::SetFrame(CFrame *pFrame)
{
	m_pFrame = pFrame;
}

CFrame *CDataCenter::GetFrame()
{
	return m_pFrame;
}

void CDataCenter::SetTimerHandler(CTimerHandler *pTimerHandler)
{
	m_pTimerHandler = pTimerHandler;
}

CTimerHandler *CDataCenter::GetTimerHandler()
{
	return m_pTimerHandler;
}

void CDataCenter::SetHttpBusiness(CHttpBusiness *pHttpBusiness)
{
	m_pHttpBusiness = pHttpBusiness;
}

CHttpBusiness *CDataCenter::GetHttpBusiness()
{
	return m_pHttpBusiness;
}

void CDataCenter::SetSessionMgt(CSessionMgt *pSessionMgt)
{
	m_pSessionMgt = pSessionMgt;
}

CSessionMgt *CDataCenter::GetSessionMgt()
{
	return m_pSessionMgt;
}

int32_t CDataCenter::IncConnCount()
{
	return ++m_nConnCount;
}

int32_t CDataCenter::DecConnCount()
{
	return --m_nConnCount;
}


