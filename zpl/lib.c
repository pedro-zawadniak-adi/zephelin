#include <zephyr/tracing/tracing.h>
#include <zephyr/tracing/tracing_format.h>
#include <zephyr/usb/usb_device.h>

LOG_MODULE_DECLARE(zpl);

#ifdef CONFIG_ZPL_TRACE_FORMAT_PLAINTEXT
void zpl_named_event(const char *name, uint32_t arg0, uint32_t arg1)
{
	TRACING_STRING("%s: %s (%d; %d)\n", __func__, name, arg0, arg1);
}
#endif /* CONFIG_ZPL_TRACE_FORMAT_PLAINTEXT */

int zpl_init(void)
{
#if defined(CONFIG_ZPL_TRACE_BACKEND_USB)
	int ret;

	ret = usb_enable(NULL);
	if (ret) {
		LOG_ERR("USB backend enable failed\n");
		return 1;
	}
#endif /* CONFIG_ZPL_TRACE_BACKEND_USB */

	// Emit event with current thread information,
	// this allows to associate ID with the main thread
	sys_port_trace_k_thread_info(k_current_get());
	return 0;
}
