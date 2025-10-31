#include <iostream>
#include <memory>
#include "vvm/core.hpp"
#include "vvm/analyzer.hpp"
#include "vvm/devices/memory.hpp"
#include "vvm/devices/rng.hpp"

// Simple output handler
std::string output;

void tickHandler(MemoryContainer mem, unsigned int pointer) {
    // Called on each VM tick
}

int main(int argc, char* argv[]) {
    try {
        std::cout << "VVM Core Test Program\n";
        std::cout << "=====================\n\n";

        // Create core with tick handler
        std::cout << "Creating Core...\n";
        auto core = std::make_shared<Core>(tickHandler);
        std::cout << "Core created successfully!\n";

        // Initialize memory layout so devices can be added before compilation
        core->init(4096);

    // Set up interrupt handler for INT_PRINT (0x21)
    core->setInterruptHandler(INT_PRINT, [](MemoryContainer mem, unsigned int pointer) {
        (void)pointer;
        std::byte ch = mem.readByte(AL);
        std::cout << "Output: " << static_cast<char>(ch) << std::endl;
        output += static_cast<char>(ch);
    });
    std::cout << "Interrupt handler for INT_PRINT set up successfully!\n";

    // Set up interrupt handler for INT_END (0xFF)
    core->setInterruptHandler(INT_END, [](MemoryContainer mem, unsigned int pointer) {
        std::cout << "Program ended successfully!" << std::endl;
    });
    std::cout << "Interrupt handler for INT_END set up successfully!\n";
    // Add some memory devices
    auto memory_device = std::make_shared<MemoryDevice>(std::byte{0x01}, 1024);
    std::cout << "Memory device created successfully!\n";
    core->addDevice(memory_device);

    std::cout << "Core initialized successfully!\n";
    std::cout << "Memory devices added\n\n";

    // Test RNG device
    std::cout << "Test RNG Device\n";
    std::cout << "-----------------\n";
    auto rng_device = std::make_shared<RngDevice>(std::byte{0x02}, 16, 10, 20);
    core->addDevice(rng_device);
    rng_device->tickHandler();
    bool rng_ok = true;
    std::cout << "RNG bytes: ";
    for (unsigned int i = 0; i < 8; ++i) {
        auto b = rng_device->memory->readByte(address{i});
        auto v = static_cast<unsigned int>(b);
        std::cout << v << (i < 7 ? ' ' : '\n');
        if (!(v >= 10 && v < 20)) rng_ok = false;
    }
    std::cout << (rng_ok ? "RNG range check: OK\n\n" : "RNG range check: FAIL\n\n");

    // Test 1: Simple register operations
    std::cout << "Test 1: Register Operations\n";
    std::cout << "----------------------------\n";

    // Set EAX register to 42
    core->setReg(EAX, 42);
    std::cout << "Set EAX = 42\n";

    // Read back EAX
    int eax_value = core->readRegInt(EAX);
    std::cout << "Read EAX = " << eax_value << "\n\n";

    // Test 2: Parse and compile a simple assembly program if provided
    if (argc > 1) {
        std::cout << "Test 2: Parsing and executing program from file\n";
        std::cout << "------------------------------------------------\n";
        std::string filename = argv[1];
        std::cout << "Loading file: " << filename << "\n";

        try {
            analyzer::Analyzer analyzer;
            auto script = analyzer.parseFile(filename);

            std::cout << "Parsed " << script.size() << " instructions\n";

            // Compile the script
            core->compile(script);
            std::cout << "Compilation successful!\n";

            // Execute the code
            std::cout << "Executing...\n\n";
            core->execCode(std::vector<address>{});

            std::cout << "\nExecution complete!\n";

            // Read final register values
            std::cout << "\nFinal Register Values:\n";
            std::cout << "EAX = " << core->readRegInt(EAX) << "\n";
            std::cout << "EBX = " << core->readRegInt(EBX) << "\n";
            std::cout << "ECX = " << core->readRegInt(ECX) << "\n";

        } catch (const std::exception& e) {
            std::cout << "Error: " << std::endl;
            std::cout << "Error: " << e.what() << std::endl;
            return 1;
        }
    } else {
        std::cout << "Test 2: Manual instruction execution\n";
        std::cout << "-------------------------------------\n";
        std::cout << "Note: Provide an assembly file as argument to parse and execute it\n";
        std::cout << "Usage: " << argv[0] << " <file.asm>\n\n";
    }

    // Test 3: Check register states
    std::cout << "Test 3: Register States\n";
    std::cout << "------------------------\n";
    std::cout << "EAX = " << core->readRegInt(EAX) << "\n";
    std::cout << "EBX = " << core->readRegInt(EBX) << "\n";
    std::cout << "ECX = " << core->readRegInt(ECX) << "\n";

        std::cout << "\n======================\n";
        std::cout << "All tests completed!\n";

        return 0;
    } catch (const std::exception& e) {
        std::cout  << "Fatal error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Fatal error: Unknown exception" << std::endl;
        return 1;
    }
}
