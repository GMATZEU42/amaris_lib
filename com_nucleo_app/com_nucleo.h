#pragma once

#include "application.h"
#include "master_console.h"
#include "network.h"
#include "file_handler.h"

#include <thread>

using amaris::Application;
using amaris::MasterConsole;
using amaris::COM;
using amaris::FileHandler;

class ComNucleoApp : public Application, MasterConsole
{
public:	// methods
	ComNucleoApp(std::string name);
	~ComNucleoApp();
	// commands
	void logHandle(const bool active);
protected:	// methods
	//void startSlaveConsole() override;
	//void stopSlaveConsole() override;
	void processInput(const std::string inp) override;
	void writeCSV();
protected:	//fields
	COM* m_pComPort = nullptr;
	//
	FileHandler m_csv = FileHandler("C:/tmp/log.csv");
	// threads
	std::thread m_receivedThread;	// thread of polling with the com-port
	std::thread m_writeCSVThread;	// thread that handle the buffer and the csv
};