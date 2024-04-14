CC = g++

subarray:
	$(CC) -o maximum-subarray-sum/subarray.exe maximum-subarray-sum/main.c
	./maximum-subarray-sum/subarray.exe

matrix:
	$(CC) -o matrix-chain-multiplication/matrix.exe matrix-chain-multiplication/main.c
	./matrix-chain-multiplication/matrix.exe