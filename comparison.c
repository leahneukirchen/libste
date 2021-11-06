#include <errno.h>
#include <string.h>
#include <stdio.h>
#ifdef __GLIBC__
#include <bsd/string.h>
#endif

#include "ste.h"

/* Task: write a function that appends three char* arguments into
   a 1024 byte fixed buffer and return a pointer to it.
   Return NULL if the strings don't fit.  */

/* Annotations of suboptimal behavior:
   (T)  traverses the string to find the end
   (I)  doesn't support incremental string construction
   (L)  overhead strlen
   (Z)  buffer is not NUL-terminated at time of truncation detection
   */

char *
path3_stecpy(char *a, char *b, char *c)
{
	static char buf[1024];
	char *end = buf + sizeof buf;

	char *pos = buf;
	pos = stecpy(pos, end, a);
	pos = stecpy(pos, end, b);
	pos = stecpy(pos, end, c);

	if (pos == end)
		return 0;
	return buf;
}

char *str_ecpy(char *to, char *e, char *from);

char *
path3_strecpy(char *a, char *b, char *c)
{
	static char buf[1024];
	char *end = buf + sizeof buf;

	char *pos = buf;
	pos = str_ecpy(pos, end, a);
	pos = str_ecpy(pos, end, b);
	pos = str_ecpy(pos, end, c);

	if (pos == end - 1)  // almost the same as stecpy but easier to get wrong
		return 0;
	return buf;
}

char *
path3_strncat(char *a, char *b, char *c)
{
	static char buf[1024];
	size_t n = sizeof buf - 1;

	buf[0] = 0;
	if (strlen(a) > n)	// (L)
		return 0;
	strncat(buf, a, n);
	n -= strlen(a);		// (L)
	if (strlen(b) > n)	// (L)
		return 0;
	strncat(buf, b, n);	// (T)
	n -= strlen(b);		// (L)
	if (strlen(c) > n)	// (L)
		return 0;
	strncat(buf, c, n);	// (T)

	return buf;
}

char *
path3_strlcat(char *a, char *b, char *c)
{
	static char buf[1024];

	strlcpy(buf, a, sizeof buf);
	strlcat(buf, b, sizeof buf);   // (T)
	if (strlcat(buf, c, sizeof buf) >= sizeof buf)   // (T)
		return 0;

	return buf;
}

char *
path3_snprintf(char *a, char *b, char *c)
{
	static char buf[1024];

	if (snprintf(buf, sizeof buf, "%s%s%s", a, b, c) >= sizeof buf)   // (I)
		return 0;

	return buf;
}

ssize_t str_scpy(char *dst, const char *src, size_t count);

char *
path3_strscpy(char *a, char *b, char *c)
{
	static char buf[1024];

	ssize_t r;
	size_t l = 0;
	r = str_scpy(buf + l, a, sizeof buf - l);
	if (r < 0)
		return 0;
	l += r;
	r = str_scpy(buf + l, b, sizeof buf - l);
	if (r < 0)
		return 0;
	l += r;
	r = str_scpy(buf + l, c, sizeof buf - l);
	if (r < 0)
		return 0;

	return buf;
}

char *
path3_memcpy(char *a, char *b, char *c)
{
	static char buf[1024];
	size_t s = 0;

	if (strlen(a) >= sizeof buf - s)   // (L)
		return 0;
	memcpy(buf + s, a, strlen(a));
	s += strlen(a);

	if (strlen(b) >= sizeof buf - s)   // (L)
		return 0;
	memcpy(buf + s, b, strlen(b));
	s += strlen(b);

	if (strlen(c) >= sizeof buf - s)   // (L)
		return 0;
	memcpy(buf + s, c, strlen(c));

	return buf;
}

size_t str_copyb(char *s, const char *t, size_t max);

char *
path3_str_copyb(char *a, char *b, char *c)
{
	static char buf[1024];

	size_t n = 0;

	n += str_copyb(buf + n, a, sizeof buf - n);
	if (n == sizeof buf)
		return 0;	// (Z)
	n += str_copyb(buf + n, b, sizeof buf - n);
	if (n == sizeof buf)
		return 0;	// (Z)
	n += str_copyb(buf + n, c, sizeof buf - n);
	if (n == sizeof buf)
		return 0;	// (Z)

	return buf;
}

int
main()
{
	printf("%s\n", path3_stecpy("abc", "def", "ghi"));
	printf("%s\n", path3_strecpy("abc", "def", "ghi"));
	printf("%s\n", path3_strncat("abc", "def", "ghi"));
	printf("%s\n", path3_strlcat("abc", "def", "ghi"));
	printf("%s\n", path3_snprintf("abc", "def", "ghi"));
	printf("%s\n", path3_strscpy("abc", "def", "ghi"));
	printf("%s\n", path3_memcpy("abc", "def", "ghi"));
	printf("%s\n", path3_str_copyb("abc", "def", "ghi"));
}



/* Plan 9 strecpy(3) */
char*
str_ecpy(char *to, char *e, char *from)
{
	if (to >= e)
		return to;

	to = memccpy(to, from, '\0', e - to);
	if (!to) {
		to = e - 1;
		*to = '\0';
	} else {
		to--;
	}

	return to;
}

/* Linux kernel strscpy */
ssize_t
str_scpy(char *dst, const char *src, size_t count)
{
        if (count == 0)
                return -E2BIG;  // no space for trailing null

        char *end = memccpy(dst, src, 0, count);
        if (!end) {
                dst[count] = 0;
                return -E2BIG;
        }

        return end - dst - 1;
}

/* djb-style, but with proper integer widths */
size_t
str_copyb(char *s, const char *t, size_t max)
{
	size_t len = 0;

	while (max-- > 0) {
		if (!(*s = *t)) { return len; } ++s; ++t; ++len;
	}

	return len;
}
