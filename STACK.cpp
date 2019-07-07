// Adrian_Pietruszka.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "my_stack.h"
#include "my_messages.h"
#include "my_interface.h"
#include "my_student.h"
#include <stdlib.h>
#include <stdio.h>


int main(int argc, _TCHAR* argv[])
{
	MY_STACK_Init(MY_STUDENT_Free, MY_STUDENT_Save, MY_STUDENT_Read);
	size_t op = 8;
	do
	{
		menu();
		printf("\nYour choice: ");
		scanf_s("%d", &op);
		while (getchar() != '\n');
		switch (op)
		{
		case INTERF_PUSH: push();
			break;
		case INTERF_POP: pop();
			break;
		case INTERF_PRINT: print();
			break;
		case INTERF_CLEAR: clear();
			break;
		case INTERF_FIND_LASTNAME: find();
			break;
		case INTERF_SAVE: save();
			break;
		case INTERF_READ: read();
			break;
		case INTERF_STOP: clear();
			return 0;
		default:
				my_mess_fun(MY_MESS_WRONG_INPUT_DATA);
		};
	} while (op != INTERF_STOP);
	return 0;
}

