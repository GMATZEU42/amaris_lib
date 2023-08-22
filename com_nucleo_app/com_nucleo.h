#pragma once

#include "application.h"
#include "communication.h"

using amaris::Application;
using amaris::COM;

class ComNucleoApp : public Application
{
public:
	ComNucleoApp(std::string name);
	~ComNucleoApp();
protected:
	void processInput(const std::string inp);
	COM* m_pComPort = nullptr;
};