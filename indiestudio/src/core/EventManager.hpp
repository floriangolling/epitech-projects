//
// Created by jbroesch on 5/21/21.
//

#ifndef B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_EVENTMANAGER_H
#define B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_EVENTMANAGER_H

#include "../utils/utils.hpp"
#include "SceneManager.hpp"
#include "../jsoncpp/json.h"
#include "Clock.hpp"

namespace Indie {
    class IGraphic;
    class EventManager {
    public:
        EventManager();
        Clock &getClock();
        void setClock();
        void addBonus(IGraphic &libgraphic, float x, float y);
        void moveTarget(std::array<std::string, 13>);
        void makeBombExplode(IGraphic &libgraphic, Component *);
        void makeCharacterMove(IGraphic& libGraphic, int i, const std::string, float time);
        void makeIAMove(IGraphic &libgraphic, float time);
        void addEvents(const std::string &filename, std::map<std::string, Json::Value> &myMap);
        void setSceneEntity(std::map<std::string, std::shared_ptr<Entity>>&, IGraphic&);
        void setEventJSON(std::map<std::string, Json::Value>);
        std::map<std::string, Json::Value> &getEventJSON();
        Ikey keyboardEvents(IGraphic& libGraphic, float time);
        bool gamepadEvents(IGraphic& libGraphic, float time);
        bool mouseEvents(IGraphic& libGraphic, float time);
        bool detectEvent(std::pair<const std::string, std::shared_ptr<Entity>> &, IGraphic&);
        static Ikey isWindowUp(IGraphic& libGraphic);
        void setSceneManager(SceneManager *);
        void setKeysAtStart(void);
        void setMusic(float, IGraphic&);
        void setSound(float, IGraphic&);
        void detectScroll(std::pair<const std::string, std::shared_ptr<Entity>> &, IGraphic&);
        bool isThisKeyBindedAlready(Ikey) const;
        void setBombSelection(IGraphic&);
        bool getInGameState();
        void saveTheGame(IGraphic &);
    private:
        Clock *_clock;
        std::map<std::string, std::shared_ptr<Entity>> *_entities;
        std::map<std::string, Json::Value> _jsonEvents;
        SceneManager *_sceneManager;
        std::map<std::string, Ikey> _savedKeys;
        std::vector<typePlayer> _playerStates;
        std::vector<State> _alivePlayers;
        float _scrollValue;
        bool _isInGame = false;
        bool _exitPause = false;
        std::vector<int> _winOrder;
    };
}


#endif //B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_EVENTMANAGER_H
