#include "amaris.h"

int main(int argc, char** argv)
{
	amaris::Application app = amaris::Application();
	app.init(argc, argv);
	app.run();
	return 0;
}