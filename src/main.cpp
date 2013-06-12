#include "lib/Game.h"
int main()
{
	Game app;
	if(!app.onInit())
	{
		Log::log("Error initializing engine. See above warning.");
	}
	return app.run();
}
