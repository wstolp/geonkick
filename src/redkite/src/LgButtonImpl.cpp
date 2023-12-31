/**
 * File name: LgButtonImpl.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2020 Iurie Nistor 
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

#include "LgButtonImpl.h"

LgButton::LgButtonImpl::LgButtonImpl(LgButton *interface, LgWidget *parent)
    : LgWidgetImpl(static_cast<LgWidget*>(interface), parent)
    , inf_ptr{interface}
    , buttonType{ButtonType::ButtonUncheckable}
    , is_pressed{false}
    , buttonState{LgButton::State::Unpressed}
    , isEmphasizeEnabled{false}
{
}

void LgButton::LgButtonImpl::setText(const RkString &text)
{
        buttonText = text;
}

RkString LgButton::LgButtonImpl::text() const
{
        return buttonText;
}

void LgButton::LgButtonImpl::setImage(const RkImage &img, LgButton::State state)
{
        buttonImages[static_cast<size_t>(state)] = img;
        if (state == LgButton::State::Unpressed)
                inf_ptr->setSize(img.size());
}

bool LgButton::LgButtonImpl::isPressed() const
{
        return is_pressed;
}

void LgButton::LgButtonImpl::setPressed(bool pressed)
{
        is_pressed = pressed;
        isEmphasizeEnabled = false;
        updateButtonState();
}

void LgButton::LgButtonImpl::setType(LgButton::ButtonType type)
{
        buttonType = type;
        updateButtonState();
}

LgButton::ButtonType LgButton::LgButtonImpl::type(void) const
{
        return buttonType;
}

void LgButton::LgButtonImpl::drawButton(RkPainter &painter)
{
        if (isPressed()) {
                if (!buttonImages[static_cast<size_t>(buttonState)].isNull())
                        painter.drawImage(buttonImages[static_cast<size_t>(buttonState)], 0, 0);
                else if (!buttonImages[static_cast<size_t>(LgButton::State::Pressed)].isNull())
                        painter.drawImage(buttonImages[static_cast<size_t>(LgButton::State::Pressed)], 0, 0);
                else if (!buttonImages[static_cast<size_t>(LgButton::State::Unpressed)].isNull())
                        painter.drawImage(buttonImages[static_cast<size_t>(LgButton::State::Unpressed)], 0, 0);
        } else if (!buttonImages[static_cast<size_t>(LgButton::State::Unpressed)].isNull()) {
                if (!buttonImages[static_cast<size_t>(buttonState)].isNull())
                        painter.drawImage(buttonImages[static_cast<size_t>(buttonState)], 0, 0);
                else
                        painter.drawImage(buttonImages[static_cast<size_t>(LgButton::State::Unpressed)], 0, 0);
        } else if (!buttonImages[static_cast<size_t>(LgButton::State::Unpressed)].isNull()) {
                painter.drawImage(buttonImages[static_cast<size_t>(LgButton::State::Unpressed)], 0, 0);
        }

        if (!buttonText.empty()) {
                auto pen = painter.pen();
                pen.setColor(textColor());
                painter.setPen(pen);
                painter.drawText(inf_ptr->rect(), buttonText);
        }
}

void LgButton::LgButtonImpl::setEmphasize(bool b)
{
        isEmphasizeEnabled = b;
        updateButtonState();
}

void LgButton::LgButtonImpl::updateButtonState()
{
        if (isPressed()) {
                if (isEmphasizeEnabled)
                        buttonState = LgButton::State::PressedHover;
                else
                        buttonState = LgButton::State::Pressed;
        } else {
                if (isEmphasizeEnabled)
                        buttonState = LgButton::State::UnpressedHover;
                else
                        buttonState = LgButton::State::Unpressed;
        }
}
