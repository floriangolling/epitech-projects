//
// Created by jbroesch on 5/15/21.
//

#include "graphical.hpp"
#include "../ecs/ComponentsList/TextComponent.hpp"
#include "../ecs/ComponentsList/CameraComponent.hpp"
#include "../ecs/ComponentsList/Perso3DComponent.hpp"
#include "../ecs/ComponentsList/AnimationComponent.hpp"
#include "../ecs/ComponentsList/MapComponent.hpp"
#include "../ecs/ComponentsList/BonusComponent.hpp"
#include "../ecs/ComponentsList/BombComponent.hpp"
#include "RaylibCamera.hpp"
#include "../ecs/ComponentsList/StatsComponent.hpp"
#include "../ecs/ComponentsList/ButtonComponent.hpp"
#include "../ecs/ComponentsList/PauseComponent.hpp"
#include "Raylib3DPerso.hpp"
#include "RaylibMap.hpp"
#include "raymath.h"

namespace Indie {

    std::map<int, Ikey> _mapKey = {
            {KEY_A , Q},
            {KEY_Z , W},
            {KEY_E , E},
            {KEY_R , R},
            {KEY_T , T},
            {KEY_Y , Y},
            {KEY_U , U},
            {KEY_I , I},
            {KEY_O , O},
            {KEY_P , P},
            {KEY_Q , A},
            {KEY_S , S},
            {KEY_D , D},
            {KEY_F , F},
            {KEY_G , G},
            {KEY_H , H},
            {KEY_J , J},
            {KEY_K , K},
            {KEY_L , L},
            {KEY_SEMICOLON , M},
            {KEY_W , Z},
            {KEY_X , X},
            {KEY_C , C},
            {KEY_V , V},
            {KEY_B , B},
            {KEY_N , N},
            {KEY_M , COMAKEY},
            {KEY_LEFT, KEYLEFT},
            {KEY_RIGHT, KEYRIGHT},
            {KEY_UP, KEYUP},
            {KEY_DOWN, KEYDOWN},
            {KEY_SPACE, SPACE}
    };

    std::map<Ikey, std::string> _mapKeyString = {
            {A, "A"},
            {B, "B"},
            {C, "C"},
            {D, "D"},
            {E, "E"},
            {F, "F"},
            {G, "G"},
            {H, "H"},
            {I, "I"},
            {J, "J"},
            {K, "K"},
            {L, "L"},
            {M, "M"},
            {N, "N"},
            {O, "O"},
            {P, "P"},
            {Q, "Q"},
            {R, "R"},
            {S, "S"},
            {T, "T"},
            {U, "U"},
            {V, "V"},
            {W, "W"},
            {X, "X"},
            {Y, "Y"},
            {Z, "Z"},
            {SPACE, "SPACE"},
            {KEYLEFT, "LEFT"},
            {KEYRIGHT, "RIGHT"},
            {KEYUP, "UP"},
            {KEYDOWN, "DOWN"}
    };

    void Raylib::createSpriteLibrarie() {
        this->displayLoading(std::string("Loading 0%"));
        _modelLibrary.push_back(LoadModel("../assets/bombe.gltf"));
        this->displayLoading(std::string("Loading 6%"));
        _modelLibrary.push_back(LoadModel("../assets/bomb/flame.gltf"));
        this->displayLoading(std::string("Loading 12%"));
        _modelLibrary.push_back(LoadModel("../assets/bonus/bonus.gltf"));
        this->displayLoading(std::string("Loading 17%"));
        _modelLibrary.push_back(LoadModel("../assets/bonus/bonus.gltf"));
        this->displayLoading(std::string("Loading 23%"));
        _modelLibrary.push_back(LoadModel("../assets/bonus/bonus.gltf"));
        this->displayLoading(std::string("Loading 29%"));
        _modelLibrary.push_back(LoadModel("../assets/bonus/bonus.gltf"));
        this->displayLoading(std::string("Loading 35%"));
        Texture2D textureBomb = LoadTexture("../assets/bomb.png");
        this->displayLoading(std::string("Loading 41%"));
        SetMaterialTexture(&_modelLibrary[BOMB].materials[0], MAP_DIFFUSE, textureBomb);
        Texture2D textureBombExplosion = LoadTexture("../assets/bomb/flame_texture.png");
        this->displayLoading(std::string("Loading 46%"));
        SetMaterialTexture(&_modelLibrary[EXPLOSION].materials[0], MAP_DIFFUSE, textureBombExplosion);
        Texture2D textureB1 = LoadTexture("../assets/bonus/double_bomb.png");
        this->displayLoading(std::string("Loading 52%"));
        Texture2D textureB2 = LoadTexture("../assets/bonus/range_up_cube_texture.png");
        this->displayLoading(std::string("Loading 58%"));
        Texture2D textureB3 = LoadTexture("../assets/bonus/speed_up_cube_texture.png");
        this->displayLoading(std::string("Loading 63%"));
        Texture2D textureB4 = LoadTexture("../assets/bonus/wall_cube_texture.png");
        this->displayLoading(std::string("Loading 69%"));
        SetMaterialTexture(&_modelLibrary[BONUSRANGE].materials[0], MAP_DIFFUSE, textureB2);
        SetMaterialTexture(&_modelLibrary[BONUSDOUBLE].materials[0], MAP_DIFFUSE, textureB1);
        SetMaterialTexture(&_modelLibrary[BONUSWALLCUBE].materials[0], MAP_DIFFUSE, textureB4);
        SetMaterialTexture(&_modelLibrary[BONUSSPEED].materials[0], MAP_DIFFUSE, textureB3);
    }

