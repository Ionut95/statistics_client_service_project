package statistics.client.statisticsclientapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import statistics.service.statisticsservicemanager.StatisticsServiceManager;
import android.os.RemoteException;
import android.util.Log;
import android.widget.TextView;

import java.util.Timer;
import java.util.TimerTask;

public class MainActivity extends AppCompatActivity {

    private StatisticsServiceManager  stservmanager = StatisticsServiceManager.getInstance();
    private Timer timer;

   private void displayCpuTemperature() {
        try {
            Float valueCpu = stservmanager.getCpuTemperature();
            String textView = "Cpu temperature:\n" + valueCpu;
            ((TextView)findViewById(R.id.textView1)).setText(textView);
        } catch (RemoteException e) {
            Log.e("Error: ", "in Client displayCpuTemperature - not reading value");
        }
   }

   private void displayGpuTemperature() {
        try {
            Float valueGpu = stservmanager.getGpuTemperature();
            String textView = "Gpu temperature:\n" + valueGpu;
            ((TextView)findViewById(R.id.textView2)).setText(textView);
        } catch (RemoteException e) {

        }
   }

   private void displayAmbientTemperature() {
        try {
            Float valueAmbient = stservmanager.getAmbientTemperature();
            String textView = "Ambient temperature:\n" + valueAmbient;
            ((TextView)findViewById(R.id.textView3)).setText(textView);
        } catch (RemoteException e) {

        }
   }

   private void displayAverageCpuTemperature() {
        try {
            Float valueAverageCpu = stservmanager.getAverageCpuTemperature();
            String textView = "Cpu average temperature:\n" + valueAverageCpu;
            ((TextView)findViewById(R.id.textView4)).setText(textView);
       } catch (RemoteException e) {

       }
   }

   private void displayAverageGpuTemperature() {
        try {
            Float valueAverageGpu = stservmanager.getAverageGpuTemperature();
            String textView = "Gpu average temperature:\n" + valueAverageGpu;
            ((TextView)findViewById(R.id.textView5)).setText(textView);
        } catch (RemoteException e) {

        }
   }

   private void displayAverageAmbientTemperature() {
        try {
            Float valueAverageAmbient = stservmanager.getAverageAmbientTemperature();
            String textView = "Ambient average temperature:\n" + valueAverageAmbient;
            ((TextView)findViewById(R.id.textView6)).setText(textView);
        } catch (RemoteException e) {

        }
   }

   private void displayMaxCpuTemperature() {
        try {
            Float valueMaxCpu = stservmanager.getMaxCpuTemperature();
            String textView = "Max cpu temperature:\n" + valueMaxCpu;
            ((TextView)findViewById(R.id.textView7)).setText(textView);
        } catch (RemoteException e) {

        }
   }

   private void displayMaxGpuTemperature() {
        try {
            Float valueMaxGpu = stservmanager.getMaxGpuTemperature();
            String textView = "Max gpu temperature:\n" + valueMaxGpu;
            ((TextView)findViewById(R.id.textView8)).setText(textView);
        } catch (RemoteException e) {

        }
   }

   private void displayMaxAmbientTemperature() {
        try {
            Float valueMaxAmbient = stservmanager.getMaxAmbientTemperature();
            String textView = "Max ambient temperature:\n" + valueMaxAmbient;
            ((TextView)findViewById(R.id.textView9)).setText(textView);
        } catch (RemoteException e) {

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