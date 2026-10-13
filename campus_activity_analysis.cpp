/*
 * Course: COEN 2220 - Programming 2
 * Name: Mario A. Marrero Colón
 * Lab: Lab 8 - Big-O / Time Complexity
 * Description: Resolved code for time-complexity analysis
 * Due date: Oct/12/2026
 */

#include <iostream>
using namespace std;

/* Returns the ID stored at a valid position already known by the caller. */
int getActivityIdAt(const int activityIds[], int activityIndex)
{
    return activityIds[activityIndex]; // Read one known array position.
}

/* Returns how many activities have an active status. */
int countActiveActivities(const bool isActive[], int activityCount)
{
    int activeCount = 0;

    for (int index = 0; index < activityCount; index++)
    {
        if (isActive[index])
        {
            activeCount++;
        }
    }

    return activeCount;
}

/*
 * Returns how many middle IDs binary search compares before finding targetId.
 * Precondition: activityIds is sorted in ascending order and contains targetId.
 */
int countBinaryComparisons(const int activityIds[], int activityCount, int targetId)
{
    int first = 0;
    int last = activityCount - 1;
    int comparisons = 0;

    while (first <= last)
    {
        int middle = (first + last) / 2;
        comparisons++;

        if (activityIds[middle] == targetId)
        {
            break;
        }
        else if (activityIds[middle] < targetId)
        {
            first = middle + 1;
        }
        else
        {
            last = middle - 1;
        }
    }

    return comparisons;
}

/* Returns how many times a positive count can be reduced by half before reaching 1. */
int countHalvingSteps(int itemCount)
{
    int steps = 0;

    while (itemCount > 1)
    {
        itemCount = itemCount / 2; // Remove approximately half of the remaining items.
        steps++;
    }

    return steps;
}

/* Returns the number of distinct activity pairs visited by two nested loops. */
int countPossiblePairs(int activityCount)
{
    int pairCount = 0;

    for (int first = 0; first < activityCount; first++)
    {
        for (int second = first + 1; second < activityCount; second++)
        {
            pairCount++; // One distinct pair would be compared here.
        }
    }

    return pairCount;
}

int main()
{
    // These activity IDs are sorted so binary search is valid.
    int activityIds[] = {101, 104, 108, 115, 130, 136, 140, 155};
    bool isActive[] = {true, false, true, true, false, false, true, false};
    int activityCount = 8;

    cout << "Activity at index 2: "
         << getActivityIdAt(activityIds, 2) << endl;
    cout << "Active activities: "
         << countActiveActivities(isActive, activityCount) << endl;
    cout << "Binary comparisons for 140: "
         << countBinaryComparisons(activityIds, activityCount, 140) << endl;
    cout << "Halving steps for 8: " << countHalvingSteps(8) << endl;
    cout << "Halving steps for 16: " << countHalvingSteps(16) << endl;
    cout << "Halving steps for 32: " << countHalvingSteps(32) << endl;
    cout << "Possible pairs for 4 activities: " << countPossiblePairs(4) << endl;
    cout << "Possible pairs for 8 activities: " << countPossiblePairs(8) << endl;

    return 0;
}

/*
 * Analysis Answers
 *
 * C1 — Direct access
 * Answer: For getActivityIdAt, n represents the number of activities, represented by operation:
 * int getActivityIdAt(const int activityIds[], int activityIndex)
 *   {
 *     return activityIds[activityIndex]; // Read one known array position.
 *   }
 * Classified as O(1)
 *
 * C2 — Count active activities
 * Answer: For countActiveActivities, n represents the active activity count, represented by:
 *   int countActiveActivities(const bool isActive[], int activityCount)
 *   {
 *      int activeCount = 0;
 *
 *      for (int index = 0; index < activityCount; index++)
 *      {
 *          if (isActive[index])
 *          {
 *              activeCount++;
 *          }
 *      }
 *
 *      return activeCount;
 *  }
 * Classified as O(n)

 * C3 — Binary search
 * Answer: For countBinaryComparisons, n represents the number of comparisons, represented by:
 *int countBinaryComparisons(const int activityIds[], int activityCount, int targetId)
 *    {
 *        int first = 0;
 *        int last = activityCount - 1;
 *        int comparisons = 0;
 *    
 *        while (first <= last)
 *        {
 *            int middle = (first + last) / 2;
 *            comparisons++;
 *    
 *            if (activityIds[middle] == targetId)
 *            {
 *                break;
 *            }
 *            else if (activityIds[middle] < targetId)
 *            {
 *                first = middle + 1;
 *            }
 *            else
 *            {
 *                last = middle - 1;
 *            }
 *        }
 *    
 *        return comparisons;
 *    } 
 *  Classified as O(log n)
 * C4 — Halving steps
 * Answer: Starting with itemCount = 16, its values are 16 -> 8 -> 4 -> 2 -> 1,
 * so the loop runs 4 times. The repeated operation is itemCount = itemCount / 2.
 * Starting with 32 gives 32 -> 16 -> 8 -> 4 -> 2 -> 1, or 5 steps. Doubling
 * the input adds one step because each iteration halves the remaining count.
 * Classified as O(log n)
 * C5 — Distinct pairs
 * Answer: In countPossiblePairs, the loop begins with first + 1 to only count later activities, so it avoids pairing an activity with itself or counting the same pair in reverse order.
 * If the loop started at 0, it would count each pair twice and include self pairs.
 * Classified as O(n^2)
 *
 * C6 — Compare the observed patterns
 * Answer: Direct access returns 108 with one indexed read, so its work stays
 * constant as the array grows: O(1). 
 * Counting active activities checks all 8 entries and finds 4 active ones; its work grows with the number of entries: O(n). 
 * Halving inputs of 8, 16, and 32 takes 3, 4, and 5 steps; doubling the input adds one step, showing logarithmic growth: O(log n). 
 * Pair counts are 6 for 4 activities and 28 for 8, following n(n - 1) / 2 and growing quadratically: O(n^2). 
 * The code's loops explain these growth patterns; the output gives examples of them.
 * C7 — Sorting decision
 * Answer: For an unsorted list with only one or a few searches, I would use linear
 * search to checks entries directly
 * If the same data will be searched many times, sorting it once costs
 * O(n log n), after which each binary search costs O(log n). Over enough
 * searches, this is less work than repeatedly scanning the unsorted list.
 * Binary search requires sorted data, so if the original order must be kept,
 * sort a copy or a separate index.
 *
 */