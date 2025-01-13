sudo apt install pipx
pipx install --force conan
pipx ensurepath
conan profile detect
conan install . --output-folder=build --build=missing -s compiler.cppstd=20
sudo chmod +x build
sudo mv color.json build/color.json
sudo mv tree-sitter-cpp.so build/tree-sitter-cpp.so
cd build
sudo cmake .. -DCMAKE_BUILD_TYPE=Release
sudo make
