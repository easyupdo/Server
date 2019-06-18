#include "JTCPServer.h"

CProtocol* TCPServer::LSX_protocol = new APPProtocol;
http_parser *TCPServer::parser = (http_parser*)malloc(sizeof(http_parser));
http_response *TCPServer::responser = new http_response;
string TCPServer::root_dir = "E:\\nowWork\\CA\\PartC\\asec5_C_standalone\\kaldiwin_vs2017_OPENBLAS\\Net_PartABC\\net_part_c_libuv\\work\\asec5_server_root\\1";

string TCPServer::parser_method;
string TCPServer::parser_url;
string TCPServer::parser_version;
string TCPServer::parser_body;
map<string, string>TCPServer::parser_header;

string TCPServer::header_field_tmp;
string TCPServer::header_value_tmp;

char TCPServer::available_buf[1024];


int TCPServer::read_num = 0;





http_parser_settings TCPServer::parser_settings =
{
	on_message_begin_cb,
	on_url_cb,
	on_status_cb,
	on_header_field_cb,
	on_header_value_cb,
	on_headers_complete_cb,
	on_body_cb,
	on_message_complete_cb,
	on_chunk_header_cb,
	on_chunk_complete_cb
};

//http_parser_info TCPServer::parser_info =
//{
//	NULL,	// char *method;
//	NULL,	// char *url;
//	NULL,	// char * body
//	0,		// unsigned int
//	0,		// unsigned short http_major
//	0		//unsigned short http_minor
//};


TCPServer::TCPServer()
{
	
	this->HTTPParserInit(this->parser,HTTP_REQUEST);

	this->parser->data = &parser_header;//not use
}
TCPServer::~TCPServer()
{

}

void TCPServer::Start(std::string address,int port)
{
	loop = uv_default_loop();

	//uv_tcp_t server;
	uv_tcp_init(loop, &server);

	uv_ip4_addr(address.c_str(),port, &addr);

	uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
	//int r = uv_listen((uv_stream_t*)&server, DEFAULT_BACKLOG, on_new_connection);
}

void TCPServer::SetService(std::string wav_filename, std::string psdata_dir, std::string model_dir,service_cb score)
{
	service.wav_filename = wav_filename;
	service.psdata = psdata_dir;
	service.model_dir = model_dir;
	service.cb_score = score;
}

//socket,bind
int TCPServer::Listen()
{
	int r = uv_listen((uv_stream_t*)&server, DEFAULT_BACKLOG,&this->On_New_Connection);
	std::cout<<"start listening 127.0.0.1:7002"<<std::endl;
	return r;
}

void TCPServer::Run()
{
	uv_run(loop, UV_RUN_DEFAULT);
}

void TCPServer::SetRootDir(string root_dir)
{
	this->root_dir = root_dir;
}



void TCPServer::alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
	buf->base = (char*)malloc(suggested_size);
	memset(buf->base, 0, suggested_size);
	buf->len = suggested_size;
}
void TCPServer::echo_write(uv_write_t *req, int status)
{
	if (status)
	{
		fprintf(stderr, "Write error %s\n", uv_strerror(status));
	}
	free(req);
}

void TCPServer:: on_close(uv_handle_t* peer)
{
	free(peer);
}

//判断一次是否是一个消息 如果不是进入循环buf 使用服务器提供的缓存大小
bool TCPServer::IsOneMessageBuf(char * buf)
{
	char _end[4];
	memset(_end,0,4);
	int length = _msize(buf);
	for (int i = 0; i < 4; i++)
	{
		_end[i] = buf[length - 4 + i];
	}
	string end = _end;
	if (end == "\r\n\r\n")
		return true;
	else
		return false;
}

bool TCPServer::IsGetContentLength()
{
	
	return true;
}

string TCPServer::GetOneHeader(parser_headers &headers,string header_name)
{
	return headers.find(header_name)->second;
}

string TCPServer::GetOneHeader(char * avalible, string header_name)
{
	return NULL;
}

