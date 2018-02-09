#ifndef ESM_VM_PAGE_HPP
#define ESM_VM_PAGE_HPP

#include <vector>
#include <map>

using namespace std;

class Page {
protected:
    vector <uint8_t> bytes;
public:
    const static size_t pageSize = 64 * 1024; // 64 KiB

    Page();
    virtual ~Page();

    uint8_t readByte(size_t offset);
    void writeByte(size_t offset, uint8_t byte);
};

class PageTable {
protected:
    map <size_t, Page *> pages;
    Page * zeroPage;
public:
    explicit PageTable(size_t pagesCount);
    PageTable(const PageTable & pageTable);
    virtual ~PageTable();

    auto getAllPages() const -> decltype(pages) {
        return pages;
    }

    size_t getPageIndex(size_t address);
    size_t getPageOffset(size_t address);
    size_t getPageBeginAddress(size_t pageIndex);

    Page * getPage(size_t pageIndex);
    Page * getPageOrThrow(size_t pageIndex);
    Page * getOrCreatePage(size_t pageIndex);

    uint8_t readByte(size_t address);
    void writeByte(size_t address, uint8_t byte);

    void createPage(size_t pageIndex);
    void deletePage(size_t pageIndex);
};

#endif /* end of include guard: ESM_VM_PAGE_HPP */
