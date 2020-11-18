#include <vector>

#include "iterator_range.h"

#ifndef __PAGINATOR_H__
#define __PAGINATOR_H__

template <typename Iterator>
class Paginator {
private:
  std::vector<IteratorRange<Iterator>> pages;

public:
  Paginator(Iterator begin, Iterator end, size_t page_size) {
    for (size_t left = std::distance(begin, end); left > 0; ) {
      size_t current_page_size = std::min(page_size, left);
      Iterator current_page_end = next(begin, current_page_size);
      pages.push_back({begin, current_page_end});

      left -= current_page_size;
      begin = current_page_end;
    }
  }

  auto begin() const {
    return pages.begin();
  }

  auto end() const {
    return pages.end();
  }

  size_t size() const {
    return pages.size();
  }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator(begin(c), end(c), page_size);
}

#endif // __PAGINATOR_H__