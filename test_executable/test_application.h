#pragma once

#include "application.h"

using amaris::Application;

class TestApplication : public Application
{
public:
	TestApplication(std::string name);
	void doStuffs1(int parameter);
	void doStuffs2(double param1);	
protected:
	void processInput(const std::string inp);
};