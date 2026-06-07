#ifndef CUCKOO_HASH_ITERS_HPP
#define CUCKOO_HASH_ITERS_HPP

#include <utility>
#include "CuckooHashTable.hpp"

namespace afanasev
{
  template < class Key, class Value, class Hash1, class Hash2, class Equal >
  class CuckooHashIter
  {
    friend class CuckooHashTable< Key, Value, Hash1, Hash2, Equal >;
    friend class CuckooHashConstIter< Key, Value, Hash1, Hash2, Equal >;
    using type = std::pair< Key, Value >;

  public:
    CuckooHashIter();
    explicit CuckooHashIter(CuckooHashTable< Key, Value, Hash1, Hash2, Equal > * table, size_t startPos = 0);

    CuckooHashIter & operator++();
    bool operator==(const CuckooHashIter & other) const;
    bool operator!=(const CuckooHashIter & other) const;
    type & operator*() const;

  private:
    CuckooHashTable< Key, Value, Hash1, Hash2, Equal> * table_;
    size_t currentPos_;

    void findValid();
  };

  template < class Key, class Value, class Hash1, class Hash2, class Equal >
  class CuckooHashConstIter
  {
    friend class CuckooHashTable< Key, Value, Hash1, Hash2, Equal >;
    friend class CuckooHashIter< Key, Value, Hash1, Hash2, Equal >;
    using type = std::pair< Key, Value >;

  public:
    CuckooHashConstIter();
    explicit CuckooHashConstIter(const CuckooHashTable< Key, Value, Hash1, Hash2, Equal > * table,
      size_t startPos = 0);

    CuckooHashConstIter & operator++();
    bool operator==(const CuckooHashConstIter & other) const;
    bool operator!=(const CuckooHashConstIter & other) const;
    const type & operator*() const;

  private:
    const CuckooHashTable< Key, Value, Hash1, Hash2, Equal > * table_;
    size_t currentPos_;

    void findValid();
  };
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
afanasev::CuckooHashIter< Key, Value, Hash1, Hash2, Equal >::
CuckooHashIter():
  table_(nullptr), currentPos_(0)
{}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
afanasev::CuckooHashIter< Key, Value, Hash1, Hash2, Equal >::
CuckooHashIter(CuckooHashTable< Key, Value, Hash1, Hash2, Equal > * table, size_t startPos):
  table_(table), currentPos_(startPos)
{
  findValid();
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
void afanasev::CuckooHashIter< Key, Value, Hash1, Hash2, Equal >::
findValid()
{
  if (!table_)
  {
    return;
  }

  size_t total = 2 * table_->capacity_;
  while (currentPos_ < total)
  {
    size_t slot = currentPos_;
    bool occupied = false;
    if (slot < table_->capacity_)
    {
      occupied = table_->occupied1_[slot];
    }
    else
    {
      occupied = table_->occupied2_[slot - table_->capacity_];
    }
    if (occupied)
    {
      return;
    }
    ++currentPos_;
  }

  table_ = nullptr;
}

#endif
