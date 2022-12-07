install:
	gcc test.c -o out/test.o
	gcc obfuscator.c -o out/obfuscator
	bash ../scripts/generate_shellcode.sh out/test.o out/shellcode
	./out/obfuscator out/shellcode
	nasm -f elf64 -o out/obfuscated.o out/obfuscated.s
	ld   -o obfuscated out/obfuscated.o

clean:
	rm out/* obfuscated