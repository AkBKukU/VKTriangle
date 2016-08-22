#ifndef HelloTriangleApplication_H
#define HelloTriangleApplication_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h> // Imported by GLFW but needed for code completion
#include <iostream>
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>
#include "DebugLayer.h"
#include "QueueFamilyIndices.h"
#include "SwapChainSupportDetails.h"
#include "VDeleter.h"


/* 
 * Class that contains all the init code for a GLFW window and a vulkan instance
 */
class HelloTriangleApplication {
public:

	/*
	 * Calls all setup functions then starts logic loop
	 */
	void run();

private:
	// GLFW members
	GLFWwindow* window;

	// Vulkan members
	VDeleter<VkInstance> instance {vkDestroyInstance}; // Main instance
	VDeleter<VkDebugReportCallbackEXT> callback{instance, DestroyDebugReportCallbackEXT};
	VDeleter<VkDevice> device{vkDestroyDevice};

	// Create device info
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	// Device Queue handle
	VkQueue graphicsQueue;
	VkQueue presentQueue;

	// Window Frame
	const int WIDTH = 800;
	const int HEIGHT = 600;
	
	// Surface
	VDeleter<VkSurfaceKHR> surface{instance, vkDestroySurfaceKHR};

	// Swap Chain
	VDeleter<VkSwapchainKHR> swapChain{device, vkDestroySwapchainKHR};
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	// Image View
	std::vector<VDeleter<VkImageView>> swapChainImageViews;

	// Check if compiling as debug and include validation layers
#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif
	// Graphic pipeline layout
	VDeleter<VkPipelineLayout> pipelineLayout{device, vkDestroyPipelineLayout};



	// Set validation layer name
	const std::vector<const char*> validationLayers = {
		"VK_LAYER_LUNARG_standard_validation"
	};

	// Extensions to use
	const std::vector<const char*> deviceExtensions = 
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	
	/*
	 * Initializes GLFW window
	 */
	void initWindow();

	/*
	 * Setup vulkan instance
	 */
	void initVulkan();

	/*
	 * Choose the GPU to be used by vulkan
	 */
	void pickPhysicalDevice();

	/*
	 * Creates an interface to a logical device
	 */
	void createLogicalDevice();
	
	/*
	 * Check if given device meets all needed requirements
	 */
	bool isDeviceSuitable(VkPhysicalDevice device);

	/*
	 * Find available queue families
	 */
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	/*
	 *  Setup the debug callback output
	 */
	void setupDebugCallback();

	/*
	 * Find extensions available on system 
	 */
	void checkExtensions();
	
	/*
	 * Check that validation layers are supported by system
	 */
	bool checkValidationLayerSupport();
	
	/*
	 * Get required extensions
	 */
	std::vector<const char*> getRequiredExtensions();
	
	/*
	 * Debug error printer
	 */
	static VkBool32 debugCallback (
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t obj,
		size_t location,
		int32_t code,
		const char* layerPrefix,
		const char* msg,
		void* userData
	);
	
	/*
	 * Create and configure instance of vulkan
	 */	
	void createInstance();

	/*
	 * Create Window Surface
	 */
	void createSurface(); 

	/*
	 * Check device supports extensions
	 */
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);

	/*
	 * Check swap chain support
	 */
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

	/*
	 * Swap chain choosing
	 */
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	/*
	 * Initialize the swap chain
	 */
	void createSwapChain();

	
	/*
	 * Create Swap Chain Image Views
	 */
	void createImageViews();	
	
	/*
	 * Create the Graphics Pipeline
	 */ 
	void createGraphicsPipeline();

	/*
	 * Shader module builder
	 */
	void createShaderModule(const std::vector<char>& code, VDeleter<VkShaderModule>& shaderModule);

	/*
	 * Logic loop
	 */
	void mainLoop();


};


#endif
