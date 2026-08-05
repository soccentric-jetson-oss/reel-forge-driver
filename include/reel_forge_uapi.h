#ifndef REEL_FORGE_UAPI_H
#define REEL_FORGE_UAPI_H
#include <linux/types.h>
#include <linux/ioctl.h>
#define REEL_FORGE_MAGIC 0x52
#define REEL_FORGE_CODEC_H264 0
#define REEL_FORGE_CODEC_H265 1
#define REEL_FORGE_CODEC_AV1  2
struct reel_forge_encode_config {
    __u32 codec; __u32 width; __u32 height; __u32 bitrate; __u32 fps; __u32 gop_size; __u64 reserved[4];
};
struct reel_forge_decode_config {
    __u32 codec; __u32 width; __u32 height; __u64 reserved[4];
};
#define REEL_FORGE_IOCTL_START_ENCODE  _IOW(REEL_FORGE_MAGIC, 1, struct reel_forge_encode_config)
#define REEL_FORGE_IOCTL_STOP_ENCODE   _IO(REEL_FORGE_MAGIC, 2)
#define REEL_FORGE_IOCTL_START_DECODE  _IOW(REEL_FORGE_MAGIC, 3, struct reel_forge_decode_config)
#define REEL_FORGE_IOCTL_STOP_DECODE   _IO(REEL_FORGE_MAGIC, 4)
#define REEL_FORGE_IOCTL_GET_STATUS    _IOR(REEL_FORGE_MAGIC, 5, __u32)
#endif
