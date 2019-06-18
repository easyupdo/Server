#pragma once
//socket bind listen  accpet
//socket  connet
#include "http-parser\http_parser.h"
#include <iostream>
#include <string>
#include "libuv\include\uv.h"
#include <fstream>
#include "protocol.h"
#include <map>
#include "http_response.h"


#define DEFAULT_BACKLOG 128


typedef struct SSCORE
{
	float score;
	float svm_score;
}sscore;



typedef sscore(*service_cb)(std::string wav_filename, std::string psdata_dir, std::string model_dir);//score fun
#define SERVICE					\
	service_cb cb_score;		\
	std::string wav_filename;	\
	std::string psdata;			\
	std::string model_dir;		\

struct Service
{
	SERVICE
};

//http parser struct

//#define HTTPREQUESTINFO	                      \
//	char *method;				  \
//	char *url;					  \
//	char *body;					  \
//	unsigned int flags;                       \
//	unsigned short http_major;				  \
//	unsigned short http_minor;				  \
//	//struct http_header *headers;             \
//	
//typedef struct HTTPPARSERINFO
//{
//	HTTPREQUESTINFO
//}http_parser_info;



static uv_loop_t * loop;
static Service service;//c fun


using parser_headers = map<string, string>;

class TCPServer
{
public:
	TCPServer();//socket,bind
	//interfase
	void Start(std::string address, int port);
	void SetService(std::string wav_filename, std::string psdata_dir, std::string model_dir,service_cb score);
	int Listen();
	void Run();

	void ReadConfig();
	void SetRootDir(string root_dir); //config set the dir



	
	//impl

	std::string ResultScoreJson();//to client result 


	//uv call back
	static void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
	static void echo_write(uv_write_t *req, int status);
	static void on_close(uv_handle_t* peer);
	static void echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);
	static void On_New_Connection(uv_stream_t* server, int status);

	

	//http call back
	static int on_message_begin_cb(http_parser *parser);
	static int on_url_cb(http_parser *parser, const char *buf, size_t len);
	static int on_status_cb(http_parser *parser, const char *buf, size_t len);
	static int on_header_field_cb(http_parser *parser, const char *buf, size_t len);
	static int on_header_value_cb(http_parser *parser, const char *buf, size_t len);
	static int on_headers_complete_cb(http_parser *parser);
	static int on_body_cb(http_parser *parser, const char *buf, size_t len);
	static int on_message_complete_cb(http_parser *parser);
	static int on_chunk_header_cb(http_parser*parser);
	static int on_chunk_complete_cb(http_parser*parser);

	static void SetParserHeader(http_parser *parser, const char *buf, size_t len, string &parser_XX);
	
	//static fun

	void HTTPParserInit(http_parser *parser, enum http_parser_type type);
	static void HTTPParserExec(http_parser *parser, http_parser_settings * settings, char *buf, size_t len);
	static bool IsOneMessageBuf(char * buf);

	static void AddAvailableMessageBuf(char * buf);

	static bool IsGetContentLength();
	static string GetOneHeader(parser_headers &headers,string header_name);
	static string GetOneHeader(char * avalible, string header_name);

	static void ParserClean();

	//
	bool ServiceType()
	{

	}
	
	

	~TCPServer();

private:
	struct sockaddr_in addr;
	uv_tcp_t server;
	static string root_dir;	//server root dir

	static http_parser_settings parser_settings;
	static http_parser *parser;// static fun use
	static CProtocol *LSX_protocol; //static fun use
	//static http_parser_info parser_info;

	//parser info
	static string parser_method;
	static string parser_url;
	static string parser_version;
	static string parser_body;
	static map<string, string>parser_header;

	static string header_field_tmp;
	static string header_value_tmp;

	//responser
	static http_response *responser;
	static int read_num;

	static char available_buf[1024];

	
};



