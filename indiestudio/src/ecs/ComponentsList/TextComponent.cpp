//
// Created by jbroesch on 5/27/21.
//

#include "TextComponent.hpp"
#include "../Component.cpp"
#include "../../graphicalLib/IGraphic.hpp"

namespace Indie {

    TextComponent::TextComponent(std::string text, Vector vector, int size_text) {
        _text = text;
        _position.x += vector.x;
        _position.y += vector.y;
        _size_text = size_text;
        _savePosition.x = _position.x;
        _savePosition.y = _position.y;
    }

    void TextComponent::init(IGraphic *libgraphic) {
        _scale = libgraphic->getScale();
        _position.x = _position.x;
        _position.x += 0 + (this->_entity->getComponent<RectangleComponent>().getRectanglePosition().x + this->_entity->getComponent<RectangleComponent>().getRectangleWidth() / 2 );
        _savePosition.y = _position.y;
    }

    void TextComponent::update(double time) {
        _position.x = _savePosition.x;
        _position.y = _savePosition.y;
        _position.y += 0 + (this->_entity->getComponent<RectangleComponent>().getRectanglePosition().y + this->_entity->getComponent<RectangleComponent>().getRectangleHeight() / 2);
        _position.x += 0 + ((this->_entity->getComponent<RectangleComponent>().getRectanglePosition().x) + (this->_entity->getComponent<RectangleComponent>().getRectangleWidth() / 2));
    }

    std::string TextComponent::getText() { return _text; }

    void TextComponent::setText(char *text) { _text = text; }

    void TextComponent::draw(IGraphic &libGraphic) {
        libGraphic.myDraw(this);
    }

    int TextComponent::getSizeText() const { return _size_text * _scale; }

    void TextComponent::setSizeText(int size) { _size_text = size; }

    void TextComponent::setPosition(Vector position) {
        _position.x = position.x;
        _position.y = position.y;
    }

    void TextComponent::setScale(float scale) {
        _scale = scale;
    }

    Vector TextComponent::getPosition() { return _position; }

}