#include <iostream>
#include <string>
#include <vector>
#include "CRegister.h"
#include "CMemory.h"
class CInstruction;

enum InstructionCode
{
    ADD, ADDI, SUB, SUBI, MUL, MULI, DIV, DIVI,
    AND, ANDI, OR, ORI, NOT, NOTI,
    LD, LDI, ST, STI, BRZ, BRNZ, BRG, BRL, JMP
};

class CInstruction
{
public:
    // set sthe variable for the instruction
    int InstCode;
    int Reg1; // the index of the register
    int Reg2;
    int Reg3;
    
    // some state variable
    std::string Target;            // the target choice: branch or loop
    int TargetA;                // the address of the target which is corresponding to the Index of the pipeline
    std::string JumpTarget;        // the target will be jump
    bool Jump = false;            // the instrction is jump or not
    bool JumpToTarget  = false; // the choise for the result of instruction
    int JumpTargetA;            // the address of the jump
    int Stage;                    // reflect the stage of instrction [1,2,3,4,5] . 0--not in the pipeline
    int Cycles;                    // the number of the cycle for this instruction
    int Index;                    // the index in the instruction set
    bool hit = true;            // hit or miss the cache
    bool ErrorOccur = false;    // Error: like a division by 0
public:
    CInstruction(){ }
    ~CInstruction() { }
    //constructor for XXX
    CInstruction(int c, int r1, int r2, int r3)
    {
        InstCode = c; Reg1 = r1; Reg2 = r2; Reg3 = r3;
    }
    //constructor for XX
    CInstruction(int c, int r1, int r2)
    {
        InstCode = c; Reg1 = r1; Reg2 = r2;
    }
    //constructor for BRX
    CInstruction(int c, int r1)
    {
        InstCode = c; Reg1 = r1;
    }
    //constructor for JMP
    CInstruction(int c)
    {
        InstCode = c;
    }
    
    //Set the target and state value
    void setStage(int n){ Stage = n; }
    void setCycles(int c) { Cycles = c; }
    void setJump(bool j) { Jump = j; }
    void setTargetAddress(int addres){ TargetA = addres; }
    void setIndex(int idx) { Index = idx; }
    void setTarget(std::string t, int addr) { Target = t; TargetA = addr;}
    void setJumpTarget(std::string t) { JumpTarget = t;}
    
