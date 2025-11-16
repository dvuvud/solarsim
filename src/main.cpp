#include <engine/engine.hpp>
#include <iostream>

int main()
{
	try 
	{
		solarsim::Engine engine;
		std::cout << glGetString(GL_VERSION) << std::endl;
		std::cout << glGetString(GL_VENDOR) << std::endl;
		std::cout << glGetString(GL_RENDERER) << std::endl;
		std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
		engine.run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
