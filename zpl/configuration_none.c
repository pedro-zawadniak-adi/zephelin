#include <zephyr/kernel.h>
#include <zpl/configuration.h>

void zpl_wait_for_usage_trace_enabled(void)
{
	if (!IS_ENABLED(CONFIG_ZPL_MEMORY_USAGE_TRACE)) {
		k_sleep(K_FOREVER);
	}
}
