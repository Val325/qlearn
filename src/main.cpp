#include <random>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <bits/stdc++.h>

#include "include/headers.hpp"
#include "image.cpp"
#include "world.cpp"
#include "agent.cpp"
#include "qlearn.cpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(void)
{
    srand(time(NULL));
 
    if(TTF_Init() == -1)
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
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

    int sizeCells = xLenghtCells * yLenghtCells;
    std::cout << "sizeCells draw: " << sizeCells << std::endl;
    Enviroment world(win, ren, sizeCells);
    agentAI player(0,0);
    agentAI endpoint(0,0);
    world.SetCellSize(sizeCell);

    //qlearning dataLearn(world, player);
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
    bool isStartGame = false;
    bool isGame = false;
    bool isStartQlearning = false;
    //bool isLoad = false;
    //Event handler
    SDL_Event e;
    world.GenerateCells(xLenghtCells, yLenghtCells);
   
    //game loop
    while( !quit ){

        SDL_RenderClear(ren);
        
        if (!isStartGame){
            player.setPosition(0, 0);
        }
        
            
        player.setConstraint(xLenghtCells, yLenghtCells);
        player.setWindow(win);
        player.setRender(ren);
        player.loadTexture("resource/images/cellhero.bmp");
        player.setSize(sizeCell,sizeCell);
        player.setGoal(700, 700);

        endpoint.setPosition(700, 500);
        endpoint.setConstraint(xLenghtCells, yLenghtCells);
        endpoint.setWindow(win);
        endpoint.setRender(ren);
        endpoint.loadTexture("resource/images/celldestination.bmp");
        endpoint.setSize(sizeCell,sizeCell);   
        qlearning qlear(&world, &player, xLenghtCells, yLenghtCells);
        
        if (player.checkCollision(endpoint.getPosition())){
            player.GetGoal();
            //std::cout << "get goal" << std::endl;
        }else{
            if (isStartQlearning){
                player.RandomDirectionMove(world);
            }
        }


        std::vector<ImageCell> CellsAll = world.getCells();
        ImageCell cellInsidePlayer;
        ImageCell cellNearbyPlayer;
        //SDL_Rect playerRect = player.getPosition();
        world.Render();
        endpoint.Render();
        player.Render();
        //here SDL_RENDER_COPY

        //cellOpen.render();

		SDL_RenderPresent(ren);
        
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 ){
            //User requests quit
            if( e.type == SDL_QUIT ){
                quit = true;
            }
            //If a key was pressed
              if( e.type == SDL_KEYDOWN ){
                    isStartGame = true;
                    switch( e.key.keysym.sym ){
                        case SDLK_UP:
                            if ((player.getYposition() - 1) >= 0){
                                cellNearbyPlayer = world.getCellPosition(player.getXposition(), player.getYposition() - 1);
                            }
                            if (!cellNearbyPlayer.getCollide()){ 
                                cellInsidePlayer = world.getCellPosition(player.getXposition(), player.getYposition());
                                //std::cout << "x: " << cellInsidePlayer.GetPositionGridX() << " y: " << cellInsidePlayer.GetPositionGridY() << std::endl;                            
                                if (isGame) player.MoveUp();
                            }
                            break;
                        case SDLK_DOWN:
                            /*
                            std::cout << "DOWN" << std::endl;                            
                            std::cout << "y: " << player.getYposition() << std::endl;
                            std::cout << "New y: " << player.getYposition() + 1 << std::endl;
                            std::cout << "yLenghtCells: " << yLenghtCells << std::endl;
                            */
                            if ((player.getYposition() + 1) >= yLenghtCells){
                                break;
                            }
                            cellNearbyPlayer = world.getCellPosition(player.getXposition(), player.getYposition() + 1);
                            if (!cellNearbyPlayer.getCollide()){                                
                                cellInsidePlayer = world.getCellPosition(player.getXposition(), player.getYposition());
                                //std::cout << "x: " << cellInsidePlayer.GetPositionGridX() << " y: " << cellInsidePlayer.GetPositionGridY() << std::endl;
                                if (isGame) player.MoveDown();
                            }
                            break;
                        case SDLK_LEFT:
                            //left cell
                            /*
                            std::cout << "LEFT" << std::endl;                            
                            std::cout << "x: " << player.getXposition() << std::endl;
                            std::cout << "New x: " << player.getXposition() - 1 << std::endl;
                            std::cout << "xLenghtCells: " << xLenghtCells << std::endl;
                            */
                            if ((player.getXposition() - 1) == -1){
                                break;
                            } 
                            cellNearbyPlayer = world.getCellPosition(player.getXposition() - 1, player.getYposition());
                            if (!cellNearbyPlayer.getCollide()){
                                cellInsidePlayer = world.getCellPosition(player.getXposition(), player.getYposition());
                                //std::cout << "x: " << cellInsidePlayer.GetPositionGridX() << " y: " << cellInsidePlayer.GetPositionGridY() << std::endl; 
                                if (isGame) player.MoveLeft();
                            }
                            break;
                        case SDLK_RIGHT:
                            //right cell
                            /*
                            std::cout << "RIGHT" << std::endl;                            
                            std::cout << "X: " << player.getXposition() << std::endl;
                            std::cout << "New X: " << player.getXposition() + 1 << std::endl;
                            std::cout << "XLenghtCells: " << xLenghtCells << std::endl;
                            */
                            if ((player.getXposition() + 1) >= xLenghtCells){
                                break;
                            } 
                            cellNearbyPlayer = world.getCellPosition(player.getXposition() + 1, player.getYposition());
                            if (!cellNearbyPlayer.getCollide()){
                                cellInsidePlayer = world.getCellPosition(player.getXposition(), player.getYposition());
                                //std::cout << "x: " << cellInsidePlayer.GetPositionGridX() << " y: " << cellInsidePlayer.GetPositionGridY() << std::endl;
                                if (isGame) player.MoveRight();
                            }
                            break;
                        case SDLK_r:
                            qlear.Train();
                            world.GenerateCells(xLenghtCells, yLenghtCells);
                            break;
                        case SDLK_SPACE:
                            isStartQlearning = true; 
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
