#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "../lib/glm/glm.hpp"

Game::Game(){
    this->isRunning = false;
}

Game::~Game(){
}

bool Game::IsRunning () const {
    return this->isRunning;
}

glm::vec2 projectilePos = glm::vec2(0.0f, 0.0f);
glm::vec2 projectileVel = glm::vec2(5.0f, 5.0f);

void Game::Initialize(int width, int height){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }
    window = SDL_CreateWindow(
        "Null",
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
    // Sets new ticks for the current frame to be used
    // Wait until 16~ms has elapsed since last frame
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);

    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME){
        SDL_Delay(timeToWait);
    }
     
    // Delta time = difference in ticks from last frame to seconds
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
    
    std::cout << projectilePos.x << " " << projectilePos.y << " vel: " << projectileVel.x << " delta: " << deltaTime << std::endl;


    ticksLastFrame = SDL_GetTicks();

    projectilePos = glm::vec2(projectilePos.x + projectileVel.x * deltaTime, projectilePos.y + projectileVel.y * deltaTime);
}

void Game::Render(){
    //Prep color
    SDL_SetRenderDrawColor(renderer,21,21,21,255);
    //Paint background
    SDL_RenderClear(renderer);

    SDL_Rect projectile{
        (int) projectilePos.x,
        (int) projectilePos.y,   
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