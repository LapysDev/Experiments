static void DrawBounds(Bounds bounds, Color color, float delay = 0.0f) {
  Vector3 p1 = new Vector3(bounds.min.x, bounds.min.y, bounds.min.z);
  Vector3 p2 = new Vector3(bounds.max.x, bounds.min.y, bounds.min.z);
  Vector3 p3 = new Vector3(bounds.max.x, bounds.min.y, bounds.max.z);
  Vector3 p4 = new Vector3(bounds.min.x, bounds.min.y, bounds.max.z);
  Vector3 p5 = new Vector3(bounds.min.x, bounds.max.y, bounds.min.z);
  Vector3 p6 = new Vector3(bounds.max.x, bounds.max.y, bounds.min.z);
  Vector3 p7 = new Vector3(bounds.max.x, bounds.max.y, bounds.max.z);
  Vector3 p8 = new Vector3(bounds.min.x, bounds.max.y, bounds.max.z);

  Debug.DrawLine(p1, p2, color, delay);
  Debug.DrawLine(p1, p5, color, delay);
  Debug.DrawLine(p2, p3, color, delay);
  Debug.DrawLine(p2, p6, color, delay);
  Debug.DrawLine(p3, p4, color, delay);
  Debug.DrawLine(p3, p7, color, delay);
  Debug.DrawLine(p4, p1, color, delay);
  Debug.DrawLine(p4, p8, color, delay);
  Debug.DrawLine(p5, p6, color, delay);
  Debug.DrawLine(p6, p7, color, delay);
  Debug.DrawLine(p7, p8, color, delay);
  Debug.DrawLine(p8, p5, color, delay);
}
