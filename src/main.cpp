#include <iostream>
#include <vector>
#include <esm/vmpage.hpp>

using namespace std;

int main() {
    Page page;
    page.writeByte(149, (uint8_t)119);
    for (size_t i = 140; i < 155; ++i) {
        cout << i << ": " << (int)page.readByte(i) << endl;
    }

    try {
        page.writeByte(888888, 9); // > 64K
    } catch (runtime_error e) {
        cerr << "Exception caught: " << e.what() << endl;
    }
    cout << page.readByte(888888) << endl; // > 64K
}
