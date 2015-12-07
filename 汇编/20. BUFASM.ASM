.586
.MODEL flat,STDCALL
.STACK 4096
option casemap:none;  大小写敏感
	public C ip,op,iq,oq;
	extern C buf:ptr BYTE
	incp PROTO C :ptr DWORD
	iq	 PROTO C :BYTE
	oq	 PROTO C :ptr BYTE

.data           
 n	DWORD	0
 ip DWORD	0
 op DWORD	0

.code
iq	proc C uses ebx,chri:BYTE
	mov	eax,0		;插入了0个元素
	cmp n,16
	jz  iqover
	lea ebx,buf
	add ebx,ip
	mov	al,chri
	mov	[ebx],al
	invoke incp,addr ip
	inc	n
	mov	eax,1		;插入了一个元素
iqover:	ret
iq	endp

oq	proc C uses ebx,chro:ptr BYTE
	mov	eax,0		;提取了0个元素
	cmp n,0
	jz  oqover
	lea ebx,buf
	add	ebx,op
	mov al,[ebx]
	mov	ebx,chro
	mov	[ebx],al
	invoke incp,addr op
	dec	n
	mov	eax,1		;提取了1个元素
oqover:	ret
oq	endp

	END