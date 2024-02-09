#ifndef STATISTICS_SERVICE
#define STATISTICS_SERVICE


#include <aidl/statistics/service/api/BnStatisticsService.h>
#include <vector>

namespace statistics {
    namespace service {

        class StatisticsService
                : public ::aidl::statistics::service::api::BnStatisticsService
        {
        public:
            StatisticsService();
            ~StatisticsService();

            static ::std::shared_ptr<StatisticsService> getInstance();

            IStatisticsService AIDL interface callbacks
            ::ndk::ScopedAStatus getCpuTemperature(float* value_return) override;
            ::ndk::ScopedAStatus getGpuTemperature(float* value_return) override;
            ::ndk::ScopedAStatus getAmbientTemperature(float* value_return) override;
            ::ndk::ScopedAStatus getAverageCpuTemperature(float* value_return) override;
            ::ndk::ScopedAStatus getAverageGpuTemperature(float* value_return) override;
            ::ndk::ScopedAStatus getAverageAmbientTemperature(float* value_return) override;
            ::ndk::ScopedAStatus getMaxCpuTemperature(float* value_return) override;
            ::ndk::ScopedAStatus getMaxGpuTemperature(float* value_return) override;
            ::ndk::ScopedAStatus getMaxAmbientTemperature(float* value_return) override;

            std::string getServiceName(void)
            {
                return std::string() + descriptor + "/default";
            }

        private:
            static ::std::shared_ptr<StatisticsService> S_INSTANCE;

        public:
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

            void readTemperatures();
            float getValue(CallbacksId id);

            float getCpuValue();
            float getGpuValue();
            float getAmbientValue();
            float calculateAverageCpu();
            float calculateAverageGpu();
            float calculateAverageAmbient();
            float calculateMaxCpu();
            float calculateMaxGpu();
            float calculateMaxAmbient();

            //read values from file
            std::vector<float> all_cpu_temperatures;
            std::vector<float> all_gpu_temperatures;
            std::vector<float> all_ambient_temperatures;
            
            int iterator_all_cpu_temps = 0;
            int iterator_all_gpu_temps = 0;
            int iterator_all_ambient_temps = 0;

            //current iterated values
            std::vector<float> iterated_cpu_values;
            std::vector<float> iterated_gpu_values;
            std::vector<float> iterated_ambient_values;
        };
    }
}

#endif  // STATISTICS_SERVICE

