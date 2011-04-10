#ifndef __RUBY_MAWK_H__
#define __RUBY_MAWK_H__

#include <stdlib.h>
#include <libmawk.h>
#include <ruby.h>

#ifndef RSTRING_PTR
#define RSTRING_PTR(s) (RSTRING(s)->ptr)
#endif
#ifndef RSTRING_LEN
#define RSTRING_LEN(s) (RSTRING(s)->len)
#endif

struct mawk {
  mawk_state_t *m;
};

#endif // __RUBY_MAWK_H__
