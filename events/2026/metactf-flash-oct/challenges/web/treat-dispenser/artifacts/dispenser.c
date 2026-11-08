// ---- _DT_INIT @ 00101000

void _DT_INIT(void)

{
  if (PTR___gmon_start___00103fe8 != (undefined *)0x0) {
    (*(code *)PTR___gmon_start___00103fe8)();
  }
  return;
}


// ---- FUN_00101020 @ 00101020

void FUN_00101020(void)

{
  (*(code *)PTR_00103f80)();
  return;
}


// ---- __cxa_finalize @ 001010d0

void __cxa_finalize(void)

{
  (*(code *)PTR___cxa_finalize_00103ff8)();
  return;
}


// ---- getenv @ 001010e0

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * getenv(char *__name)

{
  char *pcVar1;
  
  pcVar1 = (char *)(*(code *)PTR_getenv_00103f88)();
  return pcVar1;
}


// ---- __errno_location @ 001010f0

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int * __errno_location(void)

{
  int *piVar1;
  
  piVar1 = (int *)(*(code *)PTR___errno_location_00103f90)();
  return piVar1;
}


// ---- puts @ 00101100

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int puts(char *__s)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_puts_00103f98)();
  return iVar1;
}


// ---- __stack_chk_fail @ 00101110

void __stack_chk_fail(void)

{
  (*(code *)PTR___stack_chk_fail_00103fa0)();
  return;
}


// ---- fgets @ 00101120

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * fgets(char *__s,int __n,FILE *__stream)

{
  char *pcVar1;
  
  pcVar1 = (char *)(*(code *)PTR_fgets_00103fa8)();
  return pcVar1;
}


// ---- strtol @ 00101130

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

long strtol(char *__nptr,char **__endptr,int __base)

{
  long lVar1;
  
  lVar1 = (*(code *)PTR_strtol_00103fb0)();
  return lVar1;
}


// ---- __printf_chk @ 00101140

void __printf_chk(void)

{
  (*(code *)PTR___printf_chk_00103fb8)();
  return;
}


// ---- setvbuf @ 00101150

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int setvbuf(FILE *__stream,char *__buf,int __modes,size_t __n)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_setvbuf_00103fc0)();
  return iVar1;
}


// ---- fwrite @ 00101160

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

size_t fwrite(void *__ptr,size_t __size,size_t __n,FILE *__s)

{
  size_t sVar1;
  
  sVar1 = (*(code *)PTR_fwrite_00103fc8)();
  return sVar1;
}


// ---- __fprintf_chk @ 00101170

void __fprintf_chk(void)

{
  (*(code *)PTR___fprintf_chk_00103fd0)();
  return;
}


// ---- FUN_00101180 @ 00101180

undefined8 FUN_00101180(void)

{
  char *pcVar1;
  int *piVar2;
  long lVar3;
  long in_FS_OFFSET;
  char *local_70;
  char local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  setvbuf(stdout,(char *)0x0,2,0);
  pcVar1 = getenv("DISPENSER_SVC_LOG");
  if (pcVar1 != (char *)0x0) {
    __fprintf_chk(stderr,1,&DAT_0010221c,
                  "svc 09/14: slot 3 coil jams on gummy worms, reseat before restock");
    __fprintf_chk(stderr,1,&DAT_0010221c,
                  "svc 10/02: restock panel moved off the keypad label, KEY=6767");
    __fprintf_chk(stderr,1,&DAT_0010221c,
                  "svc 10/20: coin mech disabled for Halloween night, treats are free");
  }
  puts("         \\\\");
  puts("    .-\'```^```\'-.");
  puts("   /   /\\ __ /\\  \\");
  puts("   |   ^^ \\/ ^^  |");
  puts("   \\   \\_.__._/  /");
  puts("    `\'-.......-\'`");
  puts("");
  puts("  THE NEIGHBORHOOD TREAT DISPENSER");
  puts("  Trick or treat! A little something for everyone.");
  puts("  (The good candy stays locked away.)");
  puts("");
LAB_001012d0:
  do {
    puts("  1) Candy corn");
    puts("  2) Gummy worms");
    puts("  3) Peanut butter cup");
    puts("  4) Caramel apple pop");
    puts("  0) Walk away");
    fwrite(&DAT_001022e7,1,2,stdout);
    pcVar1 = fgets(local_68,0x20,stdin);
    if (pcVar1 == (char *)0x0) {
LAB_0010138b:
      if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
        return 0;
      }
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail();
    }
    piVar2 = __errno_location();
    *piVar2 = 0;
    lVar3 = strtol(local_68,&local_70,10);
    if ((local_70 != local_68) && (((*local_70 == '\n' || (*local_70 == '\0')) && (*piVar2 == 0))))
    {
      if (lVar3 < 5) {
        if (0 < lVar3) {
          __printf_chk(1,"*clunk* %s drops into the tray.\n\n",(&__DT_FINI_ARRAY)[lVar3]);
          goto LAB_001012d0;
        }
        if (lVar3 == 0) {
          puts("Happy Halloween!");
          goto LAB_0010138b;
        }
      }
      else if (lVar3 == 0x1a6f) {
        FUN_00101510(0x1a6f);
        goto LAB_001012d0;
      }
      puts("That slot is empty.\n");
      goto LAB_001012d0;
    }
    puts("The keypad only takes numbers.\n");
  } while( true );
}


