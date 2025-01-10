sudo apt install pipx
sudo pipx ensurepath --force
pipx install --force conan
/root/.local/bin/conan profile detect
/root/.local/bin/conan install . --output-folder=build --build=missing -s compiler.cppstd=20
chmod +x build
mv color.json build/color.json
mv tree-sitter-cpp.so build/tree-sitter-cpp.so
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
sudo make
