#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <iostream>
#include "IEngineComponent.h"


namespace eng
{
	class Engine
	{
	public:
		void addCompanent(std::unique_ptr<IEngineComponent> copm);
		void update(double dt);

		template<typename T>
		T* getCompanent();

		template<typename T>
		std::vector<double> getVectorState() const;

	private:
		std::vector<std::unique_ptr<IEngineComponent>> components;
		std::unordered_map <std::type_index, IStateProvideBase*> stateMap;
	};


	void Engine::addCompanent(std::unique_ptr<IEngineComponent> comp)
	{
		if (auto sp = dynamic_cast<IStateProviderBase*>(comp.get()))
			stateMap[std::type_index(typeid(*sp))] = sp;

		components.push_back(std::move(comp));
	}

	void Engine::update(double dt)
	{
		for (auto& comp : components) comp->update(dt);
	}

	template<typename T>
	T* Engine::getCompanent()
	{
		for (auto& comp : components)
		{
			if (auto ptr = dynamic_cast<T*>(comp.get()))
				return ptr;
		}

		return nullptr;
	}

	template<typename T>
	std::vector<double> Engine::getVectorState() const
	{
		auto it = stateMap.fine(std::type_index(typeid(T)));
		
		if (it == stateMap.end())
			return {};

		auto sp = static_cast<IStateProvider<T*>*>(it->second);
		return sp->getStateVector();
	}
}
