#pragma once

#include <vector>
#include <string>


class Tester {
public:
    std::vector<std::string> testList;

    template<typename ...Strings>
    void specify(Strings... strings) {
        testList = { strings... }; //unpack strings here
    }

    bool runAll();
};