    // 5 stage
    int Process(std::vector<CRegister> &Register,std::vector<CMemory> &Memory, std::vector<CMemory> &Cache)
    {
 //       std::cout << "-------------------------------------------------------------------" << std::endl;
  //      std::cout << "Before processing, the register is :     ";
 //       Register[Reg1].Print();
        // initilal
        int c = 1;
        // operate the value from the cache or memory, judge the miss or hit
        // cache is direct map and write back , write allocate
        
        switch (InstCode)
        {
                //////////////////////////////LD ST: miss cost 10 cycles/////////////////////////////////////////////
            case LD:
            {
                int n = Cache.size();
                int idx1 = Register[Reg2].GetValue();
                int idx2 = idx1 % n;
  //              std::cout << "Load the value from cache to register\n";
 //               Register[Reg1].Print();
  //              Cache[idx2].Print();
                if (Cache[idx2].isEmpty() == true)//miss: index is not equal or cache is empty
                {
   //                 std::cout << "Miss: a dealy for 10 cycles" << std::endl;
                    // copy memory to the cache
                    Cache[idx2] = Memory[idx1];
                    Cache[idx2].setEmpty(false);
                    // set the value
                    Register[Reg1].SetValue(Cache[idx2].GetValue());
                    c = c + 10;
                    hit = false;
                }
                else if (Cache[idx2].GetIdx() != idx1)
                {
  //                  std::cout << "Miss: a dealy for 10 cycles" << std::endl;
 //                   // write the cache to the memory
                    Memory[Cache[idx2].GetIdx()] = Cache[idx2];
                    // copy memory to the cache
                    Cache[idx2] = Memory[idx1];
                    Cache[idx2].setEmpty(false);
                    // set the value
                    Register[Reg1].SetValue(Cache[idx2].GetValue());
                    c = 10;
                    hit = false;
                }
                else//hit
                {
                    Register[Reg1].SetValue(Cache[idx2].GetValue());
                    hit = true;
                }
 //               Cache[idx2].Print();
                break;
            }
            case ST:
            {
                int n = Cache.size();
                int idx1 = Register[Reg2].GetValue();
                int idx2 = idx1 % n;
  //              std::cout << "Write the value from register to cache.\n";
   //             Register[Reg1].Print();
    //            Cache[idx2].Print();
                if (Cache[idx2].isEmpty() == true)//hit
                {
                    // write the value in the cache
                    Cache[idx2].SetIdx(idx1);
                    Cache[idx2].SetValue(Register[Reg1].GetValue());
                    Cache[idx2].setEmpty(false);
                    hit = true;
                }
                else if (Cache[idx2].GetIdx() == idx1)//hit
                {
                    Cache[idx2].SetValue(Register[Reg1].GetValue());
                    Cache[idx2].setEmpty(false);
                    hit = true;
                }
                else//miss
                {
   //                 Register[Reg1].Print();
    //                std::cout << "Miss: a dealy for 10 cycles" << std::endl;
                    // write the cache to the memory
                    Memory[Cache[idx2].GetIdx()] = Cache[idx2];
                    //  write the value in the cache
                    Cache[idx2].SetIdx(idx1);
                    Cache[idx2].SetValue(Register[Reg1].GetValue());
                    Cache[idx2].setEmpty(false);
                    c = c + 10;
                    hit = false;
                }
    //            Cache[idx2].Print();
                break;
            }
                //////////////////////////////Using data forwarding, no delay/////////////////////////////////////////////
            case ADD:
                Register[Reg1].SetValue(Register[Reg2].GetValue() + Register[Reg3].GetValue());
                break;
            case ADDI:
                Register[Reg1].SetValue(Register[Reg2].GetValue() + Reg3);
                break;
            case SUB:
                Register[Reg1].SetValue(Register[Reg2].GetValue() - Register[Reg3].GetValue());
                break;
            case SUBI:
                Register[Reg1].SetValue(Register[Reg2].GetValue() - Reg3);
                break;
            case MUL:
                Register[Reg1].SetValue(Register[Reg2].GetValue() * Register[Reg3].GetValue());
                break;
            case MULI:
                Register[Reg1].SetValue(Register[Reg2].GetValue() * Reg3);
                break;
            case DIV:
                if (Register[Reg3].GetValue() != 0)
                {
                    Register[Reg1].SetValue(Register[Reg2].GetValue() / Register[Reg3].GetValue());
                }
                else
                {
                    ErrorOccur = true;
                    std::cout << "ErrorOccur: A division by 0. The Program is terminating." << std::endl;
                }
                break;
            case DIVI:
                if (Register[Reg3].GetValue() != 0)
                {
                    Register[Reg1].SetValue(Register[Reg2].GetValue() / Reg3);
                }
                else
                {
                    ErrorOccur = true;
                    std::cout << "ErrorOccur: A division by 0. The Program is terminating." << std::endl;
                }
                break;
            case AND:
                Register[Reg1].SetValue(Register[Reg2].GetValue() & Register[Reg3].GetValue());
                break;
            case ANDI:
                Register[Reg1].SetValue(Register[Reg2].GetValue() & Reg3);
                break;
            case OR:
                Register[Reg1].SetValue(Register[Reg2].GetValue() | Register[Reg3].GetValue());
                break;
            case ORI:
                Register[Reg1].SetValue(Register[Reg2].GetValue() | Reg3);
                break;
            case NOT:
                Register[Reg1].SetValue(!Register[Reg2].GetValue());
                break;
            case NOTI:
                Register[Reg1].SetValue(!Reg3);
                break;
                //////////////////////////////Branch case 1 cycle delay/////////////////////////////////////////////
            case BRZ:
                if (Register[Reg1].GetValue() == 0)
                {
                    JumpToTarget = true;
                    c = c + 1;
    //                std::cout << "Take branch cost 1 cycle delay" << std::endl;
                }
                else
                {
                    JumpToTarget = false;
                }
                break;
            case BRNZ:
                if (Register[Reg1].GetValue() != 0)
                {
                    JumpToTarget = true;
                    c = c + 1;
    //                std::cout << "Take branch cost 1 cycle delay." << std::endl;
                }
                else
                {
                    JumpToTarget = false;
                }
                break;
            case BRG:
                if (Register[Reg1].GetValue() > 0)
                {
                    JumpToTarget = true;
                    c = c + 1;
   //                 std::cout << "Take branch cost 1 cycle delay" << std::endl;
                }
                else
                {
                    JumpToTarget = false;
                }
                break;
            case BRL:
                if (Register[Reg1].GetValue() < 0)
                {
                    JumpToTarget = true;
                    c = c + 1;
  //                  std::cout << "Take branch cost 1 cycle delay" << std::endl;
                }
                else
                {
                    JumpToTarget = false;
                }
                break;
            case JMP:
                JumpToTarget = true;
                break;
        }

        //print the register 1
 //       std::cout << "After processing, the register update:     ";
  //      Register[Reg1].Print();
  //     std::cout << "-------------------------------------------------------------------"<<std::endl;
        // return the cylces;

        return c;
    }
    
};
#pragma once

