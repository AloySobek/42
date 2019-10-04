/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vulkan.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 19:48:49 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/04 20:36:39 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes.cpp"

const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};
#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool eanbleValidationLayers = true;
#endif

class	VulkanTriangle
{
	public:
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
			for (int j = 0; j < glfwExtensionsCount; ++j)
				std::cout << glfwExtensions[j] << std::endl;
			instanceInfo.enabledExtensionCount = glfwExtensionsCount;
			instanceInfo.ppEnabledExtensionNames = glfwExtensions;
			instanceInfo.enabledLayerCount = 0;
			if (vkCreateInstance(&instanceInfo, nullptr, &m_instance) != VK_SUCCESS)
			{
				std::cout << "An error occured\n";
				exit(-1);
			}
			unsigned int extensionsCount;
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);
			std::vector<VkExtensionProperties>extensions(extensionsCount);
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, extensions.data());
			std::cout << "Available extensions:";
			for (int i = 0; i < extensions.size(); ++i)
				std::cout << "\n* " << extensions[i].extensionName << std::endl << extensions[i].specVersion << std::endl;
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
		void checkValidationLayerSupport()
		{
			unsigned int layerCount;
			vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
			std::vector<VkLayerProperties> availableLayers(layerCount);
			vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

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