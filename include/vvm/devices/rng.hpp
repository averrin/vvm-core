#ifndef __RNG_H_
#define __RNG_H_

#include "vvm/device.hpp"

class RngDevice : public Device {
public:
    RngDevice(std::byte id, unsigned int s, unsigned int _min, unsigned int _max)
        : Device(id, std::make_shared<MemoryContainer>(s)),
        min(_min), max(_max){}
    std::string deviceName = "Random generator";
	void tickHandler() {
        for (auto i = 0; i < memory->size; i++) {
            memory->writeByte(address{i}, std::byte{rand()%(max-min)+min});
        }
    }
    unsigned int min;
    unsigned int max;
};


#endif // __RNG_H_
