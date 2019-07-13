#include "gtest/gtest.h"

#include <cstdlib>
#include <string>

int lcs_recursive(const std::string& a, const std::string& b, int n = 0, int m = 0)
{
   if (n >= a.length()) return 0;
   if (m >= b.length()) return 0;
   if (a[n] == b[m]) return 1 + lcs_recursive(a, b, n+1, m+1);
   auto left  = lcs_recursive( a, b, n+1, m );
   auto right = lcs_recursive( a, b, n, m+1 );
   return std::max(left, right);
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
