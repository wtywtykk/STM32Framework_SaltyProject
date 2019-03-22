#include "Kernel\Common\KCommon.h"
#include <sys\stat.h>
#include "usbd_cdc_if.h"

int _fstat(int fd, struct stat *pStat)
{
	pStat->st_mode = S_IFCHR;
	return 0;
}

int _write(int fd, char *pBuffer, int size)
{
	return VCP_write(pBuffer, size);
}

int _isatty(int fd)
{
	return 1;
}

int _read(int fd, char *pBuffer, int size)
{
	for (;;)
	{
		int done = VCP_read(pBuffer, size);
		if (done)
			return done;
	}
}
