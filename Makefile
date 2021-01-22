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
                  utf8.c \

OBJ             = $(SRC:.c=.o)
LIB             = minilib.a
SOLIB           = minilib.so

#D_CFLAGS = -DNDEBUG

CFLAGS         += $(D_CFLAGS) -fPIC -Wno-misleading-indentation -Werror

.c.o:
	./compile.sh $<
	
all: lib

ready-local: READYBANNER compile.sh makelib.sh makesolib.sh

lib: ready-local $(SOLIB) $(LIB) lib$(SOLIB) lib$(LIB)

$(LIB): BINBANNER $(OBJ)
	./makelib.sh $@ $(OBJ)

$(SOLIB): BINBANNER $(OBJ)
	./makesolib.sh $@ $(OBJ)

lib$(LIB): $(LIB)
	rm -f $@
	ln -s $(LIB) $@

lib$(SOLIB): $(SOLIB)
	rm -f $@
	ln -s $(SOLIB) $@


relib: lean libclean lib

rebin: binclean bin

remake: clean all

lean:
	rm -f core $(OBJ)

libclean:
	rm -f BINBANNER $(LIB) lib$(LIB) $(SOLIB) lib$(SOLIB)

clean: lean libclean readyclean

distclean: clean
	@echo ""
	@echo "note: distclean is the same as clean"

install:
	@echo "minilib: install me not."

