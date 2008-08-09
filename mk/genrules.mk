#
# Generate autogenerated rules
# a little black magic, but allows
# to not each time manually insert many
# similar rules, like dependencies etc.
#
# (c) osFree project
# valerius, 2008 Jul 31
#

mf = $(PATH)makefile

prereq: dirhier $(mf) .SYMBOLIC
 $(SAY) prereqs made...

$(mf): $(MYDIR)makefile
 @%create $(mf)
 @%append $(mf) $#
 @%append $(mf) $# This is auto-generated file,
 @%append $(mf) $# don't edit!
 @%append $(mf) $#
 @%append $(mf)
 @%append $(mf) !include $(MYDIR)makefile
 @%append $(mf)
 # generate ordinary .obj's lists
 @for %i in ($(files)) do @$(MAKE) $(MAKEOPT) basename=%i sh= e=.$$$$$$$$(O) p=$$$$$$$$(PATH) gen_obj_defs
 # generate shifted  .obj's lists
 @for %i in ($(files)) do @$(MAKE) $(MAKEOPT) basename=%i sh=_sh e=.$$$$$$$$(SO) p=$$$$$$$$(PATH) gen_obj_defs
 # generate ordinary files link rules
 @for %i in ($(files)) do @$(MAKE) $(MAKEOPT) basename=%i sh= S= E=$$$$(OUT) gen_link_rules
 # generate shifted  files link rules
 @for %i in ($(files)) do @$(MAKE) $(MAKEOPT) basename=%i sh=_sh S=s E=$$$$(SOUT) gen_link_rules
 # generate compile rules for ordinary files
 @for %i in ($(spec_SRCS)) do @$(MAKE) $(MAKEOPT) file=%i sh=    gen_compile_rules_wrapper
 # generate compile rules for shifted files
 @for %i in ($(spec_SRCS)) do @$(MAKE) $(MAKEOPT) file=%i sh=sh_ gen_compile_rules_wrapper
 # generate dependencies
 @$(MAKE) $(MAKEOPT) gen_deps_wrapper

gen_obj_defs: .SYMBOLIC
 @%append $(mf) $(basename)$(sh)_OBJS      = $+$(OBJS)$-
 @%append $(mf)

gen_link_rules: .SYMBOLIC
 @%append $(mf) $$(PATH)$(basename).$(E): $$($(basename)$(sh)_OBJS)
 @%append $(mf)  @$$(MAKE) $$(MAKEOPT) T=$$^& S="$(S)" E=$(E) OBJS="$$<" FS=$(F) link
 @%append $(mf)

gen_compile_rules: .SYMBOLIC
 @%append $(mf) $$(PATH)$(file:$(ext)=$(e)): $$(MYDIR)$(file)
 @%append $(mf)  $$(SAY) Compiling $$(MYDIR)$(file)...
!ifeq ext .c     # if file extension is .c
 @%append $(mf)  $$(CC)  $(defs) $$(COPT) -fr=$$^*.err -fo=$$^@ $$<
!else
!ifeq ext .asm   # if file extension is .asm
 @%append $(mf)  $$(ASM) $(defs) $$(ASMOPT) -fr=$$^*.err -fo=$$^@ $$<
!endif
!endif
 @%append $(mf)

gen_deps: .SYMBOLIC
 @%append $(mf) $(trgt): $(deps)
 @%append $(mf)

#
# gen_compile_rules_wrapper must be defined in makefile,
# it calls gen_compile_rules from this file with proper
# parameters:
#
# file:   source file name
# ext:    its extension: .c, .asm or another
# e:      object file extension
# defs:   additional defines
#
# for example:
#
#gen_compile_rules_wrapper: $(MYDIR)$(file) .SYMBOLIC
#!ifeq sh
# @$(MAKE) $(MAKEOPT) file=$[. ext=$(file:$[&=) e=.$$$$$$$$(O) defs="-d$[& -dSHIFT=0" gen_compile_rules
#!else
# @$(MAKE) $(MAKEOPT) file=$[. ext=$(file:$[&=) e=.$$$$$$$$(SO) defs="-d$[& -dSHIFT=$$$$(SHIFT)" gen_compile_rules
#!endif
#
# where if sh is empty, then ordinary rule is generated;
# if sh=sh_ then a rule for shifted file is generated.
# A shifted file is a file linked at the base + $(SHIFT)
# it is used for relocation files generation.
#
