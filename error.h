#pragma once

#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>


enum Severity 
{
	AAssertFailed = -3,
	AError = -2,
	AWarning = -1,
	AInfo = 0,
};

//class error
//{
//public:
//	error();
//
//	inline std::ostream &stream() { return ss_; }
//	~error();
//private:
//	std::ostringstream ss_;
//};


class MessageLogger
{
public:
	MessageLogger();

	inline std::ostream &stream() { return ss_; }

	void HandleMessage(const Severity &envelope, const char *message);

	~MessageLogger();
private:
	std::ostringstream ss_;
};




#define ASEC_ERR \
  MessageLogger(Severity::AError,__func__, __FILE__, __LINE__).stream()
#define ASEC_WARN \
  MessageLogger(Severity::AWarning,__func__, __FILE__, __LINE__).stream()
#define ASEC_LOG \
  MessageLogger(Severity::AInfo,__func__, __FILE__, __LINE__).stream()
#define ASEC_VLOG(v) if ((v) <= ::kaldi::g_kaldi_verbose_level)	\
  MessageLogger((Severity)(v),__func__, __FILE__, __LINE__).stream()




