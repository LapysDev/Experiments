#nullable enable annotations

public class Program {
  public struct A {
    public int? _;
  };

  /* Main */
  static void Main(System.String[] arguments) {
    A     a = new();
    int?  b = null;
    int   c = 69;
    int[] d = {42};

    // ...
    a._ = 42;
    b ??= 42;
    c   = 42;

    // ...
    foreach (System.Reflection.MemberInfo _ in a.GetType().GetMembers())
    if (System.Reflection.MemberTypes.Field == _.MemberType && _.Name == nameof(A._)) {
      System.Object? value = (_ as System.Reflection.FieldInfo).GetValue(a);

      System.Console.WriteLine($"[A]: {value as int?} {null == value?.GetType() || value?.GetType() == typeof(int?)}");
      break;
    }

    System.Console.WriteLine($"[B]: {b}");
    System.Console.WriteLine($"[C]: {c}");
    System.Console.WriteLine($"[D]: {(0 != d.Length ? d[0] : null)}");
  }
}
