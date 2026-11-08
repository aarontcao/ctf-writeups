set pagination off
set confirm off
attach 890502
set $psg = 0x7f69df174120
printf "ATTACHED. ps.id now=%#lx\n", *(unsigned long*)($psg+0x10)
watch *(unsigned long*)($psg+0x10)
commands
  printf ">> ps.id := %#lx  pc=%#lx\n", *(unsigned long*)($psg+0x10), $pc
  bt 4
  printf "----\n"
  continue
end
continue
