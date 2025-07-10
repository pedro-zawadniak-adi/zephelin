*** Settings ***
Resource			${KEYWORDS}
Resource			common_keywords.resource

*** Test Cases ***
Should Display Memory Usage
	Prepare Machine

	Wait For Line On Uart	Counter: 5
	Wait For Memory Event On Uart

	Wait For Line On Uart	Counter: 4
	Wait For Memory Event On Uart

	Wait For Line On Uart	Counter: 3
	Wait For Memory Event On Uart

	Wait For Line On Uart	Counter: 2
	Wait For Memory Event On Uart

	Wait For Line On Uart	Counter: 1
	Wait For Memory Event On Uart

	Wait For Line On Uart	Counter: 0
	Wait For Memory Event On Uart
