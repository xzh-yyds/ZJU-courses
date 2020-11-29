#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <malloc.h>
#include "float.h"

void ftrans(dwrd a, dwrd* s, dwrd* e, dwrd* f);
// Assign the value of sign, exponent and fraction of the binary number a
// a - binary number  s - sign  e - exponent  f - fraction

// Transform binary number into string
char* ftoa(dwrd a) {
	dwrd sa, ea, fa;
	char* s;
	int i = 0, integer, bin_decimal, pivot;
	long long decimal, base;

	s = (char*)malloc(sizeof(char) * 100);
	// a is 0
	if (a == 0) {
		strcpy(s, "0.000000000000000000");
		return s;
	}

	ftrans(a, &sa, &ea, &fa);

	if (ea == 0xFF) {
		// a is not a number
		if (fa != 0x800000) {
			strcpy(s, "NaN");
			return s;
		}
		// a is a positive infinite number
		if (sa) {
			strcpy(s, "+INF");
			return s;
		}
		// a is a negative infinite number
		else {
			strcpy(s, "-INF");
			return s;
		}
	}

	// Store the sign
	if (sa) s[i++] = '-';

	// Store the integer
	if ((int)ea - 127 >= 0) {
		integer = fa >> 150 - ea; //(23 - (ea - 127))
		for (; integer > 0; integer /= 10) s[i++] = '0' + integer % 10;
	}
	else {
		integer = 0;
		s[i++] = '0';
	}

	// Reverse the integer
	int j = 0;
	char temp;
	if (s[0] == '-') {
		j++;
		i++;
	}
	for (; j < i / 2; j++)
	{
		temp = s[j];
		s[j] = s[i - 1 - j];
		s[i - 1 - j] = temp;
	}
	if (s[0] == '-')i--;

	// Store '.'
	s[i++] = '.';

	// Intialize the binary decimal
	if ((int)ea - 126 >= 0) bin_decimal = (fa << (ea - 126)) & 0xFFFFFF; //(ea - 127) + 1
	else bin_decimal = (fa >> (126 - ea)) & 0xFFFFFF;
	// The decimal is empty
	if (!bin_decimal) {
		strcpy(&s[i], "000000000000000000");
		return s;
	}

	// Copute the decimal
	decimal = 0;
	pivot = 0x1000000;
	base = 1000000000000000000; //10^18
	for (j = 0; j < 24; j++) {
		bin_decimal <<= 1;
		base >>= 1;
		if (bin_decimal >= pivot) {
			bin_decimal -= pivot;
			decimal += base;
		}
	}

	// Store the decimal
	for (j = 0; j < 18; j++) s[i++] = '0';
	j = i - 1;
	for (; decimal > 0; decimal /= 10) {
		s[j--] = '0' + decimal % 10;
	}
	s[i] = '\0';

	return s;
}

// Transform string into binary number
dwrd atof(char* s) {
	dwrd sa, ea, fa = 0;
	int i = 0, j, flag;

	// Read the sign
	if (s[i] == '-') {
		sa = 1;
		i++;
	}
	else {
		if (s[i] == '+') i++;
		sa = 0;
	}

	// Read the integer
	while (s[i] != '.' && s[i] != '\0') {
		fa += s[i++] - '0';
		if (s[i] != '.' && s[i] != '\0')fa *= 10;
	}

	// The integer is not 0
	if (fa) {
		for (j = 0; !(fa & 0x800000); fa <<= 1, j++);	// Shift the integer to left
		fa <<= 4;	// Spare space for rounding
		ea = 150 - j; //24 - j - 1 + 127
		j += 4;
	}
	// integer is 0
	else {
		ea = 126;
		j = 28;
	}

	// The string has '.'
	if (s[i] == '.') {
		int decimal = 0, bin_decimal = 0, pivot = 1;

		// Read the decimal
		i++;
		while (s[i] != '\0') {
			decimal += s[i++] - '0';
			pivot *= 10;
			if (s[i] != '\0') decimal *= 10;
		}

		// The integer is 0
		if (!fa) {
			if (decimal == 0) return 0;	// The integer and the decimal are both 0
			flag = 0;
		}
		else flag = 1;
		// Transform decimal into binary form
		for (int k = 0; k < j;) {
			decimal <<= 1;
			if (!flag) {
				if (decimal < pivot) ea--;
				else flag = 1;
			}
			if (decimal >= pivot) {
				decimal -= pivot;
				bin_decimal++;
			}
			if (k + 1 < j) bin_decimal <<= 1;
			if (flag) k++;
		}

		fa += bin_decimal;
	}

	if (fa == 0) return 0; // The integer is 0 and it doesn't have a decimal

	fa += 8;	// Rounding
	// Shift right
	while (fa & 0xF0000000) {
		ea++;
		fa >>= 1;
	}

	return (sa << 31) | (ea << 23) | ((fa >> 4) & 0x7FFFFF);
}

