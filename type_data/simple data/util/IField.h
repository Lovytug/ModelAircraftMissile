#pragma once
#include <typeinfo>
#include <typeindex>

namespace mdt
{
	struct IField
	{
		virtual ~IField() = default;
		virtual const std::type_info& type() const = 0;
	};
}
