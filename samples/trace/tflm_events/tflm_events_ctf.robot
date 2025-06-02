*** Settings ***
Resource			${KEYWORDS}

*** Test Cases ***
Should Display Function Name
	Execute Command		$elf = ${ELF}
	Execute Command		include ${RESC}
	Create Terminal Tester	${UART}  defaultPauseEmulation=True	binaryMode=True
	Write Char Delay	0.01

	# "TFLM_OP" in ASCII
	Wait For Bytes On Uart	54 46 4C 4D 5F 4F 50
	Wait For Bytes On Uart	54 46 4C 4D 5F 4F 50
