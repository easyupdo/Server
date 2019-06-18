// net_part_c_libuv.cpp: 定义控制台应用程序的入口点。
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
//#include <partc-score-export.h>
#include <iostream>
#include <string>
#include "http-parser\http_parser.h"

//
//#define DEFAULT_PORT 7002
//#define DEFAULT_BACKLOG 128
//
//int read_num = 0;
//typedef struct SSCORE
//{
//	float score;
//	float svm_score;
//}sscore;
//
//
////http_parser	的回调函数，需要获取HEADER后者BODY信息，可以在这里面处理。
//
///*
//http_cb      on_message_begin;
//http_data_cb on_url;
//http_data_cb on_status;
//http_data_cb on_header_field;
//http_data_cb on_header_value;
//http_cb      on_headers_complete;
//http_data_cb on_body;
//http_cb      on_message_complete;
//
//http_cb      on_chunk_header;
//http_cb      on_chunk_complete; */
//
///*	.on_message_begin = on_message_begin,
//	.on_header_field = on_header_field,
//	.on_header_value = on_header_value,
//	.on_url = on_url,
//	.on_status = 0,
//	.on_body = on_body,
//	.on_headers_complete = on_headers_complete,
//	.on_message_complete = on_message_complete*/
//
//int on_message_begin(http_parser* _) {
//	(void)_;
//	printf("\n***MESSAGE BEGIN***\n\n");
//	return 0;
//}
//
//int on_headers_complete(http_parser* _) {
//	(void)_;
//	printf("\n***HEADERS COMPLETE***\n\n");
//	return 0;
//}
//
//int on_message_complete(http_parser* _) {
//	(void)_;
//	printf("\n***MESSAGE COMPLETE***\n\n");
//	return 0;
//}
//
//int on_url(http_parser* _, const char* at, size_t length) {
//	(void)_;
//	printf("Url: %.*s\n", (int)length, at);
//	return 0;
//}
//
//int on_header_field(http_parser* _, const char* at, size_t length) {
//	(void)_;
//	printf("Header field: %.*s\n", (int)length, at);
//	return 0;
//}
//
//int on_header_value(http_parser* _, const char* at, size_t length) {
//	(void)_;
//	printf("Header value: %.*s\n", (int)length, at);
//	return 0;
//}
//
//int on_body(http_parser* _, const char* at, size_t length) {
//	(void)_;
//	printf("Body: %.*s\n", (int)length, at);
//	return 0;
//}
//
//static http_parser_settings settings_null =
//{
//	on_message_begin,
//	on_url,
//	0,
//	on_header_field,
//	on_header_value,
//	on_headers_complete,
//	on_body,
//	on_message_complete
//};
//
//static http_parser *parser;
//void http_parser_test()
//{
//	const char *buf;
//	int i;
//	float start, end;
//	size_t parsed;
//
//	parser = (http_parser*)malloc(sizeof(http_parser));  //分配一个http_parser
//
//	buf = "GET http://admin.omsg.cn/uploadpic/2016121034000012.png HTTP/1.1\r\nHost: admin.omsg.cn\r\nAccept: */*\r\nConnection: Keep-Alive\r\n\r\n";
//
//	start = (float)clock() / CLOCKS_PER_SEC;
//	for (i = 0; i < 1; i++) 
//	{
//		http_parser_init(parser, HTTP_REQUEST);  //初始化parser为Request类型
//		parsed = http_parser_execute(parser, &settings_null, buf, strlen(buf));  //执行解析过程
//		printf("URL:%s\n", parser->data);
//	}
//	end = (float)clock() / CLOCKS_PER_SEC;
//
//	buf = "HTTP/1.1 200 OK\r\n"
//		"Date: Tue, 04 Aug 2009 07:59:32 GMT\r\n"
//		"Server: Apache\r\n"
//		"X-Powered-By: Servlet/2.5 JSP/2.1\r\n"
//		"Content-Type: text/xml; charset=utf-8\r\n"
//		"Connection: close\r\n"
//		"\r\n"
//		"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
//		"<SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\">\n"
//		"  <SOAP-ENV:Body>\n"
//		"    <SOAP-ENV:Fault>\n"
//		"       <faultcode>SOAP-ENV:Client</faultcode>\n"
//		"       <faultstring>Client Error</faultstring>\n"
//		"    </SOAP-ENV:Fault>\n"
//		"  </SOAP-ENV:Body>\n"
//		"</SOAP-ENV:Envelope>";
//
//	http_parser_init(parser, HTTP_RESPONSE);  //初始化parser为Response类型
//	parsed = http_parser_execute(parser, &settings_null, buf, strlen(buf));  //执行解析过程
//
//	free(parser);
//	parser = NULL;
//
//	printf("Elapsed %f seconds.\n", (end - start));
//
//}
//
//
//	
//
//
//sscore score(std::string wav_filename, std::string psdata_dir, std::string model_dir)
//{
//	FILE *rawfh;
//	size_t nread;
//	short buf[2048];
//	float score;
//	int ret = 0;
//	char *model = const_cast<char*>("model");
//	char *psdata = const_cast<char*>("pstata");
//	//char *wav;
//
//	CPartCScore partc_score;
//
//	//printf("启动评测引擎！\n");
//	__int64 engine = partc_score.AsecRetEngineStart(const_cast<char*>(model_dir.c_str()));		//启动引擎，model为存放模型的文件夹
//
//																								//printf("%s ", wav);																	//printf("开始评测任务！\n");
//	ret = partc_score.AsecRetScStart(engine, const_cast<char*>(psdata_dir.c_str()));          //开始评测任务，ps_data为存放题目评测数据的文件夹
//
//	rawfh = fopen(wav_filename.c_str(), "rb");
//	fseek(rawfh, 44, SEEK_SET);									//跳过44字节wav文件头
//	while (!feof(rawfh))
//	{
//		nread = fread(buf, sizeof(*buf), 2048, rawfh);
//		ret = partc_score.AsecRetScPcmIn(engine, buf, nread);     //输入语音数据
//	}
//	fclose(rawfh);
//
//	//printf("语音结束，正在评分...\n");
//	ret = partc_score.AsecRetScEnd(engine);                       //语音结束，进行评分
//
//	score = partc_score.AsecRetGetScore(engine);				 //获取得分
//	double svm_score = partc_score.AsecRetGetScoreByType(engine, 2);
//	printf("score:%.1f svm_score:%.1f\n", score, svm_score);
//
//	//printf("关闭评测引擎！\n");
//	partc_score.AsecRetEngineEnd(engine);						//结束引擎
//	sscore s_score;
//	s_score.score = score;
//	s_score.svm_score = svm_score;
//	return s_score;
//}
//
//
//uv_loop_t *loop;
//struct sockaddr_in addr;
//
//void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
//{
//	buf->base = (char*)malloc(suggested_size);
//	memset(buf->base, 0, suggested_size);
//	buf->len = suggested_size;
//}
//
//void echo_write(uv_write_t *req, int status)
//{
//	if (status)
//	{
//		fprintf(stderr, "Write error %s\n", uv_strerror(status));
//	}
//	free(req);
//}
//
//static void on_close(uv_handle_t* peer)
//{
//	free(peer);
//}
//void echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
//{
//	if (nread < 0)
//	{
//		if (nread != UV_EOF)
//			fprintf(stderr, "Read error %s\n", uv_err_name(nread));
//		uv_close((uv_handle_t*)client, NULL);
//	}
//	else if (nread > 0)
//	{
//		/*uv_write_t *req = (uv_write_t *) malloc(sizeof(uv_write_t));
//		uv_buf_t wrbuf = uv_buf_init(buf->base, nread);
//		uv_write(req, client, &wrbuf, 1, echo_write);*/
//	}
//
//	read_num = read_num + nread;
//
//	//http_parser_settings settings;
//	//settings.on_url = my_url_callback;
//	//settings.on_header_field = my_header_field_callback;
//	///* ... */
//	//// 为结构体申请内存
//	//http_parser *parser = malloc(sizeof(http_parser));
//	//// 初始化解析器
//	//http_parser_init(parser, HTTP_REQUEST);
//	//// 设置保存调用者的数据，用于在callback内使用
//	//parser->data = my_socket;
//
//	//nparsed = http_parser_execute(parser, &settings, buf, recved);
//	//// 如果解析到websocket请求
//	//if (parser->upgrade) {
//	//	/* handle new protocol */
//	//	// 如果解析出错，即解析完成的数据大小不等于传递给http_parser_execute的大小
//	//}
//	//else if (nparsed != recved) {
//	//	/* Handle error. Usually just close the connection. */
//	//}
//
//
//	std::ofstream ofs("E:\\nowWork\\CA\\Server_Project\\Libuv\\test_libuv\\net\\net_test_libuv\\net_server_libuv\\wav.wav", std::ios::app | std::ios::binary);
//	if (ofs.is_open())
//	{
//		ofs.write(buf->base, nread);
//	}
//	else
//		std::cout << errno;
//	ofs.close();
//
//
//	if (buf->base)
//		free(buf->base);
//
//	printf("nread:%d\n", nread);
//	printf("all_read:%d", read_num);
//	printf("url:%s\n",buf->base);
//
//	parser = (http_parser*)malloc(sizeof(http_parser));  //分配一个http_parser
//	http_parser_init(parser, HTTP_REQUEST);  //初始化parser为Request类型
//	int parsed = http_parser_execute(parser, &settings_null, buf->base, strlen(buf->base));  //执行解析过程
//
//
//		std::string result =("HTTP/1.1 200 OK\r\n\
//Content-Type: text/plain\r\n\
//Connection: keep-alive\r\n\r\n");
//		char ch[1024];
//		memset(ch,0,1024);
//
//		std::ifstream ifs("E:\\nowWork\\CA\\Server_Project\\Libuv\\test_libuv\\net\\net_test_libuv\\net_server_libuv\\Debug\\index.html");
//		if (ifs.is_open())
//		{
//			ifs.read(ch,1024);
//		}
//		ifs.close();
//		
//		std::string all_result = result + ch;
//
//	http_parser_init(parser, HTTP_RESPONSE);  //初始化parser为Response类型
//	parsed = http_parser_execute(parser, &settings_null, all_result.c_str(), strlen(all_result.c_str()));  //执行解析过程
//
//	uv_write_t *req = (uv_write_t *)malloc(sizeof(uv_write_t));
//	uv_buf_t wrbuf = uv_buf_init(const_cast<char *>(all_result.c_str()), all_result.length());
//	uv_write(req, client, &wrbuf, 1, echo_write);
//
//	uv_close((uv_handle_t*)client, on_close);
//
//
//	
//	if (read_num == 173900)
//	{
//		std::string wav_filename = "E:\\nowWork\\CA\\Server_Project\\Libuv\\test_libuv\\net\\net_test_libuv\\net_server_libuv\\wav.wav";
//		std::string psdata_dir = "E:/nowWork/CA/PartC/asec5_C_standalone/kaldiwin_vs2017_OPENBLAS/work/psdata/graph_test_dg_mid_school";
//		std::string model_dir = "E:/nowWork/CA/PartC/asec5_C_standalone/kaldiwin_vs2017_OPENBLAS/work/model";
//
//		sscore result_score = score(wav_filename, psdata_dir, model_dir);
//		uv_write_t *req = (uv_write_t *)malloc(sizeof(uv_write_t));
//		//json
//		char ok[] = "OK";
//		uv_buf_t wrbuf = uv_buf_init(ok, 2);
//		uv_write(req, client, &wrbuf, 1, echo_write);
//
//	}
//
//
//
//}
//
//void on_new_connection(uv_stream_t *server, int status)
//{
//	if (status < 0)
//	{
//		fprintf(stderr, "New connection error %s\n", uv_strerror(status));
//		// error!
//		return;
//	}
//
//	uv_tcp_t *client = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
//	uv_tcp_init(loop, client);
//	if (uv_accept(server, (uv_stream_t*)client) == 0)
//	{
//		uv_read_start((uv_stream_t*)client, alloc_buffer, echo_read);
//		http_parser_test();
//	}
//	else
//	{
//		uv_close((uv_handle_t*)client, NULL);
//	}
//	printf("on new connection, status:%d\r\n", status);
//}
//
//int main()
//{
//	printf("buliding tcp\n");
//
//	std::string str = "abcdef\nqwer";
//	std::cout << "length:" << str.length() << std::endl;
//	std::cout << "size:" << str.size() << std::endl;
//
//
//	loop = uv_default_loop();
//
//	uv_tcp_t server;
//	uv_tcp_init(loop, &server);
//
//	printf("port%d", DEFAULT_PORT);
//
//	uv_ip4_addr("0.0.0.0", DEFAULT_PORT, &addr);
//
//	uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
//	printf("listening %d\n", DEFAULT_PORT);
//	int r = uv_listen((uv_stream_t*)&server, DEFAULT_BACKLOG, on_new_connection);
//	if (r) {
//		fprintf(stderr, "Listen error %s\n", uv_strerror(r));
//		return 1;
//	}
//
//	return uv_run(loop, UV_RUN_DEFAULT);
//}

