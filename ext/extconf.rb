require 'mkmf'

$CFLAGS += ' -Wall '

if have_header('libmawk.h') and have_library('mawk')
  create_makefile('mawkc')
end
