#include <stdarg.h>
#include <stdio.h>

char *
steprn(char *dst, char *end, const char *fmt, ...)
{
	if (dst >= end)
		return end;

	va_list ap;
	va_start(ap, fmt);
	int r = vsnprintf(dst, end - dst, fmt, ap);
	va_end(ap);

	if (r < 0) {
		/* snprintf only fails for silly reasons:
		   truncate what was written, behave as noop.  */
		*dst = 0;
		return dst;
	}

	return r > end - dst ? end : dst + r;
}