/*********************************************************/

#include "JTCPServer.h"
#include "protocol.h"
#include <assert.h>
#include "http_response.h"
#include "glog-0.3.5-install\include\glog\logging.h"

sscore score(std::string wav_filename, std::string psdata_dir, std::string model_dir)
{
	/*
	FILE *rawfh;
	size_t nread;
	short buf[2048];
	float score;
	int ret = 0;
	char *model = const_cast<char*>("model");
	char *psdata = const_cast<char*>("pstata");
	//char *wav;

	CPartCScore partc_score;

	//printf("启动评测引擎！\n");
	__int64 engine = partc_score.AsecRetEngineStart(const_cast<char*>(model_dir.c_str()));		//启动引擎，model为存放模型的文件夹

																								//printf("%s ", wav);																	//printf("开始评测任务！\n");
	ret = partc_score.AsecRetScStart(engine, const_cast<char*>(psdata_dir.c_str()));          //开始评测任务，ps_data为存放题目评测数据的文件夹

	rawfh = fopen(wav_filename.c_str(), "rb");
	std::cout << "wav_filename:" << wav_filename;
	fseek(rawfh, 44, SEEK_SET);									//跳过44字节wav文件头
	while (!feof(rawfh))
	{
		nread = fread(buf, sizeof(*buf), 2048, rawfh);
		ret = partc_score.AsecRetScPcmIn(engine, buf, nread);     //输入语音数据
	}
	fclose(rawfh);

	//printf("语音结束，正在评分...\n");
	ret = partc_score.AsecRetScEnd(engine);                       //语音结束，进行评分

	score = partc_score.AsecRetGetScore(engine);				 //获取得分
	double svm_score = partc_score.AsecRetGetScoreByType(engine, 2);
	printf("score:%.1f svm_score:%.1f\n", score, svm_score);

	//printf("关闭评测引擎！\n");
	partc_score.AsecRetEngineEnd(engine);						//结束引擎
	sscore s_score;
	s_score.score = score;
	s_score.svm_score = svm_score;
	return s_score;
	*/
}


