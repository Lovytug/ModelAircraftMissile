#pragma once

class Engine;

class IEngineComponent
{
	virtual ~IEngineComponent() = default;
	virtual void update(float dt) = 0;
	virtual [[nodiscard]] std::string getName() const = 0;
};