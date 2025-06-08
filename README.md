# my_cat

## Building:
### Build type in conan command and cmake has to match, else missing possible headers problem

```
conan install . --output-folder=build --build=missing -pr:b=debug -pr:h=debug
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"
cmake --build build
```
