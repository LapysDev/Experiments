/* Import --> del space-shooter.exe & cls && csc /out:space-shooter.exe /t:exe space-shooter.cs && space-shooter.exe & del space-shooter.exe */
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Windows.Input;

/* ... */
namespace Game {
  class Game {
    /* Class */
      /* ... */
      [StructLayout(LayoutKind.Sequential)]
      private struct DEVMODE {
        public static ulong ENUM_CURRENT_SETTINGS  = unchecked((ulong) -1);
        public static ulong ENUM_REGISTRY_SETTINGS = unchecked((ulong) -2);

        // ...
        private const int CCHDEVICENAME = 0x20;
        private const int CCHFORMNAME   = 0x20;

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = CCHDEVICENAME)]
        public string            dmDeviceName;
        public ushort            dmSpecVersion;
        public ushort            dmDriverVersion;
        public ushort            dmSize;
        public ushort            dmDriverExtra;
        public uint              dmFields;
        public uint              dmPositionX;
        public uint              dmPositionY;
        public ScreenOrientation dmDisplayOrientation;
        public uint              dmDisplayFixedOutput;
        public short             dmColor;
        public short             dmDuplex;
        public short             dmYResolution;
        public short             dmTTOption;
        public short             dmCollate;

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = CCHFORMNAME)]
        public string dmFormName;
        public ushort dmLogPixels;
        public uint   dmBitsPerPel;
        public uint   dmPelsWidth;
        public uint   dmPelsHeight;
        public uint   dmDisplayFlags;
        public uint   dmDisplayFrequency;
        public uint   dmICMMethod;
        public uint   dmICMIntent;
        public uint   dmMediaType;
        public uint   dmDitherType;
        public uint   dmReserved1;
        public uint   dmReserved2;
        public uint   dmPanningWidth;
        public uint   dmPanningHeight;
      }

      [StructLayout(LayoutKind.Sequential)]
      private struct MSG {
        public IntPtr Handle;
        public uint   Message;
        public IntPtr WParameter;
        public IntPtr LParameter;
        public uint   Time;
        public Point  Location;
      }

      /* Entity */
      private class Entity {
        private float _rotation;
        private float _size;

        public Point coordinates;
        public uint  health;
        public float rotation { get { return _rotation; } set { _rotation = (value < 0.0f ? (float) (Math.PI * 2.0f) + value : value) % (float) (Math.PI * 2.0f); } }
        public float size     { get { return _size; }     set { _size     = value < 0.0f ? 0.0f : value > 1.0f ? 1.0f : value; } }

        // ...
        public Entity(Point coordinates, float size) {
          this.coordinates = coordinates;
          this.health      = 0u;
          this.rotation    = 0.0f;
          this.size        = size;
        }

        // ...
        public Size getComputedSize(Size size) {
          return new Size((int) (this.size * size.Width), (int) (this.size * size.Height));
        }
      };
        /* Item */
        private class Item : Entity {
          public Item(Point coordinates, float size) : base(coordinates, size) {}
        };
          /* Asteroid */
          private sealed class Asteroid : Item {
            public Asteroid(Point coordinates)             : base(coordinates, 0.0300f) {}
            public Asteroid(Point coordinates, float size) : base(coordinates, size)    {}
          };

          /* Bonus */
          private sealed class Bonus : Item {
            public enum Type : ushort { CLONE, DEFENSE, HEALTH, POWER, RANGE, RECHARGE, SPEED };
            public Bonus(Point coordinates, Type type) : base(coordinates, 0.0300f) {}
          };

        /* Unit */
        private class Unit : Entity {
          public Unit(Point coordinates, float size) : base(coordinates, size) {}
        };
          /* Alien */
          private class Alien : Unit {
            public Alien(Point coordinates) : base(coordinates, 0.0400f) {}
          };

          /* Ship */
          private class Ship : Unit {
            public Ship(Point coordinates, float size) : base(coordinates, size) {}
          };
            /* Artillery */
            private sealed class Artillery : Ship {
              public Artillery(Point coordinates) : base(coordinates, 0.0675f) {}
            };

            /* Drone */
            private sealed class Drone : Ship {
              public Drone(Point coordinates) : base(coordinates, 0.0350f) {}
            };

            /* Infantry */
            private sealed class Infantry : Ship {
              public Infantry(Point coordinates) : base(coordinates, 0.0500f) {}
            };

      /* Star */
      private sealed class Star {
        public static ushort maximumSize = (ushort) 5u;
        public static ushort minimumSize = (ushort) 1u;
        public static Random randomizer  = new Random();

        // ...
        private float _delta;
        private float _speed;

        public float  delta { get { return _delta; } set { _delta = value > 0.0f ? value < 1.0f ? value : 1.0f : 0.0f; } }
        public Point  destinationCoordinates;
        public ushort size;
        public Point  sourceCoordinates;
        public float  speed { get { return _speed; } set { _speed = value > 0.0f ? value < 1.0f ? value : 1.0f : 0.0f; } }

        // ...
        public Star() {
          ushort size = (ushort) randomizer.Next(Star.minimumSize, Star.maximumSize);

          this.delta                  = 0.0f;
          this.destinationCoordinates = new Point(0, 0);
          this.size                   = size;
          this.sourceCoordinates      = new Point(0, 0);
          this.speed                  = 0.0f;
        }
      };

      /* State */
      [Flags]
      private enum State : ushort {
        GAMEPLAY = (ushort) 0x1u,
        MENU     = (ushort) 0x3u,

        PAUSED = (ushort) 0x4u
      };

      /* Window */
      public sealed class Window : Form {
        private FormBorderStyle _borderStyle;
        private Size            _size;
        private FormWindowState _windowState;

        // ...
        public Window() : base() {
          this.DoubleBuffered = true;
          this.SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.DoubleBuffer | ControlStyles.OptimizedDoubleBuffer | ControlStyles.UserPaint, true);
        }

        // ... ->> Prevent implicitly re-painting the background
        protected override void OnPaintBackground(PaintEventArgs arguments) {}

        public void exitFullscreen() {
          this.FormBorderStyle = this._borderStyle;
          this.Size            = this._size;
          this.TopMost         = false;
          this.WindowState     = this._windowState;
        }

        public bool isFullscreen() {
          return FormBorderStyle.None == this.FormBorderStyle && this.TopMost && FormWindowState.Maximized == this.WindowState;
        }

        public void requestFullscreen() {
          this._borderStyle = this.FormBorderStyle;
          this._size        = this.Size;
          this._windowState = this.WindowState;

          this.FormBorderStyle = FormBorderStyle.None;
          this.Size            = Screen.FromControl(window).Bounds.Size;
          this.TopMost         = true;
          this.WindowState     = FormWindowState.Maximized;
        }
      };

    /* Global > ... */
    private static List<Keys> keys                 = null;
    private static TimeSpan?  renderDelta          = null;
    private static ushort     renderIndex          = (ushort) 0u;
    private static Bitmap[]   renders              = {null, null, null};
    private static TimeSpan?  renderTimestamp      = null;
    private static List<Star> stars                = null;
    private static ushort     starsMaximumLength   = (ushort) 0u;
    private static ushort[]   starsSpawnCountDelta = {(ushort) 0u, (ushort) 1u};
    private static TimeSpan?  starsSpawnDelta      = null;
    private static TimeSpan?  starsSpawnTimestamp  = null;
    private static State?     state                = null;
    private static TimeSpan?  updateDelta          = null;
    private static TimeSpan?  updateTimestamp      = null;
    private static Window     window               = null;

    private static Unit[] players = {
      null, // ->> Keyboard   ⌨️
      null, // ->> Mouse      🖱️
      null  // ->> Controller 🎮
    };

    private static Unit player {
      get { return players[0]; }
      set { players[0] = value; }
    }

    /* Function > ... */
    [DllImport("user32.dll")] private static extern bool EnumDisplaySettings(string deviceName, ulong modeIndex, ref DEVMODE deviceMode);
    [DllImport("user32.dll")] private static extern int  PeekMessage        (out MSG message, IntPtr window, uint filterMinimum, uint filterMaximum, uint removedMessages);

    /* ... */
    public static void Input(Keys? releasedKey) {
      switch (releasedKey) {
        case Keys.Escape: Terminate(); break;
        case Keys.F11   : if (window.isFullscreen()) window.exitFullscreen(); else window.requestFullscreen(); break;
      }

      foreach (Keys key in keys)
      switch (key) {
        case Keys.Down : case Keys.S: break;
        case Keys.Left : case Keys.A: player.rotation -= (float) Math.PI / 180.0f; Console.WriteLine("[^]: " + (player.rotation * (180.0f / Math.PI))); break;
        case Keys.Right: case Keys.D: player.rotation += (float) Math.PI / 180.0f; Console.WriteLine("[^]: " + (player.rotation * (180.0f / Math.PI))); break;
        case Keys.Up   : case Keys.W: break;
      }
    }

    public static void Terminate() {
      window.Close();

      // ...
      if (Application.MessageLoop) Application.Exit();
      else Environment.Exit(0x00);
    }

    public static void Render(object target, PaintEventArgs arguments) {
      Bitmap   render         = renders[renderIndex];
      TimeSpan timestamp      = TimeSpan.FromTicks(DateTime.Now.Ticks);
      Window   window         = (Window) target; // ->> Same as `Game::window`… ideally
      Graphics windowGraphics = arguments.Graphics;
      Size     windowSize     = window.Size;
      PointF   windowOrigin   = new PointF(windowSize.Width * 0.5f, windowSize.Height * 0.5f);

      // ...
      windowGraphics.Clear(window.BackColor);
      windowGraphics.Clear(Color.DarkBlue);

      if (renderDelta > timestamp - renderTimestamp)
        // ->> Preserve prior render
        windowGraphics.DrawImage(renders[(renderIndex == 0 ? renders.Length : renderIndex) - 1], 0, 0);

      else {
        Graphics graphics    = Graphics.FromImage(render);
        ushort   playerCount = ((Func<uint, ushort>) (value => { foreach (Unit player in players) value += null != player ? 1u : 0u; return (ushort) (0u == value ? 1u : value); }))(0u);
        float    rotation    = ((Func<float, float>) (value => { foreach (Unit player in players) value += null != player ? player.rotation : 0.0f; return value; }))(0.0f) / playerCount;

        // ...
        graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
        renderTimestamp        = timestamp;

        // ... ->> Draw stars
        graphics.Clear(window.BackColor);

        graphics.DrawLine(Pens.Red, new PointF(windowSize.Width * 0.5f, windowSize.Height * 0.5f), new PointF(windowSize.Width * 0.0f, windowSize.Height * 0.5f));
        graphics.DrawLine(Pens.Red, new PointF(windowSize.Width * 0.5f, windowSize.Height * 0.5f), new PointF(windowSize.Width * 0.5f, windowSize.Height * 0.0f));
        graphics.DrawLine(Pens.Red, new PointF(windowSize.Width * 0.5f, windowSize.Height * 0.5f), new PointF(windowSize.Width * 0.5f, windowSize.Height * 1.0f));
        graphics.DrawLine(Pens.Red, new PointF(windowSize.Width * 0.5f, windowSize.Height * 0.5f), new PointF(windowSize.Width * 1.0f, windowSize.Height * 0.5f));

        foreach (Star star in stars) {
          PointF destinationCoordinates = new PointF(star.destinationCoordinates.X, star.destinationCoordinates.Y);
          float  rotationCosine         = (float) Math.Cos(rotation);
          float  rotationCull           = 0.0f;
          float  rotationSine           = (float) Math.Sin(rotation);
          PointF sourceCoordinates      = new PointF(star.sourceCoordinates.X, star.sourceCoordinates.Y);

          // ... --- TODO (Lapys) -> Improve rotation culling
          do {
            if (rotation >= Math.PI * 0.0f && rotation <= Math.PI * 0.5f) { rotationCull = (float) ((Math.PI * 0.0f) + (Math.PI / 4.0f)) - rotation; break; }
            if (rotation >= Math.PI * 0.5f && rotation <= Math.PI * 1.0f) { rotationCull = (float) ((Math.PI * 0.5f) + (Math.PI / 4.0f)) - rotation; break; }
            if (rotation >= Math.PI * 1.0f && rotation <= Math.PI * 1.5f) { rotationCull = (float) ((Math.PI * 1.0f) + (Math.PI / 4.0f)) - rotation; break; }
            if (rotation >= Math.PI * 1.5f && rotation <= Math.PI * 2.0f) { rotationCull = (float) ((Math.PI * 1.5f) + (Math.PI / 4.0f)) - rotation; break; }
          } while (false);

          rotationCull  = 1.0f - (Math.Abs(rotationCull) / (float) (Math.PI / 4.0f));            // ->> Scale based on rotation (45° angles are the most scaled)
          rotationCull  = (rotationCull * 0.5f) * Math.Max(windowSize.Height, windowSize.Width); // ->> Convert to in-world coordinates

          destinationCoordinates.Y += rotationCull;
          destinationCoordinates    = new PointF(
            windowOrigin.X + (rotationCosine * (destinationCoordinates.X - windowOrigin.X)) - (rotationSine   * (destinationCoordinates.Y - windowOrigin.Y)),
            windowOrigin.Y + (rotationSine   * (destinationCoordinates.X - windowOrigin.X)) + (rotationCosine * (destinationCoordinates.Y - windowOrigin.Y))
          );

          sourceCoordinates.Y -= rotationCull;
          sourceCoordinates    = new PointF(
            windowOrigin.X + (rotationCosine * (sourceCoordinates.X - windowOrigin.X)) - (rotationSine   * (sourceCoordinates.Y - windowOrigin.Y)),
            windowOrigin.Y + (rotationSine   * (sourceCoordinates.X - windowOrigin.X)) + (rotationCosine * (sourceCoordinates.Y - windowOrigin.Y))
          );

          // ...
          graphics.FillEllipse(new SolidBrush(Color.White), new RectangleF(
            sourceCoordinates.X + (star.delta * (destinationCoordinates.X - sourceCoordinates.X)),
            sourceCoordinates.Y + (star.delta * (destinationCoordinates.Y - sourceCoordinates.Y)),
            star.size,
            star.size
          ));
        }

        // ...
        renderIndex = (ushort) ((renderIndex + 1u) % renders.Length);

        graphics.Dispose();
        windowGraphics.DrawImage(render, 0, 0);
      }
    }

    public static void Update(object target, bool idle) {
      MSG      message;
      ushort   playerCount = ((Func<uint, ushort>) (value => { foreach (Unit player in players) value += null != player ? 1u : 0u; return (ushort) (0u == value ? 1u : value); }))(0u);
      float    rotation    = ((Func<float, float>) (value => { foreach (Unit player in players) value += null != player ? player.rotation : 0.0f; return value; }))(0.0f) / playerCount;
      int      starsLength = stars.Count;
      TimeSpan timestamp   = TimeSpan.FromTicks(DateTime.Now.Ticks);
      Size     windowSize  = window.Size;

      /* ... ->> Game logic unbounded by framerate ie: calculations, flags, … */ {
        // [Stars] ... ->> Remove fallen stars
        for (int index = starsLength; 0 != index--; )
        if (stars[index].delta >= 1.0f) {
          stars.Remove(stars[index]);
          --starsLength;

          continue;
        }
      }

      /* ... ->> Game logic unbounded by `Update(…)` framerate ie: calculations, flags, … */ {
        // [Stars] ... ->> Spawn falling stars
        if (starsSpawnDelta < timestamp - starsSpawnTimestamp)
        if (starsLength != starsMaximumLength) {
          ushort starsSpawnCount = (ushort) Star.randomizer.Next(starsSpawnCountDelta[0], starsSpawnCountDelta[1]);

          // ...
          starsSpawnCount     = (ushort) (starsLength + starsSpawnCount > starsMaximumLength ? starsMaximumLength - starsLength : starsSpawnCount);
          starsSpawnTimestamp = timestamp;

          while (0 != starsSpawnCount--) {
            Star star = new Star();

            // ...
            star.destinationCoordinates.X = Star.randomizer.Next(0, windowSize.Width);
            star.destinationCoordinates.Y = windowSize.Height;
            star.sourceCoordinates.X      = star.destinationCoordinates.X;
            star.sourceCoordinates.Y      = 0;
            star.speed                    = (float) Star.randomizer.NextDouble() * 0.00025f;
            star.speed                    = star.speed > 0.000025f ? star.speed < 0.00020f ? star.speed : 0.00020f : 0.000025f;

            stars.Add(star);
          }
        }
      }

      /* Update ->> Game logic bounded by `Update(…)` framerate ie: animations, transitions, … */
      if (updateDelta < timestamp - updateTimestamp) {
        // [Stars] ... ->> Fell stars
        foreach (Star star in stars)
        star.delta += star.speed;
      }

      /* Render ->> Game render bounded by `Render(…)` */
      if (PeekMessage(out message, IntPtr.Zero, 0u, 0u, 0u) == 0)
      window.Invalidate(false);
    }

    /* Main */
    static void Main(String[] commandLineArguments) {
      DEVMODE deviceMode       = new DEVMODE();
      uint    deviceFramerate  = 60u;
      Timer   updateTimer      = null;
      Screen  windowScreen     = null;
      Int32   windowSize       = 0;

      /* Update > ... */
      if (EnumDisplaySettings(null, DEVMODE.ENUM_CURRENT_SETTINGS, ref deviceMode))
      deviceFramerate = (uint) deviceMode.dmDisplayFrequency;

      keys                    = new List<Keys>();
      player                  = new Infantry(new Point(0, 0));
      renderDelta             = TimeSpan.FromTicks((long) (TimeSpan.TicksPerSecond / deviceFramerate));
      renderTimestamp         = TimeSpan.FromTicks(DateTime.Now.Ticks);
      stars                   = new List<Star>();
      starsMaximumLength      = (ushort) 25u;
      starsSpawnCountDelta[0] = (ushort) 1u;
      starsSpawnCountDelta[1] = (ushort) 5u;
      starsSpawnDelta         = TimeSpan.FromTicks((long) (TimeSpan.TicksPerMillisecond * 600uL));
      starsSpawnTimestamp     = TimeSpan.FromTicks(DateTime.Now.Ticks);
      state                   = State.MENU;
      updateDelta             = TimeSpan.FromTicks((long) (TimeSpan.TicksPerSecond / deviceFramerate));
      updateTimer             = new Timer();
      updateTimestamp         = TimeSpan.FromTicks(DateTime.Now.Ticks);
      window                  = new Window();
      windowScreen            = Screen.FromControl(window);
      windowSize              = (Int32) (Math.Min(Screen.FromControl(window).WorkingArea.Height, windowScreen.WorkingArea.Width) * 0.8f);

      for (int index = renders.Length; 0 != index; )
      renders[--index] = new Bitmap(windowScreen.Bounds.Width, windowScreen.Bounds.Height);

      /* Modification > ... */
      Application.Idle += new EventHandler(delegate(object target, EventArgs arguments) { Update(target, true); });

      updateTimer.Enabled  = true;
      updateTimer.Interval = (int) updateDelta.Value.TotalMilliseconds;
      updateTimer.Tick    += new EventHandler(delegate(object target, EventArgs arguments) { Update(target, false); });

      window.BackColor       = Color.Black;
      window.FormBorderStyle = FormBorderStyle.FixedSingle;
      window.Icon            = new Icon("favicon.ico");
      window.MaximizeBox     = false;
      window.MinimizeBox     = false;
      window.KeyDown        += new KeyEventHandler(delegate(object target, KeyEventArgs arguments) { if (false == keys.Contains(arguments.KeyCode)) keys.Add(arguments.KeyCode); Input(null);                          });
      window.KeyUp          += new KeyEventHandler(delegate(object target, KeyEventArgs arguments) { int index = keys.IndexOf(arguments.KeyCode); if (index != -1) { keys.RemoveAt(index); Input(arguments.KeyCode); } });
      window.Paint          += new PaintEventHandler(Render);
      window.Size            = new Size(windowSize, windowSize);
      window.StartPosition   = FormStartPosition.CenterScreen;
      window.Text            = "Space Shooter";

      /* ... */
      if (DialogResult.OK != window.ShowDialog())
      Terminate();
    }
  }
}
