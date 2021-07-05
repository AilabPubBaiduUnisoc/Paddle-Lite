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

#pragma once
#include <memory>
#include "lite/backends/cuda/math/gemm.h"
#include "lite/backends/cuda/math/strided_gemm.h"
#include "lite/core/kernel.h"
#include "lite/operators/op_params.h"

namespace paddle {
namespace lite_metal {
namespace kernels {
namespace cuda {

template <typename T, PrecisionType Ptype>
class MatMulCompute : public KernelLite<TARGET(kCUDA), Ptype> {
 public:
  using param_t = operators::MatMulParam;

  void PrepareForRun() override {
    strided_gemm_impl_.reset(new lite_metal::cuda::math::StridedGemm<T, T>);
    gemm_impl_.reset(new lite_metal::cuda::math::Gemm<T, T>);
  }

  void Run() override;

  virtual ~MatMulCompute() = default;

 private:
  std::unique_ptr<lite_metal::cuda::math::StridedGemm<T, T>> strided_gemm_impl_{
      nullptr};
  std::unique_ptr<lite_metal::cuda::math::Gemm<T, T>> gemm_impl_{nullptr};
};

}  // namespace cuda
}  // namespace kernels
}  // namespace lite
}  // namespace paddle
