#pragma once
#ifndef CONTAINER_HPP_
#define CONTAINER_HPP_
#include <array>
#include <string>
#include <variant>
#include <optional>
#include <map>
#include <functional>
#include <cstddef>
#include "format.h"
#include "vvm/address.hpp"
#include "vvm/memory_container.hpp"
#include "vvm/constants.hpp"
#include "vvm/specs.hpp"
#include "vvm/code_instruction.hpp"
#include "vvm/device.hpp"
#include "ostream.hpp"
#include "rang.hpp"

typedef std::function<void(MemoryContainer, unsigned int)> t_handler;
typedef std::function<bool(op_spec)> predicate;


class Core {
private:
	void writeHeader();

	t_handler _tickHandler;
	std::map<const std::byte, t_handler> _intHandlers;

	void checkInterruption();
	void printCode(const std::string_view code, const address arg1, unsigned int arg2);
	void printCode(const std::string_view code, const address arg1);
	void printCode(const std::string_view code, const address arg1, const address arg2);
	void printCode(const std::string_view code, const address arg1, const std::byte arg2);
	// void printCode(const std::string_view code, const address arg2);
	void printCode(const std::string_view code, std::byte arg2);
	void printCode(const std::string_view code, const int arg1);
	void printCode(const std::string_view code);
	void printJump(const std::string_view code, const address arg1, bool jumped);
	void printJump(const std::string_view code, const int offset, bool jumped);
	void printIRQ(const std::byte code);

	void writeByte(std::byte ch);
	void writeByte(instruction_arg ch);
	void writeAddress(const address n);
	void writeAddress(const instruction_arg n);
	void writeInt(int n);
	void writeInt(instruction_arg n);

	address writeCode(const std::byte opcode, address arg1, unsigned int arg2);
	address writeCode(const std::byte opcode, address arg1, address arg2);
	address writeCode(const std::byte opcode, address arg1, const std::byte arg2);
	address writeCode(const std::byte opcode, address arg1);
	address writeCode(const std::byte opcode, const std::byte arg1);
	address writeCode(const std::byte opcode, const int arg1);
	address writeCode(const std::byte opcode);

	static const std::byte version{ 0x01 };
	address code_offset;

	address SUB_aa_func(address _pointer);
	address SUB_ai_func(address _pointer);
	address SUB_aw_func(address _pointer);
	address ADD_aa_func(address _pointer);
	address ADD_ai_func(address _pointer);
	address ADD_aw_func(address _pointer);
	address MOV_aa_func(address _pointer);
	address MOV_ai_func(address _pointer);
	address MOV_aw_func(address _pointer);
	address OUT_func(address _pointer);
	address CMP_aa_func(address _pointer);
	address CMP_ai_func(address _pointer);
	address CMP_aw_func(address _pointer);
	address JNE_a_func(address _pointer);
	address JNE_r_func(address _pointer);
	address JE_func(address _pointer);
	address INT_func(address _pointer);
	address INC_func(address _pointer);
	address DEC_func(address _pointer);
	address NOP_func(address _pointer);
	address PUSH_a_func(address _pointer);
	address PUSH_i_func(address _pointer);
	address PUSH_w_func(address _pointer);
	address POP_func(address _pointer);
	address JMP_a_func(address _pointer);
	address JMP_r_func(address _pointer);
	address MEM_func(address _pointer);

	address CALL_func(address _pointer);
	address RET_func(address _pointer);

    MemoryContainer* getMem();

public:
	Core(t_handler th);
	op_spec::OP_TYPE next_spec_type;

    std::unique_ptr<MemoryContainer> meta;
    std::unique_ptr<MemoryContainer> code;
    std::unique_ptr<MemoryContainer> d_table;
    std::unique_ptr<MemoryContainer> stack;
    std::vector<std::shared_ptr<MemoryContainer>> memory;
	std::vector<std::shared_ptr<Device>> devices;

    static std::optional<op_spec> getSpec(predicate);
    static std::optional<address> isReservedMem(std::string arg);

    void compile(analyzer::script script);
	address execStart();

	address readRegAddress(const address reg);
	int readRegInt(const address reg);
	std::byte readRegByte(const address reg);

	std::byte getState();
	void setState(const std::byte state);
	bool checkFlag(const std::byte intf);
	void setFlag(const std::byte flag, const bool value);
	void setReg(const address reg, const address value);
	void setReg(const address reg, const int value);

	std::byte readByte();
	address readAddress();
    static unsigned int readInt(MemoryContainer, const unsigned int pointer);
	unsigned int readInt();
	int readSignedInt();

    arguments readArgs(address _pointer,op_spec::OP_TYPE opType, bool reread_first=false, bool reread_second=false);
	address execCode(std::vector<address>);
	address execCode(address local_pointer, std::vector<address>);
	address execStep(address local_pointer);
	address mapMem(std::shared_ptr<MemoryContainer> mem);
	address addDevice(std::shared_ptr<Device> device);
	void seek(address addr);
	void seek(instruction_arg addr);
	void dumpState();
	void setInterruptHandler(const std::byte interrupt, t_handler handler);
	void saveBytes(const std::string_view name);
    unsigned int getSize();

	address pointer;
};

#endif

