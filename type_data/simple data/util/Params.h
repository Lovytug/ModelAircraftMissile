#pragma once
#include <typeindex>
#include <string>
#include <memory>
#include "IField.h"

namespace mdt
{
	struct Param
	{
		std::type_index iface;
		std::string name;
		std::shared_ptr<IField> field;

		Param(std::type_index i, std::string n, std::shared_ptr<IField> f)
			: iface(i), name(std::move(n)), field(std::move(f)) {
		}
	};
}