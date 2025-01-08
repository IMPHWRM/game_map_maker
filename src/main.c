//#include <stdio.h>
//#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define matris_size 50

#include "button.h"

#include "texture_function.c"
#include "file.c"
#include "button.c"
#include "file_bloc_table.c"
#include "bloc_render.c"
int main(int argc,char* argv[])
{
//start
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
//web creation
	printf("witch file do you want to open : ");
	char file_name[30];
	scanf("%s",file_name);
	unsigned short bloc_table[matris_size][matris_size];
	for(int i=0;i<matris_size;i++)
		for(int r=0;r<matris_size;r++)
			bloc_table[i][r]=0X0020;
	if(search_bloc_table(file_name,bloc_table,0)==1)
	{
		printf("Do you want to create this file y/n ?: ");
		char respond[3];
		scanf("%s",respond);
		// 121 mean "y"
		if(respond[0]==121)
		{
			create_file(file_name,4);
		}
		else
		{
			return 0;
		}
		search_bloc_table(file_name,bloc_table,0);
	}
//window creation
	SDL_Window* window=SDL_CreateWindow("map creator",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,500,500,SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if(window==NULL)
	{
		printf("ERROR : can not create window");
		return -1;
	}
	SDL_Renderer* renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	if(renderer==NULL)
	{
		printf("ERROR : can not create renderer");
		return -1;
	}
	int window_width,window_hight;
//button creation

	button button_table[16] = {
        { { 0, 0, 50, 50 }, "0" },
        { { 50, 0, 50, 50 }, "1" },
        { { 100, 0, 50, 50 }, "2" },
        { { 150, 0, 50, 50 }, "3" },
        { { 200, 0, 50, 50  }, "4" },
        { { 250, 0, 50, 50 }, "5" },
        { { 300, 0, 50, 50 }, "6" },
        { { 350, 0, 50, 50 }, "7" },
        { { 0, 50, 50, 50 }, "8" },
        { { 50, 50, 50, 50 }, "9" },
        { { 100, 50, 50, 50 }, "a" },
        { { 150, 50, 50, 50 }, "b" },
        { { 200, 50, 50, 50 }, "c" },
        { { 250, 50, 50, 50 }, "d" },
        { { 300, 50, 50, 50 }, "e" },
        { { 350, 50, 50, 50 }, "f" }
    };
//texture creation
	//bloc texture
	SDL_Texture* texture[get_file_lenght("assets/bloc.sgf")];
	char string[50];
	for(int i=0;i<get_file_lenght("assets/bloc.sgf");i++)
	{
		search_string("assets/bloc.sgf",string,i);
		texture[i]=create_texture(renderer,string);
	}
	/*
		
	texture[1]=create_texture(renderer,"assets/wood.png");
	texture[0]=create_texture(renderer,"assets/stone.png");
	texture[2]=create_texture(renderer,"assets/grass.png");
	*/

	//button texture
	//SDL_Texture* button_texture=create_texture(renderer,"assets/button.png");
	
//event var
	SDL_Event event;
	const Uint8* keystate=SDL_GetKeyboardState(NULL);
	Uint32 mouse_state;
	int mousex,mousey;



//some var
	int file_line=0;
	int state=0;
	int turn=0;
	int bloc_type=0;
	bool running=true;
	bool select=false;
	bool choose=true;
	bool test=true;
	while(running)
	{
		mouse_state=SDL_GetMouseState(&mousex, &mousey);
		SDL_GetWindowSize(window,&window_width,&window_hight);
//input
		//window event
		while(SDL_PollEvent(&event))
		{
			if(event.type==SDL_QUIT)
			{
				running=false;
			}
			if(event.type==SDL_MOUSEWHEEL)
			{
				if(event.wheel.y>0)
				{
					bloc_type+=0X10;
				}
				if(event.wheel.y<0)
				{
					bloc_type-=0X10;
				}
			}
			if(event.type==SDL_KEYDOWN)
			{
				if(event.key.keysym.scancode==SDL_SCANCODE_RIGHT)
				{
					file_line+=1;
					search_bloc_table(file_name,bloc_table,file_line);
				}
				if(event.key.keysym.scancode==SDL_SCANCODE_LEFT)
				{
					file_line-=1;
					search_bloc_table(file_name,bloc_table,file_line);
				}
				if(event.key.keysym.scancode==SDL_SCANCODE_DOWN)
				{
					file_line+=2;
					search_bloc_table(file_name,bloc_table,file_line);
				}
				if(event.key.keysym.scancode==SDL_SCANCODE_UP)
				{
					file_line-=2;
					search_bloc_table(file_name,bloc_table,file_line);
				}
			}
		}
		//shortcut
		if(keystate[SDL_SCANCODE_C])
		{
			select=false;
			choose=true;
		}
		if(keystate[SDL_SCANCODE_LCTRL] && keystate[SDL_SCANCODE_S] && test)
		{
			printf("csd");
			write_bloc_table(file_name,bloc_table,file_line);
			test=false;
		}
		if(!test && keystate[SDL_SCANCODE_P])
			test=true;
		//color event
		if(mouse_state==SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			for(int i=0;i<16;i++)
			{
				if(better_button_update(button_table[i].dst,mousex,mousey))
				{
					turn=i;
				}
			}
		}
		if(keystate[SDL_SCANCODE_1])
		{
			bloc_type=0;
		}
		if(keystate[SDL_SCANCODE_2])
		{
			bloc_type=0X10;
		}
		if(keystate[SDL_SCANCODE_3])
		{
			bloc_type=0X20;
		}
		//web event
		if(mouse_state == SDL_BUTTON(SDL_BUTTON_LEFT) && choose && mousex>window_width/2-window_hight/2 && mousex<window_width/2+window_hight/2 && mousey>=0&& mousey<window_hight && mouse_state == SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			bloc_table[mousey/(window_hight/matris_size)][(mousex-(window_width/2-window_hight/2))/(window_hight/matris_size)]=bloc_type+turn;
		}

//render
		SDL_SetRenderDrawColor(renderer,50,50,50,255);
		SDL_RenderClear(renderer);
		//web render
		SDL_Rect dst={window_width/2-window_hight/2,0,window_hight/matris_size,window_hight/matris_size};
		for(int i=0;i<matris_size;i++)
		{
			for(int r=0;r<matris_size;r++)
			{
				bloc_render(renderer,texture,dst,bloc_table[i][r]);
				dst.x+=window_hight/matris_size;
			}
			dst.x=window_width/2-window_hight/2;
			dst.y+=window_hight/matris_size;
		}
		
		//button for file gestion
		//button for bloc type
		for(int i=0;i<0x10;i++)
		{
			//printf("i=%d\n",i);
			//printf("bloc_type=%x\n",bloc_type);
			bloc_render(renderer,texture,button_table[i].dst,bloc_type+i);
		}
		//button for bloc mod
		SDL_RenderPresent(renderer);
	}
	for(int i=0;i<3;i++)
	{
		SDL_DestroyTexture(texture[i]);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	return 0;
}
