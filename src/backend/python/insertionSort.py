import csv
import time

import globalVariables

label = f"insertion"

output = []

def insertionSort(array, length):
    startTime = time.perf_counter()
    globalVariables.createHeaders(array, output)
    for i in range(1, length):
        key = array[i]
        j = i - 1

        while j >= 0 and array[j] > key:
            array[j + 1] = array[j]
            j -= 1

        array[j + 1] = key
        globalVariables.sortTime = time.perf_counter() - startTime
        Time = f"{globalVariables.sortTime:.14f}"
        globalVariables.addDataToOutput(array, Time, label, output)
    
    with open(globalVariables.outputFile, mode='w', newline='') as file:
        datawriter = csv.writer(file)
        datawriter.writerows(output)