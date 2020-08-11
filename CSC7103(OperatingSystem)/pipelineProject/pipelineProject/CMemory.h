#include <iostream>
class CMemory
{
private:
    int idx;
    int val;
    bool empty;
public:
    CMemory()
    {
        idx = 0;
        val = 0;
        empty = true;
    }
    CMemory(int ii, int vv)
    {
        idx = ii;
        val = vv;
        empty = false;
    }
    
    int GetValue()
    {
        return val;
    }
    int GetIdx()
    {
        return idx;
    }
    
    void SetValue(int vv)
    {
        val = vv;
    }
    void SetIdx(int ii)
    {
        idx = ii;
    }
    
    bool isEmpty()
    {
        return empty;
    }
    void setEmpty(bool t)
    {
        empty = t;
    }
    
    void Print()
    {
        std::cout << "M[" << idx << "] = " << val << std::endl;
    }
};
#pragma once

