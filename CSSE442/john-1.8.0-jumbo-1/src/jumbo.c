/*
 * This file is part of John the Ripper password cracker.
 *
 * Some Jumbo-specific tweaks go here. This file must not introduce further
 * dependenices within the Jumbo tree. Use misc.[ho] for such things (the
 * latter depends on memory.o, logger.o and so on).
 *
 * This file is Copyright (c) 2013-2014 magnum, Lukasz and JimF,
 * and is hereby released to the general public under the following terms:
 * Redistribution and use in source and binary forms, with or without
 * modifications, are permitted.
 */

#include "jumbo.h"

#if HAVE_WINDOWS_H || _MSC_VER || __MINGW32__ || __MINGW64__ || __CYGWIN__
#include <windows.h>
#include <stdarg.h>
#endif

#if defined (__CYGWIN32__) && !defined(__CYGWIN64__)
#include <io.h>
#endif

#include "params.h"
#include "memory.h"
#include "memdbg.h"

/*
 * For used in jtr_basename_r function.  We need to handle separator chars
 * differently in unix vs Win32(DOS).
 */
#if defined _WIN32 || defined __WIN32__ || defined _MSC_VER || defined __DJGPP__ || defined __CYGWIN32__ || defined __MINGW32__
#define SEP_CHAR(c) ((c)=='/'||(c)=='\\')
#else
#define SEP_CHAR(c) ((c)=='/')
#endif


#ifdef _MSC_VER
// we will simply fix the broken _snprintf.  In VC, it will not null terminate buffers that get
// truncated, AND the return is - if we truncate.  We fix both of these issues, and bring snprintf
// for VC up to C99 standard.
int vc_fixed_snprintf(char *Dest, size_t max_cnt, const char *Fmt, ...) {
	va_list varg;
	int len;

	va_start(varg, Fmt);
	len = _vsnprintf(Dest, max_cnt, Fmt, varg);
	if (len < 0) {
		int len_now = max_cnt;
		Dest[max_cnt-1] = 0;
		// len = -1 right now.  We want to figure out exactly WHAT len should be, to stay C99 compliant.
		while (len < 0) {
			char *cp;
			len_now *= 2;
			cp = (char*)mem_alloc(len_now);
			len = _vsnprintf(cp, len_now, Fmt, varg);
			MEM_FREE(cp);
		}
	}
	va_end(varg);
	return len;
}
#endif

char *jtr_basename_r(const char *name, char *buf) {
	char *base, *p;
	int something=0;

	// if name was null, or the string was null, then return a '.' char.
	if (!name || name[0]==0) return ".";

	strcpy(buf, name);
	base = buf;

	// deal with 'possible' drive letter in Win32/DOS type systems.
#if defined _WIN32 || defined __WIN32__ || defined _MSC_VER || defined __DJGPP__ || defined __CYGWIN32__ || defined __MINGW32__
	if (strlen(base)>1 &&
	   ((base[0] >= 'A' && base[0] <= 'Z')||(base[0] >= 'a' && base[0] <= 'z')) &&
	   base[1] == ':')
		base += 2;
	if (base[0]==0) return ".";
#endif

	p = base;
	while (*p) {
		if (SEP_CHAR(*p)) {
			if (p[1] && !SEP_CHAR(p[1]))
				base = p+1;
		}
		else
			something = 1;
		++p;
	}
	if (!something) {
		base = &base[strlen(base)-1];
	} else if (strlen(base)) {
		p = &base[strlen(base)-1];
		while (SEP_CHAR(*p) && p >= base) {
			*p = 0;
			--p;
		}
		if (base[0]==0) return ".";
	}
	return (char*)base;
}

char *jtr_basename(const char *name) {
	static char buf[PATH_BUFFER_SIZE+1];
	return jtr_basename_r(name, buf);
}

char *strip_suffixes(const char *src, const char *suffixes[], int count)
{
	int i, suflen, retlen, done;
	static char ret[PATH_BUFFER_SIZE + 1];

	done = ret[0] = 0;
	if (src == NULL)
		return ret;

	strncat(ret, src, sizeof(ret) - 1);
	if (suffixes == NULL)
		return ret;

	while (done == 0) {
		done = 1;
		for (i = 0; i < count; i++) {
			if (!suffixes[i] || !*suffixes[i])
				continue;
			retlen = strlen(ret);
			suflen = strlen(suffixes[i]);
			if (retlen >= suflen && !strcmp(&ret[retlen - suflen], suffixes[i])) {
				ret[retlen - suflen] = 0;
				done = 0;
			}
		}
	}
	return ret;
}

#if !HAVE_MEMMEM
/* Return the first occurrence of NEEDLE in HAYSTACK.
   Faster implementation by Christian Thaeter <ct at pipapo dot org>
   http://sourceware.org/ml/libc-alpha/2007-12/msg00000.html
   LGPL 2.1+ */
