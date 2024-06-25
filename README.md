# HYGUI

> **警告：**  
> 库开发中,仅供技术预览.
  

跨平台的GUI库，基于SDL2窗口管理,Skia绘图后端。

# 构建方法

- 建立一个model文件夹，用于存放依赖库(后续会简化流程,但不是现在)
  > 可以参考我的博客文章  
  > [windows编译SKIA](https://blog.hyiy.top/archives/30/)
- 在model内构建skia/boost等
    - model结构
    ```
    model
    ├── boost
    │   ├── include
    │   └── lib
    ├── icu
    │   ├── include
    │   └── lib
    ├── SDL
    │   ├── include
    │   └── lib
    ├── skia
    │   ├── include
    │   └── out
    │       ├── debug_x64_static
    │       └── release_x64_static
    ```
- 使用cmake构建
  ```cmd
    mkdir build
    cd build
    cmake ..-DCMAKE_BUILD_TYPE=Debug -DMODULES_DIR="你的model文件夹路径" -DSKIA_PATH="你的skia文件夹路径"
    cmake --build .
  ```
  > 运行Debug下的HelloWorld试试吧

# 说明

以Skia为绘图后端,SDL2抽象窗口管理的跨平台GUI库，使用C接口导出，支持各种语言(C/C++/GO/Python/Rust等)调用。

# 计划

- [ ] 支持窗口主题
- [ ] 窗口事件
    - [ ] windows
      - [x] 进行中
    - [ ] linux
      - [x] 进行中
    - [ ] macos
      - [x] 进行中
    - [ ] android(待定)
    - [ ] ios(待定)
    - [ ] web/webassembly(待定)
- [ ] 完善窗口绘制
  - [x] 进行中
- [ ] 完善子组件绘制
    - [ ] 组件消息
        - [x] 进行中
    - [ ] 组件绘制
    - [ ] 组件嵌套绘制
        - [x] 进行中
- [ ] 局部重绘
- [ ] 跨平台支持
    - [x] windows
    - [x] linux
    - [x] macos
    - [ ] android
    - [ ] ios(待定)
    - [ ] web/webassembly(待定)
- [ ] 抽象/封装skia相关api
    - [ ] 绘图
    - [ ] 字体
    - [ ] 图片
    - [ ] 文本
- [ ] 动画机制
- [ ] 硬件加速
- [ ] 扩充组件
    - [x] 基类组件
    - [ ] 布局组件
        - [ ] 线性布局
        - [ ] 网格布局
        - [ ] 流式布局
        - [ ] ...
    - [ ] 标签(Label)
        - [x] 作为第一个扩展组件开发中
    - [ ] 按钮(Button)
    - [ ] CheckBox
    - [ ] RadioBox
    - [ ] TextBox
    - [ ] ...
- [ ] 主题包
- [ ] 内嵌资源
- [ ] 多语言绑定/包装
    - [x] C
    - [x] C++
    - [ ] GO
    - [ ] Python
    - [ ] Rust
    - [ ] ...
- [ ] ...
