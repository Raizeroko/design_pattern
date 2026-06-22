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

/*
模式角色与代码对照：
- [Singleton] AppConfig。
- [唯一实例] instance() 内的 static AppConfig config。
- [全局访问点] AppConfig::instance()。
- [阻止外部创建] 私有 AppConfig 构造函数。
- [共享状态] values_。
*/

namespace singleton::after {

// [Singleton] AppConfig 表示进程内唯一配置仓库。
class AppConfig {
public:
    // [全局访问点] 所有模块通过 instance() 取得同一对象。
    static AppConfig& instance() {
        // [唯一实例] 函数内 static 只构造一次，C++11 保证初始化线程安全。
        static AppConfig config;
        return config;
    }

    void set(std::string key, std::string value) {
        // [共享状态写入动作] 向唯一实例写入配置。
        values_[std::move(key)] = std::move(value);
    }

    std::string get(const std::string& key) const {
        // [共享状态读取动作] 从唯一实例读取，不产生插入副作用。
        auto found = values_.find(key);
        return found == values_.end() ? "" : found->second;
    }

    void clear_for_test() {
        // [测试隔离动作] 清空跨测试共享的 Singleton 状态。
        values_.clear();
    }

private:
    // [唯一性约束] 私有构造阻止外部创建第二个实例。
    AppConfig() = default;
    // [共享状态] 配置数据只存在于唯一实例中。
    std::map<std::string, std::string> values_;
};

} // namespace singleton::after
