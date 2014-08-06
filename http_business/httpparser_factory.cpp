/*
 * httpparser_factory.cpp
 *
 *  Created on: Jul 29, 2014
 *      Author: jimm
 */

#include "httpparser_factory.h"
#include "http_packetparser.h"
#include "../common/common_memmgt.h"

CHttpParserFactory::CHttpParserFactory()
{

}

IPacketParser *CHttpParserFactory::Create()
{
	return NEW(CHttpPacketParser);
}

void CHttpParserFactory::Destory(IPacketParser *pParser)
{
	DELETE(pParser);
}


