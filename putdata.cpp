#include <bits/stdc++.h>

using namespace std;

int main(int argc, char ** argv) {
    if (argc < 5) {
        cerr << "Usage: " << argv[0] << " <bytecode_file> <data_file> <output_file> <data_position>" << endl;
        return 1;
    }
    string bcfn  = argv[1],
           datfn = argv[2],
           outfn = argv[3];

    uint64_t datapos = 0;

    {
        stringstream ss;
        ss << argv[4];
        ss >> datapos;
        if (ss.fail()) {
            cerr << "Usage: " << argv[0] << " <bytecode_file> <data_file> <output_file> <data_position>" << endl;
            return 1;
        }
    }

    ifstream bcf(bcfn, ios::binary), datf(datfn, ios::binary);
    ofstream outf(outfn, ios::binary);
    if (!bcf.is_open() || !datf.is_open() || !outf.is_open()) {
        cerr << "Error: unable to open file. (opened files: bc " << bcf.is_open()
             << ", dat " << datf.is_open() << ", out " << outf.is_open() << ")" << endl;
        bcf.close();
        datf.close();
        outf.close();
        return 2;
    }

    outf << "ESMX0001";
    //outf << datapos; // Sounds good, does not work
    // Put bytes forming uint64_t, little endian (0xABCD -> 0xCD, 0xAB)
    for (unsigned int i = 0; i < sizeof(datapos); ++i) {
        outf.put((char) ((datapos & (255LL << 8*i)) >> 8*i));
    }

    bcf.seekg(0, bcf.end);
    uint64_t codeend = bcf.tellg();
    bcf.seekg(0, bcf.beg);

    for (unsigned int i = 0; i < sizeof(codeend); ++i) {
        outf.put((char) ((codeend & (255LL << 8*i)) >> 8*i));
    }
    for (int i = 0; i < 256 - 8 - 8 - 8; ++i) {
        outf.put((char)0);
    }

    outf << bcf.rdbuf();
    outf.seekp(datapos + 256LL);
    outf << datf.rdbuf();

    bcf.close();
    datf.close();
    outf.close();
}
