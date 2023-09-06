#include "master_console.h"

#ifdef _WIN32
#include <Windows.h>
#else
#endif

namespace amaris
{
	MasterConsole::MasterConsole(std::filesystem::path execPath) : m_execPath(execPath)
	{
		m_pProcessHandler = ProcessHandler::createProcessHandler();
	}

	MasterConsole::~MasterConsole()
	{
	}

	void MasterConsole::startSlaveConsole()
	{
		m_socket.connect(10);
		m_pProcessHandler->createProcess(m_execPath, true);
	}

	void MasterConsole::stopSlaveConsole()
	{
		m_socket.send("exit");
	}
}
