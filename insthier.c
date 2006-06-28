#include "install.h"

struct install_item insthier[] = {
  {IOP_MKDIR, 0, 0, "testtree", 0755, "markzero", "wheel"},
  {IOP_COPY, "bin.a", 0, "testtree", 0444, "markzero", "wheel"},
  {IOP_LIBLINK, "bin.a", "libbin.a", "testtree", 0444, "markzero", "wheel"},
  {IOP_COPY, "buffer.sld", 0, "testtree", 0444, "markzero", "wheel"},
  {IOP_COPY, "buffer.a", 0, "testtree", 0444, "markzero", "wheel"},
  {IOP_LIBLINK, "buffer.a", "libbuffer.a", "testtree", 0444, "markzero", "wheel"},
  {IOP_COPY, "error.sld", 0, "testtree", 0444, "markzero", "wheel"},
  {IOP_COPY, "error.a", 0, "testtree", 0444, "markzero", "wheel"},
  {IOP_LIBLINK, "error.a", "liberror.a", "testtree", 0444, "markzero", "wheel"},
  {IOP_COPY, "fmt.sld", 0, "testtree", 0444, "markzero", "wheel"},
  {IOP_COPY, "fmt.a", 0, "testtree", 0444, "markzero", "wheel"},
  {IOP_LIBLINK, "fmt.a", "libfmt.a", "testtree", 0444, "markzero", "wheel"},
  {IOP_COPY, "get_opt.sld", 0, "testtree", 0444, "markzero", "wheel"},
  {IOP_COPY, "get_opt.a", 0, "testtree", 0444, "markzero", "wheel"},
  {IOP_LIBLINK, "get_opt.a", "libget_opt.a", "testtree", 0444, "markzero", "wheel"},
  {IOP_COPY, "open.sld", 0, "testtree", 0444, "markzero", "wheel"},
  {IOP_COPY, "open.a", 0, "testtree", 0444, "markzero", "wheel"},
  {IOP_LIBLINK, "open.a", "libopen.a", "testtree", 0444, "markzero", "wheel"},
  {IOP_COPY, "str.sld", 0, "testtree", 0444, "markzero", "wheel"},
  {IOP_COPY, "str.a", 0, "testtree", 0444, "markzero", "wheel"},
  {IOP_LIBLINK, "str.a", "libstr.a", "testtree", 0444, "markzero", "wheel"},
  {IOP_COPY, "syserr.sld", 0, "testtree", 0444, "markzero", "wheel"},
  {IOP_COPY, "syserr.a", 0, "testtree", 0444, "markzero", "wheel"},
  {IOP_LIBLINK, "syserr.a", "libsyserr.a", "testtree", 0444, "markzero", "wheel"},
};
unsigned int insthier_size = sizeof(insthier) / sizeof(struct install_item);
