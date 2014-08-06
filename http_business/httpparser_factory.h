/*
 * httpparser_factory.h
 *
 *  Created on: Jul 29, 2014
 *      Author: jimm
 */

#ifndef HTTPPARSER_FACTORY_H_
#define HTTPPARSER_FACTORY_H_

#include "../netevent/net_namespace.h"
#include "../netevent/net_impl.h"

using namespace NETEVENT;

class CHttpParserFactory : public IPacketParserFactory
{
public:
	CHttpParserFactory();

	virtual IPacketParser *Create();

	virtual void Destory(IPacketParser *pParser);
};


#endif /* HTTPPARSER_FACTORY_H_ */
