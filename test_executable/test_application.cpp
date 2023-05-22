#include "test_application.h"


TestApplication::TestApplication(std::string name) : Application(name)
{
	addHelpMessageLine("s", "stuff1", "do stuff with a number", "integer");
	addHelpMessageLine("q", "stuff2", "do stuff with a number", "double");
}

void TestApplication::doStuffs1(int params)
{
	m_console.print("Doing " + std::to_string(params) + " stuffs");
}

void TestApplication::doStuffs2(double param1)
{
	m_console.print("Doing stuffs whit " + std::to_string(param1));
}

void TestApplication::processInput(const std::string inp)
{
	Application::processInput(inp);		
	if (findCommand(inp, "s", "stuff1"))
	{
		int p1{};
		if (getParams(inp, p1))
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
		getParams(inp, p1);
		doStuffs2(p1);
	}
	else
	{
		printNotValidCommand();
		printHelp();
	}
}
