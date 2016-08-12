#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h> // Imported by GLFW but needed for code completion
#include <iostream>
#include <stdexcept>
#include <functional>
#include <vector>
#include <cstring>

#include "HelloTriangleApplication.h"



/* 
 * FOREWORD
 *
 * This code is based off the tutorial from the website vulkan-tutorial.com
 *
 * It is not a verbatim copy paste that includes improved formatting, some 
 * abstraction, and comments.
 */

/*
 * Run the HelloTriangleApplication application
 */
int main() {
	HelloTriangleApplication app;

	try {
		app.run();
	} catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

