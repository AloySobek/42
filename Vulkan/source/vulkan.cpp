/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vulkan.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 19:48:49 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/11 19:48:25 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <string>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <vector>
#include <cstring>
#include "/usr/local/include/vulkan/vulkan.h"
#include "../include/ilu.h"
#include "../shader_source/shaders.h"
#include "../VertexData/vertex.h"
#include "../include/glfw3.h"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"
#include "../libs/glm/glm/gtc/type_ptr.hpp"
#include "../libs/glm/glm/glm.hpp"

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool eanbleValidationLayers = true;
#endif

class GlfwWindow
{
	public:
		int mWidth;
		int	mHeight;

		GLFWwindow *mpWindow;
		GlfwWindow() : mWidth(1920), mHeight(1080)
		{
			glfwInit();
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			mpWindow = glfwCreateWindow(mWidth, mHeight, "Vulkan", nullptr, nullptr);
		}

		void mainLoop()
		{
			while (!glfwWindowShouldClose(mpWindow))
				glfwPollEvents();
		}
};

class Vulkan
{
	public:
		VkApplicationInfo						msAppInfo							= {};

		VkInstance								moInstance							= VK_NULL_HANDLE;
		VkInstanceCreateInfo					msCreateInstanceInfo				= {};

		VkPhysicalDevice						moPhysicalDevice					= VK_NULL_HANDLE;
		u_int32_t								mPhysicalDeviceCount				= 0;
		std::vector<VkPhysicalDevice>			mPhysicalDevicesList;
		VkPhysicalDeviceFeatures				msPhysicalDeviceFeatures			= {};
		VkPhysicalDeviceProperties				msPhysicalDeviceProperties			= {};

		u_int32_t								mPhysicalQueueNeeded				= 0;
		std::vector<VkQueueFamilyProperties>	mPhysicalQueueFamiliesList;
		u_int32_t								mPhysicalQueueFamilesCount			= 0;

		VkDevice								moDevice							= VK_NULL_HANDLE;
		VkDeviceCreateInfo						msCreateDeviceInfo					= {};
		VkDeviceQueueCreateInfo 				msDeviceQueueCreateInfo				= {};

		VkQueue									moGraphicQueue						= VK_NULL_HANDLE;

		VkSurfaceKHR							moSurface							= VK_NULL_HANDLE;

		unsigned int							mGlfwExtensionsCount				= 0;
		const char								**mppGlfwExtensions					= NULL;
		char									*mpName								= (char *)"Vulkan";
		char									*mpEngine							= (char *)"No engine";

		Vulkan(){}

		void run(GLFWwindow *window)
		{
			fillAppInfo();
			fillInstanceInfo();
			createInstance();
			createPhysicalDevice();
			createPhysicalDeviceQueue();
			createDeviceQueue(1.0f);
			createDevice();
			createSurface(window);
		}

	private:
		void fillAppInfo()
		{
			msAppInfo.sType				= VK_STRUCTURE_TYPE_APPLICATION_INFO;
			msAppInfo.pApplicationName	= mpName;
			msAppInfo.apiVersion		= VK_MAKE_VERSION(1, 0, 0);
			msAppInfo.pEngineName		= mpEngine;
			msAppInfo.engineVersion		= VK_MAKE_VERSION(1, 0, 0);
			msAppInfo.apiVersion		= VK_API_VERSION_1_0;
			msAppInfo.pNext				= nullptr;
		}

		void fillInstanceInfo()
		{
			msCreateInstanceInfo.sType						= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			msCreateInstanceInfo.pApplicationInfo			= &msAppInfo;
			mppGlfwExtensions								= glfwGetRequiredInstanceExtensions(&mGlfwExtensionsCount);
			for (int i = 0; i < mGlfwExtensionsCount; ++i)
				printf("%s\n", mppGlfwExtensions[i]);
			msCreateInstanceInfo.enabledExtensionCount		= mGlfwExtensionsCount;
			msCreateInstanceInfo.ppEnabledExtensionNames	= mppGlfwExtensions;
		}

