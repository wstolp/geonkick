#include "RkMain.h"
#include "LgWidget.h"

int main(int arc, char **argv)
{
    LgMain app(arc, argv);

    auto widget = new LgWidget(app);
    widget->setTitle("Hello!");
    widget->setBackgroundColor({80, 80, 80});
    widget->show();

    int res = app.exec();
    return res;
}
