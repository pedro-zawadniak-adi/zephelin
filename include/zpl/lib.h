#ifndef ZPL_LIB_H_
#define ZPL_LIB_H_

#include <stdint.h>
#include <zephyr/tracing/tracing.h>

int zpl_init(void);

#ifdef CONFIG_TRACING_TEST
#undef sys_trace_named_event
#define sys_trace_named_event(name, arg0, arg1) zpl_named_event(name, arg0, arg1)
void zpl_named_event(const char *name, uint32_t arg0, uint32_t arg1);
#endif /* CONFIG_TRACING_TEST */

#endif /* ZPL_LIB_H_ */