void TCPServer::AddAvailableMessageBuf(char * buf)
{

}



void TCPServer::echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
	if (nread < 0)
	{
		if (nread != UV_EOF)
			fprintf(stderr, "Read error %s\n", uv_err_name(nread));
		uv_close((uv_handle_t*)client, NULL);
	}
	else if (nread > 0)
	{
		/*uv_write_t *req = (uv_write_t *) malloc(sizeof(uv_write_t));
		uv_buf_t wrbuf = uv_buf_init(buf->base, nread);
		uv_write(req, client, &wrbuf, 1, echo_write);*/
	
			read_num = read_num + nread;

			/* 
			std::ofstream ofs("E:\\nowWork\\CA\\PartC\\asec5_C_standalone\\kaldiwin_vs2017_OPENBLAS\\Net_PartABC\\net_part_c_libuv\\work\\wav.wav", std::ios::app | std::ios::binary);
			if (ofs.is_open())
			{
				ofs.write(buf->base, nread);
			}
			else
				std::cout << errno;
			ofs.close();
			*/

			cout << "##################################################Read Buf:" << endl;
			printf("###################################################echo_read:%d\n", nread);
			printf("Lall_read:%d\n", read_num);
			cout << "##################################################Read Buf:"<<endl;
			printf("%s\n", buf->base);


			//如果一次传输不是一个消息 就判断接收到的数据时候有Content-Length数据，如果没有添加到缓冲区bug中待用
			//bool status = IsOneMessageBuf(buf->base);
			//if (!status)
			//{

			//	string _buf = buf->base;

			//	int end_symbol_index = _buf.find("\r\n\r\n");
			//	cout << "eddd" << end_symbol_index << endl;

			//	//添加到缓冲区1M
			//	int size = strlen(available_buf);
			//	for (int i = size; i < 1024; i++)
			//	{
			//		
			//		available_buf[i] = buf->base[i - size];
			//		//available_buf
			//	}

			//	string content_length = GetOneHeader(parser_header,"Content-Length");
			//	if (content_length.length() > 0)
			//	{

			//	}
			//	else
			//	{
			//		
			//	}
			//}


			ParserClean();


			//hander the buf size



			//PARSER HTTP
			HTTPParserExec(parser, &parser_settings,buf->base, read_num);
			parser_method = http_method_str(http_method(parser->method));
			parser_version = to_string(parser->http_major) + "." + to_string(parser->http_minor);

			cout << "FLAGS:" << parser->flags<<endl;

			cout << "PARSER:" << endl;
			cout <<"method:"<< parser_method << endl;
			cout << "url:" << parser_url << endl;
			cout << "version:" << parser_version << endl;
			for(map<string,string>::const_iterator it= parser_header.cbegin();it!=parser_header.cend();it++)
				cout << "header:" << it->first<<":"<<it->second << endl;
			if (parser_body.length() > 0)
			{
				cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@body:" << parser_body << endl;
				cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@body over" << endl;

			}

	




			//RESPONSE HTTP
			//
			//HTTP/1.1  200  OK                        --响应行
			//Server: Apache-Coyote/1.1                --响应头（key-vaule）
			//Content-Length: 24

			string source_filename = root_dir + parser_url;

			cout << "source file" << source_filename <<endl;


			responser->AddStatusLineToMsg("HTTP/1.1 200 OK\r\n");
			responser->AddHeadToMsg("Server:", " LSX-ASEC-5/0.1\r\n");
			responser->AddHeadToMsg("Data:", "1\r\n");
			
			parser_headers::iterator it = parser_header.begin();
			
			if (parser_header.find("Content-Length") != parser_header.end())
				responser->AddHeadToMsg("Content-Length:", parser_header.find("Content-Length")->second+"\r\n");
			//responser->AddHeadToMsg("Content - Length:", "100\r\n");
			responser->AddBodyToMsg("\r\n\r\n",ASEC_STRING);
			//responser->AddBodyToMsg("hello world",ASEC_STRING);
			responser->AddBodyToMsg(source_filename, ASEC_FILE);
			responser->AddBodyToMsg("\r\n\r\n",ASEC_STRING);

			cout << "################################################response complete" << endl;;
			cout << responser->GetResponse();

			string buf_str = responser->GetResponse();
			char * buf_ptr = const_cast<char*>(buf_str.c_str());

			//cout << "response:" << buf_ptr << endl;
	
			//BS HTTP protcol 
			uv_write_t *req = (uv_write_t *)malloc(sizeof(uv_write_t));
			uv_buf_t wrbuf_22;
			wrbuf_22 = uv_buf_init(buf_ptr, buf_str.length());
			uv_write(req, client, &wrbuf_22, 1, echo_write);
	
	
			responser->ResposerClean();

			//uv_close((uv_handle_t*)client, NULL);

			read_num = 0;
	

			///cout << "url:" << parser_info.url<< endl;

			if (buf->base)
				free(buf->base);



			if (read_num == 173900)
			{
				std::string wav_filename = "E:\\nowWork\\CA\\PartC\\asec5_C_standalone\\kaldiwin_vs2017_OPENBLAS\\work\\wav\\130014.wav";
				std::string psdata_dir = "E:/nowWork/CA/PartC/asec5_C_standalone/kaldiwin_vs2017_OPENBLAS/work/psdata/graph_test_dg_mid_school";
				std::string model_dir = "E:/nowWork/CA/PartC/asec5_C_standalone/kaldiwin_vs2017_OPENBLAS/work/model";


				//sscore result_score = service.cb_score(wav_filename, psdata_dir, model_dir);
				uv_write_t *req = (uv_write_t *)malloc(sizeof(uv_write_t));
				//json
				//printf("score:%f  %f\n",result_score.score,result_score.svm_score);

				char ok[] = "OK";
				uv_buf_t wrbuf = uv_buf_init(ok, 2);
				uv_write(req, client, &wrbuf, 1, echo_write);
				//	uv_close((uv_handle_t*)client, NULL);

				// char ch[4];
				//IntToByteHex(ch, 10);

				//printf("%x   %d\n", ch[0], &ch[0]);
				//printf("%x   %d\n", ch[1], &ch[1]);
				//printf("%x   %d\n", ch[2], &ch[2]);
				//printf("%x   %d\n", ch[3], &ch[3]);

				//uv_buf_t wrbuf_1 = uv_buf_init(ch, 4);
				//uv_write(req, client, &wrbuf_1, 1, echo_write);


				uv_write(req, client, &wrbuf, 1, echo_write);


				//CS app protocol
				LXS_MSG &msg = LSX_protocol->GetMsg();
				cout << "What the fuck!" << endl;

				uv_buf_t wrbuf_2;
				wrbuf_2 = uv_buf_init(*(msg.msg_arr + 1), 8);
				uv_write(req, client, &wrbuf_2, 1, echo_write);
				//***************************




				/*	wrbuf_2 = uv_buf_init(msg.msg1002, 8);
				uv_write(req, client, &wrbuf_2, 1, echo_write);

				wrbuf_2 = uv_buf_init(msg.msg1003,808);
				uv_write(req, client, &wrbuf_2, 1, echo_write);*/



				//wrbuf_2 = uv_buf_init(msg.msg1004, 12);
				//uv_write(req, client, &wrbuf_2, 1, echo_write);

				//wrbuf_2 = uv_buf_init(msg.msg1005, 12);
				//uv_write(req, client, &wrbuf_2, 1, echo_write);

				uv_close((uv_handle_t*)client, NULL);


			}
	}


}


