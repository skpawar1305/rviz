// Copyright (c) 2012, Willow Garage, Inc.
// Copyright (c) 2017, Open Source Robotics Foundation, Inc.
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


#ifndef RVIZ_COMMON__VIEWS_PANEL_HPP_
#define RVIZ_COMMON__VIEWS_PANEL_HPP_

#include "rviz_common/panel.hpp"

class QComboBox;
class QModelIndex;
class QPushButton;

namespace rviz_common
{

class ViewManager;

namespace properties
{

class PropertyTreeWidget;

}  // namespace properties

/// Panel for choosing the view controller and saving and restoring viewpoints.
class ViewsPanel : public Panel
{
  Q_OBJECT

public:
  explicit ViewsPanel(QWidget * parent = 0);
  virtual ~ViewsPanel() {}

  /// Just calls setViewManager() with vis_manager_->getViewManager().
  void onInitialize() override;  // Overridden from Panel.

  /// Set the ViewManager which this panel should display and edit.
  /**
   * If this ViewsPanel is to be used with a ViewManager other than
   * the one in the VisualizationManager sent in through
   * Panel::initialize(), either Panel::initialize() must not be
   * called or setViewManager() must be called after Panel::initialize().
   */
  void setViewManager(ViewManager * view_man);

  /// Return the current ViewManager.
  ViewManager * getViewManager() const {return view_man_;}

  /// Load configuration data, specifically the PropertyTreeWidget view settings.
  void load(const Config & config) override;

  /// Save configuration data, specifically the PropertyTreeWidget view settings.
  void save(Config config) const override;

private Q_SLOTS:
  void onTypeSelectorChanged(int selected_index);
  void onDeleteClicked();
  void renameSelected();
  void onZeroClicked();
  void onCurrentChanged();

  void setCurrentViewFromIndex(const QModelIndex & index);

private:
  ViewManager * view_man_;
  rviz_common::properties::PropertyTreeWidget * properties_view_;
  QPushButton * save_button_;
  QComboBox * camera_type_selector_;
};

}  // namespace rviz_common

#endif  // RVIZ_COMMON__VIEWS_PANEL_HPP_
