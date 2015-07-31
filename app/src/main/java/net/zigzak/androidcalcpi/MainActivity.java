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
        long iterations = Long.parseLong(editTextIterations.getText().toString());

        double result = 0.0;
        switch (position) {
            case 0: // Java
                Pi pi = new Pi(iterations);
                result =  pi.estimate();
                break;
            case 1: // C++
                NativePi nativePi = new NativePi(iterations, 1);
                result = nativePi.estimate();
                break;
            case 2: // Java/C++
                SemiNativePi semiNativePi = new SemiNativePi(iterations);
                result = semiNativePi.estimate();
                break;
            case 3: // Threaded C++
                long numberOfThreads = 2;
                NativePi nativePi1 = new NativePi(iterations / numberOfThreads, numberOfThreads);
                result = nativePi1.estimate(numberOfThreads);
                break;
        }

        TextView textViewResults = (TextView)findViewById(R.id.textView);
        textViewResults.setText(String.format("%1.8f", result));
    }

    @Override
    public void onNothingSelected(AdapterView<?> parent) {
    }
}
