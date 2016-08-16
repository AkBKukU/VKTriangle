#include "HelloTriangleApplication.h"
#include "shaders/CompiledShaders.h" // File with compiled shaders as char array

/*
 * Graphic pipeline setup
 */
void HelloTriangleApplication::createGraphicsPipeline()
{
	/*
	 * This deviates from the tutorial. I wanted to keep everything in one
	 * binary output still so the shaders are put into a header file using
	 * xxd and then icluded at the top. 
	 */

	// Get shader code
	// This could probably be optimised to prevent data copying but I am 
	// maintaining compatibility with the tutorial.
	auto vertShaderCode = std::vector<char>(vert_spv, vert_spv + vert_spv_len);
	auto fragShaderCode = std::vector<char>(frag_spv, frag_spv + frag_spv_len);
	
	// Create modules for each shader
	VDeleter<VkShaderModule> vertShaderModule{device, vkDestroyShaderModule};
	VDeleter<VkShaderModule> fragShaderModule{device, vkDestroyShaderModule};
	
	createShaderModule(vertShaderCode, vertShaderModule);
	createShaderModule(fragShaderCode, fragShaderModule);

	// Create the vertex shader Stage
	VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
	vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;	
	vertShaderStageInfo.module = vertShaderModule;
	vertShaderStageInfo.pName = "main";	
	
	// Create the fragment shader stage
	VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
	fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragShaderStageInfo.module = fragShaderModule;
	fragShaderStageInfo.pName = "main";
	
	// Combine stages into an array
	VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};
}

/*
 * Create a shader module from the given code
 */
void HelloTriangleApplication::createShaderModule(const std::vector<char>& code, VDeleter<VkShaderModule>& shaderModule)
{
	// Define the shader module
	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = (uint32_t*) code.data();

	// Create the shader module
	if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
		throw std::runtime_error("failed to create shader module!");
	}
}
