// This file is a part of AtlasEngine
// CREATED : 20/04/2021
// UPDATED : 20/04/2021

// ================ FOR VISUAL STUDIO PROJECTS ================ //

/* Used to get informations from the CPU */

// Do the call
mov EAX, infoType;
cpuid;
// Save results
mov a, EAX;
mov b, EBX;
mov c, ECX;
mov d, EDX;
