#pragma once
#include <typeinfo>
#include <typeindex>

struct IField
{
	virtual ~IField() = default;
	virtual const std::type_info& type() const = 0;
};
