#ifndef QueueFamilyIndices_H
#define QueueFamilyIndices_H

// Struct for holding indices for queue families
struct QueueFamilyIndices 
{
	int graphicsFamily = -1;
	int presentFamily = -1;

	bool isComplete() 
	{
		return graphicsFamily >= 0 && presentFamily >= 0;
	}
};

#endif
