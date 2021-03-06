; Generated by holtek-gcc v3.14, Tue Jun 05 09:53:27 2018
; 
; Configuration:
;       without long instruction
;       Single ROM, Multi-RAM
;       bits_per_rom_unit:16
;       with mp1
;       with tbhp, address(0x9)
;          Use tabrd-const
;       
;       
;       
; use 'tabrdc' instead of 'tabrd'
;       

#pragma translator "holtek-gcc 4.6.4" "3.14" "build 20130711"
; Rebuild 10

ir equ [2]
mp equ [3]
sbp equ [1]
acc equ [5]
bp equ [4]
tblp equ [7]
tbhp equ [9]
status equ [10]
c equ [10].0
ac equ [10].1
z equ [10].2
ov equ [10].3
intc equ [11]

extern ra:byte
extern rb:byte
extern rc:byte
extern rd:byte
extern re:byte
extern rf:byte
extern rg:byte
extern rh:byte
extern _Crom2Prom:near
extern _Crom2PromNext:near

RAMBANK 0 @HCCINIT, @HCCINIT0

RAMBANK 0 @BITDATASEC, @BITDATASEC1
@HCCINIT	.section 'data'
@HCCINIT0	.section 'data'
@BITDATASEC	 .section 'data'
@BITDATASEC1	 .section 'data'

#pragma debug scope 1 1
	extern __DELAY3:near
	extern __DELAYX3:near
	extern __DELAYX6:near
	extern __DELAYY5:near
	extern __DELAYY3:near
	extern _builtin_holtek_delay_2:byte
___intc2 equ [16]
___intc0 equ [14]
public _UART_init
#pragma debug scope 2 1
#line 24 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
_UART_init .section 'code'
_UART_init proc
#line 26 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
	set [16].3
	set [86].7
	mov a,12
	mov [88],a
	mov a,196
	orm a,[87]
	set [14].0
#line 28 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
	clr _gu8Main_buf[0]
	clr _gu8Main_buf[1]
	clr _gu8Main_buf[2]
	clr _gu8Main_buf[3]
	clr _gu8Main_buf[4]
#line 29 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
	clr _gu8Buf_idx[0]
#line 30 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
	clr _gu8Buffer_ready[0]
#line 31 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
	clr _uart_signal[0]
	ret
_UART_init endp
#line 31 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
#pragma debug scope 1 1
public _UART_update
#pragma debug scope 3 1
#line 35 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
_UART_update .section 'code'
_UART_update proc
	ret
_UART_update endp
#line 35 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
#pragma debug scope 1 1
public _UART_getSignal
#pragma debug scope 4 1
#line 40 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
_UART_getSignal .section 'code'
_UART_getSignal proc
#line 41 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
	mov a,_uart_signal[0]
	mov ra,a
#line 42 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
	mov a,ra
	ret
_UART_getSignal endp
#line 42 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
#pragma debug scope 1 1
public _UART_setSignal
#pragma debug scope 5 1
#line 45 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
_UART_setSignal .section 'code'
_UART_setSignal proc
    local _UART_setSignal_2 db 1 dup(?)	; 0,1
	mov ra,a
#pragma debug variable 8 5 _UART_setSignal_2+0 "signal"
#line 46 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
	mov a,ra
	mov _uart_signal[0],a
	ret
_UART_setSignal endp
#line 46 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
#pragma debug scope 1 1
public _ISR_uart
#pragma debug scope 6 1
#line 53 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
@ISR_uart_code .section at 44 'code'
	mov r1,a
	mov a,bp
	mov r2,a
	jmp _ISR_uart
#pragma debug scope 1 1
@dummy44 proc
	call _ISR_uart
@dummy44 endp
#pragma debug scope 7 1
_ISR_uart .section 'code'
_ISR_uart proc
local _ISR_uart_2 db 1 dup(?)
	mov a,status
	mov r3,a
	mov a,mp
	mov r4,a
	mov a,sbp
	mov r5,a
#pragma debug variable 7 7 _ISR_uart_2+0 "data"
#line 56 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
	mov a,[89]
	mov _ISR_uart_2[0],a
#line 57 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
	sz _gu8Buffer_ready[0]
	jmp _L5
