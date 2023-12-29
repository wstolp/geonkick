/**
 * File name: LgWidget.cpp
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

#include "RkLog.h"
#include "RkEvent.h"
#include "LgWidget.h"
#include "LgWidgetImpl.h"
#include "RkWidget.h"

LgWidget::LgWidget(LgWidget *parent, Lg::WindowFlags flags)
        : LgObject(parent, std::make_unique<LgWidgetImpl>(this, parent, flags))
        , impl_ptr{static_cast<LgWidgetImpl*>(o_ptr.get())}
{
        RK_LOG_DEBUG("called: " << this);
        if (modality() == Lg::Modality::ModalTopWidget) {
                auto topWidget = getTopWidget();
                if (topWidget)
                        topWidget->disableInput();
                else if (parentWidget() && modality() == Lg::Modality::ModalParent)
                        parentWidget()->disableInput();
        }
}

LgWidget::LgWidget(LgWidget *parent, std::unique_ptr<LgWidgetImpl> impl)
        : LgObject(parent, std::move(impl))
        , impl_ptr{static_cast<LgWidgetImpl*>(o_ptr.get())}
{
        if (modality() == Lg::Modality::ModalTopWidget) {
                auto topWidget = getTopWidget();
                if (topWidget)
                        topWidget->disableInput();
                else if (parentWidget() && modality() == Lg::Modality::ModalParent)
                        parentWidget()->disableInput();
        }
}

LgWidget::~LgWidget()
{
        RK_LOG_DEBUG("called: " << this);
        if (parentWidget()) {
                if (modality() == Lg::Modality::ModalTopWidget) {
                        if (!parentWidget()->isModal()) {
                                auto topWidget = getTopWidget();
                                if (topWidget)
                                        topWidget->enableInput();
                        } else {
                                // Enable inputs only for parent widget and its
                                // childs since it is modal.
                                parentWidget()->enableInput();
                        }
                } else if (modality() == Lg::Modality::ModalParent) {
                        parentWidget()->enableInput();
                }
        }
}

Lg::WindowFlags LgWidget::windowFlags() const
{
        return impl_ptr->windowFlags();
}

void LgWidget::setTitle(const std::string &title)
{
        impl_ptr->setTitle(title);
}

const std::string& LgWidget::title() const
{
        return impl_ptr->title();
}


void LgWidget::show(bool b)
{
        impl_ptr->show(b);
}

bool LgWidget::isShown() const
{
	return impl_ptr->isShown();
}

void LgWidget::hide()
{
        impl_ptr->show(false);
}

LgWidget* LgWidget::parentWidget() const
{
        return dynamic_cast<LgWidget*>(parent());
}

bool LgWidget::isClose() const
{
        return impl_ptr->isClose();
}

void LgWidget::setSize(int w, int h)
{
        if (w > maximumWidth())
                w = maximumWidth();
        else if (w < minimumWidth())
                w = minimumWidth();

        if (h > maximumHeight())
                h = maximumHeight();
        else if (h < minimumHeight())
                h = minimumHeight();

        impl_ptr->setSize(LgSize(w, h));
}

void LgWidget::setSize(const LgSize &size)
{
        impl_ptr->setSize(size);
}

LgSize LgWidget::size() const
{
        return impl_ptr->size();
}

void LgWidget::setWidth(int w)
{
        if (w > maximumWidth())
                impl_ptr->setSize(LgSize(maximumWidth(), impl_ptr->size().height()));
        else if (w < minimumWidth())
                impl_ptr->setSize(LgSize(minimumWidth(), impl_ptr->size().height()));
        else
                impl_ptr->setSize(LgSize(w, impl_ptr->size().height()));
}

int LgWidget::width() const
{
        return impl_ptr->size().width();
}

int LgWidget::minimumWidth() const
{
        return impl_ptr->minimumWidth();
}

int LgWidget::maximumWidth() const
{
        return impl_ptr->maximumWidth();
}

void LgWidget::setHeight(int h)
{
        if (h > maximumHeight())
                impl_ptr->setSize(LgSize(impl_ptr->size().width(),  maximumHeight()));
        else if (h < minimumHeight())
                impl_ptr->setSize(LgSize(impl_ptr->size().width(),  minimumHeight()));
        else
                impl_ptr->setSize(LgSize(impl_ptr->size().width(),  h));
}

int LgWidget::height() const
{
        return impl_ptr->size().height();
}

int LgWidget::minimumHeight() const
{
        return impl_ptr->minimumHeight();
}

int LgWidget::maximumHeight() const
{
        return impl_ptr->maximumHeight();
}

void LgWidget::setMinimumWidth(int width)
{
        impl_ptr->setMinimumWidth(width);
}

void LgWidget::setMinimumHeight(int height)
{
        impl_ptr->setMinimumHeight(height);
}

void LgWidget::setMaximumWidth(int width)
{
        impl_ptr->setMaximumWidth(width);
}

void LgWidget::setMaximumHeight(int height)
{
        impl_ptr->setMaximumHeight(height);
}

void LgWidget::setFixedWidth(int width)
{
        setMinimumWidth(width);
        setMaximumWidth(width);
        setWidth(width);
}

void LgWidget::setFixedHeight(int height)
{
        setMinimumHeight(height);
        setMaximumHeight(height);
        setHeight(height);
}

void LgWidget::setFixedSize(const LgSize &size)
{
        setMinimumWidth(size.width());
        setMaximumWidth(size.width());
        setMinimumHeight(size.height());
        setMaximumHeight(size.height());
        setSize(size);
}

void LgWidget::setFixedSize(int width, int height)
{
        setFixedSize(LgSize(width, height));
}

int LgWidget::x() const
{
        return impl_ptr->position().x();
}

void LgWidget::setX(int x)
{
        impl_ptr->setPosition(LgPoint(x, impl_ptr->position().y()));
}

int LgWidget::y() const
{
        return impl_ptr->position().y();
}

void LgWidget::setY(int y)
{
        return impl_ptr->setPosition(LgPoint(impl_ptr->position().x(), y));
}

void LgWidget::setPosition(int x, int y)
{
        impl_ptr->setPosition(LgPoint(x, y));
}

void LgWidget::setPosition(const LgPoint &p)
{
        impl_ptr->setPosition(p);
}

LgPoint LgWidget::position() const
{
        return impl_ptr->position();
}

void LgWidget::setBorderWidth(int width)
{
        impl_ptr->setBorderWidth(width);
}

int LgWidget::borderWidth() const
{
        return impl_ptr->borderWidth();
}

void LgWidget::setBorderColor(int red, int green, int blue)
{
        red   = std::clamp(red, 0, 255);
        green = std::clamp(green, 0, 255);
        blue  = std::clamp(blue, 0, 255);
        impl_ptr->setBorderColor(LgColor(red, green, blue));
}

const LgColor& LgWidget::borderColor() const
{
        return impl_ptr->borderColor();
}

void LgWidget::setBackgroundColor(int red, int green, int blue)
{
        red   = std::clamp(red, 0, 255);
        green = std::clamp(green, 0, 255);
        blue  = std::clamp(blue, 0, 255);
        impl_ptr->setBackgroundColor(LgColor(red, green, blue));
}

void LgWidget::setBackgroundColor(const LgColor &color)
{
        impl_ptr->setBackgroundColor(color);
}

const LgColor& LgWidget::background() const
{
        return impl_ptr->background();
}

void LgWidget::setTextColor(const LgColor &color)
{
        return impl_ptr->setTextColor(color);
}

const LgColor& LgWidget::textColor() const
{
        return impl_ptr->textColor();
}

const LgColor& LgWidget::color() const
{
        return impl_ptr->color();
}

void LgWidget::setColor(const LgColor &color)
{
        return impl_ptr->setColor(color);
}

const LgFont& LgWidget::font() const
{
        return impl_ptr->font();
}

void LgWidget::setFont(const LgFont &font)
{
        impl_ptr->setFont(font);
}

void LgWidget::enableInput()
{
        setWidgetAttribute(static_cast<Lg::WidgetAttribute>(static_cast<int>(Lg::WidgetAttribute::KeyInputEnabled)
                           | static_cast<int>(Lg::WidgetAttribute::MouseInputEnabled)
                           | static_cast<int>(Lg::WidgetAttribute::CloseInputEnabled)));
        for (auto &ch: children()) {
                auto widget = dynamic_cast<LgWidget*>(ch);
                if (widget)
                        widget->enableInput();
        }
}

void LgWidget::disableInput()
{
        if (modality() == Lg::Modality::ModalParent || modality() == Lg::Modality::ModalTopWidget)
                return;

        clearWidgetAttribute(static_cast<Lg::WidgetAttribute>(static_cast<int>(Lg::WidgetAttribute::KeyInputEnabled)
                            | static_cast<int>(Lg::WidgetAttribute::MouseInputEnabled)
                            | static_cast<int>(Lg::WidgetAttribute::CloseInputEnabled)));
        for (const auto &ch: children()) {
                auto widget = dynamic_cast<LgWidget*>(ch);
                if (widget)
                        widget->disableInput();
        }
}

bool LgWidget::isInputEnabled() const
{
        return  static_cast<int>(widgetAttributes()) & static_cast<int>(Lg::WidgetAttribute::KeyInputEnabled);
}

void LgWidget::enableGrabKey(bool b)
{
        // For now only for top level window.
        if (!parentWidget())
                impl_ptr->enableGrabKey(b);
}

bool LgWidget::grabKeyEnabled() const
{
        return impl_ptr->grabKeyEnabled();
}

void LgWidget::propagateGrabKey(bool b)
{
        impl_ptr->propagateGrabKey(b);
}

bool LgWidget::propagateGrabKeyEnabled() const
{
        return impl_ptr->propagateGrabKeyEnabled();
}

void LgWidget::event(LgEvent *event)
{
        impl_ptr->event(event);
        LgObject::event(event);
}

void LgWidget::closeEvent([[maybe_unused]] LgCloseEvent *event)
{
        if (parentWidget()) {
                //using LgDeleteChild = RkDeleteChild;
                // auto event = std::make_unique<LgDeleteChild>(parentWidget(), this);
                //   eventQueue()->postEvent(parentWidget(), std::move(event));
        }
}

void LgWidget::keyPressEvent([[maybe_unused]] LgKeyEvent *event)
{
}

void LgWidget::keyReleaseEvent([[maybe_unused]] LgKeyEvent *event)
{
}

void LgWidget::shortcutEvent([[maybe_unused]] LgKeyEvent *event)
{
}

void LgWidget::mouseMoveEvent([[maybe_unused]] LgMouseEvent *event)
{
}

void LgWidget::mouseButtonPressEvent([[maybe_unused]] LgMouseEvent *event)
{
}

void LgWidget::mouseButtonReleaseEvent([[maybe_unused]] LgMouseEvent *event)
{
}

void LgWidget::mouseDoubleClickEvent(LgMouseEvent *event)
{
        mouseButtonPressEvent(event);
}

void LgWidget::wheelEvent([[maybe_unused]]LgWheelEvent *event)
{
}

void LgWidget::dropEvent(LgDropEvent *event)
{
        if (parentWidget())
                getTopWidget()->dropEvent(event);
}

void LgWidget::moveEvent([[maybe_unused]] LgMoveEvent *event)
{
}

void LgWidget::resizeEvent([[maybe_unused]] LgResizeEvent *event)
{
}

void LgWidget::paintEvent([[maybe_unused]] LgPaintEvent *event)
{
}

void LgWidget::showEvent([[maybe_unused]] LgShowEvent *event)
{
}

void LgWidget::hideEvent([[maybe_unused]] LgHideEvent *event)
{
}

void LgWidget::focusEvent([[maybe_unused]] LgFocusEvent *event)
{
        update();
}

void LgWidget::hoverEvent([[maybe_unused]] LgHoverEvent *event)
{
}

void LgWidget::update()
{
        impl_ptr->update();
}

LgRect LgWidget::rect() const
{
        return impl_ptr->rect();
}

void LgWidget::close()
{
        eventQueue()->postEvent(this, std::make_unique<LgCloseEvent>());
}

bool LgWidget::isModal() const
{
        return modality() != Lg::Modality::NonModal;
}

Lg::Modality LgWidget::modality() const
{
        return impl_ptr->modality();
}

void LgWidget::setWidgetAttribute(Lg::WidgetAttribute attribute)
{
        impl_ptr->setWidgetAttribute(attribute);
}

void LgWidget::clearWidgetAttribute(Lg::WidgetAttribute attribute)
{
        impl_ptr->clearWidgetAttribute(attribute);
}

Lg::WidgetAttribute LgWidget::widgetAttributes() const
{
        return impl_ptr->getWidgetAttributes();
}

LgWidget* LgWidget::getTopWidget()
{
        if (!parentWidget())
                return this;
        return parentWidget()->getTopWidget();
}

bool LgWidget::isTopWindow() const
{
        return !parentWidget();
}

void LgWidget::setFocus(bool b)
{
        impl_ptr->setFocus(b);
}

bool LgWidget::hasFocus() const
{
        return impl_ptr->hasFocus();
}

void LgWidget::setPointerShape(Lg::PointerShape shape)
{
        impl_ptr->setPointerShape(shape);
}

Lg::PointerShape LgWidget::pointerShape() const
{
        return impl_ptr->pointerShape();
}

bool LgWidget::pointerIsOverWindow() const
{
        return impl_ptr->pointerIsOverWindow();
}

bool LgWidget::isChild(LgWidget *widget)
{
        for (const auto &child: children()) {
                if (widget == dynamic_cast<LgWidget*>(child))
                        return true;
        }
        return false;
}

