set pagination off
set confirm off
set $n = 0
attach 894377
break php_session_decode
commands
  silent
  set $d=(char*)$rdi
  printf "[decode #%d] len=%ld bytes: ", $n, *(long*)($d+0x10)
  x/24bx ($d+0x18)
  set $n = $n + 1
  if $n >= 10
    detach
    quit
  end
  continue
end
break php_session_destroy
commands
  silent
  printf "[DESTROY]\n"
  bt 5
  continue
end
continue
