#include "StatisticsService.hpp"

#include <algorithm>
#include <fstream>
#include <numeric>
#include <sstream>

#include <utils/Log.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "statistics_service"

namespace statistics {
namespace service {

std::shared_ptr<StatisticsService> StatisticsService::instance_ = nullptr;

std::string StatisticsService::GetServiceName() {
    return std::string() + descriptor + "/default";
}

std::shared_ptr<StatisticsService> StatisticsService::GetInstance() {
    if (instance_ == nullptr)
    {
        instance_ = SharedRefBase::make<StatisticsService>();
    }
    return instance_;
}

StatisticsService::StatisticsService() {
    ReadTemperatures();
}

StatisticsService::~StatisticsService() {}

ScopedAStatus StatisticsService::GetCpuTemperature(float* value_return) {
    *value_return = GetValue(CallbacksId::CpuTemperature);
    return ScopedAStatus::ok();
}

ScopedAStatus StatisticsService::GetGpuTemperature(float* value_return) {
    *value_return = GetValue(CallbacksId::GpuTemperature);
    return ScopedAStatus::ok();
}

ScopedAStatus StatisticsService::GetAmbientTemperature(float* value_return) {
    *value_return = GetValue(CallbacksId::AmbientTemperature);
    return ScopedAStatus::ok();
}

ScopedAStatus StatisticsService::GetAverageCpuTemperature(float *value_return) {
    *value_return = GetValue(CallbacksId::AverageCpuTemperature);
    return ScopedAStatus::ok();
}

ScopedAStatus StatisticsService::GetAverageGpuTemperature(float *value_return) {
    *value_return = GetValue(CallbacksId::AverageGpuTemperature);
    return ScopedAStatus::ok();
}

ScopedAStatus StatisticsService::GetAverageAmbientTemperature(float *value_return) {
    *value_return = GetValue(CallbacksId::AverageAmbientTemperature);
    return ScopedAStatus::ok();
}

ScopedAStatus StatisticsService::GetMaxCpuTemperature(float *value_return) {
    *value_return = GetValue(CallbacksId::MaxCpuTemperature);
    return ScopedAStatus::ok();
}

ScopedAStatus StatisticsService::GetMaxGpuTemperature(float *value_return) {
    *value_return = GetValue(CallbacksId::MaxGpuTemperature);
    return ScopedAStatus::ok();
}

ScopedAStatus StatisticsService::GetMaxAmbientTemperature(float *value_return) {
    *value_return = GetValue(CallbacksId::MaxAmbientTemperature);
    return ScopedAStatus::ok();
}

void StatisticsService::ReadTemperatures() {
    std::ifstream file("/vendor/etc/temperatures.csv");

    if (file.is_open()) {
        ALOGI("%s:%d: file temperatures.csv open, reading values... ", __FUNCTION__, __LINE__);
        std::string line;
        
        while(getline(file, line)) {
            std::stringstream stream(line);
            std::string value;
            int current_value_index = 0;

            while(getline(stream, value, ',')) {
                switch (current_value_index) {
                    case 0:
                        all_cpu_temperatures_.push_back(std::stof(value));
                        break;
                    case 1:
                        all_gpu_temperatures_.push_back(std::stof(value));
                        break;
                    case 2:
                        all_ambient_temperatures_.push_back(std::stof(value));
                        break;
                    default:
                        ALOGE("%s:%d: Error when pushing values", __FUNCTION__, __LINE__);
                        break;
                }
                ++current_value_index;
            }
        }
    } else {
        ALOGE("%s:%d: std::cout << Error reading file ", __FUNCTION__, __LINE__);
    }
}

float StatisticsService::GetCpuValue() {
    float cpu_value = *(all_cpu_temperatures_.begin() + iterator_all_cpu_temps_);
    ++iterator_all_cpu_temps_;
    iterated_cpu_values_.push_back(cpu_value);

    if(iterator_all_cpu_temps_ == all_cpu_temperatures_.size())
        iterator_all_cpu_temps_ = 0;
    
    return cpu_value;
}

float StatisticsService::GetGpuValue() {
    float gpu_value = *(all_gpu_temperatures_.begin() + iterator_all_gpu_temps_);
    ++iterator_all_gpu_temps_;
    iterated_gpu_values_.push_back(gpu_value);

    if(iterator_all_gpu_temps_ == all_gpu_temperatures_.size())
        iterator_all_gpu_temps_ = 0;

    return gpu_value;
}

float StatisticsService::GetAmbientValue() {
    float ambient_value = *(all_ambient_temperatures_.begin() + iterator_all_ambient_temps_);
    ++iterator_all_ambient_temps_;
    iterated_ambient_values_.push_back(ambient_value);

    if(iterator_all_ambient_temps_ == all_ambient_temperatures_.size())
        iterator_all_ambient_temps_ = 0;

    return ambient_value;
}

float StatisticsService::CalculateAverageCpu() {
    if(iterator_all_cpu_temps_ == 1)  //when we start over, vector values have to be cleared excepting first element
        iterated_cpu_values_.erase(iterated_cpu_values_.begin() + 1, iterated_cpu_values_.end()); 

    float sum = std::accumulate(iterated_cpu_values_.begin(), iterated_cpu_values_.end(), 0.0f);

    if (sum == 0.0)
        return sum;

    return sum / iterated_cpu_values_.size();
}

float StatisticsService::CalculateAverageGpu() {
    if(iterator_all_gpu_temps_ == 1)  //when we start over, vector values have to be cleared excepting first element
        iterated_gpu_values_.erase(iterated_gpu_values_.begin() + 1, iterated_gpu_values_.end());

    float sum = std::accumulate(iterated_gpu_values_.begin(), iterated_gpu_values_.end(), 0.0f);
    
    if (sum == 0.0)
        return sum;
    
    return sum / iterated_gpu_values_.size();
}

float StatisticsService::CalculateAverageAmbient() {
    if (iterator_all_ambient_temps_ == 1)  //when we start over, vector values have to be cleared excepting first element
        iterated_ambient_values_.erase(iterated_ambient_values_.begin() + 1, iterated_ambient_values_.end());

    float sum = std::accumulate(iterated_ambient_values_.begin(), iterated_ambient_values_.end(), 0.0f);
    
    if (sum == 0.0)
        return sum;
    
    return sum / iterated_ambient_values_.size();
}

float StatisticsService::CalculateMaxCpu() {
    if(iterator_all_cpu_temps_ == 1)  //when we start over, vector values have to be cleared excepting first element
        iterated_cpu_values_.erase(iterated_cpu_values_.begin() + 1, iterated_cpu_values_.end());

    return *(std::max_element(iterated_cpu_values_.begin(), iterated_cpu_values_.end()));
}

float StatisticsService::CalculateMaxGpu() {
    if(iterator_all_gpu_temps_ == 1)  //when we start over, vector values have to be cleared excepting first element
        iterated_gpu_values_.erase(iterated_gpu_values_.begin() + 1, iterated_gpu_values_.end());

    return *(std::max_element(iterated_gpu_values_.begin(), iterated_gpu_values_.end()));
}

float StatisticsService::CalculateMaxAmbient() {
    if (iterator_all_ambient_temps_ == 1)  //when we start over, vector values have to be cleared excepting first element
        iterated_ambient_values_.erase(iterated_ambient_values_.begin() + 1, iterated_ambient_values_.end());

    return *(std::max_element(iterated_ambient_values_.begin(), iterated_ambient_values_.end()));
}

float StatisticsService::GetValue(CallbacksId id) {
    switch (id) {
        case CallbacksId::CpuTemperature:
            return GetCpuValue();
        case CallbacksId::GpuTemperature:
            return GetGpuValue();
        case CallbacksId::AmbientTemperature:
            return GetAmbientValue();
        case CallbacksId::AverageCpuTemperature:
            return CalculateAverageCpu();
        case CallbacksId::AverageGpuTemperature:
            return CalculateAverageGpu();
        case CallbacksId::AverageAmbientTemperature:
            return CalculateAverageAmbient();
        case CallbacksId::MaxCpuTemperature:
            return CalculateMaxCpu();
        case CallbacksId::MaxGpuTemperature:
            return CalculateMaxGpu();
        case CallbacksId::MaxAmbientTemperature:
            return CalculateMaxAmbient();
        default:
            return -0.1;
    }
}

}  //  namespace service
}  //  namespace statistics
