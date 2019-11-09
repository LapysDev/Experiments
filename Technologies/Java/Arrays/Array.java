/* ... */
public class Array {
    // Method > To String --- MINIFY (Lapys)
    private static String toString(int[] array) { String message = ""; message += "["; for (int iterator = 0, length = array.length; iterator != length; iterator += 1) message += array[iterator] + (length - iterator == 1 ? "" : ", "); message += "]"; return message; }

    /* Main */
    public static void main(String[] arguments) {
        // Initialization > Array
        int[] array;

        // ...
        array = new int[5];
        array[0] = 1; array[1] = 2; array[2] = 3; array[3] = 4; array[4] = 5;
        System.out.println("[ARRAY]: " + toString(array));

        // ...
        array = new int[10];
        System.out.println("[ARRAY]: " + toString(array));
    }
}
