# C++ 设计模式实战闯关

这是一个给即将入职程序员准备的设计模式实战项目。目标不是背诵 GoF 定义，而是在真实需求变化、代码坏味道、测试保护和 AI 辅助编码中，把设计模式变成可复用的工程判断力。

## 怎么学习

每一关都按同一种节奏推进：

1. 阅读关卡 `README.md`，理解业务背景和新增需求。
2. 阅读 `before/`，找出坏味道。
3. 在 `practice/` 中自己尝试重构。
4. 运行测试，确认行为和新增需求。
5. 最后再对照 `solutions/` 中的参考实现，观察设计模式解决了哪个变化点。
6. 完成 `notes.md` 里的复盘问题。

## 构建和测试

```powershell
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

项目不依赖 Catch2、GoogleTest 或其他第三方库，测试工具在 `tests/test_framework.hpp`。

## 目录约定

```text
lessons/
  01_strategy/
    README.md
    before/
    practice/
    tests/
    notes.md
solutions/
  01_strategy/
    after/
```

`lessons/` 是闯关区，优先只看这里。`solutions/` 是答案区，建议完成自己的版本后再打开。

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
