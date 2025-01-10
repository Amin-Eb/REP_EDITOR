sudo apt install pipx
sudo pipx ensurepath --force
pipx install --force conan
sudo /root/.local/bin/conan profile detect
sudo /root/.local/bin/conan install . --output-folder=build --build=missing -s compiler.cppstd=20
chmod 777 build
mv color.json build/color.json
mv tree-sitter-cpp.so build/tree-sitter-cpp.so
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
sudo make
