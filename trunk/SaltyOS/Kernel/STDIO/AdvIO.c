#include "Kernel\Common\KCommon.h"
#include <stdio.h>

void fsafeflush(FILE *fp)
{
	int ch;
	while ((ch = fgetc(fp)) != EOF && ch != '\n');
}

void safefulsh(void)
{
	fsafeflush(stdin);
}
