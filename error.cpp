#include "error.h"



MessageLogger::MessageLogger()
{
}


MessageLogger::~MessageLogger()
{
	// remove trailing '\n',
	std::string str = ss_.str();
	while (!str.empty() && str[str.length() - 1] == '\n')
		str.resize(str.length() - 1);

	//析构函数中处理 Message到控制台
	//MessageLogger::HandleMessage(envelope_, str.c_str());
}


void MessageLogger::HandleMessage(const Severity &envelope,const char *message) 
{
	

}
