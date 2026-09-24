// ---- _init @ 00101000

int _init(EVP_PKEY_CTX *ctx)

{
  int iVar1;
  
  iVar1 = 0;
  if (PTR___gmon_start___00103fe8 != (undefined *)0x0) {
    iVar1 = (*(code *)PTR___gmon_start___00103fe8)();
  }
  return iVar1;
}


// ---- FUN_00101020 @ 00101020

void FUN_00101020(void)

{
  (*(code *)PTR_00103f78)();
  return;
}


// ---- __cxa_finalize @ 001010e0

void __cxa_finalize(void)

{
  (*(code *)PTR___cxa_finalize_00103ff8)();
  return;
}


// ---- puts @ 001010f0

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int puts(char *__s)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_puts_00103f80)();
  return iVar1;
}


// ---- __stack_chk_fail @ 00101100

void __stack_chk_fail(void)

{
  (*(code *)PTR___stack_chk_fail_00103f88)();
  return;
}


// ---- dladdr @ 00101110

void dladdr(void)

{
  (*(code *)PTR_dladdr_00103f90)();
  return;
}


// ---- printf @ 00101120

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int printf(char *__format,...)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_printf_00103f98)();
  return iVar1;
}


// ---- fputs @ 00101130

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int fputs(char *__s,FILE *__stream)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_fputs_00103fa0)();
  return iVar1;
}


// ---- fgets @ 00101140

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * fgets(char *__s,int __n,FILE *__stream)

{
  char *pcVar1;
  
  pcVar1 = (char *)(*(code *)PTR_fgets_00103fa8)();
  return pcVar1;
}


// ---- strtoull @ 00101150

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ulonglong strtoull(char *__nptr,char **__endptr,int __base)

{
  ulonglong uVar1;
  
  uVar1 = (*(code *)PTR_strtoull_00103fb0)();
  return uVar1;
}


// ---- setvbuf @ 00101160

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int setvbuf(FILE *__stream,char *__buf,int __modes,size_t __n)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_setvbuf_00103fb8)();
  return iVar1;
}


// ---- dlsym @ 00101170

void dlsym(void)

{
  (*(code *)PTR_dlsym_00103fc0)();
  return;
}


// ---- strtoul @ 00101180

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ulong strtoul(char *__nptr,char **__endptr,int __base)

{
  ulong uVar1;
  
  uVar1 = (*(code *)PTR_strtoul_00103fc8)();
  return uVar1;
}


// ---- exit @ 00101190

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void exit(int __status)

{
  (*(code *)PTR_exit_00103fd0)();
  return;
}


// ---- _start @ 001011a0

void processEntry _start(undefined8 param_1,undefined8 param_2)

{
  undefined1 auStack_8 [8];
  
  (*(code *)PTR___libc_start_main_00103fd8)(main,param_2,&stack0x00000008,0,0,param_1,auStack_8);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}


// ---- deregister_tm_clones @ 001011d0

/* WARNING: Removing unreachable block (ram,0x001011e3) */
/* WARNING: Removing unreachable block (ram,0x001011ef) */

void deregister_tm_clones(void)

{
  return;
}


// ---- register_tm_clones @ 00101200

/* WARNING: Removing unreachable block (ram,0x00101224) */
/* WARNING: Removing unreachable block (ram,0x00101230) */

void register_tm_clones(void)

{
  return;
}


// ---- __do_global_dtors_aux @ 00101240

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


// ---- frame_dummy @ 00101280

void frame_dummy(void)

{
  register_tm_clones();
  return;
}


// ---- setup @ 00101289

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void setup(void)

{
  setvbuf(stdin,(char *)0x0,2,0);
  setvbuf(stdout,(char *)0x0,2,0);
  setvbuf(stderr,(char *)0x0,2,0);
  return;
}


// ---- read_u64_line @ 001012ee

uint64_t read_u64_line(char *prompt)

{
  long lVar1;
  char *pcVar2;
  ulonglong uVar3;
  long in_FS_OFFSET;
  char *prompt_local;
  char buf [128];
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (prompt != (char *)0x0) {
    fputs(prompt,stdout);
  }
  pcVar2 = fgets(buf,0x80,stdin);
  if (pcVar2 == (char *)0x0) {
    puts("EOF");
                    /* WARNING: Subroutine does not return */
    exit(0);
  }
  uVar3 = strtoull(buf,(char **)0x0,0);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar3;
}


// ---- leak_libc_base @ 0010139e

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void leak_libc_base(void)

