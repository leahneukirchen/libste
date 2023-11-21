#include "ste.h"

char *
steprl(char *dst, char *end, long n)
{
	if (dst >= end)
		return end;

	char buf[24];
	char *bufend = buf + sizeof buf;
	char *s = bufend;

	unsigned long u = n < 0 ? -n : n;

	do {
		*--s = '0' + (u % 10);
		u /= 10;
	} while (u);

	if (n < 0)
		*--s = '-';

	return stecpe(dst, end, s, bufend);
}
