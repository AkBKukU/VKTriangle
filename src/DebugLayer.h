#ifndef DebugLayer_H
#define DebugLayer_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h> // Imported by GLFW but needed for code completion
#include <iostream>
#include <stdexcept>
#include <functional>
#include <vector>
#include <cstring>



/*
 * The following two functions create pointer references for functions in the
 * validation layer that are NOT created by the API. The implementation here is 
 * messy and complicated. For future use check out this page for a better way:
 * http://gpuopen.com/using-the-vulkan-validation-layers/
 *
 * The above site creates actual implementations of the pointers to use while
 * the tutorial finds the pointers every call and masks the functions. This is
 * much less efficient.
 *
 * For now the original methods will be kept to maintain compatibility with the
 * tutorial. As the tutorial uses it with the VDeleter class you never directly
 * call the functions anyway. 
 */

/* This is dumb. Don't do this in real code...
 *
 * Retrieve the vkCreateDebugReportCallbackEXT function for validation, check if
 * it exists, and run it. Then return the result of running it.
 */
VkResult CreateDebugReportCallbackEXT (
	VkInstance instance, 
	const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, 
	const VkAllocationCallbacks* pAllocator, 
	VkDebugReportCallbackEXT* pCallback
);

/* This is dumb. Don't do this in real code...
 *
 * Retrieve the vkCreateDebugReportCallbackEXT function for validation, check if
 * it exists, and run it. Then return the result of running it.
 */
void DestroyDebugReportCallbackEXT(
	VkInstance instance, 
	VkDebugReportCallbackEXT callback, 
	const VkAllocationCallbacks* pAllocator
);



#endif
