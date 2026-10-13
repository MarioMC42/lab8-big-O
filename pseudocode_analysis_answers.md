PROCEDURE FindAndCountActive(sortedIds, isActive, count, targetId)
    first = 0
    last = count - 1
    found = false

    WHILE first <= last AND found is false
        middle = (first + last) / 2

        IF sortedIds[middle] = targetId
            found = true
        ELSE IF sortedIds[middle] < targetId
            first = middle + 1
        ELSE
            last = middle - 1
        END IF
    END WHILE

    activeCount = 0
    FOR index = 0 TO count - 1
        IF isActive[index] is true
            activeCount = activeCount + 1
        END IF
    END FOR

    RETURN found, activeCount
END PROCEDURE



PROCEDURE CountPotentialConflicts(startTimes, count)
    conflictCount = 0

    FOR first = 0 TO count - 1
        second = first + 1

        WHILE second < count
            IF startTimes[first] = startTimes[second]
                conflictCount = conflictCount + 1
            END IF

            second = second + 1
        END WHILE
    END FOR

    RETURN conflictCount
END PROCEDURE

# Lab 8 — Part D Pseudocode Analysis

## D1 — Search and scan pseudocode
**Answer:** The search loop is a binary search, so it will take O(log n) in the worst case, the activity tally checks each entry once, so it takes O(n). They run one after another so their costs are added since the linear tally dominates as n grows. Costs arent multiplied since that would happen with nested loops, which aren't used here.

## D2 — Potential-conflict pseudocode
**Answer:** The outer loop begins in first + 1 to count pairs once, skipping self pairs and reversed pairs. The representative operation is pairCount++ which executes once per pair. with two nested loops the pair count grows as n(n-1)/2, so the order is O(n²). Doubling count makes the work approach four times as many pair increments. In the sample,  4 activities give 6 pairs and 8 give 28; the ratio is not exactly four for these small values, but it trends toward four as count grows.

