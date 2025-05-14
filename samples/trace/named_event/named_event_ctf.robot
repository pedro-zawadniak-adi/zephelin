*** Settings ***
Resource			${KEYWORDS}

*** Test Cases ***
Should Display Function Name
	Execute Command		$elf = ${ELF}
	Execute Command		include ${RESC}
	Create Terminal Tester	${UART}  defaultPauseEmulation=True	binaryMode=True
	Write Char Delay	0.01

	# "counter_value" in ASCII
	Wait For Bytes On Uart	63 6F 75 6E 74 65 72 5F 76 61 6C 75 65
