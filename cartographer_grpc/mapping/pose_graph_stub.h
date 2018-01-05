/*
 * Copyright 2017 The Cartographer Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CARTOGRAPHER_GRPC_MAPPING_POSE_GRAPH_STUB_H_
#define CARTOGRAPHER_GRPC_MAPPING_POSE_GRAPH_STUB_H_

#include "cartographer/mapping/pose_graph_interface.h"
#include "cartographer_grpc/proto/map_builder_service.grpc.pb.h"
#include "grpc++/grpc++.h"

namespace cartographer_grpc {
namespace mapping {

class PoseGraphStub : public cartographer::mapping::PoseGraphInterface {
 public:
  PoseGraphStub(std::shared_ptr<grpc::Channel> client_channel,
                proto::MapBuilderService::Stub* stub);

  PoseGraphStub(const PoseGraphStub&) = delete;
  PoseGraphStub& operator=(const PoseGraphStub&) = delete;

  void RunFinalOptimization() override;
  cartographer::mapping::MapById<cartographer::mapping::SubmapId, SubmapData>
  GetAllSubmapData() override;
  cartographer::mapping::MapById<cartographer::mapping::SubmapId, SubmapPose>
  GetAllSubmapPoses() override;
  cartographer::transform::Rigid3d GetLocalToGlobalTransform(
      int trajectory_id) override;
  cartographer::mapping::MapById<cartographer::mapping::NodeId,
                                 cartographer::mapping::TrajectoryNode>
  GetTrajectoryNodes() override;
  bool IsTrajectoryFinished(int trajectory_id) override;
  std::vector<Constraint> constraints() override;

 private:
  std::shared_ptr<grpc::Channel> client_channel_;
  proto::MapBuilderService::Stub* stub_;
};

}  // namespace mapping
}  // namespace cartographer_grpc

#endif  // CARTOGRAPHER_GRPC_MAPPING_POSE_GRAPH_STUB_H_
