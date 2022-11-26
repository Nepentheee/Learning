#pragma once

#include <string>
#include <iostream>

using namespace std;

class DebugLog
{
public:
	DebugLog();
	~DebugLog();

	static void Log(const string value);
	static void Log(const int value);
	static void Log(const float value);
	static void Log(const unsigned int value);
private:

};

DebugLog::DebugLog()
{
}

DebugLog::~DebugLog()
{
}

void DebugLog::Log(const string value)
{
	cout << value << endl;
}

void DebugLog::Log(const int value)
{
	cout << to_string(value) << endl;
}

void DebugLog::Log(const float value)
{
	cout << to_string(value) << endl;
}

void DebugLog::Log(const unsigned int value)
{
	cout << to_string(value) << endl;
}

