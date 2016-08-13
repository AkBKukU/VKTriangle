#include "HelloTriangleApplication.h"

/*
 * Creates Swap Chain
 */



/*
 * Check device supports extensions
 */
bool HelloTriangleApplication::checkDeviceExtensionSupport(VkPhysicalDevice device) 
{
	// Get all extensions the device supports
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());
	// Make copy of required extensions
	std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
	
	// Go through all extensions
	for (const auto& extension : availableExtensions) 
	{
		// Delete any matched extensions from the copy
		requiredExtensions.erase(extension.extensionName);
	}
	
	// All extensions from the copy should have been deleted
	return requiredExtensions.empty();	
}

/*
 * Check swap chain support
 */
SwapChainSupportDetails HelloTriangleApplication::querySwapChainSupport(VkPhysicalDevice device) {
	SwapChainSupportDetails details;

	// Check device support Surface
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

	// Get the supported surface formats
	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

	if (formatCount != 0) 
	{
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
	}

	// Get present modes supported
	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

	if (presentModeCount != 0) 
	{
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
	}

	return details;
}

/*
 * Choose color space format
 */
VkSurfaceFormatKHR HelloTriangleApplication::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
	// Check for no perfered format support
	if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) 
	{
		// Default to ideal format of sRGB color space and use RGB color
		return {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
	}

	// Check if perfered format is availible
	for (const auto& availableFormat : availableFormats) 
	{
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) 
		{
			return availableFormat;
		}
	}
	
	// Perfered is not availible.
	return availableFormats[0];
}

/*
 * Choose swap chain buffer mode
 */
VkPresentModeKHR HelloTriangleApplication::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes)
{
	// Look for prefered mode
	for (const auto& availablePresentMode : availablePresentModes) 
	{
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) 
		{
			return availablePresentMode;
		}
	}
	
	// Use default mdoe
	return VK_PRESENT_MODE_FIFO_KHR;
}

/*
 * Set swap chain resolution
 */
VkExtent2D HelloTriangleApplication::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
{
	// Check if we can use the surface values
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) 
	{
		return capabilities.currentExtent;
	} else {
		//use values store in class
		VkExtent2D actualExtent = {WIDTH, HEIGHT};

		actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
		actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));
		
		return actualExtent;
	}
}

/*
 * Initialize the swap chain
 */
void HelloTriangleApplication::createSwapChain()
{
	// Get details for swap chain
	SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice);

	// Get best options for configuring swap chain
	VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
	VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
	VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

	// Determine number of images to keep in swap chain
	uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

	// Verify the imageCount is not greater than the maximum allowed
	if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
		imageCount = swapChainSupport.capabilities.maxImageCount;
	}

	// Fill in swap chain information
	VkSwapchainCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = surface;

	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1; // Has to do with Stero 3D
	// Indicate swap chain will be rendered to
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	// Configure swap chain based on queue families
	QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
	uint32_t queueFamilyIndices[] = {(uint32_t) indices.graphicsFamily, (uint32_t) indices.presentFamily};

	// If the graphics and present queue are not in the same family allow
	// access from multiple queues
	if (indices.graphicsFamily != indices.presentFamily) {
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	} else {
		// If they are the same set the access to exclusive for 
		// perfomance
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	}
	
	// Specific screen transforms
	/*
	 * I suspect this would be used to rotate the screen on a moblie device
	 *
	 * It may aslo be used for distortion for VR
	 */
	createInfo.preTransform = swapChainSupport.capabilities.currentTransform;

	// Set window Alpha setting. Might be able to make the window
	// transparent by changing this
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

	// Set the chain render mode
	createInfo.presentMode = presentMode;

	// Ignore hidden pixels(might have to change for complex shaders)
	createInfo.clipped = VK_TRUE;
	
	// Not yet implimented but will be important for handling resizing
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	// Make the API call to initilize the swap chain
	if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
		throw std::runtime_error("failed to create swap chain!");
	}
	
	// Retrive pointers the the created images	
	vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
	swapChainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());

	// Store the information about the image format
	swapChainImageFormat = surfaceFormat.format;
	swapChainExtent = extent;		
}
