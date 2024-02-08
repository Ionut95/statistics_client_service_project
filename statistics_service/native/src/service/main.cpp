#include "StatisticsService.hpp"
#include <utils/Log.h>
#include <android/log.h>
#include <iostream>
#include <signal.h>
#include <android/binder_ibinder.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <fstream>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "statistics-service"

namespace ssnamespace = statistics::service;

int main()
{
    ALOGI("%s:%d: starting service", __FUNCTION__, __LINE__);

    signal(SIGPIPE, SIG_IGN);
    if (ABinderProcess_setThreadPoolMaxThreadCount(1))
    {
        std::shared_ptr<ssnamespace::StatisticsService> ssObj = ssnamespace::StatisticsService::getInstance();
        if (ssObj)
        {
            binder_status_t status = AServiceManager_addService(ssObj->asBinder().get(),
                                                                ssObj->getServiceName().c_str());
            if (status != STATUS_OK)
            {
                ALOGE("%s:%d: adding service failed", __FUNCTION__, __LINE__);
            }
            else
            {
                int32_t version = -1;
                ssObj->getInterfaceVersion(&version);
                //std::string temp = (std::string("IONUT ") + ssObj->getServiceName());
                //ssnamespace::StatisticsService obj = ssnamespace::StatisticsService();
                std::ifstream file;
                file.open("/vendor/etc/temperatures.csv");
                if(file.is_open())
                {
                    std::string line;
                    getline(file, line);
                    ALOGI("%s:%d: file open read first_value: %s*", __FUNCTION__, __LINE__, line.c_str());
                }
                else
                {
                    ALOGE("%s:%d: ERROR file NOT open!!!", __FUNCTION__, __LINE__);
                }
                ALOGI("%s:%d: service ready (registered version V%d)", __FUNCTION__, __LINE__, version);
                ABinderProcess_joinThreadPool();
            }
        }
        else
        {
            ALOGE("%s:%d: service NULL", __FUNCTION__, __LINE__);
        }
    }
    else
    {
        ALOGE("%s:%d: configure thread-pool failed", __FUNCTION__, __LINE__);
    }
    ALOGW("%s:%d: service joined", __FUNCTION__, __LINE__);

    return 0;  // should never get here
}
