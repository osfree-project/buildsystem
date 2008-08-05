#
# Makefile for microFSD's and stage0.
# 07/10/04 valerius
#

#TARGETS          = minilibc.lib preldr0 preldr0_lite freeldr preldr0s &
#                   bt_linux bt_chain &
#                   console.trm hercules.trm serial.trm &
#                   console.trs hercules.trs serial.trs &
# preldr0.rel &
#                   console.rel hercules.rel serial.rel

#
# This is for this file to be not included twice
#
!ifneq _loader_mk_ 1
_loader_mk_ = 1

!include $(%ROOT)/mk/bootseq.mk
!include $(%ROOT)/mk/genrules.mk

all: install

install: build

build: prereq .SYMBOLIC
 @$(MAKE) $(MAKEOPT) -f $(mf) $(TARGETS)

SHIFT = 0x100

CLEANMASK    = $(CLEANMASK) *.sob *.lob

RIP          = $(REXX) ripzeroes.cmd
GENREL       = $(REXX) genrel.cmd

SO           = sob
LO           = lob

OUT          = bin
SOUT         = sbi
LOUT         = lbi

.SUFFIXES:
.SUFFIXES: .rel .trm .trs .fsd .fss .$(OUT) .$(LOUT) .$(SOUT) .lib .$(LO) .$(SO) .$(O) .c .asm .h .inc

BT_LINUX_OBJS    = linux.$(O) linuxc.$(O) modesw-npl.$(O) cmdline.$(O) &
                   wrap.$(O) end.$(O)
BT_CHAIN_OBJS    = chain.$(O) chainc.$(O) setdev.$(O) modesw-npc.$(O)  &
                   cmdline.$(O) wrap.$(O) end.$(O)

STAGE0_OBJS      = segord.$(O) init.$(O) modesw.$(O) asmcode.$(O) apm.$(O) biosdisk.$(O) filesys.$(O) &
                   video.$(O) vbe.$(O) common.$(O) stage0_fs.$(O) func.$(O) setdev.$(O) cmdline.$(O)  &
                   dskaccess.$(O) part.$(O) cfgparse.$(O) idt.$(O) bios.$(O) end.$(O)

STAGE0_SH_OBJS   = segord.$(SO) init.$(SO) modesw.$(SO) asmcode.$(SO) apm.$(SO) biosdisk.$(SO) filesys.$(SO) &
                   video.$(SO) vbe.$(SO) common.$(SO) stage0_fs.$(SO) func.$(SO) setdev.$(SO) cmdline.$(SO) &
                   dskaccess.$(SO) part.$(SO) cfgparse.$(SO) idt.$(SO) bios.$(SO) end.$(SO)

STAGE0_LT_OBJS   = segord.$(LO) init.$(LO) modesw.$(LO) asmcode.$(LO) apm.$(LO) biosdisk.$(LO) filesys.$(LO) &
                   dskaccess.$(LO) part.$(LO) video.$(LO) common.$(LO) stage0_fs.$(LO) func.$(LO) setdev.$(O) bios.$(LO) end.$(LO)

CONSOLE_OBJS     = termstrt.$(O) terminit-c.$(O) console-c.$(O) modesw-npt.$(O) consolec.$(O)
CONSOLE_SH_OBJS  = termstrt.$(SO) terminit-c.$(SO) console-c.$(SO) modesw-npt.$(SO) consolec.$(SO)
HERCULES_OBJS    = termstrt.$(O) terminit-h.$(O) hercules.$(O) console.$(O) modesw-npt.$(O)
HERCULES_SH_OBJS = termstrt.$(SO) terminit-h.$(SO) hercules.$(SO) console.$(SO) modesw-npt.$(SO)
SERIAL_OBJS      = termstrt.$(O) terminit-s.$(O) serial.$(O) modesw-npt.$(O) terminfo.$(O) tparm.$(O)
SERIAL_SH_OBJS   = termstrt.$(SO) terminit-s.$(SO) serial.$(SO) modesw-npt.$(SO) terminfo.$(SO) tparm.$(SO)

LDR_OBJS         = ldrstart.$(O) loader.$(O) wrap.$(O) commands.$(O) &
                   boot.$(O) cmdline.$(O) cfgparse-l.$(O) #varsubst.$(O)

!ifneq PATH ""
PATH = $(BLD)$(PATH)
!endif

#
# Substitute '$$' in file names to full paths or ''
#
#FAT_OBJS = $(FAT_OBJS:$$=$(PATH))

#prereq: .SYMBOLIC
# @$(MAKE) $(MAKEOPT) TARGET=all subdirs

console.rel: console.trm console.trs

hercules.rel: hercules.trm hercules.trs

serial.rel: serial.trm serial.trs

preldr0.rel: preldr0 preldr0s

