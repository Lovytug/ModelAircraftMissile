#pragma once
#include <functional>
#include <memory>
#include <cmath>
#include <numeric>

class IFuelProfile;

class IDataProvider;

class IPhisicsModule;


using IFuelProfile_uptr = std::unique_ptr<IFuelProfile>;

using IFuelProfile_shptr = std::shared_ptr<IFuelProfile>;

using IDataProvider_uptr = std::unique_ptr<IDataProvider>;

using IDataProvider_shptr = std::shared_ptr<IDataProvider>;

using IPhisicsModule_uptr = std::shared_ptr<IPhisicsModule>;


inline constexpr M_PI;