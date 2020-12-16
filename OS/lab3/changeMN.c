#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	int ret;
	FILE *fp_read;
	FILE *fp_write;
	unsigned char buf[2048];
	char infile[100] = {0};
	char outfile[100] = {0};
	
	if(argc < 2){
		printf("no arg, default source file: myfs\n");
		printf("no arg, default target file: myfs.new\n");
		strcpy(infile, "./myfs");
		strcpy(outfile, "./myfs.new");
	}else if(argc < 3){
		printf("no arg:target, default target file: myfs.new\n");
		strcpy(infile, argv[1]);
		strcpy(outfile, "./myfs.new");
	}else{
		strcpy(infile, argv[1]);
		strcpy(outfile, argv[2]);
	}
	
	fp_read = fopen(infile, "rb");
	if(fp_read == NULL){
		printf("open %s failed!\n", infile);
		return 1;
	}
	printf("open %s success!\n", infile);
	
	fp_write = fopen(outfile, "wb");
	if(fp_write == NULL){
		printf("open %s failed!\n", outfile);
		return 2;
	}
	printf("open %s success!\n", outfile);

	ret = fread(buf, sizeof(unsigned char), 2048, fp_read);
	printf("previous magic number is 0x%x%x\n", buf[0x439], buf[0x438]);
	
	buf[0x438] = 0x66; buf[0x439] = 0x66;

	fwrite(buf, sizeof(unsigned char), 2048, fp_write);
	printf("current magic number is 0x%x%x\n", buf[0x439], buf[0x438]);
	
	while(ret == 2048){
		ret = fread(buf, sizeof(unsigned char), 2048, fp_read);
		fwrite(buf, sizeof(unsigned char), 2048, fp_write);
	}

	if(ret < 2048 && feof(fp_read)){printf("change magic number ok!\n");}
	
	fclose(fp_write);
	fclose(fp_read);

	return 0;
}
