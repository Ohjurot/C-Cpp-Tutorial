#include "INIpp.hpp"

void INIpp::Parser::AddFile(const std::filesystem::path& path)
{
    std::ifstream fileIn(path, std::ios::binary | std::ios::in);
    if (!fileIn.is_open())
        throw Exception(std::format("Can't open file \"{}\"", path.string()));

    fileIn.seekg(0, std::ios::end);
    size_t fileSize = fileIn.tellg();
    fileIn.seekg(0, std::ios::beg);
    
    std::string fileData(fileSize, ' ');
    fileIn.read(&fileData[0], fileSize);

    AddString(fileData);
}

void INIpp::Parser::AddString(const std::string_view& str)
{
    Reset();
    for (char c : str)
    {
        ProcessChar(c);
    }
}

void INIpp::Parser::Reset()
{
    m_currentSection = "";
    m_currentKey = "";
    m_currentValue = "";
    m_state = State::ReadForData;
}

void INIpp::Parser::ProcessChar(char c)
{
    // Catch controle keys
    if (std::iscntrl(c))
    {
        switch (c)
        {
            case '\t':
                [[fallthrough]];
            case '\n':
                break;
            default:
                return;
        }
    }

    // Normal char parsing
    switch (m_state)
    {
        case State::ReadForData:
            switch (c)
            {
                case ';':
                    m_state = State::Comment;
                    break;
                case '[':
                    m_currentSection.clear();
                    m_state = State::Section;
                    break;
                case ' ':
                    [[fallthrough]];
                case '\t':
                    [[fallthrough]];
                case '\n':
                    break;
                default:
                    m_currentKey.clear();
                    m_currentKey += c;
                    m_state = State::KVKey;
                    break;
            }
            break;
        case State::Comment:
            if (c == '\n')
            {
                m_state = State::ReadForData;
            }
            break;
        case State::Section:
            switch (c)
            {
                case ']':
                    m_state = State::ReadForData;
                    break;
                case '\n':
                    [[fallthrough]];
                case '\t':
                    throw Exception("Newlines or Tabs are not allowed in section names!");
                default:
                    m_currentSection += c;
                    break;
            }
            break;
        case State::KVKey:
            switch (c)
            {
                case ' ':
                    m_state = State::KVKeyDone;
                    break;
                case '\t':
                    [[fallthrough]];
                case '\n':
                    throw Exception("Newlines or Tabs are not allowed in the key!");
                default:
                    m_currentKey += c;
                    break;
            }
            break;
        case State::KVKeyDone:
            switch (c)
            {
                case ' ':
                    [[fallthrough]];
                case '\t':
                    break;
                case '\n':
                    throw Exception("Every key need to have a value!");
                case '=':
                    m_state = State::KVEqual;
                    break;
                default:
                    throw Exception("Keys are not allowed to have spaces in them!");
            }
            break;
        case State::KVEqual:
            switch (c)
            {
                case ' ':
                    [[fallthrough]];
                case '\t':
                    break;
                case '\n':
                    throw Exception("Values can't be empty!");
                default:
                    m_currentValue.clear();
                    m_currentValue += c;
                    m_state = State::KVValue;
                    break;
            }
            break;
        case State::KVValue:
            if (c == '\n')
            {
                ParseKVPair(m_currentSection, m_currentKey, m_currentValue);
                m_state = State::ReadForData;
            }
            else
            {
                m_currentValue += c;
            }
            break;
    }
}

void INIpp::SAXParser::ParseKVPair(const std::string& section, const std::string& key, const std::string& value)
{
    if (m_callback)
    {
        m_callback(section, key, value);
    }
}

void INIpp::DOMParser::ParseKVPair(const std::string& section, const std::string& key, const std::string& value)
{
    m_document[section].Append(DOM::KVPair(key, value));
}
