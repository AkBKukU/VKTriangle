#ifndef SwapChainSupportDetails_H
#define SwapChainSupportDetails_H

// Struct for holding indices for queue families
struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

#endif
