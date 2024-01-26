
locality.o:     file format elf64-x86-64


Disassembly of section .text.startup:

0000000000000000 <main>:
   0:	f3 0f 1e fa          	endbr64 
   4:	41 55                	push   %r13
   6:	41 54                	push   %r12
   8:	55                   	push   %rbp
   9:	53                   	push   %rbx
   a:	48 83 ec 08          	sub    $0x8,%rsp
   e:	e8 00 00 00 00       	callq  13 <main+0x13>
  13:	49 89 c5             	mov    %rax,%r13
  16:	e8 00 00 00 00       	callq  1b <main+0x1b>
  1b:	48 89 c5             	mov    %rax,%rbp
  1e:	e8 00 00 00 00       	callq  23 <main+0x23>
  23:	4c 29 ed             	sub    %r13,%rbp
  26:	49 89 c4             	mov    %rax,%r12
  29:	e8 00 00 00 00       	callq  2e <main+0x2e>
  2e:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 35 <main+0x35>
  35:	bf 01 00 00 00       	mov    $0x1,%edi
  3a:	66 0f ef c0          	pxor   %xmm0,%xmm0
  3e:	48 89 c3             	mov    %rax,%rbx
  41:	f2 48 0f 2a c5       	cvtsi2sd %rbp,%xmm0
  46:	b8 01 00 00 00       	mov    $0x1,%eax
  4b:	f2 0f 5e 05 00 00 00 	divsd  0x0(%rip),%xmm0        # 53 <main+0x53>
  52:	00 
  53:	e8 00 00 00 00       	callq  58 <main+0x58>
  58:	4c 29 e3             	sub    %r12,%rbx
  5b:	66 0f ef c0          	pxor   %xmm0,%xmm0
  5f:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 66 <main+0x66>
  66:	bf 01 00 00 00       	mov    $0x1,%edi
  6b:	f2 48 0f 2a c3       	cvtsi2sd %rbx,%xmm0
  70:	b8 01 00 00 00       	mov    $0x1,%eax
  75:	f2 0f 5e 05 00 00 00 	divsd  0x0(%rip),%xmm0        # 7d <main+0x7d>
  7c:	00 
  7d:	e8 00 00 00 00       	callq  82 <main+0x82>
  82:	48 83 c4 08          	add    $0x8,%rsp
  86:	31 c0                	xor    %eax,%eax
  88:	5b                   	pop    %rbx
  89:	5d                   	pop    %rbp
  8a:	41 5c                	pop    %r12
  8c:	41 5d                	pop    %r13
  8e:	c3                   	retq   
