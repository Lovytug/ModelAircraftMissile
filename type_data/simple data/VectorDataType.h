#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <typeindex>
#include "../IBaseType.h"
#include "util/Field.h"
#include "util/Params.h"

namespace mdt
{
	struct VectorDataType
	{
		virtual ~VectorDataType() = default;

		template<class IFace, typename T>
		void set(std::string key, T value)
		{
			params_.emplace_back(
				typeid(IFace),
				key,
				std::make_shared<Field<T>>(std::move(value))
			);
		}

		template<typename T>
		T get(std::string key) const
		{
			for (auto& p : params_) {
				if (p.name == key) {
					auto* f = static_cast<Field<T>*>(p.field.get());
					if (f->type() != typeid(T)) {
						throw std::runtime_error("Wrong type for key: " + key);
					}
					return f->value;
				}
			}
			throw std::runtime_error("Key not found: " + key);
		}

		template<class IFace, typename T>
		const T get(std::string key) const
		{
			for (auto& p : params_) {
				if (p.iface == typeid(IFace) && p.name == key) {
					auto* f = static_cast<Field<T>*>(p.field.get());
					if (f->type() != typeid(T)) {
						throw std::runtime_error("Wrong type for key: " + std::string(key));
					}
					return f->value;
				}
			}
			throw std::runtime_error("Key not found: " + std::string(key));
		}

		template<class IFace>
		VectorDataType& subdata()
		{
			auto idx = std::type_index(typeid(IFace));
			auto it = nested_.find(idx);
			if (it == nested_.end()) {
				auto node = std::make_shared<VectorDataType>();
				nested_[idx] = node;
				return *node;
			}
			return *nested_[idx];
		}

		template<class IFace>
		const VectorDataType& subdata()
		{
			auto idx = std::type_index(typeid(IFace));
			auto it = nested_.find(idx);
			if (it == nested_.end()) {
				throw std::runtime_error("No subdata for interface");
			}
			return *it->second;
		}

		VectorDataType& subdataByIndex(const std::type_index& idx) const 
		{
			auto it = nested_.find(idx);
			if (it == nested_.end()) {
				throw std::runtime_error("No subdata for this interface");
			}
			return *it->second;
		}

		const std::vector<Param>& params() const { return params_; }
		std::vector<Param>& params() const { return params_; }

		const std::unordered_map<std::type_index, std::shared_ptr<VectorDataType>>& nested() const { return nested_; }
		std::unordered_map<std::type_index, std::shared_ptr<VectorDataType>>& nested() const { return nested_; }

		VectorDataType& operator=(const VectorDataType& other)
		{
			if (this == &other) return *this;
			params_ = other.params_;
			nested_.clear();
			for (auto& [idx, sub] : other.nested_) {
				nested_[idx] = std::make_shared<VectorDataType>(*sub);
			}
			return *this;
		}

	protected:
		std::unordered_map<std::type_index, std::shared_ptr<VectorDataType>> nested_;
		std::vector<Param> params_;
	};
}