all: esub

test: esub test.sh 
	dash test.sh

esub: format esub.c
	gcc esub.c -o esub

format: esub.c
	clang-format -i esub.c

clean:
	rm esub
