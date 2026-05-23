#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <string>

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

#endif
