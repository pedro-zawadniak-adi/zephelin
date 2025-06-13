#include <zephyr/fff.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/ztest.h>

#include <zpl/lib.h>

#ifdef CONFIG_ZPL_TRACE_BACKEND_USB
DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC(int, usb_enable, usb_dc_status_callback);
#endif

ZTEST(zpl, test_library_init_succeed)
{
#ifdef CONFIG_ZPL_TRACE_BACKEND_USB
	RESET_FAKE(usb_enable);
	usb_enable_fake.return_val = 0;
#endif /* CONFIG_ZPL_TRACE_BACKEND_USB */

	zassert_equal(0, zpl_init(),
			"zpl_init() failed to initialize");
}

#ifdef CONFIG_ZPL_TRACE_BACKEND_USB
ZTEST(zpl, test_library_init_fail)
{
	RESET_FAKE(usb_enable);
	usb_enable_fake.return_val = -EINVAL;

	zassert_equal(1, zpl_init(),
			"zpl_init() was expected to fail");
}
#endif /* CONFIG_ZPL_TRACE_BACKEND_USB */

ZTEST_SUITE(zpl, NULL, NULL, NULL, NULL, NULL);
