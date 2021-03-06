#include "ruby-mawk.h"

static VALUE rb_cMAWK;
static VALUE rb_eMAWKError;

static void rb_mawk_free(struct mawk *p) {
  xfree(p);
}

static VALUE rb_mawk_alloc(VALUE klass) {
  struct mawk *p = ALLOC(struct mawk);
  return Data_Wrap_Struct(klass, 0, rb_mawk_free, p);
}

static VALUE rd_mawk_initialize(VALUE self, VALUE script) {
  struct mawk *p;
  int argc = 2;
  char *argv[] = {"awk", StringValuePtr(script)};

  Data_Get_Struct(self, struct mawk, p);

  p->m = libmawk_initialize_stage1(argc, argv);

  if (p->m == NULL) {
    rb_raise(rb_eMAWKError, "Init failed");
  }

  p->m = libmawk_initialize_stage2(p->m);

  if (p->m->compile_error_count != 0) {
    libmawk_uninitialize(p->m);
    rb_raise(rb_eMAWKError, "Compile error");
  }

  if (p->m->do_exit) {
    libmawk_uninitialize(p->m);
    rb_raise(rb_eMAWKError, "Do exit");
  }

  p->m = libmawk_initialize_stage3(p->m);

  return Qnil;
}

static VALUE rd_mawk_uninitialize(VALUE self) {
  struct mawk *p;

  Data_Get_Struct(self, struct mawk, p);
  libmawk_uninitialize(p->m);

  return Qnil;
}

static VALUE rd_mawk_append_input(VALUE self, VALUE input) {
  struct mawk *p;

  Data_Get_Struct(self, struct mawk, p);
  libmawk_append_input(p->m, StringValuePtr(input));

  return Qnil;
}

static VALUE rd_mawk_run_main(VALUE self) {
  struct mawk *p;

  Data_Get_Struct(self, struct mawk, p);
  libmawk_run_main(p->m);

  return Qnil;
}

void Init_mawkc() {
  rb_cMAWK = rb_define_class("MAWK", rb_cObject);
  rb_define_alloc_func(rb_cMAWK, rb_mawk_alloc);
  rb_define_private_method(rb_cMAWK, "initialize", rd_mawk_initialize, 1);
  rb_define_method(rb_cMAWK, "uninitialize", rd_mawk_uninitialize, 0);
  rb_define_method(rb_cMAWK, "append_input", rd_mawk_append_input, 1);
  rb_define_method(rb_cMAWK, "<<", rd_mawk_append_input, 1);
  rb_define_method(rb_cMAWK, "run_main", rd_mawk_run_main, 0);

  rb_eMAWKError = rb_define_class_under(rb_cMAWK, "Error", rb_eStandardError);
}
