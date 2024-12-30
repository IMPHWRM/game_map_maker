#include <stdio.h>
#include <stdlib.h>

int create_file(char* file_name,int lenght)
{
	FILE* file=fopen(file_name,"w");
	if(file==NULL)
	{
		printf("ERROR: can not create %s (look if the directorie is good)\n",file_name);
		return 1;
	}
	for(int i=0;i<lenght;i++)
	{
		for(int r=0;r<matris_size*matris_size;r++)
		{
			fputc(0,file);

			fputc(0X20,file);
		}
	}
	fclose(file);
	return 0;
}
int search_bloc_table(char* file_name,unsigned short bloc_table[matris_size][matris_size],int line)
{
	FILE* file=fopen(file_name,"r");
	if(file==NULL)
	{
		printf("ERROR: cannot open %s \n",file_name);
		return 1;
	}
	fseek(file,line*matris_size*matris_size*2,SEEK_SET);
	printf("search:\nfile_pos=%ld     line=%d\n",ftell(file),line);
	
	for(int i=0;i<matris_size;i++)
	{

		for(int r=0;r<matris_size;r++)
		{
			bloc_table[i][r]=fgetc(file)*0x100;
			bloc_table[i][r]+=fgetc(file);
		}
	}
	return 0;
	fclose(file);
}

int write_bloc_table(char* file_name,unsigned short bloc_table[matris_size][matris_size],int line)
{
	FILE* file=fopen(file_name,"r+");

	if(file==NULL)	printf("edeeded");
	fseek(file,line*matris_size*matris_size*2,SEEK_SET);
	printf("write:\nfile_pos=%ld    file=%d\n",ftell(file),line);
	
	for(int i=0;i<matris_size;i++)
	{
		for(int r=0;r<matris_size;r++)
		{
			fputc(bloc_table[i][r]/0X100*0X100,file);
			fputc(bloc_table[i][r],file);
		}
	}
	
	printf("write:\nfile_pos=%ld    file=%d\n",ftell(file),line);
	fclose(file);
	return 0;
}
