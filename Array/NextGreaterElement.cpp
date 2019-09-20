#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cassert>
#include <cstdlib>
#include <stack>
#include <vector>

std::vector<int> next_greater_element(const std::vector<int>& vec)
{
   std::stack<int> s;
   std::vector<int> res(vec.size());

   for (int i = vec.size() - 1; i >= 0; --i)
   {
      if (s.empty())
      {
         res[i] = -1;
      } else
      {
         if (vec[i]>=s.top())
         while (!s.empty() && (vec[i] >= s.top()))
         {
            s.pop();
         }
         
         if (s.empty())
         {
            res[i] = -1;
         }else
         {
            res[i] = s.top();
         }
      }

      s.push(vec[i]);
   }

   return res;
}

TEST(NextGreaterElement, various)
{
   ASSERT_THAT( next_greater_element({7,4,1,8,5,6,7,2}), ::testing::ElementsAre(8,8,8,-1,6,7,-1,-1) );
}

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
