#include<SDL2/SDL.h>
#include<stdio.h>
int bloc_render(SDL_Renderer* renderer,SDL_Texture* texture[],SDL_Rect dst,unsigned short bloc_type)
{
	//printf("bloc_type=%d\n",bloc_type);
	SDL_Rect src={0,0,16,16};
	for(int i=0;i<bloc_type-(bloc_type/0X10*0x10);i++)
	{
		src.x+=16;
	}
	//printf("       src.x=%d\n",src.x);
	/*SDL_Texture* finale_texture=texture[bloc_type/0X10];
	printf("%d\n",bloc_type/0x10);
	SDL_RenderCopy(renderer,finale_texture,&src,&dst);
	return 0;*/
	//printf("%d\n",bloc_type/0x10);
	if(bloc_type/0X10>2)
	{
		SDL_RenderCopy(renderer,texture[0],NULL,&dst);
		return 1;
	}
	SDL_RenderCopy(renderer,texture[bloc_type/0x10],&src,&dst);
	return 0;
}
