#include "Engine/Engine.hpp"

int main(int argc, char* args[])
{
	Engine engine;
    engine.init();
	engine.run();
    engine.deinit();
    
	return 0;
}
