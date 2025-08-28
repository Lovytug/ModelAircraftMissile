#pragma once
#include <any>
#include <vector>
#include <string>
#include <functional>

namespace mdt
{
    struct DynamicBundle {
        virtual ~DynamicBundle() = default;

        template <typename Ret, typename... Args>
        Ret call(const std::string& name, Args&&... args)
        {
            std::vector<std::any> packed_args{ std::make_any<Args>(std::forward<Args>(args))... };
            std::any result = do_call(name, packed_args);
            return std::any_cast<Ret>(result);
        }

        template <typename Ret, typename... Args>
        void add(const std::string& name, std::function<Ret(Args...)> func)
        {
            do_add(name,
                [func = std::move(func)](const std::vector<std::any>& args) -> std::any {
                    if (args.size() != sizeof...(Args)) {
                        throw std::invalid_argument("Argument count mismatch");
                    }
                    return call_helper<Ret, Args...>(
                        func, args, std::index_sequence_for<Args...>{}
                    );
                }
            );
        }

    protected:
        // ”ниверсальный вызов Ч реализуетс€ в наследнике
        virtual std::any do_call(const std::string& name, const std::vector<std::any>& args) = 0;

        // –егистраци€ Ч реализуетс€ в наследнике
        virtual void do_add(const std::string& name, std::function<std::any(const std::vector<std::any>&)> func) = 0;

    private:
        template <typename Ret, typename... Args, std::size_t... Is>
        static Ret call_helper(
            const std::function<Ret(Args...)>& func,
            const std::vector<std::any>& args,
            std::index_sequence<Is...>
        ) {
            return func(std::any_cast<Args>(args[Is])...);
        }
    };
}