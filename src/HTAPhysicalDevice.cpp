#include "HelloTriangleApplication.h"

/*
 * Creates Physical Device and Queue Families
 */


/*
 * Choose the GPU to be used by vulkan
 */
void HelloTriangleApplication::pickPhysicalDevice()
{
	// Count all available GPUs
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
	if (deviceCount == 0) 
	{
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}
	
	// Get all available GPUs
	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	for (const auto& device : devices) 
	{
		if (isDeviceSuitable(device)) 
		{
			physicalDevice = device;
			break;
		}
	}

	if (physicalDevice == VK_NULL_HANDLE) 
	{
		throw std::runtime_error("failed to find a suitable GPU!");
	}

}


/*
 * Check if given device meets all needed requirements
 */
bool HelloTriangleApplication::isDeviceSuitable(VkPhysicalDevice device) 
{
	QueueFamilyIndices indices = findQueueFamilies(device);

	// Check for require queues
	return indices.isComplete();
}

/*
 * Find available queue families
 */
QueueFamilyIndices HelloTriangleApplication::findQueueFamilies(VkPhysicalDevice device) 
{
	QueueFamilyIndices indices;
	
	// Get number of families
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	// Save families 
	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	// Check for a queue family with the graphics bit set
	int i = 0;
	for (const auto& queueFamily : queueFamilies) {
		// Check if that there are queues in the family
		// then check for the graphics bit
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) 
		{
			indices.graphicsFamily = i;
		}
		
		// Get support for presenting
		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

		if (queueFamily.queueCount > 0 && presentSupport) 
		{
			indices.presentFamily = i;
		}

		// If index is found, break
		if (indices.isComplete()) {
			break;
		}

		i++;
	}

	return indices;
}
