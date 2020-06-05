/* Import */
import java.io.*; // Java > Input-Output
import java.util.Scanner; // Java > Utilities > Scanner

/* ... */
class ArithmeticAverage {
    /* Main */
    public static void main(String[] arguments) {
        // : Constant > Scanner
        // : Initialization > Number (A, B)
        Scanner SCANNER = new Scanner(System.in);
        float numberA, numberB;

        // ...
        System.out.print("First Number: "); numberA = SCANNER.nextFloat();
        System.out.print("Second Number: "); numberB = SCANNER.nextFloat();

        System.out.println();
        System.out.print("Average: " + ((numberA + numberB) / 2.00));

        // Scanner > Close
        SCANNER.close();
    }
}
