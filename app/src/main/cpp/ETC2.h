# pragma once
/*
 * See: https://github.com/Yalantis/GLata/blob/master/glata/src/main/java/com/yalantis/glata/core/texture/ETC2Util.kt
 * for values.
 */
class ETC2Header {

public:
    int width = 0;
    int height = 0;
    int size = 0;
    char* imageData = nullptr;

public:
    ETC2Header(char* data){
        assert(data[0] == etc2Magic[0]);
        assert(data[1] == etc2Magic[1]);
        assert(data[2] == etc2Magic[2]);
        assert(data[3] == etc2Magic[3]);
        assert(data[4] == etc2Magic[4]);
        assert(data[5] == etc2Magic[5]);

        width = getShort(data + ETC2_PKM_ENCODED_WIDTH_OFFSET);
        height = getShort(data + ETC2_PKM_ENCODED_HEIGHT_OFFSET);
        size = (width / 4) * (height / 4) * 8;
        imageData = data + ETC_PKM_HEADER_SIZE;
    }

private:
    // First couple of chars defining the file compression
    char etc2Magic[6] = {
            'P',
            'K',
            'M',
            ' ',
            '2',
            '0'
    };
    // Both ETC1 and ETC2 have the same header size
    static const int ETC_PKM_HEADER_SIZE = 16;

    static const int ETC2_PKM_FORMAT_OFFSET = 6;
    static const int ETC2_PKM_ENCODED_WIDTH_OFFSET = 8;
    static const int ETC2_PKM_ENCODED_HEIGHT_OFFSET = 10;
    static const int ETC2_PKM_WIDTH_OFFSET = 12;
    static const int ETC2_PKM_HEIGHT_OFFSET = 14;

private:
    // Gets the next two bytes
    uint16_t getShort(const char* data) const {
        return data[0] << 8 | data[1];
    }
};
