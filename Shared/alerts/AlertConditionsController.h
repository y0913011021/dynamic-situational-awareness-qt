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

#ifndef ALERTCONDITIONSCONTROLLER_H
#define ALERTCONDITIONSCONTROLLER_H

#include "AbstractTool.h"

#include "TaskWatcher.h"

#include <QHash>
#include <QStringListModel>

class QMouseEvent;
class QStringList;

namespace Esri
{
namespace ArcGISRuntime
{
class IdentifyLayerResult;
class IdentifyGraphicsOverlayResult;
class FeatureLayer;
class FeatureTable;
class GraphicsOverlay;
}
}

class LocationAlertSource;
class AlertConditionData;
class AlertConditionListModel;
class AlertTarget;

class AlertConditionsController : public Esri::ArcGISRuntime::Toolkit::AbstractTool
{
  Q_OBJECT

  Q_PROPERTY(bool active READ isActive WRITE setActive NOTIFY activeChanged)
  Q_PROPERTY(QAbstractItemModel* sourceNames READ sourceNames NOTIFY sourceNamesChanged)
  Q_PROPERTY(QAbstractItemModel* targetNames READ targetNames NOTIFY targetNamesChanged)
  Q_PROPERTY(QAbstractItemModel* levelNames READ levelNames CONSTANT)
  Q_PROPERTY(QAbstractItemModel* conditionsList READ conditionsList NOTIFY conditionsListChanged)
  Q_PROPERTY(bool pickMode READ pickMode NOTIFY pickModeChanged)

public:
  explicit AlertConditionsController(QObject* parent = nullptr);
  ~AlertConditionsController();

  // AbstractTool interface
  QString toolName() const override;

  void setActive(bool active) override;

  Q_INVOKABLE void addWithinDistanceAlert(const QString& conditionName, int levelIndex, const QString& sourceFeedname, double distance, int itemId, int targetOverlayIndex);
  Q_INVOKABLE void addWithinAreaAlert(const QString& conditionName, int levelIndex, const QString& sourceFeedname, int itemId, int targetOverlayIndex);
  Q_INVOKABLE void addAttributeEqualsAlert(const QString& conditionName, int levelIndex, const QString& sourceFeedname, const QString& attributeName, const QVariant& targetValue);
  Q_INVOKABLE void removeConditionAt(int rowIndex);
  Q_INVOKABLE void togglePickMode();

  QAbstractItemModel* sourceNames() const;
  QAbstractItemModel* targetNames() const;
  QAbstractItemModel* levelNames() const;
  QAbstractItemModel* conditionsList() const;
  bool pickMode() const;

signals:
  void activeChanged();
  void sourceNamesChanged();
  void targetNamesChanged();
  void conditionsListChanged();
  void pickModeChanged();
  void pickedElement(const QString& overlayName, int elementId);

private slots:
  void onGeoviewChanged();
  void onLayersChanged();
  void onMouseClicked(QMouseEvent& event);
  void onIdentifyLayersCompleted(const QUuid& taskId, QList<Esri::ArcGISRuntime::IdentifyLayerResult*> identifyResults);
  void onIdentifyGraphicsOverlaysCompleted(const QUuid& taskId, QList<Esri::ArcGISRuntime::IdentifyGraphicsOverlayResult*> identifyResults);
  void handleNewAlertConditionData(AlertConditionData* newConditionData);

private:
  void setTargetNames(const QStringList& targetNames);
  void setSourceNames(const QStringList& sourceNames);

  AlertTarget* targetFromItemIdAndIndex(int itemId, int targetOverlayIndex) const;
  AlertTarget* targetFromFeatureLayer(Esri::ArcGISRuntime::FeatureLayer* featureLayer, int itemId) const;
  AlertTarget* targetFromGraphicsOverlay(Esri::ArcGISRuntime::GraphicsOverlay* graphicsOverlay, int itemId) const;
  Esri::ArcGISRuntime::GraphicsOverlay* graphicsOverlayFromName(const QString& overlayName);
  QString primaryKeyFieldName(Esri::ArcGISRuntime::FeatureTable* featureTable) const;

  static QStringList realtimeFeedNames();

  AlertConditionListModel* m_conditions;
  QStringListModel* m_sourceNames;
  QStringListModel* m_targetNames;
  QStringListModel* m_levelNames;
  bool m_pickMode = false;
  double m_tolerance = 5;
  LocationAlertSource* m_locationSource = nullptr;
  Esri::ArcGISRuntime::TaskWatcher m_identifyLayersWatcher;
  Esri::ArcGISRuntime::TaskWatcher m_identifyGraphicsWatcher;
  mutable QHash<QString,AlertTarget*> m_layerTargets;
  mutable QHash<QString,AlertTarget*> m_overlayTargets;

  QMetaObject::Connection m_mouseClickConnection;
  QMetaObject::Connection m_identifyLayersConnection;
  QMetaObject::Connection m_identifyGraphicsConnection;
};

#endif // ALERTCONDITIONSCONTROLLER_H
