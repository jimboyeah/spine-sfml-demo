
### 🗝 The Graphics Rendering Pipeline
- OpenGL Wiki https://www.khronos.org/opengl/wiki/Main_Page
- Computer Graphics: Principles and Practice 3rd Edition 2014
- Fundamentals of Computer Graphics 4/5th Edition
- OpenGL SuperBible: comprehensive tutorial and reference OpenGL 4.3 6th Edition
- OpenGL SuperBible: comprehensive tutorial and reference OpenGL 4.5 7th Edition
- OpenGL Programming Guide: The Official Guide to Learning OpenGL 4.3 8th Edition
- OpenGL Programming Guide: The Official Guide to Learning OpenGL 4.5 with SPIR-V 9th Edition
- GLSL Essentials: Enrich your 3D scenes with the power of GLSL! by Jacobo Rodríguez
- GAMES101: 现代计算机图形学入门 https://sites.cs.ucsb.edu/~lingqi/teaching/games101.html
- GAMES101-现代计算机图形学入门-闫令琪 https://www.bilibili.com/video/av90798049
- GAMES101 课程录像 https://www.bilibili.com/video/av90798049
- OpenGL Reference Cards https://www.khronos.org/developers/reference-cards/
- Vulkan® API Tutorialhttps://vulkan-tutorial.com/Introduction

我接触 GPU 渲染管线是从 OpenGL 开始的，而有个金主爸爸的 DirectX 多媒体接口只有一个模糊的认识。在图形接口规范中，确实是非常混乱的一个市场，像是一个军阀混战的年代。Open Graphics Library 整体上还是比较接近图形学的基础概念，选择 OpenGL 的理由很简单：通用跨平台。

如果想要更深入 GPU 的开发，还可以选择更精细的 Vulkan® API，它也 khronos 组织制定的图形接口标准。

Vulkan 虽然给开发者提供了更多的自由度，如果这个开发者本身不自由(非大牛)，那用回 OpenGL 也是个不错的选择。原因就在于如果开发者对内存管理机制，对程序运行机制没有十足的理解，那就可能会误用 Vulkan 导致运行效率甚至 OpenGL 运行效率更低，那这样就得不偿失。

毕竟 Vulkan 细杂体现在，要实现图形学的 Hello World 程序绘制三角形绘制需要上千行代码，这对于熟悉 OpenGL 程序的开发人员来讲是不可想象的，甚至比自己用 CPU 实现一套软光栅器更为复杂！同时难度也体现在它的 API 复杂难懂，对于入门图形学的新手来讲并不是太简单。

无论这些 API 规范如何打架，着色器始终就是高效绘图的代名词，通过可编程着色器语言 Shader Language 在 GPU 中执行高效的图形渲染代码。

要了解着色器的功能以及如何有效地使用它们，了解渲染管道的基础知识非常重要。还必须学习如何编写 GLSL 程序，并找到好的教程和示例来学习。可以学习 SFML SDK 附带的着色器示例。

官方提供的 OpenGL Wiki 文档是最佳入门材料，上面有关于 Rendering pipeline，OpenGL Shading Language 的基本介绍。另外，shadertoy 网站也是一个膜拜大神着色器案例的好去处。

三大主流的 Shader 语言是：

- HLSL - Direct3D High Level Shader Language 高级着色语言
- GLSL - OpenGL Shader Language 
- CGSL - Nvidia C for Graphic

着色器 Shaders 就是在 GPU 上运行的程序，也就是对 GPU 编程的代码片断，所谓片断是指这种程序一般很小，可能最多就是上几百行代码。出于 OpenGL 的通用性，学习一般使用 GLSL (OpenGL Shading Language) 编写，语法上它和 C/C++ 语言非常相似。

与使用 OpenGL 状态机提供的固定状态和操作集相比，它为程序员提供了对绘图过程的更多控制，并且以更灵活、更简单的方式。借助这一额外的灵活性，着色器可用于创建过于复杂（如果不是不可能的话）的效果，用常规 OpenGL 函数无法描述这些效果：每像素照明、阴影等。现代显卡和新的 OpenGL Core Profile 图形接口已经完全基于着色器，称为固定管道的固定状态和函数集已被弃用，将来可能会被删除。

官方提供 GLSL Validator 工具用来检查着色器的错误，根据文档可以看到对应渲染管线的各种着色器。

GLSL Validator 验证工具基于文件扩展名来应用的特定于阶段的规则：

- *.vert*   for a vertex shader
- *.tesc*   for a tessellation control shader
- *.tese*   for a tessellation evaluation shader
- *.geom*   for a geometry shader
- *.frag*   for a fragment shader
- *.comp*   for a compute shader
- *.mesh*   for a mesh shader
- *.task*   for a task shader
- *.rgen*   for a ray generation shader
- *.rint*   for a ray intersection shader
- *.rahit*  for a ray any hit shader
- *.rchit*  for a ray closest hit shader
- *.rmiss*  for a ray miss shader
- *.rcall*  for a ray callable shader

工具提供了两个可执行程序：

- glslangValidator 着色器编译与规范验证程序，会根据扩展名来应用各个渲染阶段适用的验证规则。
- spirv-remap 中间语言编译器，将 GLSL AST 编译为 SPIR-V intermediate language。

GLSL Validator 是官方发布的开源 GLSL 编译器，命令行编译模式方便了用户直接测试着色器语法，而不必使用 C/C++ 相关依赖库及其编译执行过程，也不需要在主文件编写大量初始化代码。

只需要运行命令，将要进行语法检查的着色器程序传入，即可以看到是不有错误输出：

```sh
glslangValidator some.vert
```

OpenGL 4.5 最大变化就是支持 Khronos 自家开发新设计的 SPIR-V，Standard Portable Intermediate Representation，这是一种 GPU 通用计算和图形学的中间语言，最初是为 OpenCL 规范准备的，和下一代图形标准 Vulkan 差不多同时提出，也在不断发展完善。


有两种最基本的着色器类型：顶点着色器和片段（或像素）着色器。顶点着色器针对每个顶点运行，而片段着色器针对每个生成的片段（像素）运行。根据要实现的效果类型，可以提供顶点着色器、片段着色器或两者。

使用 Shader 进行渲染时，需要创建两个基础对象 shader 对象和 program 对象，简要来说，主要包括以下六个步骤：

- 创建一个顶点 shader 对象和一个片段 shader 对象
- 将源码附加到每一个shader对象上
- 编译 shader 对象
- 创建一个 program 对象
- 将编译后的 shader 对象附加到这个 program 对象上
- 链接这个 program 对象，然后执行着色渲染

顶点着色器*Vertex Shader*对应的是顶点 Vertex，相当于像素的概念，也是现代 GPU 最原始的输入数据，但是 GPU 希望使用它来完成更多的工作。所以，顶点一般由一组属性，除了基本的颜色属性外，还有一个 2D 或 3D 坐标、纹理坐标。

这些顶点会构成最基本的图元 Primitive，所谓图元就是最简单的图形，如点，线，三角形，四边形等等，在各版本 OpenGL 支持的图元类型如下：

| GL2.1 | GL3.3 | GL4.5 | 基本图元类型    |
| :---- | :---- | :---- | :----------   |
| ✓     | ✓     | ✓     | GL_POINTS     | 点 |
| ✓     | ✓     | ✓     | GL_LINES      | 线段 |
| ✓     | ✓     | ✓     | GL_LINE_STRIP | 多段线 |
| ✓     | ✓     | ✓     | GL_LINE_LOOP  | 线圈 |
| ✓     | ✓     | ✓     | GL_TRIANGLES  | 三角形 |
| ✓     | ✓     | ✓     | GL_TRIANGLE_STRIP | 三角形条带 |
| ✓     | ✓     | ✓     | GL_TRIANGLE_FAN   | 三角形扇 |
| ✓     | ✄     | ✄     | GL_QUADS      | 四边形 |
| ✓     | ✄     | ✄     | GL_QUAD_STRIP | 四边形条带 |
| ✓     | ✄     | ✄     | GL_POLYGON    | 多边形(凸) |
| -     | ✓     | ✓     | GL_LINE_STRIP_ADJACENCY   |  |
| -     | ✓     | ✓     | GL_LINES_ADJACENCY    |  |
| -     | ✓     | ✓     | GL_TRIANGLE_STRIP_ADJACENCY   |  |
| -     | ✓     | ✓     | GL_TRIANGLES_ADJACENCY    |  |
| -     | -     | ✓     | GL_PATCHES    | |

在绘制命令发出后，顶点着色器就被调用以处理输入的顶点数据，它应该是简单的着色器程序，甚至只是做数据的拷贝工作，供后续的着色流程添加更复杂的处理。

在顶点着色器程序运行之后，会依次进行以下操作：

- `Tessellation Shaders` 细分着色器，根据设置的细分等级不同，可能加大渲染工作量，也可能降低渲染工作量。基本图元细分为更多的基本图形，创建出更加平滑的视觉效果。或者设置更低的细分，减少细节，降低渲染工作量。
- `Geometry Shader`，几何着色器可以在图元的基础上再构建生成其它图元，比如利用四个点可以构造出多个三角形，而且每个输入的图元只会执行一次几何着色器。所以，在最坏的情况下，就是输入的图元全是点，这样几何着色器和顶点着色器执行次数一样。
- `Geometry Shader` 几何着色器，输入基本图元形式的顶点的集合，通过产生新顶点构造出新的基本图元来生成其他形状。
- `Primitive Assembly` 基本图元装配，把所有输入的顶点数据作为输入，输出制定的基本图元，为光栅化作准备。
- `Rasterization` 光栅化即像素化，把细分着色器输出的基本图形映射为屏幕上网格的像素点，生成供片段着色器处理的片段，光栅化包含一个剪裁操作，会舍弃超出定义的视窗之外的像素，来提升执行效率。
- `Fragment Shader` 片段着色器，主要作用是计算出每一个像素点最终的颜色，通常片段着色器会包含 3D 场景的一些额外的数据，如光线，阴影等。在这个阶段里会使用深度测试，通常也称作 Z-Buffering，和模板测试 Stencil Test 来决定一个片元是否是可见的。如果一个片元成功地通过了所有激活的测试，那么它就可以被直接绘制到帧缓存中了，更新它对应的像素的颜色值，也可能包括深度值。如果开启了 blending 融合模式，那么片元的颜色会与该像素当前的颜色相叠加，形成一个新的颜色值并写入帧缓存中。

根据 OpenGL 文档，详细的渲染管线工序如下：

- Vertex Specification
    - Vertex Rendering
    - Primitive
- Vertex Processing
    - Vertex Shader
    - Tessellation
    - Geometry Shader
- Vertex Post-Processing
    - Transform Feedback
    - Clipping
- Primitive Assembly
    - Face Culling
- Rasterization
- Fragment Shader
- Per-Sample Processing
    - Scissor Test
    - Stencil Test
    - Depth Test
    - Blending
    - Logical Operation
    - Write Mask

片段着色器阶段也基本就是渲染管线的最后流程，经过最后的处理就得到了屏幕上输出的图形。

Mastering SFML game development by Pupius, Raimondas 书中提供了一张 Programmable pipeline 示意图，很简明地表达了渲染管线各个工序的作用：

