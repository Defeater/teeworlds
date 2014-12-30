/*
    unsigned char*
*/
#ifndef ENGINE_GEOIP_H
#define ENGINE_GEOIP_H

#include "kernel.h"
#include <string>
#include <csignal>

class IGeoIP : public IInterface
{
	MACRO_INTERFACE("geoip", 0)
public:
    struct GeoInfo {
        GeoInfo() {
            m_CountryCode = "NULL";
        }

        std::string m_CountryCode;
        std::string m_CountryName;
        std::string m_Isp;
    };

    virtual void GetInfo(std::string ip, IGeoIP::GeoInfo *geoInfo) = 0;
};

struct InfoGeoIPThread {
    IGeoIP *m_pGeoIP;
    IGeoIP::GeoInfo *m_pGeoInfo;
    char ip[64];
};

void ThreadGeoIP(void *);
#endif
