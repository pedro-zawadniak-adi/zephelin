#include <zephyr/fff.h>
#include <zephyr/ztest.h>
#include <zephyr/usb/usbd.h>

#include <zpl/lib.h>
#include <zpl/configuration.h>

#ifdef CONFIG_ZPL_TRACE_BACKEND_USB
DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC(struct usbd_context *, zpl_usbd_init_device);
FAKE_VALUE_FUNC(int, usbd_enable, struct usbd_context *);
#endif

ZTEST(zpl, test_library_init_succeed)
{
#ifdef CONFIG_ZPL_TRACE_BACKEND_USB
	struct usbd_context ctx;

	RESET_FAKE(zpl_usbd_init_device);
	RESET_FAKE(usbd_enable);
	zpl_usbd_init_device_fake.return_val = &ctx;
	usbd_enable_fake.return_val = 0;
#endif /* CONFIG_ZPL_TRACE_BACKEND_USB */

	zassert_equal(0, zpl_init(),
			"zpl_init() failed to initialize");
}

#ifdef CONFIG_ZPL_TRACE_BACKEND_USB
ZTEST(zpl, test_library_init_fail)
{
	struct usbd_context ctx;

	RESET_FAKE(zpl_usbd_init_device);
	RESET_FAKE(usbd_enable);
	zpl_usbd_init_device_fake.return_val = &ctx;
	usbd_enable_fake.return_val = -EINVAL;

	zassert_equal(1, zpl_init(),
			"zpl_init() was expected to fail");

	RESET_FAKE(zpl_usbd_init_device);
	RESET_FAKE(usbd_enable);
	zpl_usbd_init_device_fake.return_val = NULL;
	usbd_enable_fake.return_val = 0;

	zassert_equal(1, zpl_init(),
			"zpl_init() was expected to fail");
}
#endif /* CONFIG_ZPL_TRACE_BACKEND_USB */

ZTEST(zpl, test_runtime_check_conf)
{
	zassert_equal(IS_ENABLED(CONFIG_ZPL_MEMORY_USAGE_TRACE), ZPL_CHECK_IF_CONF(mem_usage_trace), "ZPL_CHECK_IF_CONF(mem_usage_trace) returned an incorrect value");
}

ZTEST_SUITE(zpl, NULL, NULL, NULL, NULL, NULL);
