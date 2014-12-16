#include <SDL.h>
#include <SDL_image.h>
#include "iostream"
#include <stdio.h>
#include <string>
#include <cmath>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#define W 160

//Screen dimension constants
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 480;

struct col {
	unsigned short R;
	unsigned short G;
	unsigned short B;
	unsigned short A;
};

struct point
{
	int allive;
	col color;
};


col c_black {200,200,255,255};
col c_white {50,50,255,255};
col c_point {100,255,0,255};

bool init();
bool loadMedia();
void close();
void pointer(int x, int y, col color);
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

void pointer (int x, int y, col color) {
    SDL_Rect fillRect = { x ,y,3,3};
    SDL_SetRenderDrawColor( gRenderer, color.R, color.G, color.B, color.A );
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
			srand(time(NULL));
			point field[W][W]={0};
   			point field2[W][W]={0};
   			for (int ix=0;ix<W;ix++){
      			for (int iy=0;iy<W;iy++){
        		field[ix][iy].allive = rand()%2*rand()%2;
        		field[ix][iy].color = c_black;
        		field2[ix][iy].color = c_black;
      			}
    		}

    		bool pause=0;
    		bool drawing=0;
    		int drx=0;
    		int dry=0;

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
					else if( e.type == SDL_KEYDOWN )
					{
						//Select surfaces based on key press
						switch( e.key.keysym.sym )
						{
							case SDLK_c:
							std::cout << "Cleared\n";
							for (int ix=0;ix<W;ix++){
      						for (int iy=0;iy<W;iy++){
				        		field2[ix][iy].allive = 0;
				        		field[ix][iy].allive = 0;//rand()%2*rand()%2;
				        		field[ix][iy].color = c_black;
				        		field2[ix][iy].color = c_black;
				      			}
				    		}
							break;

							case SDLK_r:
							std::cout << "Ranomized\n";
							srand(time(NULL));
							for (int ix=0;ix<W;ix++){
      						for (int iy=0;iy<W;iy++){
				        		field2[ix][iy].allive = rand()%2*rand()%2;
				        		//field[ix][iy].allive = rand()%2*rand()%2;
				        		field[ix][iy].color = c_black;
				        		field2[ix][iy].color = c_black;
				        		if (pause) {
				        			if (field2[ix][iy].allive) {
				        				field2[ix][iy].color = c_white;
				        				//field[ix][iy].color = c_white;
				        			}
				        		}
				      			}
				    		}
							break;

							case SDLK_p:
							if (!drawing){
							pause = !pause;
							if (pause == 0){
								std::cout << "Pause event released\n";
							}
							else{
								std::cout << "Game paused\n";
							}
							}
							else{
								std::cout << "Drawing must be OFF\n";
							}

							break;

							case SDLK_d:
							if (pause){
							drawing = !drawing;
							if (drawing == 0){
								std::cout << "Drawing OFF\n";
							}
							else{
								std::cout << "Drawing ON\n";
							}
							drx=W/2;
							dry=W/2;
							}
							else{
								std::cout << "Game must be paused\n";
							}

							break;

							case SDLK_SPACE:
							if (drawing){
								field2[drx][dry].allive = 1;
								field2[drx][dry].color = c_white;
							}
							break;

							case SDLK_RIGHT:
								drx++;
								if (drx >= W){
									drx=0;
								}
							break;
							case SDLK_LEFT:
							drx--;
								if (drx < 0){
									drx=W-1;
								}
							break;
							case SDLK_UP:
							dry--;
								if (dry < 0){
									dry=W-1;
								}
							break;
							case SDLK_DOWN:
							dry++;
								if (dry >= W){
									dry=0;
								}
							break;
							default:

							break;
						}
					}
				}

				if (!pause){
					for (int ix=0;ix<W;ix++) for (int iy=0; iy<W;iy++){
	      				int m = field[ix-1][iy-1].allive+field[ix][iy-1].allive+field[ix+1][iy-1].allive+field[ix-1][iy].allive+field[ix+1][iy].allive+field[ix-1][iy+1].allive+field[ix][iy+1].allive+field[ix+1][iy+1].allive;

	        		if (field[ix][iy].allive==0){
	        		if (m==3) { field2[ix][iy].allive=1;
	        					field2[ix][iy].color=c_white;}
	      			}
	      			else{
	       			if  ((m==2) || (m==3)){field2[ix][iy].allive=1;field2[ix][iy].color=c_white;} else { field2[ix][iy].allive=0;field2[ix][iy].color=c_black;}
	      			}
	      			}
      			}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 255 );
				SDL_RenderClear( gRenderer );
				//std::cout << field2[0][2].color.R;
				for (int ix=0;ix<W;ix++){
        			for (int iy=0;iy<W;iy++){
                            pointer(ix*3,iy*3,field2[ix][iy].color);
        			}
      			}

      			for (int ix=0;ix<W;ix++) for (int iy=0; iy<W;iy++){
					field[ix][iy].allive=field2[ix][iy].allive;
					field[ix][iy].color=field2[ix][iy].color;
					//field2[ix][iy].allive=0;
				}
				//Draw vertical line of yellow dots
                SDL_SetRenderDrawColor( gRenderer, c_point.R, c_point.G, c_point.B, c_point.A );

                SDL_RenderDrawPoint( gRenderer, drx*3, dry*3 );
                SDL_RenderDrawPoint( gRenderer, drx*3+2, dry*3 );
                SDL_RenderDrawPoint( gRenderer, drx*3+2, dry*3+2 );
                SDL_RenderDrawPoint( gRenderer, drx*3, dry*3+2 );
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
