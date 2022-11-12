if not exist build\ (
    mkdir build 
)

cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=C:\Users\ionut\OneDrive\Desktop\vcpkg\scripts\buildsystems\vcpkg.cmake
cmake --build .
cmake --install .