Pour tester:
gcc tris.c bench_tris.c -o bench
./bench

Valgrind:
valgrind --leak-check=full ./bench -> 0 leaks
