char *
stechr(const char *src, const char *end, int c)
{
	while (src < end && *src && *(unsigned char *)src != (unsigned char)c)
		src++;

	return (char *)src;
}
