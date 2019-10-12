/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vulkan.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 19:48:49 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/12 19:59:52 by vrichese         ###   ########.fr       */
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
		VkPhysicalDeviceFeatures				msPhysicalDeviceFeatures			= {};
		VkPhysicalDeviceProperties				msPhysicalDeviceProperties			= {};

		VkQueue									moGraphicQueue						= VK_NULL_HANDLE;
		VkQueue									moPresentQueue						= VK_NULL_HANDLE;
		u_int32_t								mGraphicQueueIndex					= 0;
		u_int32_t								mPresentQueueIndex					= 0;
		std::vector<VkQueueFamilyProperties>	mPhysicalQueueFamiliesList;
		u_int32_t								mPhysicalQueueFamilesCount			= 0;

		VkDevice								moDevice							= VK_NULL_HANDLE;
		VkDeviceCreateInfo						msCreateDeviceInfo					= {};
		VkDeviceQueueCreateInfo 				msDeviceQueueCreateInfo				= {};
		VkDeviceQueueCreateInfo					msPresentQueueCreateInfo			= {};

		VkSurfaceKHR							moSurface							= VK_NULL_HANDLE;

		char									*mpName								= (char *)"Vulkan";
		char									*mpEngine							= (char *)"No engine";
		int										mError;

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
			msAppInfo.apiVersion		= VK_API_VERSION_1_1;
			msAppInfo.pNext				= nullptr;
		}

		void fillInstanceInfo()
		{
			VkLayerProperties	*pLayersProperties;
			const char			**ppGlfwExtensions;
			const char			**ppLayersNames;
			u_int32_t			glfwExtensionsCount;
			u_int32_t			layersCount;

			msCreateInstanceInfo.sType				= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			msCreateInstanceInfo.pApplicationInfo	= &msAppInfo;
			ppGlfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);
			vkEnumerateInstanceLayerProperties(&layersCount, nullptr);
			pLayersProperties	= (VkLayerProperties *)malloc(sizeof(VkLayerProperties) * layersCount);
			ppLayersNames		= (const char **)malloc(sizeof(const char *) * layersCount);
			vkEnumerateInstanceLayerProperties(&layersCount, pLayersProperties);
			for (int i = 0; i < layersCount; ++i)
				ppLayersNames[i] = pLayersProperties[i].layerName;

			msCreateInstanceInfo.enabledExtensionCount		= glfwExtensionsCount;
			msCreateInstanceInfo.ppEnabledExtensionNames	= ppGlfwExtensions;
			msCreateInstanceInfo.enabledLayerCount			= layersCount;
			msCreateInstanceInfo.ppEnabledLayerNames		= ppLayersNames;
		}

		void createInstance()
		{
			if ((mError = vkCreateInstance(&msCreateInstanceInfo, nullptr, &moInstance)) != VK_SUCCESS)
			{
				std::cout << mError << std::endl;
				throw std::runtime_error("Failed to create instance object");
			}
		}

		void createPhysicalDevice()
		{
			std::vector<VkPhysicalDevice>	physicalDevicesList;
			u_int32_t						physicalDeviceCount;

			vkEnumeratePhysicalDevices(moInstance, &physicalDeviceCount, nullptr);
			physicalDevicesList.resize(physicalDeviceCount);
			vkEnumeratePhysicalDevices(moInstance, &physicalDeviceCount, physicalDevicesList.data());
			for (const auto &device : physicalDevicesList)
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
					mGraphicQueueIndex = i;
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
			msPresentQueueCreateInfo.sType				= VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			msDeviceQueueCreateInfo.queueFamilyIndex	= mGraphicQueueIndex;
			msPresentQueueCreateInfo.queueFamilyIndex	= mPresentQueueIndex;
			msDeviceQueueCreateInfo.queueCount			= 1;
			msPresentQueueCreateInfo.queueCount			= 1;
			msDeviceQueueCreateInfo.pQueuePriorities	= &queuePriority;
			msDeviceQueueCreateInfo.pQueuePriorities	= &queuePriority;
		}

		void createDevice()
		{
			VkDeviceQueueCreateInfo	*createList;
			const char 				**extensions;
			unsigned int			extCount;

			vkEnumerateDeviceExtensionProperties(moPhysicalDevice, nullptr, &extCount, nullptr);
			std::vector <VkExtensionProperties> properties(extCount);
			vkEnumerateDeviceExtensionProperties(moPhysicalDevice, nullptr, &extCount, properties.data());

			extensions = (const char **)malloc(sizeof(char *) * 1);
			extensions[0] = "VK_KHR_swapchain";
			createList								= (VkDeviceQueueCreateInfo *)malloc(sizeof(VkDeviceQueueCreateInfo) * 2);
			createList[0]							= msDeviceQueueCreateInfo;
			createList[1]							= msPresentQueueCreateInfo;
			msCreateDeviceInfo.sType				= VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			msCreateDeviceInfo.enabledExtensionCount = 1;
			msCreateDeviceInfo.ppEnabledExtensionNames = extensions;
			msCreateDeviceInfo.pQueueCreateInfos	= createList;
			msCreateDeviceInfo.queueCreateInfoCount	= 1;
			msCreateDeviceInfo.pEnabledFeatures		= &msPhysicalDeviceFeatures;
			if (vkCreateDevice(moPhysicalDevice, &msCreateDeviceInfo, nullptr, &moDevice) != VK_SUCCESS)
				throw std::runtime_error("failed to create logical device");
			vkGetDeviceQueue(moDevice, mGraphicQueueIndex, 0, &moGraphicQueue);
			vkGetDeviceQueue(moDevice, mPresentQueueIndex, 0, &moPresentQueue);
		}

		void createSurface(GLFWwindow *window)
		{
			VkBool32 presentQueueFound = false;

			if ((mError = glfwCreateWindowSurface(moInstance, window, nullptr, &moSurface)) != VK_SUCCESS)
				throw std::runtime_error("Surface creation error");
			for (int i = 0; i < mPhysicalQueueFamiliesList.size(); ++i)
			{
				if (mPhysicalQueueFamiliesList[i].queueCount > 0 && mPhysicalQueueFamiliesList[i].queueFlags & VK_QUEUE_COMPUTE_BIT)
				{
					vkGetPhysicalDeviceSurfaceSupportKHR(moPhysicalDevice, i, moSurface, &presentQueueFound);
					mPresentQueueIndex = i;
				}
			}
			VkSurfaceCapabilitiesKHR cap;
			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(moPhysicalDevice, moSurface, &cap);
			unsigned int count;
			vkGetPhysicalDeviceSurfaceFormatsKHR(moPhysicalDevice, moSurface, &count, nullptr);
			std::vector <VkSurfaceFormatKHR> formats(count);
			vkGetPhysicalDeviceSurfaceFormatsKHR(moPhysicalDevice, moSurface, &count, formats.data());
			for (int i = 0; i < formats.size(); ++i)
				std::cout << formats[i].format  << "   " << formats[i].colorSpace << std::endl;
			unsigned int count2;
			vkGetPhysicalDeviceSurfacePresentModesKHR(moPhysicalDevice, moSurface, &count2, nullptr);
			std::vector <VkPresentModeKHR> present(count2);
			vkGetPhysicalDeviceSurfacePresentModesKHR(moPhysicalDevice, moSurface, &count2 , present.data());
			for (int i = 0; i < present.size(); ++i)
				std::cout << present[i] << std::endl;
			exit(1);
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