set pagination off

target remote :3333

set $start = &ram_tracing
set $end = (char*)&ram_tracing + sizeof(ram_tracing)

dump binary memory out.bin $start $end

quit
