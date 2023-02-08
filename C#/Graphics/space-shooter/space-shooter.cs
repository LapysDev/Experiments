/* Import --> del space-shooter.exe & cls && csc /optimize /out:space-shooter.exe /r:System.Collections.dll /r:System.Drawing.Primitives.dll /r:System.Runtime.dll /r:System.Threading.Thread.dll /r:System.Windows.Forms.dll /t:exe space-shooter.cs && space-shooter.exe & del space-shooter.exe */
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.Drawing.Text;
using System.IO;
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
        protected static Random Randomizer = new Random();

        protected float acceleration;
        protected float rotation;
        protected float size;
        protected float speed;

        public Point Coordinates;
        public uint  Health;
        public float MaximumSpeed;
        public float Acceleration { get { return acceleration; } set { acceleration = (value < 0.0f ? 0.0f : value > 1.0f ? 1.0f : value);                                  } }
        public float Rotation     { get { return rotation;     } set { rotation     = (value < 0.0f ? (float) (Math.PI * 2.0f) + value : value) % (float) (Math.PI * 2.0f); } }
        public float Size         { get { return size;         } set { size         = (value < 0.0f ? 0.0f : value > 1.0f ? 1.0f : value);                                  } }
        public float Speed        { get { return speed;        } set { speed        = (value < 0.0f ? 0.0f : value > 1.0f ? 1.0f : value);                                  } }

        // ...
        public Entity(Point coordinates, float size) {
          this.Acceleration = 0.0f;
          this.Coordinates  = coordinates;
          this.Health       = 0u;
          this.MaximumSpeed = 0.0f;
          this.Rotation     = (float) (Math.PI * Entity.Randomizer.NextDouble() * 2.0f);
          this.Size         = size;
          this.Speed        = 0.0f;
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
            public static float BaseSize = 0.0300f;

            // ...
            public Asteroid(Point coordinates, float size) : base(coordinates, size) {
              this.Acceleration = 0.001f + (Asteroid.BaseSize / size);
              this.Health       = (uint) (75u * (size / Asteroid.BaseSize));
              this.MaximumSpeed = 0.050f;
            }

            public Asteroid(Point coordinates) : this(coordinates, Asteroid.BaseSize + (float) (Entity.Randomizer.NextDouble() * 0.1000f)) {}
          };

          /* Bonus */
          private sealed class Bonus : Item {
            public enum BonusType : byte {
              CLONE,      // ->> Clone a `Unit`
              DEFENSE,    // ->> Boost a `Unit`'s defense
              GRACE,      // ->> Prevent a `Unit`'s insta-death
              HEALTH,     // ->> Regenerate half a `Unit`'s health
              INFECT,     // ->> Make a `Unit`'s offense infectious
              NECRO,      // ->> Make a `Unit`'s kills respawn as allies
              POWER,      // ->> Boost a `Unit`'s offense
              RANGE,      // ->> Boost a `Unit`'s line-of-sight or offensive range
              RECHARGE,   // ->> Regenerate a `Unit`s ability cooldowns
              REGENERATE, // ->> Regenerate a `Unit`s health over time
              SPEED       // ->> Boost a `Unit`'s maximum speed
            };

            // ...
            BonusType Type;

            // ...
            public Bonus(Point coordinates, BonusType type) : base(coordinates, 0.0300f) {
              this.Acceleration = 0.01f;
              this.MaximumSpeed = 0.05f;
              this.Type         = type;
            }
          };

        /* Unit */
        private class Unit : Entity {
          protected float defense;

          public List<Unit> Clones;                                                                                                  // --> Bonus.CLONE
          public bool       Graced;                                                                                                  // --> Bonus.GRACE
          public bool       Infectious;                                                                                              // --> Bonus.INFECT
          public bool       Necro;                                                                                                   // --> Bonus.NECRO
          public uint       Offense;                                                                                                 //
          public TimeSpan   OffenseTimestamp;                                                                                        //
          public uint       Shield;                                                                                                  // --> Bonus.DEFENSE
          public float      Defense { get { return defense; } set { defense = value > 0.0f ? value < 1.0f ? value : 1.0f : 0.0f; } } // ->> Proportion damage is reduced by
          public Image      Render  { get; protected set;                                                                          } //

          // ...
          public Unit(Point coordinates, float size) : base(coordinates, size) {
            this.Clones           = new List<Unit>();
            this.Defense          = 0.0f;
            this.Graced           = false;
            this.Infectious       = false;
            this.Necro            = false;
            this.Offense          = 0u;
            this.OffenseTimestamp = new TimeSpan(0L);
            this.Render           = null;
            this.Shield           = 0u;
          }
        };
          /* Alien */
          private class Alien : Unit {
            public float LineOfSight; // ->> Frustum representing fog-of-war

            // ...
            public Alien(Point coordinates, float size) : base(coordinates, size) {
              this.LineOfSight = (float) Math.PI / 5.0f;
            }
          };
            /* Carrier ->> Poisonous vector */
            private class Carrier : Alien {
              new public bool Infectious { get { return true; } }

              // ...
              public Carrier(Point coordinates, byte stage) : base(coordinates, 0.03500f) {
                this.Health           = 20u;
                this.LineOfSight      = (float) Math.PI * 2.0f;
                this.Offense          = 3u;
                this.OffenseTimestamp = TimeSpan.FromTicks(TimeSpan.TicksPerMillisecond * 500L);
                this.Render           = Image.FromFile("assets/entities/aliens/carrier.png");
              }
            };

            /* Globule ->> Semi-solid melee parasite */
            private class Globule : Alien {
              public static float    BaseSize    = 0.0400f;
              public static TimeSpan OffenseRate = TimeSpan.FromTicks(TimeSpan.TicksPerMillisecond * 800L);

              protected float cojoinTendency;
              protected float detachDodgeTendency;
              protected byte  stage;
              protected float throwTendency;

              public float     CojoinTendency      { get { return cojoinTendency;                        } set { cojoinTendency      = value > 1.0f ? 1.0f : value;                                      } } // ->> Tendency to join allied `Globule` via mitosis
              public float     DetachDodgeTendency { get { return detachDodgeTendency;                   } set { detachDodgeTendency = value > 1.0f ? 1.0f : value;                                      } } // ->> Tendency to dodge visible enemy fire via meiosis
              new public float LineOfSight         { get { return (float) Math.PI / (5.0f - this.Stage); }                                                                                                 } //
              new public float Size                { get { return size / Globule.BaseSize;               } set { size                = value < 0.0f ? 0.0f : value > 1.0f ? 1.0f : value;                } } //
              public byte      Stage               { get { return stage;                                 } set { stage               = (byte) (value > 0u ? value < 5u ? value : 4u : 1u); size = stage; } } // ->> Number of co-joined `Globule`s
              public float     ThrowTendency       { get { return throwTendency;                         } set { throwTendency       = value > 1.0f ? 1.0f : value;                                      } } // ->> Tendency to lunge at enemies via meiosis

              // ...
              public Globule(Point coordinates, byte stage) : base(coordinates, 1.0f) {
                this.Defense             = 0.01f;
                this.DetachDodgeTendency = difficulty / 6.0f;
                this.Health              = 30u;
                this.Offense             = 10u;
                this.Stage               = stage;
                this.ThrowTendency       = (float) Entity.Randomizer.NextDouble() * (difficulty / 3.5f);
              }

              public Globule(Point coordinates) : this(coordinates, (byte) Entity.Randomizer.Next(1, (int) difficulty)) {}
            };

            /* Kamikaze */
            private class Kamikaze : Alien {
              new public float Defense { get { return 0.0f; } }
              new public uint  Shield  { get { return 0u;   } }

              // ...
              public Kamikaze(Point coordinates) : base(coordinates, 0.0400f) {
                this.Health  = 1u;
                this.Offense = 30u;
                this.Render  = Image.FromFile("assets/entities/aliens/kamikaze.png");
              }
            };

            /* Man o' War ->> Resistant medium-heavy solider */
            private class ManOWar : Alien {
              public static TimeSpan OffenseRate = TimeSpan.FromTicks(TimeSpan.TicksPerMillisecond * 1650L);

              // ...
              public ManOWar(Point coordinates) : base(coordinates, 0.0600f) {
                this.Defense = 0.35f;
                this.Health  = 85u;
                this.Offense = 20u;
                this.Render  = Image.FromFile("assets/entities/aliens/man-o'-war.png");
                this.Shield  = 15u;
              }
            };

          /* Ship */
          private class Ship : Unit {
            public enum WeaponType : byte {
              BOUNCE,  // ->> Interactable bullets
              CHAIN,   // ->> Chained laser
              LASER,   // ->> High-concentrated damage with minimal range
              MISSILE, // ->> Extremely high-damage explosive rocket
              SCATTER, // ->> Far-spread bullet volleys
              SEEKING, // ->> Seeking bullets
              SPREAD,  // ->> Persistent damage cloud
              STANDARD // ->> Chargeable bullets
            };

            // ...
            public static TimeSpan OffenseRate = new TimeSpan(0L);
            public WeaponType Weapon;

            // ...
            public Ship(Point coordinates, float size) : base(coordinates, size) {
              this.Rotation = 0.0f;
              this.Weapon   = Ship.WeaponType.STANDARD;
            }
          };
            /* Artillery ->> Heavy bruiser with a high health pool */
            private sealed class Artillery : Ship {
              new public static TimeSpan OffenseRate = TimeSpan.FromTicks(TimeSpan.TicksPerMillisecond * 200L);

              public Artillery(Point coordinates) : base(coordinates, 0.0675f) {
                this.Health  = 250u;
                this.Offense = 40u;
                this.Render  = Image.FromFile("assets/entities/ships/artillery.png");
              }
            };

            /* Infantry ->> Standard model fighter */
            private sealed class Infantry : Ship {
              public static TimeSpan     DashRate    = TimeSpan.FromTicks(TimeSpan.TicksPerMillisecond * 2000L);
              new public static TimeSpan OffenseRate = TimeSpan.FromTicks(TimeSpan.TicksPerMillisecond * 10L);

              public TimeSpan DashTimestamp;

              // ...
              public Infantry(Point coordinates) : base(coordinates, 0.0500f) {
                this.DashTimestamp = new TimeSpan(0L);
                this.Health        = 100u;
                this.Offense       = 20u;
                this.Render        = Image.FromFile("assets/entities/ships/infantry.png");
              }
            };

            /* Rogue ->> Lightweight fighter with cloaking and espionage abilities */
            private sealed class Rogue : Ship {
              new public static TimeSpan OffenseRate = new TimeSpan(0L);
              public static TimeSpan     StealthRate = TimeSpan.FromTicks(TimeSpan.TicksPerMillisecond * 2000L);

              public TimeSpan StealthTimestamp;

              // ...
              public Rogue(Point coordinates) : base(coordinates, 0.0400f) {
                this.Health           = 75u;
                this.Offense          = 10u;
                this.Render           = Image.FromFile("assets/entities/ships/rogue.png");
                this.StealthTimestamp = new TimeSpan(0L);
              }
            };

            /* Swarm ->> Mini-carriers focused on quantity and combat formation */
            private sealed class Swarm : Ship {
              public sealed class Drone : Ship {
                public Drone(Point coordinates) : base(coordinates, 0.0300f) {
                  this.Health = 13u;
                  this.Render = Image.FromFile("assets/entities/ships/swarm-drone.png");
                }
              };

              // ...
              new public static TimeSpan OffenseRate = TimeSpan.FromTicks(TimeSpan.TicksPerMillisecond * 10L);
              public static TimeSpan     SpawnRate   = TimeSpan.FromTicks(TimeSpan.TicksPerMillisecond * 5365L);

              public List<Drone> Carriers;
              public TimeSpan    SpawnTimestamp;

              // ...
              public Swarm(Point coordinates) : base(coordinates, 0.0350f) {
                this.Carriers       = new List<Drone>();
                this.Health         = 30u;
                this.Render         = Image.FromFile("assets/entities/ships/swarm.png");
                this.SpawnTimestamp = new TimeSpan(0L);

                this.Carriers.Add(new Drone(new Point(0, 0)));
                this.Carriers.Add(new Drone(new Point(0, 0)));
                this.Carriers.Add(new Drone(new Point(0, 0)));
              }
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

          return this.ClientSize;
        }

        protected override void OnPaintBackground(PaintEventArgs arguments) {
          /* Do nothing... ->> Prevent implicitly re-painting the background */
        }
      };

    /* Global > ... */
    private static float           difficulty                                    = 0.0f;                       // ->> Overall stats. calculator
    private static List<Keys>      keys                                          = null;                       // ->> Keys ⌨️ currently activated
    private static Font            headingFont                                   = SystemFonts.CaptionFont;    // ->> Game heading UI fallback font
    private static FontFamily      headingFontFamily                             = null;                       // ->> Game heading UI font face
    private static Image[]         renderControllerImages                        = null;                       // ->> Controller UI images
    private static TimeSpan?       renderDelta                                   = null;                       // ->> Time between each `Render(…)`
    private static Pen             renderFullscreenBorderPen                     = null;                       // ->> Fullscreen graphic border
    private static Image           renderFullscreenImage                         = null;                       // ->> Fullscreen graphic background image
    private static byte            renderIndex                                   = (byte) 0u;                  // ->> Buffer currently used in multiple-buffering
    private static Thread          renderPostProcessor                           = null;                       // ->> Background processor to handle strenuous synchronous image effects processing & filtering
    private static Bitmap          renderPostProcessorFullscreenRender           = null;                       // ->> Fullscreen graphic
    private static GCHandle        renderPostProcessorFullscreenRenderAllocation = GCHandle.Alloc(0x00u);      // ->> Fullscreen graphic allocated render data
    private static BitmapData      renderPostProcessorFullscreenRenderBitmapData = null;                       // ->> Fullscreen graphic `BitmapData` for bit-block transferring from the main render
    private static byte  []        renderPostProcessorFullscreenRenderData       = null;                       // ->> Fullscreen graphic render data ie: pixels, …
    private static byte  [][]      renderPostProcessorFullscreenRenderSubdata    = null;                       // ->> Fullscreen graphic render subdata
    private static bool            renderResized                                 = false;                      // ->> Determines if the render was resized
    private static Bitmap[]        renders                                       = {null, null};               // ->> Multiple Buffering rendering for gameplay graphics (at least one required)
    private static TimeSpan?       renderTimestamp                               = null;                       // ->> Time till next `Render(…)`
    private static List<Star>      stars                                         = null;                       // ->> Stars trailing in the background
    private static ushort          starsMaximumLength                            = (ushort) 0u;                // ->> Stars total
    private static ushort[]        starsSpawnCountDelta                          = {(ushort) 0u, (ushort) 1u}; // ->> Stars spawned at a time
    private static TimeSpan?       starsSpawnDelta                               = null;                       // ->> Time between each star spawn
    private static TimeSpan?       starsSpawnTimestamp                           = null;                       // ->> Time till next star spawn
    private static State   ?       state                                         = null;                       // ->> Game state for menus, options, etc…
    private static bool            terminated                                    = false;                      // ->> Game state for `Terminate(…)`
    private static Font            textFont                                      = SystemFonts.DefaultFont;    // ->> Game text UI fallback font
    private static FontFamily      textFontFamily                                = null;                       // ->> Game text UI font face
    private static string          title                                         = "Space Shooter";            // ->> Game title
    private static TimeSpan?       updateDelta                                   = null;                       // ->> Time between each `Update(…)`
    private static TimeSpan?       updateTimestamp                               = null;                       // ->> Time till next `Update(…)`
    private static Window          window                                        = null;                       // ->> Game window
    private static FormBorderStyle windowBorderStyle                             = FormBorderStyle.None;       // ->> Game window vendor UI decorations and overlay
    private static FormWindowState windowState                                   = FormWindowState.Normal;     // ->> Game window state ie: fullscreen, …

    private static Unit[] players = {
      null, // ->> Keyboard ⌨️
      null, // ->> Mouse    🖱️
      null, // ->> Gamepad  🎮
      null  // ->> Touch    👆
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

    private static void ExitFullscreen() {
      renderResized          = false;
      window.FormBorderStyle = windowBorderStyle;
      window.WindowState     = windowState;
    }

    private static byte GetPlayerCount() {
      byte count = (byte) 0u;

      // ...
      foreach (Unit player in players)
      count += (byte) (null != player ? 1u : 0u);

      return count;
    }

    private static float GetPlayersOverallRotation() {
      float rotation = 0.0f;

      // ...
      foreach (Unit player in players)
      rotation += null != player ? player.Rotation : 0.0f;

      return rotation / GetPlayerCount();
    }

    private static bool IsFullscreen() {
      return FormBorderStyle.None == window.FormBorderStyle && FormWindowState.Maximized == window.WindowState;
    }

    private static void PostProcessRender() {
      while (false == terminated) {
        /* ... ->> Post-process fullscreen background: Gaussian blur */
        if (IsFullscreen() && null != renderPostProcessorFullscreenRenderBitmapData) {
          uint       renderPostProcessorFullscreenRenderWidth  = (uint) renderPostProcessorFullscreenRender.Width;  // ->> Ideally `renderPostProcessorFullscreenRender` is still unused at this point
          uint       renderPostProcessorFullscreenRenderHeight = (uint) renderPostProcessorFullscreenRender.Height; // ->> Ideally `renderPostProcessorFullscreenRender` is still unused at this point
          ulong[]    colorSum                                  = {0uL, 0uL, 0uL, 0uL};
          byte []    colorAverage                              = {(byte) 0u, (byte) 0u, (byte) 0u, (byte) 0u};
          byte []    blurVerticalData                          = renderPostProcessorFullscreenRenderSubdata[2];
          float      blurMedian                                = 0.0f;
          const uint blurIntensity                             = 5u;
          byte[]     blurHorizontalData                        = renderPostProcessorFullscreenRenderSubdata[1];
          float      blurFilterWidth                           = 0.0f;
          byte[]     blurData                                  = blurVerticalData;

          // ...
          blurFilterWidth  = (float) Math.Sqrt(((blurIntensity * blurIntensity * 12.0f) / 3.0f) + 1.0f);
          blurFilterWidth -= 0u == (uint) blurFilterWidth % 2u ? 1.0f : 0.0f;
          blurMedian       = (float) Math.Round(((blurIntensity * blurIntensity * 12.0) - (blurFilterWidth * blurFilterWidth * 3.0) - (blurFilterWidth * 12.0) - 9.0) / ((blurFilterWidth * -4.0) - 4.0));

          for (byte count = (byte) 0u; count != 3u; ++count) {
            uint   boxRadius  = (uint) blurFilterWidth + (0u == blurFilterWidth % 2u ? 1u : 0u) + (count >= blurMedian ? 2u : 0u);
            byte[] renderData = 0u == count ? renderPostProcessorFullscreenRenderSubdata[0] : blurData;

            // ... ->> Horizontal blurring --- TODO (Lapys)
            for (uint y = 0u; y != renderPostProcessorFullscreenRenderHeight * sizeof(byte) * 4u; y += 4u * sizeof(byte)) {
              colorSum[0] = 0uL;
              colorSum[1] = 0uL;
              colorSum[2] = 0uL;
              colorSum[3] = 0uL;

              for (uint x = 0u; x != (boxRadius < renderPostProcessorFullscreenRenderWidth ? boxRadius : renderPostProcessorFullscreenRenderWidth) * sizeof(byte) * 4u; x += 4u * sizeof(byte)) {
                uint index = (uint) (x + (y * renderPostProcessorFullscreenRenderWidth));

                colorSum[0] += renderData[index + 0];
                colorSum[1] += renderData[index + 1];
                colorSum[2] += renderData[index + 2];
                colorSum[3] += renderData[index + 3];
              }

              colorAverage[0] = (byte) (colorSum[0] / boxRadius);
              colorAverage[1] = (byte) (colorSum[1] / boxRadius);
              colorAverage[2] = (byte) (colorSum[2] / boxRadius);
              colorAverage[3] = (byte) (colorSum[3] / boxRadius);

              for (uint x = 0u; x != renderPostProcessorFullscreenRenderWidth * sizeof(byte) * 4u; x += 4u * sizeof(byte)) {
                uint index = 0u;

                if (x >= (boxRadius / 2u) * sizeof(byte) * 4u && x + ((boxRadius / 2u) * sizeof(byte) * 4u) + (4u * sizeof(byte)) < renderPostProcessorFullscreenRenderWidth * sizeof(byte) * 4u) {
                  index        = (uint) ((x - ((boxRadius / 2u) * sizeof(byte) * 4u) - (0u * 4u * sizeof(byte))) + (y * renderPostProcessorFullscreenRenderWidth));
                  colorSum[0] -= renderData[index + 0];
                  colorSum[1] -= renderData[index + 1];
                  colorSum[2] -= renderData[index + 2];
                  colorSum[3] -= renderData[index + 3];

                  index        = (uint) ((x - ((boxRadius / 2u) * sizeof(byte) * 4u) + (1u * 4u * sizeof(byte))) + (y * renderPostProcessorFullscreenRenderWidth));
                  colorSum[0] += renderData[index + 0];
                  colorSum[1] += renderData[index + 1];
                  colorSum[2] += renderData[index + 2];
                  colorSum[3] += renderData[index + 3];

                  colorAverage[0] = (byte) (colorSum[0] / boxRadius);
                  colorAverage[1] = (byte) (colorSum[1] / boxRadius);
                  colorAverage[2] = (byte) (colorSum[2] / boxRadius);
                  colorAverage[3] = (byte) (colorSum[3] / boxRadius);
                }

                index                         = (uint) (x + (y * renderPostProcessorFullscreenRenderWidth));
                blurHorizontalData[index + 0] = colorAverage[0];
                blurHorizontalData[index + 1] = colorAverage[1];
                blurHorizontalData[index + 2] = colorAverage[2];
                blurHorizontalData[index + 3] = colorAverage[3];
              }
            }

            Buffer.BlockCopy(renderData, 0, blurHorizontalData, 0, (int) renderPostProcessorFullscreenRenderHeight * (int) renderPostProcessorFullscreenRenderWidth * sizeof(byte) * 4);

            // ... ->> Vertical blurring
            for (uint x = 0u; x != renderPostProcessorFullscreenRenderWidth * sizeof(byte) * 4u; x += 4u * sizeof(byte)) {
              colorSum[0] = 0uL;
              colorSum[1] = 0uL;
              colorSum[2] = 0uL;
              colorSum[3] = 0uL;

              for (uint y = 0u; y != (boxRadius < renderPostProcessorFullscreenRenderHeight ? boxRadius : renderPostProcessorFullscreenRenderHeight) * sizeof(byte) * 4u; y += 4u * sizeof(byte)) {
                uint index = (uint) (x + (y * renderPostProcessorFullscreenRenderWidth));

                colorSum[0] += blurHorizontalData[index + 0];
                colorSum[1] += blurHorizontalData[index + 1];
                colorSum[2] += blurHorizontalData[index + 2];
                colorSum[3] += blurHorizontalData[index + 3];
              }

              colorAverage[0] = (byte) (colorSum[0] / boxRadius);
              colorAverage[1] = (byte) (colorSum[1] / boxRadius);
              colorAverage[2] = (byte) (colorSum[2] / boxRadius);
              colorAverage[3] = (byte) (colorSum[3] / boxRadius);

              for (uint y = 0u; y != renderPostProcessorFullscreenRenderHeight * sizeof(byte) * 4u; y += 4u * sizeof(byte)) {
                uint index = 0u;

                if (y >= (boxRadius / 2u) * sizeof(byte) * 4u && y + ((boxRadius / 2u) * sizeof(byte) * 4u) + (4u * sizeof(byte)) < renderPostProcessorFullscreenRenderHeight * sizeof(byte) * 4u) {
                  index        = (uint) (x + ((y - ((boxRadius / 2u) * sizeof(byte) * 4u) - (0u * 4u * sizeof(byte))) * renderPostProcessorFullscreenRenderWidth));
                  colorSum[0] -= blurHorizontalData[index + 0];
                  colorSum[1] -= blurHorizontalData[index + 1];
                  colorSum[2] -= blurHorizontalData[index + 2];
                  colorSum[3] -= blurHorizontalData[index + 3];

                  index        = (uint) (x + ((y + ((boxRadius / 2u) * sizeof(byte) * 4u) + (1u * 4u * sizeof(byte))) * renderPostProcessorFullscreenRenderWidth));
                  colorSum[0] += blurHorizontalData[index + 0];
                  colorSum[1] += blurHorizontalData[index + 1];
                  colorSum[2] += blurHorizontalData[index + 2];
                  colorSum[3] += blurHorizontalData[index + 3];

                  colorAverage[0] = (byte) (colorSum[0] / boxRadius);
                  colorAverage[1] = (byte) (colorSum[1] / boxRadius);
                  colorAverage[2] = (byte) (colorSum[2] / boxRadius);
                  colorAverage[3] = (byte) (colorSum[3] / boxRadius);
                }

                index                       = (uint) (x + (y * renderPostProcessorFullscreenRenderWidth));
                blurVerticalData[index + 0] = colorAverage[0];
                blurVerticalData[index + 1] = colorAverage[1];
                blurVerticalData[index + 2] = colorAverage[2];
                blurVerticalData[index + 3] = colorAverage[3];
              }
            }
          }

          Buffer.BlockCopy(blurData, 0, renderPostProcessorFullscreenRenderData, 0, (int) renderPostProcessorFullscreenRenderHeight * (int) renderPostProcessorFullscreenRenderWidth * sizeof(byte) * 4);
        }
      }
    }

    private static void RequestFullscreen() {
      renderResized          = true;
      windowBorderStyle      = window.FormBorderStyle;
      windowState            = window.WindowState;
      window.FormBorderStyle = FormBorderStyle.None;
      window.WindowState     = FormWindowState.Maximized;
    }

    private static void RequestPostProcessorFullscreenControllerImages() {
      if (null == renderControllerImages) renderControllerImages = new Image[] {null, null, null, null};
      if (null == renderControllerImages[0]) try { renderControllerImages[0] = Image.FromFile("assets/controls/keyboard.png"); } catch (SystemException) {}
      if (null == renderControllerImages[1]) try { renderControllerImages[1] = Image.FromFile("assets/controls/mouse.png");    } catch (SystemException) {}
      if (null == renderControllerImages[2]) try { renderControllerImages[2] = Image.FromFile("assets/controls/gamepad.png");  } catch (SystemException) {}
      if (null == renderControllerImages[3]) try { renderControllerImages[3] = Image.FromFile("assets/controls/touch.png");    } catch (SystemException) {}
    }

    /* ... */
    private static Point COORDINATES = new Point(0, 0);

    public static void Input(Keys? releasedKey) {
      switch (releasedKey) {
        case Keys.Escape: Terminate();                                                    break;
        case Keys.F11   : if (IsFullscreen()) ExitFullscreen(); else RequestFullscreen(); break;
      }

      foreach (Keys key in keys)
      switch (key) {
        case Keys.Down : case Keys.S: COORDINATES.Y = (int) (COORDINATES.Y + (window.Height * 0.05f)); break;
        case Keys.Left : case Keys.A: COORDINATES.X = (int) (COORDINATES.X - (window.Width  * 0.05f)); /*player.Rotation -= (float) Math.PI / 180.0f; Console.WriteLine("[^]: " + (player.Rotation * (180.0f / Math.PI)));*/ break;
        case Keys.Right: case Keys.D: COORDINATES.X = (int) (COORDINATES.X + (window.Width  * 0.05f)); /*player.Rotation += (float) Math.PI / 180.0f; Console.WriteLine("[^]: " + (player.Rotation * (180.0f / Math.PI)));*/ break;
        case Keys.Up   : case Keys.W: COORDINATES.Y = (int) (COORDINATES.Y - (window.Height * 0.05f)); break;
      }
    }

    public static void Render(object target, PaintEventArgs arguments) {
      Window   window         = (Window) target; // ->> Same as `Game::window`… ideally
      Graphics windowGraphics = arguments.Graphics;
      Size     windowSize     = window.GetComputedSize();
      TimeSpan timestamp      = TimeSpan.FromTicks(DateTime.Now.Ticks);
      bool     rerender       = renderDelta <= timestamp - renderTimestamp;
      Bitmap   render         = renders[rerender ? (renderIndex == 0u ? renders.Length : renderIndex) - 1u : renderIndex];
      Graphics renderGraphics = Graphics.FromImage(render);

      // ...
      renderGraphics.CompositingMode    = CompositingMode   .SourceOver;
      renderGraphics.CompositingQuality = CompositingQuality.AssumeLinear;
      renderGraphics.InterpolationMode  = InterpolationMode .NearestNeighbor;
      renderGraphics.PixelOffsetMode    = PixelOffsetMode   .Half;
      renderGraphics.SmoothingMode      = SmoothingMode     .AntiAlias;
      renderGraphics.TextRenderingHint  = TextRenderingHint .SystemDefault;

      windowGraphics.CompositingMode    = CompositingMode   .SourceCopy;
      windowGraphics.CompositingQuality = CompositingQuality.HighQuality;
      windowGraphics.InterpolationMode  = InterpolationMode .High;
      windowGraphics.PixelOffsetMode    = PixelOffsetMode   .HighQuality;
      windowGraphics.SmoothingMode      = SmoothingMode     .HighQuality;
      windowGraphics.TextRenderingHint  = TextRenderingHint .ClearTypeGridFit;

      if (rerender || renderResized) {
        float  rotation     = GetPlayersOverallRotation();
        PointF windowOrigin = new PointF(windowSize.Width / 2.0f, windowSize.Height / 2.0f);

        // ... ->> Clear previously drawn frame
        renderGraphics.Clear(window.BackColor);

        renderIndex     = (byte) ((renderIndex + 1u) % renders.Length);
        renderResized   = false;
        renderTimestamp = timestamp;

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
          renderGraphics.FillEllipse(
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
        renderGraphics.FillRectangle(new SolidBrush(Color.Indigo), 0, COORDINATES.Y,                          windowSize.Width, 50);
        renderGraphics.FillRectangle(new SolidBrush(Color.Indigo), 0, windowSize.Height - COORDINATES.Y - 50, windowSize.Width, 50);

        renderGraphics.FillRectangle(new SolidBrush(Color.Blue),   100,                           100,                          50, 50);
        renderGraphics.FillRectangle(new SolidBrush(Color.Green),  windowSize.Width / 2,          (windowSize.Height / 2) - 25, 50, 50);
        renderGraphics.FillRectangle(new SolidBrush(Color.Red),    (windowSize.Width / 2) - 50,   (windowSize.Height / 2) - 25, 50, 50);
        renderGraphics.FillRectangle(new SolidBrush(Color.Yellow), (windowSize.Width - 100) - 50, 100,                          50, 50);

        renderGraphics.FillRectangle(new SolidBrush(Color.White),  COORDINATES.X,                         COORDINATES.Y,                          30, 30);
        renderGraphics.FillRectangle(new SolidBrush(Color.White),  COORDINATES.X,                         windowSize.Height - COORDINATES.Y - 50, 30, 30);
        renderGraphics.FillRectangle(new SolidBrush(Color.Orange), windowSize.Width - COORDINATES.X - 30, COORDINATES.Y,                          30, 30);
        renderGraphics.FillRectangle(new SolidBrush(Color.Orange), windowSize.Width - COORDINATES.X - 30, windowSize.Height - COORDINATES.Y - 50, 30, 30);

        // ... ->> Draw fullscreen background
        do if (IsFullscreen()) {
          Bitmap          renderCopy                                   = null;
          Graphics        renderCopyGraphics                           = null;
          Bitmap          renderFullscreen                             = renders[renderIndex];
          Graphics        renderFullscreenGraphics                     = Graphics.FromImage(renderFullscreen);
          ImageAttributes renderPostProcessorFullscreenImageAttributes = new ImageAttributes();
          SizeF           renderPostProcessorFullscreenImageSize       = renderFullscreenImage.Size;
          Size            windowMaximizedSize                          = window.ClientSize;
          Int32           windowMaximizedBreadth                       = Math.Max(windowMaximizedSize.Height, windowMaximizedSize.Width);

          // ...
          renderFullscreenGraphics.CompositingMode   = renderGraphics.CompositingMode;
          renderFullscreenGraphics.InterpolationMode = renderGraphics.InterpolationMode;

          renderFullscreenGraphics.CompositingQuality = CompositingQuality.HighSpeed;
          renderFullscreenGraphics.PixelOffsetMode    = PixelOffsetMode   .HighSpeed;
          renderFullscreenGraphics.SmoothingMode      = SmoothingMode     .HighSpeed;
          renderFullscreenGraphics.TextRenderingHint  = TextRenderingHint .SingleBitPerPixel;

          // ... ->> Render asynchronously filtered gameplay graphics; see `PostProcessRender()`
          renderPostProcessorFullscreenRenderBitmapData = render.LockBits(new Rectangle(new Point(0, 0), render.Size), ImageLockMode.ReadOnly, PixelFormat.Format32bppPArgb);
          Marshal.Copy(renderPostProcessorFullscreenRenderBitmapData.Scan0, renderPostProcessorFullscreenRenderSubdata[0], 0, render.Height * render.Width * sizeof(byte) * 4);
          render.UnlockBits(renderPostProcessorFullscreenRenderBitmapData);
          renderPostProcessorFullscreenRenderBitmapData = null;

          // ... ->> Scale fullscreen background to fullscreen viewport and apply transparency matrix
          if (renderPostProcessorFullscreenImageSize.Height < renderPostProcessorFullscreenImageSize.Width) { renderPostProcessorFullscreenImageSize.Width  *= windowMaximizedBreadth / (float) renderPostProcessorFullscreenImageSize.Height; renderPostProcessorFullscreenImageSize.Height = windowMaximizedBreadth; }
          else                                                                                              { renderPostProcessorFullscreenImageSize.Height *= windowMaximizedBreadth / (float) renderPostProcessorFullscreenImageSize.Width;  renderPostProcessorFullscreenImageSize.Width  = windowMaximizedBreadth; }

          renderPostProcessorFullscreenImageAttributes.SetColorMatrix(new ColorMatrix(new Single[][] {
            new Single[] {1.00f, 0.00f, 0.00f, 0.00f, 0.00f},
            new Single[] {0.00f, 1.00f, 0.00f, 0.00f, 0.00f},
            new Single[] {0.00f, 0.00f, 1.00f, 0.00f, 0.00f},
            new Single[] {0.00f, 0.00f, 0.00f, 0.75f, 0.00f},
            new Single[] {0.00f, 0.00f, 0.00f, 0.00f, 1.00f},
          }), ColorMatrixFlag.Default, ColorAdjustType.Bitmap);

          // ... ->> Draw asynchronously filtered & translated gameplay graphics, gameplay graphics border, and semi-transparent fullscreen background image
          if (render == renderFullscreen) {
            renderCopy         = render.Clone(new Rectangle(0, 0, render.Width, render.Height), render.PixelFormat);
            renderCopyGraphics = Graphics.FromImage(renderCopy);

            renderCopyGraphics.CompositingMode    = CompositingMode.SourceCopy;
            renderCopyGraphics.CompositingQuality = CompositingQuality.HighSpeed;
            renderCopyGraphics.InterpolationMode  = InterpolationMode.NearestNeighbor;
            renderCopyGraphics.PixelOffsetMode    = PixelOffsetMode.None;
            renderCopyGraphics.SmoothingMode      = SmoothingMode.None;
            renderCopyGraphics.TextRenderingHint  = TextRenderingHint.SingleBitPerPixel;

            renderCopyGraphics.DrawImageUnscaled(renderFullscreen, 0, 0);
          }

          renderFullscreenGraphics.Clear(window.BackColor);
          renderFullscreenGraphics.DrawImage(renderPostProcessorFullscreenRender,
            (windowMaximizedBreadth - windowMaximizedSize.Width)  / -2.0f,
            (windowMaximizedBreadth - windowMaximizedSize.Height) / -2.0f,
            windowMaximizedBreadth * (renderPostProcessorFullscreenRender.Height < renderPostProcessorFullscreenRender.Width  ? renderPostProcessorFullscreenRender.Width  / (float) renderPostProcessorFullscreenRender.Height : 1.0f),
            windowMaximizedBreadth * (renderPostProcessorFullscreenRender.Width  < renderPostProcessorFullscreenRender.Height ? renderPostProcessorFullscreenRender.Height / (float) renderPostProcessorFullscreenRender.Width  : 1.0f)
          );
          renderFullscreenGraphics.DrawImageUnscaled(render != renderFullscreen ? render : renderCopy, (windowMaximizedSize.Width - windowSize.Width)       / 2, (windowMaximizedSize.Height - windowSize.Height)      / 2);
          renderFullscreenGraphics.DrawRectangle(renderFullscreenBorderPen, ((windowMaximizedSize.Width - windowSize.Width) / 2) + 1, ((windowMaximizedSize.Height - windowSize.Height) / 2) + 1, windowSize.Width - 1, windowSize.Height - 1);

          renderGraphics.DrawImageUnscaled(renderFullscreen, 0, 0);

          if (render == renderFullscreen) renderCopyGraphics.Dispose();
          if (render != renderFullscreen) renderFullscreenGraphics.Dispose();

          break;

          // windowGraphics.DrawImage    (renderFullscreenImage,  new Rectangle((windowMaximizedBreadth    - (int) renderPostProcessorFullscreenImageSize.Width) / 2, (windowMaximizedBreadth     - (int) renderPostProcessorFullscreenImageSize.Height) / 2, (int) renderPostProcessorFullscreenImageSize.Width, (int) renderPostProcessorFullscreenImageSize.Height), 0, 0, renderFullscreenImage.Width, renderFullscreenImage.Height, GraphicsUnit.Pixel, renderPostProcessorFullscreenImageAttributes);
          // windowGraphics.DrawImage    (render,                    (windowMaximizedSize.Width - windowSize.Width + 0) / 2, (windowMaximizedSize.Height - windowSize.Height + 0) / 2, windowSize.Width - 1, windowSize.Height - 1);
          // windowGraphics.DrawRectangle(renderFullscreenBorderPen, (windowMaximizedSize.Width - windowSize.Width + 1) / 2, (windowMaximizedSize.Height - windowSize.Height + 1) / 2, windowSize.Width - 1, windowSize.Height - 1);

          // ... ->> Draw controller prompts
          RequestPostProcessorFullscreenControllerImages();

          for (int index = renderControllerImages.Length; 0 != index; ) {
            Image controllerImage = renderControllerImages[--index];

            if (null != controllerImage) {
              uint       controllerMargin           = (uint) (windowMaximizedSize.Height * 0.050f);
              string     controllerName             = (new string[] {"KEYBOARD", "MOUSE", "GAMEPAD", "TOUCH"})[index];
              Font       controllerNameFont         = null == headingFontFamily ? new Font(headingFont.Name, 1.5000f) : new Font(headingFontFamily, 1.5000f);
              const uint controllerNameMargin       = 15u;
              Size       controllerNameSize         = TextRenderer.MeasureText(controllerName, controllerNameFont);
              string     controllerPrompt           = "Awaiting input…";
              Font       controllerPromptFont       = null == textFontFamily ? new Font(textFont.Name, 1.3125f) : new Font(textFontFamily, 1.3125f);
              const uint controllerPromptMargin     = 10u;
              Size       controllerPromptSize       = TextRenderer.MeasureText(controllerPrompt, controllerPromptFont);
              Bitmap     controllerRender           = null;
              BitmapData controllerRenderBitmapData = null;
              byte[]     controllerRenderData       = null;
              Size       controllerRenderSize       = controllerImage.Size;
              Int32      controllerSize             = Math.Max(50, Math.Min(windowMaximizedSize.Height, windowMaximizedSize.Width) / 10);
              uint       controllerX                = (uint) (windowMaximizedSize.Height * 0.050f);
              uint       controllerY                = (uint) (windowMaximizedSize.Height * 0.100f);

              // ... ->> Scale and re-color the controller render
              if (controllerRenderSize.Height < controllerRenderSize.Width) { controllerRenderSize.Width  = (int) (controllerRenderSize.Width  * (controllerSize / (float) controllerRenderSize.Height)); controllerRenderSize.Height = controllerSize; }
              else                                                          { controllerRenderSize.Height = (int) (controllerRenderSize.Height * (controllerSize / (float) controllerRenderSize.Width));  controllerRenderSize.Width  = controllerSize; }

              controllerRender           = new Bitmap(controllerImage, controllerRenderSize);
              controllerRenderBitmapData = controllerRender.LockBits(new Rectangle(new Point(0, 0), controllerRenderSize), ImageLockMode.ReadWrite, controllerRender.PixelFormat);
              controllerRenderData       = new byte[controllerRenderBitmapData.Height * Math.Abs(controllerRenderBitmapData.Stride)];

              Marshal.Copy(controllerRenderBitmapData.Scan0, controllerRenderData, 0, controllerRenderData.Length);

              for (uint subindex = 0u; subindex != controllerRenderData.Length; )
              switch (controllerRender.PixelFormat) {
                case PixelFormat.Alpha: case PixelFormat.Canonical: case PixelFormat.Format32bppArgb: case PixelFormat.Format32bppPArgb: if ((controllerRenderData[subindex + 3])                                      != 0u) controllerRenderData[subindex + 0] = controllerRenderData[subindex + 1] = controllerRenderData[subindex + 2] =                                                                                                                (byte) 0xFFu;                   subindex += 4u * sizeof(byte); break;
                case PixelFormat.Format64bppPArgb:                                                                                       if ((controllerRenderData[subindex + 6] | controllerRenderData[subindex + 7]) != 0u) controllerRenderData[subindex + 0] = controllerRenderData[subindex + 1] = controllerRenderData[subindex + 2] = controllerRenderData[subindex + 3] = controllerRenderData[subindex + 4] = controllerRenderData[subindex + 5] = (byte) 0xFFu; /* --> 0xFFFFu */ subindex += 8u * sizeof(byte); break;

                case PixelFormat.Format16bppArgb1555:                                      if (0x0001u         == (controllerRenderData[subindex + 0] | controllerRenderData[subindex + 1]) || 0x8000u == (controllerRenderData[subindex + 0] | controllerRenderData[subindex + 1]))                                                             controllerRenderData[subindex + 0] = controllerRenderData[subindex + 1] =                                                                                                                                                     (byte) 0xFFu; /* --> 0xFFFFu */ subindex += 2u * sizeof(byte); break;
                case PixelFormat.Format16bppGrayScale: case PixelFormat.Format16bppRgb565: if (0x0000u         == (controllerRenderData[subindex + 0] | controllerRenderData[subindex + 1]))                                                                                                                                                     controllerRenderData[subindex + 0] = controllerRenderData[subindex + 1] =                                                                                                                                                     (byte) 0xFFu; /* --> 0xFFFFu */ subindex += 2u * sizeof(byte); break;
                case PixelFormat.Format24bppRgb:                                           if (0x000000u       == (controllerRenderData[subindex + 0] | controllerRenderData[subindex + 1] | controllerRenderData[subindex + 2]))                                                                                                                controllerRenderData[subindex + 0] = controllerRenderData[subindex + 1] = controllerRenderData[subindex + 2] =                                                                                                                (byte) 0xFFu;                   subindex += 3u * sizeof(byte); break;
                case PixelFormat.Format32bppRgb:                                           if (0x000000u       == (controllerRenderData[subindex + 0] | controllerRenderData[subindex + 1] | controllerRenderData[subindex + 2]))                                                                                                                controllerRenderData[subindex + 0] = controllerRenderData[subindex + 1] = controllerRenderData[subindex + 2] =                                                                                                                (byte) 0xFFu;                   subindex += 4u * sizeof(byte); break;
                case PixelFormat.Format48bppRgb:                                           if (0x000000000000u == (controllerRenderData[subindex + 0] | controllerRenderData[subindex + 1] | controllerRenderData[subindex + 2] | controllerRenderData[subindex + 3] | controllerRenderData[subindex + 4] | controllerRenderData[subindex + 5])) controllerRenderData[subindex + 0] = controllerRenderData[subindex + 1] = controllerRenderData[subindex + 2] = controllerRenderData[subindex + 3] = controllerRenderData[subindex + 4] = controllerRenderData[subindex + 5] = (byte) 0xFFu; /* --> 0xFFFFu */ subindex += 6u * sizeof(byte); break;
                case PixelFormat.Format8bppIndexed:                                        if (0x00u           == (controllerRenderData[subindex + 0]))                                                                                                                                                                                          controllerRenderData[subindex + 0] =                                                                                                                                                                                          (byte) 0xFFu;                   subindex += 1u * sizeof(byte); break;
              }

              Marshal.Copy(controllerRenderData, 0, controllerRenderBitmapData.Scan0, controllerRenderData.Length);
              controllerRender.UnlockBits(controllerRenderBitmapData);

              if (0u != index % 2u) controllerX  = (uint) (windowMaximizedSize.Width - (controllerRenderSize.Width + controllerX));
              if (index > 1u)       controllerY += (uint) (controllerMargin + controllerNameMargin + controllerNameSize.Height + controllerRenderSize.Height);

              windowGraphics.DrawString(controllerName, controllerNameFont, new SolidBrush(Color.White), controllerX, controllerNameMargin + controllerY + controllerRenderSize.Height);
              windowGraphics.DrawImage(controllerRender, controllerX, controllerY, controllerRenderSize.Width, controllerRenderSize.Height);
            }
          }

          // ...
          if (renderFullscreenGraphics != renderGraphics)
          renderFullscreenGraphics.Dispose();
        } while (false);
      }

      // ...
      windowGraphics.DrawImageUnscaled(render, 0, 0);
      renderGraphics.Dispose();
    }

    public static void Terminate() {
      if (terminated) return;
      terminated = true;

      renderFullscreenBorderPen.Dispose();
      renderPostProcessorFullscreenRender.Dispose();
      renderPostProcessorFullscreenRenderAllocation.Free();
      window.Close();

      // ...
      if (Application.MessageLoop) Application.Exit();
      else Environment.Exit(0x00);
    }

    public static void Update(object target, EventArgs arguments) {
      float    rotation    = GetPlayersOverallRotation();
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
      TimeSpan     delta           = TimeSpan.FromTicks(TimeSpan.TicksPerSecond / 60L);
      DEVMODE      deviceMode      = new DEVMODE();
      uint         deviceFramerate = 60u;
      FontFamily[] fontFamilies    = {null, null};
      string[]     fontFilePaths   = {null, null};
      TimeSpan     timestamp       = TimeSpan.FromTicks(DateTime.Now.Ticks);
      Timer        updateTimer     = null;
      Screen       windowScreen    = null;
      Int32        windowSize      = 0;

      /* Update > ... */
      if (EnumerateDisplaySettings(null, DEVMODE.ENUM_CURRENT_SETTINGS, ref deviceMode)) {
        deviceFramerate = (uint) deviceMode.dmDisplayFrequency;
        delta           = 0u != deviceFramerate ? TimeSpan.FromTicks(TimeSpan.TicksPerSecond / (long) deviceFramerate) : delta;
      }

      difficulty                = 1.0f;
      fontFilePaths[0]          = "assets/fonts/riviera.otf";
      fontFilePaths[1]          = "assets/fonts/randy-gg.ttf";
      keys                      = new List<Keys>();
      player                    = new Infantry(new Point(0, 0));
      renderDelta               = delta;
      renderFullscreenBorderPen = new Pen(Color.FromArgb(255, 0xFF, 0xFF, 0xFF));
      renderPostProcessor       = new Thread(new ThreadStart(PostProcessRender));
      renderTimestamp           = timestamp;
      stars                     = new List<Star>();
      starsMaximumLength        = (ushort) 69u;
      starsSpawnCountDelta[0]   = (ushort) 1u;
      starsSpawnCountDelta[1]   = (ushort) 5u;
      starsSpawnDelta           = TimeSpan.FromTicks(TimeSpan.TicksPerMillisecond * 600L);
      starsSpawnTimestamp       = timestamp;
      state                     = State.MENU;
      updateDelta               = delta;
      updateTimer               = new Timer();
      updateTimestamp           = timestamp;
      window                    = new Window();
      windowBorderStyle         = window.FormBorderStyle;
      windowScreen              = Screen.FromControl(window);
      windowSize                = (Int32) (Math.Min(windowScreen.WorkingArea.Height, windowScreen.WorkingArea.Width) * 0.8f);
      windowState               = window.WindowState;

      for (int index = fontFamilies.Length | fontFilePaths.Length; 0 != index--; )
      try {
        byte[]                fontData       = File.ReadAllBytes(fontFilePaths[index]);
        PrivateFontCollection fontCollection = new PrivateFontCollection();
        GCHandle              fontAllocation = GCHandle.Alloc(fontData, GCHandleType.Pinned);

        // ...
        fontCollection.AddMemoryFont(fontAllocation.AddrOfPinnedObject(), fontData.Length);
        fontFamilies[index] = fontCollection.Families[0];

        fontAllocation.Free();
      } catch (SystemException) {}

      for (int index = renders.Length; 0 != index--; )
      renders[index] = new Bitmap(windowScreen.Bounds.Width, windowScreen.Bounds.Height, PixelFormat.Format32bppPArgb);

      foreach (string format in new string[] {"jpg", "jpeg", "jfif", "jpe", "jif", "jfi", "png", "bmp", "dib", "tiff", "tif", "gif"}) {
        try { renderFullscreenImage = Image.FromFile("assets/fullscreen." + format); break; }
        catch (FileNotFoundException) {} catch (OutOfMemoryException) { throw new OutOfMemoryException("Fullscreen background uses an invalid image format or unsupported pixel format"); }
      }

      headingFontFamily                             = fontFamilies[0];
      renderPostProcessorFullscreenRenderData       = new byte[windowScreen.Bounds.Height * windowScreen.Bounds.Width * sizeof(byte) * 4u];
      renderPostProcessorFullscreenRenderSubdata    = new byte[][] {new byte[renderPostProcessorFullscreenRenderData.Length], new byte[renderPostProcessorFullscreenRenderData.Length], new byte[renderPostProcessorFullscreenRenderData.Length]};
      renderPostProcessorFullscreenRenderAllocation = GCHandle.Alloc(renderPostProcessorFullscreenRenderData, GCHandleType.Pinned);
      renderPostProcessorFullscreenRender           = new Bitmap(windowScreen.Bounds.Width, windowScreen.Bounds.Height, windowScreen.Bounds.Width * sizeof(byte) * 4, PixelFormat.Format32bppPArgb, renderPostProcessorFullscreenRenderAllocation.AddrOfPinnedObject());
      textFontFamily                                = fontFamilies[1];

      /* Modification > ... */
      Application.Idle += new EventHandler(Update);

      renderPostProcessor.Priority = ThreadPriority.BelowNormal;

      updateTimer.Enabled  = true;
      updateTimer.Interval = (int) updateDelta.Value.TotalMilliseconds;
      updateTimer.Tick    += new EventHandler(Update);

      window.BackColor       = Color.Black;
      window.FormBorderStyle = FormBorderStyle.FixedSingle;
      window.MaximizeBox     = false;
      window.MinimizeBox     = false;
      window.KeyDown        += new KeyEventHandler(delegate(object target, KeyEventArgs arguments) { if (false == keys.Contains(arguments.KeyCode)) keys.Add(arguments.KeyCode); Input(null);                          });
      window.KeyUp          += new KeyEventHandler(delegate(object target, KeyEventArgs arguments) { int index = keys.IndexOf(arguments.KeyCode); if (index != -1) { keys.RemoveAt(index); Input(arguments.KeyCode); } });
      window.Paint          += new PaintEventHandler(Render);
      window.Size            = new Size(windowSize, windowSize);
      window.StartPosition   = FormStartPosition.CenterScreen;
      window.Text            = title;

      foreach (string format in new string[] {"ico", "png", "bmp", "dib"}) {
        try { window.Icon = new Icon("favicon." + format); break; }
        catch (FileNotFoundException) {}
      }

      /* ... */
      renderPostProcessor.Start();
      if (DialogResult.OK != window.ShowDialog()) Terminate();
    }
  }
}
