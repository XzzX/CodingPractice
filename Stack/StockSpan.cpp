#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cassert>
#include <cstdlib>
#include <stack>
#include <vector>

std::vector<int> stockSpanN2(const std::vector<int>& stock)
{
   std::vector<int> span(stock.size(), 0);

   for (int idx = stock.size() - 1; idx >= 0; --idx)
   {
      int cmp = idx;
      while (stock[idx] >= stock[cmp])
      {
         ++span[idx];
         --cmp;
         if (cmp < 0) break;
      }
   }

   return span;
}


std::vector<int> stockSpan(const std::vector<int>& stock)
{
   struct StockSpan
   {
      int price;
      int span;
   };

   std::vector<int> span(stock.size(), 0);
   std::stack<StockSpan> previousStockSpans; ///< strictly decreasing order

   for (int idx = 0; idx < stock.size(); ++idx)
   {
      //calculate current span
      int currentSpan = 1;
      while (!previousStockSpans.empty())
      {
         if (previousStockSpans.top().price <= stock[idx])
         {
            currentSpan += previousStockSpans.top().span;
            previousStockSpans.pop();
         } else
         {
            break;
         }
      }
      previousStockSpans.push({stock[idx], currentSpan});
      span[idx] = currentSpan;
   }

   return span;
}

TEST(StockSpan, N2)
{
   ASSERT_THAT( stockSpanN2({7,4,1,8,5,6,7,2}), ::testing::ElementsAre(1,1,1,4,1,2,3,1) );
}

TEST(StockSpan, BetterVersion)
{
   ASSERT_THAT( stockSpan({7,4,1,8,5,6,7,2}), ::testing::ElementsAre(1,1,1,4,1,2,3,1) );
}

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
