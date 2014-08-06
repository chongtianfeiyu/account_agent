/*
 * server_typedef.h
 *
 *  Created on: 2014年5月6日
 *      Author: jimm
 */

#ifndef SERVER_TYPEDEF_H_
#define SERVER_TYPEDEF_H_

#include "../common/common_typedef.h"
#include "../common/common_object.h"
#include <stddef.h>
#include <string.h>

#define SERVER_NAME			"account_agent"
#define CONFIG_SERVER		"./server_config.xml"

typedef uint8_t						MessageType;		//消息类型
enum
{
	enmMessageType_None				= 0x00,				//无效值
	enmMessageType_Request			= 0x01,				//请求
	enmMessageType_Response			= 0x02,				//响应
	enmMessageType_Notify			= 0x03,				//通知
	enmMessageType_Other			= 0x04,				//其他
};

typedef uint8_t						TransType;			//传输类型
enum
{
	enmTransType_None				= 0xFF,				//无效值
	enmTransType_P2P				= 0,				//点对点
	enmTransType_P2G				= 1,				//组播
	enmTransType_Broadcast			= 2,   				//广播
	enmTransType_ByKey				= 3,				//根据关键字转发
	enmTransType_Regist				= 4,				//Server注册
	enmTransType_Ramdom				= 5,				//在指定的目的servertype中随机选择一个发送
	enmTransType_Disconnect         = 6,				//server链接断开
};

typedef uint8_t					EntityType;
//服务器类型
enum
{
	enmEntityType_None				= 0x00,				//无效值

	enmEntityType_Example			= 0x01,				//样例服务器
	enmEntityType_Router			= 0x02,				//路由器
	enmEntityType_Connect			= 0x03,				//网络连接服务器
	enmEntityType_Hall				= 0x04,				//大厅服务器
	enmEntityType_Media				= 0x05,				//媒体服务器
	enmEntityType_Tunnel			= 0x06,				//后端网络服务器
	enmEntityType_Room				= 0x07,				//房间服务器
	enmEntityType_Item				= 0x08,				//道具服务器
	enmEntityType_DBProxy			= 0x09,				//数据库代理服务器， 专门做写服务
	enmEntityType_WebConn           = 0x0A,             //web连接服务器
	enmEntityType_Webagent          = 0x0B,             //与官网交互的代理服务器(主要功能为web与后端server之间的协议转换)
	enmEntityType_Account			= 0x0C,				//账号注册服务器
	enmEntityType_SysInfo			= 0x0D,				//系统消息服务器
	enmEntityType_Daemon			= 0x0E,				//守护精灵
	enmEntityType_RoomDispatcher	= 0x10,				//房间分发服务器
	enmEntityType_DBProxyRead       = 0x11,             //专门做读服务的dbproxy
	enmEntityType_Task              = 0x12,             //任务服务器
	enmEntityType_NewWebConn        = 0x13,             //新版web连接服务器, 十进制为19
	enmEntityType_HallDataCenter    = 0x14,             //大厅数据备份服务器
	enmEntityType_ClientGame        = 0x15,             //客户端游戏服务器
	enmEntityType_Transmiter		= 0x16,				//媒体中转服务器
	enmEntityType_AccountAgent		= 0x17,				//帐号代理服务器

	enmEntityType_Count				= 0x17,				//服务器类型个数
	enmEntityType_Client			= 0x80,				//客户端
	enmEntityType_Web				= 0x81,				//web客户端
};

typedef uint8_t					ServerID;
enum
{
	enmInvalidServerID			= 0x00,
};

typedef int32_t					RoleID;
enum
{
	enmInvalidRoleID			= 0x00,
};

typedef int32_t					SessionIndex;
enum
{
	enmInvalidSessionIndex		= -1,		//无效的会话索引
};

enum
{
	enmMaxConfigFileNameSize	= 1024,		//配置文件名长度
	enmMaxPacketTokenSize		= 64,		//最大包分割字符串长度
	enmIPV4NetAddressSize		= 16,		//IPV4网络地址长度
	enmMaxNetNodeCount			= 32,		//最大连接的服务器数量

	//token相关的最大值定义
	MAX_CLIENT_MSG_LEN				= 2048,
	MAX_SERVER_MSG_LEN				= 2048,
	MAX_HEAD_OPTION_LEN				= 128,
	MAX_ERRMSG_LEN					= 256,
	MAX_UID_LEN						= 64,
	MAX_EMAIL_LEN					= MAX_UID_LEN,
	MAX_IP_LEN 						= 32,
	MAX_SOURCE_LEN 					= 64,
	MAX_PSWD_LEN 					= 32,
	MAX_URL_LEN 					= 256,
	MAX_SESSIONKEY_LEN				= 16,
	TOKEN_MAX_LEN					= 1024,
};

//与签名认证相关信息
enum
{
	auth_service_key_length			= 16,	//与认证服务器约定的密钥长度
	crypt_key_length				= 16,	//与客户端的通讯使用的加密密钥长度

	max_signature_valid_period		= 43200,//(12*60*60) 12小时
	min_signature_valid_period		= 3600,	//60*60	1小时

	max_encrypt_key_length = 16,			/**< 加密密钥的长度*/
	max_email_addr_length  = 32,           //签名中的邮箱的长度
	max_server_bitmap_length = 16,         //签名中的serverbitmap的长度
};

class PlayerSignature
{
public:
	PlayerSignature()
	{
		memset(m_arrKey, 0, sizeof(m_arrKey));
		m_nRoleID = enmInvalidRoleID;
		memset(m_arrServerBitMap, 0, sizeof(m_arrServerBitMap));
		m_nTimeStamp = 0;
	}

public:
	uint8_t		m_arrKey[max_encrypt_key_length];
	RoleID		m_nRoleID;
	uint8_t		m_arrServerBitMap[max_server_bitmap_length];
	int32_t		m_nTimeStamp;
};

struct NetNode
{
public:
	NetNode()
	{
		memset(m_szPeerAddress, 0, sizeof(m_szPeerAddress));
		m_nPeerPort = 0;
		m_nPeerType = enmEntityType_None;
		m_nPeerID = 0;
	}

	char			m_szPeerAddress[enmIPV4NetAddressSize];
	uint16_t		m_nPeerPort;
	int32_t			m_nPeerType;
	int32_t			m_nPeerID;
};

#endif /* SERVER_TYPEDEF_H_ */

