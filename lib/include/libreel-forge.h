#ifndef LIBREEL_FORGE_H
#define LIBREEL_FORGE_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
struct reel_forge_handle;
struct reel_forge_handle *reel_forge_open(const char *path);
void reel_forge_close(struct reel_forge_handle *h);
int reel_forge_start_encode(struct reel_forge_handle *h, uint32_t codec, uint32_t w, uint32_t h_, uint32_t bitrate, uint32_t fps);
int reel_forge_stop_encode(struct reel_forge_handle *h);
int reel_forge_start_decode(struct reel_forge_handle *h, uint32_t codec, uint32_t w, uint32_t h_);
int reel_forge_stop_decode(struct reel_forge_handle *h);
const char *reel_forge_strerror(int err);
#ifdef __cplusplus
}
#endif
#endif
