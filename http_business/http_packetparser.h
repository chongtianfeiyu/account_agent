/*
 * http_packetparser.h
 *
 *  Created on: Jul 29, 2014
 *      Author: jimm
 */

#ifndef HTTP_PACKETPARSER_H_
#define HTTP_PACKETPARSER_H_

#include "../netevent/net_namespace.h"
#include "../netevent/net_impl.h"
#include "../netevent/net_packet.h"

#include <string.h>

using namespace NETEVENT;

class CHttpPacketParser : public IPacketParser
{
public:

	CHttpPacketParser();

	virtual ~CHttpPacketParser(){};

	virtual int32_t Init();

	virtual int32_t Uninit();

	virtual int32_t GetSize();

	virtual int32_t Parser(const uint8_t arrBuf[], const uint32_t nBufSize, uint8_t arrPacket[], int32_t &nPacketSize);

protected:
	char		m_arrFilterFlag[32];

};


#endif /* HTTP_PACKETPARSER_H_ */
