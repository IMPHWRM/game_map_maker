#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
SDL_Texture* create_texture(SDL_Renderer* renderer,const char* file)
{
	SDL_Surface* image=IMG_Load(file);
	if(image==NULL)
	{
		printf("ERROR: can not open the png %s\n",file);
		return NULL;
	}
	SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer,image);
	

	SDL_FreeSurface(image);
	if(texture==NULL)
	{
		printf("ERROR: can not create texture %s\n",file);
		return NULL;
	}
	return texture;
}
