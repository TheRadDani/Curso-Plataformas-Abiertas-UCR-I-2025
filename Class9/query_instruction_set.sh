lscpu | grep -o "avx[^ ]*"
echo "---------------------"
echo "Querying for AVX instructions in proc/cpuinfo"
cat /proc/cpuinfo | grep -o "avx[^ ]*" | sort | uniq
echo "---------------------"
gcc -O3 -march=native -ftree-vectorize -mavx2 -o native_program example15.c

clang -march=haswell -mavx2 -O3 -o program example15.c