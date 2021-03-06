#ifndef SLC_DEVICE_ID_H_INCLUDED
#define SLC_DEVICE_ID_H_INCLUDED

#include <lwstreams/lwstreams.h>
#include <alogging/alogging.h>

struct NodeLoraId {
    uint8_t ptr[8] = { 0 };
    size_t size{ 8 };

    NodeLoraId() {
    }

    NodeLoraId(lws::BufferPtr bp) {
        auto copying = bp.size >= size ? size : bp.size;
        memcpy(ptr, bp.ptr, copying);
        size = copying;
    }

    uint8_t &operator[](int32_t index) {
        lws_assert(index >= 0 && index < (int32_t)size);
        return ptr[index];
    }

    uint8_t operator[] (int32_t index) const {
        lws_assert(index >= 0 && index < (int32_t)size);
        return ptr[index];
    }
};

inline LogStream& operator<<(LogStream &log, const NodeLoraId &deviceId) {
    if (deviceId.size == 8) {
        log.printf("%02x%02x%02x%02x%02x%02x%02x%02x",
                   deviceId[0], deviceId[1], deviceId[2], deviceId[3],
                   deviceId[4], deviceId[5], deviceId[6], deviceId[7]);
    }
    else {
        log.printf("<EmptyDeviceId>");
    }
    return log;
}

inline bool operator==(const NodeLoraId& lhs, const NodeLoraId& rhs) {
    if (lhs.size != rhs.size) {
        return false;
    }
    if (lhs.size == 0) {
        return true;
    }
    for (auto i = 0; i < (int32_t)lhs.size; ++i) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

inline bool operator!=(const NodeLoraId& lhs, const NodeLoraId& rhs) {
    return !(lhs == rhs);
}

#endif
