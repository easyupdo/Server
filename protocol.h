#pragma once

/*
LSX MSG format
#app protocol
 
 base:
	 ------------------------------------------------------
	|  package_num(4B)   |   msg_id(4B)     |   body(nB)   |
	 ------------------------------------------------------
1.
1001:客户端通知服务器将要发送语音数据     :1001
1002:服务器通知客户端可以发送语音数据
1003:客户端发送语音数据                  :一个语音包800B
1004:客户端发送语音数据结束
	 --------------------------------------------------------------------------------------
	|  package_num(4B)   |   msg_id(4B)   |    body(nB)   |    ack(4B)(1:finaish 0:error)  |
	 --------------------------------------------------------------------------------------
	
1005:服务器通知客户端语音数据接收完毕
	 --------------------------------------------------------------------------------------
	|  package_num(4B)   |   msg_id(4B)   |    body(nB)   |    ack(4B)(1:finaish 0:error)  |
	 --------------------------------------------------------------------------------------

1007:预留 客户端发送链接验证
1008:预留 客户端发送确认链接验证


*/
#include <iostream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

//struct _MSG;
//using LSX_MSG = struct _MSG;
//DYNAMIC



typedef struct _MSG
{
	char *head;			//msg head  not used
	char **msg_arr;		//all msg complete
}LXS_MSG;

typedef struct _HEADER LSX_HEADER;

class CProtocol
{
public:
	CProtocol() {};

	virtual LXS_MSG &GetMsg() = 0;

	/*
	@填充具体的消息体
	@参数1：消息存储体指针
	@参数2：组件消息的内容
	@参数3：组建消息开始位置
	@参数4：组建消息结束位置
	*/

	//virtual void AddHeadToMsg(char* msg_ptr, int msg_id, int msg_length) = 0;

	virtual void AddHeadToMsg(char* msg_ptr, void*header_prt) = 0;					
	virtual void AddBodyToMsg(char * msg_pt, char *byte, int begin, int end) = 0;	

	/*
	@解析消息
	*/
	virtual void ProtocolParser(char * data) = 0;

	/*
	@设置有几条协议
	*/
	virtual void SetMsgSize(int size) = 0;//msg num
	/*
	@用来设置每一条消息
	@参数1：消息id
	@参数2：消息长度
	@参数3：消息体
	//当前协议之有三种消息体 见协议
	*/
	virtual void InsertMsg(int msg_id, int msg_length) = 0;
	virtual void InsertMsg(int msg_id,int msg_length,char * body) = 0;
	virtual void InsertMsg(int msg_id, int msg_length, int body) = 0;

	/*
	@用来设置消息头 8字节 包大小+消息id
	@参数1：消息存储体指针
	@参数2：消息id
	@参数3：消息长度
	*/

	virtual ~CProtocol() {};

};


class APPProtocolIMPL;
class APPProtocol:public CProtocol
{
public:
	APPProtocol();

	virtual LXS_MSG &GetMsg();
	/*
	@填充具体的消息体
	@参数1：消息存储体指针
	@参数2：组件消息的内容
	@参数3：组建消息开始位置
	@参数4：组建消息结束位置
	*/
	//virtual void AddHeadToMsg(char* msg_ptr, int msg_id, int msg_length);

	virtual void AddHeadToMsg(char* msg_ptr, void*header_prt);
	virtual void AddBodyToMsg(char * msg_pt, char *byte, int begin, int end);

	/*
	@解析消息
	*/
	virtual void ProtocolParser(char * data);

	/*
	@设置有几条协议
	*/
	virtual void SetMsgSize(int size);//msg num
	/*
	@用来设置每一条消息
	@参数1：消息id
	@参数2：消息长度
	@参数3：消息体
	//当前协议之有三种消息体 见协议
	*/
	virtual void InsertMsg(int msg_id, int msg_length);
	virtual void InsertMsg(int msg_id,int msg_length,char * body);
	virtual void InsertMsg(int msg_id, int msg_length, int body);

	/*
	@用来设置消息头 8字节 包大小+消息id
	@参数1：消息存储体指针
	@参数2：消息id
	@参数3：消息长度
	*/

	virtual ~APPProtocol();
private:
	APPProtocolIMPL * _impl;

};


