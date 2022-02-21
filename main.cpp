#include <mod/amlmod.h>
#include <dlfcn.h>

MYMOD(net.rusjj.fullsplash, GTA:SA Fullscreen Splashes, 1.0, RusJJ)

void Redirect(uintptr_t addr, uintptr_t to)
{
    if(!addr) return;
    if(addr & 1)
    {
        addr &= ~1;
        if (addr & 2)
        {
            aml->PlaceNOP(addr, 1);
            addr += 2;
        }
        uint32_t hook[2];
        hook[0] = 0xF000F8DF;
        hook[1] = to;
        aml->Write(addr, (uintptr_t)hook, sizeof(hook));
    }
    else
    {
        uint32_t hook[2];
        hook[0] = 0xE51FF004;
        hook[1] = to;
        aml->Write(addr, (uintptr_t)hook, sizeof(hook));
    }
}

extern "C" void OnModLoad()
{
    uintptr_t pGTASA = aml->GetLib("libGTASA.so");
    if(pGTASA == 0) return;

    aml->Write(pGTASA + 0x43B07B, (uintptr_t)"\xD0", 1); // BEQ
    aml->Write(pGTASA + 0x43B0C6, (uintptr_t)"\xB6\xEE\x06\x0A", 4); // On BEQ
    aml->Write(pGTASA + 0x43B07C, (uintptr_t)"\xB5\xEE\x04\x0A\x00\xBF\x00\xBF\x00\xBF", 10); // Otherwise

    Redirect(pGTASA + 0x43B024 + 0x1, pGTASA + 0x43B05A + 0x1); // Skip checks... Currently fullscreen splashes are for 4:3 screens and 16:9
}