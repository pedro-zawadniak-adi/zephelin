*** Settings ***
Resource			${KEYWORDS}

*** Test Cases ***
Should Display Memory Usage
	Execute Command		$elf = ${ELF}
	Execute Command		include ${RESC}
	Create Terminal Tester	${UART}  defaultPauseEmulation=True	binaryMode=True
	Write Char Delay	0.01

	Wait For Bytes On Uart	43 6f 75 6e 74 65 72 3a 20 35
# stack 496 528
	Wait For Bytes On Uart	73 74 61 63 6b 00 00 00 00 00 f0 01 00 00 10 02 00 00
# heap 28 164
	Wait For Bytes On Uart	68 65 61 70 00 00 00 00 00 00 1c 00 00 00 a4 00 00 00

	Wait For Bytes On Uart	43 6f 75 6e 74 65 72 3a 20 34
# stack 512 512
	Wait For Bytes On Uart	73 74 61 63 6b 00 00 00 00 00 00 02 00 00 00 02 00 00
# heap 56 132
	Wait For Bytes On Uart	68 65 61 70 00 00 00 00 00 00 38 00 00 00 84 00 00 00

	Wait For Bytes On Uart	43 6f 75 6e 74 65 72 3a 20 31
# stack 560 464
	Wait For Bytes On Uart	73 74 61 63 6b 00 00 00 00 00 30 02 00 00 d0 01 00 00
# heap 140 36
	Wait For Bytes On Uart	68 65 61 70 00 00 00 00 00 00 8c 00 00 00 24 00 00 00
