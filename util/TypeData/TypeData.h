#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>
#include "Field.h"

struct TypeData {
	virtual ~TypeData() = default;

	template<typename T>
	void set(std::string_view key, T value)
	{
		data_[key] = std::make_shared<Field<T>>(std::move(value));
	}

	template<typename T>
	T get(std::string_view key) const
	{
		auto it = data_.find(key);
		if (it == data_.end()) {
			throw std::runtime_error("Key not found: " + std::string(key));
		}

		auto* f = static_cast<Field<T>*>(it->second.get());
		if (f->type() != typeid(T)) {
			throw std::runtime_error("Wrong type for key: " + std::string(key));
		}

		return f->value;
	}

	template<typename T>
	const T getRef(std::string_view key) const
	{
		auto it = data_.find(key);
		if (it == data_.end()) {
			throw std::runtime_error("Key not found: " + std::string(key));
		}

		auto* f = static_cast<Field<T>*>(it->second.get());
		if (f->type() != typeid(T)) {
			throw std::runtime_error("Wrong type for key: " + std::string(key));
		}

		return f->value;
	}

protected:
	std::unordered_map<std::string_view, std::shared_ptr<IField>> data_;
};