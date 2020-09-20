import QtQuick 2.0
import QtLocation 5.3
import QtPositioning 5.2

Item
{
    id: window
    Plugin
    {
        id: mapPlugin
        name: "esri"
    }
    function addMarker(lat,lon)
    {
        var component = Qt.createComponent("qrc:///qml/marker.qml")
        var item = component.createObject(window,
                                      {
                                          coordinate: QtPositioning.coordinate(lat,lon)
                                      })
        map.addMapItem(item)
    }


//    Image
//    {
//        id: icon
//        source: "qrc:///image/ico.png"
//        sourceSize.width: 50
//        sourceSize.height: 50
//    }
//    MapQuickItem
//    {
//        id: marker
//        anchorPoint.x:marker.width/4
//        anchorPoint.y:marker.height
//        coordinate: QtPositioning.coordinate(50.136812, 8.659483)
//        sourceItem: icon
//    }

    Map
    {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(50.136812, 8.659483)
        zoomLevel: 13
        Component.onCompleted:
        {
            //map.addMapItem(marker)
            addMarker(50.136812, 8.659483)
        }
    }
}
