// Copyright 2016 ESRI
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

#include "DsaResources.h"

DsaResources::DsaResources(QObject* parent):
  QObject(parent)
{  
}

DsaResources::~DsaResources()
{ 
}

QUrl DsaResources::icon2d() const
{
  return "qrc:/Resources/icons/xhdpi/2D.png";
}

QUrl DsaResources::icon3d() const
{
  return "qrc:/Resources/icons/xhdpi/3D.png";
}

QUrl DsaResources::iconAboutMap() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_aboutmap_dark.png";
}

QUrl DsaResources::iconAdd() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_add_dark_d.png";
}

QUrl DsaResources::iconAddLayer() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_layervisibilitypopover_dark_d.png";
}

QUrl DsaResources::iconAlert() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_failedlayer.png";
}

QUrl DsaResources::iconAppLogo() const
{
  return "qrc:/Resources/icons/xhdpi/applogo.png";
}

QUrl DsaResources::iconChooseBasemap() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_choosebasemap_dark.png";
}

QUrl DsaResources::iconClose() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_closeclear_dark.png";
}

QUrl DsaResources::iconComplete() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_completedone_dark.png";
}

QUrl DsaResources::iconCoordinateConversion() const
{
  return "qrc:/Resources/icons/xhdpi/icon-64-coorconv-white.png";
}

QUrl DsaResources::iconCreateReport() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_editmap_dark_d-2.png";
}

QUrl DsaResources::iconDraw() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_edit_dark_d.png";
}

QUrl DsaResources::iconDrawer() const
{
  return "qrc:/Resources/icons/xhdpi/drawer_large.png";
}

QUrl DsaResources::iconFollowLocation() const
{
  return "qrc:/Resources/icons/xhdpi/navigation.png";
}

QUrl DsaResources::iconFollowLocationNorthUp() const
{
  return "qrc:/Resources/icons/xhdpi/navigation_north.png";
}

QUrl DsaResources::iconFollowLocationOff() const
{
  return "qrc:/Resources/icons/xhdpi/navigation_disabled.png";
}

QUrl DsaResources::iconGps() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_gpsondontfollow_dark.png";
}

QUrl DsaResources::iconHome() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_home_dark.png";
}

QUrl DsaResources::iconLayers() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_layergroup_dark_d.png";
}

QUrl DsaResources::iconListView() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_openlistview_dark.png";
}

QUrl DsaResources::iconMap() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_mapview_dark_d.png";
}

QUrl DsaResources::iconMessages() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_messages_dark.png";
}

QUrl DsaResources::iconPoint() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_pointlayer_light.png";
}

QUrl DsaResources::iconPolygon() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_polygonlayer_light.png";
}

QUrl DsaResources::iconPolyline() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_linelayer_light.png";
}

QUrl DsaResources::iconRaster() const
{
  return "qrc:/Resources/icons/xhdpi/raster_layer.png";
}

QUrl DsaResources::iconRemove() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_subtract_dark_d.png";
}

QUrl DsaResources::iconRotate() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_refresh_dark.png";
}

QUrl DsaResources::iconSendMap() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_sendmap_dark_d.png";
}

QUrl DsaResources::iconSettings() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_settings_dark_d.png";
}

QUrl DsaResources::iconSketch() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_freehandsketchoff_dark.png";
}

QUrl DsaResources::iconTools() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_tooloverflow_dark_d.png";
}

QUrl DsaResources::iconTrash() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_trash_dark_d.png";
}

QUrl DsaResources::iconViewshed() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_video_dark_d.png";
}

QUrl DsaResources::iconZoomTo() const
{
  return "qrc:/Resources/icons/xhdpi/ic_menu_zoomtofeature_light.png";
}
