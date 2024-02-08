
#include "StatisticsService.hpp"
#include <utils/Log.h>
#include <fstream>
#include <sstream>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "statistics_service"

namespace statistics {
    namespace service {

        ::std::shared_ptr<StatisticsService> StatisticsService::S_INSTANCE = NULL;

        ::std::shared_ptr<StatisticsService> StatisticsService::getInstance()
        {
            if (S_INSTANCE == NULL)
            {
                S_INSTANCE = ndk::SharedRefBase::make<StatisticsService>();
            }
            return S_INSTANCE;
        }

        // std::vector<float> StatisticsService::temperatures {120, 33.4, 19,
        //                                                     256.1, 22, 41.9,
        //                                                     320.8, 53.4, 19,
        //                                                     442.1, 22, 14.9,
        //                                                     520, 33.4, 19.7,
        //                                                     65.1, 12, 44.9,
        //                                                     72, 33.4, 79,
        //                                                     856.1, 22, 44.9,
        //                                                     940, 33.4, 19.1,
        //                                                     1053.1, 27, 24.9,
        //                                                     1120, 33.4, 19,
        //                                                     1256.1, 22, 41.9,
        //                                                     1320.8, 53.4, 19,
        //                                                     1442.1, 22, 14.9,
        //                                                     1520, 33.4, 19.7,
        //                                                     165.1, 12, 44.9,
        //                                                     172, 33.4, 79,
        //                                                     1856.1, 22, 44.9,
        //                                                     1940, 33.4, 19.1,
        //                                                     2053.1, 27, 24.9,
        //                                                     2120, 33.4, 19,
        //                                                     2256.1, 22, 41.9,
        //                                                     2320.8, 53.4, 19,
        //                                                     2442.1, 22, 14.9,
        //                                                     2520, 33.4, 19.7,
        //                                                     265.1, 12, 44.9,
        //                                                     272, 33.4, 79,
        //                                                     2856.1, 22, 44.9,
        //                                                     2940, 33.4, 19.1,
        //                                                     3053.1, 27, 24.9,
        //                                                     3120, 33.4, 19,
        //                                                     3256.1, 22, 41.9,
        //                                                     3320.8, 53.4, 19,
        //                                                     3442.1, 22, 14.9,
        //                                                     3520, 33.4, 19.7,
        //                                                     365.1, 12, 44.9,
        //                                                     372, 33.4, 79,
        //                                                     3856.1, 22, 44.9,
        //                                                     3940, 33.4, 19.1,
        //                                                     4053.1, 27, 24.9,
        //                                                     4120, 33.4, 19,
        //                                                     4256.1, 22, 41.9,
        //                                                     4320.8, 53.4, 19,
        //                                                     4442.1, 22, 14.9,
        //                                                     4520, 33.4, 19.7,
        //                                                     465.1, 12, 44.9,
        //                                                     472, 33.4, 79,
        //                                                     4856.1, 22, 44.9,
        //                                                     4940, 33.4, 19.1,
        //                                                     5053.1, 27, 24.9};

        StatisticsService::StatisticsService()
        {

        }

        StatisticsService::~StatisticsService()
        {

        }

        ::ndk::ScopedAStatus StatisticsService::getCpuTemperature(float* value_return)
        {
            CallbacksId id = CallbacksId::CpuTemperature;
            *value_return = getValue(id);
            return ndk::ScopedAStatus::ok();
        }

        ::ndk::ScopedAStatus StatisticsService::getGpuTemperature(float* value_return)
        {
            CallbacksId id = CallbacksId::GpuTemperature;
            *value_return = getValue(id);
            return ndk::ScopedAStatus::ok();
        }

        ::ndk::ScopedAStatus StatisticsService::getAmbientTemperature(float* value_return)
        {
            CallbacksId id = CallbacksId::AmbientTemperature;
            *value_return = getValue(id);
            return ndk::ScopedAStatus::ok();
        }

        ::ndk::ScopedAStatus StatisticsService::getAverageCpuTemperature(float *value_return)
        {
            CallbacksId id = CallbacksId::AverageCpuTemperature;
            *value_return = getValue(id);
            return ndk::ScopedAStatus::ok();
        }

