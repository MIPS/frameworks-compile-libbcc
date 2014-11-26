//===- BitReader_3_0.h - Internal BitcodeReader 3.0 impl --------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This header defines the BitcodeReader class.
//
//===----------------------------------------------------------------------===//

#ifndef BITREADER_3_0_H
#define BITREADER_3_0_H

#include "llvm/ADT/DenseMap.h"
#include "llvm/Bitcode/BitstreamReader.h"
#include "llvm/Bitcode/LLVMBitCodes.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/GVMaterializer.h"
#include "llvm/IR/OperandTraits.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/ValueHandle.h"
#include "llvm/Support/ErrorOr.h"
#include <string>

namespace llvm {
  class LLVMContext;
  class MemoryBuffer;
  class MemoryBufferRef;
  class Module;
} // End llvm namespace

namespace llvm_3_0 {

  /// Read the specified bitcode file, returning the module.
  llvm::ErrorOr<llvm::Module *> parseBitcodeFile(llvm::MemoryBufferRef Buffer,
                                                 llvm::LLVMContext &Context);


  /// Read the header of the specified bitcode buffer and extract just the
  /// triple information. If successful, this returns a string. On error, this
  /// returns "".
  std::string getBitcodeTargetTriple(llvm::MemoryBufferRef Buffer,
                                     llvm::LLVMContext &Context);

  /// Read the header of the specified bitcode buffer and prepare for lazy
  /// deserialization of function bodies.  If successful, this moves Buffer. On
  /// error, this *does not* move Buffer.
  llvm::ErrorOr<llvm::Module *> getLazyBitcodeModule(std::unique_ptr<llvm::MemoryBuffer> &&Buffer,
                                                     llvm::LLVMContext &Context);
} // End llvm_3_0 namespace

#endif
