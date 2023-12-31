/**
 * File name: child.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor
 *
 * This file is part of Redkite.
 *
 * Redkite is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "RkMain.h"
#include "RkWidget.h"
#include "LgWidget.h"
#include "RkLog.h"

#include <vector>

int main(int arc, char **argv)
{
        LgMain app(arc, argv);

        // Create main window.
        auto mainWindow = new LgWidget(app);
        mainWindow->setTitle("Main Window");
        mainWindow->setPosition(180, 180);
        mainWindow->setSize(400, 500);
        mainWindow->setBackgroundColor(80, 80, 80);

        int x = 10;
        int y = 10;
        RK_LOG_DEBUG("create childs");
        auto n = mainWindow->size().area() / RkSize(60, 60).area();
        for (auto i = 0; i < n; i++) {
                auto child = new LgWidget(mainWindow);
                child->setTitle("Child[" + std::to_string(i) + "] - LEVEL 1");
                child->setSize(60, 60);
                child->setPosition(x, y);
                child->setBackgroundColor((5 * i) % 255, (10 * i) % 255, (20 * i) % 255);
                child->show();

                auto child_l = new LgWidget(child);
                child_l->setTitle("Child[" + std::to_string(i) + "] - LEVEL 2");
                child_l->setPosition(10, 10);
                child_l->setSize(30, 30);
                child_l->setBorderColor(0, 0, 255);
                child_l->setBackgroundColor(255, 0, 0);
                child_l->show();

                for (size_t k = 0; k < 5; k++) {
                        auto c = new LgWidget(child_l);
                        c->setTitle("Child[" + std::to_string(i) + "] - LEVEL 3");
                        c->setPosition(5 * k + 3, 5 * k + 3);
                        c->setSize(5, 5);
                        c->setBorderColor(10, 10, 10);
                        c->setBackgroundColor(10, 10, 10);
                        c->show();
                }

                x += child->width() + 5;
                if (x > mainWindow->width()) {
                        y += child->height() + 5;
                        x = 10;
                }
        }

        mainWindow->show();
        int res = app.exec();
        return res;
}
