#include <zpl/lib.h>
#include <zpl/tflm_events.h>
#include <zephyr/kernel.h>
#include <stdio.h>

int main(void)
{
	const char *tflm_op_tag = "TFLM_OP";

	zpl_init();

	zpl_emit_tflm_begin_event(k_cycle_get_32(), tflm_op_tag);
	zpl_emit_tflm_end_event(k_cycle_get_32(), tflm_op_tag);

	return 0;
}
