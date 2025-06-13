*** Settings ***
Resource			${KEYWORDS}

*** Test Cases ***
Should Display OP Name
	Execute Command		$elf = ${ELF}
	Execute Command		include ${RESC}
	Create Terminal Tester	${UART}  defaultPauseEmulation=True	binaryMode=True
	Write Char Delay	0.01

	# "tvmgen_default_fused_nn_conv2d_add_nn_relu" in ASCII
	Wait For Bytes On Uart	74 76 6D 67 65 6E 5F 64 65 66 61 75 6C 74 5F 66 75 73 65 64 5F 6E 6E 5F 63 6F 6E 76 32 64 5F 61 64 64 5F 6E 6E 5F 72 65 6C 75
	Wait For Bytes On Uart	74 76 6D 67 65 6E 5F 64 65 66 61 75 6C 74 5F 66 75 73 65 64 5F 6E 6E 5F 63 6F 6E 76 32 64 5F 61 64 64 5F 6E 6E 5F 72 65 6C 75
