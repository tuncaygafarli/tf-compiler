#include "chunk.h"
#include <iostream>
#include <cstdio>

/**
 * Disassembles a single instruction at a given offset.
 * Returns the offset of the NEXT instruction.
 */
int disassembleInstruction(const Chunk& chunk, int offset) {
    std::printf("%04d ", offset);

    uint8_t instruction = chunk.code[offset];
    switch (instruction) {
        case OP_ADD:      std::printf("OP_ADD\n");      return offset + 1;
        case OP_SUBTRACT: std::printf("OP_SUBTRACT\n"); return offset + 1;
        case OP_MULTIPLY: std::printf("OP_MULTIPLY\n"); return offset + 1;
        case OP_DIVIDE:   std::printf("OP_DIVIDE\n");   return offset + 1;
        case OP_RETURN:   std::printf("OP_RETURN\n");   return offset + 1;
        case OP_EQUAL:    std::printf("OP_EQUAL\n");    return offset + 1;
        case OP_GREATER:  std::printf("OP_GREATER\n");  return offset + 1;
        case OP_SMALLER:  std::printf("OP_SMALLER\n");  return offset + 1;
        case OP_POP:      std::printf("OP_POP\n");      return offset + 1;
        case OP_PRINT:    std::printf("OP_PRINT\n");    return offset + 1;
        case OP_TYPE:     std::printf("OP_TYPE\n");     return offset + 1;

        case OP_CONSTANT:
        case OP_DEFINE_GLOBAL:
        case OP_GET_GLOBAL: {
            const char* name;
            if (instruction == OP_CONSTANT) name = "OP_CONSTANT";
            else if (instruction == OP_DEFINE_GLOBAL) name = "OP_DEFINE_GLOBAL";
            else name = "OP_GET_GLOBAL";

            uint8_t constantIndex = chunk.code[offset + 1];
            std::printf("%-16s %4d '", name, constantIndex);
            chunk.constants[constantIndex].print(std::cout);
            std::printf("'\n");
            return offset + 2;
        }

        case OP_JUMP:
        case OP_JUMP_IF_FALSE: {
            const char* name = (instruction == OP_JUMP) ? "OP_JUMP" : "OP_JUMP_IF_FALSE";
            
            uint8_t hi = chunk.code[offset + 1];
            uint8_t lo = chunk.code[offset + 2];
            uint16_t jumpOffset = (uint16_t)((hi << 8) | lo);

            int target = offset + 3 + jumpOffset;
            std::printf("%-16s %4d -> %04d\n", name, offset, target);
            return offset + 3;
        }

        case OP_ARRAY: {
            uint8_t count = chunk.code[offset + 1];
            std::printf("%-16s %4d\n", "OP_ARRAY", count);
            return offset + 2;
        }
        case OP_LOOP: {
            uint8_t hi = chunk.code[offset + 1];
            uint8_t lo = chunk.code[offset + 2];
            uint16_t jumpOffset = (uint16_t)((hi << 8) | lo);

            int target = offset + 3 - jumpOffset;
            std::printf("%-16s %4d -> %04d\n", "OP_LOOP", offset, target);
            return offset + 3;
        }

        default:
            std::printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}

/**
 * Disassembles an entire chunk of bytecode.
 */
void disassembleChunk(const Chunk& chunk, const std::string& name) {
    std::cout << "== " << name << " ==" << std::endl;

    for (int offset = 0; offset < (int)chunk.code.size(); ) {
        offset = disassembleInstruction(chunk, offset);
    }
}