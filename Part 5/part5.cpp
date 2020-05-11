#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

bool init();
SDL_Surface* loadSurface(std::string path);
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
const int windowWidth = 480;
const int windowHeight = 720;
SDL_Surface* gSurface = NULL;
SDL_Surface* gStrecthedSurface = NULL;

bool init()
{
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf( "SDL Error : %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            printf("SDL Error : Cannot create the Window, %s\n", SDL_GetError());
            success = true;
        }
        else
        {
            gSurface = SDL_GetWindowSurface(gWindow);
        }
        
    }
    return success;
}

SDL_Surface* loadSurface(std::string path)
{
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if(loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gSurface->format,0);
        if(optimizedSurface == NULL)
        {
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);

    }
    return optimizedSurface;
    
}

bool loadMedia()
{
    bool success = true;
    gStrecthedSurface = loadSurface("hello_world.bmp");
    if(gStrecthedSurface == NULL)
    {
        printf("Unable to load image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    return success;
}

void close()
{
    SDL_FreeSurface(gStrecthedSurface);
    gStrecthedSurface = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_Quit();
}

int main(int argc, char* args[])
{
    if(!init())
    {
        printf("Failed to initialize Window\n");
    }
    else
    {
        if(!loadMedia())
        {
            printf("Failed to initialize media\n");
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
                SDL_Rect stretchRect;
                stretchRect.x = 0;
                stretchRect.y = 0;
                stretchRect.w = windowWidth;
                stretchRect.h = windowHeight;

                SDL_BlitScaled(gStrecthedSurface, NULL, gSurface, &stretchRect);
                SDL_UpdateWindowSurface(gWindow);
            }
        }
        
    }
    close();
    
}

