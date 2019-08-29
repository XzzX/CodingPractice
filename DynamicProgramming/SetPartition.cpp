#include "gtest/gtest.h"

#include <cassert>
#include <cstdlib>
#include <string>

class SetPartitionRecursive
{
   public:
      using Set = std::vector<int>;
      int partition(const Set& set)
      {
         total = 0;
         for ( auto v : set )
            total += v;
         return partitionHelper(set);
      }
   private:
      int partitionHelper(const Set& set, const int idx=0, const int leftSum=0)
      {
         const auto length = set.size();
         if (idx >= length)
         {
            assert(leftSum <= total);
            return std::abs(leftSum - (total - leftSum));
         } else
         {
            return std::min( partitionHelper(set, idx+1, leftSum+set[idx]),
                  partitionHelper(set, idx+1, leftSum) );
         }
      }

      int total;
};

TEST(SetPartition, Recursive)
{
   SetPartitionRecursive partitioner;
   EXPECT_EQ( partitioner.partition( {1, 6, 11, 5} ), 1 );
   EXPECT_EQ( partitioner.partition( {1, 1, 2, 2} ), 0 );
   EXPECT_EQ( partitioner.partition( {1, 2, 3, 4} ), 0 );
   EXPECT_EQ( partitioner.partition( {10, 1, 1, 1} ), 7 );
}

/**
 * https://www.geeksforgeeks.org/partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum/
 *
 * Given a set of integers, the task is to divide it into two sets S1 and S2 such that the absolute difference between their sums is minimum. 
 **/
int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
