*** Variables ***
${CONV_2D}                  43 4F 4E 56 5F 32 44
${CONV_2D_SUBGRAPH_IDX}     00
${CONV_2D_OP_IDX}           00
${ZPL_INFERENCE_ENTER_ID}   D0
${ZPL_INFERENCE_EXIT_ID}    D1
${ZPL_TFLM_BEGIN_EVENT_ID}  A0
${ZPL_TFLM_END_EVENT_ID}    A1
${ZPL_MEMORY_EVENT}         EE
${ZPL_STACK}                00

*** Settings ***
Resource			${KEYWORDS}

*** Test Cases ***
Should Display Full Traces
	Execute Command		$elf = ${ELF}
	Execute Command		include ${RESC}
	Create Terminal Tester	${UART}  defaultPauseEmulation=True	binaryMode=True
	Write Char Delay	0.01

	# Inference events
	Wait For Bytes On Uart	${ZPL_INFERENCE_ENTER_ID}
	Wait For Bytes On Uart	${ZPL_INFERENCE_EXIT_ID}

	# Conv 2D Layer
	Wait For Bytes On Uart	${ZPL_TFLM_BEGIN_EVENT_ID}
	# thread ID
	Wait For Bytes On Uart	${CONV_2D_SUBGRAPH_IDX} ${CONV_2D_OP_IDX} ${CONV_2D}
	Wait For Bytes On Uart	${ZPL_TFLM_END_EVENT_ID}
	# thread ID
	Wait For Bytes On Uart	${CONV_2D_SUBGRAPH_IDX} ${CONV_2D_OP_IDX} ${CONV_2D}

	# Memory Events
	Wait For Bytes On Uart  ${ZPL_MEMORY_EVENT} ${ZPL_STACK}
