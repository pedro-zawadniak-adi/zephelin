#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>


void recursive_function(int counter)
{
	int *heap_variable = k_malloc(sizeof(int) * 5);

	printk("Counter: %d\n", counter);
	if (counter > 0) {
		k_msleep(200);
		recursive_function(counter - 1);
	}
	k_free(heap_variable);
}

int main(void)
{
	recursive_function(5);
	return 0;
}
