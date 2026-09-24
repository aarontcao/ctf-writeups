// ---- _init @ 00101000

void _init(void)

{
  if (PTR___gmon_start___00103fe0 != (undefined *)0x0) {
    (*(code *)PTR___gmon_start___00103fe0)();
  }
  return;
}


// ---- FUN_00101020 @ 00101020

void FUN_00101020(void)

{
  (*(code *)PTR_00103f78)();
  return;
}


// ---- setvbuf @ 001010d0

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int setvbuf(FILE *__stream,char *__buf,int __modes,size_t __n)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_setvbuf_00103fe8)();
  return iVar1;
}


// ---- __cxa_finalize @ 001010e0

void __cxa_finalize(void)

{
  (*(code *)PTR___cxa_finalize_00103ff8)();
  return;
}


// ---- seccomp_init @ 001010f0

void seccomp_init(void)

{
  (*(code *)PTR_seccomp_init_00103f80)();
  return;
}


// ---- seccomp_rule_add @ 00101100

void seccomp_rule_add(void)

{
  (*(code *)PTR_seccomp_rule_add_00103f88)();
  return;
}


// ---- seccomp_load @ 00101110

void seccomp_load(void)

{
  (*(code *)PTR_seccomp_load_00103f90)();
  return;
}


// ---- __stack_chk_fail @ 00101120

void __stack_chk_fail(void)

{
  (*(code *)PTR___stack_chk_fail_00103f98)();
  return;
}


// ---- printf @ 00101130

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int printf(char *__format,...)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_printf_00103fa0)();
  return iVar1;
}


// ---- seccomp_release @ 00101140

void seccomp_release(void)

{
  (*(code *)PTR_seccomp_release_00103fa8)();
  return;
}


// ---- fgets @ 00101150

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * fgets(char *__s,int __n,FILE *__stream)

{
  char *pcVar1;
  
  pcVar1 = (char *)(*(code *)PTR_fgets_00103fb0)();
  return pcVar1;
}


// ---- __isoc99_scanf @ 00101160

void __isoc99_scanf(void)

{
  (*(code *)PTR___isoc99_scanf_00103fb8)();
  return;
}


// ---- exit @ 00101170

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void exit(int __status)

{
  (*(code *)PTR_exit_00103fc0)();
  return;
}


// ---- fork @ 00101180

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

__pid_t fork(void)

{
  __pid_t _Var1;
  
  _Var1 = (*(code *)PTR_fork_00103fc8)();
  return _Var1;
}


// ---- _start @ 00101190

void processEntry _start(undefined8 param_1,undefined8 param_2)

{
  undefined1 auStack_8 [8];
  
  (*(code *)PTR___libc_start_main_00103fd0)(main,param_2,&stack0x00000008,0,0,param_1,auStack_8);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}


// ---- deregister_tm_clones @ 001011c0

/* WARNING: Removing unreachable block (ram,0x001011d3) */
/* WARNING: Removing unreachable block (ram,0x001011df) */

void deregister_tm_clones(void)

{
  return;
}


// ---- register_tm_clones @ 001011f0

/* WARNING: Removing unreachable block (ram,0x00101214) */
/* WARNING: Removing unreachable block (ram,0x00101220) */

void register_tm_clones(void)

{
  return;
}


// ---- __do_global_dtors_aux @ 00101230

void __do_global_dtors_aux(void)

{
  if (completed_0 == '\0') {
    if (PTR___cxa_finalize_00103ff8 != (undefined *)0x0) {
      __cxa_finalize(__dso_handle);
    }
    deregister_tm_clones();
    completed_0 = 1;
    return;
  }
  return;
}


// ---- frame_dummy @ 00101270

void frame_dummy(void)

{
  register_tm_clones();
  return;
}


// ---- init @ 00101279

int init(EVP_PKEY_CTX *ctx)

{
  int iVar1;
  
  setvbuf(stdin,(char *)0x0,2,0);
  setvbuf(stdout,(char *)0x0,2,0);
  iVar1 = setvbuf(stderr,(char *)0x0,2,0);
  return iVar1;
}


// ---- setup_seccomp @ 001012de

void setup_seccomp(void)

