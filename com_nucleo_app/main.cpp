#include "com_nucleo.h"

int main(int argc, char** argv)
{
	ComNucleoApp app = ComNucleoApp("ComNucleoApp");
	app.init(argc, argv);
	app.run();
	return 0;
}