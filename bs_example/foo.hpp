#pragma once
// #include "IClass.hpp"

class foo : public IClass
{
private:
    std::string _type;
public:
    foo();
    // IClass *entryPoint() override;
    // void endPoint() override;
    std::string getType() override;
    ~foo();
};
