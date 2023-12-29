#include "RkMain.h"
#include "LgWidget.h"
#include "RkLog.h"

int main(int arc, char **argv)
{
    RK_LOG_INFO("called");
    RkMain app(arc, argv);

    auto widget = new LgWidget();
    widget->setTitle("Hello!");
    widget->setBackgroundColor({80, 80, 80});
    widget->show();

    int res = app.exec();
    return res;
}
