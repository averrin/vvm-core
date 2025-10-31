#ifndef __MEMORY_H_
#define __MEMORY_H_


#include "vvm/device.hpp"

class MemoryDevice : public Device {
public:
    MemoryDevice(std::byte id, unsigned int s) : Device(id, std::make_shared<MemoryContainer>(s)) { deviceName = "Memory"; }
	void tickHandler() {};
};

#endif // __MEMORY_H_
