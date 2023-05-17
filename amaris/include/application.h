#pragma once

#include "logger.h"
#include "console.h"

#include <filesystem>
#include <memory>

namespace amaris
{
	class AMARIS_API Application
	{
	public:
		Application();
		virtual ~Application();
		void init(int argc, char* argv[]);
		void run();
	private:	// Methods
		void consoleCommandInit(int argc, char* argv[]);
		void configFileInit(std::filesystem::path configFilePath);
		void processInput(const std::string inp);
		void printHelp();
	private:	// Fields
		std::thread m_computeThread;
		std::string m_appName = "";
		//
		Console m_console = Console(amaris::ConsoleColor::ORANGE, ">> ", true);
		Logger m_logger = Logger(std::filesystem::current_path(), m_appName, "log");
		// 
		bool m_bRun = false;
		bool m_bDebugMode = false;


	};
}
