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

#include "lite/operators/shuffle_channel_op.h"
#include "lite/core/op_lite.h"
#include "lite/core/op_registry.h"
#include "lite/core/tensor.h"

namespace paddle {
namespace lite_metal {
namespace operators {

bool ShuffleChannelOpLite::CheckShape() const {
  CHECK_OR_FALSE(param_.X);
  CHECK_OR_FALSE(param_.Out);
  return true;
}

bool ShuffleChannelOpLite::InferShapeImpl() const {
  param_.Out->Resize(param_.X->dims());
  return true;
}

bool ShuffleChannelOpLite::AttachImpl(const cpp::OpDesc& op_desc,
                                      lite_metal::Scope* scope) {
  auto X = op_desc.Input("X").front();
  auto Out = op_desc.Output("Out").front();
  param_.X = scope->FindVar(X)->GetMutable<lite_metal::Tensor>();
  param_.Out = scope->FindVar(Out)->GetMutable<lite_metal::Tensor>();
  param_.group = op_desc.GetAttr<int>("group");
  CHECK(param_.X);
  CHECK(param_.Out);
  return true;
}

}  // namespace operators
}  // namespace lite
}  // namespace paddle

REGISTER_LITE_OP(shuffle_channel,
                 paddle::lite_metal::operators::ShuffleChannelOpLite);
