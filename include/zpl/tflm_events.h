#ifndef ZPL_TFLM_EVENTS_H_
#define ZPL_TFLM_EVENTS_H_

#include <zephyr/kernel.h>
#include <stdint.h>

#if defined(CONFIG_ZPL_TRACE_FORMAT_CTF)
/* TFLite Micro events IDs */
#define ZPL_TFLM_BEGIN_EVENT 0xA0
#define ZPL_TFLM_END_EVENT 0xA1

typedef struct __packed {
	uint32_t timestamp;
	uint8_t id;
	uint8_t tag[CONFIG_ZPL_TRACE_CTF_MAX_STR_LEN];
} zpl_tflm_begin_event_t;

typedef struct __packed {
	uint32_t timestamp;
	uint8_t id;
	uint8_t tag[CONFIG_ZPL_TRACE_CTF_MAX_STR_LEN];
} zpl_tflm_end_event_t;
#endif /* defined(CONFIG_ZPL_TRACE_FORMAT_CTF) */

void zpl_emit_tflm_begin_event(uint32_t cycles, const char *tag);

void zpl_emit_tflm_end_event(uint32_t cycles, const char *tag);

#endif /* ZPL_TFLM_EVENTS_H_ */
