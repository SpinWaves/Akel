// This file is a part of AtlasEngine
// CREATED : 19/04/2021
// UPDATED : 20/04/2021

// ================ FOR GCC COMPILATION ================ //

/* Used to get informations from the CPU */

"cpuid"
: "=a" (a),
  "=b" (b),          // The output variables. EAX -> a and vice versa.
  "=c" (c),
  "=d" (d) 
    
: "0" (infotype)    // Put the infotype into EAX.
