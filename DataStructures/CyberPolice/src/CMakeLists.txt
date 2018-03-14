project(CyberPolice)

set(SOURCE_FILES
        JournalNetActivity.h
        JournalNetActivity.hpp
        main.cpp
        NetActivity.cpp
        NetActivity.h
        OrderedList.h
        OrderedList.hpp
        SkipList.h
        SkipList.hpp
        TimeStamp.cpp
        TimeStamp.h
        stdafx.h)

add_executable(CyberPolice ${SOURCE_FILES})
