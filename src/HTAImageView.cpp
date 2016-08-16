#include "HelloTriangleApplication.h"

/*
 * Image Views
 */


/*
 * Create Image Views
 */
void HelloTriangleApplication::createImageViews()
{
	// Expand ImageView vector to number of swap images
	swapChainImageViews.resize(
			swapChainImages.size(), 
			VDeleter<VkImageView>{device, vkDestroyImageView}
	);
	
	// Got through all ImageViews
	for (uint32_t i = 0; i < swapChainImages.size(); i++) 
	{
		// Setup ImageView properties
		VkImageViewCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = swapChainImages[i]; // Set the swap chain image
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = swapChainImageFormat;
		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;

		// Create the ImageView
		if (vkCreateImageView(device, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to create image views!");
		}
	}
}
