#include <iostream>
#include "./Constants.h"
#include "./Game.h"

Game::Game(){
    this->isRunning = false;
}

Game::~Game(){
}

bool Game::IsRunning () const {
    return this->isRunning;
}

float projectilePosY = 0.0f;
float projectilePosX = 0.0f;
float projectileVelX = 0.05f;
float projectileVelY = 0.05f;

void Game::Initialize(int width, int height){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }
    window = SDL_CreateWindow(
        "BitchNigga",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS
    );
    if (!window){
        std::cerr << "Error creating SDL window" << std::endl;
        return;
    }
    // -1 set default 
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer){
        std::cerr << "Error creating SDL renderer" << std::endl;
        isRunning = false;
        return;
    }

    isRunning = true;
    return;
}

void Game::ProcessInput(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type){
        case SDL_QUIT:{
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN:{
            if (event.key.keysym.sym == SDLK_ESCAPE){
                isRunning = false;
            }
        }
        default: {
            break;
        }
    }
}

void Game::Update(){
    projectilePosX += projectileVelX;
    projectilePosY += projectileVelY;

}

void Game::Render(){
    //Prep color
    SDL_SetRenderDrawColor(renderer,21,21,21,255);
    //Paint background
    SDL_RenderClear(renderer);

    SDL_Rect projectile{
        (int) projectilePosX,
        (int) projectilePosY,
        10,
        10
    };
    //prep color
    SDL_SetRenderDrawColor(renderer,2,255,255,255);
    //Paint Rectangle with projectile struct dimentions
    SDL_RenderFillRect(renderer, &projectile);
    //update
    SDL_RenderPresent(renderer);
}

void Game::Destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}