# VKTriangle #

This is my implementation of the [vulkan-tutorial.com](https://vulkan-tutorial.com) "Drawing a triangle" example. 


## My code changes ##
This code varies from the tutorial in several ways. I broke out each new chapter into a different `cpp` file for the `HelloTriangleApplication` class. I also inline the SPIR-V shaders as cstrings using `xxd` to avoid having file read calls in the program. 

Using `xxd` makes the build process somewhat restricted to the linux environment, but the precompiled header is not in the gitignore so it should still work on Windows as long as there are no needed changes to the GLSL files.


## Linux Building ##

You should follow the setup directions for the LunarG Vulkan SDK. This assumes you have configured the necessary path environment variables from that setup as they are used in the cmake file. You will need `glfw` installed so it can be found with `pkg-config`.

After you have set all that up you should be able to run `build.sh` to compile and launch the program.

## Known Issues ##
It currently maxes out the thread that it runs on which impacts the system performance. On some systems it will give a `VK_ERROR_DEVICE_LOST` error on exit.
