#include "HelloTriangleApplication.h"

/*
 * Creates Logical Device
 */



/*
 * Creates an interface to a logical device
 */
void HelloTriangleApplication::createLogicalDevice()
{
	// Get current queue
	QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

	
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<int> uniqueQueueFamilies = {indices.graphicsFamily, indices.presentFamily};

	for (int queueFamily : uniqueQueueFamilies) 
	{
		float queuePriority = 1.0f;

		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}
	// Specify needed device features(Currently none required)_
	VkPhysicalDeviceFeatures deviceFeatures = {};

	// Create Device info
	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.queueCreateInfoCount = (uint32_t) queueCreateInfos.size();

	createInfo.pEnabledFeatures = &deviceFeatures;
	
	// Specify needed extensions
	createInfo.enabledExtensionCount = 0;

	if (enableValidationLayers) 
	{
		createInfo.enabledLayerCount = validationLayers.size();
		createInfo.ppEnabledLayerNames = validationLayers.data();
	} else {
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) 
	{
		throw std::runtime_error("failed to create logical device!");
	}
	
	// Get device queue
	vkGetDeviceQueue(device, indices.graphicsFamily, 0, &graphicsQueue);
	vkGetDeviceQueue(device, indices.presentFamily, 0, &presentQueue);
}
