# Instrument Function Pass
LLVM11 Dynamic Register Pass Plugin

This project records how to call custom instructment functions.

A basic Module Pass is implemented to insert custom instructment functions into Module functions, tracking which functions are executed.

Custom instructment functions must be compiled into a dynamic library and linked to be accessible during program runtime.

The Pass is dynamically registered and injected into the clang compilation process using the -Xclang option.

