#vision-algorithm


#*Opencv*
===


>#####升级cmake版本
1. wget https://cmake.org/files/v3.12/cmake-3.12.0.tar.gz (g++版本要求高，使用下面低版本的)
* wget https://cmake.org/files/v2.8/cmake-2.8.12.2.tar.gz --no-check-certificate
2. ./bootstrap --prefix=/usr
3. make
4. sudo make install
5. cmake -version

>#####升级g++编译器：
1. wget -c http://mirrors.ustc.edu.cn/gnu/gcc/gcc-4.1.2/gcc-4.1.2.tar.bz2    
-  wget -c http://mirrors.ustc.edu.cn/gnu/gcc/gcc-5.5.0/gcc-5.3.0.tar.gz  
-  wget -c http://mirrors.ustc.edu.cn/gnu/gcc/gcc-5.5.0/gcc-5.5.0.tar.gz  
2. ./contrib/download_prerequisites
3. mkdir gcc-build-8.2.0
4.  cd gcc-build-8.2.0  
5. ../configure -enable-checking=release -enable-languages=c,c++ -disable-multilib  
6. make -j4
7. sudo make install
8. gcc -v

#### 安装glibc  （5.5gcc）
>
先在一个可以运行的带有老 libc 和 gcc 的系统上，用老 gcc 编译出一个新版本的 gcc + 老 libc，再用这个新 gcc 编译出一个新 gcc + 新 libc，再用这套东东编译整个新系统。

- 查看系统glibc版本：ldd --version
- glibc是linux 系统中最底层的api（应用程序开发接口）
- 几乎其它任何的运行库都会倚赖于glibc
- wget http://ftp.gnu.org/gnu/glibc/glibc-2.22.tar.gz
- tar -zxvf glibc-2.14.tar.gz
- cd glibc-2.14
- mkdir build
- cd build
- ../configure --prefix=/data/apps/glibc2.14
- make -j4
- make install

>
- 更新libstdc++.so.6
- 查看glinc支持的版本:strings /usr/lib/x86_64-linux-gnu/libstdc++.so.6 | grep GLIBCXX
- 查找位置：locate libstdc++.so.6
- 本机找或者网上下载，用新版本的替换，重新创建链接文件

* ~~~sudo apt-get install cmake ~~~

### ubuntu下OpenCV的安装
* 下载：https://opencv.org/releases.html 下载source。3.4.1
* sudo apt-get install build-essential libgtk2.0-dev libavcodec-dev libavformat-dev libjpeg.dev libtiff4.dev libswscale-dev libjasper-dev  
* mkdir my_build_dir
* cd  my_build_dir
* cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
* make 
* sudo make install

- 下载opencv和opencv_contrib，版本号一样，下载github：https://blog.csdn.net/echoamor/article/details/83022352
- opencv_contrib解压后放入opencv目录下
- mkdir build
- cd build
- cmake-gui ..
- configure
- CMAKE_BUILD_TYPE 值处输入RELEASE
- OPENCV_EXTRA_MODULES_PATH 输入opencv_contrib/modules
- BUILD_opencv_world 选择
- generate
- 推出cmake-gui， make  

>
#### opencv_contrib
>
- 
- 下载github：https://blog.csdn.net/echoamor/article/details/83022352







#### 嵌入式移植入OPENCV
===
https://blog.csdn.net/u014525760/article/details/78737379
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

#### 升级cmake-gui
>
- http://rpm.pbone.net/index.php3?stat=3&search=cmake-gui&srodzaj=3
- 下载 cmake-gui-3.5.0-237.1.x86_64.rpm； http://rpm.pbone.net/index.php3/stat/4/idpl/33395678/dir/opensuse_13.x/com/cmake-gui-3.5.0-237.1.x86_64.rpm.html
- rpm -ivh cmake-gui-3.5.0-237.1.x86_64.rpm
- yum install cmake-gui-3.5.0-237.1.x86_64.rpm 自动安装依赖包




rpm包搜索地址:http://rpm.pbone.net/

### OpenEXR
#### Install(no success)
>
- 下载：http://www.openexr.com/downloads.html； ；ImlBase1.0.2.tar.gz；OpenEXR 1.7.0
- http://zlib.net 下载Zlib 1.2.7 
- sudo tar -zxvf ilmbase-1.0.2.tar.gz 
- sudo tar -zxvf openexr-1.7.0.tar.gz 
- sudo tar -zxvf zlib-1.2.7.tar.gz
- cd ilmbase-1.0.2/
- sudo ./configure
- sudo make
- sudo make install
- cd zlib-1.2.11/
- sudo ./configure
- sudo make
- sudo make install
- openexr-1.7.0
- sudo ./configure
- sudo make
- sudo make install

### Opencv Function

### API文档
>
1. https://docs.opencv.org/2.4.9/modules/refman.html

#### 基本操作
>
- 缩放
- 平移
- 坐标映射
- 旋转
- 仿射变换



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
	- 霍夫变换
	- 线检测技术
	- LSD快速直线检测
	- 圆检测技术
* 形状检测
* 角点检测



#### 腐蚀膨胀操作
>
- 实现对目标像素点进行扩展的目的
- erode()/dilate（）



#### 开关运算操作
> 
- 出去噪声及平滑目标边界等功能
 


#### 形态学梯度



####  分割算法
>
1. 分水岭分割
2. FloodFill分割
3. 均值漂移MeanShIFT
4. 图割Grabcut

#### 特征分析
>
1. 尺度空间
2. 特征描述算子
	- SIFT特征：
	- SURF特征：
	- ORB特征：
* 方向梯度直方图HOG
* 局部二值模型LBP
* Haar特征描述



#### 图像拼接
https://www.cnblogs.com/skyfsm/p/7411961.html
> 
- 对每幅图进行特征点提取
- 对对特征点进行匹配
- 进行图像配准
- 把图像拷贝到另一幅图像的特定位置
- 对重叠边界进行特殊处理




 
#### 背景建模


#### 人脸检测


#### 视频稳定


### SVM
>
1. 










