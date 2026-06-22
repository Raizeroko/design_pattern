# C++ 设计模式实战闯关

这是一个给即将入职程序员准备的设计模式实战项目。目标不是背诵 GoF 定义，而是在真实需求变化、代码坏味道、测试保护和 AI 辅助编码中，把设计模式变成可复用的工程判断力。

## 怎么学习

每一关都按同一种节奏推进：

1. 打开某一关的 `before.hpp`，阅读场景、坏味道和初始代码。
2. 在同目录的 `practice.hpp` 中完成自己的实现。
3. 运行 `before_test.cpp`，确认初始代码当前行为。
4. 在 `practice.hpp` 中自由设计自己的实现和测试。
5. 最后阅读 `after.hpp` 与 `after_test.cpp`，对照参考重构及新增需求。

## 构建和测试

```powershell
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

每个测试都使用普通 `if`、`std::cout` 和 `std::cerr`，不依赖测试框架。before 与 after 接口不同时使用独立测试文件，避免用兼容代码掩盖设计差异。

除已完成的 Strategy 外，其余 `practice.hpp` 不提供任何接口或实现骨架，也不参与 CMake 构建。你可以自由设计练习接口，并参考 before/after 测试为自己的实现补充测试。

## 目录约定

```text
lessons/
  01_strategy/
    before.hpp
    practice.hpp
    after.hpp
    before_test.cpp
    after_test.cpp
```

每一关的场景、练习、答案和测试都在同一文件夹中，减少学习时来回跳转。建议测试通过后再打开 `after.hpp`。

## 首版关卡

| 关卡 | 模式 | 学习目标 |
| --- | --- | --- |
| 01 | Strategy | 消除复杂条件分支 |
| 02 | Factory | 隔离对象创建变化 |
| 03 | Observer | 事件通知与解耦 |
| 04 | Decorator | 运行时扩展行为 |
| 05 | Adapter | 兼容旧接口或第三方接口 |
| 06 | Template Method | 稳定流程 + 可变步骤 |
| 07 | State | 替代状态分支爆炸 |
| 08 | Command | 封装操作、支持撤销 |
| 09 | Singleton | 讲清楚适用边界和线程安全 |
| 10 | Facade | 为复杂子系统提供简单入口 |

建议先顺序学习前 5 关，再根据工作场景挑选后面的关卡深入。
