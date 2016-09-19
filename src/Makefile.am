bin_PROGRAMS = fmnc

AM_LDFLAGS = `ncurses5-config --libs` `mariadb_config --libs`
AM_CFLAGS = -g -O0 `ncurses5-config --cflags` `mariadb_config --cflags`

fmnc_SOURCES =	main.c	\
		fmconfig.c \
		db.c

