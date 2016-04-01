#include <iostream>
#include "Button.h"

using namespace std;

void slot1()
{
    cout << __func__ << endl;
}

void slot2()
{
    cout << __func__ << endl;
}

int main()
{
    Button button;
    button.add_handler(slot1);
    button.add_handler(slot2);
    button.click();
    return 0;
}
