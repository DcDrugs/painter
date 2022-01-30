#pragma once
#include <fstream>


template<typename TBased>
class HasLoad {
private:
    typedef char no;
    typedef struct yes { no n[2]; } yes;


    template<typename U>
    static auto test(U* u) -> decltype((*u).Load(*((std::ifstream*)0), 0), yes());
    static no test(...);

public:
    static constexpr bool value = (sizeof(test((TBased*)0)) == sizeof(yes));
};

template<typename TBased>
class HasInstance {
private:
    typedef char no;
    typedef struct yes { no n[2]; } yes;


    template<typename U>
    static auto test(U* u) -> decltype((*u).Instance(*((BaseConfiguration*)0)), yes());
    static no test(...);

public:
    static constexpr bool value = (sizeof(test((TBased*)0)) == sizeof(yes));
};
