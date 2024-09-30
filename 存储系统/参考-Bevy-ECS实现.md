# Bevy-ECS

## data-oriented design

Bevy游戏引擎是基于DOD架构的，什么是DOD架构呢？

想要细致地了解DoD架构，可以去看一本书：https://www.dataorienteddesign.com/dodbook/

Rust的一个相关blog地址：https://jamesmcm.github.io/blog/intro-dod/







## ECS

ECS（Entity-Component-System）是一种在游戏开发中广泛使用的设计模式，尤其在需要处理大量实体和复杂交互的系统中，如Unity3D游戏引擎中。ECS模式的核心思想是将游戏对象分为三个主要部分：实体（Entity）、组件（Component）和系统（System），以此来提高代码的可维护性、可扩展性和性能。



使用ECS模式主要为了两点：

* 为应用场景提供数据交互模型
* 充分利用现代CPU cache获得更优的性能表现



下面是bevy ecs对**ECS**的解释：

> All app logic in Bevy uses the Entity Component System paradigm, which is often shortened to ECS. ECS is a software pattern that involves breaking your program up into Entities, Components, and Systems. Entities are unique “things” that are assigned groups of Components, which are then processed using Systems.
>
> For example, one entity might have a `Position` and `Velocity` component, whereas another entity might have a `Position` and `UI` component. You might have a movement system that runs on all entities with a Position and Velocity component.
>
> The ECS pattern encourages clean, decoupled designs by forcing you to break up your app data and logic into its core components. It also helps make your code faster by optimizing memory access patterns and making parallelism easier.



1. **实体（Entity）**：实体通常是游戏中的基本对象，如角色、物体等。在ECS架构中，实体通常只是一个空的容器，不包含任何具体的行为或状态。
2. **组件（Component）**：组件是附加到实体上的数据结构，用于描述实体的属性，如位置、速度、生命值等。一个实体可以有多个组件，组件之间相互独立，不同的组件可以包含不同类型的数据。
3. **系统（System）**：系统是一组操作组件数据的逻辑单元。系统会根据实体拥有的组件类型和数据来执行相应的逻辑，如物理更新、渲染、输入处理等。系统不存储状态，它们通过组件的数据来执行操作。



### bevy ecs

becy ecs是为了该引擎单独定制的ECS，本身是一个Rust crate。



## 数据库的作用

参考链接：https://spacetimedb.com/blog/databases-and-data-oriented-design



