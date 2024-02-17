/**
 * File name: GeonkickConfig.h
 * Project: Geonkick (A percussion synthesizer)
 *
 * Copyright (C) 2020 Iurie Nistor 
 *
 * This file is part of Geonkick.
 *
 * GeonKick is free software; you can redistribute it and/or modify
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

#ifndef GEONGKICK_CONFIG_H
#define GEONGKICK_CONFIG_H

#include "globals.h"

class GeonkickConfig {
 public:
        GeonkickConfig();
        void setScaleFactor(double factor);
        double getScaleFactor() const;
        void setMidiChannel(int channel);
        int getMidiChannel() const;
        bool open();
        bool save();

 protected:
        void loadConfig(const std::string &data);
        std::string toJson() const;

 private:
        double scaleFactor;
        int channelNumber;
        std::filesystem::path configFile;
};

#endif // GEONGKICK_CONFIG_H
