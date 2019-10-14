/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vkVulkanImpl.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:55:17 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/14 20:49:59 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vkVulkanObj.h"

void Vulkan::vkSetupAppInfo()
{
	sAppCreateInfo.sType				= VK_STRUCTURE_TYPE_APPLICATION_INFO;
	sAppCreateInfo.pApplicationName	= "VulkanLearn";
	sAppCreateInfo.applicationVersion	= VK_MAKE_VERSION(1, 0, 0);
	sAppCreateInfo.pEngineName			= "NoEngine";
	sAppCreateInfo.engineVersion		= VK_MAKE_VERSION(1, 0, 0);
	sAppCreateInfo.apiVersion			= VK_API_VERSION_1_1;
	sAppCreateInfo.pNext				= nullptr;
}

void Vulkan::vkSetupInstanceLayers()
{
	vkEnumerateInstanceLayerProperties(&availableInstanceLayersCount, nullptr);
	pAvailableInstanceLayers		= (VkLayerProperties *)malloc(sizeof(VkLayerProperties) * availableInstanceLayersCount);
	ppAvailableInstanceLayersNames	= (const char **)malloc(sizeof(const char *) * availableInstanceLayersCount);
	vkEnumerateInstanceLayerProperties(&availableInstanceLayersCount, pAvailableInstanceLayers);
	for (int i = 0; i < availableInstanceLayersCount; ++i)
	{
		if (vkIsLayerSuitable(pAvailableInstanceLayers[i]))
		{
			ppAvailableInstanceLayersNames[i] = pAvailableInstanceLayers[i].layerName;
			++selectedInstanceLayersCount;
		}
	}
}

void Vulkan::vkSetupInstanceExtensions()
{
	vkEnumerateInstanceExtensionProperties(nullptr, &availableInstanceExtensionsCount, nullptr);
	pAvailableInstanceExtensions		= (VkExtensionProperties *)malloc(sizeof(VkExtensionProperties) * availableInstanceExtensionsCount);
	ppAvailableInstanceExtensionsNames	= (const char **)malloc(sizeof(const char *) * availableDeviceExtensionsCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &availableInstanceExtensionsCount, pAvailableInstanceExtensions);
	for (int i = 0; i < availableInstanceExtensionsCount; ++i)
	{
		if (vkIsExtensionSuitable(pAvailableInstanceExtensions[i]))
		{
			ppAvailableInstanceExtensionsNames[i] = pAvailableInstanceExtensions[i].extensionName;
			++selectedInstanceExtensionsCount;
		}
	}
}

void Vulkan::vkSetupInstanceCreateInfo()
{
	sInstanceCreateInfo.sType						= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	sInstanceCreateInfo.flags						= 0;
	sInstanceCreateInfo.pNext 						= nullptr;
	sInstanceCreateInfo.pApplicationInfo			= &sAppCreateInfo;
	sInstanceCreateInfo.enabledLayerCount			= selectedInstanceLayersCount;
	sInstanceCreateInfo.ppEnabledLayerNames			= ppAvailableInstanceLayersNames;
	sInstanceCreateInfo.enabledExtensionCount		= selectedInstanceExtensionsCount;
	sInstanceCreateInfo.ppEnabledExtensionNames		= ppAvailableInstanceExtensionsNames;
}

void Vulkan::vkCreateInstanceObj()
{
	if ((mError = vkCreateInstance(&sInstanceCreateInfo, nullptr, &instanceObj)) != VK_SUCCESS)
	{
		std::cout << "Error occured: " << mError << std::endl;
		throw std::runtime_error(nullptr);
	}
}

void Vulkan::vkChoosePhysicalDeviceObj()
{
	vkEnumeratePhysicalDevices(instanceObj, &availablePhysicalDeviceCount, nullptr);
	pAvailablePhysicalDevices = (VkPhysicalDevice *)malloc(sizeof(VkPhysicalDevice) * availablePhysicalDeviceCount);
	vkEnumeratePhysicalDevices(instanceObj, &availablePhysicalDeviceCount, pAvailablePhysicalDevices);
	for (int i = 0; i < availablePhysicalDeviceCount; ++i)
	{
		if (vkIsDeviceSuitable(pAvailablePhysicalDevices[i]))
		{
			physicalDeviceObj = pAvailablePhysicalDevices[i];
			break;
		}
	}
	if (physicalDeviceObj == VK_NULL_HANDLE)
		throw std::runtime_error("Failed suit GPU");
}

bool Vulkan::vkIsExtensionSuitable(VkExtensionProperties)
{
	return (true);
}

bool Vulkan::vkIsLayerSuitable(VkLayerProperties)
{
	return (true);
}

bool Vulkan::vkIsDeviceSuitable(VkPhysicalDevice physicalDevice)
{
	vkGetPhysicalDeviceFeatures		(physicalDevice, &msPhysicalDeviceFeatures);
	vkGetPhysicalDeviceProperties	(physicalDevice, &msPhysicalDeviceProperties);
	return msPhysicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;
}

void Vulkan::vkQueryPhysicalDeviceQueue()
{
	bool graphicPresentQueues = 0;

	vkGetPhysicalDeviceQueueFamilyProperties(physicalDeviceObj, &availablePhysicalDeviceQueuesCount, nullptr);
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