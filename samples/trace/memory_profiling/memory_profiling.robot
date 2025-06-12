*** Settings ***
Resource			${KEYWORDS}

*** Test Cases ***
Should Display Memory Usage
	Prepare Machine

	Wait For Line On Uart	Counter: 5
	Wait For Line On Uart	zpl_memory_event stack \\d+B \\d+B  treatAsRegex=true
	Wait For Line On Uart	zpl_memory_event heap \\d+B \\d+B   treatAsRegex=true
	Wait For Line On Uart	zpl_memory_event k_heap \\d+B \\d+B   treatAsRegex=true
	Wait For Line On Uart	zpl_memory_event mem_slab \\d+B \\d+B   treatAsRegex=true

	Wait For Line On Uart	Counter: 4
	Wait For Line On Uart	zpl_memory_event stack \\d+B \\d+B  treatAsRegex=true
	Wait For Line On Uart	zpl_memory_event heap \\d+B \\d+B   treatAsRegex=true
	Wait For Line On Uart	zpl_memory_event k_heap \\d+B \\d+B   treatAsRegex=true
	Wait For Line On Uart	zpl_memory_event mem_slab \\d+B \\d+B   treatAsRegex=true

	Wait For Line On Uart	Counter: 1
	Wait For Line On Uart	zpl_memory_event stack \\d+B \\d+B  treatAsRegex=true
	Wait For Line On Uart	zpl_memory_event heap \\d+B \\d+B   treatAsRegex=true
	Wait For Line On Uart	zpl_memory_event k_heap \\d+B \\d+B   treatAsRegex=true
	Wait For Line On Uart	zpl_memory_event mem_slab \\d+B \\d+B   treatAsRegex=true
