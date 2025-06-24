*** Variables ***
${MEMORY_ADDRESS}       0[xX][0-9a-fA-F]+

*** Keywords ***
Wait For Memory Event On Uart
	Wait For Line On Uart	zpl_memory_event stack \\(${MEMORY_ADDRESS}\\) \\d+B \\d+B  treatAsRegex=true
	Wait For Line On Uart	zpl_memory_event heap \\(${MEMORY_ADDRESS}\\) \\d+B \\d+B   treatAsRegex=true
	Wait For Line On Uart	zpl_memory_event k_heap \\(${MEMORY_ADDRESS}\\) \\d+B \\d+B   treatAsRegex=true
	Wait For Line On Uart	zpl_memory_event mem_slab \\(${MEMORY_ADDRESS}\\) \\d+B \\d+B   treatAsRegex=true

Change Memory Usage Config
	[Arguments]		${state}
	Write Line To Uart  mem_usage_trace ${state}  waitForEcho=false

*** Settings ***
Resource			${KEYWORDS}

*** Test Cases ***
Should Display Memory Usage
	Prepare Machine

	Wait For Line On Uart  Counter: 5
	Wait For Line On Uart  Counter: 4
	Change Memory Usage Config  enable
	Wait For Line On Uart  Counter: 3
	Wait For Memory Event On Uart
	Wait For Line On Uart  Counter: 2
	Change Memory Usage Config  disable
	Wait For Line On Uart  Counter: 1
	Wait For Line On Uart  Counter: 0
	Run Keyword And Expect Error  *Terminal tester failed*  Wait For Line On Uart  zpl_memory_event  timeout=2
	Change Memory Usage Config  disable
	Change Memory Usage Config  disable
	Run Keyword And Expect Error  *Terminal tester failed*  Wait For Line On Uart  zpl_memory_event  timeout=2
	Change Memory Usage Config  enable
	Wait For Memory Event On Uart