![Programmable pipeline - Mastering SFML game development by Pupius, Raimondas](https://github.com/jimboyeah/spine-sfml-demo/blob/master/images/Programmable%20pipeline%20-%20Mastering%20SFML%20game%20development%20by%20Pupius,%20Raimondas.jpg)


以下是根据 OpenGL Programming Guide 第 9 版本制作的 GPU 渲染流程图：

```sh
+========+      +========+      +==============+    +==============+
| Vertex |      | Vertex |      | Tessellation |    | Tessellation |
| Data   |  ->  | Shader |  ->  | Control      | -> | Evaluation   |
+========+      +========+      | Shader       |    | Shader       |
                                +==============+    +==============+
  +==========+                                                |
  | Culling  |      +===========+      +==========+           |
  |   and    |      | Primitive |      | Geometry |           |
  | Clipping |  <-  | Setup     |  <-  | Shader   |  <--------+
  +==========+      +===========+      +==========+
       |  
       V                              +=============+
+===============+    +==========+     | █▀▀░█░█░▀█▀ |
| Rasterization | -> | Fragment | ->  | █▀▀░▄▀▄░░█░ |
+===============+    | Shader   |     | ▀▀▀░▀░▀░░▀░ |
                     +==========+     +=============+

        Figure 1.2 OpenGL pipeline
```

这里，有几个关键的阶段。

- ✒ 从顶点数据输入到 *Geometry Shader* 几何着色器为止，这部分是整个渲染流程的前端部分。
- ✒ 其次，是固定功能部分，Primitive Assembly, Clipping, Rasterization 等阶段就是将代表场景的图元转化为像素，会应用 Viewport Transformation 这类操作以将虚拟 3D 场景映射到 2D 的屏幕空间上。主要是光栅化，几何空间上的顶点通过投射变换，确定了对应屏幕光栅的位置，也就是几何图形空间的点与像素坐标的对应关系确立。
- ✒ 最后，是以 *Fragment Shader* 为分界的渲染后期阶段，这个阶段最重要的工作就是在将数据发送到帧缓冲区前确定像素的颜色。

其中，中间部分的光栅化流程涉及了非常抽象的概念。在软件模拟的 3D 世界中，所有东西都是用数学去表达的。空间的一个顶点在什么位置，用三维向量表示，移动、旋转后在什么位置，需要进行线性变换，又叫仿射变换。而要将这个数学抽象的 3D 世界转化为屏幕空间对应的 2D 坐标，还需要根据一个观测角度来决定，这相当于有一台隐藏的摄像机在给抽象世界拍照，再将照片显示在屏幕上。

这里涉及以下这些基本图形学概念：

- *Model Matrix* 模型矩阵：通过对物体进行位移、缩放、旋转来改变物体在世界空间中的位置、大小和朝向。
- *View Matrix* 观察矩阵：由一系列的位移和旋转的组合来完成，平移/旋转场景从而使得特定的对象被变换到摄像机的前方。
- *Projection Matrix* 投影矩阵：定义一个观察箱 *Viewing Box* 来限定可视物体的空间范围，也称为平截头体 *Frustum*，范围内的坐标都会最终出现在用户的屏幕上。将抽象 3D 空间坐标转化为对应的 2D 光栅坐标被称之为投影*Projection*。
    - *Orthographic Projection Matrix* 正射投影矩阵方式定义了一个类似立方体的平截头体，可以将远处的物体与近处的物体以同样的方式投射而不会产生远近不同的差别（w 分量没有被改变）。
    - *Perspective Projection Matrix* 透视投影矩阵 则是符合实际生活的投身方式，离你越远的东西看起来更小，这个效果称之为透视。
- *Viewport Transform* 视口变换：最后将裁剪坐标变换为屏幕坐标，这个过程叫视口变换。视口变换将位于 -1.0 到 1.0 范围的坐标变换到由 glViewport 函数所定义的坐标范围内，最后变换出来的坐标将会送到光栅器，将其转化为片段。

顶点变换可能涉及五个不同的坐标系统：

- Local Space 局部空间；
- World Space 世界空间；
- View Space 观察空间；
- Clip Space 裁剪空间；
- Screen Space 屏幕空间；

Perspective Projection vs. orthographic Projection:

![https://stackoverflow.com/questions/36573283/from-perspective-picture-to-orthographic-picture](https://github.com/jimboyeah/spine-sfml-demo/blob/master/images/From_perspective_picture_to_orthographic_picture.png)

OpenGL 使用的坐标是笛卡尔坐标系统，即屏幕向右、向上分别为 X、Y 轴正方向 ，顶点的值直接反映在屏幕。

始终需要明确的一点是 OpenGL 世界坐标系是`右手坐标系` right-hand system ，在二维屏幕上，屏幕水平方向是 X 轴方向，向右为正，屏幕竖起方向是 Y 轴方向，向上为正，垂直于屏幕的方向是 Z 轴方向，从屏幕里往外为正。即右手中指向自己表示 Z 轴、食指竖起向上表示 Y 轴、母指向右表示 X 轴。即使手腕怎么转动，右手系统这种轴向关系是主要的参考。

- OpenGL 使用右手系，默认窗体中心为原点，左下角为负，右上角为正；
- 屏幕鼠标的 2D 坐标左上角为原点，右正角为正；

当然，可以通过透视变换来改变屏幕的图像。

仿射变换（Affine Transformation）和齐次坐标系（Homogeneous Coordinate)是计算机图形学中经常碰到的基本概念，在闫令琪的 Game101 现代计算机图形学入门网络公开课上十分简明地讲解这些图形学理论基础。

GPU 图形渲染管线非常复杂，它包含很多可配置的部分。但对于大多数场合，只需要配置顶点着色器、片段着色器。其它是可选的，通常可以使用默认着色器。

GPU 中没有默认的顶点着色器和片段着色器，不可能随意给出某些顶点，然后涂上点颜色就渲染展示出来，所以必须至少定义一个顶点着色器和一个片段着色器。对于初始学者，这确实是有点难，因为即使是渲染一个简单的三角形，也必需学习一堆关于 GPU 渲染管线的知识。另一个难点是，它结合了线性代数基础原理，又结合了图形美学，所以这就是一个技术美术的工作。

在整个渲染流水线中，以下是一些 GPU 图形编程涉及顶点数据及其使用方式的基础概念：

- `VBO` - Vertex Buffer object 在显卡存储空间中开辟出的一块内存缓存区用来储存顶点数据，增加顶点进入 GPU 效率的方法。它们可以存储在显存中的缓冲区，以最快的 GPU 速度去访问数据。

- `VAO` - Vertex Array Object 顶点数组对象，定义了批量的顶点，和着色器变量起连接作用。VBO 保存了一个模型的顶点属性信息，每次绘制模型之前需要绑定顶点的所有信息，当数据量很大时，重复这样的动作变得非常麻烦。VAO 可以把这些所有的配置都存储在一个对象中，每次绘制模型时，只需要绑定这个 VAO 对象就可以了。 缓存顶点的方式，比起零散的顶点传输效率要高。

- `EBO` - Element Buffer Object 索引缓冲对象，或者称 `IBO` - Index Buffer Object，相当于 OpenGL 中的顶点数组的概念。通过顶点索引来解决顶点重用问题，可以减少内存空间浪费，提高执行效率。当需要使用重复的顶点时，通过顶点的位置索引来调用顶点，而不是对重复的顶点信息重复记录，重复调用。

在没有 VBO 的图形绘制，如 `glDrawArrays` 都是从本地内存推送顶点数据到给 OpenGL 核心，这样中间就会间隔着频繁的 CPU -> GPU 数据对拷操作，增大开销，从而降低效率。

使用 VBO 可以直接将顶点数据缓存到 GPU 开辟的一段内存中，直接从显存中获取而不必再走一遍主机内存，这样就能提升绘制的效率。VAO 就是组织批量的 VBO 数据，则 EBO 就是通过索引来使用顶点数据提高数据复用效率。

在 OpenGL 4.6 Core Profile 规范手册的封面上，完整地描绘了数据的流向。还有官方的 OpenGL API Reference Card 文档也有详细的 OpenGL Pipeline 流程图。

![Data Flow - OpenGL 4.6 Core Profile](https://github.com/jimboyeah/spine-sfml-demo/blob/master/images/glspec46.core.jpg)

还有游离在渲染管线之外的一个全局性的计算着色器 Compute Shader，它可以对各个阶段的渲染进行调整。


### 🗝 OpenGL History & Core Profile
- https://www.khronos.org/opengl/wiki/History_of_OpenGL
- https://www.khronos.org/opengl/wiki/Shader_Compilation
- https://www.khronos.org/opengl/wiki/Core_And_Compatibility_in_Contexts
- https://www.khronos.org/opengl/wiki/OpenGL_Extension
- https://www.khronos.org/registry/OpenGL/extensions/EXT/
- https://www.khronos.org/opengl/wiki/Debug_Output
- https://www.khronos.org/opengl/wiki/OpenGL_Error
- OpenGL Insights OpenGL, OpenGL ES, and WebGL Community Experiences by Patrick Cozzi Christophe Riccio
- OpenGL Insights Source Code https://github.com/OpenGLInsights/OpenGLInsightsCode
- OpenGL and Vulkan https://geek-docs.com/vulkan/vulkan-tutorial/vulkan-and-opengl.html
- FreeGLUT HelloWorld https://github.com/jimboyeah/spine-sfml-demo/blob/master/examples/opengl.cpp

在早期，OpenGL 和 GLSL 的版本发行并不一致，直到 OpenGL 2.0 开始，才对应发行一个版本号。但版本号并不总是一致，直到 OpenGL 3.3 开始才一致。根据对应关系经 GLSL 1.1 对应的是 OpenGL 2.0，GLSL 1.5 对应 OpenGL 3.2：

OpenGL 历史版本更新：

|    时间    |     版本     | GLSL |                    主要特性增加                    |
|------------|--------------|------|----------------------------------------------------|
| 1992/01    | OpenGL 1.0   | -    |                                                    |
| 1997/01    | OpenGL 1.1   | -    | Vertex arrays                                      |
| 1998/03/16 | OpenGL 1.2   | -    | Imaging subset (optional)                          |
| 1998/10/14 | OpenGL 1.2.1 | -    | Define ARB extensions concept                      |
| 2001/08/14 | OpenGL 1.3   | -    | Compressed texture format                          |
| 2002/07/24 | OpenGL 1.4   | -    | Automatic mipmap generation                        |
| 2003/07/29 | OpenGL 1.5   | -    | Buffer object                                      |
| 2004/09/07 | OpenGL 2.0   | 1.10 | OpenGL Shading Language 1.00                       |
| 2006/07/02 | OpenGL 2.1   | 1.20 |                                                    |
| 2008/08/11 | OpenGL 3.0   | 1.30 | Deprecation Model                                  |
| 2009/03/24 | OpenGL 3.1   | 1.40 |                                                    |
| 2009/08/03 | OpenGL 3.2   | 1.50 | Geometry shaders, in/out interface block           |
| 2010/03/11 | OpenGL 3.3   | 3.30 |                                                    |
| 2010/03/11 | OpenGL 4.0   | 4.00 | Tessellation Shader                                |
| 2010/07/26 | OpenGL 4.1   | 4.10 |                                                    |
| 2011/08/08 | OpenGL 4.2   | 4.20 |                                                    |
| 2012/08/06 | OpenGL 4.3   | 4.30 | Arbitrary Compute Shaders                          |
| 2013/07/23 | OpenGL 4.4   | 4.40 |                                                    |
| 2014       | OpenGL 4.5   | 4.50 |                                                    |
| 2017       | OpenGL 4.6   | 4.60 | The SPIR-V language can be used to define shaders. |

关键的版本有：

- OpenGL 2.0 引入着色器语言，支持顶点着色器、片段着色器；
- OpenGL 3.2 引入几何着色器；
- OpenGL 4.0 引入细分着色器；
- OpenGL 4.3 引入计算着色器；
- OpenGL 4.6 正式引入 SPIR-V 标准可移植中间层语言；

OpenGL 4.5 最大变化就是支持 Khronos 自家开发新设计的 SPIR-V，Standard Portable Intermediate Representation，这是一种 GPU 通用计算和图形学的中间语言，最初是为 OpenCL 规范准备的，和下一代图形标准 Vulkan 差不多同时提出，也在不断发展完善。

着色器就是渲染管线中的可编程阶段执行的 GUP 代码，也就是一个编译单元，互相独立的小段程序。顶点着色器各片段着色器是两个最基本的用户定义的着色器，各个着色器的输入输入是受约束的，片段着色器只能访问当前输入的片段，不可以访问邻近的其它片段。

而相对自由的计算着色器是可以访问其它着色器处理器可使用的资源，包括纹理、缓冲、图像变量、原子计数器等，它没有固定的输出。它不是图形管道的一部分，其副作用是可以更改图像、存储缓冲区和原子计数器。

计算着色器操作一个分组，即执行相同代码的一组着色器调用，可能是并行的。工作组内的调用之间可以通过共享变量共享数据，并发出内存和控制屏障，memory and control barriers，以实现同一工作组的其他成员同步。


OpenGL 与 OpenGL ES/SC 的版本关联：

- OpenGL 1.3 对应 OpenGL ES 1.0 和 OpenGL SC 1.0
• OpenGL 1.5 对应 OpenGL ES 1.1
• OpenGL 2.0 + extra features 对应 OpenGL ES 2.0
• OpenGL 3.x 对应 OpenGL ES 3.0 (Halti) Expected


OpenGL® 作为业界最为广泛使用的 2D/3D 图形库接口标准，应用在成千上万的各式各样的计算机的程序中。从初期的崭露头角，到与 Direct3D 激烈竞争，后经历黯淡被 Khronos 接手又发扬光大，已经历经波折发展了 20年。由于过去的黯淡，至今甚至仍有人站在错误的时间角度认为它是落后的——它从未停止它前进的步伐。

作为强有力的竞争者，DirectX 始终靠着强有力的金主爸爸独霸 Windows 平台，官方自从 Windows 95 时代提供了 OpenGL 1.1 的实现，就再也没有更新过了。就连 1996 年同时代出现的 Opengl Superbible: The Complete Guide to Opengl Programming for Windows Nt and Windows 95 也更新到现 2016 的第七版 OpenGL SuperBible: comprehensive tutorial and reference。

Khronos Group 接手 OpenGL 之后，近几年发展速度迅猛，版本的更新已经到了 OpenGL 4.6，其功能不在 Direct3D 11 之下，且被 Nvidia 和 AMD 主流显卡全面支持。值得注意的是，通用性极好的 OpenGL 在 96.8% 手持设备得到了支持，它们大多都只使用桌面 OpenGL 的子集 OpenGL ES 作为他们的图形编程接口，许多家用游戏机也使用 OpenGL 作为其图形的编程接口。OpenGL 已经重新回到主流的地位！

因为硬件进化趋势的一致性，API 的使用上，OpenGL 也渐渐地和 Direct3D 更加的相似了，在 OpenGL 4.4 的环境下，基本可以“还原”出和 Direct3D 11 一样的接口，从 Direct3D 11 移植到 OpenGL 程序不再是一件难事。

OpenGL 已经不是单一的 API 接口规范，还有移动设备适用的子集 OpenGL ES，和安全敏感行业适用的 OpenGL SC（OpenGL - Safety Critical Profile）开放标准，高安全敏感性的特殊市场包括航空工业，军事，医学和汽车业等等。


从 1992 年 1 月，最早版本的 OpenGL 1.0 由 Mark Segal 和 Kurt Akeley 发布。

OpenGL 最初是作为 Silicon Graphics 工作站专有图形 API - Iris GL 的一种开放的、可复制的替代品创建的。

虽然 OpenGL 最初在某些方面与 Iris GL 相似，但由于缺乏正式的规范和一致性测试，没有在 Iris GL 广泛采用。

Mark Segal 和 Kurt Akeley 编写了 OpenGL 1.0 规范，该规范试图将有用图形 API 的定义形式化，并使跨平台非 SGI 第三方实现和支持变得可行。

但，OpenGL API 1.0 版中一个值得注意的遗漏是纹理对象。Iris GL 对各种对象都有定义和绑定阶段，包括材质、灯光、纹理和纹理环境。OpenGL 避开了这些对象，转而支持增量状态更改，其思想是集体更改可以封装在显示列表中。除了关键部分的纹理对象 *glBindTexture* 没有明确定义阶段之外，它仍然是一种理念。

OpenGL 经历了一系列功能增量修订，逐渐增加融入核心 API 的扩展 API。

- OpenGL 1.1 在核心 API 中添加了 *glBindTexture* 扩展，顶点数组替代了立即模式的顶点绘制 API。时隔 5 年更新发布的版本，而另一边 Direct3D 已经上场，尤其是红色警戒游戏大卖。
- OpenGL 2.0 整合了重要新增功能 GLSL 着色语言，这是一种类似 C 语言，可用于 GPU 编程管道的转换和片段着色阶段。
- OpenGL 3.0 增加了“弃用”概念：Deprecation Model，在以后的版本中将某些功能标记为删除状态。
- OpenGL 3.1 基于现有的弃用模型，和后续将要实现的 Core Profile 重大修改，删除了大多数不推荐的功能。
- OpenGL 3.2 创建了两个 OpenGL 上下文概念：Core Profile 和 Compatibility Profile。

着色器语言扩展就是 ARB_shading_language_100，这个 OpenGL 2.0 引入的扩展就是 ARB 认可的扩展。

通过编写 OpenGL 着色器脚本，再经过 OpenGL 编译成 Program Object，也就是相应的二进制指令并上传给 GPU 执行。 

OpenGL 4.x 才引入细分着色器和计算着色器的支持，Tessellation shaders and Compute Shaders。

在谈论渲染管线或图形管线时，经常会涉及 GUP 渲染管线和软件的渲染管线模型，有时会混淆不清。不过越来越统一的硬件图形处理流程下，通常它们又是指同样一件事。


2008 年 8 月 11 日发布的 OpenGL 3.0 这个版本代号叫做 Longs Peak，包含了很多大量改变原有工作方式，从根本性改变 API 调用方式的内容。从此开始分 *Core Profile* 和 *Compatibility Profile* 两种上下文工作方式，并且 Khronos Group 希望只支持 Core Profile。但这个革新性的规范被许多厂商明确表示拒绝，他们并表示会继续支持许多被划入 Compatibility Profile 的扩展，所以 Compatibility Profile 被改为可选项。

OpenGL 3.0 的出现改变了过去 OpenGL 向后兼容的特性，在一定程度上简化了 API 的臃肿以及增加了 API 的灵活度。

在未来，OpenGL 将会由 Vulkan API 接棒，和 DX12 以及 Metal API 等图形库一较高下。

Vulkan 与 OpenGL 相比，它可以更详细对显卡描述你的应用程序打算做什么，从而可以获得更好的性能和更小的驱动开销。

Vulkan 的设计理念与 Direct3D 12 和 Metal 基本类似，但 Vulkan 作为 OpenGL 的替代者，它设计之初就是为了跨平台实现的，可以同时在 Windows、Linux 和 Android 开发。甚至在 Mac OS 系统上，Khronos 也提供了 Vulkan 的 SDK，虽然这个 SDK 底层其实是使用 MoltenVK 实现的。

关于 OpenGL 的错误处理，在内部有一个错误列表记录，可以枚举出当前发生的所有错误代码：

```cpp
GLenum err;
while((err = glGetError()) != GL_NO_ERROR)
{
  // Process/log the error.
}
```

一个简单的方法是注册一个错误处理回调函数：

```cpp
void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

// During init, enable debug output
glEnable              ( GL_DEBUG_OUTPUT );
glDebugMessageCallback( MessageCallback, 0 );
```


在 OpenGL Insights 的第一章展示了以下旧风格的 OpenGL 应用程序：

```cpp
#include <GL/glut.h>
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glEnd();
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("Hello World");
    glutDisplayFunc(display);
    glutMainLoop();
}
// OpenGL Insights Chapter 1: Teaching Computer Graphics Starting with Shader-Based OpenGL
// Listing 1.1. Hello World: Old Style
```

可以通过 git 克隆随书代码：

```sh
git clone git@github.com:OpenGLInsights/OpenGLInsightsCode
```

这个示范程序用旧风格的代码画了一个方块，有三个主要的问题：

1. 使用即时模式。
2. 依赖固定功能管线。
3. 使用状态变量的默认值。

在基于着色器的新式渲染管线上，以上使用到的 API 基本都废弃了，除了用于清理画布的 *glClear()*。理解这些函数为何要移除，是理解为何要使用最新的可编程的 OpenGL 管道的关键。


将渲染管线简化一下，表达这个示范程序的缺点：

```sh
Application                                                     Fragments         Pixels
------------                                                 ---------------    ----------
+========+      +========+    +=================+    +============+    +===========+    +========+
| Vertex |      | Vertex |    | Clipping and    |    | Rasterizer | -> | Fragment  | -> | Frame  |
| States |  ->  | Shader | -> | Primitive Setup | -> | Evaluation |    | Shader    |    | Buffer |
+========+      +===^====+    +=================+    +============+    +=====^=====+    +========+
                    |                                                        |
----------          +--------------------------------------------------------+
    CPU                                     GPU Rendering Pipeline

                               Figure 1.2. Simplified pipeline.
```

作为 OpenGL 早期的基础管道模型，它强调即时模式图形。一旦生成每个顶点，就触发顶点着色器的执行。因为几何处理是由顶点着色器在 GPU 上执行的，所以这个简单的示范程序需要在每次显示矩形时向 GPU 发送四个顶点位置。

基于早期的 OpenGL 渲染管线模型的程序掩盖了 CPU 和 GPU 之间的瓶颈，并隐藏了现代 GPU 上可用的并行性。

其次，尽管能够依靠数量不多的数据直接调用 API 进行绘图，但是这种方式在处理更复杂的几何图形时，应用程序的性能就会形成大问题。

最后，也是最主要的问题是，这种将 OpenGL 作为状态机的程序开发类型有些过时。尽管状态很重要，但使用固定函数管道和默认值隐藏了 OpenGL 中控制几何体渲染方式的大量状态变量。随着简单程序的扩展，开发者往往会迷失在大量的状态变量中，并且很难处理状态变量变化的意外副作用。在 OpenGL 的最新版本中，大多数状态变量都已被弃用，应用程序会创建自己的状态变量。

术语固定函数管道“Fixed Function Pipeline”通常指 OpenGL 旧版本中存在的一组可配置处理状态，这些状态后来被相应的着色器取代。虽然当前的 OpenGL 管道仍然保持不可编程状态，但这通常不是人们所说的“固定功能”。

OpenGL 的目的是向应用程序开发人员公开底层图形硬件的功能，通用的 OpenGL 渲染管道与现代 GPU 硬件大致相同。然而，取代可编程阶段的是内置的数学运算。用户将提供特定的矩阵和其他配置参数。通过这种方式，用户可以让系统做一些有用的事情，但它缺乏完全可配置系统的弹性。

尽管，OpenGL 2.0 已经引入着色器语言，支持可编程的管道，但是它仅仅是个可选项，因为开发者仍然可以访问所有现在不推荐使用的功能。应用程序可以有自己的着色器，也可以使用旧式的即时模式进行绘图。着色器可以访问大多数 OpenGL 状态变量，这简化了使用着色器编写应用程序的过程。并且，在第一个以即时模式和固定函数管道开始的 OpenGL 课程中，很少有讲师真正深入接触到可编程着色器。充其量，着色器在课程结束时会有一个简短的介绍。

OpenGL 3.0 发布时声明，不在 OpenGL 3.1 提供向后兼容，但迫于现状，还是提供了 Compatibility Profile 工作模式。而要使用更先进的 GPU 渲染能力，就要使用 OpenGL 3.1 Core Profile 工作模式，这是基于着色器程序的绘图模式。显然，OpenGL 同时提供这两套工作模式，不仅为自身规范的定制增加了工作量，同时也为从事 OpenGL 的开发者增加了学习难度。

在 OpenGL Insights 的第一章展示的第二个 OpenGL 示范程序是基于可编程管道的，也就是新的 OpenGL 工作模式。顶点着色器和片断着色器是唯一两个必需提供的着色器，其它是可选，代码也简化到只为演示使用。

即使是最简单的应用程序也可以分为三个部分：

- 设置着色器和与窗口系统的接口的初始化；
- 构造数据并将数据发送到 GPU 的阶段；
- 最后在 GPU 上呈现数据的阶段；

在基于着色器的方法中，可以实现一个函数 *InitShaders*，它读取着色器文件，编译它们，链接它们，如果成功，返回一个程序对象。即使使用 InitShader，第一阶段并不比传统方法更简单。对于旧式的示例，第三阶段只需要清除一些缓冲区和调用 *gldrawArray()* 绘制给定顶点的图形。

中间阶段从根本上不同于即时模式编程，即使是最简单的程序，也必须引入顶点缓冲区对象和顶点数组对象，即：

- *glGenVertexArrays()* 在 GPU 专属内存区申请空间以存放一个保存顶点数据的 VAO 对象；
- *glGenBuffers()* 在 GPU 专属内存区申请空间存放一个 VBO 顶点缓冲区对象。

以下示范程序显示内容与前面旧式的即时绘图方式输出相同，为了简化并突出结构，以下程序代码片断只作为展示使用，将着色器程序内容的读取和初始化设置放到后面。此代码并不完全，在 Github 仓库上有一份修改过的 FreeGLUT HelloWorld 供参考，仅作为显示如何加载 OpenGL 使用。

```cpp
#include "Angel.h"

void init( void )
{
    vec2 points[6] =
    {
        vec2( -0.5, -0.5 ), vec2(  0.5, -0.5 ),
        vec2(  0.5,  0.5 ), vec2(  0.5,  0.5 ),
        vec2( -0.5,  0.5 ), vec2( -0.5, -0.5 )
    };
    GLuint vao, buffer;
    GLuint glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    GLuint glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER , buffer);
    glBufferData(GL_ARRAY_BUFFER , sizeof(points), points, GL_STATIC_DRAW);
    GLuint program = InitShader("vsimple.glsl", "fsimple.glsl");
    glUseProgram(program);
    GLuint loc = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glClearColor(0.0, 0.0, 0.0, 1.0);
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES , 0, 6);
    gutSwapBuffers();
}
int main(int argc, char **argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("Hello World");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
// OpenGL Insights Chapter 1: Teaching Computer Graphics Starting with Shader-Based OpenGL
// 1.5 Hello World: New Style
// Listing 1.2. Hello World redux.
```

关于向量类型的定义，可以参考 GLM - OpenGL Mathematics 数学库的实现，OpenGL Insights 随书代码就有用到它，可以在以下章节的代码中找到：

- Chapter 15 Depth of Field with Bokeh Rendering
- Chapter 26 Indexing Multiple Vertex Arrays

顶点着色器会将输入的顶点坐标 *a_position* 直接拷贝到输出变量。

```c glsl
in vec4 vPosition;
void main()
{
    gl_Position = vPosition;
}
// Listing 1.3. Hello World vertex shader.
```

```c glsl
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
// Listing 1.4. Hello World fragment shader.
```

OpenGL 3.1 开始，像素处理就截然不同。位图和像素写入功能都是预先准备好的，并保留了一些相关的功能，例如使用累积缓冲区的功能。虽然这些功能易于使用，但效率极低。在这种情况下，编程的简单性会导致 GPU 的使用不佳，并且由于 CPU 和 GPU之 间来回传输大量数据而导致瓶颈。

另一种方法是使用片段着色器来操纵纹理，例如，以下这个简单片段着色器足以演示图像平滑处理，对周边 4 个像素进行平均值处理得到连续淡化的平滑效果，并且可以很容易地进行更改以执行其他成像操作。

```c glsl
in vec2 texCoord;
out vec4 FragColor;
uniform float d;
uniform sampler2D image;

void main()
{
    FragColor =
    ( texture( image , vec2(texCoord.x + d, texCoord.y))
    + texture( image , vec2(texCoord.x, texCoord.y + d))
    + texture( image , vec2(texCoord.x - d, texCoord.y))
    + texture( image , vec2(texCoord.x, texCoord.y - d))) / 4.0;
}
// Listing 1.5. Image-smoothing shader.
```

以下是 *InitShaders* 函数实现参考，它读取着色器文件，编译它们，链接它们，如果成功，返回一个程序对象。

在编写 ReadFile() 这个函数时，我就犯了两错误：

- 参数 out 没使用引用，这导致数据无法返回给函数外部；
- 读取使用的 getline() 这会过滤掉换行符号，这会导致正常着色器代码会被注解掉。

还好，在 main() 函数中使用了 function-try-block 进行处理，否则，发现不了问题所在，调试程序就无从下手。

以下代码演示了如何在 FreeGLUT 加载 OpenGL 扩展 API，只展示了 glDebugMessageCallback()，其它 API 加载可以参考 KHnoros 官方文档提供的头文件。 

```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/freeglut.h>

using namespace std;

/*
 * OpenGL 2+ shader mode needs some function and macro definitions,
 * avoiding a dependency on additional libraries like GLEW or the
 * GL/glext.h header
 * Reference: 
 * https://github.com/KhronosGroup/OpenGL-Registry/tree/main/api/GL/glext.h
 */
#ifndef GLAPIENTRY
#define GLAPIENTRY APIENTRY
#endif

PFNGLDEBUGMESSAGECALLBACKARBPROC glDebugMessageCallback;

void initExtensionEntries(void)
{
    glDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKARBPROC) glutGetProcAddress ("glDebugMessageCallback");
    //...
}

bool ReadFile(string fileName, string &out)
{
    string line;
    stringstream ss;
    ifstream file (fileName, ios::ate); // position at end for size
    int size = file.tellg();
    file.seekg (0, ios::beg); // position at beginning of content
    if (!file.is_open()) return false;
    while (getline (file, line))
    {
        ss << line << endl;
    }
    file.close();
    out = ss.str();
    return true;
}

class InitShaderError: public runtime_error 
{
public:
    InitShaderError(char *str): runtime_error(str) {}
    InitShaderError(string str): runtime_error(str) {}
    InitShaderError(const InitShaderError &other): runtime_error(other) {}
};

void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        throw InitShaderError(string("Error creating shader type ") + to_string(ShaderType));
    }

    const GLchar* p[1];
    p[0] = pShaderText;
    GLint Lengths[1];
    Lengths[0]= strlen(pShaderText);
    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);
    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        throw InitShaderError(string("Error compiling shader type ") + to_string(ShaderType) + ": "+ InfoLog);
    }

    glAttachShader(ShaderProgram, ShaderObj);
}

GLuint InitShader(const char *vsFileName, const char *fsFileName)
{
    GLuint ShaderProgram = glCreateProgram();

    if (ShaderProgram == 0) {
        throw InitShaderError(string("Error creating shader program."));
    }
    
    string vs, fs;

    if (!ReadFile(vsFileName, vs)) {
        throw InitShaderError(string("Faile to read file content: ")+vsFileName);
    };

    if (!ReadFile(fsFileName, fs)) {
        throw InitShaderError(string("Faile to read file content: ")+fsFileName);
    };

    AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
    AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        throw InitShaderError(string("Invalid shader program: ")+ErrorLog);
    }

    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        throw InitShaderError(string("Invalid shader program: ")+ErrorLog);
    }

    return ShaderProgram;
}

template <typename T>
class Vector2
{
public:
    Vector2(){};
    Vector2(T X, T Y);
    T x; ///< X coordinate of the vector
    T y; ///< Y coordinate of the vector
};

template <typename T>
Vector2<T>::Vector2(T X, T Y): x(X), y(Y) {};

typedef Vector2<float>  vec2;


void init( void )
{
    vec2 points[6] =
    {
        vec2( -0.5, -0.5 ), vec2(  0.5, -0.5 ),
        vec2(  0.5,  0.5 ), vec2(  0.5,  0.5 ),
        vec2( -0.5,  0.5 ), vec2( -0.5, -0.5 )
    };
    GLuint vao, buffer;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER , buffer);
    glBufferData(GL_ARRAY_BUFFER , sizeof(points), points, GL_STATIC_DRAW);
    string vert = "../examples/opengl_insights_ch1.vert";
    string frag = "../examples/opengl_insights_ch1.frag";
    GLuint program = InitShader(vert.c_str(), frag.c_str());
    glUseProgram(program);
    GLuint loc = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glClearColor(0.1, 0.1, 0.1, 1.0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES , 0, 6);
    glutSwapBuffers();
}

void GLAPIENTRY
MessageCallback( GLenum source, GLenum type, GLuint id, GLenum severity, 
                 GLsizei length, const GLchar* message, const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "`GL ERROR`" : "" ), type, severity, message );
}

int main(int argc, char **argv) try
{
    glutInit (&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("Hello World");

    cout << "GL_SHADING_LANGUAGE_VERSION:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    cout << "GL_SHADING_LANGUAGE_VERSION_ARB:" << glGetString(GL_SHADING_LANGUAGE_VERSION_ARB) << endl;
    // cout << "GL_EXTENSIONS:" << glGetString(GL_EXTENSIONS) << endl;
    cout << "GL_RENDERER:" << glGetString(GL_RENDERER) << endl;
    cout << "GL_VENDOR:" << glGetString(GL_VENDOR) << endl;
    cout << "GL_VERSION:" << glGetString(GL_VERSION) << endl;

    initExtensionEntries();

    // During init, enable debug output
    glEnable              ( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( MessageCallback, 0 );
    init();
    cout << "GL_GetError: 0x" << hex << glGetError() << endl;
    glutDisplayFunc(display);
    glutMainLoop();
}
catch (runtime_error ex)
{
    cout << ex.what() << endl;
}
```

程序中加入了信息打印功能，用于查询当前的 OpenGL 版本，以及已有的扩展名字列表。

因为使用了 FreeGLUT，在调用 *glGetString()* 函数之前，先调用 *glutInit()* 与 *glutCreateWindow()* 以初始化 OpenGL 上下文化，非则会返回 null，不能返回正确的值。通过 *glGetError()* 也可以查询到一个错误号 1282。

```cpp
#define GL_INVALID_VALUE 0x050
```

在 OpenGL Insights 随书代码中也可以看到在获取 OpenGL 接口信息时这种方法的应用：

```cpp
GLFWvidmode vidmode;

// Initialise GLFW
glfwInit();

// Open a temporary OpenGL window just to determine the desktop size
if( !glfwOpenWindow(256, 256, 8,8,8,8, 32,0, GLFW_WINDOW) )
{
    glfwTerminate(); // glfwOpenWindow failed, quit the program.
    return 1;
}
glfwGetDesktopMode(&vidmode);
glfwCloseWindow();

printf("GL vendor:       %s\n", glGetString(GL_VENDOR));
printf("GL renderer:     %s\n", glGetString(GL_RENDERER));
printf("GL version:      %s\n", glGetString(GL_VERSION));
printf("Desktop size:    %d x %d pixels\n", vidmode.Width, vidmode.Height);
```

在 SFML 源代码中 GLLoader.hpp 可以找到 OpenGL 相关的符号定义，在 Powershell 可以使用 *'{0:X4}' -f 1282* 这样的脚本转换为 16 进制显示，也可调用数值对象的转换方法，进行任意进制的转换 `[int64][convert]::ToString(1281, 2)`。

```sh
0 .. 65535 | % { "{0:D16}" -f [int64][convert]::ToString($_,2) }
```


### 🗝 OpenGL API Loaders
- https://www.khronos.org/opengl/wiki/History_of_OpenGL
- https://learnopengl.com/Getting-started/Hello-Window
- https://www.khronos.org/opengl/wiki/OpenGL_Extension
- https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions
- https://www.khronos.org/opengl/wiki/OpenGL_Loading_Library
- https://www.khronos.org/opengl/wiki/Related_toolkits_and_APIs
- GLFW: OpenGL, OpenGL ES and Vulkan https://www.glfw.org
- GLEW: The OpenGL Extension Wrangler Library http://glew.sourceforge.net
- Glad: Multi-Language GL/GLES/EGL/GLX/WGL Loader-Generator https://glad.dav1d.de

OpenGL 所有 API 文档及已注册的扩展都可以通过 git 克隆下载：

```sh
> git clone git@github.com:KhronosGroup/OpenGL-Refpages
> git clone git@github.com:KhronosGroup/OpenGL-Registry
> git clone git@github.com:KhronosGroup/GLSL
```

如果想深入了解 OpenGL 扩展，官方的 OpenGL Extension Registry 信息文档是必不可少的参考。目前包含超过 300 个扩展的信息，以及 OpenGL 和 OpenGL ES/SC 各个版本的技术规范文档，各种 OpenGL API 加载器也需要根据这些文档进行开发。在这个仓库中的文件都是以扩展前缀目录进行管理的，前缀含义主要是硬件供应商，如 AMD、APPLE，还有部分前缀具有特殊含义：

- ARB 前缀表示 OpenGL Architecture Review Board 体系结构审核委员会认可的扩展。
- ANGLE 前缀表示 Google ANGLE - Almost Native Graphics Layer Engine 项目提供的扩展。
- ARM 前缀表示。
- EXT 前缀表示多个厂商共同协商使用一致的扩展。
- KHR Khronos-approved (ARB, OES, or KHR vendor suffixed) extensions
- OES 前缀表示 OpenGL ES Extension。

Google ANGLE 扩展的主要目的是为 OpenGL ES 和 WebGL 应用实现无缝迁移，也就是要实现 OpenGL ES 的网页版本，目前已经实现 OpenGL ES 2.0, 3.0 和 3.1 到 Vulkan, OpenGL, OpenGL ES, Direct3D 9, Direct3D 11。未来还会可能实现 OpenGL ES 3.2，转译到 Metal 和 MacOS, Chrome OS, Fuchsia 的支持。

利用扩展，即便是 OpenGL 低版本也能实现大部分高版本的功能。使用扩展时，要注意优先级，标准 > ARB >EXT，优先使用标准功能，其次 ARB 扩展，然后 EXT 扩展。通常，ARB, OES, KHR, EXT 扩展大多可以跨平台，其他扩展大多都是平台相关的。


OpenGL 作为图形库规范，本身并没有 SDK，想要启用高级 OpenGL 都是通过扩展获取相应的函数指针来完成的，当然必须由显卡的驱动支持才行。不过有些库可以帮你完成这类繁琐的工作，比如 GLEW，或者 GLAD。

OpenGL 作为一个跨平台的通用图形标准规范，其所规定接口的具体的实现是由显卡的硬件驱动程序开发商提供的。由于支持 OpenGL 接口的硬件驱动版本众多，规范又不能替代操作系统对相应的驱动程序进行接口规范，驱动程序大多数函数的位置都无法在编译时确定下来，需要在 OpenGL 程序在运行时查询。

因为通用性好，在各个平台上都会有 OpenGL 接口规范的基本实现，也会提供相应的头文件，例如 Windows 会提供 opengl32.lib 基本库，并提供 *wglGetProcAddress()* 函数用来查询 OpenGL 扩展函数的地址，尽管这个平台为了自家的 DirectX 会不露声色地打压 OpenGL。在 Linux 系统上，通常使用 *glXGetProcAddress()* or *glXGetProcAddressARB()* 函数来查询 OpenGL 扩展函数的地址。

基本的功能可以提供现成的，而其它更多的扩展功能却不能，只能通过运行时检测是否有硬件及驱动支持。所以，任务就落在了开发者身上，开发者需要在运行时获取函数地址并将其保存在一个函数指针中供以后使用。函数地址的获取方法因平台而异，代码非常复杂，而且很繁琐，我们需要对每个可能使用的函数都要重复这个过程。幸运的是，有些库能简化此过程，其中 *GLAD* 是目前最新，也是最流行的库。GLAD 是用来管理 OpenGL 的函数指针的 OpenGL API 加载库，可以使 OpenGL 基础渲染变得简单。所以在使用 GLAD 时，调用任何 OpenGL 的函数之前需要初始化 GLAD。

GLAD 是一个网络服务，提供了根据页面选择 OpenGL 版本及配置，生成相应的导出库的源码，多语言支持。GLAD 应该提供了一个 zip 压缩文件供下载使用，包含两个头文件目录，和一个 glad.c 文件，这是 API 加载器的实现。将两个头文件目录 glad 和 KHR 复制到系统默认的 Include 文件夹中。或者为编译配置增加一个额外的配置项指向这些目录，最后将 glad.c 文件引入到工程中。

还有其它好用的 OpenGL API 加载器，如 *GLFW* 和 *GLEW*，它们都实现了运行时查询机制，以获取系统支持的 OpenGL 扩展。GLFW 基于 C 语言开发的针对 OpenGL、OpenGL ES 和 Vulkan 提供了一些渲染物体所需的最低限度的接口。它允许用户 创建 OpenGL 上下文，定义窗口参数以及处理用户输入。GLEW 全称 The OpenGL Extension Wrangler Library 是基于 C/C++ 开发的 OpenGL 扩展加载器。

GL3W 加载器主要关注 OpenGL 3/4 Core Profile，它只加载核心函数入口点地址，支持 Windows, Mac OS X, Linux, FreeBSD。

DevIL 是图象纹理处理、加载库，旧称 OpenIL，加载各种常见格式的图片，API 接口跟 OpenGL 一致性很强。

更早期的工具是 GLUT - The OpenGL Utility Toolkit，太旧了不要再用，现在已经改为 *FreeGLUT*。

OpenGL 程序要使用独显运行，需要根据显卡驱动来设置。根据 NVIDIA Optimus Rendering Policies 文档，在代码中定义相应的符号可以激活独显。以下激活 N 卡或 A 卡，程序打开时就会默认使用独显运行。

```cpp
// https://docs.nvidia.com/gameworks/content/technologies/desktop/optimus.htm
// The following line is to favor the high performance NVIDIA GPU if there are multiple GPUs
// Has to be .exe module to be correctly detected.
extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;

// And the AMD equivalent
// Also has to be .exe module to be correctly detected.
extern "C" __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 0x00000001;
```

激活独显后，就可以查询到 OpenGL 程序使用的独立显卡信息：

```sh
GL_SHADING_LANGUAGE_VERSION:4.60 NVIDIA
GL_SHADING_LANGUAGE_VERSION_ARB:4.60 NVIDIA
GL_RENDERER:GeForce GTX 1050/PCIe/SSE2
GL_VENDOR:NVIDIA Corporation
GL_VERSION:4.6.0 NVIDIA 461.40
```

这个方法是系统层显卡驱动在程序执行时检测的一个标记，有这个标记，则用独显运行。NVIDIA 的 Optimus 技术可以在笔记本上兼顾耗电量和性能，并能做到自动无缝切换。除了上面的方法，还有多种方法可以切换程序所使用的显卡：

- 在 BIOS 设置：支持 Optimus 的平台上，在 BIOS 中可以找到选项，可以选择使用 NV、Intel 或者自动切换。但这个是静态的，每次切换都得重启，肯定不是我们想要的。
- 在右键菜单中控制：在程序文件的图标上按右键，菜单里有一个“用图形处理器运行”的项，里面可以选择 NV 卡或者 Intel 卡。
- 在驱动中控制：在 NV 的驱动中，可以通过全局 profile，来控制所有程序是通过 NV 卡或者 Intel 卡来执行。另外还有个 per-app 的 profile，可以让每个程序有不同的显卡配置。

有趣的是，在双卡系统上，如果你在程序中枚举显卡，总会返回两块显卡。如果给程序指定的是 NV 卡，那么枚举结果两块显卡都是 NV 卡。如果选的是 Intel 卡，那么第一显卡是 Intel，第二是 NV。

    dxgiFactory -> EnumAdapters(1, &dxgiAdapter)，1 is Nvidia GPU index, 0 - intel HD GPU index

使用 OpenGL 接口规范的最新、最佳方案就是 GLAD + GLEW，前者只负载 API 装入，后者带有窗口界面适配。通过它们可以很好地管理 OpenGL 和 OpenGL ES 等扩展。它可以使 OpenGL 基础渲染变得十分简单，只需要简单四个步骤就可以完成基础渲染：

- 初始化 GLAD 库，加载所有 OpenGL 函数指针。
- 创建着色器并附加到着色器程序。
- 构建缓冲对象并附加到顶点属性。
- 使用着色器程序，利用渲染接口将缓冲对象按照指定图元类型渲染出来。

首先，打开 GLAD 主页，这是一个挑选 OpenGL 扩展 API 的配置程序，提供以下配置选项：

- Language 提供 C/C++/D/Nim/Pacal 等多种语言支持
- Specification 可选 OpenGL/WGL/EGL/GLX 等 API 规范
- API Version 选择版本
- Profile 选择模式
- Extensions 选择要使用的扩展 API
- Options 其它选项
    - Generate a loader 勾选生成加载器，并在生成的 `gladLoadGL` 执行加载器函数 `gladLoadGLLoader`。 
    - Omit KHR 勾选忽略生成 khrplatform.h，这是 Khronos 平台规范类型定义文件。
    - Local Files 只生成本地，不生成目录结构。

以下以加载 glCreateShader() 这个 OpenGL 2.0 引入的扩展 API 为例，说明一下 GLAD 在 Windows 平台下的加载流程：

- 首先，在 glad.h 头文件中声明函数原型；
- 基次，在 glad.c 文件中定义函数指针，并执行加载，然后将返回的指针赋值给定义好的函数指针。
- 执行 gladLoadGL(void) 或者 gladLoadGLLoader(&get_proc) 开始调用系统 API 获取函数地址。

加载 OpenGL API 地址的方法主要是通过以下 Windows 系统调用完成的：

- LoadLibraryW 加载 opengl32.dll；
- GetProcAddress 获取函数地址；
- FreeLibrary 释放 DLL 文件；

```cpp
// Step 1: declare function prototype in glad.h
#ifndef GL_VERSION_2_0
#define GL_VERSION_2_0 1
GLAPI int GLAD_GL_VERSION_2_0;
...
typedef GLuint (APIENTRYP PFNGLCREATESHADERPROC)(GLenum type);
GLAPI PFNGLCREATESHADERPROC glad_glCreateShader;
...
#endif


// Step 2: define function pointer in glad.c and load
PFNGLCREATESHADERPROC glad_glCreateShader = NULL;

static void load_GL_VERSION_2_0(GLADloadproc load) {
    if(!GLAD_GL_VERSION_2_0) return;
    ...
    glad_glCreateShader = (PFNGLCREATESHADERPROC)load("glCreateShader");
    ...
}

// Step 3: execute loader in glad.c
#include <windows.h>
static HMODULE libGL;

typedef void* (APIENTRYP PFNWGLGETPROCADDRESSPROC_PRIVATE)(const char*);
static PFNWGLGETPROCADDRESSPROC_PRIVATE gladGetProcAddressPtr;

static int open_gl(void) {
    libGL = LoadLibraryW(L"opengl32.dll");
    if(libGL != NULL) {
        void (* tmp)(void);
        tmp = (void(*)(void)) GetProcAddress(libGL, "wglGetProcAddress");
        gladGetProcAddressPtr = (PFNWGLGETPROCADDRESSPROC_PRIVATE) tmp;
        return gladGetProcAddressPtr != NULL;
    }
    return 0;
}

static void close_gl(void) {
    if(libGL != NULL) {
        FreeLibrary((HMODULE) libGL);
        libGL = NULL;
    }
}

static void* get_proc(const char *namez) {
    void* result = NULL;
    if(libGL == NULL) return NULL;

    if(result == NULL) {
        result = (void*)GetProcAddress((HMODULE) libGL, namez);
    }

    return result;
}

int gladLoadGL(void) {
    int status = 0;

    if(open_gl()) {
        status = gladLoadGLLoader(&get_proc);
        close_gl();
    }

    return status;
}

int gladLoadGLLoader(GLADloadproc load) {
    GLVersion.major = 0; GLVersion.minor = 0;
    glGetString = (PFNGLGETSTRINGPROC)load("glGetString");
    if(glGetString == NULL) return 0;
    if(glGetString(GL_VERSION) == NULL) return 0;
    find_coreGL();
    ...
    load_GL_VERSION_2_0(load);
    ...

    if (!find_extensionsGL()) return 0;
    load_GL_ARB_sample_shading(load);
    load_GL_ARB_shading_language_include(load);
    return GLVersion.major != 0 || GLVersion.minor != 0;
}
```

以下是摘抄自 Learn OpenGL 教程的示范，例子搭配了 GLEW 和 GLAD：

```cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
```

### 🗝 GLUT & FreeGLUT
- https://www.opengl.org/resources/libraries/glut/glut_downloads.php
- OpenGL Utility Libraries https://www.opengl.org/resources/libraries
- GLUT API version 3 https://www.opengl.org/resources/libraries/glut/spec3/spec3.html
- The Free OpenGL Utility Toolkit http://freeglut.sourceforge.net/

以下基于 *FreeGLUT* 进行原理上的简要分析，但并不建议实际中使用，毕竟太过落后，很多该有的配置都没有。

最后一版是 GLUT Release 3.7, May 7, 1998，Mark Kilgard 为了支持 OpenGL 红宝书第二版示范代码而编写的一套工具。OpenGL 'RedBook' 命名是 OpenGL Programming Guide。注意，Mark 不是这本书的作者，他本人有另外一本书 Programming OpenGL for the X Window System 是用 GLUT 作演示的。

GLUT 负责创建窗口、初始化 OpenGL 上下文和处理输入事件所需的所有系统特定的杂务，以实现真正可移植的 OpenGL 程序，在当时这些功能有的整合确实非常好用，包括现在也是这种逻辑框架。但是它并不是现在最合适、最好的工具，GLUT 曾经大流行过，也给现在带来了相当大的影响，也正是因为如此，才有必要对 GLUT 有一点清晰的认识。

根本原因是 GLUT 其许可证不允许任何人分发修改过的库代码，所以在作者不再更新后就没有人去做这个工作了。这真的很不幸，因为功能过时，但需求功能越来越多，确实需要改进。

FreeGLUT 使用 X-Consortium 许可证，非盈利性质，最初由 Pawel W.Olszta 编写，Andreas Umbach 和 Steve Baker 也有贡献。John F.Fay、John Tsiombikas 和 Diederick C.Niehorster 是 freeglut 项目的当前维护者，最后一版是 29 September 2019, freeglut 3.2.1，已经基本完全实现并替换 GLUT 所有功能。

世界上流行的开源许可证大概有 6 种，在这些许可证之中做选择，也已经是复杂的事，但可以通过 5 个问题简单化处理：

    他人修改软件后可以闭源吗？
    ├── YES！每一个改动是否必需放置版权声明？
    │    ├── Yes！ 👉 Apache License
    │    └──  No！衍生软件的广告是否可以用自己的署名？
    │         ├── Yes！ 👉 MIT License
    │         └──  No！ 👉 BSD License
    └── NO！新增代码采用同样许可证吗？
         ├── Yes！ 👉 GLP License
         └──  NO！是否需要对源代码的改动提供文档？
              ├── Yes！ 👉 Mozilla License
              └──  No！ 👉 LGPL License

以下是源自乌克兰程序员 Paul Bagwell 制作的许可证筛选流程图，只用两分钟，你就能搞清楚这六种许可证之间的最大区别。

![许可证筛选流程图](http://www.ruanyifeng.com/blogimg/asset/201105/free_software_licenses.png)

如果 *FreeGLUT* 配合 MinGW GCC 编译器，需要正确设置相应的库，可以先编译 FreeGLUT，引用生成的库文件。并且，在 Windows 系统上需要 opengl32 基本库，尽管它只提供的 OpenGL 1.1 的实现。为链接程序设置子系统类型 --subsystem,windows 可以让程序运行在 GUI 窗口模式，隐藏掉控制台窗口。

```sh
gcc -c -o example.o example.c -I"C:\Program Files (x86)\freeglut\include"
gcc -o example.exe example.o -L"C:\Program Files (x86)\freeglut\lib" -lfreeglut -lopengl32 -Wl,--subsystem,windows
```

在 Linux 系统上，libGL 通常会导出完整的 OpenGL API，所以不需要使用 API Loader，这种情况下可以直接使用 FreeeGLUT，并在引用头文件之前，设定义 *GL_GLEXT_PROTOTYPES* 符号，启用官方头文件中提供的 API 原型声明。MinGW-W64 GCC 8.1.0 包含了 KHnoros 官方文档提供的头文件。 官方 2015 发布的规范头文件，最高版本到 GL_VERSION_4_5，而官方最新的头文件包含到 GL_VERSION_4_6 版本的扩展。

```cpp
#define GL_GLEXT_PROTOTYPES
#include <GL/glext.h>
```

Khnoros 官方提供的头文件包含的内容类似如下结构：

```cpp
#include <KHR/khrplatform.h>
// - https://github.com/KhronosGroup/EGL-Registry/tree/main/api/KHR/khrplatform.h

typedef void (APIENTRYP PFNGLDEBUGMESSAGECALLBACKPROC) (GLDEBUGPROC callback, const void *userParam);

#ifdef GL_GLEXT_PROTOTYPES
GLAPI void APIENTRY glDebugMessageCallback (GLDEBUGPROC callback, const void *userParam);
#endif
```

官方头文件会引用 Khronos platform-specific types and definitions，KHR/khrplatform.h，这个文件可以在 EGL 或 GLAD 项目中找到。主要是定义了一些规范类型，可以不使用：

     Types defined in khrplatform.h:
        khronos_int8_t              signed   8  bit
        khronos_uint8_t             unsigned 8  bit
        khronos_int16_t             signed   16 bit
        khronos_uint16_t            unsigned 16 bit
        khronos_int32_t             signed   32 bit
        khronos_uint32_t            unsigned 32 bit
        khronos_int64_t             signed   64 bit
        khronos_uint64_t            unsigned 64 bit
        khronos_intptr_t            signed   same number of bits as a pointer
        khronos_uintptr_t           unsigned same number of bits as a pointer
        khronos_ssize_t             signed   size
        khronos_usize_t             unsigned size
        khronos_float_t             signed   32 bit floating point
        khronos_time_ns_t           unsigned 64 bit time in nanoseconds
        khronos_utime_nanoseconds_t unsigned time interval or absolute time in
                                             nanoseconds
        khronos_stime_nanoseconds_t signed time interval in nanoseconds
        khronos_boolean_enum_t      enumerated boolean type.


启用 API 原型声明后，在 FreeeGLUT 就不能将 glutGetProcAddress() 获取到的函数指针赋值给函数名。

Win32 存在一个恼人的问题，即存在多个 C 运行时库（CRT）。如果可执行文件与 GLUT DLL 使用不同的 CRT 链接，GLUT DLL 与可执行程序文件将不会共享相同 CRT 静态数据。特别是，如果 GLUT 调用其（不同的）退出例程，则不会调用在可执行文件中注册的 atexit 回调。

GLUT 通常是用“/MD”选项构建的，CRT 和多线程 DLL 支持，但是 Visual C++ 链接器默认为“/ml”（单线程CRT）。

解决这个问题的一个办法是要求用户始终使用与 GLUT 编译时使用的相同 CRT 进行链接。这要求用户提供非标准选项。GLUT 3.7 有自己的内置解决方案，可执行文件的“退出”函数指针被秘密传递给 GLUT。然后，GLUT 调用可执行文件的退出函数指针，以确保在 GLUT 出现时调用应用程序注册的任何“atexit”调用

另外，使用 MSVC 和 GCC 编译器，相应的头文件也有些差别，前者会使用 *WINGDIAPI* 声明原型，当然也仅限 OpenGL 1.1 版本的 API，需要引入 windows.h 头文件。GCC 使用官方提供的 *GLAPI* 修饰接口原型。

另外，因为使用了 strdup() 这些函数，在做静态链接时会出现符号找不到的错误：

```cpp
#if defined(_MSC_VER) || defined(__WATCOMC__)
/* strdup() is non-standard, for all but POSIX-2001 */
#define strdup   _strdup
#endif
```

通常，MSVC 编译程序做静态链接时应该采用 /MT，而 FreeGLUT 则不是，虽然使用的是 freeglut_static.lib 静态链接库，但是却采用 /MD 方式链接，需要在 CMake 配置中为静态链接的程序指定：

```sh
add_compile_options(/MT)
target_compile_options(${EXE_NAME} PUBLIC "/MD")
```

简单的说，无法解析的外部符号、符号未定义问题这种常见无非以下几种原因：

- 引用了外部库函数，但在编译器未将库文件引入，或者引入的路径错误、版本不对，所使用编译器不匹配、链接方式不匹配；
- 自己声明的符号却没有提供实现，也有可能是语法错误导致不能正确识别符号，这种容易解决，因为自己清楚；

像 MSVC 基础库不对版这种问题才隐蔽，它本身有多个库，而且有多个链接版本的 CRT（C Run-Time library，C 语言运行库），容易造成不一致问题。另外，在不清楚工程需要引用什么库的这种情况很常见，一般需要先学习认识才能了解需要引用什么库。

GLUT 中有大量的宏应用，以注册键盘事件回调为例，只能直接找到两个相应的原型声明：

```cpp
/*
 * Window-specific callback functions, see fg_callbacks.c
 */
FGAPI void    FGAPIENTRY glutKeyboardFunc( void (* callback)( unsigned char, int, int ) );

// * Callbacks with user data arguments.
FGAPI void FGAPIENTRY glutKeyboardFuncUcall( void (* callback)( unsigned char, int, int, void* ), void* user_data );
```

根据 fg_callback_macros.h 头文件中的宏定义，可以找到宏展开式生成一个 *fghKeyboardFuncCallback* 回调函数。在它内部会调用一个 *FGCBKeyboard* 函数指针，这个指针由 *FGCBUserData* 类型的参数传入。

继续展开后面的宏，展开式生成一个 *glutKeyboardFunc*,  *glutKeyboardFuncUcall*，也就是前面的函数原型的实现。

最后可以跟踪到所有回调函数都会在 *SET_WCB* 这个宏中记录在通过 *SFG_Structure* 结构体引用的窗口 *tagSFG_Window* 对象的 CallBacks 成员中。这个成员是 *SFG_Proc* 数组，使用 *WCB_Keyboard* 这样的索引值来设置，一个回调对应一种事件。

总结下来，这套宏为键盘事件的处理生成了以下三个函数的实现：

- *glutKeyboardFunc()* 用户注册事件回调的函数；
- *glutKeyboardFuncUcall()* 登记回调函数到窗口对象上；
- *fghKeyboardFuncCallback()* 执行用户注册的事件回调；


```cpp

/*
 * Freeglut callbacks type definitions
 * freeglut-3.2.1\src\fg_internal.h
 *
 * If anything here is modified or added, update fg_callback_macros.h functions.
 *
 * This is not ideal, but freeglut needs to either define minimal compiler specs,
 * or update header every time this is changed or updated.
 */
typedef void* FGCBUserData;
typedef void (* FGCBKeyboard        )( unsigned char, int, int );

// freeglut-3.2.1\src\fg_callback_macros.h
/* Implement all these callback setter functions... */
IMPLEMENT_CURRENT_WINDOW_CALLBACK_FUNC_ARG3_USER(Keyboard,unsigned char,int,int)

#define IMPLEMENT_CURRENT_WINDOW_CALLBACK_FUNC_ARG3_USER(a,arg1,arg2,arg3) \
        IMPLEMENT_CALLBACK_FUNC_CB_ARG3_USER(a,a,arg1,arg2,arg3)           \
        IMPLEMENT_CURRENT_WINDOW_CALLBACK_FUNC_2NAME_GLUT(a,a)

#define IMPLEMENT_CALLBACK_FUNC_CB_ARG3_USER(a,b,arg1,arg2,arg3)          \
static void fgh##a##FuncCallback( arg1 arg1val, arg2 arg2val, arg3 arg3val, FGCBUserData userData ) \
{                                                                         \
    FGCB##b* callback = (FGCB##b*)&userData;                              \
    (*callback)( arg1val, arg2val, arg3val );                             \
}

#define IMPLEMENT_CURRENT_WINDOW_CALLBACK_FUNC_2NAME_GLUT(a,b)            \
        IMPLEMENT_CURRENT_WINDOW_CALLBACK_FUNC_2NAME_GLUT_UCALL(a,b)      \
        IMPLEMENT_CALLBACK_FUNC_2NAME_GLUT_BASE(a,b)

/*
 * And almost every time the callback setter function can be implemented with these:
 */
#define IMPLEMENT_CURRENT_WINDOW_CALLBACK_FUNC_2NAME_GLUT_UCALL(a,b)      \
void FGAPIENTRY glut##a##FuncUcall( FGCB##b##UC callback, FGCBUserData userData ) \
{                                                                         \
    SET_CURRENT_WINDOW_CALLBACK( b );                                     \
}
#define SET_CURRENT_WINDOW_CALLBACK(a)                                    \
do                                                                        \
{                                                                         \
    if( fgStructure.CurrentWindow == NULL )                               \
        return;                                                           \
    SET_WCB( ( *( fgStructure.CurrentWindow ) ), a, callback, userData ); \
} while( 0 )
/* SET_WCB() is used as:
 *
 *     SET_WCB( window, cbname, func, udata );
 *
 * ...where {window} is the freeglut window to set the callback,
 *          {cbname} is the window-specific callback to set,
 *          {func} is a function-pointer,
 *          {udata} is a void* pointer for user data.
 */
#define IMPLEMENT_CALLBACK_FUNC_2NAME_GLUT_BASE(a,b)                      \
void FGAPIENTRY glut##a##Func( FGCB##b callback )                         \
{                                                                         \
    if( callback )                                                        \
    {                                                                     \
        FGCB##b* reference = &callback;                                   \
        glut##a##FuncUcall( fgh##a##FuncCallback, *((FGCBUserData*)reference) ); \
    }                                                                     \
    else                                                                  \
        glut##a##FuncUcall( NULL, NULL );                                 \
}
```

再往深一层就是 FreeGLUT 如何处理窗口消息机制，如何将事件消息数据通过回调传回到用户注册的回调函数上。不同操作系统，实现逻辑不同，Windows 系统的对应实现在 mswin 目录下。

和键盘相关的 Windows 窗口消息就是 WM_KEYDOWN 或 WM_KEYUP 等消息，最后使用 *INVOKE_WCB* 宏

```cpp
case WM_SYSKEYDOWN:
case WM_KEYDOWN:
{
    window = fghWindowUnderCursor(window);
    lRet = fghWindowProcKeyPress(window,uMsg,GL_TRUE,wParam,lParam);
}

case WM_SYSKEYUP:
case WM_KEYUP:
{
    window = fghWindowUnderCursor(window);
    lRet = fghWindowProcKeyPress(window,uMsg,GL_FALSE,wParam,lParam);
}

INVOKE_WCB( *window, KeyboardUp,
       ( (char)(wParam & 0xFF), /* and with 0xFF to indicate to runtime that we want to strip out higher bits - otherwise we get a runtime error when "Smaller Type Checks" is enabled */
            window->State.MouseX, window->State.MouseY )
);

#define INVOKE_WCB(window,cbname,arg_list)    \
do                                            \
{                                             \
    if( FETCH_WCB( window, cbname ) )         \
    {                                         \
        FGCB ## cbname ## UC func = (FGCB ## cbname ## UC)(FETCH_WCB( window, cbname )); \
        FGCBUserData userData = FETCH_USER_DATA_WCB( window, cbname ); \
        fgSetWindow( &window );               \
        func EXPAND_WCB( cbname )(( arg_list, userData )); \
    }                                         \
} while( 0 )

#define FETCH_WCB(window,cbname) ((window).CallBacks[WCB_ ## cbname])
```


如果是使用老旧的 GLUT 还会涉及 glut.lib、glut32.lib 和对应的 glut.dll、 glut32.dll 两级链接库文件，这些旧文件很烦人，上面出现的多个运行库退出函数问题都处理得不够好。至少应该使用 FreeGLUT 替代它，链接时使用 libfreeglut.a 或者静态库 libfreeglut_static.a。当然还有 Windows 系统提供的基础 opengl32 库。

```cpp
#include <iostream>

#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/freeglut.h>

using namespace std;

int main(int argc, char *argv[])
{
    glutInit (&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("Hello World");

    cout << "GL_SHADING_LANGUAGE_VERSION:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    cout << "GL_SHADING_LANGUAGE_VERSION_ARB:" << glGetString(GL_SHADING_LANGUAGE_VERSION_ARB) << endl;
    cout << "GL_VERSION:" << glGetString(GL_VERSION) << endl;
    cout << "GL_GetError:" << glGetError() << endl;
    return 0;
}
```

当然，使用 FreeGLUT 并不是就没有问题，作为一个相当旧的 OpenGL 加载器，它连 OpenGL 2.0 着色器扩展的相关 API 都没有加载进来，许多规范符号也没有定义。所以默认也是使用不了着色器的，如果程序中使用了这些未在加载器中得到支持的扩展 API，就会出现一堆的未定义引用的错误消息：

```sh
opengl.cpp:(.text+0x347): undefined reference to `glCreateShader'
opengl.cpp:(.text+0x3a1): undefined reference to `glShaderSource'
opengl.cpp:(.text+0x3a8): undefined reference to `glCompileShader'
opengl.cpp:(.text+0x3b9): undefined reference to `glGetShaderiv'
opengl.cpp:(.text+0x3d7): undefined reference to `glGetShaderInfoLog'
opengl.cpp:(.text+0x40a): undefined reference to `glAttachShader'
opengl.cpp:(.text+0x433): undefined reference to `glCreateProgram'
opengl.cpp:(.text+0x559): undefined reference to `glLinkProgram'
```

在最后一个版本的 freeglut-3.2.1 示范代码中，有两个例子演示了如何加载着色器扩展：

- demos\shapes\shapes.c
- demos\smooth_opengl3\smooth_opengl3.c

根据当前使用的系统不同而执行不同的 API 去查询扩展接口：

- Windows: *wglGetProcAddress( ( LPCSTR )procName )*
- EGL:    *eglGetProcAddress(procName)*
- X11: *glXGetProcAddressARB( ( const GLubyte * )procName )*

WGL 是 OpenGL 在 Windows 平台下的 API 前缀，*wglGetProcAddress()* 函数在系统提供的 wingdi.h 头文件中声明。

EGL 是 OpenGL ES 和本地窗口系统(native platform window system)之间的一个中间接口层，它主要由系统制造商实现。EGL 提供如下机制：

- 与设备的原生窗口系统通信
- 查询绘图表面的可用类型和配置
- 创建绘图表面
- 在 OpenGL ES 和其他图形渲染 API 之间同步渲染
- 管理纹理贴图等渲染资源

OpenGL ES 是针对 Embedded Systems 嵌入式设备：手机、PDA 和游戏主机等而设计一个 OpenGL 子集，各显卡制造商和系统制造商来实现这组 API。为了让 OpenGL ES 能够绘制在当前设备上，需要 EGL 作为 OpenGL ES 与设备的桥梁。

所以，一个 OpenGL 接口加载器要做的适配工作也是要跨平台的，否则就失去了 OpenGL 通用性的意义。



### 🗝 Shaders Language
- GLSL Essentials: Enrich your 3D scenes with the power of GLSL! by Jacobo Rodríguez
- [OpenGL Shading Language](https://www.khronos.org/opengl/wiki/OpenGL_Shading_Language)
- [Hello Traiangle](https://learnopengl.com/Getting-started/Hello-Triangle)
- [Getting started Shader](https://learnopengl-cn.github.io/01%20Getting%20started/05%20Shaders/)
- [GLM - OpenGL Mathematics](https://github.com/g-truc/glm)
- LearnOpenGL Shaders https://learnopengl.com/Getting-started/Shaders
- GLSL Built-in Variables https://www.khronos.org/opengl/wiki/Built-in_Variable_(GLSL)
- GLSL Validator https://github.com/KhronosGroup/glslang
- SPIR-V https://en.wikipedia.org/wiki/Standard_Portable_Intermediate_Representation
- The OpenGL® API & GLSL specifications https://www.khronos.org/opengl/
- The OpenGL® Graphics System: A Specification (Version 4.6 (Core Profile) - October 22, 2019)

以下是摘选自 SFML Ensentials Chapter 6 Setting shader uniforms 的一个顶点颜色器程序代码：

```c glsl
#version 110

//varying "out" variables to be used in the fragment shader
varying vec4 vColor;
varying vec2 vTexCoord;

void main()
{
    vColor = gl_Color;
    vTexCoord = (gl_TextureMatrix[0] * gl_MultiTexCoord0).xy;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
```

以下是相应的片断着色器部分，这才是魔术的地方：

```c glsl
#version 110

//varying attributes from the vertex shader
varying vec4 vColor;
varying vec2 vTexCoord;

//declare uniforms
uniform sampler2D uTexture;
uniform float uPositionFreq;
uniform float uSpeed;
uniform float uStrength;
uniform float uTime;

void main()
{
    vec2 texCoord = vTexCoord;
    float coef = sin(gl_FragCoord.x * uPositionFreq + uSpeed + uTime);
    texCoord.y += coef * uStrength;
    gl_FragColor = vColor * texture2D(uTexture, texCoord);
}

// SFML Ensentials 
```

在 SFML 环境中，应该通过着色器对象的方法设置着色器的输入变量：

```cpp
auto shader = AssetManager::GetShader("shader.vert", "ripple.frag");
sf::Sprite sprite(AssetManager::GetTexture("myTexture.png"));

sf::Clock clock;
shader->setUniform("uTexture", *sprite.getTexture());
shader->setUniform("uPositionFreq", 0.1f);
shader->setUniform("uSpeed", 20);
shader->setUniform("uStrength", 0.03f);
shader->setUniform("uTime", clock.getElapsedTime().asSeconds());
```

代码中使用到一些 GLSL 关键字，如：

- varying 定义了一个可变量；
- vec2 和 vec4 是向量类型，分别是二维向量和四维向量；
- gl 前缀的是内置变量，可以通过 GLSL specifications 着色器语言规范文档查询；

使用到的这些内置变量如下：

- gl_ModelViewProjectionMatrix 表示是模型、视图、投射变换矩阵的复合，计算顶点在屏幕空间的位置。
- gl_TextureMatrix  纹理变换矩阵；
- gl_MultiTexCoord0  输入的顶点纹理坐标；
- gl_Vertex 顶点着色器中的输入顶点；
- gl_FragColor 片断着色器输出的像素颜色；

gl_ModelViewProjectionMatrix 这些内置变量在 OpenGL 3.3 标注为过期，取而代之的是采用 uniform 的形式向着色器传递矩阵，当然还可以以 compatible 方式继续使用。

根据规范文档说明，这些内置变量都属性 Compatibility Profile，并不属于最新的 Core Profile：

```c glsl
// 7.4.1. Compatibility Profile State compatibility profile only
uniform mat4 gl_ModelViewMatrix;
uniform mat4 gl_ProjectionMatrix;
uniform mat4 gl_ModelViewProjectionMatrix;
uniform mat4 gl_TextureMatrix[gl_MaxTextureCoords];

// Compatibility profile: fragment shader output variables
out vec4 gl_FragColor;
out vec4 gl_FragData[gl_MaxDrawBuffers];

// Compatibility Profile Vertex Shader Built-In Input
in vec4 gl_Color;
in vec4 gl_SecondaryColor;
in vec3 gl_Normal;
in vec4 gl_Vertex;
in vec4 gl_MultiTexCoord0;
in vec4 gl_MultiTexCoord1;
in vec4 gl_MultiTexCoord2;
in vec4 gl_MultiTexCoord3;
in vec4 gl_MultiTexCoord4;
in vec4 gl_MultiTexCoord5;
in vec4 gl_MultiTexCoord6;
in vec4 gl_MultiTexCoord7;
in float gl_FogCoord;
```

OpenGL 扩展会影响 GLSL 功能，和 OpenGL 的扩展不同，要使用 GLSL 扩展必需在着色器程序中显式设置：

```c glsl
#extension extension_name : behavior
```

固定以下几个扩展使用行为方式：

- *enable*: 启用相应扩展，如果没硬件实现，没提示错误信息。
- *require*: 启用相应扩展，如果没硬件实现，则出错。
- *warn*: 启用相应扩展，并提示信息。
- *disable*: 不使用相应的扩展。

GLSL 也有以下宏定义： 

- `__FILE__` 着色器文件的序号。
- `__LINE__` 代码行号。
- `__VERSION__` 版本号，如 330 表示 3.30。

GLSL 的主函数和 C 语言的同名，但是没有传入参数，也不返回值。

函数定义格式参考如下，使用 in/out/inout 来确定参数的数据流向：

```c glsl
void MyFunction(in float inputValue, out int outputValue, inout float inAndOutValue);
```

调用函数时，参数必须使用左值，不能使用表达式：`MyFunction(in1, 2+4, out2)` 这种是错误用法，不能使用 2 + 4 这种表达式作参数。也不能在一个 unsettable 值上调用，包括着色器输入（全局 in 变量）、uniforms 或 const 限定的值。

GLSL 有大量内置函数，常用的数学函数都，例如：

|                Syntax               |                      Description                      |
|-------------------------------------|-------------------------------------------------------|
| genFType  radians(genFType degrees) | Converts degrees to radians, i.e., (π / 180)·degrees. |
| genFType  degrees(genFType radians) | Converts radians to degrees, i.e., (180 / π)·radians. |
| genFType  sin(genFType angle)       | The standard trigonometric sine function.             |
| genFType  cos(genFType angle)       | The standard trigonometric cosine function.           |
| genFType  tan(genFType angle)       | The standard trigonometric tangent.                   |


GLSL 内置函数大多数所有着色器中通用，部分专用，大概分成三类：

- 暴露硬件功能的函数，着色器无法模拟这些函数，如纹理贴图访问。
- 代表一个简单的操作，如 clamp、mix 等函数，用户编写起来非常简单，但它们非常常见，可能有直接的硬件支持。对于编译器来说，将表达式映射到复杂的汇编指令是一个非常困难的问题。
- 图形硬件加速的操作，三角函数属于这一类。

可以参考 GLM 数学函数库，这个库的实现参考 GLSL 规范，GLM is a header only library，只提供头文件的实现方式，不需要构建。

    git clone git@github.com:g-truc/glm.git

以下是 GLSLangSpec.3.30 规范文档目录罗列的 Built-in Functions 原型，基本都是泛型函数，genType 就是表示泛型，以下省略掉相应 template 声明部分：

```cpp
// 8.1 Angle and Trigonometry Functions
namespace trigonometric{
    genType radians(genType const & degrees);
    genType degrees(genType const & radians);
    genType sin(genType const & angle);
    genType cos(genType const & angle);
    genType tan(genType const & angle);
    genType asin(genType const & x);
    genType acos(genType const & x);
    genType atan(genType const & y, genType const & x);
    genType atan(genType const & y_over_x);
    genType sinh(genType const & angle);
    genType cosh(genType const & angle);
    genType tanh(genType const & angle);
    genType asinh(genType const & x);
    genType acosh(genType const & x);
    genType atanh(genType const & x);
}
// 8.2 Exponential Functions
namespace exponential{
    genType pow(genType const & x, genType const & y);
    genType exp(genType const & x);
    genType log(genType const & x);
    genType exp2(genType const & x);
    genType log2(genType const & x);
    genType sqrt(genType const & x);
    genType inversesqrt(genType const & x);
}
// 8.3 Common Functions
namespace common{
    genFIType abs(genFIType const & x);
    genFIType sign(genFIType const & x);
    genType floor(genType const & x);
    genType trunc(genType const & x);
    genType round(genType const & x);
    genType roundEven(genType const & x);
    genType ceil(genType const & x);
    genType fract(genType const & x);
    genType mod(genType const & x, genType const & y);
    genType mod(genType const & x, typename genType::value_type const & y);
    genType modf(genType const & x, genType & i);
    genType min(genType const & x, genType const & y);
    genType min(genType const & x, typename genType::value_type const & y);
    genType max(genType const & x, genType const & y);
    genType max(genType const & x, typename genType::value_type const & y);
    genType clamp(genType const & x, genType const & minVal, genType const & maxVal);
    genType clamp(genType const & x, typename genType::value_type const & minVal, 
                                     typename genType::value_type const & maxVal);
    genTypeT mix(genTypeT const & x, genTypeT const & y, genTypeU const & a);
    genType step(genType const & edge, genType const & x);
    genType step(typename genType::value_type const & edge, genType const & x);
    genType smoothstep(genType const & edge0, genType const & edge1, genType const & x);
    genType smoothstep(typename genType::value_type const & edge0, 
                       typename genType::value_type const & edge1, genType const & x);
    typename genType::bool_type isnan(genType const & x);
    typename genType::bool_type isinf(genType const & x);
    genIType floatBitsToInt(genType const & value);
    genUType floatBitsToUint(genType const & value);
    genType intBitsToFloat(genIType const & value); 
    genType uintBitsToFloat(genUType const & value); 
    genType fma(genType const & a, genType const & b, genType const & c);
    genType frexp(genType const & x, genIType & exp);
    genType ldexp(genType const & x, genIType const & exp);
} 
// 8.4 Geometric Functions
namespace geometric{
    typename genType::value_type length(genType const & x);
    typename genType::value_type distance(genType const & p0, genType const & p1);
    typename genType::value_type dot(genType const & x, genType const & y);
    detail::tvec3<T> cross(detail::tvec3<T> const & x, detail::tvec3<T> const & y);
    genType normalize(genType const & x);
    genType faceforward(genType const & N, genType const & I, genType const & Nref);
    genType reflect(genType const & I, genType const & N);
    genType refract(genType const & I, genType const & N, typename genType::value_type const & eta);
}
// 8.5 Matrix Functions
namespace matrix{
    matType matrixCompMult(matType const & x, matType const & y);
    matType outerProduct(vecType const & c, vecType const & r);
    typename matType::transpose_type transpose(matType const & x);
    typename detail::tmat2x2<T>::value_type determinant(detail::tmat2x2<T> const & m);
    typename detail::tmat3x3<T>::value_type determinant(detail::tmat3x3<T> const & m);
    typename detail::tmat4x4<T>::value_type determinant(detail::tmat4x4<T> const & m);
    detail::tmat2x2<T> inverse(detail::tmat2x2<T> const & m);
    detail::tmat3x3<T> inverse(detail::tmat3x3<T> const & m);
    detail::tmat4x4<T> inverse(detail::tmat4x4<T> const & m);
}
// 8.6 Vector Relational Functions
namespace vector_relational{
    typename vecType<T>::bool_type lessThan( vecType<T> const & x, vecType<T> const & y )
    typename vecType<T>::bool_type lessThanEqual( vecType<T> const & x, vecType<T> const & y )
    typename vecType<T>::bool_type greaterThan( vecType<T> const & x, vecType<T> const & y )
    typename vecType<T>::bool_type greaterThanEqual( vecType<T> const & x, vecType<T> const & y )
    typename vecType<T>::bool_type equal( vecType<T> const & x, vecType<T> const & y )
    typename vecType<T>::bool_type notEqual( vecType<T> const & x, vecType<T> const & y )
    bool any(vecType<bool> const & v);
    bool all(vecType<bool> const & v);
    vecType<bool> not_(vecType<bool> const & v);
}
// 8.7 Texture Lookup Functions
    // Texture Query Functions
    int textureSize (gsampler1D sampler, int lod)
    ivec2 textureSize (gsampler2D sampler, int lod)
    ivec3 textureSize (gsampler3D sampler, int lod)
    ivec2 textureSize (gsamplerCube sampler, int lod)
    int textureSize (sampler1DShadow sampler, int lod)
    ivec2 textureSize (sampler2DShadow sampler, int lod)
    ivec2 textureSize (samplerCubeShadow sampler, int lod)
    ivec3 textureSize (samplerCubeArray sampler, int lod)
    ivec3 textureSize (samplerCubeArrayShadow sampler, int lod)
    ivec2 textureSize (gsampler2DRect sampler)
    ivec2 textureSize (sampler2DRectShadow sampler)
    ivec2 textureSize (gsampler1DArray sampler, int lod)
    ivec3 textureSize (gsampler2DArray sampler, int lod)
    ivec2 textureSize (sampler1DArrayShadow sampler, int lod)
    ivec3 textureSize (sampler2DArrayShadow sampler, int lod)
    int textureSize (gsamplerBuffer sampler)
    ivec2 textureSize (gsampler2DMS sampler)
    ivec2 textureSize (gsampler2DMSArray sampler)
    vec2 textureQueryLod(gsampler1D sampler, float P)
    vec2 textureQueryLod(gsampler2D sampler, vec2 P)
    vec2 textureQueryLod(gsampler3D sampler, vec3 P)
    vec2 textureQueryLod(gsamplerCube sampler, vec3 P)
    vec2 textureQueryLod(gsampler1DArray sampler, float P)
    vec2 textureQueryLod(gsampler2DArray sampler, vec2 P)
    vec2 textureQueryLod(gsamplerCubeArray sampler, vec3 P)
    vec2 textureQueryLod(sampler1DShadow sampler, float P)
    vec2 textureQueryLod(sampler2DShadow sampler, vec2 P)
    vec2 textureQueryLod(samplerCubeShadow sampler, vec3 P)
    vec2 textureQueryLod(sampler1DArrayShadow sampler, float P)
    vec2 textureQueryLod(sampler2DArrayShadow sampler, vec2 P)
    vec2 textureQueryLod(samplerCubeArrayShadow sampler, vec3 P)
    // Texture Lookup Functions
    float texture (sampler1DShadow sampler, vec3 P [, float bias] )
    float textureProj (sampler1DShadow sampler, vec4 P [, float bias] )
    float textureLod (sampler1DShadow sampler, vec3 P, float lod)
    float textureOffset (sampler2DRectShadow sampler, vec3 P, ivec2 offset )
    gvec4 texelFetch (gsampler1D sampler, int P, int lod)
    float textureProjOffset (sampler2DRectShadow sampler, vec4 P, ivec2 offset )
    float textureLodOffset (sampler1DShadow sampler, vec3 P, float lod, int offset)
    float textureProjLod (sampler1DShadow sampler, vec4 P, float lod)
    float textureProjLodOffset (sampler1DShadow sampler, vec4 P, float lod, int offset)
    float textureGrad (sampler2DRectShadow sampler, vec3 P, vec2 dPdx, vec2 dPdy)
    float textureGradOffset (sampler2DRectShadow sampler, vec3 P, vec2 dPdx, vec2 dPdy, ivec2 offset)
    float textureProjGrad (sampler2DRectShadow sampler, vec4 P, vec2 dPdx, vec2 dPdy)
    float textureProjGradOffset (sampler2DRectShadow sampler,
                                 vec4 P,
                                 vec2 dPdx, vec2 dPdy, ivec2 offset)
    // Texture Gather Functions
    vec4 textureGather(sampler2DShadow sampler, vec2 P, float refZ)
    vec4 textureGatherOffset(sampler2DShadow sampler, vec2 P, float refZ, ivec2 offset)
// 8.8 Fragment Processing Functions
    // Derivative Functions
    genType dFdx (genType p);
    genType dFdy (genType p);
    genType dFdxFine (genType p);
    genType dFdyFine (genType p);
    genType dFdxCoarse (genType p);
    genType dFdyCoarse (genType p);
    genType fwidth (genType p);// Returns abs (dFdx (p)) + abs (dFdy (p)).
    genType fwidthFine (genType p);// Returns abs(dFdxFine(p)) + abs(dFdyFine(p)).
    genType fwidthCoarse (genType p);
    genType dFdxCoarse (genType p);
    genType dFdyCoarse (genType p);
    genType fwidth (genType p);// Returns abs (dFdx (p)) + abs (dFdy (p)).
    genType fwidthFine (genType p);// Returns abs(dFdxFine(p)) + abs(dFdyFine(p)).
    genType fwidthCoarse (genType p);// Returns abs(dFdxCoarse(p)) + abs(dFdyCoarse(p)).
    // Interpolation Functions
    float interpolateAtCentroid (float interpolant);
    float interpolateAtSample (float interpolant, int sample);
    float interpolateAtOffset (float interpolant, vec2 offset);
    vec2 interpolateAtCentroid (vec2 interpolant)
    vec3 interpolateAtCentroid (vec3 interpolant)
    vec4 interpolateAtCentroid (vec4 interpolant)
    vec2 interpolateAtSample (vec2 interpolant, int sample)
    vec3 interpolateAtSample (vec3 interpolant, int sample)
    vec4 interpolateAtSample (vec4 interpolant, int sample)
    vec2 interpolateAtOffset (vec2 interpolant, vec2 offset)
    vec3 interpolateAtOffset (vec3 interpolant, vec2 offset)
    vec4 interpolateAtOffset (vec4 interpolant, vec2 offset)
// 8.9 Noise Functions
float noise1 (genType x);// Returns a 1D noise value based on the input value x.
vec2 noise2 (genType x);// Returns a 2D noise value based on the input value x.
vec3 noise3 (genType x);// Returns a 3D noise value based on the input value x.
vec4 noise4 (genType x);// Returns a 4D noise value based on the input value x.
// 8.10 Geometry Shader Functions
void EmitStreamVertex (int stream);
void EndStreamPrimitive (int stream);
void EmitVertex ();
void EndPrimitive ();
```

纹理函数分为以下几种：

- Texture Query Functions
- Texel Lookup Functions
- Texture Gather Functions

虽然，在 GLSL 4.0 中声明废弃了大量名字包含 1D/2D/3D/Cube 字样的纹理函数，如  *texture1D*。但是在后续版本中，还是将它们归为 Compatibility Profile Texture Functions。

纹理查询函数 *textureSize* 查询指定精细级别的纹理尺寸，*textureQueryLod* 只用于片段着色器，获取 LOD - Level of Detail 信息。

片段着色器处理函数有两类，偏导函数（头皮发麻）和插值函数：

- Derivative Functions
- Interpolation Functions

导数可能在计算上很消耗硬件资源，或在数值上不稳定。因此，OpenGL 实现可以通过使用快速但不完全精确的导数计算来近似真实导数。在非均匀控制流中未定义导数。使用 forward/backward differencing 指定导数的预期行为。

在 GLSL 4.4 版本后弃用了 noise1, noise2, noise3, noise4 等噪点函数，它们只返回 0.0 值或向量。与之前的版本一样，它们在语义上不被认为是编译时常量表达式。

GLSLangSpec.4.60 比旧版本规范新增了大量内置函数，以下是各个规范文档的内置函数目录部分对比，前面两个版本分别对应 OpenGL 2.0 和 3.0：

    | 1.1 | 1.3 | 3.3 | 4.0 |4.5 | 4.6 |                    Contents                   |
    |-----|-----|-----|-----|----|-----|-----------------------------------------------|
    | ✔  | ✔ | ✔ | ✔ | ✔ | ✔  | 8.1. Angle and Trigonometry Functions         |
    | ✔  | ✔ | ✔ | ✔ | ✔ | ✔  | 8.2. Exponential Functions                    |
    | ✔  | ✔ | ✔ | ✔ | ✔ | ✔  | 8.3. Common Functions                         |
    | ❌  | ❌ | ❌ | ✔ | ✔ | ✔  | 8.4. Floating-Point Pack and Unpack Functions |
    | ✔  | ✔ | ✔ | ✔ | ✔ | ✔  | 8.5. Geometric Functions                      |
    | ✔  | ✔ | ✔ | ✔ | ✔ | ✔  | 8.6. Matrix Functions                         |
    | ✔  | ✔ | ✔ | ✔ | ✔ | ✔  | 8.7. Vector Relational Functions              |
    | ❌  | ❌ | ❌ | ✔ | ✔ | ✔  | 8.8. Integer Functions                        |
    | ✔  | ✔ | ✔ | ✔ | ✔ | ✔  | 8.9. Texture Functions                        |
    | ❌  | ❌ | ❌ | ❌ | ✔ | ✔  | 8.10. Atomic Counter Functions                |
    | ❌  | ❌ | ❌ | ❌ | ✔ | ✔  | 8.11. Atomic Memory Functions                 |
    | ❌  | ❌ | ❌ | ❌ | ✔ | ✔  | 8.12. Image Functions                         |
    | ❌  | ❌ | ✔ | ✔ | ✔ | ✔  | 8.13. Geometry Shader Functions               |
    | ✔  | ✔ | ✔ | ✔ | ✔ | ✔  | 8.14. Fragment Processing Functions           |
    | ✔  | ✔ | ✔ | ✔ | ✔ | ✔  | 8.15. Noise Functions                         |
    | ❌  | ❌ | ❌ | ✔ | ✔ | ✔  | 8.16. Shader Invocation Control Functions     |
    | ❌  | ❌ | ❌ | ❌ | ✔ | ✔  | 8.17. Shader Memory Control Functions         |
    | ❌  | ❌ | ❌ | ❌ | ❌ | ✔  | 8.18. Subpass-Input Functions                 |
    | ❌  | ❌ | ❌ | ❌ | ❌ | ✔  | 8.19. Shader Invocation Group Functions       |


GLSL 和其 C/C++ 等编程语言一样有数据类型，如 *int*, *float*, *double*, *uint*, *bool*，也有数组、结构体，条件判断、循环控件等等，运算符也类似。

预处理器使用的运算符：

    |  Precedence |       Operator class       |    Operators    | Associativity |
    |-------------|----------------------------|-----------------|---------------|
    | 1 (highest) | parenthetical grouping     | ( )             | NA            |
    | 2           | unary                      | defined + - ~ ! | Right to Left |
    | 3           | multiplicative             | * / %           | Left to Right |
    | 4           | additive                   | + -             | Left to Right |
    | 5           | bit-wise shift             | << >>           | Left to Right |
    | 6           | relational                 | < > <= >=       | Left to Right |
    | 7           | equality                   | == !=           | Left to Right |
    | 8           | bit-wise and               | &               | Left to Right |
    | 9           | bit-wise exclusive or      | ^               | Left to Right |
    | 10          | bit-wise inclusive or      | |               | Left to Right |
    | 11          | logical and                | &&              | Left to Right |
    | 12 (lowest) | logical inclusive or       | ||              | Left to Right |

通用运算符：

    |  Precedence |              Operator Class             | Operators  | Associativity |
    |-------------|-----------------------------------------|------------|---------------|
    | 1 (highest) | parenthetical grouping                  | ( )        | NA            |
    |-------------|-----------------------------------------|------------|---------------|
    | 2           | array subscript                         | [ ]        | Left to Right |
    |             | function call and constructor structure | ( )        |               |
    |             | field or method selector, swizzler      | .          |               |
    |             | post fix increment and decrement        | ++ --      |               |
    |-------------|-----------------------------------------|------------|---------------|
    | 3           | prefix increment and decrement unary    | ++ --      | Right to Left |
    |             |                                         | + - ~ !    |               |
    |-------------|-----------------------------------------|------------|---------------|
    | 4           | multiplicative                          | * / %      | Left to Right |
    | 5           | additive                                | + -        | Left to Right |
    | 6           | bit-wise shift                          | << >>      | Left to Right |
    | 7           | relational                              | < > <= >=  | Left to Right |
    | 8           | equality                                | == !=      | Left to Right |
    | 9           | bit-wise and                            | &          | Left to Right |
    | 10          | bit-wise exclusive or                   | ^          | Left to Right |
    | 11          | bit-wise inclusive or                   | |          | Left to Right |
    | 12          | logical and                             | &&         | Left to Right |
    | 13          | logical exclusive or                    | ^^         | Left to Right |
    | 14          | logical inclusive or                    | ||         | Left to Right |
    | 15          | selection                               | ? :        | Right to Left |
    |-------------|-----------------------------------------|------------|---------------|
    | 16          | Assignment arithmetic assignments       | =          | Right to Left |
    |             |                                         | += -=      |               |
    |             |                                         | *= /=      |               |
    |             |                                         | %= <<= >>= |               |
    |             |                                         | &= ^= |=   |               |
    |-------------|-----------------------------------------|------------|---------------|
    | 17 (lowest) | sequence                                | ,          | Left to Righ  |


Table 2.1 Basic Data Types in GLSL

|  Type  |                  Description                   |
|--------|------------------------------------------------|
| float  | IEEE 32-bit floating-point value               |
| double | IEEE 64-bit floating-point value               |
| int    | signed two ’ s-complement 32-bit integer value |
| uint   | unsigned 32-bit integer value                  |
| bool   | Boolean value                                  |

着色器是各自独立的小程序，每个着色器都有输入和输出，着色器之间可以上下串联，这也是渲染管道的一层含义。GLSL 定义了 `in` 和 `out` 关键字专门来实现输入和输出，只要一个输出变量与下一个着色器阶段的输入匹配，它就会传递下去，但在顶点和片段着色器中会有点不同。顶点着色器从顶点数据中直接接收输入，接收的是一种特殊形式的输入，否则就会效率低下。

所以，在渲染管线中，如果从 A 着色器向 B 着色器发送数据，必须在 A 着色器中声明输出变量，并在接收方 B 着色器中声明一个相同的输入变量。当类型和名字都一样的时候，数据就会从上一级着色器的 `out` 变量流向下一级着色器的 `in` 变量。

着色器中使用的像 *gl_Position* 这样以 gl 开头的都是内置常量或变量，参考 The OpenGL® Shading Language, v4.60.7 - Chapter 7. Built-In Variables。

根据不同阶段使用着色器，可用内置变量也不相同：

```c glsl
// Vertex Shaders have the following built-in input variables.
in int gl_VertexID; // only present when not targeting Vulkan
in int gl_InstanceID; // only present when not targeting Vulkan
in int gl_VertexIndex; // only present when targeting Vulkan
in int gl_InstanceIndex; // only present when targeting Vulkan
in int gl_DrawID;
in int gl_BaseVertex;
in int gl_BaseInstance;

// Vertex Shaders have the following predefined outputs.
out gl_PerVertex {
    vec4 gl_Position;
    float gl_PointSize;
    float gl_ClipDistance[];
    float gl_CullDistance[];
};


// Geometry Shaders provide the following built-in input variables:
in gl_PerVertex
{
  vec4 gl_Position;
  float gl_PointSize;
  float gl_ClipDistance[];
} gl_in[];

// Geometry Shaders have the following built-in outputs.
out gl_PerVertex
{
  vec4 gl_Position;
  float gl_PointSize;
  float gl_ClipDistance[];
};


// OpenGL 4.0 and above define additional system-generated input values:
in int gl_SampleID;
in vec2 gl_SamplePosition;
in int gl_SampleMaskIn[];

// Fragment Shaders have the following built-in input variables.
in vec4 gl_FragCoord;
in bool gl_FrontFacing;
in vec2 gl_PointCoord;

// Fragment Shaders have the following built-in output variables.
out float gl_FragDepth;

// Compute Shaders have the following built-in input variables.
in uvec3 gl_NumWorkGroups;
in uvec3 gl_WorkGroupID;
in uvec3 gl_LocalInvocationID;
in uvec3 gl_GlobalInvocationID;
in uint  gl_LocalInvocationIndex;
const uvec3 gl_WorkGroupSize;   // GLSL ≥ 4.30
```

可以看到 gl_PerVertex 块中定义了四维向量 gl_Position，是每一个输入顶点有自动绑定的内置变量。

GLSL 的类型系统：

- Basic types
    - 1.1 Scalars
    - 1.2 Vectors
    - 1.3 Matrices
    - 1.4 Opaque types
    - 1.4.1   Samplers
    - 1.4.2   Images
    - 1.4.3   Atomic counters
- Arrays
    - 2.1 Opaque arrays
    - 2.2 Arrays of arrays
- Structs

其中，有三种不透明类型，表示着色器以某种方式引用的外部对象。不透明变量不像常规类型那样具有一个值，它们只是引用真实数据的标记。因此，它们只能用作函数的参数，由这些函数返回、修改实际引用的数据。

它们有两种方式声明：

- 使用 uniform 声明为全局中变量，包含 Opaque Array 类型；
- 作为 uniform 结构体的成员进行声明；

不透明类型不能作为表达式的部分使用，不可以是 buffer-blacked 接口块，或者 in/out 变量，但可以作为函数的输入参数，以允许作为参数传入。

不透明类型不能是左值，Non-array Opaque 类型只能是和参数的同样类型才能传入函数。

数组化的不透明类型可以使用数组索引和结构体字段选择，通过 .length() 方法。

接口块 Interface Block 是一批变量定义，有名字，等价于结构体，并冠以 input, output, uniform 类型修饰符，或者 buffer 变量。如内置的 out gl_PerVertex { ... } 变量就是用于输出的接口块，叫做 gl_PerVertex 名字。

```c glsl
storage_qualifier block_name
{
  <define members here>
} instance_name;
```

原子计数器类型 Atomic Counter 是 GLSL 的一种变量类型 *atomic_uint*，内存来自 Buffer Object，用于内存的原子操作，可以认为是缓冲区图像变量的一种非常有限的形式。也只能声明为 uniform 或是 in 函数参数。

原子操作可以对一个内存位置的图像数据进行 read/modify/write，并且操作保证是原子的：如果两个着色器对同个内存的图像执行同样的原子操作，只有一个会先执行完毕，然后再轮到下一个。

相比着色器对图像进行 load/store 或使用 Shader Storage Buffer Objects，原子计数器的主要的功能限制是只能使用无符号整数，旧版中还限制增、减量为 1。如果功能满足要求，应该尽量使用它它来替代图像的 Load/Store。


GLSL 中的 Sampler 是变量类型集合，其中的变量必需为 uniform 或者使用函数参数类型。程序中的每个 Sampler 表示某种纹理类型的一个纹理，对应类型的纹理可以被 Sampler 使用。

Table 6.1 Texture Targets and Corresponding Sampler Types

    | Target (GL_TEXTURE*  |   Sampler Type   |    Dimensionality    |
    |----------------------|------------------|----------------------|
    | 1D                   | sampler1D        | 1D                   |
    | 1D_ARRAY             | sampler1DArray   | 1D array             |
    | 2D                   | sampler2D        | 2D                   |
    | 2D_ARRAY             | sampler2DArray   | 2D array             |
    | 2D_MULTISAMPLE       | sampler2DMS      | 2D multisample       |
    | 2D_MULTISAMPLE_ARRAY | sampler2DMSArray | 2D multisample array |
    | 3D                   | sampler3D        | 3D                   |
    | CUBE                 | samplerCube      | cube-map texture     |
    | ARRAY                | samplerCubeArray | cube-map array       |
    | RECTANGLE            | samplerRect      | 2D rectangle         |
    | BUFFER               | samplerBuffer    | 1D buffer            |

上表展示了 GLSL 着色器程序中可以使用的纹理采样类型和对应维度信息，对应的 OpenGL 纹理枚举类型名称相应添加 GL_TEXTURE 前缀。



GLSL Type Modifiers：

- *const* 标识只读变量，可以是编译时常量，如果在编译时初始化。
- *in* 数据会输入到颜色器的变量；
- *out* 数据会从着色器输出的变量；
- `inout` Copy in and copy out
- *uniform* 数据会从应用程序传递到着色器，并在给定的图元中保持不变，可以理解从 CPU 到 GPU。
- *buffer* 标记应用程序读写的内存块，它会被着色器程序引用。
- *shared* 标记变量在本地工作组共享，只在计算着色器时用建立内存共享。

补充一个在 OpenGL 1.3 版本开始标记为 deprecated 的存储修饰 `varying`，它用来链接顶点着色器与片段着色器的数据插值，相当顶点着色器的 *out* 变量，和片段着色器的 *in* 变量。存储的是顶点着色器的输出，同时作为片段着色器的输入。顶点着色器把需要传递给片段着色器的数据存储在一个或多个 varying 变量中，这些变量在片段着色器中需要有相对应的声明且数据类型一致，然后在光栅化过程中进行插值计算。

在渲染流水线上，不同的着色器会按顺序进行工作，着色器前后存在数据输入输出，这样所有着色器才能串联起来完成一项完整的渲染工作。

此外，还扩展的指令修饰符，如 require、enabled、disable、warn 等。

注意 `uniform` 类型修饰符是专用于从应用程序数据传递到着色器的一种方式，它表明变量、接口或者代码块是全局的 Global，意味着 uniform 变量必须在每个着色器程序对象中都是独一无二的，而且它可以被着色器程序的任意着色器在任意阶段访问。第二，无论你把 uniform 值设置成什么，uniform 会一直保存它们的数据，直到它们被重置或更新。

Uniform 代码块可以使用 Layout 修饰符：

- *shared* 表示 uniform block 在多个着色程序中共享，默认。
- *packed* 最小化 uniform block 的内存使用，通常会色色色他 *shareed* 布局。
- *std140* 使用 GLSL Version 1.40 标准布局。
- *std430* 使用 GLSL Version 4.30 标准布局。
- *row_major* 使用 uniform block 中的矩阵在行主序元素共享。
- *column_major* 使用 uniform block 中的矩阵在列主序元素共享，默认方式。

GLSL 还有两个容器类型向量和矩阵 vectors and matrices。

GLSL 中的向量是一个可以包含有 1、2、3 或者 4 个分量的容器，分量的类型可以是默认基础类型，也可以是下面的形式，n 代表分量的数量：

- vecn  包含 n 个 *float* 分量的默认向量。
- bvecn 包含 n 个 *bool* 分量的向量。
- ivecn 包含 n 个 *int* 分量的向量。
- uvecn 包含 n 个 *unsigned int* 分量的向量。
- dvecn 包含 n 个 *double* 分量的向量。

Table 2.3 GLSL Vector and Matrix Types

    | Base Type | 2D vec | 3D vec | 4D vec |           Matrix Types           |
    |-----------|--------|--------|--------|--------------|---------|---------|
    | float     | vec2   | vec3   | vec4   | mat2         | mat3    | mat4    |
    |           |        |        |        | mat2x2       | mat2x3  | mat2x4  |
    |           |        |        |        | mat3x2       | mat3x3  | mat3x4  |
    |           |        |        |        | mat4x2       | mat4x3  | mat4x4  |
    |-----------|--------|--------|--------|--------------|---------|---------|
    | double    | dvec2  | dvec3  | dvec4  | dmat2        | dmat3   | dmat4   |
    |           |        |        |        | dmat2x2      | dmat2x3 | dmat2x4 |
    |           |        |        |        | dmat3x2      | dmat3x3 | dmat3x4 |
    |           |        |        |        | dmat4x2      | dmat4x3 | dmat4x4 |
    |-----------|--------|--------|--------|--------------|---------|---------|
    | int       | ivec2  | ivec3  | ivec4  | -            | -       | -       |
    | uint      | uvec2  | uvec3  | uvec4  | -            | -       | -       |
    | bool      | bvec2  | bvec3  | bvec4  | -            | -       | -       |

向量的运算是一种叫做 Swizzling 的灵活方法，可以访问各个分量：

```c glsl
vec4 someVec;
someVec.x + someVec.y;

vec2 someVec2;
vec4 otherVec = someVec2.xyxx;
vec3 thirdVec = otherVec.zyy;
// someVec.xx = vec2(4.0, 4.0); is not allowed.

vec4 someVec3;
someVec4.wzyx = vec4(1.0, 2.0, 3.0, 4.0); // Reverses the order.
someVec4.zx = vec2(3.0, 5.0); // Sets the 3rd component of someVec to 3.0 and the 1st component to 5.0

// in OpenGL 4.2 or ARB_shading_language_420pack
float aFloat; // scalar type variable
vec4 someVec4 = aFloat.xxxx;
```

可以通过 x, y, z, w 访问具体的数据，分别是数据中的第一、二、三、四个分量。可以在赋值号右侧中重复使用某些分量，也可以对顺序进行重新排序，并通过赋值产生新的交换过不同分量的值。

注意，只有四维向量才有四个分量，如果通过 vec3 变量去访问 w 分量就会编译出错。

有三组 Swizzle masks，没有什么功能区别，只是字符不同，是语法糖。但是不能混用，如 `.xrs` 就不正确：

- xyzw 用于向量；
- rgba 用于颜色；
- stpq 用于纹理坐标；

在 OpenGL 4.2 或 ARB_shading_language_420pack 中，标量也可以使用 Swizzling 语法，它们虽然只有一个分量。

矩阵类型中，每个行就是一个向量，同样适用 Swizzling 方法。

```c glsl
mat3 theMatrix;
theMatrix[1] = vec3(3.0, 3.0, 3.0); // Sets the second column to all 3.0s
theMatrix[2][0] = 16.0; // Sets the first entry of the third column to 16.0.

// However, the result of the first array accessor is a vector, so you can swizzle that:
mat3 theMatrix;
theMatrix[1].yzx = vec3(3.0, 1.0, 2.0);
```
