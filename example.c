#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ste.h"

/* example of libste usage: iterate over $PATH and append argv[1],
   print the entries that fit into PATH_MAX. */

int
main(int argc, char *argv[])
{
	const char *path = getenv("PATH");
	if (!path)
	    path = "";

	const char *program = argc > 1 ? argv[1] : "xyzzy";

	const char *pathend = path + strlen(path);

	char buf[PATH_MAX];
	char *bufend = buf + sizeof buf;

	while (1) {
		char *pos = buf;

		char *colon = stechr(path, pathend, ':');
		if (path == colon)  /* empty entry */
			pos = stecpy(buf, bufend, ".");
		else
			pos = stecpe(buf, bufend, path, colon);

		pos = steprn(pos, bufend, "/%s", program);

		if (pos < bufend) {  /* no trunaction */
			printf("%s\n", buf);
		}

		if (colon == pathend)
			break;
		path = colon + 1;
	}
}
