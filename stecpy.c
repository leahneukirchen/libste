char *
stecpy(char *dst, char *end, const char *src)
{
	if (dst >= end)
		return dst;

	while (dst < end && (*dst = *src))
		src++, dst++;

	if (dst == end)
		dst[-1] = 0;

	return dst;
}
