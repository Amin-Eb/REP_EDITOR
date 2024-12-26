pip install conan
conan profile detect
conan install . --output-folder=build --build=missing -s compiler.cppstd=20
chmod +x build
mv color.json build/color.json
mv tree-sitter-cpp.so build/tree-sitter-cpp.so
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
sudo make