		void createInstance()
		{
			if (vkCreateInstance(&msCreateInstanceInfo, nullptr, &moInstance) != VK_SUCCESS)
				throw std::runtime_error("Failed to create vulkan object");
		}

		void createPhysicalDevice()
		{
			vkEnumeratePhysicalDevices(moInstance, &mPhysicalDeviceCount, nullptr);
			if (mPhysicalDeviceCount < 1)
				throw std::runtime_error("Failed to find GPU device, exit...");
			mPhysicalDevicesList.resize(mPhysicalDeviceCount + 1);
			vkEnumeratePhysicalDevices(moInstance, &mPhysicalDeviceCount, mPhysicalDevicesList.data());
			for (const auto &device : mPhysicalDevicesList)
			{
				if (isDeviceSuitable(device))
				{
					moPhysicalDevice = device;
					break;
				}
			}
			if (moPhysicalDevice == VK_NULL_HANDLE)
				throw std::runtime_error("Failed suit GPU");
		}

		bool isDeviceSuitable(VkPhysicalDevice graphicDevice)
		{
			vkGetPhysicalDeviceProperties	(graphicDevice, &msPhysicalDeviceProperties);
			vkGetPhysicalDeviceFeatures		(graphicDevice, &msPhysicalDeviceFeatures);
			return msPhysicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;
		}

		void createPhysicalDeviceQueue()
		{
			bool found = false;

			vkGetPhysicalDeviceQueueFamilyProperties(moPhysicalDevice, &mPhysicalQueueFamilesCount, nullptr);
			mPhysicalQueueFamiliesList.resize(mPhysicalQueueFamilesCount + 1);
			vkGetPhysicalDeviceQueueFamilyProperties(moPhysicalDevice, &mPhysicalQueueFamilesCount, mPhysicalQueueFamiliesList.data());
			for (int i = 0; i < mPhysicalQueueFamiliesList.size(); ++i)
			{
				if (mPhysicalQueueFamiliesList[i].queueCount > 0 && mPhysicalQueueFamiliesList[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
				{
					mPhysicalQueueNeeded = i;
					found = true;
					break;
				}
			}
			if (!found)
				throw std::runtime_error("Failed to find physical queue for gpu");
		}

		void createDeviceQueue(float queuePriority)
		{
			msDeviceQueueCreateInfo.sType				= VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			msDeviceQueueCreateInfo.queueFamilyIndex	= mPhysicalQueueNeeded;
			msDeviceQueueCreateInfo.queueCount			= 1;
			msDeviceQueueCreateInfo.pQueuePriorities	= &queuePriority;
		}

		void createDevice()
		{
			msCreateDeviceInfo.sType				= VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			msCreateDeviceInfo.pQueueCreateInfos	= &msDeviceQueueCreateInfo;
			msCreateDeviceInfo.queueCreateInfoCount	= 1;
			msCreateDeviceInfo.pEnabledFeatures		= &msPhysicalDeviceFeatures;
			if (vkCreateDevice(moPhysicalDevice, &msCreateDeviceInfo, nullptr, &moDevice) != VK_SUCCESS)
				throw std::runtime_error("failed to create logical device");
			vkGetDeviceQueue(moDevice, mPhysicalQueueNeeded, 0, &moGraphicQueue);
		}

		void createSurface(GLFWwindow *window)
		{
			int error;

			if ((error = glfwCreateWindowSurface(moInstance, window, nullptr, &moSurface)) != VK_SUCCESS)
			{
				if (error == VK_ERROR_EXTENSION_NOT_PRESENT)
					printf("Fuck off\n");
				throw std::runtime_error("Surface creation error");
			}
		}
};

class Triangle
{
	public:
		Vulkan		mVulkanObject;
		GlfwWindow	mWindowObject;
		int		mProgramBuildError;

		Triangle(): mProgramBuildError(0) {}
		void run()
		{
			mVulkanObject.run(mWindowObject.mpWindow);
		}
};

int				main(int argc, char **argv)
{
	Triangle	app;

	try
	{
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return (0);
}