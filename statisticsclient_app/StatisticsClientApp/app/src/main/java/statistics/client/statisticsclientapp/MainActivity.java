package statistics.client.statisticsclientapp;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.os.RemoteException;
import android.util.Log;
import android.widget.TextView;
import java.util.Timer;
import java.util.TimerTask;
import java.text.DecimalFormat;
import java.text.NumberFormat;

import statistics.service.statisticsservicemanager.StatisticsServiceManager;

public class MainActivity extends AppCompatActivity {

    private StatisticsServiceManager  statisticsServiceManager = StatisticsServiceManager.getInstance();
    private Timer timer;
    private NumberFormat formatter = new DecimalFormat("#0.00");

   private void displayCpuTemperature() {
        try {
            Float valueCpu = statisticsServiceManager.getCpuTemperature();
            String textView = "Cpu temperature:\n" + formatter.format(valueCpu);
            ((TextView)findViewById(R.id.textView1)).setText(textView);
        } catch (RemoteException e) {
            Log.e("StatisticsClientApp: ", "Error when trying to access binder!");
            e.printStackTrace();
        }
   }

   private void displayGpuTemperature() {
        try {
            Float valueGpu = statisticsServiceManager.getGpuTemperature();
            String textView = "Gpu temperature:\n" + formatter.format(valueGpu);
            ((TextView)findViewById(R.id.textView2)).setText(textView);
        } catch (RemoteException e) {
            Log.e("StatisticsClientApp: ", "Error when trying to access binder!");
            e.printStackTrace();
        }
   }

   private void displayAmbientTemperature() {
        try {
            Float valueAmbient = statisticsServiceManager.getAmbientTemperature();
            String textView = "Ambient temperature:\n" + formatter.format(valueAmbient);
            ((TextView)findViewById(R.id.textView3)).setText(textView);
        } catch (RemoteException e) {
            Log.e("StatisticsClientApp: ", "Error when trying to access binder!");
            e.printStackTrace();
        }
   }

   private void displayAverageCpuTemperature() {
        try {
            Float valueAverageCpu = statisticsServiceManager.getAverageCpuTemperature();
            String textView = "Cpu average temperature:\n" + formatter.format(valueAverageCpu);
            ((TextView)findViewById(R.id.textView4)).setText(textView);
       } catch (RemoteException e) {
            Log.e("StatisticsClientApp: ", "Error when trying to access binder!");
            e.printStackTrace();
       }
   }

   private void displayAverageGpuTemperature() {
        try {
            Float valueAverageGpu = statisticsServiceManager.getAverageGpuTemperature();
            String textView = "Gpu average temperature:\n" + formatter.format(valueAverageGpu);
            ((TextView)findViewById(R.id.textView5)).setText(textView);
        } catch (RemoteException e) {
            Log.e("StatisticsClientApp: ", "Error when trying to access binder!");
            e.printStackTrace();
        }
   }

   private void displayAverageAmbientTemperature() {
        try {
            Float valueAverageAmbient = statisticsServiceManager.getAverageAmbientTemperature();
            String textView = "Ambient average temperature:\n" + formatter.format(valueAverageAmbient);
            ((TextView)findViewById(R.id.textView6)).setText(textView);
        } catch (RemoteException e) {
            Log.e("StatisticsClientApp: ", "Error when trying to access binder!");
            e.printStackTrace();
        }
   }

   private void displayMaxCpuTemperature() {
        try {
            Float valueMaxCpu = statisticsServiceManager.getMaxCpuTemperature();
            String textView = "Max cpu temperature:\n" + formatter.format(valueMaxCpu);
            ((TextView)findViewById(R.id.textView7)).setText(textView);
        } catch (RemoteException e) {
            Log.e("StatisticsClientApp: ", "Error when trying to access binder!");
            e.printStackTrace();
        }
   }

   private void displayMaxGpuTemperature() {
        try {
            Float valueMaxGpu = statisticsServiceManager.getMaxGpuTemperature();
            String textView = "Max gpu temperature:\n" + formatter.format(valueMaxGpu);
            ((TextView)findViewById(R.id.textView8)).setText(textView);
        } catch (RemoteException e) {
            Log.e("StatisticsClientApp: ", "Error when trying to access binder!");
            e.printStackTrace();
        }
   }

   private void displayMaxAmbientTemperature() {
        try {
            Float valueMaxAmbient = statisticsServiceManager.getMaxAmbientTemperature();
            String textView = "Max ambient temperature:\n" + formatter.format(valueMaxAmbient);
            ((TextView)findViewById(R.id.textView9)).setText(textView);
        } catch (RemoteException e) {
            Log.e("StatisticsClientApp: ", "Error when trying to access binder!");
            e.printStackTrace();
        }
   }

    private void startTimer(boolean toStart) {
        if (toStart) {
            timer = new Timer();
            timer.schedule(new TimerTask() {
                @Override
                public void run() {
                    runOnUiThread(() -> {
                        displayCpuTemperature();
                        displayGpuTemperature();
                        displayAmbientTemperature();
                        displayAverageCpuTemperature();
                        displayAverageGpuTemperature();
                        displayAverageAmbientTemperature();
                        displayMaxCpuTemperature();
                        displayMaxGpuTemperature();
                        displayMaxAmbientTemperature();
                    });
                }
            }, 0, 1000);
        } else {
            timer.cancel();
            timer.purge();
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.i("StatisticsClientApp: ", "Started in onCreate");
    }

    @Override
    protected void onStart() {
        super.onStart();
    }

    @Override
    protected void onResume() {
        super.onResume();
        startTimer(true);
    }

    @Override
    protected void onPause() {
        super.onPause();
        startTimer(false);
    }

    @Override
    protected void onStop() {
        super.onStop();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }
}