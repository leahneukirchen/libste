#include <stdio.h>
#include <string.h>

#include "ste.h"

static int status;

void
is(char *desc, int ok)
{
	if (!ok)
		status = 1;
	printf("%s - %s\n", ok ? "ok" : "not ok", desc);
}

int
main()
{
	printf("1..39\n");

	printf("# stecpy\n");

	char buf[16];
	char *end = buf + sizeof buf;
	char buf2[32] = "stringxyzxyzxyzxyzxyz";
	char *pos, *prevpos;

	pos = buf;
	pos = stecpy(pos, end, "abc");
	is("1x3 = 3", strlen(buf) == 3);
	pos = stecpy(pos, end, "def");
	is("2x3 = 6", strlen(buf) == 6);
	pos = stecpy(pos, end, "ghi");
	is("3x3 = 9", strlen(buf) == 9);
	pos = stecpy(pos, end, "jkl");
	is("4x3 = 12", strlen(buf) == 12);
	pos = stecpy(pos, end, "mno");
	is("5x3 = 15", strlen(buf) == 15);
	pos = stecpy(pos, end, "full");
	is("buffer is full", strlen(buf) == 15);
	is("return value is end", pos == end);
	pos = stecpy(pos, end, "fuller");
	is("buffer doesn't get fuller", strlen(buf) == 15);
	is("return value is end", pos == end);

	pos = buf;
	pos = stecpy(pos, end, "abcdefghijklmnopq");
	is("truncation", strlen(buf) == 15);
	is("return value is end", pos == end);

	pos = buf;
	pos = stecpy(pos, end, "xyz");
	pos = stecpy(prevpos=pos, end, "");
	is("empty append works", strlen(buf) == 3);
	is("return value is unchanged", pos == prevpos);


	printf("# steprn\n");

	pos = buf;
	pos = steprn(pos, end, "%d", 123);
	is("1x3 = 3", strlen(buf) == 3);
	pos = steprn(pos, end, "%d", 456);
	is("2x3 = 6", strlen(buf) == 6);
	pos = steprn(pos, end, "%d", 789);
	is("3x3 = 9", strlen(buf) == 9);
	pos = steprn(pos, end, "%03d", 007);
	is("4x3 = 12", strlen(buf) == 12);
	pos = steprn(pos, end, "%d", -42);
	is("5x3 = 15", strlen(buf) == 15);
	pos = steprn(pos, end, "%d", 7890);
	is("buffer is full", strlen(buf) == 15);
	is("return value is end", pos == end);
	pos = steprn(pos, end, "%d", 67890);
	is("buffer doesn't get fuller", strlen(buf) == 15);
	is("return value is end", pos == end);

	pos = buf;
	pos = steprn(pos, end, "%s", "abcdefghijklmnopq");
	is("truncation", strlen(buf) == 15);
	is("return value is end", pos == end);

	pos = buf;
	pos = steprn(pos, end, "%s%s", "x", "yz");
	pos = steprn(prevpos=pos, end, "");
	is("empty append works", strlen(buf) == 3);
	is("return value is unchanged", pos == prevpos);


	printf("# stecpe\n");

	pos = buf;
	pos = stecpe(pos, end, buf2, buf2 + 6);
	is("1x6 = 6", strlen(buf) == 6);
	pos = stecpe(pos, end, buf2, buf2 + 6);
	is("2x6 = 12", strlen(buf) == 12);
	pos = stecpe(pos, end, buf2, buf2 + 6);
	is("buffer is full", strlen(buf) == 15);
	is("return value is end", pos == end);

	pos = buf;
	pos = steprn(pos, end, buf2, buf2 + sizeof buf2);
	is("truncation", strlen(buf) == 15);
	is("return value is end", pos == end);

	pos = buf;
	pos = stecpe(pos, end, buf2, buf2 + 3);
	pos = stecpe(prevpos=pos, end, buf2, buf2);
	is("empty append works", strlen(buf) == 3);
	is("return value is unchanged", pos == prevpos);


	printf("# stechr\n");
	char *x = stechr(buf2, buf2 + sizeof buf2, 'x');
	is("x found", *x == 'x');
	is("x is at buf2[6]", x == buf2 + 6);
	char *w = stechr(buf2, buf2 + sizeof buf2, 'w');
	is("w not found", *w == 0);
	is("returned end of string instead", w == buf2 + strlen(buf2));
	char *y = stechr(buf2, buf2 + 6, 'y');
	is("y not found in first 6 chars", y == buf2 + 6);


	return status;
}
