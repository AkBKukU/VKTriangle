#include "HelloTriangleApplication.h"

/*
 * Base HelloTriangleApplication methods
 */

/*
 * Calls all setup functions then starts logic loop
 */
void HelloTriangleApplication::run() 
{
	initWindow();		// GLFW
	initVulkan();		// Vulkan instance
	checkExtensions();	// Check vulkan extensions
	mainLoop();		// Enter logic loop
}
/*
 * Initializes GLFW window
 */
void HelloTriangleApplication::initWindow()
{
	// GLFW init call for platform setup
	glfwInit();
	
	// Setup window properties
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Disable OpenGL
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);   // Disable resize

	// Create window instance
	window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

/*
 * Setup vulkan instance
 */
void HelloTriangleApplication::initVulkan() 
{
	createInstance(); // Create instance
   	setupDebugCallback(); // Setup debug
	createSurface(); // Create Window Surface
	pickPhysicalDevice(); // Choose GPU
	createLogicalDevice(); // Create Device Interface
	createSwapChain(); // Create the swap chain for render images
	createImageViews(); // Create ImageViwes to interact with swap images
	createRenderPass(); // Set up render passes
	createGraphicsPipeline(); // Create the graphic pipeline for rendering
	createFramebuffers();
	createCommandPool();
	createCommandBuffers();
	createSemaphores();

}

/*
 * Logic loop
 */
void HelloTriangleApplication::mainLoop() 
{
	// Maintain loop until the window is closed	
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		drawFrame();				
	}

	vkDeviceWaitIdle(device);
}
