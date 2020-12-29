global	exception_de
global	exception_db
global	exception_nmi
global	exception_bp
global	exception_of
global	exception_br
global	exception_ud
global	exception_nm
global	exception_df
global	exception_ts
global	exception_np
global	exception_ss
global	exception_gp
global	exception_pf
global	exception_mf
global	exception_ac
global	exception_mc
global	exception_xf
global	exception_cp
global	exception_hv
global	exception_vc
global	exception_sx
global	exception_other

m_00	db	"exception_de", 0
m_01	db	"exception_db", 0
m_02	db	"exception_nmi", 0
m_03	db	"exception_bp", 0
m_04	db	"exception_of", 0
m_05	db	"exception_br", 0
m_06	db	"exception_ud", 0
m_07	db	"exception_nm", 0
m_08	db	"exception_df", 0
m_09	db	"exception_ts", 0
m_10	db	"exception_np", 0
m_11	db	"exception_ss", 0
m_12	db	"exception_gp", 0
m_13	db	"exception_pf", 0
m_14	db	"exception_mf", 0
m_15	db	"exception_ac", 0
m_16	db	"exception_mc", 0
m_17	db	"exception_xf", 0
m_18	db	"exception_cp", 0
m_19	db	"exception_hv", 0
m_20	db	"exception_vc", 0
m_21	db	"exception_sx", 0
m_22	db	"exception_other", 0

extern log
extern gpcoolcool

exception_de:
	push	m_00
	call	log
	iret

exception_db:
	push	m_01
	call	log
	iret

exception_nmi:
	push	m_02
	call	log
	iret

exception_bp:
	push	m_03
	call	log
	iret

exception_of:
	push	m_04
	call	log
	iret

exception_br:
	push	m_05
	call	log
	iret

exception_ud:
	push	m_06
	call	log
	iret

exception_nm:
	push	m_07
	call	log
	iret

exception_df:
	push	m_08
	call	log
	iret

exception_ts:
	push	m_09
	call	log
	iret

exception_np:
	push	m_10
	call	log
	iret

exception_ss:
	push	m_11
	call	log
	iret

exception_gp:
	call	gpcoolcool

	;mov	eax, [n]
	;cmp	eax, 8
	;je	.no

	;inc	eax
	;mov	[n], eax

	iret
.no
	hlt

exception_pf:
	push	m_13
	call	log
	iret

exception_mf:
	push	m_14
	call	log
	iret

exception_ac:
	push	m_15
	call	log
	iret

exception_mc:
	push	m_16
	call	log
	iret

exception_xf:
	push	m_17
	call	log
	iret

exception_cp:
	push	m_18
	call	log
	iret

exception_hv:
	push	m_19
	call	log
	iret

exception_vc:
	push	m_20
	call	log
	iret

exception_sx:
	push	m_21
	call	log
	iret

exception_other:
	push	m_22
	call	log
	iret

section .data
n:	db	0	; counter for GP
