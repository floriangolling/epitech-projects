//
// Created by jbroesch on 6/4/21.
//

#ifndef BOMBERMAN_RAYLIBMAP_HPP
#define BOMBERMAN_RAYLIBMAP_HPP

#include "IMap.hpp"

namespace Indie {

    class RaylibMap : public IMap {

    public:
        RaylibMap() = default;
        void setMap(Vector meshPos, Vector mapPos, char *fp, short map_type, ...) override;
        void setMeshPosition(Vector);
        void setMapPosition(Vector);
        Vector3 &getMapPosition();
        Model getMapModel();
        Image &getImage();
        Texture2D &getCubicMap();
        Texture2D &getTexture();
    protected:
        Vector3 _meshPosition;
        Vector3 _mapPosition;
        Model _model;
        Texture2D _cubicmap;
        Texture2D _texture;
        Mesh _mesh;
        Image _image;
    };

}

#endif //BOMBERMAN_RAYLIBMAP_HPP
