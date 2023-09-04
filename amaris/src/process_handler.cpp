#include "process_handler.h"

#ifdef _WIN32
#include "process_handler_win.h"
#else
#include "process_handler_linux.h"
#endif // _WIN32


namespace amaris
{
	ProcessHandler::ProcessHandler() {};

	ProcessHandler::~ProcessHandler() {};

}