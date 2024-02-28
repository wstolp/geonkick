/**
 * File name: Preset.cpp
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

#include "preset.h"

Preset::Preset(const std::filesystem::path& path)
        : presetName{path.stem().string()}
        , presetPath{path}
        , presetAuthor{"Unknown"}
        , presetLicense{"Unknown"}
{
        loadMetadata();
}

Preset::PresetType Preset::type() const
{
        if (path().extension().string() == ".gkit")
                return PresetType::PercussionKit;
        return PresetType::Percussion;
}

void Preset::setName(const std::string &name)
{
        presetName = name;
}

const std::string& Preset::name() const
{
        return presetName;
}

void Preset::setPath(const std::filesystem::path &path)
{
        presetPath = path;
}

const std::filesystem::path& Preset::path() const
{
        return presetPath;
}

void Preset::setAuthor(const std::string &author)
{
        presetAuthor = author;
}

const std::string& Preset::author() const
{
        return presetAuthor;
}

void Preset::setUrl(const std::string &url)
{
        presetUrl = url;
}

const std::string& Preset::url() const
{
        return presetUrl;
}

void Preset::setLicense(const std::string &license)
{
        presetLicense = license;
}

const std::string& Preset::license() const
{
        return presetLicense;
}

void Preset::setCategory(const std::string &category)
{
        presetCategory = category;
}

const std::string& Preset::category() const
{
        return presetCategory;
}

void Preset::loadMetadata()
{
        std::ifstream file(path().string().c_str());
        if (!file.is_open()) {
	        GEONKICK_LOG_ERROR("can't open preset file " << path().string());
                return;
        }

        rapidjson::Document document;
        {
                std::string fileData((std::istreambuf_iterator<char>(file)),
                                     (std::istreambuf_iterator<char>()));
                if (document.Parse(fileData.c_str()).HasParseError()) {
                        GEONKICK_LOG_ERROR("error on parsing JSON data");
                        return;
                }
        }

        if (!document.IsObject())
                return;

        for (const auto &m: document.GetObject()) {
                if (m.name == "metadata" && m.value.IsObject()) {
                        parseMetadata(m.value);
                        break;
                }
        }
}

void Preset::parseMetadata(const rapidjson::Value &obj)
{
        for (const auto &m: obj.GetObject()) {
                if (m.name == "name" && m.value.IsString())
                        presetName = m.value.GetString();
                if (m.name == "author" && m.value.IsString())
                        presetAuthor = m.value.GetString();
                if (m.name == "url" && m.value.IsString())
                        presetUrl = m.value.GetString();
                if (m.name == "license" && m.value.IsString())
                        presetLicense = m.value.GetString();
                if (m.name == "category" && m.value.IsString())
                        presetCategory = Geonkick::toLowercase(m.value.GetString());
        }
}
