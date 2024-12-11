# Cherno-OpenGL
OpenGL 小白学习之路\
目前为止，实现了Cherno OpenGL 课程第26节的内容\
正在通过 LearnOpenGL学习新的opengl知识，会增加新的测试脚本\
src文件夹下有一个test文件夹，具体的逻辑代码写在了每一个 test 脚本中\
当运行此项目时，会先显示一个主界面，主界面中有一个可点击的目录，点击某一个目录之后\
会显示这项对应的具体的 test 脚本内容\
\
非 test 文件夹下的代码是一些代码封装，比如Shader代码封装了读取 .shader 文件
生成 shader 程序的代码，这样书写代码的时候就不需要总是重复写了\
\
**Test** 所有 Testxxxxx 代码的基类\
**TestClearColor** 调节 glClear 函数参数，实现动态效果\
**TestTexture2D** 绘制一个图片\
**TestTextureBlend** 启用混合，将两张图片混合\
**TestTenRotateCube** 一个旋转的正方体\
**TestLightColor** 实现了包含环境光漫反射高光在内的光照效果\
**module_loading** 加载模型，但是对模型有要求（必须有漫反射贴图，必须要带有相应的mtl文件且文件中的贴图路径是相对路径(mtl本身是一个文本文件，可以用记事本打开，把一些贴图的绝对路径比如C://tex1.jpg这样的修改成 tex1.jpg这样的相对路径))\
#### 代码规范修改 --2024.12.11  \
\
因为封装增加了抽象程度，导致我代码写出 bug 的概率增加，且导致修 bug 时间大幅延长，经常一天写 + 改一个shader \
所以之后开头不是 test 的代码都具有main函数入口，不再抽象封装，直接将所有逻辑写在一个.cpp 文件中\
使用方法就是将除了要运行的 含有main 函数的 .cpp 文件全部右键排除在项目之外，将要运行的 .cpp 文件包含运行\


