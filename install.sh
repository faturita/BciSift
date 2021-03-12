sudo apt install -y cmake g++ wget unzip
sudo apt install libgtk2.0-dev pkg-config
sudo apt install clang2
wget -O opencv.zip https://github.com/opencv/opencv/archive/master.zip
wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/master.zip
unzip opencv.zip
unzip opencv_contrib.zip

cd opencv-master
mkdir -p build
cd build
cmake -DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib-master/modules ..
cmake --build .
sudo make install

cd ../..
git clone https://github.com/faturita/vlfeat
cd vlfeat
make DISABLE_OPENMP=yes

cd ..
wget https://github.com/sccn/liblsl/releases/download/v1.14.0/liblsl-1.14.0-bionic_amd64.deb
sudo dpkg -i liblsl-1.14.0-bionic_amd64.deb

cd ..
git clone https://github.com/shipupi/BciSift
cd BciSift
export OpenCV_DIR=~/opencv-master/build
cmake -DCMAKE_CXX_COMPILER=clang++


