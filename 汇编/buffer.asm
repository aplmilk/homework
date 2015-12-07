TITLE buffer

.686P
.MODEL flat, stdcall
.STACK 4096


	
printf      PROTO C :ptr byte,:vararg
_getche     PROTO C
ExitProcess	PROTO,dwExitCode:DWORD	  	; exit program
exit 		EQU <INVOKE ExitProcess,0>

INCLUDELIB USER32.LIB
INCLUDELIB KERNEL32.LIB
INCLUDELIB MSVCRT.LIB


chr$ MACRO any_text:VARARG
        LOCAL txtname
        .data
          IFDEF __UNICODE__
            WSTR txtname,any_text
            align 4
            .code
            EXITM <OFFSET txtname>
          ENDIF

          txtname byte any_text,0
          align 4
          .code
          EXITM <OFFSET txtname>
ENDM


.data
buf BYTE 16 DUP(?)
IQ_ DWORD 0
OQ_ DWORD 0
count DWORD 0
output BYTE ?	

.code
main PROC
	invoke printf,chr$("Please input any word between 0-9 or a-z,and press - to get element out of queue,press Esc to exit:",0dh,0ah)
	PUSH OFFSET buf   

L:
	MOV EAX,0      
	INVOKE _getche

	CMP AL,1BH
	JE ENDPROC

	CMP AL,'-'
	JE outqueue

	CMP AL,'0'
	JB miss
	CMP AL,'9'
	JBE inqueue
	CMP AL,'A'
	JB miss
	CMP AL,'Z'
	JBE inqueue
	CMP AL,'a'
	JB miss
	CMP AL,'z'
	JBE inqueue

outqueue:
	PUSH OQ_ 
	PUSH OFFSET output
	CALL OQ
	pop ebx
	pop OQ_
	SUB count,1
	ADD OQ_,1
	CMP EAX,0
	JNE adjust
	ADD count,1
	SUB OQ_,1
	INVOKE printf,chr$("The queue is empty",0dh,0ah,0)
	JMP miss


inqueue:
	PUSH IQ_
	PUSH eax
	CALL IQ
	ADD count,1
	ADD IQ_,1
	CMP EAX,0
	pop eax
	pop ebx
	JNE adjust

	INVOKE printf,chr$("The queue is full",0dh,0ah,0)
	SUB count,1
	SUB IQ_,1
	JMP miss

adjust:
	CMP IQ_,16
	JB miss
	MOV IQ_,0

	CMP OQ_,16
	JB miss
	MOV OQ_,0


miss:
	jmp L


ENDPROC:
	exit
	main ENDP



IQ PROC

	PUSH EBP
	MOV EBP,ESP
	MOV BL,[EBP + 8]	
	MOV ESI,[EBP + 12]	
	MOV EDI,[EBP + 16]	

	MOV EAX,0
	CMP count,16
	JE retpro1
	ADD EAX,1	
	MOV [EDI + ESI],BL
retpro1:
	LEAVE
	RET 
	IQ ENDP



OQ PROC

	PUSH EBP
	MOV EBP,ESP
	MOV EBX,[EBP + 8]	
	MOV ESI,[EBP + 12]	
	MOV EDI,[EBP + 16]	
	MOV EAX,0
	CMP count,0
	JE retpro2
	ADD EAX,1
	MOV ECX,[EDI + ESI]
	mov [ebx],ecx
	push eax
	INVOKE printf,chr$("%c",0dh,0ah,0),byte ptr[ebx]
	pop eax
	
retpro2:
	LEAVE
	RET 
	OQ ENDP




END main