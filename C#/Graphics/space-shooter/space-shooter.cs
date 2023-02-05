/* Import --> del space-shooter.exe & cls && csc /out:space-shooter.exe /r:System.Collections.dll /r:System.Drawing.Common.dll /r:System.Drawing.Primitives.dll /r:System.Runtime.dll /r:System.Threading.Thread.dll /r:System.Windows.Forms.dll /t:exe space-shooter.cs && space-shooter.exe & del space-shooter.exe */
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;
using System.Windows.Input;

using Timer = System.Windows.Forms.Timer;

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

      /* Entity */
      private class Entity {
        private float rotation;
        private float size;

        public Point Coordinates;
        public uint  Health;
        public float Rotation { get { return rotation; } set { rotation = (value < 0.0f ? (float) (Math.PI * 2.0f) + value : value) % (float) (Math.PI * 2.0f); } }
        public float Size     { get { return size;     } set { size     = (value < 0.0f ? 0.0f : value > 1.0f ? 1.0f : value);                                  } }

        // ...
        public Entity(Point coordinates, float size) {
          this.Coordinates = coordinates;
          this.Health      = 0u;
          this.Rotation    = 0.0f;
          this.Size        = size;
        }

        // ...
        public Size GetComputedSize(Size size) {
          return new Size((int) (this.Size * size.Width), (int) (this.Size * size.Height));
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
        public sealed class StarCoordinates {
          private PointF coordinates;
          public float   X { get { return coordinates.X; } set { coordinates.X = value > 0.0f ? value < 1.0f ? value : 1.0f : 0.0f; } }
          public float   Y { get { return coordinates.Y; } set { coordinates.Y = value > 0.0f ? value < 1.0f ? value : 1.0f : 0.0f; } }

          // ...
          public StarCoordinates(float x, float y) {
            this.coordinates = new PointF(0.0f, 0.0f);
            this.X           = x;
            this.Y           = y;
          }
        };

        // ...
        public static ushort MaximumSize = (ushort) 5u;
        public static ushort MinimumSize = (ushort) 1u;
        public static Random Randomizer  = new Random();

        // ...
        private float delta;
        private byte  opacity;
        private float speed;

        public StarCoordinates DestinationCoordinates;
        public ushort          Size;
        public StarCoordinates SourceCoordinates;
        public float           Delta   { get { return delta;   } set { delta   = value > 0.0f ? value < 1.0f ? value : 1.0f : 0.0f; } }
        public byte            Opacity { get { return opacity; } set { opacity = (byte) (value % 256u);                             } }
        public float           Speed   { get { return speed;   } set { speed   = value > 0.0f ? value < 1.0f ? value : 1.0f : 0.0f; } }

        // ...
        public Star() {
          ushort size = (ushort) Randomizer.Next(Star.MinimumSize, Star.MaximumSize);

          // ...
          this.Delta                  = 0.0f;
          this.DestinationCoordinates = new StarCoordinates(0.0f, 0.0f);
          this.Opacity                = (byte) 255u;
          this.Size                   = size;
          this.SourceCoordinates      = new StarCoordinates(0.0f, 0.0f);
          this.Speed                  = 0.0f;
        }

        // ...
        public Point GetComputedDestinationCoordinates(Size size) {
          return new Point((int) (this.DestinationCoordinates.X * size.Width), (int) (this.DestinationCoordinates.Y * size.Height));
        }

        public Point GetComputedSourceCoordinates(Size size) {
          return new Point((int) (this.SourceCoordinates.X * size.Width), (int) (this.SourceCoordinates.Y * size.Height));
        }

        public Size GetComputedSize() {
          return new Size(this.Size, this.Size);
        }
      };

      /* State */
      [Flags]
      private enum State : byte {
        GAMEPLAY = (byte) 0x1u,
        MENU     = (byte) 0x3u,

        PAUSED = (byte) 0x4u
      };

      /* Window */
      public sealed class Window : Form {
        public Window() : base() {
          this.DoubleBuffered = true;
          this.SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.DoubleBuffer | ControlStyles.OptimizedDoubleBuffer | ControlStyles.UserPaint, true);
        }

        // ...
        public Size GetComputedSize() {
          if (IsFullscreen()) {
            Rectangle windowScreenBounds = Screen.FromControl(window).Bounds;
            Int32     windowSize         = Math.Min(windowScreenBounds.Height, windowScreenBounds.Width);

            // ...
            return new Size(windowSize, windowSize);
          }

          return this.Size;
        }

        protected override void OnPaintBackground(PaintEventArgs arguments) {
          /* Do nothing... ->> Prevent implicitly re-painting the background */
        }
      };

    /* Global > ... */
    private static List<Keys>      keys                                          = null;                       // ->> Keys ⌨️ currently activated
    private static TimeSpan?       renderDelta                                   = null;                       // ->> Time between each `Render(…)`
    private static byte            renderIndex                                   = (byte) 0u;                  // ->> Buffer currently used in multiple-buffering
    private static Thread          renderPostProcessor                           = null;                       // ->> Background processor to handle strenuous synchronous image effects processing & filtering
    private static Bitmap          renderPostProcessorFullscreenRender           = null;                       // ->> Fullscreen graphic
    private static GCHandle        renderPostProcessorFullscreenRenderAllocation = GCHandle.Alloc(0x00u);      // ->> Fullscreen graphic allocated render data
    private static Pen             renderPostProcessorFullscreenRenderBorderPen  = null;                       // ->> Fullscreen graphic border
    private static byte[]          renderPostProcessorFullscreenRenderData       = null;                       // ->> Fullscreen graphic render data
    private static Bitmap[]        renders                                       = {null, null, null};         // ->> Multiple Buffering rendering for gameplay graphics
    private static TimeSpan?       renderTimestamp                               = null;                       // ->> Time till next `Render(…)`
    private static List<Star>      stars                                         = null;                       // ->> Stars trailing in the background
    private static ushort          starsMaximumLength                            = (ushort) 0u;                // ->> Stars total
    private static ushort[]        starsSpawnCountDelta                          = {(ushort) 0u, (ushort) 1u}; // ->> Stars spawned at a time
    private static TimeSpan?       starsSpawnDelta                               = null;                       // ->> Time between each star spawn
    private static TimeSpan?       starsSpawnTimestamp                           = null;                       // ->> Time till next star spawn
    private static State   ?       state                                         = null;                       // ->> Game state for menus, options, etc…
    private static bool            terminated                                    = false;                      // ->> Game state for `Terminate(…)`
    private static TimeSpan?       updateDelta                                   = null;                       // ->> Time between each `Update(…)`
    private static TimeSpan?       updateTimestamp                               = null;                       // ->> Time till next `Update(…)`
    private static Window          window                                        = null;                       // ->> Game window
    private static FormBorderStyle windowBorderStyle                             = FormBorderStyle.None;       // ->> Game window vendor UI decorations and overlay
    private static FormWindowState windowState                                   = FormWindowState.Normal;     // ->> Game window state ie: fullscreen, …

    private static Unit[] players = {
      null, // ->> Keyboard   ⌨️
      null, // ->> Mouse      🖱️
      null, // ->> Controller 🎮
      null, // ->> Touch 1    👉
      null  // ->> Touch 2    👈
    };

    private static Unit player {
      get { return players[0]; }
      set { players[0] = value; }
    }

    /* Function > ... */
    [DllImport("user32.dll",
      CallingConvention     = CallingConvention.Cdecl,
      CharSet               = CharSet.Unicode,
      EntryPoint            = "EnumDisplaySettingsA",
      ExactSpelling         = true,
      PreserveSig           = false,
      SetLastError          = true,
      ThrowOnUnmappableChar = true
    )] private static extern bool EnumerateDisplaySettings(string deviceName, ulong modeIndex, ref DEVMODE deviceMode);

    public static void ExitFullscreen() {
      window.FormBorderStyle = windowBorderStyle;
      window.WindowState     = windowState;
    }

    public static bool IsFullscreen() {
      return FormBorderStyle.None == window.FormBorderStyle && FormWindowState.Maximized == window.WindowState;
    }

    public static Point coordinates = new Point(0, 0);
    public static int   sussy       = 0;
    private static void PostProcessRender() {
      while (false == terminated) {
        /* ... ->> Post-process fullscreen background */
        if (IsFullscreen()) {
          Size  windowMaximizedSize    = window.GetComputedSize();
          Int32 windowMaximizedBreadth = Math.Max(windowMaximizedSize.Height, windowMaximizedSize.Width);

          // ...
          // sussy = coordinates.Y;
          for (uint y = (uint) sussy * 4u; y != windowMaximizedBreadth * 4u; ++sussy, y += 4u)
          for (uint x = 0 * 4u; x != windowMaximizedBreadth * 4u; x += 4u) {
            uint index = (uint) (x + (y * windowMaximizedBreadth));

            // ...
            renderPostProcessorFullscreenRenderData[index + 1] = (byte) Math.Max(0xFFu, renderPostProcessorFullscreenRenderData[index + 1] + 0x7Fu);
            // renderPostProcessorFullscreenRenderData[index + 1] = (byte) 0x00u;
            // renderPostProcessorFullscreenRenderData[index + 2] = (byte) 0x00u;
            // renderPostProcessorFullscreenRenderData[index + 3] = (byte) 255u;
          }
        }
      }
    }

    private static void RequestFullscreen() {
      windowState            = window.WindowState;
      windowBorderStyle      = window.FormBorderStyle;
      window.FormBorderStyle = FormBorderStyle.None;
      window.WindowState     = FormWindowState.Maximized;
    }

    /* ... */
    public static void Input(Keys? releasedKey) {
      switch (releasedKey) {
        case Keys.Escape: Terminate();                                                    break;
        case Keys.F11   : if (IsFullscreen()) ExitFullscreen(); else RequestFullscreen(); break;
      }

      foreach (Keys key in keys)
      switch (key) {
        case Keys.Down : case Keys.S: coordinates.Y = (int) (coordinates.Y + (window.Height * 0.05f)); break;
        case Keys.Left : case Keys.A: coordinates.X = (int) (coordinates.X - (window.Width  * 0.05f)); /*player.Rotation -= (float) Math.PI / 180.0f; Console.WriteLine("[^]: " + (player.Rotation * (180.0f / Math.PI)));*/ break;
        case Keys.Right: case Keys.D: coordinates.X = (int) (coordinates.X + (window.Width  * 0.05f)); /*player.Rotation += (float) Math.PI / 180.0f; Console.WriteLine("[^]: " + (player.Rotation * (180.0f / Math.PI)));*/ break;
        case Keys.Up   : case Keys.W: coordinates.Y = (int) (coordinates.Y - (window.Height * 0.05f)); break;
      }
    }

    public static void Render(object target, PaintEventArgs arguments) {
      Bitmap   render              = renders[renderIndex];
      TimeSpan timestamp           = TimeSpan.FromTicks(DateTime.Now.Ticks);
      Window   window              = (Window) target; // ->> Same as `Game::window`… ideally
      Graphics windowGraphics      = arguments.Graphics;
      Size     windowMaximizedSize = window.Size;
      Size     windowSize          = window.GetComputedSize();
      PointF   windowOrigin        = new PointF(windowSize.Width * 0.5f, windowSize.Height * 0.5f);

      // ...
      windowGraphics.Clear(Color.DarkBlue/*window.BackColor*/);

      if (renderDelta > timestamp - renderTimestamp)
        // ->> Preserve prior `Render(…)` (`Window::Invalidate(…)` apparently cleans up the current paint)
        windowGraphics.DrawImage(renders[(renderIndex == 0u ? renders.Length : renderIndex) - 1u], (windowMaximizedSize.Width - windowSize.Width) / 2, (windowMaximizedSize.Height - windowSize.Height) / 2);

      else {
        Graphics graphics    = Graphics.FromImage(render);
        byte     playerCount = ((Func<uint, byte>)   (value => { foreach (Unit player in players) value += null != player ? 1u              : 0u;   return (byte) value;                                   }))(0u);
        float    rotation    = ((Func<float, float>) (value => { foreach (Unit player in players) value += null != player ? player.Rotation : 0.0f; return value / (0u == playerCount ? 1u : playerCount); }))(0.0f);

        // ...
        graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
        renderTimestamp        = timestamp;

        graphics.Clear(window.BackColor);

        // ... ->> Draw stars
        foreach (Star star in stars) {
          Point  computedDestinationCoordinates = star.GetComputedDestinationCoordinates(windowSize);
          Point  computedSourceCoordinates      = star.GetComputedSourceCoordinates(windowSize);
          PointF destinationCoordinates         = new PointF(computedDestinationCoordinates.X, computedDestinationCoordinates.Y);
          float  rotationCosine                 = (float) Math.Cos(rotation);
          float  rotationCull                   = 0.0f;
          float  rotationSine                   = (float) Math.Sin(rotation);
          PointF sourceCoordinates              = new PointF(computedSourceCoordinates.X, computedSourceCoordinates.Y);

          // ... --- TODO (Lapys) -> Improve rotation culling
          do {
            if (rotation >= Math.PI * 0.0f && rotation <= Math.PI * 0.5f) { rotationCull = (float) ((Math.PI * 0.0f) + (Math.PI / 4.0f)) - rotation; break; }
            if (rotation >= Math.PI * 0.5f && rotation <= Math.PI * 1.0f) { rotationCull = (float) ((Math.PI * 0.5f) + (Math.PI / 4.0f)) - rotation; break; }
            if (rotation >= Math.PI * 1.0f && rotation <= Math.PI * 1.5f) { rotationCull = (float) ((Math.PI * 1.0f) + (Math.PI / 4.0f)) - rotation; break; }
            if (rotation >= Math.PI * 1.5f && rotation <= Math.PI * 2.0f) { rotationCull = (float) ((Math.PI * 1.5f) + (Math.PI / 4.0f)) - rotation; break; }
          } while (false);

          rotationCull = 1.0f - (Math.Abs(rotationCull) / (float) (Math.PI / 4.0f));            // ->> Scale based on rotation (45° angles are the most scaled)
          rotationCull = (rotationCull * 0.5f) * Math.Max(windowSize.Height, windowSize.Width); // ->> Convert to in-world coordinates

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
          graphics.FillEllipse(
            new SolidBrush(Color.FromArgb((int) (star.Opacity * (star.Delta > 0.5f ? 2.0f - (star.Delta * 2.0f) : (star.Delta * 2.0f))), Color.White)),
            new RectangleF(
              sourceCoordinates.X + (star.Delta * (destinationCoordinates.X - sourceCoordinates.X)),
              sourceCoordinates.Y + (star.Delta * (destinationCoordinates.Y - sourceCoordinates.Y)),
              star.Size,
              star.Size
            )
          );
        }

        // ...
        graphics.FillRectangle(new SolidBrush(Color.Indigo), 0, coordinates.Y, windowSize.Width, 50);

        graphics.FillRectangle(new SolidBrush(Color.Blue), 100, 100, 50, 50);
        graphics.FillRectangle(new SolidBrush(Color.Green), windowSize.Width / 2, (windowSize.Height / 2) - 25, 50, 50);
        graphics.FillRectangle(new SolidBrush(Color.Red), (windowSize.Width / 2) - 50, (windowSize.Height / 2) - 25, 50, 50);
        graphics.FillRectangle(new SolidBrush(Color.Yellow), (windowSize.Width - 100) - 50, 100, 50, 50);

        graphics.FillRectangle(new SolidBrush(Color.White), coordinates.X, coordinates.Y, 30, 30);

        // ...
        renderIndex = (byte) ((renderIndex + 1u) % renders.Length);

        graphics.Dispose();
        windowGraphics.DrawImage(render, (windowMaximizedSize.Width - windowSize.Width) / 2, (windowMaximizedSize.Height - windowSize.Height) / 2);
      }

      // ... ->> Draw fullscreen background
      if (IsFullscreen()) {
        int sus = Math.Min(sussy, render.Height - 1);
        BitmapData renderData             = render.LockBits(new Rectangle(0, sus, render.Width, render.Height - sus), ImageLockMode.ReadOnly, render.PixelFormat);
        Int32      windowMaximizedBreadth = Math.Max(windowMaximizedSize.Height, windowMaximizedSize.Width);

        // ...
        Marshal.Copy(renderData.Scan0, renderPostProcessorFullscreenRenderData, sus * render.Width * 4, (render.Height - sus) * render.Width * 4);
        render.UnlockBits(renderData);

        // for (uint column = 0; column != renderPostProcessorFullscreenRenderData.Width;  ++column)
        // for (uint row    = 0; row    != renderPostProcessorFullscreenRenderData.Height; ++row) {
        //   ushort averageCount = (ushort) 0u;
        //   byte   averageBlue  = (byte)   0u;
        //   byte   averageGreen = (byte)   0u;
        //   byte   averageRed   = (byte)   0u;

        //   // ...
        //   for (uint subcolumn = column; subcolumn < column + 10u && subcolumn != renderPostProcessorFullscreenRender.Width;  ++subcolumn)
        //   for (uint subrow    = row;    subrow    < row    + 10u && subrow    != renderPostProcessorFullscreenRender.Height; ++subrow) {
        //     // Color pixel = renderPostProcessorFullscreenRenderData[subcolumn + (subrow * renderPostProcessorFullscreenRender.Width)];

        //     // // ...
        //     // ++averageCount;

        //     // averageBlue  += pixel.B;
        //     // averageGreen += pixel.G;
        //     // averageRed   += pixel.R;

        //     continue;
        //   }

        //   // averageBlue  /= (byte) averageCount;
        //   // averageGreen /= (byte) averageCount;
        //   // averageRed   /= (byte) averageCount;

        //   // ...
        //   Color averagePixel = Color.FromArgb(averageRed, averageGreen, averageBlue);

        //   for (uint subcolumn = column; subcolumn < column + 10u && subcolumn != renderPostProcessorFullscreenRender.Width;  ++subcolumn)
        //   for (uint subrow    = row;    subrow    < row    + 10u && subrow    != renderPostProcessorFullscreenRender.Height; ++subrow)
        //     continue;
        //     // renderPostProcessorFullscreenRenderData[subcolumn + (subrow * renderPostProcessorFullscreenRender.Width)] = averagePixel;
        // }

        windowGraphics.DrawImage(renderPostProcessorFullscreenRender, (windowMaximizedSize.Width - windowMaximizedBreadth) / 2, (windowMaximizedSize.Height - windowMaximizedBreadth) / 2, windowMaximizedBreadth, windowMaximizedBreadth);
        windowGraphics.DrawImage(render,                              (windowMaximizedSize.Width - windowSize.Width)       / 2, (windowMaximizedSize.Height - windowSize.Height)      / 2, windowSize.Width - 1,   windowSize.Height - 1);
        windowGraphics.DrawRectangle(renderPostProcessorFullscreenRenderBorderPen, (windowMaximizedSize.Width - windowSize.Width + 1) / 2, (windowMaximizedSize.Height - windowSize.Height + 1) / 2, windowSize.Width - 1, windowSize.Height - 1);
      }
    }

    public static void Terminate() {
      if (terminated) return;
      terminated = true;

      renderPostProcessorFullscreenRender.Dispose();
      renderPostProcessorFullscreenRenderAllocation.Free();
      renderPostProcessorFullscreenRenderBorderPen.Dispose();
      window.Close();

      // ...
      if (Application.MessageLoop) Application.Exit();
      else Environment.Exit(0x00);
    }

    public static void Update(object target, EventArgs arguments) {
      byte     playerCount = ((Func<uint, byte>)   (value => { foreach (Unit player in players) value += null != player ? 1u              : 0u;   return (byte) value;                                   }))(0u);
      float    rotation    = ((Func<float, float>) (value => { foreach (Unit player in players) value += null != player ? player.Rotation : 0.0f; return value / (0u == playerCount ? 1u : playerCount); }))(0.0f);
      int      starsLength = stars.Count;
      TimeSpan timestamp   = TimeSpan.FromTicks(DateTime.Now.Ticks);
      Size     windowSize  = window.GetComputedSize();

      /* ... ->> Game logic unbounded by framerate ie: calculations, flags, … */ {
        starsMaximumLength = (ushort) ((windowSize.Height + windowSize.Width) / 20u);

        // [Stars] ... ->> Remove fallen (excess) stars
        while (starsLength > starsMaximumLength)
        stars.Remove(stars[--starsLength]);

        for (int index = starsLength; 0 != index--; )
        if (stars[index].Delta >= 1.0f) {
          stars.Remove(stars[index]);
          --starsLength;

          continue;
        }
      }

      /* ... ->> Game logic unbounded by `Update(…)` framerate ie: calculations, flags, … */ {
        // [Stars] ... ->> Spawn falling stars
        if (starsSpawnDelta < timestamp - starsSpawnTimestamp)
        if (starsLength != starsMaximumLength) {
          ushort starsSpawnCount = (ushort) Star.Randomizer.Next(starsSpawnCountDelta[0], starsSpawnCountDelta[1]);

          // ...
          starsSpawnCount     = (ushort) (starsLength + starsSpawnCount > starsMaximumLength ? starsMaximumLength - starsLength : starsSpawnCount);
          starsSpawnTimestamp = timestamp;

          while (0u != starsSpawnCount--) {
            Star star = new Star();

            // ...
            star.DestinationCoordinates.X = (float) Star.Randomizer.NextDouble();
            star.DestinationCoordinates.Y = 1.0f;
            star.Opacity                  = (byte) Star.Randomizer.Next(127, 255);
            star.SourceCoordinates.X      = star.DestinationCoordinates.X;
            star.SourceCoordinates.Y      = (float) Star.Randomizer.NextDouble() * 0.65f;
            star.Speed                    = (float) Star.Randomizer.NextDouble() * 0.0025f;

            stars.Add(star);
          }
        }
      }

      /* Update ->> Game logic bounded by `Update(…)` framerate ie: animations, transitions, … */
      if (updateDelta < timestamp - updateTimestamp) {
        updateTimestamp = timestamp;

        // [Stars] ... ->> Fell stars
        foreach (Star star in stars)
        star.Delta += star.Speed;
      }

      /* Render ->> Game render bounded by `Render(…)` */
      window.Invalidate();
    }

    /* Main */
    static void Main(String[] commandLineArguments) {
      TimeSpan delta            = TimeSpan.FromTicks((long) (TimeSpan.TicksPerSecond / 60uL));
      DEVMODE  deviceMode       = new DEVMODE();
      uint     deviceFramerate  = 60u;
      TimeSpan timestamp        = TimeSpan.FromTicks(DateTime.Now.Ticks);
      Timer    updateTimer      = null;
      Screen   windowScreen     = null;
      Int32    windowScreenSize = 0;
      Int32    windowSize       = 0;

      /* Update > ... */
      if (EnumerateDisplaySettings(null, DEVMODE.ENUM_CURRENT_SETTINGS, ref deviceMode)) {
        deviceFramerate = (uint) deviceMode.dmDisplayFrequency;
        delta           = TimeSpan.FromTicks((long) (TimeSpan.TicksPerSecond / deviceFramerate));
      }

      keys                                         = new List<Keys>();
      player                                       = new Infantry(new Point(0, 0));
      renderDelta                                  = delta;
      renderPostProcessor                          = new Thread(new ThreadStart(PostProcessRender));
      renderPostProcessorFullscreenRenderBorderPen = new Pen(Color.FromArgb(166, 0xFF, 0xFF, 0xFF));
      renderTimestamp                              = timestamp;
      stars                                        = new List<Star>();
      starsMaximumLength                           = (ushort) 69u;
      starsSpawnCountDelta[0]                      = (ushort) 1u;
      starsSpawnCountDelta[1]                      = (ushort) 5u;
      starsSpawnDelta                              = TimeSpan.FromTicks((long) (TimeSpan.TicksPerMillisecond * 600uL));
      starsSpawnTimestamp                          = timestamp;
      state                                        = State.MENU;
      updateDelta                                  = delta;
      updateTimer                                  = new Timer();
      updateTimestamp                              = timestamp;
      window                                       = new Window();
      windowBorderStyle                            = window.FormBorderStyle;
      windowScreen                                 = Screen.FromControl(window);
      windowScreenSize                             = Math.Min(windowScreen.Bounds.Height, windowScreen.Bounds.Width);
      windowSize                                   = (Int32) (Math.Min(windowScreen.WorkingArea.Height, windowScreen.WorkingArea.Width) * 0.8f);
      windowState                                  = window.WindowState;

      for (int index = renders.Length; 0 != index; )
      renders[--index] = new Bitmap(windowScreenSize, windowScreenSize, PixelFormat.Format32bppPArgb);

      renderPostProcessorFullscreenRenderData       = new byte[windowScreenSize * windowScreenSize * 4];
      renderPostProcessorFullscreenRenderAllocation = GCHandle.Alloc(renderPostProcessorFullscreenRenderData, GCHandleType.Pinned);
      renderPostProcessorFullscreenRender           = new Bitmap(windowScreenSize, windowScreenSize, windowScreenSize * 4, PixelFormat.Format32bppPArgb, renderPostProcessorFullscreenRenderAllocation.AddrOfPinnedObject());

      /* Modification > ... */
      Application.Idle += new EventHandler(Update);

      updateTimer.Enabled  = true;
      updateTimer.Interval = (int) updateDelta.Value.TotalMilliseconds;
      updateTimer.Tick    += new EventHandler(Update);

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
      renderPostProcessor.Start();
      if (DialogResult.OK != window.ShowDialog()) Terminate();
    }
  }
}
