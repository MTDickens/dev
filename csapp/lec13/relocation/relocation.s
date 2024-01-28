
relocation.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <main>:
   0:	f3 0f 1e fa          	endbr64 
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	48 83 ec 10          	sub    $0x10,%rsp
   c:	be 02 00 00 00       	mov    $0x2,%esi
  11:	48 8d 3d 00 00 00 00 	lea    0x0(%rip),%rdi        # 18 <main+0x18>
			14: R_X86_64_PC32	array-0x4
  18:	e8 00 00 00 00       	callq  1d <main+0x1d>
			19: R_X86_64_PLT32	sum-0x4
  1d:	89 45 fc             	mov    %eax,-0x4(%rbp)
  20:	8b 45 fc             	mov    -0x4(%rbp),%eax
  23:	c9                   	leaveq 
  24:	c3                   	retq   
