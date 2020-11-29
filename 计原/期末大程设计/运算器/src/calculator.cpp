#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "integer.h"
#include "float.h"

int main(void)
{
	char num1[33], num2[33];
	char* p = NULL;
	word m, n, result;
	char op;
	int option;

	printf("欢迎使用运算器模拟器！\n\n");

	while (1) {
		printf("请选择运算对象（0-整数 1-浮点数）：");
		scanf("%d", &option);
		getchar();
		switch (option) {
		case 0:
			printf("请输入运算符：+、-、*、/、%%：");
			scanf("%c", &op);
			printf("请输入两个整数：");
			scanf("%s", num1);
			getchar();
			scanf("%s", num2);
			getchar();
			m = atom(num1);
			n = atom(num2);
			switch (op) {
			case '+':
				result = madd(m, n);
				p = mtoa(result);
				printf("结果为：");
				printf("%s\n\n", p);
				break;
			case '-':
				result = msub(m, n);
				p = mtoa(result);
				printf("结果为：");
				printf("%s\n\n", p);
				break;
			case '*':
				result = mmul(m, n);
				p = mtoa(result);
				printf("结果为：");
				printf("%s\n\n", p);
				break;
			case '/':
				if (num2) {
					result = mdiv(m, n);
					p = mtoa(result);
					printf("结果为：");
					printf("%s\n\n", p);
				}
				else printf("Error！ 除数不能为0！\n\n");
				break;
			case '%':
				if (num2) {
					result = mmod(m, n);
					p = mtoa(result);
					printf("结果为：");
					printf("%s\n\n", p);
				}
				else printf("Error！ 除数不能为0！\n\n");
				break;
			default:
				printf("Error！ 无效的运算符！\n\n");
			}
			break;
		case 1:
			printf("请输入运算符：+、-、*、/：");
			scanf("%c", &op);
			printf("请输入两个浮点数：");
			scanf("%s", num1);
			getchar();
			scanf("%s", num2);
			getchar();
			m = atof(num1);
			n = atof(num2);
			switch (op) {
			case '+':
				result = fadd(m, n);
				p = ftoa(result);
				printf("结果为：");
				printf("%s\n\n", p);
				break;
			case '-':
				result = fsub(m, n);
				p = ftoa(result);
				printf("结果为：");
				printf("%s\n\n", p);
				break;
			case '*':
				result = fmul(m, n);
				p = ftoa(result);
				printf("结果为：");
				printf("%s\n\n", p);
				break;
			case '/':
				if (num2) {
					result = fdiv(m, n);
					p = ftoa(result);
					printf("结果为：");
					printf("%s\n\n", p);
				}
				else printf("Error！ 除数不能为0！\n\n");
				break;
			default:
				printf("Error！ 无效的运算符！\n\n");
			}
			break;
		default:
			printf("Error！你选择的运算对象不存在！\n\n");
		}
	}
	return 0;
}