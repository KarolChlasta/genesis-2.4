/* ncconfig.h for Linux x86_64 — generated manually (configure cross-compile false positive) */
/* $Id: ncconfig.in,v 1.1.1.1 2005/06/14 04:38:32 svitak Exp $ */
#ifndef _NCCONFIG_H_
#define _NCCONFIG_H_

/* HP-UX: no */
/* #undef _HPUX_SOURCE */

/* char unsigned: no (gcc signed by default) */
/* #undef __CHAR_UNSIGNED__ */

/* struct stat has st_blksize: yes on Linux */
#define HAVE_ST_BLKSIZE 1

/* off_t is defined by sys/types.h */
/* #undef off_t */

/* size_t is defined by sys/types.h */
/* #undef size_t */

/* ANSI C headers: yes */
#define STDC_HEADERS 1

/* big-endian: no (x86_64 is little-endian) */
/* #undef WORDS_BIGENDIAN */

/* stdlib.h: present */
/* #undef NO_STDLIB_H */

/* sys/types.h: present */
/* #undef NO_SYS_TYPES_H */

/* ftruncate: present */
#define HAVE_FTRUNCATE 1

/* alloca as function/macro: yes */
#define HAVE_ALLOCA 1

/* alloca.h: present */
#define HAVE_ALLOCA_H 1

/* strerror: present */
/* #undef NO_STRERROR */

/* sizeof(size_t) = 8 on x86_64 */
#define SIZEOF_SIZE_T 8

/* sizeof(off_t) = 8 on x86_64 with _FILE_OFFSET_BITS=64 or 64-bit libc */
#define SIZEOF_OFF_T 8

/* ssize_t defined by system */
/* #undef ssize_t */

/* ptrdiff_t defined by system */
/* #undef ptrdiff_t */

/* uchar not defined on modern Linux */
#define uchar unsigned char

/* IEEE float: yes on x86_64 */
/* #undef NO_IEEE_FLOAT */

#define SIZEOF_DOUBLE 8
#define SIZEOF_FLOAT  4
#define SIZEOF_INT    4
#define SIZEOF_LONG   8
#define SIZEOF_SHORT  2

#endif /* !_NCCONFIG_H_ */
