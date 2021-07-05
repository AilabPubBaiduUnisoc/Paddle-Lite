// Copyright (c) 2021 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "lite/kernels/host/write_back_compute.h"
#include "lite/core/target_wrapper.h"

namespace paddle {
namespace lite_metal {
namespace kernels {
namespace host {

void WriteBackCompute::Run() {
  auto& param = this->template Param<operators::WriteBackParam>();
  CHECK(param.x->target() == param.y->target());
  param.y->ShareDataWith(*param.x);
}

}  // namespace host
}  // namespace kernels
}  // namespace lite
}  // namespace paddle

REGISTER_LITE_KERNEL(write_back,
                     kHost,
                     kAny,
                     kAny,
                     paddle::lite_metal::kernels::host::WriteBackCompute,
                     tensor_copy)
    .BindInput("Src_LoDTensor",
               {LiteType::GetTensorTy(TARGET(kHost),
                                      PRECISION(kAny),
                                      DATALAYOUT(kAny))})
    .BindInput("Dst_LoDTensor",
               {LiteType::GetTensorTy(TARGET(kHost),
                                      PRECISION(kAny),
                                      DATALAYOUT(kAny))})
    .BindInput("Dep_LoDTensor",
               {LiteType::GetTensorTy(TARGET(kAny),
                                      PRECISION(kAny),
                                      DATALAYOUT(kAny))})
    .BindInput("Dep_LoDTensorArray",
               {LiteType::GetTensorListTy(TARGET(kAny),
                                          PRECISION(kAny),
                                          DATALAYOUT(kAny))})
    .Finalize();
