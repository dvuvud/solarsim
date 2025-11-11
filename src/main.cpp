#include <engine/engine.hpp>
#include <iostream>

int main()
{
	try 
	{
		solarsim::Engine engine;
		engine.run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
