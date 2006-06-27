#include "../install.h"

struct install_item insthier[] = {
  {IOP_MKDIR,0,0,"/usr/lib",0755,"root","wheel"},
  {IOP_COPY,"files/file.lib",0,"/usr/lib",0444,"root","wheel"},
  {IOP_COPY,"files/xyz.a",0,"/usr/lib",0444,"root","wheel"},
  {IOP_LIBLINK,"files/file.lib","libfile.lib","/usr/lib",0444,"root","wheel"},
  {IOP_LIBLINK,"files/xyz.a","libxyz.a","/usr/lib",0444,"root","wheel"},
  {IOP_LINK,"/usr/lib","/testlib",0,0755,"root","wheel"},
  {IOP_COPY,"nonexistant",0,"/usr/lib", 0444,"root", "wheel"},
  {IOP_COPY,"nonexistant",0,0,0444,"root","wheel"},
  {IOP_COPY,0,"to","/usr/lib",0444,"root","wheel"},
  {IOP_COPY,0,0,0,0,0,0},
  {IOP_COPY,0,"to","/usr/lib",0444,0,0},
  {IOP_COPY,0,"to","/usr/lib",0444,"root",0},
  {IOP_COPY,"file","file2","dir",0444,"1234XNOBODYx123","1234XNOBODYx123"},
};

unsigned int insthier_size = sizeof(insthier) / sizeof(struct install_item);
