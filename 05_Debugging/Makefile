all: range

test: range test/test.sh 
	dash test/test.sh

range: format range.c
	gcc range.c -O0 -g -o range

format: range.c
	clang-format -i range.c

clean:
	rm range *.out
