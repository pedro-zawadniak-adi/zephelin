*** Settings ***
Resource			${KEYWORDS}

*** Test Cases ***
Should Display Memory Usage
	Prepare Machine

	Wait For Line On Uart	Counter: 5
	Wait For Line On Uart	stack: free: 752B, used: 272B
	Wait For Line On Uart	heap free: 164B, used: 28B

	Wait For Line On Uart	Counter: 4
	Wait For Line On Uart	stack: free: 736B, used: 288B
	Wait For Line On Uart	heap free: 132B, used: 56B

	Wait For Line On Uart	Counter: 1
	Wait For Line On Uart	stack: free: 688B, used: 336B
	Wait For Line On Uart	heap free: 36B, used: 140B
