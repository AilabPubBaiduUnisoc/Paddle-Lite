// Copyright (c) 2020 PaddlePaddle Authors. All Rights Reserved.
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

#include "lite/kernels/fpga/unsqueeze_compute.h"

#include <vector>

namespace paddle {
namespace lite_metal {
namespace kernels {
namespace fpga {

void UnsqueezeCompute::Run() {
  auto& param = Param<operators::UnsqueezeParam>();
  auto x = param.X;
  auto output = param.Out;
  auto output_dims = output->dims();
  output->Resize(output_dims);
  output->mutable_data<int64_t>();
  output->CopyDataFrom(*x);
}

}  // namespace fpga
}  // namespace kernels
}  // namespace lite
}  // namespace paddle

REGISTER_LITE_KERNEL(unsqueeze,
                     kFPGA,
                     kFP16,
                     kNHWC,
                     paddle::lite_metal::kernels::fpga::UnsqueezeCompute,
                     def)
    .BindInput("X",
               {LiteType::GetTensorTy(
                   TARGET(kHost), PRECISION(kAny), DATALAYOUT(kAny), -1)})
    .BindInput("AxesTensor",
               {LiteType::GetTensorTy(
                   TARGET(kHost), PRECISION(kInt32), DATALAYOUT(kAny), -1)})
    .BindInput("AxesTensorList",
               {LiteType::GetTensorTy(
                   TARGET(kHost), PRECISION(kInt32), DATALAYOUT(kAny), -1)})
    .BindOutput("Out",
                {LiteType::GetTensorTy(
                    TARGET(kHost), PRECISION(kAny), DATALAYOUT(kAny), -1)})
    .Finalize();

REGISTER_LITE_KERNEL(unsqueeze2,
                     kFPGA,
                     kFP16,
                     kNHWC,
                     paddle::lite_metal::kernels::fpga::UnsqueezeCompute,
                     def)
    .BindInput("X",
               {LiteType::GetTensorTy(
                   TARGET(kHost), PRECISION(kAny), DATALAYOUT(kAny), -1)})
    .BindInput("AxesTensor",
               {LiteType::GetTensorTy(
                   TARGET(kHost), PRECISION(kInt32), DATALAYOUT(kAny), -1)})
    .BindInput("AxesTensorList",
               {LiteType::GetTensorTy(
                   TARGET(kHost), PRECISION(kInt32), DATALAYOUT(kAny), -1)})
    .BindOutput("Out",
                {LiteType::GetTensorTy(
                    TARGET(kHost), PRECISION(kAny), DATALAYOUT(kAny), -1)})
    .BindOutput("XShape",
                {LiteType::GetTensorTy(
                    TARGET(kHost), PRECISION(kAny), DATALAYOUT(kAny), -1)})
    .Finalize();
