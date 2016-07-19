#include <iostream>
#include <stdio.h>
#include <fstream>
#include <assert.h>
#include <cstdlib>
using namespace std;

int pc, ac, sp, ir, tir, zero, add1, sub1, Amask, Bmask;
int A, B, C, D, E, F;
int Alatch, Blatch, MAR, MBR;
int AMUX, ALU, shifter, Abus, Bbus, Cbus;
int addressOut, data_in, data_out;
int address;
int m[4095];
char inst[4];
int c = 0;

void LODD (int address)
{
    ac=m[address];
}

void LOCO (int address)
{
    if(0<=address&&address<=4095)
       ac=address;
}

void LODL (int address)
{
    ac=m[sp+address];
}

void STOD (int address)
{
m[address]=ac;
}

void SUBD (int address)
{
    ac=ac-m[address];
}

void STOL (int address)
{
    m[address+sp]=ac;
}

void SUBL (int address)
{
    ac=ac-m[sp-address];
}

void SWAP (int address)
{
    int tmp;
    tmp=ac;
    ac=sp;
    sp=tmp;
}

void STOP (int address)
{
    cout <<"The sum of three numbers is : "<< m[1004];
    exit(0);
}

void ADDD (int address)
{
ac=ac+m[address];
}

void ADDL (int address)
{
    ac=ac+m[sp+address];
}

void JPOS (int address)
{
    if(ac>=0)
    pc=address;
}

void JZER (int address)
{
    if(ac=0)
    pc=address;
}

void JUMP (int address)
{
    pc=address;
}

void JNEG (int address)
{
    if(ac<0)
    pc=address;
}

void JNZE (int address)
{
    if(ac!=0)
    pc=address;
}

void PSHI (int address)
{
    sp=sp-1;
    m[sp]=m[ac];
}

void I (int address)
{
    m[ac]=m[sp];
    sp=sp+1;
}

void PUSH (int address)
{
    sp=sp-1;
    m[sp]=ac;
}

void POP (int address)
{
    ac=m[sp];
    sp=sp+1;
}

void CALL (int address)
{
    sp=sp-1;
    m[sp]=pc;
    pc=address;
}

void RETN (int address)
{
    pc=m[sp];
    sp=sp+1;
}

void INSP (int address)
{
    if(0<=address&&address<=255)
    sp=sp+address;
}

void DESP (int address)
{
    if(0<=address&&address<=255)
    sp=sp-address;
}


int main()
{
    ifstream fin;
    ofstream fout;

    //open input file
    fin.open("Instructions.txt");
    cout<<"the file has been opened"<<endl;
    assert (!fin.fail());
}
