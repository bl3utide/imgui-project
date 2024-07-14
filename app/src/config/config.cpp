﻿#include "common.hpp"
#include "logger.hpp"
#include "config/config.hpp"
#include "config/cv.hpp"
#include "config/reader.hpp"
#include "config/writer.hpp"

// TODO change app namespace
namespace ImGuiProject
{
namespace Config
{

// private
std::string _config_file_name;
std::unordered_map<Key, Cv> _cv_by_key;

const Cv& getCv(const Key key) noexcept
{
    return _cv_by_key.at(key);
}

void load() noexcept
{
    mINI::INIStructure read_is;
    mINI::INIFile file = mINI::INIFile(_config_file_name);

    if (file.read(read_is))
    {
        Logger::debug("Load config from existing ini file");
        // ini-file already exists
        for (int key_i = 0; key_i < static_cast<int>(Key::_COUNT_); ++key_i)
        {
            Key key = static_cast<Key>(key_i);
            Reader::iniValueToCv(read_is, _cv_by_key.at(key));
        }
    }
    else
    {
        Logger::debug("Ini file does not exists");
    }
}

void save() noexcept
{
    mINI::INIStructure write_is;
    mINI::INIFile file = mINI::INIFile(_config_file_name);

    for (int key_i = 0; key_i < static_cast<int>(Key::_COUNT_); ++key_i)
    {
        Key key = static_cast<Key>(key_i);
        Writer::cvToIni(_cv_by_key.at(key), write_is);
    }

    if (!file.write(write_is, true))
    {
        Logger::debug("Failed to write config file");
    }
}

const std::string GET_CONFIG_VALUE_TYPE_ERR_TEXT = "Config key '%s' is not %s";

template<typename T>
const T getConfigValue(const Key key)
{
    throw new std::runtime_error("Unexpected type of Cv");
}

template<>
const std::string getConfigValue(const Key key)
{
    Cv& cv = _cv_by_key.at(key);

    if (cv.type() != Cv::Type::String)
        throw new std::runtime_error(StringUtil::format(GET_CONFIG_VALUE_TYPE_ERR_TEXT, cv.key_name(), "string"));

    return cv.cv();
}

template<>
const int getConfigValue(const Key key)
{
    Cv& cv = _cv_by_key.at(key);

    if (cv.type() != Cv::Type::Int)
        throw new std::runtime_error(StringUtil::format(GET_CONFIG_VALUE_TYPE_ERR_TEXT, cv.key_name(), "int"));

    return std::stoi(cv.cv());
}

template<>
const bool getConfigValue(const Key key)
{
    Cv& cv = _cv_by_key.at(key);

    if (cv.type() != Cv::Type::Bool)
        throw new std::runtime_error(StringUtil::format(GET_CONFIG_VALUE_TYPE_ERR_TEXT, cv.key_name(), "bool"));

    return cv.cv() == "1";
}

const std::string SET_CONFIG_VALUE_TYPE_ERR_TEXT = "The type of config key '%s' is not %s";

template<typename T>
void setConfigValue(const Key key, const T value)
{
    throw new std::runtime_error("Unexpected type of value");
}

template<>
void setConfigValue(const Key key, const std::string value)
{
    Cv& cv = _cv_by_key.at(key);

    if (cv.type() != Cv::Type::String)
        throw new std::runtime_error(StringUtil::format(SET_CONFIG_VALUE_TYPE_ERR_TEXT, cv.key_name(), "string"));

    cv.set(value);
}

template<>
void setConfigValue(const Key key, const int value)
{
    Cv& cv = _cv_by_key.at(key);

    if (cv.type() != Cv::Type::Int)
        throw new std::runtime_error(StringUtil::format(SET_CONFIG_VALUE_TYPE_ERR_TEXT, cv.key_name(), "int"));

    cv.set(std::to_string(value));
}

template<>
void setConfigValue(const Key key, const bool value)
{
    Cv& cv = _cv_by_key.at(key);

    if (cv.type() != Cv::Type::Bool)
        throw new std::runtime_error(StringUtil::format(SET_CONFIG_VALUE_TYPE_ERR_TEXT, cv.key_name(), "bool"));

    std::string set_v = value ? "1" : "0";
    cv.set(set_v);
}

void initialize()
{
    _config_file_name = StringUtil::format("%s.ini", APP_NAME.c_str());

    // TODO add ini keys initialization
    // ex)
    // [NewSection]
    _cv_by_key.insert({ Key::NewKey1,   Cv(Section::NewSection, Key::NewKey1, std::string()) });
    _cv_by_key.insert({ Key::NewKey2,   Cv(Section::NewSection, Key::NewKey2, 1, 10, 1) });
    _cv_by_key.insert({ Key::NewKey3,   Cv(Section::NewSection, Key::NewKey3, false) });
}

} // Config
} // ImGuiProject
