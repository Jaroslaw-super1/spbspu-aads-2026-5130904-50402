#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <string>
#include "HashTable/HashTable.hpp"
#include "HashTable/HashFunction.hpp"
#include "Graph.hpp"

namespace afanasev
{
  using GraphSet = HashTable< std::string, Graph, Hasher< std::string >, std::equal_to< std::string > >;

  void cmdPrint(std::istream & in, std::ostream & out, GraphSet & graphs);
  void cmdComplement(std::istream & in, std::ostream & out, GraphSet & graphs);
  void cmdIntersect(std::istream & in, std::ostream & out, GraphSet & graphs);
  void cmdUnion(std::istream & in, std::ostream & out, GraphSet & graphs);
}

#endif
