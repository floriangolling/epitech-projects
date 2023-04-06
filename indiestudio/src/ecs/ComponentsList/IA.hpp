#include "../Component.hpp"
#include "../../graphicalLib/IGraphic.hpp"
#include <vector>

namespace Indie {
    class IA : public Component {
    public:
        IA(std::array<std::string, 13> map, std::pair<float, float> , std::pair<float, float>, int id);
        void update(double time) override;
        void setPlantBomb(bool);
        void init(IGraphic *libgraphic) override;
        void setDestruction();
        void moveToTarget(std::array<std::string, 13> map, IGraphic &libgraphic, Component *compo, float time);
        bool moveToTargetSpecialCase();
        bool moveIfBombOnLine();
        void moveToDirection(IGraphic &libgraphic, Component *compo, float time);

        void updateMap(std::array<std::string, 13> map);

        void addSavePos();
        void findSafePos();
        bool isSafe();

        bool checkBarrier(int x, int y, Direction direction = NONEIA, bool next = false);
        bool checkBombOnLine(int x, int y, Direction direction);
        bool checkBarrierAround(int x, int y, Direction direction);

        int getType();

        std::vector<std::pair<int, int>> getPosBombEnemyOnLine();
        std::pair<float, float> plantBombe(std::array<std::string, 13> &map);
        void bombExplode(Component *compo);
        void setSafeMode(bool);
        bool plantBombeNearEnemies(std::vector<std::pair<float, float>> posEnemies);
        void takeBonus(std::array<std::string, 13> &map);

        void setPosTarget(std::vector<std::pair<float, float>> posEnemies);
        void setPosIA(float x, float z);
        void setTravelWall(bool boolean);

        bool getSafeMode() const;
        std::vector<float> getPosPlayer() const;
        std::vector<int> getPosTarget() const;
        time_t getTimingBombe() const;
        bool getPlantBomb() const;
        Direction getDirection() const;
        void setPosBombPlayer(std::pair<int, int>);
    private:
        std::pair<float, float> _posPlayer;
        std::pair<int, int> _posTarget;
        std::pair<int, int> _posBombPlayer;
        int _myRange;
        std::array<std::string, 13> _myMap;
        int _id;
        Direction _mvtDirection;
        bool _safeMode;
        time_t _timing;
        bool _plantBomb;
        float _posAdd;
        float _speed;
        bool _travelWall;
    };
};