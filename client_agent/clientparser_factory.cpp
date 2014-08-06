/*
 * clientparser_factory.cpp
 *
 *  Created on: 2014年5月13日
 *      Author: jimm
 */

#include "clientparser_factory.h"
#include "client_packetparser.h"
#include "../common/common_memmgt.h"

CClientParserFactory::CClientParserFactory()
{

}

IPacketParser *CClientParserFactory::Create()
{
	return NEW(CClientPacketParser);
}

void CClientParserFactory::Destory(IPacketParser *pParser)
{
	DELETE(pParser);
}
