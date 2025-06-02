*** Settings ***
Resource			${KEYWORDS}

*** Test Cases ***
Should Display Function Name
	Prepare Machine

	Wait For Line On Uart	zpl_tflm_begin_event: TFLM_OP
	Wait For Line On Uart	zpl_tflm_end_event: TFLM_OP
