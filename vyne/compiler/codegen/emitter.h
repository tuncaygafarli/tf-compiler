#ifndef VYNE_EMITTER_H
#define VYNE_EMITTER_H

#include "chunk.h"

class Emitter {
public:
    Chunk* currentChunk;
    int currentLine;

    Emitter(Chunk* chunk) : currentChunk(chunk), currentLine(1) {}

    void emitByte(uint8_t byte) {
        currentChunk->write(byte, currentLine);
    }

    void emitBytes(uint8_t b1, uint8_t b2) {
        emitByte(b1);
        emitByte(b2);
    }

    void emitConstant(Value val) {
        int index = currentChunk->addConstant(val);
        emitBytes(OP_CONSTANT, static_cast<uint8_t>(index));
    }

    void emitReturn() {
        emitByte(OP_RETURN);
    }

    int emitJump(uint8_t instruction){
        emitByte(instruction);
        emitByte(0xff);
        emitByte(0xff);
        return currentChunk->code.size() - 2;
    }

    void emitLoop(int loopStart){
        emitByte(OP_LOOP);

        int offset = currentChunk->code.size() - loopStart + 2;

        if (offset > UINT16_MAX) {
            throw std::runtime_error("Body too bigger!");
        }

        emitByte((offset >> 8) & 0xff);
        emitByte(offset & 0xff);
    }

    void patchJump(int offset) {
        int jumpDistance = currentChunk->code.size() - offset - 2;

        currentChunk->code[offset] = (jumpDistance >> 8) & 0xff;
        currentChunk->code[offset + 1] = jumpDistance & 0xff;
    }
};

#endif