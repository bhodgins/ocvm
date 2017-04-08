#include "log.h"
#include "io/frame.h"

#include <iostream>
using std::cout;
using std::cerr;

Logger lout(1);
Logger lerr(0);

class LogFrame : public Frame
{
public:
    LogFrame()
    {
        scrolling(true);
    }
    ~LogFrame()
    {
    }
} single_log_frame;

Frame* Logger::getFrame()
{
    return &single_log_frame;
}

Logger::Logger(int priority) :
    _priority(priority)
{
}

Logger& operator<< (Logger& logger, const string& text)
{
    Frame* pf = Logger::getFrame();
    if (!logger.priority())
        cerr << text;
    pf->write(1, 1, {text, {}, {}, false, (int)text.size()});
    return logger;
}

Logger& operator<< (Logger& logger, std::ostream& (*pf)(std::ostream&))
{
    logger << "\n";
    return logger;
}
