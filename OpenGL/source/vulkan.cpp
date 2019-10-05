/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vulkan.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 19:48:49 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/05 20:27:19 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes.cpp"

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool eanbleValidationLayers = true;
#endif

class	VulkanTriangle
{
	public:
		const char *m_layer = "VK_LAYER_KHRONOS_validation";
		int		m_width;
		int		m_height;

		VulkanTriangle(): m_width(1920), m_height(1080) { }

		void run()
		{
			initWindow();
			initVulkan();
			mainLoop();
			clenUp();
		}
	private:
		VkInstance	m_instance;
		GLFWwindow	*m_window;

		const char **checkValidationLayerSupport(u_int32_t layerCount)
		{
			std::vector<VkLayerProperties>availableLayers(layerCount);
			vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
			for (int i = 0; i < availableLayers.size(); ++i)
			{
				std::cout << availableLayers[i].layerName << std::endl;
				if (strcmp(m_layer, availableLayers[i].layerName) == 0)
					return (const char **)&availableLayers[i].layerName;
			}
			std::cout << "Requesting layer hasn't been found\n";
			return &m_layer;
		}

		int	enumareteLayers()
		{
			u_int32_t	layerCount = 0;

			vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
			return (layerCount);
		}

		void enumerateExtensions()
		{
			unsigned int extensionsCount;
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);
			std::vector<VkExtensionProperties>extensions(extensionsCount);
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, extensions.data());
			std::cout << "Available extensions:";
			for (int i = 0; i < extensions.size(); ++i)
				std::cout << "\n* " << extensions[i].extensionName << std::endl << extensions[i].specVersion << std::endl;
		}

		void createInstance()
		{
			VkApplicationInfo appInfo = {};
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pApplicationName = "Hello triangle";
			appInfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.pEngineName = "No engine";
			appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.apiVersion = VK_API_VERSION_1_0;
			appInfo.pNext = nullptr;

			VkInstanceCreateInfo instanceInfo = {};
			instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			instanceInfo.pApplicationInfo = &appInfo;
			unsigned int glfwExtensionsCount;
			const char **glfwExtensions;
			glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);
			instanceInfo.enabledExtensionCount		= glfwExtensionsCount;
			instanceInfo.enabledLayerCount			= enumareteLayers();
			instanceInfo.ppEnabledExtensionNames 	= glfwExtensions;
			if ((instanceInfo.ppEnabledLayerNames = checkValidationLayerSupport(instanceInfo.enabledLayerCount)))
				;
			else
				instanceInfo.enabledLayerCount = 0;
			if (vkCreateInstance(&instanceInfo, nullptr, &m_instance) != VK_SUCCESS)
			{
				std::cout << "An error occured\n";
				exit(-1);
			}
		}

		void initWindow()
		{
			glfwInit();
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			m_window = glfwCreateWindow(m_width, m_height, "Vulkan", nullptr, nullptr);
		}

		void initVulkan()
		{
			createInstance();
		}

		void mainLoop()
		{
			while (!glfwWindowShouldClose(m_window))
				glfwPollEvents();
		}

		void clenUp()
		{
			vkDestroyInstance(m_instance, nullptr);
			glfwDestroyWindow(m_window);
			glfwTerminate();
		}
};

int			main(int argc, char **argv)
{
	VulkanTriangle	app;

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