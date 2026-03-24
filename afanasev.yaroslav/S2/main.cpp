#include <iostream>
#include <fstream>
#include "stack.hpp"
#include "queue.hpp"

int main(int argc, char * argv[])
{
  if (argc > 2)
  {
    std::cerr << "too many args\n";
    return 1;
  }

  std::ifstream file;
  std::istream * in = & std::cin;

  if (argc == 2)
  {
    file.open(argv[1]);

    if (!file.is_open())
    {
      std::cerr << "error open file\n";
      return 1;
    }
    in = & file;
  }

  afanasev::Stack< long long > res;

  return 0;
}
