#include "ste.h"

char *
steprl(char *dst, char *end, long n)
{
	if (dst >= end)
		return end;

	char buf[24];
	char *bufend = buf + sizeof buf;
	char *s = bufend;

	int neg = n < 0;
	if (neg)
		n = -n;

	do {
		*--s = '0' + (n % 10);
		n /= 10;
	} while (n > 0);

	if (neg)
		*--s = '-';

	return stecpe(dst, end, s, bufend);
}