void *memmem(const void *haystack, size_t haystack_len,
	     const void *needle, size_t needle_len)
{
	/* not really Rabin-Karp, just using additive hashing */
	char* haystack_ = (char*)haystack;
	char* needle_ = (char*)needle;
	int hash = 0;		/* static hash value of the needle */
	int hay_hash = 0;	/* rolling hash over the haystack */
	char* last;
	size_t i;

	if (haystack_len < needle_len)
		return NULL;

	if (!needle_len)
		return haystack_;

	/* initialize hashes */
	for (i = needle_len; i; --i)
	{
		hash += *needle_++;
		hay_hash += *haystack_++;
	}

	/* iterate over the haystack */
	haystack_ = (char*)haystack;
	needle_ = (char*)needle;
	last = haystack_+(haystack_len - needle_len + 1);
	for (; haystack_ < last; ++haystack_)
	{
		if (hash == hay_hash &&
		    *haystack_ == *needle_ &&	/* prevent calling memcmp */
		    !memcmp (haystack_, needle_, needle_len))
			return haystack_;

		/* roll the hash */
		hay_hash -= *haystack_;
		hay_hash += *(haystack_+needle_len);
	}

	return NULL;
}

#endif /* !HAVE_MEMMEM */

/* cygwin32 does not have fseeko64 or ftello64.  So I created them */
#if defined (__CYGWIN32__) && !defined(__CYGWIN64__)
int fseeko64 (FILE* fp, int64_t offset, int whence) {
  fpos_t pos;
  if (whence == SEEK_CUR)
    {
      /** If fp is invalid, fgetpos sets errno. */
      if (fgetpos (fp, &pos))
        return (-1);
      pos += (fpos_t) offset;
    }
  else if (whence == SEEK_END)
    {
      /** If writing, we need to flush before getting file length.  */
	  long long size;
      fflush (fp);
	  size = 0;
	  /* only way I could find to get file length, was to fall back to Win32 function */
	  /* I could find no _filelengthi64, _filelength64, etc. */
	  GetFileSizeEx((HANDLE)_get_osfhandle(fileno(fp)), (PLARGE_INTEGER)&size);
	  pos = (fpos_t) (size + offset);
	  //fprintf(stderr, "size = %lld\n", size);
    }
  else if (whence == SEEK_SET)
    pos = (fpos_t) offset;
  else
    {
      errno = EINVAL;
      return (-1);
    }
  return fsetpos (fp, &pos);
}

int64_t ftello64 (FILE * fp)
{
  fpos_t pos;
  if (fgetpos(fp, &pos))
    return  -1LL;
  return (int64_t)pos;
}
#endif

// We configure search for unix sleep(seconds) function, MSVC and MinGW do not have this,
// so we replicate it with Win32 Sleep(ms) function.
#if (AC_BUILT && !HAVE_SLEEP) || (!AC_BUILT && (_MSC_VER || __MINGW32__ || __MINGW64__))
int sleep(int i)
{
	Sleep(1000*i);
	return 0;
}
#endif

#if NEED_STRCASECMP_NATIVE
int strcasecmp(char *dst, char *src) {
    int f,l;
    do {
        if ( ((f = (unsigned char)(*(dst++))) >= 'A') && (f <= 'Z') )
            f -= 'A' - 'a';
        if ( ((l = (unsigned char)(*(src++))) >= 'A') && (l <= 'Z') )
            l -= 'A' - 'a';
    } while (f && (f==l));
    return return(f - l);
}
#endif

#if NEED_STRNCASECMP_NATIVE
int strncasecmp(char *dst, char *src, size_t count) {
    if(count) {
        int f,l;
        do {
            if ( ((f = (unsigned char)(*(dst++))) >= 'A') && (f <= 'Z') )
                f -= 'A' - 'a';
            if ( ((l = (unsigned char)(*(src++))) >= 'A') && (l <= 'Z') )
                l -= 'A' - 'a';
        }
        while (--count && f && (f == l));
        return (f - l);
    }
    return 0;
}
#endif

// NOTE there is an encoding-aware version in unicode.c: enc_strlwr(). That
// one should be used for usernames, plaintexts etc in formats.
#if (AC_BUILT && !HAVE_STRLWR) || (!AC_BUILT && !_MSC_VER)
char *strlwr(char *s)
{
	unsigned char *ptr = (unsigned char *)s;

	while (*ptr)
	if (*ptr >= 'A' && *ptr <= 'Z')
		*ptr++ |= 0x20;
	else
		ptr++;

	return s;
}
#endif

#if (AC_BUILT && !HAVE_STRUPR) || (!AC_BUILT && !_MSC_VER)
char *strupr(char *s)
{
	unsigned char *ptr = (unsigned char *)s;

	while (*ptr)
	if (*ptr >= 'a' && *ptr <= 'z')
		*ptr++ ^= 0x20;
	else
		ptr++;

	return s;
}
#endif

#if NEED_ATOLL_NATIVE
long long atoll(const char *s) {
	long long l;
	sscanf(s, "%lld", &l);
	return l;
}
#endif


#if (AC_BUILT && !HAVE_SETENV && HAVE_PUTENV) || \
    (!AC_BUILT && (_MSC_VER || __MINGW32__ || __MINGW64__))
int setenv(const char *name, const char *val, int overwrite) {
	int len;
	char *str;
	if (strchr(name, '=')) {
		errno = EINVAL;
		return -1;
	}
	if (!overwrite) {
		str = getenv(name);
		if (str)
			return 0;
	}
	len = strlen(name)+1+strlen(val)+1;
	str = mem_alloc_tiny(len, MEM_ALIGN_NONE);
	sprintf(str, "%s=%s", name, val);
	putenv(str);
	return 0;
}
#endif