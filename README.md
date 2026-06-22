# C++ 设计模式实战闯关

这是一个给即将入职程序员准备的设计模式实战项目。目标不是背诵 GoF 定义，而是在真实需求变化、代码坏味道、测试保护和 AI 辅助编码中，把设计模式变成可复用的工程判断力。

## 怎么学习

每一关都按同一种节奏推进：

1. 打开某一关的 `before.hpp`，阅读场景、坏味道和初始代码。
2. 在同目录的 `practice.hpp` 中完成自己的实现。
3. 阅读 `test.cpp` 中直白的输入、预期结果和失败信息。
4. 单独构建并运行本关测试。
5. 测试通过后再打开 `after.hpp`，对照带注释的参考实现。

## 构建和测试

```powershell
cmake -S . -B build
cmake --build build --target strategy_test
.\build\strategy_test.exe
```

把 `strategy` 换成当前关卡名即可。每个测试都使用普通 `if`、`std::cout` 和 `std::cerr`，不依赖测试框架。

除已完成的 Strategy 外，其余 `practice.hpp` 不提供任何接口或实现骨架。先阅读 `before.hpp` 和 `test.cpp`，再自行设计类型与实现；首次构建因缺少类型而失败是正常现象。你可以自由调整练习接口，只需同步修改测试中的对象构造部分，业务断言不要降低。

## 目录约定

```text
lessons/
  01_strategy/
    before.hpp
    practice.hpp
    after.hpp
    test.cpp
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
