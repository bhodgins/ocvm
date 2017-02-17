#pragma once

#include "component.h"
#include <queue>
using std::queue;

class Computer : public Component
{
public:
    Computer();
    ~Computer();

    bool run();
    bool load(const string& machinePath);
    bool newlib(LuaProxy* proxy);
    void close();
    void setTmpAddress(const string& addr);

    static double now();

    int setArchitecture(lua_State* lua);
    int getArchitecture(lua_State* lua);
    int getArchitectures(lua_State* lua);
    int address(lua_State* lua);
    int beep(lua_State* lua);
    int getDeviceInfo(lua_State* lua);
    int getProgramLocations(lua_State* lua);
    int pushSignal(lua_State* lua);
    int removeUser(lua_State* lua);
    int addUser(lua_State* lua);
    int isRobot(lua_State* lua);
    int tmpAddress(lua_State* lua);
    int freeMemory(lua_State* lua);
    int totalMemory(lua_State* lua);
    int energy(lua_State* lua);
    int maxEnergy(lua_State* lua);
    int realTime(lua_State* lua);
protected:
    bool onInitialize(Value& config) override;
    bool resume(int nargs);
    double trace(lua_State* lua);
private:
    void injectCustomLua();

    double _start_time;
    string _tmp_address;
    lua_State* _state = nullptr;
    lua_State* _machine = nullptr;
    double _standby = 0;
    double _nexttrace = 0;

    queue<ValuePack> _signals;
};
