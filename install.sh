pip install conan
conan profile detect
sudo proxychains4 conan install . --output-folder=build --build=missing -s compiler.cppstd=20
chmod +x build
mv color.json build/color.json
mv tree-sitter-cpp.so build/tree-sitter-cpp.so
cd build
sudo cmake .. -DCMAKE_BUILD_TYPE=Release
sudo make
