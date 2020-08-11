// inlcude the standard library
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

// include the self library
#include "CMemory.h"
#include "CRegister.h"
#include "CInstruction.h"
using namespace std;

// initialize the REGISTER, MEMORY, CACHE
vector<CRegister> Register(32);
vector<CMemory> Memory(10000);
vector<CMemory> Cache(256);

vector<CInstruction> Instructions(1000);

// Record
vector<string> InitRecord;
vector<string> MainCodeRecord;
vector<string> PrintRecord;

//regular expression
regex rx("[a-zA-Z|\\=|\\-|[\\]]+");
string fmt(" ");
regex rx1(":");
string fmt1("");
int string2int(string str)
{
    stringstream in(regex_replace(str, rx, fmt));
    int num;
    in >> num;
    return num;
}
// Lexical analysis the record
bool Initialization(vector<string> InitRecord)
{
    for (int i = 0; i < InitRecord.size(); i++)
    {
        string str = InitRecord[i];
        int pos = str.find("-");
        if (str[0] == 'R')// initialize Register
        {
            if (pos>0)
            {
                stringstream in(regex_replace(str, rx, fmt));
                int idx1, idx2, val;
                in >> idx1 >> idx2 >> val;
                for (int i = idx1; i <= idx2; i++)
                {
                    Register[i] = CRegister(i, val);
                }
            }
            else
            {
                stringstream in(regex_replace(str, rx, fmt));
                int idx, val;
                in >> idx >> val;
                Register[idx] = CRegister(idx, val);
            }
        }
        else// initialize Memory
        {
            if (pos > 0)
            {
                stringstream in(regex_replace(str, rx, fmt));
                int idx1, idx2, val;
                in >>idx1 >> idx2 >> val;
                for (int i = idx1; i <= idx2; i++)
                {
                    Memory[i] = CMemory(i, val);
                }
            }
            else
            {
                stringstream in(regex_replace(str, rx, fmt));
                int idx, val;
                in >> idx >> val;
                Memory[idx] = CMemory(idx, val);
            }
        }
    }
    return 1;
}

// Print the Register and Memory
bool Print(vector<string> PrintRecord)
{
    for (int i = 0; i < PrintRecord.size(); i++)
    {
        string str = PrintRecord[i];
        int pos = str.find("-");
        if (str[0] == 'R')// Print Register
        {
            
            if (pos>0)
            {
                stringstream in(regex_replace(str, rx, fmt));
                int idx1, idx2;
                in >> idx1 >> idx2;
                for (int i = idx1; i <= idx2; i++)
                {
                    Register[i].Print();
                }
            }
            else
            {
                int idx = string2int(str);
                Register[idx].Print();
            }
        }
        else// Print Memory
        {
            if (pos>0)
            {
                stringstream in(regex_replace(str, rx, fmt));
                int idx1, idx2;
                in >> idx1 >> idx2;
                for (int i = idx1; i <= idx2; i++)
                {
                    Memory[i].Print();
                }
            }
            else
            {
                int idx = string2int(str);
                Memory[idx].Print();
            }
        }
        
    }
    return 1;
}

// Procsses the Five Stage Piple

