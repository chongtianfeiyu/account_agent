/*
 * clientparser_factory.h
 *
 *  Created on: 2014年5月12日
 *      Author: jimm
 */

#ifndef CLIENTPARSER_FACTORY_H_
#define CLIENTPARSER_FACTORY_H_

#include "../netevent/net_namespace.h"
#include "../netevent/net_impl.h"

using namespace NETEVENT;

class CClientParserFactory : public IPacketParserFactory
{
public:
	CClientParserFactory();

	virtual IPacketParser *Create();

	virtual void Destory(IPacketParser *pParser);
};


#endif /* CLIENTPARSER_FACTORY_H_ */