int main(int argc,char ** argv)
 {

	static char ta[1024];
	ta[0] = 'a';
	cout << "strlen" <<strlen(ta) << endl;
	cout << "sizeof" << sizeof(ta) <<endl;
	

	//google::InitGoogleLogging(argv[0]);
	//google::SetLogDestination(google::GLOG_INFO,"E:\\nowWork\\CA\\PartC\\asec5_C_standalone\\kaldiwin_vs2017_OPENBLAS\\Net_PartABC\\net_part_c_libuv\\Release\\LLLLOOOOGGGG.log");

	//google::SetStderrLogging(google::GLOG_INFO);

	LOG(INFO) << "This google log system!" << endl;

	http_response response;
	response.AddStatusLineToMsg("FUCK YOU");
	response.AddStatusLineToMsg("YOU MOTHERFUCK");

	string str = response.GetResponse();

	str = str + " over";
	cout << "R:" << str <<endl;

	cout << "R2:" << response.GetResponse() << endl;

	
	TCPServer server;
	server.Start("127.0.0.1",7002);

	std::string wav_filename = "E:\\nowWork\\CA\\PartC\\asec5_C_standalone\\kaldiwin_vs2017_OPENBLAS\\work\\wav\\130014.wav";
	std::string psdata_dir = "E:/nowWork/CA/PartC/asec5_C_standalone/kaldiwin_vs2017_OPENBLAS/work/psdata/graph_test_dg_mid_school";
	std::string model_dir = "E:/nowWork/CA/PartC/asec5_C_standalone/kaldiwin_vs2017_OPENBLAS/work/model";

	//server.SetService(wav_filename,psdata_dir,model_dir,score);
	server.Listen();
	server.Run();

	return 0;
}
