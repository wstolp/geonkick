/**
 * File name: Preset.h
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

#ifndef GEONKICK_PRESET_H
#define GEONKICK_PRESET_H

#include "globals.h"

#include <rapidjson/document.h>

class Preset {
 public:
        enum class PresetType: int {
                Percussion,
                PercussionKit,
        };

        explicit Preset(const std::filesystem::path& path);
        PresetType type() const;
        void setPath(const std::filesystem::path& path);
        const std::filesystem::path& path() const;
        void setName(const std::string &name);
        const std::string& name() const;
        void setAuthor(const std::string &author);
        const std::string& author() const;
        void setUrl(const std::string &url);
        const std::string& url() const;     
        void setLicense(const std::string &license);
        const std::string& license() const;
        void setCategory(const std::string &category);
        const std::string& category() const;

protected:
        void loadMetadata();
        void parseMetadata(const rapidjson::Value &obj);

 private:
        std::string presetName;
        std::filesystem::path presetPath;
        std::string presetAuthor;
        std::string presetUrl;
        std::string presetLicense;
        std::string presetCategory;
};

#endif // GEONKICK_PRESET_H
