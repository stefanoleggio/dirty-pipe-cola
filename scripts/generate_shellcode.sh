# Usage: bash generate_shellcode.sh executable.o shellcode.txt
objdump -d $1 | grep -Po '\s\K[a-f0-9]{2}(?=\s)' | sed 's/^/\\x/g' | perl -pe 's/\r?\n//' | sed 's/$/\n/' > $2