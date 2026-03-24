#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <list.hpp>

namespace afanasev
{
  template< typename T >
  class Queue
  {
   public:
    void push(const T & rhs);
    T & get() noexcept;
    void pop() noexcept;
    bool empty() const noexcept;
    size_t size() const noexcept;

   private:
    List< T > data_;
  };
}

template < class T >
void afanasev::Queue< T >::push(const T &rhs)
{
}

template < class T >
T & afanasev::Queue< T >::get() noexcept
{
}

template < class T >
void afanasev::Queue< T >::pop() noexcept
{
}

template < class T >
bool afanasev::Queue< T >::empty() const noexcept
{
  return !data_.size();
}

template < class T >
size_t afanasev::Queue< T >::size() const noexcept
{
  return data_.size();
}

#endif
