// FAILED: entry
// FAILED: FUN_011be7e0
// ---- FUN_011c4270 @ 011c4270

/* WARNING: Removing unreachable block (ram,0x011c4713) */
/* WARNING: Removing unreachable block (ram,0x011c4730) */
/* WARNING: Removing unreachable block (ram,0x011c45fd) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_011c4270(long *param_1)

{
  undefined4 uVar1;
  long *plVar2;
  ulong *puVar3;
  ulong uVar4;
  ulong *extraout_RDX;
  long lVar5;
  ulong uVar6;
  uint *puVar7;
  long lVar8;
  ulong uVar9;
  uint *puVar10;
  ulong in_R9;
  uint uVar11;
  undefined *puVar12;
  uint *puVar13;
  ulong *puVar14;
  long lVar15;
  long *in_FS_OFFSET;
  ulong local_48;
  ulong local_40;
  undefined8 local_38;
  
  lVar5 = *param_1;
  lVar15 = 1;
  DAT_01200008 = param_1 + lVar5 + 2;
  do {
    plVar2 = DAT_01200008;
    lVar15 = lVar15 + -1;
    DAT_01200008 = plVar2 + 1;
  } while (*plVar2 != 0);
  puVar3 = (ulong *)(plVar2 + 2);
  puVar13 = (uint *)0x0;
  uVar6 = 0;
  uVar4 = plVar2[1];
  if (uVar4 != 3) goto LAB_011c42f0;
LAB_011c42e1:
  puVar13 = (uint *)*puVar3;
  do {
    uVar4 = puVar3[1];
    while( true ) {
      puVar3 = puVar3 + 2;
      if (uVar4 == 3) goto LAB_011c42e1;
LAB_011c42f0:
      if (uVar4 != 5) break;
      uVar6 = *puVar3;
      uVar4 = puVar3[1];
    }
  } while (uVar4 != 0);
  DAT_011fe008 = 8;
  DAT_011fe020 = 1;
  if (uVar6 != 0) {
    uVar4 = (ulong)((uint)uVar6 & 7);
    if (uVar6 < 8) {
      puVar7 = (uint *)0x0;
      lVar8 = 0;
      uVar9 = 0;
    }
    else {
      in_R9 = uVar6 & 0xfffffffffffffff8;
      puVar7 = (uint *)0x0;
      lVar8 = 0;
      uVar9 = 0;
      puVar10 = puVar13;
      do {
        if (*puVar10 == 6) {
          lVar8 = (long)puVar13 - *(long *)(puVar10 + 4);
          uVar11 = puVar10[0xe];
          if (uVar11 == 6) goto LAB_011c4475;
LAB_011c43ae:
          if (uVar11 == 7) {
            puVar7 = puVar10 + 0xe;
          }
          uVar11 = puVar10[0x1c];
          if (uVar11 != 6) goto LAB_011c43c6;
LAB_011c448a:
          lVar8 = (long)puVar13 - *(long *)(puVar10 + 0x20);
          uVar11 = puVar10[0x2a];
          if (uVar11 == 6) goto LAB_011c44a5;
LAB_011c43e1:
          if (uVar11 == 7) {
            puVar7 = puVar10 + 0x2a;
          }
          uVar11 = puVar10[0x38];
          if (uVar11 != 6) goto LAB_011c43ff;
LAB_011c44c0:
          lVar8 = (long)puVar13 - *(long *)(puVar10 + 0x3c);
          uVar11 = puVar10[0x46];
          if (uVar11 == 6) goto LAB_011c44db;
LAB_011c441d:
          if (uVar11 == 7) {
            puVar7 = puVar10 + 0x46;
          }
          uVar11 = puVar10[0x54];
          if (uVar11 != 6) goto LAB_011c443b;
LAB_011c44f6:
          lVar8 = (long)puVar13 - *(long *)(puVar10 + 0x58);
          uVar11 = puVar10[0x62];
          if (uVar11 != 6) goto LAB_011c4511;
LAB_011c4370:
          lVar8 = (long)puVar13 - *(long *)(puVar10 + 0x66);
        }
        else {
          if (*puVar10 == 7) {
            puVar7 = puVar10;
          }
          uVar11 = puVar10[0xe];
          if (uVar11 != 6) goto LAB_011c43ae;
LAB_011c4475:
          lVar8 = (long)puVar13 - *(long *)(puVar10 + 0x12);
          uVar11 = puVar10[0x1c];
          if (uVar11 == 6) goto LAB_011c448a;
LAB_011c43c6:
          if (uVar11 == 7) {
            puVar7 = puVar10 + 0x1c;
          }
          uVar11 = puVar10[0x2a];
          if (uVar11 != 6) goto LAB_011c43e1;
LAB_011c44a5:
          lVar8 = (long)puVar13 - *(long *)(puVar10 + 0x2e);
          uVar11 = puVar10[0x38];
          if (uVar11 == 6) goto LAB_011c44c0;
LAB_011c43ff:
          if (uVar11 == 7) {
            puVar7 = puVar10 + 0x38;
          }
          uVar11 = puVar10[0x46];
          if (uVar11 != 6) goto LAB_011c441d;
LAB_011c44db:
          lVar8 = (long)puVar13 - *(long *)(puVar10 + 0x4a);
          uVar11 = puVar10[0x54];
          if (uVar11 == 6) goto LAB_011c44f6;
LAB_011c443b:
          if (uVar11 == 7) {
            puVar7 = puVar10 + 0x54;
          }
          uVar11 = puVar10[0x62];
          if (uVar11 == 6) goto LAB_011c4370;
LAB_011c4511:
          if (uVar11 == 7) {
            puVar7 = puVar10 + 0x62;
          }
        }
        uVar9 = uVar9 + 8;
        puVar10 = puVar10 + 0x70;
      } while (in_R9 != uVar9);
    }
    if (uVar4 != 0) {
      puVar10 = puVar13 + uVar9 * 0xe;
      do {
        uVar11 = *puVar10;
        in_R9 = (ulong)uVar11;
        if (uVar11 == 6) {
          lVar8 = (long)puVar13 - *(long *)(puVar10 + 4);
        }
        else if (uVar11 == 7) {
          puVar7 = puVar10;
        }
        puVar10 = puVar10 + 0xe;
        uVar4 = uVar4 - 1;
      } while (uVar4 != 0);
    }
    if (puVar7 != (uint *)0x0) {
      DAT_011fe008 = *(ulong *)(puVar7 + 0xc);
      DAT_011fe020 = lVar8 + *(long *)(puVar7 + 4);
      DAT_011fe028 = *(undefined8 *)(puVar7 + 8);
      lVar8 = *(long *)(puVar7 + 10);
      goto LAB_011c456b;
    }
  }
  lVar8 = 0;
  DAT_011fe028 = 0;
LAB_011c456b:
  DAT_011fe018 = -DAT_011fe008 & (lVar8 + DAT_011fe008) - 1;
  DAT_011fe010 = DAT_011fe018 + 0x17 & 0xfffffffffffffff8;
  DAT_011fe000 = DAT_011fe010 + 0x10;
  if ((DAT_011fe008 < 0x1001) && (DAT_011fe010 < 0xff1)) {
    puVar12 = &DAT_011ff000;
    lVar8 = DAT_011fe020;
    uVar4 = DAT_011fe018;
  }
  else {
    in_R9 = 0;
    syscall();
    puVar12 = (undefined *)(-DAT_011fe008 & DAT_011fe008 + 8);
    lVar8 = 0;
    uVar4 = 0xffffffffffffffff;
  }
  FUN_011f4160(puVar12,0,DAT_011fe000,lVar8,uVar4,in_R9);
  *(undefined **)(puVar12 + DAT_011fe018) = puVar12 + DAT_011fe018;
  uVar4 = DAT_011fe010;
  *(undefined8 *)(puVar12 + DAT_011fe010) = 1;
  *(undefined **)(puVar12 + uVar4 + 8) = puVar12;
  FUN_011f4580(puVar12,DAT_011fe020,DAT_011fe028);
  syscall();
  puVar3 = extraout_RDX;
  if (uVar6 != 0) {
    puVar14 = (ulong *)(puVar13 + 10);
    do {
      if ((uint)puVar14[-5] == 0x6474e551) {
        if (*puVar14 != 0) {
          puVar3 = (ulong *)0x0;
          syscall();
          uVar4 = *puVar14;
          if (local_40 <= *puVar14) {
            uVar4 = local_40;
          }
          if (local_48 < uVar4) {
            puVar3 = &local_48;
            syscall();
          }
        }
        break;
      }
      puVar14 = puVar14 + 7;
      uVar6 = uVar6 - 1;
    } while (uVar6 != 0);
  }
  _DAT_011fd280 = ZEXT1232(ZEXT812(0));
  _DAT_011fd2c0 = 0;
  _DAT_011fd2c8 = 0x18;
  DAT_011fd30b = lVar15 == 0;
  local_48 = *in_FS_OFFSET - 0x40003;
  local_40 = local_40 & 0xffffffff00000000;
  local_38 = 0x40000;
  syscall();
  PTR_DAT_011fd270 = (undefined *)(param_1 + lVar5 + 2);
  _DAT_011fd278 = -lVar15;
  _DAT_011fd2a0 = _DAT_011fd280;
  uVar1 = FUN_011be7e0(&local_48,0,puVar3,0x11c47b2);
  if ((short)uVar1 != 0) {
    FUN_011f30e0(uVar1);
    syscall();
  }
  syscall();
  syscall();
  lVar5 = 0x17;
  do {
    syscall();
    lVar5 = lVar5 + -1;
  } while (lVar5 != 0);
  return;
}


// ---- FUN_011c47e0 @ 011c47e0

void FUN_011c47e0(void)

{
  long lVar1;
  
  syscall();
  lVar1 = 0x17;
  do {
    syscall();
    lVar1 = lVar1 + -1;
  } while (lVar1 != 0);
  return;
}


// ---- FUN_011c4880 @ 011c4880

/* WARNING: Removing unreachable block (ram,0x011c4ac2) */

void FUN_011c4880(long *param_1,undefined8 param_2,undefined8 param_3,ulong param_4,
                 undefined8 param_5,undefined8 param_6)

{
  undefined8 *puVar1;
  int iVar2;
  int iVar3;
  ulong uVar4;
  int iVar5;
  long lVar6;
  long in_FS_OFFSET;
  bool bVar7;
  undefined *local_88;
  long local_80;
  long local_78;
  short local_70;
  undefined6 uStack_6e;
  undefined8 local_60;
  undefined8 local_58;
  long local_50;
  long *local_48;
  uint local_3c;
  long local_38;
  
  lVar6 = *(long *)(in_FS_OFFSET + -0x40010);
  if (lVar6 == 0) {
    if (*(char *)(in_FS_OFFSET + -0x40004) == '\x01') {
      iVar5 = *(int *)(in_FS_OFFSET + -0x40008);
    }
    else {
      param_4 = 0x11c48d6;
      syscall();
      iVar5 = 0xba;
      *(undefined4 *)(in_FS_OFFSET + -0x40008) = 0xba;
      *(undefined1 *)(in_FS_OFFSET + -0x40004) = 1;
    }
    local_3c = 0;
  }
  else {
    local_3c = (uint)*(byte *)(lVar6 + 0x21c);
    *(undefined1 *)(lVar6 + 0x21c) = 1;
    iVar5 = *(int *)(lVar6 + 0x218);
  }
  if (DAT_011fd2fc == iVar5) {
    DAT_011fd2d0 = DAT_011fd2d0 + 1;
  }
  else {
    LOCK();
    bVar7 = DAT_011fd300 == 0;
    iVar3 = DAT_011fd300;
    if (bVar7) {
      DAT_011fd300 = 1;
      iVar3 = 0;
    }
    iVar2 = DAT_011fd300;
    UNLOCK();
    local_88 = (undefined *)CONCAT71(local_88._1_7_,!bVar7);
    param_4 = (ulong)!bVar7;
    if (!bVar7) {
      if (iVar3 == 2) {
        param_4 = 0x11c4a7e;
        syscall();
        param_6 = param_3;
      }
      LOCK();
      DAT_011fd300 = 2;
      UNLOCK();
      if (iVar2 != 0) {
        do {
          syscall();
          LOCK();
          UNLOCK();
        } while( true );
      }
    }
    DAT_011fd2d0 = 1;
    DAT_011fd2fc = iVar5;
  }
  local_60 = param_2;
  local_58 = param_3;
  FUN_011d2070(&local_78,&DAT_011fcfb0,&DAT_0100eb50,param_4,iVar5,param_6);
  local_50 = CONCAT62(uStack_6e,local_70);
  local_38 = local_78;
  if (DAT_011fce85 == '\x01') {
    puVar1 = (undefined8 *)(local_78 + 0x18);
    uVar4 = 0;
    local_48 = param_1;
    do {
      while( true ) {
        lVar6 = 0xc - uVar4;
        if (*(ulong *)(local_38 + 0x28) < (ulong)(*(long *)(local_38 + 0x30) + lVar6)) break;
        FUN_011f4580(*(long *)(local_38 + 0x30) + *(long *)(local_38 + 0x20),&DAT_011b91e1 + uVar4,
                     lVar6);
        *(long *)(local_38 + 0x30) = *(long *)(local_38 + 0x30) + lVar6;
        uVar4 = uVar4 + lVar6;
        if (0xb < uVar4) goto LAB_011c49fe;
      }
      local_88 = &DAT_011b91e1 + uVar4;
      local_80 = lVar6;
      (**(code **)*puVar1)(&local_78,puVar1,&local_88,1,1);
      param_1 = local_48;
      if (local_70 != 0) goto LAB_011c4a09;
      uVar4 = uVar4 + local_78;
    } while (uVar4 < 0xc);
LAB_011c49fe:
    DAT_011fce85 = '\0';
    param_1 = local_48;
  }
LAB_011c4a09:
  (**(code **)(*(long *)(local_38 + 0x18) + 0x10))(local_38 + 0x18);
  *(undefined8 *)(local_38 + 0x20) = local_60;
  *(undefined8 *)(local_38 + 0x28) = local_58;
  if (*(long *)(in_FS_OFFSET + -0x40010) != 0) {
    *(byte *)(*(long *)(in_FS_OFFSET + -0x40010) + 0x21c) = (byte)local_3c & 1;
  }
  *param_1 = local_38;
  param_1[1] = local_50;
  return;
}


// ---- FUN_011c4ad0 @ 011c4ad0

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong FUN_011c4ad0(undefined *param_1,long *param_2,undefined8 param_3,long *param_4)

{
  char cVar1;
  bool bVar2;
  undefined1 auVar3 [32];
  undefined1 auVar4 [32];
  undefined1 auVar5 [32];
  undefined1 auVar6 [32];
  undefined1 auVar7 [32];
  undefined1 auVar8 [32];
  undefined1 auVar9 [32];
  undefined4 uVar10;
  undefined8 uVar11;
  byte bVar12;
  byte bVar13;
  short sVar14;
  undefined2 uVar15;
  uint uVar16;
  undefined *puVar17;
  undefined *puVar18;
  ushort *puVar19;
  byte bVar20;
  int iVar21;
  ulong uVar22;
  char *pcVar23;
  undefined2 uVar24;
  ushort uVar25;
  long *plVar26;
  char *pcVar27;
  undefined *puVar28;
  ulong uVar29;
  undefined6 uVar33;
  long lVar30;
  undefined *puVar31;
  long *plVar32;
  byte bVar34;
  undefined **ppuVar35;
  ulong uVar36;
  byte bVar37;
  undefined *puVar38;
  ulong uVar39;
  ulong in_R11;
  undefined8 *puVar40;
  undefined1 uVar41;
  long lVar42;
  undefined *puVar43;
  long lVar44;
  undefined7 uVar46;
  char *pcVar45;
  bool bVar47;
  ulong in_rflags;
  undefined1 auVar48 [32];
  undefined1 auVar49 [32];
  undefined8 local_870;
  ushort local_868;
  undefined6 uStack_866;
  undefined2 uStack_860;
  undefined2 uStack_85e;
  uint uStack_85c;
  undefined2 uStack_858;
  undefined2 uStack_856;
  undefined4 uStack_854;
  char local_850;
  char local_7f4 [388];
  ushort local_670;
  undefined4 local_66e;
  undefined1 local_654;
  undefined1 local_650;
  undefined8 *local_648;
  long *local_640;
  undefined1 local_628;
  ushort local_620 [4];
  undefined1 local_618 [9];
  undefined1 uStack_60f;
  undefined7 uStack_60e;
  undefined1 local_607;
  undefined1 local_604 [12];
  ushort local_5f8 [40];
  undefined8 local_5a8;
  ushort local_5a0;
  undefined8 local_59e;
  undefined8 uStack_596;
  undefined1 local_58c;
  undefined1 local_588;
  undefined8 *local_580;
  long *local_578;
  undefined1 local_560;
  long local_558 [2];
  long local_548 [2];
  undefined8 local_538;
  char cStack_530;
  undefined1 uStack_52f;
  undefined6 uStack_52e;
  undefined2 uStack_528;
  undefined6 uStack_526;
  undefined2 uStack_520;
  undefined2 uStack_51e;
  uint uStack_51c;
  char local_518;
  undefined8 local_3b8;
  undefined8 uStack_3b0;
  undefined1 local_3a8 [16];
  undefined1 local_398 [16];
  undefined1 local_388 [8];
  undefined1 local_380 [8];
  undefined8 *local_378;
  undefined *local_370;
  undefined1 local_368 [16];
  undefined8 local_358;
  undefined4 local_350;
  undefined2 local_34c;
  undefined1 local_34a;
  undefined1 local_32c [268];
  long *local_220;
  long local_218;
  undefined8 local_210;
  ushort local_208;
  undefined *local_200;
  undefined **ppuStack_1f8;
  undefined *local_1f0;
  undefined *local_1e8;
  undefined **ppuStack_1e0;
  undefined8 local_1d8;
  undefined8 uStack_1d0;
  undefined8 local_1c8;
  undefined **local_1c0;
  undefined8 *local_1b8;
  long *local_1b0;
  undefined1 local_1a8 [16];
  undefined *local_198;
  undefined4 local_190;
  undefined2 local_18c;
  undefined1 local_18a;
  long local_180;
  ushort local_178;
  undefined *local_170;
  undefined **local_168;
  undefined *local_160;
  undefined **local_158;
  undefined8 *local_150;
  long *local_148;
  undefined *local_140;
  char *local_138;
  undefined8 uStack_130;
  undefined2 local_128;
  undefined2 uStack_126;
  ushort uStack_124;
  undefined2 uStack_122;
  char local_120;
  undefined *local_118;
  undefined *local_110;
  long *local_108;
  ulong local_100;
  ulong local_f8;
  undefined8 *local_f0;
  char *local_e8;
  undefined8 uStack_e0;
  undefined1 local_d0;
  undefined1 local_c8;
  undefined1 local_c0;
  undefined1 local_b8;
  undefined1 local_b0;
  undefined1 local_a8;
  undefined1 local_a0;
  undefined1 local_98;
  undefined *local_90;
  long *local_88;
  undefined *local_80;
  long *local_78;
  undefined8 local_70;
  undefined *local_68;
  ulong local_60;
  undefined8 local_58;
  undefined1 local_50;
  undefined1 local_4c;
  undefined1 local_48;
  undefined1 local_44;
  undefined1 local_40 [8];
  undefined *local_38;
  
  lVar42 = *param_2;
  plVar32 = (long *)param_2[1];
  puVar40 = (undefined8 *)*param_4;
  uVar25 = *(ushort *)(param_4 + 1);
  local_80 = (undefined *)CONCAT71(local_80._1_7_,*(undefined1 *)((long)param_4 + 10));
  local_f8 = CONCAT71(local_f8._1_7_,*(undefined1 *)((long)param_4 + 0xb));
  local_158 = &PTR_FUN_0100e020;
  local_44 = 1;
  local_160 = param_1;
  local_148 = param_4;
  local_88 = param_2;
  local_58 = param_3;
  FUN_011c9bc0(&local_870,lVar42,plVar32);
  uVar41 = local_44;
  local_68 = param_1;
  uVar33 = (undefined6)((ulong)lVar42 >> 0x10);
  if (local_850 != '\0') {
LAB_011c4b69:
    local_48 = 0;
    local_870 = local_870 & 0xffffffff00000000;
    if (plVar32 != (long *)0x0) {
      bVar34 = 0;
      bVar20 = 0;
      plVar26 = (long *)0x0;
      bVar47 = false;
      do {
        while( true ) {
          cVar1 = *(char *)(lVar42 + (long)plVar26);
          bVar2 = cVar1 != '.';
          if (cVar1 == '.') break;
          bVar37 = cVar1 - 0x30;
          if ((9 < bVar37) || (bVar13 = bVar47 | cVar1 != '0', (bool)(bVar20 & bVar13)))
          goto LAB_011c4d43;
          sVar14 = (ushort)*(byte *)((long)&local_870 + (ulong)bVar34) * 10;
          bVar47 = (char)((ushort)sVar14 >> 8) != '\0';
          in_R11 = CONCAT71((int7)(in_R11 >> 8),bVar47);
          local_3a8[0] = bVar47;
          if (bVar47) goto LAB_011c4d43;
          bVar12 = (byte)sVar14;
          local_3a8[0] = CARRY1(bVar12,bVar37);
          if (CARRY1(bVar12,bVar37)) goto LAB_011c4d43;
          bVar20 = bVar13 ^ 1;
          *(byte *)((long)&local_870 + (ulong)bVar34) = bVar12 + bVar37;
          plVar26 = (long *)((long)plVar26 + 1);
          bVar47 = bVar2;
          if (plVar32 == plVar26) goto LAB_011c4c42;
        }
        if (!(bool)(bVar47 & bVar34 != 3)) goto LAB_011c4d43;
        bVar34 = bVar34 + 1;
        bVar20 = 0;
        plVar26 = (long *)((long)plVar26 + 1);
        bVar47 = bVar2;
      } while (plVar32 != plVar26);
LAB_011c4c42:
      uVar41 = local_48;
      if (cVar1 != '.' && bVar34 == 3) {
        uVar10 = (undefined4)local_870;
        if ((char)local_f8 != '\0') {
          uVar22 = CONCAT62(uVar33,0x60);
          if ((((byte)local_80 ^ DAT_0100f19f) & 1) == 0) goto LAB_011c5a8a;
        }
        if (puVar40 != (undefined8 *)0x0) {
          FUN_011f4580(puVar40,lVar42,plVar32);
          local_b0 = 0;
          local_b8 = 1;
          local_66e = uVar10;
          local_654 = uVar41;
          local_650 = 0;
          local_628 = 1;
          local_670 = uVar25;
          local_648 = puVar40;
          local_640 = plVar32;
          FUN_011cb0c0(local_3a8,local_58,&local_160,&local_670,2,2);
          uVar22 = (ulong)(ushort)local_3a8._8_2_;
          if (local_3a8._8_2_ == 0) {
            puVar17 = local_68;
            if (local_3a8._0_8_ != 2) {
              lVar42 = local_3a8._0_8_ * 0x28 + -0x668;
              goto LAB_011c500d;
            }
            goto LAB_011c71e1;
          }
          goto LAB_011c71d8;
        }
        local_c0 = 0;
        local_870._0_6_ = CONCAT42((undefined4)local_870,uVar25);
        goto LAB_011c5058;
      }
    }
LAB_011c4d43:
    local_200 = (undefined *)CONCAT44(local_200._4_4_,0xffffff9c);
    local_218 = lVar42;
    FUN_011d8d90(&local_210);
    uVar22 = (ulong)local_208;
    local_220 = plVar32;
    if (local_208 == 0) {
      local_140 = (undefined *)CONCAT62(local_140._2_6_,uVar25);
      local_538 = (undefined *)CONCAT71(local_538._1_7_,1);
      local_398 = (undefined1  [16])0x0;
      local_388 = (undefined1  [8])0x0;
      local_368 = (undefined1  [16])0x0;
      local_3a8._8_8_ = &PTR_FUN_0100e020;
      local_3a8._0_8_ = param_1;
      local_380 = (undefined1  [8])&PTR_FUN_0100f0d0;
      local_378 = &local_870;
      local_370 = (undefined *)0x200;
      local_70 = local_210;
      local_358 = local_210;
      local_350 = 0;
      local_34c = 0;
      local_34a = 1;
      local_118 = (undefined *)*local_88;
      uVar29 = local_88[1];
      local_90 = (undefined *)*local_148;
      local_150 = (undefined8 *)CONCAT62(local_150._2_6_,(short)local_148[1]);
      local_168 = &PTR_FUN_0100e020;
      local_108 = (long *)CONCAT71(local_108._1_7_,*(char *)((long)local_148 + 0xb));
      local_1f0 = (undefined *)
                  CONCAT71(local_1f0._1_7_,
                           *(byte *)((long)local_148 + 10) ^ s_ZIG_PROGRESS__0100f190[0xd]);
      local_100 = uVar29 - 1;
      local_78 = (long *)CONCAT71(local_78._1_7_,uVar29 == 0 || local_90 == (undefined *)0x0);
      local_110 = (undefined *)
                  CONCAT71(local_110._1_7_,
                           DAT_0100f19f ^ *(byte *)((long)local_148 + 10) |
                           *(char *)((long)local_148 + 0xb) == '\0');
      local_60 = 0;
      local_38 = (undefined *)0x0;
      puVar17 = (undefined *)0x0;
      lVar42 = 0;
      in_R11 = in_rflags;
      local_170 = param_1;
      local_f0 = puVar40;
LAB_011c50d5:
      puVar40 = local_378;
      FUN_011c97a0(&local_128,local_378,puVar17,lVar42,10);
      if (local_120 == '\0') {
        do {
          puVar31 = puVar17 + -lVar42;
          if (local_370 == puVar31) {
            local_538 = PTR_PTR_0100ee68;
            cStack_530 = (char)_UNK_0100ee70;
            uStack_52f = (undefined1)((ulong)_UNK_0100ee70 >> 8);
            uStack_52e = (undefined6)((ulong)_UNK_0100ee70 >> 0x10);
            uStack_528 = (undefined2)_UNK_0100ee78;
            uStack_526 = (undefined6)((ulong)_UNK_0100ee78 >> 0x10);
            uStack_520 = (undefined2)_UNK_0100ee80;
            uStack_51e = (undefined2)((ulong)_UNK_0100ee80 >> 0x10);
            uStack_51c = (uint)((ulong)_UNK_0100ee80 >> 0x20);
            do {
              (**(code **)local_380)(&local_138,local_380,&local_538,1);
            } while ((short)uStack_130 == 0);
            if ((short)uStack_130 == 0x68) {
              sVar14 = 0x72;
LAB_011c57ec:
              if (sVar14 == 0x15) goto LAB_011c5a67;
              if (sVar14 == 0x72) {
                uVar22 = 0xffffffffffffffff;
                puVar17 = (undefined *)local_368._8_8_;
                puVar31 = (undefined *)local_368._0_8_;
                if ((ulong)local_368._0_8_ < (ulong)local_368._8_8_) goto LAB_011c5870;
                while( true ) {
                  sVar14 = FUN_011cb030(local_380);
                  if (sVar14 == 0x14) break;
                  puVar17 = (undefined *)local_368._8_8_;
                  puVar31 = (undefined *)local_368._0_8_;
                  if (sVar14 == 0x15) goto LAB_011c5a67;
LAB_011c5870:
                  do {
                    uVar39 = (long)puVar17 - (long)puVar31;
                    if (uVar22 <= (ulong)((long)puVar17 - (long)puVar31)) {
                      uVar39 = uVar22;
                    }
                    FUN_011c97a0(&local_538,(undefined *)((long)local_378 + (long)puVar31),uVar39,0,
                                 10);
                    if (cStack_530 != '\0') {
                      local_368._0_8_ = puVar31 + (long)local_538;
                      puVar31 = (undefined *)local_368._0_8_;
                      if ((undefined *)local_368._0_8_ != puVar17) goto LAB_011c50b3;
                      goto LAB_011c58d3;
                    }
                    local_368._0_8_ = puVar31 + uVar39;
                    uVar22 = uVar22 - uVar39;
                    puVar31 = (undefined *)local_368._0_8_;
                  } while ((ulong)local_368._0_8_ < puVar17);
                }
                puVar31 = (undefined *)local_368._0_8_;
                if (local_368._0_8_ == local_368._8_8_) goto LAB_011c58d3;
LAB_011c50b3:
                local_368._0_8_ = puVar31 + 1;
                goto LAB_011c50c0;
              }
LAB_011c58d3:
              if ((char)local_38 != '\0') {
                local_40[0] = 1;
                local_538 = local_90;
                cStack_530 = (char)uVar29;
                uStack_52f = (undefined1)(uVar29 >> 8);
                uStack_52e = (undefined6)(uVar29 >> 0x10);
                local_518 = '\x01';
                FUN_011cb0c0(&local_1e8,local_58,&local_170,&local_538,1,1);
                uVar22 = (ulong)ppuStack_1e0 & 0xffff;
                if ((short)ppuStack_1e0 == 0) goto LAB_011c592f;
                goto LAB_011c595e;
              }
LAB_011c592f:
              syscall();
              puVar40 = local_f0;
              in_rflags = in_R11;
              uVar25 = (ushort)local_140;
              if (local_60 != 0) {
                plVar32 = local_558;
                uVar22 = 0;
                puVar17 = local_68;
                goto LAB_011c71ea;
              }
              goto LAB_011c598c;
            }
            sVar14 = (short)uStack_130;
            if ((short)uStack_130 == 0x15) goto LAB_011c57ec;
LAB_011c57bf:
            puVar31 = (undefined *)(local_368._8_8_ + -local_368._0_8_);
            if (puVar31 == (undefined *)0x0) goto LAB_011c58d3;
            lVar44 = (long)local_378 + local_368._0_8_;
            puVar17 = (undefined *)local_368._8_8_;
            lVar42 = local_368._0_8_;
            goto LAB_011c510a;
          }
          if ((local_370 <= puVar17) &&
             (sVar14 = (**(code **)((long)local_380 + 0x18))(local_380,puVar31 + 1), sVar14 != 0)) {
LAB_011c58c4:
            if (sVar14 != 0x14) goto LAB_011c57ec;
            goto LAB_011c57bf;
          }
          local_e8 = "";
          uStack_e0 = 0;
          (**(code **)((long)local_380 + 0x10))(&local_1e8,local_380,&local_e8,1);
          puVar40 = local_378;
          sVar14 = (short)ppuStack_1e0;
          if ((short)ppuStack_1e0 != 0) goto LAB_011c58c4;
          lVar42 = local_368._0_8_;
          puVar17 = (undefined *)local_368._8_8_;
          FUN_011c97a0(&local_180,local_378,local_368._8_8_,puVar31 + local_368._0_8_,10);
          lVar30 = local_180;
        } while ((char)local_178 == '\0');
      }
      else {
        lVar30 = CONCAT26(uStack_122,CONCAT24(uStack_124,CONCAT22(uStack_126,local_128)));
      }
      lVar44 = (long)puVar40 + lVar42;
      puVar31 = (undefined *)(lVar30 - lVar42);
LAB_011c510a:
      local_368._0_8_ = puVar31 + lVar42 + (puVar17 != puVar31 + lVar42);
      FUN_011c97a0(&local_538,lVar44,puVar31,0);
      if (cStack_530 != '\0') {
        puVar31 = local_538;
      }
      if (puVar31 != (undefined *)0x0) {
        puVar17 = (undefined *)0x0;
        do {
          if ((puVar17[lVar44] != '\t') && (puVar17[lVar44] != ' ')) {
            if (puVar31 != puVar17) {
              puVar18 = puVar17;
              puVar43 = puVar17;
              if (puVar31 <= puVar17) goto LAB_011c51ca;
              goto LAB_011c51b0;
            }
            break;
          }
          puVar17 = puVar17 + 1;
        } while (puVar31 != puVar17);
      }
      goto LAB_011c50c0;
    }
    if ((local_208 - 0x2d < 2) || (local_208 == 10)) goto LAB_011c598c;
    if (local_208 != 0x11) {
      uVar22 = 0x67;
    }
    goto LAB_011c5a8a;
  }
  local_3b8 = CONCAT44(uStack_85c,CONCAT22(uStack_85e,uStack_860));
  uStack_3b0 = CONCAT44(uStack_854,CONCAT22(uStack_856,uStack_858));
  local_3a8._8_8_ = uStack_3b0;
  local_3a8._0_8_ = local_3b8;
  if (local_870 != 0) goto LAB_011c4b69;
  if ((char)local_f8 != '\0') {
    uVar22 = CONCAT62(uVar33,0x60);
    if ((((byte)local_80 ^ s_ZIG_PROGRESS__0100f190[0xd]) & 1) == 0) goto LAB_011c5a8a;
  }
  if (puVar40 == (undefined8 *)0x0) {
    uStack_866 = (undefined6)local_3b8;
    uStack_860 = (undefined2)(uStack_85c >> 0x10);
    uStack_85c = (uint)((ulong)uStack_3b0 >> 0x10);
    uStack_858 = (undefined2)((uint)uStack_854 >> 0x10);
    local_a8 = 0;
    local_870 = 0;
    local_868 = uVar25;
LAB_011c5058:
    uStack_854 = CONCAT31(uStack_854._1_3_,uVar41);
    local_850 = '\0';
    FUN_011cb0c0(local_3a8,local_58,&local_160,&local_870,1,1);
    uVar22 = (ulong)(ushort)local_3a8._8_2_;
    goto LAB_011c71d8;
  }
  FUN_011f4580(puVar40,lVar42,plVar32);
  local_59e = local_3b8;
  uStack_596 = uStack_3b0;
  local_98 = 0;
  local_a0 = 1;
  local_5a8 = 0;
  local_58c = uVar41;
  local_588 = 0;
  local_560 = 1;
  local_5a0 = uVar25;
  local_580 = puVar40;
  local_578 = plVar32;
  FUN_011cb0c0(local_3a8,local_58,&local_160,&local_5a8,2,2);
  uVar22 = (ulong)(ushort)local_3a8._8_2_;
  if (local_3a8._8_2_ != 0) goto LAB_011c71d8;
  puVar17 = local_68;
  if (local_3a8._0_8_ != 2) {
    lVar42 = local_3a8._0_8_ * 0x28 + -0x5a0;
LAB_011c500d:
    puVar17 = local_68;
    FUN_011cb0c0(&local_870,local_58,&local_160,&stack0xfffffffffffffff8 + lVar42,
                 2 - local_3a8._0_8_,2 - local_3a8._0_8_);
    uVar22 = (ulong)local_868;
    if (local_868 == 0) goto LAB_011c71e1;
    goto LAB_011c4fc6;
  }
  goto LAB_011c71e1;
  while (puVar43 = puVar43 + 1, puVar18 = puVar31, puVar31 != puVar43) {
LAB_011c51b0:
    puVar18 = puVar43;
    if ((puVar43[lVar44] == '\t') || (puVar43[lVar44] == ' ')) break;
  }
LAB_011c51ca:
  puVar43 = puVar17 + lVar44;
  lVar42 = (long)puVar18 - (long)puVar17;
  if (puVar43 != (undefined *)0x0) {
    puVar17 = puVar17 + lVar42;
    while( true ) {
      if (puVar17 < puVar31) {
        while ((puVar17[lVar44] == ' ' || (puVar17[lVar44] == '\t'))) {
          puVar17 = puVar17 + 1;
          if (puVar31 == puVar17) goto LAB_011c50c0;
        }
      }
      if (puVar17 == puVar31) break;
      puVar18 = puVar17;
      puVar28 = puVar17;
      if (puVar17 < puVar31) {
        do {
          puVar18 = puVar28;
          if ((puVar28[lVar44] == '\t') || (puVar28[lVar44] == ' ')) break;
          puVar28 = puVar28 + 1;
          puVar18 = puVar31;
        } while (puVar31 != puVar28);
      }
      puVar28 = puVar17 + lVar44;
      uVar22 = (long)puVar18 - (long)puVar17;
      if (puVar28 == (undefined *)0x0) break;
      puVar17 = puVar17 + uVar22;
      if (uVar22 == uVar29) {
        uVar46 = (undefined7)((ulong)lVar44 >> 8);
        if (uVar29 == 0) {
          local_38 = (undefined *)CONCAT71(uVar46,(char)local_38 != '\0');
          goto joined_r0x011c5672;
        }
        uVar22 = 0;
        while ((char)(((byte)(puVar28[uVar22] + 0xbf) < 0x1a) << 5 | puVar28[uVar22]) ==
               (char)(((byte)(local_118[uVar22] + 0xbf) < 0x1a) << 5 | local_118[uVar22])) {
          uVar22 = uVar22 + 1;
          if (uVar29 == uVar22) {
            puVar17 = (undefined *)CONCAT71(uVar46,(char)local_38 != '\0');
            if ((char)local_38 != '\0' || ((ulong)local_78 & 1) != 0) goto LAB_011c52e1;
            uVar22 = uVar29;
            if (puVar28[uVar29 - 1] == '.') {
              uVar22 = local_100;
            }
            if (uVar22 - 0x100 < 0xffffffffffffff01) goto LAB_011c5325;
            uVar39 = 0;
            puVar17 = (undefined *)0x0;
            goto LAB_011c55a4;
          }
        }
      }
    }
  }
  goto LAB_011c50c0;
LAB_011c55a4:
  do {
    bVar20 = puVar28[uVar39];
    if (bVar20 == 0x2d) {
      if (puVar17 == (undefined *)0x0) goto LAB_011c5325;
LAB_011c5599:
      puVar17 = puVar17 + 1;
    }
    else {
      if (bVar20 != 0x2e) {
        if (((byte)(bVar20 - 0x30) < 10) || ((byte)((bVar20 & 0xdf) + 0xbf) < 0x1a))
        goto LAB_011c5599;
        goto LAB_011c5325;
      }
      if (puVar17 + -0x40 < (undefined *)0xffffffffffffffc1) goto LAB_011c5325;
      puVar17 = (undefined *)0x0;
      if ((9 < (byte)(puVar28[uVar39 - 1] - 0x30)) &&
         (0x19 < (byte)((puVar28[uVar39 - 1] & 0xdf) + 0xbf))) goto LAB_011c52e1;
    }
    uVar39 = uVar39 + 1;
  } while (uVar22 != uVar39);
  if (puVar17 + -0x40 < (undefined *)0xffffffffffffffc1) {
LAB_011c5325:
    local_38 = (undefined *)0x0;
joined_r0x011c5672:
    if (((ulong)local_110 & 1) != 0) goto LAB_011c5339;
LAB_011c54a9:
    if (((ulong)local_1f0 & 1) == 0) goto LAB_011c50c0;
  }
  else {
    puVar17 = (undefined *)0x0;
    if ((uVar29 < 0x100) &&
       ((byte)(puVar28[uVar22 - 1] - 0x30) < 10 ||
        (byte)((puVar28[uVar22 - 1] & 0xdf) + 0xbf) < 0x1a)) {
      FUN_011f4580(local_90,puVar28,uVar29);
      puVar17 = (undefined *)0x1;
    }
LAB_011c52e1:
    local_38 = puVar17;
    if (((ulong)local_110 & 1) == 0) goto LAB_011c54a9;
LAB_011c5339:
    local_4c = 0;
    local_538 = (undefined *)((ulong)local_538 & 0xffffffff00000000);
    if (lVar42 != 0) {
      bVar34 = 0;
      bVar20 = 0;
      lVar44 = 0;
      bVar47 = false;
      do {
        while( true ) {
          cVar1 = puVar43[lVar44];
          bVar2 = cVar1 != '.';
          if (cVar1 == '.') break;
          bVar37 = cVar1 - 0x30;
          if ((9 < bVar37) || (bVar13 = bVar47 | cVar1 != '0', (bool)(bVar20 & bVar13)))
          goto LAB_011c54a0;
          sVar14 = (ushort)*(byte *)((long)&local_538 + (ulong)bVar34) * 10;
          bVar47 = (char)((ushort)sVar14 >> 8) != '\0';
          local_1e8 = (undefined *)CONCAT71(local_1e8._1_7_,bVar47);
          if (bVar47) goto LAB_011c54a0;
          bVar12 = (byte)sVar14;
          local_1e8 = (undefined *)CONCAT71(local_1e8._1_7_,CARRY1(bVar12,bVar37));
          if (CARRY1(bVar12,bVar37)) goto LAB_011c54a0;
          bVar20 = bVar13 ^ 1;
          *(byte *)((long)&local_538 + (ulong)bVar34) = bVar12 + bVar37;
          lVar44 = lVar44 + 1;
          bVar47 = bVar2;
          if (lVar42 == lVar44) goto LAB_011c5412;
        }
        if (!(bool)(bVar47 & bVar34 != 3)) goto LAB_011c54a0;
        bVar34 = bVar34 + 1;
        bVar20 = 0;
        lVar44 = lVar44 + 1;
        bVar47 = bVar2;
      } while (lVar42 != lVar44);
LAB_011c5412:
      if (cVar1 != '.' && bVar34 == 3) {
        local_c8 = 0;
        local_538._0_6_ = CONCAT42((int)local_538,local_150._0_2_);
        uStack_51c = uStack_51c & 0xffffff00;
        local_518 = '\0';
        FUN_011cb0c0(&local_1e8,local_58,&local_170,&local_538,1,1);
        uVar22 = (ulong)ppuStack_1e0 & 0xffff;
        if ((short)ppuStack_1e0 != 0) goto LAB_011c595e;
        local_60 = local_60 + 1;
      }
    }
LAB_011c54a0:
    if ((char)local_108 != '\0') goto LAB_011c54a9;
  }
  local_50 = 1;
  FUN_011c9bc0(&local_538,puVar43,lVar42);
  if (local_518 == '\0') {
    local_1e8 = (undefined *)CONCAT62(uStack_526,uStack_528);
    ppuStack_1e0 = (undefined **)CONCAT44(uStack_51c,CONCAT22(uStack_51e,uStack_520));
    if (local_538 == (undefined *)0x0) {
      uStack_52e = SUB86(local_1e8,0);
      uStack_528 = (undefined2)((uint6)uStack_526 >> 0x20);
      uStack_526 = SUB86(ppuStack_1e0,0);
      uStack_520 = (undefined2)(uStack_51c >> 0x10);
      local_d0 = 0;
      local_538 = (undefined *)0x0;
      cStack_530 = (char)local_150;
      uStack_52f = (undefined1)((ulong)local_150 >> 8);
      uStack_51c = CONCAT31(uStack_51c._1_3_,local_50);
      local_518 = '\0';
      FUN_011cb0c0(&local_1e8,local_58,&local_170,&local_538,1,1);
      uVar22 = (ulong)ppuStack_1e0 & 0xffff;
      if ((short)ppuStack_1e0 != 0) goto LAB_011c595e;
      local_60 = local_60 + 1;
    }
  }
LAB_011c50c0:
  puVar17 = (undefined *)local_368._8_8_;
  lVar42 = local_368._0_8_;
  goto LAB_011c50d5;
LAB_011c595e:
  if ((short)uVar22 == 0x15) {
LAB_011c5a67:
    syscall();
    uVar22 = 0x67;
    if ((short)local_350 == 0x11) {
      uVar22 = 0x11;
    }
LAB_011c5a8a:
    plVar32 = local_548;
    puVar17 = local_68;
    goto LAB_011c71ea;
  }
  syscall();
  puVar40 = local_f0;
  in_rflags = in_R11;
  uVar25 = (ushort)local_140;
  if ((short)uVar22 != 0x60) goto LAB_011c5a8a;
LAB_011c598c:
  plVar26 = local_220;
  cVar1 = *(char *)(local_218 + -1 + (long)local_220);
  plVar32 = (long *)((ulong)(cVar1 == '.') + 9);
  if (plVar32 <= local_220) {
    pcVar27 = "localhost";
    if (cVar1 == '.') {
      pcVar27 = "localhost.";
    }
    pcVar45 = (char *)((long)local_220 + (local_218 - (long)plVar32));
    uVar22 = FUN_011c9680(pcVar45,plVar32,pcVar27,plVar32);
    if (((uVar22 & 1) != 0) && ((plVar26 == plVar32 || (*pcVar45 == '.')))) {
      if (((char)local_f8 == '\0') || (((s_ZIG_PROGRESS__0100f190[0xd] ^ (byte)local_80) & 1) != 0))
      {
        puVar19 = (ushort *)(local_604 + 0xc);
        local_604[4] = 0;
        local_604[0] = 1;
        local_618._2_7_ = 0;
        uStack_60f = 0;
        uStack_60e = 0;
        local_620[0] = 0;
        local_620[1] = 0;
        local_620[2] = 0;
        local_620[3] = 0;
        local_607 = 1;
        lVar42 = 1;
        local_618._0_2_ = uVar25;
        if ((char)local_f8 != '\0') goto LAB_011c6f83;
LAB_011c6f8e:
        *(undefined1 *)(puVar19 + 0x10) = 0;
        *(undefined1 *)(puVar19 + 0xe) = 0;
        *puVar19 = uVar25;
        puVar19[1] = 0x7f;
        puVar19[2] = 0x100;
        lVar42 = lVar42 + 1;
      }
      else {
        puVar19 = local_620;
        lVar42 = 0;
LAB_011c6f83:
        if ((((byte)local_80 ^ DAT_0100f19f) & 1) != 0) goto LAB_011c6f8e;
      }
      if (puVar40 != (undefined8 *)0x0) {
        *puVar40 = 0x736f686c61636f6c;
        *(undefined1 *)(puVar40 + 1) = 0x74;
        local_604[lVar42 * 0x28 + 4] = 1;
        *(undefined8 **)(local_618 + lVar42 * 0x28 + -8) = puVar40;
        *(undefined8 *)(local_618 + lVar42 * 0x28) = 9;
        lVar42 = lVar42 + 1;
      }
      FUN_011cb0c0(local_3a8,local_58,&local_160,local_620,lVar42,lVar42);
      uVar22 = (ulong)(ushort)local_3a8._8_2_;
      if (local_3a8._8_2_ == 0) {
        lVar42 = lVar42 - local_3a8._0_8_;
        if (lVar42 == 0) {
          uVar22 = 0;
        }
        else {
          FUN_011cb0c0(&local_870,local_58,&local_160,local_618 + local_3a8._0_8_ * 0x28 + -8,lVar42
                       ,lVar42);
          uVar22 = (ulong)local_868;
        }
      }
      goto LAB_011c71d8;
    }
  }
  local_f0 = (undefined8 *)*local_88;
  local_f8 = local_88[1];
  local_140 = (undefined *)*local_148;
  local_200 = local_68;
  ppuStack_1f8 = &PTR_FUN_0100e020;
  local_3a8 = (undefined1  [16])0x0;
  local_398._8_4_ = 5;
  local_398._0_8_ = 0x100000002;
  local_e8 = (char *)CONCAT44(local_e8._4_4_,0xffffff9c);
  FUN_011d8d90(&local_538);
  puVar17 = local_538;
  uVar25 = CONCAT11(uStack_52f,cStack_530);
  if (uVar25 == 0) {
    local_538 = local_200;
    cStack_530 = (char)ppuStack_1f8;
    uStack_52f = (undefined1)((ulong)ppuStack_1f8 >> 8);
    uStack_52e = (undefined6)((ulong)ppuStack_1f8 >> 0x10);
    local_e8 = (char *)CONCAT71(local_e8._1_7_,1);
    uStack_528 = 0;
    uStack_526 = 0;
    uStack_520 = 0;
    uStack_51e = 0;
    uStack_51c = 0;
    ppuStack_1e0 = ppuStack_1f8;
    local_1e8 = local_200;
    local_1d8 = 0;
    uStack_1d0 = 0;
    local_1c8 = 0;
    local_1a8 = (undefined1  [16])0x0;
    local_1c0 = &PTR_FUN_0100f0d0;
    local_1b8 = &local_870;
    local_1b0 = (long *)0x200;
    local_80 = puVar17;
    local_198 = puVar17;
    local_190 = 0;
    local_18c = 0;
    local_18a = 1;
    plVar32 = (long *)0x0;
    plVar26 = (long *)0x0;
    in_R11 = in_rflags;
LAB_011c5c00:
    if (local_1b0 == (long *)((long)plVar26 - (long)plVar32)) {
      local_538 = PTR_PTR_0100ee68;
      cStack_530 = (char)_UNK_0100ee70;
      uStack_52f = (undefined1)((ulong)_UNK_0100ee70 >> 8);
      uStack_52e = (undefined6)((ulong)_UNK_0100ee70 >> 0x10);
      uStack_528 = (undefined2)_UNK_0100ee78;
      uStack_526 = (undefined6)((ulong)_UNK_0100ee78 >> 0x10);
      uStack_520 = (undefined2)_UNK_0100ee80;
      uStack_51e = (undefined2)((ulong)_UNK_0100ee80 >> 0x10);
      uStack_51c = (uint)((ulong)_UNK_0100ee80 >> 0x20);
      plVar32 = &local_180;
      do {
        (*(code *)*local_1c0)(plVar32,&local_1c0,&local_538,1);
        uVar16 = (uint)local_178;
      } while (local_178 == 0);
      if (1 < local_178 - 0x14) {
        uVar16 = 0x72;
      }
    }
    else if ((plVar26 < local_1b0) ||
            (uVar16 = (*(code *)local_1c0[3])
                                (&local_1c0,(undefined *)(((long)plVar26 - (long)plVar32) + 1)),
            (short)uVar16 == 0)) {
      local_138 = "";
      uStack_130 = 0;
      (*(code *)local_1c0[2])(&local_e8,&local_1c0,&local_138,1);
      puVar40 = local_1b8;
      uVar16 = (uint)uStack_e0 & 0xffff;
      if ((short)uStack_e0 == 0) goto code_r0x011c5c62;
    }
    local_60 = 0;
    if ((short)uVar16 != 0x14) goto LAB_011c6bac;
LAB_011c6b31:
    uVar25 = 0x14;
    if (local_1a8._8_8_ != local_1a8._0_8_) goto LAB_011c70e8;
    if (local_60 == 0) {
      uVar16 = FUN_011c8000(local_3a8,&local_200,"127.0.0.1",9);
      goto LAB_011c6bac;
    }
    goto LAB_011c6bb5;
  }
  if ((0x2e < uVar25) || ((0x600000000400U >> ((ulong)(uint)uVar25 & 0x3f) & 1) == 0))
  goto LAB_011c70f3;
  sVar14 = FUN_011c8000(local_3a8,&local_200,"127.0.0.1");
  if (sVar14 != 0) {
    uVar22 = 0x61;
    goto LAB_011c71d8;
  }
  goto LAB_011c6bc0;
code_r0x011c5c62:
  plVar32 = (long *)local_1a8._0_8_;
  plVar26 = (long *)local_1a8._8_8_;
  FUN_011c97a0(&local_128,local_1b8,local_1a8._8_8_);
  if (local_120 != '\0') goto LAB_011c5d3e;
  goto LAB_011c5c00;
LAB_011c5d3e:
  local_78 = plVar26;
  local_38 = (undefined *)((long)puVar40 + (long)plVar32);
  puVar17 = (undefined *)
            (CONCAT26(uStack_122,CONCAT24(uStack_124,CONCAT22(uStack_126,local_128))) -
            (long)plVar32);
  local_70 = CONCAT44(local_70._4_4_,5);
  local_88 = (long *)CONCAT44(local_88._4_4_,2);
  local_90 = (undefined *)CONCAT44(local_90._4_4_,1);
  local_60 = 0;
  local_100 = 0;
LAB_011c5d90:
  plVar32 = (long *)((undefined *)((long)plVar32 + (long)puVar17) + 1);
  local_1a8._0_8_ = plVar32;
  puVar31 = (undefined *)0x0;
  FUN_011c97a0(&local_538,local_38,puVar17);
  if (cStack_530 != '\0') {
    puVar17 = local_538;
  }
  puVar18 = (undefined *)0x0;
  if (puVar17 != (undefined *)0x0) {
    do {
      if ((local_38[(long)puVar18] != '\t') && (local_38[(long)puVar18] != ' ')) {
        if (puVar17 != puVar18) {
          puVar43 = puVar18;
          puVar28 = puVar18;
          if (puVar17 <= puVar18) goto LAB_011c5e6a;
          goto LAB_011c5e50;
        }
        break;
      }
      puVar18 = puVar18 + 1;
    } while (puVar17 != puVar18);
  }
  goto LAB_011c6630;
  while (puVar28 = puVar28 + 1, puVar43 = puVar17, puVar17 != puVar28) {
LAB_011c5e50:
    puVar43 = puVar28;
    if ((local_38[(long)puVar28] == '\t') || (local_38[(long)puVar28] == ' ')) break;
  }
LAB_011c5e6a:
  puVar28 = local_38 + (long)puVar18;
  puVar43 = puVar43 + -(long)puVar18;
  if ((puVar28 == (undefined *)0x0) || (puVar43 + -0xb < (undefined *)0xfffffffffffffffb))
  goto LAB_011c6630;
  uVar22 = (ulong)(uint)(&DAT_0100ee18)[(long)puVar43];
  if (*(undefined **)(&DAT_0100ede0 + uVar22 * 0x10) != puVar43) goto LAB_011c6630;
  uVar29 = uVar22;
  if ((&PTR_s_domain_0100edd8)[uVar22 * 2] != puVar28) {
    puVar31 = (undefined *)0x0;
    do {
      if ((&PTR_s_domain_0100edd8)[uVar22 * 2][(long)puVar31] != puVar28[(long)puVar31]) {
        if ((2 < (uint)(&DAT_0100ee18)[(long)puVar43]) ||
           (uVar29 = uVar22 + 1, *(undefined **)(&DAT_0100ede0 + uVar29 * 0x10) != puVar43))
        goto LAB_011c6630;
        puVar31 = (&PTR_s_domain_0100edd8)[uVar29 * 2];
        if (puVar31 != puVar28) {
          puVar38 = (undefined *)0x0;
          goto LAB_011c5fc0;
        }
        break;
      }
      puVar31 = puVar31 + 1;
    } while (puVar43 != puVar31);
  }
  goto LAB_011c5ee7;
  while (puVar38 = puVar38 + 1, puVar43 != puVar38) {
LAB_011c5fc0:
    if (puVar31[(long)puVar38] != puVar28[(long)puVar38]) {
      if ((uVar22 == 2) ||
         (uVar29 = uVar22 + 2, *(undefined **)(&DAT_0100ede0 + uVar29 * 0x10) != puVar43))
      goto LAB_011c6630;
      puVar31 = (&PTR_s_domain_0100edd8)[uVar29 * 2];
      if (puVar31 != puVar28) {
        puVar38 = (undefined *)0x0;
        goto LAB_011c67f0;
      }
      break;
    }
  }
  goto LAB_011c5ee7;
  while (puVar38 = puVar38 + 1, puVar43 != puVar38) {
LAB_011c67f0:
    if (puVar31[(long)puVar38] != puVar28[(long)puVar38]) {
      if ((uVar22 != 0) || (uVar29 = 3, _UNK_0100ee10 != puVar43)) goto LAB_011c6630;
      if (_UNK_0100ee08 != puVar28) {
        puVar31 = (undefined *)0x0;
        goto LAB_011c6a57;
      }
      break;
    }
  }
  goto LAB_011c5ee7;
LAB_011c6120:
  puVar43 = puVar17 + (long)puVar43;
  puVar17 = local_1f0;
  puVar40 = local_150;
  goto LAB_011c5ff0;
LAB_011c62ad:
  sVar14 = 0x6f;
LAB_011c62b2:
  uVar16 = (uint)bVar20 << 0x10;
LAB_011c62c0:
  if (sVar14 == 0) {
    uVar16 = uVar16 >> 0x10;
  }
  else {
    if (sVar14 == 0x6f) goto LAB_011c5ff0;
LAB_011c61e7:
    uVar16 = 0xff;
  }
LAB_011c62ce:
  if ((undefined *)0xfffffffffffffffb < local_118 + -9) {
    uVar22 = (ulong)*(uint *)(&DAT_0100edb4 + (long)local_118 * 4);
    if ((*(undefined **)(&DAT_0100ed88 + uVar22 * 0x10) == local_118) &&
       (((pcVar45 = (&PTR_s_ndots_0100ed80)[uVar22 * 2], uVar29 = uVar22, pcVar45 == pcVar27 ||
         ((*pcVar45 == *pcVar27 &&
          ((local_118 == (undefined *)0x1 ||
           ((pcVar45[1] == pcVar27[1] &&
            ((local_118 == (undefined *)0x2 ||
             ((pcVar45[2] == pcVar27[2] &&
              ((local_118 == (undefined *)0x3 ||
               ((pcVar45[3] == pcVar27[3] &&
                ((local_118 == (undefined *)0x4 ||
                 ((pcVar45[4] == pcVar27[4] &&
                  ((local_118 == (undefined *)0x5 ||
                   ((pcVar45[5] == pcVar27[5] &&
                    ((local_118 == (undefined *)0x6 ||
                     ((pcVar45[6] == pcVar27[6] &&
                      ((local_118 == (undefined *)0x7 || (pcVar45[7] == pcVar27[7]))))))))))))))))))
              )))))))))))) ||
        (((*(uint *)(&DAT_0100edb4 + (long)local_118 * 4) < 2 &&
          (uVar29 = uVar22 + 1, *(undefined **)(&DAT_0100ed88 + uVar29 * 0x10) == local_118)) &&
         (((pcVar45 = (&PTR_s_ndots_0100ed80)[uVar29 * 2], pcVar45 == pcVar27 ||
           ((*pcVar45 == *pcVar27 &&
            ((local_118 == (undefined *)0x1 ||
             ((pcVar45[1] == pcVar27[1] &&
              ((local_118 == (undefined *)0x2 ||
               ((pcVar45[2] == pcVar27[2] &&
                ((local_118 == (undefined *)0x3 ||
                 ((pcVar45[3] == pcVar27[3] &&
                  ((local_118 == (undefined *)0x4 ||
                   ((pcVar45[4] == pcVar27[4] &&
                    ((local_118 == (undefined *)0x5 ||
                     ((pcVar45[5] == pcVar27[5] &&
                      ((local_118 == (undefined *)0x6 ||
                       ((pcVar45[6] == pcVar27[6] &&
                        ((local_118 == (undefined *)0x7 || (pcVar45[7] == pcVar27[7]))))))))))))))))
                 )))))))))))))) ||
          ((uVar22 == 0 &&
           ((uVar29 = 2, PTR_caseD_e2_0100eda8 == local_118 &&
            ((PTR_caseD_e1_0100eda0 == pcVar27 ||
             ((*PTR_caseD_e1_0100eda0 == *pcVar27 &&
              ((local_118 == (undefined *)0x1 ||
               ((PTR_caseD_e1_0100eda0[1] == pcVar27[1] &&
                ((local_118 == (undefined *)0x2 ||
                 ((PTR_caseD_e1_0100eda0[2] == pcVar27[2] &&
                  ((local_118 == (undefined *)0x3 ||
                   ((PTR_caseD_e1_0100eda0[3] == pcVar27[3] &&
                    ((local_118 == (undefined *)0x4 ||
                     ((PTR_caseD_e1_0100eda0[4] == pcVar27[4] &&
                      ((local_118 == (undefined *)0x5 ||
                       ((PTR_caseD_e1_0100eda0[5] == pcVar27[5] &&
                        ((local_118 == (undefined *)0x6 ||
                         ((PTR_caseD_e1_0100eda0[6] == pcVar27[6] &&
                          ((local_118 == (undefined *)0x7 ||
                           (PTR_caseD_e1_0100eda0[7] == pcVar27[7]))))))))))))))))))))))))))))))))))
          )))))))) {
      bVar20 = (byte)uVar16;
      if (((&DAT_0100edb0)[uVar29] & 3) == 2) {
        if (0x3b < bVar20) {
          bVar20 = 0x3c;
        }
        local_70 = CONCAT44(local_70._4_4_,(uint)bVar20);
      }
      else if (((&DAT_0100edb0)[uVar29] & 3) == 1) {
        if (9 < bVar20) {
          uVar16 = 10;
        }
        local_88 = (long *)CONCAT44(local_88._4_4_,uVar16);
      }
      else {
        if (0xe < bVar20) {
          uVar16 = 0xf;
        }
        local_90 = (undefined *)CONCAT44(local_90._4_4_,uVar16);
      }
    }
  }
  goto LAB_011c5ff0;
LAB_011c62a0:
  sVar14 = 0x6a;
  uVar16 = 0;
  goto LAB_011c62c0;
code_r0x011c69b9:
  plVar32 = (long *)local_1a8._0_8_;
  plVar26 = (long *)local_1a8._8_8_;
  FUN_011c97a0(&local_128,local_1b8,local_1a8._8_8_);
  if (local_120 != '\0') goto LAB_011c6a73;
  goto LAB_011c6950;
LAB_011c6a73:
  local_38 = (undefined *)((long)puVar40 + (long)plVar32);
  puVar17 = (undefined *)
            (CONCAT26(uStack_122,CONCAT24(uStack_124,CONCAT22(uStack_126,local_128))) -
            (long)plVar32);
  local_78 = plVar26;
  goto LAB_011c5d90;
  while (puVar31 = puVar31 + 1, puVar43 != puVar31) {
LAB_011c6a57:
    if (_UNK_0100ee08[(long)puVar31] != puVar28[(long)puVar31]) goto LAB_011c6630;
  }
LAB_011c5ee7:
  puVar43 = puVar43 + (long)puVar18;
  if (((byte)(&DAT_010014bc)[uVar29] & 3) - 2 < 2) {
    puVar31 = puVar43;
    if (puVar43 < puVar17) {
      do {
        if ((local_38[(long)puVar31] != ' ') && (puVar43 = puVar31, local_38[(long)puVar31] != '\t')
           ) break;
        puVar31 = puVar31 + 1;
        puVar43 = puVar17;
      } while (puVar17 != puVar31);
    }
    FUN_011f4580(local_32c,local_38 + (long)puVar43,(long)puVar17 - (long)puVar43);
    local_100 = (long)puVar17 - (long)puVar43;
    goto LAB_011c6630;
  }
  local_108 = plVar32;
  if (((byte)(&DAT_010014bc)[uVar29] & 3) != 1) {
LAB_011c5ff0:
    do {
      local_150 = puVar40;
      local_1f0 = puVar17;
      puVar40 = local_150;
      plVar32 = local_108;
      if (puVar43 < local_1f0) {
        while ((local_38[(long)puVar43] == ' ' || (local_38[(long)puVar43] == '\t'))) {
          puVar43 = puVar43 + 1;
          if (local_1f0 == puVar43) goto LAB_011c6630;
        }
      }
      if (puVar43 == local_1f0) goto LAB_011c6630;
      puVar17 = puVar43;
      puVar31 = puVar43;
      if (puVar43 < local_1f0) {
        do {
          puVar17 = puVar31;
          if ((local_38[(long)puVar31] == '\t') || (local_38[(long)puVar31] == ' ')) break;
          puVar31 = puVar31 + 1;
          puVar17 = local_1f0;
        } while (local_1f0 != puVar31);
      }
      pcVar27 = local_38 + (long)puVar43;
      puVar17 = puVar17 + -(long)puVar43;
      if (pcVar27 == (char *)0x0) goto LAB_011c6630;
      FUN_011c97a0(&local_538,pcVar27,puVar17,0,0x3a);
      if (cStack_530 == '\0') goto LAB_011c6120;
      local_118 = local_538;
      puVar31 = local_538 + 1;
      local_110 = puVar43;
      FUN_011c97a0(&local_538,pcVar27,puVar17,puVar31,0x3a);
      puVar18 = puVar17;
      if (cStack_530 != '\0') {
        puVar18 = local_538;
      }
      pcVar45 = pcVar27 + (long)local_118;
      pcVar23 = pcVar45 + 1;
      lVar42 = (long)puVar18 - (long)puVar31;
      puVar43 = puVar17 + (long)local_110;
      puVar17 = local_1f0;
      puVar40 = local_150;
      if ((pcVar23 != (char *)0x0) && (lVar42 != 0)) {
        cVar1 = *pcVar23;
        uVar16 = 0;
        sVar14 = 0x6f;
        if (cVar1 == '_') goto LAB_011c62c0;
        if (cVar1 != '-') {
          if (cVar1 == '+') {
            uVar16 = 0;
            if (((lVar42 == 1) || (pcVar45[2] == '_')) || (pcVar45[lVar42] == '_'))
            goto LAB_011c62c0;
            lVar44 = 1;
            bVar20 = 0;
            do {
              if (pcVar23[lVar44] != '_') {
                bVar34 = pcVar23[lVar44] - 0x30;
                if (9 < bVar34) goto LAB_011c62ad;
                if (bVar20 == 0) {
                  bVar37 = 0;
                }
                else {
                  bVar37 = (byte)((ushort)bVar20 * 10);
                  bVar47 = (char)((ushort)((ushort)bVar20 * 10) >> 8) != '\0';
                  local_538 = (undefined *)CONCAT71(local_538._1_7_,bVar47);
                  if (bVar47) goto LAB_011c62a0;
                }
                bVar20 = bVar37 + bVar34;
                local_538 = (undefined *)CONCAT71(local_538._1_7_,CARRY1(bVar37,bVar34));
                if (CARRY1(bVar37,bVar34)) goto LAB_011c62a0;
              }
              lVar44 = lVar44 + 1;
            } while (lVar42 != lVar44);
LAB_011c62a9:
            sVar14 = 0;
            goto LAB_011c62b2;
          }
          if (pcVar45[lVar42] != '_') {
            lVar44 = 0;
            bVar20 = 0;
            do {
              if (pcVar23[lVar44] != '_') {
                bVar34 = pcVar23[lVar44] - 0x30;
                if (9 < bVar34) goto LAB_011c62ad;
                if (bVar20 == 0) {
                  bVar37 = 0;
                }
                else {
                  bVar37 = (byte)((ushort)bVar20 * 10);
                  bVar47 = (char)((ushort)((ushort)bVar20 * 10) >> 8) != '\0';
                  local_538 = (undefined *)CONCAT71(local_538._1_7_,bVar47);
                  if (bVar47) goto LAB_011c62a0;
                }
                bVar20 = bVar37 + bVar34;
                local_538 = (undefined *)CONCAT71(local_538._1_7_,CARRY1(bVar37,bVar34));
                if (CARRY1(bVar37,bVar34)) goto LAB_011c62a0;
              }
              lVar44 = lVar44 + 1;
            } while (lVar42 != lVar44);
            goto LAB_011c62a9;
          }
          goto LAB_011c62c0;
        }
        if (((lVar42 != 1) && (pcVar45[2] != '_')) && (pcVar45[lVar42] != '_')) {
          lVar44 = 1;
          do {
            bVar20 = pcVar23[lVar44];
            if (bVar20 != 0x5f) {
              if (9 < (byte)(bVar20 - 0x30)) goto LAB_011c5ff0;
              if (0x30 < bVar20) goto LAB_011c61e7;
            }
            lVar44 = lVar44 + 1;
            uVar16 = 0;
          } while (lVar42 != lVar44);
          goto LAB_011c62ce;
        }
      }
    } while( true );
  }
  if (puVar43 < puVar17) {
    do {
      if ((local_38[(long)puVar43] != ' ') && (local_38[(long)puVar43] != '\t')) goto LAB_011c5f67;
      puVar43 = puVar43 + 1;
    } while (puVar17 != puVar43);
    goto LAB_011c6630;
  }
LAB_011c5f67:
  if (puVar43 == puVar17) goto LAB_011c6630;
  puVar18 = puVar43;
  puVar28 = puVar43;
  if (puVar43 < puVar17) {
    do {
      puVar18 = puVar28;
      if ((local_38[(long)puVar28] == '\t') || (local_38[(long)puVar28] == ' ')) break;
      puVar28 = puVar28 + 1;
      puVar18 = puVar17;
    } while (puVar17 != puVar28);
  }
  puVar17 = local_38 + (long)puVar43;
  if ((puVar17 == (undefined *)0x0) || (2 < local_60)) goto LAB_011c6630;
  local_40[0] = 0;
  local_538 = (undefined *)((ulong)local_538 & 0xffffffff00000000);
  if (puVar18 != puVar43) {
    bVar20 = 0;
    uVar29 = 0;
    uVar22 = 0;
    lVar42 = 0;
    do {
      while( true ) {
        cVar1 = puVar17[lVar42];
        puVar31 = (undefined *)CONCAT71((int7)((ulong)puVar31 >> 8),cVar1 != '.');
        if (cVar1 != '.') break;
        if (((byte)uVar29 & bVar20 != 3) == 0) goto LAB_011c680f;
        bVar20 = bVar20 + 1;
        uVar22 = 0;
        lVar42 = lVar42 + 1;
        uVar29 = (ulong)puVar31 & 0xffffffff;
        if ((long)puVar18 - (long)puVar43 == lVar42) goto LAB_011c6792;
      }
      bVar34 = cVar1 - 0x30;
      if (9 < bVar34) goto LAB_011c680f;
      bVar37 = (byte)uVar29 | cVar1 != '0';
      if (((byte)uVar22 & bVar37) != 0) goto LAB_011c680f;
      sVar14 = (ushort)*(byte *)((long)&local_538 + (ulong)bVar20) * 10;
      bVar47 = (char)((ushort)sVar14 >> 8) != '\0';
      plVar32 = (long *)CONCAT71((int7)((ulong)plVar32 >> 8),bVar47);
      local_e8 = (char *)CONCAT71(local_e8._1_7_,bVar47);
      if (bVar47) goto LAB_011c680f;
      bVar13 = (byte)sVar14;
      local_e8 = (char *)CONCAT71(local_e8._1_7_,CARRY1(bVar13,bVar34));
      if (CARRY1(bVar13,bVar34)) goto LAB_011c680f;
      uVar22 = CONCAT71((int7)(uVar29 >> 8),bVar37) ^ 1;
      *(byte *)((long)&local_538 + (ulong)bVar20) = bVar13 + bVar34;
      lVar42 = lVar42 + 1;
      uVar29 = (ulong)puVar31 & 0xffffffff;
      plVar32 = local_108;
    } while ((long)puVar18 - (long)puVar43 != lVar42);
LAB_011c6792:
    if (cVar1 == '.' || bVar20 != 3) goto LAB_011c680f;
    uVar24 = 0x35;
    ppuVar35 = (undefined **)local_40;
    iVar21 = (int)local_538;
    uVar15 = (short)CONCAT71((int7)(uVar22 >> 8),cVar1 != '.');
LAB_011c68f4:
    uVar41 = *(undefined1 *)ppuVar35;
    lVar42 = local_60 * 0x20;
    *(undefined2 *)(local_398 + lVar42 + 0xc) = uVar24;
    *(int *)(local_398 + lVar42 + 0xe) = iVar21;
    *(undefined2 *)(local_388 + lVar42 + 2) = uVar15;
    *(undefined2 *)(local_388 + lVar42 + 4) = 0x35;
    uVar11 = uStack_130;
    *(char **)(local_388 + lVar42 + 6) = local_138;
    *(undefined8 *)(local_380 + lVar42 + 6) = uVar11;
    local_368[lVar42 + -8] = uVar41;
    local_60 = local_60 + 1;
LAB_011c6630:
    FUN_011c97a0(&local_170,puVar40,local_78);
    plVar26 = local_78;
    if ((char)local_168 == '\0') {
LAB_011c6950:
      plVar32 = (long *)((long)plVar26 - (long)plVar32);
      if (local_1b0 == plVar32) {
        local_538 = PTR_PTR_0100ee68;
        cStack_530 = (char)_UNK_0100ee70;
        uStack_52f = (undefined1)((ulong)_UNK_0100ee70 >> 8);
        uStack_52e = (undefined6)((ulong)_UNK_0100ee70 >> 0x10);
        uStack_528 = (undefined2)_UNK_0100ee78;
        uStack_526 = (undefined6)((ulong)_UNK_0100ee78 >> 0x10);
        uStack_520 = (undefined2)_UNK_0100ee80;
        uStack_51e = (undefined2)((ulong)_UNK_0100ee80 >> 0x10);
        uStack_51c = (uint)((ulong)_UNK_0100ee80 >> 0x20);
        plVar32 = &local_180;
        do {
          (*(code *)*local_1c0)(plVar32,&local_1c0,&local_538,1);
          uVar16 = (uint)local_178;
        } while (local_178 == 0);
        if (1 < local_178 - 0x14) {
          uVar16 = 0x72;
        }
      }
      else if ((plVar26 < local_1b0) ||
              (uVar16 = (*(code *)local_1c0[3])(&local_1c0,(undefined *)((long)plVar32 + 1)),
              (short)uVar16 == 0)) {
        local_138 = "";
        uStack_130 = 0;
        (*(code *)local_1c0[2])(&local_e8,&local_1c0,&local_138,1);
        puVar40 = local_1b8;
        uVar16 = (uint)uStack_e0 & 0xffff;
        if ((short)uStack_e0 == 0) goto code_r0x011c69b9;
      }
      local_3a8._8_8_ = local_100;
      local_3a8._0_8_ = local_60;
      local_398._8_4_ = (undefined4)local_70;
      local_398._4_4_ = local_90._0_4_;
      local_398._0_4_ = local_88._0_4_;
      if ((short)uVar16 == 0x14) goto LAB_011c6b31;
      goto LAB_011c6bac;
    }
    local_38 = (undefined *)((long)puVar40 + (long)plVar32);
    puVar17 = local_170 + -(long)plVar32;
    goto LAB_011c5d90;
  }
LAB_011c680f:
  local_170 = (undefined *)CONCAT71(local_170._1_7_,1);
  FUN_011c9bc0(&local_538,puVar17);
  if (local_518 == '\0') {
    plVar32 = (long *)CONCAT62(uStack_52e,CONCAT11(uStack_52f,cStack_530));
    local_e8 = (char *)CONCAT62(uStack_526,uStack_528);
    uStack_e0 = CONCAT44(uStack_51c,CONCAT22(uStack_51e,uStack_520));
    if (local_538 == (undefined *)0x0) {
      lVar42 = 0;
      plVar32 = local_108;
LAB_011c68c2:
      local_128 = 0;
      uStack_126 = 0;
      uStack_124 = (ushort)lVar42;
      uStack_122 = (undefined2)((ulong)lVar42 >> 0x10);
      local_138 = local_e8;
      uStack_130 = uStack_e0;
      iVar21 = (uint)uStack_124 << 0x10;
      uVar24 = 0;
      ppuVar35 = &local_170;
      uVar15 = uStack_122;
      goto LAB_011c68f4;
    }
    if (plVar32 < (long *)0x10) {
      FUN_011f4580(&local_210,local_538,plVar32);
      *(undefined1 *)((long)&local_210 + (long)plVar32) = 0;
      FUN_011c7e40(&local_180);
      uVar16 = (uint)((ulong)local_180 >> 0x20);
      if ((short)((ulong)local_180 >> 0x20) == 0) {
        local_78 = (long *)local_1a8._8_8_;
        lVar42 = local_180;
        plVar32 = (long *)local_1a8._0_8_;
        puVar40 = local_1b8;
        goto LAB_011c68c2;
      }
    }
    else {
      uVar16 = 0x31;
    }
  }
  else {
    uVar16 = 0x6c;
  }
  local_3a8._8_8_ = local_100;
  local_3a8._0_8_ = local_60;
  local_398._8_4_ = (undefined4)local_70;
  local_398._4_4_ = local_90._0_4_;
  local_398._0_4_ = local_88._0_4_;
LAB_011c6bac:
  uVar25 = (ushort)uVar16;
  if (uVar25 == 0) {
LAB_011c6bb5:
    syscall();
LAB_011c6bc0:
    FUN_011f4580(&local_538,local_3a8,0x180);
LAB_011c6bd8:
    FUN_011f4580(&local_870,&local_538,0x180);
    if (local_f8 < 0x20) {
      lVar42 = 0;
      uVar22 = 0;
      in_R11 = local_f8;
    }
    else {
      uVar39 = (local_f8 - 0x20 >> 5) + 1;
      uVar29 = (ulong)((uint)uVar39 & 7);
      if (local_f8 - 0x20 < 0xe0) {
        uVar22 = 0;
        lVar42 = 0;
      }
      else {
        uVar39 = uVar39 & 0xfffffffffffffff8;
        uVar22 = 0;
        auVar48._4_4_ = DAT_01001480;
        auVar48._0_4_ = DAT_01001480;
        auVar48._8_4_ = DAT_01001480;
        auVar48._12_4_ = DAT_01001480;
        auVar48._16_4_ = DAT_01001480;
        auVar48._20_4_ = DAT_01001480;
        auVar48._24_4_ = DAT_01001480;
        auVar48._28_4_ = DAT_01001480;
        lVar42 = 0;
        do {
          auVar49 = vpcmpeqb_avx2(auVar48,*(undefined1 (*) [32])((long)local_f0 + lVar42));
          auVar3 = vpcmpeqb_avx2(auVar48,*(undefined1 (*) [32])((long)local_f0 + lVar42 + 0x20));
          auVar4 = vpcmpeqb_avx2(auVar48,*(undefined1 (*) [32])((long)local_f0 + lVar42 + 0x40));
          auVar5 = vpcmpeqb_avx2(auVar48,*(undefined1 (*) [32])((long)local_f0 + lVar42 + 0x60));
          auVar6 = vpcmpeqb_avx2(auVar48,*(undefined1 (*) [32])((long)local_f0 + lVar42 + 0x80));
          auVar7 = vpcmpeqb_avx2(auVar48,*(undefined1 (*) [32])((long)local_f0 + lVar42 + 0xa0));
          auVar8 = vpcmpeqb_avx2(auVar48,*(undefined1 (*) [32])((long)local_f0 + lVar42 + 0xc0));
          auVar9 = vpcmpeqb_avx2(auVar48,*(undefined1 (*) [32])((long)local_f0 + lVar42 + 0xe0));
          uVar22 = (ulong)(uint)POPCOUNT((uint)(SUB321(auVar9 >> 7,0) & 1) |
                                         (uint)(SUB321(auVar9 >> 0xf,0) & 1) << 1 |
                                         (uint)(SUB321(auVar9 >> 0x17,0) & 1) << 2 |
                                         (uint)(SUB321(auVar9 >> 0x1f,0) & 1) << 3 |
                                         (uint)(SUB321(auVar9 >> 0x27,0) & 1) << 4 |
                                         (uint)(SUB321(auVar9 >> 0x2f,0) & 1) << 5 |
                                         (uint)(SUB321(auVar9 >> 0x37,0) & 1) << 6 |
                                         (uint)(SUB321(auVar9 >> 0x3f,0) & 1) << 7 |
                                         (uint)(SUB321(auVar9 >> 0x47,0) & 1) << 8 |
                                         (uint)(SUB321(auVar9 >> 0x4f,0) & 1) << 9 |
                                         (uint)(SUB321(auVar9 >> 0x57,0) & 1) << 10 |
                                         (uint)(SUB321(auVar9 >> 0x5f,0) & 1) << 0xb |
                                         (uint)(SUB321(auVar9 >> 0x67,0) & 1) << 0xc |
                                         (uint)(SUB321(auVar9 >> 0x6f,0) & 1) << 0xd |
                                         (uint)(SUB321(auVar9 >> 0x77,0) & 1) << 0xe |
                                         (uint)SUB321(auVar9 >> 0x7f,0) << 0xf |
                                         (uint)(SUB321(auVar9 >> 0x87,0) & 1) << 0x10 |
                                         (uint)(SUB321(auVar9 >> 0x8f,0) & 1) << 0x11 |
                                         (uint)(SUB321(auVar9 >> 0x97,0) & 1) << 0x12 |
                                         (uint)(SUB321(auVar9 >> 0x9f,0) & 1) << 0x13 |
                                         (uint)(SUB321(auVar9 >> 0xa7,0) & 1) << 0x14 |
                                         (uint)(SUB321(auVar9 >> 0xaf,0) & 1) << 0x15 |
                                         (uint)(SUB321(auVar9 >> 0xb7,0) & 1) << 0x16 |
                                         (uint)SUB321(auVar9 >> 0xbf,0) << 0x17 |
                                         (uint)(SUB321(auVar9 >> 199,0) & 1) << 0x18 |
                                         (uint)(SUB321(auVar9 >> 0xcf,0) & 1) << 0x19 |
                                         (uint)(SUB321(auVar9 >> 0xd7,0) & 1) << 0x1a |
                                         (uint)(SUB321(auVar9 >> 0xdf,0) & 1) << 0x1b |
                                         (uint)(SUB321(auVar9 >> 0xe7,0) & 1) << 0x1c |
                                         (uint)(SUB321(auVar9 >> 0xef,0) & 1) << 0x1d |
                                         (uint)(SUB321(auVar9 >> 0xf7,0) & 1) << 0x1e |
                                         (uint)(byte)(auVar9[0x1f] >> 7) << 0x1f) +
                   (ulong)(uint)POPCOUNT((uint)(SUB321(auVar8 >> 7,0) & 1) |
                                         (uint)(SUB321(auVar8 >> 0xf,0) & 1) << 1 |
                                         (uint)(SUB321(auVar8 >> 0x17,0) & 1) << 2 |
                                         (uint)(SUB321(auVar8 >> 0x1f,0) & 1) << 3 |
                                         (uint)(SUB321(auVar8 >> 0x27,0) & 1) << 4 |
                                         (uint)(SUB321(auVar8 >> 0x2f,0) & 1) << 5 |
                                         (uint)(SUB321(auVar8 >> 0x37,0) & 1) << 6 |
                                         (uint)(SUB321(auVar8 >> 0x3f,0) & 1) << 7 |
                                         (uint)(SUB321(auVar8 >> 0x47,0) & 1) << 8 |
                                         (uint)(SUB321(auVar8 >> 0x4f,0) & 1) << 9 |
                                         (uint)(SUB321(auVar8 >> 0x57,0) & 1) << 10 |
                                         (uint)(SUB321(auVar8 >> 0x5f,0) & 1) << 0xb |
                                         (uint)(SUB321(auVar8 >> 0x67,0) & 1) << 0xc |
                                         (uint)(SUB321(auVar8 >> 0x6f,0) & 1) << 0xd |
                                         (uint)(SUB321(auVar8 >> 0x77,0) & 1) << 0xe |
                                         (uint)SUB321(auVar8 >> 0x7f,0) << 0xf |
                                         (uint)(SUB321(auVar8 >> 0x87,0) & 1) << 0x10 |
                                         (uint)(SUB321(auVar8 >> 0x8f,0) & 1) << 0x11 |
                                         (uint)(SUB321(auVar8 >> 0x97,0) & 1) << 0x12 |
                                         (uint)(SUB321(auVar8 >> 0x9f,0) & 1) << 0x13 |
                                         (uint)(SUB321(auVar8 >> 0xa7,0) & 1) << 0x14 |
                                         (uint)(SUB321(auVar8 >> 0xaf,0) & 1) << 0x15 |
                                         (uint)(SUB321(auVar8 >> 0xb7,0) & 1) << 0x16 |
                                         (uint)SUB321(auVar8 >> 0xbf,0) << 0x17 |
                                         (uint)(SUB321(auVar8 >> 199,0) & 1) << 0x18 |
                                         (uint)(SUB321(auVar8 >> 0xcf,0) & 1) << 0x19 |
                                         (uint)(SUB321(auVar8 >> 0xd7,0) & 1) << 0x1a |
                                         (uint)(SUB321(auVar8 >> 0xdf,0) & 1) << 0x1b |
                                         (uint)(SUB321(auVar8 >> 0xe7,0) & 1) << 0x1c |
                                         (uint)(SUB321(auVar8 >> 0xef,0) & 1) << 0x1d |
                                         (uint)(SUB321(auVar8 >> 0xf7,0) & 1) << 0x1e |
                                         (uint)(byte)(auVar8[0x1f] >> 7) << 0x1f) +
                   (ulong)(uint)POPCOUNT((uint)(SUB321(auVar7 >> 7,0) & 1) |
                                         (uint)(SUB321(auVar7 >> 0xf,0) & 1) << 1 |
                                         (uint)(SUB321(auVar7 >> 0x17,0) & 1) << 2 |
                                         (uint)(SUB321(auVar7 >> 0x1f,0) & 1) << 3 |
                                         (uint)(SUB321(auVar7 >> 0x27,0) & 1) << 4 |
                                         (uint)(SUB321(auVar7 >> 0x2f,0) & 1) << 5 |
                                         (uint)(SUB321(auVar7 >> 0x37,0) & 1) << 6 |
                                         (uint)(SUB321(auVar7 >> 0x3f,0) & 1) << 7 |
                                         (uint)(SUB321(auVar7 >> 0x47,0) & 1) << 8 |
                                         (uint)(SUB321(auVar7 >> 0x4f,0) & 1) << 9 |
                                         (uint)(SUB321(auVar7 >> 0x57,0) & 1) << 10 |
                                         (uint)(SUB321(auVar7 >> 0x5f,0) & 1) << 0xb |
                                         (uint)(SUB321(auVar7 >> 0x67,0) & 1) << 0xc |
                                         (uint)(SUB321(auVar7 >> 0x6f,0) & 1) << 0xd |
                                         (uint)(SUB321(auVar7 >> 0x77,0) & 1) << 0xe |
                                         (uint)SUB321(auVar7 >> 0x7f,0) << 0xf |
                                         (uint)(SUB321(auVar7 >> 0x87,0) & 1) << 0x10 |
                                         (uint)(SUB321(auVar7 >> 0x8f,0) & 1) << 0x11 |
                                         (uint)(SUB321(auVar7 >> 0x97,0) & 1) << 0x12 |
                                         (uint)(SUB321(auVar7 >> 0x9f,0) & 1) << 0x13 |
                                         (uint)(SUB321(auVar7 >> 0xa7,0) & 1) << 0x14 |
                                         (uint)(SUB321(auVar7 >> 0xaf,0) & 1) << 0x15 |
                                         (uint)(SUB321(auVar7 >> 0xb7,0) & 1) << 0x16 |
                                         (uint)SUB321(auVar7 >> 0xbf,0) << 0x17 |
                                         (uint)(SUB321(auVar7 >> 199,0) & 1) << 0x18 |
                                         (uint)(SUB321(auVar7 >> 0xcf,0) & 1) << 0x19 |
                                         (uint)(SUB321(auVar7 >> 0xd7,0) & 1) << 0x1a |
                                         (uint)(SUB321(auVar7 >> 0xdf,0) & 1) << 0x1b |
                                         (uint)(SUB321(auVar7 >> 0xe7,0) & 1) << 0x1c |
                                         (uint)(SUB321(auVar7 >> 0xef,0) & 1) << 0x1d |
                                         (uint)(SUB321(auVar7 >> 0xf7,0) & 1) << 0x1e |
                                         (uint)(byte)(auVar7[0x1f] >> 7) << 0x1f) +
                   (ulong)(uint)POPCOUNT((uint)(SUB321(auVar6 >> 7,0) & 1) |
                                         (uint)(SUB321(auVar6 >> 0xf,0) & 1) << 1 |
                                         (uint)(SUB321(auVar6 >> 0x17,0) & 1) << 2 |
                                         (uint)(SUB321(auVar6 >> 0x1f,0) & 1) << 3 |
                                         (uint)(SUB321(auVar6 >> 0x27,0) & 1) << 4 |
                                         (uint)(SUB321(auVar6 >> 0x2f,0) & 1) << 5 |
                                         (uint)(SUB321(auVar6 >> 0x37,0) & 1) << 6 |
                                         (uint)(SUB321(auVar6 >> 0x3f,0) & 1) << 7 |
                                         (uint)(SUB321(auVar6 >> 0x47,0) & 1) << 8 |
                                         (uint)(SUB321(auVar6 >> 0x4f,0) & 1) << 9 |
                                         (uint)(SUB321(auVar6 >> 0x57,0) & 1) << 10 |
                                         (uint)(SUB321(auVar6 >> 0x5f,0) & 1) << 0xb |
                                         (uint)(SUB321(auVar6 >> 0x67,0) & 1) << 0xc |
                                         (uint)(SUB321(auVar6 >> 0x6f,0) & 1) << 0xd |
                                         (uint)(SUB321(auVar6 >> 0x77,0) & 1) << 0xe |
                                         (uint)SUB321(auVar6 >> 0x7f,0) << 0xf |
                                         (uint)(SUB321(auVar6 >> 0x87,0) & 1) << 0x10 |
                                         (uint)(SUB321(auVar6 >> 0x8f,0) & 1) << 0x11 |
                                         (uint)(SUB321(auVar6 >> 0x97,0) & 1) << 0x12 |
                                         (uint)(SUB321(auVar6 >> 0x9f,0) & 1) << 0x13 |
                                         (uint)(SUB321(auVar6 >> 0xa7,0) & 1) << 0x14 |
                                         (uint)(SUB321(auVar6 >> 0xaf,0) & 1) << 0x15 |
                                         (uint)(SUB321(auVar6 >> 0xb7,0) & 1) << 0x16 |
                                         (uint)SUB321(auVar6 >> 0xbf,0) << 0x17 |
                                         (uint)(SUB321(auVar6 >> 199,0) & 1) << 0x18 |
                                         (uint)(SUB321(auVar6 >> 0xcf,0) & 1) << 0x19 |
                                         (uint)(SUB321(auVar6 >> 0xd7,0) & 1) << 0x1a |
                                         (uint)(SUB321(auVar6 >> 0xdf,0) & 1) << 0x1b |
                                         (uint)(SUB321(auVar6 >> 0xe7,0) & 1) << 0x1c |
                                         (uint)(SUB321(auVar6 >> 0xef,0) & 1) << 0x1d |
                                         (uint)(SUB321(auVar6 >> 0xf7,0) & 1) << 0x1e |
                                         (uint)(byte)(auVar6[0x1f] >> 7) << 0x1f) +
                   (ulong)(uint)POPCOUNT((uint)(SUB321(auVar5 >> 7,0) & 1) |
                                         (uint)(SUB321(auVar5 >> 0xf,0) & 1) << 1 |
                                         (uint)(SUB321(auVar5 >> 0x17,0) & 1) << 2 |
                                         (uint)(SUB321(auVar5 >> 0x1f,0) & 1) << 3 |
                                         (uint)(SUB321(auVar5 >> 0x27,0) & 1) << 4 |
                                         (uint)(SUB321(auVar5 >> 0x2f,0) & 1) << 5 |
                                         (uint)(SUB321(auVar5 >> 0x37,0) & 1) << 6 |
                                         (uint)(SUB321(auVar5 >> 0x3f,0) & 1) << 7 |
                                         (uint)(SUB321(auVar5 >> 0x47,0) & 1) << 8 |
                                         (uint)(SUB321(auVar5 >> 0x4f,0) & 1) << 9 |
                                         (uint)(SUB321(auVar5 >> 0x57,0) & 1) << 10 |
                                         (uint)(SUB321(auVar5 >> 0x5f,0) & 1) << 0xb |
                                         (uint)(SUB321(auVar5 >> 0x67,0) & 1) << 0xc |
                                         (uint)(SUB321(auVar5 >> 0x6f,0) & 1) << 0xd |
                                         (uint)(SUB321(auVar5 >> 0x77,0) & 1) << 0xe |
                                         (uint)SUB321(auVar5 >> 0x7f,0) << 0xf |
                                         (uint)(SUB321(auVar5 >> 0x87,0) & 1) << 0x10 |
                                         (uint)(SUB321(auVar5 >> 0x8f,0) & 1) << 0x11 |
                                         (uint)(SUB321(auVar5 >> 0x97,0) & 1) << 0x12 |
                                         (uint)(SUB321(auVar5 >> 0x9f,0) & 1) << 0x13 |
                                         (uint)(SUB321(auVar5 >> 0xa7,0) & 1) << 0x14 |
                                         (uint)(SUB321(auVar5 >> 0xaf,0) & 1) << 0x15 |
                                         (uint)(SUB321(auVar5 >> 0xb7,0) & 1) << 0x16 |
                                         (uint)SUB321(auVar5 >> 0xbf,0) << 0x17 |
                                         (uint)(SUB321(auVar5 >> 199,0) & 1) << 0x18 |
                                         (uint)(SUB321(auVar5 >> 0xcf,0) & 1) << 0x19 |
                                         (uint)(SUB321(auVar5 >> 0xd7,0) & 1) << 0x1a |
                                         (uint)(SUB321(auVar5 >> 0xdf,0) & 1) << 0x1b |
                                         (uint)(SUB321(auVar5 >> 0xe7,0) & 1) << 0x1c |
                                         (uint)(SUB321(auVar5 >> 0xef,0) & 1) << 0x1d |
                                         (uint)(SUB321(auVar5 >> 0xf7,0) & 1) << 0x1e |
                                         (uint)(byte)(auVar5[0x1f] >> 7) << 0x1f) +
                   (ulong)(uint)POPCOUNT((uint)(SUB321(auVar4 >> 7,0) & 1) |
                                         (uint)(SUB321(auVar4 >> 0xf,0) & 1) << 1 |
                                         (uint)(SUB321(auVar4 >> 0x17,0) & 1) << 2 |
                                         (uint)(SUB321(auVar4 >> 0x1f,0) & 1) << 3 |
                                         (uint)(SUB321(auVar4 >> 0x27,0) & 1) << 4 |
                                         (uint)(SUB321(auVar4 >> 0x2f,0) & 1) << 5 |
                                         (uint)(SUB321(auVar4 >> 0x37,0) & 1) << 6 |
                                         (uint)(SUB321(auVar4 >> 0x3f,0) & 1) << 7 |
                                         (uint)(SUB321(auVar4 >> 0x47,0) & 1) << 8 |
                                         (uint)(SUB321(auVar4 >> 0x4f,0) & 1) << 9 |
                                         (uint)(SUB321(auVar4 >> 0x57,0) & 1) << 10 |
                                         (uint)(SUB321(auVar4 >> 0x5f,0) & 1) << 0xb |
                                         (uint)(SUB321(auVar4 >> 0x67,0) & 1) << 0xc |
                                         (uint)(SUB321(auVar4 >> 0x6f,0) & 1) << 0xd |
                                         (uint)(SUB321(auVar4 >> 0x77,0) & 1) << 0xe |
                                         (uint)SUB321(auVar4 >> 0x7f,0) << 0xf |
                                         (uint)(SUB321(auVar4 >> 0x87,0) & 1) << 0x10 |
                                         (uint)(SUB321(auVar4 >> 0x8f,0) & 1) << 0x11 |
                                         (uint)(SUB321(auVar4 >> 0x97,0) & 1) << 0x12 |
                                         (uint)(SUB321(auVar4 >> 0x9f,0) & 1) << 0x13 |
                                         (uint)(SUB321(auVar4 >> 0xa7,0) & 1) << 0x14 |
                                         (uint)(SUB321(auVar4 >> 0xaf,0) & 1) << 0x15 |
                                         (uint)(SUB321(auVar4 >> 0xb7,0) & 1) << 0x16 |
                                         (uint)SUB321(auVar4 >> 0xbf,0) << 0x17 |
                                         (uint)(SUB321(auVar4 >> 199,0) & 1) << 0x18 |
                                         (uint)(SUB321(auVar4 >> 0xcf,0) & 1) << 0x19 |
                                         (uint)(SUB321(auVar4 >> 0xd7,0) & 1) << 0x1a |
                                         (uint)(SUB321(auVar4 >> 0xdf,0) & 1) << 0x1b |
                                         (uint)(SUB321(auVar4 >> 0xe7,0) & 1) << 0x1c |
                                         (uint)(SUB321(auVar4 >> 0xef,0) & 1) << 0x1d |
                                         (uint)(SUB321(auVar4 >> 0xf7,0) & 1) << 0x1e |
                                         (uint)(byte)(auVar4[0x1f] >> 7) << 0x1f) +
                   (ulong)(uint)POPCOUNT((uint)(SUB321(auVar3 >> 7,0) & 1) |
                                         (uint)(SUB321(auVar3 >> 0xf,0) & 1) << 1 |
                                         (uint)(SUB321(auVar3 >> 0x17,0) & 1) << 2 |
                                         (uint)(SUB321(auVar3 >> 0x1f,0) & 1) << 3 |
                                         (uint)(SUB321(auVar3 >> 0x27,0) & 1) << 4 |
                                         (uint)(SUB321(auVar3 >> 0x2f,0) & 1) << 5 |
                                         (uint)(SUB321(auVar3 >> 0x37,0) & 1) << 6 |
                                         (uint)(SUB321(auVar3 >> 0x3f,0) & 1) << 7 |
                                         (uint)(SUB321(auVar3 >> 0x47,0) & 1) << 8 |
                                         (uint)(SUB321(auVar3 >> 0x4f,0) & 1) << 9 |
                                         (uint)(SUB321(auVar3 >> 0x57,0) & 1) << 10 |
                                         (uint)(SUB321(auVar3 >> 0x5f,0) & 1) << 0xb |
                                         (uint)(SUB321(auVar3 >> 0x67,0) & 1) << 0xc |
                                         (uint)(SUB321(auVar3 >> 0x6f,0) & 1) << 0xd |
                                         (uint)(SUB321(auVar3 >> 0x77,0) & 1) << 0xe |
                                         (uint)SUB321(auVar3 >> 0x7f,0) << 0xf |
                                         (uint)(SUB321(auVar3 >> 0x87,0) & 1) << 0x10 |
                                         (uint)(SUB321(auVar3 >> 0x8f,0) & 1) << 0x11 |
                                         (uint)(SUB321(auVar3 >> 0x97,0) & 1) << 0x12 |
                                         (uint)(SUB321(auVar3 >> 0x9f,0) & 1) << 0x13 |
                                         (uint)(SUB321(auVar3 >> 0xa7,0) & 1) << 0x14 |
                                         (uint)(SUB321(auVar3 >> 0xaf,0) & 1) << 0x15 |
                                         (uint)(SUB321(auVar3 >> 0xb7,0) & 1) << 0x16 |
                                         (uint)SUB321(auVar3 >> 0xbf,0) << 0x17 |
                                         (uint)(SUB321(auVar3 >> 199,0) & 1) << 0x18 |
                                         (uint)(SUB321(auVar3 >> 0xcf,0) & 1) << 0x19 |
                                         (uint)(SUB321(auVar3 >> 0xd7,0) & 1) << 0x1a |
                                         (uint)(SUB321(auVar3 >> 0xdf,0) & 1) << 0x1b |
                                         (uint)(SUB321(auVar3 >> 0xe7,0) & 1) << 0x1c |
                                         (uint)(SUB321(auVar3 >> 0xef,0) & 1) << 0x1d |
                                         (uint)(SUB321(auVar3 >> 0xf7,0) & 1) << 0x1e |
                                         (uint)(byte)(auVar3[0x1f] >> 7) << 0x1f) +
                   (uint)POPCOUNT((uint)(SUB321(auVar49 >> 7,0) & 1) |
                                  (uint)(SUB321(auVar49 >> 0xf,0) & 1) << 1 |
                                  (uint)(SUB321(auVar49 >> 0x17,0) & 1) << 2 |
                                  (uint)(SUB321(auVar49 >> 0x1f,0) & 1) << 3 |
                                  (uint)(SUB321(auVar49 >> 0x27,0) & 1) << 4 |
                                  (uint)(SUB321(auVar49 >> 0x2f,0) & 1) << 5 |
                                  (uint)(SUB321(auVar49 >> 0x37,0) & 1) << 6 |
                                  (uint)(SUB321(auVar49 >> 0x3f,0) & 1) << 7 |
                                  (uint)(SUB321(auVar49 >> 0x47,0) & 1) << 8 |
                                  (uint)(SUB321(auVar49 >> 0x4f,0) & 1) << 9 |
                                  (uint)(SUB321(auVar49 >> 0x57,0) & 1) << 10 |
                                  (uint)(SUB321(auVar49 >> 0x5f,0) & 1) << 0xb |
                                  (uint)(SUB321(auVar49 >> 0x67,0) & 1) << 0xc |
                                  (uint)(SUB321(auVar49 >> 0x6f,0) & 1) << 0xd |
                                  (uint)(SUB321(auVar49 >> 0x77,0) & 1) << 0xe |
                                  (uint)SUB321(auVar49 >> 0x7f,0) << 0xf |
                                  (uint)(SUB321(auVar49 >> 0x87,0) & 1) << 0x10 |
                                  (uint)(SUB321(auVar49 >> 0x8f,0) & 1) << 0x11 |
                                  (uint)(SUB321(auVar49 >> 0x97,0) & 1) << 0x12 |
                                  (uint)(SUB321(auVar49 >> 0x9f,0) & 1) << 0x13 |
                                  (uint)(SUB321(auVar49 >> 0xa7,0) & 1) << 0x14 |
                                  (uint)(SUB321(auVar49 >> 0xaf,0) & 1) << 0x15 |
                                  (uint)(SUB321(auVar49 >> 0xb7,0) & 1) << 0x16 |
                                  (uint)SUB321(auVar49 >> 0xbf,0) << 0x17 |
                                  (uint)(SUB321(auVar49 >> 199,0) & 1) << 0x18 |
                                  (uint)(SUB321(auVar49 >> 0xcf,0) & 1) << 0x19 |
                                  (uint)(SUB321(auVar49 >> 0xd7,0) & 1) << 0x1a |
                                  (uint)(SUB321(auVar49 >> 0xdf,0) & 1) << 0x1b |
                                  (uint)(SUB321(auVar49 >> 0xe7,0) & 1) << 0x1c |
                                  (uint)(SUB321(auVar49 >> 0xef,0) & 1) << 0x1d |
                                  (uint)(SUB321(auVar49 >> 0xf7,0) & 1) << 0x1e |
                                  (uint)(byte)(auVar49[0x1f] >> 7) << 0x1f) + uVar22;
          lVar42 = lVar42 + 0x100;
          uVar39 = uVar39 - 8;
        } while (uVar39 != 0);
        in_R11 = local_f8 - lVar42;
      }
      if (uVar29 != 0) {
        auVar49._4_4_ = DAT_01001480;
        auVar49._0_4_ = DAT_01001480;
        auVar49._8_4_ = DAT_01001480;
        auVar49._12_4_ = DAT_01001480;
        auVar49._16_4_ = DAT_01001480;
        auVar49._20_4_ = DAT_01001480;
        auVar49._24_4_ = DAT_01001480;
        auVar49._28_4_ = DAT_01001480;
        do {
          auVar48 = vpcmpeqb_avx2(auVar49,*(undefined1 (*) [32])((long)local_f0 + lVar42));
          uVar22 = uVar22 + (uint)POPCOUNT((uint)(SUB321(auVar48 >> 7,0) & 1) |
                                           (uint)(SUB321(auVar48 >> 0xf,0) & 1) << 1 |
                                           (uint)(SUB321(auVar48 >> 0x17,0) & 1) << 2 |
                                           (uint)(SUB321(auVar48 >> 0x1f,0) & 1) << 3 |
                                           (uint)(SUB321(auVar48 >> 0x27,0) & 1) << 4 |
                                           (uint)(SUB321(auVar48 >> 0x2f,0) & 1) << 5 |
                                           (uint)(SUB321(auVar48 >> 0x37,0) & 1) << 6 |
                                           (uint)(SUB321(auVar48 >> 0x3f,0) & 1) << 7 |
                                           (uint)(SUB321(auVar48 >> 0x47,0) & 1) << 8 |
                                           (uint)(SUB321(auVar48 >> 0x4f,0) & 1) << 9 |
                                           (uint)(SUB321(auVar48 >> 0x57,0) & 1) << 10 |
                                           (uint)(SUB321(auVar48 >> 0x5f,0) & 1) << 0xb |
                                           (uint)(SUB321(auVar48 >> 0x67,0) & 1) << 0xc |
                                           (uint)(SUB321(auVar48 >> 0x6f,0) & 1) << 0xd |
                                           (uint)(SUB321(auVar48 >> 0x77,0) & 1) << 0xe |
                                           (uint)SUB321(auVar48 >> 0x7f,0) << 0xf |
                                           (uint)(SUB321(auVar48 >> 0x87,0) & 1) << 0x10 |
                                           (uint)(SUB321(auVar48 >> 0x8f,0) & 1) << 0x11 |
                                           (uint)(SUB321(auVar48 >> 0x97,0) & 1) << 0x12 |
                                           (uint)(SUB321(auVar48 >> 0x9f,0) & 1) << 0x13 |
                                           (uint)(SUB321(auVar48 >> 0xa7,0) & 1) << 0x14 |
                                           (uint)(SUB321(auVar48 >> 0xaf,0) & 1) << 0x15 |
                                           (uint)(SUB321(auVar48 >> 0xb7,0) & 1) << 0x16 |
                                           (uint)SUB321(auVar48 >> 0xbf,0) << 0x17 |
                                           (uint)(SUB321(auVar48 >> 199,0) & 1) << 0x18 |
                                           (uint)(SUB321(auVar48 >> 0xcf,0) & 1) << 0x19 |
                                           (uint)(SUB321(auVar48 >> 0xd7,0) & 1) << 0x1a |
                                           (uint)(SUB321(auVar48 >> 0xdf,0) & 1) << 0x1b |
                                           (uint)(SUB321(auVar48 >> 0xe7,0) & 1) << 0x1c |
                                           (uint)(SUB321(auVar48 >> 0xef,0) & 1) << 0x1d |
                                           (uint)(SUB321(auVar48 >> 0xf7,0) & 1) << 0x1e |
                                           (uint)(byte)(auVar48[0x1f] >> 7) << 0x1f);
          lVar42 = lVar42 + 0x20;
          uVar29 = uVar29 - 1;
        } while (uVar29 != 0);
        in_R11 = local_f8 - lVar42;
      }
    }
    if (in_R11 != 0) {
      uVar29 = (ulong)((uint)in_R11 & 7);
      if (in_R11 < 8) {
        uVar39 = 0;
      }
      else {
        uVar39 = 0;
        do {
          uVar22 = (ulong)(*(char *)((long)local_f0 + uVar39 + lVar42 + 7) == '.') +
                   (ulong)(*(char *)((long)local_f0 + uVar39 + lVar42 + 6) == '.') +
                   (ulong)(*(char *)((long)local_f0 + uVar39 + lVar42 + 5) == '.') +
                   (ulong)(*(char *)((long)local_f0 + uVar39 + lVar42 + 4) == '.') +
                   (ulong)(*(char *)((long)local_f0 + uVar39 + lVar42 + 3) == '.') +
                   (ulong)(*(char *)((long)local_f0 + uVar39 + lVar42 + 2) == '.') +
                   (ulong)(*(char *)((long)local_f0 + uVar39 + lVar42 + 1) == '.') +
                   (*(char *)((long)local_f0 + uVar39 + lVar42) == '.') + uVar22;
          uVar39 = uVar39 + 8;
        } while ((in_R11 & 0xfffffffffffffff8) != uVar39);
      }
      if (uVar29 != 0) {
        uVar36 = 0;
        do {
          uVar22 = uVar22 + (*(char *)((long)local_f0 + uVar36 + lVar42 + uVar39) == '.');
          uVar36 = uVar36 + 1;
        } while (uVar29 != uVar36);
      }
    }
    if (uVar22 < uStack_85c) {
      if (local_f8 == 0) {
        uVar29 = CONCAT62(uStack_866,local_868);
      }
      else {
        pcVar27 = (char *)((long)local_f0 + (local_f8 - 1));
        if ((pcVar27 == ".") || (*pcVar27 == '.')) goto joined_r0x011c6eac;
        uVar29 = CONCAT62(uStack_866,local_868);
        pcVar27 = (char *)((long)local_f0 + (local_f8 - 1));
        if (pcVar27 == ".") goto LAB_011c6e72;
LAB_011c6eae:
        puVar17 = (undefined *)(local_f8 - (*pcVar27 == '.'));
        if (puVar17 != (undefined *)0x0) goto LAB_011c6ebe;
      }
LAB_011c6ef2:
      local_38 = (undefined *)0x0;
    }
    else {
      uVar29 = 0;
      local_38 = (undefined *)0x0;
      if (local_f8 != 0) {
joined_r0x011c6eac:
        pcVar27 = (char *)((long)local_f0 + (local_f8 - 1));
        uVar29 = 0;
        if (pcVar27 != ".") goto LAB_011c6eae;
LAB_011c6e72:
        puVar17 = (undefined *)(local_f8 - 1);
        if (puVar17 == (undefined *)0x0) goto LAB_011c6ef2;
LAB_011c6ebe:
        uVar22 = CONCAT62((int6)(local_f8 >> 0x10),0x60);
        if (((undefined *)((long)local_f0 + (long)puVar17) + -1 == ".") ||
           (local_38 = puVar17, ((undefined *)((long)local_f0 + (long)puVar17))[-1] == '.'))
        goto LAB_011c71d8;
      }
    }
    puVar17 = local_38;
    puVar31 = local_3a8;
    if (local_140 != (undefined *)0x0) {
      puVar31 = local_140;
    }
    FUN_011f4580(puVar31,local_f0,local_38);
    puVar31[(long)puVar17] = 0x2e;
    local_118 = puVar17 + 1;
    plVar32 = (long *)(puVar31 + (long)puVar17 + 1);
    uVar39 = 0;
    if (uVar29 == 0) goto LAB_011c7137;
    do {
      while ((local_7f4[uVar39] != ' ' && (local_7f4[uVar39] != '\t'))) {
LAB_011c7137:
        do {
          if (uVar39 == uVar29) goto LAB_011c7215;
          uVar22 = uVar39;
          uVar36 = uVar39;
          if (uVar39 < uVar29) {
            do {
              uVar22 = uVar36;
              if ((local_7f4[uVar36] == '\t') || (local_7f4[uVar36] == ' ')) break;
              uVar36 = uVar36 + 1;
              uVar22 = uVar29;
            } while (uVar29 != uVar36);
          }
          lVar42 = uVar22 - uVar39;
          if (local_7f4 + uVar39 == (char *)0x0) goto LAB_011c7215;
          local_78 = plVar32;
          FUN_011f4580(plVar32,local_7f4 + uVar39,lVar42);
          local_110 = puVar31;
          uVar16 = FUN_011c8210(local_68,puVar31,local_118 + lVar42,&local_870,local_58,local_148);
          if (((short)uVar16 != 0x66) && (uVar22 = (ulong)uVar16, (uVar16 & 0xffff) != 0x60))
          goto LAB_011c71d8;
          uVar39 = uVar39 + lVar42;
          puVar31 = local_110;
          plVar32 = local_78;
        } while (uVar29 <= uVar39);
      }
      uVar39 = uVar39 + 1;
    } while (uVar29 != uVar39);
LAB_011c7215:
    uVar16 = FUN_011c8210(local_68,puVar31,local_38,&local_870,local_58,local_148);
    uVar22 = (ulong)uVar16;
  }
  else {
    if ((uVar16 & 0xffff) == 0x15) {
      syscall();
      uVar25 = (ushort)local_190;
    }
    else {
LAB_011c70e8:
      syscall();
    }
LAB_011c70f3:
    uVar22 = CONCAT62((int6)((ulong)plVar32 >> 0x10),0x61);
    if (uVar25 == 0) goto LAB_011c6bd8;
  }
LAB_011c71d8:
  puVar17 = local_68;
  if ((short)uVar22 == 0) {
LAB_011c71e1:
    plVar32 = local_558;
    uVar22 = 0;
  }
  else {
LAB_011c4fc6:
    plVar32 = local_548;
  }
LAB_011c71ea:
  *plVar32 = (long)puVar17;
  plVar32[1] = (long)&PTR_FUN_0100e020;
  FUN_011c7240(local_58);
  return uVar22 & 0xffffffff;
}


// ---- FUN_011c7240 @ 011c7240

void FUN_011c7240(long param_1,undefined8 *param_2)

{
  int *piVar1;
  int iVar2;
  undefined8 uVar3;
  long lVar4;
  long lVar5;
  int iVar6;
  bool bVar7;
  
  uVar3 = *param_2;
  lVar4 = param_2[1];
  LOCK();
  iVar6 = *(int *)(param_1 + 0x40);
  bVar7 = iVar6 == 0;
  if (bVar7) {
    *(int *)(param_1 + 0x40) = 1;
    iVar6 = 0;
  }
  UNLOCK();
  piVar1 = (int *)(param_1 + 0x40);
  if (!bVar7) {
    if (iVar6 == 2) goto LAB_011c73b4;
    while( true ) {
      LOCK();
      iVar6 = *piVar1;
      *piVar1 = 2;
      UNLOCK();
      if (iVar6 == 0) break;
LAB_011c73b4:
      (**(code **)(lVar4 + 0x68))(uVar3,piVar1,2);
    }
  }
  *(undefined1 *)(param_1 + 0x44) = 1;
  for (lVar4 = *(long *)(param_1 + 0x30); lVar4 != 0; lVar4 = *(long *)(lVar4 + 8)) {
    uVar3 = *param_2;
    lVar5 = param_2[1];
    iVar6 = *(int *)(lVar4 + 0x10);
    if ((ushort)((uint)iVar6 >> 0x10) < (ushort)iVar6) {
      do {
        LOCK();
        iVar2 = *(int *)(lVar4 + 0x10);
        bVar7 = iVar6 == iVar2;
        if (bVar7) {
          *(int *)(lVar4 + 0x10) = iVar6 + 0x10000;
          iVar2 = iVar6;
        }
        iVar6 = iVar2;
        UNLOCK();
        if (bVar7) {
          LOCK();
          *(int *)(lVar4 + 0x14) = *(int *)(lVar4 + 0x14) + 1;
          UNLOCK();
          (**(code **)(lVar5 + 0x70))(uVar3,lVar4 + 0x14,1);
          break;
        }
      } while ((ushort)((uint)iVar6 >> 0x10) < (ushort)iVar6);
    }
  }
  lVar4 = *(long *)(param_1 + 0x20);
  do {
    if (lVar4 == 0) {
      uVar3 = *param_2;
      lVar4 = param_2[1];
      LOCK();
      iVar6 = *piVar1;
      *piVar1 = 0;
      UNLOCK();
      if (iVar6 != 2) {
        return;
      }
                    /* WARNING: Could not recover jumptable at 0x011c73b2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(lVar4 + 0x70))(uVar3,piVar1,1);
      return;
    }
    uVar3 = *param_2;
    lVar5 = param_2[1];
    iVar6 = *(int *)(lVar4 + 0x10);
    if ((ushort)((uint)iVar6 >> 0x10) < (ushort)iVar6) {
      do {
        LOCK();
        iVar2 = *(int *)(lVar4 + 0x10);
        bVar7 = iVar6 == iVar2;
        if (bVar7) {
          *(int *)(lVar4 + 0x10) = iVar6 + 0x10000;
          iVar2 = iVar6;
        }
        iVar6 = iVar2;
        UNLOCK();
        if (bVar7) {
          LOCK();
          *(int *)(lVar4 + 0x14) = *(int *)(lVar4 + 0x14) + 1;
          UNLOCK();
          (**(code **)(lVar5 + 0x70))(uVar3,lVar4 + 0x14,1);
          break;
        }
      } while ((ushort)((uint)iVar6 >> 0x10) < (ushort)iVar6);
    }
    lVar4 = *(long *)(lVar4 + 8);
  } while( true );
}


// ---- FUN_011c73e0 @ 011c73e0

undefined1  [16] FUN_011c73e0(void)

{
  syscall();
  return ZEXT816(0xd);
}


// ---- FUN_011c7430 @ 011c7430

undefined1  [16] FUN_011c7430(void)

{
  syscall();
  syscall();
  syscall();
  syscall();
  syscall();
  return ZEXT816(0xe);
}


// ---- FUN_011c7440 @ 011c7440

undefined1  [16] FUN_011c7440(void)

{
  syscall();
  syscall();
  syscall();
  syscall();
  return ZEXT816(0xe);
}


// ---- FUN_011c74a0 @ 011c74a0

void FUN_011c74a0(undefined8 *param_1,ulong param_2)

{
  long lVar1;
  ulong uVar2;
  undefined *local_70;
  undefined **local_68;
  undefined1 local_60 [16];
  long local_50;
  short local_48;
  char *local_40;
  long local_38;
  
  if ((param_2 & 3) != 0) {
    uVar2 = 0;
    do {
      while( true ) {
        lVar1 = 4 - uVar2;
        if ((ulong)(param_1[3] + lVar1) <= (ulong)param_1[2]) break;
        local_40 = &DAT_011b8b30 + uVar2;
        local_38 = lVar1;
        (**(code **)*param_1)(&local_50,param_1,&local_40,1,1);
        if ((local_48 != 0) || (uVar2 = uVar2 + local_50, 3 < uVar2)) goto LAB_011c7542;
      }
      FUN_011f4580(param_1[3] + param_1[1],&DAT_011b8b30 + uVar2,lVar1);
      param_1[3] = param_1[3] + lVar1;
      uVar2 = uVar2 + lVar1;
    } while (uVar2 < 4);
  }
LAB_011c7542:
  uVar2 = 0;
  do {
    while( true ) {
      lVar1 = 0x34 - uVar2;
      if ((ulong)param_1[2] < (ulong)(param_1[3] + lVar1)) break;
      FUN_011f4580(param_1[3] + param_1[1],
                   "Cannot print stack trace: stack tracing is disabled\n" + uVar2,lVar1);
      param_1[3] = param_1[3] + lVar1;
      uVar2 = uVar2 + lVar1;
      if (0x33 < uVar2) goto LAB_011c75c6;
    }
    local_40 = "Cannot print stack trace: stack tracing is disabled\n" + uVar2;
    local_38 = lVar1;
    (**(code **)*param_1)(&local_50,param_1,&local_40,1,1);
    if (local_48 != 0) {
      local_70 = &DAT_011fcf90;
      local_68 = &PTR_FUN_0100eb88;
      local_60._0_12_ = ZEXT812(0);
      local_60._12_4_ = 0;
      FUN_011c7690(&local_70);
      return;
    }
    uVar2 = uVar2 + local_50;
  } while (uVar2 < 0x34);
LAB_011c75c6:
  if ((param_2 & 3) != 0) {
    uVar2 = 0;
    do {
      while( true ) {
        lVar1 = 4 - uVar2;
        if ((ulong)(param_1[3] + lVar1) <= (ulong)param_1[2]) break;
        local_40 = &DAT_011b8b40 + uVar2;
        local_38 = lVar1;
        (**(code **)*param_1)(&local_50,param_1,&local_40,1,1);
        if (local_48 != 0) {
          return;
        }
        uVar2 = uVar2 + local_50;
        if (3 < uVar2) {
          return;
        }
      }
      FUN_011f4580(param_1[3] + param_1[1],&DAT_011b8b40 + uVar2,lVar1);
      param_1[3] = param_1[3] + lVar1;
      uVar2 = uVar2 + lVar1;
    } while (uVar2 < 4);
  }
  return;
}


// ---- FUN_011c7690 @ 011c7690

void FUN_011c7690(undefined8 *param_1)

{
  undefined8 uVar1;
  long lVar2;
  ulong *puVar3;
  ulong *puVar4;
  ulong *puVar5;
  undefined8 unaff_retaddr;
  
  uVar1 = *param_1;
  lVar2 = param_1[1];
  puVar3 = (ulong *)param_1[3];
  puVar5 = (ulong *)param_1[2];
  while (puVar5 != (ulong *)0x0) {
    puVar4 = (ulong *)puVar5[2];
    (**(code **)(lVar2 + 0x18))(uVar1,puVar5,*puVar5 & 0xfffffffffffffffe,3,unaff_retaddr);
    puVar5 = puVar4;
  }
  while (puVar3 != (ulong *)0x0) {
    puVar5 = (ulong *)puVar3[2];
    (**(code **)(lVar2 + 0x18))(uVar1,puVar3,*puVar3 & 0xfffffffffffffffe,3,unaff_retaddr);
    puVar3 = puVar5;
  }
  return;
}


// ---- FUN_011c7730 @ 011c7730

long FUN_011c7730(long param_1,long param_2,long param_3)

{
  long lVar1;
  long lVar2;
  long lVar3;
  
  lVar1 = *(long *)(param_1 + 0x10);
  lVar2 = *(long *)(lVar1 + 8);
  if (lVar1 + lVar2 + 0x18 == param_2 + param_3) {
    LOCK();
    lVar3 = *(long *)(lVar1 + 8);
    if (lVar2 == lVar3) {
      *(long *)(lVar1 + 8) = lVar2 - param_3;
      lVar3 = lVar2;
    }
    UNLOCK();
    return lVar3;
  }
  return lVar2;
}


// ---- FUN_011c7760 @ 011c7760

long FUN_011c7760(long param_1,long param_2,ulong param_3,undefined8 param_4,ulong param_5)

{
  ulong *puVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  bool bVar6;
  
  puVar1 = *(ulong **)(param_1 + 0x10);
  uVar2 = puVar1[1];
  if ((long)puVar1 + uVar2 + 0x18 == param_2 + param_3) {
    uVar5 = param_5 - param_3;
    if (param_5 < param_3 || uVar5 == 0) {
      LOCK();
      if (uVar2 == puVar1[1]) {
        puVar1[1] = uVar5 + uVar2;
      }
      UNLOCK();
      return param_2;
    }
    uVar3 = (*puVar1 & 0xfffffffffffffffe) - 0x18;
    uVar4 = 0;
    if (uVar2 <= uVar3) {
      uVar4 = uVar3 - uVar2;
    }
    if (uVar5 <= uVar4) {
      LOCK();
      bVar6 = uVar2 == puVar1[1];
      if (bVar6) {
        puVar1[1] = uVar5 + uVar2;
      }
      UNLOCK();
      if (bVar6) {
        return param_2;
      }
    }
  }
  else if (param_5 <= param_3) {
    return param_2;
  }
  return 0;
}


// ---- FUN_011c77d0 @ 011c77d0

ulong FUN_011c77d0(long param_1,long param_2,ulong param_3,undefined8 param_4,ulong param_5)

{
  ulong *puVar1;
  ulong uVar2;
  long lVar3;
  undefined7 uVar5;
  ulong uVar4;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  bool bVar9;
  
  puVar1 = *(ulong **)(param_1 + 0x10);
  uVar2 = puVar1[1];
  lVar3 = (long)puVar1 + uVar2 + 0x18;
  uVar5 = (undefined7)((ulong)lVar3 >> 8);
  if (lVar3 == param_2 + param_3) {
    uVar8 = param_5 - param_3;
    if (param_5 < param_3 || uVar8 == 0) {
      LOCK();
      if (uVar2 == puVar1[1]) {
        puVar1[1] = uVar8 + uVar2;
      }
      UNLOCK();
      return CONCAT71(uVar5,1) & 0xffffffff;
    }
    uVar6 = (*puVar1 & 0xfffffffffffffffe) - 0x18;
    uVar4 = 0;
    uVar7 = 0;
    if (uVar2 <= uVar6) {
      uVar7 = uVar6 - uVar2;
    }
    if (uVar8 <= uVar7) {
      LOCK();
      bVar9 = uVar2 == puVar1[1];
      if (bVar9) {
        puVar1[1] = uVar8 + uVar2;
      }
      UNLOCK();
      return (ulong)bVar9;
    }
  }
  else {
    uVar4 = CONCAT71(uVar5,param_5 <= param_3);
  }
  return uVar4 & 0xffffffff;
}


// ---- FUN_011c7840 @ 011c7840

long FUN_011c7840(undefined8 *param_1,long param_2,ulong param_3)

{
  ulong *puVar1;
  ulong *puVar2;
  byte bVar3;
  ulong uVar4;
  ulong *puVar5;
  ulong *puVar6;
  ulong *puVar7;
  ulong uVar8;
  ulong uVar9;
  long lVar10;
  ulong *puVar11;
  ulong *puVar12;
  long lVar13;
  ulong uVar14;
  ulong uVar15;
  ulong uVar16;
  ulong uVar17;
  ulong uVar18;
  ulong *puVar19;
  ulong uVar20;
  ulong uVar21;
  ulong *puVar22;
  bool bVar23;
  undefined8 unaff_retaddr;
  
  uVar8 = -1L << (param_3 & 0x3f);
  uVar18 = -1L << (param_3 & 0x3f);
  uVar9 = -1L << (param_3 & 0x3f);
  uVar14 = -1L << (param_3 & 0x3f);
  uVar17 = -1L << (param_3 & 0x3f);
  bVar3 = (byte)param_3 & 0x3f;
  puVar6 = (ulong *)0x0;
  puVar19 = (ulong *)param_1[2];
LAB_011c78da:
  do {
    puVar1 = puVar19 + 3;
    while (puVar19 != (ulong *)0x0) {
      lVar13 = (1L << bVar3) + param_2 + -1;
      LOCK();
      puVar7 = puVar19 + 1;
      uVar4 = *puVar7;
      *puVar7 = *puVar7 + lVar13;
      UNLOCK();
      lVar10 = (~((uVar14 - uVar4) - (long)puVar1) & uVar14) - (long)puVar1;
      uVar4 = uVar4 + lVar13;
      uVar20 = lVar10 + param_2;
      if (uVar4 != uVar20) {
        LOCK();
        if (uVar4 == puVar19[1]) {
          puVar19[1] = uVar20;
        }
        UNLOCK();
      }
      uVar4 = (*puVar19 & 0xfffffffffffffffe) - 0x18;
      if (uVar20 <= uVar4) {
        lVar10 = (long)puVar1 + lVar10;
        if (puVar6 == (ulong *)0x0) {
          return lVar10;
        }
        puVar6[2] = 0;
        LOCK();
        uVar8 = param_1[3];
        bVar23 = uVar8 == 0;
        if (bVar23) {
          param_1[3] = puVar6;
          uVar8 = 0;
        }
        UNLOCK();
        while (!bVar23) {
          puVar6[2] = uVar8;
          LOCK();
          uVar9 = param_1[3];
          bVar23 = uVar8 == uVar9;
          if (bVar23) {
            param_1[3] = puVar6;
            uVar9 = uVar8;
          }
          UNLOCK();
          uVar8 = uVar9;
        }
        return lVar10;
      }
      uVar20 = *puVar19;
      do {
        LOCK();
        uVar16 = *puVar19;
        bVar23 = uVar20 == uVar16;
        if (bVar23) {
          *puVar19 = uVar20 | 1;
          uVar16 = uVar20;
        }
        UNLOCK();
        uVar20 = uVar16;
      } while (!bVar23);
      if ((uVar16 & 1) != 0) goto LAB_011c79a1;
      uVar20 = puVar19[1];
      lVar10 = (~((uVar17 - uVar20) - (long)puVar1) & uVar17) - (long)puVar1;
      uVar21 = param_2 + 0x19 + lVar10 & 0xfffffffffffffffe;
      if (uVar16 < uVar21) {
        uVar15 = (**(code **)(param_1[1] + 8))(*param_1,puVar19,uVar16,3,uVar21,unaff_retaddr);
        if ((uVar15 & 1) != 0) {
          LOCK();
          bVar23 = uVar20 == puVar19[1];
          if (bVar23) {
            puVar19[1] = lVar10 + param_2;
          }
          UNLOCK();
          uVar16 = uVar21;
          if (bVar23) {
            *puVar19 = uVar21;
            if (puVar6 == (ulong *)0x0) {
              return (long)puVar1 + lVar10;
            }
            puVar6[2] = 0;
            LOCK();
            uVar8 = param_1[3];
            bVar23 = uVar8 == 0;
            if (bVar23) {
              param_1[3] = puVar6;
              uVar8 = 0;
            }
            UNLOCK();
            while (!bVar23) {
              puVar6[2] = uVar8;
              LOCK();
              uVar9 = param_1[3];
              bVar23 = uVar8 == uVar9;
              if (bVar23) {
                param_1[3] = puVar6;
                uVar9 = uVar8;
              }
              UNLOCK();
              uVar8 = uVar9;
            }
            return (long)puVar1 + lVar10;
          }
        }
        *puVar19 = uVar16;
        LOCK();
        puVar1 = (ulong *)param_1[3];
        param_1[3] = 0;
        UNLOCK();
        goto joined_r0x011c7a37;
      }
      *puVar19 = uVar16;
    }
    uVar4 = 0;
LAB_011c79a1:
    LOCK();
    puVar1 = (ulong *)param_1[3];
    param_1[3] = 0;
    UNLOCK();
joined_r0x011c7a37:
    if (puVar1 != (ulong *)0x0) {
      uVar20 = 0xffffffffffffffff;
      puVar7 = (ulong *)0x0;
      puVar22 = (ulong *)0x0;
      puVar2 = puVar1;
      puVar5 = (ulong *)0x0;
      do {
        puVar11 = puVar2;
        uVar21 = (*puVar11 & 0xfffffffffffffffe) - 0x18;
        uVar15 = (param_2 - (long)(puVar11 + 3)) + (~(uVar18 - (long)(puVar11 + 3)) & uVar18);
        uVar16 = 0;
        if (uVar21 <= uVar15) {
          uVar16 = uVar15 - uVar21;
        }
        if (uVar16 < uVar20) {
          uVar20 = uVar16;
          puVar7 = puVar11;
          puVar22 = puVar5;
        }
        puVar2 = (ulong *)puVar11[2];
        puVar5 = puVar11;
      } while ((ulong *)puVar11[2] != (ulong *)0x0);
      puVar2 = puVar7 + 3;
      lVar10 = (~(uVar9 - (long)puVar2) & uVar9) - (long)puVar2;
      if ((*puVar7 & 0xfffffffffffffffe) - 0x18 < (ulong)(lVar10 + param_2)) {
        uVar16 = param_2 + 0x19 + lVar10 & 0xfffffffffffffffe;
        uVar20 = (**(code **)(param_1[1] + 8))
                           (*param_1,puVar7,*puVar7 & 0xfffffffffffffffe,3,uVar16,unaff_retaddr);
        if ((uVar20 & 1) == 0) {
          uVar16 = puVar11[2];
          LOCK();
          uVar20 = param_1[3];
          bVar23 = uVar16 == uVar20;
          if (bVar23) {
            param_1[3] = puVar1;
            uVar20 = uVar16;
          }
          UNLOCK();
          while (!bVar23) {
            puVar11[2] = uVar20;
            LOCK();
            uVar16 = param_1[3];
            bVar23 = uVar20 == uVar16;
            if (bVar23) {
              param_1[3] = puVar1;
              uVar16 = uVar20;
            }
            UNLOCK();
            uVar20 = uVar16;
          }
          goto LAB_011c7c1c;
        }
        *puVar7 = uVar16;
      }
      puVar12 = (ulong *)puVar7[2];
      puVar7[1] = lVar10 + param_2;
      puVar7[2] = (ulong)puVar19;
      LOCK();
      puVar5 = (ulong *)param_1[2];
      bVar23 = puVar19 == puVar5;
      if (bVar23) {
        param_1[2] = puVar7;
        puVar5 = puVar19;
      }
      UNLOCK();
      if (bVar23) {
        if (puVar22 != (ulong *)0x0) {
          puVar22[2] = (ulong)puVar12;
        }
        if (puVar7 != puVar1) {
          puVar12 = puVar1;
        }
        if (puVar12 != (ulong *)0x0) {
          if (puVar7 != puVar11) {
            puVar22 = puVar11;
          }
          uVar9 = puVar22[2];
          LOCK();
          uVar8 = param_1[3];
          bVar23 = uVar9 == uVar8;
          if (bVar23) {
            param_1[3] = puVar12;
            uVar8 = uVar9;
          }
          UNLOCK();
          while (!bVar23) {
            puVar22[2] = uVar8;
            LOCK();
            uVar9 = param_1[3];
            bVar23 = uVar8 == uVar9;
            if (bVar23) {
              param_1[3] = puVar12;
              uVar9 = uVar8;
            }
            UNLOCK();
            uVar8 = uVar9;
          }
        }
        if (puVar6 == (ulong *)0x0) {
          return (long)puVar2 + lVar10;
        }
        puVar6[2] = 0;
        LOCK();
        uVar8 = param_1[3];
        bVar23 = uVar8 == 0;
        if (bVar23) {
          param_1[3] = puVar6;
          uVar8 = 0;
        }
        UNLOCK();
        while (!bVar23) {
          puVar6[2] = uVar8;
          LOCK();
          uVar9 = param_1[3];
          bVar23 = uVar8 == uVar9;
          if (bVar23) {
            param_1[3] = puVar6;
            uVar9 = uVar8;
          }
          UNLOCK();
          uVar8 = uVar9;
        }
        return (long)puVar2 + lVar10;
      }
      puVar7[2] = (ulong)puVar12;
      uVar4 = puVar11[2];
      LOCK();
      uVar20 = param_1[3];
      bVar23 = uVar4 == uVar20;
      if (bVar23) {
        param_1[3] = puVar1;
        uVar20 = uVar4;
      }
      UNLOCK();
      while (puVar19 = puVar5, !bVar23) {
        puVar11[2] = uVar20;
        LOCK();
        uVar4 = param_1[3];
        bVar23 = uVar20 == uVar4;
        if (bVar23) {
          param_1[3] = puVar1;
          uVar4 = uVar20;
        }
        UNLOCK();
        uVar20 = uVar4;
      }
      goto LAB_011c78da;
    }
LAB_011c7c1c:
    if (puVar6 == (ulong *)0x0) {
      uVar20 = uVar4 + param_2 + 0x28 + (1L << bVar3);
      uVar20 = (uVar20 >> 1) + uVar20 + 1 & 0xfffffffffffffffe;
      puVar6 = (ulong *)(**(code **)param_1[1])(*param_1,uVar20,3,unaff_retaddr);
      if (puVar6 == (ulong *)0x0) {
        return 0;
      }
      *puVar6 = uVar20;
    }
    puVar1 = puVar6 + 3;
    lVar10 = (~(uVar8 - (long)puVar1) & uVar8) - (long)puVar1;
    puVar6[1] = lVar10 + param_2;
    puVar6[2] = (ulong)puVar19;
    LOCK();
    puVar7 = (ulong *)param_1[2];
    bVar23 = puVar19 == puVar7;
    if (bVar23) {
      param_1[2] = puVar6;
      puVar7 = puVar19;
    }
    UNLOCK();
    puVar19 = puVar7;
    if (bVar23) {
      return (long)puVar1 + lVar10;
    }
  } while( true );
}


// ---- FUN_011c7e40 @ 011c7e40

/* WARNING: Removing unreachable block (ram,0x011c7f9c) */
/* WARNING: Removing unreachable block (ram,0x011c7fa2) */
/* WARNING: Removing unreachable block (ram,0x011c7f0d) */
/* WARNING: Removing unreachable block (ram,0x011c7f20) */
/* WARNING: Removing unreachable block (ram,0x011c7f27) */
/* WARNING: Removing unreachable block (ram,0x011c7f2f) */
/* WARNING: Removing unreachable block (ram,0x011c7f37) */
/* WARNING: Removing unreachable block (ram,0x011c7fb1) */
/* WARNING: Removing unreachable block (ram,0x011c7f81) */
/* WARNING: Removing unreachable block (ram,0x011c7f86) */
/* WARNING: Removing unreachable block (ram,0x011c7fb7) */

undefined8 * FUN_011c7e40(undefined8 *param_1)

{
  ulong uVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long in_FS_OFFSET;
  bool bVar5;
  undefined4 local_38;
  undefined1 local_20 [4];
  short local_1c;
  
  FUN_011ca0b0(local_20,1,"");
  if (local_1c != 0) {
    switch(local_1c) {
    case 0x24:
    case 0x25:
      uVar3 = 0x200000000;
      break;
    default:
      *(short *)((long)param_1 + 4) = local_1c;
      return param_1;
    case 0x50:
    case 0x51:
    case 0x52:
    case 0x53:
    case 0x54:
      uVar3 = 0x400000000;
    }
    *param_1 = uVar3;
    return param_1;
  }
  lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar4 != 0) && ((*(byte *)(lVar4 + 0x21c) & 1) == 0)) {
    uVar1 = *(ulong *)(lVar4 + 8);
    do {
      LOCK();
      uVar2 = *(ulong *)(lVar4 + 8);
      bVar5 = uVar1 == uVar2;
      if (bVar5) {
        *(ulong *)(lVar4 + 8) = uVar1 | 3;
        uVar2 = uVar1;
      }
      UNLOCK();
      uVar1 = uVar2;
    } while (!bVar5);
    if ((uVar2 & 7) == 0) goto LAB_011c7ed0;
    if (((uint)uVar2 & 7) == 6) {
      syscall();
      *(undefined2 *)((long)param_1 + 4) = 0x11;
      return param_1;
    }
  }
  lVar4 = 0;
LAB_011c7ed0:
  if (lVar4 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar4 + 8) = *(ulong *)(lVar4 + 8) ^ 3;
    UNLOCK();
  }
  *(undefined2 *)((long)param_1 + 4) = 0;
  *(undefined4 *)param_1 = local_38;
  syscall();
  return param_1;
}


// ---- FUN_011c8000 @ 011c8000

ulong FUN_011c8000(ulong *param_1,undefined8 *param_2,long param_3,ulong param_4)

{
  byte bVar1;
  undefined8 *puVar2;
  char cVar3;
  ulong uVar4;
  bool bVar5;
  byte bVar6;
  short sVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  undefined2 uVar11;
  ulong uVar12;
  long lVar13;
  undefined8 local_b8;
  undefined8 uStack_b0;
  undefined8 local_a8;
  undefined8 uStack_a0;
  undefined8 local_98;
  undefined8 uStack_90;
  int local_80;
  undefined4 uStack_7c;
  ulong local_78;
  undefined8 local_70;
  undefined8 uStack_68;
  char local_60;
  ulong local_58;
  bool local_50;
  undefined7 uStack_4f;
  undefined8 uStack_48;
  ushort local_3c;
  undefined1 local_38;
  undefined1 local_34;
  
  uVar4 = *param_1;
  if (2 < uVar4) {
    return 0;
  }
  local_34 = 0;
  local_80 = 0;
  if (param_4 != 0) {
    bVar10 = 0;
    bVar9 = 0;
    uVar12 = 0;
    bVar5 = false;
    do {
      cVar3 = *(char *)(param_3 + uVar12);
      if (cVar3 == '.') {
        if (!(bool)(bVar5 & bVar10 != 3)) goto LAB_011c80fd;
        bVar10 = bVar10 + 1;
        bVar9 = 0;
      }
      else {
        bVar1 = cVar3 - 0x30;
        if ((9 < bVar1) || (bVar8 = bVar5 | cVar3 != '0', (bool)(bVar9 & bVar8))) goto LAB_011c80fd;
        sVar7 = (ushort)*(byte *)((long)&local_80 + (ulong)bVar10) * 10;
        local_50 = (char)((ushort)sVar7 >> 8) != '\0';
        if (local_50) goto LAB_011c80fd;
        bVar6 = (byte)sVar7;
        local_50 = CARRY1(bVar6,bVar1);
        if (CARRY1(bVar6,bVar1)) goto LAB_011c80fd;
        bVar9 = bVar8 ^ 1;
        *(byte *)((long)&local_80 + (ulong)bVar10) = bVar6 + bVar1;
      }
      uVar12 = uVar12 + 1;
      bVar5 = cVar3 != '.';
    } while (param_4 != uVar12);
    if (cVar3 != '.' && bVar10 == 3) {
      uVar11 = 0x35;
      uVar12 = uVar4;
      goto LAB_011c81c5;
    }
  }
LAB_011c80fd:
  local_38 = 1;
  FUN_011c9bc0(&local_80,param_3,param_4);
  if (local_60 != '\0') {
    return 0x6c;
  }
  local_a8 = local_70;
  uStack_a0 = uStack_68;
  if (CONCAT44(uStack_7c,local_80) == 0) {
    local_58 = 0;
  }
  else {
    if (0xf < local_78) {
      return 0x31;
    }
    FUN_011f4580(&local_50,CONCAT44(uStack_7c,local_80),local_78);
    (&local_50)[local_78] = false;
    local_b8 = CONCAT71(uStack_4f,local_50);
    uStack_b0 = uStack_48;
    (**(code **)(param_2[1] + 0x350))(&local_58,*param_2,&local_b8);
    if ((short)(local_58 >> 0x20) != 0) {
      return local_58 >> 0x20;
    }
  }
  local_3c = (ushort)local_58;
  local_98 = local_a8;
  uStack_90 = uStack_a0;
  local_80 = (uint)local_3c << 0x10;
  param_4 = local_58 >> 0x10 & 0xffff;
  uVar12 = *param_1;
  uVar11 = 0;
  local_34 = local_38;
LAB_011c81c5:
  lVar13 = uVar4 * 0x20;
  *(undefined2 *)((long)param_1 + lVar13 + 0x1c) = uVar11;
  *(int *)((long)param_1 + lVar13 + 0x1e) = local_80;
  *(short *)((long)param_1 + lVar13 + 0x22) = (short)param_4;
  *(undefined2 *)((long)param_1 + lVar13 + 0x24) = 0x35;
  puVar2 = (undefined8 *)((long)param_1 + lVar13 + 0x26);
  *puVar2 = local_98;
  puVar2[1] = uStack_90;
  *(undefined1 *)(param_1 + uVar4 * 4 + 7) = local_34;
  *param_1 = uVar12 + 1;
  return 0;
}


// ---- FUN_011c8210 @ 011c8210

/* WARNING: Type propagation algorithm not settling */

ulong FUN_011c8210(undefined8 param_1,long param_2,char *******param_3,ulong *param_4,
                  undefined8 param_5,long *param_6)

{
  char cVar1;
  char cVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined2 uVar6;
  ushort uVar7;
  long lVar8;
  ulong uVar9;
  undefined1 *puVar10;
  ulong uVar11;
  char *******pppppppcVar12;
  long *plVar13;
  char cVar14;
  ushort *puVar15;
  ulong uVar16;
  char *pcVar17;
  char *******pppppppcVar18;
  long lVar19;
  ulong uVar20;
  undefined8 *puVar21;
  ushort *extraout_RDX;
  ushort *puVar22;
  ushort *extraout_RDX_00;
  char *******extraout_RDX_01;
  char *******pppppppcVar23;
  char *pcVar24;
  char *pcVar25;
  char *pcVar26;
  uint uVar27;
  ulong uVar28;
  ulong uVar29;
  byte bVar30;
  byte bVar31;
  ushort **ppuVar32;
  int iVar33;
  char *pcVar34;
  char ******ppppppcVar35;
  long lVar36;
  long lVar37;
  bool bVar38;
  undefined1 auVar39 [64];
  undefined1 auVar40 [16];
  undefined1 auStack_c48 [1024];
  ulong local_848 [4];
  ushort uStack_828;
  int iStack_826;
  ushort local_820;
  undefined1 local_81e [18];
  byte local_80c [404];
  undefined8 local_678 [15];
  undefined8 local_600 [11];
  undefined8 local_5a8;
  char local_59b [267];
  char *****local_490 [31];
  undefined8 uStack_394;
  undefined8 auStack_388 [2];
  ushort local_378 [4];
  undefined1 local_370 [12];
  undefined8 uStack_364;
  undefined1 local_35c [68];
  undefined1 local_318 [16];
  undefined1 local_308 [16];
  undefined8 local_2f8;
  undefined8 uStack_2f0;
  long local_2e8;
  undefined4 local_2e0;
  undefined1 local_2d8;
  undefined1 local_2c8;
  undefined4 local_2b8;
  undefined2 local_2b4;
  undefined1 local_29c;
  long local_298 [2];
  long local_288 [2];
  unkbyte10 local_278;
  undefined6 uStack_26e;
  unkbyte10 Stack_268;
  undefined1 local_25c;
  ushort *puStack_258;
  undefined4 uStack_250;
  undefined4 local_24c;
  undefined4 uStack_248;
  undefined8 uStack_244;
  ushort *local_238;
  char *******local_230;
  char ******local_228;
  undefined8 local_220;
  undefined8 local_218;
  long local_210 [5];
  char *******local_1e8;
  long local_1e0;
  ulong local_1d8;
  ulong local_1d0;
  long local_1c8;
  ulong local_1c0;
  ulong local_1b8;
  long local_1b0;
  undefined8 local_1a8;
  undefined **local_1a0;
  char *******local_198;
  char *local_190;
  char *******local_188;
  undefined8 local_180;
  ulong local_178;
  long local_170;
  ushort *local_168;
  ushort local_160;
  undefined6 uStack_15e;
  undefined2 uStack_158;
  undefined2 uStack_156;
  undefined2 uStack_154;
  undefined1 uStack_152;
  undefined1 uStack_151;
  undefined8 local_150;
  undefined8 uStack_148;
  undefined1 local_140 [16];
  long local_130;
  long local_128;
  undefined8 local_120;
  undefined8 local_118;
  ushort uStack_110;
  undefined4 uStack_10e;
  short sStack_10a;
  undefined2 uStack_108;
  undefined2 uStack_106;
  undefined2 uStack_104;
  undefined2 uStack_102;
  undefined2 uStack_100;
  undefined2 uStack_fe;
  int iStack_fc;
  int local_f8;
  ushort local_f4;
  undefined1 local_e8;
  undefined4 local_e0;
  char *******local_d0;
  undefined1 local_c8;
  undefined1 local_c4;
  undefined1 local_c0;
  undefined1 local_b8;
  long local_b0;
  undefined1 local_a8;
  undefined1 local_98;
  long local_88;
  ulong local_80;
  long local_78;
  ushort local_6a;
  long local_68;
  ushort *local_60;
  char *******local_58;
  char local_49;
  undefined1 local_48;
  undefined1 local_40;
  undefined2 local_3a;
  int local_38;
  byte local_31;
  undefined1 extraout_var [56];
  
  local_78 = *param_6;
  local_6a = *(ushort *)(param_6 + 1);
  bVar31 = *(byte *)((long)param_6 + 10);
  local_88 = param_1;
  local_1a8 = param_1;
  local_1a0 = &PTR_FUN_0100e020;
  local_120 = param_5;
  local_31 = DAT_01001478 & 1;
  local_d0 = param_3;
  local_128 = param_2;
  puVar15 = (ushort *)((long)param_3 + param_2 + -1);
  if ((*(char *)((long)param_6 + 0xb) == '\0') || (((local_31 ^ bVar31) & 1) != 0)) {
    local_38 = CONCAT31(local_38._1_3_,bVar31);
    local_58 = (char *******)CONCAT71(local_58._1_7_,*(char *)((long)param_6 + 0xb));
    local_60 = puVar15;
    FUN_011cbe10(param_1,&local_3a,2);
    pcVar24 = (char *)0x0;
    if (param_3 != (char *******)0x0) {
      pcVar24 = (char *)((long)param_3 - 1);
    }
    local_b0 = CONCAT71(local_b0._1_7_,param_3 == (char *******)0x0 || puVar15 == (ushort *)".");
    pcVar34 = pcVar24;
    if (param_3 != (char *******)0x0 && puVar15 != (ushort *)".") {
      pcVar34 = (char *)((long)local_d0 - (ulong)((char)*local_60 == '.'));
    }
    local_5a8._0_2_ = local_3a;
    FUN_011f4160((long)&local_5a8 + 2,0,pcVar34 + (ulong)(pcVar34 != (char *)0x0) + 0xf);
    local_5a8._2_1_ = 1;
    local_5a8._5_1_ = 1;
    pcVar17 = local_59b;
    FUN_011f4580(pcVar17,local_128,pcVar34);
    cVar2 = (char)local_58;
    if (local_59b[0] != '\0') {
      lVar8 = 0xd;
      do {
        cVar14 = '\0';
        cVar1 = *(char *)((long)&local_5a8 + lVar8);
        lVar36 = lVar8;
        while ((lVar8 = lVar36 + 1, cVar1 != '\0' && (cVar1 != '.'))) {
          cVar14 = cVar14 + '\x01';
          cVar1 = *(char *)((long)&local_5a8 + lVar36 + 1);
          lVar36 = lVar8;
        }
        pcVar17[-1] = cVar14;
        pcVar17 = (char *)((long)&local_5a8 + lVar36 + 1);
      } while (*(char *)((long)&local_5a8 + lVar36 + 1) != '\0');
      pcVar17 = (char *)((long)&local_5a8 + lVar36 + 1);
    }
    ppppppcVar35 = (char ******)(local_59b + 0x10b);
    pcVar17[1] = '\x01';
    pcVar17[3] = '\x01';
    local_198 = (char *******)&local_5a8;
    local_190 = pcVar34 + (ulong)(pcVar34 != (char *)0x0) + 0x11;
    local_31 = DAT_0100147a & 1;
    local_68 = 1;
    if (cVar2 != '\0') {
      bVar31 = (byte)local_38 ^ DAT_0100147a & 1;
      puVar15 = local_60;
      pppppppcVar12 = (char *******)&local_188;
      pppppppcVar23 = local_58;
      goto joined_r0x011c83ea;
    }
    local_68 = 2;
    local_58 = (char *******)&local_188;
    FUN_011cbe10(local_88,&local_3a,2);
    puVar15 = local_60;
    if ((char)local_b0 == '\0') goto LAB_011c84b1;
LAB_011c84c5:
    *(undefined2 *)ppppppcVar35 = local_3a;
    FUN_011f4160((undefined2 *)((long)ppppppcVar35 + 2),0,
                 pcVar24 + (ulong)(pcVar24 != (char *)0x0) + 0xf);
    *(undefined1 *)((long)ppppppcVar35 + 2) = 1;
    *(undefined1 *)((long)ppppppcVar35 + 5) = 1;
    lVar8 = (long)ppppppcVar35 + 0xd;
    FUN_011f4580(lVar8,local_128,pcVar24);
    if (*(char *)((long)ppppppcVar35 + 0xd) != '\0') {
      lVar36 = 0xd;
      do {
        lVar37 = lVar36;
        lVar19 = 0;
        cVar2 = *(char *)((long)ppppppcVar35 + lVar37);
        while ((cVar2 != '.' && (cVar2 != '\0'))) {
          lVar19 = lVar19 + 1;
          cVar2 = *(char *)((long)ppppppcVar35 + lVar19 + lVar37);
        }
        *(char *)(lVar8 + -1) = (char)lVar19;
        lVar8 = (long)ppppppcVar35 + lVar37 + lVar19 + 1;
        lVar36 = lVar37 + lVar19 + 1;
      } while (*(char *)((long)ppppppcVar35 + lVar37 + lVar19 + 1) != '\0');
      lVar8 = (long)ppppppcVar35 + lVar19 + lVar37 + 1;
    }
    *(undefined1 *)(lVar8 + 1) = 0x1c;
    *(undefined1 *)(lVar8 + 3) = 1;
    pppppppcVar23 = local_58;
    *local_58 = ppppppcVar35;
    pppppppcVar23[1] = (char ******)(pcVar24 + (ulong)(pcVar24 != (char *)0x0) + 0x11);
    uVar29 = *param_4;
    if (uVar29 == 0) goto LAB_011c877d;
LAB_011c858e:
    uVar16 = 1;
    lVar8 = 0x1c;
    bVar31 = 0;
LAB_011c85d3:
    *(undefined1 *)((long)local_378 + lVar8) = 1;
    uVar6 = local_118._4_2_;
    uVar3 = *(undefined4 *)((long)param_4 + lVar8 + 2);
    bVar30 = *(byte *)((long)param_4 + lVar8 + 0x1c);
    local_118._4_2_ = (undefined2)((uint)uVar3 >> 0x10);
    if ((bVar30 & 1) == 0) {
      uStack_156 = 0;
      uStack_15e = 0;
      uStack_158 = 0;
      uStack_154 = 0xffff;
      uStack_152 = (char)uVar3;
      uStack_151 = (char)((uint)uVar3 >> 8);
      local_150 = CONCAT62(local_150._2_6_,local_118._4_2_);
      local_160 = *(ushort *)((long)param_4 + lVar8);
      local_168 = (ushort *)0x0;
      ppuVar32 = &local_168;
      local_118._4_2_ = uVar6;
    }
    else {
      local_118._0_2_ = *(ushort *)((long)param_4 + lVar8);
      local_118._2_2_ = (undefined2)uVar3;
      uVar4 = *(undefined8 *)((long)param_4 + lVar8 + 0x14);
      uStack_102 = (undefined2)((ulong)uVar4 >> 0x10);
      uStack_100 = (undefined2)((ulong)uVar4 >> 0x20);
      uStack_fe = (undefined2)((ulong)uVar4 >> 0x30);
      puVar21 = (undefined8 *)((long)param_4 + lVar8 + 6);
      uVar4 = *puVar21;
      uVar5 = puVar21[1];
      local_118._6_2_ = (undefined2)uVar4;
      uStack_110 = (ushort)((ulong)uVar4 >> 0x10);
      uStack_10e = (undefined4)((ulong)uVar4 >> 0x20);
      sStack_10a = (short)uVar5;
      uStack_108 = (undefined2)((ulong)uVar5 >> 0x10);
      uStack_106 = (undefined2)((ulong)uVar5 >> 0x20);
      uStack_104 = (undefined2)((ulong)uVar5 >> 0x30);
      ppuVar32 = (ushort **)&local_118;
    }
    uVar4 = *(undefined8 *)((long)ppuVar32 + 0x14);
    uStack_248 = (undefined4)((ulong)*(undefined8 *)((long)ppuVar32 + 0xc) >> 0x20);
    uStack_244 = uVar4;
    puStack_258 = *ppuVar32;
    uStack_250 = SUB84(ppuVar32[1],0);
    local_24c = (undefined4)((ulong)ppuVar32[1] >> 0x20);
    *(ulong *)((long)auStack_388 + lVar8) = CONCAT44(uStack_248,local_24c);
    *(undefined8 *)((long)auStack_388 + lVar8 + 8) = uVar4;
    uVar4 = CONCAT44(local_24c,uStack_250);
    *(ushort **)((long)&uStack_394 + lVar8) = puStack_258;
    *(undefined8 *)(&stack0xfffffffffffffc74 + lVar8) = uVar4;
    if ((bVar31 & 1) != 0) {
      bVar30 = 1;
      if (uVar29 == uVar16) goto LAB_011c86db;
LAB_011c85c9:
      uVar16 = uVar16 + 1;
      lVar8 = lVar8 + 0x20;
      bVar31 = bVar30;
      goto LAB_011c85d3;
    }
    if (uVar29 != uVar16) goto LAB_011c85c9;
    if ((bVar30 & 1) == 0) goto LAB_011c877d;
LAB_011c86db:
    local_25c = 1;
    local_278 = SUB1610((undefined1  [16])0x0,0);
    uStack_26e = 0;
    Stack_268 = SUB1610((undefined1  [16])0x0,6);
    FUN_011e0270(&local_118,(long)&local_118 + 6,&local_278,&DAT_0100ebc4);
    uVar16 = (ulong)local_f4;
    if (local_f4 != 0) {
      if (local_f4 != 0x50) goto LAB_011c90ee;
      goto LAB_011c877d;
    }
    local_38 = CONCAT22(local_118._2_2_,(ushort)local_118);
    local_60 = local_378;
  }
  else {
    local_31 = DAT_0100147a & 1;
    ppppppcVar35 = (char ******)&local_5a8;
    local_68 = 0;
    bVar31 = bVar31 ^ DAT_0100147a & 1;
    pppppppcVar12 = (char *******)&local_198;
    pppppppcVar23 = local_58;
joined_r0x011c83ea:
    local_58 = pppppppcVar12;
    if ((bVar31 & 1) != 0) {
      bVar38 = local_d0 != (char *******)0x0;
      pcVar24 = (char *)0x0;
      if (local_d0 != (char *******)0x0) {
        pcVar24 = (char *)((long)local_d0 - 1);
      }
      local_68 = local_68 + 1;
      FUN_011cbe10(local_88,&local_3a,2);
      if (bVar38 && puVar15 != (ushort *)".") {
LAB_011c84b1:
        pcVar24 = (char *)((long)local_d0 - (ulong)(*(char *)puVar15 == '.'));
      }
      goto LAB_011c84c5;
    }
    uVar29 = *param_4;
    local_58 = pppppppcVar23;
    if (uVar29 != 0) goto LAB_011c858e;
LAB_011c877d:
    local_29c = 0;
    local_2b8 = 0;
    local_2b4 = 0;
    FUN_011e0270(&local_118);
    uVar16 = (ulong)local_f4;
    if (local_f4 != 0) goto LAB_011c90ee;
    local_60 = (ushort *)((long)param_4 + 0x1c);
    local_38 = CONCAT22(local_118._2_2_,(ushort)local_118);
    uVar29 = *param_4;
  }
  local_f4 = 0;
  if ((local_68 != 0) && (local_210[1] = 0, (int)local_68 != 1)) {
    local_210[3] = 0;
  }
  if (((code *)PTR_FUN_011fcf88 == (code *)0x0) ||
     ((uVar16 = (*(code *)PTR_FUN_011fcf88)(7,&local_118), uVar16 != 0 &&
      (uVar16 != 0xffffffffffffffea)))) {
    uVar16 = 0xe4;
    syscall();
  }
  uVar20 = 0;
  uVar9 = -uVar16;
  if (uVar16 < 0xfffffffffffff001) {
    uVar9 = uVar20;
  }
  lVar8 = 0;
  if (uVar9 == 0) {
    uVar16 = CONCAT26(sStack_10a,CONCAT42(uStack_10e,uStack_110));
    uVar9 = CONCAT26(local_118._6_2_,
                     CONCAT24(local_118._4_2_,CONCAT22(local_118._2_2_,(ushort)local_118))) *
            1000000000;
    uVar20 = uVar9 + uVar16;
    lVar8 = SUB168(SEXT816(1000000000) *
                   SEXT816(CONCAT26(local_118._6_2_,
                                    CONCAT24(local_118._4_2_,
                                             CONCAT22(local_118._2_2_,(ushort)local_118)))),8) +
            ((long)sStack_10a >> 0xf) + (ulong)CARRY8(uVar9,uVar16);
  }
  uVar28 = (ulong)(uint)param_4[3];
  local_1d8 = uVar28 * 1000000000 + uVar20;
  uVar16 = 1000000000 / (ulong)(uint)param_4[2];
  uVar9 = uVar16 * uVar28;
  if (uVar28 != 0) {
    local_1c8 = (long)(int)((int)lVar8 + (uint)CARRY8(uVar28 * 1000000000,uVar20));
    local_178 = uVar29 - 1;
    local_49 = uVar29 == 0 || local_68 == 0;
    local_1b8 = (ulong)((uint)uVar29 & 3);
    local_1c0 = uVar29 & 0xfffffffffffffffc;
    local_170 = -local_1b8;
    local_1b0 = -local_1c0;
    local_b0 = 0;
    puVar15 = local_60;
    local_1e0 = local_68;
    local_1d0 = uVar9;
    local_80 = uVar29;
LAB_011c8937:
    lVar36 = local_68;
    pcVar24 = local_190;
    pppppppcVar23 = local_198;
    uVar16 = local_1c0;
    if (local_49 == '\0') {
      if (local_210[1] == 0) {
        if (local_178 < 3) {
          uVar28 = 0;
        }
        else {
          puVar21 = local_600;
          uVar28 = 0;
          puVar22 = puVar15;
          do {
            puVar21[-0x13] = puVar22;
            puVar21[-0x12] = pppppppcVar23;
            puVar21[-0x11] = pcVar24;
            puVar21[-0x10] = 1;
            puVar21[-0xf] = 0;
            puVar21[-0xe] = puVar22 + 0x10;
            puVar21[-0xd] = pppppppcVar23;
            puVar21[-0xc] = pcVar24;
            puVar21[-0xb] = 1;
            puVar21[-10] = 0;
            puVar21[-9] = puVar22 + 0x20;
            puVar21[-8] = pppppppcVar23;
            puVar21[-7] = pcVar24;
            puVar21[-6] = 1;
            puVar21[-5] = 0;
            puVar21[-4] = puVar22 + 0x30;
            puVar21[-3] = pppppppcVar23;
            puVar21[-2] = pcVar24;
            puVar21[-1] = 1;
            *puVar21 = 0;
            uVar28 = uVar28 + 4;
            puVar22 = puVar22 + 0x40;
            puVar21 = puVar21 + 0x14;
          } while (uVar16 != uVar28);
        }
        lVar19 = local_170;
        if (local_1b8 != 0) {
          puVar22 = puVar15 + uVar28 * 0x10;
          puVar21 = local_678 + uVar28 * 5;
          lVar37 = 0;
          do {
            puVar21[-4] = puVar22;
            puVar21[-3] = pppppppcVar23;
            puVar21[-2] = pcVar24;
            puVar21[-1] = 1;
            *puVar21 = 0;
            puVar22 = puVar22 + 0x10;
            lVar37 = lVar37 + -1;
            puVar21 = puVar21 + 5;
          } while (lVar19 != lVar37);
          uVar28 = uVar28 - lVar37;
          uVar29 = local_80;
        }
      }
      else {
        uVar28 = 0;
      }
      uVar4 = local_180;
      pppppppcVar23 = local_188;
      lVar19 = local_1b0;
      if (((int)lVar36 != 1) && (local_210[3] == 0)) {
        if (local_178 < 3) {
          lVar36 = 0;
          lVar19 = local_170;
        }
        else {
          puVar21 = local_600 + uVar28 * 5;
          lVar36 = 0;
          puVar22 = puVar15;
          do {
            puVar21[-0x13] = puVar22;
            puVar21[-0x12] = pppppppcVar23;
            puVar21[-0x11] = uVar4;
            puVar21[-0x10] = 1;
            puVar21[-0xf] = 0;
            puVar21[-0xe] = puVar22 + 0x10;
            puVar21[-0xd] = pppppppcVar23;
            puVar21[-0xc] = uVar4;
            puVar21[-0xb] = 1;
            puVar21[-10] = 0;
            puVar21[-9] = puVar22 + 0x20;
            puVar21[-8] = pppppppcVar23;
            puVar21[-7] = uVar4;
            puVar21[-6] = 1;
            puVar21[-5] = 0;
            puVar21[-4] = puVar22 + 0x30;
            puVar21[-3] = pppppppcVar23;
            puVar21[-2] = uVar4;
            puVar21[-1] = 1;
            *puVar21 = 0;
            puVar22 = puVar22 + 0x40;
            lVar36 = lVar36 + -4;
            puVar21 = puVar21 + 0x14;
          } while (lVar19 != lVar36);
          uVar28 = uVar28 - lVar36;
          lVar36 = -lVar36;
          lVar19 = local_170;
          uVar29 = local_80;
        }
        local_170 = lVar19;
        if ((uVar29 & 3) != 0) {
          puVar15 = puVar15 + lVar36 * 0x10;
          puVar21 = local_678 + uVar28 * 5;
          lVar36 = 0;
          do {
            puVar21[-4] = puVar15;
            puVar21[-3] = pppppppcVar23;
            puVar21[-2] = uVar4;
            puVar21[-1] = 1;
            *puVar21 = 0;
            puVar15 = puVar15 + 0x10;
            lVar36 = lVar36 + -1;
            puVar21 = puVar21 + 5;
          } while (lVar19 != lVar36);
        }
      }
    }
    FUN_011dedf0(local_308);
    local_98 = 2;
    lVar36 = uVar20 + uVar9;
    local_210[4] = lVar8 + (ulong)CARRY8(uVar20,uVar9);
    local_a8 = 2;
    local_58 = local_198;
    local_1e8 = local_188;
    local_130 = lVar36;
    do {
      lVar8 = local_210[4];
      auVar39._0_8_ = FUN_011f4580(local_848,&DAT_0100ebd0,0x1b0);
      auVar39._8_56_ = extraout_var;
      puVar10 = auStack_c48 + local_b0;
      lVar19 = 0x400 - local_b0;
      local_2e0 = (undefined4)lVar8;
      local_2d8 = 2;
      local_2c8 = 2;
      local_48 = 3;
      local_140 = vpcmpeqd_avx(auVar39._0_16_,auVar39._0_16_);
      local_168 = (ushort *)&local_118;
      local_160 = 1;
      uStack_15e = 0;
      uStack_158 = 0;
      uStack_156 = 0;
      uStack_154 = 0;
      uStack_152 = 0;
      uStack_151 = 0;
      local_e0 = 0xffffffff;
      local_118._0_2_ = (ushort)local_848;
      local_118._2_2_ = (undefined2)((ulong)local_848 >> 0x10);
      local_118._4_2_ = (undefined2)((ulong)local_848 >> 0x20);
      local_118._6_2_ = (undefined2)((ulong)local_848 >> 0x30);
      uStack_110 = 6;
      uStack_10e = 0;
      sStack_10a = 0;
      uStack_108 = SUB82(puVar10,0);
      uStack_106 = (undefined2)((ulong)puVar10 >> 0x10);
      uStack_104 = (undefined2)((ulong)puVar10 >> 0x20);
      uStack_102 = (undefined2)((ulong)puVar10 >> 0x30);
      uStack_100 = (undefined2)lVar19;
      uStack_fe = (undefined2)((ulong)lVar19 >> 0x10);
      iStack_fc = (int)((ulong)lVar19 >> 0x20);
      local_f8 = local_38;
      local_f4 = local_f4 & 0xff00;
      local_e8 = 3;
      local_150 = DAT_010008a0;
      uStack_148 = 0;
      local_2e8 = lVar36;
      uVar7 = FUN_011db530(local_88,&local_168,&local_2e8);
      puVar22 = extraout_RDX;
      puVar15 = local_60;
      uVar9 = local_1d0;
      uVar29 = local_80;
      if (uVar7 == 0) {
        uVar16 = (ulong)(uint)local_140._8_4_;
        if (uVar16 != 0xffffffff) {
          if ((ulong)local_150._4_4_ != 0xffffffff) {
            *(undefined4 *)(local_168 + (ulong)local_150._4_4_ * 0x24 + 2) = local_140._8_4_;
          }
          uVar7 = local_168[uVar16 * 0x24];
          lVar8 = *(long *)(local_168 + uVar16 * 0x24 + 4);
          *(uint *)(local_168 + uVar16 * 0x24) = local_150._4_4_;
          *(uint *)((long)(local_168 + uVar16 * 0x24) + 4) = 0xffffffff;
          puVar22 = local_168;
          lVar36 = local_130;
          if ((local_80 != 0) && (lVar8 != 0)) {
            lVar37 = 0;
            uVar16 = local_80;
            lVar19 = local_68;
LAB_011c8e2c:
            uVar29 = local_848[lVar37 * 9 + 1];
            if (3 < uVar29) {
              pcVar24 = (char *)local_848[lVar37 * 9];
              puVar22 = puVar15;
              if ((local_80c[lVar37 * 0x48] & 1) == 0) {
                uVar9 = uVar16;
                do {
                  if ((((puVar22[0xe] & 1) == 0) && ((&uStack_828)[lVar37 * 0x24] == *puVar22)) &&
                     ((&iStack_826)[lVar37 * 0x12] == *(int *)(puVar22 + 1))) goto LAB_011c8ecd;
                  puVar22 = puVar22 + 0x10;
                  uVar9 = uVar9 - 1;
                } while (uVar9 != 0);
              }
              else {
                uVar9 = uVar16;
                do {
                  if ((((puVar22[0xe] & 1) != 0) && ((&local_820)[lVar37 * 0x24] == puVar22[4])) &&
                     (*(undefined1 (*) [16])(local_81e + lVar37 * 0x48) ==
                      *(undefined1 (*) [16])(puVar22 + 5))) goto LAB_011c8ecd;
                  puVar22 = puVar22 + 0x10;
                  uVar9 = uVar9 - 1;
                } while (uVar9 != 0);
              }
            }
            goto LAB_011c8e20;
          }
        }
      }
joined_r0x011c8c6c:
      local_1d0 = uVar9;
      local_80 = uVar29;
      if (uVar7 == 0x29) goto LAB_011c9010;
      if (uVar7 == 0x11) {
        syscall();
        uVar16 = CONCAT62((int6)((ulong)puVar22 >> 0x10),0x11);
        goto LAB_011c90ee;
      }
    } while( true );
  }
LAB_011c90ce:
  syscall();
  uVar16 = CONCAT62((int6)(uVar16 >> 0x10),0x65);
LAB_011c90ee:
  return uVar16 & 0xffffffff;
LAB_011c8ecd:
  if (lVar19 == 0) goto LAB_011c8e20;
  if (*pcVar24 == *(char *)local_58) {
    plVar13 = local_210;
    pppppppcVar23 = (char *******)&local_198;
    puVar15 = local_60;
    pppppppcVar12 = local_58;
    if (pcVar24[1] != *(char *)((long)local_58 + 1)) goto LAB_011c8f0e;
  }
  else {
LAB_011c8f0e:
    if (((int)lVar19 == 1) || (uVar16 = local_80, *pcVar24 != *(char *)local_1e8))
    goto LAB_011c8e20;
    plVar13 = local_210 + 2;
    pppppppcVar23 = (char *******)&local_188;
    pppppppcVar12 = local_1e8;
    if (pcVar24[1] != *(char *)((long)local_1e8 + 1)) goto LAB_011c8e20;
  }
  if (plVar13[1] != 0) goto LAB_011c8e20;
  bVar31 = pcVar24[3] & 0xf;
  if (bVar31 != 3) {
    if (bVar31 == 2) {
      local_228 = pppppppcVar23[1];
      local_220 = 1;
      local_218 = 0;
      local_238 = puVar22;
      local_230 = pppppppcVar12;
      FUN_011dedf0(local_318,plVar13,local_38,&local_238,1,0);
      puVar22 = extraout_RDX_00;
      puVar15 = local_60;
      lVar19 = local_68;
      goto LAB_011c8e20;
    }
    if ((pcVar24[3] & 0xfU) != 0) goto LAB_011c8e20;
  }
  *plVar13 = (long)pcVar24;
  plVar13[1] = uVar29;
  local_b0 = local_b0 + uVar29;
  if ((local_b0 == 0x400) || (local_1e0 = local_1e0 + -1, local_1e0 == 0)) {
    bVar38 = false;
    lVar8 = 0;
    local_88 = 0;
    goto LAB_011c911c;
  }
LAB_011c8e20:
  lVar37 = lVar37 + 1;
  uVar9 = local_1d0;
  lVar36 = local_130;
  uVar29 = local_80;
  if (lVar37 == lVar8) goto joined_r0x011c8c6c;
  goto LAB_011c8e2c;
LAB_011c911c:
  do {
    pcVar24 = (char *)local_210[lVar8 * 2 + 1];
    if (((char *)0xb < pcVar24) &&
       (lVar36 = local_210[lVar8 * 2], (*(byte *)(lVar36 + 3) & 0xf) == 0)) {
      uVar7 = *(ushort *)(lVar36 + 4);
      if (uVar7 == 0) {
        pcVar34 = (char *)0xc;
      }
      else {
        uVar7 = uVar7 << 8 | uVar7 >> 8;
        pcVar34 = (char *)0xc;
        do {
          iVar33 = (int)pcVar34;
          pcVar17 = pcVar34;
          if (pcVar34 < pcVar24) {
            do {
              pcVar34 = pcVar17;
              if (pcVar17[lVar36] < '\x01') break;
              pcVar17 = pcVar17 + 1;
              pcVar34 = pcVar24;
            } while (pcVar24 != pcVar17);
            iVar33 = (int)pcVar34;
          }
          if ((ulong)((long)pcVar24 - (long)pcVar34) < 6) goto LAB_011c9110;
          pcVar34 = (char *)(ulong)((iVar33 - (uint)(pcVar34[lVar36] == '\0')) + 6);
          uVar7 = uVar7 - 1;
        } while (uVar7 != 0);
      }
      uVar7 = *(ushort *)(lVar36 + 6);
      if (uVar7 != 0) {
        uVar27 = (uint)(ushort)(uVar7 << 8 | uVar7 >> 8);
        local_80 = (ulong)pcVar24 >> 1;
        local_b0 = lVar8;
LAB_011c91f6:
        pcVar17 = pcVar34;
        if (pcVar34 < pcVar24) {
          do {
            pcVar34 = pcVar17;
            if (pcVar17[lVar36] < '\x01') break;
            pcVar17 = pcVar17 + 1;
            pcVar34 = pcVar24;
          } while (pcVar24 != pcVar17);
          pcVar17 = (char *)((ulong)pcVar34 & 0xffffffff);
        }
        lVar8 = local_b0;
        if ((ulong)((long)pcVar24 - (long)pcVar34) < 0xc) goto LAB_011c9110;
        uVar29 = (ulong)(pcVar34[lVar36] != '\0');
        uVar7 = *(ushort *)(pcVar17 + lVar36 + uVar29 + 9);
        uVar16 = ((ulong)(pcVar17 + uVar29 + 1) & 0xffffffff) + 10;
        pcVar34 = (char *)(ulong)((uint)(ushort)(uVar7 << 8 | uVar7 >> 8) + (int)uVar16);
        if (pcVar24 < pcVar34) goto LAB_011c9110;
        cVar2 = pcVar17[lVar36 + uVar29 + 2];
        local_60 = (ushort *)CONCAT44(local_60._4_4_,uVar27);
        if (cVar2 == '\x01') {
          if (uVar7 != 0x400) {
            syscall();
            uVar16 = 0x62;
            goto LAB_011c90ee;
          }
          local_c4 = 0;
          local_b8 = 0;
          local_118._0_2_ = local_6a;
          local_118._2_2_ = (undefined2)*(undefined4 *)(lVar36 + uVar16);
          local_118._4_2_ = (undefined2)((uint)*(undefined4 *)(lVar36 + uVar16) >> 0x10);
          iStack_fc = (uint)iStack_fc._1_3_ << 8;
          local_f8 = (uint)local_f8._1_3_ << 8;
          FUN_011cb0c0(&local_168,local_120,&local_1a8,&local_118,1,1);
          uVar16 = (ulong)local_160;
          if (local_160 != 0) {
            syscall();
            goto LAB_011c90ee;
          }
LAB_011c91d6:
          local_88 = local_88 + 1;
          lVar19 = local_68;
        }
        else {
          if (cVar2 == '\x05') {
            if (local_78 != 0) {
              local_58 = (char *******)0x0;
              pppppppcVar23 = (char *******)0x0;
              pcVar17 = (char *)(uVar16 & 0xffffffff);
              uVar29 = local_80;
              do {
                if (pcVar24 <= pcVar17) goto LAB_011c9541;
                pppppppcVar23 = (char *******)(ulong)(byte)pcVar17[lVar36];
                if (pppppppcVar23 < (char *******)0x40) {
                  if (pppppppcVar23 == (char *******)0x0) goto LAB_011c9467;
                  if (local_58 == (char *******)0x0) {
                    pcVar26 = (char *)0x0;
                  }
                  else {
                    *(char *)((long)local_58 + local_78) = '.';
                    pcVar26 = (char *)((long)local_58 + 1);
                  }
                  pcVar25 = (char *)((long)pppppppcVar23 + (long)(pcVar17 + 1));
                  if ((pcVar24 < pcVar25) ||
                     (local_58 = (char *******)(pcVar26 + (long)pppppppcVar23),
                     (char *******)0xfe < local_58)) goto LAB_011c9541;
                  FUN_011f4580(pcVar26 + local_78,pcVar17 + lVar36 + 1);
                  pppppppcVar23 = extraout_RDX_01;
                  lVar19 = local_68;
                }
                else {
                  if (pcVar24 <= pcVar17 + 1) goto LAB_011c9541;
                  pppppppcVar23 = (char *******)(ulong)(((byte)pcVar17[lVar36] & 0x3f) << 8);
                  pcVar25 = (char *)((ulong)(byte)(pcVar17 + 1)[lVar36] | (ulong)pppppppcVar23);
                  if (pcVar24 <= pcVar25) goto LAB_011c9541;
                }
                uVar29 = uVar29 - 1;
                pcVar17 = pcVar25;
                if (uVar29 == 0) goto LAB_011c9541;
              } while( true );
            }
            goto LAB_011c91de;
          }
          if (cVar2 == '\x1c') {
            if (uVar7 == 0x1000) {
              puVar21 = (undefined8 *)(lVar36 + (uVar16 & 0xffffffff));
              local_2f8 = *puVar21;
              uStack_2f0 = puVar21[1];
              local_c8 = 1;
              local_40 = 0;
              local_118._0_2_ = 0;
              local_118._2_2_ = 0;
              local_118._4_2_ = 0;
              local_118._6_2_ = 0;
              uStack_110 = local_6a;
              uStack_10e = (undefined4)local_2f8;
              sStack_10a = (short)((ulong)local_2f8 >> 0x20);
              uStack_108 = (undefined2)((ulong)local_2f8 >> 0x30);
              uStack_106 = (undefined2)uStack_2f0;
              uStack_104 = (undefined2)((ulong)uStack_2f0 >> 0x10);
              uStack_102 = (undefined2)((ulong)uStack_2f0 >> 0x20);
              uStack_100 = (undefined2)((ulong)uStack_2f0 >> 0x30);
              iStack_fc = CONCAT31(iStack_fc._1_3_,1);
              local_f8 = (uint)local_f8._1_3_ << 8;
              FUN_011cb0c0(&local_168,local_120,&local_1a8,&local_118,1,1);
              uVar16 = (ulong)local_160;
              if (local_160 == 0) goto LAB_011c91d6;
              syscall();
            }
            else {
              syscall();
              uVar16 = 99;
            }
            goto LAB_011c90ee;
          }
        }
        goto LAB_011c91de;
      }
    }
LAB_011c9110:
    lVar8 = lVar8 + 1;
  } while (lVar8 != lVar19);
  if (local_78 != 0) {
    if (bVar38) {
      local_288[0] = local_78;
      plVar13 = local_288;
      pppppppcVar23 = local_58;
    }
    else {
      local_298[0] = local_128;
      plVar13 = local_298;
      pppppppcVar23 = local_d0;
    }
    plVar13[1] = (long)pppppppcVar23;
    lVar8 = *plVar13;
    local_118._0_2_ = (ushort)lVar8;
    local_118._2_2_ = (undefined2)((ulong)lVar8 >> 0x10);
    local_118._4_2_ = (undefined2)((ulong)lVar8 >> 0x20);
    local_118._6_2_ = (undefined2)((ulong)lVar8 >> 0x30);
    lVar8 = plVar13[1];
    uStack_110 = (ushort)lVar8;
    uStack_10e = (undefined4)((ulong)lVar8 >> 0x10);
    sStack_10a = (short)((ulong)lVar8 >> 0x30);
    local_c0 = 1;
    local_f8 = CONCAT31(local_f8._1_3_,1);
    FUN_011cb0c0(&local_168,local_120,&local_1a8,&local_118,1,1);
    uVar16 = (ulong)local_160;
    if (local_160 != 0) {
      syscall();
      goto LAB_011c90ee;
    }
  }
  syscall();
  uVar16 = 0x66;
  if (local_88 != 0) {
    uVar16 = 0;
  }
  goto LAB_011c90ee;
LAB_011c9467:
  if (local_58 != (char *******)0x0) {
    pppppppcVar12 = (char *******)((long)local_58 - 1);
    if (*(char *)((long)local_58 + local_78 + -1) != '.') {
      pppppppcVar12 = local_58;
    }
    pppppppcVar23 = local_58;
    if ((char *******)0xffffffffffffff00 < pppppppcVar12 + -0x20) {
      pppppppcVar18 = (char *******)0x0;
      pppppppcVar23 = (char *******)0x0;
      do {
        bVar31 = *(byte *)((long)pppppppcVar18 + local_78);
        if (bVar31 == 0x2d) {
          if (pppppppcVar23 == (char *******)0x0) goto LAB_011c9541;
LAB_011c94aa:
          pppppppcVar23 = (char *******)((long)pppppppcVar23 + 1);
        }
        else {
          if (bVar31 != 0x2e) {
            if (((byte)(bVar31 - 0x30) < 10) || ((byte)((bVar31 & 0xdf) + 0xbf) < 0x1a))
            goto LAB_011c94aa;
            goto LAB_011c9541;
          }
          pppppppcVar23 = pppppppcVar23 + -8;
          if (pppppppcVar23 < (char *******)0xffffffffffffffc1) goto LAB_011c9541;
          bVar31 = *(byte *)((long)pppppppcVar18 + local_78 + -1);
          if ((byte)(bVar31 - 0x30) < 10) {
            pppppppcVar23 = (char *******)0x0;
          }
          else {
            pppppppcVar23 = (char *******)0x0;
            if (0x19 < (byte)((bVar31 & 0xdf) + 0xbf)) goto LAB_011c9541;
          }
        }
        pppppppcVar18 = (char *******)((long)pppppppcVar18 + 1);
      } while (pppppppcVar12 != pppppppcVar18);
      pppppppcVar23 = pppppppcVar23 + -8;
      if ((char *******)0xffffffffffffffc0 < pppppppcVar23) {
        bVar31 = *(byte *)((long)pppppppcVar12 + local_78 + -1);
        bVar38 = true;
        if (((byte)(bVar31 - 0x30) < 10) || ((byte)((bVar31 & 0xdf) + 0xbf) < 0x1a)) {
LAB_011c91de:
          uVar27 = (int)local_60 - 1;
          lVar8 = local_b0;
          if ((short)uVar27 == 0) goto LAB_011c9110;
          goto LAB_011c91f6;
        }
      }
    }
  }
LAB_011c9541:
  syscall();
  uVar16 = CONCAT62((int6)((ulong)pppppppcVar23 >> 0x10),100);
  goto LAB_011c90ee;
LAB_011c9010:
  if ((code *)PTR_FUN_011fcf88 != (code *)0x0) {
    auVar40 = (*(code *)PTR_FUN_011fcf88)(7,&local_118);
    puVar22 = auVar40._8_8_;
    puVar15 = local_60;
    if ((auVar40._0_8_ == 0) || (auVar40._0_8_ == -0x16)) goto LAB_011c905d;
  }
  auVar40._8_8_ = puVar22;
  auVar40._0_8_ = 0xe4;
  syscall();
LAB_011c905d:
  uVar16 = auVar40._8_8_;
  lVar36 = -auVar40._0_8_;
  if (auVar40._0_8_ < 0xfffffffffffff001) {
    lVar36 = 0;
  }
  uVar20 = 0;
  lVar8 = 0;
  if (lVar36 == 0) {
    uVar28 = CONCAT26(sStack_10a,CONCAT42(uStack_10e,uStack_110));
    uVar11 = CONCAT26(local_118._6_2_,
                      CONCAT24(local_118._4_2_,CONCAT22(local_118._2_2_,(ushort)local_118))) *
             1000000000;
    uVar16 = SUB168(SEXT816(1000000000) *
                    SEXT816(CONCAT26(local_118._6_2_,
                                     CONCAT24(local_118._4_2_,
                                              CONCAT22(local_118._2_2_,(ushort)local_118)))),8);
    uVar20 = uVar11 + uVar28;
    lVar8 = uVar16 + (ulong)CARRY8(uVar11,uVar28) + ((long)sStack_10a >> 0xf);
  }
  lVar36 = (int)lVar8 - local_1c8;
  if ((SBORROW8((long)(int)lVar8,local_1c8) != SBORROW8(lVar36,(ulong)(uVar20 < local_1d8))) ==
      (long)(lVar36 - (ulong)(uVar20 < local_1d8)) < 0) goto LAB_011c90ce;
  goto LAB_011c8937;
}


// ---- FUN_011c9680 @ 011c9680

ulong FUN_011c9680(undefined1 (*param_1) [16],ulong param_2,undefined1 (*param_3) [16],ulong param_4
                  )

{
  undefined1 auVar1 [16];
  long lVar2;
  ulong uVar3;
  undefined1 (*pauVar4) [16];
  
  pauVar4 = param_1;
  if (param_2 == 0) {
    pauVar4 = (undefined1 (*) [16])0x1;
  }
  if (param_4 == 0) {
    param_3 = (undefined1 (*) [16])0x1;
  }
  if (param_2 == param_4) {
    uVar3 = 1;
    if (pauVar4 != param_3 && param_2 != 0) {
      if (0x10 < param_2) {
        if (param_2 < 0x21) {
          auVar1 = vpor_avx(*param_1 ^ *param_3,
                            *(undefined1 (*) [16])(param_1[-1] + param_2) ^
                            *(undefined1 (*) [16])(param_3[-1] + param_2));
          return (ulong)(auVar1 == (undefined1  [16])0x0);
        }
        uVar3 = param_2 - 1 >> 5;
        lVar2 = 0;
        do {
          if (*(undefined1 (*) [32])(*pauVar4 + lVar2) != *(undefined1 (*) [32])(*param_3 + lVar2))
          {
            return 0;
          }
          lVar2 = lVar2 + 0x20;
          uVar3 = uVar3 - 1;
        } while (uVar3 != 0);
        return (ulong)(*(undefined1 (*) [32])(pauVar4[-2] + param_2) ==
                      *(undefined1 (*) [32])(param_3[-2] + param_2));
      }
      if (param_2 < 4) {
        return (ulong)((*param_1)[param_2 >> 1] == (*param_3)[param_2 >> 1] &&
                      (param_1[-1][param_2 + 0xf] == param_3[-1][param_2 + 0xf] &&
                      (*param_1)[0] == (*param_3)[0]));
      }
      uVar3 = (ulong)((uint)param_2 >> 1 & 0xc);
      lVar2 = (param_2 - 4) - uVar3;
      return CONCAT71((int7)((ulong)lVar2 >> 8),
                      *(int *)((long)param_3 + lVar2) == *(int *)((long)param_1 + lVar2) &&
                      (*(int *)(*param_3 + uVar3) == *(int *)(*param_1 + uVar3) &&
                      (*(int *)*param_3 == *(int *)*param_1 &&
                      *(int *)(param_3[-1] + param_2 + 0xc) == *(int *)(param_1[-1] + param_2 + 0xc)
                      )));
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}


// ---- FUN_011c97a0 @ 011c97a0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_011c97a0(undefined1 (*param_1) [16],long param_2,ulong param_3,ulong param_4,char param_5)

{
  undefined1 auVar1 [16];
  ulong uVar2;
  ulong uVar3;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [32];
  undefined1 auVar7 [32];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar13 [16];
  undefined1 auVar8 [32];
  undefined1 auVar9 [32];
  undefined1 auVar12 [32];
  
  if (param_4 < param_3) {
    if (param_4 + 0x40 < param_3) {
      auVar6[1] = param_5;
      auVar6[0] = param_5;
      auVar6[2] = param_5;
      auVar6[3] = param_5;
      auVar6[4] = param_5;
      auVar6[5] = param_5;
      auVar6[6] = param_5;
      auVar6[7] = param_5;
      auVar6[8] = param_5;
      auVar6[9] = param_5;
      auVar6[10] = param_5;
      auVar6[0xb] = param_5;
      auVar6[0xc] = param_5;
      auVar6[0xd] = param_5;
      auVar6[0xe] = param_5;
      auVar6[0xf] = param_5;
      auVar6[0x10] = param_5;
      auVar6[0x11] = param_5;
      auVar6[0x12] = param_5;
      auVar6[0x13] = param_5;
      auVar6[0x14] = param_5;
      auVar6[0x15] = param_5;
      auVar6[0x16] = param_5;
      auVar6[0x17] = param_5;
      auVar6[0x18] = param_5;
      auVar6[0x19] = param_5;
      auVar6[0x1a] = param_5;
      auVar6[0x1b] = param_5;
      auVar6[0x1c] = param_5;
      auVar6[0x1d] = param_5;
      auVar6[0x1e] = param_5;
      auVar6[0x1f] = param_5;
      do {
        uVar2 = param_4;
        auVar7 = vpcmpeqb_avx2(auVar6,*(undefined1 (*) [32])(param_2 + uVar2));
        if ((((((((((((((((((((((((((((((((SUB321(auVar7 >> 7,0) & 1) != 0 ||
                                         (SUB321(auVar7 >> 0xf,0) & 1) != 0) ||
                                        (SUB321(auVar7 >> 0x17,0) & 1) != 0) ||
                                       (SUB321(auVar7 >> 0x1f,0) & 1) != 0) ||
                                      (SUB321(auVar7 >> 0x27,0) & 1) != 0) ||
                                     (SUB321(auVar7 >> 0x2f,0) & 1) != 0) ||
                                    (SUB321(auVar7 >> 0x37,0) & 1) != 0) ||
                                   (SUB321(auVar7 >> 0x3f,0) & 1) != 0) ||
                                  (SUB321(auVar7 >> 0x47,0) & 1) != 0) ||
                                 (SUB321(auVar7 >> 0x4f,0) & 1) != 0) ||
                                (SUB321(auVar7 >> 0x57,0) & 1) != 0) ||
                               (SUB321(auVar7 >> 0x5f,0) & 1) != 0) ||
                              (SUB321(auVar7 >> 0x67,0) & 1) != 0) ||
                             (SUB321(auVar7 >> 0x6f,0) & 1) != 0) ||
                            (SUB321(auVar7 >> 0x77,0) & 1) != 0) || SUB321(auVar7 >> 0x7f,0) != '\0'
                           ) || (SUB321(auVar7 >> 0x87,0) & 1) != 0) ||
                         (SUB321(auVar7 >> 0x8f,0) & 1) != 0) || (SUB321(auVar7 >> 0x97,0) & 1) != 0
                        ) || (SUB321(auVar7 >> 0x9f,0) & 1) != 0) ||
                      (SUB321(auVar7 >> 0xa7,0) & 1) != 0) || (SUB321(auVar7 >> 0xaf,0) & 1) != 0)
                    || (SUB321(auVar7 >> 0xb7,0) & 1) != 0) || SUB321(auVar7 >> 0xbf,0) != '\0') ||
                  (SUB321(auVar7 >> 199,0) & 1) != 0) || (SUB321(auVar7 >> 0xcf,0) & 1) != 0) ||
                (SUB321(auVar7 >> 0xd7,0) & 1) != 0) || (SUB321(auVar7 >> 0xdf,0) & 1) != 0) ||
              (SUB321(auVar7 >> 0xe7,0) & 1) != 0) || (SUB321(auVar7 >> 0xef,0) & 1) != 0) ||
            (SUB321(auVar7 >> 0xf7,0) & 1) != 0) || auVar7[0x1f] < '\0') {
          auVar4._4_4_ = DAT_010014a4;
          auVar4._0_4_ = DAT_010014a4;
          auVar4._8_4_ = DAT_010014a4;
          auVar4._12_4_ = DAT_010014a4;
          auVar8._16_4_ = DAT_010014a4;
          auVar8._0_16_ = auVar4;
          auVar8._20_4_ = DAT_010014a4;
          auVar8._24_4_ = DAT_010014a4;
          auVar8._28_4_ = DAT_010014a4;
          auVar6 = vpblendvb_avx2(auVar8,_DAT_01001420,auVar7);
          auVar1 = vpminub_avx(auVar6._0_16_,auVar6._16_16_);
          auVar13 = vpshufd_avx(auVar1,0xee);
          auVar13 = vpand_avx(auVar13,auVar4);
          auVar1 = vpminub_avx(auVar1,auVar13);
          auVar13 = vpshufd_avx(auVar1,0x55);
          auVar13 = vpand_avx(auVar13,auVar4);
          auVar1 = vpminub_avx(auVar1,auVar13);
          auVar13 = vpsrld_avx(auVar1,0x10);
          auVar13 = vpand_avx(auVar13,auVar4);
          auVar1 = vpminub_avx(auVar1,auVar13);
          auVar13 = vpsrlw_avx(auVar1,8);
          auVar13 = vpand_avx(auVar13,auVar4);
          auVar13 = vpminub_avx(auVar1,auVar13);
          param_4 = (ulong)(auVar13._0_4_ & 0xffff);
          goto LAB_011c99af;
        }
        auVar7 = vpcmpeqb_avx2(auVar6,*(undefined1 (*) [32])(param_2 + 0x20 + uVar2));
        if ((((((((((((((((((((((((((((((((SUB321(auVar7 >> 7,0) & 1) != 0 ||
                                         (SUB321(auVar7 >> 0xf,0) & 1) != 0) ||
                                        (SUB321(auVar7 >> 0x17,0) & 1) != 0) ||
                                       (SUB321(auVar7 >> 0x1f,0) & 1) != 0) ||
                                      (SUB321(auVar7 >> 0x27,0) & 1) != 0) ||
                                     (SUB321(auVar7 >> 0x2f,0) & 1) != 0) ||
                                    (SUB321(auVar7 >> 0x37,0) & 1) != 0) ||
                                   (SUB321(auVar7 >> 0x3f,0) & 1) != 0) ||
                                  (SUB321(auVar7 >> 0x47,0) & 1) != 0) ||
                                 (SUB321(auVar7 >> 0x4f,0) & 1) != 0) ||
                                (SUB321(auVar7 >> 0x57,0) & 1) != 0) ||
                               (SUB321(auVar7 >> 0x5f,0) & 1) != 0) ||
                              (SUB321(auVar7 >> 0x67,0) & 1) != 0) ||
                             (SUB321(auVar7 >> 0x6f,0) & 1) != 0) ||
                            (SUB321(auVar7 >> 0x77,0) & 1) != 0) || SUB321(auVar7 >> 0x7f,0) != '\0'
                           ) || (SUB321(auVar7 >> 0x87,0) & 1) != 0) ||
                         (SUB321(auVar7 >> 0x8f,0) & 1) != 0) || (SUB321(auVar7 >> 0x97,0) & 1) != 0
                        ) || (SUB321(auVar7 >> 0x9f,0) & 1) != 0) ||
                      (SUB321(auVar7 >> 0xa7,0) & 1) != 0) || (SUB321(auVar7 >> 0xaf,0) & 1) != 0)
                    || (SUB321(auVar7 >> 0xb7,0) & 1) != 0) || SUB321(auVar7 >> 0xbf,0) != '\0') ||
                  (SUB321(auVar7 >> 199,0) & 1) != 0) || (SUB321(auVar7 >> 0xcf,0) & 1) != 0) ||
                (SUB321(auVar7 >> 0xd7,0) & 1) != 0) || (SUB321(auVar7 >> 0xdf,0) & 1) != 0) ||
              (SUB321(auVar7 >> 0xe7,0) & 1) != 0) || (SUB321(auVar7 >> 0xef,0) & 1) != 0) ||
            (SUB321(auVar7 >> 0xf7,0) & 1) != 0) || auVar7[0x1f] < '\0') {
          auVar5._4_4_ = DAT_010014a4;
          auVar5._0_4_ = DAT_010014a4;
          auVar5._8_4_ = DAT_010014a4;
          auVar5._12_4_ = DAT_010014a4;
          auVar9._16_4_ = DAT_010014a4;
          auVar9._0_16_ = auVar5;
          auVar9._20_4_ = DAT_010014a4;
          auVar9._24_4_ = DAT_010014a4;
          auVar9._28_4_ = DAT_010014a4;
          auVar6 = vpblendvb_avx2(auVar9,_DAT_01001420,auVar7);
          auVar1 = vpminub_avx(auVar6._0_16_,auVar6._16_16_);
          auVar13 = vpshufd_avx(auVar1,0xee);
          auVar13 = vpand_avx(auVar13,auVar5);
          auVar1 = vpminub_avx(auVar1,auVar13);
          auVar13 = vpshufd_avx(auVar1,0x55);
          auVar13 = vpand_avx(auVar13,auVar5);
          auVar1 = vpminub_avx(auVar1,auVar13);
          auVar13 = vpsrld_avx(auVar1,0x10);
          auVar13 = vpand_avx(auVar13,auVar5);
          auVar1 = vpminub_avx(auVar1,auVar13);
          auVar13 = vpsrlw_avx(auVar1,8);
          auVar13 = vpand_avx(auVar13,auVar5);
          auVar13 = vpminub_avx(auVar1,auVar13);
          uVar2 = (auVar13._0_4_ & 0xffff) + uVar2 + 0x20;
          goto LAB_011c9a25;
        }
        param_4 = uVar2 + 0x40;
      } while (uVar2 + 0x80 < param_3);
      uVar2 = uVar2 + 0x60;
    }
    else {
      uVar2 = param_4 + 0x20;
    }
    uVar3 = param_4;
    if ((uVar2 < param_3) &&
       (auVar7[1] = param_5, auVar7[0] = param_5, auVar7[2] = param_5, auVar7[3] = param_5,
       auVar7[4] = param_5, auVar7[5] = param_5, auVar7[6] = param_5, auVar7[7] = param_5,
       auVar7[8] = param_5, auVar7[9] = param_5, auVar7[10] = param_5, auVar7[0xb] = param_5,
       auVar7[0xc] = param_5, auVar7[0xd] = param_5, auVar7[0xe] = param_5, auVar7[0xf] = param_5,
       auVar7[0x10] = param_5, auVar7[0x11] = param_5, auVar7[0x12] = param_5,
       auVar7[0x13] = param_5, auVar7[0x14] = param_5, auVar7[0x15] = param_5,
       auVar7[0x16] = param_5, auVar7[0x17] = param_5, auVar7[0x18] = param_5,
       auVar7[0x19] = param_5, auVar7[0x1a] = param_5, auVar7[0x1b] = param_5,
       auVar7[0x1c] = param_5, auVar7[0x1d] = param_5, auVar7[0x1e] = param_5,
       auVar7[0x1f] = param_5,
       auVar6 = vpcmpeqb_avx2(auVar7,*(undefined1 (*) [32])(param_2 + param_4)), uVar3 = uVar2,
       (((((((((((((((((((((((((((((((SUB321(auVar6 >> 7,0) & 1) != 0 ||
                                    (SUB321(auVar6 >> 0xf,0) & 1) != 0) ||
                                   (SUB321(auVar6 >> 0x17,0) & 1) != 0) ||
                                  (SUB321(auVar6 >> 0x1f,0) & 1) != 0) ||
                                 (SUB321(auVar6 >> 0x27,0) & 1) != 0) ||
                                (SUB321(auVar6 >> 0x2f,0) & 1) != 0) ||
                               (SUB321(auVar6 >> 0x37,0) & 1) != 0) ||
                              (SUB321(auVar6 >> 0x3f,0) & 1) != 0) ||
                             (SUB321(auVar6 >> 0x47,0) & 1) != 0) ||
                            (SUB321(auVar6 >> 0x4f,0) & 1) != 0) ||
                           (SUB321(auVar6 >> 0x57,0) & 1) != 0) ||
                          (SUB321(auVar6 >> 0x5f,0) & 1) != 0) ||
                         (SUB321(auVar6 >> 0x67,0) & 1) != 0) || (SUB321(auVar6 >> 0x6f,0) & 1) != 0
                        ) || (SUB321(auVar6 >> 0x77,0) & 1) != 0) ||
                      SUB321(auVar6 >> 0x7f,0) != '\0') || (SUB321(auVar6 >> 0x87,0) & 1) != 0) ||
                    (SUB321(auVar6 >> 0x8f,0) & 1) != 0) || (SUB321(auVar6 >> 0x97,0) & 1) != 0) ||
                  (SUB321(auVar6 >> 0x9f,0) & 1) != 0) || (SUB321(auVar6 >> 0xa7,0) & 1) != 0) ||
                (SUB321(auVar6 >> 0xaf,0) & 1) != 0) || (SUB321(auVar6 >> 0xb7,0) & 1) != 0) ||
              SUB321(auVar6 >> 0xbf,0) != '\0') || (SUB321(auVar6 >> 199,0) & 1) != 0) ||
            (SUB321(auVar6 >> 0xcf,0) & 1) != 0) || (SUB321(auVar6 >> 0xd7,0) & 1) != 0) ||
          (SUB321(auVar6 >> 0xdf,0) & 1) != 0) || (SUB321(auVar6 >> 0xe7,0) & 1) != 0) ||
        (SUB321(auVar6 >> 0xef,0) & 1) != 0) || (SUB321(auVar6 >> 0xf7,0) & 1) != 0) ||
       auVar6[0x1f] < '\0')) {
      auVar10._4_4_ = DAT_010014a4;
      auVar10._0_4_ = DAT_010014a4;
      auVar10._8_4_ = DAT_010014a4;
      auVar10._12_4_ = DAT_010014a4;
      auVar12._16_4_ = DAT_010014a4;
      auVar12._0_16_ = auVar10;
      auVar12._20_4_ = DAT_010014a4;
      auVar12._24_4_ = DAT_010014a4;
      auVar12._28_4_ = DAT_010014a4;
      auVar6 = vpblendvb_avx2(auVar12,_DAT_01001420,auVar6);
      auVar1 = vpminub_avx(auVar6._0_16_,auVar6._16_16_);
      auVar13 = vpshufd_avx(auVar1,0xee);
      auVar13 = vpand_avx(auVar13,auVar10);
      auVar1 = vpminub_avx(auVar1,auVar13);
      auVar13 = vpshufd_avx(auVar1,0x55);
      auVar13 = vpand_avx(auVar13,auVar10);
      auVar1 = vpminub_avx(auVar1,auVar13);
      auVar13 = vpsrld_avx(auVar1,0x10);
      auVar13 = vpand_avx(auVar13,auVar10);
      auVar1 = vpminub_avx(auVar1,auVar13);
      auVar13 = vpsrlw_avx(auVar1,8);
      auVar13 = vpand_avx(auVar13,auVar10);
      auVar13 = vpminub_avx(auVar1,auVar13);
      uVar2 = (ulong)(auVar13._0_4_ & 0xffff);
LAB_011c99af:
      *(ulong *)*param_1 = param_4 + uVar2;
      (*param_1)[8] = 1;
      return;
    }
    uVar2 = uVar3;
    if ((uVar3 + 0x10 < param_3) &&
       (auVar13[1] = param_5, auVar13[0] = param_5, auVar13[2] = param_5, auVar13[3] = param_5,
       auVar13[4] = param_5, auVar13[5] = param_5, auVar13[6] = param_5, auVar13[7] = param_5,
       auVar13[8] = param_5, auVar13[9] = param_5, auVar13[10] = param_5, auVar13[0xb] = param_5,
       auVar13[0xc] = param_5, auVar13[0xd] = param_5, auVar13[0xe] = param_5,
       auVar13[0xf] = param_5,
       auVar13 = vpcmpeqb_avx(auVar13,*(undefined1 (*) [16])(param_2 + uVar3)), uVar2 = uVar3 + 0x10
       , (((((((((((((((SUB161(auVar13 >> 7,0) & 1) != 0 || (SUB161(auVar13 >> 0xf,0) & 1) != 0) ||
                     (SUB161(auVar13 >> 0x17,0) & 1) != 0) || (SUB161(auVar13 >> 0x1f,0) & 1) != 0)
                   || (SUB161(auVar13 >> 0x27,0) & 1) != 0) || (SUB161(auVar13 >> 0x2f,0) & 1) != 0)
                 || (SUB161(auVar13 >> 0x37,0) & 1) != 0) || (SUB161(auVar13 >> 0x3f,0) & 1) != 0)
               || (SUB161(auVar13 >> 0x47,0) & 1) != 0) || (SUB161(auVar13 >> 0x4f,0) & 1) != 0) ||
             (SUB161(auVar13 >> 0x57,0) & 1) != 0) || (SUB161(auVar13 >> 0x5f,0) & 1) != 0) ||
           (SUB161(auVar13 >> 0x67,0) & 1) != 0) || (SUB161(auVar13 >> 0x6f,0) & 1) != 0) ||
         (SUB161(auVar13 >> 0x77,0) & 1) != 0) || auVar13[0xf] < '\0')) {
      auVar11._4_4_ = DAT_0100148c;
      auVar11._0_4_ = DAT_0100148c;
      auVar11._8_4_ = DAT_0100148c;
      auVar11._12_4_ = DAT_0100148c;
      auVar13 = vpblendvb_avx(auVar11,_DAT_010008e0,auVar13);
      auVar1 = vpshufd_avx(auVar13,0xee);
      auVar1 = vpminub_avx(auVar13,auVar1);
      auVar13 = vpshufd_avx(auVar1,0x55);
      auVar13 = vpand_avx(auVar13,auVar11);
      auVar1 = vpminub_avx(auVar1,auVar13);
      auVar13 = vpsrld_avx(auVar1,0x10);
      auVar13 = vpand_avx(auVar13,auVar11);
      auVar1 = vpminub_avx(auVar1,auVar13);
      auVar13 = vpsrlw_avx(auVar1,8);
      auVar13 = vpand_avx(auVar13,auVar11);
      auVar13 = vpminub_avx(auVar1,auVar13);
      *(ulong *)*param_1 = uVar3 + (auVar13._0_4_ & 0xffff);
      (*param_1)[8] = 1;
      return;
    }
    for (; param_3 != uVar2; uVar2 = uVar2 + 1) {
      if (*(char *)(param_2 + uVar2) == param_5) {
LAB_011c9a25:
        *(ulong *)*param_1 = uVar2;
        (*param_1)[8] = 1;
        return;
      }
    }
  }
  *param_1 = (undefined1  [16])0x0;
  return;
}


// ---- FUN_011c9a40 @ 011c9a40

short FUN_011c9a40(undefined8 *param_1,ulong param_2,ulong param_3)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  ulong uVar4;
  undefined1 local_40 [8];
  short local_38;
  
  uVar4 = param_1[3];
  uVar1 = param_1[2] - uVar4;
  while( true ) {
    if (param_3 <= uVar1) {
      return 0;
    }
    lVar2 = uVar4 - param_2;
    if (uVar4 < param_2) {
      lVar2 = 0;
    }
    lVar3 = uVar4 - lVar2;
    param_1[3] = lVar2;
    (**(code **)*param_1)(local_40,param_1,&PTR_s__011b9ad0_0x20_0100ee88,1,1);
    if (local_38 != 0) break;
    FUN_011f41f0(param_1[3] + param_1[1],lVar2 + param_1[1],lVar3);
    uVar4 = lVar3 + param_1[3];
    param_1[3] = uVar4;
    uVar1 = param_1[2] - uVar4;
  }
  param_1[3] = param_1[3] + lVar3;
  return local_38;
}


// ---- FUN_011c9af0 @ 011c9af0

short FUN_011c9af0(undefined8 *param_1)

{
  code *pcVar1;
  undefined1 local_30 [8];
  short local_28;
  
  pcVar1 = *(code **)*param_1;
  do {
    if (param_1[3] == 0) {
      return 0;
    }
    (*pcVar1)(local_30,param_1,&PTR_s__011b9ad0_0x20_0100ee88,1,1);
  } while (local_28 == 0);
  return local_28;
}


// ---- FUN_011c9b50 @ 011c9b50

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 * FUN_011c9b50(undefined8 *param_1)

{
  undefined8 uVar1;
  
  uVar1 = _UNK_01000288;
  *param_1 = _DAT_01000280;
  param_1[1] = uVar1;
  return param_1;
}


// ---- FUN_011c9b70 @ 011c9b70

undefined2 FUN_011c9b70(void)

{
  return 0x68;
}


// ---- FUN_011c9b80 @ 011c9b80

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 * FUN_011c9b80(undefined8 *param_1)

{
  undefined8 uVar1;
  
  uVar1 = _UNK_010004c8;
  *param_1 = _DAT_010004c0;
  param_1[1] = uVar1;
  return param_1;
}


// ---- FUN_011c9ba0 @ 011c9ba0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 * FUN_011c9ba0(undefined8 *param_1)

{
  undefined8 uVar1;
  
  uVar1 = _UNK_010004c8;
  *param_1 = _DAT_010004c0;
  param_1[1] = uVar1;
  return param_1;
}


// ---- FUN_011c9bc0 @ 011c9bc0

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_011c9bc0(ulong *param_1,byte *param_2,ulong param_3,undefined8 param_4,byte param_5)

{
  byte bVar1;
  ushort uVar2;
  undefined1 auVar3 [16];
  bool bVar4;
  bool bVar5;
  ulong uVar6;
  byte bVar7;
  byte bVar8;
  short sVar9;
  byte bVar10;
  byte bVar11;
  ulong uVar12;
  int iVar13;
  ulong uVar14;
  byte bVar15;
  char cVar16;
  undefined1 local_48 [16];
  undefined4 local_38;
  bool local_31;
  
  if (param_3 < 2) goto LAB_011c9bd7;
  bVar10 = *param_2;
  if (((((6 < param_3) && ((byte)(((byte)(bVar10 + 0xbf) < 0x1a) << 5 | bVar10) == 0x3a)) &&
       ((byte)(((byte)(param_2[1] + 0xbf) < 0x1a) << 5 | param_2[1]) == 0x3a)) &&
      (((byte)(((byte)(param_2[2] + 0xbf) < 0x1a) << 5 | param_2[2]) == 0x66 &&
       ((byte)(((byte)(param_2[3] + 0xbf) < 0x1a) << 5 | param_2[3]) == 0x66)))) &&
     (((byte)(((byte)(param_2[4] + 0xbf) < 0x1a) << 5 | param_2[4]) == 0x66 &&
      (((byte)(((byte)(param_2[5] + 0xbf) < 0x1a) << 5 | param_2[5]) == 0x66 &&
       ((byte)(((byte)(param_2[6] + 0xbf) < 0x1a) << 5 | param_2[6]) == 0x3a)))))) {
    local_38 = 0;
    if (param_3 != 7) {
      uVar14 = 7;
      bVar11 = 0;
      bVar10 = 0;
      bVar4 = false;
      do {
        bVar8 = param_2[uVar14];
        if (bVar8 == 0x2e) {
          if (!(bool)(bVar4 & bVar11 != 3)) goto LAB_011c9ea5;
          bVar11 = bVar11 + 1;
          bVar10 = 0;
        }
        else {
          bVar1 = bVar8 - 0x30;
          if ((9 < bVar1) || (bVar15 = bVar4 | bVar8 != 0x30, (bool)(bVar10 & bVar15)))
          goto LAB_011c9ea5;
          sVar9 = (ushort)*(byte *)((long)&local_38 + (ulong)bVar11) * 10;
          if ((char)((ushort)sVar9 >> 8) != '\0') goto LAB_011c9ea5;
          bVar7 = (byte)sVar9;
          local_31 = CARRY1(bVar7,bVar1);
          if (CARRY1(bVar7,bVar1)) goto LAB_011c9ea5;
          bVar10 = bVar15 ^ 1;
          *(byte *)((long)&local_38 + (ulong)bVar11) = bVar7 + bVar1;
        }
        uVar14 = uVar14 + 1;
        bVar4 = bVar8 != 0x2e;
      } while (param_3 != uVar14);
      if (bVar8 != 0x2e && bVar11 == 3) {
        *(undefined1 *)(param_1 + 4) = 0;
        param_1[2] = 0;
        *(undefined4 *)(param_1 + 3) = 0xffff0000;
        *(char *)((long)param_1 + 0x1c) = (char)local_38;
        *(char *)((long)param_1 + 0x1d) = (char)((uint)local_38 >> 8);
        *(char *)((long)param_1 + 0x1e) = (char)((uint)local_38 >> 0x10);
        *(char *)((long)param_1 + 0x1f) = (char)((uint)local_38 >> 0x18);
        *param_1 = 0;
        param_1[1] = 0;
        return;
      }
    }
LAB_011c9ea5:
    *(undefined1 *)(param_1 + 4) = 5;
    *param_1 = 7;
    return;
  }
  local_48._0_12_ = ZEXT812(0);
  local_48._12_4_ = 0;
  bVar11 = 0;
  uVar14 = 0;
  bVar4 = false;
  bVar5 = false;
  cVar16 = '\0';
  switch(bVar10) {
  case 0x25:
switchD_011c9cee_caseD_25:
    if (bVar4) {
      uVar12 = (ulong)(byte)((char)uVar14 + 1);
      uVar14 = param_3 - uVar12;
      if (uVar14 == 0) {
LAB_011c9bd7:
        param_1[4] = DAT_0100eeb8;
        uVar6 = _UNK_0100eeb0;
        uVar12 = _UNK_0100eea8;
        uVar14 = _UNK_0100eea0;
        *param_1 = _DAT_0100ee98;
        param_1[1] = uVar14;
        param_1[2] = uVar12;
        param_1[3] = uVar6;
        return;
      }
      param_2 = param_2 + uVar12;
      bVar8 = bVar11 + 1;
      uVar12 = param_3 & 0xff;
      bVar11 = param_5;
joined_r0x011c9eeb:
      if (param_3 != uVar12) {
        *(undefined1 *)(param_1 + 4) = 3;
        *param_1 = uVar12;
        return;
      }
      if (bVar5) {
LAB_011c9f00:
        iVar13 = (uint)bVar8 - (uint)bVar11;
        FUN_011f41f0(local_48 + (uint)((8 - iVar13) * 2),local_48 + (ulong)bVar11 * 2,iVar13 * 2);
        FUN_011f4160(local_48 + (ulong)bVar11 * 2,0,0x10 - (ulong)((uint)bVar8 * 2));
      }
      else if (bVar8 != 8) goto LAB_011c9bd7;
      auVar3 = vpshufb_avx(local_48,_DAT_010003e0);
      *(undefined1 *)(param_1 + 4) = 0;
      local_48._0_8_ = auVar3._0_8_;
      local_48._8_8_ = auVar3._8_8_;
      param_1[2] = local_48._0_8_;
      param_1[3] = local_48._8_8_;
      *param_1 = (ulong)param_2;
      param_1[1] = uVar14;
      return;
    }
    break;
  case 0x26:
  case 0x27:
  case 0x28:
  case 0x29:
  case 0x2a:
  case 0x2b:
  case 0x2c:
  case 0x2d:
  case 0x2e:
  case 0x2f:
  case 0x3b:
  case 0x3c:
  case 0x3d:
  case 0x3e:
  case 0x3f:
  case 0x40:
  case 0x47:
  case 0x48:
  case 0x49:
  case 0x4a:
  case 0x4b:
  case 0x4c:
  case 0x4d:
  case 0x4e:
  case 0x4f:
  case 0x50:
  case 0x51:
  case 0x52:
  case 0x53:
  case 0x54:
  case 0x55:
  case 0x56:
  case 0x57:
  case 0x58:
  case 0x59:
  case 0x5a:
  case 0x5b:
  case 0x5c:
  case 0x5d:
  case 0x5e:
  case 0x5f:
  case 0x60:
    break;
  case 0x30:
  case 0x31:
  case 0x32:
  case 0x33:
  case 0x34:
  case 0x35:
  case 0x36:
  case 0x37:
  case 0x38:
  case 0x39:
switchD_011c9cee_caseD_30:
    uVar2 = *(ushort *)(local_48 + (ulong)bVar11 * 2);
    local_38 = CONCAT31(local_38._1_3_,0xfff < uVar2);
    if (0xfff < uVar2) {
LAB_011ca093:
      *(undefined1 *)(param_1 + 4) = 6;
      goto LAB_011c9d8d;
    }
    *(ushort *)(local_48 + (ulong)bVar11 * 2) = (ushort)(byte)(bVar10 - 0x30) + uVar2 * 0x10;
    if (cVar16 == '\x04') break;
    uVar14 = (uVar14 & 0xff) + 1;
    if (param_3 == uVar14) {
LAB_011ca09c:
      bVar10 = (byte)uVar14;
      bVar8 = bVar11 + 1;
LAB_011c9ee0:
      param_2 = (byte *)0x0;
      uVar14 = 0;
      uVar12 = (ulong)bVar10;
      bVar11 = param_5;
      goto joined_r0x011c9eeb;
    }
    bVar10 = param_2[uVar14];
    if (0x41 < (byte)(bVar10 - 0x25)) break;
    cVar16 = cVar16 + '\x01';
    bVar4 = true;
    switch(bVar10) {
    case 0x25:
      goto switchD_011c9cee_caseD_25;
    default:
      break;
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x38:
    case 0x39:
      goto switchD_011c9cee_caseD_30;
    case 0x3a:
switchD_011c9cee_caseD_3a:
      bVar10 = (byte)uVar14;
      if (bVar4) {
        bVar11 = bVar11 + 1;
        if (bVar11 == 8) {
          bVar8 = 8;
          goto LAB_011c9ee0;
        }
        uVar14 = (uVar14 & 0xff) + 1;
        if (param_3 == uVar14) goto LAB_011c9bd7;
        bVar10 = param_2[uVar14];
        bVar4 = false;
        cVar16 = '\0';
        switch(bVar10) {
        case 0x25:
          goto switchD_011c9cee_caseD_25;
        default:
          goto switchD_011c9cee_caseD_26;
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
          goto switchD_011c9cee_caseD_30;
        case 0x3a:
          goto switchD_011c9cee_caseD_3a;
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x45:
        case 0x46:
          goto switchD_011c9cee_caseD_41;
        case 0x61:
        case 0x62:
        case 99:
        case 100:
        case 0x65:
        case 0x66:
          goto switchD_011c9cee_caseD_61;
        }
      }
      if (bVar5) break;
      if ((bVar10 == 0) && (bVar10 = 1, param_2[1] != 0x3a)) {
        *(undefined1 *)(param_1 + 4) = 1;
        *param_1 = 1;
        return;
      }
      uVar14 = (ulong)bVar10 + 1;
      if (param_3 == uVar14) {
        param_2 = (byte *)0x0;
        uVar14 = 0;
        bVar8 = bVar11;
        goto LAB_011c9f00;
      }
      bVar10 = param_2[uVar14];
      bVar5 = true;
      bVar4 = false;
      cVar16 = '\0';
      param_5 = bVar11;
      switch(bVar10) {
      case 0x25:
        goto switchD_011c9cee_caseD_25;
      default:
        break;
      case 0x30:
      case 0x31:
      case 0x32:
      case 0x33:
      case 0x34:
      case 0x35:
      case 0x36:
      case 0x37:
      case 0x38:
      case 0x39:
        goto switchD_011c9cee_caseD_30;
      case 0x3a:
        goto switchD_011c9cee_caseD_3a;
      case 0x41:
      case 0x42:
      case 0x43:
      case 0x44:
      case 0x45:
      case 0x46:
        goto switchD_011c9cee_caseD_41;
      case 0x61:
      case 0x62:
      case 99:
      case 100:
      case 0x65:
      case 0x66:
switchD_011c9cee_caseD_61:
        uVar2 = *(ushort *)(local_48 + (ulong)bVar11 * 2);
        local_38 = CONCAT31(local_38._1_3_,0xfff < uVar2);
        if (0xfff < uVar2) goto LAB_011ca093;
        *(ushort *)(local_48 + (ulong)bVar11 * 2) = (ushort)(byte)(bVar10 + 0xa9) + uVar2 * 0x10;
        if (cVar16 == '\x04') break;
        uVar14 = (uVar14 & 0xff) + 1;
        if (param_3 == uVar14) goto LAB_011ca09c;
        bVar10 = param_2[uVar14];
        if (0x41 < (byte)(bVar10 - 0x25)) break;
        cVar16 = cVar16 + '\x01';
        bVar4 = true;
        switch(bVar10) {
        case 0x25:
          goto switchD_011c9cee_caseD_25;
        default:
          break;
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
          goto switchD_011c9cee_caseD_30;
        case 0x3a:
          goto switchD_011c9cee_caseD_3a;
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x45:
        case 0x46:
          goto switchD_011c9cee_caseD_41;
        case 0x61:
        case 0x62:
        case 99:
        case 100:
        case 0x65:
        case 0x66:
          goto switchD_011c9cee_caseD_61;
        }
      }
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x46:
      goto switchD_011c9cee_caseD_41;
    case 0x61:
    case 0x62:
    case 99:
    case 100:
    case 0x65:
    case 0x66:
      goto switchD_011c9cee_caseD_61;
    }
  case 0x3a:
    goto switchD_011c9cee_caseD_3a;
  case 0x41:
  case 0x42:
  case 0x43:
  case 0x44:
  case 0x45:
  case 0x46:
switchD_011c9cee_caseD_41:
                    /* WARNING (jumptable): Sanity check requires truncation of jumptable */
                    /* WARNING: Could not find normalized switch variable to match jumptable */
    switch(bVar10) {
    case 0xe0:
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    case 0xe1:
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    case 0xe2:
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    break;
  case 0x61:
  case 0x62:
  case 99:
  case 100:
  case 0x65:
  case 0x66:
    goto switchD_011c9cee_caseD_61;
  default:
    uVar14 = 0;
  }
switchD_011c9cee_caseD_26:
  *(undefined1 *)(param_1 + 4) = 1;
LAB_011c9d8d:
  *param_1 = uVar14 & 0xff;
  return;
}


// ---- FUN_011ca0b0 @ 011ca0b0

/* WARNING: Removing unreachable block (ram,0x011ca2bb) */
/* WARNING: Removing unreachable block (ram,0x011ca271) */
/* WARNING: Removing unreachable block (ram,0x011ca280) */
/* WARNING: Removing unreachable block (ram,0x011ca287) */
/* WARNING: Removing unreachable block (ram,0x011ca28f) */
/* WARNING: Removing unreachable block (ram,0x011ca297) */
/* WARNING: Removing unreachable block (ram,0x011ca3b3) */
/* WARNING: Removing unreachable block (ram,0x011ca3b9) */
/* WARNING: Removing unreachable block (ram,0x011ca2c7) */
/* WARNING: Recovered jumptable eliminated as dead code */
/* WARNING: Removing unreachable block (ram,0x011ca2a0) */
/* WARNING: Removing unreachable block (ram,0x011ca159) */
/* WARNING: Removing unreachable block (ram,0x011ca160) */
/* WARNING: Removing unreachable block (ram,0x011ca167) */
/* WARNING: Removing unreachable block (ram,0x011ca16f) */
/* WARNING: Removing unreachable block (ram,0x011ca2ac) */
/* WARNING: Removing unreachable block (ram,0x011ca322) */
/* WARNING: Removing unreachable block (ram,0x011ca334) */
/* WARNING: Removing unreachable block (ram,0x011ca2b3) */

undefined4 FUN_011ca0b0(undefined4 *param_1,undefined8 param_2,long param_3)

{
  byte bVar1;
  ulong uVar2;
  ulong uVar3;
  long lVar4;
  long in_FS_OFFSET;
  bool bVar5;
  
  bVar1 = *(byte *)(param_3 + 8);
  lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar4 == 0) || ((*(byte *)(lVar4 + 0x21c) & 1) != 0)) {
LAB_011ca11b:
    lVar4 = 0;
  }
  else {
    uVar2 = *(ulong *)(lVar4 + 8);
    do {
      LOCK();
      uVar3 = *(ulong *)(lVar4 + 8);
      bVar5 = uVar2 == uVar3;
      if (bVar5) {
        *(ulong *)(lVar4 + 8) = uVar2 | 3;
        uVar3 = uVar2;
      }
      UNLOCK();
      uVar2 = uVar3;
    } while (!bVar5);
    if ((uVar3 & 7) != 0) {
      if (((uint)uVar3 & 7) == 6) {
        *(undefined2 *)(param_1 + 1) = 0x11;
        return 6;
      }
      goto LAB_011ca11b;
    }
  }
  if (lVar4 == 0) {
    syscall();
                    /* WARNING: Could not find normalized switch variable to match jumptable */
    switch(switchD_011ca1c8::switchdataD_01001d28) {
    case (undefined *)0x0:
      goto switchD_011ca1c8_caseD_0;
    default:
      goto switchD_011ca1c8_caseD_1;
    case (undefined *)0xc:
      goto switchD_011ca1c8_caseD_c;
    case (undefined *)0x16:
      goto switchD_011ca1c8_caseD_16;
    case (undefined *)0x17:
      goto switchD_011ca1c8_caseD_17;
    case (undefined *)0x18:
      goto switchD_011ca1c8_caseD_18;
    }
  }
  syscall();
                    /* WARNING: Could not find normalized switch variable to match jumptable */
  switch(switchD_011ca18e::switchdataD_01001be8) {
  case (undefined *)0x0:
                    /* WARNING: This code block may not be properly labeled as switch case */
    LOCK();
    *(ulong *)(lVar4 + 8) = *(ulong *)(lVar4 + 8) ^ 3;
    UNLOCK();
    break;
  default:
                    /* WARNING: This code block may not be properly labeled as switch case */
    LOCK();
    *(ulong *)(lVar4 + 8) = *(ulong *)(lVar4 + 8) ^ 3;
    UNLOCK();
switchD_011ca1c8_caseD_1:
                    /* WARNING: This code block may not be properly labeled as switch case */
    *(undefined2 *)(param_1 + 1) = 4;
    return 0x29;
  case (undefined *)0xc:
                    /* WARNING: This code block may not be properly labeled as switch case */
    LOCK();
    *(ulong *)(lVar4 + 8) = *(ulong *)(lVar4 + 8) ^ 3;
    UNLOCK();
switchD_011ca1c8_caseD_c:
                    /* WARNING: This code block may not be properly labeled as switch case */
    *(undefined2 *)(param_1 + 1) = 2;
    return 0x29;
  case (undefined *)0x16:
                    /* WARNING: This code block may not be properly labeled as switch case */
    LOCK();
    *(ulong *)(lVar4 + 8) = *(ulong *)(lVar4 + 8) ^ 3;
    UNLOCK();
switchD_011ca1c8_caseD_16:
                    /* WARNING: This code block may not be properly labeled as switch case */
    *(undefined2 *)(param_1 + 1) = 0x51;
    return 0x29;
  case (undefined *)0x17:
                    /* WARNING: This code block may not be properly labeled as switch case */
    LOCK();
    *(ulong *)(lVar4 + 8) = *(ulong *)(lVar4 + 8) ^ 3;
    UNLOCK();
switchD_011ca1c8_caseD_17:
                    /* WARNING: This code block may not be properly labeled as switch case */
    *(undefined2 *)(param_1 + 1) = 0x25;
    return 0x29;
  case (undefined *)0x18:
                    /* WARNING: This code block may not be properly labeled as switch case */
    LOCK();
    *(ulong *)(lVar4 + 8) = *(ulong *)(lVar4 + 8) ^ 3;
    UNLOCK();
switchD_011ca1c8_caseD_18:
                    /* WARNING: This code block may not be properly labeled as switch case */
    *(undefined2 *)(param_1 + 1) = 0x24;
    return 0x29;
  }
switchD_011ca1c8_caseD_0:
                    /* WARNING: This code block may not be properly labeled as switch case */
  if ((bVar1 & 1) == 0) goto LAB_011ca3a4;
  lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar4 == 0) || ((*(byte *)(lVar4 + 0x21c) & 1) != 0)) {
LAB_011ca223:
    lVar4 = 0;
  }
  else {
    uVar2 = *(ulong *)(lVar4 + 8);
    do {
      LOCK();
      uVar3 = *(ulong *)(lVar4 + 8);
      bVar5 = uVar2 == uVar3;
      if (bVar5) {
        *(ulong *)(lVar4 + 8) = uVar2 | 3;
        uVar3 = uVar2;
      }
      UNLOCK();
      uVar2 = uVar3;
    } while (!bVar5);
    if ((uVar3 & 7) != 0) {
      if (((uint)uVar3 & 7) == 6) {
        syscall();
        *(undefined2 *)(param_1 + 1) = 0x11;
        return 3;
      }
      goto LAB_011ca223;
    }
  }
  if (lVar4 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar4 + 8) = *(ulong *)(lVar4 + 8) ^ 3;
    UNLOCK();
  }
LAB_011ca3a4:
  *(undefined2 *)(param_1 + 1) = 0;
  *param_1 = 0x29;
  return 0x29;
}


// ---- FUN_011ca3d0 @ 011ca3d0

undefined8 FUN_011ca3d0(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x20) - *(long *)(param_1 + 0x18);
  FUN_011f41f0(*(long *)(param_1 + 8),*(long *)(param_1 + 8) + *(long *)(param_1 + 0x18),lVar1);
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(long *)(param_1 + 0x20) = lVar1;
  return 0;
}


// ---- FUN_011ca410 @ 011ca410

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 (*) [16] FUN_011ca410(undefined1 (*param_1) [16],long param_2,long param_3,long param_4)

{
  ulong uVar1;
  undefined1 *puVar2;
  long lVar3;
  ulong *puVar4;
  ulong uVar5;
  long lVar6;
  ulong uVar7;
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  
  if (param_4 == 0) {
    auVar8._0_12_ = ZEXT812(0);
    auVar8._12_4_ = 0;
    *param_1 = auVar8;
  }
  else {
    param_4 = param_4 + -1;
    if (param_4 == 0) {
      lVar6 = *(long *)(param_2 + 0x18);
    }
    else {
      lVar6 = *(long *)(param_2 + 0x18);
      puVar4 = (ulong *)(param_3 + 8);
      lVar3 = param_4;
      do {
        uVar1 = *puVar4;
        uVar7 = *(long *)(param_2 + 0x10) - lVar6;
        uVar5 = uVar7;
        if (uVar1 < uVar7) {
          uVar5 = uVar1;
        }
        FUN_011f4580(*(long *)(param_2 + 8) + lVar6,puVar4[-1],uVar5);
        lVar6 = uVar5 + *(long *)(param_2 + 0x18);
        *(long *)(param_2 + 0x18) = lVar6;
        auVar9 = _DAT_010004c0;
        if (uVar7 < uVar1) goto LAB_011ca555;
        puVar4 = puVar4 + 2;
        lVar3 = lVar3 + -1;
      } while (lVar3 != 0);
    }
    uVar1 = *(ulong *)(param_3 + 8 + param_4 * 0x10);
    if (uVar1 == 0) {
      auVar9._0_12_ = ZEXT812(0);
      auVar9._12_4_ = 0;
    }
    else {
      puVar2 = *(undefined1 **)(param_3 + param_4 * 0x10);
      lVar3 = *(long *)(param_2 + 8) + lVar6;
      uVar5 = *(long *)(param_2 + 0x10) - lVar6;
      if (uVar1 == 1) {
        FUN_011f4160(lVar3,*puVar2,uVar5);
        *(long *)(param_2 + 0x18) = *(long *)(param_2 + 0x18) + uVar5;
        auVar9 = _DAT_010004c0;
      }
      else {
        do {
          uVar7 = uVar5;
          if (uVar1 < uVar5) {
            uVar7 = uVar1;
          }
          uVar5 = -(uVar1 - uVar5);
          FUN_011f4580(lVar3,puVar2,uVar7);
          *(long *)(param_2 + 0x18) = *(long *)(param_2 + 0x18) + uVar7;
          lVar3 = lVar3 + uVar1;
          auVar9 = _DAT_010004c0;
        } while (!CARRY8(uVar1,uVar5));
      }
    }
LAB_011ca555:
    *param_1 = auVar9;
  }
  return param_1;
}


// ---- FUN_011ca570 @ 011ca570

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 * FUN_011ca570(undefined8 *param_1,long param_2)

{
  short sVar1;
  long lVar2;
  ulong uVar3;
  long unaff_R14;
  long lStack_40;
  ushort uStack_38;
  undefined8 local_30;
  undefined8 uStack_28;
  undefined8 local_20;
  undefined8 uStack_18;
  
  switch(*(byte *)(param_2 + 0x36) & 7) {
  default:
    lStack_40 = 0x11ca597;
    FUN_011ca5d0(&local_30);
    local_20 = local_30;
    uStack_18 = uStack_28;
    break;
  case 1:
  case 3:
    lStack_40 = 0x11ca5a7;
    FUN_011ca900(&local_20,param_2 + -0x28);
    break;
  case 4:
    local_20 = _DAT_01000690;
    uStack_18 = _UNK_01000698;
    break;
  case 5:
  case 7:
    if (*(short *)((long)param_1 + 0x5c) == 0) {
      local_30 = param_1[10];
      lStack_40 = 0x11ca7a9;
      sVar1 = (**(code **)(param_1[1] + 0x1a0))(*param_1,&local_30);
      if (sVar1 == 0) goto switchD_011ca587_caseD_6;
      *(short *)((long)param_1 + 0x5c) = sVar1;
    }
    do {
      lStack_40 = 0x11ca7ce;
      FUN_011caad0(&lStack_40,param_1 + 5,unaff_R14);
      if (uStack_38 != 0) {
        *(ushort *)((long)param_1 + 0x5c) = uStack_38;
        return (undefined8 *)(ulong)uStack_38;
      }
      unaff_R14 = unaff_R14 - lStack_40;
    } while (unaff_R14 != 0);
    lVar2 = param_1[9];
    goto LAB_011ca801;
  case 6:
switchD_011ca587_caseD_6:
    uVar3 = ((param_1[8] + param_1[2]) - param_1[9]) + unaff_R14;
    if ((ulong)param_1[2] <= uVar3) {
      param_1[8] = param_1[9];
      param_1[2] = uVar3;
      return (undefined8 *)0x0;
    }
    lVar2 = param_1[8] + unaff_R14;
LAB_011ca801:
    param_1[8] = lVar2;
    return (undefined8 *)0x0;
  }
  *param_1 = local_20;
  param_1[1] = uStack_18;
  return param_1;
}


// ---- FUN_011ca5d0 @ 011ca5d0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_011ca5d0(ulong *param_1,undefined8 *param_2,long param_3,long param_4)

{
  undefined8 uVar1;
  long lVar2;
  long lVar3;
  ulong uVar4;
  long *plVar5;
  ulong uVar6;
  undefined1 auVar7 [16];
  long local_178 [32];
  long *local_78;
  long local_70;
  ulong local_68;
  undefined1 local_48;
  ulong local_40;
  short local_38;
  short local_28;
  
  uVar1 = *param_2;
  lVar2 = param_2[1];
  lVar3 = param_2[9];
  if (param_2[8] == lVar3) {
    if (param_4 == 0) {
      local_70 = 0;
      uVar6 = 0;
    }
    else {
      plVar5 = (long *)(param_3 + 8);
      uVar6 = 0;
      local_70 = 0;
      do {
        if (local_70 == 0x10) {
          local_70 = 0x10;
          goto LAB_011ca6b3;
        }
        lVar3 = *plVar5;
        if (lVar3 != 0) {
          local_178[local_70 * 2] = plVar5[-1];
          local_178[local_70 * 2 + 1] = lVar3;
          local_70 = local_70 + 1;
          uVar6 = uVar6 + lVar3;
        }
        plVar5 = plVar5 + 2;
        param_4 = param_4 + -1;
      } while (param_4 != 0);
    }
    lVar3 = param_2[7];
    if (lVar3 != 0) {
      auVar7._0_12_ = ZEXT812(0);
      auVar7._12_4_ = 0;
      *(undefined1 (*) [16])(param_2 + 8) = auVar7;
      local_178[local_70 * 2] = param_2[6];
      local_178[local_70 * 2 + 1] = lVar3;
      local_70 = local_70 + 1;
    }
  }
  else {
    local_178[0] = param_2[6] + lVar3;
    local_178[1] = param_2[7] - lVar3;
    local_70 = 1;
    uVar6 = 0;
  }
LAB_011ca6b3:
  uVar4 = param_2[10];
  local_78 = local_178;
  local_48 = 0;
  local_68 = uVar4;
  (**(code **)(lVar2 + 0x78))(&local_40,uVar1,&local_78);
  if (local_28 == 0) {
    uVar4 = local_40;
    local_28 = local_38;
  }
  if (local_28 == 0) {
    param_2[2] = param_2[2] + uVar4;
    if (uVar4 < uVar6 || uVar4 - uVar6 == 0) {
      *(undefined2 *)(param_1 + 1) = 0;
      *param_1 = uVar4;
    }
    else {
      param_2[9] = param_2[9] + (uVar4 - uVar6);
      *(undefined2 *)(param_1 + 1) = 0;
      *param_1 = uVar6;
    }
  }
  else {
    if (local_28 == 0x14) {
      param_2[3] = param_2[2];
      *(undefined1 *)(param_2 + 4) = 1;
      uVar6 = _DAT_01000920;
      uVar4 = _UNK_01000928;
    }
    else {
      *(short *)(param_2 + 0xb) = local_28;
      uVar6 = _DAT_01000690;
      uVar4 = _UNK_01000698;
    }
    *param_1 = uVar6;
    param_1[1] = uVar4;
  }
  return;
}


// ---- FUN_011ca760 @ 011ca760

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 (*) [16] FUN_011ca760(undefined1 **param_1,long param_2,ulong param_3)

{
  short sVar1;
  uint uVar2;
  byte bVar4;
  undefined1 *puVar5;
  ulong uVar6;
  long lVar7;
  long lVar8;
  ulong uVar9;
  undefined1 **ppuVar10;
  undefined1 **ppuVar11;
  long unaff_R15;
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined1 auStack_248 [128];
  undefined1 *puStack_1c8;
  undefined1 **ppuStack_1c0;
  undefined8 uStack_1b8;
  long lStack_1b0;
  undefined1 **ppuStack_c8;
  undefined8 uStack_c0;
  undefined1 **ppuStack_b8;
  undefined1 uStack_98;
  long lStack_80;
  byte bStack_6c;
  short sStack_68;
  undefined1 **ppuStack_58;
  undefined8 uStack_50;
  short local_40;
  undefined6 uStack_3e;
  ushort local_38 [4];
  undefined1 *local_30;
  undefined1 (*pauVar3) [16];
  
  uVar2 = *(byte *)((long)param_1 + 0x5e) & 7;
  pauVar3 = (undefined1 (*) [16])(ulong)uVar2;
  switch(uVar2) {
  default:
    if (*(short *)((long)param_1 + 0x5c) == 0) {
      local_30 = param_1[10];
      uStack_50 = 0x11ca7a9;
      sVar1 = (**(code **)(param_1[1] + 0x1a0))(*param_1,&local_30,param_2);
      if (sVar1 == 0) goto switchD_011ca587_caseD_6;
      *(short *)((long)param_1 + 0x5c) = sVar1;
    }
    do {
      uStack_50 = 0x11ca7ce;
      FUN_011caad0(&local_40,param_1 + 5,param_2);
      if (local_38[0] != 0) {
        *(ushort *)((long)param_1 + 0x5c) = local_38[0];
        return (undefined1 (*) [16])(ulong)local_38[0];
      }
      param_2 = param_2 - CONCAT62(uStack_3e,local_40);
    } while (param_2 != 0);
    puVar5 = param_1[9];
    goto LAB_011ca801;
  case 1:
  case 3:
switchD_011ca587_caseD_6:
    puVar5 = param_1[8] + (long)param_1[2] + (param_2 - (long)param_1[9]);
    if (param_1[2] <= puVar5) {
      param_1[8] = param_1[9];
      param_1[2] = puVar5;
      return (undefined1 (*) [16])0x0;
    }
    puVar5 = param_1[8] + param_2;
LAB_011ca801:
    param_1[8] = puVar5;
    return (undefined1 (*) [16])0x0;
  case 4:
    return (undefined1 (*) [16])(ulong)*(ushort *)((long)param_1 + 0x5c);
  case 5:
  case 7:
    if ((*(short *)(param_2 + 0x5a) != 0) || (*(short *)(param_2 + 0x5c) != 0)) {
      uVar6 = *(long *)(param_2 + 0x48) - *(long *)(param_2 + 0x40);
      ppuVar10 = (undefined1 **)(param_3 - uVar6);
      if (param_3 < uVar6 || ppuVar10 == (undefined1 **)0x0) {
        *(ulong *)*(undefined1 (*) [16])(param_2 + 0x40) = *(long *)(param_2 + 0x40) + param_3;
        *(undefined2 *)(*pauVar3 + 8) = 0;
        *(ulong *)*pauVar3 = param_3;
        return pauVar3;
      }
      ppuVar11 = (undefined1 **)0x80;
      if (ppuVar10 < (undefined1 **)0x80) {
        ppuVar11 = ppuVar10;
      }
      auVar12._0_12_ = ZEXT812(0);
      auVar12._12_4_ = 0;
      *(undefined1 (*) [16])(param_2 + 0x40) = auVar12;
      puStack_1c8 = auStack_248;
      if (*(long *)(param_2 + 0x38) == 0) {
        uStack_c0 = 1;
      }
      else {
        uStack_1b8 = *(undefined8 *)(param_2 + 0x30);
        uStack_c0 = 2;
        lStack_1b0 = *(long *)(param_2 + 0x38);
      }
      ppuVar10 = &puStack_1c8;
      uStack_98 = 0;
      uStack_50 = 0x11cac98;
      ppuStack_1c0 = ppuVar11;
      ppuStack_c8 = ppuVar10;
      ppuStack_b8 = param_1;
      (**(code **)(unaff_R15 + 0x78))(&ppuStack_58,param_2,&ppuStack_c8);
      if (local_40 == 0) {
        ppuVar10 = ppuStack_58;
        local_40 = (short)uStack_50;
      }
      if (local_40 == 0) {
        *(long *)(param_2 + 0x10) = *(long *)(param_2 + 0x10) + (long)ppuVar10;
        if (ppuVar11 <= ppuVar10 && (long)ppuVar10 - (long)ppuVar11 != 0) {
          *(long *)(param_2 + 0x48) = *(long *)(param_2 + 0x48) + ((long)ppuVar10 - (long)ppuVar11);
          ppuVar10 = ppuVar11;
        }
        *(undefined2 *)(*pauVar3 + 8) = 0;
        *(ulong *)*pauVar3 = uVar6 + (long)ppuVar10;
        return pauVar3;
      }
      if (local_40 == 0x14) {
        *(undefined8 *)(param_2 + 0x18) = *(undefined8 *)(param_2 + 0x10);
        *(undefined1 *)(param_2 + 0x20) = 1;
        auVar14 = _DAT_01000920;
      }
      else {
        *(short *)(param_2 + 0x58) = local_40;
        auVar14 = _DAT_01000690;
      }
      goto LAB_011cae59;
    }
    if (*(char *)(param_2 + 0x20) != '\0') {
      lStack_80 = *(long *)(param_2 + 0x18);
LAB_011caceb:
      uVar6 = lStack_80 - *(long *)(param_2 + 0x10);
      if (param_3 <= uVar6) {
        uVar6 = param_3;
      }
      if (0x7ffffffffffffffe < uVar6) {
        uVar6 = 0x7fffffffffffffff;
      }
      uStack_50 = 0x11cad1b;
      sVar1 = (**(code **)(unaff_R15 + 0x1a0))(param_2,local_38,uVar6);
      if (sVar1 != 0) {
        *(short *)(param_2 + 0x5c) = sVar1;
        auVar13._0_12_ = ZEXT812(0);
        auVar13._12_4_ = 0;
        *pauVar3 = auVar13;
        return pauVar3;
      }
      *(long *)(param_2 + 0x10) = *(long *)(param_2 + 0x10) + uVar6;
      *(undefined2 *)(*pauVar3 + 8) = 0;
      *(ulong *)*pauVar3 = uVar6;
      return pauVar3;
    }
    uStack_50 = 0x11cad56;
    ppuStack_58 = param_1;
    (**(code **)(unaff_R15 + 0x168))(&ppuStack_c8,param_2,&ppuStack_58);
    if (sStack_68 == 0) {
      if ((bStack_6c & 0xf) == 5) {
        *(long *)(param_2 + 0x18) = lStack_80;
        *(undefined1 *)(param_2 + 0x20) = 1;
        goto LAB_011caceb;
      }
      bVar4 = (*(byte *)(param_2 + 0x5e) ^ 4) & 7;
      *(byte *)(param_2 + 0x5e) = (byte)(0x480004 >> (uint)bVar4 + (uint)bVar4 * 2) & 7;
      sStack_68 = 0x36;
    }
    *(short *)(param_2 + 0x5a) = sStack_68;
    break;
  case 6:
    if (*(char *)(param_2 + 0x20) != '\0') {
      lStack_80 = *(long *)(param_2 + 0x18);
LAB_011caba0:
      lVar7 = *(long *)(param_2 + 0x48);
      lVar8 = (*(long *)(param_2 + 0x40) + *(ulong *)(param_2 + 0x10)) - lVar7;
      uVar6 = lStack_80 - lVar8;
      auVar14 = _DAT_01000920;
      if (uVar6 != 0) {
        if (param_3 < uVar6) {
          uVar6 = param_3;
        }
        uVar9 = lVar8 + uVar6;
        if (uVar9 < *(ulong *)(param_2 + 0x10)) {
          lVar7 = *(long *)(param_2 + 0x40) + uVar6;
        }
        else {
          *(ulong *)(param_2 + 0x10) = uVar9;
        }
        *(long *)(param_2 + 0x40) = lVar7;
        *(undefined2 *)(*pauVar3 + 8) = 0;
        *(ulong *)*pauVar3 = uVar6;
        return pauVar3;
      }
      goto LAB_011cae59;
    }
    if (*(short *)(param_2 + 0x5a) == 0) {
      uStack_50 = 0x11cac01;
      ppuStack_58 = param_1;
      (**(code **)(unaff_R15 + 0x168))(&ppuStack_c8,param_2,&ppuStack_58);
      if (sStack_68 == 0) {
        if ((bStack_6c & 0xf) == 5) {
          *(long *)(param_2 + 0x18) = lStack_80;
          *(undefined1 *)(param_2 + 0x20) = 1;
          goto LAB_011caba0;
        }
        bVar4 = (*(byte *)(param_2 + 0x5e) ^ 4) & 7;
        *(byte *)(param_2 + 0x5e) = (byte)(0x480004 >> (uint)bVar4 + (uint)bVar4 * 2) & 7;
        sStack_68 = 0x36;
      }
      *(short *)(param_2 + 0x5a) = sStack_68;
    }
    bVar4 = (*(byte *)(param_2 + 0x5e) ^ 4) & 7;
    *(byte *)(param_2 + 0x5e) = (byte)(0x480004 >> (uint)bVar4 + (uint)bVar4 * 2) & 7;
  }
  auVar14._0_12_ = ZEXT812(0);
  auVar14._12_4_ = 0;
LAB_011cae59:
  *pauVar3 = auVar14;
  return pauVar3;
}


// ---- FUN_011ca830 @ 011ca830

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_011ca830(undefined8 *param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  byte bVar2;
  undefined1 local_98 [72];
  undefined8 local_50;
  byte local_3c;
  short local_38;
  undefined8 local_20;
  
  if (*(char *)(param_2 + 4) != '\0') {
    *param_1 = param_2[3];
    *(undefined2 *)(param_1 + 1) = 0;
    return;
  }
  if (*(short *)((long)param_2 + 0x5a) != 0) {
    *(short *)(param_1 + 1) = *(short *)((long)param_2 + 0x5a);
    return;
  }
  local_20 = param_2[10];
  (**(code **)(param_2[1] + 0x168))(local_98,*param_2,&local_20);
  if (local_38 == 0) {
    if ((local_3c & 0xf) == 5) {
      param_2[3] = local_50;
      *(undefined1 *)(param_2 + 4) = 1;
      *(undefined2 *)(param_1 + 1) = 0;
      *param_1 = local_50;
    }
    else {
      bVar2 = (*(byte *)((long)param_2 + 0x5e) ^ 4) & 7;
      *(byte *)((long)param_2 + 0x5e) = (byte)(0x480004 >> (uint)bVar2 + (uint)bVar2 * 2) & 7;
      *(undefined2 *)((long)param_2 + 0x5a) = 0x36;
      uVar1 = _UNK_01000548;
      *param_1 = ram0x01000540;
      param_1[1] = uVar1;
    }
  }
  else {
    *(short *)((long)param_2 + 0x5a) = local_38;
    *(short *)(param_1 + 1) = local_38;
  }
  return;
}


// ---- FUN_011ca900 @ 011ca900

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_011ca900(undefined1 (*param_1) [16],undefined8 *param_2,long param_3,long param_4)

{
  undefined8 uVar1;
  long lVar2;
  long lVar3;
  byte bVar4;
  short sVar5;
  long *plVar6;
  long lVar7;
  ulong uVar8;
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  long local_138 [33];
  short local_30;
  undefined8 local_28;
  
  uVar1 = *param_2;
  lVar2 = param_2[1];
  lVar7 = param_2[9];
  if (param_2[8] == lVar7) {
    if (param_4 == 0) {
      lVar7 = 0;
      uVar8 = 0;
    }
    else {
      plVar6 = (long *)(param_3 + 8);
      uVar8 = 0;
      lVar7 = 0;
      do {
        if (lVar7 == 0x10) {
          lVar7 = 0x10;
          goto LAB_011ca9e6;
        }
        lVar3 = *plVar6;
        if (lVar3 != 0) {
          local_138[lVar7 * 2] = plVar6[-1];
          local_138[lVar7 * 2 + 1] = lVar3;
          lVar7 = lVar7 + 1;
          uVar8 = uVar8 + lVar3;
        }
        plVar6 = plVar6 + 2;
        param_4 = param_4 + -1;
      } while (param_4 != 0);
    }
    lVar3 = param_2[7];
    if (lVar3 != 0) {
      auVar9._0_12_ = ZEXT812(0);
      auVar9._12_4_ = 0;
      *(undefined1 (*) [16])(param_2 + 8) = auVar9;
      local_138[lVar7 * 2] = param_2[6];
      local_138[lVar7 * 2 + 1] = lVar3;
      lVar7 = lVar7 + 1;
    }
  }
  else {
    local_138[0] = param_2[6] + lVar7;
    local_138[1] = param_2[7] - lVar7;
    lVar7 = 1;
    uVar8 = 0;
  }
LAB_011ca9e6:
  local_28 = param_2[10];
  (**(code **)(lVar2 + 0x198))(local_138 + 0x20,uVar1,&local_28,local_138,lVar7,param_2[2]);
  if (local_30 == 0) {
    if (local_138[0x20] != 0) {
      param_2[2] = param_2[2] + local_138[0x20];
      if (uVar8 <= (ulong)local_138[0x20] && local_138[0x20] - uVar8 != 0) {
        param_2[9] = param_2[9] + (local_138[0x20] - uVar8);
        *(undefined2 *)(*param_1 + 8) = 0;
        *(ulong *)*param_1 = uVar8;
        return;
      }
      *(undefined2 *)(*param_1 + 8) = 0;
      *(long *)*param_1 = local_138[0x20];
      return;
    }
    param_2[3] = param_2[2];
    *(undefined1 *)(param_2 + 4) = 1;
    auVar10 = _DAT_01000920;
  }
  else if (local_30 == 0x16) {
    bVar4 = (*(byte *)((long)param_2 + 0x5e) ^ 4) & 7;
    *(byte *)((long)param_2 + 0x5e) = (byte)(0x480004 >> (uint)bVar4 + (uint)bVar4 * 2) & 7;
    if (param_2[2] != 0) {
      param_2[2] = 0;
      sVar5 = FUN_011ca760(param_2);
      if (sVar5 != 0) {
        *(undefined1 *)((long)param_2 + 0x5e) = 4;
        auVar10 = _DAT_01000690;
        goto LAB_011caa4b;
      }
    }
    auVar10._0_12_ = ZEXT812(0);
    auVar10._12_4_ = 0;
  }
  else {
    *(short *)(param_2 + 0xb) = local_30;
    auVar10 = _DAT_01000690;
  }
LAB_011caa4b:
  *param_1 = auVar10;
  return;
}


// ---- FUN_011caad0 @ 011caad0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 (*) [16] FUN_011caad0(undefined1 (*param_1) [16],long param_2,ulong param_3)

{
  undefined8 uVar1;
  long *plVar2;
  byte bVar3;
  short sVar4;
  ulong uVar5;
  uint uVar6;
  ulong uVar7;
  undefined1 (*unaff_RBX) [16];
  long lVar8;
  long lVar9;
  undefined1 **ppuVar10;
  undefined1 **ppuVar11;
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined1 local_248 [128];
  undefined1 *local_1c8;
  undefined1 **local_1c0;
  undefined8 local_1b8;
  long local_1b0;
  undefined1 **local_c8;
  undefined8 local_c0;
  undefined1 **local_b8;
  undefined1 local_98;
  long local_80;
  byte local_6c;
  short local_68;
  undefined1 **local_58;
  long local_50;
  ulong uStack_48;
  short local_40;
  undefined6 uStack_3e;
  undefined1 **local_38;
  undefined1 (*pauVar15) [16];
  
  uVar1 = *(undefined8 *)(param_2 + -0x28);
  plVar2 = *(long **)(param_2 + -0x20);
  local_b8 = *(undefined1 ***)(param_2 + 0x28);
  uVar6 = *(byte *)(param_2 + 0x36) & 7;
  uVar7 = (ulong)uVar6;
  local_38 = local_b8;
  pauVar15 = unaff_RBX;
  switch(uVar6) {
  default:
    if ((*(short *)(param_2 + 0x32) != 0) || (*(short *)(param_2 + 0x34) != 0)) {
      uVar7 = *(long *)(param_2 + 0x20) - *(long *)(param_2 + 0x18);
      ppuVar10 = (undefined1 **)(param_3 - uVar7);
      if (param_3 < uVar7 || ppuVar10 == (undefined1 **)0x0) {
        *(ulong *)*(undefined1 (*) [16])(param_2 + 0x18) = *(long *)(param_2 + 0x18) + param_3;
        *(undefined2 *)(*param_1 + 8) = 0;
        *(ulong *)*param_1 = param_3;
        return param_1;
      }
      ppuVar11 = (undefined1 **)0x80;
      if (ppuVar10 < (undefined1 **)0x80) {
        ppuVar11 = ppuVar10;
      }
      auVar12._0_12_ = ZEXT812(0);
      auVar12._12_4_ = 0;
      *(undefined1 (*) [16])(param_2 + 0x18) = auVar12;
      local_1c8 = local_248;
      if (*(long *)(param_2 + 0x10) == 0) {
        local_c0 = 1;
      }
      else {
        local_1b8 = *(undefined8 *)(param_2 + 8);
        local_c0 = 2;
        local_1b0 = *(long *)(param_2 + 0x10);
      }
      ppuVar10 = &local_1c8;
      local_98 = 0;
      local_1c0 = ppuVar11;
      local_c8 = ppuVar10;
      (*(code *)plVar2[0xf])(&local_58,uVar1,&local_c8);
      if (local_40 == 0) {
        ppuVar10 = local_58;
        local_40 = (short)local_50;
      }
      if (local_40 == 0) {
        *(long *)(param_2 + -0x18) = *(long *)(param_2 + -0x18) + (long)ppuVar10;
        if (ppuVar11 <= ppuVar10 && (long)ppuVar10 - (long)ppuVar11 != 0) {
          *(long *)(param_2 + 0x20) = *(long *)(param_2 + 0x20) + ((long)ppuVar10 - (long)ppuVar11);
          ppuVar10 = ppuVar11;
        }
        *(undefined2 *)(*param_1 + 8) = 0;
        *(ulong *)*param_1 = uVar7 + (long)ppuVar10;
        return param_1;
      }
      if (local_40 == 0x14) {
        *(undefined8 *)(param_2 + -0x10) = *(undefined8 *)(param_2 + -0x18);
        *(undefined1 *)(param_2 + -8) = 1;
        auVar14 = _DAT_01000920;
        goto LAB_011cae59;
      }
      *(short *)(param_2 + 0x30) = local_40;
      goto switchD_011cab05_caseD_4;
    }
    if (*(char *)(param_2 + -8) != '\0') {
      local_80 = *(long *)(param_2 + -0x10);
LAB_011caceb:
      uVar7 = local_80 - *(long *)(param_2 + -0x18);
      if (param_3 <= uVar7) {
        uVar7 = param_3;
      }
      if (0x7ffffffffffffffe < uVar7) {
        uVar7 = 0x7fffffffffffffff;
      }
      sVar4 = (*(code *)plVar2[0x34])(uVar1,&local_38,uVar7);
      if (sVar4 != 0) {
        *(short *)(param_2 + 0x34) = sVar4;
        auVar13._0_12_ = ZEXT812(0);
        auVar13._12_4_ = 0;
        *param_1 = auVar13;
        return param_1;
      }
      *(long *)(param_2 + -0x18) = *(long *)(param_2 + -0x18) + uVar7;
      *(undefined2 *)(*param_1 + 8) = 0;
      *(ulong *)*param_1 = uVar7;
      return param_1;
    }
    local_58 = local_b8;
    (*(code *)plVar2[0x2d])(&local_c8,uVar1,&local_58);
    if (local_68 == 0) {
      if ((local_6c & 0xf) == 5) {
        *(long *)(param_2 + -0x10) = local_80;
        *(undefined1 *)(param_2 + -8) = 1;
        goto LAB_011caceb;
      }
      bVar3 = (*(byte *)(param_2 + 0x36) ^ 4) & 7;
      *(byte *)(param_2 + 0x36) = (byte)(0x480004 >> (uint)bVar3 + (uint)bVar3 * 2) & 7;
      local_68 = 0x36;
    }
    *(short *)(param_2 + 0x32) = local_68;
    break;
  case 1:
  case 3:
    if (*(char *)(param_2 + -8) != '\0') {
      local_80 = *(long *)(param_2 + -0x10);
LAB_011caba0:
      lVar8 = *(long *)(param_2 + 0x20);
      lVar9 = (*(long *)(param_2 + 0x18) + *(ulong *)(param_2 + -0x18)) - lVar8;
      uVar7 = local_80 - lVar9;
      auVar14 = _DAT_01000920;
      if (uVar7 != 0) {
        if (param_3 < uVar7) {
          uVar7 = param_3;
        }
        uVar5 = lVar9 + uVar7;
        if (uVar5 < *(ulong *)(param_2 + -0x18)) {
          lVar8 = *(long *)(param_2 + 0x18) + uVar7;
        }
        else {
          *(ulong *)(param_2 + -0x18) = uVar5;
        }
        *(long *)(param_2 + 0x18) = lVar8;
        *(undefined2 *)(*param_1 + 8) = 0;
        *(ulong *)*param_1 = uVar7;
        return param_1;
      }
      goto LAB_011cae59;
    }
    if (*(short *)(param_2 + 0x32) == 0) {
      local_58 = local_b8;
      (*(code *)plVar2[0x2d])(&local_c8,uVar1,&local_58);
      if (local_68 == 0) {
        if ((local_6c & 0xf) == 5) {
          *(long *)(param_2 + -0x10) = local_80;
          *(undefined1 *)(param_2 + -8) = 1;
          goto LAB_011caba0;
        }
        bVar3 = (*(byte *)(param_2 + 0x36) ^ 4) & 7;
        *(byte *)(param_2 + 0x36) = (byte)(0x480004 >> (uint)bVar3 + (uint)bVar3 * 2) & 7;
        local_68 = 0x36;
      }
      *(short *)(param_2 + 0x32) = local_68;
    }
    bVar3 = (*(byte *)(param_2 + 0x36) ^ 4) & 7;
    *(byte *)(param_2 + 0x36) = (byte)(0x480004 >> (uint)bVar3 + (uint)bVar3 * 2) & 7;
    break;
  case 4:
switchD_011cab05_caseD_4:
    auVar14 = _DAT_01000690;
    goto LAB_011cae59;
  case 5:
  case 6:
    (**(code **)(*plVar2 + 8))(&local_40,plVar2,param_2 + -0x28);
    if ((short)local_38 != 0x12) {
      uVar5 = CONCAT62(uStack_3e,local_40);
      sVar4 = (short)local_38;
      goto LAB_011caf6e;
    }
    bVar3 = (*(byte *)(param_2 + 0x36) ^ 4) & 7;
    *(byte *)(param_2 + 0x36) = (byte)(0x69a004 >> (uint)bVar3 + (uint)bVar3 * 2) & 7;
    pauVar15 = (undefined1 (*) [16])0x0;
    uVar5 = 0;
    goto LAB_011caf6c;
  case 7:
    uVar5 = plVar2[2] - plVar2[3];
    if (uVar5 == 0) {
      uVar5 = uVar7;
      sVar4 = (**(code **)(*plVar2 + 0x18))(plVar2,0,1);
      if (sVar4 != 0) goto LAB_011caf6e;
      local_50 = plVar2[1] + plVar2[3];
      uVar5 = plVar2[2] - plVar2[3];
    }
    else {
      local_50 = plVar2[3] + plVar2[1];
    }
    uStack_48 = uVar7;
    if (uVar5 < uVar7) {
      uStack_48 = uVar5;
    }
    uVar5 = 1;
    FUN_011ca5d0(&local_40,param_2 + -0x28,&local_50);
    sVar4 = (short)local_38;
    if ((short)local_38 != 0) goto LAB_011caf6e;
    uVar5 = CONCAT62(uStack_3e,local_40);
    plVar2[3] = plVar2[3] + uVar5;
LAB_011caf6c:
    sVar4 = 0;
LAB_011caf6e:
    *(ulong *)*unaff_RBX = uVar5;
    *(short *)(*unaff_RBX + 8) = sVar4;
    *(int *)(*unaff_RBX + 10) = (int)pauVar15;
    *(short *)(*unaff_RBX + 0xe) = (short)((ulong)pauVar15 >> 0x20);
    return unaff_RBX;
  }
  auVar14._0_12_ = ZEXT812(0);
  auVar14._12_4_ = 0;
LAB_011cae59:
  *param_1 = auVar14;
  return param_1;
}


// ---- FUN_011cae70 @ 011cae70

/* WARNING: Removing unreachable block (ram,0x011cbbd5) */
/* WARNING: Removing unreachable block (ram,0x011cbbdb) */
/* WARNING: Removing unreachable block (ram,0x011cb951) */
/* WARNING: Removing unreachable block (ram,0x011cb960) */
/* WARNING: Removing unreachable block (ram,0x011cb967) */
/* WARNING: Removing unreachable block (ram,0x011cb96f) */
/* WARNING: Removing unreachable block (ram,0x011cb977) */
/* WARNING: Removing unreachable block (ram,0x011cbb17) */
/* WARNING: Removing unreachable block (ram,0x011cbb20) */
/* WARNING: Removing unreachable block (ram,0x011cbb27) */
/* WARNING: Removing unreachable block (ram,0x011cbb2f) */
/* WARNING: Removing unreachable block (ram,0x011cbb37) */
/* WARNING: Removing unreachable block (ram,0x011cbb40) */
/* WARNING: Removing unreachable block (ram,0x011cbb46) */

undefined1  [16]
FUN_011cae70(ulong *param_1,long param_2,long *param_3,ulong param_4,undefined4 *param_5,
            long param_6)

{
  byte bVar1;
  short sVar2;
  ulong uVar3;
  ulong uVar4;
  undefined2 uVar5;
  long *extraout_RDX;
  long *extraout_RDX_00;
  long *extraout_RDX_01;
  long *plVar6;
  long *extraout_RDX_02;
  long *extraout_RDX_03;
  undefined6 uVar8;
  undefined1 *puVar7;
  undefined8 unaff_R12;
  long lVar9;
  long in_FS_OFFSET;
  bool bVar10;
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  long lStack_70;
  short sStack_60;
  undefined2 uStack_5e;
  uint uStack_5c;
  undefined8 uStack_58;
  long local_50;
  undefined8 local_48;
  uint local_40;
  undefined4 uStack_3c;
  short local_38;
  undefined2 uStack_36;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined1 uVar15;
  
  lVar9 = param_2 + -0x28;
  uVar4 = param_4;
  switch(*(byte *)(param_2 + 0x36) & 7) {
  default:
    (**(code **)(*param_3 + 8))(&local_40,param_3,lVar9);
    plVar6 = extraout_RDX;
    if (local_38 != 0x12) {
      uVar4 = CONCAT44(uStack_3c,local_40);
      sVar2 = local_38;
      goto LAB_011caf6e;
    }
    bVar1 = (*(byte *)(param_2 + 0x36) ^ 4) & 7;
    *(byte *)(param_2 + 0x36) = (byte)(0x69a004 >> (uint)bVar1 + (uint)bVar1 * 2) & 7;
    local_2c._0_2_ = 0;
    local_30 = 0;
    uVar4 = 0;
    goto LAB_011caf6c;
  case 2:
    uVar3 = param_3[2] - param_3[3];
    if (uVar3 == 0) {
      sVar2 = (**(code **)(*param_3 + 0x18))(param_3,0,1);
      plVar6 = extraout_RDX_02;
      if (sVar2 != 0) goto LAB_011caf6e;
      local_50 = param_3[1] + param_3[3];
      uVar3 = param_3[2] - param_3[3];
    }
    else {
      local_50 = param_3[3] + param_3[1];
    }
    local_48 = param_4;
    if (uVar3 < param_4) {
      local_48 = uVar3;
    }
    uVar4 = 1;
    FUN_011ca5d0(&local_40,lVar9,&local_50);
    plVar6 = extraout_RDX_00;
    sVar2 = local_38;
    break;
  case 3:
    uVar3 = param_3[2] - param_3[3];
    if (uVar3 == 0) {
      sVar2 = (**(code **)(*param_3 + 0x18))(param_3,0,1);
      plVar6 = extraout_RDX_03;
      if (sVar2 != 0) goto LAB_011caf6e;
      local_50 = param_3[1] + param_3[3];
      uVar3 = param_3[2] - param_3[3];
    }
    else {
      local_50 = param_3[3] + param_3[1];
    }
    local_48 = param_4;
    if (uVar3 < param_4) {
      local_48 = uVar3;
    }
    uVar4 = 1;
    FUN_011ca900(&local_40,lVar9,&local_50);
    plVar6 = extraout_RDX_01;
    sVar2 = local_38;
    break;
  case 4:
    local_2c._0_2_ = 0;
    local_30 = 0;
    plVar6 = param_3;
    sVar2 = 0x15;
    goto LAB_011caf6e;
  case 5:
    LOCK();
    *(ulong *)(param_6 + 8) = *(ulong *)(param_6 + 8) ^ 3;
    UNLOCK();
    lVar9 = *(long *)(in_FS_OFFSET + -0x40010);
    if ((lVar9 == 0) || ((*(byte *)(lVar9 + 0x21c) & 1) != 0)) {
LAB_011cb913:
      lVar9 = 0;
    }
    else {
      uVar4 = *(ulong *)(lVar9 + 8);
      do {
        LOCK();
        uVar3 = *(ulong *)(lVar9 + 8);
        bVar10 = uVar4 == uVar3;
        if (bVar10) {
          *(ulong *)(lVar9 + 8) = uVar4 | 3;
          uVar3 = uVar4;
        }
        UNLOCK();
        uVar4 = uVar3;
      } while (!bVar10);
      if ((uVar3 & 7) != 0) {
        uVar8 = (undefined6)((ulong)param_3 >> 0x10);
        if (((uint)uVar3 & 7) == 6) {
          syscall();
          syscall();
          goto LAB_011cbc01;
        }
        goto LAB_011cb913;
      }
    }
    uVar8 = (undefined6)((ulong)&stack0xffffffffffffffd8 >> 0x10);
    if (lVar9 == 0) {
      syscall();
    }
    else {
      syscall();
      LOCK();
      *(ulong *)(lVar9 + 8) = *(ulong *)(lVar9 + 8) ^ 3;
      UNLOCK();
    }
    lVar9 = *(long *)(in_FS_OFFSET + -0x40010);
    if ((lVar9 != 0) && ((*(byte *)(lVar9 + 0x21c) & 1) == 0)) {
      uVar4 = *(ulong *)(lVar9 + 8);
      do {
        LOCK();
        uVar3 = *(ulong *)(lVar9 + 8);
        bVar10 = uVar4 == uVar3;
        if (bVar10) {
          *(ulong *)(lVar9 + 8) = uVar4 | 3;
          uVar3 = uVar4;
        }
        UNLOCK();
        uVar4 = uVar3;
      } while (!bVar10);
      if ((uVar3 & 7) == 0) goto LAB_011cbae6;
      if (((uint)uVar3 & 7) == 6) {
        syscall();
        syscall();
LAB_011cbc01:
        auVar13._10_6_ = uVar8;
        auVar13._8_2_ = 0x11;
        *(undefined2 *)(param_5 + 0x12) = 0x11;
        auVar13._0_8_ = param_5;
        return auVar13;
      }
    }
    lVar9 = 0;
LAB_011cbae6:
    puVar7 = &stack0xffffffffffffffdc;
    if (lVar9 == 0) {
      syscall();
    }
    else {
      syscall();
      LOCK();
      *(ulong *)(lVar9 + 8) = *(ulong *)(lVar9 + 8) ^ 3;
      UNLOCK();
    }
    uVar5 = 0;
    *(undefined2 *)(param_5 + 0x12) = 0;
    *param_5 = (int)unaff_R12;
    if (sStack_60 == 10) {
      uVar15 = 1;
      uVar5 = swap_bytes(uStack_5e);
      puVar7 = (undefined1 *)(ulong)uStack_5c;
      uVar4 = CONCAT44((undefined4)local_48,uStack_5c);
      uStack_78 = uStack_58;
      lStack_70 = local_50;
    }
    else if (sStack_60 == 2) {
      uVar15 = 0;
      uVar5 = swap_bytes(uStack_5e);
      uVar4 = (ulong)CONCAT42(uStack_5c,uVar5);
    }
    else {
      uVar4 = 0x100007f0000;
      uVar15 = 0;
    }
    *(ulong *)(param_5 + 1) = uVar4;
    *(undefined2 *)(param_5 + 3) = uVar5;
    *(undefined8 *)((long)param_5 + 0xe) = uStack_78;
    *(long *)((long)param_5 + 0x16) = lStack_70;
    *(undefined1 *)(param_5 + 8) = uVar15;
    param_5[9] = (int)((ulong)unaff_R12 >> 0x20);
    if (local_48._4_2_ == 10) {
      uVar15 = 1;
      uVar5 = swap_bytes(local_48._6_2_);
      puVar7 = (undefined1 *)(ulong)local_40;
      uVar4 = CONCAT44(local_2c,local_40);
      uStack_88 = CONCAT26(uStack_36,CONCAT24(local_38,uStack_3c));
      uStack_80 = CONCAT44(local_30,uStack_34);
    }
    else if (local_48._4_2_ == 2) {
      uVar15 = 0;
      uVar5 = swap_bytes(local_48._6_2_);
      uVar4 = (ulong)CONCAT42(local_40,uVar5);
    }
    else {
      uVar4 = 0x100007f0000;
      uVar15 = 0;
    }
    *(ulong *)(param_5 + 10) = uVar4;
    *(undefined2 *)(param_5 + 0xc) = uVar5;
    *(undefined8 *)((long)param_5 + 0x32) = uStack_88;
    *(undefined8 *)((long)param_5 + 0x3a) = uStack_80;
    *(undefined1 *)(param_5 + 0x11) = uVar15;
    auVar14._8_8_ = puVar7;
    auVar14._0_8_ = param_5;
    return auVar14;
  case 6:
  case 7:
    LOCK();
    *(ulong *)(param_6 + 8) = *(ulong *)(param_6 + 8) ^ 3;
    UNLOCK();
    *(undefined2 *)(param_5 + 0x12) = 4;
    auVar12._8_8_ = param_3;
    auVar12._0_8_ = param_5;
    return auVar12;
  }
  if (sVar2 == 0) {
    uVar4 = CONCAT44(uStack_3c,local_40);
    param_3[3] = param_3[3] + uVar4;
LAB_011caf6c:
    sVar2 = 0;
  }
LAB_011caf6e:
  *param_1 = uVar4;
  *(short *)(param_1 + 1) = sVar2;
  *(undefined4 *)((long)param_1 + 10) = local_30;
  *(undefined2 *)((long)param_1 + 0xe) = (undefined2)local_2c;
  auVar11._8_8_ = plVar6;
  auVar11._0_8_ = param_1;
  return auVar11;
}


// ---- FUN_011cb030 @ 011cb030

ulong FUN_011cb030(long *param_1)

{
  ulong uVar1;
  undefined1 local_40 [8];
  ushort local_38;
  char *local_30;
  undefined8 local_28;
  
  if ((param_1[2] != param_1[3]) ||
     (uVar1 = (**(code **)(*param_1 + 0x18))(param_1,1), (short)uVar1 == 0)) {
    local_30 = "";
    local_28 = 0;
    do {
      if ((ulong)param_1[3] < (ulong)param_1[4]) {
        return 0;
      }
      (**(code **)(*param_1 + 0x10))(local_40,param_1,&local_30,1);
      uVar1 = (ulong)local_38;
    } while (local_38 == 0);
  }
  return uVar1;
}


// ---- FUN_011cb0c0 @ 011cb0c0

void FUN_011cb0c0(long *param_1,long *param_2,undefined8 *param_3,long param_4,ulong param_5,
                 long param_6)

{
  int iVar1;
  undefined8 uVar2;
  undefined1 (*pauVar3) [16];
  undefined8 uVar4;
  undefined8 uVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  uint uVar9;
  short sVar10;
  int iVar11;
  uint uVar12;
  ulong uVar13;
  long *plVar14;
  long lVar15;
  undefined4 uVar16;
  ulong uVar17;
  ulong uVar18;
  long lVar19;
  ulong unaff_R13;
  ulong uVar20;
  bool bVar21;
  bool bVar22;
  undefined1 auVar23 [16];
  undefined1 auVar24 [16];
  undefined1 local_68 [16];
  undefined8 local_58;
  undefined1 local_4c;
  undefined8 *local_48;
  undefined1 local_3c;
  long *local_38;
  
  if (param_5 == 0) {
    unaff_R13 = 0;
    goto LAB_011cb389;
  }
  uVar2 = *param_3;
  lVar15 = param_3[1];
  LOCK();
  iVar11 = (int)param_2[8];
  bVar21 = iVar11 == 0;
  if (bVar21) {
    *(int *)(param_2 + 8) = 1;
    iVar11 = 0;
  }
  UNLOCK();
  plVar14 = param_2 + 8;
  local_48 = param_3;
  local_38 = plVar14;
  if (!bVar21) {
    if (iVar11 != 2) goto LAB_011cb73d;
    do {
      plVar14 = local_38;
      sVar10 = (**(code **)(lVar15 + 0x60))(uVar2,local_38,2,&DAT_0100f0f0);
      unaff_R13 = param_5;
      if (sVar10 != 0) goto LAB_011cb764;
LAB_011cb73d:
      LOCK();
      lVar19 = *plVar14;
      *(int *)plVar14 = 2;
      UNLOCK();
    } while ((int)lVar19 != 0);
  }
  sVar10 = 0x6b;
  if (*(char *)((long)param_2 + 0x44) == '\0') {
    param_5 = param_5 * 0x28;
    uVar2 = *local_48;
    lVar15 = local_48[1];
    uVar20 = 0;
    do {
      pauVar3 = (undefined1 (*) [16])param_2[6];
      unaff_R13 = param_5;
      if (pauVar3 == (undefined1 (*) [16])0x0) {
        lVar19 = param_2[3];
        goto LAB_011cb2c0;
      }
      if (*(long *)*pauVar3 == 0) {
        plVar14 = *(long **)(*pauVar3 + 8);
        param_2[6] = (long)plVar14;
        lVar19 = *(long *)*pauVar3;
        if (plVar14 == (long *)0x0) goto LAB_011cb1d1;
LAB_011cb1b2:
        *plVar14 = lVar19;
      }
      else {
        plVar14 = *(long **)(*pauVar3 + 8);
        *(long **)(*(long *)*pauVar3 + 8) = plVar14;
        lVar19 = *(long *)*pauVar3;
        if (plVar14 != (long *)0x0) goto LAB_011cb1b2;
LAB_011cb1d1:
        param_2[7] = lVar19;
      }
      uVar17 = param_5 - uVar20;
      if (*(ulong *)pauVar3[-1] < param_5 - uVar20) {
        uVar17 = *(ulong *)pauVar3[-1];
      }
      FUN_011f4580(*(undefined8 *)(pauVar3[-2] + 8),param_4 + uVar20,uVar17);
      *(ulong *)(pauVar3[-2] + 8) = *(long *)(pauVar3[-2] + 8) + uVar17;
      *(ulong *)pauVar3[-1] = *(long *)pauVar3[-1] - uVar17;
      uVar18 = *(ulong *)(pauVar3[-1] + 8);
      lVar19 = 0;
      if (uVar18 >= uVar17) {
        lVar19 = uVar18 - uVar17;
      }
      *(long *)(pauVar3[-1] + 8) = lVar19;
      if (uVar18 < uVar17 || uVar18 - uVar17 == 0) {
        uVar4 = *local_48;
        lVar19 = local_48[1];
        iVar11 = *(int *)pauVar3[1];
        do {
          if ((ushort)iVar11 <= (ushort)((uint)iVar11 >> 0x10)) goto LAB_011cb180;
          LOCK();
          iVar1 = *(int *)pauVar3[1];
          bVar21 = iVar11 == iVar1;
          if (bVar21) {
            *(int *)pauVar3[1] = iVar11 + 0x10000;
            iVar1 = iVar11;
          }
          iVar11 = iVar1;
          UNLOCK();
        } while (!bVar21);
        LOCK();
        *(int *)(pauVar3[1] + 4) = *(int *)(pauVar3[1] + 4) + 1;
        UNLOCK();
        (**(code **)(lVar19 + 0x70))(uVar4,pauVar3[1] + 4,1);
      }
      else {
        plVar14 = (long *)param_2[6];
        if (plVar14 == (long *)0x0) {
          param_2[6] = (long)pauVar3;
          param_2[7] = (long)pauVar3;
          auVar23._0_12_ = ZEXT812(0);
          auVar23._12_4_ = 0;
          *pauVar3 = auVar23;
        }
        else {
          *(long **)(*pauVar3 + 8) = plVar14;
          lVar19 = *plVar14;
          if (lVar19 == 0) {
            *(undefined8 *)*pauVar3 = 0;
            param_2[6] = (long)pauVar3;
            *plVar14 = (long)pauVar3;
          }
          else {
            *(long *)*pauVar3 = lVar19;
            *(undefined1 (**) [16])(lVar19 + 8) = pauVar3;
            *plVar14 = (long)pauVar3;
          }
        }
      }
LAB_011cb180:
      uVar20 = uVar20 + uVar17;
    } while (uVar20 != param_5);
    goto LAB_011cb358;
  }
LAB_011cb121:
  bVar21 = false;
  goto LAB_011cb361;
LAB_011cb2c0:
  do {
    uVar17 = param_2[1];
    uVar18 = lVar19 + param_2[2];
    local_3c = uVar18 < uVar17;
    if (!(bool)local_3c) {
      uVar13 = param_2[2] - (uVar18 - uVar17);
      lVar19 = (uVar18 - uVar17) + *param_2;
      if (uVar13 != 0) goto LAB_011cb316;
LAB_011cb3b3:
      bVar21 = true;
      lVar19 = param_6 * 0x28 - uVar20;
      unaff_R13 = uVar20;
      if (uVar20 <= (ulong)(param_6 * 0x28) && lVar19 != 0) {
        uVar20 = param_5 - uVar20;
        auVar24._0_12_ = ZEXT812(0);
        auVar24._12_4_ = 0;
        local_58 = 0;
        local_68._0_8_ = param_2[5];
        uVar4 = local_58;
        if (local_68._0_8_ == 0) {
          local_68._8_8_ = param_2[4];
          if ((long *)local_68._8_8_ == (long *)0x0) {
            param_2[4] = (long)local_68;
            param_2[5] = (long)local_68;
          }
          else {
            local_68._0_8_ = 0;
            lVar6 = *(long *)local_68._8_8_;
            if (lVar6 == 0) {
              param_2[4] = (long)local_68;
            }
            else {
              *(undefined1 **)(lVar6 + 8) = local_68;
              local_68._0_8_ = lVar6;
            }
            *(undefined1 **)local_68._8_8_ = local_68;
            auVar24 = local_68;
          }
        }
        else {
          local_68._8_8_ = 0;
          plVar14 = *(long **)(local_68._0_8_ + 8);
          if (plVar14 == (long *)0x0) {
            param_2[5] = (long)local_68;
            *(undefined1 **)(local_68._0_8_ + 8) = local_68;
            auVar24 = local_68;
          }
          else {
            local_68._8_8_ = plVar14;
            *plVar14 = (long)local_68;
            *(undefined1 **)(local_68._0_8_ + 8) = local_68;
            auVar24 = local_68;
          }
        }
joined_r0x011cb47b:
        local_68 = auVar24;
        local_58 = uVar4;
        if (lVar19 != 0) {
          sVar10 = 0x6b;
          if (*(char *)((long)param_2 + 0x44) == '\0') {
            uVar5 = *local_48;
            lVar6 = local_48[1];
            local_58._4_4_ = (undefined4)((ulong)uVar4 >> 0x20);
            uVar16 = local_58._4_4_;
            LOCK();
            local_58._0_4_ = (uint)uVar4;
            local_58 = CONCAT44(local_58._4_4_,(uint)local_58 + 1);
            UNLOCK();
            uVar4 = *local_48;
            lVar7 = local_48[1];
            LOCK();
            lVar8 = *local_38;
            *(int *)local_38 = 0;
            UNLOCK();
            if ((int)lVar8 == 2) {
              (**(code **)(lVar7 + 0x70))(uVar4,local_38,1);
            }
            do {
              sVar10 = (**(code **)(lVar6 + 0x60))(uVar5,(long)&local_58 + 4,uVar16,&DAT_0100f0f0);
              uVar16 = local_58._4_4_;
              uVar12 = (uint)local_58;
              while( true ) {
                if (uVar12 < 0x10000) break;
                LOCK();
                bVar22 = uVar12 == (uint)local_58;
                uVar9 = (uint)local_58;
                if (bVar22) {
                  local_58 = CONCAT44(local_58._4_4_,
                                      (uVar12 - 1 & 0xffff) + (uVar12 & 0xffff0000) + -0x10000);
                  uVar9 = uVar12;
                }
                uVar12 = uVar9;
                UNLOCK();
                local_4c = !bVar22;
                if (bVar22) {
                  uVar5 = *local_48;
                  lVar6 = local_48[1];
                  LOCK();
                  iVar11 = (int)*local_38;
                  bVar22 = iVar11 == 0;
                  if (bVar22) {
                    *(int *)local_38 = 1;
                    iVar11 = 0;
                  }
                  UNLOCK();
                  local_3c = !bVar22;
                  uVar4 = local_58;
                  auVar24 = local_68;
                  if (!bVar22) {
                    if (iVar11 == 2) goto LAB_011cb57f;
                    while( true ) {
                      LOCK();
                      lVar7 = *local_38;
                      *(int *)local_38 = 2;
                      UNLOCK();
                      uVar4 = local_58;
                      auVar24 = local_68;
                      if ((int)lVar7 == 0) break;
LAB_011cb57f:
                      (**(code **)(lVar6 + 0x68))(uVar5,local_38,2);
                    }
                  }
                  goto joined_r0x011cb47b;
                }
              }
            } while (sVar10 == 0);
            LOCK();
            local_58 = CONCAT44(local_58._4_4_,(uint)local_58 - 1);
            UNLOCK();
            uVar4 = *local_48;
            lVar6 = local_48[1];
            LOCK();
            iVar11 = (int)*local_38;
            bVar22 = iVar11 == 0;
            if (bVar22) {
              *(int *)local_38 = 1;
              iVar11 = 0;
            }
            UNLOCK();
            local_3c = !bVar22;
            if (!bVar22) {
              if (iVar11 != 2) goto LAB_011cb77d;
              do {
                (**(code **)(lVar6 + 0x68))(uVar4,local_38,2);
LAB_011cb77d:
                LOCK();
                lVar7 = *local_38;
                *(int *)local_38 = 2;
                UNLOCK();
              } while ((int)lVar7 != 0);
            }
            if (uVar20 != param_5) {
              (**(code **)(lVar15 + 0x48))(uVar2);
              unaff_R13 = param_5 - uVar20;
              if (lVar19 == 0) {
                sVar10 = 0;
              }
              else {
                if (local_68._0_8_ == 0) {
                  param_2[4] = local_68._8_8_;
                  lVar15 = 0;
                }
                else {
                  *(undefined8 *)(local_68._0_8_ + 8) = local_68._8_8_;
                  lVar15 = local_68._0_8_;
                }
                if ((long *)local_68._8_8_ == (long *)0x0) {
                  param_2[5] = lVar15;
                  sVar10 = 0;
                }
                else {
                  *(long *)local_68._8_8_ = lVar15;
                  sVar10 = 0;
                }
              }
              goto LAB_011cb361;
            }
            sVar10 = 0x11;
            unaff_R13 = param_5;
            if (lVar19 == 0) goto LAB_011cb121;
            auVar24 = local_68;
            if (local_68._0_8_ != 0) {
              *(undefined8 *)(local_68._0_8_ + 8) = local_68._8_8_;
              goto LAB_011cb656;
            }
LAB_011cb66f:
            local_68 = auVar24;
            param_2[4] = local_68._8_8_;
            lVar15 = 0;
            plVar14 = (long *)local_68._8_8_;
          }
          else {
            local_68._0_8_ = auVar24._0_8_;
            local_68._8_8_ = auVar24._8_8_;
            if (uVar20 != param_5) {
              if (local_68._0_8_ == 0) {
                param_2[4] = local_68._8_8_;
                local_68._0_8_ = 0;
              }
              else {
                *(undefined8 *)(local_68._0_8_ + 8) = local_68._8_8_;
              }
              if ((long *)local_68._8_8_ == (long *)0x0) {
                param_2[5] = local_68._0_8_;
              }
              else {
                *(undefined8 *)local_68._8_8_ = local_68._0_8_;
              }
              goto LAB_011cb59e;
            }
            if (local_68._0_8_ == 0) goto LAB_011cb66f;
            *(undefined8 *)(local_68._0_8_ + 8) = local_68._8_8_;
LAB_011cb656:
            local_68 = auVar24;
            plVar14 = (long *)local_68._8_8_;
            lVar15 = local_68._0_8_;
          }
          if (plVar14 == (long *)0x0) {
            param_2[5] = lVar15;
            unaff_R13 = param_5;
          }
          else {
            *plVar14 = lVar15;
            unaff_R13 = param_5;
          }
          goto LAB_011cb121;
        }
        sVar10 = 0x6b;
        unaff_R13 = param_5;
        if (uVar20 == param_5) goto LAB_011cb121;
LAB_011cb59e:
        unaff_R13 = param_5 - uVar20;
        sVar10 = 0;
        goto LAB_011cb361;
      }
      break;
    }
    uVar13 = uVar17 - uVar18;
    lVar19 = uVar18 + *param_2;
    if (uVar13 == 0) goto LAB_011cb3b3;
LAB_011cb316:
    if (lVar19 == 0) goto LAB_011cb3b3;
    uVar17 = param_5 - uVar20;
    if (uVar13 < param_5 - uVar20) {
      uVar17 = uVar13;
    }
    FUN_011f4580(lVar19,param_4 + uVar20,uVar17);
    lVar19 = param_2[3] + uVar17;
    param_2[3] = lVar19;
    uVar20 = uVar20 + uVar17;
  } while (uVar20 != param_5);
LAB_011cb358:
  bVar21 = true;
  sVar10 = 0;
LAB_011cb361:
  uVar2 = *local_48;
  lVar15 = local_48[1];
  LOCK();
  lVar19 = *local_38;
  *(int *)local_38 = 0;
  UNLOCK();
  if ((int)lVar19 == 2) {
    (**(code **)(lVar15 + 0x70))(uVar2,local_38,1);
  }
  if (!bVar21) {
LAB_011cb764:
    *(short *)(param_1 + 1) = sVar10;
    return;
  }
LAB_011cb389:
  *(undefined2 *)(param_1 + 1) = 0;
  *param_1 = (unaff_R13 >> 3) * -0x3333333333333333;
  return;
}


// ---- FUN_011cb7a0 @ 011cb7a0

/* WARNING: Removing unreachable block (ram,0x011cb99b) */
/* WARNING: Removing unreachable block (ram,0x011cb951) */
/* WARNING: Removing unreachable block (ram,0x011cb960) */
/* WARNING: Removing unreachable block (ram,0x011cb967) */
/* WARNING: Removing unreachable block (ram,0x011cb96f) */
/* WARNING: Removing unreachable block (ram,0x011cb977) */
/* WARNING: Removing unreachable block (ram,0x011cbb17) */
/* WARNING: Removing unreachable block (ram,0x011cbb20) */
/* WARNING: Removing unreachable block (ram,0x011cbb27) */
/* WARNING: Removing unreachable block (ram,0x011cbb2f) */
/* WARNING: Removing unreachable block (ram,0x011cbb37) */
/* WARNING: Removing unreachable block (ram,0x011cbbd5) */
/* WARNING: Removing unreachable block (ram,0x011cbbdb) */
/* WARNING: Removing unreachable block (ram,0x011cbb40) */
/* WARNING: Removing unreachable block (ram,0x011cbb46) */
/* WARNING: Removing unreachable block (ram,0x011cb9a7) */
/* WARNING: Recovered jumptable eliminated as dead code */
/* WARNING: Removing unreachable block (ram,0x011cb980) */
/* WARNING: Removing unreachable block (ram,0x011cb84b) */
/* WARNING: Removing unreachable block (ram,0x011cb850) */
/* WARNING: Removing unreachable block (ram,0x011cb857) */
/* WARNING: Removing unreachable block (ram,0x011cb85f) */
/* WARNING: Removing unreachable block (ram,0x011cb98c) */
/* WARNING: Removing unreachable block (ram,0x011cba2d) */
/* WARNING: Removing unreachable block (ram,0x011cba1a) */
/* WARNING: Removing unreachable block (ram,0x011cb993) */

undefined1  [16] FUN_011cb7a0(undefined4 *param_1,undefined8 param_2,ulong *param_3)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  undefined2 uVar4;
  undefined6 uVar6;
  undefined1 *puVar5;
  long lVar7;
  long in_FS_OFFSET;
  bool bVar8;
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined8 local_88;
  undefined8 uStack_80;
  undefined8 local_78;
  undefined8 uStack_70;
  short local_60;
  undefined2 local_5e;
  uint local_5c;
  undefined8 local_58;
  undefined8 uStack_50;
  undefined4 local_48;
  short local_44;
  undefined2 local_42;
  uint local_40;
  undefined8 local_3c;
  undefined8 uStack_34;
  undefined4 local_2c;
  undefined1 local_28 [4];
  undefined1 auStack_24 [4];
  undefined4 local_20;
  undefined4 local_1c;
  undefined1 local_18;
  undefined1 local_14;
  
  uVar3 = *param_3;
  lVar7 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar7 == 0) || ((*(byte *)(lVar7 + 0x21c) & 1) != 0)) {
LAB_011cb7fb:
    lVar7 = 0;
  }
  else {
    uVar2 = *(ulong *)(lVar7 + 8);
    do {
      auVar9._8_8_ = uVar2 | 3;
      LOCK();
      uVar1 = *(ulong *)(lVar7 + 8);
      bVar8 = uVar2 == uVar1;
      if (bVar8) {
        *(ulong *)(lVar7 + 8) = auVar9._8_8_;
        uVar1 = uVar2;
      }
      UNLOCK();
      uVar2 = uVar1;
    } while (!bVar8);
    if ((uVar1 & 7) != 0) {
      if (((uint)uVar1 & 7) == 6) {
        *(undefined2 *)(param_1 + 0x12) = 0x11;
        auVar9._0_8_ = param_1;
        return auVar9;
      }
      goto LAB_011cb7fb;
    }
  }
  uVar2 = uVar3 & 0xffffffff;
  if ((uVar3 & 0xff00000000) == 0) {
    uVar2 = 0;
  }
  if (lVar7 == 0) {
    syscall();
                    /* WARNING: Could not find normalized switch variable to match jumptable */
    switch(switchD_011cb8b9::switchdataD_01002048) {
    case (undefined *)0x0:
      goto switchD_011cb8b9_caseD_0;
    default:
      goto switchD_011cb8b9_caseD_1;
    case (undefined *)0xc:
      goto switchD_011cb8b9_caseD_c;
    case (undefined *)0xd:
      goto switchD_011cb8b9_caseD_d;
    case (undefined *)0x16:
      goto switchD_011cb8b9_caseD_16;
    case (undefined *)0x17:
      goto switchD_011cb8b9_caseD_17;
    case (undefined *)0x18:
      goto switchD_011cb8b9_caseD_18;
    }
  }
  syscall();
                    /* WARNING: Could not find normalized switch variable to match jumptable */
  switch(switchD_011cb87f::switchdataD_01001f08) {
  case (undefined *)0x0:
                    /* WARNING: This code block may not be properly labeled as switch case */
    LOCK();
    *(ulong *)(lVar7 + 8) = *(ulong *)(lVar7 + 8) ^ 3;
    UNLOCK();
    break;
  default:
                    /* WARNING: This code block may not be properly labeled as switch case */
    LOCK();
    *(ulong *)(lVar7 + 8) = *(ulong *)(lVar7 + 8) ^ 3;
    UNLOCK();
switchD_011cb8b9_caseD_1:
                    /* WARNING: This code block may not be properly labeled as switch case */
    *(undefined2 *)(param_1 + 0x12) = 4;
    auVar15._8_8_ = uVar2;
    auVar15._0_8_ = param_1;
    return auVar15;
  case (undefined *)0xc:
                    /* WARNING: This code block may not be properly labeled as switch case */
    LOCK();
    *(ulong *)(lVar7 + 8) = *(ulong *)(lVar7 + 8) ^ 3;
    UNLOCK();
switchD_011cb8b9_caseD_c:
                    /* WARNING: This code block may not be properly labeled as switch case */
    *(undefined2 *)(param_1 + 0x12) = 2;
    auVar10._8_8_ = uVar2;
    auVar10._0_8_ = param_1;
    return auVar10;
  case (undefined *)0xd:
                    /* WARNING: This code block may not be properly labeled as switch case */
    LOCK();
    *(ulong *)(lVar7 + 8) = *(ulong *)(lVar7 + 8) ^ 3;
    UNLOCK();
switchD_011cb8b9_caseD_d:
                    /* WARNING: This code block may not be properly labeled as switch case */
    *(undefined2 *)(param_1 + 0x12) = 10;
    auVar11._8_8_ = uVar2;
    auVar11._0_8_ = param_1;
    return auVar11;
  case (undefined *)0x16:
                    /* WARNING: This code block may not be properly labeled as switch case */
    LOCK();
    *(ulong *)(lVar7 + 8) = *(ulong *)(lVar7 + 8) ^ 3;
    UNLOCK();
switchD_011cb8b9_caseD_16:
                    /* WARNING: This code block may not be properly labeled as switch case */
    *(undefined2 *)(param_1 + 0x12) = 0x51;
    auVar12._8_8_ = uVar2;
    auVar12._0_8_ = param_1;
    return auVar12;
  case (undefined *)0x17:
                    /* WARNING: This code block may not be properly labeled as switch case */
    LOCK();
    *(ulong *)(lVar7 + 8) = *(ulong *)(lVar7 + 8) ^ 3;
    UNLOCK();
switchD_011cb8b9_caseD_17:
                    /* WARNING: This code block may not be properly labeled as switch case */
    *(undefined2 *)(param_1 + 0x12) = 0x25;
    auVar14._8_8_ = uVar2;
    auVar14._0_8_ = param_1;
    return auVar14;
  case (undefined *)0x18:
                    /* WARNING: This code block may not be properly labeled as switch case */
    LOCK();
    *(ulong *)(lVar7 + 8) = *(ulong *)(lVar7 + 8) ^ 3;
    UNLOCK();
switchD_011cb8b9_caseD_18:
                    /* WARNING: This code block may not be properly labeled as switch case */
    *(undefined2 *)(param_1 + 0x12) = 0x24;
    auVar13._8_8_ = uVar2;
    auVar13._0_8_ = param_1;
    return auVar13;
  }
switchD_011cb8b9_caseD_0:
                    /* WARNING: This code block may not be properly labeled as switch case */
  lVar7 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar7 == 0) || ((*(byte *)(lVar7 + 0x21c) & 1) != 0)) {
LAB_011cb913:
    lVar7 = 0;
  }
  else {
    uVar3 = *(ulong *)(lVar7 + 8);
    do {
      LOCK();
      uVar1 = *(ulong *)(lVar7 + 8);
      bVar8 = uVar3 == uVar1;
      if (bVar8) {
        *(ulong *)(lVar7 + 8) = uVar3 | 3;
        uVar1 = uVar3;
      }
      UNLOCK();
      uVar3 = uVar1;
    } while (!bVar8);
    if ((uVar1 & 7) != 0) {
      uVar6 = (undefined6)(uVar2 >> 0x10);
      if (((uint)uVar1 & 7) == 6) {
        syscall();
        syscall();
        goto LAB_011cbc01;
      }
      goto LAB_011cb913;
    }
  }
  uVar6 = (undefined6)((ulong)local_28 >> 0x10);
  if (lVar7 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar7 + 8) = *(ulong *)(lVar7 + 8) ^ 3;
    UNLOCK();
  }
  lVar7 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar7 != 0) && ((*(byte *)(lVar7 + 0x21c) & 1) == 0)) {
    uVar3 = *(ulong *)(lVar7 + 8);
    do {
      LOCK();
      uVar2 = *(ulong *)(lVar7 + 8);
      bVar8 = uVar3 == uVar2;
      if (bVar8) {
        *(ulong *)(lVar7 + 8) = uVar3 | 3;
        uVar2 = uVar3;
      }
      UNLOCK();
      uVar3 = uVar2;
    } while (!bVar8);
    if ((uVar2 & 7) == 0) goto LAB_011cbae6;
    if (((uint)uVar2 & 7) == 6) {
      syscall();
      syscall();
LAB_011cbc01:
      auVar16._10_6_ = uVar6;
      auVar16._8_2_ = 0x11;
      *(undefined2 *)(param_1 + 0x12) = 0x11;
      auVar16._0_8_ = param_1;
      return auVar16;
    }
  }
  lVar7 = 0;
LAB_011cbae6:
  puVar5 = auStack_24;
  if (lVar7 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar7 + 8) = *(ulong *)(lVar7 + 8) ^ 3;
    UNLOCK();
  }
  uVar4 = 0;
  *(undefined2 *)(param_1 + 0x12) = 0;
  *param_1 = local_20;
  if (local_60 == 10) {
    local_14 = 1;
    uVar4 = swap_bytes(local_5e);
    puVar5 = (undefined1 *)(ulong)local_5c;
    uVar3 = CONCAT44(local_48,local_5c);
    local_78 = local_58;
    uStack_70 = uStack_50;
  }
  else if (local_60 == 2) {
    local_14 = 0;
    uVar4 = swap_bytes(local_5e);
    uVar3 = (ulong)CONCAT42(local_5c,uVar4);
  }
  else {
    uVar3 = 0x100007f0000;
    local_14 = 0;
  }
  *(ulong *)(param_1 + 1) = uVar3;
  *(undefined2 *)(param_1 + 3) = uVar4;
  *(undefined8 *)((long)param_1 + 0xe) = local_78;
  *(undefined8 *)((long)param_1 + 0x16) = uStack_70;
  *(undefined1 *)(param_1 + 8) = local_14;
  param_1[9] = local_1c;
  if (local_44 == 10) {
    local_18 = 1;
    uVar4 = swap_bytes(local_42);
    puVar5 = (undefined1 *)(ulong)local_40;
    uVar3 = CONCAT44(local_2c,local_40);
    local_88 = local_3c;
    uStack_80 = uStack_34;
  }
  else if (local_44 == 2) {
    local_18 = 0;
    uVar4 = swap_bytes(local_42);
    uVar3 = (ulong)CONCAT42(local_40,uVar4);
  }
  else {
    uVar3 = 0x100007f0000;
    local_18 = 0;
  }
  *(ulong *)(param_1 + 10) = uVar3;
  *(undefined2 *)(param_1 + 0xc) = uVar4;
  *(undefined8 *)((long)param_1 + 0x32) = local_88;
  *(undefined8 *)((long)param_1 + 0x3a) = uStack_80;
  *(undefined1 *)(param_1 + 0x11) = local_18;
  auVar17._8_8_ = puVar5;
  auVar17._0_8_ = param_1;
  return auVar17;
}


// ---- FUN_011cbce0 @ 011cbce0

/* WARNING: Removing unreachable block (ram,0x011cbdc6) */
/* WARNING: Removing unreachable block (ram,0x011cbdf7) */
/* WARNING: Removing unreachable block (ram,0x011cbe00) */
/* WARNING: Removing unreachable block (ram,0x011cbdcb) */
/* WARNING: Removing unreachable block (ram,0x011cbdd0) */
/* WARNING: Removing unreachable block (ram,0x011cbdd7) */
/* WARNING: Removing unreachable block (ram,0x011cbddf) */
/* WARNING: Removing unreachable block (ram,0x011cbde7) */

undefined1  [16] FUN_011cbce0(undefined8 param_1,undefined8 param_2,long param_3)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  long in_FS_OFFSET;
  bool bVar5;
  undefined1 auVar6 [16];
  
  lVar3 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar3 != 0) && ((*(byte *)(lVar3 + 0x21c) & 1) == 0)) {
    uVar1 = *(ulong *)(lVar3 + 8);
    do {
      LOCK();
      uVar2 = *(ulong *)(lVar3 + 8);
      bVar5 = uVar1 == uVar2;
      if (bVar5) {
        *(ulong *)(lVar3 + 8) = uVar1 | 3;
        uVar2 = uVar1;
      }
      UNLOCK();
      uVar1 = uVar2;
    } while (!bVar5);
    if ((uVar2 & 7) == 0) goto LAB_011cbd39;
    if (((uint)uVar2 & 7) == 6) {
      auVar6._8_8_ = param_3;
      auVar6._0_8_ = 0x11;
      return auVar6;
    }
  }
  lVar3 = 0;
LAB_011cbd39:
  if (param_3 != 0) {
    lVar4 = 0;
    if (lVar3 == 0) {
      do {
        syscall();
        lVar4 = lVar4 + 0x13e;
      } while (param_3 != lVar4);
    }
    else {
      do {
        syscall();
        LOCK();
        *(ulong *)(lVar3 + 8) = *(ulong *)(lVar3 + 8) ^ 3;
        UNLOCK();
        lVar4 = lVar4 + 0x13e;
      } while (param_3 != lVar4);
    }
  }
  return ZEXT816(0) << 0x40;
}


// ---- FUN_011cbe10 @ 011cbe10

void FUN_011cbe10(undefined8 param_1,long param_2,ulong param_3)

{
  ulong *puVar1;
  long lVar2;
  ulong uVar3;
  undefined8 *puVar4;
  long lVar5;
  ulong uVar6;
  long in_FS_OFFSET;
  undefined8 local_280;
  undefined1 local_278 [512];
  undefined1 local_78 [32];
  undefined8 local_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  ulong *local_38;
  
  lVar2 = *(long *)(in_FS_OFFSET + -0x40010);
  if (lVar2 == 0) {
    FUN_011cc5e0(param_1,param_2,param_3);
    return;
  }
  puVar1 = (ulong *)(lVar2 + 0x10);
  uVar3 = *(ulong *)(lVar2 + 0x10);
  if (uVar3 == 0xffffffffffffffff) {
    FUN_011cc5e0(param_1,local_78,0x20);
    local_280 = 0;
    FUN_011cc1c0(local_278,local_78);
    FUN_011f4580(puVar1,&local_280,0x208);
    uVar3 = *puVar1;
  }
  if (uVar3 != 0x1e0) {
    uVar6 = 0x1e0 - uVar3;
    if (param_3 <= 0x1e0 - uVar3) {
      uVar6 = param_3;
    }
    local_38 = puVar1;
    FUN_011f4580(param_2,uVar3 + lVar2 + 0x38,uVar6);
    FUN_011f4160(*local_38 + lVar2 + 0x38,0,uVar6);
    param_2 = param_2 + uVar6;
    param_3 = param_3 - uVar6;
    *local_38 = *local_38 + uVar6;
    puVar1 = local_38;
  }
  if (param_3 != 0) {
    lVar5 = lVar2 + 0x38;
    local_58 = *(undefined8 *)(lVar2 + 0x18);
    uStack_50 = *(undefined8 *)(lVar2 + 0x20);
    uStack_48 = *(undefined8 *)(lVar2 + 0x28);
    uStack_40 = *(undefined8 *)(lVar2 + 0x30);
    puVar4 = (undefined8 *)(lVar2 + 0x18);
    FUN_011cc1c0(puVar4,&local_58);
    if (0x1df < param_3) {
      do {
        FUN_011f4580(param_2,lVar5,0x1e0);
        param_2 = param_2 + 0x1e0;
        param_3 = param_3 - 0x1e0;
        local_58 = *puVar4;
        uStack_50 = *(undefined8 *)(lVar2 + 0x20);
        uStack_48 = *(undefined8 *)(lVar2 + 0x28);
        uStack_40 = *(undefined8 *)(lVar2 + 0x30);
        FUN_011cc1c0(puVar4,&local_58);
        *puVar1 = 0;
      } while (0x1df < param_3);
      if (param_3 == 0) {
        return;
      }
    }
    FUN_011f4580(param_2,lVar5,param_3);
    FUN_011f4160(lVar5,0,param_3);
    *puVar1 = param_3;
  }
  return;
}


// ---- FUN_011cbfe0 @ 011cbfe0

/* WARNING: Removing unreachable block (ram,0x011cc0e5) */
/* WARNING: Removing unreachable block (ram,0x011cc0ef) */
/* WARNING: Removing unreachable block (ram,0x011cc170) */
/* WARNING: Removing unreachable block (ram,0x011cc1a3) */
/* WARNING: Removing unreachable block (ram,0x011cc0f8) */
/* WARNING: Removing unreachable block (ram,0x011cc100) */
/* WARNING: Removing unreachable block (ram,0x011cc110) */
/* WARNING: Removing unreachable block (ram,0x011cc117) */
/* WARNING: Removing unreachable block (ram,0x011cc120) */
/* WARNING: Removing unreachable block (ram,0x011cc1a8) */
/* WARNING: Removing unreachable block (ram,0x011cc12c) */

undefined1  [16] FUN_011cbfe0(undefined8 param_1,undefined8 *param_2,ulong param_3)

{
  long lVar1;
  undefined1 auVar2 [16];
  ulong uVar3;
  ulong uVar4;
  undefined8 uVar5;
  ulong uVar6;
  long lVar7;
  long in_FS_OFFSET;
  bool bVar8;
  undefined1 auVar9 [16];
  
  if (*(char *)(param_2 + 4) == '\0') {
    auVar2._8_8_ = 0;
    auVar2._0_8_ = param_3;
    return auVar2 << 0x40;
  }
  FUN_011f6850(*param_2,(long)(int)param_2[1],1000000000,0);
  lVar1 = *(long *)(in_FS_OFFSET + -0x40010);
  lVar7 = 0;
  if (lVar1 != 0) {
    if ((*(byte *)(lVar1 + 0x21c) & 1) == 0) {
      uVar3 = *(ulong *)(lVar1 + 8);
      do {
        uVar6 = uVar3 | 3;
        LOCK();
        uVar4 = *(ulong *)(lVar1 + 8);
        bVar8 = uVar3 == uVar4;
        if (bVar8) {
          *(ulong *)(lVar1 + 8) = uVar6;
          uVar4 = uVar3;
        }
        UNLOCK();
        uVar3 = uVar4;
      } while (!bVar8);
      lVar7 = lVar1;
      if ((uVar4 & 7) == 0) goto LAB_011cc0bc;
      uVar5 = 0x11;
      if (((uint)uVar4 & 7) == 6) goto LAB_011cc1ac;
    }
    lVar7 = 0;
  }
LAB_011cc0bc:
  syscall();
  uVar6 = 0;
  if (lVar7 != 0) {
    LOCK();
    *(ulong *)(lVar7 + 8) = *(ulong *)(lVar7 + 8) ^ 3;
    UNLOCK();
  }
  uVar5 = 0;
LAB_011cc1ac:
  auVar9._8_8_ = uVar6;
  auVar9._0_8_ = uVar5;
  return auVar9;
}


// ---- FUN_011cc1c0 @ 011cc1c0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_011cc1c0(long param_1,undefined1 (*param_2) [16])

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [32];
  undefined1 auVar5 [32];
  undefined1 auVar6 [32];
  undefined1 auVar7 [32];
  undefined1 auVar8 [32];
  undefined1 auVar9 [32];
  undefined1 auVar10 [32];
  undefined1 auVar11 [32];
  undefined1 auVar12 [32];
  undefined1 auVar13 [32];
  undefined1 auVar14 [32];
  undefined1 auVar15 [32];
  undefined1 auVar16 [32];
  undefined1 auVar17 [32];
  undefined1 auVar18 [32];
  undefined1 auVar19 [32];
  undefined1 auVar20 [32];
  undefined1 auVar21 [32];
  undefined1 auVar22 [32];
  undefined1 auVar23 [32];
  undefined1 auVar24 [32];
  undefined1 auVar25 [32];
  undefined1 auVar26 [32];
  undefined1 auVar27 [32];
  undefined1 auVar28 [32];
  undefined1 auVar29 [32];
  undefined1 auVar32 [32];
  undefined1 auVar33 [32];
  undefined1 auVar34 [32];
  int iVar35;
  int iVar36;
  int iVar37;
  int iVar38;
  undefined4 uVar39;
  undefined4 uVar40;
  undefined4 uVar41;
  undefined4 uVar42;
  undefined1 auVar43 [32];
  undefined1 auVar44 [32];
  undefined1 auVar45 [32];
  int iVar46;
  ulong uVar47;
  int iVar48;
  int iVar50;
  int iVar51;
  int iVar52;
  undefined1 auVar49 [32];
  undefined1 auVar53 [64];
  undefined1 auVar54 [32];
  undefined1 auVar55 [32];
  undefined1 auVar56 [32];
  undefined1 auVar57 [32];
  undefined1 auVar58 [32];
  undefined1 auVar59 [32];
  undefined1 auVar30 [32];
  undefined1 auVar31 [32];
  
  iVar46 = DAT_01001490;
  auVar45 = _DAT_01001360;
  auVar44 = _DAT_01001340;
  auVar43 = _DAT_010012a0;
  uVar42 = s_te_kexpand_32_by_01000530._12_4_;
  uVar41 = s_te_kexpand_32_by_01000530._8_4_;
  uVar40 = s_te_kexpand_32_by_01000530._4_4_;
  uVar39 = s_te_kexpand_32_by_01000530._0_4_;
  auVar1 = *param_2;
  auVar49._16_16_ = auVar1;
  auVar49._0_16_ = auVar1;
  iVar35 = *(int *)param_2[1];
  iVar36 = *(int *)(param_2[1] + 4);
  iVar37 = *(int *)(param_2[1] + 8);
  iVar38 = *(int *)(param_2[1] + 0xc);
  iVar48 = auVar1._0_4_;
  auVar4._0_4_ = iVar48 + _DAT_010013a0;
  iVar50 = auVar1._4_4_;
  auVar4._4_4_ = iVar50 + _UNK_010013a4;
  iVar51 = auVar1._8_4_;
  auVar4._8_4_ = iVar51 + _UNK_010013a8;
  iVar52 = auVar1._12_4_;
  auVar4._12_4_ = iVar52 + _UNK_010013ac;
  auVar4._16_4_ = iVar48 + _UNK_010013b0;
  auVar4._20_4_ = iVar50 + _UNK_010013b4;
  auVar4._24_4_ = iVar51 + _UNK_010013b8;
  auVar4._28_4_ = iVar52 + _UNK_010013bc;
  auVar53 = ZEXT864(DAT_01000500);
  uVar47 = 0xffffffffffffff80;
  do {
    auVar56 = vpermd_avx2(_DAT_01001300,auVar53._0_32_);
    auVar34 = vpblendd_avx2(auVar56,SUB6432(ZEXT1664((undefined1  [16])0x0),0),0xee);
    auVar59 = vpshufb_avx2(auVar34 ^ auVar4,auVar44);
    auVar56._0_4_ = auVar59._0_4_ + iVar35;
    auVar56._4_4_ = auVar59._4_4_ + iVar36;
    auVar56._8_4_ = auVar59._8_4_ + iVar37;
    auVar56._12_4_ = auVar59._12_4_ + iVar38;
    auVar56._16_4_ = auVar59._16_4_ + iVar35;
    auVar56._20_4_ = auVar59._20_4_ + iVar36;
    auVar56._24_4_ = auVar59._24_4_ + iVar37;
    auVar56._28_4_ = auVar59._28_4_ + iVar38;
    auVar57 = vpsrld_avx2(auVar56 ^ auVar49,0x14);
    auVar55 = vpslld_avx2(auVar56 ^ auVar49,0xc);
    auVar57 = vpor_avx2(auVar55,auVar57);
    auVar55._0_4_ = auVar57._0_4_ + auVar4._0_4_;
    auVar55._4_4_ = auVar57._4_4_ + auVar4._4_4_;
    auVar55._8_4_ = auVar57._8_4_ + auVar4._8_4_;
    auVar55._12_4_ = auVar57._12_4_ + auVar4._12_4_;
    auVar55._16_4_ = auVar57._16_4_ + auVar4._16_4_;
    auVar55._20_4_ = auVar57._20_4_ + auVar4._20_4_;
    auVar55._24_4_ = auVar57._24_4_ + auVar4._24_4_;
    auVar55._28_4_ = auVar57._28_4_ + auVar4._28_4_;
    auVar58 = vpshufb_avx2(auVar55,auVar45);
    auVar32 = vpshufb_avx2(auVar59,auVar45);
    auVar32 = auVar32 ^ auVar58;
    auVar59._0_4_ = auVar56._0_4_ + auVar32._0_4_;
    auVar59._4_4_ = auVar56._4_4_ + auVar32._4_4_;
    auVar59._8_4_ = auVar56._8_4_ + auVar32._8_4_;
    auVar59._12_4_ = auVar56._12_4_ + auVar32._12_4_;
    auVar59._16_4_ = auVar56._16_4_ + auVar32._16_4_;
    auVar59._20_4_ = auVar56._20_4_ + auVar32._20_4_;
    auVar59._24_4_ = auVar56._24_4_ + auVar32._24_4_;
    auVar59._28_4_ = auVar56._28_4_ + auVar32._28_4_;
    auVar55 = vpshufd_avx2(auVar55,0x93);
    auVar58 = vpsrld_avx2(auVar59 ^ auVar57,0x19);
    auVar56 = vpslld_avx2(auVar59 ^ auVar57,7);
    auVar56 = vpor_avx2(auVar56,auVar58);
    auVar57._0_4_ = auVar56._0_4_ + auVar55._0_4_;
    auVar57._4_4_ = auVar56._4_4_ + auVar55._4_4_;
    auVar57._8_4_ = auVar56._8_4_ + auVar55._8_4_;
    auVar57._12_4_ = auVar56._12_4_ + auVar55._12_4_;
    auVar57._16_4_ = auVar56._16_4_ + auVar55._16_4_;
    auVar57._20_4_ = auVar56._20_4_ + auVar55._20_4_;
    auVar57._24_4_ = auVar56._24_4_ + auVar55._24_4_;
    auVar57._28_4_ = auVar56._28_4_ + auVar55._28_4_;
    auVar33 = vpshufd_avx2(auVar59,0x39);
    auVar55 = vpshufb_avx2(auVar57,auVar44);
    auVar59 = vpshufb_avx2(auVar32,auVar43);
    auVar55 = auVar55 ^ auVar59;
    auVar58._0_4_ = auVar33._0_4_ + auVar55._0_4_;
    auVar58._4_4_ = auVar33._4_4_ + auVar55._4_4_;
    auVar58._8_4_ = auVar33._8_4_ + auVar55._8_4_;
    auVar58._12_4_ = auVar33._12_4_ + auVar55._12_4_;
    auVar58._16_4_ = auVar33._16_4_ + auVar55._16_4_;
    auVar58._20_4_ = auVar33._20_4_ + auVar55._20_4_;
    auVar58._24_4_ = auVar33._24_4_ + auVar55._24_4_;
    auVar58._28_4_ = auVar33._28_4_ + auVar55._28_4_;
    auVar59 = vpsrld_avx2(auVar58 ^ auVar56,0x14);
    auVar56 = vpslld_avx2(auVar58 ^ auVar56,0xc);
    auVar56 = vpor_avx2(auVar56,auVar59);
    auVar32._0_4_ = auVar56._0_4_ + auVar57._0_4_;
    auVar32._4_4_ = auVar56._4_4_ + auVar57._4_4_;
    auVar32._8_4_ = auVar56._8_4_ + auVar57._8_4_;
    auVar32._12_4_ = auVar56._12_4_ + auVar57._12_4_;
    auVar32._16_4_ = auVar56._16_4_ + auVar57._16_4_;
    auVar32._20_4_ = auVar56._20_4_ + auVar57._20_4_;
    auVar32._24_4_ = auVar56._24_4_ + auVar57._24_4_;
    auVar32._28_4_ = auVar56._28_4_ + auVar57._28_4_;
    auVar59 = vpshufb_avx2(auVar32,auVar45);
    auVar55 = vpshufb_avx2(auVar55,auVar45);
    auVar57 = vpshufd_avx2(auVar32,0x39);
    auVar59 = auVar59 ^ auVar55;
    auVar33._0_4_ = auVar58._0_4_ + auVar59._0_4_;
    auVar33._4_4_ = auVar58._4_4_ + auVar59._4_4_;
    auVar33._8_4_ = auVar58._8_4_ + auVar59._8_4_;
    auVar33._12_4_ = auVar58._12_4_ + auVar59._12_4_;
    auVar33._16_4_ = auVar58._16_4_ + auVar59._16_4_;
    auVar33._20_4_ = auVar58._20_4_ + auVar59._20_4_;
    auVar33._24_4_ = auVar58._24_4_ + auVar59._24_4_;
    auVar33._28_4_ = auVar58._28_4_ + auVar59._28_4_;
    auVar55 = vpsrld_avx2(auVar33 ^ auVar56,0x19);
    auVar56 = vpslld_avx2(auVar33 ^ auVar56,7);
    auVar58 = vpshufd_avx2(auVar33,0x93);
    auVar56 = vpor_avx2(auVar56,auVar55);
    auVar5._0_4_ = auVar56._0_4_ + auVar57._0_4_;
    auVar5._4_4_ = auVar56._4_4_ + auVar57._4_4_;
    auVar5._8_4_ = auVar56._8_4_ + auVar57._8_4_;
    auVar5._12_4_ = auVar56._12_4_ + auVar57._12_4_;
    auVar5._16_4_ = auVar56._16_4_ + auVar57._16_4_;
    auVar5._20_4_ = auVar56._20_4_ + auVar57._20_4_;
    auVar5._24_4_ = auVar56._24_4_ + auVar57._24_4_;
    auVar5._28_4_ = auVar56._28_4_ + auVar57._28_4_;
    auVar55 = vpshufb_avx2(auVar5,auVar44);
    auVar59 = vpshufb_avx2(auVar59,auVar43);
    auVar55 = auVar55 ^ auVar59;
    auVar6._0_4_ = auVar58._0_4_ + auVar55._0_4_;
    auVar6._4_4_ = auVar58._4_4_ + auVar55._4_4_;
    auVar6._8_4_ = auVar58._8_4_ + auVar55._8_4_;
    auVar6._12_4_ = auVar58._12_4_ + auVar55._12_4_;
    auVar6._16_4_ = auVar58._16_4_ + auVar55._16_4_;
    auVar6._20_4_ = auVar58._20_4_ + auVar55._20_4_;
    auVar6._24_4_ = auVar58._24_4_ + auVar55._24_4_;
    auVar6._28_4_ = auVar58._28_4_ + auVar55._28_4_;
    auVar59 = vpsrld_avx2(auVar6 ^ auVar56,0x14);
    auVar56 = vpslld_avx2(auVar6 ^ auVar56,0xc);
    auVar56 = vpor_avx2(auVar56,auVar59);
    auVar7._0_4_ = auVar56._0_4_ + auVar5._0_4_;
    auVar7._4_4_ = auVar56._4_4_ + auVar5._4_4_;
    auVar7._8_4_ = auVar56._8_4_ + auVar5._8_4_;
    auVar7._12_4_ = auVar56._12_4_ + auVar5._12_4_;
    auVar7._16_4_ = auVar56._16_4_ + auVar5._16_4_;
    auVar7._20_4_ = auVar56._20_4_ + auVar5._20_4_;
    auVar7._24_4_ = auVar56._24_4_ + auVar5._24_4_;
    auVar7._28_4_ = auVar56._28_4_ + auVar5._28_4_;
    auVar57 = vpshufd_avx2(auVar7,0x93);
    auVar59 = vpshufb_avx2(auVar7,auVar45);
    auVar55 = vpshufb_avx2(auVar55,auVar45);
    auVar59 = auVar59 ^ auVar55;
    auVar8._0_4_ = auVar6._0_4_ + auVar59._0_4_;
    auVar8._4_4_ = auVar6._4_4_ + auVar59._4_4_;
    auVar8._8_4_ = auVar6._8_4_ + auVar59._8_4_;
    auVar8._12_4_ = auVar6._12_4_ + auVar59._12_4_;
    auVar8._16_4_ = auVar6._16_4_ + auVar59._16_4_;
    auVar8._20_4_ = auVar6._20_4_ + auVar59._20_4_;
    auVar8._24_4_ = auVar6._24_4_ + auVar59._24_4_;
    auVar8._28_4_ = auVar6._28_4_ + auVar59._28_4_;
    auVar55 = vpsrld_avx2(auVar8 ^ auVar56,0x19);
    auVar56 = vpslld_avx2(auVar8 ^ auVar56,7);
    auVar56 = vpor_avx2(auVar56,auVar55);
    auVar9._0_4_ = auVar56._0_4_ + auVar57._0_4_;
    auVar9._4_4_ = auVar56._4_4_ + auVar57._4_4_;
    auVar9._8_4_ = auVar56._8_4_ + auVar57._8_4_;
    auVar9._12_4_ = auVar56._12_4_ + auVar57._12_4_;
    auVar9._16_4_ = auVar56._16_4_ + auVar57._16_4_;
    auVar9._20_4_ = auVar56._20_4_ + auVar57._20_4_;
    auVar9._24_4_ = auVar56._24_4_ + auVar57._24_4_;
    auVar9._28_4_ = auVar56._28_4_ + auVar57._28_4_;
    auVar55 = vpshufb_avx2(auVar9,auVar44);
    auVar59 = vpshufb_avx2(auVar59,auVar43);
    auVar57 = vpshufd_avx2(auVar8,0x39);
    auVar55 = auVar55 ^ auVar59;
    auVar10._0_4_ = auVar57._0_4_ + auVar55._0_4_;
    auVar10._4_4_ = auVar57._4_4_ + auVar55._4_4_;
    auVar10._8_4_ = auVar57._8_4_ + auVar55._8_4_;
    auVar10._12_4_ = auVar57._12_4_ + auVar55._12_4_;
    auVar10._16_4_ = auVar57._16_4_ + auVar55._16_4_;
    auVar10._20_4_ = auVar57._20_4_ + auVar55._20_4_;
    auVar10._24_4_ = auVar57._24_4_ + auVar55._24_4_;
    auVar10._28_4_ = auVar57._28_4_ + auVar55._28_4_;
    auVar59 = vpsrld_avx2(auVar10 ^ auVar56,0x14);
    auVar56 = vpslld_avx2(auVar10 ^ auVar56,0xc);
    auVar56 = vpor_avx2(auVar56,auVar59);
    auVar11._0_4_ = auVar56._0_4_ + auVar9._0_4_;
    auVar11._4_4_ = auVar56._4_4_ + auVar9._4_4_;
    auVar11._8_4_ = auVar56._8_4_ + auVar9._8_4_;
    auVar11._12_4_ = auVar56._12_4_ + auVar9._12_4_;
    auVar11._16_4_ = auVar56._16_4_ + auVar9._16_4_;
    auVar11._20_4_ = auVar56._20_4_ + auVar9._20_4_;
    auVar11._24_4_ = auVar56._24_4_ + auVar9._24_4_;
    auVar11._28_4_ = auVar56._28_4_ + auVar9._28_4_;
    auVar59 = vpshufb_avx2(auVar11,auVar45);
    auVar55 = vpshufb_avx2(auVar55,auVar45);
    auVar59 = auVar59 ^ auVar55;
    auVar12._0_4_ = auVar10._0_4_ + auVar59._0_4_;
    auVar12._4_4_ = auVar10._4_4_ + auVar59._4_4_;
    auVar12._8_4_ = auVar10._8_4_ + auVar59._8_4_;
    auVar12._12_4_ = auVar10._12_4_ + auVar59._12_4_;
    auVar12._16_4_ = auVar10._16_4_ + auVar59._16_4_;
    auVar12._20_4_ = auVar10._20_4_ + auVar59._20_4_;
    auVar12._24_4_ = auVar10._24_4_ + auVar59._24_4_;
    auVar12._28_4_ = auVar10._28_4_ + auVar59._28_4_;
    auVar55 = vpshufd_avx2(auVar11,0x39);
    auVar57 = vpsrld_avx2(auVar12 ^ auVar56,0x19);
    auVar56 = vpslld_avx2(auVar12 ^ auVar56,7);
    auVar56 = vpor_avx2(auVar56,auVar57);
    auVar13._0_4_ = auVar56._0_4_ + auVar55._0_4_;
    auVar13._4_4_ = auVar56._4_4_ + auVar55._4_4_;
    auVar13._8_4_ = auVar56._8_4_ + auVar55._8_4_;
    auVar13._12_4_ = auVar56._12_4_ + auVar55._12_4_;
    auVar13._16_4_ = auVar56._16_4_ + auVar55._16_4_;
    auVar13._20_4_ = auVar56._20_4_ + auVar55._20_4_;
    auVar13._24_4_ = auVar56._24_4_ + auVar55._24_4_;
    auVar13._28_4_ = auVar56._28_4_ + auVar55._28_4_;
    auVar57 = vpshufd_avx2(auVar12,0x93);
    auVar55 = vpshufb_avx2(auVar13,auVar44);
    auVar59 = vpshufb_avx2(auVar59,auVar43);
    auVar55 = auVar55 ^ auVar59;
    auVar14._0_4_ = auVar57._0_4_ + auVar55._0_4_;
    auVar14._4_4_ = auVar57._4_4_ + auVar55._4_4_;
    auVar14._8_4_ = auVar57._8_4_ + auVar55._8_4_;
    auVar14._12_4_ = auVar57._12_4_ + auVar55._12_4_;
    auVar14._16_4_ = auVar57._16_4_ + auVar55._16_4_;
    auVar14._20_4_ = auVar57._20_4_ + auVar55._20_4_;
    auVar14._24_4_ = auVar57._24_4_ + auVar55._24_4_;
    auVar14._28_4_ = auVar57._28_4_ + auVar55._28_4_;
    auVar59 = vpsrld_avx2(auVar14 ^ auVar56,0x14);
    auVar56 = vpslld_avx2(auVar14 ^ auVar56,0xc);
    auVar56 = vpor_avx2(auVar56,auVar59);
    auVar15._0_4_ = auVar56._0_4_ + auVar13._0_4_;
    auVar15._4_4_ = auVar56._4_4_ + auVar13._4_4_;
    auVar15._8_4_ = auVar56._8_4_ + auVar13._8_4_;
    auVar15._12_4_ = auVar56._12_4_ + auVar13._12_4_;
    auVar15._16_4_ = auVar56._16_4_ + auVar13._16_4_;
    auVar15._20_4_ = auVar56._20_4_ + auVar13._20_4_;
    auVar15._24_4_ = auVar56._24_4_ + auVar13._24_4_;
    auVar15._28_4_ = auVar56._28_4_ + auVar13._28_4_;
    auVar59 = vpshufb_avx2(auVar15,auVar45);
    auVar55 = vpshufb_avx2(auVar55,auVar45);
    auVar57 = vpshufd_avx2(auVar15,0x93);
    auVar59 = auVar59 ^ auVar55;
    auVar16._0_4_ = auVar14._0_4_ + auVar59._0_4_;
    auVar16._4_4_ = auVar14._4_4_ + auVar59._4_4_;
    auVar16._8_4_ = auVar14._8_4_ + auVar59._8_4_;
    auVar16._12_4_ = auVar14._12_4_ + auVar59._12_4_;
    auVar16._16_4_ = auVar14._16_4_ + auVar59._16_4_;
    auVar16._20_4_ = auVar14._20_4_ + auVar59._20_4_;
    auVar16._24_4_ = auVar14._24_4_ + auVar59._24_4_;
    auVar16._28_4_ = auVar14._28_4_ + auVar59._28_4_;
    auVar55 = vpsrld_avx2(auVar16 ^ auVar56,0x19);
    auVar56 = vpslld_avx2(auVar16 ^ auVar56,7);
    auVar58 = vpshufd_avx2(auVar16,0x39);
    auVar56 = vpor_avx2(auVar56,auVar55);
    auVar17._0_4_ = auVar56._0_4_ + auVar57._0_4_;
    auVar17._4_4_ = auVar56._4_4_ + auVar57._4_4_;
    auVar17._8_4_ = auVar56._8_4_ + auVar57._8_4_;
    auVar17._12_4_ = auVar56._12_4_ + auVar57._12_4_;
    auVar17._16_4_ = auVar56._16_4_ + auVar57._16_4_;
    auVar17._20_4_ = auVar56._20_4_ + auVar57._20_4_;
    auVar17._24_4_ = auVar56._24_4_ + auVar57._24_4_;
    auVar17._28_4_ = auVar56._28_4_ + auVar57._28_4_;
    auVar55 = vpshufb_avx2(auVar17,auVar44);
    auVar59 = vpshufb_avx2(auVar59,auVar43);
    auVar55 = auVar55 ^ auVar59;
    auVar18._0_4_ = auVar58._0_4_ + auVar55._0_4_;
    auVar18._4_4_ = auVar58._4_4_ + auVar55._4_4_;
    auVar18._8_4_ = auVar58._8_4_ + auVar55._8_4_;
    auVar18._12_4_ = auVar58._12_4_ + auVar55._12_4_;
    auVar18._16_4_ = auVar58._16_4_ + auVar55._16_4_;
    auVar18._20_4_ = auVar58._20_4_ + auVar55._20_4_;
    auVar18._24_4_ = auVar58._24_4_ + auVar55._24_4_;
    auVar18._28_4_ = auVar58._28_4_ + auVar55._28_4_;
    auVar59 = vpsrld_avx2(auVar18 ^ auVar56,0x14);
    auVar56 = vpslld_avx2(auVar18 ^ auVar56,0xc);
    auVar56 = vpor_avx2(auVar56,auVar59);
    auVar19._0_4_ = auVar56._0_4_ + auVar17._0_4_;
    auVar19._4_4_ = auVar56._4_4_ + auVar17._4_4_;
    auVar19._8_4_ = auVar56._8_4_ + auVar17._8_4_;
    auVar19._12_4_ = auVar56._12_4_ + auVar17._12_4_;
    auVar19._16_4_ = auVar56._16_4_ + auVar17._16_4_;
    auVar19._20_4_ = auVar56._20_4_ + auVar17._20_4_;
    auVar19._24_4_ = auVar56._24_4_ + auVar17._24_4_;
    auVar19._28_4_ = auVar56._28_4_ + auVar17._28_4_;
    auVar57 = vpshufd_avx2(auVar19,0x39);
    auVar59 = vpshufb_avx2(auVar19,auVar45);
    auVar55 = vpshufb_avx2(auVar55,auVar45);
    auVar59 = auVar59 ^ auVar55;
    auVar20._0_4_ = auVar18._0_4_ + auVar59._0_4_;
    auVar20._4_4_ = auVar18._4_4_ + auVar59._4_4_;
    auVar20._8_4_ = auVar18._8_4_ + auVar59._8_4_;
    auVar20._12_4_ = auVar18._12_4_ + auVar59._12_4_;
    auVar20._16_4_ = auVar18._16_4_ + auVar59._16_4_;
    auVar20._20_4_ = auVar18._20_4_ + auVar59._20_4_;
    auVar20._24_4_ = auVar18._24_4_ + auVar59._24_4_;
    auVar20._28_4_ = auVar18._28_4_ + auVar59._28_4_;
    auVar55 = vpsrld_avx2(auVar20 ^ auVar56,0x19);
    auVar56 = vpslld_avx2(auVar20 ^ auVar56,7);
    auVar56 = vpor_avx2(auVar56,auVar55);
    auVar21._0_4_ = auVar56._0_4_ + auVar57._0_4_;
    auVar21._4_4_ = auVar56._4_4_ + auVar57._4_4_;
    auVar21._8_4_ = auVar56._8_4_ + auVar57._8_4_;
    auVar21._12_4_ = auVar56._12_4_ + auVar57._12_4_;
    auVar21._16_4_ = auVar56._16_4_ + auVar57._16_4_;
    auVar21._20_4_ = auVar56._20_4_ + auVar57._20_4_;
    auVar21._24_4_ = auVar56._24_4_ + auVar57._24_4_;
    auVar21._28_4_ = auVar56._28_4_ + auVar57._28_4_;
    auVar55 = vpshufb_avx2(auVar21,auVar44);
    auVar59 = vpshufb_avx2(auVar59,auVar43);
    auVar57 = vpshufd_avx2(auVar20,0x93);
    auVar55 = auVar55 ^ auVar59;
    auVar22._0_4_ = auVar57._0_4_ + auVar55._0_4_;
    auVar22._4_4_ = auVar57._4_4_ + auVar55._4_4_;
    auVar22._8_4_ = auVar57._8_4_ + auVar55._8_4_;
    auVar22._12_4_ = auVar57._12_4_ + auVar55._12_4_;
    auVar22._16_4_ = auVar57._16_4_ + auVar55._16_4_;
    auVar22._20_4_ = auVar57._20_4_ + auVar55._20_4_;
    auVar22._24_4_ = auVar57._24_4_ + auVar55._24_4_;
    auVar22._28_4_ = auVar57._28_4_ + auVar55._28_4_;
    auVar59 = vpsrld_avx2(auVar22 ^ auVar56,0x14);
    auVar56 = vpslld_avx2(auVar22 ^ auVar56,0xc);
    auVar56 = vpor_avx2(auVar56,auVar59);
    auVar23._0_4_ = auVar56._0_4_ + auVar21._0_4_;
    auVar23._4_4_ = auVar56._4_4_ + auVar21._4_4_;
    auVar23._8_4_ = auVar56._8_4_ + auVar21._8_4_;
    auVar23._12_4_ = auVar56._12_4_ + auVar21._12_4_;
    auVar23._16_4_ = auVar56._16_4_ + auVar21._16_4_;
    auVar23._20_4_ = auVar56._20_4_ + auVar21._20_4_;
    auVar23._24_4_ = auVar56._24_4_ + auVar21._24_4_;
    auVar23._28_4_ = auVar56._28_4_ + auVar21._28_4_;
    auVar59 = vpshufb_avx2(auVar23,auVar45);
    auVar55 = vpshufb_avx2(auVar55,auVar45);
    auVar59 = auVar59 ^ auVar55;
    auVar24._0_4_ = auVar22._0_4_ + auVar59._0_4_;
    auVar24._4_4_ = auVar22._4_4_ + auVar59._4_4_;
    auVar24._8_4_ = auVar22._8_4_ + auVar59._8_4_;
    auVar24._12_4_ = auVar22._12_4_ + auVar59._12_4_;
    auVar24._16_4_ = auVar22._16_4_ + auVar59._16_4_;
    auVar24._20_4_ = auVar22._20_4_ + auVar59._20_4_;
    auVar24._24_4_ = auVar22._24_4_ + auVar59._24_4_;
    auVar24._28_4_ = auVar22._28_4_ + auVar59._28_4_;
    auVar55 = vpshufd_avx2(auVar23,0x93);
    auVar57 = vpsrld_avx2(auVar24 ^ auVar56,0x19);
    auVar56 = vpslld_avx2(auVar24 ^ auVar56,7);
    auVar56 = vpor_avx2(auVar56,auVar57);
    auVar25._0_4_ = auVar56._0_4_ + auVar55._0_4_;
    auVar25._4_4_ = auVar56._4_4_ + auVar55._4_4_;
    auVar25._8_4_ = auVar56._8_4_ + auVar55._8_4_;
    auVar25._12_4_ = auVar56._12_4_ + auVar55._12_4_;
    auVar25._16_4_ = auVar56._16_4_ + auVar55._16_4_;
    auVar25._20_4_ = auVar56._20_4_ + auVar55._20_4_;
    auVar25._24_4_ = auVar56._24_4_ + auVar55._24_4_;
    auVar25._28_4_ = auVar56._28_4_ + auVar55._28_4_;
    auVar57 = vpshufd_avx2(auVar24,0x39);
    auVar55 = vpshufb_avx2(auVar25,auVar44);
    auVar59 = vpshufb_avx2(auVar59,auVar43);
    auVar55 = auVar55 ^ auVar59;
    auVar26._0_4_ = auVar57._0_4_ + auVar55._0_4_;
    auVar26._4_4_ = auVar57._4_4_ + auVar55._4_4_;
    auVar26._8_4_ = auVar57._8_4_ + auVar55._8_4_;
    auVar26._12_4_ = auVar57._12_4_ + auVar55._12_4_;
    auVar26._16_4_ = auVar57._16_4_ + auVar55._16_4_;
    auVar26._20_4_ = auVar57._20_4_ + auVar55._20_4_;
    auVar26._24_4_ = auVar57._24_4_ + auVar55._24_4_;
    auVar26._28_4_ = auVar57._28_4_ + auVar55._28_4_;
    auVar59 = vpsrld_avx2(auVar26 ^ auVar56,0x14);
    auVar56 = vpslld_avx2(auVar26 ^ auVar56,0xc);
    auVar56 = vpor_avx2(auVar56,auVar59);
    auVar27._0_4_ = auVar56._0_4_ + auVar25._0_4_;
    auVar27._4_4_ = auVar56._4_4_ + auVar25._4_4_;
    auVar27._8_4_ = auVar56._8_4_ + auVar25._8_4_;
    auVar27._12_4_ = auVar56._12_4_ + auVar25._12_4_;
    auVar27._16_4_ = auVar56._16_4_ + auVar25._16_4_;
    auVar27._20_4_ = auVar56._20_4_ + auVar25._20_4_;
    auVar27._24_4_ = auVar56._24_4_ + auVar25._24_4_;
    auVar27._28_4_ = auVar56._28_4_ + auVar25._28_4_;
    auVar59 = vpshufb_avx2(auVar27,auVar45);
    auVar55 = vpshufb_avx2(auVar55,auVar45);
    auVar59 = auVar59 ^ auVar55;
    auVar28._0_4_ = auVar26._0_4_ + auVar59._0_4_;
    auVar28._4_4_ = auVar26._4_4_ + auVar59._4_4_;
    auVar28._8_4_ = auVar26._8_4_ + auVar59._8_4_;
    auVar28._12_4_ = auVar26._12_4_ + auVar59._12_4_;
    auVar28._16_4_ = auVar26._16_4_ + auVar59._16_4_;
    auVar28._20_4_ = auVar26._20_4_ + auVar59._20_4_;
    auVar28._24_4_ = auVar26._24_4_ + auVar59._24_4_;
    auVar28._28_4_ = auVar26._28_4_ + auVar59._28_4_;
    auVar55 = vpsrld_avx2(auVar28 ^ auVar56,0x19);
    auVar56 = vpslld_avx2(auVar28 ^ auVar56,7);
    auVar56 = vpor_avx2(auVar56,auVar55);
    auVar55 = vpshufd_avx2(auVar59,0x4e);
    auVar59 = vpshufd_avx2(auVar28,0x93);
    auVar1._0_4_ = auVar27._0_4_ + uVar39;
    auVar1._4_4_ = auVar27._4_4_ + uVar40;
    auVar1._8_4_ = auVar27._8_4_ + uVar41;
    auVar1._12_4_ = auVar27._12_4_ + uVar42;
    auVar29._16_4_ = auVar27._16_4_ + uVar39;
    auVar29._0_16_ = auVar1;
    auVar29._20_4_ = auVar27._20_4_ + uVar40;
    auVar29._24_4_ = auVar27._24_4_ + uVar41;
    auVar29._28_4_ = auVar27._28_4_ + uVar42;
    auVar2._0_4_ = auVar59._0_4_ + iVar35;
    auVar2._4_4_ = auVar59._4_4_ + iVar36;
    auVar2._8_4_ = auVar59._8_4_ + iVar37;
    auVar2._12_4_ = auVar59._12_4_ + iVar38;
    auVar30._16_4_ = auVar59._16_4_ + iVar35;
    auVar30._0_16_ = auVar2;
    auVar30._20_4_ = auVar59._20_4_ + iVar36;
    auVar30._24_4_ = auVar59._24_4_ + iVar37;
    auVar30._28_4_ = auVar59._28_4_ + iVar38;
    auVar3._0_4_ = auVar34._0_4_ + auVar55._0_4_;
    auVar3._4_4_ = auVar34._4_4_ + auVar55._4_4_;
    auVar3._8_4_ = auVar34._8_4_ + auVar55._8_4_;
    auVar3._12_4_ = auVar34._12_4_ + auVar55._12_4_;
    auVar31._16_4_ = auVar34._16_4_ + auVar55._16_4_;
    auVar31._0_16_ = auVar3;
    auVar31._20_4_ = auVar34._20_4_ + auVar55._20_4_;
    auVar31._24_4_ = auVar34._24_4_ + auVar55._24_4_;
    auVar31._28_4_ = auVar34._28_4_ + auVar55._28_4_;
    auVar1 = vpshufd_avx(auVar1,0x39);
    auVar34._0_4_ = auVar56._0_4_ + iVar48;
    auVar34._4_4_ = auVar56._4_4_ + iVar50;
    auVar34._8_4_ = auVar56._8_4_ + iVar51;
    auVar34._12_4_ = auVar56._12_4_ + iVar52;
    auVar34._16_4_ = auVar56._16_4_ + iVar48;
    auVar34._20_4_ = auVar56._20_4_ + iVar50;
    auVar34._24_4_ = auVar56._24_4_ + iVar51;
    auVar34._28_4_ = auVar56._28_4_ + iVar52;
    auVar56 = vperm2i128_avx2(ZEXT1632(auVar1),auVar34,0x20);
    *(undefined1 (*) [32])(param_1 + 0x80 + uVar47) = auVar56;
    auVar54._16_16_ = ZEXT116(0) * auVar30._16_16_ | ZEXT116(1) * auVar3;
    auVar54._0_16_ = ZEXT116(0) * auVar3 | ZEXT116(1) * auVar2;
    *(undefined1 (*) [32])(param_1 + 0xa0 + uVar47) = auVar54;
    auVar1 = vpshufd_avx(auVar29._16_16_,0x39);
    auVar56 = vpblendd_avx2(ZEXT1632(auVar1),auVar34,0xf0);
    *(undefined1 (*) [32])(param_1 + 0xc0 + uVar47) = auVar56;
    auVar56 = vperm2i128_avx2(auVar30,auVar31,0x31);
    *(undefined1 (*) [32])(param_1 + 0xe0 + uVar47) = auVar56;
    auVar53 = ZEXT1664(CONCAT412(iVar46 + auVar53._12_4_,
                                 CONCAT48(iVar46 + auVar53._8_4_,
                                          CONCAT44(iVar46 + auVar53._4_4_,iVar46 + auVar53._0_4_))))
    ;
    uVar47 = uVar47 + 0x80;
  } while (uVar47 < 0x101);
  return;
}


// ---- FUN_011cc5e0 @ 011cc5e0

int FUN_011cc5e0(int *param_1,long param_2,ulong param_3)

{
  ulong uVar1;
  ulong *puVar2;
  short sVar3;
  int iVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  ulong extraout_RDX;
  ulong extraout_RDX_00;
  byte bVar8;
  int *piVar9;
  int *piVar10;
  int *piVar11;
  long in_FS_OFFSET;
  bool bVar12;
  undefined8 local_290;
  undefined1 local_288 [512];
  undefined1 local_88 [32];
  undefined8 local_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  int *local_40;
  ulong *local_38;
  
  LOCK();
  iVar4 = param_1[0xce];
  bVar12 = iVar4 == 0;
  if (bVar12) {
    param_1[0xce] = 1;
    iVar4 = 0;
  }
  UNLOCK();
  local_68 = CONCAT71(local_68._1_7_,!bVar12);
  piVar11 = param_1 + 0xce;
  uVar6 = (ulong)!bVar12;
  uVar7 = param_3;
  piVar9 = param_1;
  if (!bVar12) {
    if (iVar4 == 2) {
      uVar7 = 2;
      uVar6 = 0x11cc66e;
      syscall();
      piVar9 = piVar11;
    }
    LOCK();
    iVar4 = *piVar11;
    *piVar11 = 2;
    UNLOCK();
    if (iVar4 != 0) {
      uVar7 = 2;
      do {
        uVar6 = 0x11cc692;
        syscall();
        LOCK();
        iVar4 = *piVar11;
        *piVar11 = 2;
        UNLOCK();
        piVar9 = piVar11;
      } while (iVar4 != 0);
    }
  }
  local_38 = (ulong *)(param_1 + 0x14);
  uVar1 = *(ulong *)(param_1 + 0x14);
  if (uVar1 == 0xffffffffffffffff) {
    LOCK();
    iVar4 = *piVar11;
    *piVar11 = 0;
    UNLOCK();
    if (iVar4 == 2) {
      uVar6 = 0x11cc6e1;
      syscall();
      lVar5 = *(long *)(in_FS_OFFSET + -0x40010);
      piVar9 = piVar11;
      if (lVar5 != 0) goto LAB_011cc6bd;
LAB_011cc6ef:
      bVar8 = 0;
    }
    else {
      lVar5 = *(long *)(in_FS_OFFSET + -0x40010);
      if (lVar5 == 0) goto LAB_011cc6ef;
LAB_011cc6bd:
      bVar8 = *(byte *)(lVar5 + 0x21c);
      *(undefined1 *)(lVar5 + 0x21c) = 1;
    }
    sVar3 = FUN_011cbce0(piVar9,local_88,0x20,uVar6);
    if (sVar3 == 0) {
      lVar5 = *(long *)(in_FS_OFFSET + -0x40010);
    }
    else {
      FUN_011cc950(param_1,local_88);
      lVar5 = *(long *)(in_FS_OFFSET + -0x40010);
    }
    if (lVar5 != 0) {
      *(byte *)(lVar5 + 0x21c) = bVar8 & 1;
    }
    FUN_011cce20(piVar11);
    local_290 = 0;
    FUN_011cc1c0(local_288,local_88);
    puVar2 = local_38;
    FUN_011f4580(local_38,&local_290,0x208);
    uVar1 = *puVar2;
    uVar7 = extraout_RDX;
  }
  if (uVar1 != 0x1e0) {
    uVar7 = 0x1e0 - uVar1;
    if (param_3 <= 0x1e0 - uVar1) {
      uVar7 = param_3;
    }
    local_40 = piVar11;
    FUN_011f4580(param_2,(long)param_1 + uVar1 + 0x78,uVar7);
    FUN_011f4160((long)param_1 + *local_38 + 0x78,0,uVar7);
    param_2 = param_2 + uVar7;
    param_3 = param_3 - uVar7;
    *local_38 = *local_38 + uVar7;
    uVar7 = extraout_RDX_00;
    piVar11 = local_40;
  }
  if (param_3 != 0) {
    piVar9 = param_1 + 0x1e;
    local_68 = *(undefined8 *)(param_1 + 0x16);
    uStack_60 = *(undefined8 *)(param_1 + 0x18);
    uStack_58 = *(undefined8 *)(param_1 + 0x1a);
    uStack_50 = *(undefined8 *)(param_1 + 0x1c);
    piVar10 = param_1 + 0x16;
    FUN_011cc1c0(piVar10,&local_68,uVar7);
    puVar2 = local_38;
    if (0x1df < param_3) {
      do {
        local_40 = piVar11;
        FUN_011f4580(param_2,piVar9,0x1e0);
        param_2 = param_2 + 0x1e0;
        param_3 = param_3 - 0x1e0;
        local_68 = *(undefined8 *)piVar10;
        uStack_60 = *(undefined8 *)(param_1 + 0x18);
        uStack_58 = *(undefined8 *)(param_1 + 0x1a);
        uStack_50 = *(undefined8 *)(param_1 + 0x1c);
        FUN_011cc1c0(piVar10,&local_68);
        *puVar2 = 0;
        piVar11 = local_40;
      } while (0x1df < param_3);
      if (param_3 == 0) goto LAB_011cc864;
    }
    FUN_011f4580(param_2,piVar9,param_3);
    FUN_011f4160(piVar9,0,param_3);
    *local_38 = param_3;
  }
LAB_011cc864:
  LOCK();
  iVar4 = *piVar11;
  *piVar11 = 0;
  UNLOCK();
  if (iVar4 == 2) {
    iVar4 = 0xca;
    syscall();
  }
  return iVar4;
}


// ---- FUN_011cc8c0 @ 011cc8c0

/* WARNING: Removing unreachable block (ram,0x011cc8f1) */
/* WARNING: Removing unreachable block (ram,0x011cc923) */
/* WARNING: Removing unreachable block (ram,0x011cc91d) */

long * FUN_011cc8c0(long *param_1)

{
  long local_18;
  ulong local_10;
  
  syscall();
  *param_1 = local_18 * 1000000000 + local_10;
  *(uint *)(param_1 + 1) =
       SUB164(SEXT816(1000000000) * SEXT816(local_18),8) + (int)((long)local_10 >> 0x3f) +
       (uint)CARRY8(local_18 * 1000000000,local_10);
  *(undefined4 *)((long)param_1 + 0xc) = 0;
  *(undefined2 *)(param_1 + 2) = 0;
  *(undefined8 *)((long)param_1 + 0x12) = 0;
  param_1[3] = 0;
  return param_1;
}


// ---- FUN_011cc950 @ 011cc950

void FUN_011cc950(undefined8 param_1,undefined1 (*param_2) [16],undefined8 param_3)

{
  ulong uVar1;
  long lVar2;
  undefined1 auVar3 [16];
  undefined8 local_28;
  undefined8 uStack_20;
  
  auVar3._0_12_ = ZEXT812(0);
  auVar3._12_4_ = 0;
  *param_2 = auVar3;
  *(undefined8 *)param_2[1] = 0;
  *(undefined8 *)(param_2[1] + 8) = param_1;
  syscall();
  *(undefined4 *)*param_2 = 0x27;
  if (PTR_FUN_011fcf88 != (undefined *)0x0) {
    uVar1 = (*(code *)PTR_FUN_011fcf88)(0,&local_28,param_3,0x11cc977);
    if ((uVar1 == 0) || (uVar1 == 0xffffffffffffffea)) goto LAB_011cc9a5;
  }
  uVar1 = 0xe4;
  syscall();
LAB_011cc9a5:
  lVar2 = 0;
  if (0xfffffffffffff000 < uVar1) {
    lVar2 = -uVar1;
  }
  if (lVar2 != 0) {
    return;
  }
  *(undefined8 *)(*param_2 + 4) = local_28;
  *(undefined8 *)(*param_2 + 0xc) = uStack_20;
  return;
}


// ---- FUN_011cc9e0 @ 011cc9e0

/* WARNING: Type propagation algorithm not settling */

undefined8 FUN_011cc9e0(undefined4 param_1,undefined8 param_2)

{
  uint *puVar1;
  byte bVar2;
  ushort uVar3;
  uint uVar4;
  uint uVar5;
  long *plVar6;
  undefined8 uVar7;
  ulong uVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  ulong *puVar13;
  long lVar14;
  ulong uVar15;
  long lVar16;
  int *piVar17;
  int *piVar18;
  long lVar19;
  long lVar20;
  long lVar21;
  int iVar22;
  long lVar23;
  long lVar24;
  ulong uVar25;
  undefined1 auVar26 [16];
  undefined1 auVar27 [16];
  
  if (DAT_01200008 == (long *)0x0) {
    PTR_FUN_011fcf88 = (undefined *)0x0;
    return 0xffffffffffffffda;
  }
  lVar11 = *DAT_01200008;
  plVar6 = DAT_01200008;
  while( true ) {
    if (lVar11 == 0) {
      PTR_FUN_011fcf88 = (undefined *)0x0;
      return 0xffffffffffffffda;
    }
    if (lVar11 == 0x21) break;
    lVar11 = plVar6[2];
    plVar6 = plVar6 + 2;
  }
  lVar11 = plVar6[1];
  if (lVar11 == 0) {
    PTR_FUN_011fcf88 = (undefined *)0x0;
    return 0xffffffffffffffda;
  }
  uVar3 = *(ushort *)(lVar11 + 0x38);
  if (uVar3 == 0) {
    PTR_FUN_011fcf88 = (undefined *)0x0;
    return 0xffffffffffffffda;
  }
  piVar17 = (int *)(*(long *)(lVar11 + 0x20) + lVar11);
  uVar8 = (ulong)*(ushort *)(lVar11 + 0x36);
  uVar25 = (ulong)(uVar3 & 3);
  if (uVar3 < 4) {
    lVar21 = -1;
    plVar6 = (long *)0x0;
  }
  else {
    uVar15 = (ulong)(uVar3 & 0xfffffffc);
    lVar21 = -1;
    plVar6 = (long *)0x0;
    do {
      piVar18 = piVar17;
      if (*piVar18 == 1) {
        lVar21 = (*(long *)(piVar18 + 2) + lVar11) - *(long *)(piVar18 + 4);
        iVar22 = *(int *)(uVar8 + (long)piVar18);
        if (iVar22 == 1) goto LAB_011ccb29;
LAB_011ccacf:
        if (iVar22 == 2) {
          plVar6 = (long *)(*(long *)((long)piVar18 + uVar8 + 8) + lVar11);
        }
        lVar10 = (long)piVar18 + uVar8 * 2;
        iVar22 = *(int *)((long)piVar18 + uVar8 * 2);
        if (iVar22 != 1) goto LAB_011ccaea;
LAB_011ccb42:
        lVar21 = (*(long *)(lVar10 + 8) + lVar11) - *(long *)(lVar10 + 0x10);
        lVar12 = uVar8 + lVar10;
        iVar22 = *(int *)(uVar8 + lVar10);
        if (iVar22 != 1) goto LAB_011ccb5f;
LAB_011cca90:
        lVar21 = (*(long *)(lVar12 + 8) + lVar11) - *(long *)(lVar12 + 0x10);
      }
      else {
        if (*piVar18 == 2) {
          plVar6 = (long *)(*(long *)(piVar18 + 2) + lVar11);
        }
        iVar22 = *(int *)(uVar8 + (long)piVar18);
        if (iVar22 != 1) goto LAB_011ccacf;
LAB_011ccb29:
        lVar21 = (*(long *)((long)piVar18 + uVar8 + 8) + lVar11) -
                 *(long *)((long)piVar18 + uVar8 + 0x10);
        lVar10 = (long)piVar18 + uVar8 * 2;
        iVar22 = *(int *)((long)piVar18 + uVar8 * 2);
        if (iVar22 == 1) goto LAB_011ccb42;
LAB_011ccaea:
        if (iVar22 == 2) {
          plVar6 = (long *)(*(long *)(lVar10 + 8) + lVar11);
        }
        lVar12 = uVar8 + lVar10;
        iVar22 = *(int *)(uVar8 + lVar10);
        if (iVar22 == 1) goto LAB_011cca90;
LAB_011ccb5f:
        if (iVar22 == 2) {
          plVar6 = (long *)(*(long *)(lVar12 + 8) + lVar11);
        }
      }
      uVar15 = uVar15 - 4;
      piVar17 = (int *)(lVar12 + uVar8);
    } while (uVar15 != 0);
    piVar17 = piVar18 + uVar8;
  }
  for (; uVar25 != 0; uVar25 = uVar25 - 1) {
    if (*piVar17 == 1) {
      lVar21 = (*(long *)(piVar17 + 2) + lVar11) - *(long *)(piVar17 + 4);
    }
    else if (*piVar17 == 2) {
      plVar6 = (long *)(*(long *)(piVar17 + 2) + lVar11);
    }
    piVar17 = (int *)((long)piVar17 + uVar8);
  }
  if (((plVar6 != (long *)0x0) && (lVar21 != -1)) && (lVar11 = *plVar6, lVar11 != 0)) {
    lVar16 = 0;
    lVar12 = 0;
    lVar10 = 0;
    lVar20 = 0;
    lVar24 = 0;
    do {
      lVar14 = plVar6[1] + lVar21;
      lVar9 = lVar10;
      lVar19 = lVar20;
      lVar23 = lVar24;
      if (lVar11 < 6) {
        lVar9 = lVar14;
        if ((lVar11 != 4) && (lVar9 = lVar10, lVar11 == 5)) {
          lVar12 = lVar14;
        }
      }
      else {
        lVar23 = lVar14;
        if (((lVar11 != 6) && (lVar19 = lVar14, lVar23 = lVar24, lVar11 != 0x6ffffff0)) &&
           (lVar19 = lVar20, lVar11 == 0x6ffffffc)) {
          lVar16 = lVar14;
        }
      }
      lVar11 = plVar6[2];
      lVar10 = lVar9;
      lVar20 = lVar19;
      lVar24 = lVar23;
      plVar6 = plVar6 + 2;
    } while (lVar11 != 0);
    if ((lVar9 != 0 && (lVar23 != 0 && lVar12 != 0)) &&
       (uVar4 = *(uint *)(lVar9 + 4), (ulong)uVar4 != 0)) {
      uVar25 = 0;
      do {
        bVar2 = *(byte *)(lVar23 + 4 + uVar25 * 0x18);
        if ((((0x27U >> (bVar2 & 0xf) & 1) != 0) && ((0x406U >> (bVar2 >> 4) & 1) != 0)) &&
           (puVar1 = (uint *)(lVar23 + uVar25 * 0x18), *(short *)((long)puVar1 + 6) != 0)) {
          uVar5 = *puVar1;
          uVar7 = FUN_011f4140((ulong)uVar5 + lVar12,param_2);
          uVar8 = FUN_011c9680("__vdso_clock_gettime",0x14,(ulong)uVar5 + lVar12,uVar7);
          if ((uVar8 & 1) != 0) {
            if (lVar19 == 0 || lVar16 == 0) {
LAB_011ccddc:
              PTR_FUN_011fcf88 = (undefined *)(lVar21 + *(long *)(puVar1 + 2));
              if ((code *)PTR_FUN_011fcf88 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x011ccdf7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
                uVar7 = (*(code *)PTR_FUN_011fcf88)(param_1);
                return uVar7;
              }
              return 0xffffffffffffffda;
            }
            bVar2 = *(byte *)(lVar16 + 2);
            lVar11 = lVar16;
            while (((bVar2 & 1) != 0 ||
                   (*(ushort *)(lVar11 + 4) != (*(ushort *)(lVar19 + uVar25 * 2) & 0x7fff)))) {
              if ((ulong)*(uint *)(lVar11 + 0x10) == 0) goto LAB_011cccc0;
              lVar11 = lVar11 + (ulong)*(uint *)(lVar11 + 0x10);
              bVar2 = *(byte *)(lVar11 + 2);
            }
            puVar13 = (ulong *)((ulong)*(uint *)((ulong)*(uint *)(lVar11 + 0xc) + lVar11) + lVar12);
            lVar11 = FUN_011f4140(puVar13,param_2);
            if ((lVar11 == 9) &&
               ((puVar13 == (ulong *)"LINUX_2.6" ||
                (auVar26._8_8_ = 0, auVar26._0_8_ = *(ulong *)((long)puVar13 + 1), auVar27._8_8_ = 0
                , auVar27._0_8_ = *puVar13, auVar26 = vpunpcklqdq_avx(auVar27,auVar26),
                auVar26 == s_LINUX_2_INUX_2_6_010008b0._0_16_)))) goto LAB_011ccddc;
          }
        }
LAB_011cccc0:
        uVar25 = uVar25 + 1;
      } while (uVar25 != uVar4);
    }
  }
  PTR_FUN_011fcf88 = (undefined *)0x0;
  return 0xffffffffffffffda;
}


// ---- FUN_011cce20 @ 011cce20

void FUN_011cce20(int *param_1)

{
  int iVar1;
  bool bVar2;
  
  LOCK();
  iVar1 = *param_1;
  bVar2 = iVar1 == 0;
  if (bVar2) {
    *param_1 = 1;
    iVar1 = 0;
  }
  UNLOCK();
  if (!bVar2) {
    if (iVar1 == 2) {
      syscall();
    }
    LOCK();
    iVar1 = *param_1;
    *param_1 = 2;
    UNLOCK();
    while (iVar1 != 0) {
      syscall();
      LOCK();
      iVar1 = *param_1;
      *param_1 = 2;
      UNLOCK();
    }
  }
  return;
}


// ---- FUN_011cce90 @ 011cce90

long * FUN_011cce90(long *param_1,undefined8 param_2,uint param_3)

{
  ulong uVar1;
  long lVar2;
  int iVar3;
  long lVar4;
  long local_28;
  ulong local_20;
  
  if (PTR_FUN_011fcf88 != (undefined *)0x0) {
    uVar1 = (*(code *)PTR_FUN_011fcf88)
                      (*(undefined4 *)(&DAT_01001440 + (ulong)((param_3 ^ 4) & 7) * 4),&local_28);
    if ((uVar1 == 0) || (uVar1 == 0xffffffffffffffea)) goto LAB_011ccee3;
  }
  syscall();
  uVar1 = 0xe4;
LAB_011ccee3:
  lVar2 = 0;
  lVar4 = -uVar1;
  if (uVar1 < 0xfffffffffffff001) {
    lVar4 = lVar2;
  }
  iVar3 = 0;
  if (lVar4 == 0) {
    lVar2 = local_28 * 1000000000 + local_20;
    iVar3 = SUB164(SEXT816(1000000000) * SEXT816(local_28),8) + (int)((long)local_20 >> 0x3f) +
            (uint)CARRY8(local_28 * 1000000000,local_20);
  }
  *param_1 = lVar2;
  *(int *)(param_1 + 1) = iVar3;
  *(undefined4 *)((long)param_1 + 0xc) = 0;
  return param_1;
}


// ---- FUN_011ccf40 @ 011ccf40

undefined8 * FUN_011ccf40(undefined8 *param_1,long param_2)

{
  FUN_011cd090(param_2);
  *(undefined4 *)(param_1 + 1) = *(undefined4 *)(param_2 + 0x318);
  *param_1 = *(undefined8 *)(param_2 + 0x310);
  return param_1;
}


// ---- FUN_011ccf80 @ 011ccf80

undefined1  [16] FUN_011ccf80(undefined8 param_1,long param_2)

{
  ulong uVar1;
  undefined1 auVar2 [16];
  
  syscall();
  syscall();
  uVar1 = 0x3d;
  if (*(char *)(param_2 + 0x128) != '\0') {
    uVar1 = 3;
    syscall();
    *(undefined8 *)(param_2 + 0x120) = 0;
    *(undefined4 *)(param_2 + 0x128) = 0;
  }
  if (*(char *)(param_2 + 0x134) != '\0') {
    uVar1 = 3;
    syscall();
    *(undefined8 *)(param_2 + 300) = 0;
    *(undefined4 *)(param_2 + 0x134) = 0;
  }
  if (*(char *)(param_2 + 0x140) != '\0') {
    uVar1 = 3;
    syscall();
    *(undefined8 *)(param_2 + 0x138) = 0;
    *(undefined4 *)(param_2 + 0x140) = 0;
  }
  *(undefined8 *)(param_2 + 0x118) = 0;
  auVar2._8_8_ = 0;
  auVar2._0_8_ = uVar1;
  return auVar2;
}


// ---- FUN_011cd090 @ 011cd090

/* WARNING: Removing unreachable block (ram,0x011cd3aa) */

int FUN_011cd090(long param_1)

{
  int *piVar1;
  char cVar2;
  long lVar3;
  long lVar4;
  char *pcVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  long lVar9;
  ulong uVar10;
  char *pcVar11;
  short sVar12;
  long lVar13;
  byte bVar14;
  long lVar15;
  long lVar16;
  long lVar17;
  byte *pbVar18;
  char *pcVar19;
  bool bVar20;
  uint local_3c;
  uint local_38;
  
  LOCK();
  iVar6 = *(int *)(param_1 + 0x338);
  bVar20 = iVar6 == 0;
  if (bVar20) {
    *(int *)(param_1 + 0x338) = 1;
    iVar6 = 0;
  }
  UNLOCK();
  piVar1 = (int *)(param_1 + 0x338);
  if (!bVar20) {
    if (iVar6 == 2) {
      syscall();
    }
    LOCK();
    iVar6 = *piVar1;
    *piVar1 = 2;
    UNLOCK();
    while (iVar6 != 0) {
      syscall();
      LOCK();
      iVar6 = *piVar1;
      *piVar1 = 2;
      UNLOCK();
    }
  }
  if (*(char *)(param_1 + 0x35b) == '\0') {
    lVar3 = *(long *)(param_1 + 0x2c8);
    if (lVar3 != 0) {
      lVar4 = *(long *)(param_1 + 0x2c0);
      lVar15 = 0;
LAB_011cd14d:
      pcVar5 = *(char **)(lVar4 + lVar15 * 8);
      pbVar18 = (byte *)(pcVar5 + 2);
      lVar17 = 0;
      cVar2 = *pcVar5;
      pcVar19 = pcVar5;
      while ((pcVar19 = pcVar19 + 1, cVar2 != '\0' && (cVar2 != '='))) {
        lVar17 = lVar17 + 1;
        pbVar18 = pbVar18 + 1;
        cVar2 = pcVar5[lVar17];
      }
      lVar9 = FUN_011f4140(pcVar5 + lVar17);
      uVar10 = FUN_011c9680(pcVar5,lVar17,"NO_COLOR",8);
      if ((uVar10 & 1) == 0) {
        uVar10 = FUN_011c9680(pcVar5,lVar17,"CLICOLOR_FORCE",0xe);
        if ((uVar10 & 1) != 0) {
          *(undefined1 *)(param_1 + 799) = 1;
          goto LAB_011cd140;
        }
        lVar16 = lVar9 + -1;
        pcVar11 = pcVar5 + lVar17 + 1;
        uVar10 = FUN_011c9680(pcVar5,lVar17,"ZIG_PROGRESS",0xc);
        if ((uVar10 & 1) == 0) {
          uVar10 = FUN_011c9680(pcVar5,lVar17,"PATH",4);
          if ((uVar10 & 1) != 0) {
            *(char **)(param_1 + 0x2d0) = pcVar11;
            *(long *)(param_1 + 0x2d8) = lVar16;
          }
          uVar10 = FUN_011c9680(pcVar5,lVar17,"DEBUGINFOD_CACHE_PATH",0x15);
          if ((uVar10 & 1) != 0) {
            *(char **)(param_1 + 0x2e0) = pcVar11;
            *(long *)(param_1 + 0x2e8) = lVar16;
          }
          uVar10 = FUN_011c9680(pcVar5,lVar17,"XDG_CACHE_HOME",0xe);
          if ((uVar10 & 1) != 0) {
            *(char **)(param_1 + 0x2f0) = pcVar11;
            *(long *)(param_1 + 0x2f8) = lVar16;
          }
          uVar10 = FUN_011c9680(pcVar5,lVar17,"HOME",4);
          if ((uVar10 & 1) != 0) {
            *(char **)(param_1 + 0x300) = pcVar11;
            *(long *)(param_1 + 0x308) = lVar16;
          }
          goto LAB_011cd140;
        }
        *(undefined2 *)(param_1 + 0x318) = 0;
        if (lVar9 != 1) {
          cVar2 = *pcVar11;
          if (cVar2 == '-') {
            lVar13 = 0;
            uVar8 = 0;
            sVar12 = 0x6f;
            lVar9 = lVar9 + -2;
            if (lVar9 == 0) goto LAB_011cd600;
            local_3c = 0;
            if ((pcVar5[lVar17 + 2] != '_') && (pcVar5[lVar17 + lVar16] != '_')) {
              do {
                bVar14 = *pbVar18;
                if (bVar14 != 0x5f) {
                  if (9 < (byte)(bVar14 - 0x30)) goto joined_r0x011cd5cf;
                  if (local_3c == 0) {
                    if (0x30 < bVar14) goto LAB_011cd600;
                    local_3c = 0;
                  }
                  else {
                    uVar10 = (ulong)local_3c * 10;
                    if (((uVar10 >> 0x1f & 1) != 0 || (int)(uVar10 >> 0x20) != 0) ||
                       (uVar7 = ((uint)uVar10 & 0x7fffffff) - (uint)(byte)(bVar14 - 0x30),
                       local_3c = uVar7 & 0x7fffffff, (int)uVar7 < 0)) goto LAB_011cd5b5;
                  }
                }
                pbVar18 = pbVar18 + 1;
                lVar9 = lVar9 + -1;
                local_38 = local_3c;
              } while (lVar9 != 0);
LAB_011cd5f5:
              sVar12 = 0;
              uVar8 = local_38;
            }
          }
          else if (cVar2 == '+') {
            sVar12 = 0x6f;
            if (lVar9 == 2) goto LAB_011cd600;
            local_38 = 0;
            uVar8 = 0;
            if ((pcVar5[lVar17 + 2] != '_') && (pcVar5[lVar17 + lVar16] != '_')) {
              lVar13 = 0;
              do {
                if (pbVar18[lVar13] != 0x5f) {
                  bVar14 = pbVar18[lVar13] - 0x30;
                  if (9 < bVar14) goto LAB_011cd5b9;
                  if (local_38 == 0) {
                    uVar8 = 0;
                  }
                  else {
                    uVar10 = (ulong)local_38 * 10;
                    uVar8 = (uint)uVar10 & 0x7fffffff;
                    if ((uVar10 >> 0x1f & 1) != 0 || (int)(uVar10 >> 0x20) != 0) goto LAB_011cd5b5;
                  }
                  uVar8 = uVar8 + bVar14;
                  local_38 = uVar8 & 0x7fffffff;
                  if ((int)uVar8 < 0) goto LAB_011cd5b5;
                }
                lVar13 = lVar13 + 1;
              } while (lVar9 + -2 != lVar13);
              goto LAB_011cd5f5;
            }
          }
          else {
            local_38 = 0;
            sVar12 = 0x6f;
            uVar8 = 0;
            if ((cVar2 != '_') && (pcVar5[lVar17 + lVar16] != '_')) {
              do {
                if (*pcVar19 != '_') {
                  bVar14 = *pcVar19 - 0x30;
                  uVar8 = (uint)bVar14;
                  if (bVar14 < 10) {
                    if (local_38 == 0) {
                      uVar7 = 0;
LAB_011cd3b1:
                      local_38 = uVar7 + bVar14 & 0x7fffffff;
                      if (-1 < (int)(uVar7 + bVar14)) goto LAB_011cd3df;
                    }
                    else {
                      uVar10 = (ulong)local_38 * 10;
                      uVar7 = (uint)uVar10 & 0x7fffffff;
                      if ((uVar10 >> 0x1f & 1) == 0 && (int)(uVar10 >> 0x20) == 0)
                      goto LAB_011cd3b1;
                    }
                    sVar12 = 0x6a;
                  }
                  goto joined_r0x011cd5cf;
                }
LAB_011cd3df:
                pcVar19 = pcVar19 + 1;
                lVar16 = lVar16 + -1;
              } while (lVar16 != 0);
              sVar12 = 0;
              uVar8 = local_38;
            }
          }
          goto joined_r0x011cd5cf;
        }
        goto LAB_011cd600;
      }
      *(undefined1 *)(param_1 + 0x31e) = 1;
      goto LAB_011cd140;
    }
LAB_011cd63e:
    *(undefined1 *)(param_1 + 0x35b) = 1;
    LOCK();
    iVar6 = *(int *)(param_1 + 0x338);
    *(int *)(param_1 + 0x338) = 0;
    UNLOCK();
    if (iVar6 == 2) {
      iVar6 = 0xca;
      syscall();
    }
  }
  else {
    LOCK();
    iVar6 = *piVar1;
    *piVar1 = 0;
    UNLOCK();
    if (iVar6 == 2) {
      iVar6 = 0xca;
      syscall();
    }
  }
  return iVar6;
LAB_011cd5b5:
  sVar12 = 0x6a;
LAB_011cd5b9:
  uVar8 = (uint)lVar13;
joined_r0x011cd5cf:
  if (sVar12 == 0) {
    *(uint *)(param_1 + 0x310) = uVar8 & 0x7fffffff;
    *(undefined1 *)(param_1 + 0x314) = 1;
  }
  else {
LAB_011cd600:
    *(undefined4 *)(param_1 + 0x318) = 0x19;
    *(undefined8 *)(param_1 + 0x310) = 0;
  }
LAB_011cd140:
  lVar15 = lVar15 + 1;
  if (lVar15 == lVar3) goto LAB_011cd63e;
  goto LAB_011cd14d;
}


// ---- FUN_011cd6d0 @ 011cd6d0

/* WARNING: Removing unreachable block (ram,0x011cd917) */
/* WARNING: Removing unreachable block (ram,0x011cd9e8) */
/* WARNING: Removing unreachable block (ram,0x011cd9fc) */
/* WARNING: Removing unreachable block (ram,0x011cd803) */
/* WARNING: Removing unreachable block (ram,0x011cd810) */
/* WARNING: Removing unreachable block (ram,0x011cd817) */
/* WARNING: Removing unreachable block (ram,0x011cd81f) */
/* WARNING: Removing unreachable block (ram,0x011cd827) */
/* WARNING: Removing unreachable block (ram,0x011cd831) */
/* WARNING: Removing unreachable block (ram,0x011cd855) */
/* WARNING: Removing unreachable block (ram,0x011cd85f) */
/* WARNING: Removing unreachable block (ram,0x011cd883) */
/* WARNING: Removing unreachable block (ram,0x011cd88d) */
/* WARNING: Removing unreachable block (ram,0x011cda01) */
/* WARNING: Removing unreachable block (ram,0x011cda07) */
/* WARNING: Removing unreachable block (ram,0x011cda11) */
/* WARNING: Removing unreachable block (ram,0x011cda35) */
/* WARNING: Removing unreachable block (ram,0x011cda3f) */
/* WARNING: Removing unreachable block (ram,0x011cda63) */
/* WARNING: Removing unreachable block (ram,0x011cda6d) */
/* WARNING: Removing unreachable block (ram,0x011cd920) */
/* WARNING: Removing unreachable block (ram,0x011cd92a) */
/* WARNING: Removing unreachable block (ram,0x011cd94e) */
/* WARNING: Removing unreachable block (ram,0x011cd958) */
/* WARNING: Removing unreachable block (ram,0x011cd97c) */
/* WARNING: Removing unreachable block (ram,0x011cd98a) */
/* WARNING: Removing unreachable block (ram,0x011cda7b) */
/* WARNING: Removing unreachable block (ram,0x011cda91) */

uint * FUN_011cd6d0(uint *param_1,undefined8 param_2,long param_3)

{
  byte bVar1;
  undefined2 uVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  long lVar6;
  long in_FS_OFFSET;
  bool bVar7;
  undefined1 local_138 [272];
  uint local_28;
  undefined1 local_24;
  
  bVar1 = *(byte *)(param_3 + 0x144);
  lVar6 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar6 == 0) || ((*(byte *)(lVar6 + 0x21c) & 1) != 0)) {
LAB_011cd7bc:
    lVar6 = 0;
  }
  else {
    uVar3 = *(ulong *)(lVar6 + 8);
    do {
      uVar5 = uVar3 | 3;
      LOCK();
      uVar4 = *(ulong *)(lVar6 + 8);
      bVar7 = uVar3 == uVar4;
      if (bVar7) {
        *(ulong *)(lVar6 + 8) = uVar5;
        uVar4 = uVar3;
      }
      UNLOCK();
      uVar3 = uVar4;
    } while (!bVar7);
    if ((uVar4 & 7) != 0) {
      if (((uint)uVar4 & 7) == 6) {
        if (*(char *)(param_3 + 0x128) != '\0') {
          uVar5 = 0x11cd757;
          syscall();
          *(undefined8 *)(param_3 + 0x120) = 0;
          *(undefined4 *)(param_3 + 0x128) = 0;
        }
        local_24 = (undefined1)uVar5;
        if (*(char *)(param_3 + 0x134) != '\0') {
          local_24 = 0x85;
          syscall();
          *(undefined8 *)(param_3 + 300) = 0;
          *(undefined4 *)(param_3 + 0x134) = 0;
        }
        if (*(char *)(param_3 + 0x140) != '\0') {
          syscall();
          local_24 = 0xb7;
          *(undefined8 *)(param_3 + 0x138) = 0;
          *(undefined4 *)(param_3 + 0x140) = 0;
        }
        local_28 = (uint)param_3;
        *(undefined8 *)(param_3 + 0x118) = 0;
        uVar2 = 0x11;
        goto LAB_011cdb6d;
      }
      goto LAB_011cd7bc;
    }
  }
  if (lVar6 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar6 + 8) = *(ulong *)(lVar6 + 8) ^ 3;
    UNLOCK();
  }
  if ((bVar1 & 1) != 0) {
    FUN_011f4580(param_3,local_138,0x110);
    *(undefined1 *)(param_3 + 0x110) = 1;
  }
  if ((local_28 & 0x7f) == 0) {
    local_24 = 0;
    local_28 = local_28 >> 8 & 0xff;
  }
  else if ((local_28 & 0xffff) - 1 < 0xff) {
    local_24 = 1;
    local_28 = local_28 & 0x7f;
  }
  else if (((local_28 << 0x10 | local_28 & 0xffff) >> 8 & 0xffff) < 0x7f01) {
    local_24 = 3;
  }
  else {
    local_24 = 2;
    local_28 = local_28 >> 8 & 0xff;
  }
  if (*(char *)(param_3 + 0x128) != '\0') {
    syscall();
    *(undefined8 *)(param_3 + 0x120) = 0;
    *(undefined4 *)(param_3 + 0x128) = 0;
  }
  if (*(char *)(param_3 + 0x134) != '\0') {
    syscall();
    *(undefined8 *)(param_3 + 300) = 0;
    *(undefined4 *)(param_3 + 0x134) = 0;
  }
  if (*(char *)(param_3 + 0x140) != '\0') {
    syscall();
    *(undefined8 *)(param_3 + 0x138) = 0;
    *(undefined4 *)(param_3 + 0x140) = 0;
  }
  *(undefined8 *)(param_3 + 0x118) = 0;
  uVar2 = 0;
LAB_011cdb6d:
  *param_1 = local_28;
  *(undefined1 *)(param_1 + 1) = local_24;
  *(undefined2 *)(param_1 + 2) = uVar2;
  return param_1;
}


// ---- FUN_011cdb90 @ 011cdb90

/* WARNING: Removing unreachable block (ram,0x011ce7f3) */
/* WARNING: Removing unreachable block (ram,0x011cdd8b) */
/* WARNING: Removing unreachable block (ram,0x011cdcb7) */
/* WARNING: Removing unreachable block (ram,0x011cde8f) */
/* WARNING: Removing unreachable block (ram,0x011cdfa9) */
/* WARNING: Removing unreachable block (ram,0x011ce949) */
/* WARNING: Removing unreachable block (ram,0x011cdcc0) */
/* WARNING: Removing unreachable block (ram,0x011cdcc5) */
/* WARNING: Removing unreachable block (ram,0x011cdcd2) */
/* WARNING: Removing unreachable block (ram,0x011ce818) */
/* WARNING: Removing unreachable block (ram,0x011ce800) */
/* WARNING: Removing unreachable block (ram,0x011ce805) */
/* WARNING: Removing unreachable block (ram,0x011ce812) */
/* WARNING: Removing unreachable block (ram,0x011ce820) */
/* WARNING: Removing unreachable block (ram,0x011ce848) */
/* WARNING: Removing unreachable block (ram,0x011ce852) */
/* WARNING: Removing unreachable block (ram,0x011ce864) */
/* WARNING: Removing unreachable block (ram,0x011ce86e) */
/* WARNING: Removing unreachable block (ram,0x011ce873) */
/* WARNING: Removing unreachable block (ram,0x011ce88d) */
/* WARNING: Removing unreachable block (ram,0x011ce894) */
/* WARNING: Removing unreachable block (ram,0x011ce898) */
/* WARNING: Removing unreachable block (ram,0x011ce8a2) */
/* WARNING: Removing unreachable block (ram,0x011ce8a8) */
/* WARNING: Removing unreachable block (ram,0x011ce8bc) */
/* WARNING: Removing unreachable block (ram,0x011ce8c3) */
/* WARNING: Removing unreachable block (ram,0x011ce8c7) */
/* WARNING: Removing unreachable block (ram,0x011ce8d1) */
/* WARNING: Removing unreachable block (ram,0x011ce8db) */
/* WARNING: Removing unreachable block (ram,0x011ce8eb) */
/* WARNING: Removing unreachable block (ram,0x011ce8f2) */
/* WARNING: Removing unreachable block (ram,0x011ce8fa) */
/* WARNING: Removing unreachable block (ram,0x011ce12c) */
/* WARNING: Removing unreachable block (ram,0x011ce130) */
/* WARNING: Removing unreachable block (ram,0x011ce137) */
/* WARNING: Removing unreachable block (ram,0x011ce13f) */
/* WARNING: Removing unreachable block (ram,0x011ce147) */
/* WARNING: Removing unreachable block (ram,0x011cdfb6) */
/* WARNING: Removing unreachable block (ram,0x011cdfc2) */
/* WARNING: Removing unreachable block (ram,0x011cdfcf) */
/* WARNING: Removing unreachable block (ram,0x011ce150) */
/* WARNING: Removing unreachable block (ram,0x011ce154) */
/* WARNING: Removing unreachable block (ram,0x011ce15d) */
/* WARNING: Removing unreachable block (ram,0x011ce177) */
/* WARNING: Removing unreachable block (ram,0x011ce17e) */
/* WARNING: Removing unreachable block (ram,0x011ce182) */
/* WARNING: Removing unreachable block (ram,0x011ce18c) */
/* WARNING: Removing unreachable block (ram,0x011ce192) */
/* WARNING: Removing unreachable block (ram,0x011ce19e) */
/* WARNING: Removing unreachable block (ram,0x011ce1a5) */
/* WARNING: Removing unreachable block (ram,0x011ce1a9) */
/* WARNING: Removing unreachable block (ram,0x011ce1b3) */
/* WARNING: Removing unreachable block (ram,0x011ce1bd) */
/* WARNING: Removing unreachable block (ram,0x011ce1d1) */
/* WARNING: Removing unreachable block (ram,0x011ce1d8) */
/* WARNING: Removing unreachable block (ram,0x011ce1e0) */
/* WARNING: Removing unreachable block (ram,0x011cddbc) */
/* WARNING: Removing unreachable block (ram,0x011cdd94) */
/* WARNING: Removing unreachable block (ram,0x011cdd99) */
/* WARNING: Removing unreachable block (ram,0x011cddad) */
/* WARNING: Removing unreachable block (ram,0x011cddb1) */
/* WARNING: Removing unreachable block (ram,0x011cddb7) */
/* WARNING: Removing unreachable block (ram,0x011cddd5) */
/* WARNING: Removing unreachable block (ram,0x011cdde1) */
/* WARNING: Removing unreachable block (ram,0x011cdde8) */
/* WARNING: Removing unreachable block (ram,0x011cddf0) */
/* WARNING: Removing unreachable block (ram,0x011cdfef) */
/* WARNING: Removing unreachable block (ram,0x011cde9c) */
/* WARNING: Removing unreachable block (ram,0x011cdea8) */
/* WARNING: Removing unreachable block (ram,0x011cdeb4) */
/* WARNING: Removing unreachable block (ram,0x011cdeb8) */
/* WARNING: Removing unreachable block (ram,0x011cdffc) */
/* WARNING: Removing unreachable block (ram,0x011ce008) */
/* WARNING: Removing unreachable block (ram,0x011ce00f) */
/* WARNING: Removing unreachable block (ram,0x011ce013) */
/* WARNING: Removing unreachable block (ram,0x011cdec2) */
/* WARNING: Removing unreachable block (ram,0x011ce01d) */
/* WARNING: Removing unreachable block (ram,0x011ce027) */
/* WARNING: Removing unreachable block (ram,0x011ce03b) */
/* WARNING: Removing unreachable block (ram,0x011ce042) */
/* WARNING: Removing unreachable block (ram,0x011ce04a) */
/* WARNING: Removing unreachable block (ram,0x011cdcdb) */
/* WARNING: Removing unreachable block (ram,0x011cefe7) */
/* WARNING: Removing unreachable block (ram,0x011cefed) */
/* WARNING: Removing unreachable block (ram,0x011ceff7) */
/* WARNING: Removing unreachable block (ram,0x011ceffc) */
/* WARNING: Removing unreachable block (ram,0x011cf00a) */
/* WARNING: Removing unreachable block (ram,0x011cf030) */
/* WARNING: Removing unreachable block (ram,0x011cf032) */
/* WARNING: Removing unreachable block (ram,0x011cf054) */
/* WARNING: Removing unreachable block (ram,0x011cf059) */
/* WARNING: Removing unreachable block (ram,0x011cf05c) */
/* WARNING: Removing unreachable block (ram,0x011cf07e) */
/* WARNING: Removing unreachable block (ram,0x011cf087) */
/* WARNING: Removing unreachable block (ram,0x011cf091) */
/* WARNING: Removing unreachable block (ram,0x011cf0b1) */
/* WARNING: Removing unreachable block (ram,0x011cf0bb) */
/* WARNING: Removing unreachable block (ram,0x011cf0c0) */
/* WARNING: Removing unreachable block (ram,0x011cf0da) */
/* WARNING: Removing unreachable block (ram,0x011cf0e1) */
/* WARNING: Removing unreachable block (ram,0x011cf0e5) */
/* WARNING: Removing unreachable block (ram,0x011cf0ef) */
/* WARNING: Removing unreachable block (ram,0x011cf0f5) */
/* WARNING: Removing unreachable block (ram,0x011cf105) */
/* WARNING: Removing unreachable block (ram,0x011cf10c) */
/* WARNING: Removing unreachable block (ram,0x011cf110) */
/* WARNING: Removing unreachable block (ram,0x011cf11a) */
/* WARNING: Removing unreachable block (ram,0x011cf128) */
/* WARNING: Removing unreachable block (ram,0x011cf134) */
/* WARNING: Removing unreachable block (ram,0x011cf13b) */
/* WARNING: Removing unreachable block (ram,0x011cf143) */

long FUN_011cdb90(long param_1,long param_2,long *param_3)

{
  undefined8 *puVar1;
  int *piVar2;
  undefined1 uVar3;
  byte bVar4;
  ulong *puVar5;
  ulong *puVar6;
  undefined8 uVar7;
  ulong *puVar8;
  ulong *puVar9;
  undefined8 uVar10;
  short sVar11;
  long lVar12;
  ulong uVar13;
  long lVar14;
  int iVar15;
  long lVar16;
  int iVar17;
  long *plVar18;
  ulong uVar19;
  long in_FS_OFFSET;
  bool bVar20;
  undefined1 auVar21 [16];
  undefined8 unaff_retaddr;
  undefined8 local_288;
  long lStack_280;
  ulong *puStack_278;
  ulong *puStack_270;
  undefined8 local_268;
  long lStack_260;
  ulong *puStack_258;
  ulong *puStack_250;
  undefined8 local_248;
  long lStack_240;
  ulong *puStack_238;
  ulong *puStack_230;
  undefined8 local_228;
  undefined8 uStack_220;
  short local_218;
  undefined8 local_210;
  undefined8 uStack_208;
  short local_200;
  undefined8 local_1f8;
  undefined8 uStack_1f0;
  undefined8 local_1e8;
  undefined8 uStack_1e0;
  undefined8 *local_1d0;
  undefined **local_1c8;
  long local_1c0;
  ulong local_1b8;
  ulong local_1b0;
  long local_1a8;
  ulong local_1a0;
  long local_198;
  int local_18c;
  int local_188;
  int local_184;
  int local_180;
  int local_17c;
  int local_178;
  undefined4 local_174;
  undefined4 local_170;
  undefined4 local_16c;
  int *local_168;
  int *local_160;
  undefined *local_158;
  int *local_150;
  int *local_148;
  long lStack_140;
  undefined1 local_138 [24];
  ulong local_120;
  byte local_118;
  int *local_110;
  int *local_108;
  undefined8 local_100;
  undefined8 local_f8;
  long lStack_f0;
  ulong *puStack_e8;
  ulong *puStack_e0;
  ulong local_d0;
  int *local_c8;
  long local_a8;
  ulong local_a0;
  int *local_98;
  int *local_90;
  int *local_88;
  int *local_80;
  byte local_78;
  undefined1 local_77;
  undefined1 local_76;
  undefined1 local_75;
  byte local_74;
  byte local_73;
  undefined1 local_72;
  ulong local_70;
  long local_68;
  int *local_60;
  int *local_58;
  int *local_50;
  undefined1 local_45;
  undefined1 local_34;
  byte local_33;
  byte local_32;
  byte local_31;
  
  local_72 = *(undefined1 *)((long)param_3 + 0x6e);
  lVar14 = *param_3;
  local_120 = param_3[1];
  local_198 = param_3[2];
  local_1a8 = param_3[3];
  local_45 = (char)param_3[4];
  local_1c0 = param_3[5];
  local_170 = (int)param_3[6];
  local_118 = *(byte *)(param_3 + 10);
  local_76 = (char)param_3[0xb];
  local_75 = (char)param_3[0xc];
  local_77 = (char)param_3[0xd];
  uVar3 = *(undefined1 *)((long)param_3 + 0x6c);
  local_78 = *(byte *)((long)param_3 + 0x6f);
  local_16c = *(undefined4 *)((long)param_3 + 0x3c);
  local_174 = (int)param_3[9];
  local_1b8 = (ulong)*(uint *)((long)param_3 + 0x54);
  local_1b0 = (ulong)*(uint *)((long)param_3 + 0x5c);
  local_1a0 = (ulong)*(uint *)((long)param_3 + 100);
  bVar4 = *(byte *)((long)param_3 + 0x6d);
  local_74 = *(byte *)(param_3 + 7);
  local_33 = *(byte *)(param_3 + 7) & 7;
  local_80 = (int *)&DAT_01000c70;
  local_110 = (int *)(ulong)local_78;
  local_108 = (int *)(ulong)local_78;
  local_88 = (int *)&DAT_01000c74;
  local_50 = (int *)&DAT_01000c70;
  local_a8 = param_2;
  iVar15 = (int)local_148;
  iVar17 = (int)((ulong)local_148 >> 0x20);
  if (local_33 == 3) {
    syscall();
    local_108 = local_148;
    local_17c = iVar15;
    local_110 = (int *)((ulong)local_148 >> 0x20);
    local_178 = iVar17;
    local_50 = &local_17c;
    local_88 = &local_178;
  }
  local_58 = (int *)&DAT_01000c74;
  local_32 = *(byte *)((long)param_3 + 0x44) & 7;
  local_168 = local_88;
  local_150 = local_88;
  if (local_32 == 3) {
    syscall();
    local_150 = local_148;
    local_184 = iVar15;
    local_168 = (int *)((ulong)local_148 >> 0x20);
    local_180 = iVar17;
    local_80 = &local_184;
    local_58 = &local_180;
  }
  local_31 = *(byte *)(param_3 + 10) & 7;
  local_a0 = (ulong)bVar4;
  local_73 = *(byte *)((long)param_3 + 0x44);
  if (local_31 == 3) {
    syscall();
    local_160 = local_148;
    local_18c = iVar15;
    local_158 = (undefined *)((ulong)local_148 >> 0x20);
    local_188 = iVar17;
    local_90 = &local_18c;
    local_98 = &local_188;
    lVar16 = local_a8;
  }
  else {
    local_90 = (int *)&DAT_01000c70;
    local_98 = (int *)&DAT_01000c74;
    local_158 = &DAT_01000c74;
    local_160 = (int *)&DAT_01000c74;
    lVar16 = param_2;
  }
  local_d0 = CONCAT71((int7)((ulong)local_98 >> 8),local_31 == 2 || (local_32 == 2 || local_33 == 2)
                     );
  local_68 = param_1;
  if (local_31 == 2 || (local_32 == 2 || local_33 == 2)) {
    LOCK();
    iVar17 = *(int *)(lVar16 + 0x338);
    bVar20 = iVar17 == 0;
    if (bVar20) {
      *(int *)(lVar16 + 0x338) = 1;
      iVar17 = 0;
    }
    UNLOCK();
    local_148 = (int *)CONCAT71(local_148._1_7_,!bVar20);
    piVar2 = (int *)(lVar16 + 0x338);
    if (!bVar20) {
      local_34 = uVar3;
      if (iVar17 == 2) {
        syscall();
      }
      LOCK();
      iVar17 = *piVar2;
      *piVar2 = 2;
      UNLOCK();
      lVar16 = local_a8;
      while (iVar17 != 0) {
        syscall();
        LOCK();
        iVar17 = *piVar2;
        *piVar2 = 2;
        UNLOCK();
        lVar16 = param_2;
      }
    }
    LOCK();
    iVar17 = *(int *)(lVar16 + 0x338);
    *(int *)(lVar16 + 0x338) = 0;
    UNLOCK();
    local_d0 = (ulong)*(uint *)(lVar16 + 0x348);
    if (*(uint *)(lVar16 + 0x348) == 0xffffffff) {
      if (iVar17 == 2) {
        syscall();
        lVar12 = *(long *)(in_FS_OFFSET + -0x40010);
        local_c8 = piVar2;
        if (lVar12 != 0) goto LAB_011ce0d8;
LAB_011ce0e6:
        lVar12 = 0;
LAB_011ce0e9:
        if (lVar12 == 0) {
          syscall();
                    /* WARNING: Could not find normalized switch variable to match jumptable */
          switch(switchD_011ce69c::switchdataD_01002250) {
          case (undefined *)0x0:
LAB_011ce6ad:
            LOCK();
            iVar17 = *piVar2;
            bVar20 = iVar17 == 0;
            if (bVar20) {
              *piVar2 = 1;
              iVar17 = 0;
            }
            UNLOCK();
            local_148 = (int *)CONCAT71(local_148._1_7_,!bVar20);
            if (!bVar20) {
              local_34 = uVar3;
              if (iVar17 == 2) {
                syscall();
              }
              LOCK();
              iVar17 = *piVar2;
              *piVar2 = 2;
              UNLOCK();
              lVar16 = local_a8;
              while (iVar17 != 0) {
                syscall();
                LOCK();
                iVar17 = *piVar2;
                *piVar2 = 2;
                UNLOCK();
                lVar16 = param_2;
              }
            }
            local_c8 = piVar2;
            if (*(int *)(lVar16 + 0x348) == -1) {
              local_d0 = 2;
              *(undefined4 *)(lVar16 + 0x348) = 2;
              LOCK();
              iVar17 = *(int *)(lVar16 + 0x338);
              *(int *)(lVar16 + 0x338) = 0;
              UNLOCK();
              if (iVar17 == 2) {
                syscall();
              }
            }
            else {
              syscall();
              local_d0 = (ulong)*(uint *)(lVar16 + 0x348);
              LOCK();
              iVar17 = *(int *)(lVar16 + 0x338);
              *(int *)(lVar16 + 0x338) = 0;
              UNLOCK();
              if (iVar17 == 2) {
                syscall();
              }
            }
            goto LAB_011cdf76;
          case (undefined *)0x2:
                    /* WARNING: This code block may not be properly labeled as switch case */
            sVar11 = 0x2d;
            break;
          default:
                    /* WARNING: This code block may not be properly labeled as switch case */
            sVar11 = 4;
            break;
          case (undefined *)0xc:
                    /* WARNING: This code block may not be properly labeled as switch case */
            sVar11 = 2;
            break;
          case (undefined *)0x18:
                    /* WARNING: This code block may not be properly labeled as switch case */
            sVar11 = 0x24;
          }
        }
        else {
          syscall();
                    /* WARNING: Could not find normalized switch variable to match jumptable */
          switch(switchD_011ce455::switchdataD_01002188) {
          case (undefined *)0x0:
                    /* WARNING: This code block may not be properly labeled as switch case */
            LOCK();
            *(ulong *)(lVar12 + 8) = *(ulong *)(lVar12 + 8) ^ 3;
            UNLOCK();
            goto LAB_011ce6ad;
          case (undefined *)0x2:
                    /* WARNING: This code block may not be properly labeled as switch case */
            LOCK();
            *(ulong *)(lVar12 + 8) = *(ulong *)(lVar12 + 8) ^ 3;
            UNLOCK();
            sVar11 = 0x2d;
            break;
          default:
                    /* WARNING: This code block may not be properly labeled as switch case */
            LOCK();
            *(ulong *)(lVar12 + 8) = *(ulong *)(lVar12 + 8) ^ 3;
            UNLOCK();
            sVar11 = 4;
            break;
          case (undefined *)0xc:
                    /* WARNING: This code block may not be properly labeled as switch case */
            LOCK();
            *(ulong *)(lVar12 + 8) = *(ulong *)(lVar12 + 8) ^ 3;
            UNLOCK();
            sVar11 = 2;
            break;
          case (undefined *)0x18:
                    /* WARNING: This code block may not be properly labeled as switch case */
            LOCK();
            *(ulong *)(lVar12 + 8) = *(ulong *)(lVar12 + 8) ^ 3;
            UNLOCK();
            sVar11 = 0x24;
          }
        }
      }
      else {
        lVar12 = *(long *)(in_FS_OFFSET + -0x40010);
        local_c8 = piVar2;
        if (lVar12 == 0) goto LAB_011ce0e6;
LAB_011ce0d8:
        if ((*(byte *)(lVar12 + 0x21c) & 1) != 0) goto LAB_011ce0e6;
        uVar19 = *(ulong *)(lVar12 + 8);
        do {
          LOCK();
          uVar13 = *(ulong *)(lVar12 + 8);
          bVar20 = uVar19 == uVar13;
          if (bVar20) {
            *(ulong *)(lVar12 + 8) = uVar19 | 3;
            uVar13 = uVar19;
          }
          UNLOCK();
          uVar19 = uVar13;
        } while (!bVar20);
        if ((uVar13 & 7) == 0) goto LAB_011ce0e9;
        sVar11 = 0x11;
        if (((uint)uVar13 & 7) != 6) {
          lVar12 = 0;
          goto LAB_011ce0e9;
        }
      }
      local_200 = sVar11;
      if (local_31 == 3) {
        if (*local_90 != -1) {
          syscall();
        }
        if (*local_90 != *local_98) {
          syscall();
        }
      }
      if (local_32 == 3) {
        if (*local_80 != -1) {
          syscall();
        }
        if (*local_80 != *local_58) {
          syscall();
        }
      }
      if (local_33 == 3) {
        if (*local_50 != -1) {
          syscall();
        }
        if (*local_50 != *local_88) {
          syscall();
        }
      }
      goto LAB_011ceb29;
    }
    if (iVar17 == 2) {
      syscall();
    }
  }
LAB_011cdf76:
  if (bVar4 == 0xff) {
    local_60 = (int *)0xffffffff;
    local_70 = 0xffffffff;
  }
  else {
    syscall();
    local_70 = (ulong)local_148 >> 0x20;
    local_60 = local_148;
    syscall();
    lVar16 = param_2;
  }
  local_f8 = *(undefined8 *)(lVar16 + 0x328);
  lStack_140 = *(long *)(lVar16 + 0x330);
  auVar21 = ZEXT816(0) << 0x20;
  local_138._8_8_ = SUB168(ZEXT816(0),4);
  puStack_e8 = (ulong *)0x0;
  puStack_e0 = (ulong *)local_138._8_8_;
  local_1d0 = &local_f8;
  local_1c8 = &PTR_FUN_0100eb88;
  local_148._1_7_ = (undefined7)((ulong)local_f8 >> 8);
  local_148 = (int *)CONCAT71(local_148._1_7_,0x1ffffffffffffffe < local_120);
  uVar7 = local_f8;
  lVar16 = lStack_140;
  puVar6 = puStack_e8;
  puVar8 = (ulong *)local_138._8_8_;
  lStack_f0 = lStack_140;
  local_100 = unaff_retaddr;
  if (local_120 < 0x1fffffffffffffff) {
    lVar16 = local_120 * 8 + 8;
    local_138._0_16_ = auVar21;
    if (lVar16 == 0) {
      lVar12 = -8;
    }
    else {
      lVar12 = FUN_011c7840(&local_f8,lVar16,3);
      auVar21 = local_138._0_16_;
      uVar7 = local_f8;
      lVar16 = lStack_f0;
      puVar6 = puStack_e8;
      puVar8 = puStack_e0;
      if (lVar12 == 0) goto joined_r0x011ce2df;
    }
    *(undefined8 *)(lVar12 + local_120 * 8) = 0;
    local_c8 = (int *)lVar12;
    local_34 = uVar3;
    if (local_120 != 0) {
      plVar18 = (long *)(lVar14 + 8);
      uVar19 = 0;
      do {
        lVar14 = plVar18[-1];
        lVar16 = *plVar18;
        lVar12 = FUN_011c7840(&local_f8,lVar16 + 1,0);
        if (lVar12 == 0) {
          local_248 = local_f8;
          lStack_240 = lStack_f0;
          puStack_238 = puStack_e8;
          puStack_230 = puStack_e0;
          FUN_011c7690(&local_248);
          if ((int)local_60 != -1) {
            syscall();
          }
          if ((int)local_60 != (int)local_70) {
            syscall();
          }
          if (local_31 == 3) {
            if (*local_90 != -1) {
              syscall();
            }
            if (*local_90 != *local_98) {
              syscall();
            }
          }
          if (local_32 == 3) {
            if (*local_80 != -1) {
              syscall();
            }
            if (*local_80 != *local_58) {
              syscall();
            }
          }
          local_200 = 0x1a;
          if (local_33 == 3) {
            if (*local_50 != -1) {
              syscall();
            }
            if (*local_50 != *local_88) {
              syscall();
            }
          }
          goto LAB_011ceb29;
        }
        FUN_011f4580(lVar12,lVar14,lVar16);
        *(undefined1 *)(lVar12 + lVar16) = 0;
        *(long *)((long)local_c8 + uVar19 * 8) = lVar12;
        uVar19 = uVar19 + 1;
        plVar18 = plVar18 + 2;
      } while (local_120 != uVar19);
    }
    iVar17 = (uint)((int)local_70 != -1) * 4 + -1;
    if (local_1c0 == 0) {
      FUN_011d0860(&local_228,*(undefined8 *)(local_a8 + 0x2c0),*(undefined8 *)(local_a8 + 0x2c8),
                   &local_1d0,iVar17,1);
      bVar4 = local_33;
      if (local_218 == 0) {
        local_1f8 = local_228;
        uStack_1f0 = uStack_220;
        goto LAB_011ce7d2;
      }
      local_288 = local_f8;
      lStack_280 = lStack_f0;
      puStack_278 = puStack_e8;
      puStack_270 = puStack_e0;
      FUN_011c7690(&local_288);
      if ((int)local_60 != -1) {
        syscall();
      }
      if ((int)local_60 != (int)local_70) {
        syscall();
      }
      if (local_31 == 3) {
        if (*local_90 != -1) {
          syscall();
        }
        if (*local_90 != *local_98) {
          syscall();
        }
      }
      if (local_32 == 3) {
        if (*local_80 != -1) {
          syscall();
        }
        if (*local_80 != *local_58) {
          syscall();
        }
      }
      local_200 = local_218;
      if (bVar4 == 3) {
        if (*local_50 != -1) {
          syscall();
        }
        if (*local_50 != *local_88) {
          syscall();
        }
      }
    }
    else {
      FUN_011d0bb0(&local_210,local_1c0,&local_1d0,iVar17,1);
      bVar4 = local_33;
      if (local_200 == 0) {
        local_1e8 = local_210;
        uStack_1e0 = uStack_208;
LAB_011ce7d2:
        syscall();
        FUN_011cd090(local_a8,0x80000);
        syscall();
                    /* WARNING: Could not recover jumptable at 0x011ce957. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        lVar14 = (*(code *)PTR_LAB_01002318)();
        return lVar14;
      }
      local_268 = local_f8;
      lStack_260 = lStack_f0;
      puStack_258 = puStack_e8;
      puStack_250 = puStack_e0;
      FUN_011c7690(&local_268);
      if ((int)local_60 != -1) {
        syscall();
      }
      if ((int)local_60 != (int)local_70) {
        syscall();
      }
      if (local_31 == 3) {
        if (*local_90 != -1) {
          syscall();
        }
        if (*local_90 != *local_98) {
          syscall();
        }
      }
      if (local_32 == 3) {
        if (*local_80 != -1) {
          syscall();
        }
        if (*local_80 != *local_58) {
          syscall();
        }
      }
      if (bVar4 == 3) {
        if (*local_50 != -1) {
          syscall();
        }
        if (*local_50 != *local_88) {
          syscall();
        }
      }
    }
  }
  else {
joined_r0x011ce2df:
    while (local_138._0_16_ = auVar21, puVar9 = puStack_e0, lVar14 = lStack_f0, uVar10 = local_f8,
          local_f8 = uVar7, puVar6 != (ulong *)0x0) {
      puVar5 = (ulong *)puVar6[2];
      puVar1 = (undefined8 *)(lStack_f0 + 0x18);
      lStack_f0 = lVar16;
      puStack_e0 = puVar8;
      (*(code *)*puVar1)(uVar10,puVar6,*puVar6 & 0xfffffffffffffffe,3,local_100);
      auVar21 = local_138._0_16_;
      uVar7 = local_f8;
      lVar16 = lStack_f0;
      puVar6 = puVar5;
      puVar8 = puStack_e0;
      puStack_e0 = puVar9;
      lStack_f0 = lVar14;
      local_f8 = uVar10;
    }
    while (puStack_e0 = puVar8, lStack_f0 = lVar16, puVar9 != (ulong *)0x0) {
      puVar6 = (ulong *)puVar9[2];
      (**(code **)(lVar14 + 0x18))(uVar10,puVar9,*puVar9 & 0xfffffffffffffffe,3,local_100);
      lVar16 = lStack_f0;
      puVar8 = puStack_e0;
      puVar9 = puVar6;
    }
    if ((int)local_60 != -1) {
      syscall();
    }
    if ((int)local_60 != (int)local_70) {
      syscall();
    }
    if (local_31 == 3) {
      if (*local_90 != -1) {
        syscall();
      }
      if (*local_90 != *local_98) {
        syscall();
      }
    }
    if (local_32 == 3) {
      if (*local_80 != -1) {
        syscall();
      }
      if (*local_80 != *local_58) {
        syscall();
      }
    }
    local_200 = 0x1a;
    if (local_33 == 3) {
      if (*local_50 != -1) {
        syscall();
      }
      if (*local_50 != *local_88) {
        syscall();
      }
    }
  }
LAB_011ceb29:
  *(short *)(local_68 + 0x148) = local_200;
  return local_68;
}


// ---- FUN_011cfc60 @ 011cfc60

undefined8
FUN_011cfc60(ulong param_1,uint param_2,undefined4 param_3,undefined4 param_4,uint param_5)

{
  undefined8 uVar1;
  
  switch(param_2 & 7) {
  case 0:
    return 0;
  case 2:
    param_1 = (ulong)param_5;
    break;
  case 3:
    uVar1 = FUN_011d0750(param_3,param_4);
    return uVar1;
  case 4:
    syscall();
    return 0;
  case 5:
    return 1;
  case 6:
    return 0x2d;
  case 7:
    return 4;
  }
  uVar1 = FUN_011d0750(param_1,param_4);
  return uVar1;
}


// ---- FUN_011cfc90 @ 011cfc90

/* WARNING: Removing unreachable block (ram,0x011d002f) */

short FUN_011cfc90(long param_1,long *param_2)

{
  long lVar1;
  ulong uVar2;
  long lVar3;
  char *pcVar4;
  ulong *puVar5;
  ulong *puVar6;
  ulong *puVar7;
  short sVar8;
  undefined8 *puVar9;
  undefined8 *puVar10;
  ulong uVar11;
  long lVar12;
  undefined8 uVar13;
  long *plVar14;
  undefined1 auVar15 [16];
  undefined8 unaff_retaddr;
  undefined8 local_198 [4];
  undefined8 local_178 [4];
  undefined8 local_158 [4];
  undefined8 local_138 [4];
  undefined8 local_118;
  undefined8 uStack_110;
  short local_108;
  undefined8 local_100;
  undefined8 uStack_f8;
  short local_f0;
  undefined8 local_e8;
  long lStack_e0;
  undefined1 local_d8 [16];
  undefined8 local_c8;
  undefined8 uStack_c0;
  undefined8 local_b8;
  undefined8 uStack_b0;
  undefined8 *local_a8;
  undefined **local_a0;
  undefined8 *local_98;
  ulong local_90;
  long local_88;
  long local_80;
  undefined8 local_78;
  long lStack_70;
  ulong *puStack_68;
  ulong *puStack_60;
  undefined8 local_50;
  undefined8 local_48;
  char *local_40;
  undefined1 local_38;
  undefined1 local_33;
  short local_32;
  
  lVar1 = *param_2;
  uVar2 = param_2[1];
  lVar3 = param_2[2];
  local_33 = (undefined1)param_2[3];
  FUN_011cd090();
  pcVar4 = *(char **)(param_1 + 0x2d0);
  uVar13 = *(undefined8 *)(param_1 + 0x2d8);
  local_e8 = *(undefined8 *)(param_1 + 0x328);
  lStack_e0 = *(long *)(param_1 + 0x330);
  auVar15 = ZEXT816(0) << 0x20;
  local_d8._8_8_ = SUB168(ZEXT816(0),4);
  puStack_68 = (ulong *)0x0;
  puStack_60 = (ulong *)local_d8._8_8_;
  local_a8 = &local_78;
  local_a0 = &PTR_FUN_0100eb88;
  local_38 = 0x1ffffffffffffffe < uVar2;
  local_78 = local_e8;
  lStack_70 = lStack_e0;
  if (uVar2 < 0x1fffffffffffffff) {
    lVar12 = uVar2 * 8 + 8;
    local_88 = lVar3;
    local_80 = param_1;
    local_48 = uVar13;
    local_40 = pcVar4;
    if (lVar12 == 0) {
      puVar9 = (undefined8 *)0xfffffffffffffff8;
      *(undefined8 *)(uVar2 * 8 + -8) = 0;
    }
    else {
      local_d8 = auVar15;
      puVar9 = (undefined8 *)FUN_011c7840(&local_78,lVar12,3);
      auVar15 = local_d8;
      if (puVar9 == (undefined8 *)0x0) goto LAB_011cfd34;
      puVar9[uVar2] = 0;
    }
    local_d8 = auVar15;
    if (uVar2 != 0) {
      plVar14 = (long *)(lVar1 + 8);
      uVar11 = 0;
      local_98 = puVar9;
      local_90 = uVar2;
      local_50 = unaff_retaddr;
      do {
        local_32 = 0x1a;
        lVar1 = plVar14[-1];
        lVar3 = *plVar14;
        lVar12 = FUN_011c7840(&local_78,lVar3 + 1,0);
        if (lVar12 == 0) {
          puVar9 = local_158;
          unaff_retaddr = local_50;
          goto LAB_011cfd41;
        }
        FUN_011f4580(lVar12,lVar1,lVar3);
        *(undefined1 *)(lVar12 + lVar3) = 0;
        local_98[uVar11] = lVar12;
        uVar11 = uVar11 + 1;
        plVar14 = plVar14 + 2;
        unaff_retaddr = local_50;
        puVar9 = local_98;
      } while (local_90 != uVar11);
    }
    if (local_88 == 0) {
      FUN_011d0860(&local_118,*(undefined8 *)(local_80 + 0x2c0),*(undefined8 *)(local_80 + 0x2c8),
                   &local_a8,0xffffffff,1);
      if (local_108 == 0) {
        local_c8 = local_118;
        uStack_c0 = uStack_110;
        puVar10 = &local_c8;
        goto LAB_011cff6c;
      }
      local_32 = local_108;
      puVar9 = local_198;
    }
    else {
      FUN_011d0bb0(&local_100,local_88,&local_a8,0xffffffff,1);
      if (local_f0 == 0) {
        local_b8 = local_100;
        uStack_b0 = uStack_f8;
        puVar10 = &local_b8;
LAB_011cff6c:
        uVar13 = local_48;
        pcVar4 = local_40;
        if (local_40 == (char *)0x0) {
          uVar13 = 0x1d;
          pcVar4 = "/usr/local/bin:/bin/:/usr/bin";
        }
        local_32 = FUN_011d0070(local_33,*puVar9,puVar9,puVar10,pcVar4,uVar13);
        puVar7 = puStack_60;
        lVar1 = lStack_70;
        uVar13 = local_78;
        puVar5 = puStack_68;
        while (puVar5 != (ulong *)0x0) {
          puVar6 = (ulong *)puVar5[2];
          (**(code **)(lVar1 + 0x18))(uVar13,puVar5,*puVar5 & 0xfffffffffffffffe,3,unaff_retaddr);
          puVar5 = puVar6;
        }
        while (puVar7 != (ulong *)0x0) {
          puVar5 = (ulong *)puVar7[2];
          (**(code **)(lVar1 + 0x18))(uVar13,puVar7,*puVar7 & 0xfffffffffffffffe,3,unaff_retaddr);
          puVar7 = puVar5;
        }
        return local_32;
      }
      puVar9 = local_178;
      local_32 = local_f0;
    }
  }
  else {
LAB_011cfd34:
    local_d8 = auVar15;
    local_32 = 0x1a;
    puVar9 = local_138;
  }
LAB_011cfd41:
  *puVar9 = local_78;
  puVar9[1] = lStack_70;
  puVar9[2] = puStack_68;
  puVar9[3] = puStack_60;
  uVar13 = *puVar9;
  lVar1 = puVar9[1];
  puVar5 = (ulong *)puVar9[3];
  puVar7 = (ulong *)puVar9[2];
  sVar8 = local_32;
  while (local_32 = sVar8, puVar7 != (ulong *)0x0) {
    puVar6 = (ulong *)puVar7[2];
    (**(code **)(lVar1 + 0x18))(uVar13,puVar7,*puVar7 & 0xfffffffffffffffe,3,unaff_retaddr);
    puVar7 = puVar6;
    sVar8 = local_32;
  }
  while (puVar5 != (ulong *)0x0) {
    puVar7 = (ulong *)puVar5[2];
    (**(code **)(lVar1 + 0x18))(uVar13,puVar5,*puVar5 & 0xfffffffffffffffe,3,unaff_retaddr);
    puVar5 = puVar7;
  }
  return sVar8;
}


// ---- FUN_011d0070 @ 011d0070

ulong FUN_011d0070(uint param_1,undefined8 param_2,long *param_3,undefined8 *param_4,long param_5,
                  ulong param_6)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  undefined1 local_1080 [4096];
  undefined1 local_80 [8];
  char local_78;
  ulong local_70;
  undefined8 *local_68;
  undefined8 local_60;
  long local_58;
  long local_50;
  ulong local_48;
  long local_40;
  uint local_34;
  
  local_50 = param_5;
  local_34 = param_1;
  lVar3 = FUN_011f4140(param_2);
  FUN_011c97a0(local_80,param_2,lVar3,0,0x2f);
  if (local_78 != '\0') {
    uVar4 = FUN_011d02a0(param_2,param_3,*param_4);
    return uVar4;
  }
  local_40 = *param_3;
  uVar4 = 0x2d;
  uVar5 = 0;
  local_48 = 0;
  local_70 = param_6;
  local_68 = param_4;
  local_60 = param_2;
  local_58 = lVar3;
  if (param_6 != 0) goto LAB_011d0150;
  while (uVar5 != local_70) {
    uVar7 = uVar5;
    uVar6 = uVar5;
    if (uVar5 < local_70) {
      do {
        uVar7 = uVar6;
        if (*(char *)(local_50 + uVar6) == ':') break;
        uVar6 = uVar6 + 1;
        uVar7 = local_70;
      } while (local_70 != uVar6);
    }
    lVar3 = uVar7 - uVar5;
    if (local_50 + uVar5 == 0) break;
    uVar4 = lVar3 + local_58;
    if (0xffe < uVar4) {
      if ((local_34 & 1) != 0) {
        return 0x31;
      }
      *param_3 = local_40;
      return 0x31;
    }
    FUN_011f4580(local_1080,local_50 + uVar5,lVar3);
    local_1080[lVar3] = 0x2f;
    FUN_011f4580(local_1080 + lVar3 + 1,local_60,local_58);
    uVar2 = local_34;
    local_1080[uVar4 + 1] = 0;
    if ((local_34 & 1) == 0) {
      *param_3 = (long)local_1080;
    }
    uVar5 = uVar5 + lVar3;
    uVar4 = FUN_011d02a0(local_1080,param_3,*local_68);
    iVar1 = (int)(uVar4 & 0xffff);
    if (1 < iVar1 - 0x2dU) {
      if (iVar1 != 10) goto joined_r0x011d027b;
      local_48 = CONCAT71((int7)((uVar4 & 0xffff) >> 8),1);
    }
    if (uVar5 < local_70) {
LAB_011d0150:
      while (*(char *)(local_50 + uVar5) == ':') {
        uVar5 = uVar5 + 1;
        if (local_70 == uVar5) goto LAB_011d0252;
      }
    }
  }
LAB_011d0252:
  uVar2 = local_34;
  if ((local_48 & 1) != 0) {
    uVar4 = 10;
  }
joined_r0x011d027b:
  if ((uVar2 & 1) == 0) {
    *param_3 = local_40;
  }
  return uVar4;
}


// ---- FUN_011d02a0 @ 011d02a0

/* WARNING: Removing unreachable block (ram,0x011d02ed) */
/* WARNING: Removing unreachable block (ram,0x011d02fa) */
/* WARNING: Removing unreachable block (ram,0x011d033d) */
/* WARNING: Removing unreachable block (ram,0x011d0337) */
/* WARNING: Removing unreachable block (ram,0x011d0313) */
/* WARNING: Removing unreachable block (ram,0x011d031f) */
/* WARNING: Removing unreachable block (ram,0x011d0325) */
/* WARNING: Removing unreachable block (ram,0x011d0319) */
/* WARNING: Removing unreachable block (ram,0x011d0343) */
/* WARNING: Removing unreachable block (ram,0x011d0301) */
/* WARNING: Removing unreachable block (ram,0x011d030d) */
/* WARNING: Removing unreachable block (ram,0x011d0307) */
/* WARNING: Removing unreachable block (ram,0x011d0331) */
/* WARNING: Removing unreachable block (ram,0x011d032b) */
/* WARNING: Recovered jumptable eliminated as dead code */

undefined8 FUN_011d02a0(void)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + -0x40010);
  if (((lVar1 != 0) && ((*(byte *)(lVar1 + 0x21c) & 1) == 0)) &&
     (((uint)*(ulong *)(lVar1 + 8) & 7) == 6)) {
    *(ulong *)(lVar1 + 8) = *(ulong *)(lVar1 + 8) | 7;
    return CONCAT62((int6)((ulong)lVar1 >> 0x10),0x11);
  }
  syscall();
  return 0xffff0004;
}


// ---- FUN_011d0350 @ 011d0350

/* WARNING: Removing unreachable block (ram,0x011d0463) */
/* WARNING: Removing unreachable block (ram,0x011d0470) */
/* WARNING: Removing unreachable block (ram,0x011d0477) */
/* WARNING: Removing unreachable block (ram,0x011d047f) */
/* WARNING: Removing unreachable block (ram,0x011d048e) */

undefined8 FUN_011d0350(long param_1,ulong param_2)

{
  undefined1 auVar1 [32];
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  long in_FS_OFFSET;
  bool bVar5;
  undefined1 local_1010 [4096];
  
  lVar2 = 0;
  uVar3 = param_2;
  if (0x1f < param_2) {
    do {
      auVar1 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])(param_1 + lVar2));
      if ((((((((((((((((((((((((((((((((SUB321(auVar1 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar1 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar1 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar1 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar1 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar1 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar1 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar1 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar1 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar1 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar1 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar1 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar1 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar1 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar1 >> 0x77,0) & 1) != 0) || SUB321(auVar1 >> 0x7f,0) != '\0')
                        || (SUB321(auVar1 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar1 >> 0x8f,0) & 1) != 0) || (SUB321(auVar1 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar1 >> 0x9f,0) & 1) != 0) || (SUB321(auVar1 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar1 >> 0xaf,0) & 1) != 0) || (SUB321(auVar1 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar1 >> 0xbf,0) != '\0') || (SUB321(auVar1 >> 199,0) & 1) != 0) ||
               (SUB321(auVar1 >> 0xcf,0) & 1) != 0) || (SUB321(auVar1 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar1 >> 0xdf,0) & 1) != 0) || (SUB321(auVar1 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar1 >> 0xef,0) & 1) != 0) || (SUB321(auVar1 >> 0xf7,0) & 1) != 0) ||
          auVar1[0x1f] < '\0') goto LAB_011d0493;
      lVar2 = lVar2 + 0x20;
      uVar3 = uVar3 - 0x20;
    } while (0x1f < uVar3);
  }
  if (uVar3 != 0) {
    lVar2 = lVar2 + param_1;
    uVar4 = 0;
    do {
      if (*(char *)(lVar2 + uVar4) == '\0') {
LAB_011d0493:
        return CONCAT62((int6)((ulong)lVar2 >> 0x10),0x32);
      }
      uVar4 = uVar4 + 1;
    } while (uVar3 != uVar4);
  }
  if (0xfff < param_2) {
    return CONCAT62((int6)((ulong)lVar2 >> 0x10),0x31);
  }
  FUN_011f4580(local_1010,param_1,param_2);
  local_1010[param_2] = 0;
  lVar2 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar2 != 0) && ((*(byte *)(lVar2 + 0x21c) & 1) == 0)) {
    uVar3 = *(ulong *)(lVar2 + 8);
    do {
      LOCK();
      uVar4 = *(ulong *)(lVar2 + 8);
      bVar5 = uVar3 == uVar4;
      if (bVar5) {
        *(ulong *)(lVar2 + 8) = uVar3 | 3;
        uVar4 = uVar3;
      }
      UNLOCK();
      uVar3 = uVar4;
    } while (!bVar5);
    if ((uVar4 & 7) == 0) goto LAB_011d0438;
    if (((uint)uVar4 & 7) == 6) {
      return 0x11;
    }
  }
  lVar2 = 0;
LAB_011d0438:
  if (lVar2 == 0) {
    syscall();
                    /* WARNING: Could not find normalized switch variable to match jumptable */
    switch(switchD_011d04de::switchdataD_01002bc8) {
    case (undefined *)0x0:
      return 0;
    }
  }
  else {
    syscall();
                    /* WARNING: Could not find normalized switch variable to match jumptable */
    switch(switchD_011d04a2::switchdataD_01002920) {
    case (undefined *)0x0:
                    /* WARNING: This code block may not be properly labeled as switch case */
      LOCK();
      *(ulong *)(lVar2 + 8) = *(ulong *)(lVar2 + 8) ^ 3;
      UNLOCK();
      return 0;
    default:
                    /* WARNING: This code block may not be properly labeled as switch case */
      LOCK();
      *(ulong *)(lVar2 + 8) = *(ulong *)(lVar2 + 8) ^ 3;
      UNLOCK();
    }
  }
                    /* WARNING: This code block may not be properly labeled as switch case */
  return 4;
}


// ---- FUN_011d0590 @ 011d0590

/* WARNING: Removing unreachable block (ram,0x011d060d) */
/* WARNING: Removing unreachable block (ram,0x011d0620) */
/* WARNING: Removing unreachable block (ram,0x011d0627) */
/* WARNING: Removing unreachable block (ram,0x011d062f) */
/* WARNING: Removing unreachable block (ram,0x011d0637) */

undefined8 FUN_011d0590(int param_1)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  long in_FS_OFFSET;
  bool bVar4;
  
  if (param_1 == -100) {
    return 0;
  }
  lVar3 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar3 != 0) && ((*(byte *)(lVar3 + 0x21c) & 1) == 0)) {
    uVar1 = *(ulong *)(lVar3 + 8);
    do {
      LOCK();
      uVar2 = *(ulong *)(lVar3 + 8);
      bVar4 = uVar1 == uVar2;
      if (bVar4) {
        *(ulong *)(lVar3 + 8) = uVar1 | 3;
        uVar2 = uVar1;
      }
      UNLOCK();
      uVar1 = uVar2;
    } while (!bVar4);
    if ((uVar2 & 7) == 0) goto LAB_011d05e4;
    if (((uint)uVar2 & 7) == 6) {
      return 0x11;
    }
  }
  lVar3 = 0;
LAB_011d05e4:
  if (lVar3 == 0) {
    syscall();
                    /* WARNING: Could not find normalized switch variable to match jumptable */
    switch(switchD_011d0684::switchdataD_01002f18) {
    case (undefined *)0x0:
                    /* WARNING: This code block may not be properly labeled as switch case */
      return 0;
    case (undefined *)0x5:
                    /* WARNING: This code block may not be properly labeled as switch case */
      return 0x38;
    case (undefined *)0xd:
                    /* WARNING: This code block may not be properly labeled as switch case */
      return 10;
    case (undefined *)0x14:
                    /* WARNING: This code block may not be properly labeled as switch case */
      return 0x2e;
    }
  }
  else {
    syscall();
                    /* WARNING: Could not find normalized switch variable to match jumptable */
    switch(switchD_011d0644::switchdataD_01002e70) {
    case (undefined *)0x0:
                    /* WARNING: This code block may not be properly labeled as switch case */
      LOCK();
      *(ulong *)(lVar3 + 8) = *(ulong *)(lVar3 + 8) ^ 3;
      UNLOCK();
      return 0;
    default:
                    /* WARNING: This code block may not be properly labeled as switch case */
      LOCK();
      *(ulong *)(lVar3 + 8) = *(ulong *)(lVar3 + 8) ^ 3;
      UNLOCK();
      break;
    case (undefined *)0x5:
                    /* WARNING: This code block may not be properly labeled as switch case */
      LOCK();
      *(ulong *)(lVar3 + 8) = *(ulong *)(lVar3 + 8) ^ 3;
      UNLOCK();
      return 0x38;
    case (undefined *)0xd:
                    /* WARNING: This code block may not be properly labeled as switch case */
      LOCK();
      *(ulong *)(lVar3 + 8) = *(ulong *)(lVar3 + 8) ^ 3;
      UNLOCK();
      return 10;
    case (undefined *)0x14:
                    /* WARNING: This code block may not be properly labeled as switch case */
      LOCK();
      *(ulong *)(lVar3 + 8) = *(ulong *)(lVar3 + 8) ^ 3;
      UNLOCK();
      return 0x2e;
    }
  }
                    /* WARNING: This code block may not be properly labeled as switch case */
  return 4;
}


// ---- FUN_011d06d0 @ 011d06d0

void FUN_011d06d0(void)

{
  long lVar1;
  
  lVar1 = 0;
  do {
    syscall();
    lVar1 = lVar1 + 1;
  } while (lVar1 != 8);
  return;
}


// ---- FUN_011d0730 @ 011d0730

/* WARNING: Removing unreachable block (ram,0x011d0824) */
/* WARNING: Removing unreachable block (ram,0x011d0841) */
/* WARNING: Removing unreachable block (ram,0x011d082d) */

undefined8 FUN_011d0730(undefined8 param_1,ulong param_2)

{
  ulong uVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long in_FS_OFFSET;
  bool bVar5;
  
  FUN_011d06d0();
  syscall();
  lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar4 != 0) && ((*(byte *)(lVar4 + 0x21c) & 1) == 0)) {
    uVar1 = *(ulong *)(lVar4 + 8);
    do {
      LOCK();
      uVar2 = *(ulong *)(lVar4 + 8);
      bVar5 = uVar1 == uVar2;
      if (bVar5) {
        *(ulong *)(lVar4 + 8) = uVar1 | 3;
        uVar2 = uVar1;
      }
      UNLOCK();
      uVar1 = uVar2;
    } while (!bVar5);
    if ((uVar2 & 7) == 0) goto LAB_011d0798;
    if (((uint)uVar2 & 7) == 6) {
      return 0x11;
    }
  }
  lVar4 = 0;
LAB_011d0798:
  if (lVar4 == 0) {
    syscall();
                    /* WARNING: Could not recover jumptable at 0x011d081d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar3 = (*(code *)PTR_LAB_01003088)(1,param_2 & 0xffffffff);
    return uVar3;
  }
  syscall();
                    /* WARNING: Could not recover jumptable at 0x011d07cd. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar3 = (*(code *)PTR_LAB_01002fc0)();
  return uVar3;
}


// ---- FUN_011d0750 @ 011d0750

/* WARNING: Removing unreachable block (ram,0x011d0824) */
/* WARNING: Removing unreachable block (ram,0x011d0841) */
/* WARNING: Removing unreachable block (ram,0x011d082d) */

undefined8 FUN_011d0750(int param_1,undefined4 param_2)

{
  ulong uVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long in_FS_OFFSET;
  bool bVar5;
  
  lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar4 != 0) && ((*(byte *)(lVar4 + 0x21c) & 1) == 0)) {
    uVar1 = *(ulong *)(lVar4 + 8);
    do {
      LOCK();
      uVar2 = *(ulong *)(lVar4 + 8);
      bVar5 = uVar1 == uVar2;
      if (bVar5) {
        *(ulong *)(lVar4 + 8) = uVar1 | 3;
        uVar2 = uVar1;
      }
      UNLOCK();
      uVar1 = uVar2;
    } while (!bVar5);
    if ((uVar2 & 7) == 0) goto LAB_011d0798;
    if (((uint)uVar2 & 7) == 6) {
      return 0x11;
    }
  }
  lVar4 = 0;
LAB_011d0798:
  if (lVar4 == 0) {
    syscall();
                    /* WARNING: Could not recover jumptable at 0x011d081d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar3 = (*(code *)PTR_LAB_01003088)((long)param_1,param_2);
    return uVar3;
  }
  syscall();
                    /* WARNING: Could not recover jumptable at 0x011d07cd. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar3 = (*(code *)PTR_LAB_01002fc0)();
  return uVar3;
}


// ---- FUN_011d0860 @ 011d0860

void FUN_011d0860(undefined8 *param_1,undefined8 *param_2,ulong param_3,undefined8 *param_4,
                 int param_5,char param_6)

{
  char cVar1;
  byte bVar2;
  long lVar3;
  undefined8 *puVar4;
  long lVar5;
  long lVar6;
  byte bVar7;
  ulong uVar8;
  char *pcVar9;
  undefined8 unaff_retaddr;
  undefined8 local_c0 [2];
  short local_b0;
  undefined8 local_a8 [2];
  short local_98;
  ulong local_90;
  undefined8 local_88;
  undefined8 *local_80;
  undefined8 local_78;
  uint local_6c;
  undefined8 *local_68;
  undefined8 *local_60;
  undefined8 *local_58;
  undefined8 *local_50;
  int local_44;
  undefined1 local_40;
  long local_38;
  
  local_88 = *param_4;
  local_80 = (undefined8 *)param_4[1];
  local_68 = param_2;
  local_58 = param_4;
  local_44 = param_5;
  if (param_3 == 0) {
    bVar2 = 0;
    if (param_6 != '\0') goto LAB_011d08f2;
LAB_011d091a:
    bVar7 = 0;
  }
  else {
    uVar8 = 0;
    do {
      pcVar9 = (char *)local_68[uVar8];
      lVar5 = 0;
      cVar1 = *pcVar9;
      while ((cVar1 != '\0' && (cVar1 != '='))) {
        lVar5 = lVar5 + 1;
        cVar1 = pcVar9[lVar5];
      }
      bVar2 = FUN_011c9680(pcVar9,lVar5,"ZIG_PROGRESS",0xc);
    } while (((bVar2 & 1) == 0) && (uVar8 = uVar8 + 1, uVar8 != param_3));
    if (param_6 == '\0') goto LAB_011d091a;
LAB_011d08f2:
    if (local_44 < 0) {
      bVar7 = (~bVar2 & 1) * '\x02' - 2;
      param_3 = param_3 - (bVar2 & 1);
    }
    else {
      bVar7 = -((bVar2 ^ 1) & 1) | 1;
      param_3 = param_3 + ((bVar2 ^ 1) & 1);
    }
  }
  local_40 = 0x1ffffffffffffffe < param_3;
  if (param_3 < 0x1fffffffffffffff) {
    lVar5 = param_3 * 8 + 8;
    local_78 = unaff_retaddr;
    if (lVar5 == 0) {
      local_50 = (undefined8 *)0xfffffffffffffff8;
    }
    else {
      local_50 = (undefined8 *)(*(code *)*local_80)(local_88,lVar5,3,unaff_retaddr);
      if (local_50 == (undefined8 *)0x0) goto LAB_011d0952;
    }
    local_50[param_3] = 0;
    local_60 = param_1;
    if ((~bVar7 & 3) == 0) {
      FUN_011d1a10(local_a8,local_58,local_44);
      if (local_98 != 0) {
        *local_50 = 0;
        FUN_011d1960(local_50,0,local_58);
        *(short *)(param_1 + 2) = local_98;
        return;
      }
      *local_50 = local_a8[0];
      local_38 = 1;
      pcVar9 = (char *)*local_68;
      puVar4 = local_50;
    }
    else {
      local_38 = 0;
      pcVar9 = (char *)*local_68;
      puVar4 = local_50;
    }
    if (pcVar9 != (char *)0x0) {
      local_6c = bVar7 & 3;
      lVar5 = 0;
      local_90 = param_3;
      local_50 = puVar4;
      do {
        lVar6 = 0;
        cVar1 = *pcVar9;
        while ((cVar1 != '\0' && (cVar1 != '='))) {
          lVar6 = lVar6 + 1;
          cVar1 = pcVar9[lVar6];
        }
        uVar8 = FUN_011c9680(pcVar9,lVar6,"ZIG_PROGRESS",0xc);
        if (((uVar8 & 1) == 0) || ((bVar7 & 3) == 0)) {
          lVar6 = FUN_011f4140(pcVar9);
          lVar3 = (*(code *)*local_80)(local_88,lVar6 + 1,0,local_78);
          if (lVar3 == 0) {
            local_50[local_38] = 0;
            FUN_011d1960(local_50,local_38,local_58);
            *(undefined2 *)(local_60 + 2) = 0x1a;
            return;
          }
          FUN_011f4580(lVar3,pcVar9,lVar6);
          *(undefined1 *)(lVar3 + lVar6) = 0;
          local_50[local_38] = lVar3;
          local_38 = local_38 + 1;
          puVar4 = local_50;
          param_3 = local_90;
        }
        else if (local_6c != 2) {
          FUN_011d1a10(local_c0,local_58,local_44);
          if (local_b0 != 0) {
            local_50[local_38] = 0;
            FUN_011d1960(local_50,local_38,local_58);
            *(short *)(local_60 + 2) = local_b0;
            return;
          }
          local_50[local_38] = local_c0[0];
          local_38 = local_38 + 1;
          puVar4 = local_50;
        }
        pcVar9 = (char *)local_68[lVar5 + 1];
        lVar5 = lVar5 + 1;
      } while (pcVar9 != (char *)0x0);
    }
    *(undefined2 *)(local_60 + 2) = 0;
    *local_60 = puVar4;
    local_60[1] = param_3;
  }
  else {
LAB_011d0952:
    *(undefined2 *)(param_1 + 2) = 0x1a;
  }
  return;
}


// ---- FUN_011d0bb0 @ 011d0bb0

/* WARNING: Type propagation algorithm not settling */

void FUN_011d0bb0(undefined8 *param_1,long *param_2,ulong *param_3,uint param_4,char param_5)

{
  byte *pbVar1;
  int *piVar2;
  bool bVar3;
  bool bVar4;
  ulong uVar5;
  undefined4 uVar6;
  undefined8 *puVar7;
  long lVar8;
  ulong uVar9;
  long lVar10;
  undefined *puVar11;
  long *plVar12;
  undefined7 uVar13;
  short sVar14;
  long lVar15;
  char cVar16;
  byte bVar17;
  ushort uVar18;
  uint uVar19;
  int iVar20;
  uint uVar21;
  byte bVar22;
  ushort uVar23;
  uint uVar24;
  ulong uVar25;
  ulong uVar26;
  ulong uVar27;
  undefined8 unaff_retaddr;
  undefined8 local_1a0 [2];
  short local_190;
  undefined *local_188;
  ulong uStack_180;
  ulong local_170;
  long local_168;
  long local_160;
  undefined *local_158;
  ulong uStack_150;
  ulong local_148;
  ulong local_140;
  uint local_134;
  undefined *local_130;
  short local_128;
  short local_120;
  ulong local_118;
  long local_110;
  undefined *local_108;
  ulong uStack_100;
  undefined **local_f8;
  long local_f0;
  ulong local_e8;
  ulong local_e0;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined1 uStack_cb;
  undefined2 uStack_ca;
  undefined *local_c8;
  ulong uStack_c0;
  undefined **local_b8;
  long local_b0;
  ulong local_a8;
  ulong local_a0;
  undefined4 local_98;
  undefined4 local_94;
  undefined8 *local_78;
  undefined8 *local_70;
  ulong *local_68;
  undefined1 local_60;
  undefined8 local_58;
  long local_50;
  undefined *local_48;
  long local_40;
  uint local_38;
  uint local_34;
  
  if (param_5 == '\0') {
    uVar26 = param_2[1];
LAB_011d0e91:
    local_34 = 0;
  }
  else {
    plVar12 = (long *)*param_2;
    uVar26 = param_2[1];
    pbVar1 = (byte *)param_2[3];
    if (pbVar1 == (byte *)0x0) {
      if (uVar26 != 0 && param_2[2] != 0) {
        plVar12 = plVar12 + 1;
        uVar25 = uVar26;
        do {
          if (*plVar12 == 0xc) {
            piVar2 = (int *)plVar12[-1];
            bVar4 = true;
            if ((piVar2 == (int *)"ZIG_PROGRESS") ||
               (((*piVar2 == 0x5f47495a && (piVar2[2] == 0x53534552)) && (piVar2[1] == 0x474f5250)))
               ) goto joined_r0x011d0e80;
          }
          plVar12 = plVar12 + 2;
          uVar25 = uVar25 - 1;
        } while (uVar25 != 0);
      }
LAB_011d0e79:
      bVar4 = false;
    }
    else {
      bVar22 = *pbVar1;
      cVar16 = '\x02' - (bVar22 < 0x11);
      if (bVar22 < 9) {
        cVar16 = '\0';
      }
      if (param_2[2] == 0) {
        plVar12 = (long *)0x8;
      }
      uVar19 = (int)(1L << ((ulong)bVar22 & 0x3f)) - 1;
      uVar25 = (ulong)(uVar19 & 0x486a5867);
      if (cVar16 != '\0') {
        if (cVar16 == '\x01') {
          uVar23 = *(ushort *)(pbVar1 + uVar25 * 4 + 4);
          if (uVar23 != 0xffff) {
            iVar20 = 0;
            do {
              if (plVar12[(ulong)uVar23 * 2 + 1] == 0xc) {
                piVar2 = (int *)plVar12[(ulong)uVar23 * 2];
                bVar4 = true;
                if ((piVar2 == (int *)"ZIG_PROGRESS") ||
                   (((*piVar2 == 0x5f47495a && (piVar2[2] == 0x53534552)) &&
                    (piVar2[1] == 0x474f5250)))) goto joined_r0x011d0e80;
              }
              uVar25 = (ulong)(uVar19 & iVar20 + 0x486a5868U);
              uVar23 = *(ushort *)(pbVar1 + uVar25 * 4 + 4);
              bVar4 = false;
              if ((uVar23 == 0xffff) ||
                 (uVar18 = (ushort)iVar20, iVar20 = iVar20 + 1,
                 *(ushort *)(pbVar1 + uVar25 * 4 + 6) <= uVar18)) goto joined_r0x011d0e80;
            } while( true );
          }
        }
        else {
          uVar24 = *(uint *)(pbVar1 + uVar25 * 8 + 4);
          if (uVar24 != 0xffffffff) {
            uVar21 = 0;
            do {
              if (plVar12[(ulong)uVar24 * 2 + 1] == 0xc) {
                piVar2 = (int *)plVar12[(ulong)uVar24 * 2];
                bVar4 = true;
                if ((piVar2 == (int *)"ZIG_PROGRESS") ||
                   (((*piVar2 == 0x5f47495a && (piVar2[2] == 0x53534552)) &&
                    (piVar2[1] == 0x474f5250)))) goto joined_r0x011d0e80;
              }
              uVar25 = (ulong)(uVar19 & uVar21 + 0x486a5868);
              uVar24 = *(uint *)(pbVar1 + uVar25 * 8 + 4);
              bVar4 = false;
              if ((uVar24 == 0xffffffff) ||
                 (bVar3 = *(uint *)(pbVar1 + uVar25 * 8 + 8) <= uVar21, uVar21 = uVar21 + 1, bVar3))
              goto joined_r0x011d0e80;
            } while( true );
          }
        }
        goto LAB_011d0e79;
      }
      bVar22 = pbVar1[uVar25 * 2 + 4];
      if (bVar22 != 0xff) {
        iVar20 = 0;
        do {
          if (plVar12[(ulong)bVar22 * 2 + 1] == 0xc) {
            piVar2 = (int *)plVar12[(ulong)bVar22 * 2];
            bVar4 = true;
            if ((piVar2 == (int *)"ZIG_PROGRESS") ||
               (((*piVar2 == 0x5f47495a && (piVar2[2] == 0x53534552)) && (piVar2[1] == 0x474f5250)))
               ) goto joined_r0x011d0e80;
          }
          uVar25 = (ulong)(uVar19 & iVar20 + 0x486a5868U);
          bVar22 = pbVar1[uVar25 * 2 + 4];
          bVar4 = false;
          if ((bVar22 == 0xff) ||
             (bVar17 = (byte)iVar20, iVar20 = iVar20 + 1, bVar4 = false,
             pbVar1[uVar25 * 2 + 5] <= bVar17)) goto joined_r0x011d0e80;
        } while( true );
      }
      bVar4 = false;
    }
joined_r0x011d0e80:
    uVar13 = (undefined7)((ulong)plVar12 >> 8);
    if ((int)param_4 < 0) {
      if (!bVar4) goto LAB_011d0e91;
      uVar26 = uVar26 - 1;
      local_34 = (uint)CONCAT71(uVar13,2);
    }
    else {
      local_34 = (uint)CONCAT71(uVar13,1);
      if (!bVar4) {
        uVar26 = uVar26 + 1;
        local_34 = (uint)CONCAT71(uVar13,3);
      }
    }
  }
  local_c8 = (undefined *)CONCAT71(local_c8._1_7_,0x1ffffffffffffffe < uVar26);
  local_70 = param_1;
  if (uVar26 < 0x1fffffffffffffff) {
    lVar15 = uVar26 * 8 + 8;
    local_68 = param_3;
    local_58 = unaff_retaddr;
    local_38 = param_4;
    if (lVar15 == 0) {
      puVar7 = (undefined8 *)0xfffffffffffffff8;
      *(undefined8 *)(uVar26 * 8 + -8) = 0;
      if ((char)local_34 != '\x03') goto LAB_011d0f11;
LAB_011d0f30:
      FUN_011d1a10(local_1a0,local_68,local_38);
      if (local_190 != 0) {
        *puVar7 = 0;
        lVar15 = 0;
        sVar14 = local_190;
LAB_011d173c:
        FUN_011d1960(puVar7,lVar15,local_68);
        *(short *)(local_70 + 2) = sVar14;
        return;
      }
      *puVar7 = local_1a0[0];
      local_50 = 1;
    }
    else {
      puVar7 = (undefined8 *)(**(code **)param_3[1])(*param_3,lVar15,3,unaff_retaddr);
      if (puVar7 == (undefined8 *)0x0) goto LAB_011d0ed3;
      puVar7[uVar26] = 0;
      if ((char)local_34 == '\x03') goto LAB_011d0f30;
LAB_011d0f11:
      local_50 = 0;
    }
    local_170 = param_2[1];
    if (local_170 != 0 && param_2[2] != 0) {
      local_160 = *param_2;
      local_168 = param_2[2] * 0x10 + local_160;
      uVar19 = -local_38;
      if ((int)-local_38 < 0) {
        uVar19 = local_38;
      }
      local_140 = (ulong)uVar19;
      local_118 = 0;
      local_134 = local_34 & 0xff;
      local_148 = uVar26;
      local_78 = puVar7;
LAB_011d0ff0:
      do {
        lVar8 = local_118 * 0x10;
        lVar15 = *(long *)(local_160 + lVar8);
        uVar25 = *(ulong *)(local_160 + 8 + lVar8);
        local_110 = *(long *)(local_168 + lVar8);
        uVar27 = *(ulong *)(local_168 + 8 + lVar8);
        uVar9 = FUN_011c9680(lVar15,uVar25,"ZIG_PROGRESS",0xc);
        if (((uVar9 & 1) == 0) || ((char)local_34 == '\0')) {
          local_158 = (undefined *)*local_68;
          uStack_150 = local_68[1];
          lVar8 = (**(code **)local_68[1])(*local_68,7,0,local_58);
          if (lVar8 == 0) goto LAB_011d1729;
          local_188 = (undefined *)((ulong)local_188 & 0xffffffffffffff00);
          local_c8 = local_158;
          uStack_c0 = uStack_150;
          local_b8 = &PTR_FUN_011b8270;
          local_a8 = 7;
          local_a0 = 0;
          local_98 = 0;
          local_94 = 0;
          local_b0 = lVar8;
          if (uVar25 != 0) {
            uVar26 = 0;
            do {
              while( true ) {
                lVar8 = uVar25 - uVar26;
                if (local_a8 < local_a0 + lVar8) break;
                FUN_011f4580(local_a0 + local_b0,(undefined *)(uVar26 + lVar15),lVar8);
                local_a0 = local_a0 + lVar8;
                uVar26 = uVar26 + lVar8;
                if (uVar25 <= uVar26) goto LAB_011d1337;
              }
              local_48 = (undefined *)(uVar26 + lVar15);
              local_40 = lVar8;
              (*(code *)*local_b8)(&local_130,&local_b8,&local_48,1,1);
              puVar7 = local_78;
              puVar11 = local_c8;
              uVar9 = uStack_c0;
              lVar8 = local_b0;
              uVar5 = local_a8;
              uVar6 = local_98;
              if (local_128 != 0) goto joined_r0x011d1705;
              uVar26 = uVar26 + (long)local_130;
            } while (uVar26 < uVar25);
          }
LAB_011d1337:
          do {
            if (local_a0 < local_a8) {
              *(undefined1 *)(local_b0 + local_a0) = 0x3d;
              local_a0 = local_a0 + 1;
              break;
            }
            local_48 = &DAT_0100f148;
            local_40 = 1;
            (*(code *)*local_b8)(&local_130,&local_b8,&local_48,1,1);
            puVar7 = local_78;
            puVar11 = local_c8;
            uVar9 = uStack_c0;
            lVar8 = local_b0;
            uVar5 = local_a8;
            uVar6 = local_98;
            if (local_128 != 0) goto joined_r0x011d1705;
          } while (local_130 == (undefined *)0x0);
          puVar7 = local_78;
          if (uVar27 != 0) {
            uVar26 = 0;
            lVar15 = local_110;
            do {
              while( true ) {
                lVar8 = uVar27 - uVar26;
                if (local_a8 < local_a0 + lVar8) break;
                FUN_011f4580(local_a0 + local_b0,(undefined *)(uVar26 + lVar15),lVar8);
                local_a0 = local_a0 + lVar8;
                uVar26 = uVar26 + lVar8;
                if (uVar27 <= uVar26) goto LAB_011d1480;
              }
              local_48 = (undefined *)(uVar26 + lVar15);
              local_40 = lVar8;
              (*(code *)*local_b8)(&local_130,&local_b8,&local_48,1,1);
              puVar11 = local_c8;
              uVar9 = uStack_c0;
              lVar8 = local_b0;
              uVar5 = local_a8;
              uVar6 = local_98;
              if (local_128 != 0) goto joined_r0x011d1705;
              uVar26 = uVar26 + (long)local_130;
              lVar15 = local_110;
            } while (uVar26 < uVar27);
          }
LAB_011d1480:
          FUN_011d17a0(&local_108,&local_c8);
          if (local_a8 != 0) {
            (**(code **)(uStack_c0 + 0x18))(local_c8,local_b0,local_a8,local_98,local_58);
          }
          puVar11 = local_108;
          sVar14 = (short)local_f8;
          if ((short)local_f8 == 0) goto LAB_011d1610;
          goto LAB_011d172d;
        }
        if (local_134 == 2) goto LAB_011d0fd2;
        local_188 = (undefined *)*local_68;
        uStack_180 = local_68[1];
        lVar8 = (**(code **)local_68[1])(*local_68,7,0,local_58);
        if (lVar8 == 0) goto LAB_011d1729;
        local_60 = 0;
        local_108 = local_188;
        uStack_100 = uStack_180;
        local_f8 = &PTR_FUN_011b8270;
        local_e8 = 7;
        local_e0 = 0;
        local_d8 = 0;
        local_d4 = 0;
        local_f0 = lVar8;
        if (uVar25 != 0) {
          uVar26 = 0;
          do {
            while( true ) {
              lVar8 = uVar25 - uVar26;
              if (local_e8 < local_e0 + lVar8) break;
              FUN_011f4580(local_e0 + local_f0,(undefined *)(uVar26 + lVar15),lVar8);
              local_e0 = local_e0 + lVar8;
              uVar26 = uVar26 + lVar8;
              if (uVar25 <= uVar26) goto LAB_011d117c;
            }
            local_48 = (undefined *)(uVar26 + lVar15);
            local_40 = lVar8;
            (*(code *)*local_f8)(&local_c8,&local_f8,&local_48,1,1);
            puVar7 = local_78;
            puVar11 = local_108;
            uVar9 = uStack_100;
            lVar8 = local_f0;
            uVar5 = local_e8;
            uVar6 = local_d8;
            if ((short)uStack_c0 != 0) goto joined_r0x011d1705;
            uVar26 = uVar26 + (long)local_c8;
          } while (uVar26 < uVar25);
        }
LAB_011d117c:
        do {
          if (local_e0 < local_e8) {
            *(undefined1 *)(local_f0 + local_e0) = 0x3d;
            local_e0 = local_e0 + 1;
            break;
          }
          local_48 = &DAT_0100f148;
          local_40 = 1;
          (*(code *)*local_f8)(&local_c8,&local_f8,&local_48,1,1);
          puVar7 = local_78;
          puVar11 = local_108;
          uVar9 = uStack_100;
          lVar8 = local_f0;
          uVar5 = local_e8;
          uVar6 = local_d8;
          if ((short)uStack_c0 != 0) goto joined_r0x011d1705;
        } while (local_c8 == (undefined *)0x0);
        lVar15 = 0x41;
        uVar26 = local_140;
        uVar25 = local_140;
        if (99 < (uint)local_140) {
          do {
            uVar26 = (uVar25 & 0xffffffff) / 100;
            *(undefined2 *)((long)&uStack_ca + lVar15) =
                 (&DAT_011b99d6)[(uint)((int)uVar25 + (int)((uVar25 & 0xffffffff) / 100) * -100)];
            lVar15 = lVar15 + -2;
            bVar4 = 9999 < uVar25;
            uVar25 = uVar26;
          } while (bVar4);
        }
        if ((uint)uVar26 < 10) {
          *(byte *)((long)&uStack_ca + lVar15 + 1) = (byte)uVar26 | 0x30;
          lVar15 = lVar15 + -1;
          if ((int)local_38 < 0) goto LAB_011d1595;
LAB_011d156c:
          lVar8 = lVar15 + -0x41;
          lVar10 = lVar15;
        }
        else {
          *(undefined2 *)((long)&uStack_ca + lVar15) = (&DAT_011b99d6)[uVar26];
          lVar15 = lVar15 + -2;
          if (-1 < (int)local_38) goto LAB_011d156c;
LAB_011d1595:
          *(undefined1 *)((long)&uStack_ca + lVar15 + 1) = 0x2d;
          lVar10 = lVar15 + -1;
          lVar8 = lVar15 + -0x42;
        }
        if (lVar8 != 0) {
          uVar26 = -lVar8;
          uVar25 = 0;
          do {
            while( true ) {
              puVar11 = (undefined *)((long)&local_c8 + uVar25 + lVar10);
              uVar27 = uVar26 - uVar25;
              if (local_e8 < local_e0 + uVar27) break;
              FUN_011f4580(local_e0 + local_f0,puVar11,uVar27);
              local_e0 = local_e0 + uVar27;
              uVar25 = uVar25 + uVar27;
              if (uVar26 <= uVar25) goto LAB_011d15ad;
            }
            local_158 = puVar11;
            uStack_150 = uVar27;
            (*(code *)*local_f8)(&local_48,&local_f8,&local_158,1,1);
            puVar7 = local_78;
            puVar11 = local_108;
            uVar9 = uStack_100;
            lVar8 = local_f0;
            uVar5 = local_e8;
            uVar6 = local_d8;
            if ((short)local_40 != 0) goto joined_r0x011d1705;
            uVar25 = uVar25 + (long)local_48;
          } while (uVar25 < uVar26);
        }
LAB_011d15ad:
        FUN_011d17a0(&local_130,&local_108);
        if (local_e8 != 0) {
          (**(code **)(uStack_100 + 0x18))(local_108,local_f0,local_e8,local_d8,local_58);
        }
        puVar11 = local_130;
        puVar7 = local_78;
        sVar14 = local_120;
        if (local_120 != 0) goto LAB_011d172d;
LAB_011d1610:
        puVar7[local_50] = puVar11;
        local_50 = local_50 + 1;
        local_118 = local_118 + 1;
        uVar26 = local_148;
      } while (local_118 < local_170);
    }
LAB_011d16e8:
    *(undefined2 *)(local_70 + 2) = 0;
    *local_70 = puVar7;
    local_70[1] = uVar26;
  }
  else {
LAB_011d0ed3:
    *(undefined2 *)(local_70 + 2) = 0x1a;
  }
  return;
LAB_011d0fd2:
  local_118 = local_118 + 1;
  if (local_170 <= local_118) goto LAB_011d16e8;
  goto LAB_011d0ff0;
joined_r0x011d1705:
  if (uVar5 != 0) {
    (**(code **)(uVar9 + 0x18))(puVar11,lVar8,uVar5,uVar6,local_58);
  }
LAB_011d1729:
  sVar14 = 0x1a;
LAB_011d172d:
  puVar7[local_50] = 0;
  lVar15 = local_50;
  goto LAB_011d173c;
}


// ---- FUN_011d17a0 @ 011d17a0

void FUN_011d17a0(long *param_1,undefined8 *param_2)

{
  undefined1 uVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  undefined1 auVar9 [16];
  undefined8 unaff_retaddr;
  
  uVar8 = param_2[5];
  lVar6 = param_2[3];
  uVar2 = param_2[4];
  if (uVar8 < uVar2) {
LAB_011d186d:
    *(undefined1 *)(lVar6 + uVar8) = 0;
    lVar7 = param_2[5];
    lVar6 = lVar7 + 1;
    param_2[5] = lVar6;
    uVar3 = param_2[3];
    lVar4 = param_2[4];
    uVar1 = *(undefined1 *)(param_2 + 6);
    if ((lVar4 == 0) ||
       (lVar5 = (**(code **)(param_2[1] + 0x10))(*param_2,uVar3,lVar4,uVar1,lVar6,unaff_retaddr),
       lVar5 == 0)) {
      lVar5 = (**(code **)param_2[1])(*param_2,lVar6,uVar1,unaff_retaddr);
      if (lVar5 == 0) {
        param_2[5] = param_2[5] + -1;
        goto LAB_011d193a;
      }
      FUN_011f4580(lVar5,uVar3,lVar6);
      if (lVar4 != 0) {
        (**(code **)(param_2[1] + 0x18))(*param_2,uVar3,lVar4,uVar1,unaff_retaddr);
      }
    }
    param_2[3] = 1;
    auVar9._0_12_ = ZEXT812(0);
    auVar9._12_4_ = 0;
    *(undefined1 (*) [16])(param_2 + 4) = auVar9;
    *(undefined2 *)(param_1 + 2) = 0;
    *param_1 = lVar5;
    param_1[1] = lVar7;
  }
  else {
    lVar7 = uVar8 + 1;
    uVar1 = *(undefined1 *)(param_2 + 6);
    if ((uVar2 != 0) &&
       (lVar4 = (**(code **)(param_2[1] + 0x10))(*param_2,lVar6,uVar2,uVar1,lVar7), lVar4 != 0)) {
LAB_011d185e:
      lVar6 = lVar4;
      param_2[3] = lVar6;
      param_2[4] = lVar7;
      uVar8 = param_2[5];
      goto LAB_011d186d;
    }
    lVar4 = (**(code **)param_2[1])(*param_2,lVar7,uVar1);
    if (lVar4 != 0) {
      FUN_011f4580(lVar4,lVar6,param_2[5]);
      if (uVar2 != 0) {
        (**(code **)(param_2[1] + 0x18))(*param_2,lVar6,uVar2,uVar1,unaff_retaddr);
      }
      goto LAB_011d185e;
    }
LAB_011d193a:
    *(undefined2 *)(param_1 + 2) = 0x1a;
  }
  return;
}


// ---- FUN_011d1960 @ 011d1960

void FUN_011d1960(long param_1,long param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  long lVar2;
  undefined8 uVar3;
  long lVar4;
  long lVar5;
  undefined8 unaff_retaddr;
  
  uVar1 = *param_3;
  lVar2 = param_3[1];
  if (param_2 != 0) {
    lVar5 = 0;
    do {
      uVar3 = *(undefined8 *)(param_1 + lVar5 * 8);
      lVar4 = FUN_011f4140(uVar3);
      (**(code **)(lVar2 + 0x18))(uVar1,uVar3,lVar4 + 1,0,unaff_retaddr);
      lVar5 = lVar5 + 1;
    } while (param_2 != lVar5);
  }
                    /* WARNING: Could not recover jumptable at 0x011d1a01. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(lVar2 + 0x18))(uVar1,param_1,param_2 * 8 + 8,3,unaff_retaddr);
  return;
}


// ---- FUN_011d1a10 @ 011d1a10

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_011d1a10(undefined8 *param_1,undefined8 *param_2,uint param_3)

{
  char *pcVar1;
  bool bVar2;
  undefined8 uVar3;
  long lVar4;
  uint uVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  undefined8 unaff_retaddr;
  undefined8 uStack_120;
  long local_118;
  short local_110;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 local_c0;
  undefined8 local_b8;
  long lStack_b0;
  char *local_a0;
  long local_98;
  char *local_90;
  long local_88;
  undefined8 local_80;
  undefined8 local_78;
  long lStack_70;
  undefined **local_68;
  long local_60;
  ulong local_58;
  long local_50;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined1 local_38;
  
  local_b8 = *param_2;
  lStack_b0 = param_2[1];
  uStack_120 = 0x11d1a4d;
  local_60 = (**(code **)param_2[1])(*param_2,0x10,0,unaff_retaddr);
  if (local_60 == 0) {
    *(undefined2 *)(param_1 + 2) = 0x1a;
    return;
  }
  local_38 = 0;
  local_78 = local_b8;
  lStack_70 = lStack_b0;
  local_68 = &PTR_FUN_011b8270;
  local_58 = 0x10;
  local_50 = 0;
  local_48 = 0;
  uStack_44 = 0;
  uVar9 = 0;
  do {
    while( true ) {
      lVar7 = 0xd - uVar9;
      if (local_58 < (ulong)(local_50 + lVar7)) break;
      uStack_120 = 0x11d1aca;
      FUN_011f4580(local_50 + local_60,"ZIG_PROGRESS=" + uVar9,lVar7);
      local_50 = local_50 + lVar7;
      uVar9 = uVar9 + lVar7;
      if (0xc < uVar9) goto LAB_011d1b2c;
    }
    uStack_120 = 0x11d1b0a;
    local_90 = "ZIG_PROGRESS=" + uVar9;
    local_88 = lVar7;
    (*(code *)*local_68)(&local_118,&local_68,&local_90,1,1);
    if (local_110 != 0) goto LAB_011d1cd8;
    uVar9 = uVar9 + local_118;
  } while (uVar9 < 0xd);
LAB_011d1b2c:
  uVar5 = -param_3;
  if ((int)-param_3 < 0) {
    uVar5 = param_3;
  }
  uVar9 = (ulong)uVar5;
  lVar7 = 0x41;
  uVar8 = uVar9;
  if (99 < uVar5) {
    do {
      uVar9 = uVar8 / 100;
      uVar5 = (uint)(uVar8 / 100);
      *(undefined2 *)((long)&uStack_120 + lVar7 + 6) = (&DAT_011b99d6)[(int)uVar8 + uVar5 * -100];
      lVar7 = lVar7 + -2;
      bVar2 = 9999 < uVar8;
      uVar8 = uVar9;
    } while (bVar2);
  }
  if (uVar5 < 10) {
    *(byte *)((long)&uStack_120 + lVar7 + 7) = (byte)uVar9 | 0x30;
    lVar7 = lVar7 + -1;
  }
  else {
    *(undefined2 *)((long)&uStack_120 + lVar7 + 6) = (&DAT_011b99d6)[uVar9];
    lVar7 = lVar7 + -2;
  }
  if ((int)param_3 < 0) {
    *(undefined1 *)((long)&uStack_120 + lVar7 + 7) = 0x2d;
    lVar4 = lVar7 + -1;
    lVar6 = lVar7 + -0x42;
  }
  else {
    lVar6 = lVar7 + -0x41;
    lVar4 = lVar7;
  }
  local_80 = unaff_retaddr;
  if (lVar6 != 0) {
    uVar9 = -lVar6;
    uVar8 = 0;
    do {
      while( true ) {
        pcVar1 = (char *)((long)&local_118 + uVar8 + lVar4);
        lVar7 = uVar9 - uVar8;
        if (local_58 < (ulong)(local_50 + lVar7)) break;
        uStack_120 = 0x11d1c74;
        FUN_011f4580(local_50 + local_60,pcVar1,lVar7);
        local_50 = local_50 + lVar7;
        uVar8 = uVar8 + lVar7;
        if (uVar9 <= uVar8) goto LAB_011d1be0;
      }
      uStack_120 = 0x11d1cb9;
      local_a0 = pcVar1;
      local_98 = lVar7;
      (*(code *)*local_68)(&local_90,&local_68,&local_a0,1,1);
      unaff_retaddr = local_80;
      if ((short)local_88 != 0) {
LAB_011d1cd8:
        if (local_58 != 0) {
          uStack_120 = 0x11d1cf6;
          (**(code **)(lStack_70 + 0x18))(local_78,local_60,local_58,local_48,unaff_retaddr);
        }
        uVar3 = _UNK_0100f138;
        *param_1 = _DAT_0100f130;
        param_1[1] = uVar3;
        param_1[2] = 0x1a;
        return;
      }
      uVar8 = uVar8 + (long)local_90;
    } while (uVar8 < uVar9);
  }
LAB_011d1be0:
  uStack_120 = 0x11d1bf0;
  FUN_011d17a0(&local_d0,&local_78);
  if (local_58 != 0) {
    uStack_120 = 0x11d1c0f;
    (**(code **)(lStack_70 + 0x18))(local_78,local_60,local_58,local_48,local_80);
  }
  param_1[2] = local_c0;
  *param_1 = local_d0;
  param_1[1] = uStack_c8;
  return;
}


// ---- FUN_011d1d10 @ 011d1d10

void FUN_011d1d10(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  FUN_011d0350(param_2,param_3);
  return;
}


// ---- FUN_011d1d20 @ 011d1d20

void FUN_011d1d20(undefined8 param_1,undefined4 *param_2)

{
  FUN_011d0590(*param_2);
  return;
}


// ---- FUN_011d1d30 @ 011d1d30

/* WARNING: Removing unreachable block (ram,0x011d1d5a) */
/* WARNING: Removing unreachable block (ram,0x011d1d6b) */

undefined8 FUN_011d1d30(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  undefined8 uVar1;
  
  syscall();
                    /* WARNING: Could not recover jumptable at 0x011d1d64. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar1 = (*(code *)PTR_LAB_01003150)(param_3);
  return uVar1;
}


// ---- FUN_011d1dc0 @ 011d1dc0

ulong FUN_011d1dc0(long param_1)

{
  long *plVar1;
  uint uVar2;
  ushort uVar3;
  ulong uVar4;
  long in_FS_OFFSET;
  undefined1 auVar5 [16];
  
  uVar3 = *(ushort *)(param_1 + 0x40);
  if (uVar3 == 0) {
    (**(code **)(*(long *)(param_1 + 0x18) + 0x10))(param_1 + 0x18);
    uVar3 = *(ushort *)(param_1 + 0x40);
  }
  uVar4 = (ulong)uVar3;
  if (uVar3 != 0) {
    if (uVar3 == 0x11) {
      uVar4 = *(ulong *)(in_FS_OFFSET + -0x40010);
      LOCK();
      *(ulong *)(uVar4 + 8) = *(ulong *)(uVar4 + 8) ^ 1;
      UNLOCK();
    }
    *(undefined2 *)(param_1 + 0x40) = 0;
  }
  *(undefined8 *)(param_1 + 0x20) = 1;
  auVar5._0_12_ = ZEXT812(0);
  auVar5._12_4_ = 0;
  *(undefined1 (*) [16])(param_1 + 0x28) = auVar5;
  plVar1 = (long *)(param_1 + 800);
  *plVar1 = *plVar1 + -1;
  if (*plVar1 == 0) {
    *(undefined4 *)(param_1 + 0x34c) = 0xffffffff;
    LOCK();
    uVar2 = *(uint *)(param_1 + 0x350);
    *(uint *)(param_1 + 0x350) = 0;
    uVar4 = (ulong)uVar2;
    UNLOCK();
    if (uVar2 == 2) {
      syscall();
      return 0xca;
    }
  }
  return uVar4;
}


// ---- FUN_011d1e60 @ 011d1e60

undefined1 (*) [32] FUN_011d1e60(undefined1 (*param_1) [32],long param_2)

{
  long lVar1;
  int iVar2;
  long in_FS_OFFSET;
  bool bVar3;
  undefined8 local_28;
  undefined8 uStack_20;
  short local_18;
  
  if (*(long *)(in_FS_OFFSET + -0x40010) == 0) {
    if (*(char *)(in_FS_OFFSET + -0x40004) == '\x01') {
      iVar2 = *(int *)(in_FS_OFFSET + -0x40008);
      if (*(int *)(param_2 + 0x34c) != iVar2) {
LAB_011d1ea5:
        LOCK();
        bVar3 = *(int *)(param_2 + 0x350) == 0;
        if (bVar3) {
          *(int *)(param_2 + 0x350) = 1;
        }
        UNLOCK();
        if (!bVar3) {
          *param_1 = ZEXT1232(ZEXT812(0));
          return param_1;
        }
        *(int *)(param_2 + 0x34c) = iVar2;
        lVar1 = 1;
        goto LAB_011d1eff;
      }
    }
    else {
      syscall();
      iVar2 = 0xba;
      *(undefined4 *)(in_FS_OFFSET + -0x40008) = 0xba;
      *(undefined1 *)(in_FS_OFFSET + -0x40004) = 1;
      if (*(int *)(param_2 + 0x34c) != 0xba) goto LAB_011d1ea5;
    }
  }
  else {
    iVar2 = *(int *)(*(long *)(in_FS_OFFSET + -0x40010) + 0x218);
    if (*(int *)(param_2 + 0x34c) != iVar2) goto LAB_011d1ea5;
  }
  lVar1 = *(long *)(param_2 + 800) + 1;
LAB_011d1eff:
  *(long *)(param_2 + 800) = lVar1;
  FUN_011d2070(&local_28);
  if (local_18 == 0) {
    *(undefined2 *)(*param_1 + 0x18) = 0;
    *(undefined8 *)*param_1 = local_28;
    *(undefined8 *)(*param_1 + 8) = uStack_20;
    (*param_1)[0x10] = 1;
  }
  else {
    *(short *)(*param_1 + 0x18) = local_18;
  }
  return param_1;
}


// ---- FUN_011d1f40 @ 011d1f40

undefined8 * FUN_011d1f40(undefined8 *param_1,long param_2,undefined8 param_3,ulong param_4)

{
  int iVar1;
  long lVar2;
  int iVar3;
  long in_FS_OFFSET;
  bool bVar4;
  undefined8 local_38;
  undefined8 uStack_30;
  undefined8 local_28;
  undefined1 local_1c;
  
  if (*(long *)(in_FS_OFFSET + -0x40010) == 0) {
    if (*(char *)(in_FS_OFFSET + -0x40004) == '\x01') {
      iVar3 = *(int *)(in_FS_OFFSET + -0x40008);
      if (*(int *)(param_2 + 0x34c) != iVar3) {
LAB_011d1f8b:
        LOCK();
        iVar1 = *(int *)(param_2 + 0x350);
        bVar4 = iVar1 == 0;
        if (bVar4) {
          *(int *)(param_2 + 0x350) = 1;
          iVar1 = 0;
        }
        UNLOCK();
        local_1c = !bVar4;
        param_4 = (ulong)!bVar4;
        if (!bVar4) {
          if (iVar1 == 2) {
            param_4 = 0x11d2035;
            syscall();
          }
          while( true ) {
            LOCK();
            iVar1 = *(int *)(param_2 + 0x350);
            *(int *)(param_2 + 0x350) = 2;
            UNLOCK();
            if (iVar1 == 0) break;
            param_4 = 0x11d2051;
            syscall();
          }
        }
        *(int *)(param_2 + 0x34c) = iVar3;
        lVar2 = 1;
        goto LAB_011d1fe2;
      }
    }
    else {
      param_4 = 0x11d1fba;
      syscall();
      iVar3 = 0xba;
      *(undefined4 *)(in_FS_OFFSET + -0x40008) = 0xba;
      *(undefined1 *)(in_FS_OFFSET + -0x40004) = 1;
      if (*(int *)(param_2 + 0x34c) != 0xba) goto LAB_011d1f8b;
    }
  }
  else {
    iVar3 = *(int *)(*(long *)(in_FS_OFFSET + -0x40010) + 0x218);
    if (*(int *)(param_2 + 0x34c) != iVar3) goto LAB_011d1f8b;
  }
  lVar2 = *(long *)(param_2 + 800) + 1;
LAB_011d1fe2:
  *(long *)(param_2 + 800) = lVar2;
  FUN_011d2070(&local_38,param_2,param_3,param_4);
  param_1[2] = local_28;
  *param_1 = local_38;
  param_1[1] = uStack_30;
  return param_1;
}


// ---- FUN_011d2070 @ 011d2070

/* WARNING: Removing unreachable block (ram,0x011d217d) */
/* WARNING: Removing unreachable block (ram,0x011d2190) */
/* WARNING: Removing unreachable block (ram,0x011d2197) */
/* WARNING: Removing unreachable block (ram,0x011d219f) */
/* WARNING: Removing unreachable block (ram,0x011d2208) */
/* WARNING: Removing unreachable block (ram,0x011d220e) */
/* WARNING: Heritage AFTER dead removal. Example location: r0x0100149e : 0x011d2213 */
/* WARNING: Restarted to delay deadcode elimination for space: ram */

void FUN_011d2070(long *param_1,long param_2,byte *param_3)

{
  char cVar1;
  uint *puVar2;
  byte bVar3;
  uint uVar4;
  ulong uVar5;
  ulong uVar6;
  char *pcVar7;
  char *pcVar8;
  long lVar9;
  byte *pbVar10;
  long in_FS_OFFSET;
  bool bVar11;
  
  if (*(char *)(param_2 + 0x357) == '\x01') goto LAB_011d2260;
  *(long *)param_2 = param_2;
  *(undefined ***)(param_2 + 8) = &PTR_FUN_0100e020;
  *(undefined1 *)(param_2 + 0x357) = 1;
  FUN_011cd090(param_2);
  if (param_3[1] == 0) {
    pcVar7 = "";
    if (*(char *)(param_2 + 799) != '\0') {
      pcVar7 = "\x01\x01";
    }
    pcVar8 = "";
    if (*(char *)(param_2 + 0x31e) == '\0') {
      pcVar8 = pcVar7;
    }
    cVar1 = pcVar8[1];
    if ((cVar1 == '\0') || (uVar4 = DAT_01001470, *pcVar8 != '\0')) {
      lVar9 = *(long *)(in_FS_OFFSET + -0x40010);
      if ((lVar9 == 0) || ((*(byte *)(lVar9 + 0x21c) & 1) != 0)) {
LAB_011d213b:
        lVar9 = 0;
      }
      else {
        uVar5 = *(ulong *)(lVar9 + 8);
        do {
          LOCK();
          uVar6 = *(ulong *)(lVar9 + 8);
          bVar11 = uVar5 == uVar6;
          if (bVar11) {
            *(ulong *)(lVar9 + 8) = uVar5 | 3;
            uVar6 = uVar5;
          }
          UNLOCK();
          uVar5 = uVar6;
        } while (!bVar11);
        if ((uVar6 & 7) != 0) {
          if (((uint)uVar6 & 7) == 6) {
            uVar4 = 0x11;
            goto LAB_011d21ab;
          }
          goto LAB_011d213b;
        }
      }
      if (lVar9 == 0) {
        syscall();
      }
      else {
        syscall();
        LOCK();
        *(ulong *)(lVar9 + 8) = *(ulong *)(lVar9 + 8) ^ 3;
        UNLOCK();
      }
      puVar2 = &DAT_01001470;
      if ((DAT_0100149c & 0x10000) != 0) {
        puVar2 = &DAT_0100149c;
      }
      uVar4 = DAT_0100149c;
      if ((*puVar2 & 0x10000) == 0) {
        uVar4 = DAT_01001470;
        if (*pcVar8 != '\0') {
          uVar4 = DAT_0100149c;
        }
        if (cVar1 == '\0') {
          uVar4 = DAT_01001470;
        }
      }
    }
    if ((short)uVar4 != 0) {
LAB_011d21ab:
      *(short *)(param_1 + 2) = (short)uVar4;
      return;
    }
    bVar3 = (byte)(uVar4 >> 0x10);
  }
  else {
    bVar3 = *param_3;
  }
  *(byte *)(param_2 + 0x356) = bVar3 & 3;
LAB_011d2260:
  *(undefined2 *)(param_1 + 2) = 0;
  *param_1 = param_2;
  pbVar10 = (byte *)(param_2 + 0x356);
  if (param_3[1] != 0) {
    pbVar10 = param_3;
  }
  *(byte *)(param_1 + 1) = *pbVar10;
  return;
}


// ---- FUN_011d2290 @ 011d2290

undefined8 *
FUN_011d2290(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 local_28;
  short local_20;
  undefined4 local_14;
  
  local_14 = 0xffffff9c;
  FUN_011d7140(&local_28,param_2,&local_14,"/proc/self/exe",0xe,param_3,param_4);
  if (local_20 == 0) {
    *param_1 = local_28;
    local_20 = 0;
  }
  *(short *)(param_1 + 1) = local_20;
  return param_1;
}


// ---- FUN_011d22f0 @ 011d22f0

undefined8 * FUN_011d22f0(undefined8 *param_1,undefined8 param_2,undefined8 param_3)

{
  undefined8 local_1c;
  undefined4 local_14;
  
  FUN_011d8d90(&local_1c,param_2,&DAT_01001494,"/proc/self/exe",0xe,param_3);
  *(undefined4 *)(param_1 + 1) = local_14;
  *param_1 = local_1c;
  return param_1;
}


// ---- FUN_011d2330 @ 011d2330

/* WARNING: Removing unreachable block (ram,0x011d24a0) */

undefined8 FUN_011d2330(undefined8 param_1,long param_2)

{
  undefined8 uVar1;
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  undefined8 uVar5;
  long lVar6;
  long lVar7;
  long in_FS_OFFSET;
  bool bVar8;
  
  if (*(char *)(param_2 + 0x20) != '\0') {
    return 0;
  }
  uVar5 = *(undefined8 *)(param_2 + 0x18);
  uVar1 = *(undefined8 *)(param_2 + 8);
  lVar2 = *(long *)(param_2 + 0x10);
  lVar7 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar7 != 0) && ((*(byte *)(lVar7 + 0x21c) & 1) == 0)) {
    uVar3 = *(ulong *)(lVar7 + 8);
    do {
      LOCK();
      uVar4 = *(ulong *)(lVar7 + 8);
      bVar8 = uVar3 == uVar4;
      if (bVar8) {
        *(ulong *)(lVar7 + 8) = uVar3 | 3;
        uVar4 = uVar3;
      }
      UNLOCK();
      uVar3 = uVar4;
    } while (!bVar8);
    if ((uVar4 & 7) == 0) goto LAB_011d23a9;
    if (((uint)uVar4 & 7) == 6) {
      return 0x11;
    }
  }
  lVar7 = 0;
LAB_011d23a9:
  if (lVar2 == 0) {
    if (lVar7 != 0) {
      LOCK();
      *(ulong *)(lVar7 + 8) = *(ulong *)(lVar7 + 8) ^ 3;
      UNLOCK();
    }
    return 0;
  }
  lVar6 = (long)(int)uVar5;
  if (lVar7 != 0) {
    syscall();
                    /* WARNING: Could not recover jumptable at 0x011d240c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar5 = (*(code *)PTR_LAB_01003268)(lVar6,uVar1,lVar2);
    return uVar5;
  }
  syscall();
                    /* WARNING: Could not recover jumptable at 0x011d2499. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar5 = (*(code *)PTR_LAB_01003640)(lVar6,uVar1,lVar2);
  return uVar5;
}


// ---- FUN_011d2510 @ 011d2510

undefined8 FUN_011d2510(undefined8 param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  
  if (*(char *)(param_2 + 4) != '\0') {
    return 0;
  }
  uVar1 = FUN_011d2540(*(undefined4 *)(param_2 + 3),param_2[1],param_2[2],*param_2);
  return uVar1;
}


// ---- FUN_011d2540 @ 011d2540

/* WARNING: Removing unreachable block (ram,0x011d269e) */
/* WARNING: Removing unreachable block (ram,0x011d26d7) */

ulong FUN_011d2540(int param_1,undefined8 param_2,long param_3,undefined8 param_4)

{
  ulong uVar1;
  ulong uVar2;
  undefined8 unaff_R14;
  long lVar3;
  long in_FS_OFFSET;
  bool bVar4;
  
  lVar3 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar3 == 0) || ((*(byte *)(lVar3 + 0x21c) & 1) != 0)) {
LAB_011d2594:
    lVar3 = 0;
  }
  else {
    uVar2 = *(ulong *)(lVar3 + 8);
    do {
      LOCK();
      uVar1 = *(ulong *)(lVar3 + 8);
      bVar4 = uVar2 == uVar1;
      if (bVar4) {
        *(ulong *)(lVar3 + 8) = uVar2 | 3;
        uVar1 = uVar2;
      }
      UNLOCK();
      uVar2 = uVar1;
    } while (!bVar4);
    if ((uVar1 & 7) != 0) {
      uVar2 = CONCAT62((int6)((ulong)unaff_R14 >> 0x10),0x11);
      if (((uint)uVar1 & 7) == 6) goto LAB_011d26dd;
      goto LAB_011d2594;
    }
  }
  if (param_3 != 0) {
    if (lVar3 == 0) {
      syscall();
                    /* WARNING: Could not recover jumptable at 0x011d268d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar2 = (*(code *)PTR_LAB_01003d90)((long)param_1,param_2,param_3,0,param_4);
      return uVar2;
    }
    syscall();
                    /* WARNING: Could not recover jumptable at 0x011d25e5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (*(code *)PTR_LAB_01003a18)();
    return uVar2;
  }
  if (lVar3 == 0) {
    uVar2 = 0;
  }
  else {
    LOCK();
    *(ulong *)(lVar3 + 8) = *(ulong *)(lVar3 + 8) ^ 3;
    UNLOCK();
    uVar2 = 0;
  }
LAB_011d26dd:
  return uVar2 & 0xffffffff;
}


// ---- FUN_011d2710 @ 011d2710

/* WARNING: Removing unreachable block (ram,0x011d28ba) */
/* WARNING: Removing unreachable block (ram,0x011d28b4) */

undefined8 FUN_011d2710(long param_1,long param_2,ulong param_3)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  ulong uVar4;
  ulong uVar5;
  long lVar6;
  long in_FS_OFFSET;
  bool bVar7;
  undefined8 unaff_retaddr;
  
  uVar1 = *(undefined8 *)(param_2 + 8);
  uVar4 = *(ulong *)(param_2 + 0x10);
  if (*(char *)(param_2 + 0x20) == '\0') {
    uVar2 = *(undefined8 *)(param_1 + 0x328);
    puVar3 = *(undefined8 **)(param_1 + 0x330);
    lVar6 = (*(code *)puVar3[2])(uVar2,uVar1,uVar4,0xc,param_3);
    if (lVar6 == 0) {
      lVar6 = (*(code *)*puVar3)(uVar2,param_3,0xc,unaff_retaddr);
      if (lVar6 == 0) {
        return 0x1a;
      }
      uVar5 = uVar4;
      if (param_3 < uVar4) {
        uVar5 = param_3;
      }
      FUN_011f4580(lVar6,uVar1,uVar5);
      *(long *)(param_2 + 8) = lVar6;
      *(ulong *)(param_2 + 0x10) = param_3;
      (*(code *)puVar3[3])(uVar2,uVar1,uVar4,0xc,unaff_retaddr);
      return 0;
    }
  }
  else {
    if (((uVar4 + 0xfff ^ param_3 + 0xfff) & 0xfffffffffffff000) == 0) goto LAB_011d28a6;
    lVar6 = *(long *)(in_FS_OFFSET + -0x40010);
    if ((lVar6 == 0) || ((*(byte *)(lVar6 + 0x21c) & 1) != 0)) {
LAB_011d27b0:
      syscall();
    }
    else {
      uVar4 = *(ulong *)(lVar6 + 8);
      do {
        LOCK();
        uVar5 = *(ulong *)(lVar6 + 8);
        bVar7 = uVar4 == uVar5;
        if (bVar7) {
          *(ulong *)(lVar6 + 8) = uVar4 | 3;
          uVar5 = uVar4;
        }
        UNLOCK();
        uVar4 = uVar5;
      } while (!bVar7);
      if ((uVar5 & 7) != 0) {
        if (((uint)uVar5 & 7) != 7) {
          return 0x11;
        }
        goto LAB_011d27b0;
      }
      syscall();
      LOCK();
      *(ulong *)(lVar6 + 8) = *(ulong *)(lVar6 + 8) ^ 3;
      UNLOCK();
    }
    lVar6 = 0x19;
  }
  *(long *)(param_2 + 8) = lVar6;
LAB_011d28a6:
  *(ulong *)(param_2 + 0x10) = param_3;
  return 0;
}


// ---- FUN_011d28e0 @ 011d28e0

undefined8 FUN_011d28e0(long param_1,long param_2)

{
  code *UNRECOVERED_JUMPTABLE;
  undefined8 in_RAX;
  undefined8 uVar1;
  undefined8 unaff_retaddr;
  
  if (*(char *)(param_2 + 0x20) == '\0') {
    UNRECOVERED_JUMPTABLE = *(code **)(*(long *)(param_1 + 0x330) + 0x18);
                    /* WARNING: Could not recover jumptable at 0x011d2927. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*UNRECOVERED_JUMPTABLE)
                      (*(undefined8 *)(param_1 + 0x328),*(undefined8 *)(param_2 + 8),
                       *(long *)(param_2 + 0x10),0xc,unaff_retaddr,UNRECOVERED_JUMPTABLE);
    return uVar1;
  }
  if (*(long *)(param_2 + 0x10) != 0) {
    syscall();
    return 0xb;
  }
  return in_RAX;
}


// ---- FUN_011d2930 @ 011d2930

/* WARNING: Removing unreachable block (ram,0x011d2aa7) */
/* WARNING: Removing unreachable block (ram,0x011d2ab4) */
/* WARNING: Removing unreachable block (ram,0x011d2ab9) */
/* WARNING: Removing unreachable block (ram,0x011d2b43) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * FUN_011d2930(long *param_1,long param_2,long *param_3,long *param_4,undefined8 param_5,
                   undefined8 param_6)

{
  byte bVar1;
  long lVar2;
  long lVar3;
  undefined8 uVar4;
  undefined8 *puVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  short sVar9;
  long lVar10;
  ulong uVar11;
  ulong uVar12;
  undefined2 uVar13;
  long in_FS_OFFSET;
  bool bVar14;
  undefined8 unaff_retaddr;
  
  lVar2 = *param_4;
  lVar3 = param_4[1];
  bVar1 = *(byte *)((long)param_4 + 0x11);
  if (*(char *)(param_2 + 0x358) == '\x01') {
    uVar4 = *(undefined8 *)(param_2 + 0x328);
    puVar5 = *(undefined8 **)(param_2 + 0x330);
    lVar10 = (*(code *)*puVar5)(uVar4,lVar2,0xc,unaff_retaddr,param_5,param_6);
    lVar8 = _UNK_0100f1d0;
    lVar7 = _UNK_0100f1c8;
    lVar6 = _UNK_0100f1c0;
    if (lVar10 == 0) {
      param_1[2] = _DAT_0100f1b8;
      param_1[3] = lVar6;
      param_1[4] = lVar7;
      param_1[5] = lVar8;
      lVar6 = _UNK_0100f1c0;
      lVar3 = _DAT_0100f1b8;
      lVar2 = _UNK_0100f1b0;
      *param_1 = _DAT_0100f1a8;
      param_1[1] = lVar2;
      param_1[2] = lVar3;
      param_1[3] = lVar6;
      return param_1;
    }
    if (((bVar1 & 1) == 0) && (sVar9 = FUN_011d2540((int)*param_3,lVar10,lVar2,lVar3), sVar9 != 0))
    {
      (*(code *)puVar5[3])(uVar4,lVar10,lVar2,0xc,unaff_retaddr);
      *(short *)(param_1 + 5) = sVar9;
      return param_1;
    }
    *(undefined2 *)(param_1 + 5) = 0;
    param_1[3] = *param_3;
    *param_1 = lVar3;
    param_1[1] = lVar10;
    param_1[2] = lVar2;
    *(undefined1 *)(param_1 + 4) = 0;
    return param_1;
  }
  if (lVar3 < 0) {
    lVar2 = *(long *)(in_FS_OFFSET + -0x40010);
    if ((lVar2 != 0) && ((*(byte *)(lVar2 + 0x21c) & 1) == 0)) {
      uVar11 = *(ulong *)(lVar2 + 8);
      do {
        LOCK();
        uVar12 = *(ulong *)(lVar2 + 8);
        bVar14 = uVar11 == uVar12;
        if (bVar14) {
          *(ulong *)(lVar2 + 8) = uVar11 | 3;
          uVar12 = uVar11;
        }
        UNLOCK();
        uVar11 = uVar12;
      } while (!bVar14);
      uVar13 = 0x11;
      if (((uint)uVar12 & 7) == 6) goto LAB_011d2b47;
    }
    uVar13 = 0x16;
LAB_011d2b47:
    *(undefined2 *)(param_1 + 5) = uVar13;
    return param_1;
  }
  lVar6 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar6 != 0) && ((*(byte *)(lVar6 + 0x21c) & 1) == 0)) {
    uVar11 = *(ulong *)(lVar6 + 8);
    do {
      LOCK();
      uVar12 = *(ulong *)(lVar6 + 8);
      bVar14 = uVar11 == uVar12;
      if (bVar14) {
        *(ulong *)(lVar6 + 8) = uVar11 | 3;
        uVar12 = uVar11;
      }
      UNLOCK();
      uVar11 = uVar12;
    } while (!bVar14);
    if ((uVar12 & 7) == 0) {
      syscall();
      LOCK();
      *(ulong *)(lVar6 + 8) = *(ulong *)(lVar6 + 8) ^ 3;
      UNLOCK();
      goto LAB_011d2a6f;
    }
    if (((uint)uVar12 & 7) != 7) {
      uVar13 = 0x11;
      goto LAB_011d2b47;
    }
  }
  syscall();
LAB_011d2a6f:
  lVar6 = *param_3;
  *(undefined2 *)(param_1 + 5) = 0;
  *param_1 = lVar3;
  param_1[1] = 9;
  param_1[2] = lVar2;
  param_1[3] = lVar6;
  *(undefined1 *)(param_1 + 4) = 1;
  return param_1;
}


// ---- FUN_011d2b90 @ 011d2b90

short FUN_011d2b90(undefined8 param_1,undefined4 *param_2,undefined4 *param_3,long param_4,
                  ulong param_5,byte *param_6)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 auVar3 [32];
  byte bVar4;
  short sVar5;
  long lVar6;
  ulong uVar7;
  ulong uVar8;
  undefined1 local_1062 [4096];
  undefined1 local_62 [26];
  undefined8 local_48 [3];
  byte local_29;
  
  uVar1 = *param_2;
  uVar2 = *param_3;
  local_29 = *param_6;
  lVar6 = 0;
  uVar7 = param_5;
  if (0x1f < param_5) {
    do {
      auVar3 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])(param_4 + lVar6));
      if ((((((((((((((((((((((((((((((((SUB321(auVar3 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar3 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar3 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar3 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar3 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar3 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar3 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar3 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar3 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar3 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar3 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar3 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar3 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar3 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar3 >> 0x77,0) & 1) != 0) || SUB321(auVar3 >> 0x7f,0) != '\0')
                        || (SUB321(auVar3 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar3 >> 0x8f,0) & 1) != 0) || (SUB321(auVar3 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar3 >> 0x9f,0) & 1) != 0) || (SUB321(auVar3 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar3 >> 0xaf,0) & 1) != 0) || (SUB321(auVar3 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar3 >> 0xbf,0) != '\0') || (SUB321(auVar3 >> 199,0) & 1) != 0) ||
               (SUB321(auVar3 >> 0xcf,0) & 1) != 0) || (SUB321(auVar3 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar3 >> 0xdf,0) & 1) != 0) || (SUB321(auVar3 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar3 >> 0xef,0) & 1) != 0) || (SUB321(auVar3 >> 0xf7,0) & 1) != 0) ||
          auVar3[0x1f] < '\0') {
        return 0x32;
      }
      lVar6 = lVar6 + 0x20;
      uVar7 = uVar7 - 0x20;
    } while (0x1f < uVar7);
  }
  if (uVar7 != 0) {
    uVar8 = 0;
    do {
      if (*(char *)(lVar6 + param_4 + uVar8) == '\0') {
        return 0x32;
      }
      uVar8 = uVar8 + 1;
    } while (uVar7 != uVar8);
  }
  sVar5 = 0x31;
  if (param_5 < 0x1000) {
    FUN_011f4580(local_1062,param_4,param_5);
    bVar4 = local_29;
    local_1062[param_5] = 0;
    sVar5 = FUN_011d2f80(uVar1,"",uVar2,local_1062,(local_29 + 4) * 0x400);
    if ((sVar5 == 0x2d) && (sVar5 = 0x2d, bVar4 == 0)) {
      FUN_011d2cd0(local_48,local_62,0x1a,uVar1);
      sVar5 = FUN_011d2f80(0xffffff9c,local_48[0],uVar2,local_1062,0x400);
    }
  }
  return sVar5;
}


// ---- FUN_011d2cd0 @ 011d2cd0

/* WARNING: Type propagation algorithm not settling */

void FUN_011d2cd0(long *param_1,long param_2,ulong param_3,uint param_4)

{
  char *pcVar1;
  bool bVar2;
  long lVar3;
  uint uVar4;
  ulong uVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  undefined8 uStack_c0;
  long local_b8;
  short local_b0;
  char *local_70;
  long local_68;
  char *local_60;
  long local_58;
  undefined **local_50;
  long local_48;
  ulong local_40;
  ulong local_38;
  
  local_50 = &PTR_FUN_0100f1e8;
  local_38 = 0;
  uVar5 = 0;
  local_48 = param_2;
  local_40 = param_3;
  do {
    while( true ) {
      lVar8 = 0xe - uVar5;
      if (local_40 < local_38 + lVar8) break;
      uStack_c0 = 0x11d2d3b;
      FUN_011f4580(local_38 + local_48,"/proc/self/fd/" + uVar5,lVar8);
      local_38 = local_38 + lVar8;
      uVar5 = uVar5 + lVar8;
      if (0xd < uVar5) goto LAB_011d2d96;
    }
    uStack_c0 = 0x11d2d74;
    local_60 = "/proc/self/fd/" + uVar5;
    local_58 = lVar8;
    (*(code *)*local_50)(&local_b8,&local_50,&local_60,1,1);
    if (local_b0 != 0) goto LAB_011d2f65;
    uVar5 = uVar5 + local_b8;
  } while (uVar5 < 0xe);
LAB_011d2d96:
  uVar4 = -param_4;
  if ((int)-param_4 < 0) {
    uVar4 = param_4;
  }
  uVar5 = (ulong)uVar4;
  lVar8 = 0x41;
  uVar7 = uVar5;
  if (99 < uVar4) {
    do {
      uVar5 = uVar7 / 100;
      uVar4 = (uint)(uVar7 / 100);
      *(undefined2 *)((long)&uStack_c0 + lVar8 + 6) = (&DAT_011b99d6)[(int)uVar7 + uVar4 * -100];
      lVar8 = lVar8 + -2;
      bVar2 = 9999 < uVar7;
      uVar7 = uVar5;
    } while (bVar2);
  }
  if (uVar4 < 10) {
    *(byte *)((long)&uStack_c0 + lVar8 + 7) = (byte)uVar5 | 0x30;
    lVar8 = lVar8 + -1;
  }
  else {
    *(undefined2 *)((long)&uStack_c0 + lVar8 + 6) = (&DAT_011b99d6)[uVar5];
    lVar8 = lVar8 + -2;
  }
  if ((int)param_4 < 0) {
    *(undefined1 *)((long)&uStack_c0 + lVar8 + 7) = 0x2d;
    lVar3 = lVar8 + -1;
    lVar6 = lVar8 + -0x42;
  }
  else {
    lVar6 = lVar8 + -0x41;
    lVar3 = lVar8;
  }
  if (lVar6 != 0) {
    uVar7 = -lVar6;
    uVar5 = 0;
    do {
      while( true ) {
        pcVar1 = (char *)((long)&local_b8 + uVar5 + lVar3);
        lVar8 = uVar7 - uVar5;
        if (local_40 < local_38 + lVar8) break;
        uStack_c0 = 0x11d2f14;
        FUN_011f4580(local_38 + local_48,pcVar1,lVar8);
        local_38 = local_38 + lVar8;
        uVar5 = uVar5 + lVar8;
        if (uVar7 <= uVar5) goto LAB_011d2e44;
      }
      uStack_c0 = 0x11d2f4d;
      local_70 = pcVar1;
      local_68 = lVar8;
      (*(code *)*local_50)(&local_60,&local_50,&local_70,1,1);
      if ((short)local_58 != 0) goto LAB_011d2f65;
      uVar5 = uVar5 + (long)local_60;
    } while (uVar5 < uVar7);
  }
LAB_011d2e44:
  do {
    if (local_38 < local_40) {
      *(undefined1 *)(local_48 + local_38) = 0;
      goto LAB_011d2eb7;
    }
    local_60 = "";
    local_58 = 1;
    uStack_c0 = 0x11d2e8a;
    (*(code *)*local_50)(&local_b8,&local_50,&local_60,1,1);
    if (local_b0 != 0) {
LAB_011d2f65:
      *(undefined2 *)(param_1 + 2) = 8;
      return;
    }
  } while (local_b8 == 0);
  local_38 = local_38 - 1;
LAB_011d2eb7:
  *(undefined2 *)(param_1 + 2) = 0;
  *param_1 = local_48;
  param_1[1] = local_38;
  return;
}


// ---- FUN_011d2f70 @ 011d2f70

undefined8 FUN_011d2f70(void)

{
  return 0;
}


// ---- FUN_011d2f80 @ 011d2f80

/* WARNING: Removing unreachable block (ram,0x011d3069) */
/* WARNING: Removing unreachable block (ram,0x011d306f) */

undefined8
FUN_011d2f80(int param_1,undefined8 param_2,int param_3,undefined8 param_4,undefined4 param_5)

{
  ulong uVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long in_FS_OFFSET;
  bool bVar5;
  
  lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar4 != 0) && ((*(byte *)(lVar4 + 0x21c) & 1) == 0)) {
    uVar1 = *(ulong *)(lVar4 + 8);
    do {
      LOCK();
      uVar2 = *(ulong *)(lVar4 + 8);
      bVar5 = uVar1 == uVar2;
      if (bVar5) {
        *(ulong *)(lVar4 + 8) = uVar1 | 3;
        uVar2 = uVar1;
      }
      UNLOCK();
      uVar1 = uVar2;
    } while (!bVar5);
    if ((uVar2 & 7) == 0) goto LAB_011d2fd9;
    if (((uint)uVar2 & 7) == 6) {
      return 0x11;
    }
  }
  lVar4 = 0;
LAB_011d2fd9:
  if (lVar4 == 0) {
    syscall();
                    /* WARNING: Could not recover jumptable at 0x011d305f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar3 = (*(code *)PTR_LAB_010044e0)((long)param_1,param_2,(long)param_3,0x109,param_5);
    return uVar3;
  }
  syscall();
                    /* WARNING: Could not recover jumptable at 0x011d3006. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar3 = (*(code *)PTR_LAB_01004108)();
  return uVar3;
}


// ---- FUN_011d3150 @ 011d3150

/* WARNING: Removing unreachable block (ram,0x011d3275) */
/* WARNING: Removing unreachable block (ram,0x011d327b) */
/* WARNING: Removing unreachable block (ram,0x011d31f3) */
/* WARNING: Removing unreachable block (ram,0x011d3200) */
/* WARNING: Removing unreachable block (ram,0x011d3207) */
/* WARNING: Removing unreachable block (ram,0x011d320f) */
/* WARNING: Removing unreachable block (ram,0x011d3286) */
/* WARNING: Removing unreachable block (ram,0x011d32e9) */
/* WARNING: Removing unreachable block (ram,0x011d32bf) */
/* WARNING: Removing unreachable block (ram,0x011d32b1) */
/* WARNING: Removing unreachable block (ram,0x011d32db) */
/* WARNING: Removing unreachable block (ram,0x011d32cd) */
/* WARNING: Removing unreachable block (ram,0x011d3295) */
/* WARNING: Removing unreachable block (ram,0x011d328d) */
/* WARNING: Removing unreachable block (ram,0x011d32a3) */
/* WARNING: Recovered jumptable eliminated as dead code */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_011d3150(undefined8 *param_1,undefined4 param_2)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  long in_FS_OFFSET;
  bool bVar4;
  undefined1 local_54 [28];
  undefined1 local_38 [24];
  
  FUN_011d2cd0(local_38,local_54,0x1c,param_2);
  lVar3 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar3 != 0) && ((*(byte *)(lVar3 + 0x21c) & 1) == 0)) {
    uVar1 = *(ulong *)(lVar3 + 8);
    do {
      LOCK();
      uVar2 = *(ulong *)(lVar3 + 8);
      bVar4 = uVar1 == uVar2;
      if (bVar4) {
        *(ulong *)(lVar3 + 8) = uVar1 | 3;
        uVar2 = uVar1;
      }
      UNLOCK();
      uVar1 = uVar2;
    } while (!bVar4);
    if ((uVar2 & 7) == 0) goto LAB_011d31be;
    if (((uint)uVar2 & 7) == 6) {
      *(undefined2 *)(param_1 + 1) = 0x11;
      return;
    }
  }
  lVar3 = 0;
LAB_011d31be:
  if (lVar3 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar3 + 8) = *(ulong *)(lVar3 + 8) ^ 3;
    UNLOCK();
  }
  *(undefined2 *)(param_1 + 1) = 0;
  *param_1 = 0x59;
  return;
}


// ---- FUN_011d3300 @ 011d3300

/* WARNING: Removing unreachable block (ram,0x011d338d) */
/* WARNING: Removing unreachable block (ram,0x011d33a0) */
/* WARNING: Removing unreachable block (ram,0x011d33a7) */
/* WARNING: Removing unreachable block (ram,0x011d33af) */
/* WARNING: Removing unreachable block (ram,0x011d33b7) */
/* WARNING: Removing unreachable block (ram,0x011d3405) */
/* WARNING: Removing unreachable block (ram,0x011d340b) */

undefined8 FUN_011d3300(void)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  long in_FS_OFFSET;
  bool bVar4;
  
  lVar3 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar3 != 0) && ((*(byte *)(lVar3 + 0x21c) & 1) == 0)) {
    uVar1 = *(ulong *)(lVar3 + 8);
    do {
      LOCK();
      uVar2 = *(ulong *)(lVar3 + 8);
      bVar4 = uVar1 == uVar2;
      if (bVar4) {
        *(ulong *)(lVar3 + 8) = uVar1 | 3;
        uVar2 = uVar1;
      }
      UNLOCK();
      uVar1 = uVar2;
    } while (!bVar4);
    if ((uVar2 & 7) == 0) goto LAB_011d3358;
    if (((uint)uVar2 & 7) == 6) {
      return 0x11;
    }
  }
  lVar3 = 0;
LAB_011d3358:
  if (lVar3 == 0) {
    syscall();
    return 0;
  }
  syscall();
  LOCK();
  *(ulong *)(lVar3 + 8) = *(ulong *)(lVar3 + 8) ^ 3;
  UNLOCK();
  return 0;
}


// ---- FUN_011d3420 @ 011d3420

void FUN_011d3420(void)

{
  syscall();
  return;
}


// ---- FUN_011d3460 @ 011d3460

/* WARNING: Removing unreachable block (ram,0x011d3586) */
/* WARNING: Removing unreachable block (ram,0x011d358c) */
/* WARNING: Removing unreachable block (ram,0x011d34ed) */
/* WARNING: Removing unreachable block (ram,0x011d3500) */
/* WARNING: Removing unreachable block (ram,0x011d3507) */
/* WARNING: Removing unreachable block (ram,0x011d350f) */
/* WARNING: Removing unreachable block (ram,0x011d359a) */
/* WARNING: Removing unreachable block (ram,0x011d35a8) */
/* WARNING: Removing unreachable block (ram,0x011d35c9) */
/* WARNING: Removing unreachable block (ram,0x011d35ad) */
/* WARNING: Removing unreachable block (ram,0x011d35b2) */
/* WARNING: Removing unreachable block (ram,0x011d3561) */
/* WARNING: Removing unreachable block (ram,0x011d3566) */
/* WARNING: Removing unreachable block (ram,0x011d356e) */
/* WARNING: Removing unreachable block (ram,0x011d3573) */
/* WARNING: Removing unreachable block (ram,0x011d35be) */

undefined4 * FUN_011d3460(undefined4 *param_1)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  long in_FS_OFFSET;
  bool bVar4;
  
  lVar3 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar3 != 0) && ((*(byte *)(lVar3 + 0x21c) & 1) == 0)) {
    uVar1 = *(ulong *)(lVar3 + 8);
    do {
      LOCK();
      uVar2 = *(ulong *)(lVar3 + 8);
      bVar4 = uVar1 == uVar2;
      if (bVar4) {
        *(ulong *)(lVar3 + 8) = uVar1 | 3;
        uVar2 = uVar1;
      }
      UNLOCK();
      uVar1 = uVar2;
    } while (!bVar4);
    if ((uVar2 & 7) == 0) goto LAB_011d34bd;
    if (((uint)uVar2 & 7) == 6) {
      *(undefined2 *)param_1 = 0x11;
      return param_1;
    }
  }
  lVar3 = 0;
LAB_011d34bd:
  if (lVar3 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar3 + 8) = *(ulong *)(lVar3 + 8) ^ 3;
    UNLOCK();
  }
  *param_1 = DAT_0100149c;
  return param_1;
}


// ---- FUN_011d35e0 @ 011d35e0

/* WARNING: Removing unreachable block (ram,0x011d366e) */
/* WARNING: Removing unreachable block (ram,0x011d3680) */
/* WARNING: Removing unreachable block (ram,0x011d3687) */
/* WARNING: Removing unreachable block (ram,0x011d368f) */
/* WARNING: Removing unreachable block (ram,0x011d3697) */
/* WARNING: Removing unreachable block (ram,0x011d36d4) */
/* WARNING: Removing unreachable block (ram,0x011d36da) */
/* WARNING: Removing unreachable block (ram,0x011d36f3) */
/* WARNING: Removing unreachable block (ram,0x011d36f6) */

undefined8 FUN_011d35e0(void)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  long in_FS_OFFSET;
  bool bVar4;
  
  lVar3 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar3 != 0) && ((*(byte *)(lVar3 + 0x21c) & 1) == 0)) {
    uVar1 = *(ulong *)(lVar3 + 8);
    do {
      LOCK();
      uVar2 = *(ulong *)(lVar3 + 8);
      bVar4 = uVar1 == uVar2;
      if (bVar4) {
        *(ulong *)(lVar3 + 8) = uVar1 | 3;
        uVar2 = uVar1;
      }
      UNLOCK();
      uVar1 = uVar2;
    } while (!bVar4);
    if ((uVar2 & 7) == 0) goto LAB_011d3648;
    if (((uint)uVar2 & 7) == 6) {
      return 0x11;
    }
  }
  lVar3 = 0;
LAB_011d3648:
  if (lVar3 == 0) {
    syscall();
    return 0;
  }
  syscall();
  LOCK();
  *(ulong *)(lVar3 + 8) = *(ulong *)(lVar3 + 8) ^ 3;
  UNLOCK();
  return 0;
}


// ---- FUN_011d3700 @ 011d3700

/* WARNING: Removing unreachable block (ram,0x011d395b) */
/* WARNING: Removing unreachable block (ram,0x011d3960) */
/* WARNING: Removing unreachable block (ram,0x011d3965) */
/* WARNING: Removing unreachable block (ram,0x011d38e6) */
/* WARNING: Removing unreachable block (ram,0x011d38f0) */
/* WARNING: Removing unreachable block (ram,0x011d38f7) */
/* WARNING: Removing unreachable block (ram,0x011d38ff) */
/* WARNING: Removing unreachable block (ram,0x011d3907) */
/* WARNING: Removing unreachable block (ram,0x011d397e) */

undefined1  [16] FUN_011d3700(undefined8 param_1,undefined8 param_2,ulong *param_3)

{
  byte bVar1;
  byte bVar2;
  ulong uVar3;
  ulong uVar4;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  ulong uVar7;
  ulong uVar8;
  undefined8 uVar9;
  long *plVar10;
  long lVar11;
  long in_FS_OFFSET;
  bool bVar12;
  undefined1 auVar13 [16];
  undefined1 auVar14 [12];
  long local_78;
  long lStack_70;
  ulong local_50;
  ulong local_48;
  long local_40;
  long local_38;
  
  bVar1 = (byte)param_3[2];
  bVar2 = (byte)param_3[6];
  if (((bVar1 ^ 1 | bVar2 ^ 1) & 3) == 0) {
    plVar10 = (long *)0x0;
    lVar11 = *(long *)(in_FS_OFFSET + -0x40010);
    if (lVar11 == 0) goto LAB_011d38b6;
LAB_011d3876:
    if ((*(byte *)(lVar11 + 0x21c) & 1) != 0) goto LAB_011d38b6;
    uVar7 = *(ulong *)(lVar11 + 8);
    do {
      LOCK();
      uVar8 = *(ulong *)(lVar11 + 8);
      bVar12 = uVar7 == uVar8;
      if (bVar12) {
        *(ulong *)(lVar11 + 8) = uVar7 | 3;
        uVar8 = uVar7;
      }
      UNLOCK();
      uVar7 = uVar8;
    } while (!bVar12);
    if ((uVar8 & 7) != 0) {
      uVar9 = 0x11;
      if (((uint)uVar8 & 7) == 6) goto LAB_011d396f;
      goto LAB_011d38b6;
    }
  }
  else {
    uVar7 = param_3[5];
    uVar8 = param_3[4];
    plVar10 = (long *)&DAT_01000810;
    if ((bVar1 & 3) != 0) {
      if ((bVar1 & 3) == 2) {
        uVar3 = *param_3;
        uVar4 = param_3[1];
        local_50 = uVar8;
        local_48 = uVar7;
        auVar14 = FUN_011f6850(uVar3,(long)(int)uVar4,1000000000,0);
        auVar5._8_8_ = 0;
        auVar5._0_8_ = auVar14._0_8_;
        uVar7 = SUB168(auVar5 * ZEXT816(1000000000),0);
        lVar11 = (long)(int)(((int)uVar4 -
                             (auVar14._8_4_ * 1000000000 + SUB164(auVar5 * ZEXT816(1000000000),8)))
                            - (uint)(uVar3 < uVar7)) >> 0x1f;
        local_40 = auVar14._0_8_ + lVar11;
        local_38 = (ulong)((uint)lVar11 & 1000000000) + (uVar3 - uVar7);
        plVar10 = &local_40;
        uVar7 = local_48;
        uVar8 = local_50;
      }
      else {
        plVar10 = (long *)&DAT_010007a0;
      }
    }
    local_78 = *plVar10;
    lStack_70 = plVar10[1];
    if (((bVar2 & 3) != 0) && ((bVar2 & 3) == 2)) {
      auVar14 = FUN_011f6850(uVar8,(long)(int)uVar7,1000000000,0);
      auVar6._8_8_ = 0;
      auVar6._0_8_ = auVar14._0_8_;
      uVar3 = SUB168(auVar6 * ZEXT816(1000000000),0);
      lVar11 = (long)(int)(((int)uVar7 -
                           (auVar14._8_4_ * 1000000000 + SUB164(auVar6 * ZEXT816(1000000000),8))) -
                          (uint)(uVar8 < uVar3)) >> 0x1f;
      local_40 = auVar14._0_8_ + lVar11;
      local_38 = (ulong)((uint)lVar11 & 1000000000) + (uVar8 - uVar3);
    }
    plVar10 = &local_78;
    lVar11 = *(long *)(in_FS_OFFSET + -0x40010);
    if (lVar11 != 0) goto LAB_011d3876;
LAB_011d38b6:
    lVar11 = 0;
  }
  if (lVar11 == 0) {
    syscall();
    uVar9 = 0;
  }
  else {
    syscall();
                    /* WARNING: Could not find normalized switch variable to match jumptable */
    switch(switchD_011d3914::switchdataD_01004b50) {
    case (undefined *)0x0:
                    /* WARNING: This code block may not be properly labeled as switch case */
      LOCK();
      *(ulong *)(lVar11 + 8) = *(ulong *)(lVar11 + 8) ^ 3;
      UNLOCK();
      uVar9 = 0;
      break;
    default:
                    /* WARNING: This code block may not be properly labeled as switch case */
      LOCK();
      *(ulong *)(lVar11 + 8) = *(ulong *)(lVar11 + 8) ^ 3;
      UNLOCK();
      uVar9 = 4;
    }
  }
LAB_011d396f:
  auVar13._8_8_ = plVar10;
  auVar13._0_8_ = uVar9;
  return auVar13;
}


// ---- FUN_011d39c0 @ 011d39c0

/* WARNING: Removing unreachable block (ram,0x011d3aa4) */
/* WARNING: Removing unreachable block (ram,0x011d3aaa) */
/* WARNING: Removing unreachable block (ram,0x011d3a3e) */
/* WARNING: Removing unreachable block (ram,0x011d3a50) */
/* WARNING: Removing unreachable block (ram,0x011d3a57) */
/* WARNING: Removing unreachable block (ram,0x011d3a5f) */
/* WARNING: Removing unreachable block (ram,0x011d3a67) */
/* WARNING: Removing unreachable block (ram,0x011d3ab4) */
/* WARNING: Removing unreachable block (ram,0x011d3ad9) */
/* WARNING: Removing unreachable block (ram,0x011d3ad3) */
/* WARNING: Removing unreachable block (ram,0x011d3ac7) */
/* WARNING: Removing unreachable block (ram,0x011d3ae5) */
/* WARNING: Removing unreachable block (ram,0x011d3adf) */
/* WARNING: Removing unreachable block (ram,0x011d3ac1) */
/* WARNING: Removing unreachable block (ram,0x011d3abb) */
/* WARNING: Removing unreachable block (ram,0x011d3acd) */
/* WARNING: Recovered jumptable eliminated as dead code */

undefined8 FUN_011d39c0(void)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  long in_FS_OFFSET;
  bool bVar4;
  
  lVar3 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar3 != 0) && ((*(byte *)(lVar3 + 0x21c) & 1) == 0)) {
    uVar1 = *(ulong *)(lVar3 + 8);
    do {
      LOCK();
      uVar2 = *(ulong *)(lVar3 + 8);
      bVar4 = uVar1 == uVar2;
      if (bVar4) {
        *(ulong *)(lVar3 + 8) = uVar1 | 3;
        uVar2 = uVar1;
      }
      UNLOCK();
      uVar1 = uVar2;
    } while (!bVar4);
    if ((uVar2 & 7) == 0) goto LAB_011d3a08;
    if (((uint)uVar2 & 7) == 6) {
      return 0x11;
    }
  }
  lVar3 = 0;
LAB_011d3a08:
  if (lVar3 == 0) {
    syscall();
    return 0;
  }
  syscall();
  LOCK();
  *(ulong *)(lVar3 + 8) = *(ulong *)(lVar3 + 8) ^ 3;
  UNLOCK();
  return 0;
}


// ---- FUN_011d3af0 @ 011d3af0

/* WARNING: Removing unreachable block (ram,0x011d3be7) */
/* WARNING: Removing unreachable block (ram,0x011d3bed) */
/* WARNING: Removing unreachable block (ram,0x011d3b81) */
/* WARNING: Removing unreachable block (ram,0x011d3b90) */
/* WARNING: Removing unreachable block (ram,0x011d3b97) */
/* WARNING: Removing unreachable block (ram,0x011d3b9f) */
/* WARNING: Removing unreachable block (ram,0x011d3ba7) */
/* WARNING: Removing unreachable block (ram,0x011d3bf7) */
/* WARNING: Removing unreachable block (ram,0x011d3c1a) */
/* WARNING: Removing unreachable block (ram,0x011d3c14) */
/* WARNING: Removing unreachable block (ram,0x011d3c0e) */
/* WARNING: Removing unreachable block (ram,0x011d3c08) */
/* WARNING: Removing unreachable block (ram,0x011d3c02) */
/* WARNING: Recovered jumptable eliminated as dead code */

undefined8 FUN_011d3af0(undefined8 param_1,undefined8 param_2,long param_3)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  long in_FS_OFFSET;
  bool bVar4;
  
  if (param_3 < 0) {
    return 6;
  }
  lVar3 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar3 != 0) && ((*(byte *)(lVar3 + 0x21c) & 1) == 0)) {
    uVar1 = *(ulong *)(lVar3 + 8);
    do {
      LOCK();
      uVar2 = *(ulong *)(lVar3 + 8);
      bVar4 = uVar1 == uVar2;
      if (bVar4) {
        *(ulong *)(lVar3 + 8) = uVar1 | 3;
        uVar2 = uVar1;
      }
      UNLOCK();
      uVar1 = uVar2;
    } while (!bVar4);
    if ((uVar2 & 7) == 0) goto LAB_011d3b49;
    if (((uint)uVar2 & 7) == 6) {
      return 0x11;
    }
  }
  lVar3 = 0;
LAB_011d3b49:
  if (lVar3 == 0) {
    syscall();
    return 0;
  }
  syscall();
  LOCK();
  *(ulong *)(lVar3 + 8) = *(ulong *)(lVar3 + 8) ^ 3;
  UNLOCK();
  return 0;
}


// ---- FUN_011d3c20 @ 011d3c20

/* WARNING: Removing unreachable block (ram,0x011d3d04) */
/* WARNING: Removing unreachable block (ram,0x011d3d0a) */
/* WARNING: Removing unreachable block (ram,0x011d3c9e) */
/* WARNING: Removing unreachable block (ram,0x011d3cb0) */
/* WARNING: Removing unreachable block (ram,0x011d3cb7) */
/* WARNING: Removing unreachable block (ram,0x011d3cbf) */
/* WARNING: Removing unreachable block (ram,0x011d3cc7) */
/* WARNING: Removing unreachable block (ram,0x011d3d14) */
/* WARNING: Removing unreachable block (ram,0x011d3d39) */
/* WARNING: Removing unreachable block (ram,0x011d3d33) */
/* WARNING: Removing unreachable block (ram,0x011d3d27) */
/* WARNING: Removing unreachable block (ram,0x011d3d45) */
/* WARNING: Removing unreachable block (ram,0x011d3d3f) */
/* WARNING: Removing unreachable block (ram,0x011d3d21) */
/* WARNING: Removing unreachable block (ram,0x011d3d1b) */
/* WARNING: Removing unreachable block (ram,0x011d3d2d) */
/* WARNING: Recovered jumptable eliminated as dead code */

undefined1  [16] FUN_011d3c20(undefined8 param_1,undefined8 param_2,ulong param_3)

{
  undefined1 auVar1 [16];
  ulong uVar2;
  ulong uVar3;
  undefined8 uVar4;
  long lVar5;
  long in_FS_OFFSET;
  bool bVar6;
  undefined1 auVar7 [16];
  
  lVar5 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar5 == 0) || ((*(byte *)(lVar5 + 0x21c) & 1) != 0)) {
LAB_011d3c66:
    lVar5 = 0;
  }
  else {
    uVar2 = *(ulong *)(lVar5 + 8);
    do {
      LOCK();
      uVar3 = *(ulong *)(lVar5 + 8);
      bVar6 = uVar2 == uVar3;
      if (bVar6) {
        *(ulong *)(lVar5 + 8) = uVar2 | 3;
        uVar3 = uVar2;
      }
      UNLOCK();
      uVar2 = uVar3;
    } while (!bVar6);
    if ((uVar3 & 7) != 0) {
      uVar4 = 0x11;
      if (((uint)uVar3 & 7) == 6) goto LAB_011d3d02;
      goto LAB_011d3c66;
    }
  }
  param_3 = param_3 & 0xffffffff;
  if (lVar5 != 0) {
    syscall();
    LOCK();
    *(ulong *)(lVar5 + 8) = *(ulong *)(lVar5 + 8) ^ 3;
    UNLOCK();
    auVar1._8_8_ = 0;
    auVar1._0_8_ = param_3;
    return auVar1 << 0x40;
  }
  syscall();
  uVar4 = 0;
LAB_011d3d02:
  auVar7._8_8_ = param_3;
  auVar7._0_8_ = uVar4;
  return auVar7;
}


// ---- FUN_011d3d50 @ 011d3d50

/* WARNING: Removing unreachable block (ram,0x011d3dcd) */
/* WARNING: Removing unreachable block (ram,0x011d3de0) */
/* WARNING: Removing unreachable block (ram,0x011d3de7) */
/* WARNING: Removing unreachable block (ram,0x011d3def) */
/* WARNING: Removing unreachable block (ram,0x011d3e53) */
/* WARNING: Removing unreachable block (ram,0x011d3e59) */

undefined1  [16] FUN_011d3d50(uint *param_1,undefined8 param_2,undefined1 *param_3)

{
  uint uVar1;
  ulong uVar2;
  ulong uVar3;
  uint uVar4;
  long lVar5;
  long in_FS_OFFSET;
  bool bVar6;
  undefined1 auVar7 [16];
  undefined1 local_10 [8];
  
  lVar5 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar5 == 0) || ((*(byte *)(lVar5 + 0x21c) & 1) != 0)) {
LAB_011d3d9b:
    lVar5 = 0;
  }
  else {
    uVar2 = *(ulong *)(lVar5 + 8);
    do {
      LOCK();
      uVar3 = *(ulong *)(lVar5 + 8);
      bVar6 = uVar2 == uVar3;
      if (bVar6) {
        *(ulong *)(lVar5 + 8) = uVar2 | 3;
        uVar3 = uVar2;
      }
      UNLOCK();
      uVar2 = uVar3;
    } while (!bVar6);
    if ((uVar3 & 7) != 0) {
      if (((uint)uVar3 & 7) == 6) {
        uVar1 = 0x11;
        uVar4 = 0;
        goto LAB_011d3e71;
      }
      goto LAB_011d3d9b;
    }
  }
  param_3 = local_10;
  if (lVar5 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar5 + 8) = *(ulong *)(lVar5 + 8) ^ 3;
    UNLOCK();
  }
  uVar1 = DAT_0100149c;
  if ((DAT_0100149c & 0x10000) == 0) {
    uVar1 = DAT_01001470;
  }
  uVar4 = uVar1 & 0xffff0000;
LAB_011d3e71:
  *param_1 = uVar1 & 0xffff | uVar4;
  auVar7._8_8_ = param_3;
  auVar7._0_8_ = param_1;
  return auVar7;
}


// ---- FUN_011d3e80 @ 011d3e80

/* WARNING: Removing unreachable block (ram,0x011d3efd) */
/* WARNING: Removing unreachable block (ram,0x011d3f10) */
/* WARNING: Removing unreachable block (ram,0x011d3f17) */
/* WARNING: Removing unreachable block (ram,0x011d3f1f) */
/* WARNING: Removing unreachable block (ram,0x011d3f78) */
/* WARNING: Removing unreachable block (ram,0x011d3f7e) */

undefined8 FUN_011d3e80(void)

{
  undefined4 *puVar1;
  ulong uVar2;
  ulong uVar3;
  undefined8 uVar4;
  long lVar5;
  long in_FS_OFFSET;
  bool bVar6;
  
  lVar5 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar5 != 0) && ((*(byte *)(lVar5 + 0x21c) & 1) == 0)) {
    uVar2 = *(ulong *)(lVar5 + 8);
    do {
      LOCK();
      uVar3 = *(ulong *)(lVar5 + 8);
      bVar6 = uVar2 == uVar3;
      if (bVar6) {
        *(ulong *)(lVar5 + 8) = uVar2 | 3;
        uVar3 = uVar2;
      }
      UNLOCK();
      uVar2 = uVar3;
    } while (!bVar6);
    if ((uVar3 & 7) == 0) goto LAB_011d3ece;
    if (((uint)uVar3 & 7) == 6) {
      return 0x11;
    }
  }
  lVar5 = 0;
LAB_011d3ece:
  if (lVar5 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar5 + 8) = *(ulong *)(lVar5 + 8) ^ 3;
    UNLOCK();
  }
  puVar1 = &DAT_01001470;
  if ((DAT_0100149c._2_1_ & 1) != 0) {
    puVar1 = &DAT_0100149c;
  }
  uVar4 = 0x3f;
  if ((*(byte *)((long)puVar1 + 2) & 1) != 0) {
    uVar4 = 0;
  }
  return uVar4;
}


// ---- FUN_011d3fb0 @ 011d3fb0

/* WARNING: Removing unreachable block (ram,0x011d402d) */
/* WARNING: Removing unreachable block (ram,0x011d4040) */
/* WARNING: Removing unreachable block (ram,0x011d4047) */
/* WARNING: Removing unreachable block (ram,0x011d404f) */
/* WARNING: Removing unreachable block (ram,0x011d40a9) */
/* WARNING: Removing unreachable block (ram,0x011d40af) */

undefined1  [16] FUN_011d3fb0(uint *param_1,undefined8 param_2,undefined1 *param_3)

{
  uint uVar1;
  ulong uVar2;
  ulong uVar3;
  uint uVar4;
  long lVar5;
  long in_FS_OFFSET;
  bool bVar6;
  undefined1 auVar7 [16];
  undefined1 local_10 [8];
  
  lVar5 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar5 == 0) || ((*(byte *)(lVar5 + 0x21c) & 1) != 0)) {
LAB_011d3ffb:
    lVar5 = 0;
  }
  else {
    uVar2 = *(ulong *)(lVar5 + 8);
    do {
      LOCK();
      uVar3 = *(ulong *)(lVar5 + 8);
      bVar6 = uVar2 == uVar3;
      if (bVar6) {
        *(ulong *)(lVar5 + 8) = uVar2 | 3;
        uVar3 = uVar2;
      }
      UNLOCK();
      uVar2 = uVar3;
    } while (!bVar6);
    if ((uVar3 & 7) != 0) {
      if (((uint)uVar3 & 7) == 6) {
        uVar4 = 0;
        uVar1 = 0x11;
        goto LAB_011d40bd;
      }
      goto LAB_011d3ffb;
    }
  }
  param_3 = local_10;
  if (lVar5 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar5 + 8) = *(ulong *)(lVar5 + 8) ^ 3;
    UNLOCK();
  }
  uVar4 = DAT_0100149c & 0xffff0000;
  uVar1 = DAT_0100149c;
LAB_011d40bd:
  *param_1 = uVar1 & 0xffff | uVar4;
  auVar7._8_8_ = param_3;
  auVar7._0_8_ = param_1;
  return auVar7;
}


// ---- FUN_011d40d0 @ 011d40d0

/* WARNING: Removing unreachable block (ram,0x011d41b4) */
/* WARNING: Removing unreachable block (ram,0x011d41ba) */
/* WARNING: Removing unreachable block (ram,0x011d41c0) */
/* WARNING: Removing unreachable block (ram,0x011d41d3) */
/* WARNING: Removing unreachable block (ram,0x011d41c8) */
/* WARNING: Removing unreachable block (ram,0x011d41df) */
/* WARNING: Removing unreachable block (ram,0x011d41cd) */
/* WARNING: Removing unreachable block (ram,0x011d414e) */
/* WARNING: Removing unreachable block (ram,0x011d4160) */
/* WARNING: Removing unreachable block (ram,0x011d4167) */
/* WARNING: Removing unreachable block (ram,0x011d416f) */
/* WARNING: Removing unreachable block (ram,0x011d4177) */
/* WARNING: Removing unreachable block (ram,0x011d41d9) */

undefined8 FUN_011d40d0(void)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  long in_FS_OFFSET;
  bool bVar4;
  
  lVar3 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar3 != 0) && ((*(byte *)(lVar3 + 0x21c) & 1) == 0)) {
    uVar1 = *(ulong *)(lVar3 + 8);
    do {
      LOCK();
      uVar2 = *(ulong *)(lVar3 + 8);
      bVar4 = uVar1 == uVar2;
      if (bVar4) {
        *(ulong *)(lVar3 + 8) = uVar1 | 3;
        uVar2 = uVar1;
      }
      UNLOCK();
      uVar1 = uVar2;
    } while (!bVar4);
    if ((uVar2 & 7) == 0) goto LAB_011d4128;
    if (((uint)uVar2 & 7) == 6) {
      return 0x11;
    }
  }
  lVar3 = 0;
LAB_011d4128:
  if (lVar3 == 0) {
    syscall();
    return 0;
  }
  syscall();
  LOCK();
  *(ulong *)(lVar3 + 8) = *(ulong *)(lVar3 + 8) ^ 3;
  UNLOCK();
  return 0;
}


// ---- FUN_011d41f0 @ 011d41f0

/* WARNING: Removing unreachable block (ram,0x011d42e9) */
/* WARNING: Removing unreachable block (ram,0x011d42ef) */
/* WARNING: Removing unreachable block (ram,0x011d4283) */
/* WARNING: Removing unreachable block (ram,0x011d4290) */
/* WARNING: Removing unreachable block (ram,0x011d4297) */
/* WARNING: Removing unreachable block (ram,0x011d429f) */
/* WARNING: Removing unreachable block (ram,0x011d42a7) */
/* WARNING: Removing unreachable block (ram,0x011d42fe) */
/* WARNING: Removing unreachable block (ram,0x011d430e) */
/* WARNING: Removing unreachable block (ram,0x011d4315) */

undefined1  [16] FUN_011d41f0(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  ulong uVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long in_FS_OFFSET;
  bool bVar5;
  undefined1 auVar6 [16];
  
  lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar4 == 0) || ((*(byte *)(lVar4 + 0x21c) & 1) != 0)) {
LAB_011d4246:
    lVar4 = 0;
  }
  else {
    uVar1 = *(ulong *)(lVar4 + 8);
    do {
      LOCK();
      uVar2 = *(ulong *)(lVar4 + 8);
      bVar5 = uVar1 == uVar2;
      if (bVar5) {
        *(ulong *)(lVar4 + 8) = uVar1 | 3;
        uVar2 = uVar1;
      }
      UNLOCK();
      uVar1 = uVar2;
    } while (!bVar5);
    if ((uVar2 & 7) != 0) {
      uVar3 = 0x11;
      if (((uint)uVar2 & 7) == 6) goto LAB_011d4313;
      goto LAB_011d4246;
    }
  }
  if (lVar4 != 0) {
    syscall();
    LOCK();
    *(ulong *)(lVar4 + 8) = *(ulong *)(lVar4 + 8) ^ 3;
    UNLOCK();
    return ZEXT816(0);
  }
  param_3 = 0;
  syscall();
  uVar3 = 0;
LAB_011d4313:
  auVar6._8_8_ = param_3;
  auVar6._0_8_ = uVar3;
  return auVar6;
}


// ---- FUN_011d4320 @ 011d4320

/* WARNING: Removing unreachable block (ram,0x011d4427) */
/* WARNING: Removing unreachable block (ram,0x011d442d) */
/* WARNING: Removing unreachable block (ram,0x011d43b1) */
/* WARNING: Removing unreachable block (ram,0x011d43c0) */
/* WARNING: Removing unreachable block (ram,0x011d43c7) */
/* WARNING: Removing unreachable block (ram,0x011d43cf) */
/* WARNING: Removing unreachable block (ram,0x011d43d7) */
/* WARNING: Removing unreachable block (ram,0x011d443c) */
/* WARNING: Removing unreachable block (ram,0x011d444c) */
/* WARNING: Removing unreachable block (ram,0x011d4453) */

undefined1  [16] FUN_011d4320(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  ulong uVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long in_FS_OFFSET;
  bool bVar5;
  undefined1 auVar6 [16];
  
  lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar4 == 0) || ((*(byte *)(lVar4 + 0x21c) & 1) != 0)) {
LAB_011d4376:
    lVar4 = 0;
  }
  else {
    uVar1 = *(ulong *)(lVar4 + 8);
    do {
      LOCK();
      uVar2 = *(ulong *)(lVar4 + 8);
      bVar5 = uVar1 == uVar2;
      if (bVar5) {
        *(ulong *)(lVar4 + 8) = uVar1 | 3;
        uVar2 = uVar1;
      }
      UNLOCK();
      uVar1 = uVar2;
    } while (!bVar5);
    if ((uVar2 & 7) != 0) {
      uVar3 = 0x11;
      if (((uint)uVar2 & 7) == 6) goto LAB_011d4451;
      goto LAB_011d4376;
    }
  }
  if (lVar4 != 0) {
    syscall();
    LOCK();
    *(ulong *)(lVar4 + 8) = *(ulong *)(lVar4 + 8) ^ 3;
    UNLOCK();
    return ZEXT816(1) << 0x40;
  }
  param_3 = 1;
  syscall();
  uVar3 = 0;
LAB_011d4451:
  auVar6._8_8_ = param_3;
  auVar6._0_8_ = uVar3;
  return auVar6;
}


// ---- FUN_011d4460 @ 011d4460

/* WARNING: Removing unreachable block (ram,0x011d45a7) */
/* WARNING: Removing unreachable block (ram,0x011d45f0) */

undefined8 *
FUN_011d4460(undefined8 *param_1,undefined8 param_2,int *param_3,long param_4,long param_5)

{
  int iVar1;
  undefined8 in_RAX;
  ulong uVar2;
  ulong uVar3;
  undefined8 *puVar4;
  undefined8 uVar5;
  undefined2 uVar6;
  long *plVar7;
  long lVar8;
  long lVar9;
  long in_FS_OFFSET;
  bool bVar10;
  long local_a0 [16];
  undefined8 local_20;
  
  if (param_5 != 0) {
    iVar1 = *param_3;
    plVar7 = (long *)(param_4 + 8);
    lVar8 = 0;
    local_20 = in_RAX;
    do {
      if (lVar8 == 8) {
        lVar8 = 8;
        goto LAB_011d44d7;
      }
      lVar9 = *plVar7;
      if (lVar9 != 0) {
        local_a0[lVar8 * 2] = plVar7[-1];
        local_a0[lVar8 * 2 + 1] = lVar9;
        lVar8 = lVar8 + 1;
      }
      plVar7 = plVar7 + 2;
      param_5 = param_5 + -1;
    } while (param_5 != 0);
    if (lVar8 != 0) {
LAB_011d44d7:
      lVar9 = *(long *)(in_FS_OFFSET + -0x40010);
      if ((lVar9 != 0) && ((*(byte *)(lVar9 + 0x21c) & 1) == 0)) {
        uVar2 = *(ulong *)(lVar9 + 8);
        do {
          LOCK();
          uVar3 = *(ulong *)(lVar9 + 8);
          bVar10 = uVar2 == uVar3;
          if (bVar10) {
            *(ulong *)(lVar9 + 8) = uVar2 | 3;
            uVar3 = uVar2;
          }
          UNLOCK();
          uVar2 = uVar3;
        } while (!bVar10);
        if ((uVar3 & 7) == 0) goto LAB_011d451d;
        if (((uint)uVar3 & 7) == 6) {
          uVar6 = 0x11;
          uVar5 = 6;
          goto LAB_011d45f6;
        }
      }
      lVar9 = 0;
LAB_011d451d:
      if (lVar9 == 0) {
        syscall();
                    /* WARNING: Could not recover jumptable at 0x011d45a0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        puVar4 = (undefined8 *)(*(code *)PTR_LAB_01005318)((long)iVar1,local_a0,lVar8,0,0);
        return puVar4;
      }
      syscall();
                    /* WARNING: Could not recover jumptable at 0x011d454c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      puVar4 = (undefined8 *)(*(code *)PTR_LAB_01004fa0)();
      return puVar4;
    }
  }
  local_20 = 0;
  uVar5 = 0;
  uVar6 = 0;
LAB_011d45f6:
  *param_1 = uVar5;
  *(undefined2 *)(param_1 + 1) = uVar6;
  *(undefined4 *)((long)param_1 + 10) = (undefined4)local_20;
  *(undefined2 *)((long)param_1 + 0xe) = local_20._4_2_;
  return param_1;
}


// ---- FUN_011d4640 @ 011d4640

/* WARNING: Removing unreachable block (ram,0x011d4957) */
/* WARNING: Removing unreachable block (ram,0x011d490c) */
/* WARNING: Removing unreachable block (ram,0x011d4911) */
/* WARNING: Removing unreachable block (ram,0x011d4916) */
/* WARNING: Removing unreachable block (ram,0x011d48ea) */
/* WARNING: Removing unreachable block (ram,0x011d48ef) */
/* WARNING: Removing unreachable block (ram,0x011d486a) */
/* WARNING: Removing unreachable block (ram,0x011d4870) */
/* WARNING: Removing unreachable block (ram,0x011d4877) */
/* WARNING: Removing unreachable block (ram,0x011d487f) */
/* WARNING: Removing unreachable block (ram,0x011d48ac) */
/* WARNING: Removing unreachable block (ram,0x011d48f4) */
/* WARNING: Removing unreachable block (ram,0x011d48b1) */
/* WARNING: Removing unreachable block (ram,0x011d4918) */
/* WARNING: Removing unreachable block (ram,0x011d48e3) */
/* WARNING: Removing unreachable block (ram,0x011d48e8) */
/* WARNING: Removing unreachable block (ram,0x011d491e) */
/* WARNING: Removing unreachable block (ram,0x011d4928) */
/* WARNING: Removing unreachable block (ram,0x011d49a1) */
/* WARNING: Removing unreachable block (ram,0x011d49ae) */
/* WARNING: Removing unreachable block (ram,0x011d496d) */
/* WARNING: Removing unreachable block (ram,0x011d492f) */
/* WARNING: Recovered jumptable eliminated as dead code */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 (*) [16]
FUN_011d4640(undefined1 (*param_1) [16],long param_2,undefined8 param_3,undefined8 param_4,
            ulong param_5,long param_6,ulong param_7,undefined8 param_8)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  long in_FS_OFFSET;
  bool bVar4;
  undefined1 auVar5 [16];
  ulong local_a0;
  short local_98;
  long local_90;
  ulong local_88;
  ulong local_80;
  short local_78;
  long local_70;
  ulong local_68;
  ulong local_60;
  short local_58;
  long local_50;
  ulong local_48;
  
  lVar3 = *(long *)(param_6 + 0x40);
  local_90 = *(long *)(param_6 + 0x30) + lVar3;
  local_88 = *(long *)(param_6 + 0x48) - lVar3;
  if (param_7 <= local_88) {
    local_48 = param_7;
    local_50 = local_90;
    FUN_011d50c0(&local_60);
    local_a0 = local_60;
    local_98 = local_58;
joined_r0x011d46d4:
    if (local_98 != 0) {
      *(short *)(*param_1 + 8) = local_98;
      return param_1;
    }
    lVar3 = 0;
    if (param_5 <= local_a0) {
      lVar3 = local_a0 - param_5;
    }
    *(long *)(param_6 + 0x40) = *(long *)(param_6 + 0x40) + lVar3;
    goto LAB_011d46ee;
  }
  if ((*(char *)(param_6 + 0x20) != '\0') &&
     (*(long *)(param_6 + 0x18) == *(long *)(param_6 + 0x10))) {
    auVar5 = _DAT_01000920;
    if (*(long *)(param_6 + 0x48) == lVar3) goto LAB_011d470f;
    local_70 = local_90;
    local_68 = local_88;
    FUN_011d50c0(&local_80,param_2,param_3,param_4,param_5,&local_70,1,1,param_8);
    local_a0 = local_80;
    local_98 = local_78;
    goto joined_r0x011d46d4;
  }
  if ((*(byte *)(param_2 + 0x35a) & 1) != 0) {
switchD_011d47dc_caseD_2:
    auVar5 = _DAT_01000280;
    goto LAB_011d470f;
  }
  if (local_88 != 0 || param_5 != 0) {
    FUN_011d50c0(&local_a0,param_2,param_3,param_4,param_5,&local_90,1,1,param_8);
    goto joined_r0x011d46d4;
  }
  switch(*(byte *)(param_6 + 0x5e) & 7) {
  case 0:
    goto switchD_011d47dc_caseD_0;
  case 1:
switchD_011d47dc_caseD_0:
    lVar3 = *(long *)(in_FS_OFFSET + -0x40010);
    if ((lVar3 == 0) || ((*(byte *)(lVar3 + 0x21c) & 1) != 0)) {
LAB_011d483b:
      lVar3 = 0;
    }
    else {
      uVar1 = *(ulong *)(lVar3 + 8);
      do {
        LOCK();
        uVar2 = *(ulong *)(lVar3 + 8);
        bVar4 = uVar1 == uVar2;
        if (bVar4) {
          *(ulong *)(lVar3 + 8) = uVar1 | 3;
          uVar2 = uVar1;
        }
        UNLOCK();
        uVar1 = uVar2;
      } while (!bVar4);
      if ((uVar2 & 7) != 0) {
        if (((uint)uVar2 & 7) == 6) {
          *(undefined2 *)(*param_1 + 8) = 0x11;
          return param_1;
        }
        goto LAB_011d483b;
      }
    }
    if (lVar3 == 0) {
      syscall();
    }
    else {
      syscall();
      LOCK();
      *(ulong *)(lVar3 + 8) = *(ulong *)(lVar3 + 8) ^ 3;
      UNLOCK();
    }
    local_a0 = 0x146;
    *(long *)(param_6 + 0x10) = *(long *)(param_6 + 0x10) + 0x146;
LAB_011d46ee:
    *(undefined2 *)(*param_1 + 8) = 0;
    *(ulong *)*param_1 = local_a0;
    return param_1;
  default:
    goto switchD_011d47dc_caseD_2;
  case 4:
    auVar5 = _DAT_01000690;
    break;
  case 5:
    auVar5 = _DAT_010004a0;
    break;
  case 6:
  case 7:
    *(undefined1 *)(param_2 + 0x35a) = 1;
    auVar5._0_12_ = ZEXT812(0);
    auVar5._12_4_ = 0;
  }
LAB_011d470f:
  *param_1 = auVar5;
  return param_1;
}


// ---- FUN_011d49d0 @ 011d49d0

/* WARNING: Removing unreachable block (ram,0x011d4d15) */
/* WARNING: Removing unreachable block (ram,0x011d4d20) */
/* WARNING: Removing unreachable block (ram,0x011d4d27) */
/* WARNING: Removing unreachable block (ram,0x011d4d2f) */
/* WARNING: Removing unreachable block (ram,0x011d4d3a) */
/* WARNING: Removing unreachable block (ram,0x011d4e7b) */
/* WARNING: Removing unreachable block (ram,0x011d4e84) */
/* WARNING: Removing unreachable block (ram,0x011d4ef5) */
/* WARNING: Removing unreachable block (ram,0x011d4efa) */
/* WARNING: Removing unreachable block (ram,0x011d4eff) */
/* WARNING: Removing unreachable block (ram,0x011d4f3a) */
/* WARNING: Removing unreachable block (ram,0x011d4f43) */
/* WARNING: Removing unreachable block (ram,0x011d4f48) */
/* WARNING: Removing unreachable block (ram,0x011d4f11) */
/* WARNING: Removing unreachable block (ram,0x011d4f16) */
/* WARNING: Removing unreachable block (ram,0x011d4f1f) */
/* WARNING: Removing unreachable block (ram,0x011d4df0) */
/* WARNING: Removing unreachable block (ram,0x011d4e00) */
/* WARNING: Removing unreachable block (ram,0x011d4e07) */
/* WARNING: Removing unreachable block (ram,0x011d4e10) */
/* WARNING: Removing unreachable block (ram,0x011d4eb7) */
/* WARNING: Removing unreachable block (ram,0x011d4ebc) */
/* WARNING: Removing unreachable block (ram,0x011d4fb9) */
/* WARNING: Removing unreachable block (ram,0x011d4fc0) */
/* WARNING: Removing unreachable block (ram,0x011d4fce) */
/* WARNING: Removing unreachable block (ram,0x011d5094) */
/* WARNING: Removing unreachable block (ram,0x011d5072) */
/* WARNING: Removing unreachable block (ram,0x011d50a5) */
/* WARNING: Removing unreachable block (ram,0x011d502d) */
/* WARNING: Removing unreachable block (ram,0x011d4f01) */
/* WARNING: Recovered jumptable eliminated as dead code */
/* WARNING: Removing unreachable block (ram,0x011d4f4a) */
/* WARNING: Removing unreachable block (ram,0x011d503e) */
/* WARNING: Removing unreachable block (ram,0x011d4f5f) */
/* WARNING: Removing unreachable block (ram,0x011d5047) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 (*) [16]
FUN_011d49d0(undefined1 (*param_1) [16],long param_2,undefined4 *param_3,undefined8 param_4,
            ulong param_5,long param_6,ulong param_7)

{
  undefined4 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  byte bVar6;
  short sVar7;
  ulong uVar8;
  ulong uVar9;
  long lVar10;
  long lVar11;
  long in_FS_OFFSET;
  bool bVar12;
  undefined1 auVar13 [16];
  ulong local_e8;
  short local_e0;
  long local_d8;
  ulong local_d0;
  long local_c8;
  short local_c0;
  ulong local_b8;
  short local_b0;
  long local_a8;
  ulong local_a0;
  ulong local_98;
  short local_90;
  long local_88;
  ulong local_80;
  ulong local_78;
  short local_70;
  long local_68;
  ulong local_60;
  long local_40;
  
  uVar5 = _UNK_01000928;
  uVar4 = _UNK_01000628;
  uVar3 = _UNK_010004a8;
  uVar2 = _UNK_01000288;
  uVar1 = *param_3;
  lVar10 = *(long *)(param_6 + 0x40);
  local_d8 = *(long *)(param_6 + 0x30) + lVar10;
  local_d0 = *(long *)(param_6 + 0x48) - lVar10;
  if (param_7 <= local_d0) {
    local_60 = param_7;
    local_68 = local_d8;
    FUN_011d5760(&local_78,uVar1,param_4,param_5,&local_68,1,1);
joined_r0x011d4a75:
    if (local_70 != 0) {
      *(short *)(*param_1 + 8) = local_70;
      return param_1;
    }
    lVar10 = 0;
    if (param_5 <= local_78) {
      lVar10 = local_78 - param_5;
    }
    *(long *)(param_6 + 0x40) = *(long *)(param_6 + 0x40) + lVar10;
    goto LAB_011d4a8f;
  }
  local_40 = (long)*(int *)(param_6 + 0x50);
  lVar11 = param_6;
  if ((*(char *)(param_6 + 0x20) != '\0') &&
     (lVar11 = *(long *)(param_6 + 0x18), lVar11 == *(long *)(param_6 + 0x10))) {
    if (*(long *)(param_6 + 0x48) == lVar10) {
      *(undefined8 *)*param_1 = _DAT_01000920;
      *(undefined8 *)(*param_1 + 8) = uVar5;
      return param_1;
    }
    local_88 = local_d8;
    local_80 = local_d0;
    FUN_011d5760(&local_98,uVar1,param_4,param_5,&local_88,1,1);
    local_78 = local_98;
    local_70 = local_90;
    goto joined_r0x011d4a75;
  }
  if ((*(byte *)(param_2 + 0x35c) & 1) != 0) {
switchD_011d4be8_caseD_2:
    if ((*(byte *)(param_2 + 0x35a) & 1) != 0) {
switchD_011d4c56_caseD_2:
      *(undefined8 *)*param_1 = _DAT_01000280;
      *(undefined8 *)(*param_1 + 8) = uVar2;
      return param_1;
    }
    if (local_d0 != 0 || param_5 != 0) {
      FUN_011d5760(&local_e8,uVar1,param_4,param_5,&local_d8,1,1);
      local_78 = local_e8;
      local_70 = local_e0;
      goto joined_r0x011d4a75;
    }
    switch(*(byte *)(param_6 + 0x5e) & 7) {
    case 0:
      break;
    case 1:
      break;
    default:
      goto switchD_011d4c56_caseD_2;
    case 4:
switchD_011d4c56_caseD_4:
      uVar2 = _UNK_01000698;
      *(undefined8 *)*param_1 = _DAT_01000690;
      *(undefined8 *)(*param_1 + 8) = uVar2;
      return param_1;
    case 5:
      *(undefined8 *)*param_1 = _DAT_010004a0;
      *(undefined8 *)(*param_1 + 8) = uVar3;
      return param_1;
    case 6:
    case 7:
      *(undefined1 *)(local_d0 + 0x35a) = 1;
      goto LAB_011d4f2d;
    }
    lVar10 = *(long *)(in_FS_OFFSET + -0x40010);
    if ((lVar10 == 0) || ((*(byte *)(lVar10 + 0x21c) & 1) != 0)) {
LAB_011d4da4:
      lVar10 = 0;
    }
    else {
      uVar8 = *(ulong *)(lVar10 + 8);
      do {
        LOCK();
        uVar9 = *(ulong *)(lVar10 + 8);
        bVar12 = uVar8 == uVar9;
        if (bVar12) {
          *(ulong *)(lVar10 + 8) = uVar8 | 3;
          uVar9 = uVar8;
        }
        UNLOCK();
        uVar8 = uVar9;
      } while (!bVar12);
      if ((uVar9 & 7) != 0) {
        if (((uint)uVar9 & 7) == 6) goto LAB_011d4e20;
        goto LAB_011d4da4;
      }
    }
    if (lVar10 == 0) {
      local_78 = 0x146;
      syscall();
    }
    else {
      local_78 = 0x146;
      syscall();
      LOCK();
      *(ulong *)(lVar10 + 8) = *(ulong *)(lVar10 + 8) ^ 3;
      UNLOCK();
    }
    goto LAB_011d4fed;
  }
  if (local_d0 != 0 || param_5 != 0) {
    local_a8 = local_d8;
    local_a0 = local_d0;
    FUN_011d5760(&local_b8,uVar1,param_4,param_5,&local_a8,1,1);
    local_78 = local_b8;
    local_70 = local_b0;
    goto joined_r0x011d4a75;
  }
  switch(*(byte *)(param_6 + 0x5e) & 7) {
  case 0:
    lVar10 = *(long *)(in_FS_OFFSET + -0x40010);
    break;
  case 1:
    FUN_011ca830(&local_c8,param_6);
    if (local_c0 != 0) goto LAB_011d4f2d;
    if (*(long *)(param_6 + 0x10) < 0) goto switchD_011d4c56_caseD_4;
    lVar10 = *(long *)(in_FS_OFFSET + -0x40010);
    break;
  default:
    goto switchD_011d4be8_caseD_2;
  case 4:
    goto switchD_011d4c56_caseD_4;
  case 5:
    *(undefined8 *)*param_1 = _DAT_01000620;
    *(undefined8 *)(*param_1 + 8) = uVar4;
    return param_1;
  case 6:
    bVar6 = (*(byte *)(param_6 + 0x5e) ^ 4) & 7;
    *(byte *)(param_6 + 0x5e) = (byte)(0x480004 >> (uint)bVar6 + (uint)bVar6 * 2) & 7;
    if (*(long *)(param_6 + 0x10) != 0) {
      *(undefined8 *)(param_6 + 0x10) = 0;
      sVar7 = FUN_011ca760(param_6);
      if (sVar7 != 0) {
        *(undefined1 *)(param_6 + 0x5e) = 4;
        uVar2 = _UNK_01000698;
        *(undefined8 *)*param_1 = _DAT_01000690;
        *(undefined8 *)(*param_1 + 8) = uVar2;
        return param_1;
      }
    }
    goto LAB_011d4f2d;
  case 7:
    *(undefined1 *)(lVar11 + 0x35c) = 1;
LAB_011d4f2d:
    auVar13._0_12_ = ZEXT812(0);
    auVar13._12_4_ = 0;
    *param_1 = auVar13;
    return param_1;
  }
  if ((lVar10 == 0) || ((*(byte *)(lVar10 + 0x21c) & 1) != 0)) {
LAB_011d4cd9:
    lVar10 = 0;
  }
  else {
    uVar8 = *(ulong *)(lVar10 + 8);
    do {
      LOCK();
      uVar9 = *(ulong *)(lVar10 + 8);
      bVar12 = uVar8 == uVar9;
      if (bVar12) {
        *(ulong *)(lVar10 + 8) = uVar8 | 3;
        uVar9 = uVar8;
      }
      UNLOCK();
      uVar8 = uVar9;
    } while (!bVar12);
    if ((uVar9 & 7) != 0) {
      if (((uint)uVar9 & 7) == 6) {
LAB_011d4e20:
        *(undefined2 *)(*param_1 + 8) = 0x11;
        return param_1;
      }
      goto LAB_011d4cd9;
    }
  }
  if (lVar10 == 0) {
    local_78 = 0x28;
    syscall();
  }
  else {
    local_78 = 0x28;
    syscall();
    LOCK();
    *(ulong *)(lVar10 + 8) = *(ulong *)(lVar10 + 8) ^ 3;
    UNLOCK();
  }
LAB_011d4fed:
  if (local_78 == 0) {
    *(long *)(param_6 + 0x18) = *(long *)(param_6 + 0x10);
    *(undefined1 *)(param_6 + 0x20) = 1;
    uVar2 = _UNK_01000928;
    *(undefined8 *)*param_1 = _DAT_01000920;
    *(undefined8 *)(*param_1 + 8) = uVar2;
  }
  else {
    *(ulong *)(param_6 + 0x10) = *(long *)(param_6 + 0x10) + local_78;
LAB_011d4a8f:
    *(undefined2 *)(*param_1 + 8) = 0;
    *(ulong *)*param_1 = local_78;
  }
  return param_1;
}


// ---- FUN_011d50c0 @ 011d50c0

/* WARNING: Removing unreachable block (ram,0x011d55f9) */
/* WARNING: Removing unreachable block (ram,0x011d54d9) */
/* WARNING: Removing unreachable block (ram,0x011d54df) */

undefined1 (*) [16]
FUN_011d50c0(undefined1 (*param_1) [16],undefined8 param_2,int *param_3,ulong param_4,long param_5,
            long param_6,long param_7,ulong param_8)

{
  undefined1 *puVar1;
  long lVar2;
  ulong uVar3;
  undefined1 (*pauVar4) [16];
  ulong *puVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  long lVar9;
  long lVar10;
  long in_FS_OFFSET;
  bool bVar11;
  undefined1 auVar12 [16];
  undefined1 local_f8 [64];
  ulong local_b8 [16];
  undefined1 (*local_38) [16];
  
  if (param_5 != 0) {
    lVar7 = 1;
    lVar10 = (long)*param_3;
    local_b8[0] = param_4;
    local_b8[1] = param_5;
    if (param_7 == 1) goto LAB_011d51a8;
LAB_011d5114:
    uVar3 = param_7 - 1;
    if (param_7 - 2U < 3) {
      uVar8 = 0;
    }
    else {
      puVar5 = (ulong *)(param_6 + 0x38);
      uVar8 = 0;
      do {
        uVar6 = puVar5[-6];
        lVar9 = lVar7;
        if ((uVar6 != 0) && (lVar9 = 8, lVar7 != 8)) {
          local_b8[lVar7 * 2] = puVar5[-7];
          local_b8[lVar7 * 2 + 1] = uVar6;
          lVar9 = lVar7 + 1;
        }
        uVar6 = puVar5[-4];
        lVar7 = lVar9;
        if ((uVar6 != 0) && (lVar7 = 8, lVar9 != 8)) {
          local_b8[lVar9 * 2] = puVar5[-5];
          local_b8[lVar9 * 2 + 1] = uVar6;
          lVar7 = lVar9 + 1;
        }
        uVar6 = puVar5[-2];
        lVar9 = lVar7;
        if ((uVar6 != 0) && (lVar9 = 8, lVar7 != 8)) {
          local_b8[lVar7 * 2] = puVar5[-3];
          local_b8[lVar7 * 2 + 1] = uVar6;
          lVar9 = lVar7 + 1;
        }
        uVar6 = *puVar5;
        lVar7 = lVar9;
        if ((uVar6 != 0) && (lVar7 = 8, lVar9 != 8)) {
          local_b8[lVar9 * 2] = puVar5[-1];
          local_b8[lVar9 * 2 + 1] = uVar6;
          lVar7 = lVar9 + 1;
        }
        uVar8 = uVar8 + 4;
        puVar5 = puVar5 + 8;
      } while ((uVar3 & 0xfffffffffffffffc) != uVar8);
    }
    if ((uVar3 & 3) != 0) {
      lVar9 = uVar8 * 0x10 + param_6;
      uVar8 = 0;
      do {
        uVar6 = *(ulong *)(lVar9 + 8 + uVar8);
        lVar2 = lVar7;
        if ((uVar6 != 0) && (lVar2 = 8, lVar7 != 8)) {
          local_b8[lVar7 * 2] = *(ulong *)(lVar9 + uVar8);
          local_b8[lVar7 * 2 + 1] = uVar6;
          lVar2 = lVar7 + 1;
        }
        lVar7 = lVar2;
        uVar8 = uVar8 + 0x10;
      } while (((uint)uVar3 & 3) << 4 != uVar8);
    }
    lVar9 = 8;
    if (lVar7 != 8) goto LAB_011d51a8;
    goto LAB_011d53d5;
  }
  lVar7 = 0;
  lVar10 = (long)*param_3;
  if (param_7 != 1) goto LAB_011d5114;
LAB_011d51a8:
  lVar9 = lVar7;
  if (param_8 == 0) {
LAB_011d53cc:
    if (lVar7 == 0) {
      auVar12._0_12_ = ZEXT812(0);
      auVar12._12_4_ = 0;
      *param_1 = auVar12;
      return param_1;
    }
  }
  else {
    lVar2 = (param_7 + -1) * 0x10;
    puVar1 = *(undefined1 **)(param_6 + lVar2);
    uVar3 = *(ulong *)(param_6 + 8 + lVar2);
    if (param_8 == 1) {
      if (uVar3 != 0) {
        local_b8[lVar7 * 2] = (ulong)puVar1;
        local_b8[lVar7 * 2 + 1] = uVar3;
        lVar9 = lVar7 + 1;
        goto LAB_011d53d5;
      }
      goto LAB_011d53cc;
    }
    if (uVar3 == 0) goto LAB_011d53cc;
    if (uVar3 == 1) {
      uVar3 = 0x40;
      if (param_8 < 0x40) {
        uVar3 = param_8;
      }
      local_38 = param_1;
      FUN_011f4160(local_f8,*puVar1,uVar3);
      local_b8[lVar7 * 2] = (ulong)local_f8;
      local_b8[lVar7 * 2 + 1] = uVar3;
      param_1 = local_38;
      param_8 = param_8 - uVar3;
      lVar2 = lVar7 + 1;
      if ((param_8 < 0x41) || (lVar2 == 8)) {
        uVar3 = 0x40;
        if (param_8 < 0x40) {
          uVar3 = param_8;
        }
        lVar9 = lVar2;
        if (param_8 == 0) goto LAB_011d53d5;
      }
      else {
        puVar5 = local_b8 + lVar7 * 2 + 3;
        do {
          lVar2 = lVar7;
          puVar5[-1] = (ulong)local_f8;
          *puVar5 = 0x40;
          param_8 = param_8 - 0x40;
          lVar7 = lVar2 + 1;
          if (param_8 < 0x41) break;
          puVar5 = puVar5 + 2;
        } while (lVar2 != 6);
        uVar3 = 0x40;
        if (param_8 < 0x40) {
          uVar3 = param_8;
        }
        lVar2 = lVar2 + 2;
      }
      lVar9 = 8;
      if (lVar2 != 8) {
        local_b8[lVar2 * 2] = (ulong)local_f8;
        local_b8[lVar2 * 2 + 1] = uVar3;
        lVar9 = lVar7 + 2;
      }
    }
    else {
      uVar8 = 8U - lVar7;
      if (param_8 < 8U - lVar7) {
        uVar8 = param_8;
      }
      uVar6 = (ulong)((uint)uVar8 & 3);
      if (2 < uVar8 - 1) {
        uVar8 = uVar8 & 0xfffffffffffffffc;
        do {
          if (lVar7 == 8) {
LAB_011d55f3:
            lVar9 = 8;
          }
          else {
            local_b8[lVar7 * 2] = (ulong)puVar1;
            local_b8[lVar7 * 2 + 1] = uVar3;
            lVar9 = lVar7 + 1;
            if (lVar9 == 8) goto LAB_011d55f3;
            local_b8[lVar9 * 2] = (ulong)puVar1;
            local_b8[lVar9 * 2 + 1] = uVar3;
            lVar2 = lVar7 + 2;
            if (lVar2 == 8) goto LAB_011d55f3;
            lVar9 = 8;
            local_b8[lVar2 * 2] = (ulong)puVar1;
            local_b8[lVar2 * 2 + 1] = uVar3;
            lVar2 = lVar7 + 3;
            if (lVar2 != 8) {
              local_b8[lVar2 * 2] = (ulong)puVar1;
              local_b8[lVar2 * 2 + 1] = uVar3;
              lVar9 = lVar7 + 4;
            }
          }
          uVar8 = uVar8 - 4;
          lVar7 = lVar9;
        } while (uVar8 != 0);
      }
      for (; uVar6 != 0; uVar6 = uVar6 - 1) {
        lVar7 = 8;
        if (lVar9 != 8) {
          local_b8[lVar9 * 2] = (ulong)puVar1;
          local_b8[lVar9 * 2 + 1] = uVar3;
          lVar7 = lVar9 + 1;
        }
        lVar9 = lVar7;
      }
    }
  }
LAB_011d53d5:
  lVar7 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar7 != 0) && ((*(byte *)(lVar7 + 0x21c) & 1) == 0)) {
    uVar3 = *(ulong *)(lVar7 + 8);
    do {
      LOCK();
      uVar8 = *(ulong *)(lVar7 + 8);
      bVar11 = uVar3 == uVar8;
      if (bVar11) {
        *(ulong *)(lVar7 + 8) = uVar3 | 3;
        uVar8 = uVar3;
      }
      UNLOCK();
      uVar3 = uVar8;
    } while (!bVar11);
    if ((uVar8 & 7) == 0) goto LAB_011d541e;
    if (((uint)uVar8 & 7) == 6) {
      *(undefined2 *)(*param_1 + 8) = 0x11;
      return param_1;
    }
  }
  lVar7 = 0;
LAB_011d541e:
  if (lVar7 != 0) {
    syscall();
                    /* WARNING: Could not recover jumptable at 0x011d545a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    pauVar4 = (undefined1 (*) [16])(*(code *)PTR_LAB_010059b0)(lVar10,local_b8,lVar9,0,0);
    return pauVar4;
  }
  syscall();
                    /* WARNING: Could not recover jumptable at 0x011d54c3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pauVar4 = (undefined1 (*) [16])(*DAT_01005d88)(lVar10,local_b8,lVar9,0,0);
  return pauVar4;
}


// ---- FUN_011d5760 @ 011d5760

/* WARNING: Removing unreachable block (ram,0x011d5c8a) */
/* WARNING: Removing unreachable block (ram,0x011d5b52) */
/* WARNING: Removing unreachable block (ram,0x011d5b58) */
/* WARNING: Removing unreachable block (ram,0x011d5ae0) */
/* WARNING: Removing unreachable block (ram,0x011d5af0) */
/* WARNING: Removing unreachable block (ram,0x011d5af7) */
/* WARNING: Removing unreachable block (ram,0x011d5aff) */
/* WARNING: Removing unreachable block (ram,0x011d5b62) */
/* WARNING: Removing unreachable block (ram,0x011d5d86) */
/* WARNING: Removing unreachable block (ram,0x011d5d93) */
/* WARNING: Removing unreachable block (ram,0x011d5d6c) */
/* WARNING: Removing unreachable block (ram,0x011d5b69) */
/* WARNING: Recovered jumptable eliminated as dead code */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_011d5760(undefined1 (*param_1) [16],undefined4 param_2,ulong param_3,long param_4,
                 long param_5,long param_6,ulong param_7)

{
  undefined1 *puVar1;
  long lVar2;
  ulong uVar3;
  ulong *puVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  long lVar8;
  long in_FS_OFFSET;
  bool bVar9;
  undefined1 auVar10 [16];
  undefined1 local_100 [64];
  ulong local_c0 [16];
  undefined1 (*local_40) [16];
  undefined4 local_34;
  
  if (param_4 != 0) {
    lVar5 = 1;
    local_c0[0] = param_3;
    local_c0[1] = param_4;
    if (param_6 == 1) goto LAB_011d5838;
LAB_011d57aa:
    uVar3 = param_6 - 1;
    if (param_6 - 2U < 3) {
      uVar7 = 0;
    }
    else {
      puVar4 = (ulong *)(param_5 + 0x38);
      uVar7 = 0;
      do {
        uVar6 = puVar4[-6];
        lVar2 = lVar5;
        if ((uVar6 != 0) && (lVar2 = 8, lVar5 != 8)) {
          local_c0[lVar5 * 2] = puVar4[-7];
          local_c0[lVar5 * 2 + 1] = uVar6;
          lVar2 = lVar5 + 1;
        }
        uVar6 = puVar4[-4];
        lVar5 = lVar2;
        if ((uVar6 != 0) && (lVar5 = 8, lVar2 != 8)) {
          local_c0[lVar2 * 2] = puVar4[-5];
          local_c0[lVar2 * 2 + 1] = uVar6;
          lVar5 = lVar2 + 1;
        }
        uVar6 = puVar4[-2];
        lVar2 = lVar5;
        if ((uVar6 != 0) && (lVar2 = 8, lVar5 != 8)) {
          local_c0[lVar5 * 2] = puVar4[-3];
          local_c0[lVar5 * 2 + 1] = uVar6;
          lVar2 = lVar5 + 1;
        }
        uVar6 = *puVar4;
        lVar5 = lVar2;
        if ((uVar6 != 0) && (lVar5 = 8, lVar2 != 8)) {
          local_c0[lVar2 * 2] = puVar4[-1];
          local_c0[lVar2 * 2 + 1] = uVar6;
          lVar5 = lVar2 + 1;
        }
        uVar7 = uVar7 + 4;
        puVar4 = puVar4 + 8;
      } while ((uVar3 & 0xfffffffffffffffc) != uVar7);
    }
    if ((uVar3 & 3) != 0) {
      lVar2 = uVar7 * 0x10 + param_5;
      uVar7 = 0;
      do {
        uVar6 = *(ulong *)(lVar2 + 8 + uVar7);
        lVar8 = lVar5;
        if ((uVar6 != 0) && (lVar8 = 8, lVar5 != 8)) {
          local_c0[lVar5 * 2] = *(ulong *)(lVar2 + uVar7);
          local_c0[lVar5 * 2 + 1] = uVar6;
          lVar8 = lVar5 + 1;
        }
        lVar5 = lVar8;
        uVar7 = uVar7 + 0x10;
      } while (((uint)uVar3 & 3) << 4 != uVar7);
    }
    if (lVar5 != 8) goto LAB_011d5838;
    goto LAB_011d5a65;
  }
  lVar5 = 0;
  if (param_6 != 1) goto LAB_011d57aa;
LAB_011d5838:
  if (param_7 == 0) {
LAB_011d5a5c:
    if (lVar5 == 0) {
      auVar10._0_12_ = ZEXT812(0);
      auVar10._12_4_ = 0;
      *param_1 = auVar10;
      return;
    }
  }
  else {
    lVar2 = (param_6 + -1) * 0x10;
    puVar1 = *(undefined1 **)(param_5 + lVar2);
    uVar3 = *(ulong *)(param_5 + 8 + lVar2);
    if (param_7 == 1) {
      if (uVar3 != 0) {
        local_c0[lVar5 * 2] = (ulong)puVar1;
        local_c0[lVar5 * 2 + 1] = uVar3;
        goto LAB_011d5a65;
      }
      goto LAB_011d5a5c;
    }
    if (uVar3 == 0) goto LAB_011d5a5c;
    if (uVar3 == 1) {
      uVar3 = 0x40;
      if (param_7 < 0x40) {
        uVar3 = param_7;
      }
      local_40 = param_1;
      local_34 = param_2;
      FUN_011f4160(local_100,*puVar1,uVar3);
      local_c0[lVar5 * 2] = (ulong)local_100;
      local_c0[lVar5 * 2 + 1] = uVar3;
      param_7 = param_7 - uVar3;
      lVar2 = lVar5 + 1;
      param_1 = local_40;
      if ((param_7 < 0x41) || (lVar2 == 8)) {
        uVar3 = 0x40;
        if (param_7 < 0x40) {
          uVar3 = param_7;
        }
        if (param_7 == 0) goto LAB_011d5a65;
      }
      else {
        puVar4 = local_c0 + lVar5 * 2 + 3;
        do {
          lVar2 = lVar5;
          puVar4[-1] = (ulong)local_100;
          *puVar4 = 0x40;
          param_7 = param_7 - 0x40;
          if (param_7 < 0x41) break;
          puVar4 = puVar4 + 2;
          lVar5 = lVar2 + 1;
        } while (lVar2 != 6);
        uVar3 = 0x40;
        if (param_7 < 0x40) {
          uVar3 = param_7;
        }
        lVar2 = lVar2 + 2;
      }
      if (lVar2 != 8) {
        local_c0[lVar2 * 2] = (ulong)local_100;
        local_c0[lVar2 * 2 + 1] = uVar3;
      }
    }
    else {
      uVar7 = 8U - lVar5;
      if (param_7 < 8U - lVar5) {
        uVar7 = param_7;
      }
      uVar6 = (ulong)((uint)uVar7 & 3);
      if (2 < uVar7 - 1) {
        uVar7 = uVar7 & 0xfffffffffffffffc;
        lVar2 = lVar5;
        do {
          if (lVar2 == 8) {
LAB_011d5c84:
            lVar5 = 8;
          }
          else {
            local_c0[lVar2 * 2] = (ulong)puVar1;
            local_c0[lVar2 * 2 + 1] = uVar3;
            lVar5 = lVar2 + 1;
            if (lVar5 == 8) goto LAB_011d5c84;
            local_c0[lVar5 * 2] = (ulong)puVar1;
            local_c0[lVar5 * 2 + 1] = uVar3;
            lVar8 = lVar2 + 2;
            if (lVar8 == 8) goto LAB_011d5c84;
            lVar5 = 8;
            local_c0[lVar8 * 2] = (ulong)puVar1;
            local_c0[lVar8 * 2 + 1] = uVar3;
            lVar8 = lVar2 + 3;
            if (lVar8 != 8) {
              local_c0[lVar8 * 2] = (ulong)puVar1;
              local_c0[lVar8 * 2 + 1] = uVar3;
              lVar5 = lVar2 + 4;
            }
          }
          uVar7 = uVar7 - 4;
          lVar2 = lVar5;
        } while (uVar7 != 0);
      }
      for (; uVar6 != 0; uVar6 = uVar6 - 1) {
        lVar2 = 8;
        if (lVar5 != 8) {
          local_c0[lVar5 * 2] = (ulong)puVar1;
          local_c0[lVar5 * 2 + 1] = uVar3;
          lVar2 = lVar5 + 1;
        }
        lVar5 = lVar2;
      }
    }
  }
LAB_011d5a65:
  lVar5 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar5 != 0) && ((*(byte *)(lVar5 + 0x21c) & 1) == 0)) {
    uVar3 = *(ulong *)(lVar5 + 8);
    do {
      LOCK();
      uVar7 = *(ulong *)(lVar5 + 8);
      bVar9 = uVar3 == uVar7;
      if (bVar9) {
        *(ulong *)(lVar5 + 8) = uVar3 | 3;
        uVar7 = uVar3;
      }
      UNLOCK();
      uVar3 = uVar7;
    } while (!bVar9);
    if ((uVar7 & 7) == 0) goto LAB_011d5aae;
    if (((uint)uVar7 & 7) == 6) {
      *(undefined2 *)(*param_1 + 8) = 0x11;
      return;
    }
  }
  lVar5 = 0;
LAB_011d5aae:
  if (lVar5 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar5 + 8) = *(ulong *)(lVar5 + 8) ^ 3;
    UNLOCK();
  }
  *(undefined2 *)(*param_1 + 8) = 0;
  *(undefined8 *)*param_1 = 0x14;
  return;
}


// ---- FUN_011d5da0 @ 011d5da0

void FUN_011d5da0(undefined8 param_1,undefined8 param_2,long param_3)

{
  long lVar1;
  
  if (param_3 != 0) {
    lVar1 = 0;
    do {
      syscall();
      lVar1 = lVar1 + 1;
    } while (param_3 != lVar1);
  }
  return;
}


// ---- FUN_011d5dd0 @ 011d5dd0

/* WARNING: Removing unreachable block (ram,0x011d5f70) */
/* WARNING: Removing unreachable block (ram,0x011d5f76) */
/* WARNING: Removing unreachable block (ram,0x011d5ea4) */
/* WARNING: Removing unreachable block (ram,0x011d5eb0) */
/* WARNING: Removing unreachable block (ram,0x011d5eb7) */
/* WARNING: Removing unreachable block (ram,0x011d5ebf) */
/* WARNING: Removing unreachable block (ram,0x011d5f91) */
/* WARNING: Removing unreachable block (ram,0x011d5f81) */
/* WARNING: Removing unreachable block (ram,0x011d5fb4) */
/* WARNING: Removing unreachable block (ram,0x011d5f88) */
/* WARNING: Recovered jumptable eliminated as dead code */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1  [16] FUN_011d5dd0(undefined8 *param_1,undefined8 param_2,undefined8 param_3)

{
  undefined8 uVar1;
  ulong uVar2;
  ulong uVar3;
  long lVar4;
  long in_FS_OFFSET;
  bool bVar5;
  undefined1 auVar6 [16];
  
  lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar4 == 0) || ((*(byte *)(lVar4 + 0x21c) & 1) != 0)) {
LAB_011d5e1f:
    lVar4 = 0;
  }
  else {
    uVar2 = *(ulong *)(lVar4 + 8);
    do {
      LOCK();
      uVar3 = *(ulong *)(lVar4 + 8);
      bVar5 = uVar2 == uVar3;
      if (bVar5) {
        *(ulong *)(lVar4 + 8) = uVar2 | 3;
        uVar3 = uVar2;
      }
      UNLOCK();
      uVar2 = uVar3;
    } while (!bVar5);
    if ((uVar3 & 7) != 0) {
      if (((uint)uVar3 & 7) == 6) {
        *(undefined2 *)(param_1 + 1) = 0x11;
        goto LAB_011d5fa2;
      }
      goto LAB_011d5e1f;
    }
  }
  if (lVar4 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar4 + 8) = *(ulong *)(lVar4 + 8) ^ 3;
    UNLOCK();
  }
  uVar1 = _UNK_01000328;
  param_3 = 0x1000;
  *param_1 = _DAT_01000320;
  param_1[1] = uVar1;
LAB_011d5fa2:
  auVar6._8_8_ = param_3;
  auVar6._0_8_ = param_1;
  return auVar6;
}


// ---- FUN_011d5fc0 @ 011d5fc0

/* WARNING: Removing unreachable block (ram,0x011d61d3) */
/* WARNING: Removing unreachable block (ram,0x011d61d9) */
/* WARNING: Removing unreachable block (ram,0x011d6211) */
/* WARNING: Removing unreachable block (ram,0x011d60a7) */
/* WARNING: Removing unreachable block (ram,0x011d60b0) */
/* WARNING: Removing unreachable block (ram,0x011d60b7) */
/* WARNING: Removing unreachable block (ram,0x011d60bf) */
/* WARNING: Removing unreachable block (ram,0x011d6277) */
/* WARNING: Removing unreachable block (ram,0x011d61e4) */
/* WARNING: Removing unreachable block (ram,0x011d6311) */
/* WARNING: Removing unreachable block (ram,0x011d61eb) */
/* WARNING: Recovered jumptable eliminated as dead code */
/* WARNING: Removing unreachable block (ram,0x011d6170) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 * FUN_011d5fc0(undefined8 *param_1,undefined8 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  ulong uVar2;
  ulong uVar3;
  long lVar4;
  undefined8 unaff_R14;
  undefined8 unaff_R15;
  long in_FS_OFFSET;
  bool bVar5;
  undefined8 in_rflags;
  undefined1 auVar6 [16];
  undefined1 local_138 [280];
  
  uVar1 = *param_3;
  lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar4 != 0) && ((*(byte *)(lVar4 + 0x21c) & 1) == 0)) {
    uVar2 = *(ulong *)(lVar4 + 8);
    do {
      LOCK();
      uVar3 = *(ulong *)(lVar4 + 8);
      bVar5 = uVar2 == uVar3;
      if (bVar5) {
        *(ulong *)(lVar4 + 8) = uVar2 | 3;
        uVar3 = uVar2;
      }
      UNLOCK();
      uVar2 = uVar3;
    } while (!bVar5);
    if ((uVar3 & 7) == 0) goto LAB_011d6021;
    if (((uint)uVar3 & 7) == 6) {
      *(undefined2 *)(param_1 + 0xc) = 0x11;
      return param_1;
    }
  }
  lVar4 = 0;
LAB_011d6021:
  auVar6._0_12_ = ZEXT812(0);
  auVar6._12_4_ = 0;
  if (lVar4 == 0) {
    syscall();
  }
  else {
    unaff_R14 = 0;
    syscall();
    LOCK();
    *(ulong *)(lVar4 + 8) = *(ulong *)(lVar4 + 8) ^ 3;
    UNLOCK();
  }
  *param_1 = in_rflags;
  *(undefined4 *)(param_1 + 1) = 0;
  *(undefined4 *)((long)param_1 + 0xc) = 0;
  *(undefined1 *)(param_1 + 2) = 0xe7;
  *(undefined8 *)((long)param_1 + 0x11) = 0;
  param_1[3] = 0;
  *(undefined4 *)(param_1 + 5) = 0x11b9af0;
  param_1[4] = unaff_R15;
  *(undefined4 *)((long)param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 7) = 0x1000;
  param_1[6] = unaff_R14;
  *(undefined4 *)((long)param_1 + 0x3c) = 0;
  *(undefined1 (*) [16])(param_1 + 8) = auVar6;
  *(int *)(param_1 + 10) = (int)local_138;
  *(undefined4 *)((long)param_1 + 0x54) = uVar1;
  *(undefined4 *)(param_1 + 0xb) = 0;
  *(undefined1 *)((long)param_1 + 0x5c) = 0;
  *(undefined2 *)((long)param_1 + 0x5d) = 0;
  *(undefined1 *)((long)param_1 + 0x5f) = 0;
  *(undefined2 *)(param_1 + 0xc) = 4;
  *(undefined8 *)((long)param_1 + 0x62) = 0;
  param_1[0xd] = 0;
  return param_1;
}


// ---- FUN_011d6350 @ 011d6350

undefined8
FUN_011d6350(undefined8 param_1,undefined4 *param_2,long param_3,ulong param_4,undefined4 *param_5,
            long param_6,ulong param_7,byte *param_8)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 auVar3 [32];
  long lVar4;
  undefined8 uVar5;
  ulong uVar6;
  ulong uVar7;
  undefined1 local_2031 [4096];
  undefined1 local_1031 [4096];
  byte local_31;
  
  uVar1 = *param_2;
  uVar2 = *param_5;
  local_31 = *param_8;
  lVar4 = 0;
  uVar6 = param_4;
  if (0x1f < param_4) {
    do {
      auVar3 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])(param_3 + lVar4));
      if ((((((((((((((((((((((((((((((((SUB321(auVar3 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar3 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar3 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar3 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar3 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar3 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar3 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar3 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar3 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar3 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar3 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar3 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar3 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar3 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar3 >> 0x77,0) & 1) != 0) || SUB321(auVar3 >> 0x7f,0) != '\0')
                        || (SUB321(auVar3 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar3 >> 0x8f,0) & 1) != 0) || (SUB321(auVar3 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar3 >> 0x9f,0) & 1) != 0) || (SUB321(auVar3 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar3 >> 0xaf,0) & 1) != 0) || (SUB321(auVar3 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar3 >> 0xbf,0) != '\0') || (SUB321(auVar3 >> 199,0) & 1) != 0) ||
               (SUB321(auVar3 >> 0xcf,0) & 1) != 0) || (SUB321(auVar3 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar3 >> 0xdf,0) & 1) != 0) || (SUB321(auVar3 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar3 >> 0xef,0) & 1) != 0) || (SUB321(auVar3 >> 0xf7,0) & 1) != 0) ||
          auVar3[0x1f] < '\0') {
        return 0x32;
      }
      lVar4 = lVar4 + 0x20;
      uVar6 = uVar6 - 0x20;
    } while (0x1f < uVar6);
  }
  if (uVar6 != 0) {
    uVar7 = 0;
    do {
      if (*(char *)(lVar4 + param_3 + uVar7) == '\0') {
        return 0x32;
      }
      uVar7 = uVar7 + 1;
    } while (uVar6 != uVar7);
  }
  uVar5 = 0x31;
  if (param_4 < 0x1000) {
    FUN_011f4580(local_1031,param_3,param_4);
    local_1031[param_4] = 0;
    lVar4 = 0;
    uVar6 = param_7;
    if (0x1f < param_7) {
      do {
        auVar3 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                               *(undefined1 (*) [32])(param_6 + lVar4));
        if ((((((((((((((((((((((((((((((((SUB321(auVar3 >> 7,0) & 1) != 0 ||
                                         (SUB321(auVar3 >> 0xf,0) & 1) != 0) ||
                                        (SUB321(auVar3 >> 0x17,0) & 1) != 0) ||
                                       (SUB321(auVar3 >> 0x1f,0) & 1) != 0) ||
                                      (SUB321(auVar3 >> 0x27,0) & 1) != 0) ||
                                     (SUB321(auVar3 >> 0x2f,0) & 1) != 0) ||
                                    (SUB321(auVar3 >> 0x37,0) & 1) != 0) ||
                                   (SUB321(auVar3 >> 0x3f,0) & 1) != 0) ||
                                  (SUB321(auVar3 >> 0x47,0) & 1) != 0) ||
                                 (SUB321(auVar3 >> 0x4f,0) & 1) != 0) ||
                                (SUB321(auVar3 >> 0x57,0) & 1) != 0) ||
                               (SUB321(auVar3 >> 0x5f,0) & 1) != 0) ||
                              (SUB321(auVar3 >> 0x67,0) & 1) != 0) ||
                             (SUB321(auVar3 >> 0x6f,0) & 1) != 0) ||
                            (SUB321(auVar3 >> 0x77,0) & 1) != 0) || SUB321(auVar3 >> 0x7f,0) != '\0'
                           ) || (SUB321(auVar3 >> 0x87,0) & 1) != 0) ||
                         (SUB321(auVar3 >> 0x8f,0) & 1) != 0) || (SUB321(auVar3 >> 0x97,0) & 1) != 0
                        ) || (SUB321(auVar3 >> 0x9f,0) & 1) != 0) ||
                      (SUB321(auVar3 >> 0xa7,0) & 1) != 0) || (SUB321(auVar3 >> 0xaf,0) & 1) != 0)
                    || (SUB321(auVar3 >> 0xb7,0) & 1) != 0) || SUB321(auVar3 >> 0xbf,0) != '\0') ||
                  (SUB321(auVar3 >> 199,0) & 1) != 0) || (SUB321(auVar3 >> 0xcf,0) & 1) != 0) ||
                (SUB321(auVar3 >> 0xd7,0) & 1) != 0) || (SUB321(auVar3 >> 0xdf,0) & 1) != 0) ||
              (SUB321(auVar3 >> 0xe7,0) & 1) != 0) || (SUB321(auVar3 >> 0xef,0) & 1) != 0) ||
            (SUB321(auVar3 >> 0xf7,0) & 1) != 0) || auVar3[0x1f] < '\0') {
          return 0x32;
        }
        lVar4 = lVar4 + 0x20;
        uVar6 = uVar6 - 0x20;
      } while (0x1f < uVar6);
    }
    if (uVar6 != 0) {
      uVar7 = 0;
      do {
        if (*(char *)(lVar4 + param_6 + uVar7) == '\0') {
          return 0x32;
        }
        uVar7 = uVar7 + 1;
      } while (uVar6 != uVar7);
    }
    uVar5 = 0x31;
    if (param_7 < 0x1000) {
      FUN_011f4580(local_2031,param_6,param_7);
      local_2031[param_7] = 0;
      uVar5 = FUN_011d2f80(uVar1,local_1031,uVar2,local_2031,(ulong)local_31 << 10);
    }
  }
  return uVar5;
}


// ---- FUN_011d64f0 @ 011d64f0

/* WARNING: Removing unreachable block (ram,0x011d682a) */
/* WARNING: Removing unreachable block (ram,0x011d682f) */
/* WARNING: Removing unreachable block (ram,0x011d6834) */
/* WARNING: Removing unreachable block (ram,0x011d67b6) */
/* WARNING: Removing unreachable block (ram,0x011d67c0) */
/* WARNING: Removing unreachable block (ram,0x011d67c7) */
/* WARNING: Removing unreachable block (ram,0x011d67cf) */
/* WARNING: Removing unreachable block (ram,0x011d67de) */
/* WARNING: Removing unreachable block (ram,0x011d6846) */

undefined1  [16]
FUN_011d64f0(undefined8 param_1,int *param_2,long *param_3,ulong param_4,ulong *param_5)

{
  byte bVar1;
  byte bVar2;
  ulong uVar3;
  ulong uVar4;
  undefined1 auVar5 [32];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  long lVar8;
  undefined8 uVar9;
  long *plVar10;
  ulong uVar11;
  ulong uVar12;
  uint uVar13;
  ulong uVar14;
  long *plVar15;
  long in_FS_OFFSET;
  bool bVar16;
  undefined1 auVar17 [16];
  undefined1 auVar18 [12];
  undefined1 local_1088 [4096];
  long local_88;
  long lStack_80;
  long local_78;
  long lStack_70;
  long *local_68;
  ulong local_60;
  ulong local_58;
  long local_50;
  long local_48;
  long local_40;
  byte local_31;
  
  local_40 = (long)*param_2;
  bVar1 = (byte)param_5[2];
  bVar2 = (byte)param_5[6];
  uVar13 = (uint)(byte)param_5[8];
  uVar11 = param_4;
  if (((bVar1 ^ 1 | bVar2 ^ 1) & 3) == 0) {
    plVar10 = (long *)0x0;
    if (0x1f < param_4) goto LAB_011d6694;
LAB_011d6540:
    lVar8 = 0;
  }
  else {
    uVar12 = param_5[5];
    uVar14 = param_5[4];
    plVar15 = (long *)&DAT_01000810;
    plVar10 = (long *)&DAT_01000810;
    if ((bVar1 & 3) != 0) {
      if ((bVar1 & 3) == 2) {
        uVar3 = *param_5;
        uVar4 = param_5[1];
        local_68 = param_3;
        local_60 = uVar14;
        local_58 = uVar12;
        local_31 = (byte)param_5[8];
        auVar18 = FUN_011f6850(uVar3,(long)(int)uVar4,1000000000,0);
        auVar6._8_8_ = 0;
        auVar6._0_8_ = auVar18._0_8_;
        uVar12 = SUB168(auVar6 * ZEXT816(1000000000),0);
        uVar13 = (uint)local_31;
        lVar8 = (long)(int)(((int)uVar4 -
                            (auVar18._8_4_ * 1000000000 + SUB164(auVar6 * ZEXT816(1000000000),8))) -
                           (uint)(uVar3 < uVar12)) >> 0x1f;
        local_50 = auVar18._0_8_ + lVar8;
        local_48 = (ulong)((uint)lVar8 & 1000000000) + (uVar3 - uVar12);
        plVar10 = &local_50;
        param_3 = local_68;
        uVar12 = local_58;
        uVar14 = local_60;
      }
      else {
        plVar10 = (long *)&DAT_010007a0;
      }
    }
    local_88 = *plVar10;
    lStack_80 = plVar10[1];
    if ((bVar2 & 3) != 0) {
      if ((bVar2 & 3) == 2) {
        auVar18 = FUN_011f6850(uVar14,(long)(int)uVar12,1000000000,0);
        auVar7._8_8_ = 0;
        auVar7._0_8_ = auVar18._0_8_;
        uVar3 = SUB168(auVar7 * ZEXT816(1000000000),0);
        lVar8 = (long)(int)(((int)uVar12 -
                            (auVar18._8_4_ * 1000000000 + SUB164(auVar7 * ZEXT816(1000000000),8))) -
                           (uint)(uVar14 < uVar3)) >> 0x1f;
        local_50 = auVar18._0_8_ + lVar8;
        local_48 = (ulong)((uint)lVar8 & 1000000000) + (uVar14 - uVar3);
        plVar15 = &local_50;
      }
      else {
        plVar15 = (long *)&DAT_010007a0;
      }
    }
    local_78 = *plVar15;
    lStack_70 = plVar15[1];
    plVar10 = &local_88;
    if (param_4 < 0x20) goto LAB_011d6540;
LAB_011d6694:
    lVar8 = 0;
    do {
      auVar5 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])((long)param_3 + lVar8));
      if ((((((((((((((((((((((((((((((((SUB321(auVar5 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar5 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar5 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar5 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar5 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar5 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar5 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar5 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar5 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar5 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar5 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar5 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar5 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar5 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar5 >> 0x77,0) & 1) != 0) || SUB321(auVar5 >> 0x7f,0) != '\0')
                        || (SUB321(auVar5 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar5 >> 0x8f,0) & 1) != 0) || (SUB321(auVar5 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar5 >> 0x9f,0) & 1) != 0) || (SUB321(auVar5 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar5 >> 0xaf,0) & 1) != 0) || (SUB321(auVar5 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar5 >> 0xbf,0) != '\0') || (SUB321(auVar5 >> 199,0) & 1) != 0) ||
               (SUB321(auVar5 >> 0xcf,0) & 1) != 0) || (SUB321(auVar5 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar5 >> 0xdf,0) & 1) != 0) || (SUB321(auVar5 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar5 >> 0xef,0) & 1) != 0) || (SUB321(auVar5 >> 0xf7,0) & 1) != 0) ||
          auVar5[0x1f] < '\0') goto LAB_011d6757;
      lVar8 = lVar8 + 0x20;
      uVar11 = uVar11 - 0x20;
    } while (0x1f < uVar11);
  }
  if (uVar11 != 0) {
    lVar8 = lVar8 + (long)param_3;
    uVar12 = 0;
    do {
      if (*(char *)(lVar8 + uVar12) == '\0') goto LAB_011d6757;
      uVar12 = uVar12 + 1;
    } while (uVar11 != uVar12);
  }
  uVar9 = CONCAT62((int6)((ulong)lVar8 >> 0x10),0x31);
  if (0xfff < param_4) goto LAB_011d675b;
  FUN_011f4580(local_1088,param_3,param_4);
  local_1088[param_4] = 0;
  lVar8 = *(long *)(in_FS_OFFSET + -0x40010);
  if (lVar8 == 0) {
    lVar8 = 0;
  }
  else {
    if ((*(byte *)(lVar8 + 0x21c) & 1) == 0) {
      uVar11 = *(ulong *)(lVar8 + 8);
      do {
        LOCK();
        uVar12 = *(ulong *)(lVar8 + 8);
        bVar16 = uVar11 == uVar12;
        if (bVar16) {
          *(ulong *)(lVar8 + 8) = uVar11 | 3;
          uVar12 = uVar11;
        }
        UNLOCK();
        uVar11 = uVar12;
      } while (!bVar16);
      if ((uVar12 & 7) == 0) goto LAB_011d6775;
      uVar9 = 0x11;
      param_3 = (long *)(ulong)uVar13;
      if (((uint)uVar12 & 7) == 6) goto LAB_011d675b;
    }
    lVar8 = 0;
  }
LAB_011d6775:
  param_3 = plVar10;
  if (lVar8 == 0) {
    uVar9 = 0;
    syscall();
  }
  else {
    syscall();
                    /* WARNING: Could not find normalized switch variable to match jumptable */
    switch(switchD_011d67ea::switchdataD_010067a0) {
    case (undefined *)0x0:
                    /* WARNING: This code block may not be properly labeled as switch case */
      LOCK();
      *(ulong *)(lVar8 + 8) = *(ulong *)(lVar8 + 8) ^ 3;
      UNLOCK();
      uVar9 = 0;
      break;
    default:
                    /* WARNING: This code block may not be properly labeled as switch case */
      LOCK();
      *(ulong *)(lVar8 + 8) = *(ulong *)(lVar8 + 8) ^ 3;
      UNLOCK();
      uVar9 = 4;
    }
  }
LAB_011d675b:
  auVar17._8_8_ = param_3;
  auVar17._0_8_ = uVar9;
  return auVar17;
LAB_011d6757:
  uVar9 = CONCAT62((int6)((ulong)lVar8 >> 0x10),0x32);
  goto LAB_011d675b;
}


// ---- FUN_011d6890 @ 011d6890

/* WARNING: Removing unreachable block (ram,0x011d6bba) */
/* WARNING: Removing unreachable block (ram,0x011d6bc0) */
/* WARNING: Removing unreachable block (ram,0x011d6b5b) */
/* WARNING: Removing unreachable block (ram,0x011d6b61) */
/* WARNING: Removing unreachable block (ram,0x011d6b6f) */
/* WARNING: Removing unreachable block (ram,0x011d6c2b) */
/* WARNING: Removing unreachable block (ram,0x011d6c22) */
/* WARNING: Removing unreachable block (ram,0x011d69d5) */
/* WARNING: Removing unreachable block (ram,0x011d69e0) */
/* WARNING: Removing unreachable block (ram,0x011d69e7) */
/* WARNING: Removing unreachable block (ram,0x011d69ef) */
/* WARNING: Removing unreachable block (ram,0x011d69fe) */
/* WARNING: Removing unreachable block (ram,0x011d6ad1) */
/* WARNING: Removing unreachable block (ram,0x011d6ae0) */
/* WARNING: Removing unreachable block (ram,0x011d6ae7) */
/* WARNING: Removing unreachable block (ram,0x011d6aef) */
/* WARNING: Removing unreachable block (ram,0x011d6afe) */
/* WARNING: Removing unreachable block (ram,0x011d6bca) */
/* WARNING: Removing unreachable block (ram,0x011d6bda) */
/* WARNING: Removing unreachable block (ram,0x011d6bd1) */
/* WARNING: Removing unreachable block (ram,0x011d6c07) */
/* WARNING: Removing unreachable block (ram,0x011d6c19) */
/* WARNING: Recovered jumptable eliminated as dead code */

undefined8
FUN_011d6890(long param_1,undefined4 *param_2,long param_3,ulong param_4,undefined4 param_5,
            char *param_6)

{
  undefined4 uVar1;
  undefined1 auVar2 [32];
  long lVar3;
  undefined8 uVar4;
  ulong uVar5;
  ulong uVar6;
  long in_FS_OFFSET;
  bool bVar7;
  undefined1 local_1029 [4096];
  char local_29;
  
  uVar1 = *param_2;
  local_29 = *param_6;
  lVar3 = 0;
  uVar5 = param_4;
  if (0x1f < param_4) {
    do {
      auVar2 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])(param_3 + lVar3));
      if ((((((((((((((((((((((((((((((((SUB321(auVar2 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar2 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar2 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar2 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar2 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar2 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar2 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar2 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar2 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar2 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar2 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar2 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar2 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar2 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar2 >> 0x77,0) & 1) != 0) || SUB321(auVar2 >> 0x7f,0) != '\0')
                        || (SUB321(auVar2 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar2 >> 0x8f,0) & 1) != 0) || (SUB321(auVar2 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar2 >> 0x9f,0) & 1) != 0) || (SUB321(auVar2 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar2 >> 0xaf,0) & 1) != 0) || (SUB321(auVar2 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar2 >> 0xbf,0) != '\0') || (SUB321(auVar2 >> 199,0) & 1) != 0) ||
               (SUB321(auVar2 >> 0xcf,0) & 1) != 0) || (SUB321(auVar2 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar2 >> 0xdf,0) & 1) != 0) || (SUB321(auVar2 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar2 >> 0xef,0) & 1) != 0) || (SUB321(auVar2 >> 0xf7,0) & 1) != 0) ||
          auVar2[0x1f] < '\0') goto LAB_011d6a00;
      lVar3 = lVar3 + 0x20;
      uVar5 = uVar5 - 0x20;
    } while (0x1f < uVar5);
  }
  if (uVar5 != 0) {
    lVar3 = lVar3 + param_3;
    uVar6 = 0;
    do {
      if (*(char *)(lVar3 + uVar6) == '\0') {
LAB_011d6a00:
        return CONCAT62((int6)((ulong)lVar3 >> 0x10),0x32);
      }
      uVar6 = uVar6 + 1;
    } while (uVar5 != uVar6);
  }
  if (0xfff < param_4) {
    return CONCAT62((int6)((ulong)lVar3 >> 0x10),0x31);
  }
  FUN_011f4580(local_1029,param_3,param_4);
  local_1029[param_4] = 0;
  if (local_29 != '\x01') {
    if ((*(byte *)(param_1 + 0x359) & 1) != 0) {
      uVar4 = FUN_011d6c60(uVar1,local_1029,param_5);
      return uVar4;
    }
    lVar3 = *(long *)(in_FS_OFFSET + -0x40010);
    if ((lVar3 != 0) && ((*(byte *)(lVar3 + 0x21c) & 1) == 0)) {
      uVar5 = *(ulong *)(lVar3 + 8);
      do {
        LOCK();
        uVar6 = *(ulong *)(lVar3 + 8);
        bVar7 = uVar5 == uVar6;
        if (bVar7) {
          *(ulong *)(lVar3 + 8) = uVar5 | 3;
          uVar6 = uVar5;
        }
        UNLOCK();
        uVar5 = uVar6;
      } while (!bVar7);
      if ((uVar6 & 7) == 0) goto LAB_011d6a85;
      if (((uint)uVar6 & 7) == 6) {
        return 0x11;
      }
    }
    lVar3 = 0;
LAB_011d6a85:
    if (lVar3 == 0) {
      syscall();
      return 0;
    }
    syscall();
    LOCK();
    *(ulong *)(lVar3 + 8) = *(ulong *)(lVar3 + 8) ^ 3;
    UNLOCK();
    return 0;
  }
  lVar3 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar3 != 0) && ((*(byte *)(lVar3 + 0x21c) & 1) == 0)) {
    uVar5 = *(ulong *)(lVar3 + 8);
    do {
      LOCK();
      uVar6 = *(ulong *)(lVar3 + 8);
      bVar7 = uVar5 == uVar6;
      if (bVar7) {
        *(ulong *)(lVar3 + 8) = uVar5 | 3;
        uVar6 = uVar5;
      }
      UNLOCK();
      uVar5 = uVar6;
    } while (!bVar7);
    if ((uVar6 & 7) == 0) goto LAB_011d6995;
    if (((uint)uVar6 & 7) == 6) {
      return 0x11;
    }
  }
  lVar3 = 0;
LAB_011d6995:
  if (lVar3 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar3 + 8) = *(ulong *)(lVar3 + 8) ^ 3;
    UNLOCK();
  }
  return 0;
}


// ---- FUN_011d6c50 @ 011d6c50

void FUN_011d6c50(undefined8 param_1,undefined4 *param_2,undefined4 param_3)

{
  FUN_011d39c0(*param_2,param_3);
  return;
}


// ---- FUN_011d6c60 @ 011d6c60

/* WARNING: Removing unreachable block (ram,0x011d6e3f) */
/* WARNING: Removing unreachable block (ram,0x011d6e50) */
/* WARNING: Removing unreachable block (ram,0x011d6e57) */
/* WARNING: Removing unreachable block (ram,0x011d6e5f) */
/* WARNING: Removing unreachable block (ram,0x011d6e6b) */
/* WARNING: Removing unreachable block (ram,0x011d70b6) */
/* WARNING: Removing unreachable block (ram,0x011d7045) */
/* WARNING: Removing unreachable block (ram,0x011d7050) */
/* WARNING: Removing unreachable block (ram,0x011d7057) */
/* WARNING: Removing unreachable block (ram,0x011d705f) */
/* WARNING: Removing unreachable block (ram,0x011d7067) */
/* WARNING: Removing unreachable block (ram,0x011d6f2c) */
/* WARNING: Removing unreachable block (ram,0x011d6fb4) */
/* WARNING: Removing unreachable block (ram,0x011d6fe0) */
/* WARNING: Removing unreachable block (ram,0x011d6fe9) */
/* WARNING: Removing unreachable block (ram,0x011d6ff0) */
/* WARNING: Removing unreachable block (ram,0x011d6ff7) */
/* WARNING: Removing unreachable block (ram,0x011d6fff) */
/* WARNING: Removing unreachable block (ram,0x011d7003) */
/* WARNING: Removing unreachable block (ram,0x011d700b) */
/* WARNING: Removing unreachable block (ram,0x011d701a) */
/* WARNING: Removing unreachable block (ram,0x011d701c) */
/* WARNING: Removing unreachable block (ram,0x011d7024) */
/* WARNING: Removing unreachable block (ram,0x011d7027) */
/* WARNING: Removing unreachable block (ram,0x011d7076) */
/* WARNING: Removing unreachable block (ram,0x011d707b) */
/* WARNING: Removing unreachable block (ram,0x011d7083) */
/* WARNING: Removing unreachable block (ram,0x011d7085) */
/* WARNING: Removing unreachable block (ram,0x011d70a3) */
/* WARNING: Removing unreachable block (ram,0x011d70a8) */
/* WARNING: Removing unreachable block (ram,0x011d70bc) */
/* WARNING: Removing unreachable block (ram,0x011d70d5) */
/* WARNING: Removing unreachable block (ram,0x011d7103) */
/* WARNING: Removing unreachable block (ram,0x011d70dc) */
/* WARNING: Removing unreachable block (ram,0x011d6f3f) */
/* WARNING: Removing unreachable block (ram,0x011d6f52) */
/* WARNING: Removing unreachable block (ram,0x011d6f58) */
/* WARNING: Removing unreachable block (ram,0x011d6f6c) */
/* WARNING: Removing unreachable block (ram,0x011d6f78) */
/* WARNING: Recovered jumptable eliminated as dead code */
/* WARNING: Removing unreachable block (ram,0x011d6e7e) */
/* WARNING: Removing unreachable block (ram,0x011d6cf1) */
/* WARNING: Removing unreachable block (ram,0x011d6d00) */
/* WARNING: Removing unreachable block (ram,0x011d6d07) */
/* WARNING: Removing unreachable block (ram,0x011d6d0f) */
/* WARNING: Removing unreachable block (ram,0x011d6d17) */
/* WARNING: Removing unreachable block (ram,0x011d6e92) */
/* WARNING: Removing unreachable block (ram,0x011d6f7d) */
/* WARNING: Removing unreachable block (ram,0x011d6fa2) */
/* WARNING: Removing unreachable block (ram,0x011d6f99) */
/* WARNING: Removing unreachable block (ram,0x011d6fab) */
/* WARNING: Removing unreachable block (ram,0x011d70e2) */
/* WARNING: Removing unreachable block (ram,0x011d70e8) */
/* WARNING: Removing unreachable block (ram,0x011d70ee) */
/* WARNING: Removing unreachable block (ram,0x011d6e99) */

undefined1  [16] FUN_011d6c60(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  undefined8 uVar1;
  ulong uVar2;
  ulong uVar3;
  long lVar4;
  long in_FS_OFFSET;
  bool bVar5;
  undefined1 auVar6 [16];
  
  lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar4 == 0) || ((*(byte *)(lVar4 + 0x21c) & 1) != 0)) {
LAB_011d6cb6:
    lVar4 = 0;
  }
  else {
    uVar2 = *(ulong *)(lVar4 + 8);
    do {
      LOCK();
      uVar3 = *(ulong *)(lVar4 + 8);
      bVar5 = uVar2 == uVar3;
      if (bVar5) {
        *(ulong *)(lVar4 + 8) = uVar2 | 3;
        uVar3 = uVar2;
      }
      UNLOCK();
      uVar2 = uVar3;
    } while (!bVar5);
    if ((uVar3 & 7) != 0) {
      uVar1 = 0x11;
      if (((uint)uVar3 & 7) == 6) goto LAB_011d70f2;
      goto LAB_011d6cb6;
    }
  }
  if (lVar4 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar4 + 8) = *(ulong *)(lVar4 + 8) ^ 3;
    UNLOCK();
  }
  lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar4 == 0) || ((*(byte *)(lVar4 + 0x21c) & 1) != 0)) {
LAB_011d6dba:
    lVar4 = 0;
  }
  else {
    uVar2 = *(ulong *)(lVar4 + 8);
    do {
      LOCK();
      uVar3 = *(ulong *)(lVar4 + 8);
      bVar5 = uVar2 == uVar3;
      if (bVar5) {
        *(ulong *)(lVar4 + 8) = uVar2 | 3;
        uVar3 = uVar2;
      }
      UNLOCK();
      uVar2 = uVar3;
    } while (!bVar5);
    if ((uVar3 & 7) != 0) {
      if (((uint)uVar3 & 7) == 6) {
        syscall();
        param_3 = 0x2a0000;
        uVar1 = 0x11;
        goto LAB_011d70f2;
      }
      goto LAB_011d6dba;
    }
  }
  if (lVar4 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar4 + 8) = *(ulong *)(lVar4 + 8) ^ 3;
    UNLOCK();
  }
  syscall();
  param_3 = 0;
  uVar1 = 4;
LAB_011d70f2:
  auVar6._8_8_ = param_3;
  auVar6._0_8_ = uVar1;
  return auVar6;
}


// ---- FUN_011d7110 @ 011d7110

void FUN_011d7110(undefined8 param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = 0xffffffff;
  uVar2 = 0xffffffff;
  if (*(char *)(param_3 + 1) != '\0') {
    uVar2 = *param_3;
  }
  if (*(char *)(param_4 + 1) != '\0') {
    uVar1 = *param_4;
  }
  FUN_011d3c20(*param_2,uVar2,uVar1);
  return;
}


// ---- FUN_011d7140 @ 011d7140

/* WARNING: Removing unreachable block (ram,0x011d730a) */
/* WARNING: Removing unreachable block (ram,0x011d7283) */
/* WARNING: Removing unreachable block (ram,0x011d7290) */
/* WARNING: Removing unreachable block (ram,0x011d7297) */
/* WARNING: Removing unreachable block (ram,0x011d729f) */
/* WARNING: Removing unreachable block (ram,0x011d72a7) */
/* WARNING: Removing unreachable block (ram,0x011d7302) */
/* WARNING: Removing unreachable block (ram,0x011d730d) */
/* WARNING: Removing unreachable block (ram,0x011d7320) */
/* WARNING: Removing unreachable block (ram,0x011d73c5) */
/* WARNING: Removing unreachable block (ram,0x011d738c) */
/* WARNING: Removing unreachable block (ram,0x011d7379) */
/* WARNING: Removing unreachable block (ram,0x011d7353) */
/* WARNING: Removing unreachable block (ram,0x011d73b2) */
/* WARNING: Removing unreachable block (ram,0x011d739f) */
/* WARNING: Removing unreachable block (ram,0x011d733d) */
/* WARNING: Removing unreachable block (ram,0x011d7366) */
/* WARNING: Removing unreachable block (ram,0x011d7327) */
/* WARNING: Recovered jumptable eliminated as dead code */

void FUN_011d7140(ulong *param_1,undefined8 param_2,undefined8 param_3,ulong param_4,ulong param_5)

{
  undefined1 auVar1 [32];
  undefined2 uVar2;
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  long in_FS_OFFSET;
  bool bVar6;
  undefined1 local_1030 [4096];
  undefined4 local_30;
  undefined2 local_2c;
  
  lVar3 = 0;
  uVar4 = param_5;
  if (0x1f < param_5) {
    do {
      auVar1 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])(param_4 + lVar3));
      if ((((((((((((((((((((((((((((((((SUB321(auVar1 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar1 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar1 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar1 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar1 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar1 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar1 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar1 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar1 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar1 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar1 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar1 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar1 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar1 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar1 >> 0x77,0) & 1) != 0) || SUB321(auVar1 >> 0x7f,0) != '\0')
                        || (SUB321(auVar1 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar1 >> 0x8f,0) & 1) != 0) || (SUB321(auVar1 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar1 >> 0x9f,0) & 1) != 0) || (SUB321(auVar1 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar1 >> 0xaf,0) & 1) != 0) || (SUB321(auVar1 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar1 >> 0xbf,0) != '\0') || (SUB321(auVar1 >> 199,0) & 1) != 0) ||
               (SUB321(auVar1 >> 0xcf,0) & 1) != 0) || (SUB321(auVar1 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar1 >> 0xdf,0) & 1) != 0) || (SUB321(auVar1 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar1 >> 0xef,0) & 1) != 0) || (SUB321(auVar1 >> 0xf7,0) & 1) != 0) ||
          auVar1[0x1f] < '\0') goto LAB_011d73d2;
      lVar3 = lVar3 + 0x20;
      uVar4 = uVar4 - 0x20;
    } while (0x1f < uVar4);
  }
  if (uVar4 != 0) {
    uVar5 = 0;
    do {
      if (*(char *)(lVar3 + param_4 + uVar5) == '\0') goto LAB_011d73d2;
      uVar5 = uVar5 + 1;
    } while (uVar4 != uVar5);
  }
  uVar2 = 0x31;
  if (0xfff < param_5) goto switchD_011d7320_caseD_3;
  FUN_011f4580(local_1030,param_4,param_5);
  local_1030[param_5] = 0;
  lVar3 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar3 == 0) || ((*(byte *)(lVar3 + 0x21c) & 1) != 0)) {
LAB_011d7247:
    lVar3 = 0;
  }
  else {
    uVar4 = *(ulong *)(lVar3 + 8);
    do {
      param_4 = uVar4 | 3;
      LOCK();
      uVar5 = *(ulong *)(lVar3 + 8);
      bVar6 = uVar4 == uVar5;
      if (bVar6) {
        *(ulong *)(lVar3 + 8) = param_4;
        uVar5 = uVar4;
      }
      UNLOCK();
      uVar4 = uVar5;
    } while (!bVar6);
    if ((uVar5 & 7) != 0) {
      if (((uint)uVar5 & 7) == 6) {
        uVar2 = 0x11;
        goto switchD_011d7320_caseD_3;
      }
      goto LAB_011d7247;
    }
  }
  if (lVar3 == 0) {
    syscall();
    param_4 = 0x10b;
    uVar2 = 0;
  }
  else {
    syscall();
    param_4 = 0x10b;
    LOCK();
    *(ulong *)(lVar3 + 8) = *(ulong *)(lVar3 + 8) ^ 3;
    UNLOCK();
    uVar2 = 0;
  }
switchD_011d7320_caseD_3:
  *param_1 = param_4;
  *(undefined2 *)(param_1 + 1) = uVar2;
  *(undefined4 *)((long)param_1 + 10) = local_30;
  *(undefined2 *)((long)param_1 + 0xe) = local_2c;
  return;
LAB_011d73d2:
  uVar2 = 0x32;
  goto switchD_011d7320_caseD_3;
}


// ---- FUN_011d7400 @ 011d7400

/* WARNING: Removing unreachable block (ram,0x011d7646) */
/* WARNING: Removing unreachable block (ram,0x011d7648) */
/* WARNING: Removing unreachable block (ram,0x011d75d1) */
/* WARNING: Removing unreachable block (ram,0x011d75e0) */
/* WARNING: Removing unreachable block (ram,0x011d75e7) */
/* WARNING: Removing unreachable block (ram,0x011d75ef) */
/* WARNING: Removing unreachable block (ram,0x011d75fc) */
/* WARNING: Removing unreachable block (ram,0x011d7659) */
/* WARNING: Removing unreachable block (ram,0x011d7692) */
/* WARNING: Removing unreachable block (ram,0x011d7684) */
/* WARNING: Removing unreachable block (ram,0x011d76ca) */
/* WARNING: Removing unreachable block (ram,0x011d76d1) */
/* WARNING: Removing unreachable block (ram,0x011d76c3) */
/* WARNING: Removing unreachable block (ram,0x011d76bc) */
/* WARNING: Removing unreachable block (ram,0x011d76a0) */
/* WARNING: Removing unreachable block (ram,0x011d76a7) */
/* WARNING: Removing unreachable block (ram,0x011d76b5) */
/* WARNING: Recovered jumptable eliminated as dead code */

ulong FUN_011d7400(undefined8 param_1,undefined8 param_2,long param_3,ulong param_4,long param_5,
                  ulong param_6)

{
  undefined1 auVar1 [32];
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  ulong unaff_R14;
  long in_FS_OFFSET;
  bool bVar5;
  undefined1 local_2030 [4096];
  undefined1 local_1030 [4096];
  
  lVar2 = 0;
  uVar3 = param_4;
  if (0x1f < param_4) {
    do {
      auVar1 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])(param_3 + lVar2));
      if ((((((((((((((((((((((((((((((((SUB321(auVar1 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar1 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar1 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar1 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar1 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar1 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar1 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar1 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar1 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar1 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar1 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar1 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar1 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar1 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar1 >> 0x77,0) & 1) != 0) || SUB321(auVar1 >> 0x7f,0) != '\0')
                        || (SUB321(auVar1 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar1 >> 0x8f,0) & 1) != 0) || (SUB321(auVar1 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar1 >> 0x9f,0) & 1) != 0) || (SUB321(auVar1 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar1 >> 0xaf,0) & 1) != 0) || (SUB321(auVar1 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar1 >> 0xbf,0) != '\0') || (SUB321(auVar1 >> 199,0) & 1) != 0) ||
               (SUB321(auVar1 >> 0xcf,0) & 1) != 0) || (SUB321(auVar1 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar1 >> 0xdf,0) & 1) != 0) || (SUB321(auVar1 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar1 >> 0xef,0) & 1) != 0) || (SUB321(auVar1 >> 0xf7,0) & 1) != 0) ||
          auVar1[0x1f] < '\0') goto switchD_011d7659_caseD_54;
      lVar2 = lVar2 + 0x20;
      uVar3 = uVar3 - 0x20;
    } while (0x1f < uVar3);
  }
  if (uVar3 != 0) {
    uVar4 = 0;
    do {
      if (*(char *)(lVar2 + param_3 + uVar4) == '\0') goto switchD_011d7659_caseD_54;
      uVar4 = uVar4 + 1;
    } while (uVar3 != uVar4);
  }
  unaff_R14 = CONCAT62((int6)(unaff_R14 >> 0x10),0x31);
  if (0xfff < param_4) goto LAB_011d766c;
  FUN_011f4580(local_1030,param_3,param_4);
  local_1030[param_4] = 0;
  lVar2 = 0;
  uVar3 = param_6;
  if (0x1f < param_6) {
    do {
      auVar1 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])(param_5 + lVar2));
      if ((((((((((((((((((((((((((((((((SUB321(auVar1 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar1 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar1 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar1 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar1 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar1 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar1 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar1 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar1 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar1 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar1 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar1 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar1 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar1 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar1 >> 0x77,0) & 1) != 0) || SUB321(auVar1 >> 0x7f,0) != '\0')
                        || (SUB321(auVar1 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar1 >> 0x8f,0) & 1) != 0) || (SUB321(auVar1 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar1 >> 0x9f,0) & 1) != 0) || (SUB321(auVar1 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar1 >> 0xaf,0) & 1) != 0) || (SUB321(auVar1 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar1 >> 0xbf,0) != '\0') || (SUB321(auVar1 >> 199,0) & 1) != 0) ||
               (SUB321(auVar1 >> 0xcf,0) & 1) != 0) || (SUB321(auVar1 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar1 >> 0xdf,0) & 1) != 0) || (SUB321(auVar1 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar1 >> 0xef,0) & 1) != 0) || (SUB321(auVar1 >> 0xf7,0) & 1) != 0) ||
          auVar1[0x1f] < '\0') goto switchD_011d7659_caseD_54;
      lVar2 = lVar2 + 0x20;
      uVar3 = uVar3 - 0x20;
    } while (0x1f < uVar3);
  }
  if (uVar3 != 0) {
    uVar4 = 0;
    do {
      if (*(char *)(lVar2 + param_5 + uVar4) == '\0') goto switchD_011d7659_caseD_54;
      uVar4 = uVar4 + 1;
    } while (uVar3 != uVar4);
  }
  if (0xfff < param_6) goto LAB_011d766c;
  FUN_011f4580(local_2030);
  local_2030[param_6] = 0;
  lVar2 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar2 == 0) || ((*(byte *)(lVar2 + 0x21c) & 1) != 0)) {
LAB_011d7594:
    lVar2 = 0;
  }
  else {
    uVar3 = *(ulong *)(lVar2 + 8);
    do {
      LOCK();
      uVar4 = *(ulong *)(lVar2 + 8);
      bVar5 = uVar3 == uVar4;
      if (bVar5) {
        *(ulong *)(lVar2 + 8) = uVar3 | 3;
        uVar4 = uVar3;
      }
      UNLOCK();
      uVar3 = uVar4;
    } while (!bVar5);
    if ((uVar4 & 7) != 0) {
      unaff_R14 = CONCAT62((int6)(param_6 >> 0x10),0x11);
      if (((uint)uVar4 & 7) == 6) goto LAB_011d766c;
      goto LAB_011d7594;
    }
  }
  if (lVar2 == 0) {
    syscall();
    unaff_R14 = 0;
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar2 + 8) = *(ulong *)(lVar2 + 8) ^ 3;
    UNLOCK();
    unaff_R14 = 0;
  }
LAB_011d766c:
  return unaff_R14 & 0xffffffff;
switchD_011d7659_caseD_54:
  unaff_R14 = CONCAT62((int6)(unaff_R14 >> 0x10),0x32);
  goto LAB_011d766c;
}


// ---- FUN_011d76e0 @ 011d76e0

/* WARNING: Removing unreachable block (ram,0x011d7940) */
/* WARNING: Removing unreachable block (ram,0x011d7946) */

ulong FUN_011d76e0(undefined8 param_1,int *param_2,long param_3,ulong param_4,int *param_5,
                  long param_6,ulong param_7)

{
  int iVar1;
  int iVar2;
  undefined1 auVar3 [32];
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  ulong unaff_R15;
  long in_FS_OFFSET;
  bool bVar7;
  undefined1 local_2030 [4096];
  undefined1 local_1030 [4096];
  
  iVar1 = *param_2;
  iVar2 = *param_5;
  lVar4 = 0;
  uVar5 = param_4;
  if (0x1f < param_4) {
    do {
      auVar3 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])(param_3 + lVar4));
      if ((((((((((((((((((((((((((((((((SUB321(auVar3 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar3 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar3 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar3 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar3 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar3 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar3 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar3 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar3 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar3 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar3 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar3 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar3 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar3 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar3 >> 0x77,0) & 1) != 0) || SUB321(auVar3 >> 0x7f,0) != '\0')
                        || (SUB321(auVar3 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar3 >> 0x8f,0) & 1) != 0) || (SUB321(auVar3 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar3 >> 0x9f,0) & 1) != 0) || (SUB321(auVar3 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar3 >> 0xaf,0) & 1) != 0) || (SUB321(auVar3 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar3 >> 0xbf,0) != '\0') || (SUB321(auVar3 >> 199,0) & 1) != 0) ||
               (SUB321(auVar3 >> 0xcf,0) & 1) != 0) || (SUB321(auVar3 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar3 >> 0xdf,0) & 1) != 0) || (SUB321(auVar3 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar3 >> 0xef,0) & 1) != 0) || (SUB321(auVar3 >> 0xf7,0) & 1) != 0) ||
          auVar3[0x1f] < '\0') goto LAB_011d7a06;
      lVar4 = lVar4 + 0x20;
      uVar5 = uVar5 - 0x20;
    } while (0x1f < uVar5);
  }
  if (uVar5 != 0) {
    uVar6 = 0;
    do {
      if (*(char *)(lVar4 + param_3 + uVar6) == '\0') goto LAB_011d7a06;
      uVar6 = uVar6 + 1;
    } while (uVar5 != uVar6);
  }
  unaff_R15 = CONCAT62((int6)(unaff_R15 >> 0x10),0x31);
  if (0xfff < param_4) goto LAB_011d7a0b;
  FUN_011f4580(local_1030,param_3,param_4);
  local_1030[param_4] = 0;
  lVar4 = 0;
  uVar5 = param_7;
  if (0x1f < param_7) {
    do {
      auVar3 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])(param_6 + lVar4));
      if ((((((((((((((((((((((((((((((((SUB321(auVar3 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar3 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar3 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar3 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar3 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar3 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar3 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar3 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar3 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar3 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar3 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar3 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar3 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar3 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar3 >> 0x77,0) & 1) != 0) || SUB321(auVar3 >> 0x7f,0) != '\0')
                        || (SUB321(auVar3 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar3 >> 0x8f,0) & 1) != 0) || (SUB321(auVar3 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar3 >> 0x9f,0) & 1) != 0) || (SUB321(auVar3 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar3 >> 0xaf,0) & 1) != 0) || (SUB321(auVar3 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar3 >> 0xbf,0) != '\0') || (SUB321(auVar3 >> 199,0) & 1) != 0) ||
               (SUB321(auVar3 >> 0xcf,0) & 1) != 0) || (SUB321(auVar3 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar3 >> 0xdf,0) & 1) != 0) || (SUB321(auVar3 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar3 >> 0xef,0) & 1) != 0) || (SUB321(auVar3 >> 0xf7,0) & 1) != 0) ||
          auVar3[0x1f] < '\0') goto LAB_011d7a06;
      lVar4 = lVar4 + 0x20;
      uVar5 = uVar5 - 0x20;
    } while (0x1f < uVar5);
  }
  if (uVar5 != 0) {
    uVar6 = 0;
    do {
      if (*(char *)(lVar4 + param_6 + uVar6) == '\0') goto LAB_011d7a06;
      uVar6 = uVar6 + 1;
    } while (uVar5 != uVar6);
  }
  if (0xfff < param_7) goto LAB_011d7a0b;
  FUN_011f4580(local_2030);
  local_2030[param_7] = 0;
  lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar4 != 0) && ((*(byte *)(lVar4 + 0x21c) & 1) == 0)) {
    uVar5 = *(ulong *)(lVar4 + 8);
    do {
      LOCK();
      uVar6 = *(ulong *)(lVar4 + 8);
      bVar7 = uVar5 == uVar6;
      if (bVar7) {
        *(ulong *)(lVar4 + 8) = uVar5 | 3;
        uVar6 = uVar5;
      }
      UNLOCK();
      uVar5 = uVar6;
    } while (!bVar7);
    if ((uVar6 & 7) == 0) goto LAB_011d7887;
    unaff_R15 = CONCAT62((int6)(param_7 >> 0x10),0x11);
    if (((uint)uVar6 & 7) == 6) goto LAB_011d7a0b;
  }
  lVar4 = 0;
LAB_011d7887:
  if (lVar4 == 0) {
    syscall();
                    /* WARNING: Could not recover jumptable at 0x011d792e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar5 = (*DAT_01007b48)((long)iVar1,local_1030,(long)iVar2,0x11d7917,1);
    return uVar5;
  }
  syscall();
                    /* WARNING: Could not recover jumptable at 0x011d78c6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar5 = (*(code *)PTR_LAB_01007770)((long)iVar1,local_1030,(long)iVar2,0,1);
  return uVar5;
LAB_011d7a06:
  unaff_R15 = CONCAT62((int6)(unaff_R15 >> 0x10),0x32);
LAB_011d7a0b:
  return unaff_R15 & 0xffffffff;
}


// ---- FUN_011d7ac0 @ 011d7ac0

/* WARNING: Removing unreachable block (ram,0x011d7d1e) */
/* WARNING: Removing unreachable block (ram,0x011d7d24) */

ulong FUN_011d7ac0(undefined8 param_1,int *param_2,long param_3,ulong param_4,int *param_5,
                  long param_6,ulong param_7)

{
  int iVar1;
  undefined1 auVar2 [32];
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  ulong unaff_R15;
  undefined6 uVar6;
  long in_FS_OFFSET;
  bool bVar7;
  undefined1 local_2038 [4096];
  undefined1 local_1038 [4096];
  long local_38;
  
  local_38 = (long)*param_2;
  iVar1 = *param_5;
  lVar3 = 0;
  uVar5 = param_4;
  if (0x1f < param_4) {
    do {
      auVar2 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])(param_3 + lVar3));
      if ((((((((((((((((((((((((((((((((SUB321(auVar2 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar2 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar2 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar2 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar2 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar2 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar2 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar2 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar2 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar2 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar2 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar2 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar2 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar2 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar2 >> 0x77,0) & 1) != 0) || SUB321(auVar2 >> 0x7f,0) != '\0')
                        || (SUB321(auVar2 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar2 >> 0x8f,0) & 1) != 0) || (SUB321(auVar2 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar2 >> 0x9f,0) & 1) != 0) || (SUB321(auVar2 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar2 >> 0xaf,0) & 1) != 0) || (SUB321(auVar2 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar2 >> 0xbf,0) != '\0') || (SUB321(auVar2 >> 199,0) & 1) != 0) ||
               (SUB321(auVar2 >> 0xcf,0) & 1) != 0) || (SUB321(auVar2 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar2 >> 0xdf,0) & 1) != 0) || (SUB321(auVar2 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar2 >> 0xef,0) & 1) != 0) || (SUB321(auVar2 >> 0xf7,0) & 1) != 0) ||
          auVar2[0x1f] < '\0') goto LAB_011d7d8c;
      lVar3 = lVar3 + 0x20;
      uVar5 = uVar5 - 0x20;
    } while (0x1f < uVar5);
  }
  if (uVar5 != 0) {
    uVar4 = 0;
    do {
      if (*(char *)(lVar3 + param_3 + uVar4) == '\0') goto LAB_011d7d8c;
      uVar4 = uVar4 + 1;
    } while (uVar5 != uVar4);
  }
  uVar6 = (undefined6)(unaff_R15 >> 0x10);
  unaff_R15 = CONCAT62(uVar6,0x31);
  if (0xfff < param_4) goto LAB_011d7d91;
  FUN_011f4580(local_1038,param_3,param_4);
  local_1038[param_4] = 0;
  lVar3 = 0;
  uVar5 = param_7;
  if (0x1f < param_7) {
    do {
      auVar2 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])(param_6 + lVar3));
      if ((((((((((((((((((((((((((((((((SUB321(auVar2 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar2 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar2 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar2 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar2 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar2 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar2 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar2 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar2 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar2 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar2 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar2 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar2 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar2 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar2 >> 0x77,0) & 1) != 0) || SUB321(auVar2 >> 0x7f,0) != '\0')
                        || (SUB321(auVar2 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar2 >> 0x8f,0) & 1) != 0) || (SUB321(auVar2 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar2 >> 0x9f,0) & 1) != 0) || (SUB321(auVar2 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar2 >> 0xaf,0) & 1) != 0) || (SUB321(auVar2 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar2 >> 0xbf,0) != '\0') || (SUB321(auVar2 >> 199,0) & 1) != 0) ||
               (SUB321(auVar2 >> 0xcf,0) & 1) != 0) || (SUB321(auVar2 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar2 >> 0xdf,0) & 1) != 0) || (SUB321(auVar2 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar2 >> 0xef,0) & 1) != 0) || (SUB321(auVar2 >> 0xf7,0) & 1) != 0) ||
          auVar2[0x1f] < '\0') goto LAB_011d7d8c;
      lVar3 = lVar3 + 0x20;
      uVar5 = uVar5 - 0x20;
    } while (0x1f < uVar5);
  }
  if (uVar5 != 0) {
    uVar4 = 0;
    do {
      if (*(char *)(lVar3 + param_6 + uVar4) == '\0') goto LAB_011d7d8c;
      uVar4 = uVar4 + 1;
    } while (uVar5 != uVar4);
  }
  if (0xfff < param_7) goto LAB_011d7d91;
  FUN_011f4580(local_2038,param_6,param_7);
  local_2038[param_7] = 0;
  lVar3 = *(long *)(in_FS_OFFSET + -0x40010);
  if (lVar3 == 0) goto LAB_011d7ceb;
  if ((*(byte *)(lVar3 + 0x21c) & 1) == 0) {
    uVar5 = *(ulong *)(lVar3 + 8);
    do {
      LOCK();
      uVar4 = *(ulong *)(lVar3 + 8);
      bVar7 = uVar5 == uVar4;
      if (bVar7) {
        *(ulong *)(lVar3 + 8) = uVar5 | 3;
        uVar4 = uVar5;
      }
      UNLOCK();
      uVar5 = uVar4;
    } while (!bVar7);
    if ((uVar4 & 7) != 0) {
      unaff_R15 = CONCAT62(uVar6,0x11);
      if (((uint)uVar4 & 7) == 6) goto LAB_011d7d91;
      goto LAB_011d7c64;
    }
  }
  else {
LAB_011d7c64:
    lVar3 = 0;
  }
  if (lVar3 != 0) {
    syscall();
                    /* WARNING: Could not recover jumptable at 0x011d7ca1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar5 = (*(code *)PTR_LAB_01007f20)(local_38,local_1038,(long)iVar1);
    return uVar5;
  }
LAB_011d7ceb:
  syscall();
                    /* WARNING: Could not recover jumptable at 0x011d7d0f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar5 = (*DAT_010082f8)(local_38,local_1038,(long)iVar1,0x11d7cf8);
  return uVar5;
LAB_011d7d8c:
  unaff_R15 = CONCAT62((int6)(unaff_R15 >> 0x10),0x32);
LAB_011d7d91:
  return unaff_R15 & 0xffffffff;
}


// ---- FUN_011d7ec0 @ 011d7ec0

/* WARNING: Removing unreachable block (ram,0x011d8055) */
/* WARNING: Removing unreachable block (ram,0x011d8057) */
/* WARNING: Removing unreachable block (ram,0x011d7fe1) */
/* WARNING: Removing unreachable block (ram,0x011d7ff0) */
/* WARNING: Removing unreachable block (ram,0x011d7ff7) */
/* WARNING: Removing unreachable block (ram,0x011d7fff) */
/* WARNING: Removing unreachable block (ram,0x011d8007) */
/* WARNING: Removing unreachable block (ram,0x011d8067) */
/* WARNING: Removing unreachable block (ram,0x011d8087) */
/* WARNING: Removing unreachable block (ram,0x011d80ab) */
/* WARNING: Removing unreachable block (ram,0x011d80b1) */
/* WARNING: Removing unreachable block (ram,0x011d8099) */
/* WARNING: Removing unreachable block (ram,0x011d8093) */
/* WARNING: Removing unreachable block (ram,0x011d808d) */
/* WARNING: Removing unreachable block (ram,0x011d80a5) */
/* WARNING: Removing unreachable block (ram,0x011d809f) */
/* WARNING: Removing unreachable block (ram,0x011d80b7) */
/* WARNING: Removing unreachable block (ram,0x011d806e) */
/* WARNING: Recovered jumptable eliminated as dead code */

undefined8 FUN_011d7ec0(undefined8 param_1,undefined8 param_2,long param_3,ulong param_4)

{
  undefined1 auVar1 [32];
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  long in_FS_OFFSET;
  bool bVar5;
  undefined1 local_1018 [4096];
  
  lVar2 = 0;
  uVar3 = param_4;
  if (0x1f < param_4) {
    do {
      auVar1 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])(param_3 + lVar2));
      if ((((((((((((((((((((((((((((((((SUB321(auVar1 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar1 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar1 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar1 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar1 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar1 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar1 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar1 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar1 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar1 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar1 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar1 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar1 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar1 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar1 >> 0x77,0) & 1) != 0) || SUB321(auVar1 >> 0x7f,0) != '\0')
                        || (SUB321(auVar1 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar1 >> 0x8f,0) & 1) != 0) || (SUB321(auVar1 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar1 >> 0x9f,0) & 1) != 0) || (SUB321(auVar1 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar1 >> 0xaf,0) & 1) != 0) || (SUB321(auVar1 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar1 >> 0xbf,0) != '\0') || (SUB321(auVar1 >> 199,0) & 1) != 0) ||
               (SUB321(auVar1 >> 0xcf,0) & 1) != 0) || (SUB321(auVar1 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar1 >> 0xdf,0) & 1) != 0) || (SUB321(auVar1 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar1 >> 0xef,0) & 1) != 0) || (SUB321(auVar1 >> 0xf7,0) & 1) != 0) ||
          auVar1[0x1f] < '\0') goto switchD_011d8067_caseD_54;
      lVar2 = lVar2 + 0x20;
      uVar3 = uVar3 - 0x20;
    } while (0x1f < uVar3);
  }
  if (uVar3 != 0) {
    lVar2 = lVar2 + param_3;
    uVar4 = 0;
    do {
      if (*(char *)(lVar2 + uVar4) == '\0') {
switchD_011d8067_caseD_54:
        return CONCAT62((int6)((ulong)lVar2 >> 0x10),0x32);
      }
      uVar4 = uVar4 + 1;
    } while (uVar3 != uVar4);
  }
  if (0xfff < param_4) {
    return CONCAT62((int6)((ulong)lVar2 >> 0x10),0x31);
  }
  FUN_011f4580(local_1018,param_3,param_4);
  local_1018[param_4] = 0;
  lVar2 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar2 != 0) && ((*(byte *)(lVar2 + 0x21c) & 1) == 0)) {
    uVar3 = *(ulong *)(lVar2 + 8);
    do {
      LOCK();
      uVar4 = *(ulong *)(lVar2 + 8);
      bVar5 = uVar3 == uVar4;
      if (bVar5) {
        *(ulong *)(lVar2 + 8) = uVar3 | 3;
        uVar4 = uVar3;
      }
      UNLOCK();
      uVar3 = uVar4;
    } while (!bVar5);
    if ((uVar4 & 7) == 0) goto LAB_011d7fa9;
    if (((uint)uVar4 & 7) == 6) {
      return 0x11;
    }
  }
  lVar2 = 0;
LAB_011d7fa9:
  if (lVar2 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar2 + 8) = *(ulong *)(lVar2 + 8) ^ 3;
    UNLOCK();
  }
  return 0;
}


// ---- FUN_011d80c0 @ 011d80c0

/* WARNING: Removing unreachable block (ram,0x011d8258) */
/* WARNING: Removing unreachable block (ram,0x011d8266) */
/* WARNING: Removing unreachable block (ram,0x011d8277) */
/* WARNING: Removing unreachable block (ram,0x011d82c1) */
/* WARNING: Removing unreachable block (ram,0x011d82c7) */
/* WARNING: Removing unreachable block (ram,0x011d82bb) */
/* WARNING: Removing unreachable block (ram,0x011d82b5) */
/* WARNING: Removing unreachable block (ram,0x011d829d) */
/* WARNING: Removing unreachable block (ram,0x011d8297) */
/* WARNING: Removing unreachable block (ram,0x011d82a3) */
/* WARNING: Removing unreachable block (ram,0x011d82a9) */
/* WARNING: Removing unreachable block (ram,0x011d82af) */
/* WARNING: Removing unreachable block (ram,0x011d827e) */
/* WARNING: Removing unreachable block (ram,0x011d82cd) */
/* WARNING: Removing unreachable block (ram,0x011d81e3) */
/* WARNING: Removing unreachable block (ram,0x011d81f0) */
/* WARNING: Removing unreachable block (ram,0x011d81f7) */
/* WARNING: Removing unreachable block (ram,0x011d81ff) */
/* WARNING: Removing unreachable block (ram,0x011d8207) */
/* WARNING: Removing unreachable block (ram,0x011d825a) */
/* WARNING: Recovered jumptable eliminated as dead code */

undefined8 FUN_011d80c0(undefined8 param_1,undefined8 param_2,long param_3,ulong param_4)

{
  undefined1 auVar1 [32];
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  long in_FS_OFFSET;
  bool bVar5;
  undefined1 local_1018 [4096];
  
  lVar2 = 0;
  uVar3 = param_4;
  if (0x1f < param_4) {
    do {
      auVar1 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])(param_3 + lVar2));
      if ((((((((((((((((((((((((((((((((SUB321(auVar1 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar1 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar1 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar1 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar1 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar1 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar1 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar1 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar1 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar1 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar1 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar1 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar1 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar1 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar1 >> 0x77,0) & 1) != 0) || SUB321(auVar1 >> 0x7f,0) != '\0')
                        || (SUB321(auVar1 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar1 >> 0x8f,0) & 1) != 0) || (SUB321(auVar1 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar1 >> 0x9f,0) & 1) != 0) || (SUB321(auVar1 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar1 >> 0xaf,0) & 1) != 0) || (SUB321(auVar1 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar1 >> 0xbf,0) != '\0') || (SUB321(auVar1 >> 199,0) & 1) != 0) ||
               (SUB321(auVar1 >> 0xcf,0) & 1) != 0) || (SUB321(auVar1 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar1 >> 0xdf,0) & 1) != 0) || (SUB321(auVar1 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar1 >> 0xef,0) & 1) != 0) || (SUB321(auVar1 >> 0xf7,0) & 1) != 0) ||
          auVar1[0x1f] < '\0') goto switchD_011d8277_caseD_52;
      lVar2 = lVar2 + 0x20;
      uVar3 = uVar3 - 0x20;
    } while (0x1f < uVar3);
  }
  if (uVar3 != 0) {
    lVar2 = lVar2 + param_3;
    uVar4 = 0;
    do {
      if (*(char *)(lVar2 + uVar4) == '\0') {
switchD_011d8277_caseD_52:
        return CONCAT62((int6)((ulong)lVar2 >> 0x10),0x32);
      }
      uVar4 = uVar4 + 1;
    } while (uVar3 != uVar4);
  }
  if (0xfff < param_4) {
    return CONCAT62((int6)((ulong)lVar2 >> 0x10),0x31);
  }
  FUN_011f4580(local_1018,param_3,param_4);
  local_1018[param_4] = 0;
  lVar2 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar2 != 0) && ((*(byte *)(lVar2 + 0x21c) & 1) == 0)) {
    uVar3 = *(ulong *)(lVar2 + 8);
    do {
      LOCK();
      uVar4 = *(ulong *)(lVar2 + 8);
      bVar5 = uVar3 == uVar4;
      if (bVar5) {
        *(ulong *)(lVar2 + 8) = uVar3 | 3;
        uVar4 = uVar3;
      }
      UNLOCK();
      uVar3 = uVar4;
    } while (!bVar5);
    if ((uVar4 & 7) == 0) goto LAB_011d81a9;
    if (((uint)uVar4 & 7) == 6) {
      return 0x11;
    }
  }
  lVar2 = 0;
LAB_011d81a9:
  if (lVar2 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar2 + 8) = *(ulong *)(lVar2 + 8) ^ 3;
    UNLOCK();
  }
  return 0;
}


// ---- FUN_011d82e0 @ 011d82e0

/* WARNING: Removing unreachable block (ram,0x011d84e8) */
/* WARNING: Removing unreachable block (ram,0x011d84ee) */
/* WARNING: Removing unreachable block (ram,0x011d8433) */
/* WARNING: Removing unreachable block (ram,0x011d8440) */
/* WARNING: Removing unreachable block (ram,0x011d8447) */
/* WARNING: Removing unreachable block (ram,0x011d844f) */
/* WARNING: Removing unreachable block (ram,0x011d84fb) */
/* WARNING: Removing unreachable block (ram,0x011d8595) */
/* WARNING: Removing unreachable block (ram,0x011d8551) */
/* WARNING: Removing unreachable block (ram,0x011d85fb) */
/* WARNING: Removing unreachable block (ram,0x011d8540) */
/* WARNING: Removing unreachable block (ram,0x011d860c) */
/* WARNING: Removing unreachable block (ram,0x011d85d9) */
/* WARNING: Removing unreachable block (ram,0x011d852f) */
/* WARNING: Removing unreachable block (ram,0x011d8562) */
/* WARNING: Removing unreachable block (ram,0x011d8584) */
/* WARNING: Removing unreachable block (ram,0x011d85ea) */
/* WARNING: Removing unreachable block (ram,0x011d85b7) */
/* WARNING: Removing unreachable block (ram,0x011d85a6) */
/* WARNING: Removing unreachable block (ram,0x011d8573) */
/* WARNING: Removing unreachable block (ram,0x011d850d) */
/* WARNING: Removing unreachable block (ram,0x011d8502) */
/* WARNING: Removing unreachable block (ram,0x011d851e) */
/* WARNING: Removing unreachable block (ram,0x011d85c8) */
/* WARNING: Recovered jumptable eliminated as dead code */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 *
FUN_011d82e0(undefined8 *param_1,undefined8 param_2,undefined8 param_3,long param_4,ulong param_5,
            undefined8 param_6,undefined8 param_7)

{
  undefined1 auVar1 [32];
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  long in_FS_OFFSET;
  bool bVar5;
  undefined1 local_1038 [4096];
  undefined8 local_38;
  undefined8 uStack_30;
  
  lVar2 = 0;
  uVar3 = param_5;
  if (0x1f < param_5) {
    do {
      auVar1 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])(param_4 + lVar2));
      if ((((((((((((((((((((((((((((((((SUB321(auVar1 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar1 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar1 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar1 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar1 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar1 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar1 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar1 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar1 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar1 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar1 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar1 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar1 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar1 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar1 >> 0x77,0) & 1) != 0) || SUB321(auVar1 >> 0x7f,0) != '\0')
                        || (SUB321(auVar1 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar1 >> 0x8f,0) & 1) != 0) || (SUB321(auVar1 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar1 >> 0x9f,0) & 1) != 0) || (SUB321(auVar1 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar1 >> 0xaf,0) & 1) != 0) || (SUB321(auVar1 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar1 >> 0xbf,0) != '\0') || (SUB321(auVar1 >> 199,0) & 1) != 0) ||
               (SUB321(auVar1 >> 0xcf,0) & 1) != 0) || (SUB321(auVar1 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar1 >> 0xdf,0) & 1) != 0) || (SUB321(auVar1 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar1 >> 0xef,0) & 1) != 0) || (SUB321(auVar1 >> 0xf7,0) & 1) != 0) ||
          auVar1[0x1f] < '\0') goto LAB_011d8361;
      lVar2 = lVar2 + 0x20;
      uVar3 = uVar3 - 0x20;
    } while (0x1f < uVar3);
  }
  if (uVar3 != 0) {
    uVar4 = 0;
    do {
      if (*(char *)(lVar2 + param_4 + uVar4) == '\0') {
LAB_011d8361:
        *(undefined2 *)(param_1 + 1) = 0x32;
        return param_1;
      }
      uVar4 = uVar4 + 1;
    } while (uVar3 != uVar4);
  }
  if (0xfff < param_5) {
    *(undefined2 *)(param_1 + 1) = 0x31;
    return param_1;
  }
  FUN_011f4580(local_1038,param_4,param_5);
  local_1038[param_5] = 0;
  lVar2 = *(long *)(in_FS_OFFSET + -0x40010);
  if (lVar2 != 0) {
    if ((*(byte *)(lVar2 + 0x21c) & 1) == 0) {
      uVar3 = *(ulong *)(lVar2 + 8);
      do {
        LOCK();
        uVar4 = *(ulong *)(lVar2 + 8);
        bVar5 = uVar3 == uVar4;
        if (bVar5) {
          *(ulong *)(lVar2 + 8) = uVar3 | 3;
          uVar4 = uVar3;
        }
        UNLOCK();
        uVar3 = uVar4;
      } while (!bVar5);
      if ((uVar4 & 7) != 0) {
        if (((uint)uVar4 & 7) == 6) {
          *(undefined2 *)(param_1 + 1) = 0x11;
          return param_1;
        }
        goto LAB_011d83eb;
      }
    }
    else {
LAB_011d83eb:
      lVar2 = 0;
    }
    if (lVar2 != 0) {
      syscall();
      LOCK();
      *(ulong *)(lVar2 + 8) = *(ulong *)(lVar2 + 8) ^ 3;
      UNLOCK();
      goto LAB_011d84b7;
    }
  }
  syscall();
LAB_011d84b7:
  FUN_011d3150(&local_38,0x101,param_6,param_7);
  syscall();
  *param_1 = local_38;
  param_1[1] = uStack_30;
  return param_1;
}


// ---- FUN_011d8620 @ 011d8620

undefined8 *
FUN_011d8620(undefined8 *param_1,undefined8 param_2,undefined4 *param_3,undefined8 param_4,
            undefined8 param_5)

{
  undefined8 local_20;
  undefined8 uStack_18;
  
  FUN_011d3150(&local_20,*param_3,param_4,param_5);
  *param_1 = local_20;
  param_1[1] = uStack_18;
  return param_1;
}


// ---- FUN_011d8650 @ 011d8650

/* WARNING: Removing unreachable block (ram,0x011d8791) */
/* WARNING: Removing unreachable block (ram,0x011d87a0) */
/* WARNING: Removing unreachable block (ram,0x011d87a7) */
/* WARNING: Removing unreachable block (ram,0x011d87af) */
/* WARNING: Removing unreachable block (ram,0x011d87b7) */
/* WARNING: Removing unreachable block (ram,0x011d89cf) */
/* WARNING: Removing unreachable block (ram,0x011d8a32) */
/* WARNING: Removing unreachable block (ram,0x011d8a27) */
/* WARNING: Recovered jumptable eliminated as dead code */
/* WARNING: Removing unreachable block (ram,0x011d89f9) */
/* WARNING: Removing unreachable block (ram,0x011d89e8) */
/* WARNING: Removing unreachable block (ram,0x011d8a09) */
/* WARNING: Removing unreachable block (ram,0x011d8873) */
/* WARNING: Removing unreachable block (ram,0x011d8878) */
/* WARNING: Removing unreachable block (ram,0x011d8880) */
/* WARNING: Removing unreachable block (ram,0x011d8887) */
/* WARNING: Removing unreachable block (ram,0x011d888f) */
/* WARNING: Removing unreachable block (ram,0x011d8897) */
/* WARNING: Removing unreachable block (ram,0x011d8a12) */
/* WARNING: Removing unreachable block (ram,0x011d89b9) */
/* WARNING: Removing unreachable block (ram,0x011d89be) */
/* WARNING: Removing unreachable block (ram,0x011d89c4) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * FUN_011d8650(long *param_1,undefined8 param_2,long *param_3,long param_4,long param_5)

{
  byte bVar1;
  long lVar2;
  undefined8 uVar3;
  byte bVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  long in_FS_OFFSET;
  bool bVar10;
  undefined8 local_60 [2];
  long local_50;
  long local_48;
  long local_40;
  long *local_38;
  
  if (param_5 == 0) {
    lVar8 = 0;
  }
  else {
    local_40 = 0;
    local_50 = param_4;
    local_48 = param_5;
    local_38 = param_1;
LAB_011d869e:
    do {
      lVar8 = param_3[2];
      if (param_3[3] == lVar8) {
        param_1 = local_38;
        lVar8 = local_40;
        if (local_40 != 0) break;
        if ((*(byte *)((long)param_3 + 0x24) & 3) == 0) {
          lVar8 = *(long *)(in_FS_OFFSET + -0x40010);
          if ((lVar8 == 0) || ((*(byte *)(lVar8 + 0x21c) & 1) != 0)) {
LAB_011d875f:
            lVar8 = 0;
          }
          else {
            uVar6 = *(ulong *)(lVar8 + 8);
            do {
              LOCK();
              uVar5 = *(ulong *)(lVar8 + 8);
              bVar10 = uVar6 == uVar5;
              if (bVar10) {
                *(ulong *)(lVar8 + 8) = uVar6 | 3;
                uVar5 = uVar6;
              }
              UNLOCK();
              uVar6 = uVar5;
            } while (!bVar10);
            if ((uVar5 & 7) != 0) {
              if (((uint)uVar5 & 7) != 7) {
                *(undefined2 *)(local_38 + 1) = 0x11;
                return local_38;
              }
              goto LAB_011d875f;
            }
          }
          if (lVar8 == 0) {
            syscall();
            *(undefined1 *)((long)param_3 + 0x24) = 1;
            lVar8 = *(long *)(in_FS_OFFSET + -0x40010);
            goto joined_r0x011d86d7;
          }
          syscall();
          LOCK();
          *(ulong *)(lVar8 + 8) = *(ulong *)(lVar8 + 8) ^ 3;
          UNLOCK();
          *(undefined1 *)((long)param_3 + 0x24) = 1;
          lVar8 = *(long *)(in_FS_OFFSET + -0x40010);
          if (lVar8 != 0) goto LAB_011d86dd;
LAB_011d8830:
          lVar8 = 0;
        }
        else {
          lVar8 = *(long *)(in_FS_OFFSET + -0x40010);
joined_r0x011d86d7:
          if (lVar8 == 0) goto LAB_011d8830;
LAB_011d86dd:
          if ((*(byte *)(lVar8 + 0x21c) & 1) != 0) goto LAB_011d8830;
          uVar6 = *(ulong *)(lVar8 + 8);
          do {
            LOCK();
            uVar5 = *(ulong *)(lVar8 + 8);
            bVar10 = uVar6 == uVar5;
            if (bVar10) {
              *(ulong *)(lVar8 + 8) = uVar6 | 3;
              uVar5 = uVar6;
            }
            UNLOCK();
            uVar6 = uVar5;
          } while (!bVar10);
          if ((uVar5 & 7) != 0) {
            if (((uint)uVar5 & 7) != 7) {
              *(undefined2 *)(local_38 + 1) = 0x11;
              return local_38;
            }
            goto LAB_011d8830;
          }
        }
        syscall();
        if (lVar8 != 0) {
          LOCK();
          *(ulong *)(lVar8 + 8) = *(ulong *)(lVar8 + 8) ^ 3;
          UNLOCK();
        }
        param_3[2] = 0;
        param_3[3] = 0xd9;
        lVar8 = 0;
      }
      lVar2 = *param_3;
      param_3[2] = (ulong)*(ushort *)(lVar2 + 0x10 + lVar8) + lVar8;
      lVar9 = lVar2 + lVar8 + 0x13;
      FUN_011c97a0(local_60,lVar9,*(short *)(lVar2 + 0x10 + lVar8) + -0x13,0,0);
      uVar3 = local_60[0];
      uVar6 = FUN_011c9680(lVar9,local_60[0],&DAT_011b9acb);
      if (((uVar6 & 1) != 0) || (uVar6 = FUN_011c9680(lVar9,uVar3,&DAT_011b9aca), (uVar6 & 1) != 0))
      {
        param_1 = local_38;
        lVar8 = local_48;
        if (local_48 == local_40) break;
        goto LAB_011d869e;
      }
      bVar1 = *(byte *)(lVar2 + lVar8 + 0x12);
      bVar4 = (byte)(0x6a4a5a0a2a13a >> (((ulong)bVar1 & 0xf) << 2));
      if (0xc < bVar1) {
        bVar4 = 10;
      }
      lVar7 = local_40 * 0x20;
      *(long *)(local_50 + lVar7) = lVar9;
      *(undefined8 *)(local_50 + 8 + lVar7) = uVar3;
      *(byte *)(local_50 + 0x18 + lVar7) = bVar4 & 0xf;
      *(undefined8 *)(local_50 + 0x10 + lVar7) = *(undefined8 *)(lVar2 + lVar8);
      local_40 = local_40 + 1;
      param_1 = local_38;
      lVar8 = local_48;
    } while (local_48 != local_40);
  }
  *(undefined2 *)(param_1 + 1) = 0;
  *param_1 = lVar8;
  return param_1;
}


// ---- FUN_011d8a60 @ 011d8a60

void FUN_011d8a60(undefined8 param_1,undefined8 param_2,long param_3)

{
  long lVar1;
  
  if (param_3 != 0) {
    lVar1 = 0;
    do {
      syscall();
      lVar1 = lVar1 + 1;
    } while (param_3 != lVar1);
  }
  return;
}


// ---- FUN_011d8a90 @ 011d8a90

/* WARNING: Removing unreachable block (ram,0x011d8c78) */
/* WARNING: Removing unreachable block (ram,0x011d8c7e) */

long FUN_011d8a90(long param_1,undefined8 param_2,int *param_3,long param_4,ulong param_5,
                 long param_6)

{
  int iVar1;
  undefined1 auVar2 [32];
  undefined2 uVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  long in_FS_OFFSET;
  bool bVar7;
  undefined1 local_1022 [4096];
  byte local_22;
  byte local_21;
  
  iVar1 = *param_3;
  local_22 = *(byte *)(param_6 + 1);
  local_21 = *(byte *)(param_6 + 2);
  lVar4 = 0;
  uVar5 = param_5;
  if (0x1f < param_5) {
    do {
      auVar2 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])(param_4 + lVar4));
      if ((((((((((((((((((((((((((((((((SUB321(auVar2 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar2 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar2 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar2 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar2 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar2 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar2 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar2 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar2 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar2 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar2 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar2 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar2 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar2 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar2 >> 0x77,0) & 1) != 0) || SUB321(auVar2 >> 0x7f,0) != '\0')
                        || (SUB321(auVar2 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar2 >> 0x8f,0) & 1) != 0) || (SUB321(auVar2 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar2 >> 0x9f,0) & 1) != 0) || (SUB321(auVar2 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar2 >> 0xaf,0) & 1) != 0) || (SUB321(auVar2 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar2 >> 0xbf,0) != '\0') || (SUB321(auVar2 >> 199,0) & 1) != 0) ||
               (SUB321(auVar2 >> 0xcf,0) & 1) != 0) || (SUB321(auVar2 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar2 >> 0xdf,0) & 1) != 0) || (SUB321(auVar2 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar2 >> 0xef,0) & 1) != 0) || (SUB321(auVar2 >> 0xf7,0) & 1) != 0) ||
          auVar2[0x1f] < '\0') goto LAB_011d8c23;
      lVar4 = lVar4 + 0x20;
      uVar5 = uVar5 - 0x20;
    } while (0x1f < uVar5);
  }
  if (uVar5 != 0) {
    uVar6 = 0;
    do {
      if (*(char *)(lVar4 + param_4 + uVar6) == '\0') goto LAB_011d8c23;
      uVar6 = uVar6 + 1;
    } while (uVar5 != uVar6);
  }
  uVar3 = 0x31;
  if (0xfff < param_5) goto LAB_011d8c27;
  FUN_011f4580(local_1022,param_4,param_5);
  local_1022[param_5] = 0;
  lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar4 != 0) && ((*(byte *)(lVar4 + 0x21c) & 1) == 0)) {
    uVar5 = *(ulong *)(lVar4 + 8);
    do {
      LOCK();
      uVar6 = *(ulong *)(lVar4 + 8);
      bVar7 = uVar5 == uVar6;
      if (bVar7) {
        *(ulong *)(lVar4 + 8) = uVar5 | 3;
        uVar6 = uVar5;
      }
      UNLOCK();
      uVar5 = uVar6;
    } while (!bVar7);
    if ((uVar6 & 7) == 0) goto LAB_011d8b9e;
    if (((uint)uVar6 & 7) == 6) {
      *(undefined2 *)(param_1 + 4) = 0x11;
      return param_1;
    }
  }
  lVar4 = 0;
LAB_011d8b9e:
  if (lVar4 != 0) {
    syscall();
                    /* WARNING: Could not recover jumptable at 0x011d8bee. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    lVar4 = (*(code *)PTR_LAB_01008f50)((long)iVar1,local_1022);
    return lVar4;
  }
  syscall();
                    /* WARNING: Could not recover jumptable at 0x011d8c69. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  lVar4 = (*(code *)PTR_LAB_010091f8)
                    ((long)iVar1,local_1022,
                     (local_22 ^ 1) * 0x200000 + (local_21 ^ 1) * 0x20000 + 0x90000);
  return lVar4;
LAB_011d8c23:
  uVar3 = 0x32;
LAB_011d8c27:
  *(undefined2 *)(param_1 + 4) = uVar3;
  return param_1;
}


// ---- FUN_011d8d90 @ 011d8d90

/* WARNING: Removing unreachable block (ram,0x011d9015) */
/* WARNING: Removing unreachable block (ram,0x011d901b) */
/* WARNING: Removing unreachable block (ram,0x011d922e) */
/* WARNING: Removing unreachable block (ram,0x011d9240) */
/* WARNING: Removing unreachable block (ram,0x011d9247) */
/* WARNING: Removing unreachable block (ram,0x011d924f) */
/* WARNING: Removing unreachable block (ram,0x011d9257) */
/* WARNING: Removing unreachable block (ram,0x011d8f23) */
/* WARNING: Removing unreachable block (ram,0x011d8f30) */
/* WARNING: Removing unreachable block (ram,0x011d8f37) */
/* WARNING: Removing unreachable block (ram,0x011d8f3f) */
/* WARNING: Removing unreachable block (ram,0x011d92b7) */
/* WARNING: Removing unreachable block (ram,0x011d9029) */
/* WARNING: Removing unreachable block (ram,0x011d90b5) */
/* WARNING: Removing unreachable block (ram,0x011d90db) */
/* WARNING: Removing unreachable block (ram,0x011d908f) */
/* WARNING: Removing unreachable block (ram,0x011d9160) */
/* WARNING: Removing unreachable block (ram,0x011d9043) */
/* WARNING: Removing unreachable block (ram,0x011d90ee) */
/* WARNING: Removing unreachable block (ram,0x011d907c) */
/* WARNING: Removing unreachable block (ram,0x011d9127) */
/* WARNING: Removing unreachable block (ram,0x011d9056) */
/* WARNING: Removing unreachable block (ram,0x011d9114) */
/* WARNING: Removing unreachable block (ram,0x011d90a2) */
/* WARNING: Removing unreachable block (ram,0x011d90c8) */
/* WARNING: Removing unreachable block (ram,0x011d913a) */
/* WARNING: Removing unreachable block (ram,0x011d914d) */
/* WARNING: Removing unreachable block (ram,0x011d9069) */
/* WARNING: Removing unreachable block (ram,0x011d9030) */
/* WARNING: Removing unreachable block (ram,0x011d9101) */
/* WARNING: Recovered jumptable eliminated as dead code */
/* WARNING: Removing unreachable block (ram,0x011d9302) */
/* WARNING: Removing unreachable block (ram,0x011d92bd) */
/* WARNING: Removing unreachable block (ram,0x011d92fd) */
/* WARNING: Removing unreachable block (ram,0x011d92d0) */
/* WARNING: Removing unreachable block (ram,0x011d92ea) */
/* WARNING: Removing unreachable block (ram,0x011d92d7) */
/* WARNING: Removing unreachable block (ram,0x011d9315) */

undefined1  [16]
FUN_011d8d90(undefined8 *param_1,undefined8 param_2,undefined8 param_3,long param_4,ulong param_5,
            byte *param_6)

{
  byte bVar1;
  byte bVar2;
  undefined1 auVar3 [32];
  undefined2 uVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  long in_FS_OFFSET;
  bool bVar9;
  undefined1 auVar10 [16];
  undefined1 local_10b8 [4096];
  undefined1 local_b8 [92];
  byte local_5c;
  ushort local_58;
  undefined4 local_40;
  undefined1 local_3c;
  byte local_35;
  byte local_34;
  byte local_33;
  byte local_32;
  byte local_31;
  
  bVar1 = *param_6;
  local_35 = param_6[1];
  local_34 = param_6[2];
  bVar2 = param_6[3];
  local_33 = param_6[4];
  local_32 = param_6[5];
  local_31 = param_6[6];
  lVar5 = 0;
  uVar7 = param_5;
  if (0x1f < param_5) {
    do {
      auVar3 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])(param_4 + lVar5));
      if ((((((((((((((((((((((((((((((((SUB321(auVar3 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar3 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar3 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar3 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar3 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar3 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar3 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar3 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar3 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar3 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar3 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar3 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar3 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar3 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar3 >> 0x77,0) & 1) != 0) || SUB321(auVar3 >> 0x7f,0) != '\0')
                        || (SUB321(auVar3 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar3 >> 0x8f,0) & 1) != 0) || (SUB321(auVar3 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar3 >> 0x9f,0) & 1) != 0) || (SUB321(auVar3 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar3 >> 0xaf,0) & 1) != 0) || (SUB321(auVar3 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar3 >> 0xbf,0) != '\0') || (SUB321(auVar3 >> 199,0) & 1) != 0) ||
               (SUB321(auVar3 >> 0xcf,0) & 1) != 0) || (SUB321(auVar3 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar3 >> 0xdf,0) & 1) != 0) || (SUB321(auVar3 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar3 >> 0xef,0) & 1) != 0) || (SUB321(auVar3 >> 0xf7,0) & 1) != 0) ||
          auVar3[0x1f] < '\0') goto LAB_011d8f4f;
      lVar5 = lVar5 + 0x20;
      uVar7 = uVar7 - 0x20;
    } while (0x1f < uVar7);
  }
  if (uVar7 != 0) {
    uVar8 = 0;
    do {
      if (*(char *)(lVar5 + param_4 + uVar8) == '\0') goto LAB_011d8f4f;
      uVar8 = uVar8 + 1;
    } while (uVar7 != uVar8);
  }
  uVar4 = 0x31;
  if (param_5 < 0x1000) {
    FUN_011f4580(local_10b8,param_4,param_5);
    local_10b8[param_5] = 0;
    uVar7 = (ulong)local_32;
    lVar5 = *(long *)(in_FS_OFFSET + -0x40010);
    if ((lVar5 != 0) && ((*(byte *)(lVar5 + 0x21c) & 1) == 0)) {
      uVar8 = *(ulong *)(lVar5 + 8);
      do {
        LOCK();
        uVar6 = *(ulong *)(lVar5 + 8);
        bVar9 = uVar8 == uVar6;
        if (bVar9) {
          *(ulong *)(lVar5 + 8) = uVar8 | 3;
          uVar6 = uVar8;
        }
        UNLOCK();
        uVar8 = uVar6;
      } while (!bVar9);
      if ((uVar6 & 7) == 0) goto LAB_011d8ec2;
      if (((uint)uVar6 & 7) != 6) goto LAB_011d8ebf;
LAB_011d8f47:
      *(undefined2 *)(param_1 + 1) = 0x11;
      goto LAB_011d8f57;
    }
LAB_011d8ebf:
    lVar5 = 0;
LAB_011d8ec2:
    uVar7 = (ulong)((local_32 ^ 1) << 8 | (local_31 ^ 1) << 0x11 | bVar1 & 3) +
            (ulong)local_34 * 0x200000 + 0x80000;
    if (lVar5 == 0) {
      syscall();
    }
    else {
      syscall();
      LOCK();
      *(ulong *)(lVar5 + 8) = *(ulong *)(lVar5 + 8) ^ 3;
      UNLOCK();
    }
    if (local_35 == 0) {
      local_40 = 0x101;
      local_3c = 0;
      FUN_011d5fc0(local_b8,local_10b8,&local_40);
      uVar7 = (ulong)local_58;
      if (local_58 == 0) {
        if ((local_5c & 0xf) == 2) {
          syscall();
          *param_1 = 0;
          *(undefined4 *)(param_1 + 1) = 0x20;
          goto LAB_011d8f57;
        }
      }
      else if (local_58 != 0x36) {
        syscall();
        *(ushort *)(param_1 + 1) = local_58;
        goto LAB_011d8f57;
      }
    }
    if ((bVar2 & 3) != 0) {
      uVar7 = *(ulong *)(in_FS_OFFSET + -0x40010);
      if ((uVar7 == 0) || ((*(byte *)(uVar7 + 0x21c) & 1) != 0)) {
LAB_011d91f2:
        uVar7 = 0;
      }
      else {
        uVar8 = *(ulong *)(uVar7 + 8);
        do {
          LOCK();
          uVar6 = *(ulong *)(uVar7 + 8);
          bVar9 = uVar8 == uVar6;
          if (bVar9) {
            *(ulong *)(uVar7 + 8) = uVar8 | 3;
            uVar6 = uVar8;
          }
          UNLOCK();
          uVar8 = uVar6;
        } while (!bVar9);
        if ((uVar6 & 7) != 0) {
          if (((uint)uVar6 & 7) == 6) {
            syscall();
            goto LAB_011d8f47;
          }
          goto LAB_011d91f2;
        }
      }
      if (uVar7 == 0) {
        uVar7 = 0;
        syscall();
      }
      else {
        syscall();
        LOCK();
        *(ulong *)(uVar7 + 8) = *(ulong *)(uVar7 + 8) ^ 3;
        UNLOCK();
      }
    }
    *(undefined2 *)(param_1 + 1) = 0;
    *(undefined4 *)param_1 = 0x101;
    *(undefined1 *)((long)param_1 + 4) = 0;
    goto LAB_011d8f57;
  }
LAB_011d8f53:
  *(undefined2 *)(param_1 + 1) = uVar4;
LAB_011d8f57:
  auVar10._8_8_ = uVar7;
  auVar10._0_8_ = param_1;
  return auVar10;
LAB_011d8f4f:
  uVar4 = 0x32;
  goto LAB_011d8f53;
}


// ---- FUN_011d9340 @ 011d9340

/* WARNING: Removing unreachable block (ram,0x011d9b2a) */
/* WARNING: Removing unreachable block (ram,0x011d9b2f) */
/* WARNING: Removing unreachable block (ram,0x011d9b35) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 *
FUN_011d9340(undefined8 *param_1,undefined8 param_2,int *param_3,char *param_4,ulong param_5,
            uint *param_6)

{
  int iVar1;
  undefined1 auVar2 [32];
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined2 uVar6;
  char *pcVar7;
  undefined8 *puVar8;
  ulong uVar9;
  ulong uVar10;
  char *pcVar11;
  ulong uVar12;
  ulong uVar13;
  ulong uVar14;
  long lVar15;
  ulong uVar16;
  undefined4 *puVar17;
  long in_FS_OFFSET;
  bool bVar18;
  undefined1 local_1100 [4096];
  undefined8 local_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined4 local_9c;
  undefined8 local_98;
  undefined **local_90;
  int *local_88;
  undefined4 local_7c;
  ushort local_78;
  ushort local_74 [2];
  int local_70;
  int local_6c;
  undefined4 local_68;
  int local_64;
  undefined8 local_60;
  int local_54;
  ushort local_50;
  uint6 uStack_4e;
  ulong local_48;
  byte local_3c;
  undefined8 *local_38;
  
  iVar1 = *param_3;
  local_48 = (ulong)*param_6;
  local_3c = (byte)param_6[1];
  local_90 = &PTR_FUN_0100e020;
  local_98 = param_2;
  local_38 = param_1;
  if ((*(byte *)((long)param_6 + 5) & 1) != 0) {
    if (param_5 != 0) {
      uVar12 = (ulong)(*param_4 == '/');
      if (param_5 != uVar12) {
        lVar15 = 0;
        uVar9 = uVar12;
        do {
          uVar10 = param_5;
          if (param_4[lVar15 + uVar12] != '/') goto joined_r0x011d9436;
          uVar9 = uVar9 + 1;
          lVar15 = lVar15 + 1;
        } while (lVar15 != param_5 - uVar12);
      }
    }
    goto LAB_011d9470;
  }
  if (param_5 == 0) {
LAB_011d977d:
    uVar12 = 0;
    pcVar11 = (char *)0x0;
  }
  else {
    uVar9 = (ulong)(*param_4 == '/');
    uVar12 = 0;
    pcVar11 = (char *)0x0;
    if (param_5 != uVar9) {
      lVar15 = 0;
      uVar10 = uVar9;
      do {
        if (param_4[lVar15 + uVar9] != '/') {
          uVar12 = 0;
          pcVar11 = (char *)0x0;
          if (uVar10 == param_5) goto LAB_011d977f;
          goto LAB_011d94d0;
        }
        uVar10 = uVar10 + 1;
        lVar15 = lVar15 + 1;
      } while (lVar15 != param_5 - uVar9);
      goto LAB_011d977d;
    }
  }
LAB_011d977f:
  local_88 = param_3;
  if ((pcVar11 != (char *)0x0 & local_3c) == 0) {
    local_60 = param_2;
    if (pcVar11 != (char *)0x0) goto LAB_011d9802;
    uVar9 = 1;
    pcVar7 = ".";
    uVar12 = 1;
    pcVar11 = ".";
    uVar10 = 0;
LAB_011d9870:
    do {
      if (pcVar7[uVar10] == '\0') goto LAB_011d98f4;
      uVar10 = uVar10 + 1;
    } while (uVar9 != uVar10);
  }
  else {
    local_64 = iVar1;
    local_60 = param_2;
    FUN_011dafd0(&local_50,param_2,&local_64,pcVar11,uVar12);
    uVar5 = _UNK_0100f398;
    uVar4 = _UNK_0100f390;
    uVar3 = _UNK_0100f388;
    if (local_50 != 0) {
      if ((local_50 < 0x37) && ((0x68140100010260U >> ((ulong)(uint)local_50 & 0x3f) & 1) != 0)) {
        local_38[2] = _DAT_0100f380;
        local_38[3] = uVar3;
        local_38[4] = uVar4;
        local_38[5] = uVar5;
        uVar5 = _UNK_0100f388;
        uVar4 = _DAT_0100f380;
        uVar3 = _UNK_0100f378;
        *local_38 = _DAT_0100f370;
        local_38[1] = uVar3;
        local_38[2] = uVar4;
        local_38[3] = uVar5;
        return local_38;
      }
      *(ushort *)(local_38 + 5) = local_50;
      return local_38;
    }
LAB_011d9802:
    lVar15 = 0;
    uVar9 = uVar12;
    if (0x1f < uVar12) {
      do {
        auVar2 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                               *(undefined1 (*) [32])(pcVar11 + lVar15));
        if ((((((((((((((((((((((((((((((((SUB321(auVar2 >> 7,0) & 1) != 0 ||
                                         (SUB321(auVar2 >> 0xf,0) & 1) != 0) ||
                                        (SUB321(auVar2 >> 0x17,0) & 1) != 0) ||
                                       (SUB321(auVar2 >> 0x1f,0) & 1) != 0) ||
                                      (SUB321(auVar2 >> 0x27,0) & 1) != 0) ||
                                     (SUB321(auVar2 >> 0x2f,0) & 1) != 0) ||
                                    (SUB321(auVar2 >> 0x37,0) & 1) != 0) ||
                                   (SUB321(auVar2 >> 0x3f,0) & 1) != 0) ||
                                  (SUB321(auVar2 >> 0x47,0) & 1) != 0) ||
                                 (SUB321(auVar2 >> 0x4f,0) & 1) != 0) ||
                                (SUB321(auVar2 >> 0x57,0) & 1) != 0) ||
                               (SUB321(auVar2 >> 0x5f,0) & 1) != 0) ||
                              (SUB321(auVar2 >> 0x67,0) & 1) != 0) ||
                             (SUB321(auVar2 >> 0x6f,0) & 1) != 0) ||
                            (SUB321(auVar2 >> 0x77,0) & 1) != 0) || SUB321(auVar2 >> 0x7f,0) != '\0'
                           ) || (SUB321(auVar2 >> 0x87,0) & 1) != 0) ||
                         (SUB321(auVar2 >> 0x8f,0) & 1) != 0) || (SUB321(auVar2 >> 0x97,0) & 1) != 0
                        ) || (SUB321(auVar2 >> 0x9f,0) & 1) != 0) ||
                      (SUB321(auVar2 >> 0xa7,0) & 1) != 0) || (SUB321(auVar2 >> 0xaf,0) & 1) != 0)
                    || (SUB321(auVar2 >> 0xb7,0) & 1) != 0) || SUB321(auVar2 >> 0xbf,0) != '\0') ||
                  (SUB321(auVar2 >> 199,0) & 1) != 0) || (SUB321(auVar2 >> 0xcf,0) & 1) != 0) ||
                (SUB321(auVar2 >> 0xd7,0) & 1) != 0) || (SUB321(auVar2 >> 0xdf,0) & 1) != 0) ||
              (SUB321(auVar2 >> 0xe7,0) & 1) != 0) || (SUB321(auVar2 >> 0xef,0) & 1) != 0) ||
            (SUB321(auVar2 >> 0xf7,0) & 1) != 0) || auVar2[0x1f] < '\0') goto LAB_011d98f4;
        lVar15 = lVar15 + 0x20;
        uVar9 = uVar9 - 0x20;
      } while (0x1f < uVar9);
    }
    if (uVar9 != 0) {
      pcVar7 = pcVar11 + lVar15;
      uVar10 = 0;
      goto LAB_011d9870;
    }
  }
  uVar6 = 0x31;
  if (uVar12 < 0x1000) {
    FUN_011f4580(local_1100,pcVar11,uVar12);
    local_1100[uVar12] = 0;
    lVar15 = *(long *)(in_FS_OFFSET + -0x40010);
    if ((lVar15 != 0) && ((*(byte *)(lVar15 + 0x21c) & 1) == 0)) {
      uVar12 = *(ulong *)(lVar15 + 8);
      do {
        LOCK();
        uVar9 = *(ulong *)(lVar15 + 8);
        bVar18 = uVar12 == uVar9;
        if (bVar18) {
          *(ulong *)(lVar15 + 8) = uVar12 | 3;
          uVar9 = uVar12;
        }
        UNLOCK();
        uVar12 = uVar9;
      } while (!bVar18);
      if (((uVar9 & 7) != 0) && (((uint)uVar9 & 7) == 6)) {
        *(undefined2 *)(local_38 + 5) = 0x11;
        return local_38;
      }
    }
    syscall();
                    /* WARNING: Could not recover jumptable at 0x011d9959. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    puVar8 = (undefined8 *)(*(code *)PTR_LAB_01009880)((long)iVar1,local_1100,0x490002);
    return puVar8;
  }
LAB_011d98f8:
  *(undefined2 *)(local_38 + 5) = uVar6;
  return local_38;
joined_r0x011d9436:
  if (uVar9 == uVar10) goto LAB_011d9470;
  if (param_4[uVar10 - 1] == '/') goto code_r0x011d945c;
  lVar15 = uVar9 - uVar10;
  for (uVar13 = uVar10;
      (uVar14 = uVar9, lVar15 != 0 && (uVar14 = uVar13, param_4[uVar13 - 1] != '/'));
      uVar13 = uVar13 - 1) {
    lVar15 = lVar15 + 1;
  }
  if (uVar14 == uVar10) {
LAB_011d9470:
    FUN_011da110(&local_100,&local_98,param_4,param_5,local_48,param_3,0);
    puVar8 = local_38;
LAB_011d973f:
    puVar8[2] = uStack_f0;
    puVar8[3] = uStack_e8;
    puVar8[4] = uStack_e0;
    puVar8[5] = uStack_d8;
    *puVar8 = local_100;
    puVar8[1] = uStack_f8;
    puVar8[2] = uStack_f0;
    puVar8[3] = uStack_e8;
    return puVar8;
  }
  do {
    uVar10 = uVar14;
    if (uVar9 == uVar10) goto LAB_011d95db;
    uVar14 = uVar10 - 1;
  } while (param_4[uVar10 - 1] == '/');
  uVar13 = uVar14;
  do {
    uVar16 = uVar13;
    uVar13 = uVar9;
    if (uVar9 - 1 == uVar16) goto LAB_011d95cf;
    uVar13 = uVar16 - 1;
  } while (param_4[uVar16] != '/');
  uVar13 = uVar16 + 1;
LAB_011d95cf:
  if (uVar13 - 1 == uVar14) goto LAB_011d95db;
joined_r0x011d95e9:
  if (param_4 != (char *)0x0) {
    if (local_3c == 0) {
      local_6c = iVar1;
      FUN_011d8a90(&local_50,param_2,&local_6c,param_4,uVar10,&DAT_0100f3a0);
      local_7c = (undefined4)CONCAT62(uStack_4e,local_50);
      local_78 = (ushort)(uStack_4e >> 0x10);
      if (local_78 != 0) goto LAB_011d9bfd;
      puVar17 = &local_9c;
    }
    else {
      local_60 = param_2;
      local_54 = iVar1;
      FUN_011d8a90(&local_7c,param_2,&local_54,param_4,uVar10,&DAT_01000a74);
      if (local_78 != 0) {
        if ((local_78 == 0x2d) &&
           (local_70 = iVar1, FUN_011dafd0(local_74,local_60,&local_70,param_4,uVar10,0x1ff),
           local_78 = local_74[0], local_74[0] == 0)) {
          FUN_011d8a90();
          local_7c = (undefined4)CONCAT62(uStack_4e,local_50);
          uVar12 = (ulong)(uStack_4e >> 0x10);
          local_78 = (ushort)(uStack_4e >> 0x10);
          uVar3 = _UNK_0100f388;
          uVar4 = _UNK_0100f390;
          uVar5 = _UNK_0100f398;
        }
        else {
          uVar12 = (ulong)local_78;
          local_7c = 0;
          uVar3 = _UNK_0100f388;
          uVar4 = _UNK_0100f390;
          uVar5 = _UNK_0100f398;
        }
        _UNK_0100f388 = uVar3;
        _UNK_0100f390 = uVar4;
        _UNK_0100f398 = uVar5;
        if (0x36 < local_78) {
LAB_011d9bfd:
          *(ushort *)(local_38 + 5) = local_78;
          return local_38;
        }
        local_78 = (ushort)uVar12;
        if ((0x68140100000260U >> (uVar12 & 0x3f) & 1) != 0) {
          local_38[2] = _DAT_0100f380;
          local_38[3] = uVar3;
          local_38[4] = uVar4;
          local_38[5] = uVar5;
          uVar5 = _UNK_0100f388;
          uVar4 = _DAT_0100f380;
          uVar3 = _UNK_0100f378;
          *local_38 = _DAT_0100f370;
          local_38[1] = uVar3;
          local_38[2] = uVar4;
          local_38[3] = uVar5;
          return local_38;
        }
        if ((uVar12 & 0xffff) != 0) goto LAB_011d9bfd;
      }
      puVar17 = &local_68;
    }
    puVar8 = local_38;
    *puVar17 = local_7c;
    pcVar11 = (char *)0x1;
    if (param_5 == 0) {
LAB_011d970f:
      lVar15 = 0;
    }
    else {
      uVar12 = (ulong)(*param_4 == '/');
      if (param_5 == uVar12) goto LAB_011d970f;
      lVar15 = 0;
      uVar9 = uVar12;
      while (param_4[lVar15 + uVar12] == '/') {
        uVar9 = uVar9 + 1;
        lVar15 = lVar15 + 1;
        if (lVar15 == param_5 - uVar12) goto LAB_011d970f;
      }
      while( true ) {
        if (uVar9 == param_5) goto LAB_011d970f;
        if (param_4[param_5 - 1] != '/') break;
        param_5 = param_5 - 1;
      }
      lVar15 = uVar9 - param_5;
      for (uVar12 = param_5;
          (uVar10 = uVar9, lVar15 != 0 && (uVar10 = uVar12, param_4[uVar12 - 1] != '/'));
          uVar12 = uVar12 - 1) {
        lVar15 = lVar15 + 1;
      }
      lVar15 = param_5 - uVar10;
      if (lVar15 == 0) goto LAB_011d970f;
      pcVar11 = param_4 + uVar10;
    }
    FUN_011da110(&local_d0,&local_98,pcVar11,lVar15,local_48,puVar17,1);
    local_100 = local_d0;
    uStack_f8 = uStack_c8;
    uStack_f0 = uStack_c0;
    uStack_e8 = uStack_b8;
    uStack_e0 = uStack_b0;
    uStack_d8 = uStack_a8;
    goto LAB_011d973f;
  }
  goto LAB_011d9470;
code_r0x011d945c:
  uVar10 = uVar10 - 1;
  goto joined_r0x011d9436;
LAB_011d95db:
  uVar10 = uVar12;
  if (uVar9 == 0) goto LAB_011d9470;
  goto joined_r0x011d95e9;
LAB_011d94d0:
  if (param_4[param_5 - 1] == '/') goto code_r0x011d94d8;
  lVar15 = uVar10 - param_5;
  for (uVar12 = param_5;
      (uVar13 = uVar10, lVar15 != 0 && (uVar13 = uVar12, param_4[uVar12 - 1] != '/'));
      uVar12 = uVar12 - 1) {
    lVar15 = lVar15 + 1;
  }
  uVar12 = 0;
  pcVar11 = (char *)0x0;
  if (uVar13 == param_5) goto LAB_011d977f;
  do {
    uVar12 = uVar13;
    pcVar11 = param_4;
    if (uVar10 == uVar12) goto LAB_011d976d;
    uVar13 = uVar12 - 1;
  } while (param_4[uVar12 - 1] == '/');
  uVar14 = uVar13;
  do {
    uVar16 = uVar14;
    uVar14 = uVar10;
    if (uVar10 - 1 == uVar16) goto LAB_011d9761;
    uVar14 = uVar16 - 1;
  } while (param_4[uVar16] != '/');
  uVar14 = uVar16 + 1;
LAB_011d9761:
  if (uVar14 - 1 != uVar13) goto LAB_011d977f;
LAB_011d976d:
  uVar12 = uVar9;
  if (uVar10 != 0) goto LAB_011d977f;
  goto LAB_011d977d;
code_r0x011d94d8:
  param_5 = param_5 - 1;
  if (uVar10 == param_5) goto LAB_011d977d;
  goto LAB_011d94d0;
LAB_011d98f4:
  uVar6 = 0x32;
  goto LAB_011d98f8;
}


// ---- FUN_011d9c10 @ 011d9c10

/* WARNING: Removing unreachable block (ram,0x011d9e87) */
/* WARNING: Removing unreachable block (ram,0x011d9e8d) */
/* WARNING: Removing unreachable block (ram,0x011d9eee) */
/* WARNING: Removing unreachable block (ram,0x011d9f00) */
/* WARNING: Removing unreachable block (ram,0x011d9f07) */
/* WARNING: Removing unreachable block (ram,0x011d9f0f) */
/* WARNING: Removing unreachable block (ram,0x011d9f17) */
/* WARNING: Removing unreachable block (ram,0x011d9d94) */
/* WARNING: Removing unreachable block (ram,0x011d9da0) */
/* WARNING: Removing unreachable block (ram,0x011d9da7) */
/* WARNING: Removing unreachable block (ram,0x011d9daf) */
/* WARNING: Removing unreachable block (ram,0x011d9f74) */
/* WARNING: Removing unreachable block (ram,0x011d9e9b) */
/* WARNING: Removing unreachable block (ram,0x011da04f) */
/* WARNING: Removing unreachable block (ram,0x011da075) */
/* WARNING: Removing unreachable block (ram,0x011da029) */
/* WARNING: Removing unreachable block (ram,0x011da0fa) */
/* WARNING: Removing unreachable block (ram,0x011d9fba) */
/* WARNING: Removing unreachable block (ram,0x011da088) */
/* WARNING: Removing unreachable block (ram,0x011da016) */
/* WARNING: Removing unreachable block (ram,0x011da0c1) */
/* WARNING: Removing unreachable block (ram,0x011d9fcd) */
/* WARNING: Removing unreachable block (ram,0x011da0ae) */
/* WARNING: Removing unreachable block (ram,0x011da03c) */
/* WARNING: Removing unreachable block (ram,0x011da062) */
/* WARNING: Removing unreachable block (ram,0x011da0d4) */
/* WARNING: Removing unreachable block (ram,0x011da0e7) */
/* WARNING: Removing unreachable block (ram,0x011d9fe0) */
/* WARNING: Removing unreachable block (ram,0x011d9ea2) */
/* WARNING: Removing unreachable block (ram,0x011da09b) */
/* WARNING: Recovered jumptable eliminated as dead code */
/* WARNING: Removing unreachable block (ram,0x011d9ff8) */
/* WARNING: Removing unreachable block (ram,0x011d9f7a) */
/* WARNING: Removing unreachable block (ram,0x011d9ff3) */
/* WARNING: Removing unreachable block (ram,0x011d9f8d) */
/* WARNING: Removing unreachable block (ram,0x011d9fa7) */
/* WARNING: Removing unreachable block (ram,0x011d9f94) */
/* WARNING: Removing unreachable block (ram,0x011da00b) */

undefined1  [16]
FUN_011d9c10(undefined4 *param_1,undefined8 param_2,undefined8 param_3,long param_4,ulong param_5,
            long param_6)

{
  byte bVar1;
  undefined1 auVar2 [32];
  undefined2 uVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  long in_FS_OFFSET;
  bool bVar8;
  undefined1 auVar9 [16];
  undefined1 local_103b [4096];
  byte local_3b;
  byte local_3a;
  byte local_38;
  undefined1 local_34;
  
  local_38 = *(byte *)(param_6 + 4);
  local_3b = *(byte *)(param_6 + 5);
  local_3a = *(byte *)(param_6 + 6);
  bVar1 = *(byte *)(param_6 + 7);
  local_34 = *(undefined1 *)(param_6 + 8);
  lVar4 = 0;
  uVar6 = param_5;
  if (0x1f < param_5) {
    do {
      auVar2 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])(param_4 + lVar4));
      if ((((((((((((((((((((((((((((((((SUB321(auVar2 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar2 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar2 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar2 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar2 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar2 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar2 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar2 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar2 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar2 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar2 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar2 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar2 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar2 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar2 >> 0x77,0) & 1) != 0) || SUB321(auVar2 >> 0x7f,0) != '\0')
                        || (SUB321(auVar2 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar2 >> 0x8f,0) & 1) != 0) || (SUB321(auVar2 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar2 >> 0x9f,0) & 1) != 0) || (SUB321(auVar2 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar2 >> 0xaf,0) & 1) != 0) || (SUB321(auVar2 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar2 >> 0xbf,0) != '\0') || (SUB321(auVar2 >> 199,0) & 1) != 0) ||
               (SUB321(auVar2 >> 0xcf,0) & 1) != 0) || (SUB321(auVar2 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar2 >> 0xdf,0) & 1) != 0) || (SUB321(auVar2 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar2 >> 0xef,0) & 1) != 0) || (SUB321(auVar2 >> 0xf7,0) & 1) != 0) ||
          auVar2[0x1f] < '\0') goto LAB_011d9dbf;
      lVar4 = lVar4 + 0x20;
      uVar6 = uVar6 - 0x20;
    } while (0x1f < uVar6);
  }
  if (uVar6 != 0) {
    uVar7 = 0;
    do {
      if (*(char *)(lVar4 + param_4 + uVar7) == '\0') goto LAB_011d9dbf;
      uVar7 = uVar7 + 1;
    } while (uVar6 != uVar7);
  }
  uVar3 = 0x31;
  if (param_5 < 0x1000) {
    FUN_011f4580(local_103b,param_4,param_5);
    local_103b[param_5] = 0;
    uVar6 = (ulong)local_3b;
    lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
    if ((lVar4 != 0) && ((*(byte *)(lVar4 + 0x21c) & 1) == 0)) {
      uVar7 = *(ulong *)(lVar4 + 8);
      do {
        LOCK();
        uVar5 = *(ulong *)(lVar4 + 8);
        bVar8 = uVar7 == uVar5;
        if (bVar8) {
          *(ulong *)(lVar4 + 8) = uVar7 | 3;
          uVar5 = uVar7;
        }
        UNLOCK();
        uVar7 = uVar5;
      } while (!bVar8);
      if ((uVar5 & 7) == 0) goto LAB_011d9d3e;
      if (((uint)uVar5 & 7) != 6) goto LAB_011d9d3b;
LAB_011d9db7:
      *(undefined2 *)(param_1 + 2) = 0x11;
      goto LAB_011d9dc7;
    }
LAB_011d9d3b:
    lVar4 = 0;
LAB_011d9d3e:
    uVar6 = ((ulong)local_3b << 9 | (ulong)local_38) + (ulong)local_3a * 0x80 + 0x80041;
    if (lVar4 == 0) {
      syscall();
    }
    else {
      syscall();
      LOCK();
      *(ulong *)(lVar4 + 8) = *(ulong *)(lVar4 + 8) ^ 3;
      UNLOCK();
    }
    if ((bVar1 & 3) != 0) {
      uVar6 = *(ulong *)(in_FS_OFFSET + -0x40010);
      if ((uVar6 == 0) || ((*(byte *)(uVar6 + 0x21c) & 1) != 0)) {
LAB_011d9eb5:
        uVar6 = 0;
      }
      else {
        uVar7 = *(ulong *)(uVar6 + 8);
        do {
          LOCK();
          uVar5 = *(ulong *)(uVar6 + 8);
          bVar8 = uVar7 == uVar5;
          if (bVar8) {
            *(ulong *)(uVar6 + 8) = uVar7 | 3;
            uVar5 = uVar7;
          }
          UNLOCK();
          uVar7 = uVar5;
        } while (!bVar8);
        if ((uVar5 & 7) != 0) {
          if (((uint)uVar5 & 7) == 6) {
            syscall();
            goto LAB_011d9db7;
          }
          goto LAB_011d9eb5;
        }
      }
      if (uVar6 == 0) {
        uVar6 = 0;
        syscall();
      }
      else {
        syscall();
        LOCK();
        *(ulong *)(uVar6 + 8) = *(ulong *)(uVar6 + 8) ^ 3;
        UNLOCK();
      }
    }
    *(undefined2 *)(param_1 + 2) = 0;
    *param_1 = 0x101;
    *(undefined1 *)(param_1 + 1) = 0;
    goto LAB_011d9dc7;
  }
LAB_011d9dc3:
  *(undefined2 *)(param_1 + 2) = uVar3;
LAB_011d9dc7:
  auVar9._8_8_ = uVar6;
  auVar9._0_8_ = param_1;
  return auVar9;
LAB_011d9dbf:
  uVar3 = 0x32;
  goto LAB_011d9dc3;
}


// ---- FUN_011da110 @ 011da110

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_011da110(ulong *param_1,undefined8 *param_2,ulong param_3,ulong param_4,undefined4 param_5,
                 undefined4 *param_6,byte param_7)

{
  uint uVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  ulong local_a0;
  short local_98;
  undefined4 *local_90;
  ulong local_88;
  ulong local_80;
  undefined8 local_78;
  long local_70;
  undefined4 local_64;
  undefined4 local_60;
  undefined1 local_5c;
  undefined1 local_5b;
  undefined4 local_58;
  undefined4 local_54;
  ulong local_50;
  char local_47;
  char local_46;
  char local_45;
  char local_44;
  char local_43;
  char local_42;
  char local_41;
  char local_40;
  char local_3f;
  char local_3e;
  char local_3d;
  char local_3c;
  char local_3b;
  char local_3a;
  char local_39;
  char local_38;
  char local_37;
  char local_36;
  char local_35;
  char local_34;
  char local_33;
  char local_32;
  char local_31;
  
  local_78 = *param_2;
  local_70 = param_2[1];
  local_54 = *param_6;
  local_90 = param_6;
  local_88 = param_4;
  local_80 = param_3;
switchD_011da352_caseD_9:
  (**(code **)(local_70 + 0x2d8))(local_78,&local_50,8);
  local_47 = "0123456789abcdef"[(uint)(local_50 >> 4) & 0xf];
  local_46 = "0123456789abcdef"[(uint)local_50 & 0xf];
  local_45 = "0123456789abcdef"[(uint)(local_50 >> 0xc) & 0xf];
  local_44 = "0123456789abcdef"[(uint)(local_50 >> 8) & 0xf];
  local_43 = "0123456789abcdef"[(uint)(local_50 >> 0x14) & 0xf];
  local_42 = "0123456789abcdef"[(uint)(local_50 >> 0x10) & 0xf];
  local_41 = "0123456789abcdef"[local_50 >> 0x1c & 0xf];
  local_40 = "0123456789abcdef"[(uint)(local_50 >> 0x18) & 0xf];
  uVar1 = (uint)(local_50 >> 0x20);
  local_3f = "0123456789abcdef"[uVar1 >> 4 & 0xf];
  local_3e = "0123456789abcdef"[uVar1 & 0xf];
  local_3d = "0123456789abcdef"[uVar1 >> 0xc & 0xf];
  local_3c = "0123456789abcdef"[uVar1 >> 8 & 0xf];
  local_3b = "0123456789abcdef"[uVar1 >> 0x14 & 0xf];
  local_3a = "0123456789abcdef"[(ushort)(local_50 >> 0x30) & 0xf];
  local_39 = "0123456789abcdef"[local_50 >> 0x3c];
  local_38 = "0123456789abcdef"[(byte)(local_50 >> 0x38) & 0xf];
  local_58 = local_54;
  local_60 = 0x10100;
  local_5c = 0;
  local_5b = 0;
  local_64 = param_5;
  local_37 = local_47;
  local_36 = local_46;
  local_35 = local_45;
  local_34 = local_44;
  local_33 = local_43;
  local_32 = local_42;
  local_31 = local_41;
  (**(code **)(param_2[1] + 0xd0))(&local_a0,*param_2,&local_58,&local_47,0x10,&local_64);
  uVar4 = _UNK_0100f398;
  uVar3 = _UNK_0100f390;
  uVar2 = _UNK_0100f388;
  if (local_98 != 0) {
    switch(local_98) {
    case 6:
    case 0x20:
    case 0x33:
    case 0x35:
      param_1[2] = _DAT_0100f380;
      param_1[3] = uVar2;
      param_1[4] = uVar3;
      param_1[5] = uVar4;
      uVar4 = _UNK_0100f388;
      uVar3 = _DAT_0100f380;
      uVar2 = _UNK_0100f378;
      *param_1 = _DAT_0100f370;
      param_1[1] = uVar2;
      param_1[2] = uVar3;
      param_1[3] = uVar4;
      return;
    default:
      *(short *)(param_1 + 5) = local_98;
      return;
    case 9:
    case 0x10:
    case 0x2a:
      goto switchD_011da352_caseD_9;
    }
  }
  *(undefined2 *)(param_1 + 5) = 0;
  param_1[3] = local_a0;
  *param_1 = local_50;
  param_1[1] = local_80;
  param_1[2] = local_88;
  *(undefined2 *)((long)param_1 + 0x24) = 0x101;
  *(byte *)((long)param_1 + 0x26) = param_7 & 1;
  *(undefined4 *)(param_1 + 4) = *local_90;
  return;
}


// ---- FUN_011da3d0 @ 011da3d0

/* WARNING: Removing unreachable block (ram,0x011da535) */
/* WARNING: Removing unreachable block (ram,0x011da540) */
/* WARNING: Removing unreachable block (ram,0x011da547) */
/* WARNING: Removing unreachable block (ram,0x011da54f) */
/* WARNING: Removing unreachable block (ram,0x011da55e) */
/* WARNING: Removing unreachable block (ram,0x011da5ed) */
/* WARNING: Removing unreachable block (ram,0x011da5f2) */
/* WARNING: Removing unreachable block (ram,0x011da655) */
/* WARNING: Removing unreachable block (ram,0x011da5a1) */
/* WARNING: Removing unreachable block (ram,0x011da5b0) */
/* WARNING: Removing unreachable block (ram,0x011da5b7) */
/* WARNING: Removing unreachable block (ram,0x011da5bf) */
/* WARNING: Removing unreachable block (ram,0x011da5ce) */
/* WARNING: Removing unreachable block (ram,0x011da65f) */
/* WARNING: Removing unreachable block (ram,0x011da6ad) */
/* WARNING: Removing unreachable block (ram,0x011da683) */
/* WARNING: Removing unreachable block (ram,0x011da6a7) */
/* WARNING: Removing unreachable block (ram,0x011da689) */
/* WARNING: Removing unreachable block (ram,0x011da6a1) */
/* WARNING: Removing unreachable block (ram,0x011da69b) */
/* WARNING: Removing unreachable block (ram,0x011da695) */
/* WARNING: Removing unreachable block (ram,0x011da6b3) */
/* WARNING: Removing unreachable block (ram,0x011da666) */
/* WARNING: Removing unreachable block (ram,0x011da68f) */
/* WARNING: Recovered jumptable eliminated as dead code */

undefined1  [16]
FUN_011da3d0(undefined8 param_1,undefined8 param_2,ulong param_3,ulong param_4,byte param_5)

{
  undefined1 auVar1 [32];
  uint uVar2;
  long lVar3;
  undefined8 uVar4;
  ulong uVar5;
  ulong uVar6;
  long in_FS_OFFSET;
  bool bVar7;
  undefined1 auVar8 [16];
  undefined1 local_1019 [4096];
  byte local_19;
  
  local_19 = param_5 & 0xf;
  lVar3 = 0;
  uVar5 = param_4;
  if (0x1f < param_4) {
    do {
      auVar1 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])(param_3 + lVar3));
      if ((((((((((((((((((((((((((((((((SUB321(auVar1 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar1 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar1 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar1 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar1 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar1 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar1 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar1 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar1 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar1 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar1 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar1 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar1 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar1 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar1 >> 0x77,0) & 1) != 0) || SUB321(auVar1 >> 0x7f,0) != '\0')
                        || (SUB321(auVar1 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar1 >> 0x8f,0) & 1) != 0) || (SUB321(auVar1 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar1 >> 0x9f,0) & 1) != 0) || (SUB321(auVar1 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar1 >> 0xaf,0) & 1) != 0) || (SUB321(auVar1 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar1 >> 0xbf,0) != '\0') || (SUB321(auVar1 >> 199,0) & 1) != 0) ||
               (SUB321(auVar1 >> 0xcf,0) & 1) != 0) || (SUB321(auVar1 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar1 >> 0xdf,0) & 1) != 0) || (SUB321(auVar1 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar1 >> 0xef,0) & 1) != 0) || (SUB321(auVar1 >> 0xf7,0) & 1) != 0) ||
          auVar1[0x1f] < '\0') goto switchD_011da65f_caseD_53;
      lVar3 = lVar3 + 0x20;
      uVar5 = uVar5 - 0x20;
    } while (0x1f < uVar5);
  }
  if (uVar5 != 0) {
    lVar3 = lVar3 + param_3;
    uVar6 = 0;
    do {
      if (*(char *)(lVar3 + uVar6) == '\0') goto switchD_011da65f_caseD_53;
      uVar6 = uVar6 + 1;
    } while (uVar5 != uVar6);
  }
  uVar4 = CONCAT62((int6)((ulong)lVar3 >> 0x10),0x31);
  if (0xfff < param_4) goto LAB_011da670;
  FUN_011f4580(local_1019,param_3,param_4);
  local_1019[param_4] = 0;
  lVar3 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar3 == 0) || ((*(byte *)(lVar3 + 0x21c) & 1) != 0)) {
LAB_011da4d6:
    lVar3 = 0;
  }
  else {
    uVar5 = *(ulong *)(lVar3 + 8);
    do {
      LOCK();
      uVar6 = *(ulong *)(lVar3 + 8);
      bVar7 = uVar5 == uVar6;
      if (bVar7) {
        *(ulong *)(lVar3 + 8) = uVar5 | 3;
        uVar6 = uVar5;
      }
      UNLOCK();
      uVar5 = uVar6;
    } while (!bVar7);
    if ((uVar6 & 7) != 0) {
      uVar2 = (uint)uVar6 & 7;
      param_3 = (ulong)uVar2;
      uVar4 = 0x11;
      if (uVar2 == 6) goto LAB_011da670;
      goto LAB_011da4d6;
    }
  }
  param_3 = (ulong)(byte)(local_19 >> 3 & 1 | local_19 >> 1 & 2 | local_19 * '\x02' & 4);
  if ((local_19 & 1) == 0) {
    if (lVar3 != 0) {
      syscall();
      goto code_r0x011da5d7;
    }
    syscall();
  }
  else {
    if (lVar3 != 0) {
      syscall();
code_r0x011da5d7:
      if (lVar3 == 0) {
        uVar4 = 0;
      }
      else {
        LOCK();
        *(ulong *)(lVar3 + 8) = *(ulong *)(lVar3 + 8) ^ 3;
        UNLOCK();
        uVar4 = 0;
      }
      goto LAB_011da670;
    }
    syscall();
  }
  uVar4 = 0;
LAB_011da670:
  auVar8._8_8_ = param_3;
  auVar8._0_8_ = uVar4;
  return auVar8;
switchD_011da65f_caseD_53:
  uVar4 = CONCAT62((int6)((ulong)lVar3 >> 0x10),0x32);
  goto LAB_011da670;
}


// ---- FUN_011da6c0 @ 011da6c0

/* WARNING: Removing unreachable block (ram,0x011da991) */
/* WARNING: Removing unreachable block (ram,0x011da99a) */
/* WARNING: Removing unreachable block (ram,0x011da85a) */
/* WARNING: Removing unreachable block (ram,0x011da860) */
/* WARNING: Removing unreachable block (ram,0x011da867) */
/* WARNING: Removing unreachable block (ram,0x011da86f) */
/* WARNING: Removing unreachable block (ram,0x011da92d) */
/* WARNING: Removing unreachable block (ram,0x011da968) */
/* WARNING: Removing unreachable block (ram,0x011da96b) */
/* WARNING: Removing unreachable block (ram,0x011da9d2) */
/* WARNING: Removing unreachable block (ram,0x011da977) */
/* WARNING: Removing unreachable block (ram,0x011da9f2) */
/* WARNING: Removing unreachable block (ram,0x011daa39) */
/* WARNING: Removing unreachable block (ram,0x011daa31) */
/* WARNING: Removing unreachable block (ram,0x011daa40) */
/* WARNING: Removing unreachable block (ram,0x011da9a5) */
/* WARNING: Removing unreachable block (ram,0x011dab9e) */
/* WARNING: Removing unreachable block (ram,0x011dab66) */
/* WARNING: Removing unreachable block (ram,0x011dab2e) */
/* WARNING: Removing unreachable block (ram,0x011da9ac) */
/* WARNING: Recovered jumptable eliminated as dead code */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 *
FUN_011da6c0(undefined8 *param_1,undefined8 param_2,int *param_3,long param_4,ulong param_5,
            byte *param_6)

{
  int iVar1;
  undefined1 auVar2 [32];
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  undefined4 unaff_R12D;
  long in_FS_OFFSET;
  bool bVar6;
  undefined1 local_1148 [4096];
  undefined1 local_148 [283];
  byte local_2d;
  
  iVar1 = *param_3;
  local_2d = *param_6;
  lVar3 = 0;
  uVar4 = param_5;
  if (0x1f < param_5) {
    do {
      auVar2 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])(param_4 + lVar3));
      if ((((((((((((((((((((((((((((((((SUB321(auVar2 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar2 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar2 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar2 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar2 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar2 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar2 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar2 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar2 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar2 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar2 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar2 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar2 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar2 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar2 >> 0x77,0) & 1) != 0) || SUB321(auVar2 >> 0x7f,0) != '\0')
                        || (SUB321(auVar2 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar2 >> 0x8f,0) & 1) != 0) || (SUB321(auVar2 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar2 >> 0x9f,0) & 1) != 0) || (SUB321(auVar2 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar2 >> 0xaf,0) & 1) != 0) || (SUB321(auVar2 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar2 >> 0xbf,0) != '\0') || (SUB321(auVar2 >> 199,0) & 1) != 0) ||
               (SUB321(auVar2 >> 0xcf,0) & 1) != 0) || (SUB321(auVar2 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar2 >> 0xdf,0) & 1) != 0) || (SUB321(auVar2 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar2 >> 0xef,0) & 1) != 0) || (SUB321(auVar2 >> 0xf7,0) & 1) != 0) ||
          auVar2[0x1f] < '\0') goto LAB_011da741;
      lVar3 = lVar3 + 0x20;
      uVar4 = uVar4 - 0x20;
    } while (0x1f < uVar4);
  }
  if (uVar4 != 0) {
    uVar5 = 0;
    do {
      if (*(char *)(lVar3 + param_4 + uVar5) == '\0') {
LAB_011da741:
        *(undefined2 *)(param_1 + 0xc) = 0x32;
        return param_1;
      }
      uVar5 = uVar5 + 1;
    } while (uVar4 != uVar5);
  }
  if (0xfff < param_5) {
    *(undefined2 *)(param_1 + 0xc) = 0x31;
    return param_1;
  }
  FUN_011f4580(local_1148,param_4,param_5);
  local_1148[param_5] = 0;
  lVar3 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar3 != 0) && ((*(byte *)(lVar3 + 0x21c) & 1) == 0)) {
    uVar4 = *(ulong *)(lVar3 + 8);
    do {
      LOCK();
      uVar5 = *(ulong *)(lVar3 + 8);
      bVar6 = uVar4 == uVar5;
      if (bVar6) {
        *(ulong *)(lVar3 + 8) = uVar4 | 3;
        uVar5 = uVar4;
      }
      UNLOCK();
      uVar4 = uVar5;
    } while (!bVar6);
    if ((uVar5 & 7) == 0) goto LAB_011da7c2;
    if (((uint)uVar5 & 7) == 6) {
      *(undefined2 *)(param_1 + 0xc) = 0x11;
      return param_1;
    }
  }
  lVar3 = 0;
LAB_011da7c2:
  if (lVar3 == 0) {
    lVar3 = 0;
    syscall();
  }
  else {
    param_5 = 0;
    syscall();
    LOCK();
    *(ulong *)(lVar3 + 8) = *(ulong *)(lVar3 + 8) ^ 3;
    UNLOCK();
  }
  *param_1 = 0x7e7;
  *(undefined4 *)(param_1 + 1) = 0xffffffff;
  *(undefined4 *)((long)param_1 + 0xc) = 0;
  *(char *)(param_1 + 2) = (char)lVar3;
  *(undefined8 *)((long)param_1 + 0x11) = 0;
  param_1[3] = 0;
  *(int *)(param_1 + 5) = (int)local_1148;
  param_1[4] = param_5;
  *(undefined4 *)((long)param_1 + 0x2c) = 0;
  *(uint *)(param_1 + 7) = ((byte)~local_2d & 1) << 8 | 0x800;
  param_1[6] = (long)iVar1;
  *(undefined4 *)((long)param_1 + 0x3c) = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  *(int *)(param_1 + 10) = (int)local_148;
  *(int *)((long)param_1 + 0x54) = iVar1;
  *(undefined4 *)(param_1 + 0xb) = unaff_R12D;
  *(undefined1 *)((long)param_1 + 0x5c) = 0;
  *(undefined2 *)((long)param_1 + 0x5d) = 0;
  *(undefined1 *)((long)param_1 + 0x5f) = 0;
  *(undefined2 *)(param_1 + 0xc) = 4;
  *(undefined8 *)((long)param_1 + 0x62) = 0;
  param_1[0xd] = 0;
  return param_1;
}


// ---- FUN_011dabe0 @ 011dabe0

undefined8 * FUN_011dabe0(undefined8 *param_1,undefined8 param_2,undefined4 *param_3)

{
  undefined8 local_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 local_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 local_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined4 local_18;
  undefined1 local_14;
  
  local_18 = *param_3;
  local_14 = 0;
  FUN_011d5fc0(&local_88,param_2,&local_18);
  param_1[10] = uStack_38;
  param_1[0xb] = uStack_30;
  param_1[0xc] = uStack_28;
  param_1[0xd] = uStack_20;
  param_1[8] = local_48;
  param_1[9] = uStack_40;
  param_1[10] = uStack_38;
  param_1[0xb] = uStack_30;
  param_1[4] = local_68;
  param_1[5] = uStack_60;
  param_1[6] = uStack_58;
  param_1[7] = uStack_50;
  *param_1 = local_88;
  param_1[1] = uStack_80;
  param_1[2] = uStack_78;
  param_1[3] = uStack_70;
  return param_1;
}


// ---- FUN_011dac40 @ 011dac40

undefined8 *
FUN_011dac40(undefined8 *param_1,undefined8 param_2,undefined4 *param_3,undefined8 param_4,
            undefined8 param_5,undefined4 param_6)

{
  undefined4 uVar1;
  undefined8 local_58;
  undefined8 local_50;
  undefined4 local_44;
  short local_40;
  short local_3c [2];
  undefined4 local_38;
  undefined4 local_34;
  
  uVar1 = *param_3;
  local_50 = param_2;
  local_34 = param_6;
  FUN_011d8a90(&local_44);
  if (local_40 == 0) {
    *(undefined4 *)param_1 = local_44;
    *(undefined2 *)((long)param_1 + 4) = 0;
  }
  else if (local_40 == 0x2d) {
    local_38 = uVar1;
    FUN_011dafd0(local_3c,local_50,&local_38,param_4,param_5,local_34);
    if (local_3c[0] == 0) {
      FUN_011d8a90(&local_58);
      *param_1 = local_58;
    }
    else {
      *(short *)((long)param_1 + 4) = local_3c[0];
    }
  }
  else {
    *(short *)((long)param_1 + 4) = local_40;
  }
  return param_1;
}


// ---- FUN_011dad00 @ 011dad00

/* WARNING: Removing unreachable block (ram,0x011dafb5) */
/* WARNING: Removing unreachable block (ram,0x011daea4) */
/* WARNING: Removing unreachable block (ram,0x011daeb0) */
/* WARNING: Removing unreachable block (ram,0x011daeb7) */
/* WARNING: Removing unreachable block (ram,0x011daebf) */
/* WARNING: Removing unreachable block (ram,0x011daf68) */
/* WARNING: Removing unreachable block (ram,0x011daf92) */
/* WARNING: Removing unreachable block (ram,0x011daf95) */
/* WARNING: Removing unreachable block (ram,0x011dafa5) */
/* WARNING: Removing unreachable block (ram,0x011dafab) */
/* WARNING: Removing unreachable block (ram,0x011daf58) */
/* WARNING: Removing unreachable block (ram,0x011daf5d) */
/* WARNING: Removing unreachable block (ram,0x011dafbb) */

void FUN_011dad00(undefined4 *param_1,undefined8 param_2,long param_3,ulong param_4)

{
  undefined1 auVar1 [32];
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  long in_FS_OFFSET;
  bool bVar5;
  undefined1 local_1128 [4360];
  
  lVar2 = 0;
  uVar3 = param_4;
  if (0x1f < param_4) {
    do {
      auVar1 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])(param_3 + lVar2));
      if ((((((((((((((((((((((((((((((((SUB321(auVar1 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar1 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar1 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar1 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar1 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar1 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar1 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar1 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar1 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar1 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar1 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar1 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar1 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar1 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar1 >> 0x77,0) & 1) != 0) || SUB321(auVar1 >> 0x7f,0) != '\0')
                        || (SUB321(auVar1 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar1 >> 0x8f,0) & 1) != 0) || (SUB321(auVar1 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar1 >> 0x9f,0) & 1) != 0) || (SUB321(auVar1 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar1 >> 0xaf,0) & 1) != 0) || (SUB321(auVar1 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar1 >> 0xbf,0) != '\0') || (SUB321(auVar1 >> 199,0) & 1) != 0) ||
               (SUB321(auVar1 >> 0xcf,0) & 1) != 0) || (SUB321(auVar1 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar1 >> 0xdf,0) & 1) != 0) || (SUB321(auVar1 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar1 >> 0xef,0) & 1) != 0) || (SUB321(auVar1 >> 0xf7,0) & 1) != 0) ||
          auVar1[0x1f] < '\0') goto LAB_011dad91;
      lVar2 = lVar2 + 0x20;
      uVar3 = uVar3 - 0x20;
    } while (0x1f < uVar3);
  }
  if (uVar3 != 0) {
    uVar4 = 0;
    do {
      if (*(char *)(lVar2 + param_3 + uVar4) == '\0') {
LAB_011dad91:
        *(undefined2 *)param_1 = 0x32;
        return;
      }
      uVar4 = uVar4 + 1;
    } while (uVar3 != uVar4);
  }
  if (0xfff < param_4) {
    *(undefined2 *)param_1 = 0x31;
    return;
  }
  FUN_011f4580(local_1128,param_3,param_4);
  local_1128[param_4] = 0;
  lVar2 = *(long *)(in_FS_OFFSET + -0x40010);
  if (lVar2 == 0) {
    lVar2 = 0;
  }
  else {
    if ((*(byte *)(lVar2 + 0x21c) & 1) == 0) {
      uVar3 = *(ulong *)(lVar2 + 8);
      do {
        LOCK();
        uVar4 = *(ulong *)(lVar2 + 8);
        bVar5 = uVar3 == uVar4;
        if (bVar5) {
          *(ulong *)(lVar2 + 8) = uVar3 | 3;
          uVar4 = uVar3;
        }
        UNLOCK();
        uVar3 = uVar4;
      } while (!bVar5);
      if ((uVar4 & 7) == 0) goto LAB_011dae1a;
      if (((uint)uVar4 & 7) == 6) {
        *(undefined2 *)param_1 = 0x11;
        return;
      }
    }
    lVar2 = 0;
  }
LAB_011dae1a:
  if (lVar2 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar2 + 8) = *(ulong *)(lVar2 + 8) ^ 3;
    UNLOCK();
  }
  *param_1 = 4;
  return;
}


// ---- FUN_011dafd0 @ 011dafd0

void FUN_011dafd0(ushort *param_1,undefined8 param_2,undefined4 *param_3,char *param_4,ulong param_5
                 ,undefined4 param_6)

{
  ulong uVar1;
  ushort uVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  bool bVar9;
  ushort local_44;
  char local_42;
  ushort *local_40;
  byte local_31;
  
  if (param_5 != 0) {
    uVar3 = (ulong)(*param_4 == '/');
    if (param_5 != uVar3) {
      lVar7 = 0;
      uVar8 = uVar3;
      do {
        uVar4 = param_5;
        if (param_4[lVar7 + uVar3] != '/') goto joined_r0x011db027;
        uVar8 = uVar8 + 1;
        lVar7 = lVar7 + 1;
      } while (lVar7 != param_5 - uVar3);
    }
  }
LAB_011db067:
  param_1[0] = 0x32;
  param_1[1] = 0;
  return;
joined_r0x011db027:
  if (uVar8 == uVar4) goto LAB_011db067;
  if (param_4[uVar4 - 1] == '/') {
    uVar4 = uVar4 - 1;
    goto joined_r0x011db027;
  }
  lVar7 = uVar8 - uVar4;
  for (uVar3 = uVar4; (uVar6 = uVar8, lVar7 != 0 && (uVar6 = uVar3, param_4[uVar3 - 1] != '/'));
      uVar3 = uVar3 - 1) {
    lVar7 = lVar7 + 1;
  }
  if (uVar6 == uVar4) goto LAB_011db067;
  uVar3 = 0;
  local_40 = param_1;
  do {
    local_31 = (byte)uVar3;
    while( true ) {
      uVar2 = FUN_011db210(uVar3,param_3,param_4,uVar4,param_6);
      uVar3 = 1;
      if (uVar2 == 0) break;
      if (uVar2 == 0x2a) {
        FUN_011dad00(&local_44,*param_3,param_4,uVar4);
        uVar2 = local_44;
        if (local_44 != 0) {
LAB_011db1dd:
          *local_40 = uVar2;
          return;
        }
        uVar3 = (ulong)local_31;
        if (local_42 != '\x02') {
          local_40[0] = 0x2e;
          local_40[1] = 0;
          return;
        }
        break;
      }
      if (uVar2 != 0x2d) goto LAB_011db1dd;
      uVar5 = uVar6 - 1;
      do {
        uVar4 = uVar6;
        if (uVar8 == uVar4) goto LAB_011db1e9;
        uVar3 = uVar5 - 1;
        uVar1 = uVar5;
        uVar5 = uVar3;
        uVar6 = uVar4 - 1;
      } while (param_4[uVar4 - 1] == '/');
      do {
        uVar5 = uVar1;
        uVar6 = uVar8;
        if (uVar8 - 1 == uVar5) goto LAB_011db12e;
        uVar1 = uVar5 - 1;
      } while (param_4[uVar5] != '/');
      uVar6 = uVar5 + 1;
LAB_011db12e:
      if (uVar6 - 1 == uVar4 - 1) {
LAB_011db1e9:
        local_40[0] = 0x2d;
        local_40[1] = 0;
        return;
      }
    }
    if (uVar4 < param_5) {
      while (param_4[uVar4] == '/') {
        uVar4 = uVar4 + 1;
        if (param_5 == uVar4) goto LAB_011db1c7;
      }
    }
    uVar6 = uVar4;
    if (param_5 <= uVar4) break;
    do {
      uVar5 = uVar6;
      if (param_4[uVar6] == '/') break;
      uVar6 = uVar6 + 1;
      uVar5 = param_5;
    } while (param_5 != uVar6);
    bVar9 = uVar4 != uVar5;
    uVar6 = uVar4;
    uVar4 = uVar5;
  } while (bVar9);
LAB_011db1c7:
  *local_40 = 0;
  *(byte *)(local_40 + 1) = (byte)uVar3 & 1;
  return;
}


// ---- FUN_011db210 @ 011db210

/* WARNING: Removing unreachable block (ram,0x011db3c8) */
/* WARNING: Removing unreachable block (ram,0x011db3ce) */

undefined8
FUN_011db210(undefined8 param_1,int *param_2,long param_3,ulong param_4,undefined4 param_5)

{
  int iVar1;
  undefined1 auVar2 [32];
  long lVar3;
  undefined8 uVar4;
  ulong uVar5;
  ulong uVar6;
  long in_FS_OFFSET;
  bool bVar7;
  undefined1 local_1020 [4096];
  
  iVar1 = *param_2;
  lVar3 = 0;
  uVar5 = param_4;
  if (0x1f < param_4) {
    do {
      auVar2 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])(param_3 + lVar3));
      if ((((((((((((((((((((((((((((((((SUB321(auVar2 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar2 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar2 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar2 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar2 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar2 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar2 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar2 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar2 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar2 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar2 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar2 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar2 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar2 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar2 >> 0x77,0) & 1) != 0) || SUB321(auVar2 >> 0x7f,0) != '\0')
                        || (SUB321(auVar2 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar2 >> 0x8f,0) & 1) != 0) || (SUB321(auVar2 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar2 >> 0x9f,0) & 1) != 0) || (SUB321(auVar2 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar2 >> 0xaf,0) & 1) != 0) || (SUB321(auVar2 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar2 >> 0xbf,0) != '\0') || (SUB321(auVar2 >> 199,0) & 1) != 0) ||
               (SUB321(auVar2 >> 0xcf,0) & 1) != 0) || (SUB321(auVar2 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar2 >> 0xdf,0) & 1) != 0) || (SUB321(auVar2 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar2 >> 0xef,0) & 1) != 0) || (SUB321(auVar2 >> 0xf7,0) & 1) != 0) ||
          auVar2[0x1f] < '\0') goto LAB_011db42e;
      lVar3 = lVar3 + 0x20;
      uVar5 = uVar5 - 0x20;
    } while (0x1f < uVar5);
  }
  if (uVar5 != 0) {
    lVar3 = lVar3 + param_3;
    uVar6 = 0;
    do {
      if (*(char *)(lVar3 + uVar6) == '\0') {
LAB_011db42e:
        return CONCAT62((int6)((ulong)lVar3 >> 0x10),0x32);
      }
      uVar6 = uVar6 + 1;
    } while (uVar5 != uVar6);
  }
  if (0xfff < param_4) {
    return CONCAT62((int6)((ulong)lVar3 >> 0x10),0x31);
  }
  FUN_011f4580(local_1020,param_3,param_4);
  local_1020[param_4] = 0;
  lVar3 = *(long *)(in_FS_OFFSET + -0x40010);
  if (lVar3 == 0) goto LAB_011db397;
  if ((*(byte *)(lVar3 + 0x21c) & 1) == 0) {
    uVar5 = *(ulong *)(lVar3 + 8);
    do {
      LOCK();
      uVar6 = *(ulong *)(lVar3 + 8);
      bVar7 = uVar5 == uVar6;
      if (bVar7) {
        *(ulong *)(lVar3 + 8) = uVar5 | 3;
        uVar6 = uVar5;
      }
      UNLOCK();
      uVar5 = uVar6;
    } while (!bVar7);
    if ((uVar6 & 7) != 0) {
      if (((uint)uVar6 & 7) == 6) {
        return 0x11;
      }
      goto LAB_011db316;
    }
  }
  else {
LAB_011db316:
    lVar3 = 0;
  }
  if (lVar3 != 0) {
    syscall();
                    /* WARNING: Could not recover jumptable at 0x011db34a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar4 = (*(code *)PTR_LAB_0100a4b8)((long)iVar1);
    return uVar4;
  }
LAB_011db397:
  syscall();
                    /* WARNING: Could not recover jumptable at 0x011db3bb. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar4 = (*DAT_0100a890)((long)iVar1,local_1020,param_5);
  return uVar4;
}


// ---- FUN_011db4e0 @ 011db4e0

void FUN_011db4e0(long param_1,long param_2)

{
  undefined8 unaff_retaddr;
  
  if (*(long *)(param_2 + 0x10) != 0) {
    if (*(long *)(param_2 + 8) != 0) {
      (**(code **)(*(long *)(param_1 + 0x330) + 0x18))
                (*(undefined8 *)(param_1 + 0x328),*(long *)(param_2 + 0x10),
                 *(long *)(param_2 + 8) << 3,2,unaff_retaddr);
    }
    *(undefined8 *)(param_2 + 0x10) = 0;
  }
  return;
}


// ---- FUN_011db530 @ 011db530

/* WARNING: Removing unreachable block (ram,0x011dbf7f) */
/* WARNING: Removing unreachable block (ram,0x011dbf8b) */
/* WARNING: Removing unreachable block (ram,0x011dbf8e) */
/* WARNING: Removing unreachable block (ram,0x011dbb34) */
/* WARNING: Removing unreachable block (ram,0x011dbb3f) */
/* WARNING: Type propagation algorithm not settling */

ulong FUN_011db530(long param_1,long *param_2,ulong *param_3)

{
  short *psVar1;
  undefined8 *puVar2;
  undefined1 uVar3;
  uint uVar4;
  undefined4 uVar5;
  long *plVar6;
  uint uVar7;
  short sVar8;
  short sVar9;
  ulong uVar10;
  undefined1 *puVar11;
  ulong uVar12;
  ulong *puVar13;
  ulong uVar14;
  int iVar15;
  ulong *extraout_RDX;
  ulong *extraout_RDX_00;
  ulong *extraout_RDX_01;
  long lVar16;
  long lVar17;
  long lVar18;
  long lVar19;
  long lVar20;
  uint uVar21;
  long lVar22;
  ulong uVar23;
  long in_FS_OFFSET;
  bool bVar24;
  undefined1 auVar25 [16];
  undefined8 unaff_retaddr;
  undefined1 local_3d8 [512];
  undefined8 local_1d8;
  undefined8 uStack_1d0;
  undefined8 uStack_1c8;
  undefined8 uStack_1c0;
  undefined8 uStack_1b8;
  undefined8 uStack_1b0;
  undefined8 uStack_1a8;
  undefined8 local_198;
  undefined8 uStack_190;
  undefined8 uStack_188;
  undefined8 local_180;
  undefined8 uStack_178;
  undefined8 uStack_170;
  undefined8 uStack_168;
  undefined8 local_158;
  undefined8 uStack_150;
  undefined8 local_148;
  ushort local_140;
  undefined8 local_138;
  undefined8 uStack_130;
  undefined8 local_128;
  ushort local_120;
  long local_118;
  ulong *local_110;
  undefined7 uStack_108;
  undefined1 local_101;
  undefined7 uStack_100;
  ulong local_f8;
  ulong local_f0;
  ulong local_e8;
  ulong local_e0;
  byte local_d8;
  undefined7 local_d7;
  undefined1 uStack_d0;
  undefined7 uStack_cf;
  undefined1 local_c8;
  ulong local_b8;
  long local_b0;
  long local_a8;
  ulong local_a0;
  undefined8 local_98;
  undefined8 *puStack_90;
  long *local_88;
  undefined1 *local_80;
  ulong local_78;
  uint local_70;
  undefined1 *local_60;
  uint local_58;
  uint local_54;
  long *local_50;
  byte local_41;
  byte local_40;
  byte local_38;
  byte local_31;
  
  local_f0 = *param_3;
  local_f8 = param_3[1];
  local_31 = (byte)param_3[2];
  uStack_100 = (undefined7)(param_3[3] >> 8);
  uStack_108 = (undefined7)*(undefined8 *)((long)param_3 + 0x11);
  local_101 = (undefined1)((ulong)*(undefined8 *)((long)param_3 + 0x11) >> 0x38);
  local_110 = param_3;
  local_41 = (byte)param_3[4];
  local_98 = *(undefined8 *)(param_1 + 0x328);
  puStack_90 = *(undefined8 **)(param_1 + 0x330);
  local_88 = param_2;
  local_80 = local_3d8;
  local_78 = 0x40;
  local_70 = 0;
  uVar21 = *(uint *)(param_2 + 4);
  if (uVar21 == 0xffffffff) {
    return 0;
  }
  local_50 = param_2;
  do {
    uVar7 = local_70;
    plVar6 = local_88;
    uVar10 = (ulong)uVar21;
    lVar16 = *param_2;
    lVar19 = uVar10 * 9;
    lVar18 = *(long *)(lVar16 + 8 + uVar10 * 0x48);
    local_60 = (undefined1 *)*(long *)(lVar16 + 0x10 + uVar10 * 0x48);
    uVar4 = *(uint *)(lVar16 + 0x38 + uVar10 * 0x48);
    switch(*(byte *)(lVar16 + 0x30 + uVar10 * 0x48) & 3) {
    case 0:
      uVar10 = (ulong)local_70;
      if (uVar10 == 0x40) {
        puVar11 = (undefined1 *)local_88[2];
        if (puVar11 == (undefined1 *)0x0) {
          uVar12 = local_88[1];
          local_e8 = CONCAT71(local_e8._1_7_,0x1fffffffffffffff < uVar12);
          if (0x1fffffffffffffff < uVar12) {
            return 0x1f;
          }
          if (uVar12 * 8 == 0) {
            puVar11 = (undefined1 *)0xfffffffffffffffc;
          }
          else {
            puVar11 = (undefined1 *)(*(code *)*puStack_90)(local_98,uVar12 * 8,2,unaff_retaddr);
            if (puVar11 == (undefined1 *)0x0) {
              return 0x1f;
            }
          }
          plVar6[2] = (long)puVar11;
        }
        else {
          uVar12 = local_88[1];
        }
        FUN_011f4580(puVar11,local_80,0x200);
        local_80 = puVar11;
        local_78 = uVar12;
        param_3 = extraout_RDX_00;
        param_2 = local_50;
      }
      *(int *)(local_80 + uVar10 * 8) = (int)local_60;
      *(undefined4 *)(local_80 + uVar10 * 8 + 4) = 9;
      uVar21 = uVar4;
      break;
    case 1:
      uVar5 = *(undefined4 *)(lVar16 + 0x28 + uVar10 * 0x48);
      uVar10 = (ulong)local_70;
      uVar21 = uVar4;
      if (uVar10 == 0x40) {
        puVar11 = (undefined1 *)local_88[2];
        local_54 = uVar4;
        if (puVar11 == (undefined1 *)0x0) {
          uVar12 = local_88[1];
          local_e8 = CONCAT71(local_e8._1_7_,0x1fffffffffffffff < uVar12);
          if (0x1fffffffffffffff < uVar12) {
            return 0x1f;
          }
          if (uVar12 * 8 == 0) {
            puVar11 = (undefined1 *)0xfffffffffffffffc;
          }
          else {
            puVar11 = (undefined1 *)(*(code *)*puStack_90)(local_98,uVar12 * 8,2,unaff_retaddr);
            if (puVar11 == (undefined1 *)0x0) {
              return 0x1f;
            }
          }
          plVar6[2] = (long)puVar11;
        }
        else {
          uVar12 = local_88[1];
        }
        FUN_011f4580(puVar11,local_80,0x200);
        local_80 = puVar11;
        local_78 = uVar12;
        param_3 = extraout_RDX_01;
        param_2 = local_50;
        uVar21 = local_54;
      }
      *(undefined4 *)(local_80 + uVar10 * 8) = uVar5;
      *(undefined4 *)(local_80 + uVar10 * 8 + 4) = 0xc;
      break;
    case 2:
      uVar10 = (ulong)local_70;
      if (uVar10 == 0x40) {
        puVar11 = (undefined1 *)local_88[2];
        local_118 = lVar18;
        if (puVar11 == (undefined1 *)0x0) {
          uVar12 = local_88[1];
          local_e8 = CONCAT71(local_e8._1_7_,0x1fffffffffffffff < uVar12);
          if (0x1fffffffffffffff < uVar12) {
            return 0x1f;
          }
          if (uVar12 * 8 == 0) {
            puVar11 = (undefined1 *)0xfffffffffffffffc;
          }
          else {
            puVar11 = (undefined1 *)(*(code *)*puStack_90)(local_98,uVar12 * 8,2,unaff_retaddr);
            if (puVar11 == (undefined1 *)0x0) {
              return 0x1f;
            }
          }
          plVar6[2] = (long)puVar11;
        }
        else {
          uVar12 = local_88[1];
        }
        FUN_011f4580(puVar11,local_80,0x200);
        local_80 = puVar11;
        local_78 = uVar12;
        param_3 = extraout_RDX;
        lVar18 = local_118;
        param_2 = local_50;
      }
      *(int *)(local_80 + uVar10 * 8) = (int)lVar18;
      *(undefined4 *)(local_80 + uVar10 * 8 + 4) = 0xd;
      uVar21 = uVar4;
      break;
    case 3:
      local_54 = uVar4;
      lVar22 = *(long *)(lVar16 + uVar10 * 0x48);
      local_b8 = *(ulong *)(lVar16 + 0x18 + uVar10 * 0x48);
      local_a0 = CONCAT44(local_a0._4_4_,*(undefined4 *)(lVar16 + 0x20 + uVar10 * 0x48));
      uVar3 = *(undefined1 *)(lVar16 + 0x24 + uVar10 * 0x48);
      local_40 = 3;
      if (lVar18 == 0) {
        sVar9 = 0;
        lVar17 = 0;
        uVar10 = (ulong)*(uint *)((long)param_2 + 0x34);
        sVar8 = 0;
        if (uVar10 == 0xffffffff) goto LAB_011db7a4;
LAB_011db742:
        *(uint *)(*param_2 + 0x18 + uVar10 * 0x48) = uVar21;
      }
      else {
        lVar17 = 0;
        lVar20 = 0;
        local_b0 = lVar16;
        local_a8 = lVar19;
        local_58 = uVar21;
        do {
          sVar9 = FUN_011dbfd0(local_a0 & 0xffffffff,lVar22,(long)local_60 + lVar20,
                               local_b8 - lVar20,uVar3,1);
          uVar21 = local_54;
          if (sVar9 != 0) {
            if (sVar9 == 0xe) {
              if (lVar17 != 0) {
                sVar9 = 0;
                goto LAB_011db723;
              }
              auVar25 = FUN_011dc280(&local_98,local_a0 & 0xffffffff,9);
              param_3 = auVar25._8_8_;
              param_2 = local_50;
              if (auVar25._0_2_ != 0) {
                return auVar25._0_8_;
              }
              goto LAB_011db5e0;
            }
            if (sVar9 == 0x11) {
              return 0x11;
            }
            lVar17 = 0;
            goto LAB_011db723;
          }
          lVar20 = lVar20 + *(long *)(lVar22 + 8);
          lVar17 = lVar17 + 1;
          lVar22 = lVar22 + 0x48;
        } while (lVar18 != lVar17);
        sVar9 = 0;
        lVar17 = lVar18;
LAB_011db723:
        uVar10 = (ulong)*(uint *)((long)local_50 + 0x34);
        lVar16 = local_b0;
        lVar19 = local_a8;
        param_2 = local_50;
        uVar21 = local_58;
        sVar8 = sVar9;
        if (uVar10 != 0xffffffff) goto LAB_011db742;
LAB_011db7a4:
        sVar9 = sVar8;
        *(uint *)(param_2 + 6) = uVar21;
      }
      psVar1 = (short *)(lVar16 + lVar19 * 8);
      psVar1[0xc] = -1;
      psVar1[0xd] = -1;
      param_3 = (ulong *)(ulong)local_40;
      *psVar1 = sVar9;
      *(long *)(psVar1 + 4) = lVar17;
      *(byte *)(psVar1 + 8) = local_40;
      *(uint *)((long)param_2 + 0x34) = uVar21;
      uVar21 = local_54;
      goto LAB_011db5e0;
    }
    local_70 = uVar7 + 1;
LAB_011db5e0:
  } while (uVar21 != 0xffffffff);
  uVar10 = (ulong)local_70;
  if (uVar10 == 0) {
    return 0;
  }
  if (((local_70 == 1) && ((char)local_110[4] == '\0')) && ((int)param_2[6] == -1)) {
    uVar21 = *(uint *)(param_2 + 4);
    uVar10 = (ulong)uVar21;
    lVar18 = *param_2;
    puVar2 = (undefined8 *)(lVar18 + uVar10 * 0x48);
    local_198 = *puVar2;
    uStack_190 = puVar2[1];
    uStack_188 = puVar2[2];
    local_180 = puVar2[3];
    lVar16 = lVar18 + 0x18 + uVar10 * 0x48;
    uStack_178 = *(undefined8 *)(lVar16 + 8);
    uStack_170 = *(undefined8 *)(lVar16 + 0x10);
    uStack_168 = *(undefined8 *)(lVar16 + 0x18);
    FUN_011dc710(&local_138);
    if (local_120 == 0) {
      puVar2 = (undefined8 *)(lVar18 + uVar10 * 0x48);
      local_50[4] = -1;
      if ((ulong)*(uint *)((long)local_50 + 0x34) == 0xffffffff) {
        *(uint *)(local_50 + 6) = uVar21;
      }
      else {
        *(uint *)(*local_50 + 0x18 + (ulong)*(uint *)((long)local_50 + 0x34) * 0x48) = uVar21;
      }
      *(undefined4 *)(puVar2 + 3) = 0xffffffff;
      *puVar2 = local_138;
      puVar2[1] = uStack_130;
      puVar2[2] = local_128;
      *(uint *)((long)local_50 + 0x34) = uVar21;
      return 0;
    }
    return (ulong)local_120;
  }
  if ((local_41 & 3) == 0) {
    puVar13 = &DAT_0100f5e0;
    if (DAT_0100f600 == '\0') {
      lVar16 = *(long *)(in_FS_OFFSET + -0x40010);
      puVar11 = local_80;
      param_2 = local_50;
      if ((lVar16 != 0) && ((*(byte *)(lVar16 + 0x21c) & 1) == 0)) {
        uVar12 = *(ulong *)(lVar16 + 8);
        do {
          LOCK();
          uVar23 = *(ulong *)(lVar16 + 8);
          bVar24 = uVar12 == uVar23;
          if (bVar24) {
            *(ulong *)(lVar16 + 8) = uVar12 | 3;
            uVar23 = uVar12;
          }
          UNLOCK();
          uVar12 = uVar23;
        } while (!bVar24);
        if ((uVar23 & 7) == 0) {
          syscall();
          LOCK();
          *(ulong *)(lVar16 + 8) = *(ulong *)(lVar16 + 8) ^ 3;
          UNLOCK();
          goto LAB_011dbe46;
        }
        if (((uint)uVar23 & 7) != 7) {
          return 0x11;
        }
      }
      syscall();
      goto LAB_011dbe46;
    }
  }
  else {
    if ((local_41 & 3) == 1) {
      local_38 = local_31 & 7;
      if ((PTR_FUN_011fcf88 == (undefined *)0x0) ||
         ((uVar12 = (*(code *)PTR_FUN_011fcf88)
                              (*(undefined4 *)(&DAT_01001440 + (ulong)((local_31 ^ 4) & 7) * 4),
                               &local_e8), param_2 = local_50, uVar12 != 0 &&
          (uVar12 != 0xffffffffffffffea)))) {
        syscall();
        uVar12 = 0xe4;
      }
      uVar14 = 0;
      uVar23 = -uVar12;
      if (uVar12 < 0xfffffffffffff001) {
        uVar23 = uVar14;
      }
      lVar16 = 0;
      if (uVar23 == 0) {
        uVar14 = local_e8 * 1000000000 + local_e0;
        lVar16 = SUB168(SEXT816(1000000000) * SEXT816((long)local_e8),8) + ((long)local_e0 >> 0x3f)
                 + (ulong)CARRY8(local_e8 * 1000000000,local_e0);
      }
      param_3 = (ulong *)(lVar16 + local_f8 + (ulong)CARRY8(uVar14,local_f0));
      local_e8 = uVar14 + local_f0;
      local_e0 = CONCAT44(local_e0._4_4_,(int)param_3);
      local_d8 = local_38;
    }
    else {
      local_e8 = local_f0;
      local_e0 = local_f8;
      local_d8 = local_31;
      local_d7 = uStack_108;
      uStack_d0 = local_101;
      uStack_cf = uStack_100;
    }
    puVar13 = &local_e8;
    local_c8 = 1;
  }
  puVar11 = local_80;
  local_b8 = *puVar13;
  local_60 = (undefined1 *)puVar13[1];
  if ((int)param_2[6] == -1) {
    if ((PTR_FUN_011fcf88 == (undefined *)0x0) ||
       ((uVar12 = (*(code *)PTR_FUN_011fcf88)
                            (*(undefined4 *)
                              (&DAT_01001440 + ((ulong)((byte)puVar13[2] & 7) ^ 4) * 4),&local_e8,
                             param_3), uVar12 != 0 && (uVar12 != 0xffffffffffffffea)))) {
      uVar12 = 0xe4;
      syscall();
    }
    lVar16 = -uVar12;
    if (uVar12 < 0xfffffffffffff001) {
      lVar16 = 0;
    }
    uVar12 = 0;
    iVar15 = 0;
    if (lVar16 == 0) {
      uVar12 = local_e8 * 1000000000 + local_e0;
      iVar15 = SUB164(SEXT816(1000000000) * SEXT816((long)local_e8),8) +
               (int)((long)local_e0 >> 0x3f) + (uint)CARRY8(local_e8 * 1000000000,local_e0);
    }
    FUN_011f6850(local_b8 - uVar12,(long)(int)(((int)local_60 - iVar15) - (uint)(local_b8 < uVar12))
                 ,1000000,0);
    lVar16 = *(long *)(in_FS_OFFSET + -0x40010);
    param_2 = local_50;
  }
  else {
    lVar16 = *(long *)(in_FS_OFFSET + -0x40010);
  }
  if ((lVar16 != 0) && ((*(byte *)(lVar16 + 0x21c) & 1) == 0)) {
    uVar12 = *(ulong *)(lVar16 + 8);
    do {
      LOCK();
      uVar23 = *(ulong *)(lVar16 + 8);
      bVar24 = uVar12 == uVar23;
      if (bVar24) {
        *(ulong *)(lVar16 + 8) = uVar12 | 3;
        uVar23 = uVar12;
      }
      UNLOCK();
      uVar12 = uVar23;
    } while (!bVar24);
    if ((uVar23 & 7) == 0) {
      syscall();
      LOCK();
      *(ulong *)(lVar16 + 8) = *(ulong *)(lVar16 + 8) ^ 3;
      UNLOCK();
      goto LAB_011dbe46;
    }
    if (((uint)uVar23 & 7) != 7) {
      return 0x11;
    }
  }
  syscall();
LAB_011dbe46:
  if (uVar10 != 0) {
    uVar23 = 0xffffffff;
    uVar12 = 0;
    uVar21 = *(uint *)(param_2 + 4);
    local_a0 = uVar10;
    local_60 = puVar11;
    do {
      uVar10 = (ulong)uVar21;
      uVar4 = *(uint *)(*param_2 + 0x38 + uVar10 * 0x48);
      if (*(short *)(local_60 + uVar12 * 8 + 6) == 0) {
        uVar23 = (ulong)uVar21;
      }
      else {
        puVar2 = (undefined8 *)(*param_2 + uVar10 * 0x48);
        local_1d8 = *puVar2;
        uStack_1d0 = puVar2[1];
        uStack_1c8 = puVar2[2];
        uStack_1c0 = puVar2[3];
        uStack_1b8 = puVar2[4];
        uStack_1b0 = puVar2[5];
        uStack_1a8 = puVar2[6];
        FUN_011dc710(&local_158);
        if (local_140 != 0) {
          return (ulong)local_140;
        }
        if ((int)uVar23 == -1) {
          *(uint *)(local_50 + 4) = uVar4;
          if (uVar4 == 0xffffffff) goto LAB_011dbf3a;
LAB_011dbf06:
          uVar14 = (ulong)*(uint *)((long)local_50 + 0x34);
          if (uVar14 != 0xffffffff) goto LAB_011dbf14;
LAB_011dbf4c:
          *(uint *)(local_50 + 6) = uVar21;
        }
        else {
          *(uint *)(*local_50 + 0x38 + uVar23 * 0x48) = uVar4;
          if (uVar4 != 0xffffffff) goto LAB_011dbf06;
LAB_011dbf3a:
          *(int *)((long)local_50 + 0x24) = (int)uVar23;
          uVar14 = (ulong)*(uint *)((long)local_50 + 0x34);
          if (uVar14 == 0xffffffff) goto LAB_011dbf4c;
LAB_011dbf14:
          *(uint *)(*local_50 + 0x18 + uVar14 * 0x48) = uVar21;
        }
        *(uint *)((long)local_50 + 0x34) = uVar21;
        lVar16 = *local_50;
        *(undefined4 *)(lVar16 + 0x18 + uVar10 * 0x48) = 0xffffffff;
        puVar2 = (undefined8 *)(lVar16 + uVar10 * 0x48);
        *puVar2 = local_158;
        puVar2[1] = uStack_150;
        *(undefined8 *)(lVar16 + 0x10 + uVar10 * 0x48) = local_148;
        param_2 = local_50;
      }
      uVar12 = uVar12 + 1;
      uVar21 = uVar4;
    } while (local_a0 != uVar12);
  }
  return 0;
}


// ---- FUN_011dbfd0 @ 011dbfd0

/* WARNING: Removing unreachable block (ram,0x011dc10b) */

undefined8
FUN_011dbfd0(int param_1,undefined8 *param_2,undefined8 param_3,undefined8 param_4,byte param_5,
            ushort param_6)

{
  ulong uVar1;
  undefined8 uVar2;
  byte bVar3;
  ulong uVar4;
  short sVar5;
  long lVar6;
  long in_FS_OFFSET;
  bool bVar7;
  undefined8 local_98;
  undefined8 uStack_90;
  undefined8 local_80;
  undefined8 local_78;
  short *local_70;
  undefined4 local_68;
  undefined8 *local_60;
  undefined8 local_58;
  long local_50;
  undefined8 local_48;
  uint local_40;
  short local_38;
  undefined2 local_36;
  undefined4 local_34;
  undefined8 local_30;
  undefined8 uStack_28;
  undefined4 local_20;
  undefined1 local_1c;
  
  local_70 = &local_38;
  local_68 = 0x1c;
  local_60 = &local_80;
  local_58 = 1;
  local_50 = param_2[2];
  local_48 = param_2[3];
  lVar6 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar6 != 0) && ((*(byte *)(lVar6 + 0x21c) & 1) == 0)) {
    uVar4 = *(ulong *)(lVar6 + 8);
    do {
      LOCK();
      uVar1 = *(ulong *)(lVar6 + 8);
      bVar7 = uVar4 == uVar1;
      if (bVar7) {
        *(ulong *)(lVar6 + 8) = uVar4 | 3;
        uVar1 = uVar4;
      }
      UNLOCK();
      uVar4 = uVar1;
    } while (!bVar7);
    if ((uVar1 & 7) == 0) goto LAB_011dc059;
    if (((uint)uVar1 & 7) == 6) {
      return 0x11;
    }
  }
  lVar6 = 0;
LAB_011dc059:
  sVar5 = (param_6 & 1) * 0x40 + (ushort)(byte)((param_5 & 4) << 3 | param_5 & 3) + 0x4000;
  if (lVar6 == 0) {
    syscall();
                    /* WARNING: Could not find normalized switch variable to match jumptable */
    switch(switchD_011dc104::switchdataD_0100afe8) {
    case (undefined *)0x0:
      goto switchD_011dc104_caseD_0;
    default:
                    /* WARNING: This code block may not be properly labeled as switch case */
      return 4;
    case (undefined *)0xb:
                    /* WARNING: This code block may not be properly labeled as switch case */
      return 0xe;
    case (undefined *)0xc:
    case (undefined *)0x69:
                    /* WARNING: This code block may not be properly labeled as switch case */
      return 2;
    case (undefined *)0x17:
                    /* WARNING: This code block may not be properly labeled as switch case */
      return 0x25;
    case (undefined *)0x18:
                    /* WARNING: This code block may not be properly labeled as switch case */
      return 0x24;
    case (undefined *)0x20:
    case (undefined *)0x6b:
                    /* WARNING: This code block may not be properly labeled as switch case */
      return 0x23;
    case (undefined *)0x5a:
                    /* WARNING: This code block may not be properly labeled as switch case */
      return 0x26;
    case (undefined *)0x64:
                    /* WARNING: This code block may not be properly labeled as switch case */
      return 0x27;
    case (undefined *)0x68:
                    /* WARNING: This code block may not be properly labeled as switch case */
      return 0x21;
    }
  }
  syscall();
  local_80 = param_3;
  local_78 = param_4;
                    /* WARNING: Could not recover jumptable at 0x011dc0ac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar2 = (*(code *)PTR_LAB_0100ac88)((long)param_1,&local_70);
  return uVar2;
switchD_011dc104_caseD_0:
                    /* WARNING: This code block may not be properly labeled as switch case */
  if (local_38 == 10) {
    local_1c = 1;
    sVar5 = swap_bytes(local_36);
    uVar4 = CONCAT44(local_20,local_34);
    local_98 = local_30;
    uStack_90 = uStack_28;
  }
  else if (local_38 == 2) {
    local_1c = 0;
    sVar5 = swap_bytes(local_36);
    uVar4 = (ulong)CONCAT42(local_34,sVar5);
  }
  else {
    local_1c = 0;
    uVar4 = 0x100007f0000;
  }
  param_2[4] = uVar4;
  *(short *)(param_2 + 5) = sVar5;
  *(undefined8 *)((long)param_2 + 0x2a) = local_98;
  *(undefined8 *)((long)param_2 + 0x32) = uStack_90;
  *(undefined1 *)((long)param_2 + 0x3c) = local_1c;
  *param_2 = param_3;
  param_2[1] = 0x2f;
  if (local_50 == 0) {
    local_50 = param_2[2];
    local_48 = param_2[3];
  }
  param_2[2] = local_50;
  param_2[3] = local_48;
  bVar3 = (byte)local_40;
  *(byte *)(param_2 + 8) =
       (byte)(local_40 >> 9) & 0x10 |
       bVar3 * '\b' & 8 | bVar3 >> 1 & 4 | bVar3 >> 4 & 2 | bVar3 >> 7;
  return 0;
}


// ---- FUN_011dc280 @ 011dc280

undefined8 FUN_011dc280(undefined8 *param_1,undefined4 param_2,undefined2 param_3)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  undefined8 unaff_retaddr;
  
  uVar1 = *(uint *)(param_1 + 5);
  uVar4 = (ulong)uVar1;
  if (uVar4 == 0x40) {
    lVar3 = param_1[2];
    lVar2 = *(long *)(lVar3 + 0x10);
    if (lVar2 == 0) {
      uVar5 = *(ulong *)(lVar3 + 8);
      if (uVar5 >> 0x3d != 0) {
LAB_011dc320:
        return CONCAT62((int6)((ulong)lVar3 >> 0x10),0x1f);
      }
      if (uVar5 * 8 == 0) {
        lVar2 = -4;
      }
      else {
        lVar2 = (**(code **)param_1[1])(*param_1,uVar5 * 8,2,unaff_retaddr);
        lVar3 = 0;
        if (lVar2 == 0) goto LAB_011dc320;
        lVar3 = param_1[2];
      }
      *(long *)(lVar3 + 0x10) = lVar2;
    }
    else {
      uVar5 = *(ulong *)(lVar3 + 8);
    }
    FUN_011f4580(lVar2,param_1[3],0x200);
    param_1[3] = lVar2;
    param_1[4] = uVar5;
  }
  else {
    lVar2 = param_1[3];
  }
  *(undefined4 *)(lVar2 + uVar4 * 8) = param_2;
  *(undefined2 *)(lVar2 + 4 + uVar4 * 8) = param_3;
  *(undefined2 *)(lVar2 + 6 + uVar4 * 8) = 0;
  *(uint *)(param_1 + 5) = uVar1 + 1;
  return 0;
}


// ---- FUN_011dc370 @ 011dc370

/* WARNING: Removing unreachable block (ram,0x011dc4f8) */
/* WARNING: Removing unreachable block (ram,0x011dc503) */
/* WARNING: Removing unreachable block (ram,0x011dc508) */
/* WARNING: Removing unreachable block (ram,0x011dc516) */
/* WARNING: Type propagation algorithm not settling */

short FUN_011dc370(undefined8 param_1,long *param_2)

{
  long lVar1;
  undefined8 *puVar2;
  uint uVar3;
  ulong uVar4;
  uint uVar5;
  ulong uVar6;
  short sVar7;
  undefined4 uVar8;
  long lVar9;
  ulong uVar10;
  uint uVar11;
  long in_FS_OFFSET;
  bool bVar12;
  undefined4 local_2f8;
  short asStack_2f4 [5];
  short local_2ea [249];
  undefined8 local_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 local_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 local_80;
  undefined8 uStack_78;
  undefined8 local_70;
  short local_68;
  undefined8 local_60;
  undefined8 uStack_58;
  undefined8 local_50;
  short local_48;
  ulong local_40;
  long *local_38;
  
  uVar11 = *(uint *)(param_2 + 4);
  if (uVar11 == 0xffffffff) {
    return 0;
  }
  lVar9 = *param_2;
  uVar6 = 0;
  uVar5 = uVar11;
  do {
    uVar10 = uVar6;
    lVar1 = lVar9 + (ulong)uVar5 * 0x48;
    switch(*(byte *)(lVar9 + 0x30 + (ulong)uVar5 * 0x48) & 3) {
    case 0:
      uVar8 = *(undefined4 *)(lVar1 + 0x10);
      goto LAB_011dc3d3;
    case 1:
      (&local_2f8)[uVar10 * 2] = *(undefined4 *)(lVar1 + 0x28);
      sVar7 = 0xc;
      break;
    case 2:
      (&local_2f8)[uVar10 * 2] = *(undefined4 *)(lVar1 + 8);
      sVar7 = 0xd;
      break;
    case 3:
      uVar8 = *(undefined4 *)(lVar1 + 0x20);
LAB_011dc3d3:
      (&local_2f8)[uVar10 * 2] = uVar8;
      sVar7 = 9;
    }
    asStack_2f4[uVar10 * 4] = sVar7;
    asStack_2f4[uVar10 * 4 + 1] = 0;
    uVar5 = *(uint *)(lVar1 + 0x38);
  } while ((uVar5 != 0xffffffff) && (uVar6 = uVar10 + 1, uVar10 < 0x3f));
  local_38 = param_2;
  if (uVar10 + 1 == 1) {
    uVar5 = *(uint *)((long)param_2 + 0x34);
    while( true ) {
      uVar3 = uVar11;
      if (uVar3 == 0xffffffff) {
        local_38[4] = -1;
        *(uint *)((long)local_38 + 0x34) = uVar5;
        return 0;
      }
      uVar6 = (ulong)uVar3;
      lVar1 = *local_38;
      uVar11 = *(uint *)(lVar1 + 0x38 + uVar6 * 0x48);
      puVar2 = (undefined8 *)(lVar1 + uVar6 * 0x48);
      local_f8 = *puVar2;
      uStack_f0 = puVar2[1];
      uStack_e8 = puVar2[2];
      uStack_e0 = puVar2[3];
      lVar9 = lVar1 + 0x18 + uVar6 * 0x48;
      uStack_d8 = *(undefined8 *)(lVar9 + 8);
      uStack_d0 = *(undefined8 *)(lVar9 + 0x10);
      uStack_c8 = *(undefined8 *)(lVar9 + 0x18);
      FUN_011dc710(&local_80);
      if (local_68 != 0) break;
      if (uVar5 == 0xffffffff) {
        *(uint *)(local_38 + 6) = uVar3;
      }
      else {
        *(uint *)(*local_38 + 0x18 + (ulong)uVar5 * 0x48) = uVar3;
      }
      puVar2 = (undefined8 *)(lVar1 + uVar6 * 0x48);
      *(undefined4 *)(puVar2 + 3) = 0xffffffff;
      *puVar2 = local_80;
      puVar2[1] = uStack_78;
      puVar2[2] = local_70;
      local_68 = 0;
      uVar5 = uVar3;
    }
    *(uint *)(local_38 + 4) = uVar3;
    *(uint *)((long)local_38 + 0x34) = uVar5;
    return local_68;
  }
  local_40 = uVar10;
  lVar9 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar9 != 0) && ((*(byte *)(lVar9 + 0x21c) & 1) == 0)) {
    uVar6 = *(ulong *)(lVar9 + 8);
    do {
      LOCK();
      uVar10 = *(ulong *)(lVar9 + 8);
      bVar12 = uVar6 == uVar10;
      if (bVar12) {
        *(ulong *)(lVar9 + 8) = uVar6 | 3;
        uVar10 = uVar6;
      }
      UNLOCK();
      uVar6 = uVar10;
    } while (!bVar12);
    if ((uVar10 & 7) == 0) goto LAB_011dc4b3;
    if (((uint)uVar10 & 7) != 7) {
      return 0x11;
    }
  }
  lVar9 = 0;
LAB_011dc4b3:
  syscall();
  if (lVar9 != 0) {
    LOCK();
    *(ulong *)(lVar9 + 8) = *(ulong *)(lVar9 + 8) ^ 3;
    UNLOCK();
  }
  uVar6 = 0xffffffff;
  uVar10 = 0xffffffffffffffff;
  uVar11 = *(uint *)(param_2 + 4);
  do {
    while( true ) {
      uVar5 = *(uint *)(*param_2 + 0x38 + (ulong)uVar11 * 0x48);
      if (local_2ea[uVar10 * 4] != 0) break;
      uVar6 = (ulong)uVar11;
      uVar10 = uVar10 + 1;
      uVar11 = uVar5;
      if (local_40 == uVar10) {
        return 0;
      }
    }
    puVar2 = (undefined8 *)(*param_2 + (ulong)uVar11 * 0x48);
    local_b8 = *puVar2;
    uStack_b0 = puVar2[1];
    uStack_a8 = puVar2[2];
    uStack_a0 = puVar2[3];
    uStack_98 = puVar2[4];
    uStack_90 = puVar2[5];
    uStack_88 = puVar2[6];
    FUN_011dc710(&local_60);
    if (local_48 != 0) {
      return local_48;
    }
    if ((int)uVar6 == -1) {
      *(uint *)(local_38 + 4) = uVar5;
      if (uVar5 != 0xffffffff) goto LAB_011dc66a;
LAB_011dc69e:
      *(int *)((long)local_38 + 0x24) = (int)uVar6;
      uVar4 = (ulong)*(uint *)((long)local_38 + 0x34);
      if (uVar4 != 0xffffffff) goto LAB_011dc678;
LAB_011dc6b0:
      *(uint *)(local_38 + 6) = uVar11;
    }
    else {
      *(uint *)(*local_38 + 0x38 + uVar6 * 0x48) = uVar5;
      if (uVar5 == 0xffffffff) goto LAB_011dc69e;
LAB_011dc66a:
      uVar4 = (ulong)*(uint *)((long)local_38 + 0x34);
      if (uVar4 == 0xffffffff) goto LAB_011dc6b0;
LAB_011dc678:
      *(uint *)(*local_38 + 0x18 + uVar4 * 0x48) = uVar11;
    }
    *(undefined4 *)(puVar2 + 3) = 0xffffffff;
    *puVar2 = local_60;
    puVar2[1] = uStack_58;
    puVar2[2] = local_50;
    *(uint *)((long)local_38 + 0x34) = uVar11;
    uVar10 = uVar10 + 1;
    param_2 = local_38;
    uVar11 = uVar5;
    if (local_40 == uVar10) {
      return 0;
    }
  } while( true );
}


// ---- FUN_011dc710 @ 011dc710

/* WARNING: Removing unreachable block (ram,0x011dc821) */
/* WARNING: Removing unreachable block (ram,0x011dc830) */
/* WARNING: Removing unreachable block (ram,0x011dc837) */
/* WARNING: Removing unreachable block (ram,0x011dc83f) */
/* WARNING: Removing unreachable block (ram,0x011dca07) */
/* WARNING: Removing unreachable block (ram,0x011dca6e) */
/* WARNING: Removing unreachable block (ram,0x011dca74) */
/* WARNING: Removing unreachable block (ram,0x011dca1f) */
/* WARNING: Removing unreachable block (ram,0x011dca25) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * FUN_011dc710(long *param_1,undefined8 param_2,long *param_3)

{
  long lVar1;
  long lVar2;
  long lVar3;
  short sVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  long *plVar8;
  long lVar9;
  long in_FS_OFFSET;
  bool bVar10;
  long local_e0 [17];
  short local_58;
  long local_40;
  undefined2 uStack_38;
  long local_30;
  short local_28;
  long local_20;
  undefined2 local_18;
  
  lVar9 = *param_3;
  lVar7 = param_3[1];
  lVar1 = param_3[2];
  lVar2 = param_3[3];
  uVar5 = param_3[4];
  switch(*(byte *)(param_3 + 6) & 3) {
  case 0:
    *(short *)(param_1 + 3) = 0;
    *(undefined1 *)(param_1 + 2) = 0;
    if (lVar7 != 0) {
      plVar8 = (long *)(lVar9 + 8);
      lVar9 = 0;
      do {
        if (lVar9 == 8) {
          lVar9 = 8;
          goto LAB_011dc92d;
        }
        lVar2 = *plVar8;
        if (lVar2 != 0) {
          local_e0[lVar9 * 2] = plVar8[-1];
          local_e0[lVar9 * 2 + 1] = lVar2;
          lVar9 = lVar9 + 1;
        }
        plVar8 = plVar8 + 2;
        lVar7 = lVar7 + -1;
      } while (lVar7 != 0);
      if (lVar9 != 0) {
LAB_011dc92d:
        lVar7 = *(long *)(in_FS_OFFSET + -0x40010);
        if ((lVar7 != 0) && ((*(byte *)(lVar7 + 0x21c) & 1) == 0)) {
          uVar5 = *(ulong *)(lVar7 + 8);
          do {
            LOCK();
            uVar6 = *(ulong *)(lVar7 + 8);
            bVar10 = uVar5 == uVar6;
            if (bVar10) {
              *(ulong *)(lVar7 + 8) = uVar5 | 3;
              uVar6 = uVar5;
            }
            UNLOCK();
            uVar5 = uVar6;
          } while (!bVar10);
          if ((uVar6 & 7) == 0) goto LAB_011dc96e;
          if (((uint)uVar6 & 7) == 6) goto LAB_011dc9c7;
        }
        lVar7 = 0;
LAB_011dc96e:
        if (lVar7 != 0) {
          syscall();
                    /* WARNING: Could not recover jumptable at 0x011dc9a0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
          plVar8 = (long *)(*(code *)PTR_LAB_0100b388)((long)(int)lVar1,local_e0,lVar9);
          return plVar8;
        }
        syscall();
                    /* WARNING: Could not recover jumptable at 0x011dca00. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        plVar8 = (long *)(*(code *)PTR_LAB_0100b700)((long)(int)lVar1,local_e0,lVar9);
        return plVar8;
      }
    }
    local_18 = 0;
    local_20 = 0;
    plVar8 = &local_20;
    break;
  case 1:
    lVar3 = param_3[5];
    *(short *)(param_1 + 3) = 0;
    *(undefined1 *)(param_1 + 2) = 1;
    FUN_011d5760(&local_30,(int)lVar3,lVar9,lVar7,lVar1,lVar2,uVar5);
    if (local_28 == 0) {
      uStack_38 = 0;
      local_40 = local_30;
      plVar8 = &local_40;
    }
    else {
      if (local_28 == 0x11) goto LAB_011dc9c7;
      local_58 = local_28;
      plVar8 = local_e0 + 0x10;
    }
    break;
  case 2:
    *(short *)(param_1 + 3) = 0;
    *(undefined1 *)(param_1 + 2) = 2;
    lVar9 = *(long *)(in_FS_OFFSET + -0x40010);
    if ((lVar9 != 0) && ((*(byte *)(lVar9 + 0x21c) & 1) == 0)) {
      uVar5 = *(ulong *)(lVar9 + 8);
      do {
        LOCK();
        uVar6 = *(ulong *)(lVar9 + 8);
        bVar10 = uVar5 == uVar6;
        if (bVar10) {
          *(ulong *)(lVar9 + 8) = uVar5 | 3;
          uVar6 = uVar5;
        }
        UNLOCK();
        uVar5 = uVar6;
      } while (!bVar10);
      if ((uVar6 & 7) == 0) goto LAB_011dc7ee;
      if (((uint)uVar6 & 7) == 6) {
        *(short *)(param_1 + 3) = 0x11;
        return param_1;
      }
    }
    lVar9 = 0;
LAB_011dc7ee:
    if (lVar9 != 0) {
      syscall();
      LOCK();
      *(ulong *)(lVar9 + 8) = *(ulong *)(lVar9 + 8) ^ 3;
      UNLOCK();
      *(undefined4 *)param_1 = 0x10;
      return param_1;
    }
    syscall();
    *(undefined4 *)param_1 = 0x10;
    return param_1;
  case 3:
    *(short *)(param_1 + 3) = 0;
    *(undefined1 *)(param_1 + 2) = 3;
    sVar4 = FUN_011dbfd0(uVar5,lVar9,lVar1,lVar2,uVar5 >> 0x20,0);
    if (sVar4 == 0) {
      *(short *)param_1 = 0;
      param_1[1] = 1;
      return param_1;
    }
    if (sVar4 != 0x11) {
      *(short *)param_1 = sVar4;
      param_1[1] = 0;
      return param_1;
    }
LAB_011dc9c7:
    lVar1 = _UNK_01001278;
    lVar7 = _UNK_01001270;
    lVar9 = _UNK_01001268;
    *param_1 = _DAT_01001260;
    param_1[1] = lVar9;
    param_1[2] = lVar7;
    param_1[3] = lVar1;
    return param_1;
  }
  lVar9 = plVar8[1];
  *param_1 = *plVar8;
  param_1[1] = lVar9;
  return param_1;
}


// ---- FUN_011dcac0 @ 011dcac0

undefined1  [16] FUN_011dcac0(undefined8 param_1,undefined8 param_2,uint param_3)

{
  undefined1 auVar1 [16];
  
  if (0x7ffffffe < param_3) {
    param_3 = 0x7fffffff;
  }
  auVar1._12_4_ = 0;
  auVar1._8_4_ = param_3;
  syscall();
  auVar1._0_8_ = 0xca;
  return auVar1;
}


// ---- FUN_011dcaf0 @ 011dcaf0

undefined1  [16] FUN_011dcaf0(undefined8 param_1,undefined8 param_2,undefined4 param_3)

{
  undefined1 auVar1 [16];
  
  syscall();
  auVar1._8_4_ = param_3;
  auVar1._0_8_ = 0xca;
  auVar1._12_4_ = 0;
  return auVar1;
}


// ---- FUN_011dcb10 @ 011dcb10

void FUN_011dcb10(undefined8 param_1,undefined8 param_2,undefined4 param_3,ulong *param_4)

{
  byte bVar1;
  ulong uVar2;
  ulong *puVar3;
  ulong uVar4;
  ulong uVar5;
  long lVar6;
  int iVar7;
  ulong *puVar8;
  ulong uVar9;
  ulong uVar10;
  ulong local_88;
  undefined1 local_80;
  ulong local_78;
  undefined8 local_70;
  byte local_68;
  undefined7 local_67;
  undefined1 uStack_60;
  undefined7 uStack_5f;
  undefined1 local_58;
  undefined4 local_3c;
  byte local_38;
  
  if ((param_4[4] & 3) == 0) {
    puVar3 = &DAT_0100f610;
    puVar8 = (ulong *)&DAT_01000740;
    if (DAT_0100f630 == '\0') goto LAB_011dcc77;
  }
  else {
    uVar2 = *param_4;
    uVar10 = param_4[1];
    bVar1 = (byte)param_4[2];
    if ((param_4[4] & 3) == 1) {
      local_78 = uVar2;
      local_70 = uVar10;
      local_68 = bVar1;
      local_67 = (undefined7)*(undefined8 *)((long)param_4 + 0x11);
      uStack_60 = (undefined1)param_4[3];
      uStack_5f = (undefined7)(param_4[3] >> 8);
    }
    else {
      if ((PTR_FUN_011fcf88 == (undefined *)0x0) ||
         ((local_3c = param_3,
          uVar4 = (*(code *)PTR_FUN_011fcf88)
                            (*(undefined4 *)(&DAT_01001440 + (ulong)((bVar1 ^ 4) & 7) * 4),&local_78
                            ), param_3 = local_3c, uVar4 != 0 && (uVar4 != 0xffffffffffffffea)))) {
        syscall();
        uVar4 = 0xe4;
      }
      uVar5 = 0;
      uVar9 = -uVar4;
      if (uVar4 < 0xfffffffffffff001) {
        uVar9 = uVar5;
      }
      iVar7 = 0;
      if (uVar9 == 0) {
        uVar5 = local_78 * 1000000000 + local_70;
        iVar7 = SUB164(SEXT816(1000000000) * SEXT816((long)local_78),8) + (local_70._4_4_ >> 0x1f) +
                (uint)CARRY8(local_78 * 1000000000,local_70);
      }
      local_38 = bVar1 & 7;
      local_78 = uVar2 - uVar5;
      local_70 = CONCAT44(local_70._4_4_,((int)uVar10 - iVar7) - (uint)(uVar2 < uVar5));
      local_68 = bVar1 & 7;
    }
    puVar3 = &local_78;
    local_58 = 1;
  }
  uVar2 = *puVar3;
  lVar6 = (long)(int)puVar3[1];
  uVar10 = uVar2;
  if (lVar6 < (long)(ulong)(uVar2 == 0)) {
    uVar10 = 0;
  }
  local_88 = 0xffffffffffffffff;
  if ((SBORROW8(0,lVar6) != SBORROW8(-lVar6,(ulong)(0xfffffffffffffffe < uVar2))) ==
      (long)(-lVar6 - (ulong)(0xfffffffffffffffe < uVar2)) < 0) {
    local_88 = uVar10;
  }
  local_80 = 1;
  puVar8 = &local_88;
LAB_011dcc77:
  FUN_011f3fb0(param_2,param_3,0,puVar8);
  return;
}


// ---- FUN_011dcca0 @ 011dcca0

undefined8 FUN_011dcca0(void)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + -0x40010);
  if (lVar1 == 0) {
    return 0;
  }
  if (((*(byte *)(lVar1 + 0x21c) & 1) == 0) && (((uint)*(ulong *)(lVar1 + 8) & 7) == 6)) {
    *(ulong *)(lVar1 + 8) = *(ulong *)(lVar1 + 8) | 7;
    return CONCAT62((int6)((ulong)lVar1 >> 0x10),0x11);
  }
  return 0;
}


// ---- FUN_011dcce0 @ 011dcce0

undefined1 FUN_011dcce0(undefined8 param_1,byte param_2)

{
  undefined1 uVar1;
  long lVar2;
  long in_FS_OFFSET;
  
  lVar2 = *(long *)(in_FS_OFFSET + -0x40010);
  if (lVar2 != 0) {
    uVar1 = *(undefined1 *)(lVar2 + 0x21c);
    *(byte *)(lVar2 + 0x21c) = param_2 & 1;
    return uVar1;
  }
  return 0;
}


// ---- FUN_011dcd10 @ 011dcd10

void FUN_011dcd10(void)

{
  ulong *puVar1;
  long in_FS_OFFSET;
  
  LOCK();
  puVar1 = (ulong *)(*(long *)(in_FS_OFFSET + -0x40010) + 8);
  *puVar1 = *puVar1 ^ 1;
  UNLOCK();
  return;
}


// ---- FUN_011dcd30 @ 011dcd30

void FUN_011dcd30(undefined8 param_1,ulong *param_2)

{
  ulong uVar1;
  ulong uVar2;
  bool bVar3;
  undefined4 local_1c;
  
  local_1c = 0;
  param_2[1] = (ulong)&local_1c;
  uVar2 = *param_2;
  do {
    LOCK();
    uVar1 = *param_2;
    bVar3 = uVar2 == uVar1;
    if (bVar3) {
      *param_2 = uVar2 | 0xc000000000000000;
      uVar1 = uVar2;
    }
    UNLOCK();
    uVar2 = uVar1;
  } while (!bVar3);
  if (uVar1 == 0) {
    uVar2 = *param_2 & 0x3fffffffffffffff;
  }
  else {
    uVar2 = 0;
    FUN_011dce90(param_2,param_1,&local_1c,0);
  }
  *param_2 = uVar2;
  return;
}


// ---- FUN_011dcda0 @ 011dcda0

undefined8 FUN_011dcda0(undefined8 param_1,ulong *param_2)

{
  short sVar1;
  uint in_EAX;
  ulong uVar2;
  ulong uVar3;
  undefined8 uVar4;
  ulong uVar5;
  bool bVar6;
  undefined8 uStack_38;
  
  uStack_38 = (ulong)in_EAX;
  uVar5 = 0x3fffffffffffffff;
  param_2[1] = (long)&uStack_38 + 4;
  uVar2 = *param_2;
  do {
    LOCK();
    uVar3 = *param_2;
    bVar6 = uVar2 == uVar3;
    if (bVar6) {
      *param_2 = uVar2 | 0x4000000000000000;
      uVar3 = uVar2;
    }
    UNLOCK();
    uVar2 = uVar3;
  } while (!bVar6);
  if (uVar3 != 0) {
    do {
      sVar1 = FUN_011f3fb0((long)&uStack_38 + 4,0,0,&DAT_01000740);
      if (sVar1 != 0) {
        uVar2 = *param_2;
        do {
          LOCK();
          uVar3 = *param_2;
          bVar6 = uVar2 == uVar3;
          if (bVar6) {
            *param_2 = uVar2 | 0x8000000000000000;
            uVar3 = uVar2;
          }
          UNLOCK();
          uVar2 = uVar3;
        } while (!bVar6);
        FUN_011dce90(param_2,param_1,(long)&uStack_38 + 4,(uVar3 & 0x3fffffffffffffff) == 0);
        uVar4 = 0x11;
        goto LAB_011dce22;
      }
    } while (uStack_38._4_4_ == 0);
  }
  uVar4 = 0;
  uVar5 = 0xbfffffffffffffff;
LAB_011dce22:
  *param_2 = *param_2 & uVar5;
  return uVar4;
}


// ---- FUN_011dce90 @ 011dce90

/* WARNING: Removing unreachable block (ram,0x011dcfa6) */

undefined1  [16] FUN_011dce90(long *param_1,long param_2,uint *param_3,ulong param_4)

{
  char cVar1;
  int iVar2;
  undefined8 *puVar3;
  int iVar4;
  uint uVar5;
  long *plVar6;
  ulong uVar7;
  long **pplVar8;
  ulong uVar9;
  long *plVar10;
  ulong extraout_RDX;
  ulong extraout_RDX_00;
  long lVar11;
  ulong extraout_RDX_01;
  undefined8 unaff_RBX;
  long *plVar12;
  undefined6 uVar13;
  byte bVar14;
  ulong uVar15;
  ulong unaff_R13;
  long *plVar16;
  long lVar17;
  bool bVar18;
  undefined1 auVar19 [16];
  long lStack_b0;
  short sStack_a8;
  long *plStack_a0;
  long *plStack_98;
  long lStack_90;
  long *plStack_88;
  long lStack_80;
  undefined8 uStack_78;
  undefined8 *puStack_70;
  byte bStack_64;
  long *local_60;
  ulong local_58;
  long *local_50;
  long local_48;
  long *local_40;
  undefined1 *local_38;
  
  if (((param_4 & 1) != 0) || (plVar12 = *(long **)(param_2 + 0x288), plVar12 == (long *)0x0)) {
    lVar11 = 0;
LAB_011dcef7:
    uVar15 = 0x400;
    if (lVar11 != 0) {
      uVar15 = 0x400;
      for (puVar3 = *(undefined8 **)(param_2 + 0x288); puVar3 != (undefined8 *)0x0;
          puVar3 = (undefined8 *)*puVar3) {
        if (((uint)puVar3[1] & 7) == 5 && (puVar3[1] ^ (ulong)param_1) < 8) {
          if (*(int *)(param_2 + 0x344) == 0) {
            syscall();
            *(undefined4 *)(param_2 + 0x344) = 0x27;
          }
          syscall();
        }
      }
    }
    while( true ) {
      syscall();
      if (*param_3 != 0) break;
      bVar18 = uVar15 != (uVar15 & 0x7fffffffffffffff);
      uVar15 = uVar15 * 2;
      if (bVar18) {
        uVar15 = 0xffffffffffffffff;
      }
    }
    return ZEXT416(*param_3);
  }
  local_50 = (long *)((ulong)param_1 | 2);
  plVar10 = (long *)((ulong)param_1 | 3);
  plVar16 = (long *)((ulong)param_1 | 5);
  plStack_88 = (long *)((ulong)param_1 | 1);
  uVar15 = (ulong)param_1 | 6;
  lVar11 = 0;
LAB_011dd03c:
  plVar6 = (long *)plVar12[1];
LAB_011dd06c:
  uVar9 = (ulong)plVar6 >> 3;
  if ((ulong)param_1 >> 3 != uVar9) goto switchD_011dd07b_caseD_6;
  switch((uint)plVar6 & 7) {
  case 0:
    LOCK();
    plVar6 = (long *)plVar12[1];
    bVar18 = param_1 == plVar6;
    if (bVar18) {
      plVar12[1] = uVar15;
      plVar6 = param_1;
    }
    UNLOCK();
    if (bVar18) goto switchD_011dd07b_caseD_6;
    goto LAB_011dd06c;
  case 1:
    LOCK();
    plVar6 = (long *)plVar12[1];
    bVar18 = plStack_88 == plVar6;
    if (bVar18) {
      plVar12[1] = uVar15;
      plVar6 = plStack_88;
    }
    UNLOCK();
    pplVar8 = &local_40;
    break;
  case 2:
    LOCK();
    plVar6 = (long *)plVar12[1];
    bVar18 = local_50 == plVar6;
    if (bVar18) {
      plVar12[1] = (ulong)param_1 | 4;
      plVar6 = local_50;
    }
    UNLOCK();
    pplVar8 = &local_60;
    break;
  case 3:
    goto switchD_011dd07b_caseD_3;
  default:
    lStack_80 = plVar12[0x65];
    puVar3 = (undefined8 *)plVar12[0x66];
    bVar14 = (byte)param_3 & 0x3f;
    uVar7 = 1L << ((ulong)param_3 & 0x3f);
    lVar17 = 0;
    if (7 < uVar7) {
      lVar17 = uVar7 - 8;
    }
    uVar7 = -1L << ((ulong)param_3 & 0x3f);
    lVar17 = ((lVar17 - uVar7) + 0x2f & uVar7) + uVar9;
    uStack_78 = unaff_RBX;
    bStack_64 = bVar14;
    local_60 = param_1;
    local_58 = uVar15;
    local_50 = (long *)unaff_R13;
    local_48 = lVar11;
    local_40 = plVar16;
    if (lVar17 == 0) {
      plVar16 = (long *)0xfffffffffffffff8;
      local_38 = &stack0xfffffffffffffff8;
    }
    else {
      plStack_a0 = plVar12;
      plStack_98 = plVar10;
      lStack_90 = param_2;
      local_38 = &stack0xfffffffffffffff8;
      auVar19 = (*(code *)*puVar3)(lStack_80,lVar17,3);
      uVar15 = auVar19._8_8_;
      plVar16 = auVar19._0_8_;
      plVar12 = plStack_a0;
      param_2 = lStack_90;
      plVar10 = plStack_98;
      if (plVar16 == (long *)0x0) {
        uVar9 = CONCAT62((int6)((ulong)plStack_a0 >> 0x10),0x1f);
        goto LAB_011dd3d1;
      }
    }
    plVar16[1] = (long)FUN_011ddfa0;
    plVar16[2] = (long)plStack_88;
    plVar16[3] = param_2;
    *(byte *)(plVar16 + 5) = bVar14;
    plVar16[4] = lVar17;
    uVar15 = -1L << ((ulong)param_3 & 0x3f);
    puStack_70 = puVar3;
    FUN_011f4580(~((uVar15 - (long)plVar16) - 0x30) & uVar15,plVar10,uVar9);
    LOCK();
    iVar4 = (int)plVar12[0x67];
    bVar18 = iVar4 == 0;
    if (bVar18) {
      *(int *)(plVar12 + 0x67) = 1;
      iVar4 = 0;
    }
    UNLOCK();
    bStack_64 = !bVar18;
    plVar10 = plVar12 + 0x67;
    uVar9 = (ulong)!bVar18;
    uVar15 = extraout_RDX;
    if (!bVar18) {
      if (iVar4 == 2) {
        uVar15 = 2;
        uVar9 = 0x11dd3fe;
        syscall();
      }
      LOCK();
      lVar11 = *plVar10;
      *(int *)plVar10 = 2;
      UNLOCK();
      if ((int)lVar11 != 0) {
        uVar15 = 2;
        do {
          uVar9 = 0x11dd425;
          syscall();
          LOCK();
          lVar11 = *plVar10;
          *(int *)plVar10 = 2;
          UNLOCK();
        } while ((int)lVar11 != 0);
      }
    }
    uVar7 = plVar12[0x50];
    uVar13 = (undefined6)((ulong)plVar12 >> 0x10);
    if (uVar7 < (ulong)plVar12[0x4f]) {
      plVar12[0x50] = uVar7 + 1;
      if ((ulong)plVar12[0x4c] >> 1 == uVar7) {
        LOCK();
        plVar12[0x4c] = plVar12[0x4c] + 2;
        UNLOCK();
        FUN_011dd860(&lStack_b0,plVar12[0x4b],plVar12,uVar9);
        if (sStack_a8 != 0) {
          LOCK();
          plVar10 = plVar12 + 0x4c;
          lVar11 = *plVar10;
          *plVar10 = *plVar10 + -2;
          UNLOCK();
          if (lVar11 == 3) {
            LOCK();
            lVar11 = plVar12[0x4d];
            *(int *)(plVar12 + 0x4d) = 2;
            UNLOCK();
            if ((int)lVar11 == 1) {
              syscall();
            }
          }
          plVar12[0x50] = uVar7;
          LOCK();
          lVar11 = plVar12[0x67];
          *(int *)(plVar12 + 0x67) = 0;
          UNLOCK();
          if ((int)lVar11 != 2) goto LAB_011dd2ed;
          syscall();
          lVar11 = plVar16[4];
          uVar9 = CONCAT62(uVar13,0x1f);
          if (lVar11 == 0) {
            uVar15 = 0;
            goto LAB_011dd3d1;
          }
          goto LAB_011dd2ff;
        }
        LOCK();
        cVar1 = *(char *)(lStack_b0 + 0x18);
        *(char *)(lStack_b0 + 0x18) = '\x01';
        UNLOCK();
        uVar15 = extraout_RDX_00;
        if (cVar1 != '\0') {
          uVar5 = *(uint *)(lStack_b0 + 0x10);
          if (uVar5 != 0) {
            do {
              uVar15 = (ulong)uVar5;
              syscall();
              uVar5 = *(uint *)(lStack_b0 + 0x10);
            } while (uVar5 != 0);
          }
          syscall();
        }
      }
      LOCK();
      *plStack_88 = *plStack_88 + 1;
      UNLOCK();
      *plVar16 = plVar12[9];
      plVar12[9] = (long)plVar16;
      iVar4 = *(int *)((long)plVar12 + 0x33c);
      do {
        if ((ushort)iVar4 <= (ushort)((uint)iVar4 >> 0x10)) goto LAB_011dd3c1;
        LOCK();
        iVar2 = *(int *)((long)plVar12 + 0x33c);
        bVar18 = iVar4 == iVar2;
        if (bVar18) {
          *(int *)((long)plVar12 + 0x33c) = iVar4 + 0x10000;
          iVar2 = iVar4;
        }
        iVar4 = iVar2;
        UNLOCK();
      } while (!bVar18);
      LOCK();
      *(int *)(plVar12 + 0x68) = (int)plVar12[0x68] + 1;
      UNLOCK();
      uVar15 = 1;
      syscall();
LAB_011dd3c1:
      LOCK();
      lVar11 = *plVar10;
      *(int *)plVar10 = 0;
      UNLOCK();
      uVar9 = 0;
      if ((int)lVar11 == 2) {
        uVar15 = 1;
        syscall();
        uVar9 = 0;
      }
    }
    else {
      LOCK();
      lVar11 = *plVar10;
      *(int *)plVar10 = 0;
      UNLOCK();
      if ((int)lVar11 == 2) {
        syscall();
        lVar11 = plVar16[4];
        uVar9 = CONCAT62(uVar13,0x1f);
        if (lVar11 == 0) {
          uVar15 = 0;
          goto LAB_011dd3d1;
        }
      }
      else {
LAB_011dd2ed:
        lVar11 = plVar16[4];
        uVar9 = CONCAT62(uVar13,0x1f);
        uVar15 = 0;
        if (lVar11 == 0) goto LAB_011dd3d1;
      }
LAB_011dd2ff:
      uVar9 = CONCAT62(uVar13,0x1f);
      (*(code *)puStack_70[3])(lStack_80,plVar16,lVar11,3,uStack_78);
      uVar15 = extraout_RDX_01;
    }
LAB_011dd3d1:
    auVar19._0_8_ = uVar9 & 0xffffffff;
    auVar19._8_8_ = uVar15;
    return auVar19;
  case 6:
  case 7:
    goto switchD_011dd07b_caseD_6;
  }
  unaff_R13 = CONCAT71((int7)(unaff_R13 >> 8),~bVar18) & 0xffffffffffffff01;
  *(char *)pplVar8 = (char)unaff_R13;
  goto LAB_011dd06c;
switchD_011dd07b_caseD_3:
  LOCK();
  plVar6 = (long *)plVar12[1];
  bVar18 = plVar10 == plVar6;
  if (bVar18) {
    plVar12[1] = (long)plVar16;
    plVar6 = plVar10;
  }
  UNLOCK();
  if (bVar18) goto LAB_011dd025;
  goto LAB_011dd06c;
LAB_011dd025:
  lVar11 = 1;
switchD_011dd07b_caseD_6:
  plVar12 = (long *)*plVar12;
  if (plVar12 == (long *)0x0) goto LAB_011dcef7;
  goto LAB_011dd03c;
}


// ---- FUN_011dd0e0 @ 011dd0e0

ulong FUN_011dd0e0(long param_1,long *param_2,undefined8 param_3,long param_4,ulong param_5,
                  undefined8 param_6)

{
  int *piVar1;
  long *plVar2;
  char cVar3;
  int iVar4;
  undefined8 *puVar5;
  ulong uVar6;
  int iVar7;
  ulong uVar8;
  undefined8 *puVar9;
  undefined6 uVar10;
  byte bVar11;
  long lVar12;
  bool bVar13;
  undefined8 unaff_retaddr;
  long local_80;
  short local_78;
  long local_70;
  undefined8 local_68;
  undefined8 local_60;
  long *local_58;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 *local_40;
  byte local_34;
  
  local_50 = *(undefined8 *)(param_1 + 0x328);
  puVar5 = *(undefined8 **)(param_1 + 0x330);
  bVar11 = (byte)param_5 & 0x3f;
  uVar8 = 1L << (param_5 & 0x3f);
  lVar12 = 0;
  if (7 < uVar8) {
    lVar12 = uVar8 - 8;
  }
  uVar8 = -1L << (param_5 & 0x3f);
  lVar12 = ((lVar12 - uVar8) + 0x2f & uVar8) + param_4;
  local_58 = param_2;
  local_48 = unaff_retaddr;
  local_34 = bVar11;
  if (lVar12 == 0) {
    puVar9 = (undefined8 *)0xfffffffffffffff8;
  }
  else {
    local_70 = param_1;
    local_68 = param_3;
    local_60 = param_6;
    puVar9 = (undefined8 *)(*(code *)*puVar5)(local_50,lVar12,3);
    param_1 = local_70;
    param_6 = local_60;
    param_3 = local_68;
    if (puVar9 == (undefined8 *)0x0) {
      uVar8 = CONCAT62((int6)((ulong)local_70 >> 0x10),0x1f);
      goto LAB_011dd3d1;
    }
  }
  puVar9[1] = FUN_011ddfa0;
  puVar9[2] = local_58;
  puVar9[3] = param_6;
  *(byte *)(puVar9 + 5) = bVar11;
  puVar9[4] = lVar12;
  uVar8 = -1L << (param_5 & 0x3f);
  local_40 = puVar5;
  FUN_011f4580(~((uVar8 - (long)puVar9) - 0x30) & uVar8,param_3,param_4);
  LOCK();
  iVar7 = *(int *)(param_1 + 0x338);
  bVar13 = iVar7 == 0;
  if (bVar13) {
    *(int *)(param_1 + 0x338) = 1;
    iVar7 = 0;
  }
  UNLOCK();
  local_34 = !bVar13;
  piVar1 = (int *)(param_1 + 0x338);
  uVar8 = (ulong)!bVar13;
  if (!bVar13) {
    if (iVar7 == 2) {
      uVar8 = 0x11dd3fe;
      syscall();
    }
    LOCK();
    iVar7 = *piVar1;
    *piVar1 = 2;
    UNLOCK();
    while (iVar7 != 0) {
      uVar8 = 0x11dd425;
      syscall();
      LOCK();
      iVar7 = *piVar1;
      *piVar1 = 2;
      UNLOCK();
    }
  }
  uVar6 = *(ulong *)(param_1 + 0x280);
  uVar10 = (undefined6)((ulong)param_1 >> 0x10);
  if (uVar6 < *(ulong *)(param_1 + 0x278)) {
    *(ulong *)(param_1 + 0x280) = uVar6 + 1;
    if (*(ulong *)(param_1 + 0x260) >> 1 == uVar6) {
      LOCK();
      *(long *)(param_1 + 0x260) = *(long *)(param_1 + 0x260) + 2;
      UNLOCK();
      FUN_011dd860(&local_80,*(undefined8 *)(param_1 + 600),param_1,uVar8);
      if (local_78 != 0) {
        LOCK();
        plVar2 = (long *)(param_1 + 0x260);
        lVar12 = *plVar2;
        *plVar2 = *plVar2 + -2;
        UNLOCK();
        if (lVar12 == 3) {
          LOCK();
          iVar7 = *(int *)(param_1 + 0x268);
          *(int *)(param_1 + 0x268) = 2;
          UNLOCK();
          if (iVar7 == 1) {
            syscall();
          }
        }
        *(ulong *)(param_1 + 0x280) = uVar6;
        LOCK();
        iVar7 = *(int *)(param_1 + 0x338);
        *(int *)(param_1 + 0x338) = 0;
        UNLOCK();
        if (iVar7 != 2) goto LAB_011dd2ed;
        syscall();
        lVar12 = puVar9[4];
        goto joined_r0x011dd2f9;
      }
      LOCK();
      cVar3 = *(char *)(local_80 + 0x18);
      *(char *)(local_80 + 0x18) = '\x01';
      UNLOCK();
      if (cVar3 != '\0') {
        if (*(int *)(local_80 + 0x10) != 0) {
          do {
            syscall();
          } while (*(int *)(local_80 + 0x10) != 0);
        }
        syscall();
      }
    }
    LOCK();
    *local_58 = *local_58 + 1;
    UNLOCK();
    *puVar9 = *(undefined8 *)(param_1 + 0x48);
    *(undefined8 **)(param_1 + 0x48) = puVar9;
    iVar7 = *(int *)(param_1 + 0x33c);
    do {
      if ((ushort)iVar7 <= (ushort)((uint)iVar7 >> 0x10)) goto LAB_011dd3c1;
      LOCK();
      iVar4 = *(int *)(param_1 + 0x33c);
      bVar13 = iVar7 == iVar4;
      if (bVar13) {
        *(int *)(param_1 + 0x33c) = iVar7 + 0x10000;
        iVar4 = iVar7;
      }
      iVar7 = iVar4;
      UNLOCK();
    } while (!bVar13);
    LOCK();
    *(int *)(param_1 + 0x340) = *(int *)(param_1 + 0x340) + 1;
    UNLOCK();
    syscall();
LAB_011dd3c1:
    LOCK();
    iVar7 = *piVar1;
    *piVar1 = 0;
    UNLOCK();
    uVar8 = 0;
    if (iVar7 == 2) {
      syscall();
      uVar8 = 0;
    }
  }
  else {
    LOCK();
    iVar7 = *piVar1;
    *piVar1 = 0;
    UNLOCK();
    if (iVar7 == 2) {
      syscall();
      lVar12 = puVar9[4];
    }
    else {
LAB_011dd2ed:
      lVar12 = puVar9[4];
    }
joined_r0x011dd2f9:
    uVar8 = CONCAT62(uVar10,0x1f);
    if (lVar12 != 0) {
      uVar8 = CONCAT62(uVar10,0x1f);
      (*(code *)local_40[3])(local_50,puVar9,lVar12,3,local_48);
    }
  }
LAB_011dd3d1:
  return uVar8 & 0xffffffff;
}


// ---- FUN_011dd480 @ 011dd480

ulong FUN_011dd480(code *param_1,long *param_2,undefined8 param_3,long param_4,uint param_5,
                  code *UNRECOVERED_JUMPTABLE)

{
  int *piVar1;
  long *plVar2;
  char cVar3;
  uint uVar4;
  undefined8 *puVar5;
  int iVar6;
  uint uVar7;
  ulong uVar8;
  undefined8 *puVar9;
  ulong uVar10;
  long lVar11;
  byte bVar12;
  bool bVar13;
  undefined8 unaff_retaddr;
  long local_80;
  short local_78;
  undefined8 local_70;
  long local_68;
  long *local_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 *local_48;
  code *local_40;
  byte local_34;
  
  uVar10 = (ulong)param_5;
  local_58 = *(undefined8 *)((long)param_1 + 0x328);
  puVar5 = *(undefined8 **)((long)param_1 + 0x330);
  bVar12 = (byte)param_5 & 0x3f;
  uVar8 = 1L << (uVar10 & 0x3f);
  lVar11 = 0;
  if (7 < uVar8) {
    lVar11 = uVar8 - 8;
  }
  uVar8 = -1L << (uVar10 & 0x3f);
  lVar11 = ((lVar11 - uVar8) + 0x2f & uVar8) + param_4;
  local_60 = param_2;
  local_50 = unaff_retaddr;
  local_34 = bVar12;
  if (lVar11 == 0) {
    puVar9 = (undefined8 *)0xfffffffffffffff8;
  }
  else {
    local_70 = param_3;
    local_68 = param_4;
    local_40 = param_1;
    puVar9 = (undefined8 *)(*(code *)*puVar5)(local_58,lVar11,3);
    param_1 = local_40;
    param_4 = local_68;
    param_3 = local_70;
    if (puVar9 == (undefined8 *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x011dd4e5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar8 = (*UNRECOVERED_JUMPTABLE)(local_70);
      return uVar8;
    }
  }
  puVar9[1] = FUN_011ddfa0;
  puVar9[2] = local_60;
  puVar9[3] = UNRECOVERED_JUMPTABLE;
  *(byte *)(puVar9 + 5) = bVar12;
  puVar9[4] = lVar11;
  uVar8 = -1L << (uVar10 & 0x3f);
  local_48 = puVar5;
  local_40 = UNRECOVERED_JUMPTABLE;
  FUN_011f4580(~((uVar8 - (long)puVar9) - 0x30) & uVar8,param_3,param_4);
  LOCK();
  iVar6 = *(int *)((long)param_1 + 0x338);
  bVar13 = iVar6 == 0;
  if (bVar13) {
    *(int *)((long)param_1 + 0x338) = 1;
    iVar6 = 0;
  }
  UNLOCK();
  local_34 = !bVar13;
  piVar1 = (int *)((long)param_1 + 0x338);
  uVar8 = (ulong)!bVar13;
  if (!bVar13) {
    if (iVar6 == 2) {
      uVar8 = 0x11dd7bc;
      syscall();
    }
    LOCK();
    iVar6 = *piVar1;
    *piVar1 = 2;
    UNLOCK();
    while (iVar6 != 0) {
      uVar8 = 0x11dd7e4;
      syscall();
      LOCK();
      iVar6 = *piVar1;
      *piVar1 = 2;
      UNLOCK();
    }
  }
  uVar10 = *(ulong *)((long)param_1 + 0x280);
  if (uVar10 < *(ulong *)((long)param_1 + 0x270)) {
    *(ulong *)((long)param_1 + 0x280) = uVar10 + 1;
    if (*(ulong *)((long)param_1 + 0x260) >> 1 == uVar10) {
      LOCK();
      *(long *)((long)param_1 + 0x260) = *(long *)((long)param_1 + 0x260) + 2;
      UNLOCK();
      FUN_011dd860(&local_80,*(undefined8 *)((long)param_1 + 600),param_1,uVar8);
      if (local_78 != 0) {
        LOCK();
        plVar2 = (long *)((long)param_1 + 0x260);
        lVar11 = *plVar2;
        *plVar2 = *plVar2 + -2;
        UNLOCK();
        if (lVar11 == 3) {
          LOCK();
          iVar6 = *(int *)((long)param_1 + 0x268);
          *(int *)((long)param_1 + 0x268) = 2;
          UNLOCK();
          if (iVar6 == 1) {
            syscall();
          }
        }
        *(ulong *)((long)param_1 + 0x280) = uVar10;
        LOCK();
        iVar6 = *(int *)((long)param_1 + 0x338);
        *(int *)((long)param_1 + 0x338) = 0;
        UNLOCK();
        if (iVar6 == 2) {
          syscall();
          lVar11 = puVar9[4];
        }
        else {
          lVar11 = puVar9[4];
        }
        if (lVar11 != 0) {
          (*(code *)local_48[3])(local_58,puVar9,lVar11,3,local_50);
        }
        goto LAB_011dd6d4;
      }
      LOCK();
      cVar3 = *(char *)(local_80 + 0x18);
      *(char *)(local_80 + 0x18) = '\x01';
      UNLOCK();
      if (cVar3 != '\0') {
        if (*(int *)(local_80 + 0x10) != 0) {
          do {
            syscall();
          } while (*(int *)(local_80 + 0x10) != 0);
        }
        syscall();
      }
    }
    LOCK();
    *local_60 = *local_60 + 1;
    UNLOCK();
    *puVar9 = *(undefined8 *)((long)param_1 + 0x48);
    *(undefined8 **)((long)param_1 + 0x48) = puVar9;
    LOCK();
    iVar6 = *(int *)((long)param_1 + 0x338);
    *(int *)((long)param_1 + 0x338) = 0;
    UNLOCK();
    if (iVar6 == 2) {
      syscall();
    }
    uVar8 = (ulong)*(uint *)((long)param_1 + 0x33c);
    do {
      uVar7 = (uint)uVar8;
      if ((ushort)uVar8 <= (ushort)(uVar8 >> 0x10)) {
        return uVar8;
      }
      LOCK();
      uVar4 = *(uint *)((long)param_1 + 0x33c);
      if (uVar7 == uVar4) {
        *(uint *)((long)param_1 + 0x33c) = uVar7 + 0x10000;
      }
      else {
        uVar8 = (ulong)uVar4;
      }
      UNLOCK();
    } while (uVar7 != uVar4);
    LOCK();
    *(int *)((long)param_1 + 0x340) = *(int *)((long)param_1 + 0x340) + 1;
    UNLOCK();
    syscall();
    return 0xca;
  }
  LOCK();
  iVar6 = *piVar1;
  *piVar1 = 0;
  UNLOCK();
  if (iVar6 == 2) {
    syscall();
    lVar11 = puVar9[4];
  }
  else {
    lVar11 = puVar9[4];
  }
  if (lVar11 != 0) {
    (*(code *)local_48[3])(local_58,puVar9,lVar11,3,local_50);
  }
LAB_011dd6d4:
                    /* WARNING: Could not recover jumptable at 0x011dd6e2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar8 = (*local_40)(param_3);
  return uVar8;
}


// ---- FUN_011dd860 @ 011dd860

/* WARNING: Removing unreachable block (ram,0x011dda8f) */

void FUN_011dd860(undefined8 param_1,ulong param_2,undefined8 param_3)

{
  ulong uVar1;
  
  uVar1 = 0x1000;
  if (0x1000 < param_2) {
    uVar1 = param_2;
  }
  syscall();
                    /* WARNING: Could not recover jumptable at 0x011dd90d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR_LAB_0100bab8)
            (0,(DAT_011fe000 +
                (-DAT_011fe008 & ((uVar1 + 0x1fff & 0xfffffffffffff000) + DAT_011fe008) - 1) + 7 &
               0xfffffffffffffff8) + 0x1027 & 0xfffffffffffff000,0,0,0xffffffffffffffff,0,param_3);
  return;
}


// ---- FUN_011ddb00 @ 011ddb00

/* WARNING: Removing unreachable block (ram,0x011ddf3c) */
/* WARNING: Removing unreachable block (ram,0x011ddfcb) */
/* WARNING: Removing unreachable block (ram,0x011ddfd6) */
/* WARNING: Removing unreachable block (ram,0x011de01d) */
/* WARNING: Removing unreachable block (ram,0x011de036) */
/* WARNING: Removing unreachable block (ram,0x011de03f) */
/* WARNING: Removing unreachable block (ram,0x011de06d) */

undefined8 FUN_011ddb00(long *param_1)

{
  int *piVar1;
  long *plVar2;
  uint uVar3;
  long lVar4;
  undefined8 *puVar5;
  int iVar6;
  uint uVar7;
  long lVar8;
  long lVar9;
  uint uVar10;
  undefined8 uVar11;
  ulong uVar12;
  long *plVar13;
  long *in_FS_OFFSET;
  bool bVar14;
  long local_268 [67];
  undefined4 local_50;
  undefined1 local_4c;
  long *local_48;
  undefined1 local_3c;
  bool local_38;
  bool local_34;
  
  lVar4 = *param_1;
  local_268[0] = *in_FS_OFFSET + -0x40003;
  local_268[2] = 0x40000;
  uVar11 = 0x11ddb5a;
  syscall();
  if (*(char *)((long)in_FS_OFFSET + -0x40004) == '\x01') {
    local_50 = (undefined4)in_FS_OFFSET[-0x8001];
  }
  else {
    local_50 = 0xba;
    uVar11 = 0x11ddb76;
    syscall();
    *(undefined4 *)(in_FS_OFFSET + -0x8001) = 0xba;
    *(undefined1 *)((long)in_FS_OFFSET + -0x40004) = 1;
  }
  local_268[1] = 0;
  local_4c = 0;
  plVar13 = (long *)0xff;
  local_48 = param_1;
  FUN_011f4160(local_268 + 2,0xff,0x208,uVar11);
  in_FS_OFFSET[-0x8002] = (long)local_268;
  local_268[0] = *(long *)(lVar4 + 0x288);
  LOCK();
  lVar8 = *(long *)(lVar4 + 0x288);
  local_38 = local_268[0] == lVar8;
  if (local_38) {
    *(long *)(lVar4 + 0x288) = (long)local_268;
    lVar8 = local_268[0];
  }
  UNLOCK();
  while (!local_38) {
    LOCK();
    lVar9 = *(long *)(lVar4 + 0x288);
    local_38 = lVar8 == lVar9;
    if (local_38) {
      *(long *)(lVar4 + 0x288) = (long)local_268;
      lVar9 = lVar8;
    }
    UNLOCK();
    local_268[0] = lVar8;
    lVar8 = lVar9;
  }
  local_38 = !local_38;
  LOCK();
  iVar6 = *(int *)(lVar4 + 0x338);
  bVar14 = iVar6 == 0;
  if (bVar14) {
    *(int *)(lVar4 + 0x338) = 1;
    iVar6 = 0;
  }
  UNLOCK();
  local_34 = !bVar14;
  piVar1 = (int *)(lVar4 + 0x338);
  uVar12 = CONCAT71((int7)((ulong)uVar11 >> 8),!bVar14);
  if (!bVar14) {
    if (iVar6 == 2) {
      plVar13 = (long *)0x80;
      uVar12 = 0x11dde92;
      syscall();
    }
    LOCK();
    iVar6 = *piVar1;
    *piVar1 = 2;
    UNLOCK();
    if (iVar6 != 0) {
      plVar13 = (long *)0x80;
      do {
        uVar12 = 0x11ddeb9;
        syscall();
        LOCK();
        iVar6 = *piVar1;
        *piVar1 = 2;
        UNLOCK();
      } while (iVar6 != 0);
    }
  }
LAB_011ddc30:
  while (puVar5 = *(undefined8 **)(lVar4 + 0x48), puVar5 != (undefined8 *)0x0) {
    *(undefined8 *)(lVar4 + 0x48) = *puVar5;
    LOCK();
    iVar6 = *(int *)(lVar4 + 0x338);
    *(int *)(lVar4 + 0x338) = 0;
    UNLOCK();
    if (iVar6 == 2) {
      uVar12 = 0x11ddd60;
      syscall();
    }
    local_4c = 0;
    plVar13 = local_268;
    (*(code *)puVar5[1])(puVar5,local_268,lVar4,uVar12);
    LOCK();
    iVar6 = *(int *)(lVar4 + 0x338);
    bVar14 = iVar6 == 0;
    if (bVar14) {
      *(int *)(lVar4 + 0x338) = 1;
      iVar6 = 0;
    }
    UNLOCK();
    local_34 = !bVar14;
    uVar12 = CONCAT71((int7)(uVar12 >> 8),!bVar14);
    if (!bVar14) {
      if (iVar6 == 2) {
        plVar13 = (long *)0x80;
        uVar12 = 0x11ddd81;
        syscall();
      }
      while( true ) {
        LOCK();
        iVar6 = *piVar1;
        *piVar1 = 2;
        UNLOCK();
        if (iVar6 == 0) break;
        plVar13 = (long *)0x80;
        uVar12 = 0x11ddda7;
        syscall();
      }
    }
    *(long *)(lVar4 + 0x280) = *(long *)(lVar4 + 0x280) + -1;
  }
  if (*(char *)(lVar4 + 0x35e) == '\x01') {
    LOCK();
    iVar6 = *piVar1;
    *piVar1 = 0;
    UNLOCK();
    if (iVar6 == 2) {
      plVar13 = (long *)0x81;
      uVar12 = 0x11ddede;
      syscall();
      LOCK();
      plVar2 = (long *)(lVar4 + 0x260);
      lVar8 = *plVar2;
      *plVar2 = *plVar2 + -2;
      UNLOCK();
    }
    else {
      LOCK();
      plVar2 = (long *)(lVar4 + 0x260);
      lVar8 = *plVar2;
      *plVar2 = *plVar2 + -2;
      UNLOCK();
    }
    if (lVar8 == 3) {
      LOCK();
      iVar6 = *(int *)(lVar4 + 0x268);
      *(int *)(lVar4 + 0x268) = 2;
      UNLOCK();
      if (iVar6 == 1) {
        plVar13 = (long *)0x81;
        uVar12 = 0x11dde51;
        syscall();
      }
    }
    LOCK();
    lVar4 = local_48[4];
    *(char *)(local_48 + 4) = '\x02';
    UNLOCK();
    if ((char)lVar4 != '\0') {
      FUN_011ddf50();
      *(ulong *)(((ulong)plVar13 & 0xfffffffffffffff0) - 8) = uVar12;
      syscall();
      return 0x38;
    }
    return 0;
  }
  LOCK();
  *(int *)(lVar4 + 0x33c) = *(int *)(lVar4 + 0x33c) + 1;
  UNLOCK();
  LOCK();
  iVar6 = *(int *)(lVar4 + 0x338);
  *(int *)(lVar4 + 0x338) = 0;
  UNLOCK();
  if (iVar6 == 2) {
    syscall();
  }
  do {
    plVar13 = (long *)0x80;
    syscall();
    uVar7 = *(uint *)(lVar4 + 0x33c);
    while (0xffff < uVar7) {
      uVar10 = ((uVar7 - 1 & 0xffff) + (uVar7 & 0xffff0000)) - 0x10000;
      LOCK();
      uVar3 = *(uint *)(lVar4 + 0x33c);
      bVar14 = uVar7 == uVar3;
      if (bVar14) {
        *(uint *)(lVar4 + 0x33c) = uVar10;
        uVar3 = uVar7;
      }
      uVar7 = uVar3;
      UNLOCK();
      if (bVar14) {
        LOCK();
        iVar6 = *piVar1;
        bVar14 = iVar6 == 0;
        if (bVar14) {
          *piVar1 = 1;
          iVar6 = 0;
        }
        UNLOCK();
        local_34 = !bVar14;
        uVar12 = (ulong)CONCAT31((int3)(uVar10 >> 8),!bVar14);
        local_3c = 0;
        if (!bVar14) {
          if (iVar6 == 2) {
            uVar12 = 0x11ddd47;
            syscall();
          }
          while( true ) {
            plVar13 = (long *)0x80;
            LOCK();
            iVar6 = *piVar1;
            *piVar1 = 2;
            UNLOCK();
            if (iVar6 == 0) break;
            uVar12 = 0x11dddd7;
            syscall();
          }
        }
        goto LAB_011ddc30;
      }
    }
  } while( true );
}


// ---- FUN_011ddf10 @ 011ddf10

/* WARNING: Removing unreachable block (ram,0x011ddf3c) */
/* WARNING: Removing unreachable block (ram,0x011ddfcb) */
/* WARNING: Removing unreachable block (ram,0x011ddfd6) */
/* WARNING: Removing unreachable block (ram,0x011de01d) */
/* WARNING: Removing unreachable block (ram,0x011de036) */
/* WARNING: Removing unreachable block (ram,0x011de03f) */
/* WARNING: Removing unreachable block (ram,0x011de06d) */

undefined8 FUN_011ddf10(undefined8 param_1,ulong param_2,undefined8 param_3,undefined8 param_4)

{
  *(undefined8 *)((param_2 & 0xfffffffffffffff0) - 8) = param_4;
  syscall();
  return 0x38;
}


// ---- FUN_011ddf50 @ 011ddf50

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_011ddf50(long param_1)

{
  long lVar1;
  ulong *puVar2;
  ulong uVar3;
  undefined8 uVar4;
  undefined8 unaff_RBP;
  bool bVar5;
  
  puVar2 = _DAT_00000010;
  syscall();
  syscall();
  lVar1 = *(long *)(param_1 + 8);
  syscall();
  syscall();
  LOCK();
  *(ulong **)(lVar1 + 8) = _DAT_00000010;
  UNLOCK();
  if ((long)*puVar2 < 0) {
    *(ulong *)(lVar1 + 8) = (ulong)puVar2 | 6;
  }
  uVar3 = -1L << ((ulong)DAT_00000028 & 0x3f);
  (*_DAT_00000018)(~(uVar3 - 0x30) & uVar3);
  *(undefined8 *)(lVar1 + 8) = 0;
  LOCK();
  uVar3 = *puVar2;
  *puVar2 = *puVar2 - 1;
  UNLOCK();
  bVar5 = (uVar3 & 0x3fffffffffffffff) == 1;
  uVar4 = CONCAT71((uint7)((uVar3 << 2) >> 10),bVar5);
  if (((byte)(uVar3 >> 0x3e) & bVar5) != 0) {
    LOCK();
    *(int *)puVar2[1] = *(int *)puVar2[1] + 1;
    UNLOCK();
    uVar4 = 0xca;
    syscall();
  }
  if (_DAT_00000020 != 0) {
                    /* WARNING: Could not recover jumptable at 0x011de06b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar4 = (**(code **)(lRam0000000000000330 + 0x18))
                      (uRam0000000000000328,0,_DAT_00000020,3,unaff_RBP);
    return uVar4;
  }
  return uVar4;
}


// ---- FUN_011ddfa0 @ 011ddfa0

undefined8 FUN_011ddfa0(long param_1,long param_2,long param_3)

{
  ulong *puVar1;
  ulong uVar2;
  undefined8 uVar3;
  bool bVar4;
  undefined8 unaff_retaddr;
  
  puVar1 = *(ulong **)(param_1 + 0x10);
  LOCK();
  *(ulong **)(param_2 + 8) = puVar1;
  UNLOCK();
  if ((long)*puVar1 < 0) {
    *(ulong *)(param_2 + 8) = (ulong)puVar1 | 6;
  }
  uVar2 = -1L << ((ulong)*(byte *)(param_1 + 0x28) & 0x3f);
  (**(code **)(param_1 + 0x18))(~((uVar2 - param_1) - 0x30) & uVar2);
  *(undefined8 *)(param_2 + 8) = 0;
  LOCK();
  uVar2 = *puVar1;
  *puVar1 = *puVar1 - 1;
  UNLOCK();
  bVar4 = (uVar2 & 0x3fffffffffffffff) == 1;
  uVar3 = CONCAT71((uint7)((uVar2 << 2) >> 10),bVar4);
  if (((byte)(uVar2 >> 0x3e) & bVar4) != 0) {
    LOCK();
    *(int *)puVar1[1] = *(int *)puVar1[1] + 1;
    UNLOCK();
    uVar3 = 0xca;
    syscall();
  }
  if (*(long *)(param_1 + 0x20) != 0) {
                    /* WARNING: Could not recover jumptable at 0x011de06b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar3 = (**(code **)(*(long *)(param_3 + 0x330) + 0x18))
                      (*(undefined8 *)(param_3 + 0x328),param_1,*(long *)(param_1 + 0x20),3,
                       unaff_retaddr);
    return uVar3;
  }
  return uVar3;
}


// ---- FUN_011de080 @ 011de080

void FUN_011de080(long param_1,long param_2,undefined8 param_3,undefined8 param_4)

{
  ulong uVar1;
  ulong uVar2;
  bool bVar3;
  undefined8 unaff_retaddr;
  undefined4 local_2c;
  
  local_2c = 0;
  *(undefined4 **)(param_2 + 0x20) = &local_2c;
  uVar1 = *(ulong *)(param_2 + 0x18);
  do {
    LOCK();
    uVar2 = *(ulong *)(param_2 + 0x18);
    bVar3 = uVar1 == uVar2;
    if (bVar3) {
      *(ulong *)(param_2 + 0x18) = uVar1 | 3;
      uVar2 = uVar1;
    }
    UNLOCK();
    uVar1 = uVar2;
  } while (!bVar3);
  if ((uVar2 & 3) == 0) {
    FUN_011de120(param_2,param_1,&local_2c,uVar2);
  }
  FUN_011f4580(param_3,*(long *)(param_2 + 0x28) + param_2,param_4);
  if (*(long *)(param_2 + 0x30) != 0) {
    (**(code **)(*(long *)(param_1 + 0x330) + 0x18))
              (*(undefined8 *)(param_1 + 0x328),param_2,*(long *)(param_2 + 0x30),3,unaff_retaddr);
  }
  return;
}


// ---- FUN_011de120 @ 011de120

/* WARNING: Removing unreachable block (ram,0x011de2ce) */

void FUN_011de120(ulong param_1,long param_2,int *param_3,long param_4)

{
  ulong *puVar1;
  short sVar2;
  uint uVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  undefined8 unaff_RBX;
  ulong uVar8;
  ulong uVar9;
  ulong unaff_R12;
  ulong *unaff_R13;
  ulong uVar10;
  long in_FS_OFFSET;
  bool bVar11;
  undefined8 uStack_68;
  long lStack_60;
  ulong local_58;
  ulong *local_50;
  ulong local_48;
  ulong local_40;
  undefined1 *local_38;
  
  local_38 = &stack0xfffffffffffffff8;
  if (param_4 != 0) {
    uVar9 = param_1 >> 3;
    uVar5 = *(ulong *)(param_4 + 8);
    if (uVar9 == uVar5 >> 3) {
      uVar6 = param_1 | 2;
      uVar7 = param_1 | 3;
      uVar8 = param_1 | 1;
      uVar10 = param_1 | 6;
LAB_011de1b8:
      uVar3 = (uint)uVar5 & 7;
      switch(uVar3) {
      case 0:
        LOCK();
        uVar5 = *(ulong *)(param_4 + 8);
        bVar11 = param_1 == uVar5;
        if (bVar11) {
          *(ulong *)(param_4 + 8) = uVar10;
          uVar5 = param_1;
        }
        UNLOCK();
        if (bVar11) goto switchD_011de1bb_caseD_6;
        break;
      case 1:
        LOCK();
        uVar5 = *(ulong *)(param_4 + 8);
        bVar11 = uVar8 == uVar5;
        if (bVar11) {
          *(ulong *)(param_4 + 8) = uVar10;
          uVar5 = uVar8;
        }
        UNLOCK();
        unaff_R13 = &local_40;
        goto LAB_011de1a1;
      case 2:
        LOCK();
        uVar5 = *(ulong *)(param_4 + 8);
        bVar11 = uVar6 == uVar5;
        if (bVar11) {
          *(ulong *)(param_4 + 8) = param_1 | 4;
          uVar5 = uVar6;
        }
        UNLOCK();
        unaff_R13 = &local_58;
LAB_011de1a1:
        *(byte *)unaff_R13 = ~bVar11 & 1;
        break;
      case 3:
        LOCK();
        uVar5 = *(ulong *)(param_4 + 8);
        bVar11 = uVar7 == uVar5;
        if (bVar11) {
          *(ulong *)(param_4 + 8) = param_1 | 5;
          uVar5 = uVar7;
        }
        UNLOCK();
        if (bVar11) {
          bVar11 = true;
          goto LAB_011de21e;
        }
        break;
      default:
        uStack_68 = (ulong)uVar3;
        *(long *)(uVar8 + 0x20) = (long)&uStack_68 + 4;
        uVar5 = *(ulong *)(uVar8 + 0x18);
        do {
          LOCK();
          uVar4 = *(ulong *)(uVar8 + 0x18);
          bVar11 = uVar5 == uVar4;
          if (bVar11) {
            *(ulong *)(uVar8 + 0x18) = uVar5 | 1;
            uVar4 = uVar5;
          }
          UNLOCK();
          uVar5 = uVar4;
        } while (!bVar11);
        lStack_60 = param_2;
        local_58 = unaff_R12;
        local_50 = unaff_R13;
        local_48 = param_1;
        local_40 = uVar10;
        if ((uVar4 & 3) == 0) {
          local_38 = &stack0xfffffffffffffff8;
          do {
            sVar2 = FUN_011f3fb0((long)&uStack_68 + 4,0,0,&DAT_01000740);
            if (sVar2 != 0) {
              uVar5 = *(ulong *)(uVar8 + 0x18);
              do {
                LOCK();
                uVar10 = *(ulong *)(uVar8 + 0x18);
                bVar11 = uVar5 == uVar10;
                if (bVar11) {
                  *(ulong *)(uVar8 + 0x18) = uVar5 | 3;
                  uVar10 = uVar5;
                }
                UNLOCK();
                uVar5 = uVar10;
              } while (!bVar11);
              if (((uint)uVar10 & 3) == 2) {
                do {
                  syscall();
                } while (uStack_68._4_4_ == 0);
              }
              else {
                FUN_011de120(uVar8,uVar9,(long)&uStack_68 + 4,uVar10 & 0xfffffffffffffffc);
                uVar10 = *(ulong *)(uVar8 + 0x18);
              }
              if (uVar10 < 4) {
                LOCK();
                puVar1 = (ulong *)(*(long *)(in_FS_OFFSET + -0x40010) + 8);
                *puVar1 = *puVar1 ^ 1;
                UNLOCK();
              }
              break;
            }
          } while (uStack_68._4_4_ == 0);
        }
        FUN_011f4580(uVar7,*(long *)(uVar8 + 0x28) + uVar8,uVar6);
        if (*(long *)(uVar8 + 0x30) != 0) {
          (**(code **)(*(long *)(uVar9 + 0x330) + 0x18))
                    (*(undefined8 *)(uVar9 + 0x328),uVar8,*(long *)(uVar8 + 0x30),3,unaff_RBX);
        }
        return;
      case 6:
      case 7:
        goto switchD_011de1bb_caseD_6;
      }
      unaff_R12 = uVar5 >> 3;
      if (uVar9 != unaff_R12) goto switchD_011de1bb_caseD_6;
      goto LAB_011de1b8;
    }
  }
switchD_011de1bb_caseD_6:
  bVar11 = false;
LAB_011de21e:
  uVar5 = 0x400;
  while( true ) {
    uVar9 = uVar5;
    if ((bVar11) &&
       (((uint)*(ulong *)(param_4 + 8) & 7) == 5 && (*(ulong *)(param_4 + 8) ^ param_1) < 8)) {
      if (*(int *)(param_2 + 0x344) == 0) {
        syscall();
        *(undefined4 *)(param_2 + 0x344) = 0x27;
      }
      syscall();
    }
    bVar11 = false;
    syscall();
    if (*param_3 != 0) break;
    uVar5 = 0xffffffffffffffff;
    if (uVar9 == (uVar9 & 0x7fffffffffffffff)) {
      uVar5 = uVar9 * 2;
    }
  }
  return;
}


// ---- FUN_011de320 @ 011de320

void FUN_011de320(long param_1,long param_2,undefined8 param_3,undefined8 param_4)

{
  ulong *puVar1;
  short sVar2;
  uint in_EAX;
  ulong uVar3;
  ulong uVar4;
  long in_FS_OFFSET;
  bool bVar5;
  undefined8 unaff_retaddr;
  undefined8 uStack_38;
  
  uStack_38 = (ulong)in_EAX;
  *(long *)(param_2 + 0x20) = (long)&uStack_38 + 4;
  uVar3 = *(ulong *)(param_2 + 0x18);
  do {
    LOCK();
    uVar4 = *(ulong *)(param_2 + 0x18);
    bVar5 = uVar3 == uVar4;
    if (bVar5) {
      *(ulong *)(param_2 + 0x18) = uVar3 | 1;
      uVar4 = uVar3;
    }
    UNLOCK();
    uVar3 = uVar4;
  } while (!bVar5);
  if ((uVar4 & 3) == 0) {
    do {
      sVar2 = FUN_011f3fb0((long)&uStack_38 + 4,0,0,&DAT_01000740);
      if (sVar2 != 0) {
        uVar3 = *(ulong *)(param_2 + 0x18);
        do {
          LOCK();
          uVar4 = *(ulong *)(param_2 + 0x18);
          bVar5 = uVar3 == uVar4;
          if (bVar5) {
            *(ulong *)(param_2 + 0x18) = uVar3 | 3;
            uVar4 = uVar3;
          }
          UNLOCK();
          uVar3 = uVar4;
        } while (!bVar5);
        if (((uint)uVar4 & 3) == 2) {
          do {
            syscall();
          } while (uStack_38._4_4_ == 0);
        }
        else {
          FUN_011de120(param_2,param_1,(long)&uStack_38 + 4,uVar4 & 0xfffffffffffffffc);
          uVar4 = *(ulong *)(param_2 + 0x18);
        }
        if (uVar4 < 4) {
          LOCK();
          puVar1 = (ulong *)(*(long *)(in_FS_OFFSET + -0x40010) + 8);
          *puVar1 = *puVar1 ^ 1;
          UNLOCK();
        }
        break;
      }
    } while (uStack_38._4_4_ == 0);
  }
  FUN_011f4580(param_3,*(long *)(param_2 + 0x28) + param_2,param_4);
  if (*(long *)(param_2 + 0x30) != 0) {
    (**(code **)(*(long *)(param_1 + 0x330) + 0x18))
              (*(undefined8 *)(param_1 + 0x328),param_2,*(long *)(param_2 + 0x30),3,unaff_retaddr);
  }
  return;
}


// ---- FUN_011de450 @ 011de450

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 *
FUN_011de450(undefined8 *param_1,long param_2,long param_3,ulong param_4,undefined8 param_5,
            long param_6,byte param_7,undefined8 param_8)

{
  int *piVar1;
  long *plVar2;
  char cVar3;
  int iVar4;
  long lVar5;
  undefined8 *puVar6;
  undefined8 uVar7;
  int iVar8;
  ulong uVar9;
  undefined8 *puVar10;
  long lVar11;
  byte bVar12;
  ulong uVar13;
  bool bVar14;
  undefined8 unaff_retaddr;
  long local_88;
  short local_80;
  long local_78;
  ulong local_70;
  long local_68;
  undefined8 local_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 *local_48;
  undefined8 *local_40;
  byte local_35;
  byte local_34;
  
  local_58 = *(undefined8 *)(param_2 + 0x328);
  puVar6 = *(undefined8 **)(param_2 + 0x330);
  local_35 = (byte)param_4 & 0x3f;
  bVar12 = param_7 & 0x3f;
  uVar9 = 1L << ((ulong)param_7 & 0x3f);
  lVar11 = 0;
  if (7 < uVar9) {
    lVar11 = uVar9 - 8;
  }
  uVar13 = -1L << ((ulong)param_7 & 0x3f);
  local_70 = -1L << (param_4 & 0x3f);
  uVar9 = ~local_70;
  param_3 = (((lVar11 - uVar13) + 0x3f & uVar13) + uVar9 + param_6 & local_70) + param_3;
  local_78 = param_2;
  local_50 = unaff_retaddr;
  local_40 = param_1;
  local_34 = bVar12;
  if (param_3 == 0) {
    puVar10 = (undefined8 *)0xfffffffffffffff8;
    lVar11 = param_6;
  }
  else {
    local_68 = param_6;
    local_60 = param_5;
    puVar10 = (undefined8 *)(*(code *)*puVar6)(local_58,param_3,3);
    uVar7 = _UNK_010008d8;
    param_5 = local_60;
    lVar11 = local_68;
    if (puVar10 == (undefined8 *)0x0) {
      *local_40 = _DAT_010008d0;
      local_40[1] = uVar7;
      return local_40;
    }
  }
  puVar10[1] = FUN_011ded40;
  puVar10[2] = param_8;
  puVar10[3] = 0;
  *(byte *)(puVar10 + 7) = bVar12;
  puVar10[5] = (((long)puVar10 + ~uVar13 + 0x40 & uVar13) + uVar9 + param_6 & local_70) -
               (long)puVar10;
  puVar10[6] = param_3;
  uVar9 = -1L << ((ulong)param_7 & 0x3f);
  local_48 = puVar6;
  FUN_011f4580(~(uVar9 - (long)(puVar10 + 8)) & uVar9,param_5,lVar11);
  lVar11 = local_78;
  LOCK();
  iVar8 = *(int *)(local_78 + 0x338);
  bVar14 = iVar8 == 0;
  if (bVar14) {
    *(int *)(local_78 + 0x338) = 1;
    iVar8 = 0;
  }
  UNLOCK();
  local_34 = !bVar14;
  piVar1 = (int *)(local_78 + 0x338);
  uVar9 = (ulong)!bVar14;
  if (!bVar14) {
    if (iVar8 == 2) {
      uVar9 = 0x11de7ad;
      syscall();
    }
    LOCK();
    iVar8 = *piVar1;
    *piVar1 = 2;
    UNLOCK();
    while (iVar8 != 0) {
      uVar9 = 0x11de7d5;
      syscall();
      LOCK();
      iVar8 = *piVar1;
      *piVar1 = 2;
      UNLOCK();
    }
  }
  uVar13 = *(ulong *)(local_78 + 0x280);
  if (uVar13 < *(ulong *)(local_78 + 0x278)) {
    *(ulong *)(local_78 + 0x280) = uVar13 + 1;
    if (*(ulong *)(local_78 + 0x260) >> 1 == uVar13) {
      LOCK();
      *(long *)(local_78 + 0x260) = *(long *)(local_78 + 0x260) + 2;
      UNLOCK();
      FUN_011dd860(&local_88,*(undefined8 *)(local_78 + 600),local_78,uVar9);
      if (local_80 != 0) {
        LOCK();
        plVar2 = (long *)(lVar11 + 0x260);
        lVar5 = *plVar2;
        *plVar2 = *plVar2 + -2;
        UNLOCK();
        if (lVar5 == 3) {
          LOCK();
          iVar8 = *(int *)(lVar11 + 0x268);
          *(int *)(lVar11 + 0x268) = 2;
          UNLOCK();
          if (iVar8 == 1) {
            syscall();
          }
        }
        *(ulong *)(lVar11 + 0x280) = uVar13;
        LOCK();
        iVar8 = *(int *)(lVar11 + 0x338);
        *(int *)(lVar11 + 0x338) = 0;
        UNLOCK();
        if (iVar8 == 2) {
          syscall();
          lVar11 = puVar10[6];
        }
        else {
          lVar11 = puVar10[6];
        }
        if (lVar11 != 0) {
          (*(code *)local_48[3])(local_58,puVar10,lVar11,3,local_50);
        }
        uVar7 = _UNK_010008d8;
        *local_40 = _DAT_010008d0;
        local_40[1] = uVar7;
        return local_40;
      }
      LOCK();
      cVar3 = *(char *)(local_88 + 0x18);
      *(char *)(local_88 + 0x18) = '\x01';
      UNLOCK();
      if (cVar3 != '\0') {
        if (*(int *)(local_88 + 0x10) != 0) {
          do {
            syscall();
          } while (*(int *)(local_88 + 0x10) != 0);
        }
        syscall();
      }
    }
    *puVar10 = *(undefined8 *)(lVar11 + 0x48);
    *(undefined8 **)(lVar11 + 0x48) = puVar10;
    iVar8 = *(int *)(lVar11 + 0x33c);
    if ((ushort)((uint)iVar8 >> 0x10) < (ushort)iVar8) {
      do {
        LOCK();
        iVar4 = *(int *)(lVar11 + 0x33c);
        bVar14 = iVar8 == iVar4;
        if (bVar14) {
          *(int *)(lVar11 + 0x33c) = iVar8 + 0x10000;
          iVar4 = iVar8;
        }
        iVar8 = iVar4;
        UNLOCK();
        if (bVar14) {
          LOCK();
          *(int *)(lVar11 + 0x340) = *(int *)(lVar11 + 0x340) + 1;
          UNLOCK();
          syscall();
          LOCK();
          iVar8 = *piVar1;
          *piVar1 = 0;
          UNLOCK();
          goto joined_r0x011de8a7;
        }
      } while ((ushort)((uint)iVar8 >> 0x10) < (ushort)iVar8);
    }
    LOCK();
    iVar8 = *piVar1;
    *piVar1 = 0;
    UNLOCK();
joined_r0x011de8a7:
    if (iVar8 == 2) {
      syscall();
    }
    *(undefined2 *)(local_40 + 1) = 0;
    *local_40 = puVar10;
  }
  else {
    LOCK();
    iVar8 = *piVar1;
    *piVar1 = 0;
    UNLOCK();
    if (iVar8 == 2) {
      syscall();
      lVar11 = puVar10[6];
    }
    else {
      lVar11 = puVar10[6];
    }
    if (lVar11 != 0) {
      (*(code *)local_48[3])(local_58,puVar10,lVar11,3,local_50);
    }
    uVar7 = _UNK_010008d8;
    *local_40 = _DAT_010008d0;
    local_40[1] = uVar7;
  }
  return local_40;
}


// ---- FUN_011de8d0 @ 011de8d0

undefined8 *
FUN_011de8d0(long param_1,undefined8 param_2,long param_3,ulong param_4,undefined8 param_5,
            long param_6,byte param_7,code *param_8)

{
  int *piVar1;
  long *plVar2;
  char cVar3;
  int iVar4;
  long lVar5;
  int iVar6;
  ulong uVar7;
  undefined8 *puVar8;
  long lVar9;
  ulong uVar10;
  ulong uVar11;
  byte bVar12;
  bool bVar13;
  undefined8 unaff_retaddr;
  long local_90;
  short local_88;
  long local_80;
  undefined8 local_78;
  ulong local_70;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 *local_58;
  undefined8 local_50;
  byte local_41;
  undefined8 *local_40;
  byte local_34;
  
  local_68 = *(undefined8 *)(param_1 + 0x328);
  local_58 = *(undefined8 **)(param_1 + 0x330);
  local_41 = (byte)param_4 & 0x3f;
  bVar12 = param_7 & 0x3f;
  uVar7 = 1L << ((ulong)param_7 & 0x3f);
  lVar9 = 0;
  if (7 < uVar7) {
    lVar9 = uVar7 - 8;
  }
  uVar10 = -1L << ((ulong)param_7 & 0x3f);
  uVar7 = -1L << (param_4 & 0x3f);
  uVar11 = ~uVar7;
  param_3 = (((lVar9 - uVar10) + 0x3f & uVar10) + uVar11 + param_6 & uVar7) + param_3;
  local_40 = (undefined8 *)param_6;
  local_80 = param_1;
  local_60 = unaff_retaddr;
  local_50 = param_2;
  local_34 = bVar12;
  if (param_3 == 0) {
    puVar8 = (undefined8 *)0xfffffffffffffff8;
  }
  else {
    local_78 = param_5;
    local_70 = uVar7;
    puVar8 = (undefined8 *)(*(code *)*local_58)(local_68,param_3,3);
    uVar7 = local_70;
    param_5 = local_78;
    if (puVar8 == (undefined8 *)0x0) {
      (*param_8)(local_78,local_50);
      return (undefined8 *)0x0;
    }
  }
  puVar8[1] = FUN_011ded40;
  puVar8[2] = param_8;
  puVar8[3] = 0;
  *(byte *)(puVar8 + 7) = bVar12;
  puVar8[5] = (((long)puVar8 + ~uVar10 + 0x40 & uVar10) + uVar11 + param_6 & uVar7) - (long)puVar8;
  puVar8[6] = param_3;
  uVar7 = -1L << ((ulong)param_7 & 0x3f);
  lVar9 = (long)local_40;
  local_40 = puVar8;
  FUN_011f4580(~(uVar7 - (long)(puVar8 + 8)) & uVar7,param_5,lVar9);
  lVar9 = local_80;
  LOCK();
  iVar6 = *(int *)(local_80 + 0x338);
  bVar13 = iVar6 == 0;
  if (bVar13) {
    *(int *)(local_80 + 0x338) = 1;
    iVar6 = 0;
  }
  UNLOCK();
  local_34 = !bVar13;
  piVar1 = (int *)(local_80 + 0x338);
  uVar7 = (ulong)!bVar13;
  if (!bVar13) {
    if (iVar6 == 2) {
      uVar7 = 0x11dec21;
      syscall();
    }
    LOCK();
    iVar6 = *piVar1;
    *piVar1 = 2;
    UNLOCK();
    while (iVar6 != 0) {
      uVar7 = 0x11dec49;
      syscall();
      LOCK();
      iVar6 = *piVar1;
      *piVar1 = 2;
      UNLOCK();
    }
  }
  uVar10 = *(ulong *)(local_80 + 0x280);
  if (uVar10 < *(ulong *)(local_80 + 0x270)) {
    *(ulong *)(local_80 + 0x280) = uVar10 + 1;
    if (*(ulong *)(local_80 + 0x260) >> 1 == uVar10) {
      LOCK();
      *(long *)(local_80 + 0x260) = *(long *)(local_80 + 0x260) + 2;
      UNLOCK();
      FUN_011dd860(&local_90,*(undefined8 *)(local_80 + 600),local_80,uVar7);
      if (local_88 != 0) {
        LOCK();
        plVar2 = (long *)(lVar9 + 0x260);
        lVar5 = *plVar2;
        *plVar2 = *plVar2 + -2;
        UNLOCK();
        if (lVar5 == 3) {
          LOCK();
          iVar6 = *(int *)(lVar9 + 0x268);
          *(int *)(lVar9 + 0x268) = 2;
          UNLOCK();
          if (iVar6 == 1) {
            syscall();
          }
        }
        *(ulong *)(lVar9 + 0x280) = uVar10;
        LOCK();
        iVar6 = *(int *)(lVar9 + 0x338);
        *(int *)(lVar9 + 0x338) = 0;
        UNLOCK();
        if (iVar6 == 2) {
          syscall();
        }
        if (local_40[6] != 0) {
          (*(code *)local_58[3])(local_68,local_40,local_40[6],3,local_60);
        }
        goto LAB_011deb7a;
      }
      LOCK();
      cVar3 = *(char *)(local_90 + 0x18);
      *(char *)(local_90 + 0x18) = '\x01';
      UNLOCK();
      if (cVar3 != '\0') {
        if (*(int *)(local_90 + 0x10) != 0) {
          do {
            syscall();
          } while (*(int *)(local_90 + 0x10) != 0);
        }
        syscall();
      }
    }
    *local_40 = *(undefined8 *)(lVar9 + 0x48);
    *(undefined8 **)(lVar9 + 0x48) = local_40;
    LOCK();
    iVar6 = *(int *)(lVar9 + 0x338);
    *(int *)(lVar9 + 0x338) = 0;
    UNLOCK();
    if (iVar6 == 2) {
      syscall();
    }
    iVar6 = *(int *)(lVar9 + 0x33c);
    if ((ushort)((uint)iVar6 >> 0x10) < (ushort)iVar6) {
      do {
        LOCK();
        iVar4 = *(int *)(lVar9 + 0x33c);
        bVar13 = iVar6 == iVar4;
        if (bVar13) {
          *(int *)(lVar9 + 0x33c) = iVar6 + 0x10000;
          iVar4 = iVar6;
        }
        iVar6 = iVar4;
        UNLOCK();
        if (bVar13) {
          LOCK();
          *(int *)(lVar9 + 0x340) = *(int *)(lVar9 + 0x340) + 1;
          UNLOCK();
          syscall();
          return local_40;
        }
      } while ((ushort)((uint)iVar6 >> 0x10) < (ushort)iVar6);
    }
  }
  else {
    LOCK();
    iVar6 = *piVar1;
    *piVar1 = 0;
    UNLOCK();
    if (iVar6 == 2) {
      syscall();
    }
    if (local_40[6] != 0) {
      (*(code *)local_58[3])(local_68,local_40,local_40[6],3,local_60);
    }
LAB_011deb7a:
    (*param_8)(param_5,local_50);
    local_40 = (undefined8 *)0x0;
  }
  return local_40;
}


// ---- FUN_011ded10 @ 011ded10

void FUN_011ded10(void)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + -0x40010);
  if (lVar1 != 0) {
    *(undefined8 *)(lVar1 + 8) = 7;
    *(undefined1 *)(lVar1 + 0x21c) = 1;
  }
  return;
}


// ---- FUN_011ded40 @ 011ded40

ulong FUN_011ded40(ulong param_1,ulong param_2)

{
  undefined8 uVar1;
  ulong uVar2;
  ulong uVar3;
  bool bVar4;
  
  *(ulong *)(param_2 + 8) = param_1;
  uVar3 = *(ulong *)(param_1 + 0x18);
  do {
    LOCK();
    uVar2 = *(ulong *)(param_1 + 0x18);
    bVar4 = uVar3 == uVar2;
    if (bVar4) {
      *(ulong *)(param_1 + 0x18) = uVar3 | param_2;
      uVar2 = uVar3;
    }
    UNLOCK();
    uVar3 = uVar2;
  } while (!bVar4);
  if (uVar2 == 3) {
    *(ulong *)(param_2 + 8) = param_1 | 6;
  }
  uVar3 = -1L << ((ulong)*(byte *)(param_1 + 0x38) & 0x3f);
  (**(code **)(param_1 + 0x10))
            (~((uVar3 - param_1) - 0x40) & uVar3,*(long *)(param_1 + 0x28) + param_1);
  uVar1 = *(undefined8 *)(param_2 + 8);
  *(undefined8 *)(param_2 + 8) = 0;
  LOCK();
  uVar3 = *(ulong *)(param_1 + 0x18);
  *(ulong *)(param_1 + 0x18) = (ulong)((~(uint)uVar1 & 7) != 0) * 4 - 2;
  UNLOCK();
  if ((uVar3 & 3) != 0) {
    LOCK();
    **(int **)(param_1 + 0x20) = **(int **)(param_1 + 0x20) + 1;
    UNLOCK();
    uVar3 = 0xca;
    syscall();
  }
  return uVar3;
}


// ---- FUN_011dedf0 @ 011dedf0

/* WARNING: Removing unreachable block (ram,0x011df0cd) */
/* WARNING: Removing unreachable block (ram,0x011df018) */
/* WARNING: Removing unreachable block (ram,0x011df1e8) */

undefined2 *
FUN_011dedf0(undefined2 *param_1,undefined8 param_2,int param_3,long param_4,long param_5,
            uint param_6)

{
  undefined4 *puVar1;
  undefined8 uVar2;
  undefined2 uVar3;
  ulong uVar4;
  undefined2 *puVar5;
  uint *puVar6;
  long lVar7;
  byte bVar8;
  ulong uVar9;
  undefined4 uVar10;
  undefined8 *puVar11;
  undefined4 uVar12;
  ulong uVar13;
  undefined2 uVar14;
  long lVar15;
  ulong *puVar16;
  long in_FS_OFFSET;
  bool bVar17;
  undefined2 local_1b60 [896];
  undefined8 local_1460;
  undefined4 auStack_1458 [2];
  long alStack_1450 [4];
  undefined8 auStack_1430 [57];
  uint local_1268 [898];
  undefined8 auStack_460 [128];
  long local_60;
  long local_58;
  long local_50;
  long local_48;
  undefined2 *local_40;
  long local_38;
  
  local_60 = param_5;
  if (param_5 == 0) {
    uVar3 = 0;
LAB_011df283:
    *param_1 = uVar3;
    *(long *)(param_1 + 4) = local_60;
    return param_1;
  }
  bVar8 = (byte)param_6;
  local_48 = (ulong)((param_6 & 1) << 0xb) + (ulong)(bVar8 & 2) * 2 +
             ((ulong)((bVar8 << 5 | bVar8 >> 3) & 0x81) | (ulong)((uint)(bVar8 & 0x10) << 0x19)) +
             0x4000;
  local_58 = param_4 + 0x20;
  local_50 = param_4 + 0x128;
  lVar15 = 0;
  local_40 = param_1;
LAB_011dee87:
  puVar5 = local_1b60;
  uVar9 = local_60 - lVar15;
  if (0x3f < uVar9) {
    uVar9 = 0x40;
  }
  local_38 = lVar15 * 0x28;
  puVar11 = (undefined8 *)(local_58 + local_38);
  uVar13 = 0;
  do {
    *(undefined8 *)((long)auStack_460 + uVar13) = puVar11[-3];
    *(undefined8 *)((long)auStack_460 + uVar13 + 8) = puVar11[-2];
    *(undefined2 **)((long)&local_1460 + uVar13 * 4) = puVar5;
    puVar1 = (undefined4 *)puVar11[-4];
    if ((*(byte *)(puVar1 + 7) & 1) == 0) {
      uVar14 = swap_bytes(*(undefined2 *)puVar1);
      uVar12 = *(undefined4 *)((long)puVar1 + 2);
      *(undefined8 *)(puVar5 + 4) = 0;
      uVar10 = 0x10;
      uVar3 = 2;
    }
    else {
      uVar14 = swap_bytes(*(undefined2 *)(puVar1 + 2));
      uVar12 = *puVar1;
      uVar10 = puVar1[1];
      uVar2 = *(undefined8 *)((long)puVar1 + 0x12);
      *(undefined8 *)(puVar5 + 4) = *(undefined8 *)((long)puVar1 + 10);
      *(undefined8 *)(puVar5 + 8) = uVar2;
      *(undefined4 *)(puVar5 + 0xc) = uVar10;
      uVar10 = 0x1c;
      uVar3 = 10;
    }
    *puVar5 = uVar3;
    puVar5[1] = uVar14;
    *(undefined4 *)(puVar5 + 2) = uVar12;
    auStack_1458[uVar13] = uVar10;
    *(ulong *)((long)alStack_1450 + uVar13 * 4) = (long)auStack_460 + uVar13;
    *(undefined8 *)((long)auStack_1430 + (uVar13 - 6) * 4) = 1;
    *(undefined8 *)((long)auStack_1430 + (uVar13 - 4) * 4) = puVar11[-1];
    *(undefined8 *)((long)auStack_1430 + (uVar13 - 2) * 4) = *puVar11;
    *(undefined4 *)((long)auStack_1430 + uVar13 * 4) = 0;
    uVar13 = uVar13 + 0x10;
    puVar5 = puVar5 + 0xe;
    puVar11 = puVar11 + 5;
  } while ((uint)((int)uVar9 << 4) != uVar13);
  lVar7 = *(long *)(in_FS_OFFSET + -0x40010);
  param_1 = local_40;
  if (lVar7 != 0) {
    if ((*(byte *)(lVar7 + 0x21c) & 1) == 0) {
      uVar13 = *(ulong *)(lVar7 + 8);
      do {
        LOCK();
        uVar4 = *(ulong *)(lVar7 + 8);
        bVar17 = uVar13 == uVar4;
        if (bVar17) {
          *(ulong *)(lVar7 + 8) = uVar13 | 3;
          uVar4 = uVar13;
        }
        UNLOCK();
        uVar13 = uVar4;
      } while (!bVar17);
      if ((uVar4 & 7) != 0) {
        if (((uint)uVar4 & 7) == 7) goto LAB_011defef;
        uVar3 = 0x11;
        local_60 = lVar15;
        goto LAB_011df283;
      }
    }
    else {
LAB_011defef:
      lVar7 = 0;
    }
    if (lVar7 != 0) {
      syscall();
                    /* WARNING: Could not recover jumptable at 0x011df047. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      puVar5 = (undefined2 *)(*(code *)PTR_LAB_0100bbd0)((long)param_3,&local_1460,uVar9);
      return puVar5;
    }
  }
  syscall();
                    /* WARNING: Could not find normalized switch variable to match jumptable */
  switch(switchD_011df0ae::switchdataD_0100bf68) {
  case (undefined *)0x0:
    break;
  default:
                    /* WARNING: This code block may not be properly labeled as switch case */
    uVar3 = 4;
    local_60 = lVar15;
    goto LAB_011df283;
  case (undefined *)0xc:
  case (undefined *)0x69:
                    /* WARNING: This code block may not be properly labeled as switch case */
    uVar3 = 2;
    local_60 = lVar15;
    goto LAB_011df283;
  case (undefined *)0xd:
                    /* WARNING: This code block may not be properly labeled as switch case */
    uVar3 = 10;
    local_60 = lVar15;
    goto LAB_011df283;
  case (undefined *)0x20:
  case (undefined *)0x6b:
                    /* WARNING: This code block may not be properly labeled as switch case */
    uVar3 = 0x23;
    local_60 = lVar15;
    goto LAB_011df283;
  case (undefined *)0x5a:
                    /* WARNING: This code block may not be properly labeled as switch case */
    uVar3 = 0x26;
    local_60 = lVar15;
    goto LAB_011df283;
  case (undefined *)0x61:
                    /* WARNING: This code block may not be properly labeled as switch case */
    uVar3 = 0x50;
    local_60 = lVar15;
    goto LAB_011df283;
  case (undefined *)0x64:
                    /* WARNING: This code block may not be properly labeled as switch case */
    uVar3 = 0x27;
    local_60 = lVar15;
    goto LAB_011df283;
  case (undefined *)0x65:
                    /* WARNING: This code block may not be properly labeled as switch case */
    uVar3 = 0x5c;
    local_60 = lVar15;
    goto LAB_011df283;
  case (undefined *)0x68:
                    /* WARNING: This code block may not be properly labeled as switch case */
    uVar3 = 0x21;
    local_60 = lVar15;
    goto LAB_011df283;
  case (undefined *)0x71:
                    /* WARNING: This code block may not be properly labeled as switch case */
    uVar3 = 0x5b;
    local_60 = lVar15;
    goto LAB_011df283;
  case (undefined *)0x72:
                    /* WARNING: This code block may not be properly labeled as switch case */
    uVar3 = 0x5d;
    local_60 = lVar15;
    goto LAB_011df283;
  }
                    /* WARNING: This code block may not be properly labeled as switch case */
  puVar16 = (ulong *)(local_50 + local_38);
  puVar6 = local_1268;
  lVar7 = 0;
  do {
    puVar16[-0x23] = (ulong)puVar6[-0x70];
    puVar16[-0x1e] = (ulong)puVar6[-0x60];
    puVar16[-0x19] = (ulong)puVar6[-0x50];
    puVar16[-0x14] = (ulong)puVar6[-0x40];
    puVar16[-0xf] = (ulong)puVar6[-0x30];
    puVar16[-10] = (ulong)puVar6[-0x20];
    puVar16[-5] = (ulong)puVar6[-0x10];
    *puVar16 = (ulong)*puVar6;
    lVar7 = lVar7 + 8;
    puVar16 = puVar16 + 0x28;
    puVar6 = puVar6 + 0x80;
  } while (lVar7 != 0x130);
  puVar6 = (uint *)&stack0x000037d8;
  lVar7 = 0;
  do {
    *(ulong *)(local_38 + param_4 + 0x2f90 + lVar7) = (ulong)*puVar6;
    puVar6 = puVar6 + 0x10;
    lVar7 = lVar7 + 0x28;
  } while (lVar7 != 0x78);
  lVar15 = lVar15 + 0x133;
  uVar3 = 0;
  if (local_60 == lVar15) goto LAB_011df283;
  goto LAB_011dee87;
}


// ---- FUN_011df2a0 @ 011df2a0

/* WARNING: Removing unreachable block (ram,0x011df7a9) */
/* WARNING: Removing unreachable block (ram,0x011df72c) */
/* WARNING: Removing unreachable block (ram,0x011df732) */
/* WARNING: Removing unreachable block (ram,0x011df6ad) */
/* WARNING: Removing unreachable block (ram,0x011df6c0) */
/* WARNING: Removing unreachable block (ram,0x011df6c7) */
/* WARNING: Removing unreachable block (ram,0x011df6cf) */
/* WARNING: Removing unreachable block (ram,0x011df73d) */
/* WARNING: Removing unreachable block (ram,0x011df88e) */
/* WARNING: Removing unreachable block (ram,0x011df8c1) */
/* WARNING: Removing unreachable block (ram,0x011df8b0) */
/* WARNING: Removing unreachable block (ram,0x011df86c) */
/* WARNING: Removing unreachable block (ram,0x011df85b) */
/* WARNING: Removing unreachable block (ram,0x011df744) */
/* WARNING: Recovered jumptable eliminated as dead code */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1  [16]
FUN_011df2a0(undefined8 *param_1,undefined8 param_2,ulong param_3,ulong param_4,long param_5,
            long param_6,long param_7,ulong param_8)

{
  undefined1 uVar1;
  long lVar2;
  ulong *puVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  long lVar8;
  undefined1 *puVar9;
  long in_FS_OFFSET;
  bool bVar10;
  undefined1 auVar11 [16];
  undefined1 local_130 [64];
  ulong local_f0 [17];
  undefined4 local_68;
  ulong *local_60;
  long local_58;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined1 auStack_48 [12];
  uint local_34;
  
  local_f0[0x10] = 0;
  local_68 = 0;
  local_60 = local_f0;
  local_58 = 0;
  uStack_50 = 0;
  uStack_4c = 0;
  auStack_48._8_4_ = 0;
  auStack_48._0_8_ = SUB128(ZEXT812(0),4);
  if (param_5 == 0) {
    lVar8 = 0;
    if (param_7 != 1) goto LAB_011df31c;
LAB_011df397:
    if (param_8 != 0) {
      lVar2 = (param_7 + -1) * 0x10;
      puVar9 = *(undefined1 **)(param_6 + lVar2);
      uVar4 = *(ulong *)(param_6 + 8 + lVar2);
      if (param_8 == 1) {
        lVar2 = lVar8;
        if (uVar4 != 0) {
LAB_011df607:
          local_f0[lVar2 * 2] = (ulong)puVar9;
          local_f0[lVar2 * 2 + 1] = uVar4;
        }
      }
      else if (uVar4 != 0) {
        if (uVar4 == 1) {
          local_34 = (uint)param_3;
          uVar4 = 0x40;
          if (param_8 < 0x40) {
            uVar4 = param_8;
          }
          uVar1 = *puVar9;
          puVar9 = local_130;
          FUN_011f4160(puVar9,uVar1,uVar4);
          local_f0[lVar8 * 2] = (ulong)puVar9;
          local_f0[lVar8 * 2 + 1] = uVar4;
          lVar2 = lVar8 + 1;
          param_8 = param_8 - uVar4;
          if ((0x40 < param_8) && (lVar2 != 8)) {
            puVar3 = local_f0 + lVar8 * 2 + 3;
            lVar8 = lVar2;
            do {
              puVar3[-1] = (ulong)local_130;
              *puVar3 = 0x40;
              lVar2 = lVar8 + 1;
              param_8 = param_8 - 0x40;
              if (param_8 < 0x41) break;
              puVar3 = puVar3 + 2;
              bVar10 = lVar8 != 7;
              lVar8 = lVar2;
            } while (bVar10);
          }
          param_3 = (ulong)local_34;
          if ((param_8 != 0) && (lVar2 != 8)) {
            uVar4 = 0x40;
            if (param_8 < 0x40) {
              uVar4 = param_8;
            }
            goto LAB_011df607;
          }
        }
        else {
          uVar6 = 8U - lVar8;
          if (param_8 < 8U - lVar8) {
            uVar6 = param_8;
          }
          uVar5 = (ulong)((uint)uVar6 & 3);
          if (2 < uVar6 - 1) {
            uVar6 = uVar6 & 0xfffffffffffffffc;
            lVar2 = lVar8;
            do {
              if (lVar2 == 8) {
LAB_011df7a3:
                lVar8 = 8;
              }
              else {
                local_f0[lVar2 * 2] = (ulong)puVar9;
                local_f0[lVar2 * 2 + 1] = uVar4;
                lVar8 = lVar2 + 1;
                if (lVar8 == 8) goto LAB_011df7a3;
                local_f0[lVar8 * 2] = (ulong)puVar9;
                local_f0[lVar8 * 2 + 1] = uVar4;
                lVar7 = lVar2 + 2;
                if (lVar7 == 8) goto LAB_011df7a3;
                lVar8 = 8;
                local_f0[lVar7 * 2] = (ulong)puVar9;
                local_f0[lVar7 * 2 + 1] = uVar4;
                lVar7 = lVar2 + 3;
                if (lVar7 != 8) {
                  local_f0[lVar7 * 2] = (ulong)puVar9;
                  local_f0[lVar7 * 2 + 1] = uVar4;
                  lVar8 = lVar2 + 4;
                }
              }
              uVar6 = uVar6 - 4;
              lVar2 = lVar8;
            } while (uVar6 != 0);
          }
          for (; uVar5 != 0; uVar5 = uVar5 - 1) {
            lVar2 = 8;
            if (lVar8 != 8) {
              local_f0[lVar8 * 2] = (ulong)puVar9;
              local_f0[lVar8 * 2 + 1] = uVar4;
              lVar2 = lVar8 + 1;
            }
            lVar8 = lVar2;
          }
        }
      }
    }
  }
  else {
    local_58 = 1;
    lVar8 = 1;
    local_f0[0] = param_4;
    local_f0[1] = param_5;
    if (param_7 == 1) goto LAB_011df397;
LAB_011df31c:
    uVar4 = param_7 - 1;
    if (param_7 - 2U < 3) {
      uVar6 = 0;
    }
    else {
      puVar3 = (ulong *)(param_6 + 0x38);
      uVar6 = 0;
      do {
        uVar5 = puVar3[-6];
        if ((uVar5 != 0) && (lVar8 != 8)) {
          local_f0[lVar8 * 2] = puVar3[-7];
          local_f0[lVar8 * 2 + 1] = uVar5;
          lVar8 = lVar8 + 1;
          local_58 = lVar8;
        }
        uVar5 = puVar3[-4];
        if ((uVar5 != 0) && (lVar8 != 8)) {
          local_f0[lVar8 * 2] = puVar3[-5];
          local_f0[lVar8 * 2 + 1] = uVar5;
          lVar8 = lVar8 + 1;
          local_58 = lVar8;
        }
        uVar5 = puVar3[-2];
        if ((uVar5 != 0) && (lVar8 != 8)) {
          local_f0[lVar8 * 2] = puVar3[-3];
          local_f0[lVar8 * 2 + 1] = uVar5;
          lVar8 = lVar8 + 1;
          local_58 = lVar8;
        }
        uVar5 = *puVar3;
        if ((uVar5 != 0) && (lVar8 != 8)) {
          local_f0[lVar8 * 2] = puVar3[-1];
          local_f0[lVar8 * 2 + 1] = uVar5;
          lVar8 = lVar8 + 1;
          local_58 = lVar8;
        }
        uVar6 = uVar6 + 4;
        puVar3 = puVar3 + 8;
      } while ((uVar4 & 0xfffffffffffffffc) != uVar6);
    }
    if ((uVar4 & 3) != 0) {
      lVar2 = uVar6 * 0x10 + param_6;
      uVar6 = 0;
      do {
        uVar5 = *(ulong *)(lVar2 + 8 + uVar6);
        if ((uVar5 != 0) && (lVar8 != 8)) {
          local_f0[lVar8 * 2] = *(ulong *)(lVar2 + uVar6);
          local_f0[lVar8 * 2 + 1] = uVar5;
          lVar8 = lVar8 + 1;
          local_58 = lVar8;
        }
        uVar6 = uVar6 + 0x10;
      } while (((uint)uVar4 & 3) << 4 != uVar6);
    }
    if (lVar8 != 8) goto LAB_011df397;
  }
  lVar8 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar8 == 0) || ((*(byte *)(lVar8 + 0x21c) & 1) != 0)) {
LAB_011df66b:
    lVar8 = 0;
  }
  else {
    uVar4 = *(ulong *)(lVar8 + 8);
    do {
      LOCK();
      uVar6 = *(ulong *)(lVar8 + 8);
      bVar10 = uVar4 == uVar6;
      if (bVar10) {
        *(ulong *)(lVar8 + 8) = uVar4 | 3;
        uVar6 = uVar4;
      }
      UNLOCK();
      uVar4 = uVar6;
    } while (!bVar10);
    if ((uVar6 & 7) != 0) {
      if (((uint)uVar6 & 7) == 6) {
        *(undefined2 *)(param_1 + 1) = 0x11;
        goto LAB_011df74a;
      }
      goto LAB_011df66b;
    }
  }
  if (lVar8 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar8 + 8) = *(ulong *)(lVar8 + 8) ^ 3;
    UNLOCK();
  }
  param_3 = 0x4000;
  *(undefined2 *)(param_1 + 1) = 0;
  *param_1 = 0x2e;
LAB_011df74a:
  auVar11._8_8_ = param_3;
  auVar11._0_8_ = param_1;
  return auVar11;
}


// ---- FUN_011df8f0 @ 011df8f0

/* WARNING: Removing unreachable block (ram,0x011dfa40) */
/* WARNING: Removing unreachable block (ram,0x011dfa46) */
/* WARNING: Removing unreachable block (ram,0x011df9bd) */
/* WARNING: Removing unreachable block (ram,0x011df9d0) */
/* WARNING: Removing unreachable block (ram,0x011df9d7) */
/* WARNING: Removing unreachable block (ram,0x011df9df) */
/* WARNING: Removing unreachable block (ram,0x011dfa51) */
/* WARNING: Removing unreachable block (ram,0x011dfa88) */
/* WARNING: Removing unreachable block (ram,0x011dfaac) */
/* WARNING: Removing unreachable block (ram,0x011dfa9a) */
/* WARNING: Removing unreachable block (ram,0x011dfa76) */
/* WARNING: Removing unreachable block (ram,0x011dfa64) */
/* WARNING: Removing unreachable block (ram,0x011dfa58) */
/* WARNING: Recovered jumptable eliminated as dead code */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1  [16]
FUN_011df8f0(undefined8 *param_1,undefined8 param_2,undefined8 param_3,long param_4,long param_5)

{
  ulong uVar1;
  ulong uVar2;
  long *plVar3;
  long lVar4;
  long lVar5;
  long in_FS_OFFSET;
  bool bVar6;
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  long local_88 [16];
  
  plVar3 = (long *)(param_4 + 8);
  lVar4 = 0;
  do {
    if (lVar4 == 8) {
      lVar4 = 8;
      break;
    }
    lVar5 = *plVar3;
    if (lVar5 != 0) {
      local_88[lVar4 * 2] = plVar3[-1];
      local_88[lVar4 * 2 + 1] = lVar5;
      lVar4 = lVar4 + 1;
    }
    plVar3 = plVar3 + 2;
    param_5 = param_5 + -1;
  } while (param_5 != 0);
  lVar5 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar5 != 0) && ((*(byte *)(lVar5 + 0x21c) & 1) == 0)) {
    uVar1 = *(ulong *)(lVar5 + 8);
    do {
      LOCK();
      uVar2 = *(ulong *)(lVar5 + 8);
      bVar6 = uVar1 == uVar2;
      if (bVar6) {
        *(ulong *)(lVar5 + 8) = uVar1 | 3;
        uVar2 = uVar1;
      }
      UNLOCK();
      uVar1 = uVar2;
    } while (!bVar6);
    if ((uVar2 & 7) == 0) goto LAB_011df98e;
    if (((uint)uVar2 & 7) == 6) {
      *(undefined2 *)(param_1 + 1) = 0x11;
      auVar7._8_8_ = lVar4;
      auVar7._0_8_ = param_1;
      return auVar7;
    }
  }
  lVar5 = 0;
LAB_011df98e:
  if (lVar5 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar5 + 8) = *(ulong *)(lVar5 + 8) ^ 3;
    UNLOCK();
  }
  *(undefined2 *)(param_1 + 1) = 0;
  *param_1 = 0x13;
  auVar8._8_8_ = lVar4;
  auVar8._0_8_ = param_1;
  return auVar8;
}


// ---- FUN_011dfac0 @ 011dfac0

/* WARNING: Removing unreachable block (ram,0x011dfb5e) */
/* WARNING: Removing unreachable block (ram,0x011dfb70) */
/* WARNING: Removing unreachable block (ram,0x011dfb77) */
/* WARNING: Removing unreachable block (ram,0x011dfb7f) */
/* WARNING: Removing unreachable block (ram,0x011dfb87) */
/* WARNING: Removing unreachable block (ram,0x011dfbc4) */
/* WARNING: Removing unreachable block (ram,0x011dfbca) */
/* WARNING: Removing unreachable block (ram,0x011dfbe3) */
/* WARNING: Removing unreachable block (ram,0x011dfbe6) */

undefined8 FUN_011dfac0(void)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  long in_FS_OFFSET;
  bool bVar4;
  
  lVar3 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar3 != 0) && ((*(byte *)(lVar3 + 0x21c) & 1) == 0)) {
    uVar1 = *(ulong *)(lVar3 + 8);
    do {
      LOCK();
      uVar2 = *(ulong *)(lVar3 + 8);
      bVar4 = uVar1 == uVar2;
      if (bVar4) {
        *(ulong *)(lVar3 + 8) = uVar1 | 3;
        uVar2 = uVar1;
      }
      UNLOCK();
      uVar1 = uVar2;
    } while (!bVar4);
    if ((uVar2 & 7) == 0) goto LAB_011dfb28;
    if (((uint)uVar2 & 7) == 6) {
      return 0x11;
    }
  }
  lVar3 = 0;
LAB_011dfb28:
  if (lVar3 == 0) {
    syscall();
    return 0;
  }
  syscall();
  LOCK();
  *(ulong *)(lVar3 + 8) = *(ulong *)(lVar3 + 8) ^ 3;
  UNLOCK();
  return 0;
}


// ---- FUN_011dfbf0 @ 011dfbf0

/* WARNING: Removing unreachable block (ram,0x011dfd6b) */
/* WARNING: Removing unreachable block (ram,0x011dfd89) */
/* WARNING: Removing unreachable block (ram,0x011dfdd2) */
/* WARNING: Removing unreachable block (ram,0x011dfd8e) */
/* WARNING: Removing unreachable block (ram,0x011dfd93) */
/* WARNING: Removing unreachable block (ram,0x011dfce0) */
/* WARNING: Removing unreachable block (ram,0x011dfcf0) */
/* WARNING: Removing unreachable block (ram,0x011dfcf7) */
/* WARNING: Removing unreachable block (ram,0x011dfcff) */
/* WARNING: Removing unreachable block (ram,0x011dfd7c) */
/* WARNING: Removing unreachable block (ram,0x011dfdb7) */
/* WARNING: Removing unreachable block (ram,0x011dfdc0) */
/* WARNING: Removing unreachable block (ram,0x011dfdc9) */
/* WARNING: Removing unreachable block (ram,0x011dfd9c) */
/* WARNING: Removing unreachable block (ram,0x011dfdae) */
/* WARNING: Recovered jumptable eliminated as dead code */

undefined8 * FUN_011dfbf0(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  ulong uVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long in_FS_OFFSET;
  bool bVar5;
  undefined1 local_94 [108];
  undefined4 local_28;
  short local_24;
  
  FUN_011ca0b0(&local_28,1,&DAT_0100f640);
  if (local_24 != 0) {
    if (local_24 == 0x52) {
      uVar3 = 0x5000000000;
    }
    else {
      if (local_24 != 0x54) {
        *(short *)((long)param_1 + 4) = local_24;
        return param_1;
      }
      uVar3 = 0x400000000;
    }
    *param_1 = uVar3;
    return param_1;
  }
  lVar4 = param_3[1];
  FUN_011f4580(local_94,*param_3,lVar4);
  if (lVar4 == 0x6c) {
    lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
  }
  else {
    local_94[lVar4] = 0;
    lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
  }
  if ((lVar4 != 0) && ((*(byte *)(lVar4 + 0x21c) & 1) == 0)) {
    uVar1 = *(ulong *)(lVar4 + 8);
    do {
      LOCK();
      uVar2 = *(ulong *)(lVar4 + 8);
      bVar5 = uVar1 == uVar2;
      if (bVar5) {
        *(ulong *)(lVar4 + 8) = uVar1 | 3;
        uVar2 = uVar1;
      }
      UNLOCK();
      uVar1 = uVar2;
    } while (!bVar5);
    if ((uVar2 & 7) == 0) goto LAB_011dfc9e;
    if (((uint)uVar2 & 7) != 7) {
      syscall();
      *(undefined2 *)((long)param_1 + 4) = 0x11;
      return param_1;
    }
  }
  lVar4 = 0;
LAB_011dfc9e:
  if (lVar4 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar4 + 8) = *(ulong *)(lVar4 + 8) ^ 3;
    UNLOCK();
  }
  *(undefined2 *)((long)param_1 + 4) = 0;
  *(undefined4 *)param_1 = local_28;
  return param_1;
}


// ---- FUN_011dfe30 @ 011dfe30

/* WARNING: Removing unreachable block (ram,0x011e00b1) */
/* WARNING: Removing unreachable block (ram,0x011e00c0) */
/* WARNING: Removing unreachable block (ram,0x011e00c7) */
/* WARNING: Removing unreachable block (ram,0x011e00cf) */
/* WARNING: Removing unreachable block (ram,0x011e00d7) */
/* WARNING: Removing unreachable block (ram,0x011e01e1) */
/* WARNING: Removing unreachable block (ram,0x011e01e7) */
/* WARNING: Removing unreachable block (ram,0x011dffc1) */

int * FUN_011dfe30(int *param_1,undefined8 param_2,undefined4 *param_3,long param_4)

{
  int *piVar1;
  ulong uVar2;
  ulong uVar3;
  undefined2 uVar4;
  long lVar5;
  long in_FS_OFFSET;
  bool bVar6;
  undefined8 local_68;
  undefined8 uStack_60;
  undefined8 local_50;
  undefined2 local_48;
  byte local_46;
  int local_44;
  short local_40;
  short local_3c;
  undefined2 local_3a;
  undefined4 local_38;
  undefined8 local_34;
  undefined8 uStack_2c;
  undefined4 local_24;
  undefined4 local_20;
  undefined1 local_1c;
  
  if ((*(byte *)(param_4 + 0x20) & 3) != 0) {
                    /* WARNING: Subroutine does not return */
    FUN_011f3790("TODO implement netConnectIpPosix with timeout",0x2d);
  }
  local_50 = *(undefined8 *)(param_4 + 0x30);
  local_48 = 0;
  local_46 = *(byte *)(param_4 + 0x38) & 7;
  FUN_011ca0b0(&local_44,(*(byte *)(param_3 + 7) & 1) * '\b' + '\x02',&local_50);
  if (local_40 != 0) {
    *(short *)(param_1 + 9) = local_40;
    return param_1;
  }
  if ((*(byte *)(param_3 + 7) & 1) == 0) {
    local_3a = swap_bytes(*(undefined2 *)param_3);
    local_38 = *(undefined4 *)((long)param_3 + 2);
    local_34 = 0;
    local_20 = 0x10;
    local_3c = 2;
  }
  else {
    local_3a = swap_bytes(*(undefined2 *)(param_3 + 2));
    local_38 = *param_3;
    local_24 = param_3[1];
    local_34 = *(undefined8 *)((long)param_3 + 10);
    uStack_2c = *(undefined8 *)((long)param_3 + 0x12);
    local_20 = 0x1c;
    local_3c = 10;
  }
  lVar5 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar5 == 0) || ((*(byte *)(lVar5 + 0x21c) & 1) != 0)) {
LAB_011dff2b:
    lVar5 = 0;
  }
  else {
    uVar3 = *(ulong *)(lVar5 + 8);
    do {
      LOCK();
      uVar2 = *(ulong *)(lVar5 + 8);
      bVar6 = uVar3 == uVar2;
      if (bVar6) {
        *(ulong *)(lVar5 + 8) = uVar3 | 3;
        uVar2 = uVar3;
      }
      UNLOCK();
      uVar3 = uVar2;
    } while (!bVar6);
    if ((uVar2 & 7) != 0) {
      if (((uint)uVar2 & 7) != 7) {
        uVar4 = 0x11;
        goto LAB_011dffcb;
      }
      goto LAB_011dff2b;
    }
  }
  if (lVar5 != 0) {
    syscall();
                    /* WARNING: Could not recover jumptable at 0x011dff59. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    piVar1 = (int *)(*(code *)PTR_LAB_0100cac0)((long)local_44,&local_3c,local_20);
    return piVar1;
  }
  syscall();
                    /* WARNING: Could not find normalized switch variable to match jumptable */
  switch(switchD_011dffb4::switchdataD_0100ce60) {
  case (undefined *)0x0:
                    /* WARNING: This code block may not be properly labeled as switch case */
    lVar5 = *(long *)(in_FS_OFFSET + -0x40010);
    if ((lVar5 != 0) && ((*(byte *)(lVar5 + 0x21c) & 1) == 0)) {
      uVar3 = *(ulong *)(lVar5 + 8);
      do {
        LOCK();
        uVar2 = *(ulong *)(lVar5 + 8);
        bVar6 = uVar3 == uVar2;
        if (bVar6) {
          *(ulong *)(lVar5 + 8) = uVar3 | 3;
          uVar2 = uVar3;
        }
        UNLOCK();
        uVar3 = uVar2;
      } while (!bVar6);
      if ((uVar2 & 7) == 0) goto LAB_011e0076;
      if (((uint)uVar2 & 7) == 6) {
        syscall();
        *(undefined2 *)(param_1 + 9) = 0x11;
        return param_1;
      }
    }
    lVar5 = 0;
LAB_011e0076:
    if (lVar5 == 0) {
      syscall();
    }
    else {
      syscall();
      LOCK();
      *(ulong *)(lVar5 + 8) = *(ulong *)(lVar5 + 8) ^ 3;
      UNLOCK();
    }
    uVar4 = 0;
    *(undefined2 *)(param_1 + 9) = 0;
    *param_1 = local_44;
    if (local_3c == 10) {
      local_1c = 1;
      uVar4 = swap_bytes(local_3a);
      uVar3 = CONCAT44(local_24,local_38);
      local_68 = local_34;
      uStack_60 = uStack_2c;
    }
    else if (local_3c == 2) {
      local_1c = 0;
      uVar4 = swap_bytes(local_3a);
      uVar3 = (ulong)CONCAT42(local_38,uVar4);
    }
    else {
      local_1c = 0;
      uVar3 = 0x100007f0000;
    }
    *(ulong *)(param_1 + 1) = uVar3;
    *(undefined2 *)(param_1 + 3) = uVar4;
    *(undefined8 *)((long)param_1 + 0xe) = local_68;
    *(undefined8 *)((long)param_1 + 0x16) = uStack_60;
    *(undefined1 *)(param_1 + 8) = local_1c;
    return param_1;
  default:
                    /* WARNING: This code block may not be properly labeled as switch case */
    uVar4 = 4;
    break;
  case (undefined *)0x64:
                    /* WARNING: This code block may not be properly labeled as switch case */
    uVar4 = 0x27;
    break;
  case (undefined *)0x68:
                    /* WARNING: This code block may not be properly labeled as switch case */
    uVar4 = 0x21;
    break;
  case (undefined *)0x6e:
                    /* WARNING: This code block may not be properly labeled as switch case */
    uVar4 = 0x29;
    break;
  case (undefined *)0x72:
                    /* WARNING: This code block may not be properly labeled as switch case */
    uVar4 = 0x59;
  }
LAB_011dffcb:
  syscall();
  *(undefined2 *)(param_1 + 9) = uVar4;
  return param_1;
}


// ---- FUN_011e0270 @ 011e0270

/* WARNING: Removing unreachable block (ram,0x011e06a1) */
/* WARNING: Removing unreachable block (ram,0x011e06a7) */
/* WARNING: Removing unreachable block (ram,0x011e04b1) */
/* WARNING: Removing unreachable block (ram,0x011e04c0) */
/* WARNING: Removing unreachable block (ram,0x011e04c7) */
/* WARNING: Removing unreachable block (ram,0x011e04cf) */
/* WARNING: Removing unreachable block (ram,0x011e04d7) */
/* WARNING: Removing unreachable block (ram,0x011e060d) */
/* WARNING: Removing unreachable block (ram,0x011e0620) */
/* WARNING: Removing unreachable block (ram,0x011e0627) */
/* WARNING: Removing unreachable block (ram,0x011e062f) */
/* WARNING: Removing unreachable block (ram,0x011e0637) */
/* WARNING: Removing unreachable block (ram,0x011e06c7) */
/* WARNING: Removing unreachable block (ram,0x011e06cd) */
/* WARNING: Removing unreachable block (ram,0x011e04f8) */
/* WARNING: Removing unreachable block (ram,0x011e04e0) */
/* WARNING: Removing unreachable block (ram,0x011e04ee) */
/* WARNING: Removing unreachable block (ram,0x011e051d) */
/* WARNING: Removing unreachable block (ram,0x011e04f3) */
/* WARNING: Removing unreachable block (ram,0x011e037d) */
/* WARNING: Removing unreachable block (ram,0x011e0390) */
/* WARNING: Removing unreachable block (ram,0x011e0397) */
/* WARNING: Removing unreachable block (ram,0x011e039f) */
/* WARNING: Removing unreachable block (ram,0x011e0501) */
/* WARNING: Removing unreachable block (ram,0x011e0506) */
/* WARNING: Removing unreachable block (ram,0x011e050b) */
/* WARNING: Removing unreachable block (ram,0x011e0514) */
/* WARNING: Removing unreachable block (ram,0x011e0526) */

undefined4 * FUN_011e0270(undefined4 *param_1,undefined8 param_2,undefined4 *param_3,long param_4)

{
  byte bVar1;
  undefined2 uVar2;
  ulong uVar3;
  ulong uVar4;
  undefined2 uVar5;
  undefined4 uVar6;
  short sVar7;
  long lVar8;
  long in_FS_OFFSET;
  bool bVar9;
  undefined8 local_68;
  undefined8 uStack_60;
  undefined4 local_50;
  short local_4c;
  undefined8 local_40;
  undefined8 uStack_38;
  undefined4 local_30;
  undefined1 local_24;
  
  bVar1 = *(byte *)(param_4 + 9);
  FUN_011ca0b0(&local_50,(*(byte *)(param_3 + 7) & 1) * '\b' + '\x02',param_4);
  if (local_4c != 0) {
    *(short *)(param_1 + 9) = local_4c;
    return param_1;
  }
  if ((*(byte *)(param_3 + 7) & 1) == 0) {
    uVar2 = swap_bytes(*(undefined2 *)param_3);
    uVar6 = *(undefined4 *)((long)param_3 + 2);
    local_40 = 0;
    sVar7 = 2;
  }
  else {
    uVar2 = swap_bytes(*(undefined2 *)(param_3 + 2));
    uVar6 = *param_3;
    local_30 = param_3[1];
    local_40 = *(undefined8 *)((long)param_3 + 10);
    uStack_38 = *(undefined8 *)((long)param_3 + 0x12);
    sVar7 = 10;
  }
  lVar8 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar8 == 0) || ((*(byte *)(lVar8 + 0x21c) & 1) != 0)) {
LAB_011e034b:
    lVar8 = 0;
  }
  else {
    uVar4 = *(ulong *)(lVar8 + 8);
    do {
      LOCK();
      uVar3 = *(ulong *)(lVar8 + 8);
      bVar9 = uVar4 == uVar3;
      if (bVar9) {
        *(ulong *)(lVar8 + 8) = uVar4 | 3;
        uVar3 = uVar4;
      }
      UNLOCK();
      uVar4 = uVar3;
    } while (!bVar9);
    if ((uVar3 & 7) != 0) {
      if (((uint)uVar3 & 7) != 7) {
        syscall();
        goto LAB_011e03b2;
      }
      goto LAB_011e034b;
    }
  }
  if (lVar8 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar8 + 8) = *(ulong *)(lVar8 + 8) ^ 3;
    UNLOCK();
  }
  if ((bVar1 & 1) != 0) {
    lVar8 = *(long *)(in_FS_OFFSET + -0x40010);
    if ((lVar8 == 0) || ((*(byte *)(lVar8 + 0x21c) & 1) != 0)) {
LAB_011e0463:
      lVar8 = 0;
    }
    else {
      uVar4 = *(ulong *)(lVar8 + 8);
      do {
        LOCK();
        uVar3 = *(ulong *)(lVar8 + 8);
        bVar9 = uVar4 == uVar3;
        if (bVar9) {
          *(ulong *)(lVar8 + 8) = uVar4 | 3;
          uVar3 = uVar4;
        }
        UNLOCK();
        uVar4 = uVar3;
      } while (!bVar9);
      if ((uVar3 & 7) != 0) {
        if (((uint)uVar3 & 7) == 6) {
          syscall();
LAB_011e03b2:
          *(undefined2 *)(param_1 + 9) = 0x11;
          return param_1;
        }
        goto LAB_011e0463;
      }
    }
    if (lVar8 == 0) {
      syscall();
    }
    else {
      syscall();
      LOCK();
      *(ulong *)(lVar8 + 8) = *(ulong *)(lVar8 + 8) ^ 3;
      UNLOCK();
    }
  }
  lVar8 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar8 != 0) && ((*(byte *)(lVar8 + 0x21c) & 1) == 0)) {
    uVar4 = *(ulong *)(lVar8 + 8);
    do {
      LOCK();
      uVar3 = *(ulong *)(lVar8 + 8);
      bVar9 = uVar4 == uVar3;
      if (bVar9) {
        *(ulong *)(lVar8 + 8) = uVar4 | 3;
        uVar3 = uVar4;
      }
      UNLOCK();
      uVar4 = uVar3;
    } while (!bVar9);
    if ((uVar3 & 7) == 0) goto LAB_011e05d6;
    if (((uint)uVar3 & 7) == 6) {
      syscall();
      *(undefined2 *)(param_1 + 9) = 0x11;
      return param_1;
    }
  }
  lVar8 = 0;
LAB_011e05d6:
  if (lVar8 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar8 + 8) = *(ulong *)(lVar8 + 8) ^ 3;
    UNLOCK();
  }
  uVar5 = 0;
  *(undefined2 *)(param_1 + 9) = 0;
  *param_1 = local_50;
  if (sVar7 == 10) {
    local_24 = 1;
    uVar5 = swap_bytes(uVar2);
    uVar4 = CONCAT44(local_30,uVar6);
    local_68 = local_40;
    uStack_60 = uStack_38;
  }
  else if (sVar7 == 2) {
    local_24 = 0;
    uVar5 = swap_bytes(uVar2);
    uVar4 = (ulong)CONCAT42(uVar6,uVar5);
  }
  else {
    local_24 = 0;
    uVar4 = 0x100007f0000;
  }
  *(ulong *)(param_1 + 1) = uVar4;
  *(undefined2 *)(param_1 + 3) = uVar5;
  *(undefined8 *)((long)param_1 + 0xe) = local_68;
  *(undefined8 *)((long)param_1 + 0x16) = uStack_60;
  *(undefined1 *)(param_1 + 8) = local_24;
  return param_1;
}


// ---- FUN_011e0740 @ 011e0740

/* WARNING: Removing unreachable block (ram,0x011e0872) */
/* WARNING: Removing unreachable block (ram,0x011e0878) */
/* WARNING: Removing unreachable block (ram,0x011e07cd) */
/* WARNING: Removing unreachable block (ram,0x011e07e0) */
/* WARNING: Removing unreachable block (ram,0x011e07e7) */
/* WARNING: Removing unreachable block (ram,0x011e07ef) */
/* WARNING: Removing unreachable block (ram,0x011e0882) */
/* WARNING: Removing unreachable block (ram,0x011e0889) */

undefined1  [16] FUN_011e0740(undefined4 *param_1,undefined8 param_2,undefined8 param_3)

{
  ulong uVar1;
  ulong uVar2;
  undefined2 uVar3;
  undefined1 *puVar4;
  long lVar5;
  long in_FS_OFFSET;
  bool bVar6;
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined8 local_48;
  undefined8 uStack_40;
  short local_34;
  undefined2 local_32;
  uint local_30;
  undefined8 local_2c;
  undefined8 uStack_24;
  undefined4 local_1c;
  undefined1 local_18 [4];
  undefined1 local_14;
  
  lVar5 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar5 != 0) && ((*(byte *)(lVar5 + 0x21c) & 1) == 0)) {
    uVar2 = *(ulong *)(lVar5 + 8);
    do {
      LOCK();
      uVar1 = *(ulong *)(lVar5 + 8);
      bVar6 = uVar2 == uVar1;
      if (bVar6) {
        *(ulong *)(lVar5 + 8) = uVar2 | 3;
        uVar1 = uVar2;
      }
      UNLOCK();
      uVar2 = uVar1;
    } while (!bVar6);
    if ((uVar1 & 7) == 0) goto LAB_011e078e;
    if (((uint)uVar1 & 7) == 6) {
      *(undefined2 *)(param_1 + 9) = 0x11;
      auVar7._8_8_ = param_3;
      auVar7._0_8_ = param_1;
      return auVar7;
    }
  }
  lVar5 = 0;
LAB_011e078e:
  puVar4 = local_18;
  if (lVar5 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar5 + 8) = *(ulong *)(lVar5 + 8) ^ 3;
    UNLOCK();
  }
  uVar3 = 0;
  *(undefined2 *)(param_1 + 9) = 0;
  *param_1 = 0x120;
  if (local_34 == 10) {
    local_14 = 1;
    uVar3 = swap_bytes(local_32);
    puVar4 = (undefined1 *)(ulong)local_30;
    uVar2 = CONCAT44(local_1c,local_30);
    local_48 = local_2c;
    uStack_40 = uStack_24;
  }
  else if (local_34 == 2) {
    local_14 = 0;
    uVar3 = swap_bytes(local_32);
    uVar2 = (ulong)CONCAT42(local_30,uVar3);
  }
  else {
    local_14 = 0;
    uVar2 = 0x100007f0000;
  }
  *(ulong *)(param_1 + 1) = uVar2;
  *(undefined2 *)(param_1 + 3) = uVar3;
  *(undefined8 *)((long)param_1 + 0xe) = local_48;
  *(undefined8 *)((long)param_1 + 0x16) = uStack_40;
  *(undefined1 *)(param_1 + 8) = local_14;
  auVar8._8_8_ = puVar4;
  auVar8._0_8_ = param_1;
  return auVar8;
}


// ---- FUN_011e09b0 @ 011e09b0

/* WARNING: Removing unreachable block (ram,0x011e0c8e) */
/* WARNING: Removing unreachable block (ram,0x011e0c94) */
/* WARNING: Removing unreachable block (ram,0x011e0cbe) */
/* WARNING: Removing unreachable block (ram,0x011e0bd0) */
/* WARNING: Removing unreachable block (ram,0x011e0be0) */
/* WARNING: Removing unreachable block (ram,0x011e0be7) */
/* WARNING: Removing unreachable block (ram,0x011e0bef) */
/* WARNING: Removing unreachable block (ram,0x011e0bf7) */
/* WARNING: Removing unreachable block (ram,0x011e0ca6) */
/* WARNING: Removing unreachable block (ram,0x011e0cac) */
/* WARNING: Removing unreachable block (ram,0x011e0c74) */
/* WARNING: Removing unreachable block (ram,0x011e0c79) */
/* WARNING: Removing unreachable block (ram,0x011e0c7e) */
/* WARNING: Removing unreachable block (ram,0x011e0cc4) */
/* WARNING: Removing unreachable block (ram,0x011e0c09) */
/* WARNING: Removing unreachable block (ram,0x011e0ab0) */
/* WARNING: Removing unreachable block (ram,0x011e0ac0) */
/* WARNING: Removing unreachable block (ram,0x011e0ac7) */
/* WARNING: Removing unreachable block (ram,0x011e0acf) */
/* WARNING: Removing unreachable block (ram,0x011e0c1d) */
/* WARNING: Removing unreachable block (ram,0x011e0d1e) */
/* WARNING: Removing unreachable block (ram,0x011e0d27) */
/* WARNING: Removing unreachable block (ram,0x011e0cfa) */
/* WARNING: Removing unreachable block (ram,0x011e0cf1) */
/* WARNING: Removing unreachable block (ram,0x011e0cdf) */
/* WARNING: Removing unreachable block (ram,0x011e0d15) */
/* WARNING: Removing unreachable block (ram,0x011e0d0c) */
/* WARNING: Removing unreachable block (ram,0x011e0cd6) */
/* WARNING: Removing unreachable block (ram,0x011e0d03) */
/* WARNING: Removing unreachable block (ram,0x011e0ce8) */
/* WARNING: Removing unreachable block (ram,0x011e0c24) */
/* WARNING: Recovered jumptable eliminated as dead code */

undefined8 * FUN_011e09b0(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  ulong uVar1;
  ulong uVar2;
  undefined8 uVar3;
  long lVar4;
  long in_FS_OFFSET;
  bool bVar5;
  undefined1 local_9c [108];
  undefined4 local_30;
  short local_2c;
  
  FUN_011ca0b0(&local_30,1,&DAT_0100f640);
  if (local_2c != 0) {
    switch(local_2c) {
    case 0x51:
    case 0x52:
    case 0x53:
      uVar3 = 0x5000000000;
      break;
    case 0x54:
      uVar3 = 0x400000000;
      break;
    default:
      *(short *)((long)param_1 + 4) = local_2c;
      return param_1;
    }
    *param_1 = uVar3;
    return param_1;
  }
  lVar4 = param_3[1];
  FUN_011f4580(local_9c,*param_3,lVar4);
  if (lVar4 == 0x6c) {
    lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
    if (lVar4 != 0) goto LAB_011e0a34;
LAB_011e0a6b:
    lVar4 = 0;
  }
  else {
    local_9c[lVar4] = 0;
    lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
    if (lVar4 == 0) goto LAB_011e0a6b;
LAB_011e0a34:
    if ((*(byte *)(lVar4 + 0x21c) & 1) != 0) goto LAB_011e0a6b;
    uVar1 = *(ulong *)(lVar4 + 8);
    do {
      LOCK();
      uVar2 = *(ulong *)(lVar4 + 8);
      bVar5 = uVar1 == uVar2;
      if (bVar5) {
        *(ulong *)(lVar4 + 8) = uVar1 | 3;
        uVar2 = uVar1;
      }
      UNLOCK();
      uVar1 = uVar2;
    } while (!bVar5);
    if ((uVar2 & 7) != 0) {
      if (((uint)uVar2 & 7) != 7) {
        syscall();
        *(undefined2 *)((long)param_1 + 4) = 0x11;
        return param_1;
      }
      goto LAB_011e0a6b;
    }
  }
  if (lVar4 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar4 + 8) = *(ulong *)(lVar4 + 8) ^ 3;
    UNLOCK();
  }
  lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar4 != 0) && ((*(byte *)(lVar4 + 0x21c) & 1) == 0)) {
    uVar1 = *(ulong *)(lVar4 + 8);
    do {
      LOCK();
      uVar2 = *(ulong *)(lVar4 + 8);
      bVar5 = uVar1 == uVar2;
      if (bVar5) {
        *(ulong *)(lVar4 + 8) = uVar1 | 3;
        uVar2 = uVar1;
      }
      UNLOCK();
      uVar1 = uVar2;
    } while (!bVar5);
    if ((uVar2 & 7) == 0) goto LAB_011e0b8f;
    if (((uint)uVar2 & 7) == 6) {
      syscall();
      *(undefined2 *)((long)param_1 + 4) = 0x11;
      return param_1;
    }
  }
  lVar4 = 0;
LAB_011e0b8f:
  if (lVar4 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar4 + 8) = *(ulong *)(lVar4 + 8) ^ 3;
    UNLOCK();
  }
  *(undefined2 *)((long)param_1 + 4) = 0;
  *(undefined4 *)param_1 = local_30;
  return param_1;
}


// ---- FUN_011e0d90 @ 011e0d90

/* WARNING: Removing unreachable block (ram,0x011e1249) */
/* WARNING: Removing unreachable block (ram,0x011e140b) */
/* WARNING: Removing unreachable block (ram,0x011e12d4) */
/* WARNING: Removing unreachable block (ram,0x011e12dd) */
/* WARNING: Removing unreachable block (ram,0x011e12e6) */
/* WARNING: Removing unreachable block (ram,0x011e1411) */
/* WARNING: Removing unreachable block (ram,0x011e0fad) */
/* WARNING: Removing unreachable block (ram,0x011e0fc0) */
/* WARNING: Removing unreachable block (ram,0x011e0fc7) */
/* WARNING: Removing unreachable block (ram,0x011e0fd0) */
/* WARNING: Removing unreachable block (ram,0x011e0fd8) */
/* WARNING: Removing unreachable block (ram,0x011e12f4) */
/* WARNING: Removing unreachable block (ram,0x011e110d) */
/* WARNING: Removing unreachable block (ram,0x011e1120) */
/* WARNING: Removing unreachable block (ram,0x011e1127) */
/* WARNING: Removing unreachable block (ram,0x011e112f) */
/* WARNING: Removing unreachable block (ram,0x011e1210) */
/* WARNING: Removing unreachable block (ram,0x011e1220) */
/* WARNING: Removing unreachable block (ram,0x011e1227) */
/* WARNING: Removing unreachable block (ram,0x011e122f) */
/* WARNING: Removing unreachable block (ram,0x011e1237) */
/* WARNING: Removing unreachable block (ram,0x011e13db) */
/* WARNING: Removing unreachable block (ram,0x011e13e1) */
/* WARNING: Removing unreachable block (ram,0x011e13c0) */
/* WARNING: Removing unreachable block (ram,0x011e13c7) */
/* WARNING: Removing unreachable block (ram,0x011e1272) */
/* WARNING: Removing unreachable block (ram,0x011e12fd) */
/* WARNING: Removing unreachable block (ram,0x011e127b) */
/* WARNING: Removing unreachable block (ram,0x011e1280) */
/* WARNING: Removing unreachable block (ram,0x011e124f) */
/* WARNING: Removing unreachable block (ram,0x011e1257) */
/* WARNING: Removing unreachable block (ram,0x011e12eb) */
/* WARNING: Removing unreachable block (ram,0x011e1269) */
/* WARNING: Removing unreachable block (ram,0x011e1391) */
/* WARNING: Removing unreachable block (ram,0x011e13a0) */
/* WARNING: Removing unreachable block (ram,0x011e13a7) */
/* WARNING: Removing unreachable block (ram,0x011e13af) */
/* WARNING: Removing unreachable block (ram,0x011e13b7) */
/* WARNING: Removing unreachable block (ram,0x011e0e8d) */
/* WARNING: Removing unreachable block (ram,0x011e0ea0) */
/* WARNING: Removing unreachable block (ram,0x011e0ea7) */
/* WARNING: Removing unreachable block (ram,0x011e0eb0) */
/* WARNING: Removing unreachable block (ram,0x011e1491) */
/* WARNING: Removing unreachable block (ram,0x011e13f3) */
/* WARNING: Removing unreachable block (ram,0x011e0fe1) */

undefined4 * FUN_011e0d90(undefined4 *param_1,undefined8 param_2,undefined4 *param_3,long param_4)

{
  byte bVar1;
  undefined2 uVar2;
  ulong uVar3;
  ulong uVar4;
  undefined2 uVar5;
  undefined4 uVar6;
  long lVar7;
  short sVar8;
  long in_FS_OFFSET;
  bool bVar9;
  undefined8 local_88;
  undefined8 uStack_80;
  undefined4 local_6c;
  short local_68;
  undefined4 local_64;
  undefined1 local_60;
  undefined2 local_5c;
  byte local_5a;
  undefined8 local_50;
  undefined8 uStack_48;
  undefined4 local_40;
  undefined1 local_34;
  
  local_64 = *(undefined4 *)(param_4 + 4);
  bVar1 = *(byte *)(param_4 + 8);
  local_5c = 0;
  local_5a = *(byte *)(param_4 + 9) & 7;
  local_60 = 1;
  FUN_011ca0b0(&local_6c,(*(byte *)(param_3 + 7) & 1) * '\b' + '\x02',&local_64);
  if (local_68 != 0) {
    *(short *)(param_1 + 9) = local_68;
    return param_1;
  }
  if ((bVar1 & 1) != 0) {
    lVar7 = *(long *)(in_FS_OFFSET + -0x40010);
    if ((lVar7 == 0) || ((*(byte *)(lVar7 + 0x21c) & 1) != 0)) {
LAB_011e0e4c:
      lVar7 = 0;
    }
    else {
      uVar4 = *(ulong *)(lVar7 + 8);
      do {
        LOCK();
        uVar3 = *(ulong *)(lVar7 + 8);
        bVar9 = uVar4 == uVar3;
        if (bVar9) {
          *(ulong *)(lVar7 + 8) = uVar4 | 3;
          uVar3 = uVar4;
        }
        UNLOCK();
        uVar4 = uVar3;
      } while (!bVar9);
      if ((uVar3 & 7) != 0) {
        if (((uint)uVar3 & 7) != 7) {
          syscall();
          *(undefined2 *)(param_1 + 9) = 0x11;
          return param_1;
        }
        goto LAB_011e0e4c;
      }
    }
    if (lVar7 == 0) {
      syscall();
    }
    else {
      syscall();
      LOCK();
      *(ulong *)(lVar7 + 8) = *(ulong *)(lVar7 + 8) ^ 3;
      UNLOCK();
    }
    lVar7 = *(long *)(in_FS_OFFSET + -0x40010);
    if ((lVar7 == 0) || ((*(byte *)(lVar7 + 0x21c) & 1) != 0)) {
LAB_011e0f64:
      lVar7 = 0;
    }
    else {
      uVar4 = *(ulong *)(lVar7 + 8);
      do {
        LOCK();
        uVar3 = *(ulong *)(lVar7 + 8);
        bVar9 = uVar4 == uVar3;
        if (bVar9) {
          *(ulong *)(lVar7 + 8) = uVar4 | 3;
          uVar3 = uVar4;
        }
        UNLOCK();
        uVar4 = uVar3;
      } while (!bVar9);
      if ((uVar3 & 7) != 0) {
        if (((uint)uVar3 & 7) == 6) {
          syscall();
          *(undefined2 *)(param_1 + 9) = 0x11;
          return param_1;
        }
        goto LAB_011e0f64;
      }
    }
    if (lVar7 == 0) {
      syscall();
    }
    else {
      syscall();
      LOCK();
      *(ulong *)(lVar7 + 8) = *(ulong *)(lVar7 + 8) ^ 3;
      UNLOCK();
    }
  }
  if ((*(byte *)(param_3 + 7) & 1) == 0) {
    uVar2 = swap_bytes(*(undefined2 *)param_3);
    uVar6 = *(undefined4 *)((long)param_3 + 2);
    local_50 = 0;
    sVar8 = 2;
  }
  else {
    uVar2 = swap_bytes(*(undefined2 *)(param_3 + 2));
    uVar6 = *param_3;
    local_40 = param_3[1];
    local_50 = *(undefined8 *)((long)param_3 + 10);
    uStack_48 = *(undefined8 *)((long)param_3 + 0x12);
    sVar8 = 10;
  }
  lVar7 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar7 == 0) || ((*(byte *)(lVar7 + 0x21c) & 1) != 0)) {
LAB_011e10db:
    lVar7 = 0;
  }
  else {
    uVar4 = *(ulong *)(lVar7 + 8);
    do {
      LOCK();
      uVar3 = *(ulong *)(lVar7 + 8);
      bVar9 = uVar4 == uVar3;
      if (bVar9) {
        *(ulong *)(lVar7 + 8) = uVar4 | 3;
        uVar3 = uVar4;
      }
      UNLOCK();
      uVar4 = uVar3;
    } while (!bVar9);
    if ((uVar3 & 7) != 0) {
      if (((uint)uVar3 & 7) != 7) {
        syscall();
        *(undefined2 *)(param_1 + 9) = 0x11;
        return param_1;
      }
      goto LAB_011e10db;
    }
  }
  if (lVar7 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar7 + 8) = *(ulong *)(lVar7 + 8) ^ 3;
    UNLOCK();
  }
  lVar7 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar7 == 0) || ((*(byte *)(lVar7 + 0x21c) & 1) != 0)) {
LAB_011e11cd:
    lVar7 = 0;
  }
  else {
    uVar4 = *(ulong *)(lVar7 + 8);
    do {
      LOCK();
      uVar3 = *(ulong *)(lVar7 + 8);
      bVar9 = uVar4 == uVar3;
      if (bVar9) {
        *(ulong *)(lVar7 + 8) = uVar4 | 3;
        uVar3 = uVar4;
      }
      UNLOCK();
      uVar4 = uVar3;
    } while (!bVar9);
    if ((uVar3 & 7) != 0) {
      if (((uint)uVar3 & 7) == 6) {
        syscall();
        *(undefined2 *)(param_1 + 9) = 0x11;
        return param_1;
      }
      goto LAB_011e11cd;
    }
  }
  if (lVar7 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar7 + 8) = *(ulong *)(lVar7 + 8) ^ 3;
    UNLOCK();
  }
  lVar7 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar7 != 0) && ((*(byte *)(lVar7 + 0x21c) & 1) == 0)) {
    uVar4 = *(ulong *)(lVar7 + 8);
    do {
      LOCK();
      uVar3 = *(ulong *)(lVar7 + 8);
      bVar9 = uVar4 == uVar3;
      if (bVar9) {
        *(ulong *)(lVar7 + 8) = uVar4 | 3;
        uVar3 = uVar4;
      }
      UNLOCK();
      uVar4 = uVar3;
    } while (!bVar9);
    if ((uVar3 & 7) == 0) goto LAB_011e1356;
    if (((uint)uVar3 & 7) == 6) {
      syscall();
      *(undefined2 *)(param_1 + 9) = 0x11;
      return param_1;
    }
  }
  lVar7 = 0;
LAB_011e1356:
  if (lVar7 == 0) {
    syscall();
  }
  else {
    syscall();
    LOCK();
    *(ulong *)(lVar7 + 8) = *(ulong *)(lVar7 + 8) ^ 3;
    UNLOCK();
  }
  uVar5 = 0;
  *(undefined2 *)(param_1 + 9) = 0;
  *param_1 = local_6c;
  if (sVar8 == 10) {
    local_34 = 1;
    uVar5 = swap_bytes(uVar2);
    uVar4 = CONCAT44(local_40,uVar6);
    local_88 = local_50;
    uStack_80 = uStack_48;
  }
  else if (sVar8 == 2) {
    local_34 = 0;
    uVar5 = swap_bytes(uVar2);
    uVar4 = (ulong)CONCAT42(uVar6,uVar5);
  }
  else {
    local_34 = 0;
    uVar4 = 0x100007f0000;
  }
  *(ulong *)(param_1 + 1) = uVar4;
  *(undefined2 *)(param_1 + 3) = uVar5;
  *(undefined8 *)((long)param_1 + 0xe) = local_88;
  *(undefined8 *)((long)param_1 + 0x16) = uStack_80;
  *(undefined1 *)(param_1 + 8) = local_34;
  return param_1;
}


// ---- FUN_011e1520 @ 011e1520

undefined8 FUN_011e1520(void)

{
  long lVar1;
  char acStack_24c7 [9407];
  
  builtin_strncpy(acStack_24c7 + 0x57,"A\x15\x1e\x01",5);
  acStack_24c7[0x5c] = '\0';
  acStack_24c7[0x5d] = '\0';
  acStack_24c7[0x5e] = '\0';
  FUN_011f4580(acStack_24c7 + 0x5f,&DAT_01404219,0x2400);
  lVar1 = 0x5f;
  while( true ) {
    if (acStack_24c7[lVar1] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 1] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 2] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 3] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 4] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 5] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 6] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 7] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 8] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 9] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 10] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0xb] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0xc] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0xd] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0xe] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0xf] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x10] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x11] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x12] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x13] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x14] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x15] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x16] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x17] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x18] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x19] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x1a] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x1b] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x1c] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x1d] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x1e] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x1f] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x20] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x21] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x22] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x23] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x24] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x25] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x26] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x27] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x28] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x29] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x2a] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x2b] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x2c] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x2d] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x2e] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x2f] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x30] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x31] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x32] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x33] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x34] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x35] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x36] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x37] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x38] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x39] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x3a] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x3b] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x3c] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x3d] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x3e] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x3f] != '\0') break;
    if (acStack_24c7[lVar1 + 0x40] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x41] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x42] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x43] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x44] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x45] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x46] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x47] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x48] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x49] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x4a] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x4b] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x4c] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x4d] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x4e] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x4f] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x50] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x51] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x52] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x53] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x54] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x55] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x56] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x57] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x58] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x59] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x5a] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x5b] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x5c] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x5d] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x5e] != '\0') {
      return 1;
    }
    if (acStack_24c7[lVar1 + 0x5f] != '\0') {
      return 1;
    }
    lVar1 = lVar1 + 0x60;
    if (lVar1 == 0x245f) {
      return 0;
    }
  }
  return 1;
}


// FAILED: FUN_011e1d00
// ---- FUN_011ed370 @ 011ed370

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_011ed370(byte param_1,ulong param_2,ulong param_3)

{
  double *pdVar1;
  ulong uVar2;
  ulong uVar3;
  long lVar4;
  int iVar5;
  ulong uVar7;
  long lVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uVar11;
  long lVar12;
  long lVar13;
  ulong uVar14;
  double dVar15;
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  double dVar18;
  uint uVar6;
  
  pdVar1 = (double *)&DAT_01261468;
  if (((((DAT_01261485 == '\0') || (pdVar1 = (double *)&DAT_01261488, DAT_012614a5 != '\x01')) ||
       (pdVar1 = (double *)&DAT_012614a8, DAT_012614c5 != '\x01')) ||
      (((((pdVar1 = (double *)&DAT_012614c8, DAT_012614e5 != '\x01' ||
          (pdVar1 = (double *)&DAT_012614e8, DAT_01261505 != '\x01')) ||
         ((pdVar1 = (double *)&DAT_01261508, DAT_01261525 != '\x01' ||
          ((pdVar1 = (double *)&DAT_01261528, DAT_01261545 != '\x01' ||
           (pdVar1 = (double *)&DAT_01261548, DAT_01261565 != '\x01')))))) ||
        (pdVar1 = (double *)&DAT_01261568, DAT_01261585 != '\x01')) ||
       (((((pdVar1 = (double *)&DAT_01261588, DAT_012615a5 != '\x01' ||
           (pdVar1 = (double *)&DAT_012615a8, DAT_012615c5 != '\x01')) ||
          (pdVar1 = (double *)&DAT_012615c8, DAT_012615e5 != '\x01')) ||
         ((pdVar1 = (double *)&DAT_012615e8, DAT_01261605 != '\x01' ||
          (pdVar1 = (double *)&DAT_01261608, DAT_01261625 != '\x01')))) ||
        ((pdVar1 = (double *)&DAT_01261628, DAT_01261645 != '\x01' ||
         ((pdVar1 = (double *)&DAT_01261648, DAT_01261665 != '\x01' ||
          (pdVar1 = (double *)&DAT_01261668, DAT_01261685 != '\x01')))))))))) ||
     ((((pdVar1 = (double *)&DAT_01261688, DAT_012616a5 != '\x01' ||
        (((((pdVar1 = (double *)&DAT_012616a8, DAT_012616c5 != '\x01' ||
            (pdVar1 = (double *)&DAT_012616c8, DAT_012616e5 != '\x01')) ||
           (pdVar1 = (double *)&DAT_012616e8, DAT_01261705 != '\x01')) ||
          ((pdVar1 = (double *)&DAT_01261708, DAT_01261725 != '\x01' ||
           (pdVar1 = (double *)&DAT_01261728, DAT_01261745 != '\x01')))) ||
         (pdVar1 = (double *)&DAT_01261748, DAT_01261765 != '\x01')))) ||
       (((((pdVar1 = (double *)&DAT_01261768, DAT_01261785 != '\x01' ||
           (pdVar1 = (double *)&DAT_01261788, DAT_012617a5 != '\x01')) ||
          ((pdVar1 = (double *)&DAT_012617a8, DAT_012617c5 != '\x01' ||
           (((pdVar1 = (double *)&DAT_012617c8, DAT_012617e5 != '\x01' ||
             (pdVar1 = (double *)&DAT_012617e8, DAT_01261805 != '\x01')) ||
            (pdVar1 = (double *)&DAT_01261808, DAT_01261825 != '\x01')))))) ||
         (((pdVar1 = (double *)&DAT_01261828, DAT_01261845 != '\x01' ||
           (pdVar1 = (double *)&DAT_01261848, DAT_01261865 != '\x01')) ||
          (pdVar1 = (double *)&DAT_01261868, DAT_01261885 != '\x01')))) ||
        (((pdVar1 = (double *)&DAT_01261888, DAT_012618a5 != '\x01' ||
          (pdVar1 = (double *)&DAT_012618a8, DAT_012618c5 != '\x01')) ||
         ((pdVar1 = (double *)&DAT_012618c8, DAT_012618e5 != '\x01' ||
          (((pdVar1 = (double *)&DAT_012618e8, DAT_01261905 != '\x01' ||
            (pdVar1 = (double *)&DAT_01261908, DAT_01261925 != '\x01')) ||
           (pdVar1 = (double *)&DAT_01261928, DAT_01261945 != '\x01')))))))))) ||
      (((pdVar1 = (double *)&DAT_01261948, DAT_01261965 != '\x01' ||
        (pdVar1 = (double *)&DAT_01261968, DAT_01261985 != '\x01')) ||
       ((pdVar1 = (double *)&DAT_01261988, DAT_012619a5 != '\x01' ||
        (((pdVar1 = (double *)&DAT_012619a8, DAT_012619c5 != '\x01' ||
          (pdVar1 = (double *)&DAT_012619c8, DAT_012619e5 != '\x01')) ||
         ((pdVar1 = (double *)&DAT_012619e8, DAT_01261a05 != '\x01' ||
          (((pdVar1 = (double *)&DAT_01261a08, DAT_01261a25 != '\x01' ||
            (pdVar1 = (double *)&DAT_01261a28, DAT_01261a45 != '\x01')) ||
           (pdVar1 = (double *)&DAT_01261a48, DAT_01261a65 == '\0')))))))))))))) {
    uVar9 = 0;
    uVar6 = *(uint *)(&DAT_01001220 + (ulong)((param_1 ^ 4) & 7) * 4) >> 1;
    if (DAT_01406659 == '\0') {
      uVar6 = 0;
    }
    if ((char)(param_1 << 5) >> 5 < -1) {
      uVar6 = 0;
    }
    iVar5 = uVar6 + *(uint *)(&DAT_01001220 + (ulong)((param_1 ^ 4) & 7) * 4);
    uVar7 = param_2;
    uVar11 = param_3;
    do {
      uVar10 = 0x5e;
      if (uVar7 < 0x5e) {
        uVar10 = uVar7;
      }
      uVar14 = 0x5e;
      if (uVar11 < 0x5e) {
        uVar14 = uVar11;
      }
      lVar12 = param_3 - uVar9;
      if (param_3 < uVar9 || lVar12 == 0) {
        lVar12 = 1;
      }
      uVar2 = uVar9 + param_3;
      if (0x5d < uVar2) {
        uVar2 = 0x5e;
      }
      if (uVar2 + 1 != lVar12) {
        uVar2 = param_2 - uVar9;
        if (param_2 < uVar9 || uVar2 == 0) {
          uVar2 = 1;
        }
        uVar3 = uVar9 + param_2;
        if (0x5d < uVar3) {
          uVar3 = 0x5e;
        }
        if (uVar3 + 1 != uVar2) {
          lVar4 = lVar12 * 0x60 + 0x1a6644;
          lVar8 = 0;
          do {
            uVar3 = uVar2;
            lVar13 = (uVar10 - uVar2) + 1 + (ulong)(uVar10 - uVar2 == -1);
            do {
              if (*(char *)((long)&DAT_01260018 + uVar3 + lVar4) == '.') {
                auVar16._8_8_ = 0;
                auVar16._0_8_ = lVar8 + lVar12;
                auVar17._8_8_ = 0;
                auVar17._0_8_ = uVar3;
                auVar17 = vpunpcklqdq_avx(auVar17,auVar16);
                auVar16 = vpblendd_avx2(auVar17,(undefined1  [16])0x0,10);
                auVar16 = vpor_avx(auVar16,_DAT_010006f0);
                auVar17 = vpsrlq_avx(auVar17,0x20);
                auVar17 = vpor_avx(auVar17,_DAT_01000430);
                auVar17 = vsubpd_avx(auVar17,_DAT_01000440);
                dVar15 = auVar16._0_8_ + auVar17._0_8_ + _DAT_010003a0;
                dVar18 = auVar16._8_8_ + auVar17._8_8_ + _UNK_010003a8;
                goto LAB_011ed845;
              }
              uVar3 = uVar3 + 1;
              lVar13 = lVar13 + -1;
            } while (lVar13 != 0);
            lVar8 = lVar8 + 1;
            lVar4 = lVar4 + 0x60;
          } while (lVar8 != (uVar14 - lVar12) + 1 + (ulong)(uVar14 - lVar12 == -1));
        }
      }
      uVar9 = uVar9 + 1;
      uVar7 = uVar7 + 1;
      uVar11 = uVar11 + 1;
      dVar15 = DAT_01000c78;
      dVar18 = DAT_01000c78;
    } while (uVar9 != 0x60);
LAB_011ed845:
    *pdVar1 = dVar15;
    pdVar1[1] = dVar18;
    *(byte *)((long)pdVar1 + 0x1c) = param_1 & 7;
    *(int *)(pdVar1 + 2) = iVar5;
    *(int *)((long)pdVar1 + 0x14) = iVar5;
    *(undefined1 *)((long)pdVar1 + 0x1d) = 1;
    *(undefined4 *)(pdVar1 + 3) = 0;
  }
  return;
}


// ---- FUN_011ed880 @ 011ed880

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_011ed880(uint *param_1,char param_2,char param_3)

{
  char cVar1;
  double dVar2;
  undefined1 auVar3 [16];
  double dVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  ulong uVar9;
  uint uVar10;
  uint uVar11;
  byte bVar13;
  int iVar14;
  undefined1 uVar15;
  ulong uVar16;
  double dVar17;
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  uint uVar20;
  uint uVar24;
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  double dVar25;
  undefined1 auVar26 [64];
  undefined1 auVar27 [16];
  undefined1 auVar28 [16];
  undefined1 auVar29 [16];
  uint local_3c;
  uint local_38;
  int iVar12;
  
  iVar5 = (int)DAT_01261430;
  iVar14 = 7;
  if (7 < iVar5) {
    iVar14 = iVar5;
  }
  if (0x57 < iVar5) {
    iVar5 = 0x58;
  }
  uVar10 = iVar14 + 0x7ffffffaU & 0x7fffffff;
  if (iVar5 + 6 < (int)uVar10) {
    uVar15 = 0;
  }
  else {
    iVar7 = (int)DAT_01261428;
    iVar14 = 7;
    if (7 < iVar7) {
      iVar14 = iVar7;
    }
    iVar12 = 0x58;
    if (iVar7 < 0x58) {
      iVar12 = iVar7;
    }
    uVar11 = iVar12 + 6;
    uVar15 = 0;
    uVar6 = iVar14 + 0x7ffffffaU & 0x7fffffff;
    auVar26 = ZEXT864(DAT_01000a18);
    dVar25 = DAT_01000a78;
    do {
      if ((int)uVar6 <= (int)uVar11) {
        uVar8 = uVar6;
        if (uVar10 < 0x60) {
          dVar4 = ((double)uVar10 + DAT_01000ce0) - DAT_01261430;
          do {
            cVar1 = (&DAT_0140665c)[(ulong)uVar8 + (ulong)uVar10 * 0x60];
            if (cVar1 == 'D') {
              if ((&DAT_01404219)[(ulong)uVar8 + (ulong)uVar10 * 0x60] == '\x01') goto LAB_011eda60;
            }
            else if ((cVar1 == 'R') || (cVar1 == 'V')) {
LAB_011eda60:
              if (param_3 == '\0') {
                if (((uVar10 != 0x14) || (7 < uVar8 - 0x12)) &&
                   ((uVar10 != 0xf || (0xf < uVar8 - 0xe)))) {
                  if ((uVar10 != 0x15 || 5 < uVar8 - 0x1d) && (uVar8 != 0x22 || uVar10 != 0x10))
                  goto LAB_011eda6d;
                }
              }
              else if (cVar1 == param_2) {
LAB_011eda6d:
                dVar17 = ((double)uVar8 + DAT_01000ce0) - DAT_01261428;
                dVar2 = dVar4 * DAT_01261440 + dVar17 * DAT_01261438;
                if ((auVar26._0_8_ < dVar2) && (dVar2 < dVar25)) {
                  if ((double)((ulong)(dVar17 * DAT_01261440 - dVar4 * DAT_01261438) & _DAT_01000240
                              ) < dVar2 * DAT_01000b10 + DAT_01001030) {
                    auVar21._0_8_ = SQRT(dVar17 * dVar17 + dVar4 * dVar4) / DAT_01000ab8;
                    auVar21._8_8_ = 0;
                    auVar21 = vroundsd_avx(auVar21,auVar21,10);
                    uVar9 = (ulong)auVar21._0_8_;
                    uVar9 = (long)(auVar21._0_8_ - DAT_01000c30) & (long)uVar9 >> 0x3f | uVar9;
                    if (1 < uVar9) {
                      auVar22._8_8_ = 0;
                      auVar22._0_8_ = uVar9;
                      auVar28._8_8_ = 0;
                      auVar28._0_8_ = DAT_01000340;
                      auVar21 = vpunpckldq_avx(auVar22,auVar28);
                      auVar3 = vsubpd_avx(auVar21,_DAT_01000250);
                      auVar22 = vshufpd_avx(auVar3,auVar3,1);
                      auVar27._8_8_ = 0;
                      auVar27._0_8_ = dVar17;
                      auVar29._8_8_ = 0;
                      auVar29._0_8_ = dVar4;
                      auVar21 = vpunpcklqdq_avx(auVar27,auVar29);
                      uVar16 = 1;
                      do {
                        auVar23._8_8_ = 0;
                        auVar23._0_8_ = uVar16;
                        auVar27 = vpunpckldq_avx(auVar23,auVar28);
                        auVar29 = vsubpd_avx(auVar27,_DAT_01000250);
                        auVar27 = vshufpd_avx(auVar29,auVar29,1);
                        dVar17 = (auVar27._0_8_ + auVar29._0_8_) / (auVar22._0_8_ + auVar3._0_8_);
                        auVar18._0_8_ = DAT_01261428 + auVar21._0_8_ * dVar17;
                        auVar18._8_8_ = DAT_01261430 + auVar21._8_8_ * dVar17;
                        auVar27 = vroundpd_avx(auVar18,9);
                        uVar20 = (uint)auVar27._0_8_;
                        uVar24 = (uint)auVar27._8_8_;
                        bVar13 = 0x31;
                        if (uVar24 < 0x60 && uVar20 < 0x60) {
                          bVar13 = (&DAT_0140665c)[(ulong)uVar20 + (ulong)uVar24 * 0x60];
                          if ((0x28 < bVar13 - 0x2e) ||
                             ((0x15000000001U >> ((ulong)(bVar13 - 0x2e) & 0x3f) & 1) == 0))
                          goto LAB_011edba4;
                        }
                        else {
LAB_011edba4:
                          auVar19._8_8_ = CONCAT44(uVar24,uVar20);
                          auVar19._0_8_ = CONCAT44(uVar24,uVar20);
                          auVar27 = vpblendd_avx2(auVar19,_DAT_01000950,0xc);
                          auVar29 = vpblendd_avx2(_DAT_01000950,auVar19,0xc);
                          auVar27 = vpcmpgtd_avx(auVar29,auVar27);
                          iVar14 = vmovmskps_avx(auVar27);
                          if ((iVar14 != 0xf) ||
                             ((bVar13 != 0x44 ||
                              ((&DAT_01404219)[(ulong)uVar20 + (ulong)uVar24 * 0x60] != '\x01'))))
                          goto LAB_011edcab;
                        }
                        uVar16 = uVar16 + 1;
                      } while (uVar9 != uVar16);
                      uVar15 = 1;
                      dVar25 = dVar2;
                      local_3c = uVar10;
                      local_38 = uVar8;
LAB_011edcab:
                      auVar26 = ZEXT1664(auVar26._0_16_);
                      goto LAB_011eda20;
                    }
                    uVar15 = 1;
                    dVar25 = dVar2;
                    local_3c = uVar10;
                    local_38 = uVar8;
                  }
                  auVar26 = ZEXT1664(auVar26._0_16_);
                }
              }
            }
LAB_011eda20:
            uVar8 = uVar8 + 1 & 0x7fffffff;
          } while ((int)uVar8 <= (int)uVar11);
        }
        else {
          do {
            uVar8 = uVar8 + 1 & 0x7fffffff;
          } while (uVar8 <= uVar11);
        }
      }
      uVar10 = uVar10 + 1 & 0x7fffffff;
    } while ((int)uVar10 <= iVar5 + 6);
  }
  *param_1 = local_38;
  param_1[1] = local_3c;
  *(undefined1 *)(param_1 + 2) = uVar15;
  *(undefined2 *)((long)param_1 + 9) = 0;
  *(undefined1 *)((long)param_1 + 0xb) = 0;
  return;
}


// ---- FUN_011edcc0 @ 011edcc0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

double FUN_011edcc0(undefined8 param_1,undefined8 param_2,long param_3)

{
  undefined1 auVar1 [16];
  double dVar2;
  double dVar3;
  uint uVar4;
  double dVar5;
  double dVar6;
  undefined1 auVar7 [16];
  undefined1 in_ZMM0 [64];
  undefined1 auVar8 [16];
  
  dVar5 = in_ZMM0._0_8_;
  uVar4 = in_ZMM0._4_4_ & 0x7fffffff;
  auVar7 = in_ZMM0._0_16_;
  if (0x440fffff < uVar4) {
    auVar1 = vcmpsd_avx(auVar7,auVar7,3);
    auVar8._8_8_ = 0;
    auVar8._0_8_ = *(ulong *)(&DAT_01000910 + (ulong)(-1 < (long)dVar5) * 8);
    auVar7 = vblendvpd_avx(auVar8,auVar7,auVar1);
    return auVar7._0_8_;
  }
  if (uVar4 < 0x3fdc0000) {
    dVar6 = dVar5;
    if (uVar4 < 0x3e400000) {
      if (0xfffff < uVar4) {
        return dVar5;
      }
      return dVar5;
    }
  }
  else {
    auVar7 = vpand_avx(auVar7,_DAT_01000240);
    dVar6 = auVar7._0_8_;
    if (uVar4 < 0x3ff30000) {
      if (uVar4 < 0x3fe60000) {
        param_3 = 0;
        dVar6 = (dVar6 + dVar6 + DAT_010009f0) / (dVar6 + DAT_01000a68);
      }
      else {
        param_3 = 1;
        dVar6 = (dVar6 + DAT_010009f0) / (dVar6 + DAT_01000bf8);
      }
    }
    else if (uVar4 < 0x40038000) {
      param_3 = 2;
      dVar6 = (dVar6 + DAT_01000a60) / (dVar6 * DAT_01000e28 + DAT_01000bf8);
    }
    else {
      param_3 = 3;
      dVar6 = DAT_010009f0 / dVar6;
    }
  }
  dVar2 = dVar6 * dVar6;
  dVar3 = dVar2 * dVar2;
  dVar2 = dVar2 * (dVar3 * (dVar3 * (dVar3 * (dVar3 * (dVar3 * _DAT_01000d18 + DAT_01000cd0) +
                                             DAT_010009d8) + DAT_010010d0) + DAT_01000bb8) +
                  DAT_010009e0);
  dVar3 = dVar3 * (dVar3 * (dVar3 * (dVar3 * (dVar3 * DAT_01000ee8 + DAT_01000ff0) + DAT_01000ef0) +
                           DAT_01001178) + DAT_01000b20);
  if (uVar4 < 0x3fdc0000) {
    dVar6 = dVar6 - dVar6 * (dVar3 + dVar2);
  }
  else {
    dVar6 = *(double *)(&DAT_01001320 + param_3 * 8) -
            ((dVar6 * (dVar3 + dVar2) - *(double *)(&DAT_010013c0 + param_3 * 8)) - dVar6);
    if ((long)dVar5 < 0) {
      return (double)((ulong)dVar6 ^ _DAT_010007e0);
    }
  }
  return dVar6;
}


// ---- FUN_011ede80 @ 011ede80

undefined4 FUN_011ede80(char param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0x5f626a;
  if ((byte)(param_1 - 0x31U) < 0x26) {
    uVar1 = (&DAT_011b8674)[(byte)(param_1 - 0x31U)];
  }
  return uVar1;
}


// ---- FUN_011edea0 @ 011edea0

/* WARNING: Type propagation algorithm not settling */

void FUN_011edea0(uint param_1,int param_2,long param_3,long param_4,int param_5,undefined4 param_6)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  long lVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  long lVar11;
  int iVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  byte local_38 [8];
  
  if (param_4 != 0) {
    lVar11 = 0;
    do {
      switch(((byte)(*(byte *)(param_3 + lVar11) + 0x9f) < 0x1a) << 5 ^ *(byte *)(param_3 + lVar11))
      {
      case 0x30:
        local_38[0] = 0xe;
        local_38[1] = 0x11;
        local_38[2] = 0x13;
        local_38[3] = 0x15;
        local_38[4] = 0x19;
        local_38[5] = 0x11;
        local_38[6] = 0xe;
        break;
      case 0x31:
        local_38[0] = 4;
        local_38[1] = 0xc;
        local_38[2] = 4;
        local_38[3] = 4;
        local_38[4] = 4;
        local_38[5] = 4;
        local_38[6] = 0xe;
        break;
      case 0x32:
        local_38[0] = 0xe;
        local_38[1] = 0x11;
        local_38[2] = 1;
        local_38[3] = 2;
        local_38[4] = 4;
        local_38[5] = 8;
        local_38[6] = 0x1f;
        break;
      case 0x33:
        local_38[0] = 0x1e;
        local_38[1] = 1;
        local_38[2] = 1;
        local_38[3] = 0xe;
        goto LAB_011ee123;
      case 0x34:
        local_38[0] = 2;
        local_38[1] = 6;
        local_38[2] = 10;
        local_38[3] = 0x12;
        local_38[4] = 0x1f;
        local_38[5] = 2;
        local_38[6] = 2;
        break;
      case 0x35:
        local_38[0] = 0x1f;
        local_38[1] = 0x10;
        local_38[2] = 0x10;
        local_38[3] = 0x1e;
        goto LAB_011ee123;
      case 0x36:
        local_38[0] = 0xe;
        local_38[1] = 0x10;
        local_38[2] = 0x10;
        local_38[3] = 0x1e;
        goto LAB_011ee187;
      case 0x37:
        local_38[0] = 0x1f;
        local_38[1] = 1;
        local_38[2] = 2;
        local_38[3] = 4;
        local_38[4] = 8;
        local_38[5] = 8;
        local_38[6] = 8;
        break;
      case 0x38:
        local_38[0] = 0xe;
        local_38[1] = 0x11;
        local_38[2] = 0x11;
        local_38[3] = 0xe;
        goto LAB_011ee187;
      case 0x39:
        local_38[0] = 0xe;
        local_38[1] = 0x11;
        local_38[2] = 0x11;
        local_38[3] = 0xf;
        local_38[4] = 1;
        local_38[5] = 1;
        local_38[6] = 0xe;
        break;
      case 0x3a:
        local_38[0] = 0;
        local_38[1] = 4;
        local_38[2] = 4;
        local_38[3] = 0;
        local_38[4] = 4;
        local_38[5] = 4;
        local_38[6] = 0;
        break;
      default:
        local_38[4] = 0;
        local_38[5] = 0;
        local_38[6] = 0;
        local_38[0] = 0;
        local_38[1] = 0;
        local_38[2] = 0;
        local_38[3] = 0;
        break;
      case 0x41:
        local_38[0] = 0xe;
        local_38[1] = 0x11;
        local_38[2] = 0x11;
        local_38[3] = 0x1f;
        goto LAB_011ee0a9;
      case 0x42:
        local_38[0] = 0x1e;
        local_38[1] = 0x11;
        local_38[2] = 0x11;
        local_38[3] = 0x1e;
        goto LAB_011ee0f7;
      case 0x43:
        local_38[0] = 0xe;
        local_38[1] = 0x11;
        local_38[2] = 0x10;
        local_38[3] = 0x10;
        local_38[4] = 0x10;
        local_38[5] = 0x11;
        local_38[6] = 0xe;
        break;
      case 0x44:
        local_38[0] = 0x1e;
        local_38[1] = 0x11;
        local_38[2] = 0x11;
        local_38[3] = 0x11;
LAB_011ee0f7:
        local_38[4] = 0x11;
        local_38[5] = 0x11;
        local_38[6] = 0x1e;
        break;
      case 0x45:
        local_38[0] = 0x1f;
        local_38[1] = 0x10;
        local_38[2] = 0x10;
        local_38[3] = 0x1e;
        goto LAB_011ee10d;
      case 0x46:
        local_38[0] = 0x1f;
        local_38[1] = 0x10;
        local_38[2] = 0x10;
        local_38[3] = 0x1e;
        goto LAB_011ee1f8;
      case 0x47:
        local_38[0] = 0xe;
        local_38[1] = 0x11;
        local_38[2] = 0x10;
        local_38[3] = 0x17;
        local_38[4] = 0x11;
        local_38[5] = 0x11;
        local_38[6] = 0xf;
        break;
      case 0x48:
        local_38[0] = 0x11;
        local_38[1] = 0x11;
        local_38[2] = 0x11;
        local_38[3] = 0x1f;
        goto LAB_011ee0a9;
      case 0x49:
        local_38[0] = 0x1f;
        local_38[1] = 4;
        local_38[2] = 4;
        local_38[3] = 4;
        local_38[4] = 4;
        local_38[5] = 4;
        local_38[6] = 0x1f;
        break;
      case 0x4a:
        local_38[0] = 7;
        local_38[1] = 2;
        local_38[2] = 2;
        local_38[3] = 2;
        local_38[4] = 0x12;
        local_38[5] = 0x12;
        local_38[6] = 0xc;
        break;
      case 0x4b:
        local_38[0] = 0x11;
        local_38[1] = 0x12;
        local_38[2] = 0x14;
        local_38[3] = 0x18;
        goto LAB_011ee022;
      case 0x4c:
        local_38[0] = 0x10;
        local_38[1] = 0x10;
        local_38[2] = 0x10;
        local_38[3] = 0x10;
LAB_011ee10d:
        local_38[4] = 0x10;
        local_38[5] = 0x10;
        local_38[6] = 0x1f;
        break;
      case 0x4d:
        local_38[0] = 0x11;
        local_38[1] = 0x1b;
        local_38[2] = 0x15;
        local_38[3] = 0x15;
        goto LAB_011ee0a9;
      case 0x4e:
        local_38[0] = 0x11;
        local_38[1] = 0x19;
        local_38[2] = 0x15;
        local_38[3] = 0x13;
LAB_011ee0a9:
        local_38[4] = 0x11;
        local_38[5] = 0x11;
        local_38[6] = 0x11;
        break;
      case 0x4f:
        local_38[0] = 0xe;
        local_38[1] = 0x11;
        local_38[2] = 0x11;
        local_38[3] = 0x11;
        goto LAB_011ee187;
      case 0x50:
        local_38[0] = 0x1e;
        local_38[1] = 0x11;
        local_38[2] = 0x11;
        local_38[3] = 0x1e;
LAB_011ee1f8:
        local_38[4] = 0x10;
        local_38[5] = 0x10;
        local_38[6] = 0x10;
        break;
      case 0x51:
        local_38[0] = 0xe;
        local_38[1] = 0x11;
        local_38[2] = 0x11;
        local_38[3] = 0x11;
        local_38[4] = 0x15;
        local_38[5] = 0x12;
        local_38[6] = 0xd;
        break;
      case 0x52:
        local_38[0] = 0x1e;
        local_38[1] = 0x11;
        local_38[2] = 0x11;
        local_38[3] = 0x1e;
LAB_011ee022:
        local_38[4] = 0x14;
        local_38[5] = 0x12;
        local_38[6] = 0x11;
        break;
      case 0x53:
        local_38[0] = 0xf;
        local_38[1] = 0x10;
        local_38[2] = 0x10;
        local_38[3] = 0xe;
LAB_011ee123:
        local_38[4] = 1;
        local_38[5] = 1;
        local_38[6] = 0x1e;
        break;
      case 0x54:
        local_38[0] = 0x1f;
        local_38[1] = 4;
        local_38[2] = 4;
        local_38[3] = 4;
        goto LAB_011ee20b;
      case 0x55:
        local_38[0] = 0x11;
        local_38[1] = 0x11;
        local_38[2] = 0x11;
        local_38[3] = 0x11;
LAB_011ee187:
        local_38[4] = 0x11;
        local_38[5] = 0x11;
        local_38[6] = 0xe;
        break;
      case 0x56:
        local_38[0] = 0x11;
        local_38[1] = 0x11;
        local_38[2] = 0x11;
        local_38[3] = 0x11;
        local_38[4] = 0x11;
        local_38[5] = 10;
        local_38[6] = 4;
        break;
      case 0x57:
        local_38[0] = 0x11;
        local_38[1] = 0x11;
        local_38[2] = 0x11;
        local_38[3] = 0x15;
        local_38[4] = 0x15;
        local_38[5] = 0x15;
        local_38[6] = 10;
        break;
      case 0x58:
        local_38[0] = 0x11;
        local_38[1] = 0x11;
        local_38[2] = 10;
        local_38[3] = 4;
        local_38[4] = 10;
        local_38[5] = 0x11;
        local_38[6] = 0x11;
        break;
      case 0x59:
        local_38[0] = 0x11;
        local_38[1] = 0x11;
        local_38[2] = 10;
        local_38[3] = 4;
LAB_011ee20b:
        local_38[4] = 4;
        local_38[5] = 4;
        local_38[6] = 4;
        break;
      case 0x5a:
        local_38[0] = 0x1f;
        local_38[1] = 1;
        local_38[2] = 2;
        local_38[3] = 4;
        local_38[4] = 8;
        local_38[5] = 0x10;
        local_38[6] = 0x1f;
        break;
      case 0x5f:
        local_38[4] = 0;
        local_38[5] = 0;
        local_38[0] = 0;
        local_38[1] = 0;
        local_38[2] = 0;
        local_38[3] = 0;
        local_38[6] = 0x1f;
        break;
      case 0x7b:
        local_38[0] = 6;
        local_38[1] = 8;
        local_38[2] = 8;
        local_38[3] = 0x10;
        local_38[4] = 8;
        local_38[5] = 8;
        local_38[6] = 6;
        break;
      case 0x7d:
        local_38[0] = 0xc;
        local_38[1] = 2;
        local_38[2] = 2;
        local_38[3] = 1;
        local_38[4] = 2;
        local_38[5] = 2;
        local_38[6] = 0xc;
      }
      uVar15 = param_1 + param_5;
      uVar10 = 0x280;
      if ((int)uVar15 < 0x280) {
        uVar10 = uVar15;
      }
      uVar2 = param_5 + uVar15;
      if (0x27f < (int)(param_5 + uVar15)) {
        uVar2 = 0x280;
      }
      uVar3 = param_5 * 2 + param_1;
      uVar14 = param_5 * 2 + uVar15;
      if (0x27f < (int)uVar14) {
        uVar14 = 0x280;
      }
      uVar4 = param_5 * 3 + param_1;
      uVar17 = param_5 * 3 + uVar15;
      if (0x27f < (int)uVar17) {
        uVar17 = 0x280;
      }
      uVar5 = param_5 * 4 + param_1;
      uVar16 = uVar15 + param_5 * 4;
      if (0x27f < (int)uVar16) {
        uVar16 = 0x280;
      }
      uVar5 = ~((int)uVar5 >> 0x1f) & uVar5 & 0x7fffffff;
      uVar18 = ~((int)uVar4 >> 0x1f) & uVar4 & 0x7fffffff;
      uVar3 = ~((int)uVar3 >> 0x1f) & uVar3 & 0x7fffffff;
      uVar15 = ~((int)uVar15 >> 0x1f) & uVar15 & 0x7fffffff;
      uVar4 = ~((int)param_1 >> 0x1f) & param_1 & 0x7fffffff;
      lVar7 = 0;
      do {
        bVar1 = local_38[lVar7];
        iVar12 = param_5 * (int)lVar7;
        uVar6 = param_2 + iVar12;
        uVar13 = iVar12 + param_2 + param_5;
        if (0x167 < (int)uVar13) {
          uVar13 = 0x168;
        }
        if (((bVar1 & 0x10) != 0) && (uVar9 = uVar6 & 0x7fffffff, (int)uVar9 < (int)uVar13)) {
          do {
            if ((int)uVar4 < (int)uVar10) {
              uVar8 = uVar4;
              do {
                (&DAT_01320df0)[(ulong)uVar9 * 0x280 + (ulong)uVar8] = param_6;
                uVar8 = uVar8 + 1 & 0x7fffffff;
              } while (uVar8 < uVar10);
            }
            uVar9 = uVar9 + 1 & 0x7fffffff;
          } while (uVar9 < uVar13);
        }
        if (((bVar1 & 8) != 0) && (uVar9 = uVar6 & 0x7fffffff, (int)uVar9 < (int)uVar13)) {
          do {
            if ((int)uVar15 < (int)uVar2) {
              uVar8 = uVar15;
              do {
                (&DAT_01320df0)[(ulong)uVar9 * 0x280 + (ulong)uVar8] = param_6;
                uVar8 = uVar8 + 1 & 0x7fffffff;
              } while (uVar8 < uVar2);
            }
            uVar9 = uVar9 + 1 & 0x7fffffff;
          } while (uVar9 < uVar13);
        }
        if (((bVar1 & 4) != 0) && (uVar9 = uVar6 & 0x7fffffff, (int)uVar9 < (int)uVar13)) {
          do {
            if ((int)uVar3 < (int)uVar14) {
              uVar8 = uVar3;
              do {
                (&DAT_01320df0)[(ulong)uVar9 * 0x280 + (ulong)uVar8] = param_6;
                uVar8 = uVar8 + 1 & 0x7fffffff;
              } while (uVar8 < uVar14);
            }
            uVar9 = uVar9 + 1 & 0x7fffffff;
          } while (uVar9 < uVar13);
        }
        if (((bVar1 & 2) != 0) && (uVar9 = uVar6 & 0x7fffffff, (int)uVar9 < (int)uVar13)) {
          do {
            if ((int)uVar18 < (int)uVar17) {
              uVar8 = uVar18;
              do {
                (&DAT_01320df0)[(ulong)uVar9 * 0x280 + (ulong)uVar8] = param_6;
                uVar8 = uVar8 + 1 & 0x7fffffff;
              } while (uVar8 < uVar17);
            }
            uVar9 = uVar9 + 1 & 0x7fffffff;
          } while (uVar9 < uVar13);
        }
        if (((bVar1 & 1) != 0) && (uVar6 = uVar6 & 0x7fffffff, (int)uVar6 < (int)uVar13)) {
          do {
            if ((int)uVar5 < (int)uVar16) {
              uVar9 = uVar5;
              do {
                (&DAT_01320df0)[(ulong)uVar6 * 0x280 + (ulong)uVar9] = param_6;
                uVar9 = uVar9 + 1 & 0x7fffffff;
              } while (uVar9 < uVar16);
            }
            uVar6 = uVar6 + 1 & 0x7fffffff;
          } while (uVar6 < uVar13);
        }
        lVar7 = lVar7 + 1;
      } while (lVar7 != 7);
      param_1 = param_1 + param_5 * 6;
      lVar11 = lVar11 + 1;
    } while (lVar11 != param_4);
  }
  return;
}


// ---- FUN_011ee5d0 @ 011ee5d0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_011ee5d0(void)

{
  long lVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  ulong uVar5;
  uint uVar6;
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 in_ZMM0 [64];
  double dVar9;
  undefined1 in_ZMM1 [64];
  uint uVar10;
  uint uVar16;
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auStack_16f1 [22];
  byte abStack_16db [10];
  undefined1 auStack_16d1 [22];
  byte abStack_16bb [10];
  undefined1 auStack_16b1 [17];
  undefined8 uStack_16a0;
  byte local_1698 [5760];
  undefined1 local_18 [16];
  
  local_18 = vpunpcklqdq_avx(in_ZMM0._0_16_,in_ZMM1._0_16_);
  auVar11._0_8_ = local_18._0_8_ + _DAT_01000840;
  auVar11._8_8_ = local_18._8_8_ + _UNK_01000848;
  auVar11 = vroundpd_avx(auVar11,9);
  uVar10 = (uint)auVar11._0_8_;
  uVar16 = (uint)auVar11._8_8_;
  auVar12._0_8_ = CONCAT44(uVar16,uVar10);
  bVar2 = 0x31;
  if (uVar16 < 0x60 && uVar10 < 0x60) {
    bVar2 = (&DAT_0140665c)[(ulong)uVar10 + (ulong)uVar16 * 0x60];
    if ((bVar2 - 0x2e < 0x29) && ((0x15000000001U >> ((ulong)(bVar2 - 0x2e) & 0x3f) & 1) != 0))
    goto LAB_011ee68f;
  }
  auVar12._8_8_ = auVar12._0_8_;
  auVar11 = vpblendd_avx2(auVar12,_DAT_01000950,0xc);
  auVar12 = vpblendd_avx2(_DAT_01000950,auVar12,0xc);
  auVar11 = vpcmpgtd_avx(auVar12,auVar11);
  iVar4 = vmovmskps_avx(auVar11);
  if (iVar4 != 0xf) {
    return 0;
  }
  if (bVar2 != 0x44) {
    return 0;
  }
  if ((&DAT_01404219)[(ulong)uVar10 + (ulong)uVar16 * 0x60] != '\x01') {
    return 0;
  }
LAB_011ee68f:
  auVar7._8_8_ = 0;
  auVar7._0_8_ = in_ZMM0._0_8_ + DAT_01000be8;
  auVar11 = vroundsd_avx(auVar7,auVar7,9);
  uVar3 = (uint)auVar11._0_8_;
  if (0x5f < uVar3) {
    return 0;
  }
  if (0x5f < uVar16) {
    return 0;
  }
  uVar6 = (byte)(&DAT_0140665c)[(ulong)uVar3 + (ulong)uVar16 * 0x60] - 0x2e;
  if (0x28 < uVar6) {
    return 0;
  }
  if ((0x15000000001U >> ((ulong)uVar6 & 0x3f) & 1) == 0) {
    if ((ulong)uVar6 != 0x16) {
      return 0;
    }
    if ((&DAT_01404219)[(ulong)uVar3 + (ulong)uVar16 * 0x60] != '\x01') {
      return 0;
    }
  }
  auVar8._8_8_ = 0;
  auVar8._0_8_ = in_ZMM1._0_8_ + DAT_01000be8;
  auVar11 = vroundsd_avx(auVar8,auVar8,9);
  if (0x5f < (uint)(int)auVar11._0_8_) {
    return 0;
  }
  uVar5 = (ulong)(uint)(int)auVar11._0_8_;
  uVar16 = (byte)(&DAT_0140665c)[(ulong)uVar10 + uVar5 * 0x60] - 0x2e;
  if (uVar16 < 0x29) {
    if ((0x15000000001U >> ((ulong)uVar16 & 0x3f) & 1) == 0) {
      if ((ulong)uVar16 != 0x16) {
        return 0;
      }
      if ((&DAT_01404219)[(ulong)uVar10 + uVar5 * 0x60] != '\x01') {
        return 0;
      }
    }
    uVar10 = (byte)(&DAT_0140665c)[(ulong)uVar3 + uVar5 * 0x60] - 0x2e;
    if (0x28 < uVar10) {
      return 0;
    }
    if ((0x15000000001U >> ((ulong)uVar10 & 0x3f) & 1) == 0) {
      if ((ulong)uVar10 != 0x16) {
        return 0;
      }
      if ((&DAT_01404219)[(ulong)uVar3 + uVar5 * 0x60] == '\0') {
        return 0;
      }
    }
    uStack_16a0 = 0x11ee76e;
    FUN_011f4580(local_1698,&DAT_01263f68,0x1680);
    lVar1 = 0x59;
    do {
      if (((abStack_16db[lVar1 + 3] & 1) != 0) && ((abStack_16db[lVar1 + 2] & 1) != 0)) {
        dVar9 = DAT_01000e30;
        if ((abStack_16db[lVar1] & 7) != 3) {
          dVar9 = *(double *)(&DAT_011b8710 + (ulong)((abStack_16db[lVar1] ^ 4) & 7) * 8);
        }
        auVar11 = vsubpd_avx(*(undefined1 (*) [16])(auStack_16f1 + lVar1),local_18);
        auVar14._0_8_ = auVar11._0_8_ * auVar11._0_8_;
        auVar14._8_8_ = auVar11._8_8_ * auVar11._8_8_;
        auVar11 = vshufpd_avx(auVar14,auVar14,1);
        if (auVar14._0_8_ + auVar11._0_8_ < dVar9 * dVar9) {
          return 0;
        }
      }
      if (((abStack_16bb[lVar1 + 3] & 1) != 0) && ((abStack_16bb[lVar1 + 2] & 1) != 0)) {
        dVar9 = DAT_01000e30;
        if ((abStack_16bb[lVar1] & 7) != 3) {
          dVar9 = *(double *)(&DAT_011b8710 + (ulong)((abStack_16bb[lVar1] ^ 4) & 7) * 8);
        }
        auVar11 = vsubpd_avx(*(undefined1 (*) [16])(auStack_16d1 + lVar1),local_18);
        auVar15._0_8_ = auVar11._0_8_ * auVar11._0_8_;
        auVar15._8_8_ = auVar11._8_8_ * auVar11._8_8_;
        auVar11 = vshufpd_avx(auVar15,auVar15,1);
        if (auVar15._0_8_ + auVar11._0_8_ < dVar9 * dVar9) {
          return 0;
        }
      }
      if (((local_1698[lVar1] & 1) != 0) && ((local_1698[lVar1 + -1] & 1) != 0)) {
        dVar9 = DAT_01000e30;
        if ((local_1698[lVar1 + -3] & 7) != 3) {
          dVar9 = *(double *)(&DAT_011b8710 + (ulong)((local_1698[lVar1 + -3] ^ 4) & 7) * 8);
        }
        auVar11 = vsubpd_avx(*(undefined1 (*) [16])(auStack_16b1 + lVar1),local_18);
        auVar13._0_8_ = auVar11._0_8_ * auVar11._0_8_;
        auVar13._8_8_ = auVar11._8_8_ * auVar11._8_8_;
        auVar11 = vshufpd_avx(auVar13,auVar13,1);
        if (auVar13._0_8_ + auVar11._0_8_ < dVar9 * dVar9) {
          return 0;
        }
      }
      lVar1 = lVar1 + 0x60;
      if (lVar1 == 0x16d9) {
        return 1;
      }
    } while( true );
  }
  return 0;
}


// ---- FUN_011ee950 @ 011ee950

void FUN_011ee950(undefined8 *param_1,undefined8 *param_2,undefined1 param_3,undefined4 param_4)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  
  puVar2 = (undefined8 *)&DAT_01261a68;
  if (((((((DAT_01261a8f._1_1_ == '\0') ||
          (puVar2 = (undefined8 *)&DAT_01261a98, DAT_01261abf._1_1_ != '\x01')) ||
         (puVar2 = (undefined8 *)&DAT_01261ac8, DAT_01261aef._1_1_ != '\x01')) ||
        ((puVar2 = (undefined8 *)&DAT_01261af8, DAT_01261b1f._1_1_ != '\x01' ||
         (puVar2 = (undefined8 *)&DAT_01261b28, DAT_01261b4f._1_1_ != '\x01')))) ||
       ((puVar2 = (undefined8 *)&DAT_01261b58, DAT_01261b7f._1_1_ != '\x01' ||
        ((puVar2 = (undefined8 *)&DAT_01261b88, DAT_01261baf._1_1_ != '\x01' ||
         (puVar2 = (undefined8 *)&DAT_01261bb8, DAT_01261bdf._1_1_ != '\x01')))))) ||
      ((puVar2 = (undefined8 *)&DAT_01261be8, DAT_01261c0f._1_1_ != '\x01' ||
       (((puVar2 = (undefined8 *)&DAT_01261c18, DAT_01261c3f._1_1_ != '\x01' ||
         (puVar2 = (undefined8 *)&DAT_01261c48, DAT_01261c6f._1_1_ != '\x01')) ||
        (puVar2 = (undefined8 *)&DAT_01261c78, DAT_01261c9f._1_1_ != '\x01')))))) ||
     ((((((puVar2 = (undefined8 *)&DAT_01261ca8, DAT_01261ccf._1_1_ != '\x01' ||
          (puVar2 = (undefined8 *)&DAT_01261cd8, DAT_01261cff._1_1_ != '\x01')) ||
         ((puVar2 = (undefined8 *)&DAT_01261d08, DAT_01261d2f._1_1_ != '\x01' ||
          ((puVar2 = (undefined8 *)&DAT_01261d38, DAT_01261d5f._1_1_ != '\x01' ||
           (puVar2 = (undefined8 *)&DAT_01261d68, DAT_01261d8f._1_1_ != '\x01')))))) ||
        ((puVar2 = (undefined8 *)&DAT_01261d98, DAT_01261dbf._1_1_ != '\x01' ||
         (((((puVar2 = (undefined8 *)&DAT_01261dc8, DAT_01261def._1_1_ != '\x01' ||
             (puVar2 = (undefined8 *)&DAT_01261df8, DAT_01261e1f._1_1_ != '\x01')) ||
            (puVar2 = (undefined8 *)&DAT_01261e28, DAT_01261e4f._1_1_ != '\x01')) ||
           ((puVar2 = (undefined8 *)&DAT_01261e58, DAT_01261e7f._1_1_ != '\x01' ||
            (puVar2 = (undefined8 *)&DAT_01261e88, DAT_01261eaf._1_1_ != '\x01')))) ||
          (((puVar2 = (undefined8 *)&DAT_01261eb8, DAT_01261edf._1_1_ != '\x01' ||
            ((puVar2 = (undefined8 *)&DAT_01261ee8, DAT_01261f0f._1_1_ != '\x01' ||
             (puVar2 = (undefined8 *)&DAT_01261f18, DAT_01261f3f._1_1_ != '\x01')))) ||
           ((puVar2 = (undefined8 *)&DAT_01261f48, DAT_01261f6f._1_1_ != '\x01' ||
            ((((puVar2 = (undefined8 *)&DAT_01261f78, DAT_01261f9f._1_1_ != '\x01' ||
               (puVar2 = (undefined8 *)&DAT_01261fa8, DAT_01261fcf._1_1_ != '\x01')) ||
              (puVar2 = (undefined8 *)&DAT_01261fd8, DAT_01261fff._1_1_ != '\x01')) ||
             ((puVar2 = (undefined8 *)&DAT_01262008, DAT_0126202f._1_1_ != '\x01' ||
              (puVar2 = (undefined8 *)&DAT_01262038, DAT_0126205f._1_1_ != '\x01')))))))))))))) ||
       (((((puVar2 = (undefined8 *)&DAT_01262068, DAT_0126208f._1_1_ != '\x01' ||
           ((puVar2 = (undefined8 *)&DAT_01262098, DAT_012620bf._1_1_ != '\x01' ||
            (puVar2 = (undefined8 *)&DAT_012620c8, DAT_012620ef._1_1_ != '\x01')))) ||
          (puVar2 = (undefined8 *)&DAT_012620f8, DAT_0126211f._1_1_ != '\x01')) ||
         (((puVar2 = (undefined8 *)&DAT_01262128, DAT_0126214f._1_1_ != '\x01' ||
           (puVar2 = (undefined8 *)&DAT_01262158, DAT_0126217f._1_1_ != '\x01')) ||
          (puVar2 = (undefined8 *)&DAT_01262188, DAT_012621af._1_1_ != '\x01')))) ||
        (((((puVar2 = (undefined8 *)&DAT_012621b8, DAT_012621df._1_1_ != '\x01' ||
            (puVar2 = (undefined8 *)&DAT_012621e8, DAT_0126220f._1_1_ != '\x01')) ||
           ((puVar2 = (undefined8 *)&DAT_01262218, DAT_0126223f._1_1_ != '\x01' ||
            ((puVar2 = (undefined8 *)&DAT_01262248, DAT_0126226f._1_1_ != '\x01' ||
             (puVar2 = (undefined8 *)&DAT_01262278, DAT_0126229f._1_1_ != '\x01')))))) ||
          (puVar2 = (undefined8 *)&DAT_012622a8, DAT_012622cf._1_1_ != '\x01')) ||
         (((puVar2 = (undefined8 *)&DAT_012622d8, DAT_012622ff._1_1_ != '\x01' ||
           (puVar2 = (undefined8 *)&DAT_01262308, DAT_0126232f._1_1_ != '\x01')) ||
          (puVar2 = (undefined8 *)&DAT_01262338, DAT_0126235f._1_1_ != '\x01')))))))) ||
      (((((puVar2 = (undefined8 *)&DAT_01262368, DAT_0126238f._1_1_ != '\x01' ||
          (puVar2 = (undefined8 *)&DAT_01262398, DAT_012623bf._1_1_ != '\x01')) ||
         ((puVar2 = (undefined8 *)&DAT_012623c8, DAT_012623ef._1_1_ != '\x01' ||
          ((puVar2 = (undefined8 *)&DAT_012623f8, DAT_0126241f._1_1_ != '\x01' ||
           (puVar2 = (undefined8 *)&DAT_01262428, DAT_0126244f._1_1_ != '\x01')))))) ||
        (puVar2 = (undefined8 *)&DAT_01262458, DAT_0126247f._1_1_ != '\x01')) ||
       ((((((puVar2 = (undefined8 *)&DAT_01262488, DAT_012624af._1_1_ != '\x01' ||
            (puVar2 = (undefined8 *)&DAT_012624b8, DAT_012624df._1_1_ != '\x01')) ||
           (puVar2 = (undefined8 *)&DAT_012624e8, DAT_0126250f._1_1_ != '\x01')) ||
          ((puVar2 = (undefined8 *)&DAT_01262518, DAT_0126253f._1_1_ != '\x01' ||
           (puVar2 = (undefined8 *)&DAT_01262548, DAT_0126256f._1_1_ != '\x01')))) ||
         (puVar2 = (undefined8 *)&DAT_01262578, DAT_0126259f._1_1_ != '\x01')) ||
        (((puVar2 = (undefined8 *)&DAT_012625a8, DAT_012625cf._1_1_ != '\x01' ||
          (puVar2 = (undefined8 *)&DAT_012625d8, DAT_012625ff._1_1_ != '\x01')) ||
         ((puVar2 = (undefined8 *)&DAT_01262608, DAT_0126262f._1_1_ != '\x01' ||
          (puVar2 = (undefined8 *)&DAT_01262638, DAT_0126265f._1_1_ == '\0')))))))))))) {
    uVar1 = param_1[1];
    *puVar2 = *param_1;
    puVar2[1] = uVar1;
    uVar1 = param_2[1];
    puVar2[2] = *param_2;
    puVar2[3] = uVar1;
    *(undefined1 *)((long)puVar2 + 0x26) = param_3;
    *(undefined4 *)(puVar2 + 4) = param_4;
    *(undefined2 *)((long)puVar2 + 0x24) = 300;
    *(undefined2 *)((long)puVar2 + 0x27) = 0x101;
  }
  return;
}


// ---- FUN_011eede0 @ 011eede0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_011eede0(uint param_1,long param_2)

{
  double dVar1;
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  double dVar6;
  double dVar7;
  ulong uVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  long lVar12;
  ulong uVar13;
  ulong uVar14;
  uint uVar15;
  ulong uVar16;
  undefined1 in_ZMM0 [64];
  undefined1 in_ZMM1 [64];
  undefined1 auVar17 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [32];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  undefined1 auVar24 [16];
  undefined1 auVar25 [32];
  undefined1 auVar26 [32];
  undefined1 auVar27 [16];
  undefined1 auVar28 [16];
  undefined1 auVar29 [16];
  undefined1 auVar30 [16];
  undefined1 auVar18 [32];
  
  dVar11 = DAT_01001058;
  dVar10 = DAT_01000f38;
  dVar9 = DAT_01000cd8;
  uVar8 = DAT_01000c08;
  dVar7 = DAT_01000a18;
  dVar6 = DAT_010009f0;
  auVar5 = _DAT_01000650;
  auVar3 = vpunpcklqdq_avx(in_ZMM0._0_16_,in_ZMM1._0_16_);
  lVar12 = -0x1900;
  auVar17._8_8_ = DAT_01000f88;
  auVar17._0_8_ = DAT_01000f88;
  auVar18._16_8_ = DAT_01000f88;
  auVar18._0_16_ = auVar17;
  auVar18._24_8_ = DAT_01000f88;
  auVar27._8_8_ = 0;
  auVar27._0_8_ = DAT_010010f0;
  auVar28 = ZEXT816(0);
  uVar13 = DAT_01261420;
  do {
    if (param_2 == 0) {
      return;
    }
    if (*(char *)(lVar12 + 0x1263f8e) == '\0') {
      uVar13 = uVar13 << 0xd ^ uVar13;
      uVar13 = uVar13 >> 7 ^ uVar13;
      uVar14 = uVar13 << 0x11 ^ uVar13;
      uVar14 = uVar14 << 0xd ^ uVar14;
      uVar14 = uVar14 >> 7 ^ uVar14;
      uVar16 = uVar14 << 0x11 ^ uVar14;
      auVar19._8_8_ = 0;
      auVar19._0_8_ = uVar13;
      auVar29._8_8_ = 0;
      auVar29._0_8_ = uVar14;
      auVar4 = vpunpcklqdq_avx(auVar19,auVar29);
      uVar16 = uVar16 << 0xd ^ uVar16;
      uVar16 = uVar16 >> 7 ^ uVar16;
      uVar13 = uVar16 << 0x11 ^ uVar16;
      uVar13 = uVar13 << 0xd ^ uVar13;
      uVar13 = uVar13 >> 7 ^ uVar13;
      auVar22._8_8_ = 0;
      auVar22._0_8_ = uVar16;
      auVar30._8_8_ = 0;
      auVar30._0_8_ = uVar13;
      auVar19 = vpunpcklqdq_avx(auVar22,auVar30);
      auVar4 = vpshufb_avx(auVar4,auVar5);
      auVar4 = vcvtdq2pd_avx(auVar4);
      auVar2 = vdivpd_avx(auVar4,auVar17);
      auVar4 = vpshufb_avx(auVar19,auVar5);
      auVar4 = vcvtdq2pd_avx(auVar4);
      auVar25._16_16_ = auVar4;
      auVar25._0_16_ = auVar3;
      auVar25 = vdivpd_avx(auVar25,auVar18);
      auVar21._0_8_ = (auVar2._0_8_ + dVar6) * dVar7 + auVar3._0_8_;
      auVar21._8_8_ = (auVar2._8_8_ + dVar6) * dVar7 + auVar3._8_8_;
      auVar21._16_8_ = (dVar6 + 0.0) * 0.0 + dVar10;
      auVar21._24_8_ = (dVar6 + 0.0) * 0.0 + dVar10;
      auVar26._0_8_ = (auVar25._0_8_ + dVar6) * auVar3._0_8_;
      auVar26._8_8_ = (auVar25._8_8_ + dVar6) * auVar3._8_8_;
      auVar26._16_8_ = (auVar25._16_8_ + dVar6) * dVar10;
      auVar26._24_8_ = (auVar25._24_8_ + dVar6) * dVar10;
      auVar25 = vblendpd_avx(auVar21,auVar26,0xc);
      *(undefined1 (*) [32])(&DAT_01263f68 + lVar12) = auVar25;
      uVar13 = uVar13 << 0x11 ^ uVar13;
      uVar13 = uVar13 << 0xd ^ uVar13;
      uVar13 = uVar13 >> 7 ^ uVar13;
      dVar1 = (double)((ulong)((double)((uint)uVar13 & 0xffff) / DAT_01000f88 + DAT_010009f0) &
                      uVar8) * dVar11 + dVar9;
      auVar23._8_8_ = 0;
      auVar23._0_8_ = dVar1 * (double)(param_1 >> 0x10 & 0xff);
      auVar4 = vminsd_avx(auVar23,auVar27);
      auVar4 = vmaxsd_avx(auVar4,auVar28);
      auVar24._8_8_ = 0;
      auVar24._0_8_ = dVar1 * (double)(param_1 >> 8 & 0xff);
      auVar2 = vminsd_avx(auVar24,auVar27);
      auVar2 = vmaxsd_avx(auVar2,auVar28);
      auVar20._8_8_ = 0;
      auVar20._0_8_ = dVar1 * (double)(param_1 & 0xff);
      auVar19 = vminsd_avx(auVar20,auVar27);
      auVar19 = vmaxsd_avx(auVar19,auVar28);
      uVar13 = uVar13 << 0x11 ^ uVar13;
      *(uint *)(lVar12 + 0x1263f88) =
           (int)auVar19._0_8_ & 0xffU |
           ((int)auVar2._0_8_ & 0xffU) << 8 | ((int)auVar4._0_8_ & 0xffU) << 0x10;
      uVar13 = uVar13 << 0xd ^ uVar13;
      uVar13 = uVar13 >> 7 ^ uVar13;
      uVar16 = uVar13 << 0x11 ^ uVar13;
      auVar4._8_8_ = 0;
      auVar4._0_8_ = uVar16;
      uVar15 = SUB164(auVar4 * ZEXT816(0x8888888888888889),8) >> 4;
      *(char *)(lVar12 + 0x1263f8c) =
           (char)uVar13 + ((char)uVar15 * '\x02' - (char)(uVar15 << 5)) + '\x12';
      uVar16 = uVar16 << 0xd ^ uVar16;
      uVar16 = uVar16 >> 7 ^ uVar16;
      uVar13 = uVar16 << 0x11 ^ uVar16;
      auVar2._8_8_ = 0;
      auVar2._0_8_ = uVar13;
      DAT_01261420 = uVar13;
      *(char *)(lVar12 + 0x1263f8d) =
           (char)uVar16 + (char)(SUB164(auVar2 * ZEXT816(0xaaaaaaaaaaaaaaab),8) >> 1) * -3 + '\x01';
      *(undefined1 *)(lVar12 + 0x1263f8e) = 1;
      param_2 = param_2 + -1;
    }
    lVar12 = lVar12 + 0x28;
  } while (lVar12 != 0);
  return;
}


// ---- FUN_011ef0b0 @ 011ef0b0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_011ef0b0(void)

{
  int iVar1;
  ushort uVar2;
  short sVar3;
  short sVar4;
  ulong uVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  long lVar9;
  ushort uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  ushort auStack_4820 [9216];
  
  lVar9 = 0;
  FUN_011f4160(&DAT_01404219,0,0x2400);
  uVar5 = 0;
  lVar6 = 0;
  do {
    lVar8 = 0;
    do {
      sVar3 = (short)lVar9;
      sVar4 = (short)lVar8;
      if (((&DAT_0140665c)[lVar8 + lVar9] == 'V') && ((&DAT_01401e18)[lVar8 + lVar9] == '\x01')) {
        (&DAT_01404219)[lVar8 + lVar9] = 1;
        auStack_4820[uVar5] = sVar3 + sVar4;
        uVar5 = uVar5 + 1;
      }
      if (((&DAT_0140665d)[lVar8 + lVar9] == 'V') && ((&DAT_01401e19)[lVar8 + lVar9] == '\x01')) {
        (&DAT_0140421a)[lVar8 + lVar9] = 1;
        auStack_4820[uVar5] = sVar3 + sVar4 + 1;
        uVar5 = uVar5 + 1;
      }
      if (((&DAT_0140665e)[lVar8 + lVar9] == 'V') && ((&DAT_01401e1a)[lVar8 + lVar9] == '\x01')) {
        (&DAT_0140421b)[lVar8 + lVar9] = 1;
        auStack_4820[uVar5] = sVar3 + sVar4 + 2;
        uVar5 = uVar5 + 1;
      }
      if (((&DAT_0140665f)[lVar8 + lVar9] == 'V') && ((&DAT_01401e1b)[lVar8 + lVar9] == '\x01')) {
        (&DAT_0140421c)[lVar8 + lVar9] = 1;
        auStack_4820[uVar5] = sVar3 + sVar4 + 3;
        uVar5 = uVar5 + 1;
      }
      lVar8 = lVar8 + 4;
    } while (lVar8 != 0x60);
    lVar6 = lVar6 + 1;
    lVar9 = lVar9 + 0x60;
  } while (lVar6 != 0x60);
  if (uVar5 != 0) {
    uVar7 = 0;
    do {
      uVar2 = auStack_4820[uVar7];
      uVar11 = uVar2 / 0x60;
      uVar12 = (uint)uVar2 % 0x60;
      uVar10 = (ushort)uVar12;
      if (0xffffffa1 < uVar11 - 0x5f && uVar10 < 0x5e) {
        lVar6 = (ulong)uVar12 + 1;
        if ((((byte)(&DAT_0140665c)[lVar6 + (ulong)(uVar11 * 0x60)] - 0x44 < 0x13) &&
            ((0x44801U >> ((byte)(&DAT_0140665c)[lVar6 + (ulong)(uVar11 * 0x60)] - 0x44 & 0x1f) & 1)
             != 0)) && ((&DAT_01404219)[lVar6 + (ulong)(uVar11 * 0x60)] == '\0')) {
          (&DAT_01404219)[lVar6 + (ulong)(uVar11 * 0x60)] = 1;
          auStack_4820[uVar5] = (short)uVar11 * 0x60 + (short)lVar6;
          uVar5 = uVar5 + 1;
        }
      }
      if (1 < uVar10 && 0xffffffa1 < uVar11 - 0x5f) {
        uVar13 = uVar12 - 1;
        if ((((byte)(&DAT_0140665c)[(ulong)uVar13 + (ulong)(uVar11 * 0x60)] - 0x44 < 0x13) &&
            ((0x44801U >>
              ((byte)(&DAT_0140665c)[(ulong)uVar13 + (ulong)(uVar11 * 0x60)] - 0x44 & 0x1f) & 1) !=
             0)) && ((&DAT_01404219)[(ulong)uVar13 + (ulong)(uVar11 * 0x60)] == '\0')) {
          (&DAT_01404219)[(ulong)uVar13 + (ulong)(uVar11 * 0x60)] = 1;
          auStack_4820[uVar5] = (short)uVar11 * 0x60 + (short)uVar13;
          uVar5 = uVar5 + 1;
        }
      }
      if (uVar2 < 0x2340 && 0xffffffa1 < uVar12 - 0x5f) {
        iVar1 = uVar11 + 1;
        if ((((byte)(&DAT_0140665c)[(ulong)uVar12 + (ulong)(uint)(iVar1 * 0x60)] - 0x44 < 0x13) &&
            ((0x44801U >>
              ((byte)(&DAT_0140665c)[(ulong)uVar12 + (ulong)(uint)(iVar1 * 0x60)] - 0x44 & 0x1f) & 1
             ) != 0)) && ((&DAT_01404219)[(ulong)uVar12 + (ulong)(uint)(iVar1 * 0x60)] == '\0')) {
          (&DAT_01404219)[(ulong)uVar12 + (ulong)(uint)(iVar1 * 0x60)] = 1;
          auStack_4820[uVar5] = (short)iVar1 * 0x60 + uVar10;
          uVar5 = uVar5 + 1;
        }
      }
      if (0xffffffa1 < uVar11 - 0x60 && 0xffffffa1 < uVar12 - 0x5f) {
        lVar6 = (ulong)(uVar11 - 1) * 0x60;
        if ((((byte)(&DAT_0140665c)[(ulong)uVar12 + lVar6] - 0x44 < 0x13) &&
            ((0x44801U >> ((byte)(&DAT_0140665c)[(ulong)uVar12 + lVar6] - 0x44 & 0x1f) & 1) != 0))
           && ((&DAT_01404219)[(ulong)uVar12 + lVar6] == '\0')) {
          (&DAT_01404219)[(ulong)uVar12 + lVar6] = 1;
          auStack_4820[uVar5] = (short)(uVar11 - 1) * 0x60 + uVar10;
          uVar5 = uVar5 + 1;
        }
      }
      uVar7 = uVar7 + 1;
    } while (uVar7 < uVar5);
  }
  if (DAT_0140662f == '\x01') {
    _DAT_01404a16 = 0x1010101;
    _DAT_01404a1a = 0x101;
    DAT_0140483b = 1;
  }
  DAT_0140661d = 0;
  return;
}


// ---- FUN_011ef430 @ 011ef430

void FUN_011ef430(double param_1,double *param_2)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  long lVar6;
  byte bVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  double dVar12;
  undefined1 auVar13 [16];
  undefined1 in_ZMM0 [64];
  double dVar14;
  undefined1 in_ZMM1 [64];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  double dVar17;
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  double dVar24;
  double dVar25;
  double dVar26;
  undefined1 auVar27 [64];
  double dVar28;
  undefined1 auVar29 [16];
  undefined1 auVar30 [64];
  double dVar31;
  undefined1 auVar32 [16];
  double dVar33;
  undefined1 auVar34 [16];
  
  auVar15._8_8_ = 0;
  auVar15._0_8_ = DAT_01261428;
  auVar15 = vroundsd_avx(auVar15,auVar15,9);
  uVar4 = (uint)auVar15._0_8_;
  auVar16._8_8_ = 0;
  auVar16._0_8_ = DAT_01261430;
  auVar32 = vroundsd_avx(auVar16,auVar16,9);
  dVar12 = in_ZMM0._0_8_;
  auVar21._0_8_ = DAT_01000c08 & (ulong)(DAT_01000bf8 / dVar12);
  auVar21._8_8_ = 0;
  auVar15 = vcmpsd_avx(ZEXT816(0),in_ZMM0._0_16_,0);
  auVar29._8_8_ = 0;
  auVar29._0_8_ = DAT_01000dd8;
  auVar15 = vblendvpd_avx(auVar21,auVar29,auVar15);
  dVar14 = in_ZMM1._0_8_;
  auVar18._0_8_ = DAT_01000c08 & (ulong)(DAT_01000bf8 / dVar14);
  auVar18._8_8_ = 0;
  auVar16 = vcmpsd_avx(ZEXT816(0),in_ZMM1._0_16_,0);
  auVar16 = vblendvpd_avx(auVar18,auVar29,auVar16);
  dVar24 = auVar32._0_8_;
  if (0.0 <= dVar12) {
    dVar25 = (double)(int)(uVar4 + 1) - DAT_01261428;
  }
  else {
    dVar25 = DAT_01261428 - (double)(int)uVar4;
  }
  if (dVar14 < 0.0) {
    dVar26 = DAT_01261430 - (double)(int)dVar24;
  }
  else {
    dVar26 = (double)((int)dVar24 + 1) - DAT_01261430;
  }
  uVar5 = (uint)dVar24;
  iVar10 = (uint)(0.0 <= dVar12) * 2 + -1;
  iVar11 = (uint)(0.0 <= dVar14) * 2 + -1;
  dVar24 = auVar15._0_8_;
  auVar27 = ZEXT864((ulong)(dVar24 * dVar25));
  dVar25 = auVar16._0_8_;
  auVar30 = ZEXT864((ulong)(dVar25 * dVar26));
  lVar6 = 0x100;
  do {
    dVar28 = auVar30._0_8_;
    dVar26 = auVar27._0_8_;
    bVar1 = dVar26 < dVar28;
    if (dVar28 <= dVar26) {
      auVar34._8_8_ = 0;
      auVar34._0_8_ = dVar25 + dVar28;
      uVar8 = uVar5 + iVar11;
      uVar9 = uVar4;
      auVar32 = auVar27._0_16_;
    }
    else {
      auVar32._8_8_ = 0;
      auVar32._0_8_ = dVar24 + dVar26;
      uVar9 = uVar4 + iVar10;
      uVar8 = uVar5;
      auVar34 = auVar30._0_16_;
    }
    dVar31 = auVar32._0_8_;
    dVar26 = dVar31 - dVar24;
    dVar33 = auVar34._0_8_;
    dVar28 = dVar33 - dVar25;
    auVar15 = vcmpsd_avx(auVar27._0_16_,auVar30._0_16_,1);
    auVar19._8_8_ = 0;
    auVar19._0_8_ = dVar26;
    auVar22._8_8_ = 0;
    auVar22._0_8_ = dVar28;
    auVar15 = vblendvpd_avx(auVar22,auVar19,auVar15);
    dVar17 = auVar15._0_8_;
    if (param_1 < dVar17) break;
    bVar7 = 0x31;
    if ((uVar9 < 0x60) && (uVar8 < 0x60)) {
      bVar7 = (&DAT_0140665c)[(ulong)uVar9 + (ulong)uVar8 * 0x60];
      if ((0x28 < bVar7 - 0x2e) || ((0x15000000001U >> ((ulong)(bVar7 - 0x2e) & 0x3f) & 1) == 0))
      goto LAB_011ef5d0;
    }
    else {
LAB_011ef5d0:
      uVar2 = uVar4;
      uVar3 = uVar5;
      if ((((bVar7 != 0x44) || ((int)uVar9 < 0)) || ((int)uVar8 < 0)) ||
         (((0x5f < (int)uVar9 || (0x5f < (int)uVar8)) ||
          ((&DAT_01404219)[(ulong)uVar9 + (ulong)uVar8 * 0x60] == '\0')))) goto joined_r0x011ef710;
    }
    bVar1 = dVar31 < dVar33;
    if (dVar33 <= dVar31) {
      auVar30 = ZEXT864((ulong)(dVar25 + dVar33));
      uVar5 = uVar8 + iVar11;
      auVar27 = ZEXT1664(auVar32);
      uVar4 = uVar9;
    }
    else {
      auVar27 = ZEXT864((ulong)(dVar24 + dVar31));
      auVar30 = ZEXT1664(auVar34);
      uVar4 = uVar9 + iVar10;
      uVar5 = uVar8;
    }
    dVar26 = auVar27._0_8_ - dVar24;
    dVar28 = auVar30._0_8_ - dVar25;
    auVar15 = vcmpsd_avx(auVar32,auVar34,1);
    auVar20._8_8_ = 0;
    auVar20._0_8_ = dVar26;
    auVar23._8_8_ = 0;
    auVar23._0_8_ = dVar28;
    auVar15 = vblendvpd_avx(auVar23,auVar20,auVar15);
    dVar17 = auVar15._0_8_;
    if (param_1 < dVar17) break;
    bVar7 = 0x31;
    if ((uVar4 < 0x60) && (uVar5 < 0x60)) {
      bVar7 = (&DAT_0140665c)[(ulong)uVar4 + (ulong)uVar5 * 0x60];
      if ((0x28 < bVar7 - 0x2e) || ((0x15000000001U >> ((ulong)(bVar7 - 0x2e) & 0x3f) & 1) == 0))
      goto LAB_011ef6b0;
    }
    else {
LAB_011ef6b0:
      uVar2 = uVar9;
      uVar9 = uVar4;
      uVar3 = uVar8;
      uVar8 = uVar5;
      if (((((bVar7 != 0x44) || ((int)uVar4 < 0)) || ((int)uVar5 < 0)) ||
          ((0x5f < (int)uVar4 || (0x5f < (int)uVar5)))) ||
         ((&DAT_01404219)[(ulong)uVar4 + (ulong)uVar5 * 0x60] != '\x01')) {
joined_r0x011ef710:
        if (bVar1) {
          dVar12 = DAT_01261430 + dVar14 * dVar26;
        }
        else {
          dVar12 = DAT_01261428 + dVar12 * dVar28;
        }
        auVar13._8_8_ = 0;
        auVar13._0_8_ = dVar12;
        auVar15 = vroundsd_avx(auVar13,auVar13,9);
        *(undefined1 *)(param_2 + 5) = 1;
        *(uint *)(param_2 + 2) = uVar9;
        *(uint *)((long)param_2 + 0x14) = uVar8;
        *(uint *)(param_2 + 3) = uVar2;
        *(uint *)((long)param_2 + 0x1c) = uVar3;
        *param_2 = dVar17;
        *(byte *)(param_2 + 4) = bVar7;
        *(bool *)((long)param_2 + 0x21) = bVar1;
        param_2[1] = dVar12 - auVar15._0_8_;
        return;
      }
    }
    lVar6 = lVar6 + -2;
  } while (lVar6 != 0);
  param_2[2] = 0.0;
  param_2[3] = 0.0;
  param_2[4] = 0.0;
  param_2[5] = 0.0;
  *param_2 = 0.0;
  param_2[1] = 0.0;
  param_2[2] = 0.0;
  param_2[3] = 0.0;
  return;
}


// ---- FUN_011ef760 @ 011ef760

void FUN_011ef760(void)

{
  long lVar1;
  ulong uVar2;
  ulong uVar3;
  
  uVar2 = (ulong)DAT_0140661e * -0x61c8864680b583eb + 0x9e3779b97f4a7c15 ^ 0x243f6a8885a308d3;
  uVar3 = (uVar2 >> 0x33 | uVar2 << 0xd) * -0x40a7b892e31b1a47;
  uVar2 = (ulong)DAT_0140661f * -0x61c8874680b5825a + 0x9e3778b97f4a7da6 ^ uVar3;
  uVar3 = (uVar2 >> 0x33 | (uVar3 >> 0x1d ^ uVar2) << 0xd) * -0x40a7b892e31b1a47;
  uVar2 = (ulong)DAT_01406620 * -0x61c8844680b5808d + 0x9e377bb97f4a7f73 ^ uVar3;
  uVar3 = (uVar2 >> 0x33 | (uVar3 >> 0x1d ^ uVar2) << 0xd) * -0x40a7b892e31b1a47;
  uVar2 = (ulong)DAT_01406621 * -0x61c8854680b586f4 + 0x9e377ab97f4a790c ^ uVar3;
  uVar3 = (uVar2 >> 0x33 | (uVar3 >> 0x1d ^ uVar2) << 0xd) * -0x40a7b892e31b1a47;
  uVar2 = (ulong)DAT_01406622 * -0x61c8824680b58527 + 0x9e377db97f4a7ad9 ^ uVar3;
  uVar3 = (uVar2 >> 0x33 | (uVar3 >> 0x1d ^ uVar2) << 0xd) * -0x40a7b892e31b1a47;
  uVar2 = (ulong)DAT_01406623 * -0x61c8834680b58b96 + 0x9e377cb97f4a746a ^ uVar3;
  uVar3 = (uVar2 >> 0x33 | (uVar3 >> 0x1d ^ uVar2) << 0xd) * -0x40a7b892e31b1a47;
  uVar2 = (ulong)DAT_01406624 * -0x61c8804680b589d9 + 0x9e377fb97f4a7627 ^ uVar3;
  uVar3 = (uVar2 >> 0x33 | (uVar3 >> 0x1d ^ uVar2) << 0xd) * -0x40a7b892e31b1a47;
  uVar2 = (ulong)DAT_01406625 * -0x61c8814680b58810 + 0x9e377eb97f4a77f0 ^ uVar3;
  uVar3 = (uVar2 >> 0x33 | (uVar3 >> 0x1d ^ uVar2) << 0xd) * -0x40a7b892e31b1a47;
  uVar2 = (ulong)DAT_01406626 * -0x61c88e4680b58e73 + 0x9e3771b97f4a718d ^ uVar3;
  uVar3 = (uVar2 >> 0x33 | (uVar3 >> 0x1d ^ uVar2) << 0xd) * -0x40a7b892e31b1a47;
  uVar2 = (ulong)DAT_01406627 * -0x61c88f4680b58ca2 + 0x9e3770b97f4a735e ^ uVar3;
  uVar3 = (uVar2 >> 0x33 | (uVar3 >> 0x1d ^ uVar2) << 0xd) * -0x40a7b892e31b1a47;
  uVar2 = (ulong)DAT_01406628 * -0x61c88c4680b59315 + 0x9e3773b97f4a6ceb ^ uVar3;
  uVar3 = (uVar2 >> 0x33 | (uVar3 >> 0x1d ^ uVar2) << 0xd) * -0x40a7b892e31b1a47;
  uVar2 = (ulong)DAT_01406629 * -0x61c88d4680b5915c + 0x9e3772b97f4a6ea4 ^ uVar3;
  uVar3 = (uVar2 >> 0x33 | (uVar3 >> 0x1d ^ uVar2) << 0xd) * -0x40a7b892e31b1a47;
  uVar2 = (ulong)DAT_0140662a * -0x61c88a4680b5978f + 0x9e3775b97f4a6871 ^ uVar3;
  uVar3 = (uVar2 >> 0x33 | (uVar3 >> 0x1d ^ uVar2) << 0xd) * -0x40a7b892e31b1a47;
  uVar2 = (ulong)DAT_0140662b * -0x61c88b4680b595fe + 0x9e3774b97f4a6a02 ^ uVar3;
  uVar3 = (uVar2 >> 0x33 | (uVar3 >> 0x1d ^ uVar2) << 0xd) * -0x40a7b892e31b1a47;
  uVar2 = (ulong)DAT_0140662c * -0x61c8884680b59421 + 0x9e3777b97f4a6bdf ^ uVar3;
  uVar3 = (uVar2 >> 0x33 | (uVar3 >> 0x1d ^ uVar2) << 0xd) * -0x40a7b892e31b1a47;
  uVar2 = (ulong)DAT_0140662d * -0x61c8894680b59a98 + 0x9e3776b97f4a6568 ^ uVar3;
  uVar2 = (uVar2 >> 0x33 | (uVar3 >> 0x1d ^ uVar2) << 0xd) * -0x40a7b892e31b1a47;
  uVar2 = uVar2 ^ 0x13198a2e03707344 ^ uVar2 >> 0x1d;
  lVar1 = -0x27;
  do {
    uVar2 = uVar2 >> 0xc ^ uVar2;
    uVar2 = uVar2 << 0x19 ^ uVar2;
    uVar2 = uVar2 >> 0x1b ^ uVar2;
    (&DAT_01406657)[lVar1] = (byte)(uVar2 * 0x2545f4914f6cdd1d >> 0x38) ^ (&DAT_0100f7fc)[lVar1];
    uVar2 = uVar2 >> 0xc ^ uVar2;
    uVar2 = uVar2 << 0x19 ^ uVar2;
    uVar2 = uVar2 >> 0x1b ^ uVar2;
    (&DAT_01406658)[lVar1] = (byte)(uVar2 * 0x2545f4914f6cdd1d >> 0x38) ^ (&UNK_0100f7fd)[lVar1];
    uVar2 = uVar2 >> 0xc ^ uVar2;
    uVar2 = uVar2 << 0x19 ^ uVar2;
    uVar2 = uVar2 >> 0x1b ^ uVar2;
    (&DAT_01406659)[lVar1] = (byte)(uVar2 * 0x2545f4914f6cdd1d >> 0x38) ^ (&DAT_0100f7fe)[lVar1];
    lVar1 = lVar1 + 3;
  } while (lVar1 != 0);
  DAT_01406657 = 0x27;
  return;
}


// ---- FUN_011efb20 @ 011efb20

void FUN_011efb20(undefined2 *param_1,char param_2)

{
  undefined2 *puVar1;
  
  puVar1 = &DAT_0100f816;
  if ((byte)(param_2 - 0x31U) < 0x26) {
    puVar1 = (undefined2 *)(&PTR_DAT_011b8748)[(byte)(param_2 - 0x31U)];
  }
  *param_1 = *puVar1;
  return;
}


// ---- FUN_011efb50 @ 011efb50

byte FUN_011efb50(char param_1,char param_2)

{
  byte bVar1;
  byte bVar2;
  
  bVar2 = param_1 - 0x31;
  if ((bVar2 < 0x26) && ((0x2eca9e001fU >> ((ulong)bVar2 & 0x3f) & 1) != 0)) {
    bVar1 = (byte)((&DAT_011b8878)[bVar2] + param_2) / (byte)(param_2 + 1U);
    bVar2 = 1;
    if (1 < bVar1) {
      bVar2 = bVar1;
    }
    return bVar2;
  }
  return 0xff;
}


// ---- FUN_011efba0 @ 011efba0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_011efba0(void)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  ulong uVar4;
  ulong uVar5;
  ushort uVar6;
  ulong uVar7;
  bool bVar8;
  
  uVar4 = DAT_01261420 << 0xd ^ DAT_01261420;
  uVar4 = uVar4 >> 7 ^ uVar4;
  uVar5 = uVar4 << 0x11 ^ uVar4;
  uVar6 = ((ushort)uVar4 & 3) + 2;
  bVar8 = CARRY2(uVar6,DAT_01401e02);
  DAT_01401e02 = uVar6 + DAT_01401e02;
  if (bVar8) {
    DAT_01401e02 = -1;
  }
  uVar5 = uVar5 << 0xd ^ uVar5;
  uVar5 = uVar5 >> 7 ^ uVar5;
  uVar7 = uVar5 << 0x11 ^ uVar5;
  auVar2._8_8_ = 0;
  auVar2._0_8_ = uVar7;
  uVar7 = uVar7 << 0xd ^ uVar7;
  uVar7 = uVar7 >> 7 ^ uVar7;
  uVar4 = uVar7 << 0x11 ^ uVar7;
  auVar2 = vpinsrw_avx(ZEXT416((int)uVar5 +
                               (SUB164(auVar2 * ZEXT816(0xcccccccccccccccd),8) >> 2) * -5),
                       (uint)uVar7 & 3,1);
  auVar1._0_2_ = auVar2._0_2_ + _DAT_01000580;
  auVar1._2_2_ = auVar2._2_2_ + _UNK_01000582;
  auVar1._4_2_ = auVar2._4_2_ + _UNK_01000584;
  auVar1._6_2_ = auVar2._6_2_ + _UNK_01000586;
  auVar1._8_2_ = auVar2._8_2_ + _UNK_01000588;
  auVar1._10_2_ = auVar2._10_2_ + _UNK_0100058a;
  auVar1._12_2_ = auVar2._12_2_ + _UNK_0100058c;
  auVar1._14_2_ = auVar2._14_2_ + _UNK_0100058e;
  auVar1 = vpaddusw_avx(ZEXT416(_DAT_01401dfe),auVar1);
  _DAT_01401dfe = auVar1._0_4_;
  uVar4 = uVar4 << 0xd ^ uVar4;
  uVar4 = uVar4 >> 7 ^ uVar4;
  DAT_01261420 = uVar4 << 0x11 ^ uVar4;
  if ((DAT_01261420 * -0x5555555555555555 < 0x5555555555555556) &&
     (DAT_01401e08 = DAT_01401e08 + 1, DAT_01401e08 == 0)) {
    DAT_01401e08 = -1;
  }
  if (DAT_01406659 != '\0') {
    uVar4 = DAT_01261420 << 0xd ^ DAT_01261420;
    uVar4 = uVar4 >> 7 ^ uVar4;
    DAT_01261420 = uVar4 << 0x11 ^ uVar4;
    auVar3._8_8_ = 0;
    auVar3._0_8_ = DAT_01261420;
    uVar6 = (short)uVar4 + (short)(SUB164(auVar3 * ZEXT816(0xaaaaaaaaaaaaaaab),8) >> 1) * -3 + 1;
    bVar8 = CARRY2(uVar6,DAT_01401e0a);
    uVar6 = uVar6 + DAT_01401e0a;
    DAT_01401e0a = 0xffff;
    if (!bVar8) {
      DAT_01401e0a = uVar6;
    }
  }
  DAT_01261458 = DAT_01261458 + 0x14;
  if (DAT_0126145c < DAT_01261458) {
    DAT_01261458 = DAT_0126145c;
  }
  FUN_011eede0(0xffcd3c,0x1a);
  DAT_0140661c = 5;
  return;
}


// ---- FUN_011efd50 @ 011efd50

void FUN_011efd50(byte param_1,uint param_2,uint param_3)

{
  if ((param_1 & 3) == 0) {
    if ((DAT_01401e16 & 7) != 0) {
      return;
    }
    if (DAT_01401e14 < 4) {
      DAT_01404218 = 1;
      DAT_01401df8 = 0xb4;
      return;
    }
    DAT_01404218 = 2;
    DAT_01401e16 = 1;
  }
  else if ((param_1 & 3) == 1) {
    if ((DAT_01401e16 & 7) != 2) {
      return;
    }
    if ((DAT_01406619 < 2) || (DAT_0140661a < 2)) {
      DAT_01404218 = 4;
      DAT_01401df8 = 0xb4;
      return;
    }
    DAT_01404218 = 6;
    DAT_01401e16 = 3;
  }
  else {
    if ((DAT_01401e16 & 7) != 4) {
      return;
    }
    if ((DAT_01406619 < 3) || (DAT_0140661a < 3)) {
      DAT_01404218 = 5;
      DAT_01401df8 = 0xb4;
      return;
    }
    DAT_01404218 = 8;
    DAT_01401e16 = 5;
  }
  DAT_01401df8 = 0xb4;
  (&DAT_0140665c)[(ulong)param_2 + (ulong)param_3 * 0x60] = 0x2e;
  FUN_011ed370(param_1);
  return;
}


// ---- FUN_011efe30 @ 011efe30

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_011efe30(void)

{
  double dVar1;
  double dVar2;
  undefined8 uVar3;
  byte bVar4;
  uint uVar5;
  int iVar6;
  undefined8 *puVar7;
  uint uVar8;
  long lVar9;
  ulong uVar10;
  ulong uVar11;
  undefined1 *puVar12;
  undefined1 uVar13;
  double *pdVar14;
  long lVar15;
  int iVar16;
  uint uVar17;
  uint uVar18;
  int iVar19;
  char cVar20;
  int iVar21;
  ulong uVar22;
  uint uVar23;
  uint uVar24;
  uint uVar25;
  uint uVar26;
  uint uVar27;
  uint uVar28;
  uint uVar29;
  ulong uVar30;
  bool bVar31;
  float fVar32;
  undefined1 auVar33 [16];
  double adStack_17d1 [3];
  byte abStack_17b8 [7];
  double adStack_17b1 [3];
  byte abStack_1798 [7];
  double adStack_1791 [3];
  byte abStack_1778 [7];
  double adStack_1771 [3];
  byte abStack_1758 [7];
  double adStack_1751 [3];
  byte local_1738 [5760];
  ulong local_b8;
  ulong local_b0;
  ulong local_a8;
  long local_a0;
  ulong local_98;
  ulong local_90;
  long local_88;
  ulong local_80;
  ulong local_78;
  uint local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  double local_58;
  double local_50;
  long local_48;
  ulong local_40;
  byte local_31;
  
  stack0xffffffffffffe8c0 = 0x11efe58;
  FUN_011f4580(&DAT_01260018,&DAT_0100f828,0x1a8a48);
  stack0xffffffffffffe8c0 = 0x11efe6c;
  FUN_011f4160(&DAT_0140665c,0x31,0x2400);
  stack0xffffffffffffe8c0 = 0x11efe85;
  FUN_011f1840(6,6,0x26,0x18);
  stack0xffffffffffffe8c0 = 0x11efe9e;
  FUN_011f1840(0x26,0x18,0x48,0x4c);
  stack0xffffffffffffe8c0 = 0x11efeb7;
  FUN_011f1840(0x48,0x4c,0x56);
  lVar9 = 0;
  uVar10 = DAT_01261420;
  do {
    uVar10 = uVar10 << 0xd ^ uVar10;
    uVar10 = uVar10 >> 7 ^ uVar10;
    uVar10 = uVar10 << 0x11 ^ uVar10;
    uVar11 = uVar10 << 0xd ^ uVar10;
    uVar11 = uVar11 >> 7 ^ uVar11;
    DAT_01261420 = uVar11 << 0x11 ^ uVar11;
    uVar11 = (ulong)((int)uVar10 + (int)(uVar10 / 0x56) * -0x56 + 5);
    uVar25 = (int)DAT_01261420 + (int)(DAT_01261420 / 0x56) * -0x56 + 5;
    stack0xffffffffffffe8c0 = 0x11eff7a;
    local_88 = lVar9;
    FUN_011f1840(6,6,uVar11);
    uVar10 = DAT_01261420;
    lVar9 = 0;
    do {
      local_a8 = uVar11;
      local_a0 = lVar9;
      uVar10 = uVar10 << 0xd ^ uVar10;
      uVar10 = uVar10 >> 7 ^ uVar10;
      local_98 = uVar10 << 0x11 ^ uVar10;
      bVar31 = local_98 * -0x71c71c71c71c71c7 < 0x1c71c71c71c71c72;
      uVar17 = ~(uint)bVar31;
      uVar18 = (uint)bVar31 * 3 + 3;
      iVar21 = -(uint)bVar31;
      uVar5 = (uint)local_a8;
      local_58 = (double)(ulong)(uVar5 - bVar31);
      iVar6 = uVar17 + 2;
      local_50 = (double)CONCAT44(local_50._4_4_,iVar6);
      uVar8 = uVar18 - iVar6 * iVar6;
      local_48 = CONCAT44(local_48._4_4_,uVar8);
      local_68 = uVar17 + 3;
      local_b8 = (ulong)(uint)(local_68 * local_68);
      local_64 = uVar17 + 4;
      local_b0 = (ulong)(uint)(local_64 * local_64);
      local_5c = (uVar17 + 5) * (uVar17 + 5);
      iVar19 = bVar31 + 1;
      local_60 = uVar5 - 1;
      iVar16 = uVar17 - 1;
      uVar24 = uVar17 + uVar5;
      local_6c = uVar17 + 1 + uVar5;
      uVar26 = uVar17 + 2 + uVar5;
      local_40 = (ulong)uVar26;
      uVar27 = uVar17 + 3 + uVar5;
      local_80 = (ulong)uVar27;
      uVar28 = uVar17 + 4 + uVar5;
      local_78 = (ulong)uVar28;
      local_90 = (ulong)(uVar17 + uVar5 + 5);
      do {
        if ((uVar25 - 1) + uVar17 < 0x5e) {
          uVar29 = uVar17 * uVar17;
          uVar23 = uVar25 + uVar17;
          if (((uint)bVar31 * 3 + 1 + uVar29 <= uVar18) && (iVar16 + uVar5 < 0x5e)) {
            (&DAT_0140665c)[(ulong)uVar24 + (ulong)uVar23 * 0x60] = 0x2e;
          }
          if ((iVar21 * iVar21 + uVar29 <= uVar18) && (uVar24 < 0x5e)) {
            (&DAT_0140665c)[(long)local_58 + (ulong)uVar23 * 0x60] = 0x2e;
          }
          if (iVar21 != iVar19) {
            if ((uVar29 <= uVar8) && (local_6c < 0x5e)) {
              (&DAT_0140665c)[local_40 + (ulong)uVar23 * 0x60] = 0x2e;
            }
            if (iVar6 != iVar19) {
              if ((local_68 * local_68 + uVar29 <= uVar18) && (uVar26 < 0x5e)) {
                (&DAT_0140665c)[local_80 + (ulong)uVar23 * 0x60] = 0x2e;
              }
              if (local_68 != iVar19) {
                if ((local_64 * local_64 + uVar29 <= uVar18) && (uVar27 < 0x5e)) {
                  (&DAT_0140665c)[local_78 + (ulong)uVar23 * 0x60] = 0x2e;
                }
                if (((local_64 != iVar19) && (uVar29 + local_5c <= uVar18)) && (uVar28 < 0x5e)) {
                  (&DAT_0140665c)[local_90 + (ulong)uVar23 * 0x60] = 0x2e;
                }
              }
            }
          }
        }
        uVar17 = uVar17 + 1;
      } while ((bVar31 | 2) != uVar17);
      uVar11 = local_98 << 0xd ^ local_98;
      uVar11 = uVar11 >> 7 ^ uVar11;
      uVar10 = uVar11 << 0x11 ^ uVar11;
      uVar10 = uVar10 << 0xd ^ uVar10;
      uVar10 = uVar10 >> 7 ^ uVar10;
      uVar10 = uVar10 << 0x11 ^ uVar10;
      iVar16 = (int)uVar10 + (int)(uVar10 / 3) * -3;
      uVar8 = (uVar25 - 1) + iVar16;
      if ((uVar11 & 1) == 0) {
        uVar5 = local_60 + iVar16;
        uVar8 = uVar25;
      }
      if ((int)uVar5 < 3) {
        uVar5 = 2;
      }
      if (0x5c < (int)uVar5) {
        uVar5 = 0x5d;
      }
      if ((int)uVar8 < 3) {
        uVar8 = 2;
      }
      uVar25 = uVar8;
      if (0x5c < (int)uVar8) {
        uVar25 = 0x5d;
      }
      lVar9 = local_a0 + 1;
      uVar11 = (ulong)uVar5;
    } while (local_a0 + 1 != 0x5a);
    lVar9 = local_88 + 1;
  } while (lVar9 != 0x48);
  puVar12 = &DAT_0140671d;
  uVar11 = 0;
  DAT_01261420 = uVar10;
  do {
    if (uVar11 < 0x40) {
      uVar22 = 0;
      do {
        if ((puVar12[uVar22 - 0x60] == '1') &&
           (((puVar12[uVar22 - 0xc0] == '.' || (puVar12[uVar22] == '.')) ||
            ((puVar12[uVar22 - 0x61] == '.' || (puVar12[uVar22 - 0x5f] == '.')))))) {
          uVar10 = uVar10 << 0xd ^ uVar10;
          uVar10 = uVar10 >> 7 ^ uVar10;
          uVar10 = uVar10 << 0x11 ^ uVar10;
          uVar30 = uVar10 % 1000;
          if (uVar22 < 0x21 && 0x1b < uVar11) {
            cVar20 = 'E';
            if (((0x22 < uVar30) && (cVar20 = '3', 0x77 < uVar30)) && (cVar20 = 'J', 0xc2 < uVar30))
            {
              cVar20 = (uVar30 < 0xff) * '\x02' + '2';
            }
          }
          else if (uVar22 < 0x3d || 0x38 < uVar11) {
            cVar20 = 'E';
            if (((0x25 < uVar30) && (cVar20 = '5', 0x59 < uVar30)) &&
               ((cVar20 = '4', 0x9f < uVar30 && (cVar20 = '3', 0xf4 < uVar30)))) {
              cVar20 = (uVar30 < 0x186) + '1';
            }
          }
          else {
            cVar20 = 'E';
            if (((0x27 < uVar30) && (cVar20 = 'C', 0x65 < uVar30)) && (cVar20 = '5', 0xa4 < uVar30))
            {
              cVar20 = '1';
              if (uVar30 < 0xe6) {
                cVar20 = 'S';
              }
            }
          }
          DAT_01261420 = uVar10;
          puVar12[uVar22 - 0x60] = cVar20;
        }
        uVar22 = uVar22 + 1;
      } while (uVar22 != 0x5e);
    }
    else {
      lVar9 = -0x5e;
      do {
        if ((puVar12[lVar9 + -2] == '1') &&
           (((puVar12[lVar9 + -0x62] == '.' || (puVar12[lVar9 + 0x5e] == '.')) ||
            ((puVar12[lVar9 + -3] == '.' || (puVar12[lVar9 + -1] == '.')))))) {
          uVar10 = uVar10 << 0xd ^ uVar10;
          uVar10 = uVar10 >> 7 ^ uVar10;
          uVar10 = uVar10 << 0x11 ^ uVar10;
          uVar22 = uVar10 % 1000;
          uVar13 = 0x45;
          if ((((0x25 < uVar22) && (uVar13 = 0x48, 0x6d < uVar22)) && (uVar13 = 0x42, 0xea < uVar22)
              ) && (uVar13 = 0x43, 299 < uVar22)) {
            uVar13 = 0x31;
          }
          DAT_01261420 = uVar10;
          puVar12[lVar9 + -2] = uVar13;
        }
        lVar9 = lVar9 + 1;
      } while (lVar9 != 0);
    }
    uVar11 = uVar11 + 1;
    puVar12 = puVar12 + 0x60;
  } while (uVar11 != 0x5e);
  lVar9 = -6;
  puVar12 = (undefined1 *)((long)((long)(BADSPACEBASE *)0x0 + 0x1406d9d) + 6);
  while( true ) {
    if (lVar9 == 0) {
      *(undefined8 *)(puVar12 + -0x62) = 0x2e2e2e2e2e2e2e2e;
      *(undefined8 *)(puVar12 + -0x67) = 0x2e2e2e2e2e2e2e2e;
    }
    else {
      uVar10 = lVar9 * lVar9;
      if (uVar10 < 0xe) {
        *(undefined8 *)(puVar12 + -0x66) = 0x2e2e2e2e2e2e2e2e;
        *(undefined4 *)(puVar12 + -0x5f) = 0x2e2e2e2e;
      }
      else if (uVar10 < 0x17) {
        *(undefined8 *)(puVar12 + -0x65) = 0x2e2e2e2e2e2e2e2e;
        puVar12[-0x5d] = 0x2e;
      }
      else if (uVar10 < 0x1e) {
        *(undefined4 *)(puVar12 + -0x61) = 0x2e2e2e2e;
        *(undefined4 *)(puVar12 + -100) = 0x2e2e2e2e;
      }
      else if (uVar10 < 0x23) {
        puVar12[-0x5f] = 0x2e;
        *(undefined4 *)(puVar12 + -99) = 0x2e2e2e2e;
      }
      else if (uVar10 < 0x26) {
        *(undefined2 *)(puVar12 + -0x62) = 0x2e2e;
        puVar12[-0x60] = 0x2e;
      }
    }
    if (lVar9 == 6) break;
    uVar10 = (lVar9 + 1) * (lVar9 + 1);
    if (uVar10 < 3) {
      *(undefined8 *)(puVar12 + -2) = 0x2e2e2e2e2e2e2e2e;
      *(undefined8 *)(puVar12 + -7) = 0x2e2e2e2e2e2e2e2e;
    }
    else if (uVar10 < 0xe) {
      *(undefined8 *)(puVar12 + -6) = 0x2e2e2e2e2e2e2e2e;
      *(undefined4 *)(puVar12 + 1) = 0x2e2e2e2e;
    }
    else if (uVar10 < 0x17) {
      *(undefined8 *)(puVar12 + -5) = 0x2e2e2e2e2e2e2e2e;
      puVar12[3] = 0x2e;
    }
    else if (uVar10 < 0x1e) {
      *(undefined4 *)(puVar12 + -1) = 0x2e2e2e2e;
      *(undefined4 *)(puVar12 + -4) = 0x2e2e2e2e;
    }
    else if (uVar10 < 0x23) {
      puVar12[1] = 0x2e;
      *(undefined4 *)(puVar12 + -3) = 0x2e2e2e2e;
    }
    else if (uVar10 < 0x26) {
      *(undefined2 *)(puVar12 + -2) = 0x2e2e;
      *puVar12 = 0x2e;
    }
    lVar9 = lVar9 + 2;
    puVar12 = puVar12 + 0xc0;
  }
  DAT_01406f7d._5_1_ = 0x47;
  DAT_01406dfd._5_1_ = 0x54;
  DAT_01407102 = 0x54;
  lVar9 = -6;
  puVar12 = (undefined1 *)((long)&DAT_01408201 + 6);
  while( true ) {
    if (lVar9 == 0) {
      *(undefined8 *)(puVar12 + -0x62) = 0x2e2e2e2e2e2e2e2e;
      *(undefined8 *)(puVar12 + -0x67) = 0x2e2e2e2e2e2e2e2e;
    }
    else {
      uVar10 = lVar9 * lVar9;
      if (uVar10 < 0xe) {
        *(undefined8 *)(puVar12 + -0x66) = 0x2e2e2e2e2e2e2e2e;
        *(undefined4 *)(puVar12 + -0x5f) = 0x2e2e2e2e;
      }
      else if (uVar10 < 0x17) {
        *(undefined8 *)(puVar12 + -0x65) = 0x2e2e2e2e2e2e2e2e;
        puVar12[-0x5d] = 0x2e;
      }
      else if (uVar10 < 0x1e) {
        *(undefined4 *)(puVar12 + -0x61) = 0x2e2e2e2e;
        *(undefined4 *)(puVar12 + -100) = 0x2e2e2e2e;
      }
      else if (uVar10 < 0x23) {
        puVar12[-0x5f] = 0x2e;
        *(undefined4 *)(puVar12 + -99) = 0x2e2e2e2e;
      }
      else if (uVar10 < 0x26) {
        *(undefined2 *)(puVar12 + -0x62) = 0x2e2e;
        puVar12[-0x60] = 0x2e;
      }
    }
    if (lVar9 == 6) break;
    uVar10 = (lVar9 + 1) * (lVar9 + 1);
    if (uVar10 < 3) {
      *(undefined8 *)(puVar12 + -2) = 0x2e2e2e2e2e2e2e2e;
      *(undefined8 *)(puVar12 + -7) = 0x2e2e2e2e2e2e2e2e;
    }
    else if (uVar10 < 0xe) {
      *(undefined8 *)(puVar12 + -6) = 0x2e2e2e2e2e2e2e2e;
      *(undefined4 *)(puVar12 + 1) = 0x2e2e2e2e;
    }
    else if (uVar10 < 0x17) {
      *(undefined8 *)(puVar12 + -5) = 0x2e2e2e2e2e2e2e2e;
      puVar12[3] = 0x2e;
    }
    else if (uVar10 < 0x1e) {
      *(undefined4 *)(puVar12 + -1) = 0x2e2e2e2e;
      *(undefined4 *)(puVar12 + -4) = 0x2e2e2e2e;
    }
    else if (uVar10 < 0x23) {
      puVar12[1] = 0x2e;
      *(undefined4 *)(puVar12 + -3) = 0x2e2e2e2e;
    }
    else if (uVar10 < 0x26) {
      *(undefined2 *)(puVar12 + -2) = 0x2e2e;
      *puVar12 = 0x2e;
    }
    lVar9 = lVar9 + 2;
    puVar12 = puVar12 + 0xc0;
  }
  DAT_014083e1._5_1_ = 0x41;
  DAT_01408261._5_1_ = 0x54;
  DAT_01408566 = 0x54;
  lVar9 = -6;
  puVar12 = (undefined1 *)((long)&DAT_01406b8d + 6);
  while( true ) {
    if (lVar9 == 0) {
      *(undefined8 *)(puVar12 + -0x62) = 0x2e2e2e2e2e2e2e2e;
      *(undefined8 *)(puVar12 + -0x67) = 0x2e2e2e2e2e2e2e2e;
    }
    else {
      uVar10 = lVar9 * lVar9;
      if (uVar10 < 0xe) {
        *(undefined8 *)(puVar12 + -0x66) = 0x2e2e2e2e2e2e2e2e;
        *(undefined4 *)(puVar12 + -0x5f) = 0x2e2e2e2e;
      }
      else if (uVar10 < 0x17) {
        *(undefined8 *)(puVar12 + -0x65) = 0x2e2e2e2e2e2e2e2e;
        puVar12[-0x5d] = 0x2e;
      }
      else if (uVar10 < 0x1e) {
        *(undefined4 *)(puVar12 + -0x61) = 0x2e2e2e2e;
        *(undefined4 *)(puVar12 + -100) = 0x2e2e2e2e;
      }
      else if (uVar10 < 0x23) {
        puVar12[-0x5f] = 0x2e;
        *(undefined4 *)(puVar12 + -99) = 0x2e2e2e2e;
      }
      else if (uVar10 < 0x26) {
        *(undefined2 *)(puVar12 + -0x62) = 0x2e2e;
        puVar12[-0x60] = 0x2e;
      }
    }
    if (lVar9 == 6) break;
    uVar10 = (lVar9 + 1) * (lVar9 + 1);
    if (uVar10 < 3) {
      *(undefined8 *)(puVar12 + -2) = 0x2e2e2e2e2e2e2e2e;
      *(undefined8 *)(puVar12 + -7) = 0x2e2e2e2e2e2e2e2e;
    }
    else if (uVar10 < 0xe) {
      *(undefined8 *)(puVar12 + -6) = 0x2e2e2e2e2e2e2e2e;
      *(undefined4 *)(puVar12 + 1) = 0x2e2e2e2e;
    }
    else if (uVar10 < 0x17) {
      *(undefined8 *)(puVar12 + -5) = 0x2e2e2e2e2e2e2e2e;
      puVar12[3] = 0x2e;
    }
    else if (uVar10 < 0x1e) {
      *(undefined4 *)(puVar12 + -1) = 0x2e2e2e2e;
      *(undefined4 *)(puVar12 + -4) = 0x2e2e2e2e;
    }
    else if (uVar10 < 0x23) {
      puVar12[1] = 0x2e;
      *(undefined4 *)(puVar12 + -3) = 0x2e2e2e2e;
    }
    else if (uVar10 < 0x26) {
      *(undefined2 *)(puVar12 + -2) = 0x2e2e;
      *puVar12 = 0x2e;
    }
    lVar9 = lVar9 + 2;
    puVar12 = puVar12 + 0xc0;
  }
  DAT_01406d6d._5_1_ = 0x4d;
  DAT_01406bed._5_1_ = 0x54;
  DAT_01406ef2 = 0x54;
  uVar10 = 0;
  do {
    uVar11 = DAT_01261420 << 0xd ^ DAT_01261420;
    uVar11 = uVar11 >> 7 ^ uVar11;
    uVar11 = uVar11 << 0x11 ^ uVar11;
    uVar22 = uVar11 << 0xd ^ uVar11;
    lVar9 = uVar11 + (uVar11 / 5 & 0xfffffffffffffff0) * -5;
    uVar22 = uVar22 >> 7 ^ uVar22;
    DAT_01261420 = uVar22 << 0x11 ^ uVar22;
    lVar15 = (DAT_01261420 + (DAT_01261420 / 5 & 0xfffffffffffffff0) * -5) * 0x60;
    if ((&DAT_01406964)[lVar9 + lVar15] == '.') {
      (&DAT_01406964)[lVar9 + lVar15] = 0x51;
      uVar10 = uVar10 + 1;
    }
  } while (uVar10 < 0xe);
  _DAT_01406781 = 0x2e2e;
  DAT_01406783 = 0x2e;
  _DAT_014069c1 = 0x2e2e;
  DAT_014069c3 = 0x2e;
  _DAT_014067e0 = 0x2e2e2e2e;
  _DAT_0140683f = 0x2e2e2e2e;
  DAT_01406843 = 0x2e;
  _DAT_0140689f = 0x2e2e2e2e2e2e2e2e;
  _DAT_014068ff = 0x2e2e2e2e2e2e2e2e;
  _DAT_01406960 = 0x2e2e2e2e;
  DAT_01406964 = 0x2e;
  DAT_01406966 = 0x34;
  DAT_014069c6 = 0x35;
  _DAT_01406725 = 0x2e2e;
  DAT_01406727 = 0x2e;
  DAT_014068a7 = 0x2e;
  DAT_01406788 = 0x2e;
  _DAT_01406784 = 0x2e2e2e2e;
  _DAT_01406844 = 0x2e2e2e2e;
  DAT_01406848 = 0x2e;
  _DAT_014067e4 = 0x4f525256;
  DAT_014067e8 = 0x44;
  stack0xffffffffffffe8c0 = 0x11f0aaf;
  FUN_011f1840(6,6,0x18,0x19);
  uRam0000000001406b58 = (undefined1)((uint)DAT_01001474 >> 0x18);
  uRam0000000001406b59 = DAT_01001474;
  uRam0000000001406b5d = DAT_01001474;
  _DAT_01406b48 = DAT_01001474;
  uRam0000000001406b4c = DAT_01001474;
  uRam0000000001406b50 = DAT_01001474;
  uRam0000000001406b54 = DAT_01001474;
  DAT_01406ba8 = 0x53;
  auVar33._0_8_ = CONCAT44(DAT_01001480,DAT_01001480);
  auVar33._8_4_ = DAT_01001480;
  auVar33._12_4_ = DAT_01001480;
  _DAT_01406ba9 = auVar33._0_15_;
  DAT_01406bb8 = 0x2e;
  uRam0000000001406bb9 = 0x2e2e2e2e2e2e2e;
  DAT_01406bc0 = 0x53;
  DAT_01406c08 = 0x53;
  DAT_01406c09 = (undefined1)DAT_01001480;
  uRam0000000001406c1a = 0x2e2e2e2e2e2e;
  DAT_01406c20 = 0x53;
  DAT_01406c68 = 0x53;
  DAT_01406c78 = 0x2e;
  uRam0000000001406c79 = 0x2e2e2e2e2e;
  uRam0000000001406c7f = 0x2e;
  DAT_01406c80 = 0x53;
  DAT_01406cc8 = 0x53;
  DAT_01406cd8 = 0x2e;
  uRam0000000001406cd9 = 0x2e2e2e2e2e2e2e;
  DAT_01406ce0 = 0x53;
  DAT_01406d28 = 0x53;
  uRam0000000001406d39 = 0x2e2e2e2e2e2e2e;
  DAT_01406d38 = (undefined1)((uint)DAT_01001480 >> 0x18);
  DAT_01406d3e._2_1_ = 0x53;
  DAT_01406d88 = 0x53;
  DAT_01406d98 = 0x2e;
  uRam0000000001406d99 = 0x2e2e2e2e2e2e2e;
  DAT_01406d9d._3_1_ = 0x53;
  DAT_01406de8 = 0x53;
  _DAT_01406de9 = (undefined5)auVar33._0_8_;
  uRam0000000001406df6 = (undefined2)((uint)DAT_01001480 >> 8);
  DAT_01406df8 = 0x2e;
  uRam0000000001406df9 = 0x2e2e2e2e2e2e2e;
  DAT_01406dfd._3_1_ = 0x53;
  DAT_01406e48 = 0x53;
  DAT_01406e58 = 0x2e;
  DAT_01406e5d._2_1_ = 0x2e;
  DAT_01406e5d._3_1_ = 0x53;
  DAT_01406ea8 = 0x53;
  uRam0000000001406eb9 = 0x2e2e2e2e2e2e2e;
  DAT_01406ebc._4_1_ = 0x53;
  DAT_01406f08 = 0x53;
  DAT_01406f18 = 0x2e;
  uRam0000000001406f19 = 0x2e2e2e2e2e2e2e;
  DAT_01406f1c._4_1_ = 0x53;
  uRam0000000001406f79 = DAT_01001474;
  DAT_01406f7d._0_4_ = DAT_01001474;
  _DAT_01406f68 = DAT_01001474;
  uRam0000000001406f6c = DAT_01001474;
  uRam0000000001406f70 = (undefined1)DAT_01001474;
  _DAT_01406f71 = (undefined2)((uint)DAT_01001474 >> 8);
  uRam0000000001406f76 = (undefined2)((uint)DAT_01001474 >> 0x10);
  DAT_01406f73 = 0x2e;
  uRam0000000001406f74 = 0x2e;
  DAT_01406f75 = 0x2e;
  _DAT_01406c0a = s_fbgchadebhcfaged_010002a0._0_14_;
  DAT_01406c18 = s_fbgchadebhcfaged_010002a0[0xe];
  cRam0000000001406c19 = s_fbgchadebhcfaged_010002a0[0xf];
  _DAT_01406dee = 0x5656565656565656;
  _DAT_01406e59 = 0x52525252;
  DAT_01406e5d._0_2_ = 0x4452;
  DAT_01406c7e = 0x4f;
  uVar22 = 0;
  uVar10 = 0;
  uVar11 = DAT_01261420;
  _DAT_01406c69 = _DAT_01406ba9;
  _DAT_01406cc9 = _DAT_01406ba9;
  _DAT_01406d29 = _DAT_01406ba9;
  _DAT_01406d89 = _DAT_01406ba9;
  _DAT_01406e49 = _DAT_01406ba9;
  _DAT_01406ea9 = _DAT_01406ba9;
  DAT_01406eb8 = DAT_01406d38;
  _DAT_01406f09 = _DAT_01406ba9;
  uRam0000000001406f78 = uRam0000000001406b58;
  do {
    uVar11 = uVar11 << 0xd ^ uVar11;
    uVar11 = uVar11 >> 7 ^ uVar11;
    uVar30 = uVar11 << 0x11 ^ uVar11;
    uVar11 = uVar30 << 0xd ^ uVar30;
    uVar11 = uVar11 >> 7 ^ uVar11;
    uVar11 = uVar11 << 0x11 ^ uVar11;
    uVar3 = _UNK_01000408;
    if ((0x18 < uVar30 % 0x5a - 9) || (0xb < uVar11 % 0x5a - 10)) {
      uVar30 = uVar30 % 0x5a;
      lVar9 = uVar30 + 3;
      lVar15 = uVar11 % 0x5a + 3;
      if ((&DAT_0140665c)[lVar9 + lVar15 * 0x60] == '.') {
        local_58 = (double)lVar9 + DAT_01000ce0;
        local_50 = (double)lVar15 + DAT_01000ce0;
        stack0xffffffffffffe8c0 = 0x11f0d5f;
        local_48 = lVar9;
        local_40 = uVar11 % 0x5a;
        FUN_011f4580(local_1738,&DAT_01263f68,0x1680);
        lVar9 = 0x99;
        do {
          uVar3 = _UNK_01000408;
          if (((((((abStack_17b8[lVar9] & 1) != 0) &&
                 (dVar1 = *(double *)((long)adStack_17d1 + lVar9) - local_58,
                 dVar2 = *(double *)((long)adStack_17d1 + lVar9 + 8) - local_50,
                 dVar2 * dVar2 + dVar1 * dVar1 < DAT_01000b78)) ||
                (((abStack_1798[lVar9] & 1) != 0 &&
                 (dVar1 = *(double *)((long)adStack_17b1 + lVar9) - local_58,
                 dVar2 = *(double *)((long)adStack_17b1 + lVar9 + 8) - local_50,
                 dVar2 * dVar2 + dVar1 * dVar1 < DAT_01000b78)))) ||
               (((abStack_1778[lVar9] & 1) != 0 &&
                (dVar1 = *(double *)((long)adStack_1791 + lVar9) - local_58,
                dVar2 = *(double *)((long)adStack_1791 + lVar9 + 8) - local_50,
                dVar2 * dVar2 + dVar1 * dVar1 < DAT_01000b78)))) ||
              (((abStack_1758[lVar9] & 1) != 0 &&
               (dVar1 = *(double *)((long)adStack_1771 + lVar9) - local_58,
               dVar2 = *(double *)((long)adStack_1771 + lVar9 + 8) - local_50,
               dVar2 * dVar2 + dVar1 * dVar1 < DAT_01000b78)))) ||
             (((local_1738[lVar9] & 1) != 0 &&
              (dVar1 = *(double *)((long)adStack_1751 + lVar9) - local_58,
              dVar2 = *(double *)((long)adStack_1751 + lVar9 + 8) - local_50,
              dVar2 * dVar2 + dVar1 * dVar1 < DAT_01000b78)))) goto joined_r0x011f13cf;
          lVar9 = lVar9 + 0xa0;
        } while (lVar9 != 0x1719);
        iVar16 = (int)local_48 + -6;
        iVar6 = (int)lVar15 + -6;
        if (0x17 < (uint)(iVar6 * iVar6 + iVar16 * iVar16)) {
          if (local_40 < 0x3e) {
            if ((uVar30 < 0x21) && (0x17 < local_40)) {
              uVar11 = uVar11 << 0xd ^ uVar11;
              uVar11 = uVar11 >> 7 ^ uVar11;
              uVar11 = uVar11 << 0x11 ^ uVar11;
              uVar30 = uVar11 + (uVar11 / 5 & 0xfffffffffffffffe) * -5;
              local_31 = (6 < uVar30) * '\x03' + 3;
              if (uVar30 < 4) {
                local_31 = 1;
              }
              uVar11 = uVar11 << 0xd ^ uVar11;
              uVar11 = uVar11 >> 7 ^ uVar11;
              uVar11 = uVar11 << 0x11 ^ uVar11;
              if (local_31 != 1) {
                fVar32 = (float)((int)(uVar11 / 0x1e) * -0x1e + (int)uVar11) / DAT_010014b8 +
                         DAT_010014b4;
                goto LAB_011f11f0;
              }
              fVar32 = (float)((int)uVar11 + (int)(uVar11 / 0x23) * -0x23) / DAT_010014b8 +
                       DAT_01001468;
              bVar31 = true;
              lVar9 = 0;
              bVar4 = local_31;
            }
            else {
              uVar11 = uVar11 << 0xd ^ uVar11;
              uVar11 = uVar11 >> 7 ^ uVar11;
              uVar11 = uVar11 << 0x11 ^ uVar11;
              if ((uVar30 < 0x3a) || (0x37 < local_40)) {
                uVar30 = uVar11 + (uVar11 / 5 & 0xfffffffffffffffe) * -5;
                if (uVar30 < 3) {
                  local_31 = 0;
                }
                else {
                  local_31 = 3;
                  if (5 < uVar30) {
                    local_31 = (uVar30 < 8) - 3;
                  }
                }
                local_31 = local_31 & 7;
                uVar11 = uVar11 << 0xd ^ uVar11;
                uVar30 = uVar11 >> 7 ^ uVar11;
                uVar11 = uVar30 << 0x11 ^ uVar30;
                if (local_31 != 0) {
                  fVar32 = (float)((uint)uVar30 & 0x1f) / DAT_010014b8 + DAT_010014a8;
                  goto LAB_011f11f0;
                }
                fVar32 = (float)((int)(uVar11 / 0x1e) * -0x1e + (int)uVar11) / DAT_010014b8 +
                         DAT_01001498;
                bVar31 = true;
                lVar9 = 0;
                bVar4 = local_31;
              }
              else {
                local_31 = uVar11 % 5 < 3 ^ 5;
                uVar11 = uVar11 << 0xd ^ uVar11;
                uVar11 = uVar11 >> 7 ^ uVar11;
                uVar11 = uVar11 << 0x11 ^ uVar11;
                fVar32 = (float)((int)uVar11 + (int)(uVar11 / 0x23) * -0x23) / DAT_010014b8 +
                         DAT_0100147c;
                bVar31 = local_31 == 4;
                lVar9 = 0;
                bVar4 = local_31;
              }
            }
          }
          else {
            uVar11 = uVar11 << 0xd ^ uVar11;
            uVar30 = uVar11 >> 7 ^ uVar11;
            uVar11 = uVar30 << 0x11 ^ uVar30;
            local_31 = ((uVar30 & 3) != 0) * '\x03' + 2;
            bVar31 = true;
            if (local_31 == 2) {
              lVar9 = 0;
              bVar4 = local_31;
              fVar32 = DAT_0100146c;
            }
            else {
              uVar11 = uVar11 << 0xd ^ uVar11;
              uVar11 = uVar11 >> 7 ^ uVar11;
              uVar11 = uVar11 << 0x11 ^ uVar11;
              fVar32 = (float)((int)uVar11 + (int)(uVar11 / 0x23) * -0x23) / DAT_010014b8 +
                       DAT_01001488;
LAB_011f11f0:
              bVar31 = false;
              lVar9 = 0;
              bVar4 = local_31;
            }
          }
          do {
            if ((&DAT_01263f81)[lVar9] == '\0') {
              pdVar14 = (double *)(&DAT_01263f68 + lVar9);
LAB_011f1371:
              *pdVar14 = local_58;
              pdVar14[1] = local_50;
              *(byte *)((long)pdVar14 + 0x16) = bVar4;
              *(float *)(pdVar14 + 2) = fVar32;
              *(char *)((long)pdVar14 + 0x17) =
                   (char)(0x305070700010406 >> ((ulong)(bVar4 ^ 4) << 3));
              uVar11 = uVar11 << 0xd ^ uVar11;
              uVar30 = uVar11 >> 7 ^ uVar11;
              uVar11 = uVar30 << 0x11 ^ uVar30;
              *(short *)((long)pdVar14 + 0x14) = (short)uVar30;
              *(bool *)(pdVar14 + 3) = bVar31;
              *(undefined1 *)((long)pdVar14 + 0x19) = 1;
              uVar22 = uVar22 + 1;
              uVar3 = _UNK_01000408;
              goto joined_r0x011f13cf;
            }
            if ((&DAT_01263fa1)[lVar9] != '\x01') {
              pdVar14 = (double *)(lVar9 + 0x1263f88);
              goto LAB_011f1371;
            }
            if ((&DAT_01263fc1)[lVar9] != '\x01') {
              pdVar14 = (double *)(lVar9 + 0x1263fa8);
              goto LAB_011f1371;
            }
            if ((&DAT_01263fe1)[lVar9] != '\x01') {
              pdVar14 = (double *)(lVar9 + 0x1263fc8);
              goto LAB_011f1371;
            }
            if ((&DAT_01264001)[lVar9] != '\x01') {
              pdVar14 = (double *)(lVar9 + 0x1263fe8);
              goto LAB_011f1371;
            }
            if ((&DAT_01264021)[lVar9] != '\x01') {
              pdVar14 = (double *)(lVar9 + 0x1264008);
              goto LAB_011f1371;
            }
            if ((&DAT_01264041)[lVar9] != '\x01') {
              pdVar14 = (double *)(lVar9 + 0x1264028);
              goto LAB_011f1371;
            }
            if ((&DAT_01264061)[lVar9] != '\x01') {
              pdVar14 = (double *)(lVar9 + 0x1264048);
              goto LAB_011f1371;
            }
            if (*(char *)((long)&DAT_01264080 + lVar9 + 1) != '\x01') {
              pdVar14 = (double *)((long)&DAT_01264068 + lVar9);
              goto LAB_011f1371;
            }
            if (*(char *)((long)&DAT_012640a0 + lVar9 + 1) != '\x01') {
              pdVar14 = (double *)((long)&DAT_01264088 + lVar9);
              goto LAB_011f1371;
            }
            if (*(char *)((long)&DAT_012640c0 + lVar9 + 1) != '\x01') {
              pdVar14 = (double *)((long)&DAT_012640a8 + lVar9);
              goto LAB_011f1371;
            }
            if (*(char *)((long)&DAT_012640e0 + lVar9 + 1) != '\x01') {
              pdVar14 = (double *)((long)&DAT_012640c8 + lVar9);
              goto LAB_011f1371;
            }
            if (*(char *)((long)&DAT_01264100 + lVar9 + 1) != '\x01') {
              pdVar14 = (double *)((long)&DAT_012640e8 + lVar9);
              goto LAB_011f1371;
            }
            if (*(char *)((long)&DAT_01264120 + lVar9 + 1) != '\x01') {
              pdVar14 = (double *)((long)&DAT_01264108 + lVar9);
              goto LAB_011f1371;
            }
            if (*(char *)((long)&DAT_01264140 + lVar9 + 1) != '\x01') {
              pdVar14 = (double *)((long)&DAT_01264128 + lVar9);
              goto LAB_011f1371;
            }
            lVar9 = lVar9 + 0x1e0;
          } while (lVar9 != 0x1680);
          uVar22 = uVar22 + 1;
        }
      }
    }
joined_r0x011f13cf:
    _UNK_01000408 = uVar3;
  } while ((uVar22 < 0x91) && (bVar31 = uVar10 < 6999, uVar10 = uVar10 + 1, bVar31));
  lVar9 = 0;
  do {
    if ((&DAT_01263f81)[lVar9] == '\0') {
      puVar7 = (undefined8 *)(&DAT_01263f68 + lVar9);
LAB_011f157d:
      *puVar7 = _DAT_01000400;
      puVar7[1] = uVar3;
      *(undefined2 *)((long)puVar7 + 0x16) = 0x700;
      *(undefined4 *)(puVar7 + 2) = 0x3fa00000;
      uVar11 = uVar11 << 0xd ^ uVar11;
      uVar10 = uVar11 >> 7 ^ uVar11;
      uVar11 = uVar10 << 0x11 ^ uVar10;
      DAT_01261420 = uVar11;
      *(short *)((long)puVar7 + 0x14) = (short)uVar10;
      *(undefined2 *)(puVar7 + 3) = 0x101;
      break;
    }
    if ((&DAT_01263fa1)[lVar9] != '\x01') {
      puVar7 = (undefined8 *)(lVar9 + 0x1263f88);
      goto LAB_011f157d;
    }
    if ((&DAT_01263fc1)[lVar9] != '\x01') {
      puVar7 = (undefined8 *)(lVar9 + 0x1263fa8);
      goto LAB_011f157d;
    }
    if ((&DAT_01263fe1)[lVar9] != '\x01') {
      puVar7 = (undefined8 *)(lVar9 + 0x1263fc8);
      goto LAB_011f157d;
    }
    if ((&DAT_01264001)[lVar9] != '\x01') {
      puVar7 = (undefined8 *)(lVar9 + 0x1263fe8);
      goto LAB_011f157d;
    }
    if ((&DAT_01264021)[lVar9] != '\x01') {
      puVar7 = (undefined8 *)(lVar9 + 0x1264008);
      goto LAB_011f157d;
    }
    if ((&DAT_01264041)[lVar9] != '\x01') {
      puVar7 = (undefined8 *)(lVar9 + 0x1264028);
      goto LAB_011f157d;
    }
    if ((&DAT_01264061)[lVar9] != '\x01') {
      puVar7 = (undefined8 *)(lVar9 + 0x1264048);
      goto LAB_011f157d;
    }
    if (*(char *)((long)&DAT_01264080 + lVar9 + 1) != '\x01') {
      puVar7 = (undefined8 *)((long)&DAT_01264068 + lVar9);
      goto LAB_011f157d;
    }
    if (*(char *)((long)&DAT_012640a0 + lVar9 + 1) != '\x01') {
      puVar7 = (undefined8 *)((long)&DAT_01264088 + lVar9);
      goto LAB_011f157d;
    }
    if (*(char *)((long)&DAT_012640c0 + lVar9 + 1) != '\x01') {
      puVar7 = (undefined8 *)((long)&DAT_012640a8 + lVar9);
      goto LAB_011f157d;
    }
    if (*(char *)((long)&DAT_012640e0 + lVar9 + 1) != '\x01') {
      puVar7 = (undefined8 *)((long)&DAT_012640c8 + lVar9);
      goto LAB_011f157d;
    }
    if (*(char *)((long)&DAT_01264100 + lVar9 + 1) != '\x01') {
      puVar7 = (undefined8 *)((long)&DAT_012640e8 + lVar9);
      goto LAB_011f157d;
    }
    if (*(char *)((long)&DAT_01264120 + lVar9 + 1) != '\x01') {
      puVar7 = (undefined8 *)((long)&DAT_01264108 + lVar9);
      goto LAB_011f157d;
    }
    if (*(char *)((long)&DAT_01264140 + lVar9 + 1) != '\x01') {
      puVar7 = (undefined8 *)((long)&DAT_01264128 + lVar9);
      goto LAB_011f157d;
    }
    lVar9 = lVar9 + 0x1e0;
    DAT_01261420 = uVar11;
  } while (lVar9 != 0x1680);
  uVar3 = _UNK_010008c8;
  lVar9 = 0;
  do {
    if ((&DAT_01263f81)[lVar9] == '\0') {
      puVar7 = (undefined8 *)(&DAT_01263f68 + lVar9);
LAB_011f1726:
      *puVar7 = ram0x010008c0;
      puVar7[1] = uVar3;
      *(undefined2 *)((long)puVar7 + 0x16) = 0x303;
      *(undefined4 *)(puVar7 + 2) = 0x3f3851ec;
      uVar11 = uVar11 << 0xd ^ uVar11;
      uVar11 = uVar11 >> 7 ^ uVar11;
      DAT_01261420 = uVar11 << 0x11 ^ uVar11;
      *(short *)((long)puVar7 + 0x14) = (short)uVar11;
      *(undefined2 *)(puVar7 + 3) = 0x100;
      break;
    }
    if ((&DAT_01263fa1)[lVar9] != '\x01') {
      puVar7 = (undefined8 *)(lVar9 + 0x1263f88);
      goto LAB_011f1726;
    }
    if ((&DAT_01263fc1)[lVar9] != '\x01') {
      puVar7 = (undefined8 *)(lVar9 + 0x1263fa8);
      goto LAB_011f1726;
    }
    if ((&DAT_01263fe1)[lVar9] != '\x01') {
      puVar7 = (undefined8 *)(lVar9 + 0x1263fc8);
      goto LAB_011f1726;
    }
    if ((&DAT_01264001)[lVar9] != '\x01') {
      puVar7 = (undefined8 *)(lVar9 + 0x1263fe8);
      goto LAB_011f1726;
    }
    if ((&DAT_01264021)[lVar9] != '\x01') {
      puVar7 = (undefined8 *)(lVar9 + 0x1264008);
      goto LAB_011f1726;
    }
    if ((&DAT_01264041)[lVar9] != '\x01') {
      puVar7 = (undefined8 *)(lVar9 + 0x1264028);
      goto LAB_011f1726;
    }
    if ((&DAT_01264061)[lVar9] != '\x01') {
      puVar7 = (undefined8 *)(lVar9 + 0x1264048);
      goto LAB_011f1726;
    }
    if (*(char *)((long)&DAT_01264080 + lVar9 + 1) != '\x01') {
      puVar7 = (undefined8 *)((long)&DAT_01264068 + lVar9);
      goto LAB_011f1726;
    }
    if (*(char *)((long)&DAT_012640a0 + lVar9 + 1) != '\x01') {
      puVar7 = (undefined8 *)((long)&DAT_01264088 + lVar9);
      goto LAB_011f1726;
    }
    if (*(char *)((long)&DAT_012640c0 + lVar9 + 1) != '\x01') {
      puVar7 = (undefined8 *)((long)&DAT_012640a8 + lVar9);
      goto LAB_011f1726;
    }
    if (*(char *)((long)&DAT_012640e0 + lVar9 + 1) != '\x01') {
      puVar7 = (undefined8 *)((long)&DAT_012640c8 + lVar9);
      goto LAB_011f1726;
    }
    if (*(char *)((long)&DAT_01264100 + lVar9 + 1) != '\x01') {
      puVar7 = (undefined8 *)((long)&DAT_012640e8 + lVar9);
      goto LAB_011f1726;
    }
    if (*(char *)((long)&DAT_01264120 + lVar9 + 1) != '\x01') {
      puVar7 = (undefined8 *)((long)&DAT_01264108 + lVar9);
      goto LAB_011f1726;
    }
    if (*(char *)((long)&DAT_01264140 + lVar9 + 1) != '\x01') {
      puVar7 = (undefined8 *)((long)&DAT_01264128 + lVar9);
      goto LAB_011f1726;
    }
    lVar9 = lVar9 + 0x1e0;
  } while (lVar9 != 0x1680);
  _DAT_01406619 = 0x303;
  DAT_01401dfc = 0x10;
  DAT_01401e04 = 6;
  _DAT_01401e0c = 0x3000500030018;
  stack0xffffffffffffe8c0 = 0x11f179f;
  FUN_011ef0b0();
  stack0xffffffffffffe8c0 = 0x11f17b0;
  FUN_011ed370(0,0xf,0xc);
  stack0xffffffffffffe8c0 = 0x11f17c4;
  FUN_011ed370(1,0x17,0x11);
  stack0xffffffffffffe8c0 = 0x11f17d5;
  FUN_011ed370(0,0x1f,0x1b);
  stack0xffffffffffffe8c0 = 0x11f17e9;
  FUN_011ed370(1,0x2b,0x22);
  stack0xffffffffffffe8c0 = 0x11f17fd;
  FUN_011ed370(2,0x42,0x46);
  stack0xffffffffffffe8c0 = 0x11f1811;
  FUN_011ed370(2,0x4d,0x4e);
  FUN_011ed370(1,0x54,0x3e);
  return;
}


// ---- FUN_011f1840 @ 011f1840

void FUN_011f1840(uint param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  long lVar4;
  undefined1 *puVar5;
  uint uVar6;
  ulong uVar7;
  ulong uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  bool bVar20;
  bool bVar21;
  bool bVar22;
  
  bVar20 = param_1 != param_3;
  bVar21 = param_2 != param_4;
  if (bVar20 || bVar21) {
    do {
      uVar7 = DAT_01261420 << 0xd ^ DAT_01261420;
      uVar7 = uVar7 >> 7 ^ uVar7;
      bVar22 = (uVar7 & 7) == 0;
      uVar16 = (uint)bVar22;
      iVar11 = -2 - uVar16;
      uVar2 = (uint)bVar22;
      uVar1 = ~uVar2;
      uVar18 = -uVar2;
      uVar12 = uVar2 ^ 1;
      uVar19 = 2 - uVar16;
      uVar17 = uVar2 ^ 3;
      uVar9 = 4 - uVar16;
      uVar2 = uVar2 ^ 5;
      uVar15 = bVar22 + 2;
      uVar6 = (uint)bVar22 * 5 + 6;
      iVar14 = param_1 + iVar11;
      uVar3 = iVar11 + param_1;
      do {
        if ((param_2 - 1) + iVar11 < 0x5e) {
          iVar13 = iVar11 * iVar11;
          uVar10 = param_2 + iVar11;
          if ((iVar14 - 1U < 0x5e) && ((uint)bVar22 * 5 + 4 + iVar13 <= uVar6)) {
            (&DAT_0140665c)[(ulong)uVar3 + (ulong)uVar10 * 0x60] = 0x2e;
          }
          if ((uVar3 < 0x5e) && (uVar1 * uVar1 + iVar13 <= uVar6)) {
            (&DAT_0140665c)[(ulong)(uVar1 + param_1) + (ulong)uVar10 * 0x60] = 0x2e;
          }
          if (((param_1 - 1) - uVar16 < 0x5e) && (uVar18 * uVar18 + iVar13 <= uVar6)) {
            (&DAT_0140665c)[(ulong)(param_1 - uVar16) + (ulong)uVar10 * 0x60] = 0x2e;
          }
          if (uVar18 != uVar15) {
            if (((param_1 - 1) + uVar12 < 0x5e) && (uVar12 * uVar12 + iVar13 <= uVar6)) {
              (&DAT_0140665c)[(ulong)(uVar12 + param_1) + (ulong)uVar10 * 0x60] = 0x2e;
            }
            if (uVar12 != uVar15) {
              if (((param_1 - 1) + uVar19 < 0x5e) && (uVar19 * uVar19 + iVar13 <= uVar6)) {
                (&DAT_0140665c)[(ulong)(uVar19 + param_1) + (ulong)uVar10 * 0x60] = 0x2e;
              }
              if (uVar19 != uVar15) {
                if (((param_1 - 1) + uVar17 < 0x5e) && (uVar17 * uVar17 + iVar13 <= uVar6)) {
                  (&DAT_0140665c)[(ulong)(uVar17 + param_1) + (ulong)uVar10 * 0x60] = 0x2e;
                }
                if (uVar17 != uVar15) {
                  if (((param_1 - 1) + uVar9 < 0x5e) && (uVar9 * uVar9 + iVar13 <= uVar6)) {
                    (&DAT_0140665c)[(ulong)(uVar9 + param_1) + (ulong)uVar10 * 0x60] = 0x2e;
                  }
                  if (((uVar9 != uVar15) && ((param_1 + uVar2) - 1 < 0x5e)) &&
                     (iVar13 + uVar2 * uVar2 <= uVar6)) {
                    (&DAT_0140665c)[(ulong)(uVar2 + param_1) + (ulong)uVar10 * 0x60] = 0x2e;
                  }
                }
              }
            }
          }
        }
        iVar11 = iVar11 + 1;
      } while (uVar16 + 3 != iVar11);
      DAT_01261420 = uVar7 << 0x11 ^ uVar7;
      if (bVar20) {
        if (param_2 != param_4) {
          uVar7 = DAT_01261420 << 0xd ^ DAT_01261420;
          uVar7 = uVar7 >> 7 ^ uVar7;
          DAT_01261420 = uVar7 << 0x11 ^ uVar7;
          if ((uVar7 & 1) != 0) goto LAB_011f1bef;
        }
        param_1 = (param_1 + (uint)((int)param_1 < (int)param_3) * 2) - 1;
      }
      else {
LAB_011f1bef:
        if (bVar21) {
          param_2 = (param_2 + (uint)((int)param_2 < (int)param_4) * 2) - 1;
        }
      }
      bVar21 = param_2 != param_4;
      bVar20 = param_1 != param_3;
    } while ((bVar20) || (param_2 != param_4));
    uVar7 = (ulong)(param_3 - 1);
    uVar1 = param_4 - 3;
    uVar8 = (ulong)uVar1;
    if (0x5d < param_4 - 4 || 0x5f < param_3) goto LAB_011f1cc2;
    (&DAT_0140665c)[uVar7 + uVar8 * 0x60] = 0x2e;
    if (0x5e < param_3) {
      uVar7 = 0x5e;
      if (0x5d < uVar1) goto LAB_011f1d55;
LAB_011f1d11:
      lVar4 = (ulong)(param_4 - 2) * 0x60;
      puVar5 = &DAT_0140665c + lVar4;
      (&DAT_0140665a)[(ulong)param_3 + lVar4] = 0x2e;
      goto LAB_011f1d2f;
    }
    (&DAT_0140665c)[(ulong)param_3 + uVar8 * 0x60] = 0x2e;
    if (param_3 != 0x5e) goto LAB_011f1cb2;
    uVar7 = 0x5d;
    if (uVar1 < 0x5e) goto LAB_011f1d11;
LAB_011f1d55:
    if (param_4 - 2 < 0x5e) {
      lVar4 = (ulong)(param_4 - 1) * 0x60;
      puVar5 = &DAT_0140665c + lVar4;
      if ((param_3 < 0x62) && ((&DAT_01406659)[(ulong)param_3 + lVar4] = 0x2e, param_3 != 0x61)) {
LAB_011f1de3:
        puVar5[param_3 - 2] = 0x2e;
      }
      if (param_3 - 2 < 0x5e) {
        puVar5[uVar7] = 0x2e;
      }
      if ((param_3 < 0x5f) && (puVar5[param_3] = 0x2e, param_3 != 0x5e)) {
        puVar5[(ulong)param_3 + 1] = 0x2e;
        if ((param_3 < 0x5d) && (puVar5[(ulong)param_3 + 2] = 0x2e, param_3 != 0x5c)) {
          puVar5[(ulong)param_3 + 3] = 0x2e;
        }
      }
    }
  }
  else {
    uVar7 = (ulong)(param_3 - 1);
    uVar8 = (ulong)(param_4 - 3);
    (&DAT_0140665c)[uVar7 + uVar8 * 0x60] = 0x2e;
    (&DAT_0140665c)[(ulong)param_3 + uVar8 * 0x60] = 0x2e;
LAB_011f1cb2:
    (&DAT_0140665d)[(ulong)param_3 + uVar8 * 0x60] = 0x2e;
LAB_011f1cc2:
    if (0x5d < (uint)uVar8 || 0x60 < param_3) goto LAB_011f1d55;
    lVar4 = (ulong)(param_4 - 2) * 0x60;
    puVar5 = &DAT_0140665c + lVar4;
    (&DAT_0140665a)[(ulong)param_3 + lVar4] = 0x2e;
    if (0x5f < param_3) {
      if (param_3 < 0x5f) goto LAB_011f1d3b;
      goto LAB_011f1d55;
    }
LAB_011f1d2f:
    puVar5[uVar7] = 0x2e;
    if (0x5e < param_3) goto LAB_011f1d55;
LAB_011f1d3b:
    puVar5[param_3] = 0x2e;
    if (param_3 == 0x5e) goto LAB_011f1d55;
    puVar5[(ulong)param_3 + 1] = 0x2e;
    if (param_3 < 0x5d) {
      puVar5[(ulong)param_3 + 2] = 0x2e;
      goto LAB_011f1d55;
    }
    if (param_4 - 2 < 0x5e) {
      lVar4 = (ulong)(param_4 - 1) * 0x60;
      puVar5 = &DAT_0140665c + lVar4;
      (&DAT_01406659)[(ulong)param_3 + lVar4] = 0x2e;
      goto LAB_011f1de3;
    }
  }
  if (param_4 - 1 < 0x5e) {
    lVar4 = (ulong)param_4 * 0x60;
    if ((param_3 < 0x62) && ((&DAT_01406659)[(ulong)param_3 + lVar4] = 0x2e, param_3 != 0x61)) {
      (&DAT_0140665c)[(ulong)(param_3 - 2) + lVar4] = 0x2e;
    }
    if (param_3 - 2 < 0x5e) {
      (&DAT_0140665c)[uVar7 + lVar4] = 0x2e;
    }
    if ((0x5e < param_3) || ((&DAT_0140665c)[(ulong)param_3 + lVar4] = 0x2e, param_3 == 0x5e))
    goto LAB_011f1e8b;
    (&DAT_0140665d)[(ulong)param_3 + lVar4] = 0x2e;
    if (0x5c < param_3) goto LAB_011f1e8b;
    (&DAT_0140665e)[(ulong)param_3 + lVar4] = 0x2e;
    if (param_3 != 0x5c) {
      (&DAT_0140665f)[(ulong)param_3 + lVar4] = 0x2e;
      goto LAB_011f1e8b;
    }
    if (param_4 < 0x5e) {
      lVar4 = (ulong)(param_4 + 1) * 0x60;
      puVar5 = &DAT_0140665c + lVar4;
      *(undefined1 *)(lVar4 + 0x14066b5) = 0x2e;
      goto LAB_011f1f56;
    }
  }
  else {
LAB_011f1e8b:
    if (param_4 < 0x5e) {
      lVar4 = (ulong)(param_4 + 1) * 0x60;
      puVar5 = &DAT_0140665c + lVar4;
      if ((param_3 < 0x62) && ((&DAT_01406659)[(ulong)param_3 + lVar4] = 0x2e, param_3 != 0x61)) {
LAB_011f1f56:
        puVar5[param_3 - 2] = 0x2e;
      }
      if (param_3 - 2 < 0x5e) {
        puVar5[uVar7] = 0x2e;
      }
      if ((param_3 < 0x5f) && (puVar5[param_3] = 0x2e, param_3 != 0x5e)) {
        puVar5[(ulong)param_3 + 1] = 0x2e;
        if ((param_3 < 0x5d) && (puVar5[(ulong)param_3 + 2] = 0x2e, param_3 != 0x5c)) {
          puVar5[(ulong)param_3 + 3] = 0x2e;
        }
      }
    }
  }
  uVar1 = param_4 + 2;
  if (param_3 < 0x61 && param_4 + 1 < 0x5e) {
    lVar4 = (ulong)uVar1 * 0x60;
    (&DAT_0140665a)[(ulong)param_3 + lVar4] = 0x2e;
    if (param_3 < 0x60) {
      (&DAT_0140665c)[uVar7 + lVar4] = 0x2e;
    }
    if (param_3 < 0x5f) {
      (&DAT_0140665c)[(ulong)param_3 + lVar4] = 0x2e;
      if (param_3 == 0x5e) {
        if (0x5d < uVar1) {
          return;
        }
        (&DAT_0140677c)[uVar7 + (long)(int)param_4 * 0x60] = 0x2e;
        *(undefined1 *)((long)(int)param_4 * 0x60 + 0x14067da) = 0x2e;
        return;
      }
      (&DAT_0140665d)[(ulong)param_3 + lVar4] = 0x2e;
      if (0x5c < param_3) {
        if (0x5d < uVar1) {
          return;
        }
        (&DAT_0140677c)[uVar7 + (long)(int)param_4 * 0x60] = 0x2e;
        (&DAT_0140677c)[(ulong)param_3 + (long)(int)param_4 * 0x60] = 0x2e;
        goto LAB_011f1fdd;
      }
      (&DAT_0140665e)[(ulong)param_3 + lVar4] = 0x2e;
    }
  }
  if (0x5d < uVar1 || 0x5f < param_3) {
    return;
  }
  (&DAT_0140677c)[uVar7 + (long)(int)param_4 * 0x60] = 0x2e;
  if (0x5e < param_3) {
    return;
  }
  (&DAT_0140677c)[(ulong)param_3 + (long)(int)param_4 * 0x60] = 0x2e;
  if (param_3 == 0x5e) {
    return;
  }
LAB_011f1fdd:
  (&DAT_0140677d)[(ulong)param_3 + (long)(int)param_4 * 0x60] = 0x2e;
  return;
}


// ---- FUN_011f2000 @ 011f2000

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long * FUN_011f2000(long *param_1,long param_2,long param_3,long param_4,long param_5)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  long lVar10;
  ulong uVar11;
  long lVar12;
  long *plVar13;
  undefined8 unaff_retaddr;
  
  puVar2 = *(undefined1 **)(param_3 + -0x10 + param_4 * 0x10);
  lVar3 = *(long *)(param_3 + -8 + param_4 * 0x10);
  uVar4 = *(ulong *)(param_2 + 0x18);
  plVar13 = (long *)(param_3 + 8);
  uVar11 = uVar4;
  while( true ) {
    lVar10 = *plVar13;
    uVar8 = lVar3 * param_5 + 1 + lVar10;
    uVar9 = uVar8 + uVar11;
    lVar5 = plVar13[-1];
    if (CARRY8(uVar8,uVar11)) break;
    lVar6 = *(long *)(param_2 + 8);
    uVar8 = *(ulong *)(param_2 + 0x10);
    lVar7 = lVar6;
    if (uVar8 < uVar9) {
      uVar11 = (uVar9 >> 1) + 0x80;
      lVar12 = uVar11 + uVar9;
      if (CARRY8(uVar11,uVar9)) {
        lVar12 = -1;
      }
      uVar1 = *(undefined1 *)(param_2 + 0x20);
      if ((uVar8 == 0) ||
         (lVar7 = (**(code **)(*(long *)(param_2 + -8) + 0x10))
                            (*(undefined8 *)(param_2 + -0x10),lVar6,uVar8,uVar1,lVar12), lVar7 == 0)
         ) {
        lVar7 = (*(code *)**(undefined8 **)(param_2 + -8))
                          (*(undefined8 *)(param_2 + -0x10),lVar12,uVar1);
        if (lVar7 == 0) break;
        FUN_011f4580(lVar7,lVar6,*(undefined8 *)(param_2 + 0x18));
        if (uVar8 != 0) {
          (**(code **)(*(long *)(param_2 + -8) + 0x18))
                    (*(undefined8 *)(param_2 + -0x10),lVar6,uVar8,uVar1,unaff_retaddr);
        }
      }
      *(long *)(param_2 + 8) = lVar7;
      *(long *)(param_2 + 0x10) = lVar12;
      uVar11 = *(ulong *)(param_2 + 0x18);
    }
    FUN_011f4580(lVar7 + uVar11,lVar5,lVar10);
    uVar11 = lVar10 + *(long *)(param_2 + 0x18);
    *(ulong *)(param_2 + 0x18) = uVar11;
    plVar13 = plVar13 + 2;
    param_4 = param_4 + -1;
    if (param_4 == 0) {
      if (param_5 == 0) {
        uVar11 = uVar11 - lVar3;
        *(ulong *)(param_2 + 0x18) = uVar11;
      }
      else if (lVar3 != 0) {
        if (lVar3 == 1) {
          FUN_011f4160(uVar11 + *(long *)(param_2 + 8),*puVar2,param_5 + -1);
          uVar11 = param_5 + -1 + *(long *)(param_2 + 0x18);
          *(ulong *)(param_2 + 0x18) = uVar11;
        }
        else {
          uVar8 = param_5 - 1;
          if (uVar8 != 0) {
            uVar9 = (ulong)((uint)uVar8 & 3);
            if (2 < param_5 - 2U) {
              uVar8 = uVar8 & 0xfffffffffffffffc;
              do {
                FUN_011f4580(uVar11 + *(long *)(param_2 + 8),puVar2,lVar3);
                lVar10 = *(long *)(param_2 + 0x18) + lVar3;
                *(long *)(param_2 + 0x18) = lVar10;
                FUN_011f4580(lVar10 + *(long *)(param_2 + 8),puVar2,lVar3);
                lVar10 = *(long *)(param_2 + 0x18) + lVar3;
                *(long *)(param_2 + 0x18) = lVar10;
                FUN_011f4580(lVar10 + *(long *)(param_2 + 8),puVar2,lVar3);
                lVar10 = *(long *)(param_2 + 0x18) + lVar3;
                *(long *)(param_2 + 0x18) = lVar10;
                FUN_011f4580(lVar10 + *(long *)(param_2 + 8),puVar2,lVar3);
                uVar11 = *(long *)(param_2 + 0x18) + lVar3;
                *(ulong *)(param_2 + 0x18) = uVar11;
                uVar8 = uVar8 - 4;
              } while (uVar8 != 0);
            }
            for (; uVar9 != 0; uVar9 = uVar9 - 1) {
              FUN_011f4580(uVar11 + *(long *)(param_2 + 8),puVar2,lVar3);
              uVar11 = *(long *)(param_2 + 0x18) + lVar3;
              *(ulong *)(param_2 + 0x18) = uVar11;
            }
          }
        }
      }
      *(undefined2 *)(param_1 + 1) = 0;
      *param_1 = uVar11 - uVar4;
      return param_1;
    }
  }
  lVar3 = _UNK_010004c8;
  *param_1 = _DAT_010004c0;
  param_1[1] = lVar3;
  return param_1;
}


// ---- FUN_011f2320 @ 011f2320

undefined8 FUN_011f2320(long param_1,ulong param_2,ulong param_3)

{
  undefined1 uVar1;
  undefined8 uVar2;
  undefined8 in_RAX;
  ulong uVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uVar9;
  bool bVar10;
  undefined8 unaff_retaddr;
  
  uVar7 = param_2 + param_3;
  lVar4 = CONCAT71((int7)((ulong)in_RAX >> 8),CARRY8(param_2,param_3));
  if (!CARRY8(param_2,param_3)) {
    uVar9 = *(ulong *)(param_1 + 0x10);
    if (uVar9 < uVar7) {
      uVar3 = (uVar7 >> 1) + 0x80;
      uVar8 = 0xffffffffffffffff;
      if (!CARRY8(uVar3,uVar7)) {
        uVar8 = uVar3 + uVar7;
      }
      uVar2 = *(undefined8 *)(param_1 + 8);
      uVar1 = *(undefined1 *)(param_1 + 0x20);
      if ((uVar9 == 0) ||
         (lVar4 = (**(code **)(*(long *)(param_1 + -8) + 0x10))
                            (*(undefined8 *)(param_1 + -0x10),uVar2,uVar9,uVar1,uVar8,unaff_retaddr)
         , lVar5 = lVar4, lVar4 == 0)) {
        lVar5 = (*(code *)**(undefined8 **)(param_1 + -8))
                          (*(undefined8 *)(param_1 + -0x10),uVar8,uVar1,unaff_retaddr);
        lVar4 = 0;
        if (lVar5 == 0) goto LAB_011f2412;
        lVar4 = FUN_011f4580(lVar5,uVar2,*(undefined8 *)(param_1 + 0x18));
        if (uVar9 != 0) {
          lVar4 = (**(code **)(*(long *)(param_1 + -8) + 0x18))
                            (*(undefined8 *)(param_1 + -0x10),uVar2,uVar9,uVar1,unaff_retaddr);
        }
      }
      *(long *)(param_1 + 8) = lVar5;
      *(ulong *)(param_1 + 0x10) = uVar8;
      uVar9 = uVar8;
    }
    bVar10 = CARRY8(param_3,*(ulong *)(param_1 + 0x18));
    param_3 = param_3 + *(ulong *)(param_1 + 0x18);
    lVar4 = CONCAT71((int7)((ulong)lVar4 >> 8),bVar10);
    if (!bVar10) {
      if (uVar9 < param_3) {
        uVar7 = (param_3 >> 1) + 0x80;
        lVar5 = -1;
        if (!CARRY8(uVar7,param_3)) {
          lVar5 = uVar7 + param_3;
        }
        uVar2 = *(undefined8 *)(param_1 + 8);
        uVar1 = *(undefined1 *)(param_1 + 0x20);
        if ((uVar9 == 0) ||
           (lVar6 = (**(code **)(*(long *)(param_1 + -8) + 0x10))
                              (*(undefined8 *)(param_1 + -0x10),uVar2,uVar9,uVar1,lVar5,
                               unaff_retaddr), lVar6 == 0)) {
          lVar6 = (*(code *)**(undefined8 **)(param_1 + -8))
                            (*(undefined8 *)(param_1 + -0x10),lVar5,uVar1,unaff_retaddr);
          lVar4 = 0;
          if (lVar6 == 0) goto LAB_011f2412;
          FUN_011f4580(lVar6,uVar2,*(undefined8 *)(param_1 + 0x18));
          if (uVar9 != 0) {
            (**(code **)(*(long *)(param_1 + -8) + 0x18))
                      (*(undefined8 *)(param_1 + -0x10),uVar2,uVar9,uVar1,unaff_retaddr);
          }
        }
        *(long *)(param_1 + 8) = lVar6;
        *(long *)(param_1 + 0x10) = lVar5;
      }
      return 0;
    }
  }
LAB_011f2412:
  return CONCAT62((int6)((ulong)lVar4 >> 0x10),0x68);
}


// ---- FUN_011f24e0 @ 011f24e0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_011f24e0(undefined1 (*param_1) [16],long param_2,undefined8 *param_3,ulong param_4)

{
  long lVar1;
  long lVar2;
  undefined8 uVar3;
  byte bVar4;
  ulong uVar5;
  long lVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uVar9;
  undefined8 uVar10;
  undefined1 auVar11 [16];
  undefined8 uVar12;
  long unaff_retaddr;
  undefined1 local_e8;
  undefined7 uStack_e7;
  short local_e0;
  long local_a0;
  byte local_8c;
  short local_88;
  undefined8 local_70;
  long local_68;
  long local_60;
  long local_58;
  uint local_4c;
  undefined1 (*local_48) [16];
  ulong local_40;
  long local_38;
  
  if (param_4 == 0) {
    auVar11._0_12_ = ZEXT812(0);
    auVar11._12_4_ = 0;
    *param_1 = auVar11;
    return;
  }
  lVar6 = param_3[8];
  lVar1 = param_3[9];
  lVar2 = param_3[2];
  if (*(char *)(param_3 + 4) == '\0') {
    if (*(short *)((long)param_3 + 0x5a) == 0) {
      local_68 = param_3[10];
      local_40 = param_4;
      (**(code **)(param_3[1] + 0x168))(&local_e8,*param_3,&local_68);
      param_4 = local_40;
      if (local_88 == 0) {
        if ((local_8c & 0xf) == 5) {
          param_3[3] = local_a0;
          *(undefined1 *)(param_3 + 4) = 1;
          uVar8 = (lVar1 - (lVar6 + lVar2)) + local_a0;
          uVar10 = _DAT_01000920;
          uVar12 = _UNK_01000928;
          goto joined_r0x011f2598;
        }
        bVar4 = (*(byte *)((long)param_3 + 0x5e) ^ 4) & 7;
        *(byte *)((long)param_3 + 0x5e) = (byte)(0x480004 >> (uint)bVar4 + (uint)bVar4 * 2) & 7;
        local_88 = 0x36;
      }
      *(short *)((long)param_3 + 0x5a) = local_88;
    }
    uVar8 = 0x80;
  }
  else {
    uVar8 = (lVar1 - (lVar6 + lVar2)) + param_3[3];
    uVar10 = _DAT_01000920;
    uVar12 = _UNK_01000928;
joined_r0x011f2598:
    _DAT_01000920 = uVar10;
    _UNK_01000928 = uVar12;
    if (uVar8 == 0) goto LAB_011f2756;
  }
  if (param_4 <= uVar8) {
    uVar8 = param_4;
  }
  uVar5 = *(ulong *)(param_2 + 0x18);
  local_e8 = CARRY8(uVar8,uVar5);
  uVar8 = uVar8 + uVar5;
  uVar10 = _DAT_010004c0;
  uVar12 = _UNK_010004c8;
  if (!(bool)local_e8) {
    uVar9 = *(ulong *)(param_2 + 0x10);
    local_48 = param_1;
    if (uVar9 < uVar8) {
      uVar5 = (uVar8 >> 1) + 0x80;
      uVar7 = 0xffffffffffffffff;
      if (!CARRY8(uVar5,uVar8)) {
        uVar7 = uVar5 + uVar8;
      }
      local_70 = *(undefined8 *)(param_2 + 8);
      bVar4 = *(byte *)(param_2 + 0x20);
      local_40 = param_4;
      if ((uVar9 == 0) ||
         (local_38 = unaff_retaddr,
         lVar6 = (**(code **)(*(long *)(param_2 + -8) + 0x10))
                           (*(undefined8 *)(param_2 + -0x10),local_70,uVar9,bVar4,uVar7),
         unaff_retaddr = local_38, lVar6 == 0)) {
        local_4c = (uint)bVar4;
        local_58 = (*(code *)**(undefined8 **)(param_2 + -8))
                             (*(undefined8 *)(param_2 + -0x10),uVar7,bVar4,unaff_retaddr);
        uVar3 = local_70;
        param_1 = local_48;
        uVar10 = _DAT_010004c0;
        uVar12 = _UNK_010004c8;
        if (local_58 == 0) goto LAB_011f2756;
        local_38 = unaff_retaddr;
        FUN_011f4580(local_58,local_70,*(undefined8 *)(param_2 + 0x18));
        lVar6 = local_58;
        if (uVar9 != 0) {
          (**(code **)(*(long *)(param_2 + -8) + 0x18))
                    (*(undefined8 *)(param_2 + -0x10),uVar3,uVar9,local_4c,local_38);
          lVar6 = local_58;
        }
      }
      *(long *)(param_2 + 8) = lVar6;
      *(ulong *)(param_2 + 0x10) = uVar7;
      uVar5 = *(ulong *)(param_2 + 0x18);
      param_4 = local_40;
      uVar9 = uVar7;
    }
    else {
      lVar6 = *(long *)(param_2 + 8);
    }
    uVar8 = uVar9 - uVar5;
    if (param_4 <= uVar9 - uVar5) {
      uVar8 = param_4;
    }
    uVar7 = param_3[9] - param_3[8];
    uVar9 = uVar7;
    if (uVar8 < uVar7) {
      uVar9 = uVar8;
    }
    local_38 = param_2;
    FUN_011f4580(lVar6 + uVar5,param_3[6] + param_3[8],uVar9);
    param_3[8] = param_3[8] + uVar9;
    if (uVar7 < uVar8) {
      do {
        local_68 = lVar6 + uVar5 + uVar9;
        local_60 = uVar8 - uVar9;
        FUN_011f27e0(&local_e8,param_3 + 5,&local_68);
        if (local_e0 != 0) {
          uVar8 = uVar9;
          if (local_e0 != 0x14) {
            *(undefined2 *)(*local_48 + 8) = 0x15;
            return;
          }
          break;
        }
        uVar9 = uVar9 + CONCAT71(uStack_e7,local_e8);
      } while (uVar8 != uVar9);
    }
    param_1 = local_48;
    uVar10 = _DAT_01000920;
    uVar12 = _UNK_01000928;
    if (uVar8 != 0) {
      *(long *)(local_38 + 0x18) = *(long *)(local_38 + 0x18) + uVar8;
      *(undefined2 *)(*local_48 + 8) = 0;
      *(ulong *)*local_48 = uVar8;
      return;
    }
  }
LAB_011f2756:
  *(undefined8 *)*param_1 = uVar10;
  *(undefined8 *)(*param_1 + 8) = uVar12;
  return;
}


// ---- FUN_011f27e0 @ 011f27e0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_011f27e0(long *param_1,long *param_2,long *param_3)

{
  ulong uVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  long lVar7;
  long local_60;
  short local_58;
  long *local_50;
  long local_48;
  ulong local_40;
  long *local_38;
  
  local_48 = *param_3;
  uVar1 = param_3[1];
  lVar4 = param_2[3];
  uVar6 = param_2[4] - lVar4;
  uVar5 = uVar1;
  if (uVar6 < uVar1) {
    uVar5 = uVar6;
  }
  local_50 = param_3;
  local_38 = param_1;
  FUN_011f4580(local_48,param_2[1] + lVar4,uVar5);
  lVar3 = local_48;
  plVar2 = local_50;
  lVar4 = lVar4 + uVar5;
  lVar7 = param_2[3];
  if (uVar1 <= uVar6) {
    param_2[3] = lVar4;
    *(undefined2 *)(local_38 + 1) = 0;
    *local_38 = lVar4 - lVar7;
    return;
  }
  param_2[3] = lVar4;
  *local_50 = uVar5 + local_48;
  local_50[1] = uVar1 - uVar5;
  local_40 = uVar1;
  (**(code **)(*param_2 + 0x10))(&local_60,param_2,local_50,1);
  if (local_58 == 0) {
LAB_011f287e:
    *plVar2 = lVar3;
    plVar2[1] = local_40;
    *(undefined2 *)(local_38 + 1) = 0;
    *local_38 = (lVar4 - lVar7) + local_60;
  }
  else {
    if (local_58 == 0x14) {
      if (lVar4 != lVar7) {
        local_60 = 0;
        goto LAB_011f287e;
      }
      *plVar2 = lVar3;
      plVar2[1] = local_40;
      lVar4 = _DAT_01000920;
      lVar7 = _UNK_01000928;
    }
    else {
      *plVar2 = lVar3;
      plVar2[1] = local_40;
      lVar4 = _DAT_01000690;
      lVar7 = _UNK_01000698;
    }
    *local_38 = lVar4;
    local_38[1] = lVar7;
  }
  return;
}


// ---- FUN_011f2910 @ 011f2910

long FUN_011f2910(long param_1)

{
  long *plVar1;
  long lVar2;
  
  if (DAT_01200008 == (long *)0x0) {
    return 0;
  }
  lVar2 = *DAT_01200008;
  if (lVar2 != 0) {
    plVar1 = DAT_01200008;
    do {
      if (lVar2 == param_1) {
        return plVar1[1];
      }
      lVar2 = plVar1[2];
      plVar1 = plVar1 + 2;
    } while (lVar2 != 0);
    return 0;
  }
  return 0;
}


// ---- FUN_011f2950 @ 011f2950

/* WARNING: Removing unreachable block (ram,0x011f2a58) */

undefined1  [16] FUN_011f2950(undefined8 param_1,ulong param_2,ulong param_3)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  undefined1 auVar6 [16];
  
  uVar1 = param_3 & 0xffffffffffffff3f;
  if (0xffffffffffffeffe < param_2) {
    lVar3 = 0;
    goto LAB_011f2a61;
  }
  uVar4 = 1L << (param_3 & 0x3f);
  uVar2 = param_2 + 0xfff & 0xfffffffffffff000;
  lVar5 = uVar4 - 0x1000;
  if (uVar4 < 0x1000) {
    lVar5 = 0;
  }
  uVar1 = 3;
  syscall();
  if ((byte)(param_3 & 0x3f) < 0xd) {
    lVar3 = 0;
LAB_011f2a2b:
    lVar3 = lVar3 + 9;
  }
  else {
    if (uVar4 - 1 < 0xfffffffffffffff7) {
      lVar3 = (uVar4 + 8 & -uVar4) - 9;
      goto LAB_011f2a2b;
    }
    lVar3 = 0;
  }
  if (lVar3 + -9 != 0) {
    syscall();
  }
  if (uVar2 < (lVar5 + uVar2) - (lVar3 + -9)) {
    syscall();
  }
  LOCK();
  UNLOCK();
  DAT_01200010 = lVar3;
LAB_011f2a61:
  auVar6._8_8_ = uVar1;
  auVar6._0_8_ = lVar3;
  return auVar6;
}


// ---- FUN_011f2a70 @ 011f2a70

undefined8 FUN_011f2a70(void)

{
  syscall();
  return 0xb;
}


// ---- FUN_011f2a90 @ 011f2a90

undefined1  [16]
FUN_011f2a90(undefined8 param_1,undefined8 param_2,ulong param_3,byte param_4,long param_5)

{
  ulong uVar1;
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  
  if ((param_4 & 0x3f) < 0xd) {
    uVar1 = param_5 + 0xfffU & 0xfffffffffffff000;
    param_3 = param_3 + 0xfff & 0xfffffffffffff000;
    if (uVar1 != param_3) {
      syscall();
      auVar3._8_8_ = uVar1;
      auVar3._0_8_ = 0x19;
      return auVar3;
    }
  }
  else {
    param_2 = 0;
  }
  auVar2._8_8_ = param_3;
  auVar2._0_8_ = param_2;
  return auVar2;
}


// ---- FUN_011f2b10 @ 011f2b10

ulong FUN_011f2b10(undefined8 param_1,undefined8 param_2,long param_3,byte param_4,long param_5,
                  undefined8 param_6)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  
  if ((param_4 & 0x3f) < 0xd) {
    uVar2 = param_5 + 0xfffU & 0xfffffffffffff000;
    uVar1 = param_3 + 0xfffU & 0xfffffffffffff000;
    uVar3 = CONCAT71((int7)((ulong)param_6 >> 8),1);
    if (uVar1 != uVar2) {
      if (uVar2 < uVar1) {
        syscall();
        return uVar3 & 0xffffffff;
      }
      return 0;
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3 & 0xffffffff;
}


// ---- FUN_011f2b70 @ 011f2b70

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong * FUN_011f2b70(ulong *param_1,long param_2,undefined8 param_3,ulong param_4,undefined8 param_5
                    )

{
  ulong uVar1;
  byte bVar2;
  ulong uVar3;
  undefined2 uVar4;
  undefined8 *puVar5;
  long lVar6;
  ulong local_80;
  ushort local_78;
  ushort local_68;
  ulong local_60;
  ulong local_58;
  undefined8 local_50;
  ulong local_48;
  ulong local_40;
  undefined8 local_38;
  undefined4 local_30;
  undefined2 uStack_2c;
  undefined4 local_28;
  undefined2 local_24;
  
  uVar1 = _UNK_010004c8;
  uVar3 = _UNK_01000288;
  puVar5 = (undefined8 *)(param_2 + -0x18);
  switch(*(byte *)(param_2 + 0x2e) & 7) {
  default:
    local_60 = *(ulong *)(param_2 + 8);
    local_58 = *(undefined8 *)(param_2 + 0x18);
    local_38 = *(undefined8 *)(param_2 + 0x20);
    local_30 = CONCAT31(local_30._1_3_,1);
    local_50 = param_3;
    local_48 = param_4;
    local_40 = param_5;
    (**(code **)(*(long *)(param_2 + -0x10) + 0x78))(&local_80,*puVar5,&local_60);
    if ((local_68 == 0) && (local_68 = local_78, local_78 == 0)) {
      *(long *)(param_2 + -8) = *(long *)(param_2 + -8) + local_80;
      uVar1 = *(ulong *)(param_2 + 0x18);
      uVar3 = local_80 - uVar1;
      if (local_80 < uVar1) {
        lVar6 = uVar1 - local_80;
        FUN_011f41f0(*(long *)(param_2 + 8),*(long *)(param_2 + 8) + local_80,lVar6);
        uVar3 = 0;
      }
      else {
        lVar6 = 0;
      }
      *(long *)(param_2 + 0x18) = lVar6;
      uVar4 = 0;
    }
    else {
      uVar3 = (ulong)local_68;
      *(ushort *)(param_2 + 0x28) = local_68;
      uVar4 = 0x68;
    }
    *param_1 = uVar3;
    *(undefined2 *)(param_1 + 1) = uVar4;
    *(undefined4 *)((long)param_1 + 10) = 0;
    *(undefined2 *)((long)param_1 + 0xe) = 0;
    break;
  case 1:
  case 3:
    local_80 = *(ulong *)(param_2 + 0x20);
    (**(code **)(*(long *)(param_2 + -0x10) + 0x180))
              (&local_60,*puVar5,&local_80,*(undefined8 *)(param_2 + 8),
               *(undefined8 *)(param_2 + 0x18),param_3,param_4,param_5,*(undefined8 *)(param_2 + -8)
              );
    uVar3 = local_58 & 0xffff;
    if ((short)local_58 == 0) {
      *(long *)(param_2 + -8) = *(long *)(param_2 + -8) + local_60;
      uVar1 = *(ulong *)(param_2 + 0x18);
      uVar3 = local_60 - uVar1;
      if (local_60 < uVar1) {
        lVar6 = uVar1 - local_60;
        FUN_011f41f0(*(long *)(param_2 + 8),*(long *)(param_2 + 8) + local_60,lVar6);
        uVar3 = 0;
      }
      else {
        lVar6 = 0;
      }
      *(long *)(param_2 + 0x18) = lVar6;
LAB_011f2c80:
      uVar4 = 0;
    }
    else {
      if ((short)local_58 == 0x16) {
        bVar2 = (*(byte *)(param_2 + 0x2e) ^ 4) & 7;
        *(byte *)(param_2 + 0x2e) = (byte)(0x480004 >> (uint)bVar2 + (uint)bVar2 * 2) & 7;
        if (*(long *)(param_2 + -8) != 0) {
          *(undefined8 *)(param_2 + -8) = 0;
          uVar3 = FUN_011f3020(puVar5);
          if ((short)uVar3 != 0) {
            *(undefined1 *)(param_2 + 0x2e) = 4;
            goto LAB_011f2d3d;
          }
        }
        local_24 = 0;
        local_28 = 0;
        uVar3 = 0;
        goto LAB_011f2c80;
      }
      *(short *)(param_2 + 0x28) = (short)local_58;
LAB_011f2d3d:
      local_24 = 0;
      local_28 = 0;
      uVar4 = 0x68;
    }
    *param_1 = uVar3;
    *(undefined2 *)(param_1 + 1) = uVar4;
    *(undefined4 *)((long)param_1 + 10) = local_28;
    *(undefined2 *)((long)param_1 + 0xe) = local_24;
    break;
  case 4:
    *param_1 = _DAT_010004c0;
    param_1[1] = uVar1;
    break;
  case 5:
    local_38 = *(undefined8 *)(param_2 + 0x20);
    (**(code **)(*(long *)(param_2 + -0x10) + 0x188))
              (&local_48,*puVar5,&local_38,*(undefined8 *)(param_2 + 8),
               *(undefined8 *)(param_2 + 0x18),param_3,param_5);
    uVar3 = local_40 & 0xffff;
    if ((short)local_40 == 0) {
      *(long *)(param_2 + -8) = *(long *)(param_2 + -8) + local_48;
      uVar1 = *(ulong *)(param_2 + 0x18);
      uVar3 = local_48 - uVar1;
      if (local_48 < uVar1) {
        lVar6 = uVar1 - local_48;
        FUN_011f41f0(*(long *)(param_2 + 8),*(long *)(param_2 + 8) + local_48,lVar6);
        uVar3 = 0;
      }
      else {
        lVar6 = 0;
      }
      *(long *)(param_2 + 0x18) = lVar6;
      uVar4 = 0;
      goto LAB_011f2e9c;
    }
    switch((short)local_40) {
    case 0x11:
      *(undefined2 *)(param_2 + 0x28) = 0x11;
      goto LAB_011f2f50;
    case 0x12:
      uVar4 = 0x12;
      break;
    default:
      *(short *)(param_2 + 0x2a) = (short)local_40;
LAB_011f2f50:
      uVar4 = 0x68;
      break;
    case 0x14:
      uVar4 = 0x14;
      break;
    case 0x15:
      uVar4 = 0x15;
    }
    uStack_2c = 0;
    local_30 = 0;
LAB_011f2e9c:
    *param_1 = uVar3;
    *(undefined2 *)(param_1 + 1) = uVar4;
    *(undefined4 *)((long)param_1 + 10) = local_30;
    local_24 = uStack_2c;
LAB_011f2ec9:
    *(undefined2 *)((long)param_1 + 0xe) = local_24;
    return param_1;
  case 6:
    local_38 = *(undefined8 *)(param_2 + 0x20);
    (**(code **)(*(long *)(param_2 + -0x10) + 400))
              (&local_48,*puVar5,&local_38,*(undefined8 *)(param_2 + 8),
               *(undefined8 *)(param_2 + 0x18),param_3,param_5,*(undefined8 *)(param_2 + -8));
    uVar3 = local_40 & 0xffff;
    if ((short)local_40 == 0) {
      *(long *)(param_2 + -8) = *(long *)(param_2 + -8) + local_48;
      uVar1 = *(ulong *)(param_2 + 0x18);
      uVar3 = local_48 - uVar1;
      if (local_48 < uVar1) {
        lVar6 = uVar1 - local_48;
        FUN_011f41f0(*(long *)(param_2 + 8),*(long *)(param_2 + 8) + local_48,lVar6);
        uVar3 = 0;
      }
      else {
        lVar6 = 0;
      }
      *(long *)(param_2 + 0x18) = lVar6;
LAB_011f2eb6:
      uVar4 = 0;
      goto LAB_011f2eb8;
    }
    switch((short)local_40) {
    case 0x11:
      *(undefined2 *)(param_2 + 0x28) = 0x11;
      goto LAB_011f2feb;
    case 0x12:
      uVar4 = 0x12;
      break;
    default:
      *(short *)(param_2 + 0x2a) = (short)local_40;
LAB_011f2feb:
      uVar4 = 0x68;
      break;
    case 0x14:
      uVar4 = 0x14;
      break;
    case 0x15:
      uVar4 = 0x15;
      break;
    case 0x16:
      bVar2 = (*(byte *)(param_2 + 0x2e) ^ 4) & 7;
      *(byte *)(param_2 + 0x2e) = (byte)(0x480004 >> (uint)bVar2 + (uint)bVar2 * 2) & 7;
      if (*(long *)(param_2 + -8) != 0) {
        *(undefined8 *)(param_2 + -8) = 0;
        uVar3 = FUN_011f3020(puVar5);
        if ((short)uVar3 != 0) {
          *(undefined1 *)(param_2 + 0x2e) = 4;
          goto LAB_011f2feb;
        }
      }
      local_24 = 0;
      local_28 = 0;
      uVar3 = 0;
      goto LAB_011f2eb6;
    }
    local_24 = 0;
    local_28 = 0;
LAB_011f2eb8:
    *param_1 = uVar3;
    *(undefined2 *)(param_1 + 1) = uVar4;
    *(undefined4 *)((long)param_1 + 10) = local_28;
    goto LAB_011f2ec9;
  case 7:
    *param_1 = _DAT_01000280;
    param_1[1] = uVar3;
    return param_1;
  }
  return param_1;
}


// ---- FUN_011f2d70 @ 011f2d70

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong * FUN_011f2d70(ulong *param_1,long param_2,undefined8 param_3,ulong param_4)

{
  ulong uVar1;
  byte bVar2;
  ulong uVar3;
  undefined2 uVar4;
  undefined8 *puVar5;
  long lVar6;
  ulong local_48;
  ushort local_40;
  undefined8 local_38;
  undefined4 local_30;
  undefined2 local_2c;
  undefined4 local_28;
  undefined2 local_24;
  
  uVar1 = _UNK_010004c8;
  uVar3 = _UNK_01000288;
  puVar5 = (undefined8 *)(param_2 + -0x18);
  switch(*(byte *)(param_2 + 0x2e) & 7) {
  case 0:
    local_38 = *(undefined8 *)(param_2 + 0x20);
    (**(code **)(*(long *)(param_2 + -0x10) + 0x188))
              (&local_48,*puVar5,&local_38,*(undefined8 *)(param_2 + 8),
               *(undefined8 *)(param_2 + 0x18),param_3,param_4);
    param_4 = (ulong)local_40;
    if (local_40 != 0) {
      switch(local_40) {
      case 0x11:
        goto switchD_011f2d94_caseD_5;
      case 0x12:
        goto switchD_011f2d94_caseD_6;
      default:
        goto switchD_011f2d94_caseD_7;
      case 0x14:
        uVar4 = 0x14;
        break;
      case 0x15:
        uVar4 = 0x15;
      }
      goto LAB_011f2f61;
    }
    *(long *)(param_2 + -8) = *(long *)(param_2 + -8) + local_48;
    uVar3 = *(ulong *)(param_2 + 0x18);
    param_4 = local_48 - uVar3;
    if (local_48 < uVar3) {
      lVar6 = uVar3 - local_48;
      FUN_011f41f0(*(long *)(param_2 + 8),*(long *)(param_2 + 8) + local_48,lVar6);
      param_4 = 0;
    }
    else {
      lVar6 = 0;
    }
    *(long *)(param_2 + 0x18) = lVar6;
    uVar4 = 0;
    goto LAB_011f2e9c;
  case 1:
    local_38 = *(undefined8 *)(param_2 + 0x20);
    (**(code **)(*(long *)(param_2 + -0x10) + 400))
              (&local_48,*puVar5,&local_38,*(undefined8 *)(param_2 + 8),
               *(undefined8 *)(param_2 + 0x18),param_3,param_4,*(undefined8 *)(param_2 + -8));
    uVar3 = (ulong)local_40;
    if (local_40 == 0) {
      *(long *)(param_2 + -8) = *(long *)(param_2 + -8) + local_48;
      uVar1 = *(ulong *)(param_2 + 0x18);
      uVar3 = local_48 - uVar1;
      if (local_48 < uVar1) {
        lVar6 = uVar1 - local_48;
        FUN_011f41f0(*(long *)(param_2 + 8),*(long *)(param_2 + 8) + local_48,lVar6);
        uVar3 = 0;
      }
      else {
        lVar6 = 0;
      }
      *(long *)(param_2 + 0x18) = lVar6;
LAB_011f2eb6:
      uVar4 = 0;
      goto LAB_011f2eb8;
    }
    switch(local_40) {
    case 0x11:
      *(undefined2 *)(param_2 + 0x28) = 0x11;
      goto LAB_011f2feb;
    case 0x12:
      uVar4 = 0x12;
      break;
    default:
      *(ushort *)(param_2 + 0x2a) = local_40;
LAB_011f2feb:
      uVar4 = 0x68;
      break;
    case 0x14:
      uVar4 = 0x14;
      break;
    case 0x15:
      uVar4 = 0x15;
      break;
    case 0x16:
      bVar2 = (*(byte *)(param_2 + 0x2e) ^ 4) & 7;
      *(byte *)(param_2 + 0x2e) = (byte)(0x480004 >> (uint)bVar2 + (uint)bVar2 * 2) & 7;
      if (*(long *)(param_2 + -8) != 0) {
        *(undefined8 *)(param_2 + -8) = 0;
        uVar3 = FUN_011f3020(puVar5);
        if ((short)uVar3 != 0) {
          *(undefined1 *)(param_2 + 0x2e) = 4;
          goto LAB_011f2feb;
        }
      }
      local_24 = 0;
      local_28 = 0;
      uVar3 = 0;
      goto LAB_011f2eb6;
    }
    local_24 = 0;
    local_28 = 0;
LAB_011f2eb8:
    *param_1 = uVar3;
    *(undefined2 *)(param_1 + 1) = uVar4;
    *(undefined4 *)((long)param_1 + 10) = local_28;
    local_2c = local_24;
    goto LAB_011f2ec9;
  default:
    *param_1 = _DAT_01000280;
    param_1[1] = uVar3;
    return param_1;
  case 4:
    *param_1 = _DAT_010004c0;
    param_1[1] = uVar1;
    return param_1;
  case 5:
switchD_011f2d94_caseD_5:
    *(undefined2 *)(param_2 + 0x28) = 0x11;
    break;
  case 6:
switchD_011f2d94_caseD_6:
    uVar4 = 0x12;
    goto LAB_011f2f61;
  case 7:
switchD_011f2d94_caseD_7:
    *(short *)(param_2 + 0x2a) = (short)param_4;
  }
  uVar4 = 0x68;
LAB_011f2f61:
  local_2c = 0;
  local_30 = 0;
LAB_011f2e9c:
  *param_1 = param_4;
  *(undefined2 *)(param_1 + 1) = uVar4;
  *(undefined4 *)((long)param_1 + 10) = local_30;
LAB_011f2ec9:
  *(undefined2 *)((long)param_1 + 0xe) = local_2c;
  return param_1;
}


// ---- FUN_011f3020 @ 011f3020

ulong FUN_011f3020(undefined8 *param_1,undefined8 param_2)

{
  ulong uVar1;
  undefined8 local_20;
  
  uVar1 = (**(code **)(param_1[3] + 0x10))(param_1 + 3);
  if ((short)uVar1 == 0) {
                    /* WARNING (jumptable): Sanity check requires truncation of jumptable */
                    /* WARNING: Could not find normalized switch variable to match jumptable */
    switch(*(byte *)((long)param_1 + 0x46) & 7) {
    default:
      if (*(ushort *)((long)param_1 + 0x44) != 0) {
        return (ulong)*(ushort *)((long)param_1 + 0x44);
      }
      local_20 = param_1[7];
      uVar1 = (**(code **)(param_1[1] + 0x1a8))(*param_1,&local_20,param_2);
      if ((short)uVar1 != 0) {
        *(short *)((long)param_1 + 0x44) = (short)uVar1;
        return uVar1;
      }
    case 1:
    case 3:
      param_1[2] = param_2;
      uVar1 = 0;
      break;
    case 4:
      uVar1 = (ulong)*(ushort *)((long)param_1 + 0x44);
    }
  }
  return uVar1;
}


// ---- FUN_011f30a0 @ 011f30a0

undefined8 FUN_011f30a0(void)

{
  return 0;
}


// ---- FUN_011f30b0 @ 011f30b0

void FUN_011f30b0(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}


// ---- FUN_011f30c0 @ 011f30c0

void FUN_011f30c0(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}


// ---- FUN_011f30d0 @ 011f30d0

void FUN_011f30d0(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}


// ---- FUN_011f30e0 @ 011f30e0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_011f30e0(undefined4 param_1)

{
  ulong *puVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  byte bVar5;
  ulong uVar6;
  ulong uVar7;
  long in_FS_OFFSET;
  undefined1 local_b8 [64];
  long local_78;
  byte local_70;
  undefined4 local_68;
  uint local_64;
  byte local_60;
  undefined8 *local_58;
  long local_50;
  short local_48;
  char *local_40;
  long local_38;
  
  lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
  if (lVar4 == 0) {
    local_64 = 0;
  }
  else {
    local_64 = (uint)*(byte *)(lVar4 + 0x21c);
    *(undefined1 *)(lVar4 + 0x21c) = 1;
  }
  local_68 = param_1;
  FUN_011c4880(&local_78,local_b8,0x40);
  local_58 = (undefined8 *)(local_78 + 0x18);
  bVar5 = local_70 & 3;
  local_60 = bVar5;
  if (bVar5 != 0) {
    uVar6 = 0;
    do {
      while( true ) {
        lVar4 = 5 - uVar6;
        if ((ulong)(*(long *)(local_78 + 0x30) + lVar4) <= *(ulong *)(local_78 + 0x28)) break;
        local_40 = &DAT_011b8b3a + uVar6;
        local_38 = lVar4;
        (**(code **)*local_58)(&local_50,local_58,&local_40,1,1);
        if ((local_48 != 0) || (uVar6 = uVar6 + local_50, 4 < uVar6)) goto LAB_011f31d6;
      }
      FUN_011f4580(*(long *)(local_78 + 0x30) + *(long *)(local_78 + 0x20),&DAT_011b8b3a + uVar6,
                   lVar4);
      *(long *)(local_78 + 0x30) = *(long *)(local_78 + 0x30) + lVar4;
      uVar6 = uVar6 + lVar4;
    } while (uVar6 < 5);
LAB_011f31d6:
    uVar6 = 0;
    do {
      while( true ) {
        lVar4 = 4 - uVar6;
        if ((ulong)(*(long *)(local_78 + 0x30) + lVar4) <= *(ulong *)(local_78 + 0x28)) break;
        local_40 = &DAT_011b8b35 + uVar6;
        local_38 = lVar4;
        (**(code **)*local_58)(&local_50,local_58,&local_40,1,1);
        if ((local_48 != 0) || (uVar6 = uVar6 + local_50, 3 < uVar6)) goto LAB_011f3256;
      }
      FUN_011f4580(*(long *)(local_78 + 0x30) + *(long *)(local_78 + 0x20),&DAT_011b8b35 + uVar6,
                   lVar4);
      *(long *)(local_78 + 0x30) = *(long *)(local_78 + 0x30) + lVar4;
      uVar6 = uVar6 + lVar4;
    } while (uVar6 < 4);
  }
LAB_011f3256:
  uVar6 = 0;
  do {
    while( true ) {
      lVar4 = 5 - uVar6;
      if (*(ulong *)(local_78 + 0x28) < (ulong)(*(long *)(local_78 + 0x30) + lVar4)) break;
      FUN_011f4580(*(long *)(local_78 + 0x30) + *(long *)(local_78 + 0x20),"error" + uVar6,lVar4);
      *(long *)(local_78 + 0x30) = *(long *)(local_78 + 0x30) + lVar4;
      uVar6 = uVar6 + lVar4;
      if (4 < uVar6) goto LAB_011f32da;
    }
    local_40 = "error" + uVar6;
    local_38 = lVar4;
    (**(code **)*local_58)(&local_50,local_58,&local_40,1,1);
    if (local_48 != 0) goto LAB_011f366a;
    uVar6 = uVar6 + local_50;
  } while (uVar6 < 5);
LAB_011f32da:
  if (bVar5 != 0) {
    uVar6 = 0;
    do {
      while( true ) {
        lVar4 = 4 - uVar6;
        if ((ulong)(*(long *)(local_78 + 0x30) + lVar4) <= *(ulong *)(local_78 + 0x28)) break;
        local_40 = &DAT_011b8b40 + uVar6;
        local_38 = lVar4;
        (**(code **)*local_58)(&local_50,local_58,&local_40,1,1);
        if ((local_48 != 0) || (uVar6 = uVar6 + local_50, 3 < uVar6)) goto LAB_011f3366;
      }
      FUN_011f4580(*(long *)(local_78 + 0x30) + *(long *)(local_78 + 0x20),&DAT_011b8b40 + uVar6,
                   lVar4);
      *(long *)(local_78 + 0x30) = *(long *)(local_78 + 0x30) + lVar4;
      uVar6 = uVar6 + lVar4;
    } while (uVar6 < 4);
LAB_011f3366:
    uVar6 = 0;
    do {
      while( true ) {
        lVar4 = 4 - uVar6;
        if ((ulong)(*(long *)(local_78 + 0x30) + lVar4) <= *(ulong *)(local_78 + 0x28)) break;
        local_40 = &DAT_011b8b30 + uVar6;
        local_38 = lVar4;
        (**(code **)*local_58)(&local_50,local_58,&local_40,1,1);
        if ((local_48 != 0) || (uVar6 = uVar6 + local_50, 3 < uVar6)) goto LAB_011f33e6;
      }
      FUN_011f4580(*(long *)(local_78 + 0x30) + *(long *)(local_78 + 0x20),&DAT_011b8b30 + uVar6,
                   lVar4);
      *(long *)(local_78 + 0x30) = *(long *)(local_78 + 0x30) + lVar4;
      uVar6 = uVar6 + lVar4;
    } while (uVar6 < 4);
LAB_011f33e6:
    uVar6 = 0;
    do {
      while( true ) {
        lVar4 = 4 - uVar6;
        if ((ulong)(*(long *)(local_78 + 0x30) + lVar4) <= *(ulong *)(local_78 + 0x28)) break;
        local_40 = &DAT_011b8b35 + uVar6;
        local_38 = lVar4;
        (**(code **)*local_58)(&local_50,local_58,&local_40,1,1);
        if ((local_48 != 0) || (uVar6 = uVar6 + local_50, 3 < uVar6)) goto LAB_011f3466;
      }
      FUN_011f4580(*(long *)(local_78 + 0x30) + *(long *)(local_78 + 0x20),&DAT_011b8b35 + uVar6,
                   lVar4);
      *(long *)(local_78 + 0x30) = *(long *)(local_78 + 0x30) + lVar4;
      uVar6 = uVar6 + lVar4;
    } while (uVar6 < 4);
  }
LAB_011f3466:
  uVar6 = 0;
  do {
    while( true ) {
      lVar4 = 2 - uVar6;
      if (*(ulong *)(local_78 + 0x28) < (ulong)(*(long *)(local_78 + 0x30) + lVar4)) break;
      FUN_011f4580(*(long *)(local_78 + 0x30) + *(long *)(local_78 + 0x20),&DAT_011b9acd + uVar6,
                   lVar4);
      *(long *)(local_78 + 0x30) = *(long *)(local_78 + 0x30) + lVar4;
      uVar6 = uVar6 + lVar4;
      if (1 < uVar6) goto LAB_011f34ea;
    }
    local_40 = &DAT_011b9acd + uVar6;
    local_38 = lVar4;
    (**(code **)*local_58)(&local_50,local_58,&local_40,1,1);
    if (local_48 != 0) goto LAB_011f366a;
    uVar6 = uVar6 + local_50;
  } while (uVar6 < 2);
LAB_011f34ea:
  if (bVar5 != 0) {
    uVar6 = 0;
    do {
      while( true ) {
        lVar4 = 4 - uVar6;
        if ((ulong)(*(long *)(local_78 + 0x30) + lVar4) <= *(ulong *)(local_78 + 0x28)) break;
        local_40 = &DAT_011b8b40 + uVar6;
        local_38 = lVar4;
        (**(code **)*local_58)(&local_50,local_58,&local_40,1,1);
        if ((local_48 != 0) || (uVar6 = uVar6 + local_50, 3 < uVar6)) goto LAB_011f3575;
      }
      FUN_011f4580(*(long *)(local_78 + 0x30) + *(long *)(local_78 + 0x20),&DAT_011b8b40 + uVar6,
                   lVar4);
      *(long *)(local_78 + 0x30) = *(long *)(local_78 + 0x30) + lVar4;
      uVar6 = uVar6 + lVar4;
    } while (uVar6 < 4);
  }
LAB_011f3575:
  uVar6 = *(ulong *)(&DAT_0100e398 + (ulong)(ushort)local_68 * 0x10);
  if (uVar6 != 0) {
    lVar4 = *(long *)(&DAT_0100e390 + (ulong)(ushort)local_68 * 0x10);
    uVar7 = 0;
    do {
      while( true ) {
        lVar3 = uVar6 - uVar7;
        if (*(ulong *)(local_78 + 0x28) < (ulong)(*(long *)(local_78 + 0x30) + lVar3)) break;
        FUN_011f4580(*(long *)(local_78 + 0x30) + *(long *)(local_78 + 0x20),(char *)(lVar4 + uVar7)
                     ,lVar3);
        *(long *)(local_78 + 0x30) = *(long *)(local_78 + 0x30) + lVar3;
        uVar7 = uVar7 + lVar3;
        if (uVar6 <= uVar7) goto LAB_011f360f;
      }
      local_40 = (char *)(lVar4 + uVar7);
      local_38 = lVar3;
      (**(code **)*local_58)(&local_50,local_58,&local_40,1,1);
      if (local_48 != 0) goto LAB_011f366a;
      uVar7 = uVar7 + local_50;
    } while (uVar7 < uVar6);
  }
LAB_011f360f:
  while (*(ulong *)(local_78 + 0x28) <= *(ulong *)(local_78 + 0x30)) {
    local_40 = "\n";
    local_38 = 1;
    (**(code **)*local_58)(&local_50,local_58,&local_40,1,1);
    if ((local_48 != 0) || (local_50 != 0)) goto LAB_011f366a;
  }
  *(undefined1 *)(*(long *)(local_78 + 0x20) + *(ulong *)(local_78 + 0x30)) = 10;
  *(long *)(local_78 + 0x30) = *(long *)(local_78 + 0x30) + 1;
LAB_011f366a:
  if (DAT_011fcff0 == 0) {
    (**(code **)(PTR_PTR_011fcfc8 + 0x10))(&PTR_PTR_011fcfc8);
  }
  if (DAT_011fcff0 != 0) {
    if (DAT_011fcff0 == 0x11) {
      LOCK();
      puVar1 = (ulong *)(*(long *)(in_FS_OFFSET + -0x40010) + 8);
      *puVar1 = *puVar1 ^ 1;
      UNLOCK();
    }
    DAT_011fcff0 = 0;
  }
  iVar2 = DAT_011fd300;
  _DAT_011fcfd0 = 1;
  _DAT_011fcfd8 = ZEXT812(0);
  register0x0000120c = 0;
  DAT_011fd2d0 = DAT_011fd2d0 + -1;
  if (DAT_011fd2d0 == 0) {
    DAT_011fd2fc = 0xffffffff;
    LOCK();
    DAT_011fd300 = 0;
    UNLOCK();
    if (iVar2 == 2) {
      syscall();
      lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
      goto joined_r0x011f36f4;
    }
  }
  lVar4 = *(long *)(in_FS_OFFSET + -0x40010);
joined_r0x011f36f4:
  if (lVar4 != 0) {
    *(byte *)(lVar4 + 0x21c) = (byte)local_64 & 1;
  }
  return;
}


// ---- FUN_011f3740 @ 011f3740

undefined2 * FUN_011f3740(undefined2 *param_1)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + -0x40010);
  if ((lVar1 != 0) && ((*(byte *)(lVar1 + 0x21c) & 1) == 0)) {
    if (((uint)*(ulong *)(lVar1 + 8) & 7) == 6) {
      *(ulong *)(lVar1 + 8) = *(ulong *)(lVar1 + 8) | 7;
      *param_1 = 0x11;
      return param_1;
    }
  }
                    /* WARNING: Subroutine does not return */
  FUN_011f3790("TODO implement netInterfaceName for linux",0x29);
}


// ---- FUN_011f3790 @ 011f3790

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_011f3790(long param_1,ulong param_2)

{
  ulong *puVar1;
  char *pcVar2;
  int iVar3;
  undefined8 *puVar4;
  long lVar5;
  long lVar6;
  uint uVar7;
  undefined8 extraout_RDX;
  ulong uVar8;
  ulong uVar9;
  ulong uVar10;
  long in_FS_OFFSET;
  bool bVar11;
  undefined1 auStack_120 [16];
  undefined8 uStack_110;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined1 uStack_e1;
  undefined1 *puStack_e0;
  long local_d8 [2];
  char *local_c8;
  long local_c0;
  long local_b8;
  byte local_b0;
  long local_a8;
  undefined8 local_a0;
  undefined4 local_98;
  undefined4 uStack_94;
  short local_90;
  undefined8 *local_50;
  char *local_48;
  ulong local_40;
  byte local_38;
  
  lVar5 = *(long *)(in_FS_OFFSET + -0x40010);
  if (lVar5 != 0) {
    *(undefined8 *)(lVar5 + 8) = 7;
    *(undefined1 *)(lVar5 + 0x21c) = 1;
  }
  local_a8 = param_1;
  if (*(long *)(in_FS_OFFSET + -0x40018) != 0) {
    if (*(long *)(in_FS_OFFSET + -0x40018) == 1) {
      *(undefined8 *)(in_FS_OFFSET + -0x40018) = 2;
      uVar10 = 0;
      puStack_e0 = (undefined1 *)0x11f3dfa;
      FUN_011c4880(local_d8,1,0);
      do {
        while( true ) {
          uVar8 = 0x20 - uVar10;
          if (*(long *)(local_d8[0] + 0x30) + uVar8 <= *(ulong *)(local_d8[0] + 0x28)) break;
          puStack_e0 = (undefined1 *)0x11f3e6a;
          local_48 = "aborting due to recursive panic\n" + uVar10;
          local_40 = uVar8;
          (*(code *)**(undefined8 **)(local_d8[0] + 0x18))
                    (&local_98,(undefined8 *)(local_d8[0] + 0x18),&local_48,1,1);
          if ((local_90 != 0) || (uVar10 = uVar10 + CONCAT44(uStack_94,local_98), 0x1f < uVar10))
          goto LAB_011f3e84;
        }
        puStack_e0 = (undefined1 *)0x11f3e33;
        FUN_011f4580(*(long *)(local_d8[0] + 0x30) + *(long *)(local_d8[0] + 0x20),
                     "aborting due to recursive panic\n" + uVar10,uVar8);
        *(long *)(local_d8[0] + 0x30) = *(long *)(local_d8[0] + 0x30) + uVar8;
        uVar10 = uVar10 + uVar8;
      } while (uVar10 < 0x20);
    }
    goto LAB_011f3e84;
  }
  *(undefined8 *)(in_FS_OFFSET + -0x40018) = 1;
  LOCK();
  DAT_01200000 = DAT_01200000 + '\x01';
  UNLOCK();
  puStack_e0 = (undefined1 *)0x11f3804;
  FUN_011c4880(&local_b8,1,0);
  local_38 = local_b0 & 3;
  if (*(char *)(in_FS_OFFSET + -0x40004) == '\x01') {
    uVar7 = *(uint *)(in_FS_OFFSET + -0x40008);
  }
  else {
    syscall();
    uVar7 = 0xba;
    *(undefined4 *)(in_FS_OFFSET + -0x40008) = 0xba;
    *(undefined1 *)(in_FS_OFFSET + -0x40004) = 1;
  }
  local_50 = (undefined8 *)(local_b8 + 0x18);
  uVar10 = 0;
  local_a0 = param_2;
  do {
    while( true ) {
      uVar8 = uVar10 ^ 7;
      if (*(ulong *)(local_b8 + 0x28) < *(long *)(local_b8 + 0x30) + uVar8) break;
      puStack_e0 = (undefined1 *)0x11f3888;
      FUN_011f4580(*(long *)(local_b8 + 0x30) + *(long *)(local_b8 + 0x20),
                   "thread localhost" + uVar10,uVar8);
      *(long *)(local_b8 + 0x30) = *(long *)(local_b8 + 0x30) + uVar8;
      uVar10 = uVar10 + uVar8;
      if (6 < uVar10) goto LAB_011f38e5;
    }
    puStack_e0 = (undefined1 *)0x11f38c3;
    local_48 = "thread localhost" + uVar10;
    local_40 = uVar8;
    (**(code **)*local_50)(&local_98,local_50,&local_48,1,1);
    if (local_90 != 0) goto LAB_011f3c70;
    uVar10 = uVar10 + CONCAT44(uStack_94,local_98);
  } while (uVar10 < 7);
LAB_011f38e5:
  uVar10 = (ulong)uVar7;
  lVar5 = 0x41;
  if (uVar7 < 100) {
    if (9 < uVar7) goto LAB_011f395c;
LAB_011f3939:
    *(byte *)((long)&local_a0 + lVar5 + 7) = (byte)uVar10 | 0x30;
    lVar6 = lVar5 + -1;
    lVar5 = lVar5 + -0x42;
  }
  else {
    do {
      uVar8 = uVar10 / 100;
      uVar7 = (uint)(uVar10 / 100);
      *(undefined2 *)((long)&local_a0 + lVar5 + 6) = (&DAT_011b99d6)[(int)uVar10 + uVar7 * -100];
      lVar5 = lVar5 + -2;
      bVar11 = 9999 < uVar10;
      uVar10 = uVar8;
    } while (bVar11);
    if (uVar7 < 10) goto LAB_011f3939;
LAB_011f395c:
    *(undefined2 *)((long)&local_a0 + lVar5 + 6) = (&DAT_011b99d6)[uVar10];
    lVar6 = lVar5 + -2;
    lVar5 = lVar5 + -0x43;
  }
  if (lVar5 != 0) {
    uVar8 = -lVar5;
    uVar10 = 0;
    do {
      while( true ) {
        pcVar2 = (char *)((long)&local_98 + uVar10 + lVar6);
        lVar5 = uVar8 - uVar10;
        if (*(ulong *)(local_b8 + 0x28) < (ulong)(*(long *)(local_b8 + 0x30) + lVar5)) break;
        puStack_e0 = (undefined1 *)0x11f3c14;
        FUN_011f4580(*(long *)(local_b8 + 0x30) + *(long *)(local_b8 + 0x20),pcVar2,lVar5);
        *(long *)(local_b8 + 0x30) = *(long *)(local_b8 + 0x30) + lVar5;
        uVar10 = uVar10 + lVar5;
        if (uVar8 <= uVar10) goto LAB_011f397d;
      }
      puStack_e0 = (undefined1 *)0x11f3c58;
      local_c8 = pcVar2;
      local_c0 = lVar5;
      (**(code **)*local_50)(&local_48,local_50,&local_c8,1,1);
      if ((short)local_40 != 0) goto LAB_011f3c70;
      uVar10 = uVar10 + (long)local_48;
    } while (uVar10 < uVar8);
  }
LAB_011f397d:
  uVar10 = 0;
  do {
    while( true ) {
      uVar8 = 8 - uVar10;
      if (*(ulong *)(local_b8 + 0x28) < *(long *)(local_b8 + 0x30) + uVar8) break;
      puStack_e0 = (undefined1 *)0x11f39ba;
      FUN_011f4580(*(long *)(local_b8 + 0x30) + *(long *)(local_b8 + 0x20),&DAT_01000aa8 + uVar10,
                   uVar8);
      *(long *)(local_b8 + 0x30) = *(long *)(local_b8 + 0x30) + uVar8;
      uVar10 = uVar10 + uVar8;
      if (7 < uVar10) goto LAB_011f3a0f;
    }
    puStack_e0 = (undefined1 *)0x11f39f1;
    local_48 = &DAT_01000aa8 + uVar10;
    local_40 = uVar8;
    (**(code **)*local_50)(&local_98,local_50,&local_48,1,1);
    if (local_90 != 0) goto LAB_011f3c70;
    uVar10 = uVar10 + CONCAT44(uStack_94,local_98);
  } while (uVar10 < 8);
LAB_011f3a0f:
  uVar10 = local_a0;
  uVar8 = 0;
  do {
    while( true ) {
      uVar9 = uVar10 - uVar8;
      if (*(ulong *)(local_b8 + 0x28) < *(long *)(local_b8 + 0x30) + uVar9) break;
      puStack_e0 = (undefined1 *)0x11f3a4b;
      FUN_011f4580(*(long *)(local_b8 + 0x30) + *(long *)(local_b8 + 0x20),
                   (char *)(local_a8 + uVar8),uVar9);
      *(long *)(local_b8 + 0x30) = *(long *)(local_b8 + 0x30) + uVar9;
      uVar8 = uVar8 + uVar9;
      if (uVar10 <= uVar8) goto LAB_011f3aa6;
    }
    puStack_e0 = (undefined1 *)0x11f3a85;
    local_48 = (char *)(local_a8 + uVar8);
    local_40 = uVar9;
    (**(code **)*local_50)(&local_98,local_50,&local_48,1,1);
    if (local_90 != 0) goto LAB_011f3d11;
    uVar8 = uVar8 + CONCAT44(uStack_94,local_98);
  } while (uVar8 < uVar10);
LAB_011f3aa6:
  puVar4 = local_50;
  do {
    if (*(ulong *)(local_b8 + 0x30) < *(ulong *)(local_b8 + 0x28)) {
      *(undefined1 *)(*(long *)(local_b8 + 0x20) + *(ulong *)(local_b8 + 0x30)) = 10;
      *(long *)(local_b8 + 0x30) = *(long *)(local_b8 + 0x30) + 1;
      break;
    }
    local_48 = "\n";
    local_40 = 1;
    puStack_e0 = (undefined1 *)0x11f3aee;
    (**(code **)*puVar4)(&local_98,puVar4,&local_48,1,1);
    if (local_90 != 0) goto LAB_011f3d11;
  } while (CONCAT44(uStack_94,local_98) == 0);
  puStack_e0 = (undefined1 *)0x11f3b20;
  FUN_011c74a0(puVar4,local_38);
  if (DAT_011fcff0 == 0) {
    puStack_e0 = (undefined1 *)0x11f3b3b;
    (**(code **)(PTR_PTR_011fcfc8 + 0x10))(&PTR_PTR_011fcfc8);
  }
  if (DAT_011fcff0 != 0) {
    if (DAT_011fcff0 == 0x11) {
      LOCK();
      puVar1 = (ulong *)(*(long *)(in_FS_OFFSET + -0x40010) + 8);
      *puVar1 = *puVar1 ^ 1;
      UNLOCK();
    }
    DAT_011fcff0 = 0;
  }
  iVar3 = DAT_011fd300;
  _DAT_011fcfd8 = ZEXT812(0);
  register0x0000120c = 0;
  DAT_011fd2d0 = DAT_011fd2d0 + -1;
  if (DAT_011fd2d0 == 0) {
    DAT_011fd2fc = 0xffffffff;
    LOCK();
    DAT_011fd300 = 0;
    UNLOCK();
    if (iVar3 == 2) {
      syscall();
    }
  }
  goto LAB_011f3ba2;
LAB_011f3d11:
  if (DAT_011fcff0 == 0) {
    puStack_e0 = (undefined1 *)0x11f3d2c;
    (**(code **)(PTR_PTR_011fcfc8 + 0x10))(&PTR_PTR_011fcfc8);
  }
  if (DAT_011fcff0 != 0) {
    if (DAT_011fcff0 == 0x11) {
      LOCK();
      puVar1 = (ulong *)(*(long *)(in_FS_OFFSET + -0x40010) + 8);
      *puVar1 = *puVar1 ^ 1;
      UNLOCK();
    }
    DAT_011fcff0 = 0;
  }
  iVar3 = DAT_011fd300;
  _DAT_011fcfd8 = ZEXT812(0);
  register0x0000120c = 0;
  DAT_011fd2d0 = DAT_011fd2d0 + -1;
  if (DAT_011fd2d0 == 0) {
    DAT_011fd2fc = 0xffffffff;
    LOCK();
    DAT_011fd300 = 0;
    UNLOCK();
    if (iVar3 == 2) {
      syscall();
    }
  }
  goto LAB_011f3ba2;
LAB_011f3c70:
  if (DAT_011fcff0 == 0) {
    puStack_e0 = (undefined1 *)0x11f3c8b;
    (**(code **)(PTR_PTR_011fcfc8 + 0x10))(&PTR_PTR_011fcfc8);
  }
  if (DAT_011fcff0 != 0) {
    if (DAT_011fcff0 == 0x11) {
      LOCK();
      puVar1 = (ulong *)(*(long *)(in_FS_OFFSET + -0x40010) + 8);
      *puVar1 = *puVar1 ^ 1;
      UNLOCK();
    }
    DAT_011fcff0 = 0;
  }
  iVar3 = DAT_011fd300;
  _DAT_011fcfd8 = ZEXT812(0);
  register0x0000120c = 0;
  DAT_011fd2d0 = DAT_011fd2d0 + -1;
  if (DAT_011fd2d0 == 0) {
    DAT_011fd2fc = 0xffffffff;
    LOCK();
    DAT_011fd300 = 0;
    UNLOCK();
    if (iVar3 == 2) {
      syscall();
    }
  }
LAB_011f3ba2:
  _DAT_011fcfd0 = 1;
  LOCK();
  DAT_01200000 = DAT_01200000 + -1;
  UNLOCK();
  if (DAT_01200000 != '\0') {
    do {
      syscall();
    } while( true );
  }
LAB_011f3e84:
  puStack_e0 = (undefined1 *)0x11f3e89;
  FUN_011f3e90();
  uStack_100 = 0xffffffffffffffff;
  syscall();
  syscall();
  syscall();
  syscall();
  uStack_f0 = 0xffffffffffffffff;
  syscall();
  do {
    LOCK();
    bVar11 = DAT_01200001 == '\0';
    if (bVar11) {
      DAT_01200001 = '\x01';
    }
    UNLOCK();
    uStack_e1 = !bVar11;
  } while (!bVar11);
  auStack_120._0_12_ = ZEXT812(0);
  auStack_120._12_4_ = 0;
  uStack_110 = 0;
  puStack_e0 = &stack0xfffffffffffffff8;
  FUN_011c73e0(auStack_120,&uStack_f0,0);
  syscall();
  syscall();
  uStack_f8 = 0x20;
  syscall();
  DAT_00000000 = 0;
  FUN_011c7440(9,&uStack_f8,0,0x11f3f66);
  syscall();
                    /* WARNING: Subroutine does not return */
  FUN_011f3790("TODO implement netWriteFile",0x1b,extraout_RDX,0x11f3f84);
}


// ---- FUN_011f3e90 @ 011f3e90

void FUN_011f3e90(void)

{
  undefined8 extraout_RDX;
  undefined8 in_R8;
  undefined8 in_R9;
  bool bVar1;
  undefined1 local_48 [16];
  undefined8 local_38;
  undefined8 local_28;
  undefined8 local_20;
  undefined8 local_18;
  undefined1 local_9;
  
  local_28 = 0xffffffffffffffff;
  syscall();
  syscall();
  syscall();
  syscall();
  local_18 = 0xffffffffffffffff;
  syscall();
  do {
    LOCK();
    bVar1 = DAT_01200001 == '\0';
    if (bVar1) {
      DAT_01200001 = '\x01';
    }
    UNLOCK();
    local_9 = !bVar1;
  } while (!bVar1);
  local_48._0_12_ = ZEXT812(0);
  local_48._12_4_ = 0;
  local_38 = 0;
  FUN_011c73e0(local_48,&local_18,0);
  syscall();
  syscall();
  local_20 = 0x20;
  syscall();
  DAT_00000000 = 0;
  FUN_011c7440(9,&local_20,0,0x11f3f66);
  syscall();
                    /* WARNING: Subroutine does not return */
  FUN_011f3790("TODO implement netWriteFile",0x1b,extraout_RDX,0x11f3f84,in_R8,in_R9,
               &stack0xfffffffffffffff8);
}


// ---- FUN_011f3f90 @ 011f3f90

void FUN_011f3f90(void)

{
                    /* WARNING: Subroutine does not return */
  FUN_011f3790("TODO implement netWriteFile",0x1b);
}


// ---- FUN_011f3fb0 @ 011f3fb0

undefined1  [16] FUN_011f3fb0(undefined8 param_1,ulong param_2,ulong param_3,ulong *param_4)

{
  long lVar1;
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  long in_FS_OFFSET;
  bool bVar7;
  undefined1 auVar8 [16];
  
  uVar6 = param_3;
  if ((char)param_4[1] != '\0') {
    uVar6 = *param_4 / 1000000000;
  }
  if ((param_3 & 1) == 0) {
    lVar1 = *(long *)(in_FS_OFFSET + -0x40010);
    if ((lVar1 != 0) && ((*(byte *)(lVar1 + 0x21c) & 1) == 0)) {
      uVar4 = *(ulong *)(lVar1 + 8);
      do {
        uVar5 = uVar4;
        LOCK();
        uVar4 = *(ulong *)(lVar1 + 8);
        bVar7 = uVar5 == uVar4;
        if (bVar7) {
          *(ulong *)(lVar1 + 8) = uVar5 | 3;
          uVar4 = uVar5;
        }
        UNLOCK();
      } while (!bVar7);
      if ((uVar4 & 7) == 0) {
        syscall();
        LOCK();
        *(ulong *)(lVar1 + 8) = *(ulong *)(lVar1 + 8) ^ 3;
        UNLOCK();
        auVar3._8_8_ = 0;
        auVar3._0_8_ = param_2 & 0xffffffff;
        return auVar3 << 0x40;
      }
      uVar5 = CONCAT62((int6)(uVar5 >> 0x10),0x11);
      if (((uint)uVar4 & 7) == 6) goto LAB_011f4003;
    }
    syscall();
    auVar2._8_8_ = 0;
    auVar2._0_8_ = param_2 & 0xffffffff;
    return auVar2 << 0x40;
  }
  uVar6 = param_2 & 0xffffffff;
  syscall();
  uVar5 = 0;
LAB_011f4003:
  auVar8._0_8_ = uVar5 & 0xffffffff;
  auVar8._8_8_ = uVar6;
  return auVar8;
}


// ---- FUN_011f4080 @ 011f4080

void FUN_011f4080(void)

{
                    /* WARNING: Subroutine does not return */
  FUN_011f3790("TODO processSpawnPath",0x15);
}


// ---- FUN_011f40a0 @ 011f40a0

void FUN_011f40a0(void)

{
                    /* WARNING: Subroutine does not return */
  FUN_011f3790("TODO processReplacePath",0x17);
}


// ---- FUN_011f40c0 @ 011f40c0

undefined8 FUN_011f40c0(undefined8 param_1,undefined8 param_2,long param_3,ulong param_4)

{
  undefined1 auVar1 [32];
  ulong uVar2;
  long lVar3;
  ulong uVar4;
  
  lVar3 = 0;
  uVar2 = param_4;
  if (0x1f < param_4) {
    do {
      auVar1 = vpcmpeqb_avx2(SUB6432(ZEXT1664((undefined1  [16])0x0),0),
                             *(undefined1 (*) [32])(param_3 + lVar3));
      if ((((((((((((((((((((((((((((((((SUB321(auVar1 >> 7,0) & 1) != 0 ||
                                       (SUB321(auVar1 >> 0xf,0) & 1) != 0) ||
                                      (SUB321(auVar1 >> 0x17,0) & 1) != 0) ||
                                     (SUB321(auVar1 >> 0x1f,0) & 1) != 0) ||
                                    (SUB321(auVar1 >> 0x27,0) & 1) != 0) ||
                                   (SUB321(auVar1 >> 0x2f,0) & 1) != 0) ||
                                  (SUB321(auVar1 >> 0x37,0) & 1) != 0) ||
                                 (SUB321(auVar1 >> 0x3f,0) & 1) != 0) ||
                                (SUB321(auVar1 >> 0x47,0) & 1) != 0) ||
                               (SUB321(auVar1 >> 0x4f,0) & 1) != 0) ||
                              (SUB321(auVar1 >> 0x57,0) & 1) != 0) ||
                             (SUB321(auVar1 >> 0x5f,0) & 1) != 0) ||
                            (SUB321(auVar1 >> 0x67,0) & 1) != 0) ||
                           (SUB321(auVar1 >> 0x6f,0) & 1) != 0) ||
                          (SUB321(auVar1 >> 0x77,0) & 1) != 0) || SUB321(auVar1 >> 0x7f,0) != '\0')
                        || (SUB321(auVar1 >> 0x87,0) & 1) != 0) ||
                       (SUB321(auVar1 >> 0x8f,0) & 1) != 0) || (SUB321(auVar1 >> 0x97,0) & 1) != 0)
                     || (SUB321(auVar1 >> 0x9f,0) & 1) != 0) || (SUB321(auVar1 >> 0xa7,0) & 1) != 0)
                   || (SUB321(auVar1 >> 0xaf,0) & 1) != 0) || (SUB321(auVar1 >> 0xb7,0) & 1) != 0)
                 || SUB321(auVar1 >> 0xbf,0) != '\0') || (SUB321(auVar1 >> 199,0) & 1) != 0) ||
               (SUB321(auVar1 >> 0xcf,0) & 1) != 0) || (SUB321(auVar1 >> 0xd7,0) & 1) != 0) ||
             (SUB321(auVar1 >> 0xdf,0) & 1) != 0) || (SUB321(auVar1 >> 0xe7,0) & 1) != 0) ||
           (SUB321(auVar1 >> 0xef,0) & 1) != 0) || (SUB321(auVar1 >> 0xf7,0) & 1) != 0) ||
          auVar1[0x1f] < '\0') {
        return 0x32;
      }
      lVar3 = lVar3 + 0x20;
      uVar2 = uVar2 - 0x20;
    } while (0x1f < uVar2);
  }
  if (uVar2 != 0) {
    uVar4 = 0;
    do {
      if (*(char *)(param_3 + lVar3 + uVar4) == '\0') {
        return 0x32;
      }
      uVar4 = uVar4 + 1;
    } while (uVar2 != uVar4);
  }
  if (0xfff < param_4) {
    return 0x31;
  }
                    /* WARNING: Subroutine does not return */
  FUN_011f3790("TODO implement dirSetFileOwner",0x1e);
}


// ---- FUN_011f4140 @ 011f4140

void FUN_011f4140(long param_1)

{
  char *pcVar1;
  long lVar2;
  
  lVar2 = -1;
  do {
    pcVar1 = (char *)(param_1 + 1 + lVar2);
    lVar2 = lVar2 + 1;
  } while (*pcVar1 != '\0');
  return;
}


// ---- FUN_011f4160 @ 011f4160

void FUN_011f4160(long param_1,undefined1 param_2,ulong param_3)

{
  ulong uVar1;
  ulong uVar2;
  
  if (param_3 != 0) {
    uVar2 = param_3;
    if ((param_3 & 7) != 0) {
      uVar1 = 0;
      do {
        *(undefined1 *)(param_1 + uVar1) = param_2;
        uVar1 = uVar1 + 1;
      } while ((param_3 & 7) != uVar1);
      uVar2 = param_3 - uVar1;
      param_1 = uVar1 + param_1;
    }
    if (7 < param_3) {
      uVar1 = 0;
      do {
        *(undefined1 *)(param_1 + uVar1) = param_2;
        *(undefined1 *)(param_1 + 1 + uVar1) = param_2;
        *(undefined1 *)(param_1 + 2 + uVar1) = param_2;
        *(undefined1 *)(param_1 + 3 + uVar1) = param_2;
        *(undefined1 *)(param_1 + 4 + uVar1) = param_2;
        *(undefined1 *)(param_1 + 5 + uVar1) = param_2;
        *(undefined1 *)(param_1 + 6 + uVar1) = param_2;
        *(undefined1 *)(param_1 + 7 + uVar1) = param_2;
        uVar1 = uVar1 + 8;
      } while (uVar2 != uVar1);
    }
  }
  return;
}


// ---- FUN_011f41f0 @ 011f41f0

void FUN_011f41f0(undefined8 *param_1,undefined8 *param_2,ulong param_3)

{
  undefined8 *puVar1;
  long lVar2;
  undefined8 *puVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  ulong uVar20;
  long lVar21;
  long lVar22;
  ulong uVar23;
  ulong uVar24;
  
  if (0xf < param_3) {
    if (param_3 < 0x40) {
      uVar20 = (ulong)((uint)(param_3 >> 1) & 0x10);
      lVar22 = (param_3 - 0x10) - uVar20;
      uVar9 = param_2[1];
      uVar10 = *(undefined8 *)((long)param_2 + uVar20);
      uVar11 = ((undefined8 *)((long)param_2 + uVar20))[1];
      puVar1 = (undefined8 *)((long)param_2 + lVar22);
      uVar12 = *puVar1;
      uVar13 = puVar1[1];
      puVar1 = (undefined8 *)((long)param_2 + (param_3 - 0x10));
      uVar14 = *puVar1;
      uVar15 = puVar1[1];
      *param_1 = *param_2;
      param_1[1] = uVar9;
      *(undefined8 *)((long)param_1 + uVar20) = uVar10;
      ((undefined8 *)((long)param_1 + uVar20))[1] = uVar11;
      puVar1 = (undefined8 *)((long)param_1 + lVar22);
      *puVar1 = uVar12;
      puVar1[1] = uVar13;
      param_1 = (undefined8 *)((long)param_1 + (param_3 - 0x10));
      *param_1 = uVar14;
      param_1[1] = uVar15;
    }
    else if (param_2 < param_1) {
      puVar1 = (undefined8 *)((long)param_2 + (param_3 - 0x20));
      uVar9 = *puVar1;
      uVar10 = puVar1[1];
      uVar11 = puVar1[2];
      uVar12 = puVar1[3];
      uVar13 = *param_2;
      uVar14 = param_2[1];
      uVar15 = param_2[2];
      uVar16 = param_2[3];
      uVar20 = (ulong)(param_3 + (long)param_1) & 0xffffffffffffffe0;
      uVar23 = uVar20 - (long)param_1;
      if (0x1f < uVar23) {
        uVar24 = uVar23 >> 5;
        lVar22 = 1;
        if (6 < uVar24 - 1) {
          lVar21 = -0x20;
          do {
            puVar3 = (undefined8 *)((long)param_2 + lVar21 + uVar23);
            uVar17 = puVar3[1];
            uVar18 = puVar3[2];
            uVar19 = puVar3[3];
            puVar1 = (undefined8 *)(uVar20 + lVar21);
            *puVar1 = *puVar3;
            puVar1[1] = uVar17;
            puVar1[2] = uVar18;
            puVar1[3] = uVar19;
            puVar1 = (undefined8 *)((long)param_2 + lVar21 + (uVar23 - 0x20));
            uVar17 = puVar1[1];
            uVar18 = puVar1[2];
            uVar19 = puVar1[3];
            puVar3 = (undefined8 *)((uVar20 - 0x20) + lVar21);
            *puVar3 = *puVar1;
            puVar3[1] = uVar17;
            puVar3[2] = uVar18;
            puVar3[3] = uVar19;
            puVar1 = (undefined8 *)((long)param_2 + lVar21 + (uVar23 - 0x40));
            uVar17 = puVar1[1];
            uVar18 = puVar1[2];
            uVar19 = puVar1[3];
            puVar3 = (undefined8 *)((uVar20 - 0x40) + lVar21);
            *puVar3 = *puVar1;
            puVar3[1] = uVar17;
            puVar3[2] = uVar18;
            puVar3[3] = uVar19;
            puVar1 = (undefined8 *)((long)param_2 + lVar21 + (uVar23 - 0x60));
            uVar17 = puVar1[1];
            uVar18 = puVar1[2];
            uVar19 = puVar1[3];
            puVar3 = (undefined8 *)((uVar20 - 0x60) + lVar21);
            *puVar3 = *puVar1;
            puVar3[1] = uVar17;
            puVar3[2] = uVar18;
            puVar3[3] = uVar19;
            puVar1 = (undefined8 *)((long)param_2 + lVar21 + (uVar23 - 0x80));
            uVar17 = puVar1[1];
            uVar18 = puVar1[2];
            uVar19 = puVar1[3];
            puVar3 = (undefined8 *)((uVar20 - 0x80) + lVar21);
            *puVar3 = *puVar1;
            puVar3[1] = uVar17;
            puVar3[2] = uVar18;
            puVar3[3] = uVar19;
            puVar1 = (undefined8 *)((long)param_2 + lVar21 + (uVar23 - 0xa0));
            uVar17 = puVar1[1];
            uVar18 = puVar1[2];
            uVar19 = puVar1[3];
            puVar3 = (undefined8 *)((uVar20 - 0xa0) + lVar21);
            *puVar3 = *puVar1;
            puVar3[1] = uVar17;
            puVar3[2] = uVar18;
            puVar3[3] = uVar19;
            puVar1 = (undefined8 *)((long)param_2 + lVar21 + (uVar23 - 0xc0));
            uVar17 = puVar1[1];
            uVar18 = puVar1[2];
            uVar19 = puVar1[3];
            puVar3 = (undefined8 *)((uVar20 - 0xc0) + lVar21);
            *puVar3 = *puVar1;
            puVar3[1] = uVar17;
            puVar3[2] = uVar18;
            puVar3[3] = uVar19;
            puVar1 = (undefined8 *)((long)param_2 + lVar21 + (uVar23 - 0xe0));
            uVar17 = puVar1[1];
            uVar18 = puVar1[2];
            uVar19 = puVar1[3];
            puVar3 = (undefined8 *)((uVar20 - 0xe0) + lVar21);
            *puVar3 = *puVar1;
            puVar3[1] = uVar17;
            puVar3[2] = uVar18;
            puVar3[3] = uVar19;
            lVar21 = lVar21 + -0x100;
            lVar2 = lVar22 - (uVar24 & 0xfffffffffffffff8);
            lVar22 = lVar22 + 8;
          } while (lVar2 != -7);
        }
        if ((uVar24 & 7) != 0) {
          lVar21 = 0;
          do {
            puVar1 = (undefined8 *)((long)param_2 + lVar21 + uVar23 + lVar22 * -0x20);
            uVar17 = puVar1[1];
            uVar18 = puVar1[2];
            uVar19 = puVar1[3];
            puVar3 = (undefined8 *)(uVar20 + lVar22 * -0x20 + lVar21);
            *puVar3 = *puVar1;
            puVar3[1] = uVar17;
            puVar3[2] = uVar18;
            puVar3[3] = uVar19;
            lVar21 = lVar21 + -0x20;
          } while ((ulong)(((uint)uVar24 & 7) << 5) + lVar21 != 0);
        }
      }
      *param_1 = uVar13;
      param_1[1] = uVar14;
      param_1[2] = uVar15;
      param_1[3] = uVar16;
      param_1 = (undefined8 *)((long)param_1 + (param_3 - 0x20));
      *param_1 = uVar9;
      param_1[1] = uVar10;
      param_1[2] = uVar11;
      param_1[3] = uVar12;
    }
    else {
      uVar9 = *param_2;
      uVar10 = param_2[1];
      uVar11 = param_2[2];
      uVar12 = param_2[3];
      puVar1 = (undefined8 *)((long)param_2 + (param_3 - 0x20));
      uVar13 = *puVar1;
      uVar14 = puVar1[1];
      uVar15 = puVar1[2];
      uVar16 = puVar1[3];
      uVar20 = (ulong)((uint)param_2 & 0x1f);
      uVar23 = (param_3 + uVar20) - 0x20 >> 5;
      if (uVar23 - 1 < 7) {
        uVar24 = 0;
      }
      else {
        uVar24 = 0;
        lVar22 = -uVar20;
        do {
          lVar21 = lVar22 + 0x100;
          puVar1 = (undefined8 *)((long)param_2 + lVar22 + 0x20);
          uVar17 = puVar1[1];
          uVar18 = puVar1[2];
          uVar19 = puVar1[3];
          puVar3 = (undefined8 *)((long)param_1 + lVar22 + 0x20);
          *puVar3 = *puVar1;
          puVar3[1] = uVar17;
          puVar3[2] = uVar18;
          puVar3[3] = uVar19;
          puVar1 = (undefined8 *)((long)param_2 + lVar22 + 0x40);
          uVar17 = puVar1[1];
          uVar18 = puVar1[2];
          uVar19 = puVar1[3];
          puVar3 = (undefined8 *)((long)param_1 + lVar22 + 0x40);
          *puVar3 = *puVar1;
          puVar3[1] = uVar17;
          puVar3[2] = uVar18;
          puVar3[3] = uVar19;
          puVar1 = (undefined8 *)((long)param_2 + lVar22 + 0x60);
          uVar17 = puVar1[1];
          uVar18 = puVar1[2];
          uVar19 = puVar1[3];
          puVar3 = (undefined8 *)((long)param_1 + lVar22 + 0x60);
          *puVar3 = *puVar1;
          puVar3[1] = uVar17;
          puVar3[2] = uVar18;
          puVar3[3] = uVar19;
          puVar1 = (undefined8 *)((long)param_2 + lVar22 + 0x80);
          uVar17 = puVar1[1];
          uVar18 = puVar1[2];
          uVar19 = puVar1[3];
          puVar3 = (undefined8 *)((long)param_1 + lVar22 + 0x80);
          *puVar3 = *puVar1;
          puVar3[1] = uVar17;
          puVar3[2] = uVar18;
          puVar3[3] = uVar19;
          puVar1 = (undefined8 *)((long)param_2 + lVar22 + 0xa0);
          uVar17 = puVar1[1];
          uVar18 = puVar1[2];
          uVar19 = puVar1[3];
          puVar3 = (undefined8 *)((long)param_1 + lVar22 + 0xa0);
          *puVar3 = *puVar1;
          puVar3[1] = uVar17;
          puVar3[2] = uVar18;
          puVar3[3] = uVar19;
          puVar1 = (undefined8 *)((long)param_2 + lVar22 + 0xc0);
          uVar17 = puVar1[1];
          uVar18 = puVar1[2];
          uVar19 = puVar1[3];
          puVar3 = (undefined8 *)((long)param_1 + lVar22 + 0xc0);
          *puVar3 = *puVar1;
          puVar3[1] = uVar17;
          puVar3[2] = uVar18;
          puVar3[3] = uVar19;
          puVar1 = (undefined8 *)((long)param_2 + lVar22 + 0xe0);
          uVar17 = puVar1[1];
          uVar18 = puVar1[2];
          uVar19 = puVar1[3];
          puVar3 = (undefined8 *)((long)param_1 + lVar22 + 0xe0);
          *puVar3 = *puVar1;
          puVar3[1] = uVar17;
          puVar3[2] = uVar18;
          puVar3[3] = uVar19;
          puVar1 = (undefined8 *)((long)param_2 + lVar21);
          uVar17 = puVar1[1];
          uVar18 = puVar1[2];
          uVar19 = puVar1[3];
          puVar3 = (undefined8 *)((long)param_1 + lVar21);
          *puVar3 = *puVar1;
          puVar3[1] = uVar17;
          puVar3[2] = uVar18;
          puVar3[3] = uVar19;
          uVar24 = uVar24 + 8;
          lVar22 = lVar21;
        } while ((uVar23 & 0xfffffffffffffff8) != uVar24);
      }
      if ((uVar23 & 7) != 0) {
        lVar22 = uVar24 * 0x20 - uVar20;
        uVar20 = 0;
        do {
          puVar1 = (undefined8 *)((long)param_2 + uVar20 + lVar22 + 0x20);
          uVar17 = puVar1[1];
          uVar18 = puVar1[2];
          uVar19 = puVar1[3];
          puVar3 = (undefined8 *)((long)param_1 + uVar20 + lVar22 + 0x20);
          *puVar3 = *puVar1;
          puVar3[1] = uVar17;
          puVar3[2] = uVar18;
          puVar3[3] = uVar19;
          uVar20 = uVar20 + 0x20;
        } while (((uint)uVar23 & 7) << 5 != uVar20);
      }
      puVar1 = (undefined8 *)((long)param_1 + (param_3 - 0x20));
      *puVar1 = uVar13;
      puVar1[1] = uVar14;
      puVar1[2] = uVar15;
      puVar1[3] = uVar16;
      *param_1 = uVar9;
      param_1[1] = uVar10;
      param_1[2] = uVar11;
      param_1[3] = uVar12;
    }
    return;
  }
  if (param_3 < 4) {
    if (param_3 != 0) {
      uVar4 = *(undefined1 *)((long)param_2 + (param_3 >> 1));
      uVar5 = *(undefined1 *)((long)param_2 + (param_3 - 1));
      *(undefined1 *)param_1 = *(undefined1 *)param_2;
      *(undefined1 *)((long)param_1 + (param_3 >> 1)) = uVar4;
      *(undefined1 *)((long)param_1 + (param_3 - 1)) = uVar5;
      return;
    }
  }
  else {
    uVar20 = (ulong)((uint)(param_3 >> 1) & 4);
    lVar22 = (param_3 - 4) - uVar20;
    uVar6 = *(undefined4 *)((long)param_2 + uVar20);
    uVar7 = *(undefined4 *)((long)param_2 + lVar22);
    uVar8 = *(undefined4 *)((long)param_2 + (param_3 - 4));
    *(undefined4 *)param_1 = *(undefined4 *)param_2;
    *(undefined4 *)((long)param_1 + uVar20) = uVar6;
    *(undefined4 *)((long)param_1 + lVar22) = uVar7;
    *(undefined4 *)((long)param_1 + (param_3 - 4)) = uVar8;
  }
  return;
}


// ---- FUN_011f4580 @ 011f4580

void FUN_011f4580(undefined8 *param_1,undefined8 *param_2,ulong param_3)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  long lVar6;
  ulong uVar7;
  ulong uVar8;
  ulong uVar9;
  long lVar10;
  
  if (param_3 < 0x10) {
    if (3 < param_3) {
      uVar9 = (ulong)((uint)param_3 >> 1 & 4);
      lVar6 = (param_3 - 4) - uVar9;
      *(undefined4 *)param_1 = *(undefined4 *)param_2;
      *(undefined4 *)((long)param_1 + uVar9) = *(undefined4 *)((long)param_2 + uVar9);
      *(undefined4 *)((long)param_1 + lVar6) = *(undefined4 *)((long)param_2 + lVar6);
      *(undefined4 *)((long)param_1 + (param_3 - 4)) =
           *(undefined4 *)((long)param_2 + (param_3 - 4));
      return;
    }
    if (param_3 != 0) {
      *(undefined1 *)param_1 = *(undefined1 *)param_2;
      *(undefined1 *)((long)param_1 + (param_3 >> 1)) =
           *(undefined1 *)((long)param_2 + (param_3 >> 1));
      *(undefined1 *)((long)param_1 + (param_3 - 1)) =
           *(undefined1 *)((long)param_2 + (param_3 - 1));
      return;
    }
  }
  else {
    if (0x3f < param_3) {
      uVar3 = param_2[1];
      uVar4 = param_2[2];
      uVar5 = param_2[3];
      *param_1 = *param_2;
      param_1[1] = uVar3;
      param_1[2] = uVar4;
      param_1[3] = uVar5;
      uVar9 = (ulong)((uint)param_2 & 0x1f);
      uVar7 = (uVar9 + param_3) - 0x20 >> 5;
      if (uVar7 - 1 < 7) {
        uVar8 = 0;
      }
      else {
        uVar8 = 0;
        lVar6 = -uVar9;
        do {
          lVar10 = lVar6 + 0x100;
          puVar1 = (undefined8 *)((long)param_2 + lVar6 + 0x20);
          uVar3 = puVar1[1];
          uVar4 = puVar1[2];
          uVar5 = puVar1[3];
          puVar2 = (undefined8 *)((long)param_1 + lVar6 + 0x20);
          *puVar2 = *puVar1;
          puVar2[1] = uVar3;
          puVar2[2] = uVar4;
          puVar2[3] = uVar5;
          puVar1 = (undefined8 *)((long)param_2 + lVar6 + 0x40);
          uVar3 = puVar1[1];
          uVar4 = puVar1[2];
          uVar5 = puVar1[3];
          puVar2 = (undefined8 *)((long)param_1 + lVar6 + 0x40);
          *puVar2 = *puVar1;
          puVar2[1] = uVar3;
          puVar2[2] = uVar4;
          puVar2[3] = uVar5;
          puVar1 = (undefined8 *)((long)param_2 + lVar6 + 0x60);
          uVar3 = puVar1[1];
          uVar4 = puVar1[2];
          uVar5 = puVar1[3];
          puVar2 = (undefined8 *)((long)param_1 + lVar6 + 0x60);
          *puVar2 = *puVar1;
          puVar2[1] = uVar3;
          puVar2[2] = uVar4;
          puVar2[3] = uVar5;
          puVar1 = (undefined8 *)((long)param_2 + lVar6 + 0x80);
          uVar3 = puVar1[1];
          uVar4 = puVar1[2];
          uVar5 = puVar1[3];
          puVar2 = (undefined8 *)((long)param_1 + lVar6 + 0x80);
          *puVar2 = *puVar1;
          puVar2[1] = uVar3;
          puVar2[2] = uVar4;
          puVar2[3] = uVar5;
          puVar1 = (undefined8 *)((long)param_2 + lVar6 + 0xa0);
          uVar3 = puVar1[1];
          uVar4 = puVar1[2];
          uVar5 = puVar1[3];
          puVar2 = (undefined8 *)((long)param_1 + lVar6 + 0xa0);
          *puVar2 = *puVar1;
          puVar2[1] = uVar3;
          puVar2[2] = uVar4;
          puVar2[3] = uVar5;
          puVar1 = (undefined8 *)((long)param_2 + lVar6 + 0xc0);
          uVar3 = puVar1[1];
          uVar4 = puVar1[2];
          uVar5 = puVar1[3];
          puVar2 = (undefined8 *)((long)param_1 + lVar6 + 0xc0);
          *puVar2 = *puVar1;
          puVar2[1] = uVar3;
          puVar2[2] = uVar4;
          puVar2[3] = uVar5;
          puVar1 = (undefined8 *)((long)param_2 + lVar6 + 0xe0);
          uVar3 = puVar1[1];
          uVar4 = puVar1[2];
          uVar5 = puVar1[3];
          puVar2 = (undefined8 *)((long)param_1 + lVar6 + 0xe0);
          *puVar2 = *puVar1;
          puVar2[1] = uVar3;
          puVar2[2] = uVar4;
          puVar2[3] = uVar5;
          puVar1 = (undefined8 *)((long)param_2 + lVar10);
          uVar3 = puVar1[1];
          uVar4 = puVar1[2];
          uVar5 = puVar1[3];
          puVar2 = (undefined8 *)((long)param_1 + lVar10);
          *puVar2 = *puVar1;
          puVar2[1] = uVar3;
          puVar2[2] = uVar4;
          puVar2[3] = uVar5;
          uVar8 = uVar8 + 8;
          lVar6 = lVar10;
        } while ((uVar7 & 0xfffffffffffffff8) != uVar8);
      }
      if ((uVar7 & 7) != 0) {
        lVar6 = uVar8 * 0x20 - uVar9;
        uVar9 = 0;
        do {
          puVar1 = (undefined8 *)((long)param_2 + uVar9 + lVar6 + 0x20);
          uVar3 = puVar1[1];
          uVar4 = puVar1[2];
          uVar5 = puVar1[3];
          puVar2 = (undefined8 *)((long)param_1 + uVar9 + lVar6 + 0x20);
          *puVar2 = *puVar1;
          puVar2[1] = uVar3;
          puVar2[2] = uVar4;
          puVar2[3] = uVar5;
          uVar9 = uVar9 + 0x20;
        } while (((uint)uVar7 & 7) << 5 != uVar9);
      }
      param_2 = (undefined8 *)((long)param_2 + (param_3 - 0x20));
      uVar3 = param_2[1];
      uVar4 = param_2[2];
      uVar5 = param_2[3];
      param_1 = (undefined8 *)((long)param_1 + (param_3 - 0x20));
      *param_1 = *param_2;
      param_1[1] = uVar3;
      param_1[2] = uVar4;
      param_1[3] = uVar5;
      return;
    }
    uVar9 = (ulong)((uint)param_3 >> 1 & 0x10);
    lVar6 = (param_3 - 0x10) - uVar9;
    uVar3 = param_2[1];
    *param_1 = *param_2;
    param_1[1] = uVar3;
    uVar3 = ((undefined8 *)((long)param_2 + uVar9))[1];
    *(undefined8 *)((long)param_1 + uVar9) = *(undefined8 *)((long)param_2 + uVar9);
    ((undefined8 *)((long)param_1 + uVar9))[1] = uVar3;
    puVar1 = (undefined8 *)((long)param_2 + lVar6);
    uVar3 = puVar1[1];
    puVar2 = (undefined8 *)((long)param_1 + lVar6);
    *puVar2 = *puVar1;
    puVar2[1] = uVar3;
    param_2 = (undefined8 *)((long)param_2 + (param_3 - 0x10));
    uVar3 = param_2[1];
    param_1 = (undefined8 *)((long)param_1 + (param_3 - 0x10));
    *param_1 = *param_2;
    param_1[1] = uVar3;
  }
  return;
}


// ---- FUN_011f4760 @ 011f4760

/* WARNING: Removing unreachable block (ram,0x011f503c) */
/* WARNING: Removing unreachable block (ram,0x011f4fd2) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_011f4760(ulong param_1,double *param_2,undefined8 param_3,ulong param_4,long param_5)

{
  uint *puVar1;
  bool bVar2;
  double dVar3;
  double dVar4;
  short sVar5;
  ushort uVar6;
  int iVar7;
  ulong uVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  long lVar12;
  double dVar13;
  undefined1 *puVar14;
  uint uVar15;
  ulong uVar16;
  ulong uVar17;
  ushort uVar18;
  double *pdVar19;
  ulong uVar20;
  double *pdVar21;
  ulong uVar22;
  uint uVar23;
  long lVar24;
  long lVar25;
  long lVar26;
  ulong uVar27;
  ulong uVar28;
  ulong uVar29;
  double *pdVar30;
  ulong uVar31;
  int iVar32;
  undefined1 auVar33 [16];
  double dVar34;
  undefined1 auVar35 [16];
  undefined1 auVar36 [16];
  undefined1 auVar37 [64];
  undefined1 auVar38 [16];
  double adStack_310 [6];
  undefined8 uStack_2e0;
  double local_2d8 [12];
  double adStack_278 [8];
  double adStack_238 [7];
  undefined1 auStack_200 [72];
  double adStack_1b8 [4];
  double *local_198;
  double local_190;
  ulong local_188;
  double local_180;
  double local_178;
  long local_e0;
  double *local_d8;
  long local_d0;
  uint auStack_c8 [4];
  undefined8 local_b8;
  undefined8 local_b0;
  uint local_a8 [20];
  ulong local_58;
  ulong local_50;
  ulong local_48;
  ulong local_40;
  ulong local_38;
  undefined1 auVar39 [64];
  
  iVar10 = (int)param_3;
  local_d8 = param_2;
  local_58 = param_1;
  uVar15 = *(uint *)(&DAT_010006c0 + param_5 * 4);
  local_48 = param_4;
  iVar7 = (int)param_4;
  uVar9 = iVar7 - 1;
  sVar5 = (short)((short)param_3 + -3) / 0x18;
  uVar18 = ((short)(sVar5 * -0x18 + (short)param_3 + -3) >> 0xf) + sVar5;
  uVar6 = 0;
  if (0 < (short)uVar18) {
    uVar6 = uVar18;
  }
  local_40 = (ulong)uVar15;
  local_38._0_4_ = iVar10;
  if (-1 < (int)(uVar15 + uVar9)) {
    uVar23 = uVar6 - uVar9;
    uVar16 = (ulong)(uVar15 + iVar7 & 3);
    if ((uVar15 + iVar7) - 1 < 3) {
      uVar17 = 0;
    }
    else {
      uVar17 = 0;
      lVar12 = (long)(int)uVar23 * 4;
      local_38 = param_3;
      do {
        dVar13 = 0.0;
        dVar34 = 0.0;
        iVar32 = (int)(uVar23 + uVar17);
        if (-1 < iVar32) {
          dVar34 = (double)*(int *)(&DAT_011b9b38 + (uVar23 + uVar17 & 0xffffffff) * 4);
        }
        adStack_310[uVar17 + 7] = dVar34;
        if (-2 < iVar32) {
          dVar13 = (double)*(int *)(&DAT_011b9b3c + uVar17 * 4 + lVar12);
        }
        adStack_310[uVar17 + 8] = dVar13;
        dVar13 = 0.0;
        dVar34 = 0.0;
        if (-3 < iVar32) {
          dVar34 = (double)*(int *)(&DAT_011b9b40 + uVar17 * 4 + lVar12);
        }
        adStack_310[uVar17 + 9] = dVar34;
        if (-4 < iVar32) {
          dVar13 = (double)*(int *)(&DAT_011b9b44 + uVar17 * 4 + lVar12);
        }
        adStack_310[uVar17 + 10] = dVar13;
        uVar17 = uVar17 + 4;
      } while ((uVar15 + iVar7 & 0xfffffffc) != uVar17);
      uVar23 = uVar23 + (int)uVar17;
    }
    if (uVar16 != 0) {
      uVar29 = 0;
      do {
        while (-1 < (int)(uVar23 + uVar29)) {
          adStack_310[uVar17 + uVar29 + 7] =
               (double)*(int *)(&DAT_011b9b38 + (uVar23 + uVar29 & 0xffffffff) * 4);
          uVar29 = uVar29 + 1;
          if (uVar16 == uVar29) goto LAB_011f4913;
        }
        adStack_310[uVar17 + uVar29 + 7] = 0.0;
        uVar29 = uVar29 + 1;
      } while (uVar16 != uVar29);
    }
  }
LAB_011f4913:
  local_38 = (ulong)((int)local_38 + (uint)uVar6 * -0x18);
  local_50 = (ulong)((iVar10 + (uint)uVar6 * -0x18) - 0x18);
  local_b8 = local_48 & 0xffffffff;
  if (-1 < (int)local_40) {
    lVar12 = local_40 + 1;
    uVar15 = (uint)local_48;
    uVar16 = (ulong)(uVar15 & 7);
    pdVar19 = (double *)(local_58 + 0x38);
    pdVar21 = adStack_310 + (ulong)uVar9 + 7;
    lVar24 = 0;
    do {
      dVar13 = 0.0;
      dVar34 = 0.0;
      if ((uint)local_48 < 8) {
        lVar25 = 0;
      }
      else {
        lVar25 = 0;
        pdVar30 = pdVar19;
        do {
          dVar13 = dVar13 + pdVar30[-7] * pdVar21[lVar25] + pdVar30[-6] * pdVar21[lVar25 + -1] +
                   pdVar30[-5] * pdVar21[lVar25 + -2] + pdVar30[-4] * pdVar21[lVar25 + -3] +
                   pdVar30[-3] * pdVar21[lVar25 + -4] + pdVar30[-2] * pdVar21[lVar25 + -5] +
                   pdVar30[-1] * pdVar21[lVar25 + -6] + *pdVar30 * pdVar21[lVar25 + -7];
          pdVar30 = pdVar30 + 8;
          lVar25 = lVar25 + -8;
        } while (-lVar25 != (ulong)(uVar15 & 0xfffffff8));
        lVar25 = -lVar25;
        dVar34 = dVar13;
      }
      if (uVar16 != 0) {
        lVar26 = -lVar25;
        uVar17 = 0;
        do {
          dVar34 = dVar34 + *(double *)(local_58 + lVar25 * 8 + uVar17 * 8) * pdVar21[lVar26];
          uVar17 = uVar17 + 1;
          lVar26 = lVar26 + -1;
        } while (uVar16 != uVar17);
      }
      adStack_278[lVar24 + 8] = dVar34;
      lVar24 = lVar24 + 1;
      pdVar21 = pdVar21 + 1;
    } while (lVar24 != lVar12);
  }
  iVar7 = (int)local_38;
  uVar9 = -(iVar7 + -0x18);
  uVar15 = -iVar7 - 0x3e6U;
  if ((int)uVar9 < (int)(-iVar7 - 0x3e6U)) {
    uVar15 = uVar9;
  }
  dVar13 = 0.0;
  uVar23 = (uint)local_50;
  if (0xfffffbcc < uVar23) {
    dVar13 = (double)(~(ulong)(uVar15 == 0x35) &
                     (0x10000000000000U >> ((ulong)(byte)((char)uVar15 - 1) & 0x3f)) + 1 >> 1);
  }
  if (0xfffffc01 < uVar23) {
    dVar13 = (double)(0x3ff0000000000000 - ((ulong)uVar9 << 0x34));
  }
  if (uVar23 < 0x400) {
    local_b0 = (double)((local_50 << 0x34) + 0x3ff0000000000000);
  }
  else {
    local_b0 = DAT_01000b28;
  }
  local_188 = (ulong)uVar9;
  local_d0 = param_5;
  local_e0 = (long)(int)local_40;
  if (iVar7 < 0x18) {
    local_b0 = dVar13;
  }
  auStack_c8[1] = 0x30 - iVar7;
  auStack_c8[2] = 0x2f - iVar7;
  auStack_c8[3] = (uint)(uVar23 == 1) << 0x16 | 0x3fffff;
  uVar15 = (uint)local_b8;
  uVar29 = (ulong)(uVar15 & 7);
  local_190 = (double)((long)(int)local_40 + -1);
  local_198 = (double *)(local_58 + 0x38);
  uVar16 = local_58;
  uVar17 = local_40;
  do {
    uVar9 = (uint)uVar17;
    uVar31 = uVar17 & 0xffffffff;
    dVar13 = adStack_278[uVar31 + 8];
    if (uVar9 != 0) {
      if (uVar9 < 4) {
        uVar28 = 0;
        uVar27 = uVar31;
      }
      else {
        pdVar19 = adStack_278 + uVar31 + 7;
        uVar28 = 0;
        do {
          auVar35 = vcvtdq2pd_avx(ZEXT416((uint)(int)(dVar13 * DAT_01000e38)));
          local_a8[uVar28] = (int)(dVar13 - auVar35._0_8_ * DAT_01001120);
          dVar13 = auVar35._0_8_ + *pdVar19;
          auVar35 = vcvtdq2pd_avx(ZEXT416((uint)(int)(dVar13 * DAT_01000e38)));
          local_a8[uVar28 + 1] = (int)(dVar13 - auVar35._0_8_ * DAT_01001120);
          dVar13 = auVar35._0_8_ + pdVar19[-1];
          auVar35 = vcvtdq2pd_avx(ZEXT416((uint)(int)(dVar13 * DAT_01000e38)));
          local_a8[uVar28 + 2] = (int)(dVar13 - auVar35._0_8_ * DAT_01001120);
          dVar13 = auVar35._0_8_ + pdVar19[-2];
          auVar35 = vcvtdq2pd_avx(ZEXT416((uint)(int)(dVar13 * DAT_01000e38)));
          uVar23 = (uint)(dVar13 - auVar35._0_8_ * DAT_01001120);
          uVar16 = (ulong)uVar23;
          local_a8[uVar28 + 3] = uVar23;
          dVar13 = auVar35._0_8_ + pdVar19[-3];
          uVar28 = uVar28 + 4;
          pdVar19 = pdVar19 + -4;
        } while ((uVar9 & 0xfffffffc) != uVar28);
        uVar27 = uVar31 - uVar28;
      }
      if ((uVar17 & 3) != 0) {
        pdVar19 = adStack_278 + uVar27 + 7;
        uVar16 = 0;
        do {
          auVar35 = vcvtdq2pd_avx(ZEXT416((uint)(int)(dVar13 * DAT_01000e38)));
          local_a8[uVar28 + uVar16] = (int)(dVar13 + auVar35._0_8_ * DAT_01000de0);
          dVar13 = auVar35._0_8_ + *pdVar19;
          uVar16 = uVar16 + 1;
          pdVar19 = pdVar19 + -1;
        } while ((uVar9 & 3) != uVar16);
      }
    }
    uStack_2e0 = 0x11f4d61;
    dVar13 = (double)FUN_011f5b20();
    uVar28 = local_b8;
    auVar35._8_8_ = 0;
    auVar35._0_8_ = dVar13 * DAT_01000be0;
    auVar35 = vroundsd_avx(auVar35,auVar35,9);
    dVar13 = dVar13 + auVar35._0_8_ * ram0x01000fa0;
    uVar23 = (uint)dVar13;
    auVar35 = vcvtdq2pd_avx(ZEXT416((uint)(int)dVar13));
    dVar13 = dVar13 - auVar35._0_8_;
    if ((int)local_38 < 0x19) {
      if ((int)local_50 == 0) {
        iVar7 = *(int *)((long)&local_b0 + uVar31 * 4 + 4) >> 0x17;
        goto LAB_011f4ed5;
      }
      iVar7 = 0;
      uVar27 = local_48;
      if (DAT_01000ce0 <= dVar13) {
        uVar23 = uVar23 + 1;
        iVar7 = 2;
        if (uVar9 == 0) {
          dVar13 = DAT_01000bf8 - dVar13;
          goto LAB_011f5050;
        }
        goto joined_r0x011f4e27;
      }
    }
    else {
      iVar7 = *(int *)((long)&local_b0 + uVar31 * 4 + 4);
      iVar10 = iVar7 >> (auStack_c8[1] & 0x1f);
      uVar23 = uVar23 + iVar10;
      iVar7 = iVar7 - (iVar10 << (auStack_c8[1] & 0x1f));
      *(int *)((long)&local_b0 + uVar31 * 4 + 4) = iVar7;
      iVar7 = iVar7 >> (auStack_c8[2] & 0x1f);
LAB_011f4ed5:
      uVar27 = local_48;
      if (0 < iVar7) {
        uVar23 = uVar23 + 1;
joined_r0x011f4e27:
        local_48 = uVar27;
        if (uVar9 - 1 < 3) {
          uVar8 = 0;
          bVar2 = false;
        }
        else {
          uVar8 = 0;
          bVar2 = false;
          do {
            while( true ) {
              iVar10 = 0xffffff;
              if ((!bVar2) && (iVar10 = 0x1000000, local_a8[uVar8] == 0)) break;
              local_a8[uVar8] = iVar10 - local_a8[uVar8];
              uVar11 = local_a8[uVar8 + 1];
              iVar10 = 0xffffff;
LAB_011f4f7f:
              local_a8[uVar8 + 1] = iVar10 - uVar11;
              uVar11 = local_a8[uVar8 + 2];
              iVar10 = 0xffffff;
LAB_011f4fe0:
              local_a8[uVar8 + 2] = iVar10 - uVar11;
              uVar11 = local_a8[uVar8 + 3];
              iVar10 = 0xffffff;
LAB_011f4f20:
              local_a8[uVar8 + 3] = iVar10 - uVar11;
              bVar2 = true;
              uVar16 = 0;
              uVar8 = uVar8 + 4;
              if ((uVar9 & 0xfffffffc) == uVar8) goto LAB_011f4e31;
            }
            uVar11 = local_a8[uVar8 + 1];
            iVar10 = 0x1000000;
            if (uVar11 != 0) goto LAB_011f4f7f;
            uVar11 = local_a8[uVar8 + 2];
            iVar10 = 0x1000000;
            if (uVar11 != 0) goto LAB_011f4fe0;
            uVar11 = local_a8[uVar8 + 3];
            iVar10 = 0x1000000;
            if (uVar11 != 0) goto LAB_011f4f20;
            bVar2 = false;
            uVar16 = 1;
            uVar8 = uVar8 + 4;
          } while ((uVar9 & 0xfffffffc) != uVar8);
        }
LAB_011f4e31:
        if ((uVar17 & 3) != 0) {
          uVar22 = 0;
          do {
            while( true ) {
              iVar10 = 0xffffff;
              if ((bVar2) || (iVar10 = 0x1000000, local_a8[uVar8 + uVar22] != 0)) break;
              bVar2 = false;
              uVar16 = 1;
              uVar22 = uVar22 + 1;
              if ((uVar9 & 3) == uVar22) goto LAB_011f4e90;
            }
            local_a8[uVar8 + uVar22] = iVar10 - local_a8[uVar8 + uVar22];
            bVar2 = true;
            uVar16 = 0;
            uVar22 = uVar22 + 1;
          } while ((uVar9 & 3) != uVar22);
        }
LAB_011f4e90:
        if (0x18 < (int)local_38) {
          puVar1 = (uint *)((long)&local_b0 + uVar31 * 4 + 4);
          *puVar1 = *puVar1 & auStack_c8[3];
        }
        if (iVar7 == 2) {
          dVar13 = DAT_01000bf8 - dVar13;
          if ((uVar16 & 1) == 0) {
            dVar13 = dVar13 - local_b0;
          }
          iVar7 = 2;
        }
      }
    }
LAB_011f5050:
    uVar8 = local_58;
    if ((dVar13 != 0.0) || (NAN(dVar13))) {
      uStack_2e0 = 0x11f52c1;
      dVar13 = (double)FUN_011f5b20(local_188);
      lVar12 = local_d0;
      if (DAT_01001120 <= dVar13) {
        auVar35 = vcvtdq2pd_avx(ZEXT416((uint)(int)(dVar13 * DAT_01000e38)));
        local_a8[uVar31] = (int)(dVar13 + auVar35._0_8_ * DAT_01000de0);
        uVar17 = (ulong)(uVar9 + 1);
        local_a8[uVar31 + 1] = (int)(dVar13 * DAT_01000e38);
        local_50 = local_38 & 0xffffffff;
      }
      else {
        local_a8[uVar31] = (int)dVar13;
      }
      goto LAB_011f5356;
    }
    if ((int)local_40 < (int)uVar9) {
      uVar22 = uVar31 - local_e0;
      uVar11 = 0;
      uVar16 = uVar31;
      if (local_e0 - uVar31 < 0xfffffffffffffff9) {
        uVar20 = uVar22 & 0xfffffffffffffff8;
        uVar11 = 0;
        do {
          uVar11 = uVar11 | *(uint *)((long)&local_b0 + uVar16 * 4 + 4) |
                   *(uint *)((long)&local_b0 + uVar16 * 4) |
                   *(uint *)((long)&local_b8 + uVar16 * 4 + 4) |
                   *(uint *)((long)&local_b8 + uVar16 * 4) | auStack_c8[uVar16 + 3] |
                   auStack_c8[uVar16 + 2] | auStack_c8[uVar16 + 1] | auStack_c8[uVar16];
          uVar16 = uVar16 - 8;
          uVar20 = uVar20 - 8;
        } while (uVar20 != 0);
      }
      uVar20 = (ulong)((uint)uVar22 & 7);
      uVar22 = uVar22 & 7;
      while (uVar22 != 0) {
        uVar11 = uVar11 | *(uint *)((long)&local_b0 + uVar16 * 4 + 4);
        uVar16 = uVar16 - 1;
        uVar20 = uVar20 - 1;
        uVar22 = uVar20;
      }
      if (uVar11 != 0) {
        do {
          uVar31 = uVar31 - 1;
          local_50 = (ulong)((int)local_50 - 0x18);
          uVar17 = (ulong)((int)uVar17 - 1);
          lVar12 = local_d0;
        } while (local_a8[uVar31 & 0xffffffff] == 0);
LAB_011f5356:
        uVar16 = ram0x01000d28;
        uVar15 = (uint)local_50;
        if ((int)uVar15 < 0) {
          uVar9 = -uVar15;
          if (uVar15 < 0xfffffc02) {
            dVar13 = 0.0;
            if (0xfffffbcc < uVar15) {
              uVar11 = -uVar15 - 0x3fe;
              if ((int)uVar9 < (int)(-uVar15 - 0x3fe)) {
                uVar11 = uVar9;
              }
              dVar13 = (double)(~(ulong)(uVar11 == 0x35) &
                               (0x10000000000000U >> ((ulong)(byte)((char)uVar11 - 1) & 0x3f)) + 1
                               >> 1);
            }
          }
          else {
            dVar13 = (double)(0x3ff0000000000000 - ((ulong)uVar9 << 0x34));
          }
        }
        else {
          dVar13 = DAT_01000b28;
          if (uVar15 < 0x400) {
            dVar13 = (double)((local_50 << 0x34) + 0x3ff0000000000000);
          }
        }
        uVar15 = (uint)uVar17;
        if (-1 < (int)uVar15) {
          uVar29 = uVar17 & 0xffffffff;
          uVar31 = uVar29;
          if ((~uVar15 & 7) != 0) {
            uVar28 = (ulong)(uVar15 + 1 & 7);
            do {
              adStack_278[uVar31 + 8] = dVar13 * (double)(int)local_a8[uVar31];
              dVar13 = dVar13 * DAT_01000e38;
              uVar31 = uVar31 - 1;
              uVar28 = uVar28 - 1;
            } while (uVar28 != 0);
          }
          if (6 < uVar15) {
            lVar24 = uVar31 + 1;
            do {
              adStack_278[lVar24 + 7] = dVar13 * (double)*(int *)((long)&local_b0 + lVar24 * 4 + 4);
              adStack_278[lVar24 + 6] =
                   dVar13 * DAT_01000e38 * (double)*(int *)((long)&local_b0 + lVar24 * 4);
              dVar13 = dVar13 * DAT_01000e38 * DAT_01000e38;
              adStack_278[lVar24 + 5] = dVar13 * (double)*(int *)((long)&local_b8 + lVar24 * 4 + 4);
              dVar13 = dVar13 * DAT_01000e38;
              adStack_278[lVar24 + 4] = dVar13 * (double)*(int *)((long)&local_b8 + lVar24 * 4);
              dVar13 = dVar13 * DAT_01000e38;
              adStack_278[lVar24 + 3] = dVar13 * (double)(int)auStack_c8[lVar24 + 3];
              dVar13 = dVar13 * DAT_01000e38;
              adStack_278[lVar24 + 2] = dVar13 * (double)(int)auStack_c8[lVar24 + 2];
              dVar13 = dVar13 * DAT_01000e38;
              adStack_278[lVar24 + 1] = dVar13 * (double)(int)auStack_c8[lVar24 + 1];
              dVar13 = dVar13 * DAT_01000e38;
              adStack_278[lVar24] = dVar13 * (double)(int)auStack_c8[lVar24];
              dVar13 = dVar13 * DAT_01000e38;
              lVar24 = lVar24 + -8;
            } while (lVar24 != 0);
          }
          puVar14 = auStack_200 + uVar29 * 8;
          pdVar19 = adStack_278 + uVar29 + 8;
          do {
            uVar11 = uVar15 - (int)uVar29;
            uVar9 = uVar11;
            if ((int)(uint)local_40 < (int)uVar11) {
              uVar9 = (uint)local_40;
            }
            if ((int)uVar9 < 0) {
              dVar13 = 0.0;
            }
            else {
              if (uVar9 < 7) {
                dVar13 = 0.0;
                uVar31 = 0;
              }
              else {
                dVar13 = 0.0;
                uVar31 = 0;
                do {
                  dVar13 = dVar13 + (double)(&DAT_011ba600)[uVar31] *
                                    *(double *)(puVar14 + uVar31 * 8 + -0x38) +
                           (double)(&DAT_011ba608)[uVar31] *
                           *(double *)(puVar14 + uVar31 * 8 + -0x30) +
                           (double)(&DAT_011ba610)[uVar31] *
                           *(double *)(puVar14 + uVar31 * 8 + -0x28) +
                           (double)(&DAT_011ba618)[uVar31] *
                           *(double *)(puVar14 + uVar31 * 8 + -0x20) +
                           (double)(&DAT_011ba620)[uVar31] *
                           *(double *)(puVar14 + uVar31 * 8 + -0x18) +
                           (double)(&DAT_011ba628)[uVar31] *
                           *(double *)(puVar14 + uVar31 * 8 + -0x10) +
                           (double)(&DAT_011ba630)[uVar31] * *(double *)(puVar14 + uVar31 * 8 + -8)
                           + (double)(&DAT_011ba638)[uVar31] * *(double *)(puVar14 + uVar31 * 8);
                  uVar31 = uVar31 + 8;
                } while ((uVar9 + 1 & 0xfffffff8) != uVar31);
              }
              uVar9 = uVar9 + 1 & 7;
              if (uVar9 != 0) {
                uVar28 = 0;
                do {
                  dVar13 = dVar13 + (double)(&DAT_011ba600)[uVar31 + uVar28] *
                                    pdVar19[uVar31 + uVar28];
                  uVar28 = uVar28 + 1;
                } while (uVar9 != uVar28);
              }
            }
            (&local_190)[(ulong)uVar11 + 2] = dVar13;
            puVar14 = puVar14 + -8;
            pdVar19 = pdVar19 + -1;
            bVar2 = 0 < (long)uVar29;
            uVar29 = uVar29 - 1;
          } while (bVar2);
        }
        if (lVar12 - 1U < 2) {
          if ((int)uVar15 < 0) {
            dVar13 = 0.0;
          }
          else {
            uVar17 = uVar17 & 0xffffffff;
            if ((~uVar15 & 7) == 0) {
              dVar13 = 0.0;
            }
            else {
              uVar16 = (ulong)(uVar15 + 1 & 7);
              dVar13 = 0.0;
              do {
                dVar13 = dVar13 + (&local_190)[uVar17 + 2];
                uVar17 = uVar17 - 1;
                uVar16 = uVar16 - 1;
              } while (uVar16 != 0);
            }
            if (6 < uVar15) {
              do {
                dVar13 = dVar13 + (&local_190)[uVar17 + 2] + (&local_190)[uVar17 + 1] +
                         (&local_190)[uVar17] + (double)(&local_198)[uVar17] +
                         adStack_1b8[uVar17 + 3] + adStack_1b8[uVar17 + 2] + adStack_1b8[uVar17 + 1]
                         + adStack_1b8[uVar17];
                uVar17 = uVar17 - 8;
              } while (uVar17 != 0xffffffffffffffff);
            }
          }
          dVar34 = dVar13;
          if (iVar7 != 0) {
            dVar34 = (double)((ulong)dVar13 ^ _DAT_010007e0);
          }
          *local_d8 = dVar34;
          local_180 = local_180 - dVar13;
          if (0 < (int)uVar15) {
            if (uVar15 < 8) {
              lVar12 = 1;
            }
            else {
              uVar16 = 0;
              do {
                uVar17 = uVar16;
                local_180 = local_180 + (&local_190)[uVar17 + 3] + (&local_190)[uVar17 + 4] +
                            (&local_190)[uVar17 + 5] + (&local_190)[uVar17 + 6] +
                            (&local_190)[uVar17 + 7] + (&local_190)[uVar17 + 8] +
                            (&local_190)[uVar17 + 9] + (&local_190)[uVar17 + 10];
                uVar16 = uVar17 + 8;
              } while ((ulong)(uVar15 & 0x7ffffff8) != uVar17 + 8);
              lVar12 = uVar17 + 9;
            }
            if ((ulong)(uVar15 & 7) != 0) {
              uVar16 = 0;
              do {
                local_180 = local_180 + (&local_190)[lVar12 + uVar16 + 2];
                uVar16 = uVar16 + 1;
              } while ((uVar15 & 7) != uVar16);
            }
          }
          if (iVar7 != 0) {
            local_180 = (double)((ulong)local_180 ^ _DAT_010007e0);
          }
          local_d8[1] = local_180;
        }
        else if (lVar12 == 0) {
          if ((int)uVar15 < 0) {
            dVar13 = 0.0;
          }
          else {
            uVar17 = uVar17 & 0xffffffff;
            if ((~uVar15 & 7) == 0) {
              dVar13 = 0.0;
            }
            else {
              uVar16 = (ulong)(uVar15 + 1 & 7);
              dVar13 = 0.0;
              do {
                dVar13 = dVar13 + (&local_190)[uVar17 + 2];
                uVar17 = uVar17 - 1;
                uVar16 = uVar16 - 1;
              } while (uVar16 != 0);
            }
            if (6 < uVar15) {
              do {
                dVar13 = dVar13 + (&local_190)[uVar17 + 2] + (&local_190)[uVar17 + 1] +
                         (&local_190)[uVar17] + (double)(&local_198)[uVar17] +
                         adStack_1b8[uVar17 + 3] + adStack_1b8[uVar17 + 2] + adStack_1b8[uVar17 + 1]
                         + adStack_1b8[uVar17];
                uVar17 = uVar17 - 8;
              } while (uVar17 != 0xffffffffffffffff);
            }
          }
          if (iVar7 != 0) {
            dVar13 = (double)((ulong)dVar13 ^ _DAT_010007e0);
          }
          *local_d8 = dVar13;
        }
        else {
          dVar13 = 0.0;
          if (0 < (int)uVar15) {
            uVar31 = uVar17 & 0xffffffff;
            auVar38._8_8_ = 0;
            auVar38._0_8_ = (&local_190)[uVar31 + 2];
            auVar39 = ZEXT1664(auVar38);
            uVar17 = uVar17 & 3;
            uVar29 = uVar31;
            if (uVar17 == 0) {
              auVar37 = ZEXT1664(auVar38);
              uVar28 = uVar31;
            }
            else {
              do {
                uVar28 = uVar29 - 1;
                dVar34 = (&local_190)[uVar29 + 1] + auVar39._0_8_;
                auVar37 = ZEXT864((ulong)dVar34);
                (&local_190)[uVar29 + 2] = auVar39._0_8_ + ((&local_190)[uVar29 + 1] - dVar34);
                (&local_190)[uVar29 + 1] = dVar34;
                auVar39 = ZEXT864((ulong)dVar34);
                uVar17 = uVar17 - 1;
                uVar29 = uVar28;
              } while (uVar17 != 0);
            }
            if (3 < uVar15) {
              uVar28 = uVar28 + 1;
              do {
                dVar34 = (&local_190)[uVar28] + auVar37._0_8_;
                (&local_190)[uVar28 + 1] = auVar37._0_8_ + ((&local_190)[uVar28] - dVar34);
                dVar3 = (double)(&local_198)[uVar28] + dVar34;
                (&local_190)[uVar28] = dVar34 + ((double)(&local_198)[uVar28] - dVar3);
                dVar34 = adStack_1b8[uVar28 + 2];
                dVar4 = adStack_1b8[uVar28 + 3] + dVar3;
                (&local_198)[uVar28] = (double *)(dVar3 + (adStack_1b8[uVar28 + 3] - dVar4));
                dVar3 = dVar34 + dVar4;
                auVar37 = ZEXT864((ulong)dVar3);
                adStack_1b8[uVar28 + 3] = dVar4 + (dVar34 - dVar3);
                adStack_1b8[uVar28 + 2] = dVar3;
                uVar28 = uVar28 - 4;
              } while (1 < uVar28);
            }
            if (uVar15 != 1) {
              uVar17 = uVar31 + 1;
              dVar13 = (&local_190)[uVar31 + 2];
              do {
                dVar34 = (&local_190)[uVar17] + dVar13;
                (&local_190)[uVar17 + 1] = dVar13 + ((&local_190)[uVar17] - dVar34);
                (&local_190)[uVar17] = dVar34;
                uVar17 = uVar17 - 1;
                dVar13 = dVar34;
              } while (2 < uVar17);
              uVar31 = uVar31 + 1;
              dVar13 = 0.0;
              do {
                dVar13 = dVar13 + (&local_190)[uVar31 + 1];
                uVar31 = uVar31 - 1;
              } while (2 < uVar31);
            }
          }
          auVar36._8_8_ = 0;
          auVar36._0_8_ = local_180;
          if (iVar7 == 0) {
            *local_d8 = local_180;
            local_d8[1] = local_178;
            local_d8[2] = dVar13;
          }
          else {
            auVar35 = vmovhpd_avx(auVar36,local_178);
            dVar34 = (double)(auVar35._8_8_ ^ ram0x01000d28);
            *local_d8 = (double)(auVar35._0_8_ ^ ram0x01000d28);
            local_d8[1] = dVar34;
            auVar33._0_8_ = (ulong)dVar13 ^ uVar16;
            auVar33._8_8_ = uVar16;
            dVar13 = (double)vmovlpd_avx(auVar33);
            local_d8[2] = dVar13;
          }
        }
        return uVar23 & 7;
      }
    }
    uVar17 = uVar17 & 0xffffffff;
    dVar13 = local_190;
    do {
      uVar23 = (int)uVar17 + 1;
      uVar17 = (ulong)uVar23;
      puVar1 = local_a8 + (long)dVar13;
      dVar13 = (double)((long)dVar13 + -1);
    } while (*puVar1 == 0);
    iVar7 = uVar9 + (uint)uVar27;
    do {
      lVar12 = (long)iVar7;
      adStack_310[uVar31 + uVar28 + 7] =
           (double)*(int *)(&DAT_011b9b3c + uVar31 * 4 + (ulong)(uint)uVar6 * 4);
      if ((uint)uVar27 < 8) {
        dVar13 = 0.0;
        uVar16 = 0;
      }
      else {
        dVar13 = 0.0;
        lVar24 = 0;
        pdVar19 = local_198;
        do {
          dVar13 = dVar13 + pdVar19[-7] * adStack_310[lVar12 + lVar24 + 7] +
                   pdVar19[-6] * adStack_310[lVar12 + lVar24 + 6] +
                   pdVar19[-5] * adStack_310[lVar12 + lVar24 + 5] +
                   pdVar19[-4] * adStack_310[lVar12 + lVar24 + 4] +
                   pdVar19[-3] * adStack_310[lVar12 + lVar24 + 3] +
                   pdVar19[-2] * adStack_310[lVar12 + lVar24 + 2] +
                   pdVar19[-1] * adStack_310[lVar12 + lVar24 + 1] +
                   *pdVar19 * adStack_310[lVar12 + lVar24];
          pdVar19 = pdVar19 + 8;
          lVar24 = lVar24 + -8;
        } while (-lVar24 != (ulong)(uVar15 & 0xfffffff8));
        uVar16 = -lVar24;
      }
      if (uVar29 != 0) {
        lVar12 = lVar12 - uVar16;
        uVar16 = uVar8 + uVar16 * 8;
        uVar22 = 0;
        do {
          dVar13 = dVar13 + *(double *)(uVar16 + uVar22 * 8) * adStack_310[lVar12 + 7];
          uVar22 = uVar22 + 1;
          lVar12 = lVar12 + -1;
        } while (uVar29 != uVar22);
      }
      uVar22 = uVar31 + 1;
      adStack_278[uVar31 + 9] = dVar13;
      iVar7 = iVar7 + 1;
      uVar31 = uVar22;
    } while (uVar22 < (ulong)(long)(int)uVar23);
  } while( true );
}


// ---- FUN_011f5b20 @ 011f5b20

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

double FUN_011f5b20(ulong param_1)

{
  undefined1 auVar1 [16];
  uint uVar2;
  double dVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  double dVar7;
  undefined1 in_ZMM0 [64];
  undefined1 auVar8 [16];
  
  dVar7 = in_ZMM0._0_8_;
  if ((!NAN(dVar7)) && ((in_ZMM0._4_4_ >> 0x14 & 0x7ff) < 0x7ff)) {
    dVar3 = (double)((ulong)dVar7 & 0x8000000000000000);
    uVar4 = 0xb - (int)LZCOUNT((long)dVar7 * 2);
    if ((ulong)ABS(dVar7) >> 0x34 != 0) {
      uVar4 = (uint)((ulong)((long)dVar7 * 2) >> 0x35);
    }
    iVar6 = (int)param_1;
    if (iVar6 < 0) {
      uVar5 = -iVar6;
      if ((int)-uVar4 < iVar6) {
        return (double)((long)dVar7 - ((ulong)uVar5 << 0x34));
      }
      if (iVar6 < (int)(-0x34 - uVar4)) {
        return dVar3;
      }
      uVar2 = 1 - (iVar6 + uVar4);
      if ((int)uVar5 < (int)uVar2) {
        uVar2 = uVar5;
      }
      uVar5 = 0;
      for (dVar3 = dVar7; ((ulong)dVar3 & 1) == 0;
          dVar3 = (double)((ulong)dVar3 >> 1 | 0x8000000000000000)) {
        uVar5 = uVar5 + 1;
      }
      uVar2 = uVar2 - 1 & 0x3f;
      auVar8._8_8_ = 0;
      auVar8._0_8_ = ~(ulong)(uVar5 == uVar2) &
                     (((ulong)(0 < (int)uVar4) << 0x34 | (ulong)dVar7 & 0xfffffffffffff) >> uVar2) +
                     1 >> 1;
      auVar8 = vpand_avx(auVar8,_DAT_01000240);
      auVar1._8_8_ = _UNK_010007e8;
      auVar1._0_8_ = _DAT_010007e0;
      auVar1 = vpand_avx(in_ZMM0._0_16_,auVar1);
      auVar8 = vpor_avx(auVar8,auVar1);
      return auVar8._0_8_;
    }
    if ((int)(0x7fe - uVar4) < iVar6) {
      return (double)((ulong)dVar7 & _DAT_010007e0 | DAT_01000b28);
    }
    uVar5 = uVar4 + iVar6;
    if (uVar5 == 0 || SCARRY4(uVar4,iVar6) != (int)uVar5 < 0) {
      return (double)((long)dVar7 << (param_1 & 0x3f) | (ulong)dVar3);
    }
    if ((int)uVar4 < 1) {
      return (double)((long)dVar7 << ((ulong)(byte)(1 - (char)uVar4) & 0x3f) & 0xfffffffffffffU |
                      (ulong)uVar5 << 0x34 | (ulong)dVar3);
    }
    dVar7 = (double)((param_1 << 0x34) + (long)dVar7);
  }
  return dVar7;
}


// ---- FUN_011f5c80 @ 011f5c80

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong FUN_011f5c80(double param_1,double *param_2)

{
  double dVar1;
  undefined1 auVar2 [16];
  double dVar3;
  double dVar4;
  double dVar5;
  uint uVar6;
  ulong uVar7;
  int iVar8;
  double dVar9;
  uint uVar10;
  double dVar11;
  undefined1 auVar12 [16];
  double dVar13;
  double dVar14;
  undefined1 local_40 [16];
  double local_30;
  double local_28;
  double local_20;
  
  dVar5 = DAT_010010a0;
  dVar4 = DAT_01001020;
  dVar3 = DAT_01000fa8;
  dVar14 = DAT_01000e80;
  dVar11 = DAT_01000ad8;
  dVar13 = DAT_01000a40;
  dVar1 = DAT_01000a38;
  dVar9 = DAT_01000a00;
  uVar6 = (uint)((ulong)param_1 >> 0x20);
  uVar10 = uVar6 & 0x7fffffff;
  if (uVar10 < 0x400f6a7b) {
    if ((uVar6 & 0xfffff) != 0x921fb) {
      if (0x4002d97c < uVar10) {
        if (-1 < (long)param_1) {
          param_1 = param_1 + DAT_010009a8;
          dVar9 = param_1 + DAT_010010a0;
          *param_2 = dVar9;
          param_2[1] = (param_1 - dVar9) + dVar5;
          return 2;
        }
        param_1 = param_1 + DAT_01000c18;
        dVar1 = param_1 + DAT_01000a00;
        *param_2 = dVar1;
        param_2[1] = (param_1 - dVar1) + dVar9;
        return 0xfffffffe;
      }
      if (-1 < (long)param_1) {
        param_1 = param_1 + DAT_01000c10;
        dVar9 = param_1 + DAT_01001020;
        *param_2 = dVar9;
        param_2[1] = (param_1 - dVar9) + dVar4;
        return 1;
      }
      param_1 = param_1 + DAT_01000df0;
      dVar9 = param_1 + DAT_01000a38;
      *param_2 = dVar9;
      param_2[1] = (param_1 - dVar9) + dVar1;
      return 0xffffffff;
    }
LAB_011f5d5f:
    dVar9 = param_1 * DAT_010010d8 + DAT_01000da0 + DAT_01000d58;
    uVar6 = (uint)dVar9;
    dVar1 = param_1 + dVar9 * DAT_01000c10;
    dVar13 = dVar9 * DAT_01000a38;
    if (DAT_01000e78 <= dVar1 - dVar13) {
      if (DAT_01000d60 < dVar1 - dVar13) {
        uVar6 = uVar6 + 1;
        dVar1 = DAT_01000bf8;
        goto LAB_011f5dc1;
      }
    }
    else {
      uVar6 = uVar6 - 1;
      dVar1 = DAT_010009f0;
LAB_011f5dc1:
      dVar9 = dVar9 + dVar1;
      dVar1 = param_1 + dVar9 * DAT_01000c10;
      dVar13 = dVar9 * DAT_01000a38;
    }
    uVar7 = (ulong)uVar6;
    dVar11 = dVar1 - dVar13;
    *param_2 = dVar11;
    dVar14 = dVar1;
    if ((int)((uVar10 >> 0x14) - ((uint)((ulong)dVar11 >> 0x34) & 0x7ff)) < 0x11) goto LAB_011f5fd9;
    dVar14 = dVar1 - dVar9 * DAT_01000de8;
    dVar13 = dVar9 * DAT_01000f00 - ((dVar1 - dVar14) - dVar9 * DAT_01000de8);
    dVar11 = dVar14 - dVar13;
    *param_2 = dVar11;
    if ((int)((uVar10 >> 0x14) - ((uint)((ulong)dVar11 >> 0x34) & 0x7ff)) < 0x32) goto LAB_011f5fd9;
  }
  else {
    if (0x401c463b < uVar10) {
      if (0x413921fa < uVar10) {
        if (0x7fefffff < uVar10) {
          *param_2 = param_1 - param_1;
          param_2[1] = param_1 - param_1;
          return 0;
        }
        dVar9 = (double)((ulong)param_1 & 0xfffffffffffff | 0x4160000000000000);
        auVar12 = vcvtdq2pd_avx(ZEXT416((uint)(int)dVar9));
        dVar9 = (dVar9 - auVar12._0_8_) * DAT_01001120;
        auVar2 = vcvtdq2pd_avx(ZEXT416((uint)(int)dVar9));
        local_40 = vpunpcklqdq_avx(auVar12,auVar2);
        local_30 = (dVar9 - auVar2._0_8_) * DAT_01001120;
        iVar8 = 4;
        do {
          uVar6 = iVar8 - 2;
          iVar8 = iVar8 + -1;
        } while (*(double *)(local_40 + (ulong)uVar6 * 8) == 0.0);
        uVar7 = FUN_011f4760(local_40,&local_28,(uVar10 >> 0x14) - 0x416,iVar8,1);
        auVar12._8_8_ = 0;
        auVar12._0_8_ = local_28;
        if (-1 < (long)param_1) {
          *param_2 = local_28;
          param_2[1] = local_20;
          return uVar7;
        }
        auVar12 = vmovhpd_avx(auVar12,local_20);
        dVar9 = (double)(auVar12._8_8_ ^ _UNK_010007e8);
        *param_2 = (double)(auVar12._0_8_ ^ _DAT_010007e0);
        param_2[1] = dVar9;
        return (ulong)(uint)-(int)uVar7;
      }
      goto LAB_011f5d5f;
    }
    if (uVar10 < 0x4015fdbd) {
      if (uVar10 != 0x4012d97c) {
        if (-1 < (long)param_1) {
          param_1 = param_1 + DAT_01001188;
          dVar9 = param_1 + DAT_01000ad8;
          *param_2 = dVar9;
          param_2[1] = (param_1 - dVar9) + dVar11;
          return 3;
        }
        param_1 = param_1 + DAT_01000fb0;
        dVar9 = param_1 + DAT_01000e80;
        *param_2 = dVar9;
        param_2[1] = (param_1 - dVar9) + dVar14;
        return 0xfffffffd;
      }
    }
    else if (uVar10 != 0x401921fb) {
      if (-1 < (long)param_1) {
        param_1 = param_1 + DAT_01000f08;
        dVar9 = param_1 + DAT_01000fa8;
        *param_2 = dVar9;
        param_2[1] = (param_1 - dVar9) + dVar3;
        return 4;
      }
      param_1 = param_1 + DAT_01000e40;
      dVar9 = param_1 + DAT_01000a40;
      *param_2 = dVar9;
      param_2[1] = (param_1 - dVar9) + dVar13;
      return 0xfffffffc;
    }
    dVar9 = param_1 * DAT_010010d8 + DAT_01000da0 + DAT_01000d58;
    uVar6 = (uint)dVar9;
    dVar1 = param_1 + dVar9 * DAT_01000c10;
    dVar13 = dVar9 * DAT_01000a38;
    if (DAT_01000e78 <= dVar1 - dVar13) {
      if (DAT_01000d60 < dVar1 - dVar13) {
        uVar6 = uVar6 + 1;
        dVar1 = DAT_01000bf8;
        goto LAB_011f5f65;
      }
    }
    else {
      uVar6 = uVar6 - 1;
      dVar1 = DAT_010009f0;
LAB_011f5f65:
      dVar9 = dVar9 + dVar1;
      dVar1 = param_1 + dVar9 * DAT_01000c10;
      dVar13 = dVar9 * DAT_01000a38;
    }
    uVar7 = (ulong)uVar6;
    dVar11 = dVar1 - dVar13;
    *param_2 = dVar11;
    dVar14 = dVar1;
    if (0x3f0 < ((uint)((ulong)dVar11 >> 0x34) & 0x7ff)) goto LAB_011f5fd9;
    dVar14 = dVar1 - dVar9 * DAT_01000de8;
    dVar13 = dVar9 * DAT_01000f00 - ((dVar1 - dVar14) - dVar9 * DAT_01000de8);
    dVar11 = dVar14 - dVar13;
    *param_2 = dVar11;
    if (0x3c < ((byte)((ulong)dVar11 >> 0x38) & 0x7f)) goto LAB_011f5fd9;
  }
  dVar1 = dVar14 - dVar9 * DAT_010009a0;
  dVar13 = dVar9 * DAT_01001180 - ((dVar14 - dVar1) - dVar9 * DAT_010009a0);
  dVar11 = dVar1 - dVar13;
  *param_2 = dVar11;
  dVar14 = dVar1;
LAB_011f5fd9:
  param_2[1] = (dVar14 - dVar11) - dVar13;
  return uVar7;
}


// ---- FUN_011f6180 @ 011f6180

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_011f6180(double *param_1,double *param_2)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  uint uVar5;
  double dVar6;
  undefined1 auVar7 [16];
  undefined1 in_ZMM0 [64];
  undefined1 auVar8 [16];
  double local_38;
  double local_30;
  
  dVar6 = in_ZMM0._0_8_;
  uVar5 = in_ZMM0._4_4_ & 0x7fffffff;
  if (uVar5 < 0x3fe921fc) {
    if (uVar5 < 0x3e46a09e) {
      *param_1 = dVar6;
      dVar6 = DAT_01000bf8;
    }
    else {
      dVar1 = dVar6 * dVar6;
      dVar2 = dVar1 * dVar1;
      *param_1 = dVar6 + dVar6 * dVar1 *
                         (dVar1 * (dVar1 * dVar2 * (dVar1 * DAT_01000c28 + DAT_01001028) +
                                  dVar1 * (dVar1 * DAT_01000da8 + DAT_01000c20) + DAT_01000b80) +
                         DAT_01000ab0);
      dVar3 = DAT_01000bf8 - dVar1 * DAT_01000ce0;
      dVar6 = dVar3 + ((DAT_01000bf8 - dVar3) - dVar1 * DAT_01000ce0) +
                      dVar1 * (dVar1 * (dVar1 * (dVar1 * DAT_01000bc0 + DAT_01000d30) + DAT_01000f10
                                       ) +
                              dVar2 * dVar2 *
                              (dVar1 * (dVar1 * DAT_01000ae0 + DAT_01000f60) + DAT_010010e0)) +
                      dVar6 * ram0x01000d28;
    }
  }
  else if (uVar5 < 0x7ff00000) {
    uVar5 = FUN_011f5c80(&local_38);
    dVar4 = ram0x01000d28;
    dVar1 = local_38 * local_38;
    dVar2 = dVar1 * dVar1;
    dVar3 = local_38 -
            (local_38 * dVar1 * DAT_01000e88 +
            (dVar1 * (local_30 * DAT_01000ce0 -
                     local_38 * dVar1 *
                     (dVar1 * dVar2 * (dVar1 * DAT_01000c28 + DAT_01001028) +
                     dVar1 * (dVar1 * DAT_01000da8 + DAT_01000c20) + DAT_01000b80)) - local_30));
    dVar6 = DAT_01000bf8 - dVar1 * DAT_01000ce0;
    dVar6 = dVar6 + ((DAT_01000bf8 - dVar6) - dVar1 * DAT_01000ce0) +
                    (dVar1 * (dVar1 * (dVar1 * (dVar1 * DAT_01000bc0 + DAT_01000d30) + DAT_01000f10)
                             + dVar2 * dVar2 *
                               (dVar1 * (dVar1 * DAT_01000ae0 + DAT_01000f60) + DAT_010010e0)) -
                    local_38 * local_30);
    switch(uVar5 & 3) {
    case 0:
      *param_1 = dVar3;
      break;
    case 1:
      *param_1 = dVar6;
      dVar6 = (double)((ulong)dVar3 ^ _DAT_010007e0);
      break;
    case 2:
      auVar8._0_8_ = (ulong)dVar3 ^ (ulong)ram0x01000d28;
      auVar8._8_8_ = ram0x01000d28;
      dVar1 = (double)vmovlpd_avx(auVar8);
      *param_1 = dVar1;
      dVar6 = (double)((ulong)dVar6 ^ (ulong)dVar4);
      break;
    case 3:
      auVar7._0_8_ = (ulong)dVar6 ^ _DAT_010007e0;
      auVar7._8_8_ = _UNK_010007e8;
      dVar6 = (double)vmovlpd_avx(auVar7);
      *param_1 = dVar6;
      dVar6 = dVar3;
    }
  }
  else {
    *param_1 = dVar6 - dVar6;
    dVar6 = dVar6 - dVar6;
  }
  *param_2 = dVar6;
  return;
}


// ---- FUN_011f6430 @ 011f6430

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

double FUN_011f6430(double param_1)

{
  double dVar1;
  double dVar2;
  double dVar3;
  uint uVar4;
  double local_28;
  double local_20;
  
  uVar4 = (uint)((ulong)param_1 >> 0x20) & 0x7fffffff;
  if (0x3fe921fb < uVar4) {
    if (0x7fefffff < uVar4) {
      return param_1 - param_1;
    }
    uVar4 = FUN_011f5c80(&local_28);
    dVar1 = local_28 * local_28;
    dVar2 = dVar1 * dVar1;
    switch(uVar4 & 3) {
    case 0:
      return local_28 -
             (local_28 * dVar1 * DAT_01000e88 +
             (dVar1 * (local_20 * DAT_01000ce0 -
                      local_28 * dVar1 *
                      (dVar1 * dVar2 * (dVar1 * DAT_01000c28 + DAT_01001028) +
                      dVar1 * (dVar1 * DAT_01000da8 + DAT_01000c20) + DAT_01000b80)) - local_20));
    case 1:
      dVar3 = DAT_01000bf8 - dVar1 * DAT_01000ce0;
      return dVar3 + ((DAT_01000bf8 - dVar3) - dVar1 * DAT_01000ce0) +
                     (dVar1 * (dVar1 * (dVar1 * (dVar1 * DAT_01000bc0 + DAT_01000d30) + DAT_01000f10
                                       ) +
                              dVar2 * dVar2 *
                              (dVar1 * (dVar1 * DAT_01000ae0 + DAT_01000f60) + DAT_010010e0)) -
                     local_28 * local_20);
    case 2:
      return (double)((ulong)(local_28 -
                             (local_28 * dVar1 * DAT_01000e88 +
                             (dVar1 * (local_20 * DAT_01000ce0 -
                                      local_28 * dVar1 *
                                      (dVar1 * dVar2 * (dVar1 * DAT_01000c28 + DAT_01001028) +
                                      dVar1 * (dVar1 * DAT_01000da8 + DAT_01000c20) + DAT_01000b80))
                             - local_20))) ^ _DAT_010007e0);
    case 3:
      dVar3 = DAT_01000bf8 - dVar1 * DAT_01000ce0;
      return (double)((ulong)(dVar3 + ((DAT_01000bf8 - dVar3) - dVar1 * DAT_01000ce0) +
                                      (dVar1 * (dVar1 * (dVar1 * (dVar1 * DAT_01000bc0 +
                                                                 DAT_01000d30) + DAT_01000f10) +
                                               dVar2 * dVar2 *
                                               (dVar1 * (dVar1 * DAT_01000ae0 + DAT_01000f60) +
                                               DAT_010010e0)) - local_28 * local_20)) ^
                     _DAT_010007e0);
    }
  }
  if (uVar4 < 0x3e500000) {
    if (uVar4 < 0x100000) {
      return param_1;
    }
    return param_1;
  }
  dVar1 = param_1 * param_1;
  return param_1 + param_1 * dVar1 *
                   (dVar1 * (dVar1 * dVar1 * dVar1 * (dVar1 * DAT_01000c28 + DAT_01001028) +
                            dVar1 * (dVar1 * DAT_01000da8 + DAT_01000c20) + DAT_01000b80) +
                   DAT_01000ab0);
}


// ---- FUN_011f6700 @ 011f6700

undefined1  [16]
FUN_011f6700(ulong param_1,ulong param_2,ulong param_3,ulong param_4,ulong *param_5)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  ulong uVar11;
  ulong uVar12;
  undefined8 uVar13;
  ulong uVar14;
  ulong uVar15;
  ulong uVar16;
  bool bVar17;
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  
  if (param_2 < param_4 || param_2 - param_4 < (ulong)(param_1 < param_3)) {
    if (param_5 != (ulong *)0x0) {
      *param_5 = param_1;
      param_5[1] = param_2;
    }
    uVar13 = 0;
  }
  else {
    if (param_4 == 0) {
      if (param_2 < param_3) {
        auVar2._8_8_ = 0;
        auVar2._0_8_ = param_3;
        auVar5._8_8_ = param_2;
        auVar5._0_8_ = param_1;
        uVar13 = SUB168(auVar5 / auVar2,0);
        uVar15 = SUB168(auVar5 % auVar2,0);
        uVar11 = 0;
      }
      else {
        if ((param_2 | param_3) >> 0x20 == 0) {
          uVar11 = (param_2 & 0xffffffff) / (param_3 & 0xffffffff);
          param_2 = (param_2 & 0xffffffff) % (param_3 & 0xffffffff);
        }
        else {
          uVar11 = param_2 / param_3;
          param_2 = param_2 % param_3;
        }
        auVar3._8_8_ = 0;
        auVar3._0_8_ = param_3;
        auVar6._8_8_ = param_2;
        auVar6._0_8_ = param_1;
        uVar13 = SUB168(auVar6 / auVar3,0);
        uVar15 = SUB168(auVar6 % auVar3,0);
      }
      if (param_5 != (ulong *)0x0) {
        *param_5 = uVar15;
        param_5[1] = 0;
        auVar20._8_8_ = uVar11;
        auVar20._0_8_ = uVar13;
        return auVar20;
      }
      goto LAB_011f671b;
    }
    uVar11 = LZCOUNT(param_4);
    if (uVar11 != 0) {
      uVar15 = (ulong)(byte)-(char)uVar11;
      auVar1._8_8_ = 0;
      auVar1._0_8_ = param_3 >> (uVar15 & 0x3f) | param_4 << (uVar11 & 0x3f);
      auVar4._8_8_ = param_2 >> (uVar15 & 0x3f);
      auVar4._0_8_ = param_1 >> (uVar15 & 0x3f) | param_2 << (uVar11 & 0x3f);
      uVar12 = SUB168(auVar4 / auVar1,0);
      auVar7._8_8_ = 0;
      auVar7._0_8_ = param_3;
      auVar9._8_8_ = 0;
      auVar9._0_8_ = uVar12;
      uVar11 = SUB168(auVar7 * auVar9,0);
      uVar16 = SUB168(auVar7 * auVar9,8);
      auVar8._8_8_ = 0;
      auVar8._0_8_ = param_4;
      auVar10._8_8_ = 0;
      auVar10._0_8_ = uVar12;
      uVar15 = SUB168(auVar8 * auVar10,0);
      uVar14 = uVar15 + uVar16;
      if (((CARRY8(uVar15,uVar16) || SUB168(auVar8 * auVar10,8) != 0) || (param_2 < uVar14)) ||
         ((uVar14 == param_2 && (param_1 < uVar11)))) {
        uVar12 = uVar12 - 1;
        bVar17 = uVar11 < param_3;
        uVar11 = uVar11 - param_3;
        uVar14 = uVar14 - (bVar17 + param_4);
      }
      if (param_5 != (ulong *)0x0) {
        *param_5 = param_1 - uVar11;
        param_5[1] = param_2 - (uVar14 + (param_1 < uVar11));
      }
      auVar19._8_8_ = 0;
      auVar19._0_8_ = uVar12;
      return auVar19;
    }
    uVar13 = 1;
    if (param_5 != (ulong *)0x0) {
      *param_5 = param_1 - param_3;
      param_5[1] = (param_2 - param_4) - (ulong)(param_1 < param_3);
    }
  }
  uVar11 = 0;
LAB_011f671b:
  auVar18._8_8_ = uVar11;
  auVar18._0_8_ = uVar13;
  return auVar18;
}


// ---- FUN_011f6850 @ 011f6850

undefined1  [16] FUN_011f6850(ulong param_1,ulong param_2,ulong param_3,ulong param_4)

{
  ulong uVar1;
  ulong uVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  
  uVar2 = (long)param_2 >> 0x3f;
  uVar1 = (long)param_4 >> 0x3f;
  auVar3 = FUN_011f6700((param_1 ^ uVar2) - uVar2,
                        ((param_2 ^ uVar2) - uVar2) - (ulong)((param_1 ^ uVar2) < uVar2),
                        (param_3 ^ uVar1) - uVar1,
                        ((param_4 ^ uVar1) - uVar1) - (ulong)((param_3 ^ uVar1) < uVar1),0);
  uVar2 = (long)(param_4 ^ param_2) >> 0x3f;
  uVar1 = auVar3._0_8_ ^ uVar2;
  auVar4._0_8_ = uVar1 - uVar2;
  auVar4._8_8_ = ((auVar3._8_8_ ^ uVar2) - uVar2) - (ulong)(uVar1 < uVar2);
  return auVar4;
}


