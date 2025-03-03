#pragma once
#include "Time.h"
#include "unordered_map"


namespace psh
{
	class GameObject;

	namespace Component
	{
		using ComponentTypeID = size_t;

		class Component
		{
		public:
			Component() = default;
			virtual ~Component() = default;

			virtual void Initialize()
			{
			}

			virtual void Update(MsTime deltaTime)
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

			[[nodiscard]] virtual ComponentTypeID GetTypeID() const = 0;

		private:
			GameObject* m_Owner;
		};

		/**
	 * \brief 컴포넌트마다 고유 ID를 발급하기 위한 클래스.
	 * 런타임에 타입 이름을 확인할 수 있도록 별도 클래스를 만들어 등록 방식으로 구현함.
	 * \note enum이나 템플릿으로 자동 부여하는 방식을 고려했으나,
	 * 템플릿은 타이핑이 번거롭고, enum은 새 컴포넌트 추가 시 헤더 수정으로 재컴파일이 필요해 제외함.
	 */
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
	}


	//GetTypeID는 런타임에 타입 얻어오는데 사용
#define TYPEID_DEFINE(typename)\
private:\
	inline static const ComponentTypeID m_typeID = ComponentTypeRegistry::RegisterComponentType(typename);\
public:\
	[[nodiscard]] ComponentTypeID GetTypeID() const override \
	{\
		return m_typeID;\
	}\
	[[nodiscard]] static ComponentTypeID TypeID()  \
	{\
		return m_typeID;\
	}
}
