#pragma once

class GameObject;

class Component
{
public:
	using ComponentTypeID = size_t;
	Component() = default;
	virtual ~Component() = default;

	virtual void Initialize()
	{
	}

	virtual void Update(float deltaTime)
	{
	}

	void SetOwner(GameObject* owner)
	{
		m_Owner = owner;
	}

	[[nodiscard]] GameObject* GetOwner() const
	{
		return m_Owner;
	}

	[[nodiscard]] virtual const ComponentTypeID GetTypeID() const = 0;

private:
	GameObject* m_Owner;
};

class ComponentTypeRegistry
{
public:
	using ComponentTypeID = size_t;

	static ComponentTypeID RegisterComponentType(const std::string& typeName)
	{
		static ComponentTypeID nextID = 0;
		const auto id = nextID++;
		GetInstance().m_typeNames[id] = typeName;
		return id;
	}

	static const std::string& GetTypeName(ComponentTypeID id)
	{
		static const std::string emptyString;
		const auto it = GetInstance().m_typeNames.find(id);
		return it != GetInstance().m_typeNames.end() ? it->second : emptyString;
	}

private:
	static ComponentTypeRegistry& GetInstance()
	{
		static ComponentTypeRegistry instance;
		return instance;
	}

	std::unordered_map<ComponentTypeID, std::string> m_typeNames;
};


//GetTypeID는 런타임에 해당 객체의 타입 얻어오는데 사용
#define TYPEID_DEFINE(typename)\
private:\
	inline static const Component::ComponentTypeID m_typeID = ComponentTypeRegistry::RegisterComponentType(typename);\
public:\
	[[nodiscard]] const ComponentTypeID GetTypeID() const override \
	{\
		return m_typeID;\
	}\
	[[nodiscard]] static const ComponentTypeID TypeID()  \
	{\
		return m_typeID;\
	}
