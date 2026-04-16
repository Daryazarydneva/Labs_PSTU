#pragma once
class Object {
public:
    virtual ~Object() {}
    virtual void Show() const = 0;
};