DEFAULT: all
include ./Makefile.sets
include ./Makefile.ready
include ./Makefile.bin

SRC             = getseg.c \
                  die.c \
                  setnum.c \
                  strzero.c \
                  strset_ulong.c \
                  gather_input.c \
                  getarg.c \
                  dup_elem.c \
                  is_numeric.c \
                  file_is_sticky.c \
                  fork_pipefdout.c \
                  fork_passthru.c \
                  fork_passthru_wait.c \
                  get_sessionid.c \
                  sig_catch.c \
                  sig_block.c \
                  sig_misc.c \
                  exitstatus.c \
                  diestatus.c \

OBJ             = $(SRC:.c=.o)
LIB             = minilib.a

CFLAGS         += $(D_CFLAGS)

.c.o:
	./compile.sh $<
	
all: lib

ready-local: READYBANNER compile.sh makelib.sh

lib: ready-local $(LIB) lib$(LIB)

$(LIB): BINBANNER $(OBJ)
	./makelib.sh $@ $(OBJ)
#	$(AR) $@ $(OBJ)
#	$(RANLIB) $@

lib$(LIB): $(LIB)
	rm -f $@
	ln -s $(LIB) $@

relib: lean libclean lib

rebin: binclean bin

remake: clean all

lean:
	rm -f core $(OBJ)

libclean:
	rm -f BINBANNER $(LIB) lib$(LIB)

clean: lean libclean readyclean

distclean: clean
	@echo ""
	@echo "note: distclean is the same as clean"

install:
	@echo "minilib: install me not."

