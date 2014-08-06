/*
 * session_param.cpp
 *
 *  Created on: 2014年5月26日
 *      Author: jimm
 */

#include "session_param.h"

int32_t CSessionParam::Init()
{
	m_nEntityType = enmEntityType_None;
	m_nID = enmInvalidServerID;
	return 0;
}

int32_t CSessionParam::Uninit()
{
	return 0;
}

int32_t CSessionParam::GetSize()
{
	return sizeof(*this);
}

void CSessionParam::SetParamInfo(EntityType nEntityType, int32_t nID)
{
	m_nEntityType = nEntityType;
	m_nID = nID;
}

void CSessionParam::GetParamInfo(EntityType &nEntityType, int32_t &nID)
{
	nEntityType = m_nEntityType;
	nID = m_nID;
}



