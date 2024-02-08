
package statistics.service.api;

@VintfStability
interface IStatisticsService {
    float getCpuTemperature();
    float getGpuTemperature();
    float getAmbientTemperature();
    float getAverageCpuTemperature();
    float getAverageGpuTemperature();
    float getAverageAmbientTemperature();
    float getMaxCpuTemperature();
    float getMaxGpuTemperature();
    float getMaxAmbientTemperature();
}
