DEFAULT: all
include ./Makefile.sets
include ./Makefile.ready
include ./Makefile.bin

SRC             = \
                  blob.c \
                  blobqueue.c \
                  die.c \
                  diestatus.c \
                  dup_elem.c \
                  exitstatus.c \
                  file_is_sticky.c \
                  fork_passthru.c \
                  fork_passthru_wait.c \
                  fork_pipefdout.c \
                  gather_input.c \
                  get_sessionid.c \
                  getarg.c \
		  getseg.c \
                  is_numeric.c \
                  setnum.c \
                  sig_block.c \
                  sig_catch.c \
                  sig_misc.c \
                  strset_ulong.c \
                  strzero.c \

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

