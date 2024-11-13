##### 概论：

三维图形技术：表达与表现三维数字对象，构建和创造虚拟世界（内容创建[建模]、仿真[动画]、呈现[渲染]）

照片（图像）： 记录真实世界投影在相机成像平面的影像

离散表示：光栅；栅格图像与矢量图形；矢量图形的光栅化：扫描转化

渲染成像：光的计算科学；仿真动画：运动的计算科学

国内CAD软件的公司主要有中望龙腾、山大华天和数码大方等；主流国外：SolidWorks、CATIA、Pro/Engineer

CAD软件底层技术：三维几何建模引擎，几何约束求解引擎



##### 三维几何造型概述：

三维对象的表示：面表示|体表示|**边界表示**|**空间分解表示**|**八叉树（octrees）表示**|**构造实体几何表示**|**扫描表示**

​                               **隐式表示**|

- 边界表示：用组成实体边界的基本元素(即顶点、边和面)及其连接关系信息表示实体。采用边界表示法定义的实体为有限数量的面的集合，面则由边及顶点加以定义。

<img src="C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20241105142627169.png" alt="image-20241105142627169" style="zoom:50%;" />用多边形表示物体的边界|用光滑曲面表示物体的边界（曲面）

- 均匀分解：选一个立方体空间，均匀划分，三维数组c [i] [j] [k]表示物体\数组的元素与单位小立方体对应

  - 高精度的表示需要细致的空间分解，即体素要小。

  - 采用多种体素的分解：（各种不同的小的单位块）

<img src="C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20241105143557716.png" alt="image-20241105143557716" style="zoom:50%;" />

<img src="C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20241105143709693.png" alt="image-20241105143709693" style="zoom:50%;" /> 八叉树，根节点对应整个物体空间，Full/Empty/Partial_dfs

<img src="C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20241105143946329.png" alt="image-20241105143946329" style="zoom:50%;" />

- 利用集合运算（并、交、差）进行实体造型
  - 表示简单，容易被修改， 图形输入；表示物体的CSG树不唯一，求交计算麻烦

- 扫描表示：基于一个基体（封闭的二维区域）沿某一路径运动而产生形体（平移旋转，广义扫描[siz,shape]）
  - 简单，图形输入；作几何变换困难、表示形体的覆盖域非常有限
- 隐式表示：不直接指定模型点的坐标，而是用方程的解来表示，这类方法称为隐式表示
  - 转换为网格表示[Marching Cubes]——隐式曲面没有表面的直接表示，使得绘制和一些几何处理比较困难
  - 算法：[划分网格] [计算网格顶点函数值,根据顶点函数值的正负做标记label(v)] [找边集端点值不同,连折]

<img src="C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20241105145059484.png" alt="image-20241105145059484" style="zoom:50%;" />立方体共15种模式，256种组合，两种对称[顶点状态|旋转]



**曲线曲面造型概述**

- 概念：初等解析曲面：例如平面、圆柱面、圆锥面、球面，大多数机械零件属于这一类；自由曲线曲面：不能由初等解析曲面组成（飞机汽车外形）

- 曲线的参数表示：将曲线上各点的坐标变量显式地表示成参数t的函数形式 P(t)=(x(t), y(t), z(t)) , t ∈[a,b]
  - 参数表示有更大的自由度，不依赖坐标系；变化率以切矢量表示，几何变换比较容易，交互能力强
- 插值、逼近、连续(参数连续性用 $C^{阶数}$表示，几何连续性用 $G^{阶数}$表示)
  - $G^1$ 是连接处切矢量方向相同， $G^2$ 是连接处曲率矢量相等

<img src="C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20241105150506881.png" alt="image-20241105150506881" style="zoom:50%;" />

<img src="C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20241105153126068.png" alt="image-20241105153126068" style="zoom:50%;" />

<img src="C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20241105154134146.png" alt="image-20241105154134146" style="zoom:50%;" />





