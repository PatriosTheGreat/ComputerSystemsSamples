
main.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <_Z3sumPll>:
long sum(long *start, long count) {
   0:	55                   	push   rbp
   1:	48 89 e5             	mov    rbp,rsp
   4:	48 89 7d f8          	mov    QWORD PTR [rbp-0x8],rdi
   8:	48 89 75 f0          	mov    QWORD PTR [rbp-0x10],rsi
    long sum = 0;
   c:	48 c7 45 e8 00 00 00 	mov    QWORD PTR [rbp-0x18],0x0
  13:	00 
    while (count) {
  14:	48 83 7d f0 00       	cmp    QWORD PTR [rbp-0x10],0x0
  19:	0f 84 30 00 00 00    	je     4f <_Z3sumPll+0x4f>
        sum += *start;
  1f:	48 8b 45 f8          	mov    rax,QWORD PTR [rbp-0x8]
  23:	48 8b 00             	mov    rax,QWORD PTR [rax]
  26:	48 03 45 e8          	add    rax,QWORD PTR [rbp-0x18]
  2a:	48 89 45 e8          	mov    QWORD PTR [rbp-0x18],rax
        start++;
  2e:	48 8b 45 f8          	mov    rax,QWORD PTR [rbp-0x8]
  32:	48 05 08 00 00 00    	add    rax,0x8
  38:	48 89 45 f8          	mov    QWORD PTR [rbp-0x8],rax
        count--;
  3c:	48 8b 45 f0          	mov    rax,QWORD PTR [rbp-0x10]
  40:	48 05 ff ff ff ff    	add    rax,0xffffffffffffffff
  46:	48 89 45 f0          	mov    QWORD PTR [rbp-0x10],rax
    while (count) {
  4a:	e9 c5 ff ff ff       	jmp    14 <_Z3sumPll+0x14>
    }

    return sum;
  4f:	48 8b 45 e8          	mov    rax,QWORD PTR [rbp-0x18]
  53:	5d                   	pop    rbp
  54:	c3                   	ret    
  55:	66 2e 0f 1f 84 00 00 	nop    WORD PTR cs:[rax+rax*1+0x0]
  5c:	00 00 00 
  5f:	90                   	nop

0000000000000060 <main>:
}

int main() {
  60:	55                   	push   rbp
  61:	48 89 e5             	mov    rbp,rsp
  64:	31 c0                	xor    eax,eax
    
  66:	5d                   	pop    rbp
  67:	c3                   	ret    
