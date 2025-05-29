*** Settings ***
Resource			${KEYWORDS}

*** Test Cases ***
Should Display Memory Usage
	Prepare Machine

	Wait For Line On Uart	Counter: 5
	Wait For Line On Uart	zpl_memory_event stack 496B 528B
	Wait For Line On Uart	zpl_memory_event heap 28B 164B

	Wait For Line On Uart	Counter: 4
	Wait For Line On Uart	zpl_memory_event stack 512B 512B
	Wait For Line On Uart	zpl_memory_event heap 56B 132B

	Wait For Line On Uart	Counter: 1
	Wait For Line On Uart	zpl_memory_event stack 560B 464B
	Wait For Line On Uart	zpl_memory_event heap 140B 36B
