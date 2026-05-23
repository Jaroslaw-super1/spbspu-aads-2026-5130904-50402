#include <iostream>
#include <limits>
#include <string>
#include <stdexcept>
#include "commands.hpp"

int main()
{
  using NoteSet = afanasev::HashTable<
    std::string, afanasev::Note, afanasev::Hasher< std::string >, std::equal_to< std::string > >;

  using CmdFunc = void (*)(std::istream &, std::ostream &, NoteSet &);
  using CmdHash = afanasev::Hasher< std::string >;

  afanasev::HashTable< std::string, CmdFunc, CmdHash, std::equal_to< std::string > > commands(16);

  commands.add("cr",          afanasev::cmdCr);
  commands.add("str",         afanasev::cmdStr);
  commands.add("del",         afanasev::cmdDel);
  commands.add("delk",        afanasev::cmdDelk);
  commands.add("see",         afanasev::cmdSee);
  commands.add("link",        afanasev::cmdLink);
  commands.add("deltagnote",  afanasev::cmdDeltagNote);
  commands.add("seetag",      afanasev::cmdSeetag);
  commands.add("seetagand",   afanasev::cmdSeetagAnd);
  commands.add("seetagor",    afanasev::cmdSeetagOr);
  commands.add("tagrp",       afanasev::cmdTagRp);
  commands.add("tagaddnew",   afanasev::cmdTagAddNew);
  commands.add("deltag",      afanasev::cmdDelTag);
  commands.add("tag",         afanasev::cmdTag);
  commands.add("tagdel",      afanasev::cmdTagDel);
  commands.add("getliked",    afanasev::cmdGetLiked);
  commands.add("addlinktag",  afanasev::cmdAddLinkTag);
  commands.add("dellinktag",  afanasev::cmdDelLinkTag);

  NoteSet notes(64);

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      commands.get(cmd)(std::cin, std::cout, notes);
    }
    catch (const std::exception &)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  return 0;
}
