TITLE Experiment-two
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
	
.DATA
	
	buf BYTE 16 dup(?)
	_iq DWORD 0      
	_oq DWORD 0      
	count DWORD 0
	output BYTE ?	 
	lettera BYTE "A"
	letterz BYTE "Z"

.CODE
main PROC  
		INVOKE printf,chr$("Press Esc to exit,0-9,A-Z to add to queue,- to get element out of queue",0dh,0ah,0)
		PUSH OFFSET buf   
	L:
		MOV EAX,0      
		INVOKE _getche
.if     al==1bh
	    jmp endL
.endif
.if		(al>='a' && al<='z')||(al<='9' && al>='0')
		jmp inqueue
.endif
.if		al == '-'
		jmp outqueue


	inqueue:
			PUSH _iq
			PUSH eax
			CALL IQ
			ADD count,1
			ADD _iq,1
			CMP EAX,0
			pop eax
			pop ebx
			JNE adjust

			INVOKE printf,chr$("The queue is full",0dh,0ah,0)
			SUB count,1
			SUB _iq,1
			JMP continue

	outqueue:
			PUSH _oq 
			PUSH OFFSET output
			CALL OQ
			pop ebx
			pop _oq
			SUB count,1
			ADD _oq,1
			CMP EAX,0
			JNE adjust
			ADD count,1
			SUB _oq,1
			INVOKE printf,chr$("The queue is empty",0dh,0ah,0)
			JMP continue

	adjust:
		CMP _iq,16
		JB continue
		MOV _iq,0

		CMP _oq,16
		JB continue
		MOV _oq,0

	continue:
		JMP L
	endL:
		EXIT
main endp

IQ PROC

	enter 0,0
	MOV EBX,[EBP + 8]
	MOV ESI,[EBP + 12]	
	MOV EDI,[EBP + 16]	
	MOV EAX,0
	CMP count,16
	JE retpro1
	ADD EAX,1
	MOV [EDI + ESI],bl
retpro1:
	leave
	RET 
	IQ ENDP

OQ PROC

	enter 0,0
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
	leave
	RET 
	OQ ENDP

END main
