#include <stdio.h>
#include <SDL2/SDL.h>

bool init();
bool loadMedia();

SDL_Window* gWindow;
SDL_Renderer* gRenderer;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

bool init()
{
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL Error %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            printf("Can not create window, %s\n",SDL_GetError());
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if(gRenderer == NULL)
            {
                printf("Can not create renderer, %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
            }
        }
        
    }
    return success;
    
}

bool loadMedia()
{
    bool success = true;
    return success;
}

void close()
{
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();

}

int main(int args, char* argc[])
{
    if(!init())
    {
        printf("Failed to initialize : ");
    }
    else
    {
        if(!loadMedia())
        {
            printf("Failed to load media : ");
        }
        else
        {
            bool quit = false;
            SDL_Event e;
            while(!quit)
            {
                while(SDL_PollEvent(&e) != 0)
                {
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }

                SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderClear(gRenderer);

                SDL_Rect fillRect = { WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
                SDL_SetRenderDrawColor(gRenderer, 0xff, 0x00, 0x00, 0xff);
                SDL_RenderFillRect(gRenderer, &fillRect);

                SDL_Rect outlineRect = {WINDOW_WIDTH / 6, WINDOW_HEIGHT / 6, WINDOW_WIDTH * 2/3, WINDOW_HEIGHT * 2/3};
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0xff, 0x00, 0xff);
                SDL_RenderDrawRect(gRenderer, &outlineRect);

                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderDrawLine(gRenderer, 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH , WINDOW_HEIGHT / 2);

                SDL_SetRenderDrawColor(gRenderer, 0x00, 0xff, 0xff, 0xff);
                for(int i = 0; i < WINDOW_HEIGHT; i += 4)
                {
                    SDL_RenderDrawPoint(gRenderer, WINDOW_WIDTH / 2, i);
                }

                SDL_RenderPresent(gRenderer);
            }
        }
        
    }
    close();
}