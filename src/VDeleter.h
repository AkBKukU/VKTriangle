#ifndef VDeleter_H
#define VDeleter_H

#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <functional>

template <typename T>
class VDeleter {
public:
	VDeleter() : VDeleter([](T _) {}) {}

	VDeleter(
		std::function<void(T, VkAllocationCallbacks*)> deletef
	) {
		this->deleter = 
			[=](T obj) 
			{ 
				deletef(obj, nullptr); 
			};
	}

	VDeleter(
		const VDeleter<VkInstance>& instance, 
		std::function<void(VkInstance, T, VkAllocationCallbacks*)> deletef
	) {
		this->deleter = 
			[&instance, deletef](T obj) 
			{ 
				deletef(instance, obj, nullptr); 
			};
	}

	VDeleter(
		const VDeleter<VkDevice>& device, 
		std::function<void(VkDevice, T, VkAllocationCallbacks*)> deletef
	) {
		this->deleter = 
			[&device, deletef](T obj) 
			{ 
				deletef(device, obj, nullptr); 
			};
	}

	~VDeleter() 
	{
		cleanup();
	}

	T* operator &() 
	{
		cleanup();
		return &object;
	}

	operator T() const 
	{
		return object;
	}

private:
	T object{VK_NULL_HANDLE};
	std::function<void(T)> deleter;

	void cleanup() 
	{
		if (object != VK_NULL_HANDLE) 
		{
			deleter(object);
		}
		object = VK_NULL_HANDLE;
	}
};

#endif