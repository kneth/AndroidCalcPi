package net.zigzak.androidcalcpi;

public class Pi {
    private long iterations;
    private RNG rng;

    Pi(long iterations) {
        if (iterations < 1) {
            throw new IllegalArgumentException("Number of iterations must be larger than 0");
        }

        this.iterations = iterations;
        rng = new RNG(1);
    }

    double estimate() {
        long nHits = 0;
        for (int i = 0; i < iterations; i++) {
            double x = rng.uniform();
            double y = rng.uniform();
            if (x*x+y*y < 1.0) { // square root not really needed!
                nHits++;
            }
        }
        return 4.0*(double)nHits/(double)iterations;
    }
}
