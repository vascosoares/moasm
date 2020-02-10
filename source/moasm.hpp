#pragma once
#include <cassert>
#include <functional>
#include "event.h"

namespace moasm
{
    template <typename T>
    class Property {

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

        Property(const Property<T>&) = delete;
        Property(Property<T>&&) = delete;

    public:
        Property() { initialize(); }
        Property(T o) : __val__(o) { initialize(); }

        Property(Getter getter, Setter setter) :
            __getter__(getter), __setter__(setter) {}

        virtual Property<T>& operator=(T o)
        { __setter__(o); return *this; }

        virtual operator T() const
        { return __getter__(); }

        virtual T operator++(int)
        { T t = __getter__(); __setter__(__getter__() + 1); return t; }

        virtual T operator--(int)
        { T t = __getter__(); __setter__(__getter__() - 1); return t; }

        virtual Property<T>& operator++()
        { __setter__(__getter__() + 1); return *this; }

        virtual Property<T>& operator--()
        { __setter__(__getter__() - 1); return *this; }

        #define COMPOUND_ASSIGNMENT(OP)                   \
            virtual Property<T>& operator OP##=(T o)         \
            { __setter__(__getter__() OP o); return *this; }

        COMPOUND_ASSIGNMENT(+)
        COMPOUND_ASSIGNMENT(-)
        COMPOUND_ASSIGNMENT(*)
        COMPOUND_ASSIGNMENT(/)
        COMPOUND_ASSIGNMENT(%)
        COMPOUND_ASSIGNMENT(>>)
        COMPOUND_ASSIGNMENT(<<)
        COMPOUND_ASSIGNMENT(&)
        COMPOUND_ASSIGNMENT(^)
        COMPOUND_ASSIGNMENT(|)

        #undef COMPOUND_ASSIGNMENT
    };

    template <typename T>
    class Property<const T> {

    public:
        using Getter = std::function<T()>;

    private:
        Getter __getter__;

        Property(const Property<T>&) = delete;
        Property(Property<T>&&) = delete;

    public:
        Property(Getter getter) : __getter__(getter) {}

        virtual operator T() const
        { return __getter__(); }
    };

    #define __get__() [&]()
    #define __set__(T) , [&](T value)

    template<typename T>
    class ObservableProperty : Property<T> {

    public:
        ObservableProperty() : Property();
        ObservableProperty(T o) : Property(o);

        ObservableProperty(Getter getter, Setter setter) : Property(getter, setter);

        Event SubscribePropertyChange;

        void Test() {
            SubscribePropertyChange += [&](){ return 0;};
        }
    };
}
