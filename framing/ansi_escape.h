#pragma once

#include "frame.h"

#include <vector>
#include <map>
#include "frame.h"

using std::map;

struct AnsiFrameState
{
};

class AnsiEscapeTerm : public Framer
{
public:
    bool update() override;
    bool open() override;
    void close() override;
    void onWrite(Frame* pWhichFrame) override;
    void onResolution(Frame* pWhichFrame) override;
    tuple<int, int> maxResolution() const override;
protected:
    bool onAdd(Frame* pf) override;
    void print(AnsiFrameState* pfState, int x, int y, const string& text);
private:
    map<Frame*, AnsiFrameState> _states;
};
