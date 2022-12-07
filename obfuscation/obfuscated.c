#include <stdio.h>


int main(int argc, char **argv)
{
    FILE *out_file = fopen("out/obfuscated.hex","r");
    unsigned char code[10000];
    fread(code, 1, sizeof(code), out_file);
    int (*hack_func)();
    hack_func = (int (*)()) code;
    (int)(*hack_func)();
}


