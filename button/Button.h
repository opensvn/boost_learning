#ifndef _BUTTON_H

#include <vector>
#include <boost/signal.hpp>
#include <boost/function.hpp>

class Button
{
public:
    void add_handler(boost::function<void()> handle)
    {
        handles.connect(handle);
    }

    void remove_handler(boost::function<void()> handle)
    {
        handles.disconnect(handle);
    }

    void click()
    {
        handles();
    }

private:
    boost::signal<void()> handles;
};

#endif // _BUTTON_H