// ---- entry @ 00101420

void processEntry entry(undefined8 param_1,undefined8 param_2)

{
  undefined1 auStack_8 [8];
  
  (*(code *)PTR___libc_start_main_00103fd8)
            (FUN_00101180,param_2,&stack0x00000008,0,0,param_1,auStack_8);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}


// ---- FUN_00101450 @ 00101450

/* WARNING: Removing unreachable block (ram,0x00101463) */
/* WARNING: Removing unreachable block (ram,0x0010146f) */

void FUN_00101450(void)

{
  return;
}


// ---- FUN_00101480 @ 00101480

/* WARNING: Removing unreachable block (ram,0x001014a4) */
/* WARNING: Removing unreachable block (ram,0x001014b0) */

void FUN_00101480(void)

{
  return;
}


// ---- _FINI_0 @ 001014c0

void _FINI_0(void)

{
  if (DAT_00104048 == '\0') {
    if (PTR___cxa_finalize_00103ff8 != (undefined *)0x0) {
      __cxa_finalize(PTR_LOOP_00104008);
    }
    FUN_00101450();
    DAT_00104048 = 1;
    return;
  }
  return;
}


// ---- _INIT_0 @ 00101500

void _INIT_0(void)

{
  FUN_00101480();
  return;
}


// ---- FUN_00101510 @ 00101510

void FUN_00101510(int param_1)

{
  long lVar1;
  byte bVar2;
  uint uVar3;
  long in_FS_OFFSET;
  byte local_38 [34];
  undefined1 local_16;
  long local_10;
  
  bVar2 = 0x10;
  uVar3 = param_1 * -0x61c8864f ^ 0x5eed5eed;
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  lVar1 = 0;
  while( true ) {
    uVar3 = uVar3 * 0x41c64e6d + 0x3039;
    local_38[lVar1] = bVar2 ^ (byte)(uVar3 >> 0x10);
    if (lVar1 + 1 == 0x22) break;
    bVar2 = (&DAT_00102381)[lVar1];
    lVar1 = lVar1 + 1;
  }
  local_16 = 0;
  puts("*CLUNK* The locked compartment swings open and a full-size bar drops out.");
  __printf_chk(1,"The wrapper reads: %s\n\n",local_38);
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


// ---- _DT_FINI @ 001015b0

void _DT_FINI(void)

{
  return;
}


// ---- getenv @ 00105000

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * getenv(char *__name)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- __libc_start_main @ 00105008

/* WARNING: Control flow encountered bad instruction data */

void __libc_start_main(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- __errno_location @ 00105010

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int * __errno_location(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- _ITM_deregisterTMCloneTable @ 00105018

/* WARNING: Control flow encountered bad instruction data */

void _ITM_deregisterTMCloneTable(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- puts @ 00105020

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int puts(char *__s)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- __stack_chk_fail @ 00105028

/* WARNING: Control flow encountered bad instruction data */

void __stack_chk_fail(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- fgets @ 00105030

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * fgets(char *__s,int __n,FILE *__stream)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- __gmon_start__ @ 00105038

/* WARNING: Control flow encountered bad instruction data */

void __gmon_start__(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- strtol @ 00105040

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

long strtol(char *__nptr,char **__endptr,int __base)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- __printf_chk @ 00105048

/* WARNING: Control flow encountered bad instruction data */

void __printf_chk(void)

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
  halt_baddata();
}


// ---- fwrite @ 00105058

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

size_t fwrite(void *__ptr,size_t __size,size_t __n,FILE *__s)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- __fprintf_chk @ 00105060

/* WARNING: Control flow encountered bad instruction data */

void __fprintf_chk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- _ITM_registerTMCloneTable @ 00105068

/* WARNING: Control flow encountered bad instruction data */

void _ITM_registerTMCloneTable(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ---- __cxa_finalize @ 00105070

/* WARNING: Control flow encountered bad instruction data */

void __cxa_finalize(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


