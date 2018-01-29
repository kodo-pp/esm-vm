#include <iostream>
#include <vector>
#include <esm/vmpage.hpp>

using namespace std;

int main() {
    PageTable pageTable(0);

    pageTable.writeByte(1738248, 34);
    for (size_t i = 1731240; i < 1738255; ++i) {
        cout << "Byte at [" << i << "]: Page #" << pageTable.getPageIndex(i) << ", Value (decimal): " << (int)pageTable.readByte(i) << endl;
    }

    for (size_t i = 1731; i < 1738; ++i) {
        cout << "Byte at [" << i << "]: Page #" << pageTable.getPageIndex(i) << ", Value (decimal): " << (int)pageTable.readByte(i) << endl;
    }
}
