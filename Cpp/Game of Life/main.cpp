#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#define W 160

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct point
{
	int x;
	int y;
	int col;
};

bool init();
bool loadMedia();
void close();
void pointer(int x, int y, int col);
void game_init ();
void game_step ();
void game_draw ();

SDL_Texture* loadTexture( std::string path );//Loads individual image as texture
SDL_Window* gWindow = NULL;//The window we'll be rendering to
SDL_Renderer* gRenderer = NULL; //The window renderer

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Nothing to load
	return success;
}

void close()
{
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

void pointer (int x, int y, int col) {
    SDL_Rect fillRect = { x ,y,3,3};
    if (col == 1){
            SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 255 );
    }
    else{
        SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
    }
    SDL_RenderFillRect( gRenderer, &fillRect );
}




int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			int field[W][W]={0};
   			int field2[W][W]={0};
   			for (int ix=0;ix<W;ix++){
      			for (int iy=0;iy<W;iy++){
        		field[ix][iy]=rand()%2*rand()%2;
      			}
    		}



			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}
				

				for (int ix=0;ix<W;ix++) for (int iy=0; iy<W;iy++){
      				int m = field[ix-1][iy-1]+field[ix][iy-1]+field[ix+1][iy-1]+field[ix-1][iy]+field[ix+1][iy]+field[ix-1][iy+1]+field[ix][iy+1]+field[ix+1][iy+1];

        		if (field[ix][iy]==0){
        		if (m==3) { field2[ix][iy]=1;}
      			}
      			else{
       			if  ((m==2) || (m==3)){field2[ix][iy]=1;} else { field2[ix][iy]=0;}
      			}
      			}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				for (int ix=0;ix<W;ix++){
        			for (int iy=0;iy<W;iy++){
                            pointer(ix*3,iy*3,field2[ix][iy]);
        			}
      			}

      			for (int ix=0;ix<W;ix++) for (int iy=0; iy<W;iy++){
					field[ix][iy]=field2[ix][iy];
					//field2[ix][iy]=0;
				}

				//Update screen
				SDL_RenderPresent( gRenderer );
				
				//Sleep(1)
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
