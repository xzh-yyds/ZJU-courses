#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    char exe[128] = {0};
    char out[128] = {0};

    if(argc <= 1){
        strcpy(exe, "hello.exe");
        strcpy(out, "hello2.exe");
        printf("no arg, use default \"hello.exe -> hello2.exe\"\n");
    }else if(argc <= 2){
        strcpy(exe, argv[1]);
        int i = 0;
        for(i=strlen(exe)-1; i>0; i--){
            out[i+1] = exe[i];
            if(exe[i] == '.') break;
        }
        out[i] = '2';
        memcpy(out, exe, i);
        printf("%s -> %s\n", exe, out);
    }else{
        strcpy(exe, argv[1]);
        strcpy(out, argv[2]);
        printf("%s -> %s\n", exe, out);
    }

    int len_hello;
    unsigned char *hello;
    FILE *fin;
    fin = fopen(exe, "rb");
    fseek(fin, 0, SEEK_END);
    len_hello = ftell(fin);
    fseek(fin, 0, SEEK_SET);
    hello = (unsigned char*)malloc(len_hello);
    fread(hello, sizeof(char), len_hello, fin);
    fclose(fin);

    int header_len = *(short*)(hello + 8) << 4;

    fin = fopen("shell.bin", "rb");
    unsigned char *shell_bin;
    fseek(fin, 0, SEEK_END);
    int len_shell_bin = ftell(fin);
    fseek(fin, 0, SEEK_SET);
    shell_bin = (unsigned char*)malloc(len_shell_bin);
    fread(shell_bin, sizeof(char), len_shell_bin, fin);
    fclose(fin);

    unsigned char *shelldat_bin;
    int len_shelldat_bin = len_shell_bin + header_len;
    shelldat_bin = (unsigned char*)malloc(len_shelldat_bin);
    memcpy(shelldat_bin, shell_bin, len_shell_bin);
    memcpy(shelldat_bin+len_shell_bin, hello, header_len);

    unsigned char *hello2;
    int len_hello2 = len_hello + len_shelldat_bin;
    hello2 = (unsigned char*)malloc(len_hello2);
    memcpy(hello2, hello, len_hello);
    memcpy(hello2+len_hello, shelldat_bin, len_shelldat_bin);
    
    for(int i=header_len; i<len_hello; i++){
        hello2[i] ^= 0x33;
    }

    int page_size = 0x200;
    int page_cnt = len_hello2 / page_size;
    int bytes_in_last_page = len_hello2 % page_size;
    if(bytes_in_last_page == 0){
        bytes_in_last_page = page_size;
    }else{
        page_cnt++;
    }
    
    *(short*)(hello2 + 6) = 0;
    *(short*)(hello2 + 2) = bytes_in_last_page;
    *(short*)(hello2 + 4) = page_cnt;
    *(short*)(hello2 + 0x16) = (len_hello - header_len) / 0x10;
    *(short*)(hello2 + 0x14) = len_hello % 0x10;
    
    FILE *fout = fopen(out, "wb");
    fwrite(hello2, sizeof(char), len_hello2, fout);
    fclose(fout);

    return 0;
}