    void Raylib::rotateAngle(float x, float y, float z, Component *compo) {
        Raylib3DPerso &model = *((Raylib3DPerso*)(&(compo->_entity->getComponent<Perso3DComponent>().get3DPerso())));
        Vector3 ang = {0};
        ang.x = DEG2RAD*x;
        ang.y = DEG2RAD*y;
        ang.z = DEG2RAD*z;
        model.getModel(MODEL_IDDLE).transform = MatrixRotateXYZ(ang);
        model.getModel(MODEL_ACTION).transform = MatrixRotateXYZ(ang);
        model.getModel(MODEL_DEATH).transform = MatrixRotateXYZ(ang);
    }

    std::pair<float, float> Raylib::moveXYZEntity(float x, float y, float z, Component *compo) {
        std::pair<float, float> pos;
        if (!compo->_entity->hasComponent<StatsComponent>()) {
            Vector3 pos2 = ((Raylib3DPerso*)(&(compo->_entity->getComponent<Perso3DComponent>().get3DPerso())))->getPosition();
            return (std::make_pair(pos2.x, pos2.z));
        }

        Vector3 position = ((Raylib3DPerso*)(&(compo->_entity->getComponent<Perso3DComponent>().get3DPerso())))->getPosition();
        auto &perso = compo->_entity->getComponent<Perso3DComponent>().get3DPerso();
        perso.setPersoPosition(position.x + x * compo->_entity->getComponent<StatsComponent>().getSpeed(), position.y + y, position.z + z * compo->_entity->getComponent<StatsComponent>().getSpeed());
        position = ((Raylib3DPerso*)(&(compo->_entity->getComponent<Perso3DComponent>().get3DPerso())))->getPosition();
        pos.first = position.x;
        pos.second = position.z;
        return (pos);
    }

    void Raylib::setPersoToSky(Component *compo) {
        Vector3 position = ((Raylib3DPerso*)(&(compo->_entity->getComponent<Perso3DComponent>().get3DPerso())))->getPosition();
        auto &perso = compo->_entity->getComponent<Perso3DComponent>().get3DPerso();
        perso.setPersoPosition(position.x, 16 , position.z);
    }

    std::pair<float, float> Raylib::setXYZEntity(float x, float y, float z, Component *compo) {
        std::pair<float, float> pos;
        Vector3 position = ((Raylib3DPerso*)(&(compo->_entity->getComponent<Perso3DComponent>().get3DPerso())))->getPosition();
        auto &perso = compo->_entity->getComponent<Perso3DComponent>().get3DPerso();
        perso.setPersoPosition(x, y , z);
        position = ((Raylib3DPerso*)(&(compo->_entity->getComponent<Perso3DComponent>().get3DPerso())))->getPosition();
        pos.first = position.x;
        pos.second = position.z;
        return (pos);
    }

    std::string Raylib::getInputAsString(Ikey key) {
        return (_mapKeyString[key]);
    }

    Raylib::Raylib() {

    }

