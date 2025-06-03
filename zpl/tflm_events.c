#include <zpl/tflm_events.h>

#include <zephyr/kernel.h>
#include <zephyr/tracing/tracing_format.h>

void zpl_emit_tflm_begin_event(
	uint32_t cycles, uint16_t subgraph_idx, uint16_t op_idx, const char *tag,
	uint32_t arena_used_bytes, uint32_t arena_tail_usage)
{
#if defined(CONFIG_ZPL_TRACE_FORMAT_CTF)
	zpl_tflm_begin_event_t zpl_tflm_begin_event = {
		.timestamp = k_cyc_to_ns_floor64(cycles),
		.id = ZPL_TFLM_BEGIN_EVENT,
		.subgraph_idx = subgraph_idx,
		.op_idx = op_idx,
		.arena_used_bytes = arena_used_bytes,
		.arena_tail_usage = arena_tail_usage
	};
	snprintf(&(zpl_tflm_begin_event.tag[0]), CONFIG_ZPL_TRACE_CTF_MAX_STR_LEN, "%s", tag);

	tracing_format_raw_data(
		(uint8_t *)&zpl_tflm_begin_event, sizeof(zpl_tflm_begin_event_t)
	);
#elif defined(CONFIG_ZPL_TRACE_FORMAT_PLAINTEXT)
	TRACING_STRING(
		"zpl_tflm_begin_event: subgraph_idx=%d op_idx=%d tag=%s "
		"arena_used_bytes=%d arena_tail_usage=%d\n",
		subgraph_idx, op_idx, tag, arena_used_bytes, arena_tail_usage);
#endif /* CONFIG_ZPL_TRACE_FORMAT_* */
}

void zpl_emit_tflm_end_event(
	uint32_t cycles, uint16_t subgraph_idx, uint16_t op_idx, const char *tag,
	uint32_t arena_used_bytes, uint32_t arena_tail_usage)
{
#if defined(CONFIG_ZPL_TRACE_FORMAT_CTF)
	zpl_tflm_end_event_t zpl_tflm_end_event = {
		.timestamp = k_cyc_to_ns_floor64(cycles),
		.id = ZPL_TFLM_END_EVENT,
		.subgraph_idx = subgraph_idx,
		.op_idx = op_idx,
		.arena_used_bytes = arena_used_bytes,
		.arena_tail_usage = arena_tail_usage
	};
	snprintf(&(zpl_tflm_end_event.tag[0]), CONFIG_ZPL_TRACE_CTF_MAX_STR_LEN, "%s", tag);

	tracing_format_raw_data(
		(uint8_t *)&zpl_tflm_end_event, sizeof(zpl_tflm_end_event_t)
	);
#elif defined(CONFIG_ZPL_TRACE_FORMAT_PLAINTEXT)
	TRACING_STRING(
		"zpl_tflm_end_event: subgraph_idx=%d op_idx=%d tag=%s "
		"arena_used_bytes=%d arena_tail_usage=%d\n",
		subgraph_idx, op_idx, tag, arena_used_bytes, arena_tail_usage);
#endif /* CONFIG_ZPL_TRACE_FORMAT_* */
}
