/* Matija Nalis, mnalis-libfakeaccess@voyager.hr, 2014 released under LGPLv3+ */

/* fake access(2) check for "/", W_OK to return "false" always.

   Use it to implement "allow_writable_root=YES"
   by doing "LD_PRELOAD=/usr/local/lib/libfakeaccess.so vsftpd"
   
   v1.0, 2014-02-15
*/


#define _GNU_SOURCE
#include <sys/stat.h>
#include <errno.h>
#include <dlfcn.h>
#include <string.h>
#include <unistd.h>


int access(const char *pathname, int mode)
{
  int (*libc_access)(const char *pathpath, int mode);
  *(void **)(&libc_access) = dlsym(RTLD_NEXT, "access");
  if(dlerror()) {
    errno = EPERM;
    return -1;
  }

  if (strcmp(pathname, "/")==0) {
    if (mode == W_OK) {
      errno = EPERM;
      return -1;
    }
  }
  
  return (*libc_access)(pathname, mode);
}
