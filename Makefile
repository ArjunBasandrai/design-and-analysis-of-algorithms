CC = g++

subarray:
	$(CC) -o maximum-subarray-sum/subarray.exe maximum-subarray-sum/main.c
	./maximum-subarray-sum/subarray.exe

matrix:
	$(CC) -o matrix-chain-multiplication/matrix.exe matrix-chain-multiplication/main.c
	./matrix-chain-multiplication/matrix.exe

subsequence:
	$(CC) -o longest-common-subsequence/subsequence.exe longest-common-subsequence/main.c
	./longest-common-subsequence/subsequence.exe

01-dp:
	$(CC) -o 0-1-knapsack-dp/0-1-dp.exe 0-1-knapsack-dp/main.c
	./0-1-knapsack-dp/0-1-dp.exe

01-bb:
	$(CC) -o 0-1-knapsack-bb/0-1-bb.exe 0-1-knapsack-bb/main.c
	./0-1-knapsack-bb/0-1-bb.exe

subset:
	$(CC) -o subset-sum/subset.exe subset-sum/main.c
	./subset-sum/subset.exe

k-m-p:
	$(CC) -o kmp/kmp.exe kmp/main.c
	./kmp/kmp.exe

rabin:
	$(CC) -o rabin-karp/rabin-karp.exe rabin-karp/main.c
	./rabin-karp/rabin-karp.exe

huffman:
	$(CC) -o huffman-coding/huffman.exe huffman-coding/main.c
	./huffman-coding/huffman.exe