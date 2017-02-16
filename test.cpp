#include <gtest/gtest.h>

#include <iterator>
#include <chrono>

#include "bst.hpp"

using namespace bst;
using namespace std;

TEST(MapShould, Insert_An_Element_At_The_Root) {
  Map<int, int> m;
  m.insert(make_pair(1, 4));

  ASSERT_EQ(1, m.size());
}

TEST(MapShould, Have_Unique_Keys) {
  Map<int, int> m;
  m.insert(make_pair(1, 4));
  m.insert(make_pair(1, 5));
  m.insert(make_pair(1, 6));

  ASSERT_EQ(1, m.size());
}

TEST(MapShould, Insert_Element_On_The_Left) {
  Map<int, int> m;
  m.insert(make_pair(7, 4));
  m.insert(make_pair(3, 4));

  ASSERT_EQ(2, m.size());
}

TEST(MapShould, Insert_Element_On_The_Right) {
  Map<int, int> m;
  m.insert(make_pair(7, 4));
  m.insert(make_pair(9, 4));

  ASSERT_EQ(2, m.size());
}

TEST(MapShould, Return_Equal_Begin_And_End_Iterator_When_Empty) {
  Map<int, int> m;
  EXPECT_TRUE(m.end() == m.begin());
}

TEST(MapShould, Return_Different_Begin_And_End_Iterators_When_Not_Empty) {
  Map<int, int> m;
  m.insert(make_pair(3, 5));
  m.insert(make_pair(5, 5));
  EXPECT_TRUE(m.end() != m.begin());
}

TEST(MapShould, Handle_String_Type) {
  Map<string, string> m;

  m.insert(make_pair("abc", "bcd"));
  m.insert(make_pair("xyz", "bcd"));

  EXPECT_EQ(2, m.size());
}


TEST(MapShould, Get_Iterator_Of_An_Existing_Value) {
  Map<string, string> m;

  m.insert(make_pair("abc", "bcd"));
  m.insert(make_pair("xyz", "bcd"));
 
  Map<string,string>::iterator it = m.get("abc");

  EXPECT_TRUE(it != m.end());
}

TEST(MapShould, Get_Iterator_Of_An_Unexisting_Value) {
  Map<string, string> m;

  m.insert(make_pair("abc", "bcd"));
  m.insert(make_pair("xyz", "bcd"));
 
  Map<string,string>::iterator it = m.get("abce");

  EXPECT_TRUE(it == m.end());
}

TEST(MapShould, Get_Iterator_From_Empty_Map) {
  Map<string, string> m;
  Map<string,string>::iterator it = m.get("abce");
  EXPECT_TRUE(it == m.end());
}


TEST(MapShould, Get_An_Existing_Value) {
  Map<string, string> m;

  m.insert(make_pair("abc", "bcd"));
  m.insert(make_pair("xyz", "uvw"));
 
  Map<string,string>::iterator it = m.get("abc");

  ASSERT_TRUE(it != m.end());
  EXPECT_EQ("bcd", it.value());
}

TEST(MapShould, Remove_An_Existing_Value) {
  Map<string, string> m;

  m.insert(make_pair("abc", "bcd"));
  m.insert(make_pair("xyz", "uvw"));

  EXPECT_TRUE(m.get("abc") != m.end());
 
  m.remove("abc");

  EXPECT_TRUE(m.get("abc") == m.end());
}

TEST(MapShould, Have_Good_Size_After_Removing_Some_Elements) {
  Map<int, int> m;

  m.insert(make_pair(2, 5));
  m.insert(make_pair(1, 4));
  m.insert(make_pair(5, 5));

  EXPECT_EQ(3, m.size());

  m.remove(0);
  EXPECT_EQ(3, m.size());

  m.remove(2);
  EXPECT_EQ(2, m.size());

  m.remove(1);
  EXPECT_EQ(1, m.size());

  m.remove(5);
  EXPECT_EQ(0, m.size());

  m.remove(5);
  EXPECT_EQ(0, m.size());
}

TEST(MapShould, Insert_Correctly_More_Than_5_Values) {
  Map<int, int> m;
  m.insert(make_pair(1, 2));
  m.insert(make_pair(2, 2));
  m.insert(make_pair(3, 2));
  m.insert(make_pair(4, 2));
  m.insert(make_pair(5, 2));
  m.insert(make_pair(6, 2));
  EXPECT_EQ(6, m.size());
}

template<typename T>
size_t performanceTest(T f, int iterations) {
  auto before = std::chrono::high_resolution_clock::now();
  f(iterations);
  auto after = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(after - before);
  return duration.count();
}

void testNewMap(int iterations) {
  int max = iterations;
  Map<int, int> m;
  for(int i=0; i<max; ++i) {
    m.insert(make_pair(i, max - i));
  }
}

void testStlMap(int iterations) {
  int max = iterations;
  std::map<int, int> m;
  for(int i=0; i<max; ++i) {
    m.insert(make_pair(i, max - i));
  }
}

TEST(MapShould, Have_A_Good_Perf) {
  int iterations = 5000;
  size_t us_new = performanceTest(testNewMap, iterations);
  size_t us_stl = performanceTest(testStlMap, iterations);

  float factor = (float) us_new / us_stl;
  EXPECT_GT(18.0, factor);
}
