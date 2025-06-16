*** Variables ***
${MEMORY_ADDRESS}       0[xX][0-9a-fA-F]+

*** Settings ***
Resource			${KEYWORDS}

*** Test Cases ***
Should Display Memory Usage
	Prepare Machine

	Wait For Line On Uart	Counter: 5
	Wait For Line On Uart	zpl_memory_event stack \\(${MEMORY_ADDRESS}\\) \\d+B \\d+B  treatAsRegex=true
	Wait For Line On Uart	zpl_memory_event heap \\(${MEMORY_ADDRESS}\\) \\d+B \\d+B   treatAsRegex=true
	Wait For Line On Uart	zpl_memory_event k_heap \\(${MEMORY_ADDRESS}\\) \\d+B \\d+B   treatAsRegex=true
	Wait For Line On Uart	zpl_memory_event mem_slab \\(${MEMORY_ADDRESS}\\) \\d+B \\d+B   treatAsRegex=true

	Wait For Line On Uart	Counter: 4
	Wait For Line On Uart	zpl_memory_event stack \\(${MEMORY_ADDRESS}\\) \\d+B \\d+B  treatAsRegex=true
	Wait For Line On Uart	zpl_memory_event heap \\(${MEMORY_ADDRESS}\\) \\d+B \\d+B   treatAsRegex=true
	Wait For Line On Uart	zpl_memory_event k_heap \\(${MEMORY_ADDRESS}\\) \\d+B \\d+B   treatAsRegex=true
	Wait For Line On Uart	zpl_memory_event mem_slab \\(${MEMORY_ADDRESS}\\) \\d+B \\d+B   treatAsRegex=true

	Wait For Line On Uart	Counter: 1
	Wait For Line On Uart	zpl_memory_event stack \\(${MEMORY_ADDRESS}\\) \\d+B \\d+B  treatAsRegex=true
	Wait For Line On Uart	zpl_memory_event heap \\(${MEMORY_ADDRESS}\\) \\d+B \\d+B   treatAsRegex=true
	Wait For Line On Uart	zpl_memory_event k_heap \\(${MEMORY_ADDRESS}\\) \\d+B \\d+B   treatAsRegex=true
	Wait For Line On Uart	zpl_memory_event mem_slab \\(${MEMORY_ADDRESS}\\) \\d+B \\d+B   treatAsRegex=true