void TCPServer::On_New_Connection(uv_stream_t* server, int status)
{
	if (status < 0)
	{
		fprintf(stderr, "New connection error %s\n", uv_strerror(status));
		// error!
		return;
	}

	uv_tcp_t *client = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
	uv_tcp_init(loop, client);
	if (uv_accept(server, (uv_stream_t*)client) == 0)
	{
		
		uv_read_start((uv_stream_t*)client, alloc_buffer, echo_read);
		//http_parser_test();
	}
	else
	{
		uv_close((uv_handle_t*)client, NULL);
	}
	printf("on new connection, status:%d\r\n", status);
}

void TCPServer::SetParserHeader(http_parser *parser, const char *buf, size_t len,string &parser_XX)
{
	char *buf_tmp = new char[len + 1];
	memset(buf_tmp, 0, len + 1);
	memcpy(buf_tmp, buf, len);
	parser_XX = buf_tmp;
	delete[]buf_tmp;
}

int TCPServer::on_url_cb(http_parser *parser, const char *buf, size_t len)
{
	SetParserHeader(parser, buf, len,parser_url);

	cout << "#######url:length" << parser_url <<len << endl;
	//cout << "BUF:" << buf;

	//cout << "parser_info:"<<parser_info.url << endl;
	//cout << "method:" <<http_method_str(http_method(parser->method)) << endl;
	return 0;
}

