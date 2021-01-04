#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned __int32 uint32_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int8 uint8_t;

typedef uint32_t dword;
typedef uint16_t word;
typedef uint8_t byte;

typedef struct Section{
    byte name[8];
    dword vlen;
    dword voff;
    dword len;
    dword off;
}Section;

typedef struct Import{
    byte *dll_name;
    byte *apis;
}Import;

void print_sect_info(Section s){
    printf("name: %s\n", s.name);
    printf("length in mem: 0x%x\n", s.vlen);
    printf("offset in mem: 0x%x\n", s.voff);
    printf("length in file: 0x%x\n", s.len);
    printf("offset in file: 0x%x\n", s.off);
}

dword locate_in_file(Section sects[], int n, dword vaddr){
    int i=0;
    for(i=0; i<n; i++){
        if(sects[i].voff <= vaddr && vaddr - sects[i].voff < sects[i].vlen){
            return vaddr - sects[i].voff + sects[i].off;
        }
    }
    return 0;
}

int main(int argc, char **argv){
    char *filename;
    FILE *exef;
    int exe_len;
    int sects_num;
    int i=0;
    Section *sects;
    byte *exe;
    byte *sect_info;
    byte *import_tbl;
    byte *pe;
    dword pe_base;
    dword vaddr_import;
    dword vlen_import;
    int dlls_vn;
    int dlls_n;
    Import *dlls;

    if(argc > 1){
        filename = (char*)malloc(strlen(argv[1]) + 1);
        strcpy(filename, argv[1]);
    }else{
        filename = (char*)malloc(strlen("mine.exe") + 1);
        strcpy(filename, "mine.exe");
    }
    printf("file: %s\n\n", filename);
    exef = fopen(filename, "rb+");
    if(exef == NULL){
        printf("Error when open exe\n");
        return -1;
    }
    fseek(exef, 0, SEEK_END);
    exe_len = ftell(exef);
    fseek(exef, 0, SEEK_SET);
    exe = (byte*)malloc(sizeof(byte) * exe_len);
    fread(exe, sizeof(byte), exe_len, exef);
    fclose(exef);

    pe_base = *(dword*)(exe + 0x3c);
    // printf("pe base: %x\n", pe_base);
    
    pe = exe + pe_base;
    sects_num = *(word*)(pe + 6);
    // printf("sections number: %d\n", sects_num);

    sects = (Section*)malloc(sizeof(Section) * sects_num);
    
    sect_info = pe + 0xf8;
    for(i=0; i<sects_num; i++){
        strcpy(sects[i].name, sect_info);
        sects[i].vlen = *(dword*)(sect_info + 0x8);
        sects[i].voff = *(dword*)(sect_info + 0xC);
        sects[i].len = *(dword*)(sect_info + 0x10);
        sects[i].off = *(dword*)(sect_info + 0x14);
        sect_info += 0x28;
    }

    for(i=0; i<sects_num; i++){
        // print_sect_info(sects[i]);
        // printf("\n");
    }

    vaddr_import = *(dword*)(pe + 0x80);
    vlen_import = *(dword*)(pe + 0x84);
    // printf("offset in mem of import table: 0x%x\n", vaddr_import);
    // printf("length in mem of import table: 0x%x\n", vlen_import);

    import_tbl = exe + locate_in_file(sects, sects_num, vaddr_import);
    dlls_vn = vlen_import / 0x14;

    dlls_n = 0;
    for(i=0; ; i++){
        byte *p = import_tbl + i*0x14;
        int nonzero = 0;
        int j=0;
        for(; j<0x14; j++){
            if(*(p+j) != 0){
                nonzero++;
                break;
            }
        }
        if(nonzero > 0){
            dlls_n++;
            continue;
        }
        break;
    }
    dlls = (Import*)malloc(sizeof(Import) * dlls_n);

    for(i=0; i<dlls_n; i++){
        byte *impo = import_tbl + i*0x14;
        dlls[i].dll_name = exe + locate_in_file(sects, sects_num, *(dword*)(impo + 0xc));
        dlls[i].apis = exe + locate_in_file(sects, sects_num, *(dword*)impo);
    }

    for(i=0; i<dlls_n; i++){
        dword* ap = (dword*)dlls[i].apis;
        printf("%s\n", dlls[i].dll_name);
        for(; ; ap++){
            dword api = *ap;
            if(api == 0){
                break;
            }
            if(api & 0x80000000){
                printf("0x%08x\n", api & 0x7fffffff);
            }else{
                byte *api_name = exe + locate_in_file(sects, sects_num, api) + 2;
                printf("%s\n", api_name);
            }
        }
        printf("\n");
    }

    return 0;
}