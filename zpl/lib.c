#include <zephyr/tracing/tracing.h>
#include <zephyr/tracing/tracing_format.h>
#include <zephyr/usb/usb_device.h>

#ifdef CONFIG_TRACING_TEST
void zpl_named_event(const char *name, uint32_t arg0, uint32_t arg1)
{
	TRACING_STRING("%s: %s (%d; %d)\n", __func__, name, arg0, arg1);
}
#endif /* CONFIG_TRACING_TEST */

int zpl_init(void)
{

#if defined(CONFIG_USB_DEVICE_STACK)
	int ret;

	ret = usb_enable(NULL);
	if (ret) {
		printk("usb backend enable failed");
		return 1;
	}
#endif /* CONFIG_USB_DEVICE_STACK */

	return 0;
}
