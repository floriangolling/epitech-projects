#ifndef COREBABEL
#define COREBABEL

#include "../utils/utils.hpp"
#include "../GUI/GraphLib/Igraphic.hpp"
#include <iostream>
#include "../Network/Qclient.hpp"
#include "../../common/PacketDecoder.hpp"
#include "../../common/PacketEncoder.hpp"

class Core {
    public:
        Core();
        Core(const Core&) =delete;
        Core& operator=(const Core&) =delete;
        ~Core();
        int display();
        void init(int &, char *[]);
        int manageEvent(int);
        void manageTextEvent(const std::string &, int);
        int managePacket(std::vector<uint8_t>);
        void manageIDCall(int id);
    private:
        IGraphic *_libgraphic;
        Client *_client;
};

#endif