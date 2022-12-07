install:
	gcc test.c -o out/test.o
	gcc obfuscator.c -o out/obfuscator
	bash ../scripts/generate_shellcode.sh out/test.o out/shellcode
	./out/obfuscator out/shellcode
	gcc -m32 obfuscated.c -z execstack -o obfuscated
	./obfuscated

clean:
	rm out/* obfuscated