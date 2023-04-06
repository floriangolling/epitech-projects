//
// Created by jbroesch on 5/21/21.
//

#include "RectangleComponent.hpp"
#include "TextureComponent.hpp"
#include "PositionComponent.hpp"
#include "../../graphicalLib/IGraphic.hpp"

namespace Indie {
    void RectangleComponent::init(IGraphic *libgraphic) {
        if (!this->_entity->hasComponent<TextureComponent>() || !this->_entity->hasComponent<PositionComponent>()) {
            this->_entity->destroy();
            return;
        }
        _scale = libgraphic->getScale();
        _position.x = this->_entity->getComponent<PositionComponent>().getPosition().x - (float)_entity->getComponent<TextureComponent>().getTexture().textureGetWidth()/2 * _scale;
        _position.y = this->_entity->getComponent<PositionComponent>().getPosition().y - (float)_entity->getComponent<TextureComponent>().getTexture().textureGetHeight()/2 * _scale;
        _height = (float)this->_entity->getComponent<TextureComponent>().getTexture().textureGetHeight() * _scale;
        _width = (float)this->_entity->getComponent<TextureComponent>().getTexture().textureGetWidth() * _scale;
        _rectangle = {_position.x, _position.y, _width, _height};
    }

    void RectangleComponent::update(double time) {
        (void)time;
        _position.x = (this->_entity->getComponent<PositionComponent>().getPosition().x - ((float)_entity->getComponent<TextureComponent>().getTexture().textureGetWidth() * _scale )/2) * _scale;
        _position.y = (this->_entity->getComponent<PositionComponent>().getPosition().y - ((float)_entity->getComponent<TextureComponent>().getTexture().textureGetHeight() * _scale )/2) * _scale;
        _rectangle.x = _position.x;
        _rectangle.y = _position.y;
        _rectangle.width = _width * _scale;
        _rectangle.height = _height - 5 * _scale;
    }

    void RectangleComponent::setScale(float scale) {_scale = scale; }

    Rect RectangleComponent::getRectangle() { return _rectangle; }

    float RectangleComponent::getRectangleHeight() const { return _height; }

    void RectangleComponent::setRectangleHeight(float size) { _height = size; }

    void RectangleComponent::setRectanglePosition(Vector position) {
        _position.x = position.x;
        _position.y = position.y;
    }

    Vector RectangleComponent::getRectanglePosition() { return _position; }

    float RectangleComponent::getRectangleWidth() const { return _width; }

    void RectangleComponent::setRectangleWidth(float size) { _width = size; }
}