
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

import QtQuick 2.6
import QtQuick.Controls 1.4
import Esri.DSAVehicle 1.0
import Esri.ArcGISExtras 1.1
import Esri.ArcGISRuntime.Solutions 1.0

DSA_Vehicle {
    width: 800
    height: 600

    // Local app data path
    property string dataPath: System.resolvedPath(System.userHomePath) + "/ArcGIS/Runtime/Data/DSA";

    // Create MapQuickView here, and create its Map etc. in C++ code
    MapView {
        anchors.fill: parent
        objectName: "mapView"
        // set focus to enable keyboard navigation
        focus: true

        Button {
            id: coordConvButton
            text: "Coordinate conversion"

            onClicked: {
                coordinateConversion.visible = true;
            }
        }

        CoordinateConversion {
            id: coordinateConversion
            objectName: "coordinateConversion"
            visible: false
            height: parent.height / 3
            width: parent.width
            anchors {
                bottom: parent.bottom
            }
        }
    }
}