void StoreInst(string s1, string s2, string s3, string s4, int No)
{
    if (s1 == "ADD")
    {
        int idx1 = string2int(s2); int idx2 = string2int(s3); int idx3 = string2int(s4);
        Instructions[No] = CInstruction(0, idx1, idx2, idx3);
    }
    else if (s1 == "ADDI")
    {
        int idx1 = string2int(s2); int idx2 = string2int(s3); int val = string2int(s4);
        Instructions[No] = CInstruction(1, idx1, idx2, val);
    }
    else if (s1 == "SUB")
    {
        int idx1 = string2int(s2); int idx2 = string2int(s3); int idx3 = string2int(s4);
        Instructions[No] = CInstruction(2, idx1, idx2, idx3);
    }
    else if (s1 == "SUBI")
    {
        int idx1 = string2int(s2); int idx2 = string2int(s3); int val = string2int(s4);
        Instructions[No] = CInstruction(3, idx1, idx2, val);
    }
    else if (s1 == "MUL")
    {
        int idx1 = string2int(s2); int idx2 = string2int(s3); int idx3 = string2int(s4);
        Instructions[No] = CInstruction(4, idx1, idx2, idx3);
    }
    else if (s1 == "MULI")
    {
        int idx1 = string2int(s2); int idx2 = string2int(s3); int val = string2int(s4);
        Instructions[No] = CInstruction(5, idx1, idx2, val);
    }
    else if (s1 == "DIV")
    {
        int idx1 = string2int(s2); int idx2 = string2int(s3); int idx3 = string2int(s4);
        Instructions[No] = CInstruction(6, idx1, idx2, idx3);
    }
    else if (s1 == "DIVI")
    {
        int idx1 = string2int(s2); int idx2 = string2int(s3); int val = string2int(s4);
        
        Instructions[No] = CInstruction(7, idx1, idx2, val);
    }
    else if (s1 == "AND")
    {
        int idx1 = string2int(s2); int idx2 = string2int(s3); int idx3 = string2int(s4);
        Instructions[No] = CInstruction(8, idx1, idx2, idx3);
    }
    else if (s1 == "ANDI")
    {
        int idx1 = string2int(s2); int idx2 = string2int(s3); int val = string2int(s4);
        Instructions[No] = CInstruction(9, idx1, idx2, val);
    }
    else if (s1 == "OR")
    {
        int idx1 = string2int(s2); int idx2 = string2int(s3); int idx3 = string2int(s4);
        Instructions[No] = CInstruction(10, idx1, idx2, idx3);
    }
    else if (s1 == "ORI")
    {
        int idx1 = string2int(s2); int idx2 = string2int(s3); int val = string2int(s4);
        Instructions[No] = CInstruction(11, idx1, idx2, val);
    }
    else if (s1 == "NOT")
    {
        int idx1 = string2int(s2); int idx2 = string2int(s3);
        Instructions[No] = CInstruction(12, idx1, idx2);
    }
    else if (s1 == "NOTI")
    {
        int idx1 = string2int(s2); int val = string2int(s3);
        Instructions[No] = CInstruction(13, idx1, val);
    }
    else if (s1 == "LD")
    {
        int idx1 = string2int(s2); int idx2 = string2int(s3);
        Instructions[No] = CInstruction(14, idx1, idx2);
    }
    else if (s1 == "LDI")
    {
        int idx1 = string2int(s2); int idx2 = string2int(s3); int val = string2int(s4);
        Instructions[No] = CInstruction(15, idx1, idx2, val);
    }
    else if (s1 == "ST")
    {
        int idx1 = string2int(s2); int idx2 = string2int(s3);
        Instructions[No] = CInstruction(16, idx1, idx2);
    }
    else if (s1 == "STI")
    {
        int idx1 = string2int(s2); int idx2 = string2int(s3); int val = string2int(s4);
        Instructions[No] = CInstruction(17, idx1, idx2, val);
    }
    else if (s1 == "BRZ")
    {
        int idx1 = string2int(s2);
        Instructions[No] = CInstruction(18, idx1);
    }
    else if (s1 == "BRNZ")
    {
        int idx1 = string2int(s2);
        Instructions[No] = CInstruction(19, idx1);
    }
    else if (s1 == "BRG")
    {
        int idx1 = string2int(s2);
        Instructions[No] = CInstruction(20, idx1);
    }
    else if (s1 == "BRL")
    {
        int idx1 = string2int(s2);
        Instructions[No] = CInstruction(21, idx1);
    }
    else if (s1 == "JMY")
    {
        Instructions[No] = CInstruction(22);
    }
}

