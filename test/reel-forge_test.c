#include "libreel-forge.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
static int p=0,f=0;
#define T(n) do{printf("  TEST: %s ... ",n);fflush(stdout);}while(0)
#define P() do{printf("PASS\n");p++;}while(0)
#define F(m) do{printf("FAIL: %s\n",m);f++;}while(0)
#define S() do{printf("SKIP\n");}while(0)

static void t1(void) {
    T("open/close");
    struct reel_forge_handle *h = reel_forge_open("/dev/reel-forge0");
    if(!h){S();return;}
    reel_forge_close(h); P();
}
static void t2(void) {
    T("start/stop encode");
    struct reel_forge_handle *h = reel_forge_open("/dev/reel-forge0");
    if(!h){S();return;}
    int r = reel_forge_start_encode(h, 0, 1920, 1080, 10000000, 30);
    if(r){reel_forge_close(h);F("start");return;}
    r = reel_forge_stop_encode(h);
    if(r){reel_forge_close(h);F("stop");return;}
    reel_forge_close(h); P();
}
static void t3(void) {
    T("start/stop decode");
    struct reel_forge_handle *h = reel_forge_open("/dev/reel-forge0");
    if(!h){S();return;}
    int r = reel_forge_start_decode(h, 0, 1920, 1080);
    if(r){reel_forge_close(h);F("start");return;}
    r = reel_forge_stop_decode(h);
    if(r){reel_forge_close(h);F("stop");return;}
    reel_forge_close(h); P();
}
static void t4(void) {
    T("invalid args");
    int r = reel_forge_start_encode(NULL,0,0,0,0,0);
    if(r==-EINVAL)P();else F("expected -EINVAL");
}
int main(void) {
    printf("Reel Forge Driver Test Suite\n");
    t1();t2();t3();t4();
    printf("\n%d passed, %d failed\n",p,f);
    return f>0?1:0;
}
