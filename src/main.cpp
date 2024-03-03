#include <random>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include "image.cpp"
#include "world.cpp"
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(void)
{
    srand(time(NULL));
 
    //Initialize SDL_ttf
    if(TTF_Init() == -1)
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    //success = false;
    }

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Window* win = SDL_CreateWindow("Q-learning", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == NULL) {
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
    
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL) {
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_Quit();
		return EXIT_FAILURE;
	}
    


    int sizeCell = 100;
    int xLenghtCells = SCREEN_WIDTH / sizeCell; 
    int yLenghtCells = SCREEN_HEIGHT / sizeCell;
    
    std::cout << "-------- Debug --------" << std::endl;
    std::cout << "Size x len: " << xLenghtCells << std::endl;
    std::cout << "Size y len: " << yLenghtCells << std::endl; 
    
    //std::vector<ImageCell> allCells;
    int sizeCells = xLenghtCells * yLenghtCells;
    //allCells.resize(sizeCells);
    std::cout << "sizeCells draw: " << sizeCells << std::endl;
    Enviroment world(win, ren, sizeCells);
    world.SetCellSize(sizeCell);
    /*
    ImageCell cellOpen(win, ren);
    cellOpen.loadTexture("resource/images/cellopen.bmp");
    cellOpen.setSize(sizeCell, sizeCell);
    cellOpen.setWindow(win);
    cellOpen.setRender(ren);

    for (int i = 0; i <= sizeCells; i++){
        allCells.push_back(cellOpen);
    }
    */
    //cellopen load
    //
	SDL_Surface* cellopen = SDL_LoadBMP("resource/images/cellopen.bmp");
	if (cellopen == NULL) {
		fprintf(stderr, "SDL_LoadBMP Error: %s\n", SDL_GetError());
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_Texture* texcellopen = SDL_CreateTextureFromSurface(ren, cellopen);
	if (texcellopen == NULL) {
		fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
		SDL_FreeSurface(cellopen);
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return EXIT_FAILURE;
	}
	SDL_FreeSurface(cellopen);

    //Main loop flag
    bool quit = false;
    //bool isLoad = false;
    //Event handler
    SDL_Event e;
    
    /*
    int x = 0;
    int y = 0;
    int positionHero = 0;
    int lastPosition = sizeCells - 1; 
    */
    //fill position
    /*
    for (int i = 0; i < sizeCells; i++){
        allCells[i].setPosition(x * sizeCell,y * sizeCell);
        allCells[i].setWindow(win);
        allCells[i].setRender(ren);
        allCells[i].setSize(sizeCell, sizeCell);
        (ran(rng) == 0) ? allCells[i].loadTexture("resource/images/cellobstacle.bmp"): allCells[i].loadTexture("resource/images/cellopen.bmp"); 
        x++;
        // x = 8
        if (x == xLenghtCells){
            x = 0;
            y++;
        }
        // y == 6
        if (y == yLenghtCells){
            y = 0;
        }
        //std::cout << "random: " << ran(rng) << std::endl;
    }
    */
    world.GenerateCells(xLenghtCells, yLenghtCells);
    //game loop
    while( !quit ){
        //allCells[positionHero].loadTexture("resource/images/cellhero.bmp");
        //allCells[lastPosition].loadTexture("resource/images/celldestination.bmp");
        SDL_RenderClear(ren);
        world.Render();
        //here SDL_RENDER_COPY
        //cellOpen.render();
/*
        for (int i = 0; i < sizeCells; i++){
            allCells[i].render();
        }*/
		SDL_RenderPresent(ren);
        
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 ){
            //User requests quit
            if( e.type == SDL_QUIT ){
                quit = true;
            }
            //If a key was pressed
              if( e.type == SDL_KEYDOWN ){

                               // ------------------------------------------
                    switch( e.key.keysym.sym ){
                        case SDLK_UP:
                            break;
                        case SDLK_DOWN:
                            break;
                        case SDLK_LEFT:
                            break;
                        case SDLK_RIGHT:
                            break;
                        case SDLK_r:
                            world.GenerateCells(xLenghtCells, yLenghtCells);
                            /*
                            for (int i = 0; i < sizeCells; i++){
                                allCells[i].setPosition(x * sizeCell,y * sizeCell);
                                allCells[i].setWindow(win);
                                allCells[i].setRender(ren);
                                allCells[i].setSize(sizeCell, sizeCell);
                                (ran(rng) == 0) ? allCells[i].loadTexture("resource/images/cellobstacle.bmp"): allCells[i].loadTexture("resource/images/cellopen.bmp"); 
                                x++;
                                // x = 8
                                if (x == xLenghtCells){
                                    x = 0;
                                    y++;
                                }
                                // y == 6
                                if (y == yLenghtCells){
                                    y = 0;
                                }*/
                                //std::cout << "random: " << ran(rng) << std::endl;
                            //}
                            break;
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                    }
                    
                }


            }

        }


	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return EXIT_SUCCESS;
}
