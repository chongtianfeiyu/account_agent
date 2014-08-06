/*
 * web_packetparser.h
 *
 *  Created on: 2014年5月12日
 *      Author: jimm
 */

#ifndef WEB_PACKETPARSER_H_
#define WEB_PACKETPARSER_H_

#include "../netevent/net_namespace.h"
#include "../netevent/net_impl.h"
#include "../netevent/net_packet.h"

#include <string.h>

using namespace NETEVENT;

class CWebPacketParser : public IPacketParser
{
public:

	virtual ~CWebPacketParser(){};

	virtual int32_t Init();

	virtual int32_t Uninit();

	virtual int32_t GetSize();

	virtual int32_t Parser(const uint8_t arrBuf[], const uint32_t nBufSize, uint8_t arrPacket[], int32_t &nPacketSize);

};

#endif /* CLIENT_PACKETPARSER_H_ */
