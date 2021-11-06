#include <stddef.h>

char *
stecpy(char *dst, char *end, const char *src)
{
        if (dst >= end)
                return dst;

	size_t n = end - dst;
	while (n && (*dst = *src))
		n--, src++, dst++;

	if (dst == end)
		dst[-1] = 0;

	return dst;
}
