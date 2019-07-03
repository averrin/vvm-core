#ifndef __DEVICE_H_
#define __DEVICE_H_

#include <map>
#include <memory>
#include <functional>
#include "vvm/memory_container.hpp"

typedef std::function<void()> dt_handler;

class Device {
public:
    Device(std::byte id) : deviceId(id) {}
    Device(std::byte id, std::shared_ptr<MemoryContainer> m) : deviceId(id), memory(m) {}
    virtual ~Device() = default;
    std::shared_ptr<MemoryContainer> memory;
	virtual void tickHandler() = 0;
	std::map<const std::byte, dt_handler> intHandlers;
    std::string deviceName;
    std::byte deviceId;
};

#endif // __DEVICE_H_
