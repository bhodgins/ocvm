#pragma once
#include "component.h"
#include "value.h"
#include "io/frame.h"

class Screen : public Component, public Frame
{
public:
    Screen();
    int getKeyboards(lua_State*);

    void addKeyboard(const string& addr);
protected:
    bool onInitialize(Value& config) override;
private:
    vector<string> _keyboards;
};
