#ifndef NOTE_HPP
#define NOTE_HPP

#include <HashTable/HashTable.hpp>
#include <HashTable/HashFunction.hpp>
#include <top-it-vector.hpp>
#include <list.hpp>

namespace afanasev
{
  class Note
  {
    Vector< std::string > lines;
    HashTable< std::string, bool, Hasher< std::string >, std::equal_to< std::string > > tags;
    List< std::string > children;
  };
}

#endif
