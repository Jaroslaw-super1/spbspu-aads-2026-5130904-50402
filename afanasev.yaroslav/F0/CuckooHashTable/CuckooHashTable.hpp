#ifndef CUCKOO_HASH_TABLE_HPP
#define CUCKOO_HASH_TABLE_HPP

#include <cstddef>
#include <functional>
#include <stdexcept>
#include <utility>
#include "CuckooHashFunction.hpp"
#include "top-it-vector.hpp"

namespace afanasev
{
  template < class Key, class Value, class Hash1 = Hasher< Key >,
    class Hash2 = Hasher< Key >, class Equal = std::equal_to< Key > >
  class CuckooHashTable
  {
  public:
    using value_type = std::pair< Key, Value >;

    explicit CuckooHashTable( size_t initial_capacity = 16 );
    CuckooHashTable( const CuckooHashTable & other );
    CuckooHashTable( CuckooHashTable && other ) noexcept;
    ~CuckooHashTable();

    CuckooHashTable & operator=( const CuckooHashTable & other );
    CuckooHashTable & operator=( CuckooHashTable && other ) noexcept;

    void add( const Key & k, const Value & v );        // вставка / обновление
    void add( Key && k, Value && v );                  // перемещающая версия

    Value drop( const Key & k );                       // удалить ключ, вернуть значение
    bool has( const Key & k ) const noexcept;          // проверить наличие

    Value & get( const Key & k );                      // доступ к значению (неконстантный)
    const Value & get( const Key & k ) const;          // константный доступ

    void clear() noexcept;                             // очистить таблицу
    size_t size() const noexcept;                      // количество элементов
    bool empty() const noexcept;                       // пуста ли таблица

    void rehash( size_t new_capacity );                // изменить ёмкость (перестроить)
    void swap( CuckooHashTable & other ) noexcept;     // обмен содержимым

  private:
    Vector< value_type > data1_;
    Vector< bool > occupied1_;
    Vector< value_type > data2_;
    Vector< bool > occupied2_;

    size_t capacity_;
    size_t size_;
    Hash1 hash1_;
    Hash2 hash2_;
    Equal equal_;

    size_t index1( const Key & k ) const { return hash1_( k ) % capacity_; }
    size_t index2( const Key & k ) const { return hash2_( k ) % capacity_; }

    bool insertInternal( const Key & k, const Value & v );
    bool insertInternal( Key && k, Value && v );

    Value * findValue( const Key & k ) noexcept;
    const Value * findValue( const Key & k ) const noexcept;

