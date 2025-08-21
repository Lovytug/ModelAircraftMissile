#pragma once
#include <any>
#include <vector>
#include <string>
#include <functional>
#include "TypeData.h"

struct DynamicBundle {
	virtual ~DynamicBundle() = default;

    template <typename Ret, typename... Args>
    Ret call(const std::string& name, Args&&... args) 
    {
        return do_call(name, std::make_any<Args>(std::forward<Args>(args))...);
    }

    template <typename Ret, typename... Args>
    void add(const std::string& name, std::function<Ret(Args...)> func) 
    {
        do_add(name, [func = std::move(func)](const std::vector<std::any>& args) -> double {
            if (args.size() != sizeof...(Args)) {
                throw std::invalid_argument("Argument count mismatch");
            }
            return std::any_cast<Ret>(call_helper<Ret, Args...>(func, args, std::index_sequence_for<Args...>{}));
            });
    }

protected:
    // ”ниверсальный вызов Ч реализуетс€ в наследнике
    virtual double do_call(const std::string& name, const std::vector<std::any>& args) = 0;

    // –егистраци€ Ч реализуетс€ в наследнике
    virtual void do_add(const std::string& name, std::function<double(const std::vector<std::any>&)> func) = 0;

private:
    template <typename Ret, typename... Args, std::size_t... Is>
    Ret call_helper(const std::function<Ret(Args...)>& func, const std::vector<std::any>& args, std::index_sequence<Is...>) {
        return func(std::any_cast<Args>(args[Is])...);
    }
};