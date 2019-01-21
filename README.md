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
* 

IplImage
Mat
CvMat

在图片上画根线

分割算法
GrabCut

直线检测

#### 边缘识别
> 
* 13



####  123

====








