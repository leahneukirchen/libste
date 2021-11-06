#include <string.h>

char *
stecpy(char *dst, char *end, const char *src)
{
        if (dst >= end)
                return dst;

	size_t n = strnlen(src, end - dst);

	if (n == end - dst) {
		memcpy(dst, src, n - 1);
		end[-1] = 0;
		return end;
	}

	return memcpy(dst, src, n + 1) + n;
}
