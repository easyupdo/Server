#include "http_response.h"



http_response::http_response()
{
}


http_response::~http_response()
{
}


void http_response::AddStatusLineToMsg(string status_line)
{

	this->resposer = this->resposer + status_line;

	
}
void http_response::AddHeadToMsg(string key, string value)
{
	this->resposer = this->resposer + (key)+ (value);
}
void http_response::AddBodyToMsg(string body,body_type type)
{
	if(type == ASEC_STRING)
		this->resposer = this->resposer + body;
	if (type == ASEC_FILE)
	{
		ifstream ifs(body, std::ios::in | std::ios::binary);
		if (ifs.is_open())
		{
			char line[1024];
			memset(line,0,1024);
			while (ifs.getline(line, sizeof(line)))
			{
				//cout << "line:" << line << endl;
				this->resposer = this->resposer + line;
			}
		}
	}
}

void http_response::ResposerClean()
{
	this->resposer.clear();
}


string http_response::operator+(string str)
{
	
	return "S";
}


const string& http_response::GetResponse()
{
	return this->resposer;
}
