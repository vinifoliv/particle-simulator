# REMARK: ALL OF THE COMMANDS ARE AIMED FOR UBUNTU

default: run

# Runs the project
run: compile
	@./particle_simulator.o

# Installs project dependencies
dependencies:
	@sudo apt-get install libsdl2-dev

# Compiles the project
compile:
	@clang main.c -o particle_simulator.o -lSDL2

clear:
	rm -rf *.o