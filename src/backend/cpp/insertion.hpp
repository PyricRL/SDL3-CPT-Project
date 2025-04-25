#pragma once

#include <vector>

void insertion(std::vector<int> data)
{
    for(int i=1;i<data.size();i++)
    {   
        int unsorted = data[i];
        int j=i-1;
        while(j >= 0 && data[j] > unsorted)
        {
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = unsorted;
    }
}