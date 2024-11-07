default: compile

compile:
	@clang main.c -o particle_simulator.o -lSDL2

clear:
	rm -rf *.o