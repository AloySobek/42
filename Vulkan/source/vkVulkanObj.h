/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vkVulkanObj.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:59:07 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/14 20:50:32 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VK_VULKAN_OBJECT_H
# define VK_VULKAN_OBJECT_H

#include "includes.h"

class Vulkan
{
	public:
		/*
		** Instance Object creating and handle--------------------------------------------
		*/
		VkInstance					instanceObj							= VK_NULL_HANDLE;
		VkApplicationInfo			sAppCreateInfo						= {};
		VkInstanceCreateInfo		sInstanceCreateInfo					= {};
		VkExtensionProperties		*pAvailableInstanceExtensions		= nullptr;
		const char 					**ppAvailableInstanceExtensionsNames= nullptr;
		u_int32_t					availableInstanceExtensionsCount	= 0;
		u_int32_t					selectedInstanceExtensionsCount		= 0;
		VkLayerProperties			*pAvailableInstanceLayers			= nullptr;
		const char					**ppAvailableInstanceLayersNames	= nullptr;
		u_int32_t					availableInstanceLayersCount		= 0;
		u_int32_t					selectedInstanceLayersCount			= 0;
		/*
		** Physical Device finding and setup----------------------------------------------
		*/
		VkPhysicalDevice			physicalDeviceObj					= VK_NULL_HANDLE;
		VkPhysicalDevice			*pAvailablePhysicalDevices			= nullptr;
		VkPhysicalDeviceFeatures	msPhysicalDeviceFeatures			= {};
		VkPhysicalDeviceProperties	msPhysicalDeviceProperties			= {};
		u_int32_t					availablePhysicalDeviceCount		= 0;
		u_int32_t					availablePhysicalDeviceQueuesCount	= 0;

		VkQueue						graphicQueue						= VK_NULL_HANDLE;
		VkQueue						presentQueue						= VK_NULL_HANDLE;
		VkQueueFamilyProperties		*p

		u_int32_t					mGraphicQueueIndex					= 0;
		u_int32_t					mPresentQueueIndex					= 0;
		u_int32_t					mPhysicalQueueFamilesCount			= 0;

		VkDevice					moDevice							= VK_NULL_HANDLE;
		VkDeviceCreateInfo			msCreateDeviceInfo					= {};
		VkDeviceQueueCreateInfo 	msDeviceQueueCreateInfo				= {};
		VkDeviceQueueCreateInfo		msPresentQueueCreateInfo			= {};

		VkSurfaceKHR				moSurface							= VK_NULL_HANDLE;
		const char					**ppAvailableDeviceExtensions;
		const char 					**ppAvailableDeviceLayers;
		u_int32_t					availableDeviceLayresCount;
		u_int32_t					availableDeviceExtensionsCount;

		int							mError;

		Vulkan(){}

		void run(GLFWwindow *window)
		{
			vkSetupAppInfo();
			vkSetupInstanceLayers();
			vkSetupInstanceExtensions();
			vkSetupInstanceCreateInfo();
			vkCreateInstanceObj();

			vkChoosePhysicalDeviceObj();
			vkQueryPhysicalDeviceQueue();

			createDeviceQueue(1.0f);
			createDevice();
			createSurface(window);
		}

	private:
		void vkSetupAppInfo				();
		void vkSetupInstanceLayers		();
		void vkSetupInstanceExtensions	();
		void vkSetupInstanceCreateInfo	();
		void vkCreateInstanceObj		();

		void vkChoosePhysicalDeviceObj	();

		bool vkIsExtensionSuitable		(VkExtensionProperties);
		bool vkIsLayerSuitable			(VkLayerProperties);
		bool vkIsDeviceSuitable			(VkPhysicalDevice graphicDevice);
		void vkQueryPhysicalDeviceQueue	();

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

#endif