#include "application.h"

#include <iostream>

namespace amaris
{
	// Public methods 
	Application::Application()
	{};

	Application::~Application()
	{};

	void Application::init(int argc, char* argv[])
	{
		if (argc > 1)
		{
			consoleCommandInit(argc, argv);
		}
		else
		{
			configFileInit(argv[0]);
		}
	}

	void Application::run()
	{
		std::string inp = "";
		m_bRun = true;
		while (m_bRun)
		{
			inp = m_console.getInput();
			processInput(inp);
		}
	}

	// Private methods
	void Application::processInput(const std::string inp)
	{
		if (inp == "h" || inp == "help")
		{
			printHelp();
		}

	}

	void Application::configFileInit(std::filesystem::path configFilePath)
	{
		// ToDo: read from config file all app settings.
	}

	void Application::consoleCommandInit(int argc, char* argv[])
	{
		if (argc == 0U)
		{
			configFileInit(argv[0]);
		}
		else
		{
			for (auto i = 1U; i < argc; ++i)
			{
				std::string command{ argv[i] };
				if (command == "-h" || command == "-help")
				{
					printHelp();
				}
				else if (command == "-d" || command == "--debug")
				{
					m_bDebugMode = true;
				}
				else
				{
					printHelp();
				}
			}
		}
	}

	void Application::printHelp()
	{
		std::string helpString =
		{
			"Hello everyone, this is an application that calculate prime numbers.\n"
			"[-h | --help]\t print an usage message\n"
			"[-l | --load <path>]\t set the path where to load primes\n"
			"[-s | --save <path>]\t set the path where to save primes\n"
			"[-t | --threshold <number>]\t set the when to stop the computation\n"
			"[-d | --debug]\t set debug mode while computing\n"
			"During the computation there are these commands avaible:\n"
			"[c | compute]\t to start the computation\n"
			"[s | stop]\t to stop the computation immediately\n"
			"[e | exit]\t to exit the application\n"
			"[h | help]\t to print the help menu\n"
		};
		m_console.print(helpString, amaris::ConsoleColor::ORANGE);
	}
}
