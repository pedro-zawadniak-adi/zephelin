#include <zephyr/ztest.h>

#include <zpl/lib.h>

ZTEST(zpl, test_library_init)
{
	zassert_equal(0, zpl_init(),
			"zpl_init() failed to initialize");
}

ZTEST_SUITE(zpl, NULL, NULL, NULL, NULL, NULL);
