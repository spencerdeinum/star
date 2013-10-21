COMPILER=clang
OPTIONS=-std=c99 -Weverything

SOURCES=$(wildcard src/*.c)
OBJECTS=$(subst src/,build/,$(subst .c,.o,$(SOURCES)))

default: star

build/%.o: src/%.c
	$(COMPILER) $(OPTIONS) -c $< -o $@

star: $(OBJECTS)
	$(COMPILER) $(OPTIONS) -o bin/star $(OBJECTS)

clean:
	$(RM) build/* bin/*

valgrind: star
	valgrind --tool=memcheck --leak-check=yes --suppressions=valgrind.supp ./bin/star

gdb: star
	gdb ./bin/star
