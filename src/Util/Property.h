//
// Created by Lucas on 21-05-2024.
//

#pragma once

#include <functional>

template<typename T>
class Property {
public:
    Property(std::function<void(T)> callback) : data(), callback(callback) { }
    Property(T value) : data(value), callback() {}
    Property(T value, std::function<void(T)> callback) : data(value), callback(callback) {}

    Property& operator=(const T& newvalue) {
        data = newvalue;
        if (callback)
            callback(data);

        return *this;
    }

    operator T() const {
        return data;
    }

private:
    T data;
    std::function<void(T)> callback;
};