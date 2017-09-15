bin_PROGRAMS = bswap
bswap_SOURCES = bswap.c
AM_CPPFLAGS = -D_GNU_SOURCE -std=gnu11 -Wall -Werror

install-exec-hook:
	cd $(DESTDIR)$(bindir) && \
	mv -f bswap$(EXEEXT) .bswap$(EXEEXT) && \
	$(LN_S) .bswap$(EXEEXT) bswap-16$(EXEEXT) && \
	$(LN_S) .bswap$(EXEEXT) bswap-32$(EXEEXT) && \
	$(LN_S) .bswap$(EXEEXT) bswap-64$(EXEEXT)
