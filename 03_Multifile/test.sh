ARGS1=(argument1)
ARGS_MULTI=(argument1 argument2 argument3)

./prog 2>&1 | sed "s/prog//" > testprog
./prog-a 2>&1 | sed "s/prog-a//" > testprog-a
./prog-so 2>&1 | sed "s/prog-so//" > testprog-so

./prog "${ARGS1[@]}" >> testprog
./prog-a "${ARGS1[@]}" >> testprog-a
./prog-so "${ARGS1[@]}" >> testprog-so

./prog "${ARGS_MULTI[@]}" >> testprog
./prog-a "${ARGS_MULTI[@]}" >> testprog-a
./prog-so "${ARGS_MULTI[@]}" >> testprog-so

cmp testprog testprog-a
cmp testprog-a testprog-so