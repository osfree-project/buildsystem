;
; start.asm:
; uFSD startup code
;

name start

extern  init:NEAR
public  fsd_init

include fsd.inc

.386

_TEXT    segment dword public 'CODE'  use32
_TEXT    ends
_DATA    segment dword public 'DATA'  use32
_DATA    ends
CONST    segment dword public 'DATA'  use32
CONST    ends
CONST2   segment dword public 'DATA'  use32
CONST2   ends
_BSS     segment dword public 'BSS'   use32
_BSS     ends

DGROUP   group _TEXT,_DATA,CONST,CONST2,_BSS

_TEXT    segment dword public 'CODE'  use32
         org EXT_BUF_BASE
fsd_init:
_TEXT    ends

         end fsd_init