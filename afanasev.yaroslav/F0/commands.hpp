#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <functional>
#include "HashTable/HashTable.hpp"
#include "HashTable/HashFunction.hpp"
#include "Note.hpp"

namespace afanasev
{
  using NoteSet = afanasev::HashTable<
    std::string, afanasev::Note, afanasev::Hasher< std::string >, std::equal_to< std::string > >;

//  using CmdFunc = void (*)(std::istream &, std::ostream &, NoteSet &);
//  using CmdHash = afanasev::Hasher< std::string >;

  void cmdCr(std::istream & in, std::ostream & out, NoteSet & ns);
  void cmdStr(std::istream & in, std::ostream & out, NoteSet & ns);
  void cmdDel(std::istream & in, std::ostream & out, NoteSet & ns);
  void cmdDelk(std::istream & in, std::ostream & out, NoteSet & ns);
  void cmdSee(std::istream & in, std::ostream & out, NoteSet & ns);
  void cmdLink(std::istream & in, std::ostream & out, NoteSet & ns);
  void cmdDeltagNote(std::istream & in, std::ostream & out, NoteSet & ns);
  void cmdSeetag(std::istream & in, std::ostream & out, NoteSet & ns);
  void cmdSeetagAnd(std::istream & in, std::ostream & out, NoteSet & ns);
  void cmdSeetagOr(std::istream & in, std::ostream & out, NoteSet & ns);
  void cmdTagRp(std::istream & in, std::ostream & out, NoteSet & ns);
  void cmdTagAddNew(std::istream & in, std::ostream & out, NoteSet & ns);
  void cmdDelTag(std::istream & in, std::ostream & out, NoteSet & ns);
  void cmdTag(std::istream & in, std::ostream & out, NoteSet & ns);
  void cmdTagDel(std::istream & in, std::ostream & out, NoteSet & ns);
  void cmdGetLiked(std::istream & in, std::ostream & out, NoteSet & ns);
  void cmdAddLinkTag(std::istream & in, std::ostream & out, NoteSet & ns);
  void cmdDelLinkTag(std::istream & in, std::ostream & out, NoteSet & ns);
}

void afanasev::cmdCr(std::istream & in, std::ostream & out, NoteSet & ns)
{
  std::string title;
  in >> std::quoted(title);

  if (ns.has(title))
  {
    throw std::runtime_error("Note exists");
  }

  ns.add(title, Note());
  out << "created \"" << title << "\"\n";
}

void afanasev::cmdStr(std::istream & in, std::ostream & out, NoteSet & ns)
{

}

void afanasev::cmdDel(std::istream & in, std::ostream & out, NoteSet & ns)
{

}

void afanasev::cmdDelk(std::istream & in, std::ostream & out, NoteSet & ns)
{

}

void afanasev::cmdSee(std::istream & in, std::ostream & out, NoteSet & ns)
{

}

void afanasev::cmdLink(std::istream & in, std::ostream & out, NoteSet & ns)
{

}

void afanasev::cmdDeltagNote(std::istream & in, std::ostream & out, NoteSet & ns)
{

}

void afanasev::cmdSeetag(std::istream & in, std::ostream & out, NoteSet & ns)
{

}

void afanasev::cmdSeetagAnd(std::istream & in, std::ostream & out, NoteSet & ns)
{

}

void afanasev::cmdSeetagOr(std::istream & in, std::ostream & out, NoteSet & ns)
{

}

void afanasev::cmdTagRp(std::istream & in, std::ostream & out, NoteSet & ns)
{

}

void afanasev::cmdTagAddNew(std::istream & in, std::ostream & out, NoteSet & ns)
{

}

void afanasev::cmdDelTag(std::istream & in, std::ostream & out, NoteSet & ns)
{

}

void afanasev::cmdTag(std::istream & in, std::ostream & out, NoteSet & ns)
{

}

void afanasev::cmdTagDel(std::istream & in, std::ostream & out, NoteSet & ns)
{

}

void afanasev::cmdGetLiked(std::istream & in, std::ostream & out, NoteSet & ns)
{

}

void afanasev::cmdAddLinkTag(std::istream & in, std::ostream & out, NoteSet & ns)
{

}

void afanasev::cmdDelLinkTag(std::istream & in, std::ostream & out, NoteSet & ns)
{

}

#endif
