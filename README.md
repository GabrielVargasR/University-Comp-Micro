# University-Comp-Micro
Simple Micro compiler for ARM based on chapter 2 of "Crafting a Compiler with C" by Fischer and LeBlanc

# Instructions
1. sudo apt install cmake
2. check CMakeLists.txt and make sure cmake version is compatible (cmake --version)
3. create directory for build: `<mkdir cmake-build-debug>`

######Compilation steps:

`<cmake cmake-build-debug . >`

`<cmake --build cmake-build-debug >`

`<cmake-build-debug/comp test_file.micro >`




# TODOs
- funciones pequeñas:
	- Kevin:
		- syntax\_error (parser)
		- lookup (para symbol table)
		- enter (para symbol table)
		- generate (action rutines)
		- extract (action rutines)

- adaptar funciones del parser (Gabriel)
- adaptar action rutines para generar ARM (Kevin)
- agregar if (pendiente)
- agregar optimización expresión con dos literals (pendiente)
