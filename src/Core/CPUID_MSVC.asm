// This file is a part of AtlasEngine
// CREATED : 20/04/2021
// UPDATED : 21/04/2021

// ================ FOR VISUAL STUDIO PROJECTS ================ //

/* Used to get informations from the CPU */

// Do the call
mov EAX, funcId;
mov ECX, subFuncId;
cpuid;
// Save results
mov regs[0], EAX;
mov regs[1], EBX;
mov regs[2], ECX;
mov regs[3], EDX;
