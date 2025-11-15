filename=$(basename "$1" .c)

# preprocess
gcc -E -P $1 -o $filename.i

#compile
gcc -S -O -fno-asynchronous-unwind-tables -fcf-protection=none $filename.i
rm $filename.i

#assemble
gcc $filename.s -o $filename
rm $filename.s

exit 0