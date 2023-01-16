#include "INIpp.hpp"

#include <iostream>
#include <sstream>

class MyFancySettingsProvider
{
    public:
        MyFancySettingsProvider(std::ostream& os) :
            m_os(os)
        {}

        void Kickoff(const std::filesystem::path& configFile = "./config.ini")
        {
            INIpp::SAXParser parser(
                std::bind(&MyFancySettingsProvider::OnKVPair, this, 
                    std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
            parser.AddFile(configFile);
        }

    private:
        void OnKVPair(const std::string& s, const std::string& k, const std::string& v)
        {
            m_os << s << ": " << k << " = " << v << std::endl;
        }

    private:
        std::ostream& m_os;
};

int main()
{
    std::stringstream ss;

    MyFancySettingsProvider sp(ss);
    sp.Kickoff();
    
    std::ofstream of("./myfile.ini");
    of << ss.str();
}
