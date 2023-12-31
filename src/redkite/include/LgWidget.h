/**
 * File name: LgWidget.h
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

#ifndef LGW_WIDGET_H
#define LGW_WIDGET_H

#include "Rk.h"
#include "RkEvent.h"
#include "LgObject.h"
#include "RkRect.h"
#include "RkColor.h"
#include "RkFont.h"
#include "RkCanvas.h"

class LgMain;

class LgWidget: public LgObject, public LgCanvas {
  public:
          RK_CLASS_INFO(style_element, "LgWidget")
          RK_CLASS_INFO(style_class, "")
          RK_CLASS_INFO(style_id, "")
          explicit LgWidget(LgMain& app,
                            Lg::WindowFlags flags = Lg::WindowFlags::Widget);
          explicit LgWidget(LgWidget *parent,
                            Lg::WindowFlags flags = Lg::WindowFlags::Widget);
          virtual ~LgWidget();
          Lg::WindowFlags windowFlags() const;
	  void show(bool b = true);
	  bool isShown() const;
          void hide();
          void setTitle(const std::string &title);
	  const std::string& title() const;
	  bool isClose() const;
          LgWidget* parentWidget() const;
	  void setSize(int w, int h);
	  void setSize(const LgSize &size);
	  LgSize size() const;
	  void setWidth(int w);
	  int width() const;
          int minimumWidth() const;
          int maximumWidth() const;
          void setMinimumWidth(int width);
          void setMaximumWidth(int width);
	  void setHeight(int h);
	  int height() const;
          int minimumHeight() const;
          int maximumHeight() const;
          void setMinimumHeight(int height);
          void setMaximumHeight(int height);
          void setFixedWidth(int width);
          void setFixedHeight(int height);
          void setFixedSize(const LgSize &size);
          void setFixedSize(int width, int height);
          int x() const;
          void setX(int x);
          int y() const;
          void setY(int y);
          void setPosition(int x, int y);
          void setPosition(const LgPoint &p);
          LgPoint position() const;
          void setBorderWidth(int width);
          int borderWidth() const;
          void setBackgroundColor(int red, int green, int blue);
          void setBackgroundColor(const LgColor &color);
          const LgColor& background() const;
          void setBorderColor(int red, int green, int blue);
          const LgColor& borderColor() const;
          void setTextColor(const LgColor &color);
          const LgColor& textColor() const;
          const LgColor& color() const;
          void setColor(const LgColor &color);
          const LgFont& font() const;
          void setFont(const LgFont &font);
          LgRect rect() const;
          void update();
          void close();
          Lg::Modality modality() const;
          bool isModal() const;
          void setWidgetAttribute(Lg::WidgetAttribute attribute);
          void clearWidgetAttribute(Lg::WidgetAttribute attribute);
          Lg::WidgetAttribute widgetAttributes() const;
          void enableInput();
          void disableInput();
          bool isInputEnabled() const;
          LgWidget* getTopWidget();
          bool isTopWindow() const;
          void enableGrabKey(bool b);
          bool grabKeyEnabled() const;
          void propagateGrabKey(bool b);
          bool propagateGrabKeyEnabled() const;
          void setFocus(bool b = true);
          bool hasFocus() const;
          void setPointerShape(Lg::PointerShape shape);
          Lg::PointerShape pointerShape() const;
          void setScaleFactor(double factor);
          double scaleFactor() const;
          bool pointerIsOverWindow() const;
          bool isChild(LgWidget *widget);
          LgPoint mapToGlobal(const LgPoint &p);
        
  protected:
          RK_DELCATE_IMPL_PTR(LgWidget);
          LgWidget(LgWidget *parent, std::unique_ptr<LgWidgetImpl> impl);
          void event(LgEvent *event) override;
          virtual void closeEvent(LgCloseEvent *event);
          virtual void keyPressEvent(LgKeyEvent *event);
          virtual void keyReleaseEvent(LgKeyEvent *event);
          virtual void shortcutEvent(LgKeyEvent *event);
          virtual void mouseMoveEvent(LgMouseEvent *event);
          virtual void mouseButtonPressEvent(LgMouseEvent *event);
          virtual void mouseButtonReleaseEvent(LgMouseEvent *event);
          virtual void mouseDoubleClickEvent(LgMouseEvent *event);
          virtual void wheelEvent(LgWheelEvent *event);
          virtual void dropEvent(LgDropEvent *event);
          virtual void moveEvent(LgMoveEvent *event);
          virtual void resizeEvent(LgResizeEvent *event);
          virtual void paintEvent(LgPaintEvent *event);
          virtual void showEvent(LgShowEvent *event);
          virtual void hideEvent(LgHideEvent *event);
          virtual void focusEvent(LgFocusEvent *event);
          virtual void hoverEvent(LgHoverEvent *event);

 private:
          RkCanvasInfo* getCanvasInfo() const override;
          void freeCanvasInfo() override;
          RK_DISABLE_COPY(LgWidget);
          RK_DISABLE_MOVE(LgWidget);
};

#endif // LGW_WIDGET_H
