#ifndef MY_INTERFACE__H
#define MY_INTERFACE__H

enum MY_INTERF_EN
{
	INTERF_PUSH,
	INTERF_POP,
	INTERF_PRINT,
	INTERF_CLEAR,
	INTERF_FIND_LASTNAME,
	INTERF_SAVE,
	INTERF_READ,
	INTERF_STOP,
	INTERF_TOT
};

void push();
void pop();
void print();
void clear();
void menu();
void find();
void save();
void read();
#endif