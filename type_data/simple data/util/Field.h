#pragma once
#include "IField.h"

namespace mdt
{
	template<typename T>
	struct Field : IField
	{
		T value;
		explicit Field(T v) : value(std::move(v)) {}
		const std::type_info& type() const override { return typeid(T); }
	};
}