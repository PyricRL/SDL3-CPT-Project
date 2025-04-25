import csv
import sys

import globalVariables
import bubbleSort
import mergeSort
import insertionSort

globalVariables.inputFile = f"../../Data/{sys.argv[1]}"
globalVariables.outputFile = f"../../Data/{sys.argv[2]}"

tempArray = []

with open(globalVariables.inputFile, "r") as readfile:      # Open file and write to each new line
    datareader = csv.DictReader(readfile)
    for col in datareader:
        length = int(col["Length"])                     # Check for col with "Length" tag
        for i in range(length):
            temp = int(col[f"A{i}"])                    # Check for col with "A#" tag
            tempArray.append(temp)
    
        if col["Type"] == "bubble":                     # Check for sort type
            bubbleSort.bubbleSort(tempArray, length)
        elif col["Type"] == "merge":
            mergeSort.mergeSort(tempArray, 0, length - 1)
        elif col["Type"] == "insertion":
            insertionSort.insertionSort(tempArray, length)
        elif col["Type"] == "quick":
            pass
        elif col["Type"] == "selection":
            pass
        else:
            print("Sort not available")