*** Settings ***
Resource			${KEYWORDS}

*** Test Cases ***
Should Display TFLM Events
	Prepare Machine

	Wait For Line On Uart	zpl_tflm_begin_event:
	Wait For Line On Uart	zpl_tflm_end_event:
