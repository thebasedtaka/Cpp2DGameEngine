#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "../lib/glm/glm.hpp"
#include "./AssetManager.h"
#include "./components/TransformComponent.h"
#include "./components/SpriteComponent.h"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;

Game::Game(){
    //Sets Game to not running once it is created
    this->isRunning = false;
}

Game::~Game(){
}

bool Game::IsRunning () const {
    return this->isRunning;
}

void Game::Initialize(int width, int height){
    //Initialize SDL
    std::cout << "init" <<  std::endl; 
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }
    //Create window with SDL
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
    // creates a renderer for the window -1 set default 
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

void Game::LoadLevel(int levelNumber) {
    std::cout << "level loaded" << std::endl; 
    /* Start including new assets to the assetmanager list */
    std::string textureFilePath = "./assets/images/tank-big-right.png";
    assetManager->AddTexture("tank-image", textureFilePath.c_str());

    /* Start including entities and also components to them */
    Entity& newEntity(manager.AddEntity("tank"));
    newEntity.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
    newEntity.AddComponent<SpriteComponent>("tank-image");
    std::cout << "entity loaded" << std::endl; 
}

void Game::ProcessInput(){
    //Creates and stores event information
    SDL_Event event;
    SDL_PollEvent(&event);

    //Exit conditions
    switch (event.type){
        //Close button
        case SDL_QUIT:{
            isRunning = false;
            break;
        }
        //Escape Key
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
    //SDL_SetRenderDrawColor(renderer,99,21,21,255);
    //Paint background
    //SDL_RenderClear(renderer);
    //prep color
    
    if (manager.HasNoEntities()){
        return;
    }

    manager.Render();
    //Entity::HasComponent();
    //update
    SDL_RenderPresent(renderer);
}

void Game::Destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
