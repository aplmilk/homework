TITLE LongInt

INCLUDE Irvine32.inc


.data
int1 DWORD 8 DUP (70000000)  
int2 DWORD 8 DUP (40000000)
sum1 DWORD 9 DUP (0)
sum2 DWORD 9 DUP (0)
string1  BYTE "长整数和：",0
string2  BYTE "长整数减：",0

.code 
main PROC
	mov esi,offset int1
	mov edi,offset int2
	mov ebx,offset sum1
	mov ecx,8
	call ADDLONGINT

	mov edx,offset string1     
	call WriteString

	mov ecx,9
	mov edx,32
L1:
	mov eax,[sum1+edx]
	call WriteDec
	sub edx,4
	LOOP L1
	call Crlf



	mov ebx,offset sum2
	mov ecx,8
	call SUBLONGINT

	mov edx,offset string2     
	call WriteString

	mov ecx,9
	mov edx,32
L2:
	mov eax,[sum2+edx]
	call WriteDec
	sub edx,4
	LOOP L2
	call Crlf

	exit
main ENDP


ADDLONGINT PROC

	pushad
	clc
L3:
	mov eax,[esi]
	adc eax,[edi]
	pushfd
	mov [ebx],eax
	add esi,4
	add edi,4
	add ebx,4
	popfd
	loop L3

	mov DWORD ptr [ebx],0
	adc DWORD ptr [ebx],0
	popad
	ret
ADDLONGINT ENDP


SUBLONGINT PROC

	pushad
	clc
L4:
	mov eax,[esi]
	sbb eax,[edi]
	pushfd
	mov [ebx],eax
	add esi,4
	add edi,4
	add ebx,4
	popfd
	loop L4

	mov DWORD ptr [ebx],0
	sbb DWORD ptr [ebx],0
	popad
	ret
SUBLONGINT ENDP


END main