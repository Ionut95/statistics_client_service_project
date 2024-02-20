#ifndef STATISTICS_SERVICE_H_
#define STATISTICS_SERVICE_H_


#include <vector>

#include <aidl/statistics/service/api/BnStatisticsService.h>

namespace statistics {
namespace service {

using ::aidl::statistics::service::api::BnStatisticsService;
using ::ndk::ScopedAStatus;

class StatisticsService: public BnStatisticsService {
    public:
        StatisticsService();
        ~StatisticsService();

        static std::shared_ptr<StatisticsService> GetInstance();
        std::string GetServiceName();

        //IStatisticsService AIDL interface callbacks
        ScopedAStatus GetCpuTemperature(float* value_return) override;
        ScopedAStatus GetGpuTemperature(float* value_return) override;
        ScopedAStatus GetAmbientTemperature(float* value_return) override;
        ScopedAStatus GetAverageCpuTemperature(float* value_return) override;
        ScopedAStatus GetAverageGpuTemperature(float* value_return) override;
        ScopedAStatus GetAverageAmbientTemperature(float* value_return) override;
        ScopedAStatus GetMaxCpuTemperature(float* value_return) override;
        ScopedAStatus GetMaxGpuTemperature(float* value_return) override;
        ScopedAStatus GetMaxAmbientTemperature(float* value_return) override;

    private:
        enum class CallbacksId {
            CpuTemperature = 1,
            GpuTemperature,
            AmbientTemperature,
            AverageCpuTemperature,
            AverageGpuTemperature,
            AverageAmbientTemperature,
            MaxCpuTemperature,
            MaxGpuTemperature,
            MaxAmbientTemperature,
        };

        void ReadTemperatures();
        float GetValue(CallbacksId id);

        float GetCpuValue();
        float GetGpuValue();
        float GetAmbientValue();
        float CalculateAverageCpu();
        float CalculateAverageGpu();
        float CalculateAverageAmbient();
        float CalculateMaxCpu();
        float CalculateMaxGpu();
        float CalculateMaxAmbient();

        //read all values from file
        std::vector<float> all_cpu_temperatures_;
        std::vector<float> all_gpu_temperatures_;
        std::vector<float> all_ambient_temperatures_;
        
        size_t iterator_all_cpu_temps_ = 0;
        size_t iterator_all_gpu_temps_ = 0;
        size_t iterator_all_ambient_temps_ = 0;

        //current iterated values
        std::vector<float> iterated_cpu_values_;
        std::vector<float> iterated_gpu_values_;
        std::vector<float> iterated_ambient_values_;

        static std::shared_ptr<StatisticsService> instance_;
};

}  //  namespace service
}  //  namespace statistics

#endif  // STATISTICS_SERVICE_H_
