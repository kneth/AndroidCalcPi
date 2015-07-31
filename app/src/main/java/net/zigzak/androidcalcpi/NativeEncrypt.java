package net.zigzak.androidcalcpi;

public class NativeEncrypt {

    public static String encrypt(String message) {
        return nativeEncrypt(message);
    }

    private static native String nativeEncrypt(String message);
}