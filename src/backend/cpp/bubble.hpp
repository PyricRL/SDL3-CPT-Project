#pragma once

#include <vector>

void bubble(std::vector<int> data)
{
    if(data.size() > 0)
        for(int i=0;i<data.size()-1;i++)
        {
            for(int j=0;j<data.size()-i-1;j++)
            {
                if(data.at(j) > data.at(j+1))
                {
                    int temp = data.at(j);
                    data.at(j) = data.at(j+1);
                    data.at(j+1) = temp;
                }
            }
        }
}