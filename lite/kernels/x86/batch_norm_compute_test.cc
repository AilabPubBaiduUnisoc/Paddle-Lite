// Copyright (c) 2019 PaddlePaddle Authors. All Rights Reserved.
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

#include <gtest/gtest.h>

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "lite/core/op_registry.h"
#include "lite/kernels/x86/batch_norm_compute.h"

namespace paddle {
namespace lite_metal {
namespace kernels {
namespace x86 {

TEST(batch_norm_x86, retrive_op) {
  auto batch_norm = KernelRegistry::Global().Create("batch_norm");
  ASSERT_FALSE(batch_norm.empty());
  ASSERT_TRUE(batch_norm.front());
}

TEST(batch_norm_x86, init) {
  BatchNormCompute<float> batch_norm;
  ASSERT_EQ(batch_norm.precision(), PRECISION(kFloat));
  ASSERT_EQ(batch_norm.target(), TARGET(kX86));
}

TEST(batch_norm_x86, run_test) {
  lite_metal::Tensor x, scale, bias, mean, variance, y, mean_out, variance_out,
      saved_mean, saved_variance;
  constexpr int batch_size = 2;
  std::vector<int64_t> x_shape{batch_size, 3, 64, 64};
  x.Resize(lite_metal::DDim(x_shape));

  std::vector<int64_t> scale_shape{3};
  scale.Resize(lite_metal::DDim(scale_shape));

  std::vector<int64_t> bias_shape{3};
  bias.Resize(lite_metal::DDim(bias_shape));

  std::vector<int64_t> mean_shape{3};
  mean.Resize(lite_metal::DDim(mean_shape));

  std::vector<int64_t> variance_shape{3};
  variance.Resize(lite_metal::DDim(variance_shape));

  std::vector<int64_t> y_shape{batch_size, 3, 64, 64};
  y.Resize(lite_metal::DDim(y_shape));

  std::vector<int64_t> mean_out_shape{3};
  mean_out.Resize(lite_metal::DDim(mean_out_shape));

  std::vector<int64_t> variance_out_shape{3};
  variance_out.Resize(lite_metal::DDim(variance_out_shape));

  std::vector<int64_t> saved_mean_shape{3};
  saved_mean.Resize(lite_metal::DDim(saved_mean_shape));

  std::vector<int64_t> saved_variance_shape{3};
  saved_variance.Resize(lite_metal::DDim(saved_variance_shape));

  auto x_data = x.mutable_data<float>();
  auto scale_data = scale.mutable_data<float>();
  auto bias_data = bias.mutable_data<float>();
  auto mean_data = mean.mutable_data<float>();
  auto variance_data = variance.mutable_data<float>();
  y.mutable_data<float>();
  mean_out.mutable_data<float>();
  variance_out.mutable_data<float>();
  saved_mean.mutable_data<float>();
  saved_variance.mutable_data<float>();

  for (int64_t i = 0; i < x.dims().production(); i++) {
    x_data[i] = static_cast<float>(i);
  }
  for (int i = 0; i < scale.dims().production(); i++) {
    scale_data[i] = static_cast<float>(i) * 0.01f + 0.03f;
  }
  for (int i = 0; i < bias.dims().production(); i++) {
    bias_data[i] = static_cast<float>(i) * 0.065f + 0.1f;
  }
  for (int i = 0; i < mean.dims().production(); i++) {
    mean_data[i] = static_cast<float>(i) * 0.0565f;
  }
  for (int i = 0; i < variance.dims().production(); i++) {
    variance_data[i] = static_cast<float>(i) * 2.08f + 1.5f;
  }
  // BatchNormCompute batch_norm;
  BatchNormCompute<float> batch_norm;
  operators::BatchNormParam param;

  param.x = &x;
  param.is_test = true;
  param.scale = &scale;
  param.bias = &bias;
  param.mean = &mean;
  param.variance = &variance;
  param.use_global_stats = false;
  param.epsilon = 1e-4f;
  param.momentum = 0.9f;
  param.y = &y;
  param.mean_out = &mean_out;
  param.variance_out = &variance_out;
  param.saved_mean = &saved_mean;
  param.saved_variance = &saved_variance;

  std::unique_ptr<KernelContext> ctx(new KernelContext);
  ctx->As<X86Context>();
  batch_norm.SetContext(std::move(ctx));
  batch_norm.SetParam(param);
  batch_norm.Run();

  LOG(INFO) << "output: " << y;
  LOG(INFO) << "mean_out: " << mean_out;
  LOG(INFO) << "variance_out: " << mean_out;
  LOG(INFO) << "saved_mean: " << saved_mean;
  LOG(INFO) << "saved_variance: " << saved_variance;

  /*for (int i = 0; i < y.dims().production(); i++) {
    if(i < 5 || i > y.dims().production() - 5)
      LOG(INFO) << y_data[i];
  }*/
}

}  // namespace x86
}  // namespace kernels
}  // namespace lite
}  // namespace paddle

USE_LITE_KERNEL(batch_norm, kX86, kFloat, kNCHW, def);
