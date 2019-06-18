#pragma once
#include "protocol.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//typedef map<string, string> http_reposer;

//200 OK //请求成功, 所请求信息在响应消息中返回
//301 Moved Permanently  //所请求的对象已永久迁移, 新的URL在本响应消息的（location：）头部指出
//400 Bad Request  //该请求不能被服务器解读
//404 Not Found  //服务器上不存在所请求文档
//505 HTTP Version Not Supported

enum body_type
{
	ASEC_STRING,
	ASEC_FILE,
};

class http_response
{
public:
	http_response();

	void AddStatusLineToMsg(string status_line);
	void AddHeadToMsg(string key,string value);
	void AddBodyToMsg(string body,body_type type);
	void ResposerClean();


	string operator+(string str);

	const string& GetResponse();


	~http_response();
private:
	
	string resposer;
};

