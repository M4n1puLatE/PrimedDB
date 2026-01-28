#include <string>
#include <iostream>
#include <sstream>
#include <format>
#include <future>
#include <queue>
#include <shared_mutex>

class Log
{
	std::stringstream m_messageStream;

public:
	void add(const std::string& text);
	void end();
	static size_t size();
	static void join();
};
