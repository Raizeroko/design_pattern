#pragma once

/*
场景：应用需要共享一份进程级配置。
新需求：任意模块都能取得同一个配置实例。
当前问题：
1. 当前函数要求每个调用方传入 map，没有稳定的共享入口。
2. 如果直接改成裸全局变量，初始化顺序和生命周期不清晰。
3. 全局状态会污染测试，因此必须明确清理边界。
练习目标：实现线程安全的单实例入口，同时理解它不适合多租户和强隔离测试。
*/

#include <map>
#include <string>

/*
概念与代码对照：
- [共享资源] 调用方各自持有并传入的 config map。
- [访问动作] read_config(config, key)。
- [问题证据] 没有统一实例入口；所有需要配置的函数都要传递 map。
*/

namespace singleton::before {

// [访问动作] 每个业务模块必须显式传入共享 config。
inline std::string read_config(std::map<std::string, std::string>& config, const std::string& key) {
    // [问题证据] 没有统一访问点；operator[] 还让读取带有写入副作用。
    return config[key];
}

} // namespace singleton::before
