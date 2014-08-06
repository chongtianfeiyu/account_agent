/*
 * http_business.h
 *
 *  Created on: Jul 29, 2014
 *      Author: jimm
 */

#ifndef HTTP_BUSINESS_H_
#define HTTP_BUSINESS_H_

#include "../../netevent/net_connector.h"
#include "http_req.h"
#include <list>
using namespace NETEVENT;
using namespace std;

class CHttpBusiness
{
public:
	void SetConnector(CConnector *pConnector);

	int32_t Write(uint8_t *pBuf, int32_t nBufSize);

	int32_t Read(uint8_t arrBuf[], int32_t nBufSize);
private:
	CConnector			*m_pConnector;
	list<HttpReq *>		m_stHttpReqQueue;
};


#endif /* HTTP_BUSINESS_H_ */
