#include <boost/test/unit_test.hpp>
#include "HashTable/HashTable.hpp"
#include "HashTable/HashFunction.hpp"
#include <string>
#include <utility>

namespace af = afanasev;

BOOST_AUTO_TEST_SUITE(HashTableStringInt)

BOOST_AUTO_TEST_CASE(test_constructor)
{
  af::HashTable<std::string, int, af::Hasher<std::string>, std::equal_to<std::string> > ht(16);
  BOOST_CHECK(ht.empty());
  BOOST_CHECK_EQUAL(ht.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_add_and_size)
{
  af::HashTable<std::string, int, af::Hasher<std::string>, std::equal_to<std::string> > ht(16);
  ht.add("one", 1);
  BOOST_CHECK_EQUAL(ht.size(), 1);
  BOOST_CHECK(!ht.empty());

  ht.add("two", 2);
  BOOST_CHECK_EQUAL(ht.size(), 2);
}

BOOST_AUTO_TEST_CASE(test_has)
{
  af::HashTable<std::string, int, af::Hasher<std::string>, std::equal_to<std::string> > ht(16);
  ht.add("one", 1);
  ht.add("two", 2);

  BOOST_CHECK(ht.has("one"));
  BOOST_CHECK(ht.has("two"));
  BOOST_CHECK(!ht.has("three"));
}

BOOST_AUTO_TEST_CASE(test_drop)
{
  af::HashTable<std::string, int, af::Hasher<std::string>, std::equal_to<std::string> > ht(16);
  ht.add("one", 1);
  ht.add("two", 2);

  int val = ht.drop("one");
  BOOST_CHECK_EQUAL(val, 1);
  BOOST_CHECK_EQUAL(ht.size(), 1);
  BOOST_CHECK(!ht.has("one"));
  BOOST_CHECK(ht.has("two"));

  BOOST_CHECK_THROW(ht.drop("missing"), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_add_update_existing)
{
  af::HashTable<std::string, int, af::Hasher<std::string>, std::equal_to<std::string> > ht(16);
  ht.add("key", 1);
  ht.add("key", 2);

  int val = ht.drop("key");
  BOOST_CHECK_EQUAL(val, 2);
  BOOST_CHECK_EQUAL(ht.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_clear)
{
  af::HashTable<std::string, int, af::Hasher<std::string>, std::equal_to<std::string> > ht(16);
  ht.add("one", 1);
  ht.add("two", 2);
  ht.add("three", 3);

  ht.clear();
  BOOST_CHECK(ht.empty());
  BOOST_CHECK_EQUAL(ht.size(), 0);
  BOOST_CHECK(!ht.has("one"));
  BOOST_CHECK(!ht.has("two"));
  BOOST_CHECK(!ht.has("three"));
}

BOOST_AUTO_TEST_CASE(test_rehash)
{
  af::HashTable<std::string, int, af::Hasher<std::string>, std::equal_to<std::string> > ht(4);
  ht.add("one", 1);
  ht.add("two", 2);
  ht.add("three", 3);
  ht.add("four", 4);
  ht.add("five", 5);

  ht.rehash(16);
  BOOST_CHECK_EQUAL(ht.size(), 5);
  BOOST_CHECK(ht.has("one"));
  BOOST_CHECK(ht.has("two"));
  BOOST_CHECK(ht.has("three"));
  BOOST_CHECK(ht.has("four"));
  BOOST_CHECK(ht.has("five"));

  ht.rehash(2);
  BOOST_CHECK_EQUAL(ht.size(), 5);
  BOOST_CHECK(ht.has("one"));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(HashTableIntInt)

BOOST_AUTO_TEST_CASE(test_int_keys)
{
  af::HashTable<int, int, std::hash<int>, std::equal_to<int> > ht(8);
  BOOST_CHECK(ht.empty());

  ht.add(10, 100);
  ht.add(20, 200);
  BOOST_CHECK_EQUAL(ht.size(), 2);
  BOOST_CHECK(ht.has(10));
  BOOST_CHECK(ht.has(20));

  ht.add(20, 250);
  int val = ht.drop(20);
  BOOST_CHECK_EQUAL(val, 250);
  BOOST_CHECK_EQUAL(ht.size(), 1);
  BOOST_CHECK(!ht.has(20));
  BOOST_CHECK(ht.has(10));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(HashTablePairString)

BOOST_AUTO_TEST_CASE(test_pair_keys)
{
  typedef std::pair<std::string, std::string> Key;
  af::HashTable<Key, int, af::PairHasher<std::string>, std::equal_to<Key> > ht(8);

  Key e1 = std::make_pair("A", "B");
  Key e2 = std::make_pair("B", "C");
  Key e3 = std::make_pair("A", "B");

  ht.add(e1, 10);
  ht.add(e2, 20);
  ht.add(e3, 30);

  BOOST_CHECK_EQUAL(ht.size(), 2);
  BOOST_CHECK(ht.has(e1));
  BOOST_CHECK(ht.has(e2));

  int val = ht.drop(e1);
  BOOST_CHECK_EQUAL(val, 30);
  BOOST_CHECK_EQUAL(ht.size(), 1);
  BOOST_CHECK(!ht.has(e1));
  BOOST_CHECK(ht.has(e2));
}

BOOST_AUTO_TEST_SUITE_END()
