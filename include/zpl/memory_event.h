#ifndef ZEPHYR_PROFILING_LIB_MEMORY_EVENT_H_
#define ZEPHYR_PROFILING_LIB_MEMORY_EVENT_H_

#include <stdint.h>

#define ZPL_MEMORY_EVENT 0xEE

typedef struct __packed {
	uint32_t timestamp;
	uint8_t id;
	uint8_t memory_region[10];
	uintptr_t memory_addr;
	uint32_t used;
	uint32_t unused;
} zpl_memory_event_t;

void zpl_emit_memory_event(const char *memory_region, uintptr_t memory_addr, uint32_t used_memory, uint32_t unused_memory);

#endif /* ZEPHYR_PROFILING_LIB_MEMORY_EVENT_H_ */