#line 59 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
	mov a,_gu8Buf_idx[0]
	mov ra,a
	inca ra
	mov _gu8Buf_idx[0],a
	mov a,low offset _gu8Main_buf
	add a,ra
	mov mp,a
	mov a,high offset _gu8Main_buf
	clr sbp
	adcm a,sbp
	mov a,sbp
	mov bp,a
	mov a,_ISR_uart_2[0]
	mov ir,a
#line 60 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
	mov a,_ISR_uart_2[0]
	sub a,10
	sz z
	jmp _L8
	sub a,(13)-(10)
	sz z
	jmp _L8
	mov a,_ISR_uart_2[0]
	mov ra,a
	mov a,_ISR_uart_2[0]
	mov ra,a
	mov a,3
	sub a,_gu8Buf_idx[0]
	sz c
	jmp _L5
_L8:
#line 62 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
	mov a,low (offset _gu8Main_buf-1)
	add a,_gu8Buf_idx[0]
	mov mp,a
	mov a,high (offset _gu8Main_buf-1)
	clr sbp
	adcm a,sbp
	mov a,sbp
	mov bp,a
	mov a,0
	mov ir,a
#line 63 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
	clr _gu8Buf_idx[0]
#line 64 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
	mov a,1
	mov _gu8Buffer_ready[0],a
_L5:
	mov a,r2
	mov bp,a
	mov a,r3
	mov status,a
	mov a,r4
	mov mp,a
	mov a,r5
	mov sbp,a
	mov a,r1
	reti
_ISR_uart endp

#line 64 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
#pragma debug scope 1 1
@HCCINIT0	.section	'data'
_uart_signal	db 0
#pragma debug variable 8 1 _uart_signal "uart_signal"

@HCCINIT .section 'data'
public _gu8Buffer_ready
@HCCINIT	.section 'data'
#line 20 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
@HCCINIT .section 'data'
_gu8Buffer_ready label byte
#pragma debug variable 8 1 _gu8Buffer_ready "gu8Buffer_ready"
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT .section 'data'
public _gu8Main_buf
#line 19 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
@HCCINIT .section 'data'
_gu8Main_buf label byte
#pragma debug array 42 8 5 1
#pragma debug variable 42 1 _gu8Main_buf "gu8Main_buf"
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT .section 'data'
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT .section 'data'
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT .section 'data'
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT .section 'data'
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT .section 'data'
public _gu8Buf_idx
#line 18 "E:\1_TOSHIBA\Projects\voltage_stabilizer\DataLoggerJig\proj\test_sd_READ\uart.c"
@HCCINIT .section 'data'
_gu8Buf_idx label byte
#pragma debug variable 8 1 _gu8Buf_idx "gu8Buf_idx"
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT .section 'data'
#pragma debug struct_begin 43 "__intc0_bits"
#pragma debug field 21 8 0 1 "__emi" ;0,1
#pragma debug field 21 8 0 1 "__int0e" ;1,1
#pragma debug field 21 8 0 1 "__cpe" ;2,1
#pragma debug field 21 8 0 1 "__mf0e" ;3,1
#pragma debug field 21 8 0 1 "__int0f" ;4,1
#pragma debug field 21 8 0 1 "__cpf" ;5,1
#pragma debug field 21 8 0 1 "__mf0f" ;6,1
#pragma debug field 21 8 0 1 ;7,1
#pragma debug struct_end
#pragma debug union_begin 44 ""
#pragma debug field 2 43 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 44 1 ___intc0 "__intc0" 1
#pragma debug struct_begin 45 "__intc2_bits"
#pragma debug field 21 8 0 1 "__tb1e" ;0,1
#pragma debug field 21 8 0 1 "__int1e" ;1,1
#pragma debug field 21 8 0 1 "__sime" ;2,1
#pragma debug field 21 8 0 1 "__ure" ;3,1
#pragma debug field 21 8 0 1 "__tb1f" ;4,1
#pragma debug field 21 8 0 1 "__int1f" ;5,1
#pragma debug field 21 8 0 1 "__simf" ;6,1
#pragma debug field 21 8 0 1 "__urf" ;7,1
#pragma debug struct_end
#pragma debug union_begin 46 ""
#pragma debug field 2 45 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 46 1 ___intc2 "__intc2" 1
extern r1:byte
extern r2:byte
extern r3:byte
extern r4:byte
extern r5:byte

; 
; Generated by holtek-gcc v3.14, Tue Jun 05 09:53:28 2018
; Rebuild 10
; end of file
