#ifndef __FLOAT_H__
#define __FLOAT_H__

#define P_INF 0x7F800000	// Default positive infinite number
#define N_INF 0xFF800000	// Default negative infinite number
#define NaN 0x7F800001		// Default not a number

typedef unsigned int dwrd;	// Binary number

char* ftoa(dwrd a);			// Transform binary number into string
dwrd atof(char* s);			// Transform string into binary number
dwrd fadd(dwrd a, dwrd b);	// Addition
dwrd fsub(dwrd a, dwrd b);	// Subtraction
dwrd fmul(dwrd a, dwrd b);	// Multiplication
dwrd fdiv(dwrd a, dwrd b);	// Division

#endif // !__FLOAT_H__