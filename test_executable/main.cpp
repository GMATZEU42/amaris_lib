#include "test_applicationx.h"

int main(int argc, char** argv)
{
	TestApplication app = TestApplication("test_app");
	app.init(argc, argv);
	app.run();
	return 0;
}