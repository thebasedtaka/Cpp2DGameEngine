#ifndef ENTITY_H
#define ENTITY_H
#include <vector>
#include <string>
#include <map>
#include <typeinfo>
#include <typeindex>
#include "./EntityManager.h"
#include "./Component.h"
#include <iostream>

class Component;
class EntityManager;

//Methods that manage specific entities

class Entity {
    private:
        EntityManager& manager;
        bool isActive;
        std::vector<Component*> components;
        std::map<std::type_index, Component*> componentTypeMap;
    public:
        std::string name;
        Entity(EntityManager& manager);
        Entity(EntityManager& manager, std::string name);
        void Update(float deltaTime);
        void Render();
        void Destroy();
        bool IsActive() const;
        void ListAllComponents() const;
        template <typename T, typename... TArgs>
        T& AddComponent(TArgs&&... args){
            T* newComponent(new T(std::forward<TArgs>(args)...));
            newComponent->owner = this;
            components.emplace_back(newComponent);
            componentTypeMap[std::type_index(typeid(T))] = newComponent;
            newComponent->Initialize();
            return *newComponent;
        }
        template <typename T>
        T* GetComponent(){
            return static_cast<T*>(componentTypeMap[std::type_index(typeid(T))]);
        }
        template <typename T>
        bool HasComponent() const{
            bool state = componentTypeMap.find(std::type_index(typeid(T))) != componentTypeMap.end();
           
            return state;
        }
};

#endif