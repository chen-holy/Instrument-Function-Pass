# Instrument Function Pass
LLVM11 Dynamic Register Pass Plugin

This project records how to call custom instructment functions.

# Simplified Workflow for Custom Instrumentation

In summary, there are three main components: the instrumentation function, the Pass plugin, and the source program.


### step1、Implement Instrumentation Function
such as：myfunc.cpp

### step2、Compile Instrumentation


Convert the function into a dynamic link library and create a symbolic link.
> For details, refer to the command content.

### step3、Develop Pass Plugin
Write the plugin in InjectFunctionPass.cpp.

such InjectFunctionPass.cpp

### step4、Compile Pass Plugin
Build the plugin into a dynamic link library
> For details, refer to the command content.

### step5、Compile Source Code
Use clang to compile hello.c, integrating the plugin with the -Xclang flag.
> For details, refer to the command content.

