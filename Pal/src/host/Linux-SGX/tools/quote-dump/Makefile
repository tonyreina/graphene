include ../../../../../../Scripts/Makefile.configs
include ../../../../../../Scripts/Makefile.rules

CFLAGS += -I../.. \
          -I../common \
          -L../common \
          -L../../../../../lib/crypto/mbedtls/install/lib \
          -D_GNU_SOURCE

LDLIBS += -lsgx_util -lmbedcrypto

PREFIX ?= /usr/local

.PHONY: all
all: quote_dump

quote_dump: quote_dump.o
	$(call cmd,csingle)

.PHONY: install
install:
	install -D quote_dump -t ${PREFIX}/bin

.PHONY: clean
clean:
	$(RM) *.o quote_dump

.PHONY: distclean
distclean: clean
