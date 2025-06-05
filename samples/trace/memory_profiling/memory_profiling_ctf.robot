*** Settings ***
Resource			${KEYWORDS}

*** Test Cases ***
Should Display Memory Usage
	Execute Command		$elf = ${ELF}
	Execute Command		include ${RESC}
	Create Terminal Tester	${UART}  defaultPauseEmulation=True	binaryMode=True
	Write Char Delay	0.01

# Counter: 5
	Wait For Bytes On Uart	43 6f 75 6e 74 65 72 3a 20 35
# stack
	Wait For Bytes On Uart	73 74 61 63 6b 00 00 00 00 00
# heap
	Wait For Bytes On Uart	68 65 61 70 00 00 00 00 00 00

# Counter: 4
	Wait For Bytes On Uart	43 6f 75 6e 74 65 72 3a 20 34
# stack
	Wait For Bytes On Uart	73 74 61 63 6b 00 00 00 00 00
# heap
	Wait For Bytes On Uart	68 65 61 70 00 00 00 00 00 00

# Counter: 1
	Wait For Bytes On Uart	43 6f 75 6e 74 65 72 3a 20 31
# stack
	Wait For Bytes On Uart	73 74 61 63 6b 00 00 00 00 00
# heap
	Wait For Bytes On Uart	68 65 61 70 00 00 00 00 00 00
