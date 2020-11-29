#include<stdlib.h>
#include<string.h>
#include "integer.h"

word negative(word i);
word getsign(word i);
word bepositive(word i);

// Transform string into binary number
word atom(char* ch) {
	word i = 0, p = 1, num = 0, flag = 0, size = 0;
	char* n = ch;
	if (*n == '-') {
		flag = 1;
		size = i = 1;
	}
	while (n[size] != '\0') {
		size = madd(size, 1);
		p = mmul(p, 10);
	}
	p = mdiv(p, 10);

	while (i < size) {
		num = num + mmul((n[i] - '0'), p);
		p = mdiv(p, 10);
		i = madd(i, 1);
	}

	if (flag) num = negative(num);

	return num;
}

// Transform binary number into string
char* mtoa(word num) {
	word n = num, i = 13, flag = getsign(num);
	char* str = (char*)malloc(sizeof(char) * 15);
	memset(str, '0', sizeof(char) * 15);
	str[14] = '\0';

	if (n == 0) {
		str[0] = '0';
		str[1] = '\0';
		return str;
	}

	// Negative number
	if (flag) {
		n = bepositive(num);
		while (n > 0) {
			str[i] = '0' + mmod(n, 10);
			n = mdiv(n, 10);
			i = msub(i, 1);
		}
		str[i] = '-';
	}
	// Positive number
	else {
		while (n > 0) {
			str[i] = '0' + mmod(n, 10);
			n = mdiv(n, 10);
			i = msub(i, 1);
		}
		i = madd(i, 1);
	}

	return &str[i];
}

word negative(word i)
{
	return madd(~i, 1);
}

word getsign(word i)
{
	return (i >> 31);
}
// Transform one number into positive one
// Be aware that for -2147483648, it would carry out 
word bepositive(word i)
{
	if (i >> 31)
		return negative(i);
	else
		return i;
}

word madd(word m, word n) {
	word s, c;
	while (n != 0)
	{
		s = m ^ n;
		c = (m & n) << 1;
		m = s;
		n = c;
	}
	return m;
}

word msub(word m, word n) {
	word c = negative(n);
	return madd(m, c);
}

word mmul(word m, word n) {
	word flag = 1;
	if (getsign(m) == getsign(n))
		flag = 0;

	m = bepositive(m);
	n = bepositive(n);
	word ans = 0;

	while (n){
		if (n & 1)
			ans = madd(ans, m);
		m = (m << 1);
		n = (n >> 1); 
	}

	if (flag) ans = negative(ans);
	return ans;
}

word mdiv(word m, word n) {
	word flag = 1;
	if (getsign(m) == getsign(n))
		flag = 0;

	word x = bepositive(m);
	word y = bepositive(n);

	word ans = 0;
	word i = 31;
	while (i >= 0)
	{
		if ((x >> i) >= y){
			ans = madd(ans, (1 << i));
			x = msub(x, (y << i));
		}
		if (i == 0) break;
		i = msub(i, 1);
	}
	if (flag) ans = negative(ans);
	return ans;
}

word mmod(word m, word n) {
	word flag = 1;
	if (getsign(m) == getsign(n))
		flag = 0;

	word x = bepositive(m);
	word y = bepositive(n);

	word ans = 0;
	word i = 31;
	while (i >= 0)
	{
		if ((x >> i) >= y){
			ans = madd(ans, (1 << i));
			x = msub(x, (y << i));
		}
		if (i == 0) break;
		i = msub(i, 1);
	}
	if (flag) x = negative(x);
	return x;
}