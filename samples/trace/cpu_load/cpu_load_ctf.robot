*** Settings ***
Resource			${KEYWORDS}

*** Test Cases ***
Should Display CPU Load
	Execute Command		$elf = ${ELF}
	Execute Command		include ${RESC}
	Create Terminal Tester	${UART}  defaultPauseEmulation=True	binaryMode=True
	Write Char Delay	0.01

	# Event ID and value 1000
	Wait For Bytes On Uart	C0 E8 03
