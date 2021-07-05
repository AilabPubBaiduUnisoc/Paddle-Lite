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

#include "lite/operators/polygon_box_transform_op.h"
#include "lite/core/op_registry.h"

namespace paddle {
namespace lite_metal {
namespace operators {

bool PolygonBoxTransformOp::CheckShape() const {
  CHECK(param_.input);
  CHECK(param_.output);
  CHECK_EQ(param_.input->dims().size(), 4UL)
      << "polygon_box_transform only support 4-D input.";
  return true;
}

bool PolygonBoxTransformOp::InferShapeImpl() const {
  param_.output->Resize(param_.input->dims());
  param_.output->set_lod(param_.input->lod());
  return true;
}

bool PolygonBoxTransformOp::AttachImpl(const cpp::OpDesc &op_desc,
                                       lite_metal::Scope *scope) {
  param_.input = scope->FindTensor(op_desc.Input("Input").front());
  param_.output = scope->FindMutableTensor(op_desc.Output("Output").front());
  return true;
}

}  // namespace operators
}  // namespace lite
}  // namespace paddle

REGISTER_LITE_OP(polygon_box_transform,
                 paddle::lite_metal::operators::PolygonBoxTransformOp);
