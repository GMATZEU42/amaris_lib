#include "slave_console.h"

namespace amaris
{
	SlaveConsole::SlaveConsole()
	{
		m_socket.connect(10u);
	}

	SlaveConsole::~SlaveConsole()
	{

	}	
}
