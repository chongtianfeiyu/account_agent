/*
 * http_req.h
 *
 *  Created on: Jul 29, 2014
 *      Author: jimm
 */

#ifndef HTTP_REQ_H_
#define HTTP_REQ_H_

#include "../../common/common_object.h"

class HttpReq : public CBaseObject
{
public:
	HttpReq()
	{
		m_nHttpReqLen = 0;
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
		return sizeof(*this) + m_nHttpReqLen;
	}

	uint32_t 		m_nHttpReqLen;	//³¤¶È
	uint8_t			m_pHttpReq[0];
};


#endif /* HTTP_REQ_H_ */