        ::ndk::ScopedAStatus StatisticsService::getAverageGpuTemperature(float *value_return)
        {
            CallbacksId id = CallbacksId::AverageGpuTemperature;
            *value_return = getValue(id);
            return ndk::ScopedAStatus::ok();
        }

        ::ndk::ScopedAStatus StatisticsService::getAverageAmbientTemperature(float *value_return)
        {
            CallbacksId id = CallbacksId::AverageAmbientTemperature;
            *value_return = getValue(id);
            return ndk::ScopedAStatus::ok();
        }

        ::ndk::ScopedAStatus StatisticsService::getMaxCpuTemperature(float *value_return)
        {
            CallbacksId id = CallbacksId::MaxCpuTemperature;
            *value_return = getValue(id);
            return ndk::ScopedAStatus::ok();
        }

        ::ndk::ScopedAStatus StatisticsService::getMaxGpuTemperature(float *value_return)
        {
            CallbacksId id = CallbacksId::MaxGpuTemperature;
            *value_return = getValue(id);
            return ndk::ScopedAStatus::ok();
        }

        ::ndk::ScopedAStatus StatisticsService::getMaxAmbientTemperature(float *value_return)
        {
            CallbacksId id = CallbacksId::MaxAmbientTemperature;
            *value_return = getValue(id);
            return ndk::ScopedAStatus::ok();
        }

        std::vector<float> StatisticsService::readTemperatures() {
            std::vector<float> values;

            if(current_line_to_read > TOTAL_NR_LINES)
                current_line_to_read = 1;

            std::ifstream file("/vendor/etc/temperatures.csv");

            if (file.is_open())
            {
                ALOGI("%s:%d: file temperatures.csv open, reading values... ", __FUNCTION__, __LINE__);
                std::string line;
                for(int i = 1; getline(file, line); ++i)
                {
                    if(i == current_line_to_read) {
                        std::stringstream stream(line);
                        std::string value;

                        while(getline(stream, value, ','))
                        {
                            std::stringstream token(value);
                            float myFloat;
                            token >> myFloat;
                            values.push_back(myFloat);
                        }

                        ++current_line_to_read;
                        file.close();
                        break;
                    }
                }
            }
            else
            {
                ALOGE("%s:%d: Error reading file ", __FUNCTION__, __LINE__);
                for(int it = 0; it < 3; ++it) 
                {
                    values.push_back(0);
                }
            }
            return values;
        }

        // std::vector<float> StatisticsService::readTemperatures() 
        // {
        //     std::vector<float> values;
        //     ALOGI("%s:%d: Inside readTemperatures(), printing current index %d", __FUNCTION__, __LINE__, (int)current_index);
        //     if(current_index == temperatures.size())
        //     {
        //         current_index = 0;
        //     }

        //     if (!temperatures.empty()) 
        //     {
        //         ALOGI("%s:%d: Inside readTemperatures(), reading temperatures...", __FUNCTION__, __LINE__);
        //         for(size_t it = 0; it < ITEMS_PER_LINE; ++it)
        //         {
        //             values.push_back(temperatures[current_index]);
        //             ++current_index;
        //         }
        //     }
        //     else
        //     {
        //         ALOGE("%s:%d: Error temperatures vector empty ", __FUNCTION__, __LINE__);
        //         for(size_t it = 0; it < ITEMS_PER_LINE; ++it) 
        //         {
        //             values.push_back(0);
        //         }
        //     }

        //     return values;
        // }


        float StatisticsService::getValue(CallbacksId id)
        {
            std::vector<float> read_values = readTemperatures();

            switch (id) {
                case CallbacksId::CpuTemperature:
                    return read_values[0];
                case CallbacksId::GpuTemperature:
                    return read_values[1];
                case CallbacksId::AmbientTemperature:
                    return read_values[2];
                case CallbacksId::AverageCpuTemperature:
                    return read_values[0];
                case CallbacksId::AverageGpuTemperature:
                    return read_values[1];
                case CallbacksId::AverageAmbientTemperature:
                    return read_values[2];
                case CallbacksId::MaxCpuTemperature:
                    return read_values[0];
                case CallbacksId::MaxGpuTemperature:
                    return read_values[1];
                case CallbacksId::MaxAmbientTemperature:
                    return read_values[2];
                default:
                    return 0.0;
            }
        }
    }
}

