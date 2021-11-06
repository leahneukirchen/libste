#include <string.h>

char *
stecpy(char *dst, char *end, const char *src)
{
        if (dst >= end)
                return dst;

	dst = memccpy(dst, src, '\0', end - dst);
	if (!dst) {
		end[-1] = 0;
		return end;
	}

	return dst - 1;
}
