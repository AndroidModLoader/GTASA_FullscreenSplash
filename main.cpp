#include <mod/amlmod.h>

MYMOD(net.rusjj.fullsplash, GTA:SA Fullscreen Splashes, 1.1, RusJJ)

#ifdef AML32
    #define BYVER(__for32, __for64) (__for32)
#else
    #define BYVER(__for32, __for64) (__for64)
#endif

extern "C" void OnModLoad()
{
    uintptr_t pGTASA = aml->GetLib("libGTASA.so");
    if(pGTASA == 0) return;

    aml->Write(pGTASA + BYVER(0x43B07B, 0x5204F0), (uintptr_t)BYVER("\xD0", "\x80"), 1); // BEQ
    aml->Write(pGTASA + BYVER(0x43B0C6, 0x520540), (uintptr_t)BYVER("\xB6\xEE\x06\x0A", "\x00\xD0\x2C\x1E"), 4); // On BEQ
    aml->Write(pGTASA + BYVER(0x43B07C, 0x5204F4), (uintptr_t)BYVER("\xB5\xEE\x04\x0A\x00\xBF\x00\xBF\x00\xBF", "\x00\x90\x2A\x1E\x1F\x20\x03\xD5\x1F\x20\x03\xD5"), BYVER(10, 12)); // Otherwise

    aml->PlaceB(pGTASA + BYVER(0x43B024 + 0x1, 0x520498), pGTASA + BYVER(0x43B05A + 0x1, 0x5204C8)); // Skip checks... Currently fullscreen splashes are for 4:3 screens and 16:9
}