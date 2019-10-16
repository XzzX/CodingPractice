#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cassert>
#include <cstdlib>
#include <stack>
#include <vector>

void insert_bottom(std::stack<int>& s, const int v)
{
   if (s.empty())
   {
      s.push(v);
      return;
   }

   auto tmp = s.top();
   s.pop();
   insert_bottom(s, v);
   s.push(tmp);
}

void reverse(std::stack<int>& s)
{
   if (s.empty()) return;

   auto tmp = s.top();
   s.pop();
   reverse(s);
   insert_bottom(s, tmp);
}

/**
 * \param v value to be inserted
 */
void insert_sorted(std::stack<int>& s, const int v)
{
   if (s.empty())
   {
      s.push(v);
      return;
   }

   if (s.top() <= v)
   {
      s.push(v);
   } else
   {
      auto tmp = s.top();
      s.pop();
      insert_sorted(s, v);
      s.push(tmp);
   }
}

void sort(std::stack<int>& s)
{
   if (s.empty()) return;

   auto tmp = s.top();
   s.pop();
   sort(s);
   insert_sorted(s, tmp);
}

void stack_equal(std::stack<int> lhs, std::stack<int> rhs)
{
   while (!lhs.empty())
   {
      ASSERT_TRUE(!rhs.empty());
      ASSERT_EQ(lhs.top(), rhs.top());
      lhs.pop();
      rhs.pop();
   }
}

TEST(StackModification, Reverse)
{
   std::stack<int> s({8,4,1,8,5,6,7,2});
   reverse(s);
   stack_equal(s, std::stack<int>({2,7,6,5,8,1,4,8}));
}

TEST(StackModification, Sort)
{
   std::stack<int> s({8,4,1,8,5,6,7,2});
   sort(s);
   stack_equal(s, std::stack<int>({1,2,4,5,6,7,8,8}));
}

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
