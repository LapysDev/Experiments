#nullable enable annotations

/* … */
public class Program {
  private const System.Collections.Generic.Dictionary<System.Type, System.Type[]> IMPLICIT_TYPE_CONVERSIONS = new() {
    {typeof(double), new[] {typeof(byte), typeof(char), typeof(float), typeof(int),   typeof(long),  typeof(sbyte), typeof(short), typeof(uint), typeof(ulong), typeof(ushort)}},
    {typeof(float),  new[] {typeof(byte), typeof(char), typeof(int),   typeof(long),  typeof(sbyte), typeof(short), typeof(uint), typeof(ulong), typeof(ushort)}},
    {typeof(int),    new[] {typeof(byte), typeof(char), typeof(sbyte), typeof(short), typeof(ushort)}},
    {typeof(long),   new[] {typeof(byte), typeof(char), typeof(int),   typeof(sbyte), typeof(short), typeof(uint), typeof(ushort)}},
    {typeof(short),  new[] {typeof(byte), typeof(sbyte)}},
    {typeof(uint),   new[] {typeof(byte), typeof(char), typeof(ushort)}},
    {typeof(ulong),  new[] {typeof(byte), typeof(char), typeof(uint), typeof(ushort)}},
    {typeof(ushort), new[] {typeof(byte), typeof(char)}}
  };

  /* … */
  // … ->> Sequence all reflected `T` members of `structure` into a `T?` array
  public static T?[] ArrayFromMembers<T>(object structure) where T : class? {
    if (null == structure)
    return null as T?[];

    return System.Array.ConvertAll(structure.GetType().GetMembers(), member => {
      System.Object? valued = member.MemberType switch {
        System.Reflection.MemberTypes.Field    => new System.Func<System.Object?>(() => (member as System.Reflection.FieldInfo)   .GetValue(structure))(),
        System.Reflection.MemberTypes.Property => new System.Func<System.Object?>(() => (member as System.Reflection.PropertyInfo).GetValue(structure))(),
        _                                      => null
      };
      System.Type? valuedType = valued?.GetType();

      // …
      if (valuedType == typeof(T))
      return new T?[] {valued as T};

      // …
      for (System.Collections.Generic.List<System.Type> types = new() {
        typeof(T[]),
        typeof(T?[])
      }; 0 != types.Count; types.RemoveAt(0)) {
        System.Type type = types[0];

        // …
        if (
          type == valuedType                ||
          type.IsAssignableFrom(valuedType) ||
          System.Array.Exists(new[] {type, valuedType}, type => System.Array.Exists(
            type.GetMethods(System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.Static), method => {
              var parameter = new System.Func<System.Reflection.ParameterInfo[], System.Reflection.ParameterInfo?>(parameters => 0 != parameters.Length ? parameters[0] : null)(method.GetParameters());
              return method.Name == "op_Implicit"
                && (method    .ReturnType    == type       || Program.IsImplicitConvertibleType(valuedType, type))
                && (parameter?.ParameterType == valuedType || Program.IsImplicitConvertibleType(valuedType, parameter?.ParameterType));
            })
          )
        ) {
          if (type == typeof(T[])) {
            T?[] array = new T?[(valued as T[]).Length];

            (valued as T[]).CopyTo(array, 0);
            return array;
          }

          else if (type == typeof(T?[]))
            return valued as T?[];

          else if (type == typeof(byte)) {
            (valuedType == double) => byte
            System.Convert.ChangeType(valued as byte, typeof(T?[]));
            typeof(byte), typeof(char), typeof(double), typeof(float), typeof(int), typeof(long), typeof(sbyte), typeof(short), typeof(uint), typeof(ulong), typeof(ushort)

            // TODO
          }

          else {
            typeof(System.IConvertible).IsAssignableFrom(valued)
            ? System.Convert.ChangeType(valued, type) as T?[]
            : null;

            // TODO
          }
        }

        break; // NO, REALLY.. YOU DON'T NEED TO TEST FOR IMPLICITS

        if (IMPLICIT_TYPE_CONVERSIONS.TryGetValue(type, out System.Type[] implicitTypes))
        if (System.Array.IndexOf(implicitTypes, valuedType) != implicitTypes.GetLowerBound(0) - 1) {
          foreach (System.Type implicitType in implicitTypes) {
            if (!types.Contains(implicitType))
            types.Add(implicitType);
          }
        }

        foreach (var GetUnderlyingType in new System.Func<System.Type, System.Type>?[] {
          type.IsEnum ? System.Enum    .GetUnderlyingType : null,
          true        ? System.Nullable.GetUnderlyingType : null
        }) {
          System.Type underlyingType = null != GetUnderlyingType ? GetUnderlyingType(type) : null;

          if (!types.Contains(underlyingType))
          types.Add(underlyingType);
        }
      }

      return null as T?[];
    });
  }

  // …
  private static bool IsConvertibleType(System.Type typeA, System.Type typeB) {
    if (typeA == typeB) {}
  }

  // …
  private static bool IsImplicitConvertibleType(System.Type typeA, System.Type typeB) {
    return
      IMPLICIT_TYPE_CONVERSIONS.TryGetValue(typeB, out System.Type[] implicitTypes)
      ? System.Array.IndexOf(implicitTypes, typeA) != implicitTypes.GetLowerBound(0) - 1
      : false;
  }

  /* Main */
  static void Main(System.String[] arguments) {
  }
}