$(PATH)fat.rel: $(PATH)fat.fsd $(PATH)fat.fss

$(PATH)ext2fs.rel: $(PATH)ext2fs.fsd $(PATH)ext2fs.fss

$(PATH)jfs.rel: $(PATH)jfs.fsd $(PATH)jfs.fss

$(PATH)ffs.rel: $(PATH)ffs.fsd $(PATH)ffs.fss

$(PATH)vstafs.rel: $(PATH)vstafs.fsd $(PATH)vstafs.fss

$(PATH)ufs2.rel: $(PATH)ufs2.fsd $(PATH)ufs2.fss

$(PATH)xfs.rel: $(PATH)xfs.fsd $(PATH)xfs.fss

$(PATH)reiserfs.rel: $(PATH)reiserfs.fsd $(PATH)reiserfs.fss

$(PATH)iso9660.rel: $(PATH)iso9660.fsd $(PATH)iso9660.fss

$(PATH)minix.rel: $(PATH)minix.fsd $(PATH)minix.fss


$(PATH)fat.fsd: $(PATH)fat.$(OUT)

$(PATH)ext2fs.fsd: $(PATH)ext2fs.$(OUT)

$(PATH)jfs.fsd: $(PATH)jfs.$(OUT)

$(PATH)ffs.fsd: $(PATH)ffs.$(OUT)

$(PATH)vstafs.fsd: $(PATH)vstafs.$(OUT)

$(PATH)ufs2.fsd: $(PATH)ufs2.$(OUT)

$(PATH)xfs.fsd: $(PATH)xfs.$(OUT)

$(PATH)reiserfs.fsd: $(PATH)reiserfs.$(OUT)

$(PATH)iso9660.fsd: $(PATH)iso9660.$(OUT)

$(PATH)minix.fsd: $(PATH)minix.$(OUT)


$(PATH)fat.fss: $(PATH)fat.$(SOUT)

$(PATH)ext2fs.fss: $(PATH)ext2fs.$(SOUT)

$(PATH)jfs.fss: $(PATH)jfs.$(SOUT)

$(PATH)ffs.fss: $(PATH)ffs.$(SOUT)

$(PATH)vstafs.fss: $(PATH)vstafs.$(SOUT)

$(PATH)ufs2.fss: $(PATH)ufs2.$(SOUT)

$(PATH)xfs.fss: $(PATH)xfs.$(SOUT)

$(PATH)reiserfs.fss: $(PATH)reiserfs.$(SOUT)

$(PATH)iso9660.fss: $(PATH)iso9660.$(SOUT)

$(PATH)minix.fss: $(PATH)minix.$(SOUT)

#.trm: $(PATH)

.fsd: $(PATH)

.fss: $(PATH)

.$(OUT):  $(PATH)

.$(SOUT): $(PATH)

#.trm.rel
# $(GENREL) $^&.trm $^&.trs $(SHIFT) >$^@
# $(DC) $[*.trs

