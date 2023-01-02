# $Id: makefile,v 1.3 2004/08/16 04:51:55 prokushev Exp $

PROJ = hlldump
TRGT = $(PROJ).exe
DESC = Debug information dump facility
srcfiles = $(p)hll$(e) $(p)hlldirectory$(e) $(p)exe$(e) $(p)hllmodule$(e) $(p)hllpublics$(e) &
           $(p)hlllines$(e) $(p)hllsymbols$(e) $(p)hlltypes$(e)


!ifeq %OS OS2
defs = $(%WATCOM)$(SEP)h$(SEP)os2
!endif
!ifeq %OS WIN32
defs = $(%WATCOM)$(SEP)h$(SEP)nt
!endif
!ifeq %OS DOS
defs = $(%WATCOM)$(SEP)h$(SEP)dos
!endif
!ifeq %OS LINUX
defs = $(%WATCOM)$(SEP)lh
!endif

ADD_COPT = -i=$(defs) -i=$(%WATCOM)$(SEP)h$(SEP)os2
#          -i=$(%OS2TK)$(SEP)h &
#                      -i=$(%ROOT)$(SEP)build$(SEP)include$(SEP)shared

STACKSIZE = 65536

!include $(%ROOT)tools/mk/tools.mk