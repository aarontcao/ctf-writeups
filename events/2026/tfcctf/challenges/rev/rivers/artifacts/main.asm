
handout/rivers:     file format elf64-x86-64


Disassembly of section .text:

00000000004017a0 <.text+0x6a0>:
  4017a0:	f3 0f 1e fa          	endbr64
  4017a4:	41 57                	push   %r15
  4017a6:	41 56                	push   %r14
  4017a8:	41 55                	push   %r13
  4017aa:	41 54                	push   %r12
  4017ac:	55                   	push   %rbp
  4017ad:	53                   	push   %rbx
  4017ae:	31 db                	xor    %ebx,%ebx
  4017b0:	48 81 ec e8 03 00 00 	sub    $0x3e8,%rsp
  4017b7:	64 48 8b 2c 25 28 00 	mov    %fs:0x28,%rbp
  4017be:	00 00 
  4017c0:	48 89 ac 24 d8 03 00 	mov    %rbp,0x3d8(%rsp)
  4017c7:	00 
  4017c8:	48 8d ac 24 50 02 00 	lea    0x250(%rsp),%rbp
  4017cf:	00 
  4017d0:	4c 8d a4 24 d0 03 00 	lea    0x3d0(%rsp),%r12
  4017d7:	00 
  4017d8:	4c 89 e0             	mov    %r12,%rax
  4017db:	41 89 dc             	mov    %ebx,%r12d
  4017de:	49 89 c5             	mov    %rax,%r13
  4017e1:	48 89 6c 24 38       	mov    %rbp,0x38(%rsp)
  4017e6:	48 89 eb             	mov    %rbp,%rbx
  4017e9:	48 8b 0d 08 9f 0d 00 	mov    0xd9f08(%rip),%rcx        # 0x4db6f8
  4017f0:	ba 02 00 00 00       	mov    $0x2,%edx
  4017f5:	be 01 00 00 00       	mov    $0x1,%esi
  4017fa:	4c 89 ef             	mov    %r13,%rdi
  4017fd:	e8 ae be 02 00       	call   0x42d6b0
  401802:	48 83 f8 02          	cmp    $0x2,%rax
  401806:	0f 85 04 01 00 00    	jne    0x401910
  40180c:	0f b7 84 24 d0 03 00 	movzwl 0x3d0(%rsp),%eax
  401813:	00 
  401814:	66 3d 00 10          	cmp    $0x1000,%ax
  401818:	0f 87 f2 00 00 00    	ja     0x401910
  40181e:	0f b7 c8             	movzwl %ax,%ecx
  401821:	31 ff                	xor    %edi,%edi
  401823:	89 4c 24 20          	mov    %ecx,0x20(%rsp)
  401827:	66 85 c0             	test   %ax,%ax
  40182a:	0f 84 ba 10 00 00    	je     0x4028ea
  401830:	c7 44 24 10 00 00 00 	movl   $0x0,0x10(%rsp)
  401837:	00 
  401838:	45 31 f6             	xor    %r14d,%r14d
  40183b:	45 31 ff             	xor    %r15d,%r15d
  40183e:	48 89 7c 24 18       	mov    %rdi,0x18(%rsp)
  401843:	48 89 5c 24 28       	mov    %rbx,0x28(%rsp)
  401848:	48 89 6c 24 08       	mov    %rbp,0x8(%rsp)
  40184d:	48 8b 3d a4 9e 0d 00 	mov    0xd9ea4(%rip),%rdi        # 0x4db6f8
  401854:	e8 c7 c1 02 00       	call   0x42da20
  401859:	89 c3                	mov    %eax,%ebx
  40185b:	83 f8 ff             	cmp    $0xffffffff,%eax
  40185e:	74 4c                	je     0x4018ac
  401860:	48 8b 3d 91 9e 0d 00 	mov    0xd9e91(%rip),%rdi        # 0x4db6f8
  401867:	e8 b4 c1 02 00       	call   0x42da20
  40186c:	89 c5                	mov    %eax,%ebp
  40186e:	83 f8 ff             	cmp    $0xffffffff,%eax
  401871:	74 39                	je     0x4018ac
  401873:	48 8b 3d 7e 9e 0d 00 	mov    0xd9e7e(%rip),%rdi        # 0x4db6f8
  40187a:	e8 a1 c1 02 00       	call   0x42da20
  40187f:	83 f8 ff             	cmp    $0xffffffff,%eax
  401882:	89 44 24 30          	mov    %eax,0x30(%rsp)
  401886:	74 24                	je     0x4018ac
  401888:	48 8b 0d 69 9e 0d 00 	mov    0xd9e69(%rip),%rcx        # 0x4db6f8
  40188f:	ba 08 00 00 00       	mov    $0x8,%edx
  401894:	be 01 00 00 00       	mov    $0x1,%esi
  401899:	4c 89 ef             	mov    %r13,%rdi
  40189c:	e8 0f be 02 00       	call   0x42d6b0
  4018a1:	44 8b 4c 24 30       	mov    0x30(%rsp),%r9d
  4018a6:	48 83 f8 08          	cmp    $0x8,%rax
  4018aa:	74 69                	je     0x401915
  4018ac:	49 63 c6             	movslq %r14d,%rax
  4018af:	48 8b 6c 24 08       	mov    0x8(%rsp),%rbp
  4018b4:	44 89 e3             	mov    %r12d,%ebx
  4018b7:	85 c0                	test   %eax,%eax
  4018b9:	7e 26                	jle    0x4018e1
  4018bb:	4c 8d 2c 40          	lea    (%rax,%rax,2),%r13
  4018bf:	4d 8d 67 10          	lea    0x10(%r15),%r12
  4018c3:	49 c1 e5 04          	shl    $0x4,%r13
  4018c7:	4d 01 e5             	add    %r12,%r13
  4018ca:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  4018d0:	4c 89 e7             	mov    %r12,%rdi
  4018d3:	49 83 c4 30          	add    $0x30,%r12
  4018d7:	e8 24 26 00 00       	call   0x403f00
  4018dc:	4d 39 e5             	cmp    %r12,%r13
  4018df:	75 ef                	jne    0x4018d0
  4018e1:	4c 89 ff             	mov    %r15,%rdi
  4018e4:	e8 c7 7e 03 00       	call   0x4397b0
  4018e9:	45 31 e4             	xor    %r12d,%r12d
  4018ec:	44 39 e3             	cmp    %r12d,%ebx
  4018ef:	0f 8e 4f 09 00 00    	jle    0x402244
  4018f5:	4c 89 e7             	mov    %r12,%rdi
  4018f8:	49 83 c4 01          	add    $0x1,%r12
  4018fc:	48 c1 e7 04          	shl    $0x4,%rdi
  401900:	48 01 ef             	add    %rbp,%rdi
  401903:	e8 38 14 00 00       	call   0x402d40
  401908:	eb e2                	jmp    0x4018ec
  40190a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  401910:	44 89 e3             	mov    %r12d,%ebx
  401913:	eb d4                	jmp    0x4018e9
  401915:	f2 0f 10 84 24 d0 03 	movsd  0x3d0(%rsp),%xmm0
  40191c:	00 00 
  40191e:	f2 0f 10 15 ca d9 0a 	movsd  0xad9ca(%rip),%xmm2        # 0x4af2f0
  401925:	00 
  401926:	66 0f 28 c8          	movapd %xmm0,%xmm1
  40192a:	66 0f 54 0d ee d8 0a 	andpd  0xad8ee(%rip),%xmm1        # 0x4af220
  401931:	00 
  401932:	66 0f 2e d1          	ucomisd %xmm1,%xmm2
  401936:	0f 82 70 ff ff ff    	jb     0x4018ac
  40193c:	80 fb 3c             	cmp    $0x3c,%bl
  40193f:	0f 97 c0             	seta   %al
  401942:	40 80 fd 3c          	cmp    $0x3c,%bpl
  401946:	0f 97 c2             	seta   %dl
  401949:	08 d0                	or     %dl,%al
  40194b:	0f 85 f8 08 00 00    	jne    0x402249
  401951:	41 80 f9 3c          	cmp    $0x3c,%r9b
  401955:	0f 87 ee 08 00 00    	ja     0x402249
  40195b:	0f b6 f3             	movzbl %bl,%esi
  40195e:	40 0f b6 d5          	movzbl %bpl,%edx
  401962:	41 0f b6 c9          	movzbl %r9b,%ecx
  401966:	8d 04 32             	lea    (%rdx,%rsi,1),%eax
  401969:	01 c8                	add    %ecx,%eax
  40196b:	83 f8 78             	cmp    $0x78,%eax
  40196e:	0f 8f d5 08 00 00    	jg     0x402249
  401974:	48 8d 9c 24 40 03 00 	lea    0x340(%rsp),%rbx
  40197b:	00 
  40197c:	89 4c 24 48          	mov    %ecx,0x48(%rsp)
  401980:	48 89 df             	mov    %rbx,%rdi
  401983:	89 74 24 40          	mov    %esi,0x40(%rsp)
  401987:	89 54 24 30          	mov    %edx,0x30(%rsp)
  40198b:	f2 0f 11 44 24 50    	movsd  %xmm0,0x50(%rsp)
  401991:	e8 ba 26 00 00       	call   0x404050
  401996:	f2 0f 10 44 24 50    	movsd  0x50(%rsp),%xmm0
  40199c:	48 89 df             	mov    %rbx,%rdi
  40199f:	e8 cc 2e 00 00       	call   0x404870
  4019a4:	8b 4c 24 48          	mov    0x48(%rsp),%ecx
  4019a8:	8b 54 24 30          	mov    0x30(%rsp),%edx
  4019ac:	49 89 d8             	mov    %rbx,%r8
  4019af:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  4019b4:	8b 74 24 40          	mov    0x40(%rsp),%esi
  4019b8:	48 8d bc 24 80 01 00 	lea    0x180(%rsp),%rdi
  4019bf:	00 
  4019c0:	4c 89 bc 24 80 01 00 	mov    %r15,0x180(%rsp)
  4019c7:	00 
  4019c8:	48 89 84 24 88 01 00 	mov    %rax,0x188(%rsp)
  4019cf:	00 
  4019d0:	e8 cb 11 00 00       	call   0x402ba0
  4019d5:	48 8b 84 24 88 01 00 	mov    0x188(%rsp),%rax
  4019dc:	00 
  4019dd:	48 89 df             	mov    %rbx,%rdi
  4019e0:	4c 8b bc 24 80 01 00 	mov    0x180(%rsp),%r15
  4019e7:	00 
  4019e8:	44 8b b4 24 88 01 00 	mov    0x188(%rsp),%r14d
  4019ef:	00 
  4019f0:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
  4019f5:	e8 06 25 00 00       	call   0x403f00
  4019fa:	83 44 24 10 01       	addl   $0x1,0x10(%rsp)
  4019ff:	8b 4c 24 20          	mov    0x20(%rsp),%ecx
  401a03:	8b 44 24 10          	mov    0x10(%rsp),%eax
  401a07:	39 c8                	cmp    %ecx,%eax
  401a09:	0f 85 3e fe ff ff    	jne    0x40184d
  401a0f:	48 8b 7c 24 18       	mov    0x18(%rsp),%rdi
  401a14:	48 8b 5c 24 28       	mov    0x28(%rsp),%rbx
  401a19:	48 8b 6c 24 08       	mov    0x8(%rsp),%rbp
  401a1e:	41 83 c4 01          	add    $0x1,%r12d
  401a22:	4c 89 3b             	mov    %r15,(%rbx)
  401a25:	48 83 c3 10          	add    $0x10,%rbx
  401a29:	48 89 7b f8          	mov    %rdi,-0x8(%rbx)
  401a2d:	41 83 fc 03          	cmp    $0x3,%r12d
  401a31:	0f 85 b2 fd ff ff    	jne    0x4017e9
  401a37:	4c 8b 74 24 38       	mov    0x38(%rsp),%r14
  401a3c:	4c 8d ac 24 40 03 00 	lea    0x340(%rsp),%r13
  401a43:	00 
  401a44:	48 8d 84 24 80 02 00 	lea    0x280(%rsp),%rax
  401a4b:	00 
  401a4c:	48 c7 44 24 48 00 00 	movq   $0x0,0x48(%rsp)
  401a53:	00 00 
  401a55:	4c 8d a4 24 e0 02 00 	lea    0x2e0(%rsp),%r12
  401a5c:	00 
  401a5d:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  401a62:	4c 89 64 24 70       	mov    %r12,0x70(%rsp)
  401a67:	4c 89 74 24 78       	mov    %r14,0x78(%rsp)
  401a6c:	4c 89 ac 24 80 00 00 	mov    %r13,0x80(%rsp)
  401a73:	00 
  401a74:	48 89 6c 24 68       	mov    %rbp,0x68(%rsp)
  401a79:	48 89 ac 24 88 00 00 	mov    %rbp,0x88(%rsp)
  401a80:	00 
  401a81:	4c 89 ed             	mov    %r13,%rbp
  401a84:	48 8b 44 24 68       	mov    0x68(%rsp),%rax
  401a89:	48 8b 7c 24 08       	mov    0x8(%rsp),%rdi
  401a8e:	8b 58 08             	mov    0x8(%rax),%ebx
  401a91:	4c 8b 28             	mov    (%rax),%r13
  401a94:	89 5c 24 40          	mov    %ebx,0x40(%rsp)
  401a98:	e8 b3 25 00 00       	call   0x404050
  401a9d:	4c 89 e7             	mov    %r12,%rdi
  401aa0:	e8 ab 25 00 00       	call   0x404050
  401aa5:	85 db                	test   %ebx,%ebx
  401aa7:	0f 8e ab 0d 00 00    	jle    0x402858
  401aad:	4c 63 74 24 40       	movslq 0x40(%rsp),%r14
  401ab2:	49 8d 45 10          	lea    0x10(%r13),%rax
  401ab6:	48 89 6c 24 38       	mov    %rbp,0x38(%rsp)
  401abb:	31 db                	xor    %ebx,%ebx
  401abd:	49 89 c5             	mov    %rax,%r13
  401ac0:	48 89 44 24 50       	mov    %rax,0x50(%rsp)
  401ac5:	4f 8d 3c 76          	lea    (%r14,%r14,2),%r15
  401ac9:	4c 89 74 24 58       	mov    %r14,0x58(%rsp)
  401ace:	41 89 de             	mov    %ebx,%r14d
  401ad1:	49 c1 e7 04          	shl    $0x4,%r15
  401ad5:	4c 89 64 24 10       	mov    %r12,0x10(%rsp)
  401ada:	4d 89 ec             	mov    %r13,%r12
  401add:	4c 01 f8             	add    %r15,%rax
  401ae0:	45 31 ff             	xor    %r15d,%r15d
  401ae3:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
  401ae8:	31 c0                	xor    %eax,%eax
  401aea:	49 89 c5             	mov    %rax,%r13
  401aed:	0f 1f 00             	nopl   (%rax)
  401af0:	41 8b 44 24 f0       	mov    -0x10(%r12),%eax
  401af5:	85 c0                	test   %eax,%eax
  401af7:	0f 84 b3 00 00 00    	je     0x401bb0
  401afd:	48 8b 7c 24 10       	mov    0x10(%rsp),%rdi
  401b02:	48 63 f0             	movslq %eax,%rsi
  401b05:	ba 01 00 00 00       	mov    $0x1,%edx
  401b0a:	89 44 24 20          	mov    %eax,0x20(%rsp)
  401b0e:	41 8b 6c 24 f4       	mov    -0xc(%r12),%ebp
  401b13:	41 8b 5c 24 f8       	mov    -0x8(%r12),%ebx
  401b18:	e8 23 2b 00 00       	call   0x404640
  401b1d:	48 8b 54 24 10       	mov    0x10(%rsp),%rdx
  401b22:	48 8b 7c 24 08       	mov    0x8(%rsp),%rdi
  401b27:	4c 89 e6             	mov    %r12,%rsi
  401b2a:	e8 11 26 00 00       	call   0x404140
  401b2f:	8b 44 24 20          	mov    0x20(%rsp),%eax
  401b33:	8d 50 ff             	lea    -0x1(%rax),%edx
  401b36:	45 85 ff             	test   %r15d,%r15d
  401b39:	0f 8e 99 08 00 00    	jle    0x4023d8
  401b3f:	49 63 f7             	movslq %r15d,%rsi
  401b42:	4c 89 e8             	mov    %r13,%rax
  401b45:	4c 8d 1c 76          	lea    (%rsi,%rsi,2),%r11
  401b49:	49 c1 e3 04          	shl    $0x4,%r11
  401b4d:	4d 01 eb             	add    %r13,%r11
  401b50:	eb 1b                	jmp    0x401b6d
  401b52:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  401b59:	00 00 00 00 
  401b5d:	0f 1f 00             	nopl   (%rax)
  401b60:	48 83 c0 30          	add    $0x30,%rax
  401b64:	4c 39 d8             	cmp    %r11,%rax
  401b67:	0f 84 6b 08 00 00    	je     0x4023d8
  401b6d:	3b 10                	cmp    (%rax),%edx
  401b6f:	75 ef                	jne    0x401b60
  401b71:	3b 68 04             	cmp    0x4(%rax),%ebp
  401b74:	75 ea                	jne    0x401b60
  401b76:	3b 58 08             	cmp    0x8(%rax),%ebx
  401b79:	75 e5                	jne    0x401b60
  401b7b:	48 8d 58 10          	lea    0x10(%rax),%rbx
  401b7f:	48 8b 54 24 08       	mov    0x8(%rsp),%rdx
  401b84:	48 89 44 24 20       	mov    %rax,0x20(%rsp)
  401b89:	48 89 de             	mov    %rbx,%rsi
  401b8c:	48 89 df             	mov    %rbx,%rdi
  401b8f:	4c 89 5c 24 28       	mov    %r11,0x28(%rsp)
  401b94:	e8 47 23 00 00       	call   0x403ee0
  401b99:	48 8b 44 24 20       	mov    0x20(%rsp),%rax
  401b9e:	8b 40 14             	mov    0x14(%rax),%eax
  401ba1:	85 c0                	test   %eax,%eax
  401ba3:	0f 84 6b 09 00 00    	je     0x402514
  401ba9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  401bb0:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  401bb5:	49 83 c4 30          	add    $0x30,%r12
  401bb9:	49 39 c4             	cmp    %rax,%r12
  401bbc:	0f 85 2e ff ff ff    	jne    0x401af0
  401bc2:	4c 89 6c 24 18       	mov    %r13,0x18(%rsp)
  401bc7:	44 89 f3             	mov    %r14d,%ebx
  401bca:	48 8b 6c 24 38       	mov    0x38(%rsp),%rbp
  401bcf:	4c 8b 74 24 58       	mov    0x58(%rsp),%r14
  401bd4:	4c 8b 64 24 10       	mov    0x10(%rsp),%r12
  401bd9:	48 8b 7c 24 08       	mov    0x8(%rsp),%rdi
  401bde:	e8 1d 23 00 00       	call   0x403f00
  401be3:	4c 89 e7             	mov    %r12,%rdi
  401be6:	e8 15 23 00 00       	call   0x403f00
  401beb:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  401bf0:	44 89 7d 08          	mov    %r15d,0x8(%rbp)
  401bf4:	4f 8d 3c 76          	lea    (%r14,%r14,2),%r15
  401bf8:	49 c1 e7 04          	shl    $0x4,%r15
  401bfc:	c7 44 24 18 01 00 00 	movl   $0x1,0x18(%rsp)
  401c03:	00 
  401c04:	48 89 45 00          	mov    %rax,0x0(%rbp)
  401c08:	48 8b 44 24 50       	mov    0x50(%rsp),%rax
  401c0d:	4c 89 64 24 10       	mov    %r12,0x10(%rsp)
  401c12:	4c 01 f8             	add    %r15,%rax
  401c15:	89 5d 0c             	mov    %ebx,0xc(%rbp)
  401c18:	48 89 eb             	mov    %rbp,%rbx
  401c1b:	48 89 44 24 28       	mov    %rax,0x28(%rsp)
  401c20:	48 8b 7c 24 08       	mov    0x8(%rsp),%rdi
  401c25:	e8 26 24 00 00       	call   0x404050
  401c2a:	48 8b 7c 24 10       	mov    0x10(%rsp),%rdi
  401c2f:	e8 1c 24 00 00       	call   0x404050
  401c34:	8b 44 24 40          	mov    0x40(%rsp),%eax
  401c38:	85 c0                	test   %eax,%eax
  401c3a:	0f 8e c6 08 00 00    	jle    0x402506
  401c40:	49 89 dc             	mov    %rbx,%r12
  401c43:	4c 8b 74 24 50       	mov    0x50(%rsp),%r14
  401c48:	4c 89 64 24 58       	mov    %r12,0x58(%rsp)
  401c4d:	45 31 ff             	xor    %r15d,%r15d
  401c50:	48 c7 44 24 20 00 00 	movq   $0x0,0x20(%rsp)
  401c57:	00 00 
  401c59:	48 89 6c 24 60       	mov    %rbp,0x60(%rsp)
  401c5e:	4c 89 f3             	mov    %r14,%rbx
  401c61:	44 89 fd             	mov    %r15d,%ebp
  401c64:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  401c6b:	00 00 00 00 
  401c6f:	90                   	nop
  401c70:	83 7c 24 18 01       	cmpl   $0x1,0x18(%rsp)
  401c75:	0f 84 25 06 00 00    	je     0x4022a0
  401c7b:	44 8b 63 f8          	mov    -0x8(%rbx),%r12d
  401c7f:	45 85 e4             	test   %r12d,%r12d
  401c82:	0f 84 a8 00 00 00    	je     0x401d30
  401c88:	49 63 f4             	movslq %r12d,%rsi
  401c8b:	ba 01 00 00 00       	mov    $0x1,%edx
  401c90:	44 8b 6b f0          	mov    -0x10(%rbx),%r13d
  401c94:	44 8b 73 f4          	mov    -0xc(%rbx),%r14d
  401c98:	48 8b 7c 24 10       	mov    0x10(%rsp),%rdi
  401c9d:	e8 9e 29 00 00       	call   0x404640
  401ca2:	48 8b 54 24 10       	mov    0x10(%rsp),%rdx
  401ca7:	48 8b 7c 24 08       	mov    0x8(%rsp),%rdi
  401cac:	48 89 de             	mov    %rbx,%rsi
  401caf:	e8 8c 24 00 00       	call   0x404140
  401cb4:	41 8d 4c 24 ff       	lea    -0x1(%r12),%ecx
  401cb9:	85 ed                	test   %ebp,%ebp
  401cbb:	0f 8e 5f 06 00 00    	jle    0x402320
  401cc1:	48 63 c5             	movslq %ebp,%rax
  401cc4:	48 8b 74 24 20       	mov    0x20(%rsp),%rsi
  401cc9:	48 8d 04 40          	lea    (%rax,%rax,2),%rax
  401ccd:	48 c1 e0 04          	shl    $0x4,%rax
  401cd1:	49 89 f4             	mov    %rsi,%r12
  401cd4:	48 01 f0             	add    %rsi,%rax
  401cd7:	eb 14                	jmp    0x401ced
  401cd9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  401ce0:	49 83 c4 30          	add    $0x30,%r12
  401ce4:	49 39 c4             	cmp    %rax,%r12
  401ce7:	0f 84 33 06 00 00    	je     0x402320
  401ced:	45 39 2c 24          	cmp    %r13d,(%r12)
  401cf1:	75 ed                	jne    0x401ce0
  401cf3:	45 39 74 24 04       	cmp    %r14d,0x4(%r12)
  401cf8:	75 e6                	jne    0x401ce0
  401cfa:	41 39 4c 24 08       	cmp    %ecx,0x8(%r12)
  401cff:	75 df                	jne    0x401ce0
  401d01:	4d 8d 6c 24 10       	lea    0x10(%r12),%r13
  401d06:	48 8b 54 24 08       	mov    0x8(%rsp),%rdx
  401d0b:	48 89 44 24 30       	mov    %rax,0x30(%rsp)
  401d10:	4c 89 ee             	mov    %r13,%rsi
  401d13:	4c 89 ef             	mov    %r13,%rdi
  401d16:	e8 c5 21 00 00       	call   0x403ee0
  401d1b:	41 8b 44 24 14       	mov    0x14(%r12),%eax
  401d20:	85 c0                	test   %eax,%eax
  401d22:	0f 84 bb 07 00 00    	je     0x4024e3
  401d28:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  401d2f:	00 
  401d30:	48 8b 44 24 28       	mov    0x28(%rsp),%rax
  401d35:	48 83 c3 30          	add    $0x30,%rbx
  401d39:	48 39 c3             	cmp    %rax,%rbx
  401d3c:	0f 85 2e ff ff ff    	jne    0x401c70
  401d42:	41 89 ed             	mov    %ebp,%r13d
  401d45:	48 8b 5c 24 58       	mov    0x58(%rsp),%rbx
  401d4a:	4c 8b 74 24 20       	mov    0x20(%rsp),%r14
  401d4f:	48 8b 6c 24 60       	mov    0x60(%rsp),%rbp
  401d54:	48 8b 7c 24 08       	mov    0x8(%rsp),%rdi
  401d59:	48 83 c3 10          	add    $0x10,%rbx
  401d5d:	e8 9e 21 00 00       	call   0x403f00
  401d62:	4c 8b 64 24 10       	mov    0x10(%rsp),%r12
  401d67:	4c 89 e7             	mov    %r12,%rdi
  401d6a:	e8 91 21 00 00       	call   0x403f00
  401d6f:	4c 89 33             	mov    %r14,(%rbx)
  401d72:	44 89 6b 08          	mov    %r13d,0x8(%rbx)
  401d76:	44 89 7b 0c          	mov    %r15d,0xc(%rbx)
  401d7a:	83 7c 24 18 02       	cmpl   $0x2,0x18(%rsp)
  401d7f:	0f 85 51 07 00 00    	jne    0x4024d6
  401d85:	48 83 44 24 48 03    	addq   $0x3,0x48(%rsp)
  401d8b:	48 8b 44 24 48       	mov    0x48(%rsp),%rax
  401d90:	48 83 c5 30          	add    $0x30,%rbp
  401d94:	48 83 44 24 68 10    	addq   $0x10,0x68(%rsp)
  401d9a:	48 83 f8 09          	cmp    $0x9,%rax
  401d9e:	0f 85 e0 fc ff ff    	jne    0x401a84
  401da4:	44 8b 8c 24 c8 03 00 	mov    0x3c8(%rsp),%r9d
  401dab:	00 
  401dac:	4c 8b bc 24 c0 03 00 	mov    0x3c0(%rsp),%r15
  401db3:	00 
  401db4:	48 8d 9c 24 9c 00 00 	lea    0x9c(%rsp),%rbx
  401dbb:	00 
  401dbc:	c7 84 24 9c 00 00 00 	movl   $0x0,0x9c(%rsp)
  401dc3:	00 00 00 00 
  401dc7:	48 8b 84 24 80 03 00 	mov    0x380(%rsp),%rax
  401dce:	00 
  401dcf:	49 89 d8             	mov    %rbx,%r8
  401dd2:	8b b4 24 88 03 00 00 	mov    0x388(%rsp),%esi
  401dd9:	44 89 c9             	mov    %r9d,%ecx
  401ddc:	4c 89 fa             	mov    %r15,%rdx
  401ddf:	44 89 4c 24 10       	mov    %r9d,0x10(%rsp)
  401de4:	4c 8b 74 24 78       	mov    0x78(%rsp),%r14
  401de9:	48 89 c7             	mov    %rax,%rdi
  401dec:	4c 8b ac 24 80 00 00 	mov    0x80(%rsp),%r13
  401df3:	00 
  401df4:	89 74 24 30          	mov    %esi,0x30(%rsp)
  401df8:	48 8b ac 24 88 00 00 	mov    0x88(%rsp),%rbp
  401dff:	00 
  401e00:	48 89 44 24 28       	mov    %rax,0x28(%rsp)
  401e05:	e8 e6 11 00 00       	call   0x402ff0
  401e0a:	4c 8b 94 24 90 03 00 	mov    0x390(%rsp),%r10
  401e11:	00 
  401e12:	44 8b 9c 24 b8 03 00 	mov    0x3b8(%rsp),%r11d
  401e19:	00 
  401e1a:	49 89 d8             	mov    %rbx,%r8
  401e1d:	44 8b a4 24 98 03 00 	mov    0x398(%rsp),%r12d
  401e24:	00 
  401e25:	48 89 94 24 a8 00 00 	mov    %rdx,0xa8(%rsp)
  401e2c:	00 
  401e2d:	48 8b 94 24 b0 03 00 	mov    0x3b0(%rsp),%rdx
  401e34:	00 
  401e35:	44 89 d9             	mov    %r11d,%ecx
  401e38:	4c 89 d7             	mov    %r10,%rdi
  401e3b:	44 89 5c 24 48       	mov    %r11d,0x48(%rsp)
  401e40:	44 89 e6             	mov    %r12d,%esi
  401e43:	4c 89 54 24 40       	mov    %r10,0x40(%rsp)
  401e48:	48 89 84 24 a0 00 00 	mov    %rax,0xa0(%rsp)
  401e4f:	00 
  401e50:	48 89 54 24 20       	mov    %rdx,0x20(%rsp)
  401e55:	e8 96 11 00 00       	call   0x402ff0
  401e5a:	8b b4 24 a8 00 00 00 	mov    0xa8(%rsp),%esi
  401e61:	48 8b bc 24 a0 00 00 	mov    0xa0(%rsp),%rdi
  401e68:	00 
  401e69:	48 89 94 24 b8 00 00 	mov    %rdx,0xb8(%rsp)
  401e70:	00 
  401e71:	8b 8c 24 b8 00 00 00 	mov    0xb8(%rsp),%ecx
  401e78:	48 89 84 24 b0 00 00 	mov    %rax,0xb0(%rsp)
  401e7f:	00 
  401e80:	48 8b 94 24 b0 00 00 	mov    0xb0(%rsp),%rdx
  401e87:	00 
  401e88:	e8 33 18 00 00       	call   0x4036c0
  401e8d:	48 8d bc 24 a0 00 00 	lea    0xa0(%rsp),%rdi
  401e94:	00 
  401e95:	48 89 84 24 c0 00 00 	mov    %rax,0xc0(%rsp)
  401e9c:	00 
  401e9d:	48 89 94 24 c8 00 00 	mov    %rdx,0xc8(%rsp)
  401ea4:	00 
  401ea5:	e8 96 0e 00 00       	call   0x402d40
  401eaa:	48 8d bc 24 b0 00 00 	lea    0xb0(%rsp),%rdi
  401eb1:	00 
  401eb2:	e8 89 0e 00 00       	call   0x402d40
  401eb7:	8b 8c 24 c8 00 00 00 	mov    0xc8(%rsp),%ecx
  401ebe:	49 89 d8             	mov    %rbx,%r8
  401ec1:	8b b4 24 48 03 00 00 	mov    0x348(%rsp),%esi
  401ec8:	48 8b bc 24 40 03 00 	mov    0x340(%rsp),%rdi
  401ecf:	00 
  401ed0:	48 8b 94 24 c0 00 00 	mov    0xc0(%rsp),%rdx
  401ed7:	00 
  401ed8:	e8 13 11 00 00       	call   0x402ff0
  401edd:	48 8d bc 24 c0 00 00 	lea    0xc0(%rsp),%rdi
  401ee4:	00 
  401ee5:	48 89 84 24 d0 00 00 	mov    %rax,0xd0(%rsp)
  401eec:	00 
  401eed:	48 89 94 24 d8 00 00 	mov    %rdx,0xd8(%rsp)
  401ef4:	00 
  401ef5:	e8 46 0e 00 00       	call   0x402d40
  401efa:	8b 4c 24 10          	mov    0x10(%rsp),%ecx
  401efe:	49 89 d8             	mov    %rbx,%r8
  401f01:	4c 89 fa             	mov    %r15,%rdx
  401f04:	4c 8b 94 24 70 03 00 	mov    0x370(%rsp),%r10
  401f0b:	00 
  401f0c:	44 8b 9c 24 78 03 00 	mov    0x378(%rsp),%r11d
  401f13:	00 
  401f14:	4c 89 d7             	mov    %r10,%rdi
  401f17:	44 89 de             	mov    %r11d,%esi
  401f1a:	44 89 5c 24 18       	mov    %r11d,0x18(%rsp)
  401f1f:	4c 89 54 24 10       	mov    %r10,0x10(%rsp)
  401f24:	e8 c7 10 00 00       	call   0x402ff0
  401f29:	48 8b 7c 24 40       	mov    0x40(%rsp),%rdi
  401f2e:	49 89 d8             	mov    %rbx,%r8
  401f31:	44 89 e6             	mov    %r12d,%esi
  401f34:	4c 8b 8c 24 a0 03 00 	mov    0x3a0(%rsp),%r9
  401f3b:	00 
  401f3c:	44 8b bc 24 a8 03 00 	mov    0x3a8(%rsp),%r15d
  401f43:	00 
  401f44:	4d 8d 65 30          	lea    0x30(%r13),%r12
  401f48:	48 89 94 24 e8 00 00 	mov    %rdx,0xe8(%rsp)
  401f4f:	00 
  401f50:	48 89 84 24 e0 00 00 	mov    %rax,0xe0(%rsp)
  401f57:	00 
  401f58:	45 31 ed             	xor    %r13d,%r13d
  401f5b:	4c 89 ca             	mov    %r9,%rdx
  401f5e:	44 89 f9             	mov    %r15d,%ecx
  401f61:	4c 89 4c 24 38       	mov    %r9,0x38(%rsp)
  401f66:	e8 85 10 00 00       	call   0x402ff0
  401f6b:	8b b4 24 e8 00 00 00 	mov    0xe8(%rsp),%esi
  401f72:	48 8b bc 24 e0 00 00 	mov    0xe0(%rsp),%rdi
  401f79:	00 
  401f7a:	48 89 94 24 f8 00 00 	mov    %rdx,0xf8(%rsp)
  401f81:	00 
  401f82:	8b 8c 24 f8 00 00 00 	mov    0xf8(%rsp),%ecx
  401f89:	48 89 84 24 f0 00 00 	mov    %rax,0xf0(%rsp)
  401f90:	00 
  401f91:	48 8b 94 24 f0 00 00 	mov    0xf0(%rsp),%rdx
  401f98:	00 
  401f99:	e8 22 17 00 00       	call   0x4036c0
  401f9e:	48 8d bc 24 e0 00 00 	lea    0xe0(%rsp),%rdi
  401fa5:	00 
  401fa6:	48 89 84 24 00 01 00 	mov    %rax,0x100(%rsp)
  401fad:	00 
  401fae:	48 89 94 24 08 01 00 	mov    %rdx,0x108(%rsp)
  401fb5:	00 
  401fb6:	e8 85 0d 00 00       	call   0x402d40
  401fbb:	48 8d bc 24 f0 00 00 	lea    0xf0(%rsp),%rdi
  401fc2:	00 
  401fc3:	e8 78 0d 00 00       	call   0x402d40
  401fc8:	8b 8c 24 08 01 00 00 	mov    0x108(%rsp),%ecx
  401fcf:	49 89 d8             	mov    %rbx,%r8
  401fd2:	8b b4 24 58 03 00 00 	mov    0x358(%rsp),%esi
  401fd9:	48 8b bc 24 50 03 00 	mov    0x350(%rsp),%rdi
  401fe0:	00 
  401fe1:	48 8b 94 24 00 01 00 	mov    0x100(%rsp),%rdx
  401fe8:	00 
  401fe9:	e8 02 10 00 00       	call   0x402ff0
  401fee:	48 8d bc 24 00 01 00 	lea    0x100(%rsp),%rdi
  401ff5:	00 
  401ff6:	48 89 84 24 10 01 00 	mov    %rax,0x110(%rsp)
  401ffd:	00 
  401ffe:	48 89 94 24 18 01 00 	mov    %rdx,0x118(%rsp)
  402005:	00 
  402006:	e8 35 0d 00 00       	call   0x402d40
  40200b:	8b 4c 24 48          	mov    0x48(%rsp),%ecx
  40200f:	8b 74 24 18          	mov    0x18(%rsp),%esi
  402013:	49 89 d8             	mov    %rbx,%r8
  402016:	48 8b 7c 24 10       	mov    0x10(%rsp),%rdi
  40201b:	48 8b 54 24 20       	mov    0x20(%rsp),%rdx
  402020:	e8 cb 0f 00 00       	call   0x402ff0
  402025:	8b 74 24 30          	mov    0x30(%rsp),%esi
  402029:	49 89 d8             	mov    %rbx,%r8
  40202c:	44 89 f9             	mov    %r15d,%ecx
  40202f:	48 89 94 24 28 01 00 	mov    %rdx,0x128(%rsp)
  402036:	00 
  402037:	48 8b 7c 24 28       	mov    0x28(%rsp),%rdi
  40203c:	48 8b 54 24 38       	mov    0x38(%rsp),%rdx
  402041:	48 89 84 24 20 01 00 	mov    %rax,0x120(%rsp)
  402048:	00 
  402049:	e8 a2 0f 00 00       	call   0x402ff0
  40204e:	8b b4 24 28 01 00 00 	mov    0x128(%rsp),%esi
  402055:	48 8b bc 24 20 01 00 	mov    0x120(%rsp),%rdi
  40205c:	00 
  40205d:	48 89 94 24 38 01 00 	mov    %rdx,0x138(%rsp)
  402064:	00 
  402065:	8b 8c 24 38 01 00 00 	mov    0x138(%rsp),%ecx
  40206c:	48 89 84 24 30 01 00 	mov    %rax,0x130(%rsp)
  402073:	00 
  402074:	48 8b 94 24 30 01 00 	mov    0x130(%rsp),%rdx
  40207b:	00 
  40207c:	e8 3f 16 00 00       	call   0x4036c0
  402081:	48 8d bc 24 20 01 00 	lea    0x120(%rsp),%rdi
  402088:	00 
  402089:	48 89 84 24 40 01 00 	mov    %rax,0x140(%rsp)
  402090:	00 
  402091:	48 89 94 24 48 01 00 	mov    %rdx,0x148(%rsp)
  402098:	00 
  402099:	e8 a2 0c 00 00       	call   0x402d40
  40209e:	48 8d bc 24 30 01 00 	lea    0x130(%rsp),%rdi
  4020a5:	00 
  4020a6:	e8 95 0c 00 00       	call   0x402d40
  4020ab:	8b 8c 24 48 01 00 00 	mov    0x148(%rsp),%ecx
  4020b2:	49 89 d8             	mov    %rbx,%r8
  4020b5:	8b b4 24 68 03 00 00 	mov    0x368(%rsp),%esi
  4020bc:	48 8b bc 24 60 03 00 	mov    0x360(%rsp),%rdi
  4020c3:	00 
  4020c4:	48 8b 94 24 40 01 00 	mov    0x140(%rsp),%rdx
  4020cb:	00 
  4020cc:	e8 1f 0f 00 00       	call   0x402ff0
  4020d1:	48 8d bc 24 40 01 00 	lea    0x140(%rsp),%rdi
  4020d8:	00 
  4020d9:	48 89 84 24 50 01 00 	mov    %rax,0x150(%rsp)
  4020e0:	00 
  4020e1:	48 89 94 24 58 01 00 	mov    %rdx,0x158(%rsp)
  4020e8:	00 
  4020e9:	e8 52 0c 00 00       	call   0x402d40
  4020ee:	48 89 6c 24 10       	mov    %rbp,0x10(%rsp)
  4020f3:	49 8d 5c 24 d0       	lea    -0x30(%r12),%rbx
  4020f8:	48 63 43 08          	movslq 0x8(%rbx),%rax
  4020fc:	85 c0                	test   %eax,%eax
  4020fe:	7e 28                	jle    0x402128
  402100:	4c 8d 3c 40          	lea    (%rax,%rax,2),%r15
  402104:	31 ed                	xor    %ebp,%ebp
  402106:	49 c1 e7 04          	shl    $0x4,%r15
  40210a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  402110:	48 8b 3b             	mov    (%rbx),%rdi
  402113:	48 01 ef             	add    %rbp,%rdi
  402116:	48 83 c5 30          	add    $0x30,%rbp
  40211a:	48 83 c7 10          	add    $0x10,%rdi
  40211e:	e8 dd 1d 00 00       	call   0x403f00
  402123:	4c 39 fd             	cmp    %r15,%rbp
  402126:	75 e8                	jne    0x402110
  402128:	48 8b 3b             	mov    (%rbx),%rdi
  40212b:	48 83 c3 10          	add    $0x10,%rbx
  40212f:	e8 7c 76 03 00       	call   0x4397b0
  402134:	48 c7 43 f0 00 00 00 	movq   $0x0,-0x10(%rbx)
  40213b:	00 
  40213c:	48 c7 43 f8 00 00 00 	movq   $0x0,-0x8(%rbx)
  402143:	00 
  402144:	4c 39 e3             	cmp    %r12,%rbx
  402147:	75 af                	jne    0x4020f8
  402149:	41 83 c5 01          	add    $0x1,%r13d
  40214d:	4c 8d 63 30          	lea    0x30(%rbx),%r12
  402151:	41 83 fd 03          	cmp    $0x3,%r13d
  402155:	75 9c                	jne    0x4020f3
  402157:	44 8b 94 24 9c 00 00 	mov    0x9c(%rsp),%r10d
  40215e:	00 
  40215f:	48 8b 6c 24 10       	mov    0x10(%rsp),%rbp
  402164:	45 85 d2             	test   %r10d,%r10d
  402167:	0f 85 56 07 00 00    	jne    0x4028c3
  40216d:	8b 8c 24 18 01 00 00 	mov    0x118(%rsp),%ecx
  402174:	8b b4 24 d8 00 00 00 	mov    0xd8(%rsp),%esi
  40217b:	48 8b bc 24 d0 00 00 	mov    0xd0(%rsp),%rdi
  402182:	00 
  402183:	48 8b 94 24 10 01 00 	mov    0x110(%rsp),%rdx
  40218a:	00 
  40218b:	e8 30 15 00 00       	call   0x4036c0
  402190:	48 8d bc 24 d0 00 00 	lea    0xd0(%rsp),%rdi
  402197:	00 
  402198:	48 89 84 24 60 01 00 	mov    %rax,0x160(%rsp)
  40219f:	00 
  4021a0:	48 89 94 24 68 01 00 	mov    %rdx,0x168(%rsp)
  4021a7:	00 
  4021a8:	e8 93 0b 00 00       	call   0x402d40
  4021ad:	48 8d bc 24 10 01 00 	lea    0x110(%rsp),%rdi
  4021b4:	00 
  4021b5:	e8 86 0b 00 00       	call   0x402d40
  4021ba:	8b 8c 24 58 01 00 00 	mov    0x158(%rsp),%ecx
  4021c1:	8b b4 24 68 01 00 00 	mov    0x168(%rsp),%esi
  4021c8:	48 8b bc 24 60 01 00 	mov    0x160(%rsp),%rdi
  4021cf:	00 
  4021d0:	48 8b 94 24 50 01 00 	mov    0x150(%rsp),%rdx
  4021d7:	00 
  4021d8:	e8 53 12 00 00       	call   0x403430
  4021dd:	48 8d bc 24 60 01 00 	lea    0x160(%rsp),%rdi
  4021e4:	00 
  4021e5:	48 89 84 24 70 01 00 	mov    %rax,0x170(%rsp)
  4021ec:	00 
  4021ed:	48 89 94 24 78 01 00 	mov    %rdx,0x178(%rsp)
  4021f4:	00 
  4021f5:	e8 46 0b 00 00       	call   0x402d40
  4021fa:	48 8d bc 24 50 01 00 	lea    0x150(%rsp),%rdi
  402201:	00 
  402202:	e8 39 0b 00 00       	call   0x402d40
  402207:	83 bc 24 78 01 00 00 	cmpl   $0x1,0x178(%rsp)
  40220e:	01 
  40220f:	0f 84 25 03 00 00    	je     0x40253a
  402215:	48 8d bc 24 70 01 00 	lea    0x170(%rsp),%rdi
  40221c:	00 
  40221d:	e8 1e 0b 00 00       	call   0x402d40
  402222:	48 89 ef             	mov    %rbp,%rdi
  402225:	e8 16 0b 00 00       	call   0x402d40
  40222a:	48 8d bc 24 60 02 00 	lea    0x260(%rsp),%rdi
  402231:	00 
  402232:	e8 09 0b 00 00       	call   0x402d40
  402237:	48 8d bc 24 70 02 00 	lea    0x270(%rsp),%rdi
  40223e:	00 
  40223f:	e8 fc 0a 00 00       	call   0x402d40
  402244:	e8 57 0b 00 00       	call   0x402da0
  402249:	48 8b 6c 24 08       	mov    0x8(%rsp),%rbp
  40224e:	44 89 e3             	mov    %r12d,%ebx
  402251:	44 89 f0             	mov    %r14d,%eax
  402254:	45 85 f6             	test   %r14d,%r14d
  402257:	0f 8e 84 f6 ff ff    	jle    0x4018e1
  40225d:	4c 63 e0             	movslq %eax,%r12
  402260:	4d 8d 6f 10          	lea    0x10(%r15),%r13
  402264:	4d 6b e4 30          	imul   $0x30,%r12,%r12
  402268:	4d 01 ec             	add    %r13,%r12
  40226b:	4c 89 ef             	mov    %r13,%rdi
  40226e:	49 83 c5 30          	add    $0x30,%r13
  402272:	e8 89 1c 00 00       	call   0x403f00
  402277:	4d 39 ec             	cmp    %r13,%r12
  40227a:	75 ef                	jne    0x40226b
  40227c:	e9 60 f6 ff ff       	jmp    0x4018e1
  402281:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  402288:	00 00 00 00 
  40228c:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  402293:	00 00 00 00 
  402297:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  40229e:	00 00 
  4022a0:	44 8b 73 f4          	mov    -0xc(%rbx),%r14d
  4022a4:	45 85 f6             	test   %r14d,%r14d
  4022a7:	0f 85 ec 01 00 00    	jne    0x402499
  4022ad:	48 83 c3 30          	add    $0x30,%rbx
  4022b1:	48 39 5c 24 28       	cmp    %rbx,0x28(%rsp)
  4022b6:	75 e8                	jne    0x4022a0
  4022b8:	4c 8b 6c 24 08       	mov    0x8(%rsp),%r13
  4022bd:	4c 8b 64 24 58       	mov    0x58(%rsp),%r12
  4022c2:	44 89 fb             	mov    %r15d,%ebx
  4022c5:	41 89 ef             	mov    %ebp,%r15d
  4022c8:	48 8b 6c 24 60       	mov    0x60(%rsp),%rbp
  4022cd:	4c 89 ef             	mov    %r13,%rdi
  4022d0:	49 83 c4 10          	add    $0x10,%r12
  4022d4:	e8 27 1c 00 00       	call   0x403f00
  4022d9:	4c 8b 74 24 10       	mov    0x10(%rsp),%r14
  4022de:	4c 89 f7             	mov    %r14,%rdi
  4022e1:	e8 1a 1c 00 00       	call   0x403f00
  4022e6:	48 8b 44 24 20       	mov    0x20(%rsp),%rax
  4022eb:	45 89 7c 24 08       	mov    %r15d,0x8(%r12)
  4022f0:	4c 89 ef             	mov    %r13,%rdi
  4022f3:	41 89 5c 24 0c       	mov    %ebx,0xc(%r12)
  4022f8:	49 89 04 24          	mov    %rax,(%r12)
  4022fc:	e8 4f 1d 00 00       	call   0x404050
  402301:	4c 89 f7             	mov    %r14,%rdi
  402304:	e8 47 1d 00 00       	call   0x404050
  402309:	c7 44 24 18 02 00 00 	movl   $0x2,0x18(%rsp)
  402310:	00 
  402311:	e9 2d f9 ff ff       	jmp    0x401c43
  402316:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  40231d:	00 00 00 
  402320:	8b 84 24 84 02 00 00 	mov    0x284(%rsp),%eax
  402327:	85 c0                	test   %eax,%eax
  402329:	0f 84 01 fa ff ff    	je     0x401d30
  40232f:	44 8d 65 01          	lea    0x1(%rbp),%r12d
  402333:	45 39 fc             	cmp    %r15d,%r12d
  402336:	7e 42                	jle    0x40237a
  402338:	43 8d 04 3f          	lea    (%r15,%r15,1),%eax
  40233c:	45 85 ff             	test   %r15d,%r15d
  40233f:	41 bf 08 00 00 00    	mov    $0x8,%r15d
  402345:	44 0f 45 f8          	cmovne %eax,%r15d
  402349:	45 39 e7             	cmp    %r12d,%r15d
  40234c:	7d 0a                	jge    0x402358
  40234e:	66 90                	xchg   %ax,%ax
  402350:	45 01 ff             	add    %r15d,%r15d
  402353:	45 39 e7             	cmp    %r12d,%r15d
  402356:	7c f8                	jl     0x402350
  402358:	49 63 c7             	movslq %r15d,%rax
  40235b:	48 8b 7c 24 20       	mov    0x20(%rsp),%rdi
  402360:	89 4c 24 30          	mov    %ecx,0x30(%rsp)
  402364:	48 8d 34 40          	lea    (%rax,%rax,2),%rsi
  402368:	48 c1 e6 04          	shl    $0x4,%rsi
  40236c:	e8 af 77 03 00       	call   0x439b20
  402371:	8b 4c 24 30          	mov    0x30(%rsp),%ecx
  402375:	48 89 44 24 20       	mov    %rax,0x20(%rsp)
  40237a:	4c 63 d5             	movslq %ebp,%r10
  40237d:	89 4c 24 38          	mov    %ecx,0x38(%rsp)
  402381:	48 8b 4c 24 20       	mov    0x20(%rsp),%rcx
  402386:	4b 8d 04 52          	lea    (%r10,%r10,2),%rax
  40238a:	48 c1 e0 04          	shl    $0x4,%rax
  40238e:	48 8d 2c 01          	lea    (%rcx,%rax,1),%rbp
  402392:	48 8d 7d 10          	lea    0x10(%rbp),%rdi
  402396:	48 89 7c 24 30       	mov    %rdi,0x30(%rsp)
  40239b:	e8 b0 1c 00 00       	call   0x404050
  4023a0:	48 8b 74 24 08       	mov    0x8(%rsp),%rsi
  4023a5:	48 8b 7c 24 30       	mov    0x30(%rsp),%rdi
  4023aa:	e8 f1 21 00 00       	call   0x4045a0
  4023af:	8b 4c 24 38          	mov    0x38(%rsp),%ecx
  4023b3:	66 41 0f 6e c5       	movd   %r13d,%xmm0
  4023b8:	66 41 0f 6e de       	movd   %r14d,%xmm3
  4023bd:	66 0f 62 c3          	punpckldq %xmm3,%xmm0
  4023c1:	89 4d 08             	mov    %ecx,0x8(%rbp)
  4023c4:	66 0f d6 45 00       	movq   %xmm0,0x0(%rbp)
  4023c9:	44 89 e5             	mov    %r12d,%ebp
  4023cc:	e9 5f f9 ff ff       	jmp    0x401d30
  4023d1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  4023d8:	8b 84 24 84 02 00 00 	mov    0x284(%rsp),%eax
  4023df:	85 c0                	test   %eax,%eax
  4023e1:	0f 84 c9 f7 ff ff    	je     0x401bb0
  4023e7:	45 8d 5f 01          	lea    0x1(%r15),%r11d
  4023eb:	45 39 f3             	cmp    %r14d,%r11d
  4023ee:	7e 50                	jle    0x402440
  4023f0:	43 8d 04 36          	lea    (%r14,%r14,1),%eax
  4023f4:	45 85 f6             	test   %r14d,%r14d
  4023f7:	41 be 08 00 00 00    	mov    $0x8,%r14d
  4023fd:	44 0f 45 f0          	cmovne %eax,%r14d
  402401:	45 39 de             	cmp    %r11d,%r14d
  402404:	7d 12                	jge    0x402418
  402406:	66 90                	xchg   %ax,%ax
  402408:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  40240f:	00 
  402410:	45 01 f6             	add    %r14d,%r14d
  402413:	45 39 f3             	cmp    %r14d,%r11d
  402416:	7f f8                	jg     0x402410
  402418:	49 63 c6             	movslq %r14d,%rax
  40241b:	4c 89 ef             	mov    %r13,%rdi
  40241e:	44 89 5c 24 28       	mov    %r11d,0x28(%rsp)
  402423:	48 8d 34 40          	lea    (%rax,%rax,2),%rsi
  402427:	89 54 24 20          	mov    %edx,0x20(%rsp)
  40242b:	48 c1 e6 04          	shl    $0x4,%rsi
  40242f:	e8 ec 76 03 00       	call   0x439b20
  402434:	44 8b 5c 24 28       	mov    0x28(%rsp),%r11d
  402439:	8b 54 24 20          	mov    0x20(%rsp),%edx
  40243d:	49 89 c5             	mov    %rax,%r13
  402440:	4d 63 d7             	movslq %r15d,%r10
  402443:	89 54 24 28          	mov    %edx,0x28(%rsp)
  402447:	4b 8d 04 52          	lea    (%r10,%r10,2),%rax
  40244b:	44 89 5c 24 30       	mov    %r11d,0x30(%rsp)
  402450:	48 c1 e0 04          	shl    $0x4,%rax
  402454:	4d 8d 7c 05 00       	lea    0x0(%r13,%rax,1),%r15
  402459:	49 8d 7f 10          	lea    0x10(%r15),%rdi
  40245d:	48 89 7c 24 20       	mov    %rdi,0x20(%rsp)
  402462:	e8 e9 1b 00 00       	call   0x404050
  402467:	48 8b 74 24 08       	mov    0x8(%rsp),%rsi
  40246c:	48 8b 7c 24 20       	mov    0x20(%rsp),%rdi
  402471:	e8 2a 21 00 00       	call   0x4045a0
  402476:	8b 54 24 28          	mov    0x28(%rsp),%edx
  40247a:	66 0f 6e e5          	movd   %ebp,%xmm4
  40247e:	41 89 5f 08          	mov    %ebx,0x8(%r15)
  402482:	66 0f 6e c2          	movd   %edx,%xmm0
  402486:	66 0f 62 c4          	punpckldq %xmm4,%xmm0
  40248a:	66 41 0f d6 07       	movq   %xmm0,(%r15)
  40248f:	44 8b 7c 24 30       	mov    0x30(%rsp),%r15d
  402494:	e9 17 f7 ff ff       	jmp    0x401bb0
  402499:	4c 8b 64 24 10       	mov    0x10(%rsp),%r12
  40249e:	8b 4b f8             	mov    -0x8(%rbx),%ecx
  4024a1:	49 63 f6             	movslq %r14d,%rsi
  4024a4:	ba 01 00 00 00       	mov    $0x1,%edx
  4024a9:	44 8b 6b f0          	mov    -0x10(%rbx),%r13d
  4024ad:	41 83 ee 01          	sub    $0x1,%r14d
  4024b1:	4c 89 e7             	mov    %r12,%rdi
  4024b4:	89 4c 24 30          	mov    %ecx,0x30(%rsp)
  4024b8:	e8 83 21 00 00       	call   0x404640
  4024bd:	48 8b 7c 24 08       	mov    0x8(%rsp),%rdi
  4024c2:	4c 89 e2             	mov    %r12,%rdx
  4024c5:	48 89 de             	mov    %rbx,%rsi
  4024c8:	e8 73 1c 00 00       	call   0x404140
  4024cd:	8b 4c 24 30          	mov    0x30(%rsp),%ecx
  4024d1:	e9 e3 f7 ff ff       	jmp    0x401cb9
  4024d6:	c7 44 24 18 02 00 00 	movl   $0x2,0x18(%rsp)
  4024dd:	00 
  4024de:	e9 3d f7 ff ff       	jmp    0x401c20
  4024e3:	4c 89 ef             	mov    %r13,%rdi
  4024e6:	83 ed 01             	sub    $0x1,%ebp
  4024e9:	e8 12 1a 00 00       	call   0x403f00
  4024ee:	48 8b 44 24 30       	mov    0x30(%rsp),%rax
  4024f3:	b9 0c 00 00 00       	mov    $0xc,%ecx
  4024f8:	4c 89 e7             	mov    %r12,%rdi
  4024fb:	48 8d 70 d0          	lea    -0x30(%rax),%rsi
  4024ff:	f3 a5                	rep movsl %ds:(%rsi),%es:(%rdi)
  402501:	e9 2a f8 ff ff       	jmp    0x401d30
  402506:	45 31 ff             	xor    %r15d,%r15d
  402509:	45 31 ed             	xor    %r13d,%r13d
  40250c:	45 31 f6             	xor    %r14d,%r14d
  40250f:	e9 40 f8 ff ff       	jmp    0x401d54
  402514:	48 89 df             	mov    %rbx,%rdi
  402517:	41 83 ef 01          	sub    $0x1,%r15d
  40251b:	e8 e0 19 00 00       	call   0x403f00
  402520:	4c 8b 5c 24 28       	mov    0x28(%rsp),%r11
  402525:	48 8b 7c 24 20       	mov    0x20(%rsp),%rdi
  40252a:	b9 0c 00 00 00       	mov    $0xc,%ecx
  40252f:	49 8d 73 d0          	lea    -0x30(%r11),%rsi
  402533:	f3 a5                	rep movsl %ds:(%rsi),%es:(%rdi)
  402535:	e9 76 f6 ff ff       	jmp    0x401bb0
  40253a:	48 8b 84 24 70 01 00 	mov    0x170(%rsp),%rax
  402541:	00 
  402542:	48 83 38 00          	cmpq   $0x0,(%rax)
  402546:	0f 85 c9 fc ff ff    	jne    0x402215
  40254c:	83 78 08 00          	cmpl   $0x0,0x8(%rax)
  402550:	0f 85 bf fc ff ff    	jne    0x402215
  402556:	48 8d bc 24 70 01 00 	lea    0x170(%rsp),%rdi
  40255d:	00 
  40255e:	48 8d 9c 24 30 02 00 	lea    0x230(%rsp),%rbx
  402565:	00 
  402566:	4c 8d a4 24 10 02 00 	lea    0x210(%rsp),%r12
  40256d:	00 
  40256e:	4c 8d ac 24 90 01 00 	lea    0x190(%rsp),%r13
  402575:	00 
  402576:	e8 c5 07 00 00       	call   0x402d40
  40257b:	48 89 5c 24 28       	mov    %rbx,0x28(%rsp)
  402580:	49 89 d9             	mov    %rbx,%r9
  402583:	4d 89 e0             	mov    %r12,%r8
  402586:	4c 89 64 24 20       	mov    %r12,0x20(%rsp)
  40258b:	48 8d 84 24 d0 01 00 	lea    0x1d0(%rsp),%rax
  402592:	00 
  402593:	4c 89 ef             	mov    %r13,%rdi
  402596:	48 8d b4 24 b0 01 00 	lea    0x1b0(%rsp),%rsi
  40259d:	00 
  40259e:	4c 8d bc 24 f0 01 00 	lea    0x1f0(%rsp),%r15
  4025a5:	00 
  4025a6:	48 83 ec 08          	sub    $0x8,%rsp
  4025aa:	48 89 c2             	mov    %rax,%rdx
  4025ad:	6a 00                	push   $0x0
  4025af:	4c 89 f9             	mov    %r15,%rcx
  4025b2:	48 89 44 24 28       	mov    %rax,0x28(%rsp)
  4025b7:	31 c0                	xor    %eax,%eax
  4025b9:	48 89 74 24 20       	mov    %rsi,0x20(%rsp)
  4025be:	e8 dd 1a 00 00       	call   0x4040a0
  4025c3:	48 8b 54 24 28       	mov    0x28(%rsp),%rdx
  4025c8:	48 8b 74 24 20       	mov    0x20(%rsp),%rsi
  4025cd:	4c 89 ef             	mov    %r13,%rdi
  4025d0:	e8 2b 05 00 00       	call   0x402b00
  4025d5:	41 58                	pop    %r8
  4025d7:	41 59                	pop    %r9
  4025d9:	85 c0                	test   %eax,%eax
  4025db:	0f 84 97 02 00 00    	je     0x402878
  4025e1:	48 89 da             	mov    %rbx,%rdx
  4025e4:	4c 89 e6             	mov    %r12,%rsi
  4025e7:	4c 89 ff             	mov    %r15,%rdi
  4025ea:	e8 11 05 00 00       	call   0x402b00
  4025ef:	85 c0                	test   %eax,%eax
  4025f1:	0f 84 81 02 00 00    	je     0x402878
  4025f7:	4c 89 fe             	mov    %r15,%rsi
  4025fa:	4c 89 ef             	mov    %r13,%rdi
  4025fd:	e8 be 21 00 00       	call   0x4047c0
  402602:	85 c0                	test   %eax,%eax
  402604:	74 2a                	je     0x402630
  402606:	48 8b 74 24 20       	mov    0x20(%rsp),%rsi
  40260b:	48 8b 7c 24 10       	mov    0x10(%rsp),%rdi
  402610:	e8 ab 21 00 00       	call   0x4047c0
  402615:	85 c0                	test   %eax,%eax
  402617:	74 17                	je     0x402630
  402619:	48 8b 74 24 28       	mov    0x28(%rsp),%rsi
  40261e:	48 8b 7c 24 18       	mov    0x18(%rsp),%rdi
  402623:	e8 98 21 00 00       	call   0x4047c0
  402628:	85 c0                	test   %eax,%eax
  40262a:	0f 85 48 02 00 00    	jne    0x402878
  402630:	48 8d 84 24 a0 02 00 	lea    0x2a0(%rsp),%rax
  402637:	00 
  402638:	4c 8d 8c 24 20 03 00 	lea    0x320(%rsp),%r9
  40263f:	00 
  402640:	45 31 e4             	xor    %r12d,%r12d
  402643:	4c 8d 84 24 00 03 00 	lea    0x300(%rsp),%r8
  40264a:	00 
  40264b:	48 8d 94 24 c0 02 00 	lea    0x2c0(%rsp),%rdx
  402652:	00 
  402653:	48 89 44 24 48       	mov    %rax,0x48(%rsp)
  402658:	48 89 c6             	mov    %rax,%rsi
  40265b:	4c 89 4c 24 40       	mov    %r9,0x40(%rsp)
  402660:	48 83 ec 08          	sub    $0x8,%rsp
  402664:	31 c0                	xor    %eax,%eax
  402666:	4c 89 44 24 60       	mov    %r8,0x60(%rsp)
  40266b:	48 89 54 24 58       	mov    %rdx,0x58(%rsp)
  402670:	6a 00                	push   $0x0
  402672:	48 8b 5c 24 18       	mov    0x18(%rsp),%rbx
  402677:	48 8b 8c 24 80 00 00 	mov    0x80(%rsp),%rcx
  40267e:	00 
  40267f:	48 89 df             	mov    %rbx,%rdi
  402682:	e8 19 1a 00 00       	call   0x4040a0
  402687:	59                   	pop    %rcx
  402688:	5e                   	pop    %rsi
  402689:	48 8d 84 24 58 02 00 	lea    0x258(%rsp),%rax
  402690:	00 
  402691:	4c 89 6c 24 30       	mov    %r13,0x30(%rsp)
  402696:	48 89 44 24 38       	mov    %rax,0x38(%rsp)
  40269b:	4c 89 74 24 60       	mov    %r14,0x60(%rsp)
  4026a0:	49 89 de             	mov    %rbx,%r14
  4026a3:	4c 89 e3             	mov    %r12,%rbx
  4026a6:	48 8b 44 24 38       	mov    0x38(%rsp),%rax
  4026ab:	4c 8b 64 1d 00       	mov    0x0(%rbp,%rbx,1),%r12
  4026b0:	4d 89 f1             	mov    %r14,%r9
  4026b3:	49 83 c6 20          	add    $0x20,%r14
  4026b7:	4c 8b 44 24 18       	mov    0x18(%rsp),%r8
  4026bc:	48 8b 4c 24 10       	mov    0x10(%rsp),%rcx
  4026c1:	44 8b 2c 18          	mov    (%rax,%rbx,1),%r13d
  4026c5:	48 8b 54 24 30       	mov    0x30(%rsp),%rdx
  4026ca:	4c 89 e7             	mov    %r12,%rdi
  4026cd:	44 89 ee             	mov    %r13d,%esi
  4026d0:	e8 eb 06 00 00       	call   0x402dc0
  4026d5:	48 8b 44 24 70       	mov    0x70(%rsp),%rax
  4026da:	4c 89 fa             	mov    %r15,%rdx
  4026dd:	44 89 ee             	mov    %r13d,%esi
  4026e0:	4c 8b 44 24 28       	mov    0x28(%rsp),%r8
  4026e5:	48 8b 4c 24 20       	mov    0x20(%rsp),%rcx
  4026ea:	4c 89 e7             	mov    %r12,%rdi
  4026ed:	4c 8d 0c 58          	lea    (%rax,%rbx,2),%r9
  4026f1:	48 83 c3 10          	add    $0x10,%rbx
  4026f5:	e8 c6 06 00 00       	call   0x402dc0
  4026fa:	48 83 fb 30          	cmp    $0x30,%rbx
  4026fe:	75 a6                	jne    0x4026a6
  402700:	48 8b 74 24 70       	mov    0x70(%rsp),%rsi
  402705:	48 8b 7c 24 08       	mov    0x8(%rsp),%rdi
  40270a:	4c 8b 74 24 60       	mov    0x60(%rsp),%r14
  40270f:	4c 8b 6c 24 30       	mov    0x30(%rsp),%r13
  402714:	e8 a7 20 00 00       	call   0x4047c0
  402719:	41 89 c4             	mov    %eax,%r12d
  40271c:	85 c0                	test   %eax,%eax
  40271e:	74 2e                	je     0x40274e
  402720:	48 8b 74 24 58       	mov    0x58(%rsp),%rsi
  402725:	48 8b 7c 24 48       	mov    0x48(%rsp),%rdi
  40272a:	e8 91 20 00 00       	call   0x4047c0
  40272f:	41 89 c4             	mov    %eax,%r12d
  402732:	85 c0                	test   %eax,%eax
  402734:	74 18                	je     0x40274e
  402736:	48 8b 74 24 40       	mov    0x40(%rsp),%rsi
  40273b:	48 8b 7c 24 50       	mov    0x50(%rsp),%rdi
  402740:	45 31 e4             	xor    %r12d,%r12d
  402743:	e8 78 20 00 00       	call   0x4047c0
  402748:	85 c0                	test   %eax,%eax
  40274a:	41 0f 95 c4          	setne  %r12b
  40274e:	48 83 ec 08          	sub    $0x8,%rsp
  402752:	4c 89 ef             	mov    %r13,%rdi
  402755:	4c 89 f9             	mov    %r15,%rcx
  402758:	31 c0                	xor    %eax,%eax
  40275a:	6a 00                	push   $0x0
  40275c:	4c 8b 4c 24 38       	mov    0x38(%rsp),%r9
  402761:	4c 8d 6d 30          	lea    0x30(%rbp),%r13
  402765:	4c 8b 44 24 30       	mov    0x30(%rsp),%r8
  40276a:	48 8b 54 24 28       	mov    0x28(%rsp),%rdx
  40276f:	48 8b 74 24 20       	mov    0x20(%rsp),%rsi
  402774:	e8 d7 17 00 00       	call   0x403f50
  402779:	4c 8b 4c 24 50       	mov    0x50(%rsp),%r9
  40277e:	4c 8b 44 24 68       	mov    0x68(%rsp),%r8
  402783:	31 c0                	xor    %eax,%eax
  402785:	48 8b 8c 24 80 00 00 	mov    0x80(%rsp),%rcx
  40278c:	00 
  40278d:	48 8b 54 24 60       	mov    0x60(%rsp),%rdx
  402792:	48 c7 04 24 00 00 00 	movq   $0x0,(%rsp)
  402799:	00 
  40279a:	48 8b 74 24 58       	mov    0x58(%rsp),%rsi
  40279f:	48 8b 7c 24 18       	mov    0x18(%rsp),%rdi
  4027a4:	e8 a7 17 00 00       	call   0x403f50
  4027a9:	58                   	pop    %rax
  4027aa:	5a                   	pop    %rdx
  4027ab:	49 63 46 08          	movslq 0x8(%r14),%rax
  4027af:	4d 8b 3e             	mov    (%r14),%r15
  4027b2:	85 c0                	test   %eax,%eax
  4027b4:	7e 2b                	jle    0x4027e1
  4027b6:	48 8d 2c 40          	lea    (%rax,%rax,2),%rbp
  4027ba:	49 8d 5f 10          	lea    0x10(%r15),%rbx
  4027be:	48 c1 e5 04          	shl    $0x4,%rbp
  4027c2:	48 01 dd             	add    %rbx,%rbp
  4027c5:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  4027cc:	00 00 00 00 
  4027d0:	48 89 df             	mov    %rbx,%rdi
  4027d3:	48 83 c3 30          	add    $0x30,%rbx
  4027d7:	e8 24 17 00 00       	call   0x403f00
  4027dc:	48 39 dd             	cmp    %rbx,%rbp
  4027df:	75 ef                	jne    0x4027d0
  4027e1:	4c 89 ff             	mov    %r15,%rdi
  4027e4:	49 83 c6 10          	add    $0x10,%r14
  4027e8:	e8 c3 6f 03 00       	call   0x4397b0
  4027ed:	49 c7 46 f0 00 00 00 	movq   $0x0,-0x10(%r14)
  4027f4:	00 
  4027f5:	49 c7 46 f8 00 00 00 	movq   $0x0,-0x8(%r14)
  4027fc:	00 
  4027fd:	4d 39 f5             	cmp    %r14,%r13
  402800:	75 a9                	jne    0x4027ab
  402802:	45 85 e4             	test   %r12d,%r12d
  402805:	0f 84 39 fa ff ff    	je     0x402244
  40280b:	48 8d 3d 1c a8 0a 00 	lea    0xaa81c(%rip),%rdi        # 0x4ad02e
  402812:	e8 29 ab 02 00       	call   0x42d340
  402817:	48 85 c0             	test   %rax,%rax
  40281a:	48 89 c7             	mov    %rax,%rdi
  40281d:	48 8d 05 fa a7 0a 00 	lea    0xaa7fa(%rip),%rax        # 0x4ad01e
  402824:	48 0f 44 f8          	cmove  %rax,%rdi
  402828:	e8 e3 af 02 00       	call   0x42d810
  40282d:	48 8b 84 24 d8 03 00 	mov    0x3d8(%rsp),%rax
  402834:	00 
  402835:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
  40283c:	00 00 
  40283e:	0f 85 ae 00 00 00    	jne    0x4028f2
  402844:	48 81 c4 e8 03 00 00 	add    $0x3e8,%rsp
  40284b:	31 c0                	xor    %eax,%eax
  40284d:	5b                   	pop    %rbx
  40284e:	5d                   	pop    %rbp
  40284f:	41 5c                	pop    %r12
  402851:	41 5d                	pop    %r13
  402853:	41 5e                	pop    %r14
  402855:	41 5f                	pop    %r15
  402857:	c3                   	ret
  402858:	45 31 db             	xor    %r11d,%r11d
  40285b:	49 8d 45 10          	lea    0x10(%r13),%rax
  40285f:	4c 63 74 24 40       	movslq 0x40(%rsp),%r14
  402864:	31 db                	xor    %ebx,%ebx
  402866:	4c 89 5c 24 18       	mov    %r11,0x18(%rsp)
  40286b:	45 31 ff             	xor    %r15d,%r15d
  40286e:	48 89 44 24 50       	mov    %rax,0x50(%rsp)
  402873:	e9 61 f3 ff ff       	jmp    0x401bd9
  402878:	57                   	push   %rdi
  402879:	4c 89 f9             	mov    %r15,%rcx
  40287c:	31 c0                	xor    %eax,%eax
  40287e:	4c 89 ef             	mov    %r13,%rdi
  402881:	6a 00                	push   $0x0
  402883:	4c 8b 4c 24 38       	mov    0x38(%rsp),%r9
  402888:	4c 8b 44 24 30       	mov    0x30(%rsp),%r8
  40288d:	48 8b 54 24 28       	mov    0x28(%rsp),%rdx
  402892:	48 8b 74 24 20       	mov    0x20(%rsp),%rsi
  402897:	e8 b4 16 00 00       	call   0x403f50
  40289c:	48 89 ef             	mov    %rbp,%rdi
  40289f:	e8 9c 04 00 00       	call   0x402d40
  4028a4:	48 8d bc 24 70 02 00 	lea    0x270(%rsp),%rdi
  4028ab:	00 
  4028ac:	e8 8f 04 00 00       	call   0x402d40
  4028b1:	48 8d bc 24 80 02 00 	lea    0x280(%rsp),%rdi
  4028b8:	00 
  4028b9:	e8 82 04 00 00       	call   0x402d40
  4028be:	e8 dd 04 00 00       	call   0x402da0
  4028c3:	48 8d bc 24 d0 00 00 	lea    0xd0(%rsp),%rdi
  4028ca:	00 
  4028cb:	e8 70 04 00 00       	call   0x402d40
  4028d0:	48 8d bc 24 10 01 00 	lea    0x110(%rsp),%rdi
  4028d7:	00 
  4028d8:	e8 63 04 00 00       	call   0x402d40
  4028dd:	48 8d bc 24 50 01 00 	lea    0x150(%rsp),%rdi
  4028e4:	00 
  4028e5:	e9 33 f9 ff ff       	jmp    0x40221d
  4028ea:	45 31 ff             	xor    %r15d,%r15d
  4028ed:	e9 2c f1 ff ff       	jmp    0x401a1e
  4028f2:	e8 89 49 04 00       	call   0x447280
  4028f7:	66                   	data16
