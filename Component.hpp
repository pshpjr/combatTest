#pragma once
#include <memory>

class GameObject;

class Component {
public:
    Component() = default;
    virtual ~Component() = default;

    virtual void Initialize() {}
    virtual void Update(float deltaTime) {}
    
    void SetOwner(std::shared_ptr<GameObject> owner) { m_Owner = owner; }
    std::shared_ptr<GameObject> GetOwner() const { return m_Owner.lock(); }

private:
    std::weak_ptr<GameObject> m_Owner;
};
