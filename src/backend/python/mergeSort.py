import csv
import time

import globalVariables

label = f"merge"

output = []

# This code was taken from geeks for geeks at:
# https://www.geeksforgeeks.org/merge-sort/?utm_source=geeksforgeeks&utm_medium=gfgcontent_shm&utm_campaign=shm
# With some modifications made to fit this use case
def merge(array, left, mid, right):
    n1 = mid - left + 1
    n2 = right - mid

    # Create temp arrays
    L = [0] * n1
    R = [0] * n2

    # Copy data to temp arrays L[] and R[]
    for i in range(n1):
        L[i] = array[left + i]
    for j in range(n2):
        R[j] = array[mid + 1 + j]

    i = 0  # Initial index of first subarray
    j = 0  # Initial index of second subarray
    k = left  # Initial index of merged subarray

    # Merge the temp arrays back
    # into arr[left..right]
    while i < n1 and j < n2:
        if L[i] <= R[j]:
            array[k] = L[i]
            i += 1
        else:
            array[k] = R[j]
            j += 1
        k += 1

    # Copy the remaining elements of L[],
    # if there are any
    while i < n1:
        array[k] = L[i]
        i += 1
        k += 1

    # Copy the remaining elements of R[], 
    # if there are any
    while j < n2:
        array[k] = R[j]
        j += 1
        k += 1
    
    globalVariables.sortTime = time.perf_counter() - startTime
    Time = f"{globalVariables.sortTime:.14f}"
    globalVariables.addDataToOutput(array, Time, label, output)

# This code was taken from geeks for geeks at:
# https://www.geeksforgeeks.org/merge-sort/?utm_source=geeksforgeeks&utm_medium=gfgcontent_shm&utm_campaign=shm
# With some modifications made to fit this use case
def mergeSort(array, left, right):
    global startTime
    if left == 0 and right == len(array) - 1:
        startTime = time.perf_counter()
        globalVariables.createHeaders(array, output)
        
    if left < right:
        mid = (left + right) // 2

        mergeSort(array, left, mid)
        mergeSort(array, mid + 1, right)
        merge(array, left, mid, right)

    if left == 0 and right == len(array) - 1:
        globalVariables.sortTime = time.perf_counter() - startTime
        Time = f"{globalVariables.sortTime:.14f}"
        globalVariables.addDataToOutput(array, Time, label, output)

    with open(globalVariables.outputFile, "w", newline='') as file:
        datawriter = csv.writer(file)
        datawriter.writerows(output)        # Write rows to ouput file