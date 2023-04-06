//
// Created by jbroesch on 5/31/21.
//

#ifndef BOMBERMAN_RAYLIB3DPERSO_HPP
#define BOMBERMAN_RAYLIB3DPERSO_HPP

#include "I3DPerso.hpp"

namespace Indie {

    class Raylib3DPerso : public I3DPerso {

    public:
        int getPlayerID() const override;
        void setPlayerID(int) override;
        Raylib3DPerso();
        float getY() override;
        std::pair<float, float> getPositionPair() override;
        void setPersoPosition(float x, float y, float z) override;
        void setPersoModel(char *fp, ModelSelection) override;
        void setPersoTexture(char *fp) override;
        void setPersoMaterialTexture() override;
        Vector3 getPosition();
        Model &getModel(ModelSelection);
        Texture2D &getTexture();
        float getSpeed() const override;
        void setSpeed(float) override;
        void setWinID(int) override;
        int getWinID() override;

    protected:
        float _speed;
        Vector3 _position;
        Model _modelIddle;
        Model _modelAction;
        Model _modelDeath;
        Texture2D _texture;
        int _numberPlayer;
        int _win_ID = 0;
    };

}

#endif //BOMBERMAN_RAYLIB3DPERSO_HPP
