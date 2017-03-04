#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <tuple>

using std::tuple;
using std::vector;
using std::string;

struct Color
{
    int rgb;
    bool paletted;
};

struct Cell
{
    string value; // must be a string for multibyte chars
    Color fg;
    Color bg;
};

class Frame;

class Framer
{
public:
    Framer();
    virtual ~Framer();
    bool add(Frame* pf, size_t index = static_cast<size_t>(-1));

    bool open();
    void close();
    virtual bool update() = 0;
    void invalidate(Frame* pf, int x = 0, int y = 0);
    virtual void onResolution(Frame*) = 0;
    virtual tuple<int, int> maxResolution() const = 0;
protected:
    virtual bool onOpen() { return true; }
    virtual void onClose() { }
    virtual void onWrite(Frame* pf, int x, int y, const Cell& cell) = 0;
    virtual bool onAdd(Frame* pf) { return true; }
    vector<Frame*> _frames;
};

class Frame
{
public:
    Frame();
    virtual ~Frame();
    void framer(Framer* pfr);
    Framer* framer() const;

    void foreground(const Color& color);
    const Color& foreground() const;
    void background(const Color& color);
    const Color& background() const;
    vector<const Cell*> scan(int x, int y, int width) const;
    const Cell* get(int x, int y) const;
    void set(int x, int y, const Cell& cell);
    void set(int x, int y, const string& text);
    void set(int x, int y, const vector<const Cell*>& scanned);

    bool setResolution(int width, int height, bool bQuiet = false);
    tuple<int, int> getResolution() const;
    bool scrolling() const;
    void scrolling(bool enable);
protected:
    void resizeBuffer(int width, int height);
private:
    Framer* _framer;

    int _width;
    int _height;

    bool _scrolling;

    Cell* _cells = nullptr;
    Color _bg;
    Color _fg;
};

namespace Factory
{
    Framer* create_framer(const string& framerTypeName);
};
