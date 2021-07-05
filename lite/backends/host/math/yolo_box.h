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

#pragma once
#include <vector>
#include "lite/core/tensor.h"

namespace paddle {
namespace lite_metal {
namespace host {
namespace math {

void YoloBox(lite_metal::Tensor* X,
             lite_metal::Tensor* ImgSize,
             lite_metal::Tensor* Boxes,
             lite_metal::Tensor* Scores,
             std::vector<int> anchors,
             int class_num,
             float conf_thresh,
             int downsample_ratio,
             bool clip_bbox,
             float scale,
             float bias);

}  // namespace math
}  // namespace host
}  // namespace lite
}  // namespace paddle
