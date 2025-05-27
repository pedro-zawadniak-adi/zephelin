#include <zephyr/kernel.h>
#include <zephyr/sys/sys_heap.h>
#include <zephyr/logging/log.h>

LOG_MODULE_DECLARE(memory_profiler);

void zpl_profile_stack(const struct k_thread *thread, void *user_data)
{
	size_t unused;
	int err = k_thread_stack_space_get(thread, &unused);

	if (err) {
		LOG_ERR("Error getting thread stack space\n");
		return;
	}

	/* TODO: Temporary solution, to be replaced with custom events in CTF */
	printk("stack: free: %dB, used: %dB\n", unused, thread->stack_info.size - unused);
}

void zpl_profile_heap(void)
{
	struct sys_heap **ha;
	size_t i;
	struct sys_memory_stats stats;

	for (i = 0; i < sys_heap_array_get(&ha); i++) {
		sys_heap_runtime_stats_get(ha[i], &stats);
		/* TODO: Temporary solution, to be replaced with custom events in CTF */
		printk("heap free: %dB, used: %dB\n", stats.free_bytes, stats.allocated_bytes);
	}
}

void zpl_profile_memory(void)
{
	while (true) {
		k_thread_foreach(zpl_profile_stack, NULL);
		zpl_profile_heap();
		k_msleep(CONFIG_ZPL_MEMORY_PROFILING_INTERVAL);
	}
}

K_THREAD_DEFINE(zpl_memory_profiling,
				CONFIG_ZPL_MEMORY_PROFILING_THREAD_STACK_SIZE,
				zpl_profile_memory, NULL, NULL, NULL,
				CONFIG_ZPL_MEMORY_PROFILING_THREAD_PRIORITY,
				0, CONFIG_ZPL_MEMORY_PROFILING_THREAD_DELAY);
