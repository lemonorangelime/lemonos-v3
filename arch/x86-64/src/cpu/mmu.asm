bits 64

extern invalidate_page
invalidate_page:
	invlpg [rdi]
	ret
