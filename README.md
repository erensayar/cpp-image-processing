Developed on Linux and STILL CONTINUES


# Requirements For Linux

## 1. Install OpenCV

### Install minimal prerequisites (Ubuntu 18.04 as reference)
    sudo apt update && sudo apt install -y cmake g++ wget unzip
### Download and unpack sources
    wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
    wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/4.x.zip
    unzip opencv.zip
    unzip opencv_contrib.zip
### Create build directory and switch into it
    mkdir -p build && cd build
### Configure
    cmake -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib-4.x/modules ../opencv-4.x
### Build
    cmake --build .
### MAKE Build Files
    make -j4
### Save To OS
    sudo make install

### Copy Libraries (For Linux)
    cp -r /usr/local/include/opencv4/opencv2 /usr/include/c++/10

## 2. Install OpenCV Dependencies

### 2.1. Easiest Way Install The Dependencies To Linux
    sudo apt-get install libopencv-*

### 2.2. Manuel Installation
    sudo apt-get install python-dev python3-dev libqt4-dev libgphoto2-dev python3-numpy python-numpy libv4l-dev libv4l2rds0 libgtk-3-dev libgstreamer-plugins-base1.0-dev libgst-dev cmake-qt-gui build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libswscale-dev libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev libgstreamer-vaapi1.0-dev libavformat-dev libavformat-ffmpeg-dev -y

## 3. Build And Run

### 3.1. Build :

    mkdir build && cd build
    cmake ..
    cmake --build .

### 3.2. Run : 

    ./ImageProcessing <IMAGE_PATH>
    
Like This:

    ./ImageProcessing ../resources/paper.jpg


## Sources

* Murtaza Workshops - Resource's from Murtaza and I will complete him lesson.