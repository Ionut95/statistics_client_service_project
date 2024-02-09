
#include "StatisticsService.hpp"
#include <utils/Log.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <numeric>

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

        StatisticsService::StatisticsService()
        {
            readTemperatures();
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

        void StatisticsService::readTemperatures() 
        {
            std::ifstream file("/vendor/etc/temperatures.csv");

            if (file.is_open())
            {
                ALOGI("%s:%d: std::cout << file temperatures.csv open, reading values... ", __FUNCTION__, __LINE__);
                std::string line;
                
                while(getline(file, line))
                {
                    std::stringstream stream(line);
                    std::string value;
                    int current_value_index = 0;

                    while(getline(stream, value, ','))
                    {
                        switch (current_value_index) {
                            case 0:
                                all_cpu_temperatures.push_back(::std::stof(value));
                                break;
                            case 1:
                                all_gpu_temperatures.push_back(::std::stof(value));
                                break;
                            case 2:
                                all_ambient_temperatures.push_back(::std::stof(value));
                                break;
                            default:
                                ALOGE("%s:%d: Error when pushing values", __FUNCTION__, __LINE__);
                                break;
                        }
                        ++current_value_index;
                    }
                }
                file.close();
            }
            else
            {
                ALOGE("%s:%d: std::cout << Error reading file ", __FUNCTION__, __LINE__);
            }
        }

        float StatisticsService::getCpuValue()
        {
            float cpu_value = *(all_cpu_temperatures.begin() + iterator_all_cpu_temps);
            std::cout << "$" << iterator_all_cpu_temps << "$";
            ++iterator_all_cpu_temps;
            iterated_cpu_values.push_back(cpu_value);

            if(iterator_all_cpu_temps == all_cpu_temperatures.size())
                iterator_all_cpu_temps = 0;
            
            return cpu_value;
        }

        float StatisticsService::getGpuValue()
        {
            float gpu_value = *(all_gpu_temperatures.begin() + iterator_all_gpu_temps);
            std::cout << "$" << iterator_all_gpu_temps << "$";
            ++iterator_all_gpu_temps;
            iterated_gpu_values.push_back(gpu_value);

            if(iterator_all_gpu_temps == all_gpu_temperatures.size())
                iterator_all_gpu_temps = 0;

            return gpu_value;
        }

        float StatisticsService::getAmbientValue()
        {
            float ambient_value = *(all_ambient_temperatures.begin() + iterator_all_ambient_temps);
            std::cout << "$" << iterator_all_ambient_temps << "$";
            ++iterator_all_ambient_temps;
            iterated_ambient_values.push_back(ambient_value);

            if(iterator_all_ambient_temps == all_ambient_temperatures.size())
                iterator_all_ambient_temps = 0;

            return ambient_value;
        }

        float StatisticsService::calculateAverageCpu()
        {
            if(iterator_all_cpu_temps == 1)  //if we start over again, vector values has to be cleared excepting first element
                iterated_cpu_values.erase(iterated_cpu_values.begin() + 1, iterated_cpu_values.end()); 

            float sum = std::accumulate(iterated_cpu_values.begin(), iterated_cpu_values.end(), 0.0f);
            std::cout << "$" << sum << "$";

            if (sum == 0)
            {
                std::cout << "&sum is 0&";
                return sum;
            }

            return sum / iterated_cpu_values.size();
        }

        float StatisticsService::calculateAverageGpu()
        {
            if(iterator_all_gpu_temps == 1)  //if we start over again, vector values has to be cleared excepting first element
                iterated_gpu_values.erase(iterated_gpu_values.begin() + 1, iterated_gpu_values.end());

            float sum = std::accumulate(iterated_gpu_values.begin(), iterated_gpu_values.end(), 0.0f);
            std::cout << "$" << sum << "$";
            
            if (sum == 0)
            {
                std::cout << "&sum is 0&";
                return sum;
            }
            
            return sum / iterated_gpu_values.size();
        }

        float StatisticsService::calculateAverageAmbient()
        {
            if (iterator_all_ambient_temps == 1)  //if we start over again, vector values has to be cleared excepting first element
                iterated_ambient_values.erase(iterated_ambient_values.begin() + 1, iterated_ambient_values.end());

            float sum = std::accumulate(iterated_ambient_values.begin(), iterated_ambient_values.end(), 0.0f);
            std::cout << "$" << sum << "$";
            
            if (sum == 0)
            {
                std::cout << "&sum is 0&";
                return sum;
            }
            
            return sum / iterated_ambient_values.size();
        }

        float StatisticsService::calculateMaxCpu()
        {
            if(iterator_all_cpu_temps == 1)  //if we start over again, vector values has to be cleared excepting first element
                iterated_cpu_values.erase(iterated_cpu_values.begin() + 1, iterated_cpu_values.end());

            return *(std::max_element(iterated_cpu_values.begin(), iterated_cpu_values.end()));
        }

        float StatisticsService::calculateMaxGpu()
        {
            if(iterator_all_gpu_temps == 1)  //if we start over again, vector values has to be cleared excepting first element
                iterated_gpu_values.erase(iterated_gpu_values.begin() + 1, iterated_gpu_values.end());

            return *(std::max_element(iterated_gpu_values.begin(), iterated_gpu_values.end()));
        }

        float StatisticsService::calculateMaxAmbient()
        {
            if (iterator_all_ambient_temps == 1)  //if we start over again, vector values has to be cleared excepting first element
                iterated_ambient_values.erase(iterated_ambient_values.begin() + 1, iterated_ambient_values.end());

            return *(std::max_element(iterated_ambient_values.begin(), iterated_ambient_values.end()));
        }




        float StatisticsService::getValue(CallbacksId id)
        {
            switch (id) {
                case CallbacksId::CpuTemperature:
                    return getCpuValue();
                case CallbacksId::GpuTemperature:
                    return getGpuValue();
                case CallbacksId::AmbientTemperature:
                    return getAmbientValue();
                case CallbacksId::AverageCpuTemperature:
                    return calculateAverageCpu();
                case CallbacksId::AverageGpuTemperature:
                    return calculateAverageGpu();
                case CallbacksId::AverageAmbientTemperature:
                    return calculateAverageAmbient();
                case CallbacksId::MaxCpuTemperature:
                    return calculateMaxCpu();
                case CallbacksId::MaxGpuTemperature:
                    return calculateMaxGpu();
                case CallbacksId::MaxAmbientTemperature:
                    return calculateMaxAmbient();
                default:
                    return -0.1;
            }
        }
    }
}

