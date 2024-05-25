public class Program {
  private class A {
     public virtual void function() { System.Console.WriteLine("[A]"); }
  };

  private class B : A {
    public new void function() { System.Console.WriteLine("[B]"); }
  };

  private class C : A {
    public override void function() { System.Console.WriteLine("[A]"); }
  };

  /* Main */
  static void Main(System.String[] arguments) {
    A a = new B();

    // ...
    a.function();

    for (System.Type type = a.GetType(); null != type; type = type.BaseType) {
      foreach (System.Reflection.MethodInfo methodInformation in type.GetMethods())
      if (
        // ->> Look for `MethodInfo` resembling `A.function`
        false                                    == methodInformation.IsConstructor   &&
        false                                    == methodInformation.IsGenericMethod &&
        false                                    != methodInformation.IsPublic        &&
        false                                    == methodInformation.IsStatic        &&
        methodInformation.Name                   == nameof(A.function)                &&
        methodInformation.ReturnType             == typeof(void)                      && // ->> May be acquired through the `MethodInfo` of `A.function` specifically
        methodInformation.GetParameters().Length == 0u                                   // ->> May be acquired through the `MethodInfo` of `A.function` specifically
      ) {
        // --> a.function();
        methodInformation.Invoke(a, null as object[]);
        return;
      }
    }
  }
}
