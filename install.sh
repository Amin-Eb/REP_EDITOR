pip install conan
sudo conan profile detect
sudo conan install . --output-folder=build --build=missing -s compiler.cppstd=20
sudo chmod -R 777 build
mv color.json build/color.json
mv tree-sitter-cpp.so build/tree-sitter-cpp.so
cd build
sudo cmake .. -DCMAKE_BUILD_TYPE=Release
sudo make
