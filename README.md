## 介绍
使用c++实现图像处理，使用std::thread多线程加速。

## 依赖
* https://github.com/nothings/stb   图片读写
* https://github.com/progschj/ThreadPool   线程池实现多线程

## 特征
###  亮度检测
计算0.299*r + 0.587 * g + 0.114 * b作为亮度，大于给定阈值设置灰度，输出灰度图。
### 高斯模糊 
首先在横向使用一维高斯核卷积，随后纵向再使用一维高斯核卷积。
### 边缘检测
首先得到灰度图，使用sobel方法检测边缘。

## 使用
可以通过修改main函数中的成员变量来修改参数
* num_thread 线程数量
* edge_threshold 边缘检测中的阈值，（0， 1）之间
* bright_threshold 亮度检测中的阈值，（0， 1）之间
* path 文件夹路径