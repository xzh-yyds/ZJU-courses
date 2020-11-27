#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    FILE *fp;
    if((fp=fopen("/var/log/kern.log", "r")) == NULL){
        printf("Error: cannot open the log file.\n");
        exit(1);
    }
    fseek(fp, 0, SEEK_SET);
    char c = fgetc(fp);
    int matched = 0;
    int find = 0;
    while(c != EOF){
        if(c=='#') matched++;
        else matched=0;
        
        if(matched==3){find = 1; break;}
        c = fgetc(fp);
    }
    if(find){
        printf("Find!\n");
    }else{
        printf("Error: cannot find log info. :(\n");
        exit(1);
    }
    c = fgetc(fp);
    matched=0;
    int out = 0;
    while(c != EOF){
        if(out==0 && c==']') out++;
        else if(out==1 && c==' ') out++;
        else if(out==2){if(c!='#') printf("%c", c);}
        
        if(c=='\n') out = 0;    
        else if(c=='#') matched++;

        if(matched==3) break;
        c = fgetc(fp);
    }
    printf("End\n");
    fclose(fp);
    return 0;
}
