//
// Created by jbroesch on 5/19/21.
//

#include "TextureComponent.hpp"
#include "../Component.cpp"

namespace Indie {

    TextureComponent::TextureComponent(const char *fp) {
        _fp = fp;
    }

    void TextureComponent::init(IGraphic *libgraphic) {
        if (_fp == nullptr) {
            this->_entity->destroy();
            return;
        }
        _texture = libgraphic->create_texture();
        _texture->setTexture(_fp);
        _position.x = this->_entity->getComponent<PositionComponent>().getPosition().x + (float)_texture->textureGetWidth()/2;
        _position.y = this->_entity->getComponent<PositionComponent>().getPosition().y + (float)_texture->textureGetHeight()/2;
        _entity->getComponent<PositionComponent>().setPosition(_position);
    }

    ITexture &TextureComponent::getTexture() { return *_texture; }

    void TextureComponent::update(double time) {
        (void)time;
        _position.x = this->_entity->getComponent<PositionComponent>().getPosition().x;
        _position.y = this->_entity->getComponent<PositionComponent>().getPosition().y;
    }

    void TextureComponent::draw(IGraphic &libGraphic) {
        libGraphic.myDraw(this);
    }

}