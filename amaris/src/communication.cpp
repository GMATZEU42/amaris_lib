#include "communication.h"

#ifdef _WIN32
#include "serial_port_win.h"
#else
#include "serial_port_unix.h"
#endif


namespace amaris
{
	COM::COM(const std::string& name) : m_name(name) {};

	void COM::received(std::string& msg) 
	{
		// To override on ComImpl
	};

	void COM::send(const std::string& msg)
	{
		// To override on ComImpl
	};

	std::string COM::getComStatus()
	{
		return ComErrorToString(m_errorState);
	}

	//	free function
	std::string ComErrorToString(const COM_ERROR error)
	{
		std::string retStr{};
		switch (error)
		{
		case(COM_ERROR::COM_OK):
			retStr = "COM OK";
			break;
		case(COM_ERROR::ERROR_OPENING_SERIAL_PORT):
			retStr = "Opening serial port error";
			break;
		case(COM_ERROR::GETTING_STATE_ERROR):
			retStr = "Getting state error";
			break;
		case(COM_ERROR::RECEIVING_ERROR):
			retStr = "Receiving error";
			break;
		case(COM_ERROR::SENDING_ERROR):
			retStr = "Sending error";
			break;
		case(COM_ERROR::SERIAL_PORT_DOESNT_EXIST):
			retStr = "Serial port doesn't exist";
			break;
		case(COM_ERROR::SETTING_STATE_ERROR):
			retStr = "Setting state error";
			break;
		case(COM_ERROR::BUILDING_DCB_ERROR):
			retStr = "Building DCB error";
			break;
		case(COM_ERROR::SETTING_TIMEOUT_ERROR):
			retStr = "Setting timeout error";
			break;
		case(COM_ERROR::UNKNOWN):
			retStr = "Unknown error";
			break;
		default:
			break;
		}
		return retStr;
	}

	COM* createComPort(const std::string& name)
	{
		return createComPortOS(name);
	}
}