# University-Comp-Micro
Simple Micro compiler for ARM based on chapter 2 of "Crafting a Compiler with C" by Fischer and LeBlanc

# Instructions
1. sudo apt install cmake
2. check CMakeLists.txt and make sure cmake version is compatible (cmake --version)
3. create directory for build: `mkdir cmake-build-debug`

###### Compilation steps:

`cmake cmake-build-debug . `

`cmake --build cmake-build-debug `

`cmake-build-debug/comp test_file.micro `

# TODOs
- funciones pequeñas:
	- Kevin:
		- lookup (para symbol table) (optimizar)
		- enter (para symbol table) (optimizar)
		- generate (action rutines)
	
- adaptar action rutines para generar ARM (Kevin)
- agregar if (pendiente)
- agregar optimización expresión con dos literals (pendiente)
