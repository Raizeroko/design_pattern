#pragma once

/*
参考重构：Singleton
- instance 使用函数内 static；从 C++11 起，首次初始化由语言保证线程安全。
- 构造函数私有，阻止调用方创建第二个 AppConfig。
- clear_for_test 明确暴露测试清理点，提醒我们全局状态会造成测试耦合。
注意：set/get 本身没有并发保护；若运行期多线程写配置，还需要 mutex。
*/

#include <map>
#include <string>
#include <utility>

namespace singleton::after {

class AppConfig {
public:
    // C++11 起，函数内 static 的首次初始化由语言保证线程安全。
    static AppConfig& instance() {
        static AppConfig config;
        return config;
    }

    void set(std::string key, std::string value) {
        values_[std::move(key)] = std::move(value);
    }

    std::string get(const std::string& key) const {
        auto found = values_.find(key);
        return found == values_.end() ? "" : found->second;
    }

    void clear_for_test() {
        values_.clear();
    }

private:
    // 私有构造阻止调用方创建第二个实例。
    AppConfig() = default;
    std::map<std::string, std::string> values_;
};

} // namespace singleton::after
