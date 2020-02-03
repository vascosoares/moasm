#ifndef MOASM_HPP
#define MOASM_HPP

#pragma once
#include <cassert>
#include <functional>

namespace moasm
{
    template<typename T>
    class Property
    {
        public:
            using Getter = std::function<T()>;
            using Setter = std::function<void(T)>;

        private:  
            T __val__;
            Getter __getter__;
            Setter __setter__;

            void initialize() {
                __getter__ = [&]() { return __val__; }; 
                __setter__ = [&](T value) { __val__ = value; };
            }

        public:
            Property() { initialize(); }
            Property(T o) : __val__(o) { initialize(); }
            Property(Getter getter, Setter setter = readonly_setter()) :
                __getter__(getter), __setter__(setter) {}

            virtual prop<T>& operator=(T o)
            { __setter__(o); return *this; }

            virtual operator T() const
            { return __getter__(); }
    };

    template <typename T>
    class Property<const T> {
        public:
            using Getter = std::function<T()>;

        private:
            Getter __getter__;

            Property(const prop<T>&) = delete;
            Property(prop<T>&&) = delete;

        public:
            Property(Getter getter) : __getter__(getter) {}

            virtual operator T() const
            { return __getter__(); }
    };

    #define __get__() [&]()
    #define __set__(T) , [&](T& value)
}

#endif // MOASM_HPP