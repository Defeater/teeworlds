/*
    unsigned char*
*/
#ifndef ENGINE_CLIENT_GEOIP_H
#define ENGINE_CLIENT_GEOIP_H

#include <base/system.h>
#include <engine/geoip.h>
#include <string>
#include <list>

class CGeoIP : public IGeoIP
{
public:
    CGeoIP();

    void GetInfo(std::string ip, IGeoIP::GeoInfo *geoInfo);
};

#endif
