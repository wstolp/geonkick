/**
 * File name: painter.cpp
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
#include "RkPainter.h"
#include "RkPoint.h"
#include "RkLog.h"
#include "RkEvent.h"

class  PainterExample: public LgWidget {
  public:
        PainterExample(LgWidget *parent)
                : LgWidget(parent)
                , clickPoint(50, 50)
                , startDraw{true}
        {
                RK_LOG_INFO("called");
                setBackgroundColor(80, 80, 80);
        }

        ~PainterExample() = default;

  protected:
        void paintEvent(LgPaintEvent *event) override
        {
                RkPainter painter(this);
                LgPen pen(RkColor(255, 0, 0));
                pen.setWidth(1);
                pen.setStyle(RkPen::PenStyle::DashLine);
                painter.setPen(pen);
                painter.drawLine({10, 10}, {100, 100});
                painter.drawCircle(50, 50, 40);
                painter.fillRect({50, 50, 20, 20}, background());
                pen.setStyle(LgPen::PenStyle::DotLine);
                pen.setColor({0, 55, 123});
                painter.setPen(pen);
                painter.drawRect({10, 10, 10, 10});
        }

        void mouseButtonPressEvent(LgMouseEvent *event) override
        {
                clickPoint = RkPoint(event->x(), event->y());
                startDraw = !startDraw;
                update();
        }

        void mouseMoveEvent(LgMouseEvent* event) override
        {
                if (startDraw) {
                        clickPoint = LgPoint(event->x(), event->y());
                        update();
                }
        }

  private:
        LgPoint clickPoint;
        bool startDraw;
};

int main(int arc, char **argv)
{
    RkMain app(arc, argv);

    auto window = new RkWidget(&app);
    window->setTitle("Painter Example");
    window->setSize(350, 350);
    window->show();

    auto parent = new LgWidget(window);
    parent->setBackgroundColor(40, 40, 40);
    parent->setTitle("Main Widget");
    parent->setSize(window->size());
    parent->show();

    auto child = new PainterExample(parent);
    child->setBackgroundColor(150, 150, 150);
    child->setTitle("Child Widget");
    child->setPosition(20, 20);
    child->setSize(100, 100);
    child->show();

    return app.exec();
}
