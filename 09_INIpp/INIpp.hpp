#pragma once

#include <string>
#include <format>
#include <cctype>
#include <fstream>
#include <stdexcept>
#include <functional>
#include <filesystem>
#include <string_view>

namespace INIpp
{
    class Exception : public std::runtime_error
    {
        public:
            using std::runtime_error::runtime_error;
    };
    
    class Parser
    {
        private:
            enum class State
            {
                // Internal state flushed and ready for any ini data
                ReadForData,
                // Comment started
                Comment,
                // Section is beeing defined
                Section,
                // Key value
                KVKey,
                KVKeyDone,
                // Equal sign of KV value reached
                KVEqual,
                // KV Value coming
                KVValue,
            };

        public:
            void AddFile(const std::filesystem::path& path);
            void AddString(const std::string_view& str);
            void Reset();

            virtual void ParseKVPair(const std::string& section, const std::string& key, const std::string& value) = 0;

        private:
            void ProcessChar(char c);

        private:
            State m_state = State::ReadForData;
            std::string m_currentSection, m_currentKey, m_currentValue;
    };

    class SAXParser : public Parser
    {
        public:
            using Callback = std::function<void(const std::string&, const std::string&, const std::string&)>;

            SAXParser() = default;
            SAXParser(Callback callback) : 
                m_callback(callback)
            {}

            void ParseKVPair(const std::string& section, const std::string& key, const std::string& value) override;
    
        private:
            Callback m_callback;
    };

    class DOMParser : public Parser
    {
        public:
            void ParseKVPair(const std::string& section, const std::string& key, const std::string& value) override;
 
        private:

    };
}
