
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

        StatisticsService::current_line_to_read = 1;

        StatisticsService::StatisticsService()
        {

        }

        StatisticsService::~StatisticsService()
        {

        }

        ::ndk::ScopedAStatus StatisticsService::getCpuTemperature(float* value_return)
        {
            CallbacksId id = CallbacksId::CpuTemperature;
            value_return = getValue(id);
            return ndk::ScopedAStatus::ok();
        }

        ::ndk::ScopedAStatus StatisticsService::getGpuTemperature(float* value_return)
        {
            CallbacksId id = CallbacksId::GpuTemperature;
            value_return = getValue(id);
            return ndk::ScopedAStatus::ok();
        }

        ::ndk::ScopedAStatus StatisticsService::getAmbientTemperature(float* value_return)
        {
            CallbacksId id = CallbacksId::AmbientTemperature;
            value_return = getValue(id);
            return ndk::ScopedAStatus::ok();
        }

        ::ndk::ScopedAStatus StatisticsService::getAverageCpuTemperature(float *value_return)
        {
            CallbacksId id = CallbacksId::AverageCpuTemperature;
            value_return = getValue(id);
            return ndk::ScopedAStatus::ok();
        }

        ::ndk::ScopedAStatus StatisticsService::getAverageGpuTemperature(float *value_return)
        {
            CallbacksId id = CallbacksId::AverageGpuTemperature;
            value_return = getValue(id);
            return ndk::ScopedAStatus::ok();
        }

        ::ndk::ScopedAStatus StatisticsService::getAverageAmbientTemperature(float *value_return)
        {
            CallbacksId id = CallbacksId::AverageAmbientTemperature;
            value_return = getValue(id);
            return ndk::ScopedAStatus::ok();
        }

        ::ndk::ScopedAStatus StatisticsService::getMaxCpuTemperature(float *value_return)
        {
            CallbacksId id = CallbacksId::MaxCpuTemperature;
            value_return = getValue(id);
            return ndk::ScopedAStatus::ok();
        }

        ::ndk::ScopedAStatus StatisticsService::getMaxGpuTemperature(float *value_return)
        {
            CallbacksId id = CallbacksId::MaxGpuTemperature;
            value_return = getValue(id);
            return ndk::ScopedAStatus::ok();
        }

        ::ndk::ScopedAStatus StatisticsService::getMaxAmbientTemperature(float *value_return)
        {
            CallbacksId id = CallbacksId::MaxAmbientTemperature;
            value_return = getValue(id);
            return ndk::ScopedAStatus::ok();
        }

        float StatisticsService::readTemperatures() {
            std::vector<float> values;

            if(current_line_to_read > TOTAL_NR_LINES)
                current_line_to_read = 1;

            std::fstream file("temperatures.csv");

            if (file.is_open())
            {
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
            return values;
        }

        float StatisticsService::getValue(CallbacksId id)
        {
            std::vector<float> read_values = readTemperatures();

            switch (id) {
                CallbacksId::CpuTemperature:
                    return read_values[0];
                CallbacksId::GpuTemperature:
                    return read_values[1];
                CallbacksId::AmbientTemperature:
                    return read_values[2];
                CallbacksId::AverageCpuTemperature:
                    return read_values[0];
                CallbacksId::AverageGpuTemperature:
                    return read_values[1];
                CallbacksId::AverageAmbientTemperature:
                    return read_values[2];
                CallbacksId::MaxCpuTemperature:
                    return read_values[0];
                CallbacksId::MaxGpuTemperature:
                    return read_values[1];
                CallbacksId::MaxAmbientTemperature:
                    return read_values[2];
                default:
                    return 0.0;
            }
        }
    }
}

