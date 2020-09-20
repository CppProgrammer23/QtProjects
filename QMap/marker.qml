import QtQuick 2.0
import QtQuick.Controls 2.0
import QtLocation 5.11



MapQuickItem
{
    id: marker
    anchorPoint.x:marker.width/4
    anchorPoint.y:marker.height
    coordinate: QtPositioning.coordinate(50.136812, 8.659483)
    sourceItem: Item
    {
        Image
        {
            id: icon
            source: "qrc:///image/ico.png"
            sourceSize.width: 50
            sourceSize.height: 50
        }
    }
}
