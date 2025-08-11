define target remote
target extended-remote $arg0
symbol-file hello.elf
monitor reset shellhalt
load hello.elf
end