preldr0.rel: preldr0
 $(GENREL) $^& $^&s $(SHIFT) >$^@
 $(DC) $[*s

.fsd.rel
 $(GENREL) $[*.fsd $[*.fss $(SHIFT) >$^@
 $(DC) $[*.fss

bt_linux: bt_linux.$(OUT)
 $(DC) $^@
 $(RIP) $< KERN_BASE $(MYDIR)..$(SEP)include$(SEP)mb_etc.inc >$^@
 $(DC) $<

bt_chain: bt_chain.$(OUT)
 $(DC) $^@
 $(RIP) $< KERN_BASE $(MYDIR)..$(SEP)include$(SEP)mb_etc.inc >$^@
 $(DC) $<

.$(OUT).trm:
 $(DC) $^@
 $(RIP) $< EXT_BUF_BASE $(MYDIR)..$(SEP)include$(SEP)fsd.inc >$^@
 $(DC) $<

.$(SOUT).trs:
 $(DC) $^@
 $(RIP) $< EXT_BUF_BASE $(MYDIR)..$(SEP)include$(SEP)fsd.inc $(SHIFT) >$^@
 $(DC) $<

.$(OUT).fsd:
 $(DC) $^@
 $(RIP) $[@ EXT_BUF_BASE $(MYDIR)..$(SEP)include$(SEP)fsd.inc >$^@
 $(DC) $[@

.$(SOUT).fss:
 $(DC) $^@
 $(RIP) $[@ EXT_BUF_BASE $(MYDIR)..$(SEP)include$(SEP)fsd.inc $(SHIFT) >$^@
 $(DC) $[@

preldr0: stage0.$(OUT)
 $(DC) $^@
 $(RIP) $< STAGE0_BASE $(MYDIR)..$(SEP)include$(SEP)fsd.inc >$^@
 $(DC) $<

preldr0_lite: stage0.$(LOUT)
 $(DC) $^@
 $(RIP) $< STAGE0_BASE $(MYDIR)..$(SEP)include$(SEP)fsd.inc >$^@
 $(DC) $<

preldr0s: stage0.$(SOUT)
 $(DC) $^@
 $(RIP) $< STAGE0_BASE $(MYDIR)..$(SEP)include$(SEP)fsd.inc $(SHIFT) >$^@
 $(DC) $<

freeldr: freeldr.$(OUT)
 $(DC) $^@
 $(RIP) $< LDR_BASE $(MYDIR)..$(SEP)include$(SEP)fsd.inc >$^@
 $(DC) $<

bt_linux.$(OUT): $(BT_LINUX_OBJS)
 $(MAKE) $(MAKEOPT) T=$^& S="" E=$(OUT) OBJS="$<" link

bt_chain.$(OUT): $(BT_CHAIN_OBJS)
 $(MAKE) $(MAKEOPT) T=$^& S="" E=$(OUT) OBJS="$<" link

freeldr.$(OUT): $(LDR_OBJS)
 $(MAKE) $(MAKEOPT) T=$^& S="" E=$(OUT) OBJS="$<" link

console.$(OUT): $(CONSOLE_OBJS)
 $(MAKE) $(MAKEOPT) T=$^& S="" E=$(OUT) OBJS="$<" link

console.$(SOUT): $(CONSOLE_SH_OBJS)
 $(MAKE) $(MAKEOPT) T=$^& S="s" E=$(SOUT) OBJS="$<" link

hercules.$(OUT): $(HERCULES_OBJS)
 $(MAKE) $(MAKEOPT) T=$^& S="" E=$(OUT) OBJS="$<" link

hercules.$(SOUT): $(HERCULES_SH_OBJS)
 $(MAKE) $(MAKEOPT) T=$^& S="s" E=$(SOUT) OBJS="$<" link

serial.$(OUT): $(SERIAL_OBJS)
 $(MAKE) $(MAKEOPT) T=$^& S="" E=$(OUT) OBJS="$<" link

serial.$(SOUT): $(SERIAL_SH_OBJS)
 $(MAKE) $(MAKEOPT) T=$^& S="s" E=$(SOUT) OBJS="$<" link

stage0.$(OUT): $(STAGE0_OBJS)
 $(MAKE) $(MAKEOPT) T=$^& S="" E=$(OUT) OBJS="$<" link

stage0.$(LOUT): $(STAGE0_LT_OBJS)
 $(MAKE) $(MAKEOPT) T=$^& S="l" E=$(LOUT) OBJS="$<" link

stage0.$(SOUT): $(STAGE0_SH_OBJS)
 $(MAKE) $(MAKEOPT) T=$^& S="s" E=$(SOUT) OBJS="$<" link

link: $(PATH)$(T)$(S).lnk .SYMBOLIC .PROCEDURE
 $(SAY) Linking $< $(LOG)
 $(LINKER) @$< $(LOG)

$(PATH)$(T)$(S).lnk: .SYMBOLIC
 @%create $^@
 @%append $^@ system os2v2
 @%append $^@ output raw offset=0x10000
 @%append $^@ OPTION QUIET
 @%append $^@ OPTION MAP=$^*.wmp
 @%append $^@ OPTION NODEFAULTLIBS
 @%append $^@ NAME $(PATH)$(T).$(E)
 @%append $^@ ALIAS init=_init
!ifneq T stage0
!ifeq FS 1
 @%append $^@ ALIAS fs_mount_=$(T)_mount_
 @%append $^@ ALIAS fs_dir_=$(T)_dir_
 @%append $^@ ALIAS fs_read_=$(T)_read_
!else
 @%append $^@ ALIAS _init=init_
 @%append $^@ ALIAS cmain=cmain_
!endif
!else
 @%append $^@ ALIAS mem_lower=_mem_lower
 @%append $^@ ALIAS _biosdisk_int13_extensions=biosdisk_int13_extensions
 @%append $^@ ALIAS _biosdisk_standard=biosdisk_standard
 @%append $^@ ALIAS _check_int13_extensions=check_int13_extensions
 @%append $^@ ALIAS _get_diskinfo_standard=get_diskinfo_standard
!endif
 @%append $^@ LIBPATH $(PATH)..$(SEP)minilibc
 @%append $^@ LIBRARY minilibc.lib
 @for %%i in ($(OBJS)) do @%append $^@ FILE %%i

.c:   $(MYDIR)

.asm: $(MYDIR)

func.$(O): func.c
 $(CC) -dSTAGE0 -dSHIFT=0 $(COPT) -fr=$^& -fo=$^@ $<

func.$(LO): func.c
 $(CC) -dSTAGE0 -dSHIFT=0 -dSTAGE1_5 -dNO_BLOCK_FILES $(COPT) -fr=$^& -fo=$^@ $<

func.$(SO): func.c
 $(CC) -dSTAGE0 -dSHIFT=$(SHIFT) $(COPT) -fr=$^& -fo=$^@ $<

modesw-npl.$(O): modesw.asm
 $(ASM) -dNO_PROT -dREAL_BASE=0x8000 -dSHIFT=0 $(ASMOPT) -fr=$^& -fo=$^@ $<

linux.$(O): linux.asm
 $(ASM) -dSHIFT=0 -dREAL_BASE=0x8000 $(ASMOPT) -fr=$^& -fo=$^@ $<

modesw-npc.$(O): modesw.asm
 $(ASM) -dNO_PROT -dREAL_BASE=0x90000 -dSHIFT=0 $(ASMOPT) -fr=$^& -fo=$^@ $<

chain.$(O): chain.asm
 $(ASM) -dSHIFT=0 -dREAL_BASE=0x90000 $(ASMOPT) -fr=$^& -fo=$^@ $<

modesw-npt.$(O): modesw.asm
 $(ASM) -dNO_PROT -dBLACKBOX -dSHIFT=0 $(ASMOPT) -fr=$^& -fo=$^@ $<

modesw-npt.$(SO): modesw.asm
 $(ASM) -dNO_PROT -dBLACKBOX -dSHIFT=$(SHIFT) $(ASMOPT) -fr=$^& -fo=$^@ $<

cfgparse-l.$(O): cfgparse.c
 $(CC) -dLOADER $(COPT) -fr=$^& -fo=$^@ $<

cfgparse.$(O): cfgparse.c

terminit-c.$(O): terminit.c
 $(CC) -dSHIFT=0 -dTERM_CONSOLE $(COPT) -fr=$^& -fo=$^@ $<

terminit-c.$(SO): terminit.c
 $(CC) -dSHIFT=$(SHIFT) -dTERM_CONSOLE $(COPT) -fr=$^& -fo=$^@ $<

terminit-h.$(O): terminit.c
 $(CC) -dSHIFT=0 -dTERM_HERCULES $(COPT) -fr=$^& -fo=$^@ $<

terminit-h.$(SO): terminit.c
 $(CC) -dSHIFT=$(SHIFT) -dTERM_HERCULES $(COPT) -fr=$^& -fo=$^@ $<

terminit-s.$(O): terminit.c
 $(CC) -dSHIFT=0 -dTERM_SERIAL $(COPT) -fr=$^& -fo=$^@ $<

terminit-s.$(SO): terminit.c
 $(CC) -dSHIFT=$(SHIFT) -dTERM_SERIAL $(COPT) -fr=$^& -fo=$^@ $<

console-c.$(O): console.asm
 $(ASM) -dSHIFT=0 -dTERM_CONSOLE $(ASMOPT) -fr=$^& -fo=$^@ $<

console-c.$(SO): console.asm
 $(ASM) -dSHIFT=$(SHIFT) -dTERM_CONSOLE $(ASMOPT) -fr=$^& -fo=$^@ $<

.c.$(O):
 $(CC) -dSHIFT=0 $(COPT) -fr=$^&.err -fo=$^@ $<

.c.$(LO):
 $(CC) -dSHIFT=0 -dSTAGE1_5 -dNO_BLOCK_FILES $(COPT) -fr=$^&.err -fo=$^@ $<

.c.$(SO):
 $(CC) -dSHIFT=$(SHIFT) $(COPT) -fr=$^&.err -fo=$^@ $<

.asm.$(O):
 $(ASM) -dSHIFT=0 $(ASMOPT) -fr=$^&.err -fo=$^@ $<

.asm.$(LO):
 $(ASM) -dSHIFT=0 -dSTAGE1_5 -dNO_BLOCK_FILES $(ASMOPT) -fr=$^&.err -fo=$^@ $<

.asm.$(SO):
 $(ASM) -dSHIFT=$(SHIFT) $(ASMOPT) -fr=$^&.err -fo=$^@ $<

.inc.h:
 $(AWK) -f inc2h.awk <$< >$^@

install: .SYMBOLIC
 $(SAY) Making install... $(LOG)
 @$(MDHIER) $(FILESDIR)$(SEP)boot
 @for %i in ($(PROJ)) do @if exist %i $(CP) %i $(FILESDIR)$(SEP)boot

.IGNORE
clean: .SYMBOLIC
 $(SAY) Making clean... $(LOG)
 $(CLEAN_CMD)
 $(DC) $(TARGETS)
 $(MAKE) $(MAKEOPT) TARGET=$^@ subdirs

!endif