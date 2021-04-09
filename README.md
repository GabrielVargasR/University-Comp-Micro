# Micro Compiler IC-5701
Simple Micro compiler for ARM based on chapter 2 of "Crafting a Compiler with C" by Fischer and LeBlanc.

### Integrantes
- Gabriel Vargas Rodríguez - 2018103129
- Kevin Sánchez Cerdas - 2019206148

# Instructions
1. sudo apt install cmake
2. check CMakeLists.txt and make sure cmake version is compatible (cmake --version)
3. create directory for build: `mkdir cmake-build-debug`

###### Compilation steps:

`cmake cmake-build-debug . `

`cmake --build cmake-build-debug `

`cmake-build-debug/comp test_file.micro `
