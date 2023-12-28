/**
 * File name: LgWidgetImpl.cpp
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

#include "LgWidgetImpl.h"
#include "RkEvent.h"
#include "RkPainter.h"

LgWidget::LgWidgetImpl::LgWidgetImpl(LgWidget* widgetInterface, LgWidget* parent, Lg::WindowFlags flags, bool isTopWindow)
        : RkObject::RkObjectImpl(widgetInterface, parent, Lg::ObjectType::Widget)
        , inf_ptr{widgetInterface}
        , widgetClosed{false}
        , widgetMinimumSize{0, 0}
        , widgetMaximumSize{1000000, 1000000}
        , widgetSize{0, 0}
        , widgetBackground{255, 255, 255}
        , widgetAttributes{defaultWidgetAttributes()}
        , widgetModality{(static_cast<int>(flags) & static_cast<int>(Lg::WindowFlags::Dialog)) ? Lg::Modality::ModalTopWidget : Lg::Modality::NonModal}
        , widgetTextColor{0, 0, 0}
        , widgetDrawingColor{0, 0, 0}
        , widgetPointerShape{Lg::PointerShape::Arrow}
	, isWidgetSown{false}
        , isGrabKeyEnabled{false}
        , isPropagateGrabKey{true}
{
        RK_LOG_DEBUG("called");
}

LgWidget::LgWidgetImpl::~LgWidgetImpl()
{
        RK_LOG_DEBUG("called");
}

Lg::WindowFlags LgWidget::LgWidgetImpl::windowFlags() const
{
        return static_cast<Lg::WindowFlags>(0);
}

Lg::WidgetAttribute LgWidget::LgWidgetImpl::defaultWidgetAttributes()
{
        return static_cast<Lg::WidgetAttribute>(static_cast<int>(Lg::WidgetAttribute::KeyInputEnabled)
                                                | static_cast<int>(Lg::WidgetAttribute::MouseInputEnabled)
                                                | static_cast<int>(Lg::WidgetAttribute::CloseInputEnabled));

}

void LgWidget::LgWidgetImpl::show(bool b)
{
	isWidgetSown = b;
}

bool LgWidget::LgWidgetImpl::isShown() const
{
	return isWidgetSown;
}

void LgWidget::LgWidgetImpl::setTitle(const std::string &title)
{
        widgetTitle = title;
}

const std::string& LgWidget::LgWidgetImpl::title() const
{
        return widgetTitle;
}

bool LgWidget::LgWidgetImpl::isClose() const
{
        return widgetClosed;
}

void LgWidget::LgWidgetImpl::event(LgEvent *event)
{
        switch (event->type())
        {
        case LgEvent::Type::Paint:
                inf_ptr->paintEvent(static_cast<LgPaintEvent*>(event));
                break;
        case LgEvent::Type::KeyPressed:
                RK_LOG_DEBUG("LgEvent::Type::KeyPressed: " << title());
                if (static_cast<int>(widgetAttributes) & static_cast<int>(Lg::WidgetAttribute::KeyInputEnabled)) {
                        auto keyEvent = static_cast<LgKeyEvent*>(event);
                        if (keyEvent->isShortcut())
                                inf_ptr->shortcutEvent(keyEvent);
                        else
                                inf_ptr->keyPressEvent(keyEvent);
                }
                break;
        case LgEvent::Type::KeyReleased:
                RK_LOG_DEBUG("LgEvent::Type::KeyReleased: " << title());
                if (static_cast<int>(widgetAttributes) & static_cast<int>(Lg::WidgetAttribute::KeyInputEnabled)) {
                        auto keyEvent = static_cast<LgKeyEvent*>(event);
                        if (keyEvent->isShortcut())
                                inf_ptr->shortcutEvent(keyEvent);
                        else
                                inf_ptr->keyReleaseEvent(keyEvent);
                }
                break;
        case LgEvent::Type::FocusedIn:
                RK_LOG_DEBUG("LgEvent::Type::FocsedIn:" << title());
                inf_ptr->focusEvent(static_cast<LgFocusEvent*>(event));
                break;
        case LgEvent::Type::FocusedOut:
                RK_LOG_DEBUG("LgEvent::Type::FocsedOut: " << title());
                inf_ptr->focusEvent(static_cast<LgFocusEvent*>(event));
                break;
        case LgEvent::Type::MouseButtonPress:
                RK_LOG_DEBUG("LgEvent::Type::MouseButtonPress: " << title());
                if (static_cast<int>(widgetAttributes) & static_cast<int>(Lg::WidgetAttribute::MouseInputEnabled))
                        inf_ptr->mouseButtonPressEvent(static_cast<LgMouseEvent*>(event));
                break;
        case LgEvent::Type::MouseDoubleClick:
                RK_LOG_DEBUG("LgEvent::Type::MouseDoubleClick:" << title());
                if (static_cast<int>(widgetAttributes) & static_cast<int>(Lg::WidgetAttribute::MouseInputEnabled))
                        inf_ptr->mouseDoubleClickEvent(static_cast<LgMouseEvent*>(event));
                break;
        case LgEvent::Type::MouseButtonRelease:
                RK_LOG_DEBUG("LgEvent::Type::MouseButtonRelease:" << title());
                if (static_cast<int>(widgetAttributes) & static_cast<int>(Lg::WidgetAttribute::MouseInputEnabled))
                        inf_ptr->mouseButtonReleaseEvent(static_cast<LgMouseEvent*>(event));
                break;
        case LgEvent::Type::MouseMove:
                if (static_cast<int>(widgetAttributes) & static_cast<int>(Lg::WidgetAttribute::MouseInputEnabled))
                        inf_ptr->mouseMoveEvent(static_cast<LgMouseEvent*>(event));
                break;
        case LgEvent::Type::Drop:
                RK_LOG_DEBUG("LgEvent::Type::Drop:" << title());
                if (static_cast<int>(widgetAttributes) & static_cast<int>(Lg::WidgetAttribute::MouseInputEnabled))
                        inf_ptr->dropEvent(static_cast<LgDropEvent*>(event));
                break;
        case LgEvent::Type::Hover:
                RK_LOG_DEBUG("LgEvent::Type::Hover:" << title());
                inf_ptr->hoverEvent(static_cast<LgHoverEvent*>(event));
                break;
        case LgEvent::Type::Resize:
                inf_ptr->resizeEvent(static_cast<LgResizeEvent*>(event));
                break;
	case LgEvent::Type::Show:
		isWidgetSown = true;
                inf_ptr->showEvent(static_cast<LgShowEvent*>(event));
                break;
	case LgEvent::Type::Hide:
		isWidgetSown = false;
                inf_ptr->hideEvent(static_cast<LgHideEvent*>(event));
                break;
        case LgEvent::Type::DeleteChild:
                RK_LOG_DEBUG("LgEvent::Type::DeleteChild:" << title());
                //                delete static_cast<LgDeleteChild*>(event)->child();
                break;
        case LgEvent::Type::Close:
                RK_LOG_DEBUG("LgEvent::Type::Close");
                if (static_cast<int>(widgetAttributes) & static_cast<int>(Lg::WidgetAttribute::CloseInputEnabled)) {
                        widgetClosed = true;
                        inf_ptr->closeEvent(static_cast<LgCloseEvent*>(event));
                }
                break;
        default:
                break;
                RK_LOG_DEBUG("LgEvent::Type::Unknown:" << title());
        }
}

void LgWidget::LgWidgetImpl::setSize(const LgSize &size)
{
        widgetSize = size;
}

LgSize LgWidget::LgWidgetImpl::size() const
{
        return  widgetSize;
}

int LgWidget::LgWidgetImpl::minimumWidth() const
{
        return widgetMinimumSize.width();
}

int LgWidget::LgWidgetImpl::maximumWidth() const
{
        return widgetMaximumSize.width();
}

int LgWidget::LgWidgetImpl::minimumHeight() const
{
        return widgetMinimumSize.height();
}

int LgWidget::LgWidgetImpl::maximumHeight() const
{
        return widgetMaximumSize.height();
}

void LgWidget::LgWidgetImpl::setMinimumWidth(int width)
{
        widgetMinimumSize.setWidth(width);
}

void LgWidget::LgWidgetImpl::setMaximumWidth(int width)
{
        widgetMaximumSize.setWidth(width);
}

void LgWidget::LgWidgetImpl::setMinimumHeight(int height)
{
        widgetMinimumSize.setHeight(height);
}

void LgWidget::LgWidgetImpl::setMaximumHeight(int height)
{
        widgetMaximumSize.setHeight(height);
}

void LgWidget::LgWidgetImpl::setPosition(const LgPoint &position)
{
}

LgPoint LgWidget::LgWidgetImpl::position() const
{
        return {0, 0};
}

void LgWidget::LgWidgetImpl::setBorderWidth(int width)
{
        //        widgetBorderWidth = width;
}

int LgWidget::LgWidgetImpl::borderWidth() const
{
        return 0;//widgetBorderWidth;
}

void LgWidget::LgWidgetImpl::setBorderColor(const LgColor &color)
{
        widgetBorderColor = color;
}

const LgColor& LgWidget::LgWidgetImpl::borderColor() const
{
        return widgetBorderColor;
}

void LgWidget::LgWidgetImpl::setBackgroundColor(const LgColor &color)
{
        widgetBackground = color;
}

const LgColor& LgWidget::LgWidgetImpl::background() const
{
        return widgetBackground;
}

LgRect LgWidget::LgWidgetImpl::rect() const
{
        return LgRect(LgPoint(0, 0), size());
}

void LgWidget::LgWidgetImpl::update()
{
        // IMPLEMENT
}

Lg::Modality LgWidget::LgWidgetImpl::modality() const
{
        return widgetModality;
}

void LgWidget::LgWidgetImpl::setWidgetAttribute(Lg::WidgetAttribute attribute)
{
        widgetAttributes = static_cast<Lg::WidgetAttribute>(static_cast<int>(widgetAttributes) | static_cast<int>(attribute));
}

void LgWidget::LgWidgetImpl::clearWidgetAttribute(Lg::WidgetAttribute attribute)
{
        widgetAttributes = static_cast<Lg::WidgetAttribute>(static_cast<int>(widgetAttributes) & (~static_cast<int>(attribute)));
}

Lg::WidgetAttribute LgWidget::LgWidgetImpl::getWidgetAttributes() const
{
        return widgetAttributes;
}

void LgWidget::LgWidgetImpl::setFocus(bool b)
{
}

bool LgWidget::LgWidgetImpl::hasFocus() const
{
        return false;
}

void LgWidget::LgWidgetImpl::setTextColor(const LgColor &color)
{
        widgetTextColor = color;
}

const LgColor& LgWidget::LgWidgetImpl::textColor() const
{
        return widgetTextColor;
}

const LgColor& LgWidget::LgWidgetImpl::color() const
{
        return widgetDrawingColor;
}

void LgWidget::LgWidgetImpl::setColor(const LgColor &color)
{
        widgetDrawingColor = color;
}

const LgFont& LgWidget::LgWidgetImpl::font() const
{
        return widgetFont;
}

void LgWidget::LgWidgetImpl::setFont(const LgFont &font)
{
        widgetFont = font;
}

void LgWidget::LgWidgetImpl::setPointerShape(Lg::PointerShape shape)
{
        widgetPointerShape = shape;
}

Lg::PointerShape LgWidget::LgWidgetImpl::pointerShape() const
{
        return widgetPointerShape;
}

void LgWidget::LgWidgetImpl::enableGrabKey(bool b)
{
        isGrabKeyEnabled = b;
}

bool LgWidget::LgWidgetImpl::grabKeyEnabled() const
{
        return isGrabKeyEnabled;
}

void LgWidget::LgWidgetImpl::propagateGrabKey(bool b)
{
        isPropagateGrabKey = b;
}

bool LgWidget::LgWidgetImpl::propagateGrabKeyEnabled() const
{
        return isPropagateGrabKey;
}

bool LgWidget::LgWidgetImpl::pointerIsOverWindow() const
{
        return false;
}

void LgWidget::LgWidgetImpl::setScaleFactor(double factor)
{
}

double LgWidget::LgWidgetImpl::scaleFactor() const
{
        return 1.0;
}
