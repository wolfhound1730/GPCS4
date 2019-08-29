#include "GveSwapChain.h"
#include <algorithm>

namespace gve
{;

GveSwapChain::GveSwapChain(RcPtr<GvePhysicalDevice>& phyDevice,
	RcPtr<GveDevice>& logicDevice,
	std::shared_ptr<sce::SceVideoOut>& videoOut) :
	m_swapchain(VK_NULL_HANDLE),
	m_phyDevice(phyDevice),
	m_logicalDevice(logicDevice),
	m_videoOut(videoOut)
{
	createSwapChain();
}

GveSwapChain::~GveSwapChain()
{
	vkDestroySwapchainKHR(*m_logicalDevice, m_swapchain, nullptr);
}


void GveSwapChain::createSwapChain()
{
	do 
	{
		SwapChainSupportDetails swapChainSupport = querySwapChainSupport();

		VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
		VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
		VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
		{
			imageCount = swapChainSupport.capabilities.maxImageCount;
		}

		GveInstance* instance = m_phyDevice->getInstance();
		VkDevice device = *m_logicalDevice;
		VkSurfaceKHR surface = m_videoOut->getSurface(*instance);

		VkSwapchainCreateInfoKHR createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = surface;

		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		QueueFamilyIndices indices = m_phyDevice->getSuitableQueueIndices(surface);
		uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

		if (indices.graphicsFamily != indices.presentFamily)
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else 
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		}

		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;

		if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &m_swapchain) != VK_SUCCESS)
		{
			LOG_ERR("failed to create swap chain!");
			break;
		}

		vkGetSwapchainImagesKHR(device, m_swapchain, &imageCount, nullptr);
		m_swapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(device, m_swapchain, &imageCount, m_swapChainImages.data());

		m_swapChainImageFormat = surfaceFormat.format;
		m_swapChainExtent = extent;
	} while (false);
}

SwapChainSupportDetails GveSwapChain::querySwapChainSupport()
{
	SwapChainSupportDetails details;

	do 
	{
		GveInstance* instance = m_phyDevice->getInstance();
		VkPhysicalDevice device = *m_phyDevice;
		VkSurfaceKHR surface = m_videoOut->getSurface(*instance);

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

		if (formatCount == 0)
		{
			break;
		}
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

		if (presentModeCount == 0)
		{
			break;
		}
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());

	} while (false);



	return details;
}

VkSurfaceFormatKHR GveSwapChain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
	bool foundBest = false;
	VkSurfaceFormatKHR format;

	for (const auto& availableFormat : availableFormats) 
	{
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM &&
			availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) 
		{
			format = availableFormat;
			foundBest = true;
			break;
		}
	}

	if (!foundBest)
	{
		format = availableFormats[0];
	}

	return format;
}

VkPresentModeKHR GveSwapChain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
{
	VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;

	for (const auto& availablePresentMode : availablePresentModes) 
	{
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) 
		{
			bestMode = availablePresentMode;
			break;
		}
		else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) 
		{
			bestMode = availablePresentMode;
		}
	}

	return bestMode;
}

VkExtent2D GveSwapChain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
{
	VkExtent2D extend = {};
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) 
	{
		extend = capabilities.currentExtent;
	}
	else 
	{
		uint32_t width = 0, height = 0;
		m_videoOut->getFramebufferSize(width, height);

		VkExtent2D actualExtent = { width,height };

		actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
		actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

		extend = actualExtent;
	}
	return extend;
}

}  // namespace gve