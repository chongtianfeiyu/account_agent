/*
 * webparser_factory.h
 *
 *  Created on: 2014年5月12日
 *      Author: jimm
 */

#ifndef WEBPARSER_FACTORY_H_
#define WEBPARSER_FACTORY_H_

#include "../netevent/net_namespace.h"
#include "../netevent/net_impl.h"

using namespace NETEVENT;

class CWebParserFactory : public IPacketParserFactory
{
public:
	CWebParserFactory();

	virtual IPacketParser *Create();

	virtual void Destory(IPacketParser *pParser);
};


#endif /* WEBPARSER_FACTORY_H_ */
