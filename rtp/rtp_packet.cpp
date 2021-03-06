#include "rtp_packet.h"

RTP_packet::RTP_packet()
{

}

QByteArray &RTP_packet::data()
{
    return _data;
}

int RTP_packet::getPayloadStart()
{
    return RTP_HEADER_SIZE + getCC() * 4;
}

int RTP_packet::getPayloadLength()
{
    return _data.length() - getPayloadStart();
}

/**
 * @brief Количество CSRC идентификаторов
 * @return
 */
BYTE RTP_packet::getCC()
{
    BYTE c = (BYTE)((_data[0]) & 0x0f);
    return  c;
}

bool RTP_packet::hasPadding()
{
    return ((_data[0] & 0x20) >> 5) == 1;
}


unsigned int RTP_packet::getTimeStamp()
{    
    int idx = 4; //-- с какой позиции начиная

    //-- собираем 4 байта в int
    unsigned int i = (((_data[idx] << 24) & 0xFF000000L)
        | ((_data[idx + 1] << 16) & 0xFF0000L)
        | (_data[idx + 2] << 8 & 0xFF00L)
        | (_data[idx + 3] & 0xFFL));

    return i;
}


unsigned short RTP_packet::getSequence()
{
    unsigned short s;

    int idx = 2; //-- с какой позиции начиная

    //-- собираем 2 байта в unsigned short
    s = (((_data[idx] << 8) & 0xFF00) | (_data[idx+1] & 0xFF));

    return s;
}
