*** Settings ***
Resource			${KEYWORDS}

*** Test Cases ***
Should Display DIE Temp
	Execute Command		$elf = ${ELF}
	Execute Command		include ${RESC}
	Create Terminal Tester	${UART}  defaultPauseEmulation=True	binaryMode=True
	Write Char Delay	0.01

	# Event ID, 0, NaN
	Wait For Bytes On Uart	C1 00 00 00 00 00 00 C0 7F
