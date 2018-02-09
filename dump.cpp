#include <bits/stdc++.h>
using namespace std;

#define SH4(x) ((x) << 4)

enum opcodes {
    AXC = SH4(0x0), // //
    MOV = SH4(0x1),
    LOA = SH4(0x2),
    STO = SH4(0x3),
    AND = SH4(0x4),
    ORB = SH4(0x5),
    XOR = SH4(0x6),
    ADD = SH4(0x7),
    JMP = SH4(0x8),//
    JGZ = SH4(0x9),
    CMP = SH4(0xA),
    LSH = SH4(0xB),
    PUT = SH4(0xC),//
    GET = SH4(0xD),//
    XRX = SH4(0xE),//
    STP = SH4(0xF) //
};

char rname(int t) {
    return 'A' + t;
}

int main(int argc, char ** argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    ifstream fin(argv[1], ios::binary);
    if (!fin.is_open()) {
        cerr << "Unable to open file " << argv[1] << endl;
        return 1;
    }

    uint64_t datapos = 0, codeend = 0;
    {
        char c[8];
        fin.read(c, 8);
        if (string(c, 8) != "ESMX0001") {
            cerr << "Error: invaild file format" << endl;
            fin.close();
            return 1;
        }

        char _datapos[8];
        fin.read(_datapos, 8);
        for (int i = 0; i < 8; ++i) {
            datapos |= uint64_t(_datapos[i]) << (8 * i);
        }

        char _codeend[8];
        fin.read(_codeend, 8);
        for (int i = 0; i < 8; ++i) {
            codeend |= uint64_t(_codeend[i]) << (8 * i);
        }
        cout << "# Data located at " << datapos << endl;
        cout << "# Code ends at " << codeend << endl;
        fin.seekg(256);
    }

    while (fin.good()) {
        if (codeend != 0 && size_t(fin.tellg()) - 256 >= codeend) {
            cout << "# <code ends>" << endl;
            break;
        }
        int ch;
        ch = fin.get();
        if (ch != (ch & 0xff)) {
            return 42;
        }

        int opcode = ch & 0xf0;
        switch (opcode) {
        case AXC:
        {
            cout << "axc ";
            int t = ch & 0x0f;
            cout << ((t & 0b1000) >> 3);
            cout << ((t & 0b100) >> 2);
            cout << ((t & 0b10) >> 1);
            cout << ((t & 0b1) >> 0);
            cout << endl;
            break;
        }
        case MOV:
            cout << "mov " << rname((ch & 0b1100) >> 2) << " " << rname(ch & 0b11) << endl;
            break;
        case LOA:
            cout << "loa " << rname((ch & 0b1100) >> 2) << " " << rname(ch & 0b11) << endl;
            break;
        case STO:
            cout << "sto " << rname((ch & 0b1100) >> 2) << " " << rname(ch & 0b11) << endl;
            break;
        case AND:
            cout << "and " << rname((ch & 0b1100) >> 2) << " " << rname(ch & 0b11) << endl;
            break;
        case ORB:
            cout << "orb " << rname((ch & 0b1100) >> 2) << " " << rname(ch & 0b11) << endl;
            break;
        case XOR:
            cout << "xor " << rname((ch & 0b1100) >> 2) << " " << rname(ch & 0b11) << endl;
            break;
        case ADD:
            cout << "add " << rname((ch & 0b1100) >> 2) << " " << rname(ch & 0b11) << endl;
            break;
        case JGZ:
            cout << "jgz " << rname((ch & 0b1100) >> 2) << " " << rname(ch & 0b11) << endl;
            break;
        case CMP:
            cout << "cmp " << rname((ch & 0b1100) >> 2) << " " << rname(ch & 0b11) << endl;
            break;
        case LSH:
            cout << "lsh " << rname((ch & 0b1100) >> 2) << " " << rname(ch & 0b11) << endl;
            break;
        case JMP:
            cout << "jmp   " << rname(ch & 0b11) << endl;
            break;
        case PUT:
            cout << "put " << rname((ch & 0b1100) >> 2) << endl;
            break;
        case GET:
            cout << "get " << rname((ch & 0b1100) >> 2) << endl;
            break;
        case XRX:
            cout << "xrx " << rname((ch & 0b1100) >> 2) << endl;
            break;
        case STP:
            cout << "stp " << rname((ch & 0b1100) >> 2) << endl;
            break;

        default:
            cout << "???" << endl;
            break;
        }
    }
}
