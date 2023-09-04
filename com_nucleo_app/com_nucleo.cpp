#include "com_nucleo.h"

#include <Windows.h>


ComNucleoApp::ComNucleoApp(std::string name) : Application(name), MasterConsole("C:/Workspace/tmp/Amaris/amaris_lib/cmakebuild/Debug/SlavePrompt.exe")
{	
	m_console.setColor(amaris::ConsoleColor::AZURE);

	addHelpMessageLine("", "log on", "Activate log on the nucleo. These are saved on ", "integer");
	addHelpMessageLine("", "log off", "do stuff with a number", "double");

	m_pComPort = amaris::createComPort("COM6");

}

ComNucleoApp::~ComNucleoApp()
{
	if (m_receivedThread.joinable())
	{
		m_receivedThread.join();
	}
	if (m_writeCSVThread.joinable())
	{
		m_writeCSVThread.join();
	}
	if (m_pComPort)
	{
		delete m_pComPort;
	}
}

void ComNucleoApp::processInput(const std::string inp)
{
	if (!Application::processDefaultInput(inp))
	{
		if (findCommand(inp, "", "stuff1"))
		{
			int p1{};
			if (getParams(inp, "stuff1", p1))
			{
				//doStuffs1(p1);
			}
			else
			{
				printNotValidCommand();
				printHelp();
			}

		}
		else if (findCommand(inp, "", "stuff2"))
		{
			double p1{};
			getParams(inp, "stuff2", p1);
			//doStuffs2(p1);
		}
		else if (findCommand(inp, "", "log on"))
		{
			logHandle(true);
		}
		else if (findCommand(inp, "", "log off"))
		{
			logHandle(false);
		}
		else if (findCommand(inp, "", "set flow"))
		{
			// ToDo
		}
		else if (findCommand(inp, "", "start pid"))
		{
			// ToDo
		}
		else if (findCommand(inp, "", "stop pid"))
		{
			// ToDo
		}
		else if (findCommand(inp, "", "set pid"))
		{
			// ToDo
		}
		else if (findCommand(inp, "", "reset procedure"))
		{
			// ToDo
		}
		else if (findCommand(inp, "", "add procedure"))
		{
			// ToDo
		}
		else if (findCommand(inp, "", "get com status"))
		{
			m_console.print(m_pComPort->getComStatus(), amaris::ConsoleColor::GREEN);
		}
		else if (findCommand(inp, "", "start slave"))
		{
			startSlaveConsole();
		}
		else if (findCommand(inp, "", "stop slave"))
		{
			stopSlaveConsole();
		}
		else if (findCommand(inp, "", "slave print"))
		{
			std::string s;
			getParams(inp, "slave print", s);
			m_socket.send(s);
		}
		else
		{
			printNotValidCommand();
			printHelp();
		}
	}	
}

void ComNucleoApp::logHandle(const bool active)
{
	if (active)
	{
		m_pComPort->send("log on");
		m_pComPort->startPolling();
		// avoid to recreate a thread already running
		if (!m_receivedThread.joinable())
		{
			m_receivedThread = std::thread(&amaris::COM::received, m_pComPort);
		}
		if (!m_writeCSVThread.joinable())
		{
			m_writeCSVThread = std::thread(&ComNucleoApp::writeCSV, this);
		}
	}
	else
	{
		m_pComPort->stopPolling();
		m_pComPort->send("log off");
		m_receivedThread.join();
		m_writeCSVThread.join();
	}
}

void ComNucleoApp::writeCSV()
{
	while (m_pComPort->isPolling())
	{
		std::string line{};
		m_pComPort->popLastBuffer(line);
		if (!line.empty())
		{
			try
			{
				m_csv.writeLine(line);
				m_socket.send(line);
			}
			catch (std::exception& e)
			{
				m_pComPort->stopPolling();
				m_pComPort->send("log off");
				m_console.print("Exception" + std::string(e.what()) + " during csv file open, log switched off", amaris::ConsoleColor::RED);

			}
		}
	}
}
