#g++ main.o -o test-sfml -L/Users/nathanialstodick/SFML-2.5.1-macOS-clang/lib -lsfml-graphics -lsfml-window -lsfml-system

SHELL=/bin/sh


# we can cleam this up a lot using variables
objects = main.o snake.o
flags = -std=c++14 -g
sfml_link_flags = -L/Users/nathanialstodick/SFML-2.5.1-macOS-clang/lib \
	-lsfml-graphics -lsfml-window -lsfml-system

sfml_include_flags = -I/Users/nathanialstodick/SFML-2.5.1-macOS-clang/include
#main executable

snake : $(objects)
		clang++ $(flags) $(objects) -o snake $(sfml_link_flags)
		# append correct RPATH
		install_name_tool -add_rpath /Users/nathanialstodick/SFML-2.5.1-macOS-clang/lib snake

# this only changes when the snake and driver source files change
main.o : snake.cpp main.cpp include/snake.hh include/sandbox.hh
		clang++ -c main.cpp $(flags) $(sfml_include_flags)

snake.o : snake.cpp include/snake.hh 
		clang++ -c snake.cpp $(flags) $(sfml_include_flags)

sandbox.o: include/sandbox.hh

# phony target - this would be useful in the (unlikely) event that we have a file
# named clean, which would never change and clean rule would never run
.PHONY: clean
clean :
	rm $(objects)

# this is good, but we can clean this up using variables