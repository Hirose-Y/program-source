#ifndef CALLBACK_REGISTRY_H
#define CALLBACK_REGISTRY_H

#include <string>
#include <unordered_map>
#include <functional>

class CallbackRegistry {
public:
    // 登録（上書き可）
    void Add(const std::string& name, std::function<void()> callback) {
        callbacks[name] = callback;
    }

    // 削除
    void Remove(const std::string& name) {
        callbacks.erase(name);
    }

    // 存在確認
    bool Exists(const std::string& name) const {
        return callbacks.find(name) != callbacks.end();
    }

    // 実行（すべて）
    void ExecuteAll() const {
        for (const auto& [name, callback] : callbacks) {
            if (callback) callback();
        }
    }

    // 指定したコールバックだけ実行
    void Execute(const std::string& name) const {
        auto it = callbacks.find(name);
        if (it != callbacks.end() && it->second) {
            it->second();
        }
    }

    // 全削除
    void Clear() {
        callbacks.clear();
    }

private:
    std::unordered_map<std::string, std::function<void()>> callbacks;
};

#endif // CALLBACK_REGISTRY_H
