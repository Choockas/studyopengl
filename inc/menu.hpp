#pragma once
#include <string>
#include <vector>
#include <memory>

class IGraphicObject;

class Menu
{
public:
    Menu(const std::vector< std::string>& menuDescription);
;
    void render() const;
    void update(const uint64_t);
private:
    size_t _width;
    size_t  _hight;
    std::vector <std::shared_ptr<IGraphicObject>> _mapOjects;
};
