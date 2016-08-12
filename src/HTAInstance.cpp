#include "HelloTriangleApplication.h"

/*
 * Creates Instance
 */


/*
 * Create and configure instance of vulkan
 */	
void HelloTriangleApplication::createInstance()
{
	// Check if validation layers are to be used and that the exist
	if (enableValidationLayers && !checkValidationLayerSupport()) {
		throw std::runtime_error("validation layers requested, but not available!");
	}

	// Define struct with application info 
	VkApplicationInfo appInfo = {};
	appInfo.sType = 				VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = 		"Hello Triangle";
	appInfo.applicationVersion = 	VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = 			"No Engine";
	appInfo.engineVersion = 		VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = 			VK_API_VERSION_1_0;

	// Define struct with instance info
	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = 				VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = 	&appInfo;

	// Find extensions for GLFW
	unsigned int glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	// Add extensions
	auto extensions = getRequiredExtensions();
	createInfo.enabledExtensionCount = extensions.size();
	createInfo.ppEnabledExtensionNames = extensions.data();
	
	// Validation layers
	if (enableValidationLayers) 
	{
		// Add validation layers
		createInfo.enabledLayerCount = validationLayers.size();
		createInfo.ppEnabledLayerNames = validationLayers.data();
	} else {
		// Set no layers
		createInfo.enabledLayerCount = 0;
	}

	// Initialize the instance and verify
	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
		throw std::runtime_error("failed to create instance!");
	}

}
