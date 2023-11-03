char *
steccpy(char *dst, char *end, const char *src, int c)
{
	if (dst >= end)
		return dst;

	while (dst < end && *src != c && (*dst = *src))
		src++, dst++;

	if (dst == end)
		dst[-1] = 0;
	else if (*src == c)
		dst[0] = 0;

	return dst;
}
