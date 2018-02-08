#include <iostream>
#include <fstream>
#include <vector>
#include <esm/vmpage.hpp>

using namespace std;

PageTable pageTable(0);

void handleInstuction(uint8_t instruction, size_t & instrPtr);
void recursive_death();

int64_t regs[5]; // A, B, C, D, X - all 64-bit

int main(int argc, char ** argv) {
    // Minimal argument parsing
    // TODO: add some options and flags, '--help' at least
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    string filename(argv[1]);

    // Open file with bytecode
    ifstream fin(filename, ios::binary);

    // Handle different errors
    if (!fin.is_open()) {
        cerr << "Error: unable to open file '" << filename << "'" << endl;
        return 2;
    }

    if (!fin.good()) {
        cerr << "Error: unable to read from file" << endl;
        fin.close();
        return 3;
    }

    // Read all code to memory table
    // TODO: add buffers, not just byte-by-byte reading and writing
    // NOTE: it's a separate block to reduce some local variables' lifetime
    {
        register size_t i = 0;
        register char c;
        while (fin.good()) {
            c = fin.get();
            // If we don't do that, an EOF (-1) will be written additionally
            // (and that's not what we want)
            if (!fin.good()) {
                break;
            }
            pageTable.writeByte(i, static_cast <uint8_t> (c));
            ++i;
        }
    }

    // And, finally, instruction parsing
    // NOTE: again, separate block
    {
        size_t instrPtr = 0; // pointer to instruction
        register uint8_t instruction; // the instruction itself
        while (true) {
            instruction = pageTable.readByte(instrPtr);
            handleInstuction(instruction, instrPtr);
            ++instrPtr;
        }
    }
}

void handleInstuction(uint8_t instruction, size_t & instrPtr) {
    // Quite a naïve method. Is to be replaced by switch-case all 256 possible values (yay, jump table!)
    uint8_t  opcode   = (instruction & 0b11110000) >> 4;
    uint8_t  reg1no   = (instruction & 0b00001100) >> 2;
    uint8_t  reg2no   = (instruction & 0b00000011);
    int64_t  constVal = (instruction & 0b00001111); // Yes, it *is* 64-bit,
                                                    // since virtual registers are 64-bit
    int64_t * reg1 = regs + reg1no;
    int64_t * reg2 = regs + reg2no;
    int64_t * regA = regs + 0;
    int64_t * regX = regs + 4;

    switch (opcode) {
    case 0x0: // AXC
        *regA <<= 4;
        *regA |= constVal;
        break;
    case 0x1: // MOV
        *reg1 = *reg2;
        break;
    case 0x2: // LOA
        *reg1 &= ~(0xFFll); // 11111...11100000000 (8 zeros at the end)
                            // (just zero the lowest byte)
        *reg1 |= pageTable.readByte(*reg2);
        break;
    case 0x3: // STO
        pageTable.writeByte(*reg2, static_cast <uint8_t> (*reg1 & 0xFFll));
        break;
    case 0x4: // AND
        *reg1 &= *reg2;
        break;
    case 0x5: // ORB
        *reg1 |= *reg2;
        break;
    case 0x6: // XOR
        *reg1 ^= *reg2;
        break;
    case 0x7: // ADD
        *reg1 += *reg2;
        break;
    case 0x8: // JMP
        instrPtr = *reg2 - 1; // -1 because instrPtr will be incremented in main()
        break;
    case 0x9: // JGZ
        if (*reg1 > 0) {
            instrPtr = *reg2 - 1;
        }
        break;
    case 0xA: // CMP
        if (*reg1 == *reg2) {
            *reg1 = 0;
        } else if (*reg1 > *reg2) {
            *reg1 = 2;
        } else { // *reg1 < *reg2
            *reg1 = 1;
        }
        break;
    case 0xB: // LSH
        *reg1 <<= (*reg2 & 0b111111); // Low 6 bits, no larger than 63 (equiv to ... % 64)
        break;
    case 0xC: // PUT
        cout << (static_cast <char> (*reg1 & 0xFFll));
        break;
    case 0xD: // GET
        *reg1 &= ~(0xFFll);
        *reg1 |= cin.get();
        break;
    case 0xE: // XRX
        {
            decltype (*reg1) T = *reg1;
            *reg1 = *regX;
            *regX = T;
            break;
        }
    case 0xF: // STP
        exit(static_cast <int> (*reg1 & 0xFFFFFFFFll));
        break;
    default:
        cerr << "Something impossible happened and 4-bit value is not in range [0; 16)." << endl;
        cerr << "You should probably test your memor@E<A\x71\x94(??W{:g@6";
        ((void (*)(void))(0))();

        // If that didn't segfault, then what?
        volatile auto _ = *(int*)(nullptr);

        // What are we running on if execution continues?
        recursive_death();

        // OK, I give up
        // Just a segfault simulator
        cerr << "Segmentation fault" << endl;
        exit(139);

        // WAT?
        while (true) {
            do {
                for (;;) {
                    terminate();
                }
            } while (true);
        }
    }
}

void recursive_death() {
    while (true) {
        recursive_death();
    }
}
