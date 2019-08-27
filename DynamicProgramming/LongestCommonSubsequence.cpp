#include "gtest/gtest.h"

#include <cassert>
#include <cstdlib>
#include <string>

class Vector2D
{
   public:
      Vector2D(const size_t m, const size_t n, const int def = 0)
         : m_(m)
         , n_(n)
         , cache_(m*n, def)
   {}

      int& operator()(const size_t x, const size_t y)
      {
         assert(x < m_);
         assert(y < n_);
         auto idx = x + y * m_;
         return cache_[idx];
      }
   private:
      int m_;
      int n_;
      std::vector<int> cache_;
};

int lcs_recursive(const std::string& a, const std::string& b, int n = 0, int m = 0)
{
   if (n >= a.length()) return 0;
   if (m >= b.length()) return 0;
   if (a[n] == b[m]) return 1 + lcs_recursive(a, b, n+1, m+1);
   auto left  = lcs_recursive( a, b, n+1, m );
   auto right = lcs_recursive( a, b, n, m+1 );
   return std::max(left, right);
}

int lcs_bottom_up(const std::string& a, const std::string& b)
{
   const auto a_length = a.length();
   const auto b_length = b.length();

   Vector2D cache(a_length, b_length);

   for (int j = 0; j < b_length; ++j)
   {
      for (int i = 0; i < a_length; ++i)
      {
         if (a[i] == b[j])
         {
            int tmp = (i-1 >= 0) && (j-1 >= 0) ? cache(i-1, j-1) : 0;
            cache(i, j) = tmp + 1;
         } else
         {
            int cache_left  = i-1 >= 0 ? cache(i-1, j) : 0;
            int cache_right = j-1 >= 0 ? cache(i, j-1) : 0;
            auto tmp = std::max(cache_left, cache_right);
            cache(i, j) = tmp;
         }
      }
   }
   return cache(a_length - 1, (b_length - 1));
}

int lcs_top_down_helper(const std::string& a, 
      const std::string& b, 
      Vector2D& cache,
      int n = 0, 
      int m = 0)
{
   if (n >= a.length()) return 0;
   if (m >= b.length()) return 0;
   if (a[n] == b[m])
   {
      return cache(n+1, m+1) == -1 ? 1 + lcs_top_down_helper(a, b, cache, n+1, m+1) : 1 + cache(n+1, m+1);
   }
   auto left  = cache(n+1, m) == -1 ? lcs_top_down_helper(a, b, cache, n+1, m) : cache(n+1, m);
   auto right = cache(n, m+1) == -1 ? lcs_top_down_helper(a, b, cache, n, m+1) : cache(n, m+1);
   return std::max(left, right);
}

int lcs_top_down(const std::string& a, const std::string& b)
{
   const auto a_length = a.length();
   const auto b_length = b.length();

   Vector2D cache(a_length + 1, b_length + 1, -1);

   return lcs_top_down_helper(a, b, cache, 0, 0);
}

TEST(LongestCommonSubsequence, TopDown)
{
   EXPECT_EQ( lcs_top_down("ABCDGH", "AEDFHR"), 3 );
   EXPECT_EQ( lcs_top_down("AGGTAB", "GXTXAZB"), 4 );
}

TEST(LongestCommonSubsequence, BottomUp)
{
   EXPECT_EQ( lcs_bottom_up("ABCDGH", "AEDFHR"), 3 );
   EXPECT_EQ( lcs_bottom_up("AGGTAB", "GXTXAZB"), 4 );
}

TEST(LongestCommonSubsequence, Recursive)
{
   EXPECT_EQ( lcs_recursive("ABCDGH", "AEDFHR"), 3 );
   EXPECT_EQ( lcs_recursive("AGGTAB", "GXTXAZB"), 4 );
}

/**
 * https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/
 *
 * Problem Statement: Given two sequences, find the length of longest subsequence present in both of them. A subsequence is a sequence that appears in the same relative order, but not necessarily contiguous. For example, “abc”, “abg”, “bdf”, “aeg”, ‘”acefg”, .. etc are subsequences of “abcdefg”.
 */
int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
