#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "../lib/glm/glm.hpp"
#include "EntityManager.h"
#include "./components/TransformComponent.h"

EntityManager manager;
SDL_Renderer* Game::renderer;

Game::Game(){
    this->isRunning = false;
}

Game::~Game(){
}

bool Game::IsRunning () const {
    return this->isRunning;
}

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
    LoadLevel(0);

    isRunning = true;
    return;
}

void Game::LoadLevel(int levelNumber){
    std::cout << "Level loaded" << std::endl;
    Entity& projectile(manager.AddEntity("projectile"));
    projectile.AddComponent<TransformComponent>(643,6,20,20,32,32,1);
    Entity& projectile1(manager.AddEntity("projectile1"));
    projectile1.AddComponent<TransformComponent>(0,0,20,20,32,32,1);
    Entity& projectile2(manager.AddEntity("projectile2"));
    projectile2.AddComponent<TransformComponent>(425,24,-20,-24,63,722,1);
    Entity& projectile3(manager.AddEntity("projectile3"));
    projectile3.AddComponent<TransformComponent>(643,566,-240,-520,32,32,1);
    Entity& projectile4(manager.AddEntity("projectile4"));
    projectile4.AddComponent<TransformComponent>(175,175,-20,-266,32,32,1);
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
    
    ticksLastFrame = SDL_GetTicks();

    manager.Update(deltaTime);
}

void Game::Render(){
    //Prep color
    SDL_SetRenderDrawColor(renderer,21,21,21,255);
    //Paint background
    SDL_RenderClear(renderer);
    //prep color
    
    if (manager.hasNoEntities()){
        return;
    }

    manager.Render();
    manager.GetEntities();
    //update
    SDL_RenderPresent(renderer);
}

void Game::Destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
