#pragma once
#include <vector>

template<class T>
class IStateProvader
{
public:
	virtual [[nodiscard]] std::vector<double> getVectorState() const = 0;
};