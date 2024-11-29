#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/CBindingWrapping.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"


using namespace llvm;
/*
At the entry point of the program, insert code
to print the called functions during the program execution
*/
namespace {
  struct HelloModulePass : public ModulePass {
    static char ID;
    HelloModulePass() : ModulePass(ID) {}

    bool runOnModule(Module &M) override {
        errs() << "Insert __qy_printf function to print the names of functions called during execution." << "\n";
        auto &CTX = M.getContext();
        Type *VoidTy = Type::getVoidTy(CTX);                                              // eturn type of the custom function - void
        PointerType *PrintfArgTy = PointerType::getUnqual(IntegerType::getInt8Ty(CTX));   // Parameter type of the custom function - pointer to char*
        
        /*
        Define the function to be inserted QY_Printf

        __qy_printf is the inserted custom function, 
        used to receive and process information from the execution flow, 
        such as dynamically collecting called functions
        */
        FunctionCallee QY_Printf = M.getOrInsertFunction("__qy_printf", VoidTy, PrintfArgTy);
        
        for(auto &F : M){
            // Skip probing for external functions, like c/c++ std library func
            if (F.isDeclaration()) continue;

            // Find the position to insert instructions
            IRBuilder<> Builder(&*F.getEntryBlock().getFirstInsertionPt());

            // Insert the content to be executed
            auto FuncName = Builder.CreateGlobalStringPtr(F.getName());
            Builder.CreateCall(QY_Printf, {FuncName});
            
        }
        errs() << "This is runOnModule" << "\n";
        return false;
    }
  };
}

char HelloModulePass::ID = 0;

static RegisterPass<HelloModulePass>
    X(
      /*PassArg=*/"my-printf-instrument", 
      /*Name=*/"My Printf Instrument Pass",
      /*CFGOnly=*/false, 
      /*is_analysis=*/false
      );

static void registerHelloPass(const PassManagerBuilder &,
                                 legacy::PassManagerBase &PM) {
  PM.add(new HelloModulePass());
}

static RegisterStandardPasses
    RegisterHelloPass(PassManagerBuilder::EP_OptimizerLast,
                         registerHelloPass);

static RegisterStandardPasses
    RegisterHelloPass0(PassManagerBuilder::EP_EnabledOnOptLevel0,
                          registerHelloPass);