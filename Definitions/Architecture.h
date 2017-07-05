#ifndef SILEXARS_DEFINITIONS_ARCHITECTURE_H
#define SILEXARS_DEFINITIONS_ARCHITECTURE_H

// Reference: http://sourceforge.net/p/predef/wiki/Architectures/

#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64)
    #define X86_64
    #define TARGET_ARCH X86_64
    #define TARGET_WORD 64
#elif defined(i386) || defined(__i386) || defined(__i386__) || defined(_M_I86) || defined(_M_IX86) || defined(__X86__) || defined(_X86_)
    #define X86
    #define TARGET_ARCH X86
    #define TARGET_WORD 32
#elif defined(__mips__) || defined(__mips) || defined(__MIPS__)
    #define MIPS
    #define TARGET_ARCH MIPS
    #define TARGET_WORD 32
#elif defined(__aarch64__)
    #define ARM64
    #define TARGET_ARCH ARM64
    #define TARGET_WORD 64
#elif defined(__arm__) || defined(__TARGET_ARCH_ARM) || defined(__TARGET_ARCH_THUMB) || defined(_ARM) || defined(_M_ARM) || defined(_M_ARMT) || defined(__arm)
    #define ARM
    #define TARGET_ARCH ARM
    #define TARGET_WORD 32
#endif

#endif // ARCHITECTURE_H
