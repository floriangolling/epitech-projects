//
// Created by jbroesch on 5/27/21.
//

#ifndef BOMBERMAN_TEXTCOMPONENT_H
#define BOMBERMAN_TEXTCOMPONENT_H

#include "../Component.hpp"
#include <cstring>

namespace Indie {

    class TextComponent : public Component {
    public:
        TextComponent(std::string text, Vector, int = 20);
        void init(IGraphic *libgraphic) override;
        std::string getText();
        void setText(char *);
        void setSizeText(int);
        int getSizeText() const;
        void setPosition(Vector);
        Vector getPosition();
        void update(double time) override;
        void setScale(float);
        void draw(IGraphic &libGraphic) override;
    private:
        std::string _text;
        int _size_text;
        float _scale;
        Vector _position{};
        Vector _savePosition{};
    };

}

#endif //BOMBERMAN_TEXTCOMPONENT_H
