#include "stdafx.h"
#include "my_messages.h"
#include "my_stack.h"
#include "my_student.h"
#include "my_interface.h"
#include <stdlib.h>
#include <string.h>

const char *my_message_str_tab[] = {
	"Ememory allocation error",
	"WWrong input data",
	"UWrong Push",
	"FFile not opened",
	"IFile not created",
	"BWrong write to file",
	"RWrong read from file"
};

MY_DECISION my_mess_fun(enum MY_MESSAGES mess)
{
	MY_DECISION retval = MY_DECISION_CONTINUE;
	puts(my_message_str_tab[mess] + 1);


	if (my_message_str_tab[mess][0] == 'E')
		retval = MY_DECISION_BREAK;
	return retval;
}

void my_mess_error(MY_STUDENT *student, char * tab, __int64 * t, FILE * pf)
{
	if (pf)
	{
		fclose(pf);
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
	if (student)
	{
		if (student->nazwisko)
		{
			free(student->nazwisko);
			student->nazwisko = NULL;
		}
		free(student);
		student = NULL;
	}
	if (pf)
	{
		free(pf);
		pf = NULL;
	}

	MY_STACK_Free();
	exit(1);
}