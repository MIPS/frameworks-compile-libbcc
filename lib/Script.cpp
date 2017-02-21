/*
 * Copyright 2010-2012, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "bcc/Script.h"

#include "Assert.h"
#include "Log.h"

#include "bcc/CompilerConfig.h"
#include "bcc/Source.h"

using namespace bcc;

Script::Script(Source *pSource)
    : mSource(pSource),
      mOptimizationLevel(llvm::CodeGenOpt::Aggressive),
      mLinkRuntimeCallback(nullptr), mEmbedInfo(false), mEmbedGlobalInfo(false),
      mEmbedGlobalInfoSkipConstant(false) {}

bool Script::LinkRuntime(const char *core_lib) {
  bccAssert(core_lib != nullptr);

  // Using the same context with the source.
  BCCContext &context = mSource->getContext();

  Source *libclcore_source = Source::CreateFromFile(context, core_lib);
  if (libclcore_source == nullptr) {
    ALOGE("Failed to load Renderscript library '%s' to link!", core_lib);
    return false;
  }

  if (mLinkRuntimeCallback != nullptr) {
    mLinkRuntimeCallback(this, &mSource->getModule(),
                         &libclcore_source->getModule());
  }

  if (!mSource->merge(*libclcore_source)) {
    ALOGE("Failed to link Renderscript library '%s'!", core_lib);
    delete libclcore_source;
    return false;
  }

  return true;
}

bool Script::mergeSource(Source &pSource) { return mSource->merge(pSource); }
