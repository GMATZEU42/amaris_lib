#include "slave_prompt.h"

using amaris::SocketEvent;

SlavePromptApp::SlavePromptApp(std::string name) : Application(name), SlaveConsole()
{
	m_socket.addListener(this);
	//addHelpMessageLine("", "stuff1", "do stuff with a number", "integer");
	//addHelpMessageLine("", "stuff2", "do stuff with a number", "double");
}

void SlavePromptApp::doStuffs1(int params)
{
	m_console.print("Doing " + std::to_string(params) + " stuffs");
}

void SlavePromptApp::doStuffs2(double param1)
{
	m_console.print("Doing stuffs whit " + std::to_string(param1));
}

void SlavePromptApp::processInput(const std::string inp)
{
	if (!Application::processDefaultInput(inp))
	{
		if (findCommand(inp, "s", "stuff1"))
		{
			int p1{};
			if (getParams(inp, "stuff1",  p1))
			{
				doStuffs1(p1);
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
			if (getParams(inp, "stuff2", p1))
			{
				doStuffs2(p1);
			}
			else
			{
				printNotValidCommand();
				printHelp();
			}
		}
		else if (findCommand(inp, "p", "print"))
		{
			std::string s;
			if (getParams(inp, "print", s))
			{
				m_console.print(s);
			}
			else
			{
				printNotValidCommand();
				printHelp();
			}
		}
		else
		{
			printNotValidCommand();
			printHelp();
		}
	}	
}

void SlavePromptApp::update(const Event& event)
{
	if (event.getType() == SocketEvent::Type::RECEIVED_MESSAGE)
	{
		std::string s;
		m_socket.getMessage(s);
		m_console.print(s);
	}
}
