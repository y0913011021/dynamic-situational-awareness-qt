
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

import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1
import QtQuick.Window 2.2
import Esri.DSA 1.0

DsaPanel {
    id: contactReportRoot
    clip: true
    title: qsTr("Contact Report")

    property bool isMobile
    property alias pickMode: toolController.pickMode
    property bool  toolActive: toolController.active
    property bool readyToAdd: reportFrame.currentItem == reviewPage

    ContactReportController {
        id: toolController

        active: isMobile ? (contactReportRoot.visible || pickMode) : contactReportRoot.visible

        onActiveChanged: {
            if (!active && contactReportRoot.visible)
                contactReportRoot.visible = false;
        }
    }

    Text {
        id: instructionText
        anchors {
            top: titleBar.bottom
            margins: 8 * scaleFactor
            horizontalCenter: parent.horizontalCenter
        }
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: DsaStyles.toolFontPixelSize * scaleFactor
        color: Material.accent
        text: reportFrame.currentItem.instruction
    }

    PageIndicator {
        id: pageIndicator
        anchors {
            top: instructionText.bottom
            horizontalCenter: reportFrame.horizontalCenter
            margins: 8 * scaleFactor
        }
        width: nextButton.width
        count: reportFrame.count
        currentIndex: reportFrame.currentIndex
    }

    SwipeView {
        id: reportFrame
        clip: true
        anchors {
            top: pageIndicator.bottom
            bottom: nextButton.top
            left: parent.left
            right: parent.right
            margins: 8 * scaleFactor
        }
        currentIndex: 0

        // Date and time of report
        ContactReportUnitPage {
            id: unitPage
            visible: reportFrame.currentIndex === 0
        }

        // Size of enemy unit
        ContactReportSizePage {
            id: sizePage
            visible: reportFrame.currentIndex === 1
        }

        // Activity
        ContactReportActivityPage {
            id: activityPage
            visible: reportFrame.currentIndex === 2
        }

        // Location
        ContactReportLocationPage {
            id: locationPage
            visible: reportFrame.currentIndex === 3
        }

        // Enemy Unit
        ContactReportEnemyUnitPage {
            id: enemyUnitPage
            visible: reportFrame.currentIndex === 4
        }

        // Observed Time
        ContactReportObservedTimePage {
            id: observedTimePage
            visible: reportFrame.currentIndex === 5
        }

        // Review
        Item {
            id: reviewPage
            visible: reportFrame.currentIndex === 6
            property string instruction: "Create contact report"
            property bool valid: true

            function text() {
                return reviewText.text;
            }

            function clear() {
                summaryText.text = "";
            }

            Text {
                id: reviewText
                text: "Create report?"
                anchors.centerIn: parent
                width: parent.width * 0.75
                font {
                    pixelSize: DsaStyles.titleFontPixelSize * scaleFactor
                    bold: true
                }
                wrapMode: Text.Wrap
                elide: Text.ElideRight
                color: Material.foreground
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    Button {
        id: backButton
        visible: reportFrame.currentIndex > 0
        anchors {
            left: reportFrame.left
            verticalCenter: nextButton.verticalCenter
            margins: 8 * scaleFactor
        }
        height: nextButton.height
        width: nextButton.width
        text: "Back"
        font.pixelSize: DsaStyles.toolFontPixelSize * scaleFactor

        onClicked: reportFrame.decrementCurrentIndex();
    }

    Button {
        id: nextButton
        visible: reportFrame.currentIndex < (reportFrame.count -1) && reportFrame.currentItem.valid
        anchors {
            right: reportFrame.right
            bottom: parent.bottom
            margins: 16 * scaleFactor
        }
        height: 32 * scaleFactor
        width: 64 * scaleFactor
        text: "Next"
        font.pixelSize: DsaStyles.toolFontPixelSize * scaleFactor

        onClicked: reportFrame.incrementCurrentIndex();
    }

    ToolIcon {
        id: createButton
        anchors {
            verticalCenter: nextButton.verticalCenter
            right: reportFrame.horizontalCenter
            margins: 4 * scaleFactor
        }
        enabled: readyToAdd
        opacity: enabled ? 1.0 : 0.5
        iconSource: DsaResources.iconComplete
        toolName: "Create"
        labelColor: Material.accent
        onToolSelected: {
            toolController.sendReport(sizePage.size,
                                      locationPage.locationDescription,
                                      enemyUnitPage.enemyUnit,
                                      observedTimePage.observedTime,
                                      "");
        }
    }

    ToolIcon {
        id: cancelButton
        anchors {
            verticalCenter: nextButton.verticalCenter
            left: reportFrame.horizontalCenter
            margins: 4 * scaleFactor
        }
        toolName: "Cancel"
        iconSource: DsaResources.iconClose

        onToolSelected: {
            for (var i = 0; i < conditionFrame.count; ++i)
                reportFrame.itemAt(i).clear();
            reportFrame.setCurrentIndex(0);
        }
    }

}
