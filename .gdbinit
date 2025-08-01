define target remote
target extended-remote $arg0
symbol-file ps1HeroMain.elf
monitor reset shellhalt
load ps1HeroMain.elf
end
