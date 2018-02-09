#include <esm/vmpage.hpp>
#include <vector>
#include <exception>
#include <stdexcept>

using namespace std;

PageTable::PageTable(size_t pagesCount) {
    for (size_t i = 0; i < pagesCount; ++i) {
        createPage(i);
    }
    zeroPage = new Page;
}

PageTable::PageTable(const PageTable & pageTable): pages(pageTable.getAllPages()) {
    zeroPage = new Page;
}

PageTable::~PageTable() {
    while (!pages.empty()) {
        size_t pageIndex = (*pages.begin()).first;
        deletePage(pageIndex);
    }

    delete zeroPage;
    pages.clear();
}

size_t PageTable::getPageIndex(size_t address) {
    return address / Page::pageSize;
}

size_t PageTable::getPageOffset(size_t address) {
    return address % Page::pageSize;
}

size_t PageTable::getPageBeginAddress(size_t pageIndex) {
    return pageIndex * Page::pageSize;
}

Page * PageTable::getPage(size_t pageIndex) {
    if (pages.count(pageIndex)) {
        return pages.at(pageIndex);
    } else {
        return zeroPage;
    }
}

Page * PageTable::getPageOrThrow(size_t pageIndex) {
    if (pages.count(pageIndex)) {
        return pages.at(pageIndex);
    } else {
        throw out_of_range("no such page");
    }
}

Page * PageTable::getOrCreatePage(size_t pageIndex) {
    if (pages.count(pageIndex)) {
        return pages.at(pageIndex);
    } else {
        createPage(pageIndex);
        return getPage(pageIndex);
    }
}

uint8_t PageTable::readByte(size_t address) {
    size_t pageIndex  = getPageIndex(address);
    size_t pageOffset = getPageOffset(address);

    return getPage(pageIndex)->readByte(pageOffset);
}

void PageTable::writeByte(size_t address, uint8_t byte) {
    size_t pageIndex  = getPageIndex(address);
    size_t pageOffset = getPageOffset(address);

    getOrCreatePage(pageIndex)->writeByte(pageOffset, byte);
}

void PageTable::createPage(size_t pageIndex) {
    if (pages.count(pageIndex)) {
        throw std::runtime_error("attempt to double-create page");
    }
}

void PageTable::deletePage(size_t pageIndex) {
    delete getPageOrThrow(pageIndex);
    pages.erase(pageIndex);
}
