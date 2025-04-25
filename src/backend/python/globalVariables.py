inputFile = 'NULL'
outputFile = 'NULL'

sortTime = 0.0

def createHeaders(array, outputArray):
    tempArray = []
    for i in range(len(array)):         # Append array tags to the temp list
        tempArray.append(f"A{i}")

    tempArray.append("Time")            # Append time tag to temp list
    tempArray.append("Type")            # Append type tag to temp list
    outputArray.append(tempArray)       # Append full temp list tags to main array

def addDataToOutput(sortArray, time, type, outputArray):
    temp = []
    for i in range(len(sortArray)):     # Append array items to the temp list
        temp.append(sortArray[i])
    temp.append(time)                   # Append time to temp list
    temp.append(type)                   # Append type to temp list
    outputArray.append(temp)            # Append full temp list to main array