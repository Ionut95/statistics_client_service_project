package statistics.service.statisticsservicemanager;

import android.util.Log;
import android.os.ServiceManager;
import android.os.IBinder;
import android.os.RemoteException;

import statistics.service.api.IStatisticsService;

public class StatisticsServiceManager {
    private IBinder binder;
    private IStatisticsService service;

    private static StatisticsServiceManager instance;

    private StatisticsServiceManager() {
        binder = ServiceManager.getService("statistics.service.api.IStatisticsService/default");
        if (binder != null) {
            service = IStatisticsService.Stub.asInterface(binder);

            if (service != null) {
                Log.d("StatisticsServiceManager", "Service accessed succesfully!");
            } else {
                Log.e("StatisticsServiceManager", "Error to access service StatisticsServiceManager!");
            }
            
        } else {
            Log.e("StatisticsServiceManager", "Error to access binder!");
        }
    }

    public static StatisticsServiceManager getInstance() {
        if (instance == null) {
            instance = new StatisticsServiceManager();
        }
        return instance;
    }

    public Float getCpuTemperature() throws RemoteException {
        Log.i("StatisticsServiceManager", "W - getCpuTemperature");
        return service.getCpuTemperature();
    }

    public Float getGpuTemperature() throws RemoteException {
        Log.i("StatisticsServiceManager", "W - getGpuTemperature");
        return service.getGpuTemperature();
    }

    public Float getAmbientTemperature() throws RemoteException {
        Log.i("StatisticsServiceManager", "W - getAmbientTemperature");
        return service.getAmbientTemperature();
    }

    public Float getAverageCpuTemperature() throws RemoteException {
        Log.i("StatisticsServiceManager", "W - getAverageCpuTemperature");
        return service.getAverageCpuTemperature();
    }

    public Float getAverageGpuTemperature() throws RemoteException {
        Log.i("StatisticsServiceManager", "W - getAverageGpuTemperature");
        return service.getAverageGpuTemperature();
    }

    public Float getAverageAmbientTemperature() throws RemoteException {
        Log.i("StatisticsServiceManager", "W - getAverageAmbientTemperature");
        return service.getAverageAmbientTemperature();
    }

    public Float getMaxCpuTemperature() throws RemoteException {
        Log.i("StatisticsServiceManager", "W - getMaxCpuTemperature");
        return service.getMaxCpuTemperature();
    }

    public Float getMaxGpuTemperature() throws RemoteException {
        Log.i("StatisticsServiceManager", "W - getMaxGpuTemperature");
        return service.getMaxGpuTemperature();
    }

    public Float getMaxAmbientTemperature() throws RemoteException {
        Log.i("StatisticsServiceManager", "W - getMaxAmbientTemperature");
        return service.getMaxAmbientTemperature();
    }
}