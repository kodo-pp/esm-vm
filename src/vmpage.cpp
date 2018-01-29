#include <esm/vmpage.hpp>
#include <vector>
#include <exception>
#include <stdexcept>

using namespace std;

Page::Page() {
    bytes.resize(pageSize, 0);
}

Page::~Page() {
    bytes.clear();
}

uint8_t Page::readByte(size_t offset) {
    if (offset >= pageSize) {
        throw std::out_of_range("page byte read failed");
    }

    return bytes.at(offset);
}

void Page::writeByte(size_t offset, uint8_t byte) {
    if (offset >= pageSize) {
        throw std::out_of_range("page byte write failed");
    }

    bytes.at(offset) = byte;
}
