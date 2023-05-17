#pragma once

#include "console.h"

#include <Windows.h>
#include <conio.h>

namespace amaris
{
	void Console::changeColor(ConsoleColor color)  const 
	{
		WORD c = 0U;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		switch (color)
		{
		case amaris::ConsoleColor::DEFAULT:
			break;
		case amaris::ConsoleColor::NATIVE:
			c = 7U;
			break;
		case amaris::ConsoleColor::GREY:
			c = 8U;
			break;
		case amaris::ConsoleColor::BLUE:
			c = 9U;
			break;
		case amaris::ConsoleColor::GREEN:
			c = 10U;
			break;
		case amaris::ConsoleColor::AZURE:
			c = 11U;
			break;
		case amaris::ConsoleColor::RED:
			c = 12U;
			break;
		case amaris::ConsoleColor::MAGENTA:
			c = 13U;
			break;
		case amaris::ConsoleColor::YELLOW:
			c = 14U;
			break;
		case amaris::ConsoleColor::ORANGE:
			c = FOREGROUND_RED | FOREGROUND_GREEN;
			break;
		default:
			break;
		}

		SetConsoleTextAttribute(hConsole, c);
	}
}