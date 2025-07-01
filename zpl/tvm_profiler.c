#include <tvm/runtime/crt/profiler.h>
#include <zpl/tvm_events.h>
#include <zpl/tvm_profiler.h>

TVMProfiler tvm_profiler = {
    .begin_event_cb = zpl_tvm_profiler_begin_event,
    .end_event_cb = zpl_tvm_profiler_end_event,
};

static int num_events_ = 0;
static uint8_t op_idx_[CONFIG_ZPL_TVM_PROFILER_MAX_EVENTS];
static uint32_t begin_cycles_[CONFIG_ZPL_TVM_PROFILER_MAX_EVENTS];
static uint32_t end_cycles_[CONFIG_ZPL_TVM_PROFILER_MAX_EVENTS];
static const char *tags_[CONFIG_ZPL_TVM_PROFILER_MAX_EVENTS];

int zpl_tvm_profiler_begin_event(int op_idx, const char* tag)
{
	if (num_events_ >= CONFIG_ZPL_TVM_PROFILER_MAX_EVENTS) {
		return -1;
	}
	int event_handle = num_events_;

	begin_cycles_[event_handle] = k_cycle_get_32();
	op_idx_[event_handle] = op_idx;
	tags_[event_handle] = tag;

	++num_events_;

	return event_handle;
}

void zpl_tvm_profiler_end_event(int event_handle)
{
	if (event_handle >= CONFIG_ZPL_TVM_PROFILER_MAX_EVENTS) {
		return;
	}

	end_cycles_[event_handle] = k_cycle_get_32();
}

void zpl_tvm_profiler_dump_events()
{
	for (int i = 0; i < num_events_; ++i) {
		zpl_emit_tvm_enter_event(
			begin_cycles_[i],
			op_idx_[i],
			tags_[i]);
		zpl_emit_tvm_exit_event(
			end_cycles_[i],
			op_idx_[i],
			tags_[i]);
	}

	num_events_ = 0;
}
