#include <bits/stdc++.h>

using namespace std;

#define SH4(x) ((x) << 4)

#define rr(x) do { \
    fin >> x; \
    if (x != "A" && x != "B" && x != "C" && x != "D" && x != "a" && x != "b" && x != "c" && x != "d") { \
        cerr << "Syntax error: invalid register name: " << x << endl; \
        return 2; \
    } \
} while (false)

#define rn(x,y) do { \
    if (x == "A") y = 0; \
    else if (x == "B") y = 1; \
    else if (x == "C") y = 2; \
    else if (x == "D") y = 3; \
    else if (x == "a") y = 0; \
    else if (x == "b") y = 1; \
    else if (x == "c") y = 2; \
    else if (x == "d") y = 3; \
    else { \
        cerr << "Syntax error: invalid register name: " << x << endl; \
        return 2; \
    } \
} while(false)

enum opcodes {
    AXC = SH4(0x0),
    MOV = SH4(0x1),
    LOA = SH4(0x2),
    STO = SH4(0x3),
    AND = SH4(0x4),
    ORB = SH4(0x5),
    XOR = SH4(0x6),
    ADD = SH4(0x7),
    JMP = SH4(0x8),
    JGZ = SH4(0x9),
    CMP = SH4(0xA),
    LSH = SH4(0xB),
    PUT = SH4(0xC),
    GET = SH4(0xD),
    XRX = SH4(0xE),
    STP = SH4(0xF)
};

int main(int argc, char ** argv) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input> <output>" << endl;
        return 1;
    }
    string inn(argv[1]), outn(argv[2]);
    ifstream fin(inn);
    if (!fin.is_open()) {
        cerr << "Error: unable to open file '" << inn << "' for reading" << endl;
        return 1;
    }
    ofstream fout(outn, ios::binary);
    if (!fout.is_open()) {
        cerr << "Error: unable to open file '" << outn << "' for writing" << endl;
        fin.close();
        return 1;
    }

    while (fin.good()) {
        string opcode;
        fin >> opcode;
        char byte = 0;
        if (opcode == "#") {
            string _;
            getline(fin, _);
            continue;
        } else if (opcode == "axc") {
            byte |= AXC;
            string cn;
            fin >> cn;
            if (cn.length() != 4) {
                cerr << "Syntax error: invalid constant format for AXC: " << cn << endl;
                fin.close();
                fout.close();
                return 2;
            }
            for (int i = 0; i < 4; ++i) {
                if (cn[i] != '0' && cn[i] != '1') {
                    cerr << "Syntax error: invalid constant format for AXC: " << cn << endl;
                    fin.close();
                    fout.close();
                    return 2;
                }
            }
            byte |= (cn[0] - '0') << 3;
            byte |= (cn[1] - '0') << 2;
            byte |= (cn[2] - '0') << 1;
            byte |= (cn[3] - '0') << 0;
        } else if (opcode == "mov") {
            byte |= MOV;
            string to, from;
            rr(to);
            rr(from);
            int tn, fn;
            rn(to, tn);
            rn(from, fn);
            byte |= tn << 2;
            byte |= fn;
        } else if (opcode == "loa") {
            byte |= LOA;
            string to, from;
            rr(to);
            rr(from);
            int tn, fn;
            rn(to, tn);
            rn(from, fn);
            byte |= tn << 2;
            byte |= fn;
        } else if (opcode == "sto") {
            byte |= STO;
            string to, from;
            rr(to);
            rr(from);
            int tn, fn;
            rn(to, tn);
            rn(from, fn);
            byte |= tn << 2;
            byte |= fn;
        } else if (opcode == "and") {
            byte |= AND;
            string to, from;
            rr(to);
            rr(from);
            int tn, fn;
            rn(to, tn);
            rn(from, fn);
            byte |= tn << 2;
            byte |= fn;
        } else if (opcode == "orb") {
            byte |= ORB;
            string to, from;
            rr(to);
            rr(from);
            int tn, fn;
            rn(to, tn);
            rn(from, fn);
            byte |= tn << 2;
            byte |= fn;
        } else if (opcode == "xor") {
            byte |= XOR;
            string to, from;
            rr(to);
            rr(from);
            int tn, fn;
            rn(to, tn);
            rn(from, fn);
            byte |= tn << 2;
            byte |= fn;
        } else if (opcode == "add") {
            byte |= ADD;
            string to, from;
            rr(to);
            rr(from);
            int tn, fn;
            rn(to, tn);
            rn(from, fn);
            byte |= tn << 2;
            byte |= fn;
        } else if (opcode == "jmp") {
            byte |= JMP;
            string to;
            rr(to);
            int tn;
            rn(to, tn);
            byte |= tn;
        } else if (opcode == "jgz") {
            byte |= JGZ;
            string to, from;
            rr(to);
            rr(from);
            int tn, fn;
            rn(to, tn);
            rn(from, fn);
            byte |= tn << 2;
            byte |= fn;
        } else if (opcode == "cmp") {
            byte |= CMP;
            string to, from;
            rr(to);
            rr(from);
            int tn, fn;
            rn(to, tn);
            rn(from, fn);
            byte |= tn << 2;
            byte |= fn;
        } else if (opcode == "lsh") {
            byte |= LSH;
            string to, from;
            rr(to);
            rr(from);
            int tn, fn;
            rn(to, tn);
            rn(from, fn);
            byte |= tn << 2;
            byte |= fn;
        } else if (opcode == "put") {
            byte |= PUT;
            string r;
            rr(r);
            int rnn;
            rn(r, rnn);
            byte |= rnn << 2;
        } else if (opcode == "get") {
            byte |= GET;
            string r;
            rr(r);
            int rnn;
            rn(r, rnn);
            byte |= rnn << 2;
        } else if (opcode == "xrx") {
            byte |= XRX;
            string r;
            rr(r);
            int rnn;
            rn(r, rnn);
            byte |= rnn << 2;
        } else if (opcode == "stp") {
            byte |= STP;
            string r;
            rr(r);
            int rnn;
            rn(r, rnn);
            byte |= rnn << 2;
        } else if (!fin.good()) {
            break;
        } else {
            cerr << "Syntax error: invalid opcode: " << opcode << endl;
            return 2;
        }
        fout << byte;
    }
}
