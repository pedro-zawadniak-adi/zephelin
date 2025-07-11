*** Variables ***
${ZPL_INFERENCE_ENTER_ID}   D0
${ZPL_INFERENCE_EXIT_ID}    D1
${ZPL_MEMORY_EVENT}         EE
${ZPL_STACK}                00

*** Settings ***
Resource			${KEYWORDS}

*** Test Cases ***
Should Display Minimal Traces
	Execute Command		$elf = ${ELF}
	Execute Command		include ${RESC}
	Create Terminal Tester	${UART}  defaultPauseEmulation=True	binaryMode=True
	Write Char Delay	0.01

	# Inference events
	Wait For Bytes On Uart	${ZPL_INFERENCE_ENTER_ID}
	Wait For Bytes On Uart	${ZPL_INFERENCE_EXIT_ID}

	# Memory Events
	Wait For Bytes On Uart  ${ZPL_MEMORY_EVENT} ${ZPL_STACK}
