#include "com_nucleo.h"

#include <Windows.h>


ComNucleoApp::ComNucleoApp(std::string name) : Application(name), MasterConsole("C:/Workspace/tmp/Amaris/amaris_lib/cmakebuild/Debug/SlavePrompt.exe")
{	
	m_console.setColor(amaris::ConsoleColor::AZURE);

	addHelpMessageLine("", "log on", "Activate log on the nucleo. These are saved on ", "");
	addHelpMessageLine("", "log off", "Deactivate logging from the nucleo", "");
	addHelpMessageLine("", "set flow", "Set the flow", "double");
	addHelpMessageLine("", "start pid", "Start the flow in closed loop", "");
	addHelpMessageLine("", "stop pid", "Stop the flow in closed loop", "");
	addHelpMessageLine("", "set pid", "Set the parameters for the closed loop (Kp, Ki, Kd)", "double, double, double");
	addHelpMessageLine("", "add procedure", "Set the procedure", "double,double double,double");
	addHelpMessageLine("", "reset procedure", "Clear the old procedure", "");
	addHelpMessageLine("", "get com status", "Print the status of the communication with the nucleo", "");

	m_pComPort = amaris::createComPort("COM6");
	startSlaveConsole();
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
		if (findCommand(inp, "", "log on"))
		{
			logHandle(true);
		}
		else if (findCommand(inp, "", "log off"))
		{
			logHandle(false);
		}
		else if (findCommand(inp, "", "set flow"))
		{
			m_pComPort->send(inp);
		}
		else if (findCommand(inp, "", "start pid"))
		{
			m_pComPort->send("start pid");
		}
		else if (findCommand(inp, "", "stop pid"))
		{
			m_pComPort->send("stop pid");
		}
		else if (findCommand(inp, "", "set pid"))
		{
			m_pComPort->send(inp);
		}
		else if (findCommand(inp, "", "reset procedure"))
		{
			m_pComPort->send("reset procedure");
		}
		else if (findCommand(inp, "", "add procedure"))
		{
			m_pComPort->send(inp);
		}
		else if (findCommand(inp, "", "get com status"))
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
