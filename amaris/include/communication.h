#pragma once

#include "amaris.h"

#include <string>

// Windows case
#ifdef _WIN32

namespace amaris
{
	enum class COM_ERROR
	{
		COM_OK,
		ERROR_OPENING_SERIAL_PORT,
		SERIAL_PORT_DOESNT_EXIST,
		SETTING_STATE_ERROR,
		GETTING_STATE_ERROR,
		BUILDING_DCB_ERROR,
		SETTING_TIMEOUT_ERROR,
		RECEIVING_ERROR,
		SENDING_ERROR,
		UNKNOWN
	};

	class AMARIS_API COM
	{
	public:
		COM(const std::string& name = "");
		virtual ~COM() {};
		virtual void received(std::string& msg);
		virtual void send(const std::string& msg = "");
		std::string getComStatus();
	protected:
		std::string m_name{};
		COM_ERROR m_errorState = COM_ERROR::COM_OK;
	};

	AMARIS_API std::string ComErrorToString(const COM_ERROR error);
	AMARIS_API COM* createComPort(const std::string& name);

}

#else
// put here the code for other OS
#endif