int TCPServer::on_status_cb(http_parser *parser, const char *buf, size_t len)
{
	return 0;
}

int TCPServer::on_header_field_cb(http_parser *parser, const char *buf, size_t len)
{

	SetParserHeader(parser, buf, len, header_field_tmp);
	
	//cout << "Head Filed:len" << header_field_tmp << len << endl;
	
	return 0;
}

int TCPServer::on_header_value_cb(http_parser *parser, const char *buf, size_t len)
{

	SetParserHeader(parser, buf, len, header_value_tmp);

	parser_header.insert(pair<string,string>(header_field_tmp,header_value_tmp));

	header_field_tmp.clear();
	header_value_tmp.clear();

	//cout << "Head Filed:len" << header_value_tmp << len << endl;
	
	return 0;
}

int TCPServer::on_body_cb(http_parser *parser, const char *buf, size_t len)
{

	SetParserHeader(parser, buf, len, parser_body);

	//cout << "########################################Body:" << parser_body << endl;
	return 0;
}

int TCPServer::on_message_begin_cb(http_parser *parser)
{
	printf("#############################################################on_message_begin\n");
	return 0;
}
// 通知回调：说明消息解析完毕
int TCPServer::on_message_complete_cb(http_parser *parser)
{
	printf("##########################################################on_message_complete\n");
	return 0;
}
// 通知回调：说明HTTP报文头部解析完毕
int TCPServer::on_headers_complete_cb(http_parser *parser)
{
	printf("on_headers_complete\n");
	return 0;
}

int TCPServer::on_chunk_header_cb(http_parser*parser)
{
	return 0;
}
int TCPServer::on_chunk_complete_cb(http_parser*parser)
{
	return 0;
}

//void TCPServer::HTTPSettings(http_parser_settings parser_settings)
//{
//	parser_settings.on_message_begin = on_message_begin_cb;
//	parser_settings.on_url = on_url_cb;
//	parser_settings.on_status = on_status_cb;
//	parser_settings.on_header_field = on_header_field_cb;
//	parser_settings.on_header_value = on_header_value_cb;
//	parser_settings.on_headers_complete = on_headers_complete_cb;
//	parser_settings.on_body = on_body_cb;
//	parser_settings.on_message_complete = on_message_complete_cb;
//	parser_settings.on_chunk_header = on_chunk_header_cb;
//	parser_settings.on_chunk_complete = on_chunk_complete_cb;
//}


void TCPServer::HTTPParserInit(http_parser *parser, enum http_parser_type type)
{
	http_parser_init(parser, type);
}
void TCPServer::HTTPParserExec(http_parser *parser, http_parser_settings * settings, char *buf, size_t len)
{
	http_parser_execute(parser, settings, buf, len);
}

void TCPServer::ParserClean()// no use  static init by system
{
	parser_method.clear();
	parser_url.clear();
	parser_version.clear();
	parser_body.clear();
	parser_header.clear();

	header_field_tmp.clear();
	header_value_tmp.clear();
}


 