{
  long lVar1;
  int iVar2;
  long lVar3;
  long in_FS_OFFSET;
  void *real_puts;
  Dl_info info;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  lVar3 = dlsym(0xffffffffffffffff,&DAT_0010200c);
  if (lVar3 == 0) {
    puts("dlsym failed");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  iVar2 = dladdr(lVar3,&info);
  if ((iVar2 != 0) && (info.dli_fbase != (void *)0x0)) {
    printf("libc base: %p\n",info.dli_fbase);
    printf("puts@libc: %p\n",lVar3);
    if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail();
    }
    return;
  }
  puts("dladdr failed");
                    /* WARNING: Subroutine does not return */
  exit(1);
}


// ---- main @ 00101479

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int main(void)

{
  long lVar1;
  char *pcVar2;
  byte *pbVar3;
  ulong uVar4;
  long in_FS_OFFSET;
  uint bit;
  uintptr_t addr;
  char buf [128];
  char final_buf [256];
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  setup();
  leak_libc_base();
  puts(&DAT_00102050);
  puts("first addr");
  pcVar2 = fgets(buf,0x80,stdin);
  if (pcVar2 != (char *)0x0) {
    pbVar3 = (byte *)strtoull(buf,(char **)0x0,0);
    puts("first bit");
    pcVar2 = fgets(buf,0x80,stdin);
    if ((pcVar2 != (char *)0x0) && (uVar4 = strtoul(buf,(char **)0x0,0), (uint)uVar4 < 8)) {
      *pbVar3 = *pbVar3 ^ (byte)(1 << ((byte)uVar4 & 0x1f));
      puts("What was your name? I didnt get it");
      fgets(final_buf,0x100,stdin);
      puts("See you around traveler");
    }
  }
  if (lVar1 == *(long *)(in_FS_OFFSET + 0x28)) {
    return 0;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


// ---- _fini @ 001015f0

void _fini(void)

{
  return;
}


// ---- __libc_start_main @ 00105000

/* WARNING: Control flow encountered bad instruction data */

void __libc_start_main(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* __libc_start_main@GLIBC_2.34 */
  halt_baddata();
}


// ---- _ITM_deregisterTMCloneTable @ 00105008

/* WARNING: Control flow encountered bad instruction data */

void _ITM_deregisterTMCloneTable(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- puts @ 00105010

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int puts(char *__s)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* puts@GLIBC_2.2.5 */
  halt_baddata();
}


// ---- __stack_chk_fail @ 00105018

/* WARNING: Control flow encountered bad instruction data */

void __stack_chk_fail(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* __stack_chk_fail@GLIBC_2.4 */
  halt_baddata();
}


// ---- dladdr @ 00105020

/* WARNING: Control flow encountered bad instruction data */

void dladdr(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* dladdr@GLIBC_2.34 */
  halt_baddata();
}


// ---- printf @ 00105028

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int printf(char *__format,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* printf@GLIBC_2.2.5 */
  halt_baddata();
}


// ---- fputs @ 00105030

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int fputs(char *__s,FILE *__stream)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* fputs@GLIBC_2.2.5 */
  halt_baddata();
}


// ---- fgets @ 00105038

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * fgets(char *__s,int __n,FILE *__stream)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* fgets@GLIBC_2.2.5 */
  halt_baddata();
}


// ---- strtoull @ 00105040

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ulonglong strtoull(char *__nptr,char **__endptr,int __base)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* strtoull@GLIBC_2.2.5 */
  halt_baddata();
}


// ---- __gmon_start__ @ 00105048

/* WARNING: Control flow encountered bad instruction data */

void __gmon_start__(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- setvbuf @ 00105050

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int setvbuf(FILE *__stream,char *__buf,int __modes,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* setvbuf@GLIBC_2.2.5 */
  halt_baddata();
}


// ---- dlsym @ 00105058

/* WARNING: Control flow encountered bad instruction data */

void dlsym(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* dlsym@GLIBC_2.34 */
  halt_baddata();
}


// ---- strtoul @ 00105060

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ulong strtoul(char *__nptr,char **__endptr,int __base)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* strtoul@GLIBC_2.2.5 */
  halt_baddata();
}


// ---- exit @ 00105068

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void exit(int __status)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* exit@GLIBC_2.2.5 */
  halt_baddata();
}


// ---- _ITM_registerTMCloneTable @ 00105070

/* WARNING: Control flow encountered bad instruction data */

void _ITM_registerTMCloneTable(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- __cxa_finalize @ 00105078

/* WARNING: Control flow encountered bad instruction data */

void __cxa_finalize(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* __cxa_finalize@GLIBC_2.2.5 */
  halt_baddata();
}