    bool isOccupied1( size_t idx ) const { return occupied1_[ idx ] == 1; }
    bool isOccupied2( size_t idx ) const { return occupied2_[ idx ] == 1; }
    void setOccupied1( size_t idx, bool occ ) { occupied1_[ idx ] = occ ? 1 : 0; }
    void setOccupied2( size_t idx, bool occ ) { occupied2_[ idx ] = occ ? 1 : 0; }
  };
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal >::
CuckooHashTable(size_t initial_capacity):
  capacity_(initial_capacity),
  size_(0),
  hash1_(Hash1()),
  hash2_(Hash2()),
  equal_(Equal())
{
  if (!capacity_)
  {
    capacity_ = 1;
  }

  for (size_t i = 0; i < capacity_; ++i)
  {
    data1_.pushBack(value_type());
    occupied1_.pushBack(false);
    data2_.pushBack(value_type());
    occupied2_.pushBack(false);
  }
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal >::
CuckooHashTable(const CuckooHashTable & other):
  data1_(other.data1_),
  occupied1_(other.occupied1_),
  data2_(other.data2_),
  occupied2_(other.occupied2_),
  capacity_(other.capacity_),
  size_(other.size_),
  hash1_(other.hash1_),
  hash2_(other.hash2_),
  equal_(other.equal_)
{}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal >::
CuckooHashTable(CuckooHashTable && other) noexcept:
  data1_(std::move(other.data1_)),
  occupied1_(std::move(other.occupied1_)),
  data2_(std::move(other.data2_)),
  occupied2_(std::move(other.occupied2_)),
  capacity_(other.capacity_),
  size_(other.size_),
  hash1_(std::move(other.hash1_)),
  hash2_(std::move(other.hash2_)),
  equal_(std::move(other.equal_))
{
  other.capacity_ = 0;
  other.size_ = 0;
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal >::
~CuckooHashTable()
{
  clear();
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal > &
afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal >::
operator=(const CuckooHashTable & other)
{
  if (this != &other)
  {
    CuckooHashTable tmp(other);
    swap(tmp);
  }
  return *this;
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal > &
afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal >::
operator=(CuckooHashTable && other) noexcept
{
  if (this != &other)
  {
    CuckooHashTable tmp(std::move(other));
    swap(tmp);
  }
  return *this;
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
void afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal >::
swap(CuckooHashTable & other) noexcept
{
  data1_.swap(other.data1_);
  occupied1_.swap(other.occupied1_);
  data2_.swap(other.data2_);
  occupied2_.swap(other.occupied2_);
  std::swap(capacity_, other.capacity_);
  std::swap(size_, other.size_);
  std::swap(hash1_, other.hash1_);
  std::swap(hash2_, other.hash2_);
  std::swap(equal_, other.equal_);
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
void afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal >::
add(const Key & k, const Value & v)
{
  while (!insertInternal(k, v))
  {
    size_t new_cap = capacity_ * 2;
    rehash(new_cap);
  }
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
void afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal >::
add(Key && k, Value && v)
{
  while (!insertInternal(std::move(k), std::move(v)))
  {
    size_t new_cap = capacity_ * 2;
    rehash(new_cap);
  }
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
Value afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal >::
drop(const Key & k)
{
  size_t i1 = index1(k);
  if (isOccupied1(i1) && equal_(data1_[i1].first, k))
  {
    Value val = std::move(data1_[i1].second);
    setOccupied1(i1, false);
    --size_;
    return val;
  }

  size_t i2 = index2(k);
  if (isOccupied2(i2) && equal_(data2_[i2].first, k))
  {
    Value val = std::move(data2_[i2].second);
    setOccupied2(i2, false);
    --size_;
    return val;
  }
  throw std::out_of_range("CuckooHashTable::drop: key not found");
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
bool afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal >::
has(const Key & k) const noexcept
{
  size_t i1 = index1(k);
  if (isOccupied1(i1) && equal_(data1_[i1].first, k))
  {
    return true;
  }

  size_t i2 = index2(k);
  if (isOccupied2(i2) && equal_(data2_[i2].first, k))
  {
    return true;
  }
  return false;
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
Value & afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal >::
get(const Key & k)
{
  Value * p = findValue(k);
  if (!p)
  {
    throw std::out_of_range("CuckooHashTable::get: key not found");
  }
  return *p;
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
const Value & afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal >::
get(const Key & k) const
{
  const Value * p = findValue(k);
  if (!p)
  {
    throw std::out_of_range("CuckooHashTable::get const: key not found");
  }
  return *p;
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
void afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal >::
clear() noexcept
{
  for (size_t i = 0; i < capacity_; ++i)
  {
    setOccupied1(i, false);
    setOccupied2(i, false);
  }
  size_ = 0;
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
size_t afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal >::
size() const noexcept
{
  return size_;
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
bool afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal >::
empty() const noexcept
{
  return !size_;
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
void afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal >::
rehash(size_t new_capacity)
{
  if (new_capacity <= capacity_)
  {
    return;
  }

  CuckooHashTable new_table(new_capacity);

  for (size_t i = 0; i < capacity_; ++i)
  {
    if (isOccupied1(i))
    {
      new_table.add(std::move(data1_[i].first), std::move(data1_[i].second));
    }
    if (isOccupied2(i))
    {
      new_table.add(std::move(data2_[i].first), std::move(data2_[i].second));
    }
  }

  swap(new_table);
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
bool afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal >::
insertInternal(const Key & k, const Value & v)
{
  Value * existing = findValue(k);
  if (existing)
  {
    *existing = v;
    return true;
  }

  value_type current(k, v);
  const size_t MAX_LOOP = 2 * capacity_;

  for (size_t step = 0; step < MAX_LOOP; ++step)
  {
    size_t i1 = hash1_(current.first) % capacity_;
    if (!isOccupied1(i1))
    {
      data1_[i1] = std::move(current);
      setOccupied1(i1, true);
      ++size_;
      return true;
    }
    std::swap(current, data1_[i1]);

    size_t i2 = hash2_(current.first) % capacity_;
    if (!isOccupied2(i2))
    {
      data2_[i2] = std::move(current);
      setOccupied2(i2, true);
      ++size_;
      return true;
    }
    std::swap(current, data2_[i2]);
  }

  return false;
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
bool afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal >::
insertInternal(Key && k, Value && v)
{
  Value * existing = findValue(k);
  if (existing)
  {
    *existing = std::move(v);
    return true;
  }

  value_type current(std::move(k), std::move(v));
  const size_t MAX_LOOP = 2 * capacity_;

  for (size_t step = 0; step < MAX_LOOP; ++step)
  {
    size_t i1 = hash1_(current.first) % capacity_;
    if (!isOccupied1(i1))
    {
      data1_[i1] = std::move(current);
      setOccupied1(i1, true);
      ++size_;
      return true;
    }
    std::swap(current, data1_[i1]);

    size_t i2 = hash2_(current.first) % capacity_;
    if (!isOccupied2(i2))
    {
      data2_[i2] = std::move(current);
      setOccupied2(i2, true);
      ++size_;
      return true;
    }
    std::swap(current, data2_[i2]);
  }

  return false;
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
Value * afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal >::
findValue(const Key & k) noexcept
{
  size_t i1 = index1(k);
  if (isOccupied1(i1) && equal_(data1_[i1].first, k))
  {
    return &data1_[i1].second;
  }

  size_t i2 = index2(k);
  if (isOccupied2(i2) && equal_(data2_[i2].first, k))
  {
    return &data2_[i2].second;
  }

  return nullptr;
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
const Value * afanasev::CuckooHashTable< Key, Value, Hash1, Hash2, Equal >::
findValue(const Key & k) const noexcept
{
  size_t i1 = index1(k);
  if (isOccupied1(i1) && equal_(data1_[i1].first, k))
  {
    return &data1_[i1].second;
  }

  size_t i2 = index2(k);
  if (isOccupied2(i2) && equal_(data2_[i2].first, k))
  {
    return &data2_[i2].second;
  }

  return nullptr;
}

#endif
