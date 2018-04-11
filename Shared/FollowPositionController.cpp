// Copyright 2017 ESRI
//
// All rights reserved under the copyright laws of the United States
// and applicable international laws, treaties, and conventions.
//
// You may freely redistribute and use this sample code, with or
// without modification, provided you include the original copyright
// notice and use restrictions.
//
// See the Sample code usage restrictions document for further information.
//

// PCH header
#include "pch.hpp"

#include "FollowPositionController.h"

// toolkit headers
#include "ToolManager.h"
#include "ToolResourceProvider.h"

// C++ API headers
#include "GlobeCameraController.h"
#include "MapView.h"
#include "OrbitGeoElementCameraController.h"
#include "SceneView.h"

using namespace Esri::ArcGISRuntime;

namespace Dsa {

/*!
  \class FollowPositionController
  \inherits Toolkit::AbstractTool
  \brief Tool controller for managing the follow navigation modes.
 */

/*!
  \brief Constructor taking an optional \a parent.
 */

FollowPositionController::FollowPositionController(QObject* parent) :
  Toolkit::AbstractTool(parent)
{
  Toolkit::ToolManager::instance().addTool(this);

  connect(Toolkit::ToolResourceProvider::instance(), &Toolkit::ToolResourceProvider::geoViewChanged, this,
          &FollowPositionController::updateGeoView);

  updateGeoView();
}

/*!
  \brief Destructor.
 */
FollowPositionController::~FollowPositionController()
{
}

/*!
  \brief Initializes the tool with a \a geoView.
 */
void FollowPositionController::init(GeoView* geoView)
{
  m_geoView = geoView;

  handleNewMode();
}

/*!
  \brief Sets the follow mode for the tool to \a followMode.
 */
void FollowPositionController::setFollowMode(FollowPositionController::FollowMode followMode)
{
  if (m_mode == followMode)
    return;

  m_mode = followMode;
  handleNewMode();
}

/*!
  \brief Returns the follow mode for the tool.
 */
FollowPositionController::FollowMode FollowPositionController::followMode() const
{
  return m_mode;
}

/*!
  \brief Returns the name of the tool - c "follow position".
 */
QString FollowPositionController::toolName() const
{
  return QStringLiteral("follow position");
}

/*!
  \brief Sets the app to follow the \l Esri::ArcGISRuntime::GeoElement \a elementToFollow.
 */
void FollowPositionController::followGeoElement(GeoElement* elementToFollow)
{
  if (elementToFollow == nullptr)
    return;

  SceneView* sceneView = dynamic_cast<SceneView*>(m_geoView);
  if (!sceneView)
    return;

  m_mode = FollowMode::TrackUp;

  OrbitGeoElementCameraController* followController = new OrbitGeoElementCameraController(elementToFollow, 2000.0, this);
  sceneView->setCameraController(followController);
}

/*!
  \internal
 */
void FollowPositionController::handleNewMode()
{
  if (!m_geoView)
    return;

  if (handleFollowInMap())
    emit followModeChanged();
  else if (handleFollowInScene())
    emit followModeChanged();
}

/*!
  \internal
 */
void FollowPositionController::updateGeoView()
{
  GeoView* geoView = Toolkit::ToolResourceProvider::instance()->geoView();
  if (geoView)
    init(geoView);
}

/*!
  \internal
 */
bool FollowPositionController::handleFollowInMap()
{
  MapView* mapView = dynamic_cast<MapView*>(m_geoView);
  if (!mapView)
    return false;

  mapView->locationDisplay()->setAutoPanMode(m_mode == FollowMode::Disabled ?
                                               LocationDisplayAutoPanMode::Off :
                                               LocationDisplayAutoPanMode::Navigation );
  return true;
}

/*!
  \internal
 */
bool FollowPositionController::handleFollowInScene()
{
  SceneView* sceneView = dynamic_cast<SceneView*>(m_geoView);
  if (!sceneView)
    return false;

  if (m_mode == FollowMode::Disabled)
  {
    sceneView->setCameraController(new GlobeCameraController(this));
  }
  else
  {
    GraphicListModel* graphics = locationGraphicsModel();
    if (!graphics || graphics->rowCount() != 1)
      return true;

    Graphic* locationGraphic = graphics->at(0);
    if (!locationGraphic)
      return true;

    OrbitGeoElementCameraController* followController = new OrbitGeoElementCameraController(locationGraphic, 2000., this);

    if (m_mode == FollowMode::NorthUp)
    {
      followController->setAutoHeadingEnabled(false);
      followController->setCameraPitchOffset(0.);
    }

    sceneView->setCameraController(followController);
  }

  return true;
}

/*!
  \internal
 */
GraphicListModel* FollowPositionController::locationGraphicsModel() const
{
  if (!m_geoView)
    return nullptr;

  GraphicsOverlayListModel* overlays = m_geoView->graphicsOverlays();
  if (overlays->isEmpty())
    return nullptr;

  QString locationOverlayId("SCENEVIEWLOCATIONOVERLAY");
  for (int i = 0; i < overlays->rowCount(); ++i)
  {
    GraphicsOverlay* candidateOverlay = overlays->at(i);
    if (!candidateOverlay)
      continue;

    if (candidateOverlay->overlayId() != locationOverlayId)
      continue;

    return candidateOverlay->graphics();
  }

  return nullptr;
}

} // Dsa
