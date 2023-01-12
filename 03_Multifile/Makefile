GENERATES = prog prog-* README *.so *.a
CFLAGS = -fPIC
TRASH = *.o *~ o.* testprog*

%.o: %.c
		cc $(CFLAGS) $< -c -o $@

all: test

README: prog
		./$< 2> $@

clean-trash:
		rm -f $(TRASH)

clean: clean-trash
		rm -rf $(GENERATES)

liboutput_static.a: const.o fun.o
		ar -rcs $@ $^

liboutput.so: fun.o const.o
		cc -shared $^ -o $@

prog: const.o fun.o prog.o
		cc $^ -o $@

prog-a: prog.o liboutput_static.a
		cc $^ -o $@

prog-so: prog.o liboutput.so
		cc $^ -o $@

test: test.sh prog prog-a prog-so
		bash test.sh 