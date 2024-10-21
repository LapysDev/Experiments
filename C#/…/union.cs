public class Program {
  [System.Runtime.InteropServices.StructLayout(System.Runtime.InteropServices.LayoutKind.Explicit)]
  public struct union {
    [System.Runtime.InteropServices.FieldOffset(0)] public float a;
    [System.Runtime.InteropServices.FieldOffset(4)] public int   b1;
    [System.Runtime.InteropServices.FieldOffset(4)] public float b2;
  };

  /* Main */
  static void Main(System.String[] arguments) {
    union variant = new();

    // ...
    variant.a  = 4.20f;

    variant.b2 = 13.37f;
    System.Console.WriteLine($"");
    System.Console.WriteLine($"{{float a: {variant.a}, int   b: {variant.b1}}}");
    System.Console.WriteLine($"{{float a: {variant.a}, float b: {variant.b2}}}");

    variant.b1 = 69;
    System.Console.WriteLine($"");
    System.Console.WriteLine($"{{float a: {variant.a}, int   b: {variant.b1}}}");
    System.Console.WriteLine($"{{float a: {variant.a}, float b: {variant.b2}}}");
  }
}