    bool Raylib::isBombButtonPressed(int map, int button)
    {
        if (IsGamepadButtonDown(map, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
            return true;
        return false;
    }

    bool Raylib::checkAxisButton(int map, int axis, float dir, int greater) {
        if (greater == 1) {
            if (GetGamepadAxisMovement(map, axis) >= dir)
                return true;
        } else if (greater == 0) {
            if (GetGamepadAxisMovement(map, axis) <= dir)
                return true;
        }
        return false;
    }

    void Raylib::moveBombSelection(Vector vect)
    {
        _savedBombSelection = Vector{vect.x + 220, vect.y + 10};
    }

    bool Raylib::getGamepadAxisCharacterSelector(int pad, float axis) {
        for (int i = 0; i < 4; i++) {
            if (GetGamepadAxisMovement(i, axis) > 0.9)
                return true;
        }
        return false;
    }

    bool Raylib::checkGamepadButton(int map, int dir) {
        if (IsGamepadButtonDown(map, dir))
            return true;
        return false;
    }

    void Raylib::init_window() {
        InitWindow(this->init_lib.window_x, this->init_lib.window_y, this->init_lib.window_name.c_str());
        SetTargetFPS(this->init_lib.window_fps);
        _font = LoadFontEx(this->init_lib.font.c_str(), this->init_lib.font_size, nullptr, 0);
        SetTextureFilter(_font.texture, FILTER_BILINEAR);
#if ! defined(__APPLE__)
        InitAudioDevice();
        _music = LoadMusicStream(this->init_lib.music.c_str());
        if (!_music.looping && _music.sampleCount == 0)
            throw std::runtime_error("Error : Not a valid music file, exiting");
        _sound = LoadSound(this->init_lib.sound.c_str());
        if (!_sound.sampleCount)
            throw std::runtime_error("Error : Not a valid sound file, exiting");
        SetMusicVolume(_music, 1);
        SetSoundVolume(_sound, 1);
        PlayMusicStream(_music);
#endif
        SetExitKey(KEY_NULL);
        _shouldClose = false;
        _scale = 1;
        _soundVolume = 10;
        _musicVolume = 10;
        _bombSelection = LoadTexture("../assets/MainMenu/bomb_selection.png");
        if (_bombSelection.id == 0)
            throw std::runtime_error("Error : Not a valid file assets/MainMenu/bomb_selection.png, exiting");
        _savedBombSelection = {110 + 220, 370 + 10};
        _isPaused = false;
    }

    void Raylib::makeSoundExplosion()
    {
        PlaySound(_sound);
    }

    void Raylib::setPause(bool pause) {
        _isPaused = pause;
    }

    Raylib::~Raylib() {
#if ! defined(__APPLE__)
        UnloadMusicStream(_music);
        UnloadSound(_sound);
        CloseAudioDevice();
#endif
        CloseWindow();
    }

    void Raylib::openMyWindow(float scale) {
       InitWindow(this->init_lib.window_x * scale, this->init_lib.window_y * scale, this->init_lib.window_name.c_str());
        SetTargetFPS(this->init_lib.window_fps);
        _font = LoadFontEx(this->init_lib.font.c_str(), this->init_lib.font_size, nullptr, 0);
        if (_font.texture.id == 0) {
            std::stringstream ss;
            ss << "Error : Not a valid font file" << this->init_lib.font.c_str() << ", exiting";
            std::string font_error = ss.str();
            throw std::runtime_error(font_error);
        }
        SetTextureFilter(_font.texture, FILTER_BILINEAR);
        SetExitKey(KEY_NULL);
        _shouldClose = false;
        _scale = scale;
    }

    void Raylib::closeMyWindow() {
        CloseWindow();
    }

    bool Raylib::isMyKeyDown(Ikey key) {
        for (auto it = _mapKey.begin(); it != _mapKey.end(); it++) {
            if ((*it).second == key) {
                if (IsKeyDown((*it).first))
                    return (true);
            }
        }
        return (false);
    }

    int Raylib::getGamepadInput() {
        return GetGamepadButtonPressed();
    }

    Ikey Raylib::getInput() {
        int key = NO_EVENT;
        if (WindowShouldClose()) {
            return WINDOWCLOSE;
        }
        key = GetKeyPressed();
        if (key == 0)
            return (NO_EVENT);
        if (_mapKey.count(key) != 0)
            return _mapKey[key];
        if (_mapKey.count(key) == 0)
            return (UNKNOWN);
        return (NO_EVENT);
    }

    std::string Raylib::getName() {
        return "";
    }

    void Raylib::myClear() {
        ClearBackground(RAYWHITE);
    }

    void Raylib::changeAnimation(ModelSelection i, Component *component) {
        if ((*((RaylibAnimation*)(&(component->_entity->getComponent<AnimationComponent>().getAnimation())))).getActualAnimationState() != MODEL_DEATH) {
            RaylibAnimation *anims = &(*((RaylibAnimation*)(&(component->_entity->getComponent<AnimationComponent>().getAnimation()))));
            anims->setActualAnimationState(i);
        }
        return;
    }

    void Raylib::updateMusic() {
        UpdateMusicStream(_music);
    }

    void Raylib::draw_threed(Component *component)
    {
        UpdateCamera(&_camera);
        Raylib3DPerso model = *((Raylib3DPerso*)(&(component->_entity->getComponent<Perso3DComponent>().get3DPerso())));
        RaylibAnimation *anims = &(*((RaylibAnimation*)(&(component->_entity->getComponent<AnimationComponent>().getAnimation()))));
        int AnimeFC = component->_entity->getComponent<AnimationComponent>().getAnimation().getRaylibAnimeFrameCounetr(anims->getActualAnimationState());
        UpdateModelAnimation(model.getModel(anims->getActualAnimationState()), anims->getModelAnimation(anims->getActualAnimationState())[0], AnimeFC);
        if (AnimeFC >= anims->getModelAnimation(anims->getActualAnimationState())[0].frameCount)
            component->_entity->getComponent<AnimationComponent>().getAnimation().setResetAnimeFrameCounter(anims->getActualAnimationState());
        Vector3 position;
        if (model.getWinID() == 3)
            return;
        if (_sceneName == "winMenu") {
            if (model.getWinID() == 0) {
                position = {0.18, 0.4, 0.4};
            } else if (model.getWinID() == 1) {
                position = {-0.5, 0.4, 0.7};
            } else if (model.getWinID() == 2) {
                position = {0.78, 0.4, 0.8};
            }

        } else
            position = ((Raylib3DPerso*)(&(component->_entity->getComponent<Perso3DComponent>().get3DPerso())))->getPosition();
        Vector3 rotation = {0};
        rotation.x = 1.0;
        rotation.y = 0;
        rotation.z = 0;
        Vector3 scale = {0};
        scale.x = 1.0;
        scale.y = 1.0;
        scale.z = 1.0;
        BeginMode3D(_camera);
        DrawModelEx(model.getModel(anims->getActualAnimationState()), position, rotation, -90.0f,
                    scale, WHITE);
        EndMode3D();
    }

    void Raylib::reset_map(Component *component) {
        RaylibMap map = *((RaylibMap*)(&(component->_entity->getComponent<MapComponent>().getMap())));
    }

    bool Raylib::isPlayerIn(Component *bomb, Component * player) {
        std::pair<float, float >pos = this->moveXYZEntity(0, 0, 0, player);
        Raylib3DPerso &model = *((Raylib3DPerso*)(&(player->_entity->getComponent<Perso3DComponent>().get3DPerso())));
        Vector2 vector = {0};
        Rectangle rec = {0};
        vector.x = pos.first;
        vector.y = pos.second;
        rec.width = 1;
        rec.height = 1;
        rec.x = bomb->_entity->getComponent<BombComponent>().getPosition().first;
        rec.y = bomb->_entity->getComponent<BombComponent>().getPosition().second;
        if (CheckCollisionCircleRec(vector, 0.2, rec)) {
            return (true);
        } else {
            return (false);
        }
    }

    bool Raylib::checkPlayerColiBomb(Component *bomb, Component * player) {
        if (player->_entity->getComponent<StatsComponent>().getCanThrough())
            return (false);
        Raylib3DPerso &model = *((Raylib3DPerso*)(&(player->_entity->getComponent<Perso3DComponent>().get3DPerso())));
        Vector2 vector = {0};
        Rectangle rec = {0};
        vector.x = model.getPosition().x;
        vector.y = model.getPosition().z;
        rec.width = 1;
        rec.height = 1;
        rec.x = bomb->_entity->getComponent<BombComponent>().getPosition().first;
        rec.y = bomb->_entity->getComponent<BombComponent>().getPosition().second;
        for (auto it = bomb->_entity->getComponent<BombComponent>().getIsThrough().begin(); it != bomb->_entity->getComponent<BombComponent>().getIsThrough().end(); it++) {
            if (it->first == player->_entity->getComponent<Perso3DComponent>().get3DPerso().getPlayerID()) {
                if (CheckCollisionCircleRec(vector, 0.2, rec)) {
                    if (it->second) {
                        return (false);
                    } else {
                        return (true);
                    }
                } else {
                    it->second = false;
                }
            }
        }
        if (CheckCollisionCircleRec(vector, 0.2, rec)) {
            return (true);
        }
        return (false);
    }

    void Raylib::draw_map(Component *component)
    {
        UpdateCamera(&_camera);
        RaylibMap map = *((RaylibMap*)(&(component->_entity->getComponent<MapComponent>().getMap())));
        BeginMode3D(_camera);
        DrawModel(map.getMapModel(), map.getMapPosition(), 1.0f, WHITE);
        EndMode3D();
    }

    bool Raylib::getIsPaused() {
        return _isPaused;
    }

    void Raylib::myDraw(Component *component) {
        if (!component->_entity->hasComponent<PauseComponent>() && _isPaused == true)
            return;
        if (component->_entity->hasComponent<PauseComponent>() && _isPaused == false)
            return;
        if (component->_entity->hasComponent<BonusComponent>()) {
            UpdateCamera(&_camera);
            BeginMode3D(_camera);
            DrawModel(_modelLibrary[component->_entity->getComponent<BonusComponent>().getType()], {float(round(component->_entity->getComponent<BonusComponent>().getPos().second)), 0.5f, float(round(component->_entity->getComponent<BonusComponent>().getPos().first))}, 1.0f, WHITE);
            EndMode3D();
            return;
        }
        if (component->_entity->hasComponent<BombComponent>() && component->_entity->getComponent<BombComponent>().gethasExploded() == false) {
            std::pair<float, float> pos = component->_entity->getComponent<BombComponent>().getPosition();
            UpdateCamera(&_camera);
            BeginMode3D(_camera);
            DrawModel(_modelLibrary[BOMB], {float(round(pos.first)), 0.5f, float(round(pos.second))}, 1.0f, WHITE);
            EndMode3D();
            return;
        }
        if (component->_entity->hasComponent<BombComponent>() && component->_entity->getComponent<BombComponent>().gethasExploded() == true) {
            for (auto it = component->_entity->getComponent<BombComponent>().getVector().begin(); it != component->_entity->getComponent<BombComponent>().getVector().end(); it++) {
                BeginMode3D(_camera);
                UpdateCamera(&_camera);
                DrawModel(_modelLibrary[EXPLOSION], {float(round((*it).first)), 0.5f, float(round((*it).second))}, 1.0f, WHITE);
                EndMode3D();
            }
            return;
        } else if (component->_entity->hasComponent<BombComponent>())
            return;

        if (component->_entity->hasComponent<MapComponent>()) {
            draw_map(component);
            return;
        }
        if (component->_entity->hasComponent<Perso3DComponent>()) {
            draw_threed(component);
            return;
        }
        RaylibTexture texture = *((RaylibTexture*)(&(component->_entity->getComponent<TextureComponent>().getTexture())));
        Vector2 position;
        position.x = (component->_entity->getComponent<PositionComponent>().getPosition().x -
                     component->_entity->getComponent<TextureComponent>().getTexture().textureGetWidth() / 2) * _scale;
        position.y = (component->_entity->getComponent<PositionComponent>().getPosition().y -
                     component->_entity->getComponent<TextureComponent>().getTexture().textureGetHeight() / 2) * _scale;
        DrawTextureEx(texture.getTexture(), position, 0, _scale, WHITE);
        if (component->_entity->hasComponent<ButtonComponent>() && (_sceneName == "mainMenu" || (_sceneName == "game" && _isPaused) ||
            _sceneName == "winMenu" || (_sceneName == "save" && _isPaused))) {
            if (component->_entity->getComponent<ButtonComponent>().getState() == BUT_HOVER) {
                if (_sceneName == "winMenu") {
                    DrawTextureEx(_bombSelection, Vector2{ position.x + 520, position.y + 25 }, 0, _scale, WHITE);
                    _savedBombSelection = Vector{ position.x + 520, position.y + 20 };
                }
                else {
                    _savedBombSelection = Vector{ position.x + 220, position.y + 10 };
                    DrawTextureEx(_bombSelection, Vector2{ position.x + 220, position.y + 10 }, 0, _scale, WHITE);
                }
                if (_sceneName == "mainMenu")
                    _savedBombSelectionMainMenu = Vector{ position.x + 220, position.y + 10 };
            }
        }
        if (component->_entity->hasComponent<ButtonComponent>() && _sceneName == "characterSelectorMenu") {
            if (component->_entity->getComponent<ButtonComponent>().getState() == BUT_HOVER) {
                if (position.x < 500 && position.y > 100) {
                    DrawTextureEx(_bombSelection, Vector2{ position.x - 80, position.y + 5}, 0, _scale, WHITE);
                    _savedBombSelection = Vector{ position.x - 80, position.y + 5};
                } else if (position.x > 500 || position.y < 100) {
                    DrawTextureEx(_bombSelection, Vector2{ position.x + 125, position.y + 5 }, 0, _scale, WHITE);
                    _savedBombSelection = Vector{ position.x + 100, position.y + 5};
                }
            }
        }
        if (component->_entity->hasComponent<TextComponent>()) {
            Vector2 positiont;
            positiont.x = (component->_entity->getComponent<TextComponent>().getPosition().x -
                           (float)getTextSize((component->_entity->getComponent<TextComponent>().getText()),
                                              component->_entity->getComponent<TextComponent>().getSizeText()) / 2);
            positiont.y = (component->_entity->getComponent<TextComponent>().getPosition().y);
            DrawTextEx(_font, component->_entity->getComponent<TextComponent>().getText().c_str(),
                     positiont, (float)component->_entity->getComponent<TextComponent>().getSizeText(), 1, RAYWHITE);
        }
    }

    Vector Raylib::getSavedBombSelection() {
        return _savedBombSelectionMainMenu;
    }

    void Raylib::setSceneName(const std::string name)
    {
        _sceneName = name;
    }

    void Raylib::myRefresh() {

    }

    void Raylib::beginDrawing() {
        BeginDrawing();
    }

    void Raylib::endDrawing() {
        EndDrawing();
    }

    Vector Raylib::getMousePosition() {
        Vector iPosition;
        Vector2 rPosition = GetMousePosition();
        iPosition.x = rPosition.x;
        iPosition.y = rPosition.y;
        return iPosition;
    }

    bool Raylib::checkMouseCollision(Rect indierectangle) {
        Rectangle rectangle;
        rectangle.x = indierectangle.x;
        rectangle.y = indierectangle.y;
        rectangle.height = indierectangle.height;
        rectangle.width = indierectangle.width;
       Vector2 rPosition = GetMousePosition();
       if (CheckCollisionPointRec(rPosition, rectangle))
           return true;
       return false;
    }

    float Raylib::getWheel() {
        return (GetMouseWheelMove());
    }

   bool Raylib::isWindowClosed() {
       if (WindowShouldClose() || getClose())
           return true;
       return false;
   }

    bool Raylib::getClose() const {
        return (_shouldClose);
    }

    void Raylib::setClose(bool close) {
        _shouldClose = close;
    }

    int Raylib::getTextSize(std::basic_string<char> text, int fontSize) {
        const char *cstr = text.c_str();
        return MeasureText(cstr, fontSize);
    }

    float Raylib::getScale() {
        return _scale;
    }

    void Raylib::setScale(float scale) {
        _scale = scale;
    }

    void Raylib::changeDeathAnimation(Component * compo, std::vector<std::pair<float, float>> posPair, std::vector<State> &vec, int i, std::vector<int> &_winOrder) {
        std::vector<Vector3> pos;
        Vector3 position = ((Raylib3DPerso*)(&(compo->_entity->getComponent<Perso3DComponent>().get3DPerso())))->getPosition();
        if (vec[i] == DEAD)
            return;
        for (auto it = posPair.begin(); it != posPair.end(); it++)
            pos.push_back({(*it).first, 0, (*it).second});
        for (auto it = pos.begin(); it != pos.end(); it++) {
            if (round(position.x) == (*it).x && round(position.z) == (*it).z) {
                this->changeAnimation(MODEL_DEATH, compo);
                vec[i] = DEAD;
                _winOrder.push_back(i);
                compo->_entity->getComponent<Perso3DComponent>().setAlive(false);
            }
        }
    }

    bool Raylib::BonusHitbox(Component * compo, std::pair<float, float> posPair) {
        Vector3 position = ((Raylib3DPerso*)(&(compo->_entity->getComponent<Perso3DComponent>().get3DPerso())))->getPosition();
        if (round(position.x) == posPair.first && round(position.z) == posPair.second)
            return (true);
        return (false);
    }

    void Raylib::recreateLibrary() {
        UnloadTexture(_transitionToSettings);
        this->displayLoading(std::string("Loading 0%"));
        if (int(_scale * 10) / 10.0 == 1) {
            _transitionToSettings = LoadTexture("../assets/menu_to_settings.png");
        }
        else if (int(_scale * 10) / 10.0 == 0.8) {
            _transitionToSettings = LoadTexture("../assets/menu_to_settings_1526.png");
        }
        else if (int(_scale * 10) / 10.0 == 0.6) {
            _transitionToSettings = LoadTexture("../assets/menu_to_settings_1152.png");
        }


        this->displayLoading(std::string("Loading 6%"));
        _bombSelection = LoadTexture("../assets/MainMenu/bomb_selection.png");
        this->displayLoading(std::string("Loading 13%"));
        UnloadModel(_modelLibrary[BONUSRANGE]);
        UnloadModel(_modelLibrary[BONUSDOUBLE]);
        UnloadModel(_modelLibrary[BONUSSPEED]);
        UnloadModel(_modelLibrary[BONUSWALLCUBE]);
        UnloadModel(_modelLibrary[BOMB]);
        UnloadModel(_modelLibrary[EXPLOSION]);
        _modelLibrary[BONUSDOUBLE] = LoadModel("../assets/bonus/bonus.gltf");
        this->displayLoading(std::string("Loading 19%"));
        _modelLibrary[BONUSSPEED] = LoadModel("../assets/bonus/bonus.gltf");
        this->displayLoading(std::string("Loading 26%"));
        _modelLibrary[BONUSWALLCUBE] = LoadModel("../assets/bonus/bonus.gltf");
        this->displayLoading(std::string("Loading 33%"));
        _modelLibrary[BONUSRANGE] = LoadModel("../assets/bonus/bonus.gltf");
        this->displayLoading(std::string("Loading 39%"));
        _modelLibrary[BOMB] = LoadModel("../assets/bombe.gltf");
        this->displayLoading(std::string("Loading 46%"));
        _modelLibrary[EXPLOSION] = LoadModel("../assets/bomb/flame.gltf");
        this->displayLoading(std::string("Loading 53%"));
        Texture2D textureBomb = LoadTexture("../assets/bomb.png");
        this->displayLoading(std::string("Loading 59%"));
        SetMaterialTexture(&_modelLibrary[BOMB].materials[0], MAP_DIFFUSE, textureBomb);
        Texture2D textureBombExplosion = LoadTexture("../assets/bomb/flame_texture.png");
        this->displayLoading(std::string("Loading 66%"));
        SetMaterialTexture(&_modelLibrary[EXPLOSION].materials[0], MAP_DIFFUSE, textureBombExplosion);
        Texture2D textureB1 = LoadTexture("../assets/bonus/double_bomb.png");
        this->displayLoading(std::string("Loading 73%"));
        Texture2D textureB2 = LoadTexture("../assets/bonus/range_up_cube_texture.png");
        this->displayLoading(std::string("Loading 79%"));
        Texture2D textureB3 = LoadTexture("../assets/bonus/speed_up_cube_texture.png");
        this->displayLoading(std::string("Loading 86%"));
        Texture2D textureB4 = LoadTexture("../assets/bonus/wall_cube_texture.png");
        this->displayLoading(std::string("Loading 93%"));
        SetMaterialTexture(&_modelLibrary[BONUSRANGE].materials[0], MAP_DIFFUSE, textureB2);
        SetMaterialTexture(&_modelLibrary[BONUSDOUBLE].materials[0], MAP_DIFFUSE, textureB1);
        SetMaterialTexture(&_modelLibrary[BONUSWALLCUBE].materials[0], MAP_DIFFUSE, textureB4);
        SetMaterialTexture(&_modelLibrary[BONUSSPEED].materials[0], MAP_DIFFUSE, textureB3);
        this->displayLoading(std::string("Loading 100%"));
    }

    ITexture *Raylib::create_texture() {
        return new class RaylibTexture();
    }

    ICamera * Raylib::create_camera() {
        return new class RaylibCamera();
    }

    I3DPerso * Raylib::create_3d_perso() {
        return new class Raylib3DPerso();
    }

    IAnimation * Raylib::create_animation() {
        return new class RaylibAnimation();
    }

    IMap * Raylib::create_map() {
        return new class RaylibMap();
    }

    void Raylib::set_camera(Component &component) {
        RaylibCamera camera = *((RaylibCamera*) (&(component._entity->getComponent<CameraComponent>().getCamera())));
        _camera = camera.getCamera();
    }

    bool Raylib::checkPlayerColi(Component *first, Component *second, float x, float z) {
        if (first->_entity->getComponent<MapComponent>().getType() == 0 && second->_entity->getComponent<StatsComponent>().getCanThrough() == true)
            return (false);
        Raylib3DPerso &model = *((Raylib3DPerso*)(&(second->_entity->getComponent<Perso3DComponent>().get3DPerso())));
        RaylibMap map = *((RaylibMap*)(&(first->_entity->getComponent<MapComponent>().getMap())));
        Vector3 mapPosition = map.getMapPosition();
        Image img = map.getImage();
        Color *mapPixel = LoadImageColors(img);
        Texture2D cubicmap = map.getCubicMap();
        Vector2 vector = {0};
        Rectangle rec = {0};
        vector.x = model.getPosition().x;
        vector.y = model.getPosition().z;
        rec.width = 1;
        rec.height = 1;
        for (int y = 0; y < cubicmap.height; y++) {
            for (int u = 0; u < cubicmap.width; u++) {
                rec.x =  mapPosition.x - 0.5f + u*1.0f;
                rec.y = mapPosition.z - 0.5f + y*1.0f;
                if (mapPixel[y * cubicmap.width + u].r == 255 && CheckCollisionCircleRec(vector, 0.2f, rec)) {
                    return (true);
                }
            }
        }
        return (false);
    }

    int Raylib::getSoundVolume() {
        return _soundVolume;
    }

    int Raylib::getMusicVolume() {
        return _musicVolume;
    }

    void Raylib::setMusicVolume(int volume) {
        _musicVolume += volume;
        if (_musicVolume > 10)
            _musicVolume = 10;
        if (_musicVolume <= 0)
            _musicVolume = 0;
        SetMusicVolume(_music, (float)(_musicVolume / 10));
    }

    void Raylib::setSoundVolume(int volume) {
        _soundVolume += volume;
        if (_soundVolume > 10)
            _soundVolume = 10;
        if (_soundVolume < 0)
            _soundVolume = 0;
        SetSoundVolume(_sound,(float)(_soundVolume / 10));
    }

    void Raylib::unload_assets(Entity &entity) {
        if (entity.hasComponent<TextureComponent>()) {
            RaylibTexture texture = *((RaylibTexture*)(&(entity.getComponent<TextureComponent>().getTexture())));
            UnloadTexture(texture.getTexture());
            return;
        }
        if (entity.hasComponent<MapComponent>()) {
            RaylibMap map = *((RaylibMap*)(&(entity.getComponent<MapComponent>().getMap())));
            UnloadModel(map.getMapModel());
            UnloadTexture(map.getCubicMap());
            UnloadTexture(map.getTexture());
            UnloadImage(map.getImage());
        }
        if (entity.hasComponent<Perso3DComponent>()) {
            Raylib3DPerso model = *((Raylib3DPerso*)(&(entity.getComponent<Perso3DComponent>().get3DPerso())));
            UnloadModel(model.getModel(MODEL_IDDLE));
            UnloadModel(model.getModel(MODEL_ACTION));
            UnloadModel(model.getModel(MODEL_DEATH));
            UnloadTexture(model.getTexture());
        }
        if (entity.hasComponent<AnimationComponent>()) {
            RaylibAnimation *anims = &(*((RaylibAnimation*)(&(entity.getComponent<AnimationComponent>().getAnimation()))));

            for (int i = 0; i < anims->getRaylibAnimscount(MODEL_IDDLE); i++) UnloadModelAnimation(anims->getModelAnimation(MODEL_IDDLE)[i]);
            for (int i = 0; i < anims->getRaylibAnimscount(MODEL_ACTION); i++) UnloadModelAnimation(anims->getModelAnimation(MODEL_ACTION)[i]);
            for (int i = 0; i < anims->getRaylibAnimscount(MODEL_DEATH); i++) UnloadModelAnimation(anims->getModelAnimation(MODEL_DEATH)[i]);
            RL_FREE(anims->getModelAnimation(MODEL_IDDLE));
            RL_FREE(anims->getModelAnimation(MODEL_ACTION));
            RL_FREE(anims->getModelAnimation(MODEL_DEATH));
        }
    }

    void Raylib::displayLoading(std::string str) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextEx(_font, str.c_str(), {840 * _scale, 500 * _scale}, 40, 1, WHITE);
        EndDrawing();
    }

    void Raylib::displayIntro() {

        int video = 1;
        Texture2D transition = LoadTexture("../assets/intro/partie_1.png");
        this->displayLoading(std::string("Loading 75%"));
        int width = transition.width / 1920;
        int height = transition.height / 1080;
        Vector2 position = { 0.0f, 0.0f };
        Rectangle frameRec = { 0.0f, 0.0f, (float)transition.width / width, (float)transition.height / height };
        int currentFrame = 0;
        int frameNumber = 0;
        int framesCounter = 0;
        int framesSpeed = 17;
        Texture2D transition2 = LoadTexture("../assets/intro/partie_2.png");
        this->displayLoading(std::string("Loading 81%"));
        Texture2D transition3 = LoadTexture("../assets/intro/partie_3.png");
        this->displayLoading(std::string("Loading 87%"));
        Texture2D transition4 = LoadTexture("../assets/intro/partie_4.png");
        this->displayLoading(std::string("Loading 92%"));
        _transitionToSettings = LoadTexture("../assets/menu_to_settings.png");
        this->displayLoading(std::string("Loading 100%"));
        while (video != 5) {
            UpdateMusicStream(_music);
            framesCounter++;
            if (video == 1) {
                if (frameNumber != (width * height) - 1) {
                    if (framesCounter >= (60 / framesSpeed))
                    {
                        frameNumber++;
                        framesCounter = 0;
                        currentFrame++;

                        if (currentFrame > height) {
                            currentFrame = 0;
                            frameRec.y += float(1080);
                        }

                        frameRec.x = (float)currentFrame*(float)transition.width/width;
                    }
                } else {
                    video = 2;
                    framesCounter = 0;
                    width = transition2.width / 1920;
                    height = transition2.height / 1080;
                    currentFrame = 0;
                    frameNumber = 0;
                    framesCounter = 0;
                    frameRec = { 0.0f, 0.0f, (float)transition2.width / width, (float)transition2.height / height };
                }
            }
            else if (video == 2) {
                if (frameNumber != (width * height) - 1) {
                    if (framesCounter >= (60 / framesSpeed))
                    {
                        frameNumber++;
                        framesCounter = 0;
                        currentFrame++;

                        if (currentFrame > height) {
                            currentFrame = 0;
                            frameRec.y += float(1080);
                        }

                        frameRec.x = (float)currentFrame*(float)transition2.width / width;
                    }
                } else {
                    video = 3;
                    framesCounter = 0;
                    width = transition3.width / 1920;
                    height = transition3.height / 1080;
                    currentFrame = 0;
                    frameNumber = 0;
                    framesCounter = 0;
                    frameRec = { 0.0f, 0.0f, (float)transition3.width / width, (float)transition3.height / height };
                }
            } else if (video == 3) {
                if (frameNumber != (width * height) - 1) {
                    if (framesCounter >= (60 / framesSpeed))
                    {
                        frameNumber++;
                        framesCounter = 0;
                        currentFrame++;

                        if (currentFrame > height) {
                            currentFrame = 0;
                            frameRec.y += float(1080);
                        }

                        frameRec.x = (float)currentFrame*(float)transition3.width / width;
                    }
                } else {
                    video = 4;
                    framesCounter = 0;
                    width = transition3.width / 1920;
                    height = transition3.height / 1080;
                    currentFrame = 0;
                    frameNumber = 0;
                    framesCounter = 0;
                    frameRec = { 0.0f, 0.0f, (float)transition4.width / width, (float)transition4.height / height };
                }
            } else if  (video == 4) {
                if (frameNumber != (width * height) - 1) {
                    if (framesCounter >= (60 / framesSpeed))
                    {
                        frameNumber++;
                        framesCounter = 0;
                        currentFrame++;

                        if (currentFrame > height) {
                            currentFrame = 0;
                            frameRec.y += float(1080);
                        }

                        frameRec.x = (float)currentFrame*(float)transition4.width / width;
                    }
                } else {
                    video = 5;
                }
            }
            BeginDrawing();
            if (video == 1) {
                DrawTextureRec(transition, frameRec, position, WHITE);  // Draw part of the texture
            } else if (video == 2) {
                DrawTextureRec(transition2, frameRec, position, WHITE);  // Draw part of the texture
            } else if (video == 3) {
                DrawTextureRec(transition3, frameRec, position, WHITE);  // Draw part of the texture
            } else if (video == 4) {
                DrawTextureRec(transition4, frameRec, position, WHITE);  // Draw part of the texture
            }
            EndDrawing();
        }

        UnloadTexture(transition);
        UnloadTexture(transition2);
        UnloadTexture(transition3);
        UnloadTexture(transition4);
    }

    void Raylib::menuToSettings() {
        ClearBackground(BLACK);
        int video = 1;
        int width = _transitionToSettings.width / (1920 * _scale);
        int height = _transitionToSettings.height / (1080 * _scale);
        Vector2 position = { 0.0f, 0.0f };
        Rectangle frameRec = { 0.0f, 0.0f, (float)_transitionToSettings.width / width, (float)_transitionToSettings.height / height };
        int currentFrame = 0;
        int frameNumber = 0;
        int framesCounter = 0;

        int framesSpeed = 17;

        while (video == 1) {
            UpdateMusicStream(_music);
            framesCounter++;
            if (video == 1) {
                if (frameNumber != (width * height) - 1) {
                    if (framesCounter >= (60 / framesSpeed))
                    {
                        frameNumber++;
                        framesCounter = 0;
                        currentFrame++;

                        if (currentFrame > height) {
                            currentFrame = 0;
                            frameRec.y += float(1080 * _scale);
                        }

                        frameRec.x = (float)currentFrame*(float)_transitionToSettings.width/width;
                    }
                } else {
                    video = 2;
                }
            }
            BeginDrawing();
            if (video == 1) {
                DrawTextureRec(_transitionToSettings, frameRec, position, WHITE);  // Draw part of the texture
            }
            EndDrawing();
        }
    }
}
