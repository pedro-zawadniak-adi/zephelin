*** Variables ***
${COUNTER_HEX}          43 6f 75 6e 74 65 72 3a 20
${ZPL_MEMORY_EVENT}     EE
${ZPL_STACK}            00
${ZPL_HEAP}             01
${ZPL_K_HEAP}           02
${ZPL_MEM_SLAB}         03

*** Settings ***
Resource			${KEYWORDS}

*** Test Cases ***
Should Display Memory Usage
	Execute Command		$elf = ${ELF}
	Execute Command		include ${RESC}
	Create Terminal Tester	${UART}  defaultPauseEmulation=True	binaryMode=True
	Write Char Delay	0.01

# Counter: 5
	Wait For Bytes On Uart  ${COUNTER_HEX} 35
	Wait For Bytes On Uart  ${ZPL_MEMORY_EVENT} ${ZPL_STACK}
	Wait For Bytes On Uart  ${ZPL_MEMORY_EVENT} ${ZPL_HEAP}
	Wait For Bytes On Uart  ${ZPL_MEMORY_EVENT} ${ZPL_K_HEAP}
	Wait For Bytes On Uart  ${ZPL_MEMORY_EVENT} ${ZPL_MEM_SLAB}

# Counter: 4
	Wait For Bytes On Uart  ${COUNTER_HEX} 34
	Wait For Bytes On Uart  ${ZPL_MEMORY_EVENT} ${ZPL_STACK}
	Wait For Bytes On Uart  ${ZPL_MEMORY_EVENT} ${ZPL_HEAP}
	Wait For Bytes On Uart  ${ZPL_MEMORY_EVENT} ${ZPL_K_HEAP}
	Wait For Bytes On Uart  ${ZPL_MEMORY_EVENT} ${ZPL_MEM_SLAB}

# Counter: 1
	Wait For Bytes On Uart  ${COUNTER_HEX} 31
	Wait For Bytes On Uart  ${ZPL_MEMORY_EVENT} ${ZPL_STACK}
	Wait For Bytes On Uart  ${ZPL_MEMORY_EVENT} ${ZPL_HEAP}
	Wait For Bytes On Uart  ${ZPL_MEMORY_EVENT} ${ZPL_K_HEAP}
	Wait For Bytes On Uart  ${ZPL_MEMORY_EVENT} ${ZPL_MEM_SLAB}
