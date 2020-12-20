/* PENDING (Lapys) -> Part 05 | Initialize Swapchain */
/* Import */
// : C++ Standard Library
#include <cstdio>
#include <cstdlib>

// : Vulkan
#include <util_init.hpp>

/* Global > ... */
static char const APPLICATION_NAME[] = "Vulkan | Introduction";

/* Main */
int main(void) {
    // Initialization
    // : GPU Count, ...
    std::uint32_t GPUCount = 1u;
    VkResult vulkanPhysicalDevicesEnumerationResult;

    // : Sample Information
    struct sample_info sampleInformation = {};

    // : Vulkan Command ...
    VkResult vulkanCommandBuffersAllocationResult;
    VkResult vulkanCommandPoolCreationResult;

    // : Vulkan Device ...
    VkDevice vulkanDevice;
    VkResult vulkanDeviceCreationResult;

    // : Vulkan Instance ...
    VkInstance vulkanInstance;
    VkResult vulkanInstanceCreationResult;

    // : Vulkan ... Information
    VkApplicationInfo vulkanApplicationInformation = {};
    VkCommandBufferAllocateInfo vulkanCommandBufferAllocationInformation = {};
    VkCommandPoolCreateInfo vulkanCommandPoolInformation = {};
    VkDeviceCreateInfo vulkanDeviceInformation = {};
    VkInstanceCreateInfo vulkanInstanceInformation = {};
    VkDeviceQueueCreateInfo vulkanQueueInformation = {};

    // Update > ...
    init_global_layer_properties(sampleInformation);

    vulkanApplicationInformation.apiVersion = VK_API_VERSION_1_0;
    vulkanApplicationInformation.applicationVersion = 1;
    vulkanApplicationInformation.engineVersion = 1;
    vulkanApplicationInformation.pApplicationName = APPLICATION_NAME;
    vulkanApplicationInformation.pEngineName = APPLICATION_NAME;
    vulkanApplicationInformation.pNext = NULL;
    vulkanApplicationInformation.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;

    vulkanInstanceInformation.enabledExtensionCount = 0;
    vulkanInstanceInformation.enabledLayerCount = 0;
    vulkanInstanceInformation.flags = 0x0;
    vulkanInstanceInformation.pApplicationInfo = &app_info;
    vulkanInstanceInformation.pNext = NULL;
    vulkanInstanceInformation.ppEnabledExtensionNames = NULL;
    vulkanInstanceInformation.ppEnabledLayerNames = NULL;
    vulkanInstanceInformation.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

    // Initiate > Vulkan Instance; ...
    vulkanInstanceCreationResult = vkCreateInstance(&vulkanInstanceInformation, NULL, &vulkanInstance);
    switch (vulkanInstanceCreationResult) {
        case 0: break;
        case VK_ERROR_INCOMPATIBLE_DRIVER: {
            std::fprintf(stderr, "[ERROR]: Unable to find a compatible Vulkan ICD (Installable Client Driver)" "\r\n");
            return std::exit(EXIT_FAILURE), EXIT_FAILURE;
        } break;
        default: {
            std::fprintf(stderr, "[ERROR]: Unknown error with creating Vulkan instance" "\r\n");
            return std::exit(EXIT_FAILURE), EXIT_FAILURE;
        } break;
    }

    // Update > GPU Count
    vulkanPhysicalDevicesEnumerationResult = vkEnumeratePhysicalDevices(sampleInformation.inst, &GPUCount, NULL);
    if (0u == GPUCount) {
        std::fprintf(stderr, "[ERROR]: Unable to infer the number of GPUs available for use" "\r\n");
        return std::exit(EXIT_FAILURE), EXIT_FAILURE;
    }

    else {
        sampleInformation.gpus.resize(GPUCount);
        vulkanPhysicalDevicesEnumerationResult = vkEnumeratePhysicalDevices(sampleInformation.inst, &GPUCount, sampleInformation.gpus.data());;
    }

    if (false == (GPUCount >= 1u && false == vulkanPhysicalDevicesEnumerationResult)) {
        std::fprintf(stderr, "[ERROR]: Unable to enumerate any available GPUs for use" "\r\n");
        return std::exit(EXIT_FAILURE), EXIT_FAILURE;
    }

    // Update > Vulkan Queue Information
    vkGetPhysicalDeviceQueueFamilyProperties(*sampleInformation.gpus, &sampleInformation.queue_family_count, NULL);
    if (sampleInformation.queue_family_count < 1u) {
        std::fprintf(stderr, "[ERROR]: Unable to infer the number of Vulkan device queue families available" "\r\n");
        return std::exit(EXIT_FAILURE), EXIT_FAILURE;
    }

    sampleInformation.queue_props.resize(sampleInformation.queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(*sampleInformation.gpus, &sampleInformation.queue_family_count, sampleInformation.queue_props.data());
    if (sampleInformation.queue_family_count < 1u) {
        std::fprintf(stderr, "[ERROR]: Unable to infer the number of Vulkan device queue families available" "\r\n");
        return std::exit(EXIT_FAILURE), EXIT_FAILURE;
    }

    bool vulkanQueueFamilyFound = false; {
        for (unsigned int iterator = 0u; iterator != sampleInformation.queue_family_count; ++iterator)
        if (sampleInformation.queue_props[iterator].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            vulkanQueueFamilyFound = true;
            vulkanQueueInformation.queueFamilyIndex = iterator;
            break;
        }

        if (false == vulkanQueueFamilyFound) {
            std::fprintf(stderr, "[ERROR]: Could not find required Vulkan queue family" "\r\n");
            return std::exit(EXIT_FAILURE), EXIT_FAILURE;
        }
    }

    // Update > Vulkan (Device, ...)
    float vulkanQueuePriorities[1] = {0.0f}; {
        vulkanDeviceInformation.enabledExtensionCount = 0;
        vulkanDeviceInformation.enabledLayerCount = 0;
        vulkanDeviceInformation.pEnabledFeatures = NULL;
        vulkanDeviceInformation.pNext = NULL;
        vulkanDeviceInformation.ppEnabledExtensionNames = NULL;
        vulkanDeviceInformation.ppEnabledLayerNames = NULL;
        vulkanDeviceInformation.pQueueCreateInfos = &vulkanQueueInformation;
        vulkanDeviceInformation.queueCreateInfoCount = 1;
        vulkanDeviceInformation.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        vulkanQueueInformation.pNext = NULL;
        vulkanQueueInformation.pQueuePriorities = vulkanQueuePriorities;
        vulkanQueueInformation.queueCount = 1;
        vulkanQueueInformation.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;

        vulkanDeviceCreationResult = vkCreateDevice(*sampleInformation.gpus, &vulkanDeviceInformation, NULL, &vulkanDevice);
        if (VK_SUCCESS != vulkanDeviceCreationResult) {
            std::fprintf(stderr, "[ERROR]: Unable to create required Vulkan device" "\r\n");
            return std::exit(EXIT_FAILURE), EXIT_FAILURE;
        }
    }

    // Update > Vulkan Command Pool Information
    vulkanCommandPoolInformation.flags = 0x0;
    vulkanCommandPoolInformation.pNext = NULL;
    vulkanCommandPoolInformation.queueFamilyIndex = sampleInformation.graphics_queue_family_index;
    vulkanCommandPoolInformation.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;

    vulkanCommandPoolCreationResult = vkCreateCommandPool(sampleInformation.device, &vulkanCommandPoolInformation, NULL, &sampleInformation.cmd_pool);
    if (VK_SUCCESS != vulkanCommandPoolCreationResult) {
        std::fprintf(stderr, "[ERROR]: Unable to create Vulkan command pool" "\r\n");
        return std::exit(EXIT_FAILURE), EXIT_FAILURE;
    }

    // Update > Vulkan Command Buffer Allocation Information
    vulkanCommandBufferAllocationInformation.commandBufferCount = 1;
    vulkanCommandBufferAllocationInformation.commandPool = sampleInformation.cmd_pool;
    vulkanCommandBufferAllocationInformation.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    vulkanCommandBufferAllocationInformation.pNext = NULL;
    vulkanCommandBufferAllocationInformation.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;

    vulkanCommandBuffersAllocationResult = vkAllocateCommandBuffers(sampleInformation.device, &vulkanCommandBufferAllocationInformation, &sampleInformation.cmd);
    if (VK_SUCCESS != vulkanCommandBuffersAllocationResult) {
        std::fprintf(stderr, "[ERROR]: Unable to allocate resources for Vulkan command buffers" "\r\n");
        return std::exit(EXIT_FAILURE), EXIT_FAILURE;
    }

    // ...; Deletion > ...
    VkCommandBuffer vulkanCommandBuffers[1] = {sampleInformation.cmd}; {
        vkFreeCommandBuffers(sampleInformation.device, sampleInformation.cmd_pool, 1, vulkanCommandBuffers);
        vkDestroyCommandPool(sampleInformation.device, sampleInformation.cmd_pool, NULL);

        destroy_device(sampleInformation);
        destroy_instance(sampleInformation);
    }

    // Return
    return EXIT_SUCCESS;
}
