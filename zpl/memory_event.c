#include <zephyr/kernel.h>
#include <zephyr/tracing/tracing_format.h>

#include <zpl/memory_event.h>

void zpl_emit_memory_event(const char *memory_region, uint32_t used_memory, uint32_t unused_memory)
{
#if defined(CONFIG_ZPL_TRACE_FORMAT_CTF)
	uint32_t cycles = k_cycle_get_32();

	zpl_memory_event_t memory_event = {
		.timestamp = k_cyc_to_ns_floor64(cycles),
		.id = ZPL_MEMORY_EVENT,
		.used = used_memory,
		.unused = unused_memory,
	};
	memset(&(memory_event.memory_region[0]), 0, 10);
	snprintf(&(memory_event.memory_region[0]), 10, "%s", memory_region);

	tracing_format_raw_data(
		(uint8_t *)&memory_event, sizeof(zpl_memory_event_t)
	);
#elif defined(CONFIG_ZPL_TRACE_FORMAT_PLAINTEXT)
	TRACING_STRING(
		 "zpl_memory_event %s %uB %uB\n", memory_region, used_memory, unused_memory
	);
#endif /* CONFIG_ZPL_TRACE_FORMAT_* */
}
