#include "serial_port_win.h"

#include <stdio.h>

#define BUFFER_SIZE 100

namespace amaris
{
	WinCom::WinCom(const std::string& name) : COM(name)
	{
		m_hSerial = CreateFile(name.c_str(),
			GENERIC_WRITE | GENERIC_READ,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (m_hSerial == INVALID_HANDLE_VALUE)
		{
			if (GetLastError() == ERROR_FILE_NOT_FOUND)
			{
				//serial port does not exist. Inform user.
				m_errorState = COM_ERROR::SERIAL_PORT_DOESNT_EXIST;
			}
			else
			{
				//some other error occurred. Inform user.
				m_errorState = COM_ERROR::ERROR_OPENING_SERIAL_PORT;
			}
		}
		else
		{
			m_dcbSerialParams.DCBlength = sizeof(m_dcbSerialParams);
			if (!GetCommState(m_hSerial, &m_dcbSerialParams)) 
			{
				//error getting state
				m_errorState = COM_ERROR::GETTING_STATE_ERROR;
			}

			m_dcbSerialParams.BaudRate = CBR_115200;
			m_dcbSerialParams.ByteSize = 8;
			m_dcbSerialParams.StopBits = ONESTOPBIT;
			m_dcbSerialParams.Parity = NOPARITY;
			m_dcbSerialParams.fBinary = TRUE;					// has to be TRUE in Windows
			m_dcbSerialParams.fParity = FALSE;					// No parity
			m_dcbSerialParams.fOutxCtsFlow = FALSE;				// No CTS flow control
			m_dcbSerialParams.fOutxDsrFlow = FALSE;				// No DSR flow control
			m_dcbSerialParams.fDtrControl = FALSE;				// No DTR low control
			m_dcbSerialParams.fDsrSensitivity = FALSE;			// Ignore DSR
			m_dcbSerialParams.fOutX = FALSE;					// No XON/XOFF flow control
			m_dcbSerialParams.fInX = FALSE;						// No XON/XOFF flow control
			m_dcbSerialParams.fErrorChar = FALSE;				// do not replace errors
			m_dcbSerialParams.fNull = FALSE;					// allow NULL bytes
			m_dcbSerialParams.fRtsControl = RTS_CONTROL_ENABLE; // Enable RTS pin
			m_dcbSerialParams.fAbortOnError = FALSE;			// do not stop on error

			if (!SetCommState(m_hSerial, &m_dcbSerialParams))
			{
				//error setting serial port state
				m_errorState = COM_ERROR::SETTING_STATE_ERROR;
			}
			if (!GetCommState(m_hSerial, &m_dcbSerialParams))
			{
				m_errorState = COM_ERROR::GETTING_STATE_ERROR;
			}
			if (!BuildCommDCB("baud=115200 parity=n data=8 stop=1", &m_dcbSerialParams))
			{
				m_errorState = COM_ERROR::BUILDING_DCB_ERROR;
			}
		}

		if (m_bUseTimeout && COM_ERROR::COM_OK == m_errorState)
		{
			m_timeouts.ReadIntervalTimeout = 50;
			m_timeouts.ReadTotalTimeoutConstant = 0;
			m_timeouts.ReadTotalTimeoutMultiplier = 0;
			m_timeouts.WriteTotalTimeoutConstant = 0;
			m_timeouts.WriteTotalTimeoutMultiplier = 0;
			if (!SetCommTimeouts(m_hSerial, &m_timeouts)) 
			{
				//error occureed. Inform user
				m_errorState = COM_ERROR::SETTING_TIMEOUT_ERROR;
			}
		}

		if (COM_ERROR::COM_OK == m_errorState)
		{
			if (!EscapeCommFunction(m_hSerial, CLRDTR))
			{
				auto tmp = 4;
			}
			if (!EscapeCommFunction(m_hSerial, SETDTR))
			{
				auto tmp = 2;
			}
		}
	}

	WinCom::~WinCom()
	{
		CloseHandle(m_hSerial);
	}

	void WinCom::received(std::string& msg)
	{
		char szBuff[BUFFER_SIZE + 1] = { 0 };
		DWORD dwBytesRead = 0;
		if (!ReadFile(m_hSerial, szBuff, BUFFER_SIZE, &dwBytesRead, NULL))
		{
			//error occurred. Report to user.
			m_errorState = COM_ERROR::RECEIVING_ERROR;
		}

	}

	void WinCom::send(const std::string& msg)
	{
		char szBuff[BUFFER_SIZE] = { 0 };
		strcpy(szBuff, msg.c_str());
		szBuff[strlen(msg.c_str())] = '\n';
		DWORD dwBytesRead = 0;
		DWORD size = (DWORD)sizeof(szBuff);
		DWORD len = (DWORD)strlen(szBuff);
		if (!WriteFile(m_hSerial, szBuff, len, &dwBytesRead, NULL))
		{
			//error occurred. Report to user.
			auto lastError = GetLastError();
			m_errorState = COM_ERROR::SENDING_ERROR;
		}	
	}

	// free-function
	COM* createComPortOS(const std::string& name)
	{
		return new WinCom(name);
	}
}