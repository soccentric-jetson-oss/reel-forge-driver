#include "libreel-forge.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#define REEL_FORGE_MAGIC 0x52
#define REEL_FORGE_IOCTL_START_ENCODE  _IOW(REEL_FORGE_MAGIC, 1, uint32_t[6])
#define REEL_FORGE_IOCTL_STOP_ENCODE   _IO(REEL_FORGE_MAGIC, 2)
#define REEL_FORGE_IOCTL_START_DECODE  _IOW(REEL_FORGE_MAGIC, 3, uint32_t[3])
#define REEL_FORGE_IOCTL_STOP_DECODE   _IO(REEL_FORGE_MAGIC, 4)

struct reel_forge_handle { int fd; };

struct reel_forge_handle *reel_forge_open(const char *path) {
    if(!path){errno=EINVAL;return NULL;}
    int fd=open(path,O_RDWR); if(fd<0)return NULL;
    struct reel_forge_handle *h=calloc(1,sizeof(*h)); if(!h){close(fd);return NULL;}
    h->fd=fd; return h;
}
void reel_forge_close(struct reel_forge_handle *h){if(!h)return;close(h->fd);free(h);}
int reel_forge_start_encode(struct reel_forge_handle *h, uint32_t codec, uint32_t w, uint32_t h_, uint32_t bitrate, uint32_t fps){
    if(!h)return -EINVAL; uint32_t a[6]={codec,w,h_,bitrate,fps,0};
    int r=ioctl(h->fd,REEL_FORGE_IOCTL_START_ENCODE,a); return r<0?-errno:0;
}
int reel_forge_stop_encode(struct reel_forge_handle *h){if(!h)return -EINVAL;int r=ioctl(h->fd,REEL_FORGE_IOCTL_STOP_ENCODE);return r<0?-errno:0;}
int reel_forge_start_decode(struct reel_forge_handle *h, uint32_t codec, uint32_t w, uint32_t h_){
    if(!h)return -EINVAL; uint32_t a[3]={codec,w,h_};
    int r=ioctl(h->fd,REEL_FORGE_IOCTL_START_DECODE,a); return r<0?-errno:0;
}
int reel_forge_stop_decode(struct reel_forge_handle *h){if(!h)return -EINVAL;int r=ioctl(h->fd,REEL_FORGE_IOCTL_STOP_DECODE);return r<0?-errno:0;}
const char *reel_forge_strerror(int e){switch(e){case 0:return "OK";case -EINVAL:return "EINVAL";default:return strerror(-e);}}