// Addition
dwrd fadd(dwrd a, dwrd b) {
	dwrd ma, mb, sa, sb, sans, ea, eb, eans, fa, fb, fans;

	// a or b is 0
	if (a == 0) return b;
	if (b == 0) return a;

	// The absolute number of a is greater than that of b
	if ((a & 0x7FFFFFFF) >= (b & 0x7FFFFFFF)) {
		ma = a;
		mb = b;
	}
	// The absolute number of b is greater than that of a
	else {
		// Swap
		ma = b;
		mb = a;
	}

	ftrans(ma, &sa, &ea, &fa);
	ftrans(mb, &sb, &eb, &fb);

	// ma and mb are infinite or not a number
	if (ea == 0xFF && eb == 0xFF) {
		if (fa != 0x800000) return ma;	// ma is not a number
		if (fb != 0x800000) return mb;	// mb is not a number
		if (sa ^ sb) return NaN;		// ma and mb are both infinite, but share different signs
	}
	if (ea == 0xFF) return ma;	// ma is infinite or not a number
	if (eb == 0xFF) return mb;	// mb is infinite or not a number

	// Spare space for rounding
	fa <<= 4;
	fb <<= 4;

	sans = sa;	// The sign of answer is the same as ma
	eans = ea;	// Set the exponent of answer the same as ma
	fb >>= (ea - eb);	// Let mb has the same exponent as ma

	// ma and mb have different signs
	if (sa ^ sb) {
		fans = fa - fb;	// The fraction of answer is fa minus fb
		if (fans == 0) return 0;	// The fraction of answer is 0
		// Shift left
		while (!(fans & 0x8000000)) {
			eans--;
			fans <<= 1;
		}
		if (eans <= 0) return 0;
		fans += 8;	// Rounding
	}
	else {
		fans = fa + fb;	// The fraction of answer is fa add fb
		// Shift right
		while (fans & 0xF0000000) {
			eans++;
			fans >>= 1;
			fans += 8;	// Rounding
		}
		// Overflow
		if (eans >= 0xFF) {
			eans = 0xFF;
			fans = 0;
		}
	}

	return (sans << 31) | (eans << 23) | ((fans >> 4) & 0x7FFFFF);
}

// Subtraction
dwrd fsub(dwrd a, dwrd b) {
	// b is 0
	if (b == 0) return a;
	// Add a and the opposite number of b
	return fadd(a, b ^ 0x80000000);
}

// Multiplication
dwrd fmul(dwrd a, dwrd b) {
	dwrd sa, sb, sans, ea, eb, eans, fa, fb, fans;

	ftrans(a, &sa, &ea, &fa);
	ftrans(b, &sb, &eb, &fb);

	if (ea == 0xFF && fa != 0x800000) return a;	// a is not a number
	if (eb == 0xFF && fb != 0x800000) return b;	// b is not a number
	if ((a == 0) || (b == 0)) return 0;	// a or b is 0
	// a is infinite
	if (ea == 0xFF) {
		dwrd ma;
		if (sa ^ sb) ma = a | 0x80000000;
		else ma = a & 0x7FFFFFFF;
		return ma;
	}
	// b is infinite
	if (eb == 0xFF) {
		dwrd mb;
		if (sa ^ sb) mb = b | 0x80000000;
		else mb = b & 0x7FFFFFFF;
		return mb;
	}

	fa <<= 4;	// Spare space for rounding

	sans = sa ^ sb;			// The sign of answer is sa XOR sb
	eans = ea + eb - 127;	// Set the exponent to be the sum of exponents of a and b

	// Shift multiplication
	fans = 0;
	while (fb) {
		if (fb & 1) fans += fa;
		fb >>= 1;
		if (fb) fans >>= 1;	// Do not shift in the last step
	}

	// Shift right
	while (fans & 0xF0000000) {
		eans++;
		fans >>= 1;
	}
	fans += 8;	// Rounding
	// Shift right
	while (fans & 0xF0000000) {
		eans++;
		fans >>= 1;
	}

	// Overflow
	if (eans >= 0xFF) {
		eans = 0xFF;
		fans = 0;
	}
	if (eans < 0) return 0;

	return (sans << 31) | (eans << 23) | ((fans >> 4) & 0x7FFFFF);
}

// Division
dwrd fdiv(dwrd a, dwrd b) {
	dwrd sa, sb, sans, ea, eb, eans, fa, fb, fans;

	ftrans(a, &sa, &ea, &fa);
	ftrans(b, &sb, &eb, &fb);

	if (ea == 0xFF && fa != 0x800000) return a;	// a is not a number
	if (eb == 0xFF && fb != 0x800000) return b;	// b is not a number
	if (ea == 0xFF && eb == 0xFF) return NaN;	// a and b are both infinite
	if (b == 0) return NaN;	// The divisor is 0
	if (a == 0) return a;	// The dividend is 0
	// a is infinite
	if (ea == 0xFF) {
		dwrd ma;
		if (sa ^ sb) ma = a | 0x80000000;
		else ma = a & 0x7FFFFFFF;
		return ma;
	}
	// b is infinite
	if (eb == 0xFF) return 0;

	sans = sa ^ sb;			// The sign of answer is sa XOR sb
	eans = ea - eb + 127;	// Set the exponent to be the exponent of a minus that of b

	// Shift division
	fans = 0;
	for (int i = 0; i < 28; i++) {
		if (fa > fb) {
			fa -= fb;
			fans++;
		}
		fa <<= 1;
		if (i < 27) fans <<= 1;	// Do not shift in the last step
	}

	// Shift left
	while (!(fans & 0x8000000)) {
		eans--;
		fans <<= 1;
	}
	fans += 8;	// Rounding
	// Shift right
	while (fans & 0xF0000000) {
		eans++;
		fans >>= 1;
	}

	// Overflow
	if (eans >= 0xFF) {
		eans = 0xFF;
		fans = 0;
	}
	if (eans < 0) return 0;

	return (sans << 31) | (eans << 23) | ((fans >> 4) & 0x7FFFFF);
}

// Assign the value of sign, exponent and fraction of the binary number
void ftrans(dwrd a, dwrd* s, dwrd* e, dwrd* f) {
	*s = (a >> 31) & 1;
	*e = (a >> 23) & 0xFF;
	*f = 0x800000 | (a & 0x7FFFFF);
}