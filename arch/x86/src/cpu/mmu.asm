bits 32

extern invalidate_page
invalidate_page:
	push eax
	mov eax, [esp + 4]
	invlpg [eax]
	pop eax
	ret
