TITLE Program sort

INCLUDE Irvine32.inc

.data
arrayi SDWORD 100 DUP(?)
str1 BYTE "������1<n<100��32λ�з�������������0��������:",0
str2 BYTE "����ǰ���顢�Ĵ���״̬��",0
str3 BYTE "��������顢�Ĵ���״̬��",0

.code
main PROC

mov edx,offset str1       ;����
call WriteString
mov ebx, offset arrayi
mov ecx,100  
mov edi,0
L6:
call ReadHex
mov [ebx+edi*4],eax
inc edi
cmp eax,0
jg L7
mov ecx,1
L7:Loop L6


mov edx,offset str2        ;����ǰ���
call WriteString

dec edi
mov ecx,edi      
mov ebx, offset arrayi 
mov esi,0
L8:mov eax,[ebx+esi*4]
call WriteHexB
mov al,' '
call WriteChar
inc esi
loop L8

call Dumpregs



mov ecx,edi
dec ecx

L1:push ecx 
mov ebx,offset arrayi
mov esi,0 

L2:mov eax,[ebx+esi*4]
inc esi
cmp [ebx+esi*4],eax
JL L3
xchg eax,[ebx+esi*4]
dec esi
mov [ebx+esi*4],eax
inc esi

L3:loop L2

pop ecx
loop L1


mov edx,offset str3  ;��������
call WriteString
mov ecx,edi
mov ebx, offset arrayi
mov esi,0
L4:mov eax,[ebx+esi*4]
call WriteHexB
mov al,' '
call WriteChar
inc esi
loop L4

call Dumpregs

exit 
main ENDP
END main