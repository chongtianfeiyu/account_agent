/*
 * webparser_factory.cpp
 *
 *  Created on: 2014年5月13日
 *      Author: jimm
 */

#include "webparser_factory.h"
#include "web_packetparser.h"
#include "../common/common_memmgt.h"

CWebParserFactory::CWebParserFactory()
{

}

IPacketParser *CWebParserFactory::Create()
{
	return NEW(CWebPacketParser);
}

void CWebParserFactory::Destory(IPacketParser *pParser)
{
	DELETE(pParser);
}
