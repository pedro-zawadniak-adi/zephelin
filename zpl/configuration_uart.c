#include <zpl/configuration.h>
#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>

K_MUTEX_DEFINE(conf_lock);
K_CONDVAR_DEFINE(conf_condvar);

volatile bool memory_usage_trace_enabled = false;


void zpl_wait_for_usage_trace_enabled(void)
{
	k_mutex_lock(&conf_lock, K_FOREVER);
	if (!IS_ENABLED(CONFIG_ZPL_MEMORY_USAGE_TRACE) && !memory_usage_trace_enabled) {
		k_condvar_wait(&conf_condvar, &conf_lock, K_FOREVER);
	}
	k_mutex_unlock(&conf_lock);
}

void zpl_memory_usage_trace_change_state(bool state)
{
	k_mutex_lock(&conf_lock, K_FOREVER);
	memory_usage_trace_enabled = state;
	if (memory_usage_trace_enabled) {
		k_condvar_signal(&conf_condvar);
	}
	k_mutex_unlock(&conf_lock);
}

static int memory_usage_trace_enable(const struct shell *sh, size_t argc, char **argv)
{
	zpl_memory_usage_trace_change_state(true);
	return 0;
}

static int memory_usage_trace_disable(const struct shell *sh, size_t argc, char **argv)
{
	zpl_memory_usage_trace_change_state(false);
	return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_memory_usage_trace,
        SHELL_CMD(enable, NULL, "Memory usage trace - enable", memory_usage_trace_enable),
        SHELL_CMD(disable, NULL, "Memory usage trace - enable", memory_usage_trace_disable),
        SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(mem_usage_trace, &sub_memory_usage_trace, "Memory usage trace", NULL);
