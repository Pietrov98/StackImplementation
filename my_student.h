
#ifndef MY_STUDENT_ADFGRETW_H
#define MY_STUDENT_ADFGRETW_H

struct MY_STUDENT
{
	char *nazwisko;
	size_t length_nazwisko;
	int rok;
	enum KIERUNEK_STUD kierunek;
	
};

enum KIERUNEK_STUD
{
	INFORMATYKA,
	MATEMATYKA,
	FIZYKA
};
void *MY_STUDENT_Init(char *lastname, int year, int course);
void MY_STUDENT_Free(void *ptr);
void *MY_STUDENT_Push(char *lastname, int year, int course);
void MY_STUDENT_Print(void *ptr);
int MY_STUDENT_SearchLastName(void *pCurData, void *pSearchData);
int MY_STUDENT_SearchYear(void *pCurData, void *pSearchData);
int MY_STUDENT_SearchCourse(void *pCurData, void *pSearchData);
void MY_STUDENT_Save(void *ptr, FILE *pf);
void *MY_STUDENT_Read(void *ptr, FILE *pf, _int64 *file_desc);


#endif