{
  int iVar1;
  long lVar2;
  
  lVar2 = seccomp_init(0x80000000);
  if (lVar2 == 0) {
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  seccomp_rule_add(lVar2,0x7fff0000,2,0);
  seccomp_rule_add(lVar2,0x7fff0000,0x101,0);
  seccomp_rule_add(lVar2,0x7fff0000,0,0);
  seccomp_rule_add(lVar2,0x7fff0000,1,0);
  seccomp_rule_add(lVar2,0x7fff0000,0xe,0);
  seccomp_rule_add(lVar2,0x7fff0000,0xf,0);
  seccomp_rule_add(lVar2,0x7fff0000,0x3c,0);
  seccomp_rule_add(lVar2,0x7fff0000,0xe7,0);
  seccomp_rule_add(lVar2,0x7fff0000,0x142,0);
  iVar1 = seccomp_load(lVar2);
  if (iVar1 < 0) {
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  seccomp_release(lVar2);
  return;
}


// ---- main @ 00101452

undefined8 main(EVP_PKEY_CTX *param_1)

{
  long in_FS_OFFSET;
  char *local_20;
  int local_18 [2];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  init(param_1);
  setup_seccomp();
  printf("%p\n",PTR_setvbuf_00103fe8);
  __isoc99_scanf("%zu %zu ",&local_20,local_18);
  fgets(local_20,local_18[0],stdin);
  fork();
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return 0;
}


// ---- _fini @ 001014f8

void _fini(void)

{
  return;
}


// ---- seccomp_init @ 00107000

/* WARNING: Control flow encountered bad instruction data */

void seccomp_init(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- __libc_start_main@GLIBC_2.34 @ 00107008

/* WARNING: Control flow encountered bad instruction data */

void __libc_start_main_GLIBC_2_34(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- _ITM_deregisterTMCloneTable @ 00107010

/* WARNING: Control flow encountered bad instruction data */

void _ITM_deregisterTMCloneTable(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- seccomp_rule_add @ 00107018

/* WARNING: Control flow encountered bad instruction data */

void seccomp_rule_add(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- seccomp_load @ 00107020

/* WARNING: Control flow encountered bad instruction data */

void seccomp_load(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- __stack_chk_fail@GLIBC_2.4 @ 00107028

/* WARNING: Control flow encountered bad instruction data */

void __stack_chk_fail_GLIBC_2_4(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- printf@GLIBC_2.2.5 @ 00107030

/* WARNING: Control flow encountered bad instruction data */

void printf_GLIBC_2_2_5(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- seccomp_release @ 00107038

/* WARNING: Control flow encountered bad instruction data */

void seccomp_release(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- fgets@GLIBC_2.2.5 @ 00107040

/* WARNING: Control flow encountered bad instruction data */

void fgets_GLIBC_2_2_5(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- __gmon_start__ @ 00107048

/* WARNING: Control flow encountered bad instruction data */

void __gmon_start__(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- setvbuf@GLIBC_2.2.5 @ 00107050

/* WARNING: Control flow encountered bad instruction data */

void setvbuf_GLIBC_2_2_5(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- __isoc99_scanf@GLIBC_2.7 @ 00107058

/* WARNING: Control flow encountered bad instruction data */

void __isoc99_scanf_GLIBC_2_7(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- exit@GLIBC_2.2.5 @ 00107060

/* WARNING: Control flow encountered bad instruction data */

void exit_GLIBC_2_2_5(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- _ITM_registerTMCloneTable @ 00107068

/* WARNING: Control flow encountered bad instruction data */

void _ITM_registerTMCloneTable(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- __cxa_finalize@GLIBC_2.2.5 @ 00107070

/* WARNING: Control flow encountered bad instruction data */

void __cxa_finalize_GLIBC_2_2_5(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- fork@GLIBC_2.2.5 @ 00107078

/* WARNING: Control flow encountered bad instruction data */

void fork_GLIBC_2_2_5(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- __libc_start_main @ 00107080

/* WARNING: Control flow encountered bad instruction data */

void __libc_start_main(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- __stack_chk_fail @ 00107088

/* WARNING: Control flow encountered bad instruction data */

void __stack_chk_fail(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- printf @ 00107090

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int printf(char *__format,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- fgets @ 00107098

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * fgets(char *__s,int __n,FILE *__stream)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- __isoc99_scanf @ 001070a0

/* WARNING: Control flow encountered bad instruction data */

void __isoc99_scanf(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- exit @ 001070a8

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void exit(int __status)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- fork @ 001070b0

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

__pid_t fork(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- setvbuf @ 001070b8

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int setvbuf(FILE *__stream,char *__buf,int __modes,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- __cxa_finalize @ 001070c0

/* WARNING: Control flow encountered bad instruction data */

void __cxa_finalize(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


