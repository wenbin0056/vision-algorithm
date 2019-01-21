#vision-algorithm


#*Opencv*
===
### ubuntu下OpenCV的安装
* 下载：https://opencv.org/releases.html 下载source。3.4.1

>#####升级cmake版本
1. wget https://cmake.org/files/v3.12/cmake-3.12.0.tar.gz (g++版本要求高，使用下面低版本的)
* wget https://cmake.org/files/v2.8/cmake-2.8.12.2.tar.gz --no-check-certificate
2. ./bootstrap --prefix=/usr
3. make
4. sudo make install
5. cmake -version

>#####升级g++编译器：
1. wget -c http://mirrors.ustc.edu.cn/gnu/gcc/gcc-4.1.2/gcc-4.1.2.tar.bz2      
2. ./contrib/download_prerequisites
3. mkdir gcc-build-8.2.0
4.  cd gcc-build-8.2.0  
5. ../configure -enable-checking=release -enable-languages=c,c++ -disable-multilib  
6. make -j4
7. sudo make install
8. gcc -v


* ~~~sudo apt-get install cmake ~~~


* sudo apt-get install build-essential libgtk2.0-dev libavcodec-dev libavformat-dev libjpeg.dev libtiff4.dev libswscale-dev libjasper-dev  
* mkdir my_build_dir
* cd  my_build_dir
* cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
* make 
* sudo make install
* export LD_LIBRARY_PATH=/usr/local/lib/



### 嵌入式移植入OPENCV
===
> 
* 解压。
* cd opencv-2.4.13.6/
* mkdir /usr/local/opencv/install_opencv
* mkdir /usr/local/opencv/config_opencv
* sudo cmake-gui 
* source code：/work/arm-opencv/opencv-2.4.13.6
* build：/usr/local/opencv/config_opencv
* configure-> unix Makefile -> specify option for cross-cpmpiling
* LINUX 4.9.37
* /opt/hisi-linux/x86-arm/aarch64-himix100-linux/bin/aarch64-himix100-linux-gcc
* /opt/hisi-linux/x86-arm/aarch64-himix100-linux/bin/aarch64-himix100-linux-g++
* finish




### Opencv Function

### API文档
>
1. https://docs.opencv.org/2.4.9/modules/refman.html


#### 灰度变换技术
> 
1. 阈值化处理
2. 直方图处理
3. 距离变换
4. Gamma矫正
5. 线性变换
6. 对数变换
7. 对比度拉伸
8. 灰度级分层
9. 灰度比特平面


#### 平滑技术
> 
1. 傅里叶变换。
2. 图像噪声。
3. 空间平滑。




#### 边缘检测
> 
* Sobel
* Laplace
* Roberts
* Prewitt
* Canny
* Marr-Hildreth
* 几何检测
>	> 1. 霍夫变换
>	> 2. 线检测技术
>	> 3. LSD快速直线检测
>	> 4. 圆检测技术
* 形状检测
* 角点检测



#### 腐蚀膨胀操作



#### 开关运算操作



#### 形态学梯度



####  分割算法
>
1. 分水岭分割
2. FloodFill分割
3. 均值漂移MeanShIFT
4. 图割Grabcut

### 特征分析
>
1. 尺度空间
2. 特征描述算子，
SIFT特征
SURF特征
ORB特征
* 方向梯度直方图HOG
* 

====








