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

  void deleteDepth(const std::string & title, NoteSet & ns, unsigned int depth);

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

void afanasev::deleteDepth(const std::string & title, NoteSet & ns, unsigned int depth)
{
  if (!ns.has(title))
  {
    return;
  }

  const Note & note = ns.get(title);
  LIter< std::string > end = LIter< std::string >();
  List< std::string > childrenCopy = note.getChildren();

  if (!depth)
  {
    ns.drop(title);
  }

  depth = (!depth) ? 0 : depth - 1;

  for (LIter< std::string > it = childrenCopy.begin(); it != end; ++it)
  {
    deleteDepth(*it, ns, depth);
  }
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
  std::string title, line;
  in >> std::quoted(title) >> std::quoted(line);

  if (!ns.has(title))
  {
    throw std::runtime_error("Note not found");
  }

  ns.get(title).addLine(line);
  out << "added line to \"" << title << "\"\n";
}

void afanasev::cmdDel(std::istream & in, std::ostream & out, NoteSet & ns)
{
  std::string title;
  in >> std::quoted(title);

  if (!ns.has(title))
  {
    throw std::runtime_error("Note not found");
  }

  ns.drop(title);
  out << "\"" << title << "\" deleted\n";
}

void afanasev::cmdDelk(std::istream & in, std::ostream & out, NoteSet & ns)
{
  std::string title;
  unsigned int depth = 0;

  in >> std::quoted(title) >> depth;

  if (!ns.has(title))
  {
    throw std::runtime_error("Note not found");
  }

  deleteDepth(title, ns, depth);
  out << "\"" << title << "\" subtree up to depth " << depth << " deleted\n";
}

void afanasev::cmdSee(std::istream & in, std::ostream & out, NoteSet & ns)
{
  std::string title;
  in >> std::quoted(title);

  if (!ns.has(title))
  {
    throw std::runtime_error("Note not found");
  }

  const Note & note = ns.get(title);

  out << "name: \"" << title << "\"\n";
  out << "tags:";

  Vector< std::string > tags = note.getTags();
  for (size_t i = 0; i < tags.getSize(); ++i)
  {
    out << " " << tags[i];
  }
  out << "\n";

  const Vector< std::string > & lines = note.getLines();
  for (size_t i = 0; i < lines.getSize(); ++i)
  {
    out << (i + 1) << ": " << lines[i] << "\n";
  }
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
