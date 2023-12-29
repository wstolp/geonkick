/**
 * File name: LgWidgetImpl.h
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2023 Iurie Nistor 
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

#ifndef LWG_WIDGET_IMPL_H
#define LWG_WIDGET_IMPL_H

#include "LgWidget.h"
#include "RkObjectImpl.h"

class RkWidget;

class LgWidget::LgWidgetImpl : public RkObject::RkObjectImpl {
 public:
        explicit LgWidgetImpl(LgWidget* interface,
                              LgWidget* parent = nullptr,
                              Lg::WindowFlags flags = Lg::WindowFlags::Widget,
                              bool isTopWindow = false);
        LgWidgetImpl(const LgWidget &other) = delete;
        LgWidgetImpl& operator=(const LgWidgetImpl &other) = delete;
        LgWidgetImpl(LgWidgetImpl &&other) = delete;
        LgWidgetImpl& operator=(LgWidgetImpl &&other) = delete;
        virtual ~LgWidgetImpl();
        Lg::WindowFlags windowFlags() const;
        void show(bool b);
	bool isShown() const;
        void setTitle(const std::string &title);
        const std::string& title() const;
        bool isClose() const;
        void event(LgEvent *event);
        void setSize(const LgSize &size);
        LgSize size() const;
        int minimumWidth() const;
        int maximumWidth() const;
        int minimumHeight() const;
        int maximumHeight() const;
        void setMinimumWidth(int width);
        void setMaximumWidth(int widht);
        void setMinimumHeight(int heigth);
        void setMaximumHeight(int heigth);
        void setPosition(const LgPoint &position);
        LgPoint position() const;
        void setBorderWidth(int width);
        int borderWidth() const;
        void setBorderColor(const LgColor &color);
        const LgColor &borderColor() const;
        void setBackgroundColor(const LgColor &color);
        const LgColor& background() const;
        LgRect rect() const;
        void update();
        static Lg::WidgetAttribute defaultWidgetAttributes();
        Lg::Modality modality() const;
        void setWidgetAttribute(Lg::WidgetAttribute attribute);
        void clearWidgetAttribute(Lg::WidgetAttribute attribute);
        Lg::WidgetAttribute getWidgetAttributes() const;
        void setFocus(bool b);
        bool hasFocus() const;
        void setTextColor(const LgColor &color);
        const LgColor& textColor() const;
        const LgColor& color() const;
        void setColor(const LgColor &color);
        const LgFont& font() const;
        void setFont(const LgFont &font);
        void setPointerShape(Lg::PointerShape shape);
        Lg::PointerShape pointerShape() const;
        void enableGrabKey(bool b);
        bool grabKeyEnabled() const;
        void propagateGrabKey(bool b);
        bool propagateGrabKeyEnabled() const;
        bool pointerIsOverWindow() const;
        void setScaleFactor(double factor);
        double scaleFactor() const;
        void setSystemWindow(RkWidget *window);
        RkWidget* getSystemWindow() const;

 private:
        RK_DECALRE_INTERFACE_PTR(LgWidget);
        std::string widgetTitle;
        bool widgetClosed;
        LgPoint widgetPosition;
        LgSize widgetMinimumSize;
        LgSize widgetMaximumSize;
        LgSize widgetSize;
        LgColor widgetBackground;
        Lg::WidgetAttribute widgetAttributes;
        Lg::Modality widgetModality;
        LgColor widgetBorderColor;
        LgColor widgetTextColor;
        LgColor widgetDrawingColor;
        LgFont widgetFont;
        Lg::PointerShape widgetPointerShape;
	bool isWidgetSown;
        bool isGrabKeyEnabled;
        bool isPropagateGrabKey;
        RkWidget* systemWindow;
};

#endif // LWG_WIDGET_IMPL_H
