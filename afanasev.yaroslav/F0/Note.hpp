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
  public:
    void addLine(const std::string & line);
    const List< std::string > & getChildren() const;
    const Vector< std::string > & getLines() const;
    Vector< std::string > getTags() const;

  private:
    Vector< std::string > lines_;
    HashTable< std::string, bool, Hasher< std::string >, std::equal_to< std::string > > tags_{16};
    List< std::string > children_;
  };
}

afanasev::Vector< std::string > afanasev::Note::
getTags() const
{

}

const afanasev::Vector< std::string > & afanasev::Note::
getLines() const
{

}

const afanasev::List< std::string > & afanasev::Note::
getChildren() const
{
  return children_;
}

void afanasev::Note::
addLine(const std::string & line)
{
  lines_.pushBack(line);
}

#endif
