//
// Created by jbroesch on 5/31/21.
//

#include "Perso3DComponent.hpp"
#include "../../graphicalLib/IGraphic.hpp"
#include <filesystem>

namespace Indie {

    Perso3DComponent::Perso3DComponent(Json::Value &values) {
        _values = values;
    }

    void Perso3DComponent::init(IGraphic *libgraphic) {
        _time = 0;
        _perso = libgraphic->create_3d_perso();
        _perso->setPlayerID(_values["id"].asInt());
        float positionx = _values["positionX"].asFloat();
        float positiony = _values["positionY"].asFloat();
        float positionz = _values["positionZ"].asFloat();
        std::string mipath = _values["iddlemodelpath"].asString();
        std::string mapath = _values["actionmodelpath"].asString();
        std::string mdpath = _values["deathmodelpath"].asString();
        if (!std::filesystem::exists(mipath) || !std::filesystem::exists(mapath) || !std::filesystem::exists(mdpath)) {
            std::cerr << "A path for 3DPerso component does not exist !" << std::endl;
            throw std::exception();
        }
        _perso->setPersoPosition(positionx, positiony, positionz);
        _perso->setPersoModel(const_cast<char *>(mipath.c_str()), MODEL_IDDLE);
        _perso->setPersoModel(const_cast<char *>(mapath.c_str()), MODEL_ACTION);
        _perso->setPersoModel(const_cast<char *>(mdpath.c_str()), MODEL_DEATH);
        std::string tpath = _values["texturepath"].asString();
        _perso->setPersoTexture(const_cast<char *>(tpath.c_str()));
        _perso->setPersoMaterialTexture();
        _alive = true;
    }

    void Perso3DComponent::update(double time) {

        if (_alive == false && _time < 5) {
            _time += time;
            _perso->setPersoPosition(_perso->getPositionPair().first, _perso->getY() + 3 * time, _perso->getPositionPair().second);
        }
    }

    void Perso3DComponent::setAlive(bool alive)  {
        _alive = alive;
    }

    bool Perso3DComponent::getAlive()  {
        return (_alive);
    }

    void Perso3DComponent::draw(IGraphic &libGraphic) {
        libGraphic.myDraw(this);
    }

    I3DPerso &Perso3DComponent::get3DPerso() {
        return *_perso;
    }

    void Perso3DComponent::reset3DPerso(Vector3 vector, char *mfp, char *tfp) {
        _perso->setPersoPosition(vector.x, vector.y, vector.z);
        _perso->setPersoModel(mfp, MODEL_IDDLE);
        _perso->setPersoModel(mfp, MODEL_ACTION);
        _perso->setPersoModel(mfp, MODEL_DEATH);
        _perso->setPersoTexture(tfp);
        _perso->setPersoMaterialTexture();
    }

}