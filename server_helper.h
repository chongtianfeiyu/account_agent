/*
 * server_helper.h
 *
 *  Created on: 2014年5月14日
 *      Author: jimm
 */

#ifndef SERVER_HELPER_H_
#define SERVER_HELPER_H_

#include "../common/common_object.h"
#include "../frame/frame_typedef.h"
#include "../netevent/net_impl.h"
#include "../logger/logger.h"
#include "protocol_head.h"
#include "server_typedef.h"
#include "../rapidjson/document.h"

#include <map>
#include <string>
using namespace std;

using namespace LOGGER;
using namespace FRAME;
using namespace NETEVENT;
using namespace rapidjson;

typedef map<ServerID, IIOSession *> IDMap;
typedef map<EntityType, IDMap> EntityMap;

typedef int32_t (CBaseObject::*SessionCallBack)(CBaseObject *pObject, CBaseObject *pParam);
#define HTTP_GET_REQ	"GET %s HTTP/1.1\r\nHost: client.69xiu.com\r\nConnection: keep-alive\r\n\r\n"

class CServerHelper : public CBaseObject
{
public:
	virtual int32_t Init()
	{
		return 0;
	}

	virtual int32_t Uninit()
	{
		return 0;
	}

	virtual int32_t GetSize()
	{
		return sizeof(*this);
	}

	static int32_t SendMsg(uint8_t *pBuf, int32_t nBufSize, EntityType nEntityType, ServerID nServerID = enmInvalidServerID);

	static void RegistSessionInfo(EntityType nEntityType, int32_t nID, IIOSession *pIoSession);

	static void UnregistSessionInfo(IIOSession *pIoSession);

	static IIOSession *GetIoSession(EntityType nEntityType, int32_t nID);

	static IIOSession *GetOneIoSession(EntityType nEntityType);

	static bool IsExist(Document &document, const char *szKey);

	static bool GetInt(Document &document, const char *szKey, int32_t &nValue);

	static bool GetString(Document &document, const char *szKey, string &nValue);

	static bool GetValue(Document &document, const char *szKey, Value &nValue);

	static bool IsExist(Value &value, const char *szKey);

	static bool GetInt(Value &value, const char *szKey, int32_t &nValue);

	static bool GetString(Value &value, const char *szKey, string &nValue);

	static bool GetValue(Value &value, const char *szKey, Value &nValue);

	static int32_t MakeToken(char arrToken[], int32_t nRoleID);
protected:
	static EntityMap		m_stEntityMap;
};


#endif /* SERVER_HELPER_H_ */
