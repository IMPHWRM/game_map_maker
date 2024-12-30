#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

//return true if the mouse is in the button else it return false
bool button_update(SDL_Rect button,int x,int y)
{	
	return x>button.x && x<button.x+button.w*50 && y>button.y && y<button.y+button.h*50;
}
bool better_button_update(SDL_Rect button,int x,int y)
{	
	return x>button.x && x<button.x+button.w && y>button.y && y<button.y+button.h;
}


//use to render button whith the good size
void button_render (SDL_Renderer* renderer,SDL_Rect button_size,char* text,SDL_Texture* button_texture)
{
	SDL_Rect src1 = {0,0,10,10};
	SDL_Rect src2 = {10,0,10,10};
	SDL_Rect src3 = {20,0,10,10};

	SDL_Rect dst = {button_size.x,button_size.y,50,50};
	int a=0;
	if(button_texture==NULL)
	{
		a=1;
		SDL_Texture* button_texture=create_texture(renderer,"assets/button.png");
	}
	SDL_Rect dst2 = {button_size.x,button_size.y,button_size.w*50,button_size.h*50};
	SDL_RenderCopy(renderer,button_texture,&src1,&dst2);

	for (int i=0; i<button_size.h;i++)
	{
		for (int x=0; x<button_size.w;x++)
		{
			if (x==0)
			{
				SDL_RenderCopyEx(renderer, button_texture, &src3, &dst, 270, NULL, SDL_FLIP_NONE);
			} 
			if (x==button_size.w-1)
			{		
				SDL_RenderCopyEx(renderer, button_texture, &src3, &dst, 90, NULL, SDL_FLIP_NONE);	
			}
			if (i==0)
			{
				SDL_RenderCopy(renderer,button_texture,&src3,&dst);
				if (x==button_size.w-1)
				{
					SDL_RenderCopy(renderer,button_texture,&src2,&dst);
				}
			}
			if (i==button_size.h-1)
			{
				SDL_RenderCopyEx(renderer, button_texture, &src3, &dst, 180, NULL, SDL_FLIP_NONE);	
			}
			dst.x+=50;
		}
		dst.x=button_size.x;
		dst.y+=50;
	}

	TTF_Font* font = TTF_OpenFont("assets/font/font4.ttf", 15);
	if(font==NULL)
	{
		printf("ERROR: can not open font\n");
		return;
	}
	SDL_Color color={0,0,0,255};
	SDL_Surface* image=TTF_RenderText_Solid(font,text,color);
	if(image==NULL)
	{
		printf("ERROR: can not create text\n");
		return;
	}
	TTF_CloseFont(font);
	SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer,image);
	SDL_FreeSurface(image);

	SDL_Rect dst3=dst2;
	SDL_QueryTexture(texture,NULL,NULL,&dst3.w,&dst3.h);
	dst3.w*=5;
	dst3.h*=5;
	dst3.x+=(dst2.w-dst3.w)/2;
	dst3.y+=(dst2.h-dst3.h)/2-3;
	
	SDL_RenderCopy(renderer,texture,NULL,&dst3);
	if (a)
	{
		SDL_DestroyTexture(button_texture);
	}
	SDL_DestroyTexture(texture);
}
SDL_Rect return_dst(int x,int y,int w,int h)
{
	SDL_Rect dst={x,y,w,h};
	return dst;
}
