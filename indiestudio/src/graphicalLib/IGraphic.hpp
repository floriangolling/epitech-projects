//
// Created by jbroesch on 5/17/21.
//

#ifndef B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_IGRAPHICAL_HPP
#define B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_IGRAPHICAL_HPP

#define XBOX360_LEGACY_NAME_ID  "Xbox Controller"
#if defined(PLATFORM_RPI)
#define XBOX360_NAME_ID     "Microsoft X-Box 360 pad"
#define PS3_NAME_ID         "PLAYSTATION(R)3 Controller"
#else
#define XBOX360_NAME_ID     "Xbox 360 Controller"
#define PS3_NAME_ID         "PLAYSTATION(R)3 Controller"
#endif

#include "../utils/utils.hpp"
#include "../ecs/Entity.hpp"
#include "raylib.h"
#include "../ecs/ComponentsList/TextureComponent.hpp"
#include "../ecs/ComponentsList/RectangleComponent.hpp"
#include "../ecs/ComponentsList/Perso3DComponent.hpp"
#include "RaylibCamera.hpp"
#include "ITexture.hpp"
#include "ICamera.hpp"
#include "IAnimation.hpp"
#include "I3DPerso.hpp"
#include "IMap.hpp"
#include <string>
#include <vector>

namespace Indie {
    class IGraphic {
    public :
        virtual ~IGraphic() = default;
        virtual void displayLoading(std::string str) = 0;
        virtual void setPersoToSky(Component *compo) = 0;
        virtual bool checkPlayerColi(Component *, Component *, float, float) = 0;
        virtual void changeAnimation(ModelSelection, Component *) = 0;
        virtual bool checkPlayerColiBomb(Component *, Component *) = 0;
        virtual bool BonusHitbox(Component * compo, std::pair<float, float> posPair) = 0;
        virtual std::pair<float, float> moveXYZEntity(float x, float y, float z, Component *compo) = 0;
        virtual std::pair<float, float> setXYZEntity(float x, float y, float z, Component *compo) = 0;
        virtual void rotateAngle(float x, float y, float z, Component *compo) = 0;
        virtual void setPause(bool pause) = 0;
        virtual bool isPlayerIn(Component *, Component *) = 0;
        virtual void beginDrawing() = 0;
        virtual void myDraw(Component*) = 0;
        virtual void endDrawing() = 0;
        virtual void myClear() = 0;
        virtual void myRefresh() = 0;
        virtual Indie::Ikey getInput() = 0;
        virtual int getGamepadInput() = 0;
        virtual void moveBombSelection(Vector) = 0;
        virtual bool checkGamepadButton(int, int) = 0;
        virtual bool checkAxisButton(int, int, float, int) = 0;
        virtual bool getGamepadAxisCharacterSelector(int, float) = 0;
        virtual Vector getMousePosition() = 0;
        virtual bool checkMouseCollision(Rect) = 0;
        virtual bool isWindowClosed() = 0;
        virtual std::string getName() = 0;
        virtual void setClose(bool) = 0;
        virtual void reset_map(Component *) = 0;
        virtual bool getClose() const = 0;
        virtual void createSpriteLibrarie() = 0;
        virtual void recreateLibrary() = 0;
        virtual void changeDeathAnimation(Component *, std::vector<std::pair<float, float >>, std::vector<State> &vec, int i, std::vector<int> &_winOrder) = 0;
        virtual std::string getInputAsString(Ikey) = 0;
        virtual int getTextSize(std::basic_string<char> text, int fontSize) = 0;
        virtual void init_window() = 0;
        virtual float getScale() = 0;
        virtual void setScale(float) = 0;
        virtual float getWheel() = 0;
        virtual ITexture *create_texture() = 0;
        virtual ICamera *create_camera() = 0;
        virtual I3DPerso *create_3d_perso() = 0;
        virtual IAnimation *create_animation() = 0;
        virtual void set_camera(Component&) = 0;
        virtual void closeMyWindow() = 0;
        virtual void openMyWindow(float scale) = 0;
        virtual IMap * create_map() = 0;
        virtual void setSoundVolume(int) = 0;
        virtual int getSoundVolume() = 0;
        virtual void setMusicVolume(int) = 0;
        virtual int getMusicVolume() = 0;
        virtual void draw_map(Component *component) = 0;
        virtual void unload_assets(Entity&) = 0;
        virtual void setSceneName(const std::string) = 0;
        virtual Vector getSavedBombSelection() = 0;
        virtual bool getIsPaused() = 0;
        virtual bool isBombButtonPressed(int, int) = 0;
        virtual void makeSoundExplosion() = 0;
        virtual void displayIntro() = 0;
        virtual void menuToSettings() = 0;
        typedef struct init_graphicallib {
            int window_x;
            int window_y;
            std::string window_name;
            int window_fps;
            std::string font;
            int font_size;
            std::string music;
            std::string sound;
        } init_graphicallib;
        init_graphicallib init_lib;
        virtual bool isMyKeyDown(Ikey) = 0;
        virtual void updateMusic() = 0;

    };
}
#endif //B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_IGRAPHICAL_HPP
