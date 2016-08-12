#include "HelloTriangleApplication.h"

/*
 * Creates Window Surface
 */
void HelloTriangleApplication::createSurface() 
{
	// Use GLFW to create the surface for the platform automatically
	if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) 
	{
		throw std::runtime_error("failed to create window surface!");
	}
}
