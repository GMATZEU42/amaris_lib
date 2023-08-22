#pragma once

#include "application.h"

using amaris::Application;

class SlavePromptApp : public Application
{
public:
	SlavePromptApp(std::string name);
	void doStuffs1(int parameter);
	void doStuffs2(double param1);	
protected:
	void processInput(const std::string inp);
};