// Copyright (c) 2023, Open Source Robotics Foundation, Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the copyright holder nor the names of its
//      contributors may be used to endorse or promote products derived from
//      this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.


#include <memory>
#include <string>

#include "rviz_visual_testing_framework/visual_test_fixture.hpp"
#include "rviz_visual_testing_framework/visual_test_publisher.hpp"

#include "../../page_objects/effort_display_page_object.hpp"
#include "../../publishers/effort_publisher.hpp"

TEST_F(VisualTestFixture, wrenches_are_displayed) {
  auto effort_publisher = std::make_shared<nodes::EffortPublisher>();
  auto effort_visual_publisher =
    std::make_unique<VisualTestPublisher>(effort_publisher, "effort_frame");

  setCamPose(Ogre::Vector3(10, 10, 16));
  setCamLookAt(Ogre::Vector3(0, 0, 0));

  auto effort_display = addDisplay<EffortDisplayPageObject>();
  effort_display->setTopic("/joint_states");
  effort_display->setScale(2);
  effort_display->setWidth(4);
  effort_display->setRobotDescription("robot_description");

  captureMainWindow();

  effort_display->setAlpha(0.0f);
  captureMainWindow("empty_scene");

  assertScreenShotsIdentity();
}
