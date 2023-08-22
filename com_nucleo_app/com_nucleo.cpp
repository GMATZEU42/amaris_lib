#include "com_nucleo.h"


ComNucleoApp::ComNucleoApp(std::string name) : Application(name)
{
	addHelpMessageLine("s", "stuff1", "do stuff with a number", "integer");
	addHelpMessageLine("q", "stuff2", "do stuff with a number", "double");

	m_pComPort = amaris::createComPort("COM6");
}

ComNucleoApp::~ComNucleoApp()
{
	if (m_pComPort)
	{
		delete m_pComPort;
	}
}

void ComNucleoApp::processInput(const std::string inp)
{
	if (!Application::processDefaultInput(inp))
	{
		if (findCommand(inp, "s", "stuff1"))
		{
			int p1{};
			if (getParams(inp, p1))
			{
				//doStuffs1(p1);
			}
			else
			{
				printNotValidCommand();
				printHelp();
			}

		}
		else if (findCommand(inp, "q", "stuff2"))
		{
			double p1{};
			getParams(inp, p1);
			//doStuffs2(p1);
		}
		else if (findCommand(inp, "", "log on"))
		{
			m_pComPort->send("log on");
		}
		else if (findCommand(inp, "", "log off"))
		{
			m_pComPort->send("log off");
		}
		else if (findCommand(inp, "", "get_com_status"))
		{
			m_console.print(m_pComPort->getComStatus(), amaris::ConsoleColor::GREEN);
		}
		else
		{
			printNotValidCommand();
			printHelp();
		}
	}
}
