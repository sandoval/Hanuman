; bloco de seleção da operação
INICIO:	input	OP	;12 69	-0
	load	OP	;10 69
	jmpz	FIM	;8  68
	sub	UM	;2  73
	jmpz	SOMA	;8  24
	sub	UM	;2  73
	jmpz	SUBS	;8  34
	sub	UM	;2  73
	jmpz	MULS	;8  44
	sub	UM	;2  73
	jmpz	DIVS	;8  54
	jmp	INICIO	;5  0
; operação de soma
SOMA:	input	M1	;12 70	-24
	input	M2	;12 71
	load	M1	;10 70
	add	M2	;1  71
	jmp	PRINT	;5  62
; operação de subtração
SUBS:	input	M1	;12 70	-34
	input	M2	;12 71
	load	M1	;10 70
	sub	M2	;2  71
	jmp	PRINT	;5  62
; operação de multiplicação
MULS:	input	M1	;12 70	-44
	input	M2	;12 71
	load	M1	;10 70
	mult	M2	;3  71
	jmp	PRINT	;5  62
; operação de divisão
DIVS:	input	M1	;12 70	-54
	input	M2	;12 71
	load	M1	;10 70
	div	M2	;4  71
PRINT:	store	RESULT	;11 72	-62
	output	RESULT	;13 72
	jmp	INICIO	;5  0
FIM:	stop		;14	-68
OP:	space		;0	-69
M1:	space		;0	-70
M2:	space		;0	-71
RESULT:	space		;0	-72
UM:	const	1	;1	-73