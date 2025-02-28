#pragma once
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <typeindex>
#include <unordered_map>
#include "Component.hpp"

class GameObject : public std::enable_shared_from_this<GameObject> {
public:
    GameObject(const std::string& name = "GameObject") : m_Name(name) {}
    ~GameObject() = default;

    void Initialize() {
        for (auto& component : m_Components) {
            component->Initialize();
        }
    }

    void Update(float deltaTime) {
        for (auto& component : m_Components) {
            component->Update(deltaTime);
        }
    }

    template<typename T, typename... Args>
    std::shared_ptr<T> AddComponent(Args&&... args) {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
        
        auto component = std::make_shared<T>(std::forward<Args>(args)...);
        component->SetOwner(shared_from_this());
        m_Components.push_back(component);
        
        return component;
    }

    template<typename T>
    std::shared_ptr<T> GetComponent() {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
        
        for (auto& component : m_Components) {
            auto casted = std::dynamic_pointer_cast<T>(component);
            if (casted) {
                return casted;
            }
        }
        
        return nullptr;
    }

    const std::string& GetName() const { return m_Name; }
    void SetName(const std::string& name) { m_Name = name; }

private:
    std::string m_Name;
    std::vector<std::shared_ptr<Component>> m_Components;
};
