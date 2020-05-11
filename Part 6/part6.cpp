#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
SDL_Window* gWindow = NULL;
SDL_Surface* gSurface = NULL;
SDL_Surface* gMedia = NULL;

bool init();
SDL_Surface* loadSurface(std::string path);
bool loadMedia();
void close();

bool init()
{
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to load SDL.  SDL Error : %s", SDL_GetError());
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("Learn SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            printf("Unable to load Window. SDL Error : %s", SDL_GetError());
            success = false;
        }
        else
        {
            int imgFlags = IMG_INIT_PNG;
            if( !(IMG_Init(imgFlags) & imgFlags))
            {
                printf("SDL image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            }
            else
            {
                gSurface = SDL_GetWindowSurface(gWindow);
            }
            
        }
        
    }
    return success;
}

SDL_Surface* loadSurface(std::string path)
{
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gSurface->format,0);
        if(optimizedSurface == NULL)
        {
            printf("Unable to optimize image %s! SDL_Error: %s\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
        
    }
    return optimizedSurface;
    
}

void close()
{
    SDL_FreeSurface(gMedia);
    gMedia = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
}

int main(int args, char* argc[])
{
    if(!init())
    {
        printf("Failed to initialize SDL\n");
    }
    else
    {
        gMedia = loadSurface("loaded.png");
        if(gMedia == NULL)
        {
            printf("Failed to initialize surface\n");
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
                    else
                    {
                        SDL_BlitSurface(gMedia, NULL, gSurface, NULL);
                        SDL_UpdateWindowSurface(gWindow);
                    }
                    
                }
            }
        }
        
    }
    close();
    
}
