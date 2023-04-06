#ifndef QTUTILSBABEL
#define QTUTILSBABEL

#ifdef _WIN32
#define _WIN32_WINNT  0x0601
#endif

enum events {
    goToRegister,
    goToLogin,
    LoginEvent,
    RegisterEvent,
    connectToServerEvent,
    PACKETRECEIVED,
    addFriendEvent,
    STOPCALLPLEASE,
    STOPTRYINGTOCALL = 1000,
    DECLINECALL,
    ACCEPTCALL
};

enum inputIds {
    RegisterUsernameInput,
    RegisterPasswordInput,
    LoginPasswordInput,
    LoginUsernameInput,
    LoginIPInput,
    LoginPortInput,
    friendChanged
};

enum responseEvent {
    OKEVENT,
    IPNOTOKEVENT,
    IPOKEVENT,
    TRYINGTOCONNECT,
    ACCOUNTALREADYEXIST,
    ACCOUNTCREATED
};

enum ConnectionEvents {
    SOCKETUNCONNECTED,
    SOCKETHOSLOOKUPSTATE,
    SOCKETCONNECTINGSTATE,
    SOCKETCONNECTEDSTATE
};

#endif