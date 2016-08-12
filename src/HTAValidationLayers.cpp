#include "HelloTriangleApplication.h"

/*
 * Creates Validation Layers
 */



/*
 * Check that validation layers are supported by system
 */
bool  HelloTriangleApplication::checkValidationLayerSupport() 
{
	// Get number of layers system supports
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	// Get layers in the system
	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
	
	// Check desired layer names for a match to the validation layer
	for (const char* layerName : validationLayers)
	{
		// State of layer match
		bool layerFound = false;
		// Go through available layers
		for (const auto& layerProperties : availableLayers) 
		{
			// Check for match
			if (strcmp(layerName, layerProperties.layerName) == 0) 
			{
				// Match found exit loop
				layerFound = true;
				break;
			}
		}
		
		// A Layer was not found so exit with false
		if (!layerFound) 
		{
			return false;
		}
	}
	
	// By this point all layers were found
	return true;

}

/*
 * Get required extensions
 */
std::vector<const char*>  HelloTriangleApplication::getRequiredExtensions() 
{
	// Create container for extensions
	std::vector<const char*> extensions;
	
	// Find extensions for GLFW
	unsigned int glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	
	// Add GLFW extensions to vector	
	for (unsigned int i = 0; i < glfwExtensionCount; i++) {
		extensions.push_back(glfwExtensions[i]);
	}
	
	// Check for and add validation layers.
	if (enableValidationLayers) {
		extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	}
	
	return extensions;
}

/*
 * Find extensions available on system 
 */
void  HelloTriangleApplication::checkExtensions()
{
	// Get number of available extensions
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	
	// Create vector to hold info on extensions
	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
	
	// Print out extension names
	std::cout << "available extensions:" << std::endl;
	// Go through all extensions and print names
	for (const auto& extension : extensions) {
		std::cout << "\t" << extension.extensionName << std::endl;
	}
}

/*
 * Debug error printer
 */
VkBool32  HelloTriangleApplication::debugCallback (
	VkDebugReportFlagsEXT flags,
	VkDebugReportObjectTypeEXT objType,
	uint64_t obj,
	size_t location,
	int32_t code,
	const char* layerPrefix,
	const char* msg,
	void* userData
) {
	// Print out error message
	std::cerr << "validation layer: " << msg << std::endl;
	
	// Return error flag
	return VK_FALSE;
}

/*
 *  Setup the debug callback output
 */
void  HelloTriangleApplication::setupDebugCallback() 
{
	if (!enableValidationLayers) return;
	
	VkDebugReportCallbackCreateInfoEXT createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
	createInfo.pfnCallback = (PFN_vkDebugReportCallbackEXT) debugCallback;

	if (CreateDebugReportCallbackEXT(instance, &createInfo, nullptr, &callback) != VK_SUCCESS) {
		throw std::runtime_error("failed to set up debug callback!");
	}	
}