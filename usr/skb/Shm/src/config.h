#define NULL ((void *)0)
/* Shm/x86_64_linux/config.h.  Generated by configure.  */
/* config.h.in.  Generated automatically from configure.in by autoheader.  */

/* Define if you have a working `mmap' system call.  */
//#define HAVE_MMAP 0

/* Define to `long' if <sys/types.h> doesn't define.  */
/* #undef off_t */

/* Define if you have the ANSI C header files.  */
#define STDC_HEADERS 1

/* PATH_MAX is declared in limits.h */
#define PATH_IN_LIMITS 1

/* memcpy() is declared in string.h */
#define MEMCPY_STRING 1

/* memcpy() is declared in memory.h */
/* #undef MEMCPY_MEMORY */

/* sbrk() is not declared */
/* #undef SBRK_UNDEF */

/* compiler doesn't understand void pointers */
/* #undef HAVE_NO_VOID_PTR */

#ifdef __x86_64__
#       define SIZEOF_INT 4
#       define SIZEOF_LONG 8
#       define SIZEOF_CHAR_P 8
#elif defined(__i386__) || defined(__arm__)
#       define SIZEOF_INT 4
#       define SIZEOF_LONG 4
#       define SIZEOF_CHAR_P 4
#else
#       error Unknown architecture
#endif

/* Define if you have the <fcntl.h> header file.  */
//#define HAVE_FCNTL_H 1

/* Define if you have the <limits.h> header file.  */
#define HAVE_LIMITS_H 1

/* Define if you have the <stdlib.h> header file.  */
#define HAVE_STDLIB_H 1

/* Define if you have the <string.h> header file.  */
#define HAVE_STRING_H 1

/* Define if you have the <windos.h> header file.  */
/* #undef HAVE_WINDOWS_H */

/* Define if you have the <unistd.h> header file.  */
#define HAVE_UNISTD_H 1

/* Define if SVR4.  */
/* #undef SVR4 */
