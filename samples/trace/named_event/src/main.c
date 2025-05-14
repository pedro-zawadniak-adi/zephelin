#include <zpl/lib.h>

int main(void)
{
	zpl_init();

	for (int i = 0; i < 10; i++) {
		sys_trace_named_event("counter_value", i, 0);
	}

	return 0;
}
