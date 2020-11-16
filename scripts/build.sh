BASE_DIR = $PWD
cd build
rm -r -f *

cmake ../ -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake --build . --config Debug
cd $BASE_DIR