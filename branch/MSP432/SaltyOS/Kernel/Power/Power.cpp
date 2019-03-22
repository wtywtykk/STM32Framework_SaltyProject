#include "Kernel\Common\KCommon.h"
#include "HAL\PowerManagement.h"

void KernelPowerDown(void)
{
	//TODO: end all tasks and power down(actually restart)
	HardwareRestart();
}
