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

            // IStatisticsService AIDL interface callbacks
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
            int current_line_to_read = 1;
            const int TOTAL_NR_LINES = 50;

            //static std::vector<float> temperatures;
            //size_t current_index = 0;
            //const size_t ITEMS_PER_LINE = 3;

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

            std::vector<float> readTemperatures();
            float getValue(CallbacksId id);
        };
    }
}

#endif  // STATISTICS_SERVICE

