** Settings ***
Resource			${KEYWORDS}

*** Test Cases ***
Should Display TFLM OP Name
	Execute Command		$elf = ${ELF}
	Execute Command		include ${RESC}
	Create Terminal Tester	${UART}  defaultPauseEmulation=True	binaryMode=True
	Write Char Delay	0.01

	# "CONV_2D" in ASCII
	Wait For Bytes On Uart	43 4F 4E 56 5F 32 44
	Wait For Bytes On Uart	43 4F 4E 56 5F 32 44
