#pragma once

#define NOT_COPYABLE_OR_MOVABLE(classname)                 \
private:                                                   \
    classname(const classname&) = delete;                  \
    classname& operator=(const classname& other) = delete; \
    classname(classname&&) = delete;                       \
    classname& operator=(classname&&) = delete
