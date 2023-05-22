#pragma once

#include "amaris.h"
#include "logger.h"
#include "console.h"

#include <filesystem>
#include <memory>
#include <functional>
#include <charconv>
#include <algorithm>


namespace amaris
{
	class AMARIS_API Application
	{
	public:
		Application(const std::string appName = "");
		virtual ~Application() {};
		//
		void init(int argc, char* argv[]);
		void run();
	protected:
		//
		virtual void processInput(const std::string inp);
		void addHelpMessageLine(const std::string& shortCmd, const std::string& longCmd, const std::string& description, const std::string& inputs = "");
		//
		bool findCommand(std::string inp, std::string shortName, std::string longName);
		void printNotValidCommand();
		void printHelp();

		template <typename T>
		bool getParams(const std::string& inp, T& param)
		{
			// get params
			param = T{};
			std::string sParam = inp.substr(inp.find(" ") + 1U);
			std::from_chars_result res = std::from_chars(sParam.data(), sParam.data() + sParam.size(), param);
			if (res.ec == std::errc())
			{
				return true;
			}
			else if (res.ec == std::errc::invalid_argument)
			{
				return false;
			}
			else if (res.ec == std::errc::result_out_of_range)
			{
				return false;
			}
			else
			{
				return false;
			}		
		}
	protected:
		//
		Console m_console = Console(amaris::ConsoleColor::ORANGE, ">> ", true);
		Logger m_logger = Logger(std::filesystem::current_path(), "Amaris_Application", "log");
		// 
		bool m_bRun = false;
	private:
		//
		void consoleCommandInit(int argc, char* argv[]);
		void configFileInit(std::filesystem::path configFilePath);
		void exit();
		//
	private:	// Fields		
		std::string m_appName = "Amaris Application";
		std::string m_helpMsg = "";
		bool m_bDebugMode = false;
	};
}