bool PreMainCode(vector<string> MainCodeRecord)
{
    // regular the Main code and store in the instruction set
    for (int i = 0; i < MainCodeRecord.size(); i++)
    {
        string str = MainCodeRecord[i];
        int pos1 = str.find("Loop");
        int pos2 = str.find("Branch");
        
        if (pos1 < 0 && pos2 < 0)
        {
            string s1, s2, s3, s4;
            stringstream in(str);
            in >> s1 >> s2 >> s3 >> s4;
            StoreInst(s1, s2, s3, s4, i);
        }
        else if (pos1 == 0 || pos2 == 0)
        {
            string s1, s2, s3, s4, s0;
            stringstream in(str);
            in >> s0 >> s1 >> s2 >>s3 >> s4;
            StoreInst(s1, s2, s3, s4, i);
            string str11 = regex_replace(s0, rx1, fmt1);
            Instructions[i].setTarget(regex_replace(s0, rx1, fmt1),i);
        }
        else
        {
            string s1, s2, s3, s4;
            stringstream in(str);
            in >> s1 >> s2 >> s3 >> s4;
            StoreInst(s1, s2, s3, s4, i);
            Instructions[i].setJumpTarget(s3);
            Instructions[i].setJump(1);
        }
    }
    
    // find the jump target address
    for (int i = 0; i < MainCodeRecord.size(); i++)
    {
        Instructions[i].setIndex(i);
        if (Instructions[i].Jump == true)
        {
            for (int j = 0; j < MainCodeRecord.size(); j++)
            {
                if (Instructions[i].JumpTarget == Instructions[j].Target)
                {
                    Instructions[i].JumpTargetA = Instructions[j].TargetA;
                }
            }
        }
    }
    
    return 1;
}


int Total_Cycle = 4;
int Total_inst = 0;
int Total_miss = 0;

void FiveStage()
{
    int Record_Count = MainCodeRecord.size();
    // prepare: copy the cache from the memory
    int count = 0;
    while (count < Record_Count)
    {
        Total_inst++;
//        cout << MainCodeRecord[count] << endl;
        int c = Instructions[count].Process(Register, Memory, Cache);
        if (Instructions[count].hit == false)
        {
            Total_miss = Total_miss + 1;
        }
        
        if (Instructions[count].ErrorOccur == true)
        {
            break;// meet the occur, the program terminate.
        }
        
        if (Instructions[count].JumpToTarget == true)
        {
            count = Instructions[count].JumpTargetA;
        }
        else
        {
            count++;
        }
        
        Total_Cycle = Total_Cycle + c;
    }
}

int main()
{
    // read the file to load the instruction
    string m_nFileName = "xxx.txt";
    ifstream m_nFp(m_nFileName);
    if (!m_nFp.is_open())
    {
        cout << m_nFileName << " can not open." << endl;
    }
    
    // read the record file per line
    string temp;
    while (getline(m_nFp, temp))
    {
        // read the Initialization
        if (temp[0] == 'R' || temp[0] == 'M')
        {
            InitRecord.push_back(temp);
        }
        else if (temp[0] == 'P')
        {
            PrintRecord.push_back(temp.substr(7));
        }
        else if (temp[0] == '/' && temp[1] == '/')
        {
            continue;
        }
        else
        {
            MainCodeRecord.push_back(temp);
        }
    }
    
    // Process the Initialization record
    if (!Initialization(InitRecord))
    {
        cout << "The initialization is failure" << endl;
    }
    
    // initialize the register and memory
    for (int i = 0; i < Register.size(); i++)
    {
        Register[i].SetIdx(i);
    }
    
    for (int i = 0; i < Memory.size(); i++)
    {
        Memory[i].SetIdx(i);
    }
    
    // Main code
    if (!PreMainCode(MainCodeRecord))
    {
        cout << "The Main code running is failure" << endl;
    }
    
    // 5 Stage Pipeline
    FiveStage();
    
    // write the cache data to the memory
    for (int i = 0; i < Cache.size(); i++)
    {
        if (Cache[i].isEmpty() == false)
        {
            Memory[Cache[i].GetIdx()] = CMemory(Cache[i].GetIdx(), Cache[i].GetValue());
        }
    }
    
    // Print the Register and the Memory
    if (!Print(PrintRecord))
    {
        cout << "The Print is failure" << endl;
    }
    
    // Print the statistical values
    std::cout << "-------------------------------------------------------------------"<<std::endl;

    cout << "Total number of instructions executed: " << Total_inst << endl;
    cout << "Total number of cycles: " << Total_Cycle << endl;
    cout << "Average of the cycle per instructions: " << (double)Total_Cycle/Total_inst << endl;
    cout << "Total number of misses: " << Total_miss << endl;
    cout << "Misses per instructions: " << (double)Total_miss / Total_inst << endl;
    
    // close the file
    m_nFp.close();
    return 0;
}

