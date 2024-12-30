#include <stdio.h>
#include <stdlib.h>
void search_string(char* file_name,char* string,int line)
{
	FILE* file=fopen(file_name,"r");
	if(file==NULL)
	{
		printf("cecceece\n");
		return;
	}
	for(int i=0;i<line;i++)
	{
		while(fgetc(file)!=10);
	}

	fscanf(file,"%s",string);
	fclose(file);
}
int get_file_lenght(char* file_name)
{
	FILE* file=fopen(file_name,"r");
	if(file==NULL)
	{
		printf("ERROR : can not open file\n");
		return-1;
	}
	int i=0;
	int caca;
	while (1)
	{
		caca=fgetc(file);
		if(caca==10)	i++;
		if(caca==-1)	break;
	}
	fclose(file);
	return i;
}
