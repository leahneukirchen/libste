#include <stddef.h>
#include <string.h>

char *
stecpe(char *dst, const char *end, const char *src, const char *srcend)
{
        if (dst >= end)
                return dst;

	ptrdiff_t l = end - dst - 1;
	size_t t = 1;
	if (srcend - src < l) {
		l = srcend - src;
		t = 0;
	}

	memcpy(dst, src, l);
	dst[l] = 0;

	return dst + l + t;
}
