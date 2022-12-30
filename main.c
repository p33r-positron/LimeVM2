#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "VM.c"

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		puts("Utilisation: limevm <imageDisque>");
		return 1;
	}

	#if defined(WIN32) || defined(_WIN32)
		system("cls");
	#else
		system("clear");
	#endif
	
	printf("\tLimeVM v2.0.1\r\n-----------------------------\r\n\r\n");

	FILE* image = NULL;

	image = fopen(argv[1], "r");

	if(image == NULL)
	{
		err(0x01);
		return 1;
	}

	exec(image);

	return 0;
}
