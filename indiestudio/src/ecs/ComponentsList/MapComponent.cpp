//
// Created by jbroesch on 6/4/21.
//

#include "MapComponent.hpp"
#include "../../graphicalLib/IGraphic.hpp"
#include "../../utils/GenerateImages.hpp"

namespace Indie {

    MapComponent::MapComponent(Json::Value &values) {
        _values = values;
    }

    void MapComponent::init(IGraphic *libgraphic) {
        _map = libgraphic->create_map();
        std::pair<int, std::array<std::string, 13>> returnValues;
        Vector meshPosition;
        meshPosition.x = _values["positionMeshX"].asFloat();
        meshPosition.y = _values["positionMeshY"].asFloat();
        meshPosition.z = _values["positionMeshZ"].asFloat();
        Vector mapPosition;
        mapPosition.x = _values["positionMapX"].asFloat();
        mapPosition.y = _values["positionMapY"].asFloat();
        mapPosition.z = _values["positionMapZ"].asFloat();
        short maptype = (short)_values["maptype"].asInt();
        returnValues.first = 0;
        if (maptype == 0) {
            returnValues = createMap();
            _myMapArray = returnValues.second;
            _type = 1;
        } else {
            _type = 0;
            returnValues = createMap();
            _myMapArray = returnValues.second;
        }
        const char *pathMap[2] {"../assets/maps/mapInitial.png", "../assets/maps/mapOne.png"};
        _map->setMap(meshPosition, mapPosition, (char*)pathMap[returnValues.first], maptype);
    }

    std::array<std::string, 13> &MapComponent::getMyMapArray() {
        return _myMapArray;
    }

    int MapComponent::getType() {
        return (_type);
    }

    void MapComponent::update(double time) {
        (void)time;
    }

    void MapComponent::draw(IGraphic &libGraphic) {
        libGraphic.myDraw(this);
    }

    void MapComponent::setMap(std::array<std::string, 13> map) {
        _myMapArray = map;
    }

    IMap & MapComponent::getMap() {
        return *_map;
    }

    void MapComponent::resetMap(Vector mapv, Vector meshv, char *fp) {
        fp = (char*)"../assets/maps/mapBox.png";
        _map->setMap(mapv, meshv, fp, 3);    }

}