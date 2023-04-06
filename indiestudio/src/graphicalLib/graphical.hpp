//
// Created by jbroesch on 5/15/21.
//

#ifndef B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_GRAPHICAL_H
#define B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_GRAPHICAL_H

#include "IGraphic.hpp"
#include "../utils/utils.hpp"
#include "ITexture.hpp"

namespace Indie {

    class Raylib : public IGraphic {
    public :
        Raylib();
        ~Raylib() override;
        void displayLoading(std::string) override;
        void setPause(bool pause) override;
        void setPersoToSky(Component *compo) override;
        bool BonusHitbox(Component * compo, std::pair<float, float> posPair) override;
        void createSpriteLibrarie() override;
        bool isPlayerIn(Component *, Component *) override;
        bool checkPlayerColiBomb(Component *, Component *) override;
        bool checkPlayerColi(Component *, Component *, float, float) override;
        void changeAnimation(ModelSelection, Component *) override;
        std::pair<float, float>  moveXYZEntity(float x, float y, float z, Component *compo) override;
        std::pair<float, float>  setXYZEntity(float x, float y, float z, Component *compo) override;
        void rotateAngle(float x, float y, float z, Component *compo) override;
        bool isMyKeyDown(Ikey) override;
        void beginDrawing() override;
        void myDraw(Component *component) override;
        void endDrawing() override;
        void myClear() override;
        void myRefresh() override;
        Indie::Ikey getInput() override;
        int getGamepadInput() override;
        bool checkAxisButton(int, int, float, int) override;
        bool getGamepadAxisCharacterSelector(int, float) override;
        bool checkGamepadButton(int, int) override;
        bool checkMouseCollision(Rect) override;
        bool isWindowClosed() override;
        std::string getName() override;
        Vector getMousePosition() override;
        void moveBombSelection(Vector) override;
        void setClose(bool) override;
        bool getClose() const override;
        std::string getInputAsString(Ikey key) override;
        int getTextSize(std::basic_string<char> text, int fontSize) override;
        void init_window() override;
        void setScale(float) override;
        float getScale() override;
        float getWheel() override;
        void openMyWindow(float scale) override;
        void closeMyWindow() override;
        ITexture *create_texture() override;
        ICamera *create_camera() override;
        I3DPerso *create_3d_perso() override;
        IAnimation *create_animation() override;
        IMap * create_map() override;
        void set_camera(Component&) override;
        void draw_threed(Component *component);
        void setSoundVolume(int) override;
        int getSoundVolume() override;
        void setMusicVolume(int) override;
        int getMusicVolume() override;
        void draw_map(Component *component) override;
        void unload_assets(Entity&) override;
        void reset_map(Component *component) override;
        void recreateLibrary() override;
        void changeDeathAnimation(Component *, std::vector<std::pair<float, float>>, std::vector<State> &vec, int i, std::vector<int> &_winOrder) override;
        void setSceneName(const std::string) override;
        Vector getSavedBombSelection() override;
        bool getIsPaused() override;
        bool isBombButtonPressed(int, int) override;
        void updateMusic() override;
        void makeSoundExplosion() override;
        void displayIntro() override;
        void menuToSettings() override;
        enum library {
            BOMB,
            EXPLOSION,
            BONUSRANGE,
            BONUSSPEED,
            BONUSWALLCUBE,
            BONUSDOUBLE
        };
    private :
        bool _isPaused;
        Camera _camera;
        bool _shouldClose;
        Font _font;
        float _scale;
        Texture2D _transitionToSettings;
        float _musicVolume;
        float _soundVolume;
        std::vector<Model> _modelLibrary;
        Texture2D _bombSelection;
        Vector _savedBombSelection = {0};
        Vector _savedBombSelectionMainMenu = { 0 };
        std::string _sceneName;
        Music _music;
        Sound _sound;
    };
}

#endif //B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_GRAPHICAL_H
