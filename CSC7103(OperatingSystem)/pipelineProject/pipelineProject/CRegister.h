#include <iostream>
class CRegister
{
private:
    int idx;
    int val;
public:
    
    CRegister()
    {
        idx = 0;
        val = 0;
    }
    CRegister(int ii, int vv)
    {
        idx = ii;
        val = vv;
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
    
    void Print()
    {
        std::cout << "R" << idx << " = " << val << std::endl;
        std::cout<<std::endl;
    }
};
#pragma once

