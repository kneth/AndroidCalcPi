package net.zigzak.androidcalcpi;

import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;

public class MainActivity extends ActionBarActivity implements AdapterView.OnItemSelectedListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Loading the native code should probably be placed
        // in a separate utility class.
        System.loadLibrary("calcPi"); // "calcPi" is the Gradle module name

        Spinner dropdown = (Spinner)findViewById(R.id.spinner1);
        String[] items = new String[]{"Java", "C++", "Mixture", "Posix Thread"};
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(MainActivity.this, android.R.layout.simple_spinner_item, items);
        dropdown.setAdapter(adapter);
        dropdown.setOnItemSelectedListener(this);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
        EditText editTextIterations = (EditText)findViewById(R.id.editText);
        final long iterations = Long.parseLong(editTextIterations.getText().toString());

        final double[] result = {0.0};
        switch (position) {
            case 0: { // Java
                Measurement measurement = new Measurement() {
                    @Override
                    public void run() {
                        Pi pi = new Pi(iterations);
                        result[0] = pi.estimate();
                    }
                };
                measurement.execute("Java");
                break;
            }
            case 1: { // C++
                Measurement measurement = new Measurement() {
                    @Override
                    public void run() {
                        NativePi nativePi = new NativePi(iterations, 1);
                        result[0] = nativePi.estimate();
                    }
                };
                measurement.execute("C++");
                break;
            }
            case 2: { // Java/C++
                Measurement measurement = new Measurement() {
                    @Override
                    public void run() {
                        SemiNativePi semiNativePi = new SemiNativePi(iterations);
                        result[0] = semiNativePi.estimate();
                    }
                };
                measurement.execute("Java/C++");
                }
                break;
            case 3: { // Threaded C++
                Measurement measurement = new Measurement() {
                    @Override
                    public void run() {
                        long numberOfThreads = 2;
                        NativePi nativePi1 = new NativePi(iterations / numberOfThreads, numberOfThreads);
                        result[0] = nativePi1.estimate(numberOfThreads);
                    }
                };
                measurement.execute("Threaded C++");
            }
            break;
        }

        TextView textViewResults = (TextView)findViewById(R.id.textView);
        textViewResults.setText(String.format("%1.8f", result[0]));

        TextView textViewEncrypted = (TextView)findViewById(R.id.encrypted);
        String encrypted = NativeEncrypt.encrypt(String.format("%1.8f", result[0]));
        textViewEncrypted.setText(encrypted);
    }

    @Override
    public void onNothingSelected(AdapterView<?> parent) {
    }
}
