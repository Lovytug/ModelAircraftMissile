#pragma once

#include "StateBase.h"

// ������ ������ ��������� State � �������
#define DEFINE_STATE(NAME, ENUMS...)                   \
    enum NAME##Index { ENUMS, NAME##Count };           \
    struct NAME : public StateBase<NAME##Count> {      \
        union {                                        \
            struct { double ENUMS; };                  \
            std::array<double, NAME##Count>& raw = this->data; \
        };                                             \
        NAME() { for (auto& v : data) v = 0.0; }        \
    };
