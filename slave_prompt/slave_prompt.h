#pragma once

#include "application.h"
#include "slave_console.h"

using amaris::Application;
using amaris::SlaveConsole;
using amaris::Event;

class SlavePromptApp : public Application, SlaveConsole
{
public:
	SlavePromptApp(std::string name);
	void doStuffs1(int parameter);
	void doStuffs2(double param1);	
	void update(const amaris::Event& event) override; // override from Listener
protected:
	void processInput(const std::string inp);
};