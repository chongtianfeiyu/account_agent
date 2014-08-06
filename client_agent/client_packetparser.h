/*
 * client_packetparser.h
 *
 *  Created on: 2014年5月12日
 *      Author: jimm
 */

#ifndef CLIENT_PACKETPARSER_H_
#define CLIENT_PACKETPARSER_H_

#include "../netevent/net_namespace.h"
#include "../netevent/net_impl.h"
#include "../netevent/net_packet.h"

#include <string.h>

using namespace NETEVENT;

class CClientPacketParser : public IPacketParser
{
public:

	virtual ~CClientPacketParser(){};

	virtual int32_t Init();

	virtual int32_t Uninit();

	virtual int32_t GetSize();

	virtual int32_t Parser(const uint8_t arrBuf[], const uint32_t nBufSize, uint8_t arrPacket[], int32_t &nPacketSize);

};

#endif /* CLIENT_PACKETPARSER_H_ */
