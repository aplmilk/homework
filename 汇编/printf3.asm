TITLE MASM Template						(main.asm)

; Description:
; 
; Revision date:

.686P		; Pentium Pro or later
.MODEL flat, stdcall
.STACK 4096
option casemap:none;  大小写不敏感

	
printf          PROTO C :ptr byte,:vararg
scanf           PROTO C :dword,:vararg
gets		PROTO C :ptr byte
getchar		PROTO C
ExitProcess	PROTO,dwExitCode:DWORD	  	; exit program
exit 		EQU <INVOKE ExitProcess,0>

INCLUDELIB ..\USER32.LIB
INCLUDELIB ..\KERNEL32.LIB
INCLUDELIB ..\MSVCRT.LIB


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
.code
main PROC
	invoke printf,chr$("Hello！",0dh,0ah)
	exit
main ENDP

END main