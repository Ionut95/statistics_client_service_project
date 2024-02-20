package statistics.service.api;

@VintfStability
interface IStatisticsService {
    float GetCpuTemperature();
    float GetGpuTemperature();
    float GetAmbientTemperature();
    float GetAverageCpuTemperature();
    float GetAverageGpuTemperature();
    float GetAverageAmbientTemperature();
    float GetMaxCpuTemperature();
    float GetMaxGpuTemperature();
    float GetMaxAmbientTemperature();
}
