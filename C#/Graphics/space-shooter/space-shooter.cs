/* Import --> del space-shooter.exe & cls && csc /NoWarn:0162,0164 /optimize /out:space-shooter.exe /r:System.Collections.dll /r:System.Drawing.Primitives.dll /r:System.Runtime.dll /r:System.Threading.Thread.dll /r:System.Windows.Forms.dll /t:exe space-shooter.cs && space-shooter.exe & del space-shooter.exe */
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.Drawing.Text;
using System.IO;
using System.Reflection;
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
        public    const           uint   BaseHealth = 0u;
        protected readonly static Random Randomizer = new Random();

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
          this.Coordinates  = Point.Empty == coordinates ? new Point(0, 0) : coordinates;
          this.Health       = 0u;
          this.MaximumSpeed = 0.0f;
          this.Rotation     = (float) (Math.PI * Entity.Randomizer.NextDouble() * 2.0f);
          this.Size         = size;
          this.Speed        = 0.0f;
        }

        // ...
        public SizeF GetComputedSize(SizeF size) {
          return new SizeF(this.Size * size.Width, this.Size * size.Height);
        }
      };
        /* Item */
        private class Item : Entity {
          public Item(Point coordinates, float size) :
            base(coordinates, size)
          {}
        };
          /* Asteroid */
          private sealed class Asteroid : Item {
            new public const uint  BaseHealth = 75u;
            public     const float BaseSize   = 0.0300f;

            // ...
            public Asteroid(Point coordinates, float size) :
              base(coordinates, size)
            {
              this.Acceleration = 0.001f + (Asteroid.BaseSize / size);
              this.Health       = (uint) (Asteroid.BaseHealth * (size / Asteroid.BaseSize));
              this.MaximumSpeed = 0.050f;
            }

            public Asteroid(Point coordinates) :
              this(coordinates, Asteroid.BaseSize + (float) (Entity.Randomizer.NextDouble() * 0.1000f))
            {}
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
            public Bonus(Point coordinates, BonusType type) :
              base(coordinates, 0.0300f)
            {
              this.Acceleration = 0.01f;
              this.MaximumSpeed = 0.05f;
              this.Type         = type;
            }
          };

        /* Unit */
        private class Unit : Entity {
          public readonly static TimeSpan OffenseRate = TimeSpan.Zero;
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
          public Unit(Point coordinates, float size) :
            base(coordinates, size)
          {
            this.Clones           = new List<Unit>();
            this.Defense          = 0.0f;
            this.Graced           = false;
            this.Infectious       = false;
            this.Necro            = false;
            this.Offense          = 0u;
            this.OffenseTimestamp = TimeSpan.Zero;
            this.Render           = null;
            this.Shield           = 0u;
          }
        };
          /* Alien */
          private class Alien : Unit {
            public float LineOfSight; // ->> Frustum representing fog-of-war

            // ...
            public Alien(Point coordinates, float size) :
              base(coordinates, size)
            {
              this.LineOfSight = (float) Math.PI / 5.0f;
            }
          };
            /* Carrier ->> Poisonous vector */
            private class Carrier : Alien {
              new public const uint BaseHealth = 20u;

              new public readonly bool Infectious = true;

              // ...
              public Carrier(Point coordinates, byte stage) :
                base(coordinates, 0.03500f)
              {
                this.Health           = Carrier.BaseHealth;
                this.LineOfSight      = (float) Math.PI * 2.0f;
                this.Offense          = 3u;
                this.OffenseTimestamp = TimeSpan.FromTicks(TimeSpan.TicksPerMillisecond * 500L);
                this.Render           = Image.FromFile("assets/entities/aliens/carrier.png");
              }
            };

            /* Globule ->> Semi-solid melee parasite */
            private class Globule : Alien {
              new public const           uint     BaseHealth  = 30u;
              public     const           float    BaseSize    = 0.0400f;
              new public readonly static TimeSpan OffenseRate = TimeSpan.FromTicks(TimeSpan.TicksPerMillisecond * 800L);

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
              public Globule(Point coordinates, byte stage) :
                base(coordinates, 1.0f)
              {
                this.Defense             = 0.01f;
                this.DetachDodgeTendency = difficulty / 6.0f;
                this.Health              = Globule.BaseHealth;
                this.Offense             = 10u;
                this.Stage               = stage;
                this.ThrowTendency       = (float) Entity.Randomizer.NextDouble() * (difficulty / 3.5f);
              }

              public Globule(Point coordinates) :
                this(coordinates, (byte) Entity.Randomizer.Next(1, (int) difficulty))
              {}
            };

            /* Kamikaze */
            private class Kamikaze : Alien {
              new public const uint BaseHealth = 1u;

              new public readonly float Defense     = 0.0f;
              public readonly     float BurstRadius = 0.0675f;
              new public readonly uint  Shield      = 0u;

              // ...
              public Kamikaze(Point coordinates) :
                base(coordinates, 0.0400f)
              {
                this.Health  = Kamikaze.BaseHealth;
                this.Offense = 30u;
                this.Render  = Image.FromFile("assets/entities/aliens/kamikaze.png");
              }
            };

            /* Man o' War ->> Resistant medium-heavy solider */
            private class ManOWar : Alien {
              new public const           uint     BaseHealth  = 85u;
              new public readonly static TimeSpan OffenseRate = TimeSpan.FromTicks(TimeSpan.TicksPerMillisecond * 1650L);

              // ...
              public ManOWar(Point coordinates) :
                base(coordinates, 0.0600f)
              {
                this.Defense = 0.35f;
                this.Health  = ManOWar.BaseHealth;
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
            public readonly static TimeSpan DeployRate = TimeSpan.FromTicks(TimeSpan.TicksPerMillisecond * 900L);

            public TimeSpan   DeployTimestamp;
            public WeaponType Weapon;

            // ...
            public Ship(Point coordinates, float size) :
              base(coordinates, size)
            {
              this.DeployTimestamp = TimeSpan.Zero;
              this.Rotation        = 0.0f;
              this.Weapon          = Ship.WeaponType.STANDARD;
            }
          };
            /* Artillery ->> Heavy bruiser with a high health pool */
            private sealed class Artillery : Ship {
              new public const           uint     BaseHealth  = 250u;
              new public readonly static TimeSpan OffenseRate = TimeSpan.FromTicks(TimeSpan.TicksPerMillisecond * 200L);

              public Artillery(Point coordinates) :
                base(coordinates, 0.0675f)
              {
                this.Health  = Artillery.BaseHealth;
                this.Offense = 40u;
                this.Render  = Image.FromFile("assets/entities/ships/artillery.png");
              }
            };

            /* Infantry ->> Standard model fighter */
            private sealed class Infantry : Ship {
              new public const           uint     BaseHealth  = 100u;
              public     readonly static TimeSpan DashRate    = TimeSpan.FromTicks(TimeSpan.TicksPerMillisecond * 2000L);
              new public readonly static TimeSpan OffenseRate = TimeSpan.FromTicks(TimeSpan.TicksPerMillisecond * 10L);

              public TimeSpan DashTimestamp;

              // ...
              public Infantry(Point coordinates) :
                base(coordinates, 0.0500f)
              {
                this.DashTimestamp = TimeSpan.Zero;
                this.Health        = Infantry.BaseHealth;
                this.Offense       = 20u;
                this.Render        = Image.FromFile("assets/entities/ships/infantry.png");
              }
            };

            /* Rogue ->> Lightweight fighter with cloaking and espionage abilities */
            private sealed class Rogue : Ship {
              new public const           uint     BaseHealth  = 75u;
              new public readonly static TimeSpan OffenseRate = TimeSpan.Zero;
              public     readonly static TimeSpan StealthRate = TimeSpan.FromTicks(TimeSpan.TicksPerMillisecond * 2000L);

              public TimeSpan StealthTimestamp;

              // ...
              public Rogue(Point coordinates) :
                base(coordinates, 0.0400f)
              {
                this.Health           = Rogue.BaseHealth;
                this.Offense          = 10u;
                this.Render           = Image.FromFile("assets/entities/ships/rogue.png");
                this.StealthTimestamp = TimeSpan.Zero;
              }
            };

            /* Swarm ->> Mini-carriers focused on quantity and combat formation */
            private sealed class Swarm : Ship {
              public sealed class Drone : Ship {
                new public const           uint     BaseHealth  = 13u;
                new public readonly static TimeSpan OffenseRate = TimeSpan.FromTicks(TimeSpan.TicksPerMillisecond * 900L);

                public Drone(Point coordinates) :
                  base(coordinates, 0.0300f)
                {
                  this.Health = Drone.BaseHealth;
                  this.Render = Image.FromFile("assets/entities/ships/swarm-drone.png");
                }
              };

              // ...
              new public const           uint     BaseHealth  = 30u;
              new public readonly static TimeSpan OffenseRate = TimeSpan.FromTicks(TimeSpan.TicksPerMillisecond * 10L);
              public     readonly static TimeSpan SpawnRate   = TimeSpan.FromTicks(TimeSpan.TicksPerMillisecond * 5365L);

              public List<Drone> Carriers;
              public TimeSpan    SpawnTimestamp;

              // ...
              public Swarm(Point coordinates) :
                base(coordinates, 0.0350f)
              {
                this.Carriers       = new List<Drone>();
                this.Health         = Swarm.BaseHealth;
                this.Render         = Image.FromFile("assets/entities/ships/swarm.png");
                this.SpawnTimestamp = TimeSpan.Zero;

                this.Carriers.Add(new Drone(Point.Empty));
                this.Carriers.Add(new Drone(Point.Empty));
                this.Carriers.Add(new Drone(Point.Empty));
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
            this.coordinates = new PointF(0.0f, 0.0f); // ->> not `PointF.Empty`
            this.X           = x;
            this.Y           = y;
          }
        };

        // ...
        public static byte   MaximumSize = (byte) 5u;
        public static byte   MinimumSize = (byte) 1u;
        public static Random Randomizer  = new Random();

        // ...
        private float delta;
        private byte  opacity;
        private float speed;

        public Color           Color;
        public StarCoordinates DestinationCoordinates;
        public byte            Size;
        public StarCoordinates SourceCoordinates;
        public float           Delta   { get { return delta;   } set { delta   = value > 0.0f ? value < 1.0f ? value : 1.0f : 0.0f; } }
        public byte            Opacity { get { return opacity; } set { opacity = (byte) (value % 256u);                             } }
        public float           Speed   { get { return speed;   } set { speed   = value > 0.0f ? value < 1.0f ? value : 1.0f : 0.0f; } }

        // ...
        public Star() {
          byte size = (byte) Randomizer.Next(Star.MinimumSize, Star.MaximumSize);

          // ...
          this.Color                  = Star.Randomizer.NextDouble() > 0.1675f ? Color.White : new Color[] {Color.Cyan, Color.LightYellow, Color.Pink}[Star.Randomizer.Next(3)];
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
      };

      /* State */
      [Flags]
      private enum State : byte {
        CREDITS  = (byte) 0x01u,
        GAMEPLAY = (byte) 0x02u,
        HELP     = (byte) 0x04u,
        MENU     = (byte) 0x08u,
        SETTINGS = (byte) 0x10u,

        PAUSED     = (byte) 0x20u,
        TERMINATED = (byte) 0x40u
      };

      /* Window */
      public sealed class Window : Form {
        private FormBorderStyle borderStyle;
        private Screen          screen;
        private FormWindowState windowState;
        public  Size            ViewportSize { get; private set; }

        // ...
        public Window() :
          base()
        {
          this.ClientSizeChanged += new EventHandler(delegate(object target, EventArgs arguments) { this.UpdateViewportSize(this.ClientSize); });
          this.DoubleBuffered     = true;
          this.ResizeEnd         += new EventHandler(delegate(object target, EventArgs arguments) { this.screen = Screen.FromControl(target as Window); });
          this.screen             = Screen.FromControl(this);

          this.SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.DoubleBuffer | ControlStyles.OptimizedDoubleBuffer | ControlStyles.UserPaint, true);
          this.UpdateViewportSize(this.ClientSize);
        }

        // ...
        public void ExitFullscreen() {
          this.FormBorderStyle = this.borderStyle;
          this.WindowState     = this.windowState;

          this.UpdateViewportSize(this.ClientSize);
        }

        public bool IsFullscreen() {
          return FormBorderStyle.None == this.FormBorderStyle && FormWindowState.Maximized == this.WindowState;
        }

        protected override void OnPaintBackground(PaintEventArgs arguments) {
          /* Do nothing... ->> Prevent implicitly re-painting the background */
        }

        public void RequestFullscreen() {
          this.borderStyle  = this.FormBorderStyle;
          this.windowState  = this.WindowState;

          this.FormBorderStyle = FormBorderStyle.None;
          this.WindowState     = FormWindowState.Maximized;

          this.UpdateViewportSize(this.screen.Bounds.Size);
        }

        private void UpdateViewportSize(Size size) {
          int length = size.Height < size.Width ? size.Height : size.Width;
          this.ViewportSize = new Size(length, length);
        }
      };

    /* Global > ... */
    private static RectangleF[]    creditsPromptBounds;                           // ->> Game credits prompts bound
    private static State[]         creditsPromptStates;                           // ->> Game credits prompts game state
    private static string[]        creditsPromptTexts;                            // ->> Game credits prompts text
    private static bool            cursorActivated;                               // ->> Mouse pointer activation state by user
    private static RectangleF      cursorBound;                                   // ->> Mouse pointer bounds in game window --- UPDATE (Lapys) -> Normalize for window viewport, instead
    private static Brush           cursorBrush;                                   // ->> Mouse pointer fill
    private static Pen             cursorPen;                                     // ->> Mouse pointer secondary fill
    private static bool            cursorVisibility;                              // ->> Mouse pointer visibility
    private static bool            cursorWithinWindow;                            // ->> Mouse pointer intersection with game window
    private static float           difficulty;                                    // ->> Stats. calculator
    private static ulong           focusIndex;                                    // ->> UI focus index
    private static bool            focusIndexed;                                  // ->> UI focus is active
    private static Font            headingFont;                                   // ->> Game heading UI fallback font
    private static FontFamily      headingFontFamily;                             // ->> Game heading UI font face
    private static RectangleF[]    helpPromptBounds;                              // ->> Game help prompts bound
    private static State[]         helpPromptStates;                              // ->> Game help prompts game state
    private static string[]        helpPromptTexts;                               // ->> Game help prompts text
    private static List<Keys>      keys;                                          // ->> Keys currently currently activated by user
    private static string          menuFooter;                                    // ->> Game menu footer text
    private static RectangleF[]    menuPromptBounds;                              // ->> Game menu prompts bound
    private static State[]         menuPromptStates;                              // ->> Game menu prompts game state
    private static string[]        menuPromptTexts;                               // ->> Game menu prompts text
    private static Brush           promptBrush;                                   // ->> Game prompts fill
    private static Brush           promptFontBrush;                               // ->> Game prompts font fill
    private static Brush           promptSelectionBrush;                          // ->> Game prompts selection fill
    private static Brush           renderControllerIconBrush;                     // ->> Controller UI fill
    private static Pen             renderControllerIconPen;                       // ->> Controller UI secondary fill
    private static Image[]         renderControllerIcons;                         // ->> Controller UI image icons
    private static Brush           renderControllerPromptBrush;                   // ->> Controller UI prompt fill
    private static Pen             renderControllerPromptPen;                     // ->> Controller UI prompt secondary fill
    private static Brush           renderControllerTitleBrush;                    // ->> Controller UI title fill
    private static Pen             renderControllerTitlePen;                      // ->> Controller UI title secondary fill
    private static TimeSpan        renderDelta;                                   // ->> Time between each `Render(…)`
    private static Image           renderFullscreenImage;                         // ->> Fullscreen graphic background image
    private static Pen             renderFullscreenPen;                           // ->> Fullscreen graphic border
    private static byte            renderIndex;                                   // ->> Multiple-buffering index
    private static Thread          renderPostProcessor;                           // ->> Background processor to handle strenuous synchronous image effects processing & filtering
    private static Bitmap          renderPostProcessorFullscreenRender;           // ->> Fullscreen graphic
    private static GCHandle        renderPostProcessorFullscreenRenderAllocation; // ->> Fullscreen graphic allocated render data
    private static BitmapData      renderPostProcessorFullscreenRenderBitmapData; // ->> Fullscreen graphic `BitmapData` for bit-block transferring from the main render
    private static byte[]          renderPostProcessorFullscreenRenderData;       // ->> Fullscreen graphic render data ie: pixels, …
    private static byte[][]        renderPostProcessorFullscreenRenderSubdata;    // ->> Fullscreen graphic render subdata (for post-processing)
    private static Bitmap[]        renders;                                       // ->> Multiple-buffering rendering for gameplay graphics (at least one required)
    private static TimeSpan        renderTimestamp;                               // ->> Time till next `Render(…)`
    private static RectangleF[]    settingsPromptBounds;                          // ->> Game settings prompts bound
    private static State[]         settingsPromptStates;                          // ->> Game settings prompts game state
    private static string[]        settingsPromptTexts;                           // ->> Game settings prompts text
    private static List<Star>      stars;                                         // ->> Stars trailing in the background
    private static ushort          starsMaximumLength;                            // ->> Stars total
    private static ushort[]        starsSpawnCountDelta;                          // ->> Stars spawned at a time
    private static TimeSpan        starsSpawnDelta;                               // ->> Time between each star spawn
    private static TimeSpan        starsSpawnTimestamp;                           // ->> Time till next star spawn
    private static State           state;                                         // ->> Game state for menus, options, etc…
    private static Font            textFont;                                      // ->> Game text UI fallback font
    private static FontFamily      textFontFamily;                                // ->> Game text UI font face
    private static string          title;                                         // ->> Game title
    private static TimeSpan        updateDelta;                                   // ->> Time between each `Update(…)`
    private static TimeSpan        updateTimestamp;                               // ->> Time till next `Update(…)`
    private static Window          window;                                        // ->> Game window

    private static Unit[] players = {
      null, // ->> Keyboard ⌨
      null, // ->> Mouse    🖱️
      null, // ->> Gamepad  🎮
      null  // ->> Touch    👆
    };

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

    private static float GetFontSizeInPixels(Font font, Graphics graphics) {
      return font.SizeInPoints * (graphics.DpiY / 72.0f);
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

    private static void PostProcessRender() {
      /* ... ->> Post-process fullscreen background: Gaussian blur */
      while (0x00u == (byte) (state & State.TERMINATED))
      if (null != renderPostProcessorFullscreenRenderBitmapData) {
        int        renderPostProcessorFullscreenRenderWidth  = renderPostProcessorFullscreenRender.Width;  // ->> Ideally `renderPostProcessorFullscreenRender` is still unused at this point
        int        renderPostProcessorFullscreenRenderHeight = renderPostProcessorFullscreenRender.Height; // ->> Ideally `renderPostProcessorFullscreenRender` is still unused at this point
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
          uint   boxRadius  = (uint) blurFilterWidth + (0u == blurFilterWidth % 2u ? 1u : 0u) + (count < blurMedian ? 0u : 2u);
          byte[] renderData = 0u == count ? renderPostProcessorFullscreenRenderSubdata[0] : blurData;

          // ... --- TODO (Lapys) -> Fix horizontal blurring
          blurHorizontalData = renderData;
          goto VerticalBoxBlur;

          // ...
          HorizontalBoxBlur:
          for (uint y = 0u; y != renderPostProcessorFullscreenRenderHeight * sizeof(byte) * 4u; y += 4u * sizeof(byte)) {
            colorSum[0] = 0uL;
            colorSum[1] = 0uL;
            colorSum[2] = 0uL;
            colorSum[3] = 0uL;

            for (uint x = 0u; x != (boxRadius < renderPostProcessorFullscreenRenderWidth ? boxRadius : (uint) renderPostProcessorFullscreenRenderWidth) * sizeof(byte) * 4u; x += 4u * sizeof(byte)) {
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

          VerticalBoxBlur:
          for (uint x = 0u; x != renderPostProcessorFullscreenRenderWidth * sizeof(byte) * 4u; x += 4u * sizeof(byte)) {
            colorSum[0] = 0uL;
            colorSum[1] = 0uL;
            colorSum[2] = 0uL;
            colorSum[3] = 0uL;

            for (uint y = 0u; y != (boxRadius < renderPostProcessorFullscreenRenderHeight ? boxRadius : (uint) renderPostProcessorFullscreenRenderHeight) * sizeof(byte) * 4u; y += 4u * sizeof(byte)) {
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

        Buffer.BlockCopy(blurData, 0, renderPostProcessorFullscreenRenderData, 0, renderPostProcessorFullscreenRenderHeight * renderPostProcessorFullscreenRenderWidth * sizeof(byte) * 4);
      }
    }

    private static void RequestControllerIcons() {
      if (null == renderControllerIcons[0]) try { renderControllerIcons[0] = Image.FromFile("assets/controls/keyboard.png"); } catch (SystemException) {}
      if (null == renderControllerIcons[1]) try { renderControllerIcons[1] = Image.FromFile("assets/controls/mouse.png");    } catch (SystemException) {}
      if (null == renderControllerIcons[2]) try { renderControllerIcons[2] = Image.FromFile("assets/controls/gamepad.png");  } catch (SystemException) {}
      if (null == renderControllerIcons[3]) try { renderControllerIcons[3] = Image.FromFile("assets/controls/touch.png");    } catch (SystemException) {}
    }

    private static void ResetFocusIndex() {
      focusIndex   = UInt64.MaxValue;
      focusIndexed = false;
    }

    private static void SetGameState(State gameState) {
      if (0x00u != (byte) (gameState & State.PAUSED))     state |= State.PAUSED;
      if (0x00u != (byte) (gameState & State.TERMINATED)) Terminate();

      foreach (State value in Enum.GetValues(typeof(State)))
      if (0x00u != (byte) (gameState & value) && 0x00u == (byte) (state & value)) {
        ResetFocusIndex();
        state = value | (state & State.PAUSED) | (state & State.TERMINATED);
      }
    }

    /* ... */
    public static void Input(Keys? releasedKey) {
      State        selectedPromptState = (State) (byte) 0x00u;
      State[]      promptStates        = {selectedPromptState};
      RectangleF[] promptBounds        = {RectangleF.Empty};

      // ...
      if (0x00u != (byte) (state & State.CREDITS))  { promptBounds = creditsPromptBounds;  promptStates = creditsPromptStates;  }
      if (0x00u != (byte) (state & State.HELP))     { promptBounds = helpPromptBounds;     promptStates = helpPromptStates;     }
      if (0x00u != (byte) (state & State.MENU))     { promptBounds = menuPromptBounds;     promptStates = menuPromptStates;     }
      if (0x00u != (byte) (state & State.SETTINGS)) { promptBounds = settingsPromptBounds; promptStates = settingsPromptStates; }

      // ... ->> Key input
      switch (releasedKey) {
        // ... ->> Select UI prompt
        case Keys.Enter: {
          for (int index = promptBounds.Length; 0 != index--; )
          if (cursorBound.IntersectsWith(promptBounds[index])) {
            selectedPromptState = promptStates[index];
            break;
          }

          if (focusIndexed && (State) (byte) 0x00u == selectedPromptState)
          selectedPromptState = promptStates[focusIndex % (ulong) promptStates.Length];
        } break;

        // ... ->> Quit the game
        case Keys.Escape: {
          if (0x00u != (byte) (state & State.MENU))       Terminate();
          if (0x00u == (byte) (state & State.TERMINATED)) SetGameState(State.MENU);
        } return;

        // ... ->> Toggle game fullscreen
        case Keys.F11: {
          if (window.IsFullscreen()) window.ExitFullscreen();
          else window.RequestFullscreen();
        } break;

        // ... ->> Switch focused UI prompt
        case Keys.Tab: {
          ++focusIndex;
          focusIndexed = true;

          foreach (Keys key in keys)
          if (Keys.LShiftKey == key || Keys.RShiftKey == key || Keys.ShiftKey == key) {
            focusIndex -= 2uL;
            break;
          }
        } break;

        // ... ->> Keyboard player fire
        case Keys.OemPeriod: case Keys.X: break;
      }

      foreach (Keys key in keys)
      switch (key) {
        // ... ->> Keyboard player movement
        case Keys.Down : case Keys.S: break;
        case Keys.Left : case Keys.A: break;
        case Keys.Right: case Keys.D: break;
        case Keys.Up   : case Keys.W: break;

        // ... ->> Keyboard player fire
        case Keys.OemPeriod: case Keys.X: break;
      }

      // ... ->> Mouse input
      if (cursorActivated) {
        // ... ->> Select UI prompt
        for (int index = promptBounds.Length; 0 != index--; )
        if (cursorBound.IntersectsWith(promptBounds[index])) {
          selectedPromptState = promptStates[index];
          break;
        }
      }

      // ...
      if ((State) (byte) 0x00u != selectedPromptState)
      SetGameState(selectedPromptState);
    }

    public static void Render(object target, PaintEventArgs arguments) {
      Window   window             = target as Window;
      Size     windowViewportSize = window.ViewportSize;
      TimeSpan timestamp          = TimeSpan.FromTicks(DateTime.Now.Ticks);
      bool     rerender           = renderDelta <= timestamp - renderTimestamp;
      Bitmap   render             = renders[rerender ? (renderIndex == 0u ? renders.Length : renderIndex) - 1u : renderIndex];
      Graphics renderGraphics     = Graphics.FromImage(render);
      Graphics graphics           = arguments.Graphics;

      // ...
      graphics.CompositingMode    = CompositingMode   .SourceCopy;
      graphics.CompositingQuality = CompositingQuality.HighQuality;
      graphics.InterpolationMode  = InterpolationMode .High;
      graphics.PixelOffsetMode    = PixelOffsetMode   .HighQuality;
      graphics.SmoothingMode      = SmoothingMode     .HighQuality;
      graphics.TextRenderingHint  = TextRenderingHint .ClearTypeGridFit;

      renderGraphics.CompositingMode    = CompositingMode   .SourceOver;
      renderGraphics.CompositingQuality = CompositingQuality.AssumeLinear;
      renderGraphics.InterpolationMode  = InterpolationMode .NearestNeighbor;
      renderGraphics.PixelOffsetMode    = PixelOffsetMode   .Half;
      renderGraphics.SmoothingMode      = SmoothingMode     .AntiAlias;
      renderGraphics.TextRenderingHint  = TextRenderingHint .SystemDefault;

      if (rerender) {
        PointF      windowViewportOrigin          = new PointF(windowViewportSize.Width / 2.0f, windowViewportSize.Height / 2.0f);
        float       starsRotation                 = GetPlayersOverallRotation();
        float       starsRotationSine             = (float) Math.Sin(starsRotation);
        float       starsRotationCosine           = (float) Math.Cos(starsRotation);
        SizeF       promptsSize                   = new SizeF(windowViewportSize.Height * 0.8f, windowViewportSize.Width * 0.9f);
        const float promptsTextMinimumFontSize    = 8.0f;
        float       promptsTextFontSize           = Math.Min(promptsSize.Height, promptsSize.Width) * (0.1f / 3.5f);
        const float promptsHeadingMinimumFontSize = 10.0f;
        float       promptsHeadingFontSize        = Math.Min(promptsSize.Height, promptsSize.Width) * (0.1f / 3.0f);
        PointF      promptsCoordinates            = new PointF((windowViewportSize.Width - promptsSize.Width) / 2.0f, (windowViewportSize.Height - promptsSize.Height) / 2.0f);
        Font        promptTextFont                = null == textFontFamily    ? new Font(textFont   .Name, promptsTextFontSize)    : new Font(textFontFamily,    promptsTextFontSize);
        Font        promptHeadingFont             = null == headingFontFamily ? new Font(headingFont.Name, promptsHeadingFontSize) : new Font(headingFontFamily, promptsHeadingFontSize);

        // ... ->> Clear previously drawn frame
        renderGraphics.Clear(window.BackColor);

        renderIndex     = (byte) ((renderIndex + 1u) % renders.Length);
        renderTimestamp = timestamp;

        // ... ->> Draw stars
        foreach (Star star in stars) {
          Brush  starBrush                  = new SolidBrush(Color.FromArgb((int) (star.Opacity * (star.Delta > 0.5f ? 2.0f - (star.Delta * 2.0f) : (star.Delta * 2.0f))), star.Color)) as Brush;
          PointF starDestinationCoordinates = (PointF) star.GetComputedDestinationCoordinates(windowViewportSize);
          float  starRotationCull           = 0.0f;
          PointF starSourceCoordinates      = (PointF) star.GetComputedSourceCoordinates(windowViewportSize);

          // ...
          do {
            if (starsRotation >= Math.PI * 0.0f && starsRotation <= Math.PI * 0.5f) { starRotationCull = (float) ((Math.PI * 0.0f) + (Math.PI / 4.0f)) - starsRotation; break; }
            if (starsRotation >= Math.PI * 0.5f && starsRotation <= Math.PI * 1.0f) { starRotationCull = (float) ((Math.PI * 0.5f) + (Math.PI / 4.0f)) - starsRotation; break; }
            if (starsRotation >= Math.PI * 1.0f && starsRotation <= Math.PI * 1.5f) { starRotationCull = (float) ((Math.PI * 1.0f) + (Math.PI / 4.0f)) - starsRotation; break; }
            if (starsRotation >= Math.PI * 1.5f && starsRotation <= Math.PI * 2.0f) { starRotationCull = (float) ((Math.PI * 1.5f) + (Math.PI / 4.0f)) - starsRotation; break; }
          } while (false);

          starRotationCull  = 1.0f - (float) (Math.Abs(starRotationCull) / Math.PI / 4.0f);                                                                                                                                                                    // ->> Scale based on degree of rotation (45° angles are the most scaled)
          starRotationCull *= 1.0f - (float) (Math.Sqrt(((windowViewportSize.Width * windowViewportSize.Width) / 4.0f) - ((starSourceCoordinates.X % windowViewportOrigin.X) * (starSourceCoordinates.X % windowViewportOrigin.X))) / windowViewportOrigin.X); // ->> Scale based on center of rotation --- TODO (Lapys) -> Still not perfect
          starRotationCull *= 0.0f + (float) (Math.Sqrt(((windowViewportSize.Width * windowViewportSize.Width))        + ((windowViewportSize.Height                         * windowViewportSize.Height))));                                                  // ->> Convert to in-world coordinates

          starDestinationCoordinates.Y += starRotationCull;
          starDestinationCoordinates    = new PointF(
            windowViewportOrigin.X + (starsRotationCosine * (starDestinationCoordinates.X - windowViewportOrigin.X)) - (starsRotationSine   * (starDestinationCoordinates.Y - windowViewportOrigin.Y)),
            windowViewportOrigin.Y + (starsRotationSine   * (starDestinationCoordinates.X - windowViewportOrigin.X)) + (starsRotationCosine * (starDestinationCoordinates.Y - windowViewportOrigin.Y))
          );

          starSourceCoordinates.Y -= starRotationCull;
          starSourceCoordinates    = new PointF(
            windowViewportOrigin.X + (starsRotationCosine * (starSourceCoordinates.X - windowViewportOrigin.X)) - (starsRotationSine   * (starSourceCoordinates.Y - windowViewportOrigin.Y)),
            windowViewportOrigin.Y + (starsRotationSine   * (starSourceCoordinates.X - windowViewportOrigin.X)) + (starsRotationCosine * (starSourceCoordinates.Y - windowViewportOrigin.Y))
          );

          // ...
          renderGraphics.FillEllipse(
            starBrush,
            starSourceCoordinates.X + (star.Delta * (starDestinationCoordinates.X - starSourceCoordinates.X)),
            starSourceCoordinates.Y + (star.Delta * (starDestinationCoordinates.Y - starSourceCoordinates.Y)),
            star.Size,
            star.Size
          );

          starBrush.Dispose();
        }

        // ...
        if (0x00u != (byte) (state & (State.CREDITS | State.HELP | State.SETTINGS))) {
          RectangleF backPromptBound        = RectangleF.Empty;
          Font       backPromptFont         = promptHeadingFont;
          bool       backPromptHovered      = false;
          bool       backPromptSelected     = false;
          string     backPromptText         = String.Empty;
          SizeF      backPromptTextSize     = SizeF .Empty;
          Font       messageDescriptionFont = promptTextFont;
          Font       messageHeadingFont     = promptHeadingFont;
          bool       messageIsHeading       = true;
          string[]   messages               = {};
          float      messagesHeight         = 0.0f;
          float      messagesWidth          = 0.0f;
          float      messagesY              = 0.0f;

          // ...
          if (0x00u != (byte) (state & State.CREDITS)) {
            backPromptSelected = focusIndexed && 0uL == focusIndex % (ulong) creditsPromptBounds.Length;
            backPromptText     = creditsPromptTexts[0];
            messages           = new string[] {
              "Gameplay",      "Lapys",
              "Graphics",      "Lapys",
              "Sound Effects", "Lapys",
              "Music Tracks",  "Phyrnna"
            };
          }

          if (0x00u != (byte) (state & State.HELP)) {
            backPromptSelected = focusIndexed && 0uL == focusIndex % (ulong) helpPromptBounds.Length;
            backPromptText     = helpPromptTexts[0];
            messages           = new string[] {
              "  ¯\\_(ツ)_/¯", "Git gud, lmao\n\n",
              "\u2328 KEYBOARD",          "Standard arrow key convention and \u201CWASD\u201D PC controls;\n  \u2022 \u2018W\u2019 \u2191 to accelerate,\n  \u2022 \u2018S\u2019 \u2193 to reverse,\n  \u2022 \u2018A\u2019 \u2190 to strafe left,\n  \u2022 \u2018D\u2019 \u2192 to strafe right,\n  \u2022 \u2018Spacebar\u2019 to fire",
              "\uD83D\uDDB1\uFE0F MOUSE", "Computer mouse movement and control;\n  Player follows where your cursor goes\n  \u2014 click to blast away",
              "\uD83C\uDFAE GAMEPAD",     "\u2026",
              "\u270E TOUCH",             "\u2026"
            };
          }

          if (0x00u != (byte) (state & State.SETTINGS)) {
            backPromptSelected = focusIndexed && 0uL == focusIndex % (ulong) settingsPromptBounds.Length;
            backPromptText     = settingsPromptTexts[0];
          }

          // ...
          while (true) {
            messageIsHeading = true;
            messagesHeight   = 0.0f;
            messagesWidth    = 0.0f;

            foreach (string message in messages) {
              Font  messageFont = messageIsHeading ? messageHeadingFont : messageDescriptionFont;
              SizeF messageSize = renderGraphics.MeasureString(message, messageFont, promptsSize);

              // ...
              messagesWidth    = messagesWidth > messageSize.Width ? messagesWidth : messageSize.Width;
              messagesHeight  += messageSize.Height;
              messageIsHeading = false == messageIsHeading;
            }

            messagesY = promptsCoordinates.Y + ((promptsSize.Height - messagesHeight) / 2.0f);

            if (promptsHeadingMinimumFontSize < messageHeadingFont.Size && promptsTextMinimumFontSize < messageDescriptionFont.Size && (promptsSize.Height < messagesHeight || promptsSize.Width < messagesWidth)) {
              messageDescriptionFont = new Font(messageDescriptionFont.FontFamily, messageDescriptionFont.Size - (GetFontSizeInPixels(messageDescriptionFont, renderGraphics) / messageDescriptionFont.Size));
              messageHeadingFont     = new Font(messageHeadingFont    .FontFamily, messageHeadingFont    .Size - (GetFontSizeInPixels(messageHeadingFont,     renderGraphics) / messageHeadingFont    .Size));

              continue;
            }

            break;
          }

          messageIsHeading = true;
          renderGraphics.DrawRectangle(Pens.White, promptsCoordinates.X, promptsCoordinates.Y, promptsSize.Width, promptsSize.Height);
          renderGraphics.DrawRectangle(Pens.Red,   promptsCoordinates.X, messagesY, messagesWidth, messagesHeight);

          foreach (string message in messages) {
            Font         messageFont         = messageIsHeading ? messageHeadingFont : messageDescriptionFont;
            GraphicsPath messageGraphicsPath = new GraphicsPath();
            SizeF        messageSize         = renderGraphics.MeasureString(message, messageFont, promptsSize);

            // ...
            messageGraphicsPath.AddString(message, messageFont.FontFamily, (Int32) messageFont.Style, GetFontSizeInPixels(messageFont, renderGraphics), new PointF(promptsCoordinates.X, messagesY), new StringFormat());
            renderGraphics.DrawPath(Pens.Black,    messageGraphicsPath);
            renderGraphics.FillPath(Brushes.White, messageGraphicsPath);

            messageIsHeading = false == messageIsHeading;
            messagesY       += messageSize.Height;
          }

          // ...
          backPromptTextSize = renderGraphics.MeasureString(backPromptText, backPromptFont);
          backPromptBound    = new RectangleF(windowViewportSize.Width * 0.05f, windowViewportSize.Height * 0.05f, backPromptTextSize.Width * 1.5f, backPromptTextSize.Height * 1.5f);
          backPromptHovered  = cursorBound.IntersectsWith(backPromptBound);
          backPromptSelected = backPromptHovered || backPromptSelected;

          if (backPromptHovered) ResetFocusIndex();
          if (0x00u != (byte) (state & State.CREDITS))  creditsPromptBounds [0] = backPromptBound;
          if (0x00u != (byte) (state & State.HELP))     helpPromptBounds    [0] = backPromptBound;
          if (0x00u != (byte) (state & State.SETTINGS)) settingsPromptBounds[0] = backPromptBound;

          renderGraphics.FillRectangle(backPromptSelected ? promptSelectionBrush : promptBrush, backPromptBound);
          renderGraphics.DrawString(backPromptText, backPromptFont, promptFontBrush, backPromptBound.Left + ((backPromptBound.Width - backPromptTextSize.Width) / 2.0f), backPromptBound.Top + ((backPromptBound.Height - backPromptTextSize.Height) / 2.0f));
        }

        if (0x00u != (byte) (state & State.GAMEPLAY)) {}

        if (0x00u != (byte) (state & State.MENU)) {
          Font  menuFooterFont          = new Font(promptTextFont.FontFamily, (promptTextFont.Size * 2.0f) / 3.0f);
          SizeF menuFooterSize          = renderGraphics.MeasureString(menuFooter, menuFooterFont);
          Font  menuPromptFont          = promptTextFont;
          float menuPromptMarginY       = 0.0f;
          SizeF menuPromptSelectionSize = new SizeF(windowViewportSize.Width * 0.715f, 0.0f);
          SizeF menuPromptSize          = new SizeF(windowViewportSize.Width * 0.650f, 0.0f);
          float menuPromptsY            = 0.0f;

          // ...
          while (true) {
            float       menuPromptFontSize     = GetFontSizeInPixels(menuPromptFont, renderGraphics);
            const float menuPromptHeightRatio  = 3.65f;
            const float menuPromptMarginYRatio = 1.75f;

            // ...
            menuPromptMarginY              = menuPromptFontSize * menuPromptMarginYRatio;
            menuPromptSelectionSize.Height = menuPromptFontSize * menuPromptHeightRatio;
            menuPromptSize.Height          = menuPromptFontSize * menuPromptHeightRatio;
            menuPromptsY                   = (windowViewportSize.Height - ((menuPromptMarginY * (menuPromptTexts.Length - 1)) + (menuPromptSize.Height * (menuPromptTexts.Length - 0)))) / 2.0f;

            if (promptsTextMinimumFontSize < menuPromptFont.Size && promptsSize.Height < (menuPromptMarginY * (menuPromptTexts.Length - 1)) + (menuPromptSize.Height * (menuPromptTexts.Length - 0))) {
              menuPromptFont = new Font(menuPromptFont.FontFamily, menuPromptFont.Size - (menuPromptFontSize / menuPromptFont.Size));
              continue;
            }

            break;
          }

          for (int index = menuPromptBounds.Length | menuPromptTexts.Length; 0 != index--; ) {
            RectangleF menuPromptBound          = new RectangleF(new PointF((windowViewportSize.Width - menuPromptSize.Width) / 2.0f, menuPromptsY + (index * (menuPromptMarginY + menuPromptSize.Height))), menuPromptSize);
            bool       menuPromptHovered        = cursorBound.IntersectsWith(menuPromptBound);
            bool       menuPromptSelected       = menuPromptHovered || (focusIndexed && (ulong) index == focusIndex % (ulong) menuPromptBounds.Length);
            RectangleF menuPromptSelectionBound = new RectangleF(new PointF((windowViewportSize.Width - menuPromptSelectionSize.Width) / 2.0f, menuPromptsY + (index * (menuPromptMarginY + menuPromptSelectionSize.Height))), menuPromptSelectionSize);
            string     menuPromptText           = menuPromptTexts[index];
            SizeF      menuPromptTextSize       = renderGraphics.MeasureString(menuPromptText, menuPromptFont);

            // ...
            menuPromptBounds[index] = menuPromptBound;
            menuPromptBound         = menuPromptSelected ? menuPromptSelectionBound : menuPromptBound;
            if (menuPromptHovered) ResetFocusIndex();

            renderGraphics.FillRectangle(menuPromptSelected ? menuPromptText == "EXIT" ? Brushes.DarkRed : promptSelectionBrush : promptBrush, menuPromptBound);
            renderGraphics.DrawString(menuPromptText, menuPromptFont, promptFontBrush, menuPromptBound.Left + ((menuPromptBound.Width - menuPromptTextSize.Width) / 2.0f), menuPromptBound.Top + ((menuPromptBound.Height - menuPromptTextSize.Height) / 2.0f));
          }

          renderGraphics.DrawString(menuFooter, menuFooterFont, Brushes.White, (windowViewportSize.Width - menuFooterSize.Width) / 2.0f, windowViewportSize.Height - (menuFooterSize.Height * 1.5f));
        }

        // ... ->> Draw cursor (avoid drawing over system cursor)
        if (false == cursorBound.IsEmpty && cursorWithinWindow) {
          renderGraphics.FillEllipse(cursorBrush, cursorBound.Left + 0.0f, cursorBound.Top + 0.0f, cursorBound.Width - 0.0f, cursorBound.Height - 0.0f);
          renderGraphics.DrawArc    (cursorPen,   cursorBound.Left + 2.0f, cursorBound.Top + 2.0f, cursorBound.Width - 4.0f, cursorBound.Height - 4.0f, 0, 360);
        }

        // ... ->> Draw fullscreen background
        if (window.IsFullscreen()) {
          Bitmap          renderCopy                      = null;
          Graphics        renderCopyGraphics              = null;
          Bitmap          renderFullscreen                = renders[renderIndex];
          Graphics        renderFullscreenGraphics        = Graphics.FromImage(renderFullscreen);
          ImageAttributes renderFullscreenImageAttributes = new ImageAttributes();
          Rectangle       windowScreenBounds              = Screen.FromControl(window).Bounds;
          Int32           windowScreenSize                = Math.Max(windowScreenBounds.Height, windowScreenBounds.Width);

          // ...
          renderFullscreenGraphics.CompositingMode   = renderGraphics.CompositingMode;
          renderFullscreenGraphics.InterpolationMode = renderGraphics.InterpolationMode;

          renderFullscreenGraphics.CompositingQuality = CompositingQuality.HighSpeed;
          renderFullscreenGraphics.PixelOffsetMode    = PixelOffsetMode   .HighSpeed;
          renderFullscreenGraphics.SmoothingMode      = SmoothingMode     .HighQuality;
          renderFullscreenGraphics.TextRenderingHint  = TextRenderingHint .ClearTypeGridFit;

          // ... ->> Render asynchronously filtered gameplay graphics; see `PostProcessRender()` (a fast blur function would be useful here)
          renderPostProcessorFullscreenRenderBitmapData = render.LockBits(new Rectangle(Point.Empty, render.Size), ImageLockMode.ReadOnly, PixelFormat.Format32bppPArgb);
          Marshal.Copy(renderPostProcessorFullscreenRenderBitmapData.Scan0, renderPostProcessorFullscreenRenderSubdata[0], 0, render.Height * render.Width * sizeof(byte) * 4);
          render.UnlockBits(renderPostProcessorFullscreenRenderBitmapData);
          renderPostProcessorFullscreenRenderBitmapData = null;

          // ... ->> Apply transparency matrix to fullscreen background image
          renderFullscreenImageAttributes.SetColorMatrix(new ColorMatrix(new Single[][] {
            new Single[] {1.00f, 0.00f, 0.00f, 0.00f, 0.00f},
            new Single[] {0.00f, 1.00f, 0.00f, 0.00f, 0.00f},
            new Single[] {0.00f, 0.00f, 1.00f, 0.00f, 0.00f},
            new Single[] {0.00f, 0.00f, 0.00f, 0.75f, 0.00f},
            new Single[] {0.00f, 0.00f, 0.00f, 0.00f, 1.00f},
          }), ColorMatrixFlag.Default, ColorAdjustType.Bitmap);

          // ... ->> Draw asynchronously filtered & translated gameplay graphics and semi-transparent fullscreen background image
          if (render == renderFullscreen) {
            renderCopy         = render.Clone(new Rectangle(Point.Empty, render.Size), render.PixelFormat);
            renderCopyGraphics = Graphics.FromImage(renderCopy);

            renderCopyGraphics.CompositingMode    = CompositingMode   .SourceCopy;
            renderCopyGraphics.CompositingQuality = CompositingQuality.HighSpeed;
            renderCopyGraphics.InterpolationMode  = InterpolationMode .NearestNeighbor;
            renderCopyGraphics.PixelOffsetMode    = PixelOffsetMode   .None;
            renderCopyGraphics.SmoothingMode      = SmoothingMode     .None;
            renderCopyGraphics.TextRenderingHint  = TextRenderingHint .SingleBitPerPixel;

            renderCopyGraphics.DrawImageUnscaled(renderFullscreen, 0, 0);
          }

          renderFullscreenGraphics.Clear(window.BackColor);

          renderFullscreenGraphics.DrawImage(
            renderPostProcessorFullscreenRender,
            (windowScreenSize - windowScreenBounds.Width)  / -2.0f,
            (windowScreenSize - windowScreenBounds.Height) / -2.0f,
            windowScreenSize * (renderPostProcessorFullscreenRender.Height < renderPostProcessorFullscreenRender.Width  ? renderPostProcessorFullscreenRender.Width  / (float) renderPostProcessorFullscreenRender.Height : 1.0f),
            windowScreenSize * (renderPostProcessorFullscreenRender.Width  < renderPostProcessorFullscreenRender.Height ? renderPostProcessorFullscreenRender.Height / (float) renderPostProcessorFullscreenRender.Width  : 1.0f)
          );

          if (null != renderFullscreenImage)
          renderFullscreenGraphics.DrawImage(renderFullscreenImage,  new Rectangle(
            (int) ((windowScreenSize - windowScreenBounds.Width)  / -2.0f),
            (int) ((windowScreenSize - windowScreenBounds.Height) / -2.0f),
            (int) (windowScreenSize * (renderFullscreenImage.Height < renderFullscreenImage.Width  ? renderFullscreenImage.Width  / (float) renderFullscreenImage.Height : 1.0f)),
            (int) (windowScreenSize * (renderFullscreenImage.Width  < renderFullscreenImage.Height ? renderFullscreenImage.Height / (float) renderFullscreenImage.Width  : 1.0f))
          ), 0, 0, renderFullscreenImage.Width, renderFullscreenImage.Height, GraphicsUnit.Pixel, renderFullscreenImageAttributes);

          // ... ->> Draw controller prompts
          RequestControllerIcons();

          for (int index = renderControllerIcons.Length; 0 != index--; ) {
            Image controllerIcon = renderControllerIcons[index];
            Unit  player         = players              [index];

            // ...
            if (null != controllerIcon) {
              PointF       controllerCoordinates        = new PointF(windowScreenBounds.Width * 0.033f, windowScreenBounds.Height * 0.100f);
              Size         controllerIconSize           = controllerIcon.Size;
              float        controllerMarginY            = windowScreenBounds.Height * 0.050f;
              const string controllerPrompt             = "Awaiting input\u2026";
              Font         controllerPromptFont         = null == textFontFamily ? new Font(textFont.Name, 10.0f) : new Font(textFontFamily, 10.0f);
              FontFamily   controllerPromptFontFamily   = null == textFontFamily ? FontFamily.GenericMonospace    : textFontFamily;
              GraphicsPath controllerPromptGraphicsPath = new GraphicsPath();
              const uint   controllerPromptMarginY      = 10u;
              SizeF        controllerPromptSize         = renderFullscreenGraphics.MeasureString(controllerPrompt, controllerPromptFont);
              string       controllerTitle              = (new string[] {"KEYBOARD", "MOUSE", "GAMEPAD", "TOUCH"})[index];
              Font         controllerTitleFont          = null == headingFontFamily ? new Font(headingFont.Name, 18.0f) : new Font(headingFontFamily, 18.0f);
              FontFamily   controllerTitleFontFamily    = null == headingFontFamily ? FontFamily.GenericSansSerif       : headingFontFamily;
              GraphicsPath controllerTitleGraphicsPath  = new GraphicsPath();
              const uint   controllerTitleMarginY       = 15u;
              SizeF        controllerTitleSize          = renderFullscreenGraphics.MeasureString(controllerTitle, controllerTitleFont);
              Bitmap       controllerRender             = null;
              BitmapData   controllerRenderBitmapData   = null;
              byte[]       controllerRenderData         = null;
              Single       controllerSize               = Math.Max(50.0f, Math.Min(windowScreenBounds.Height, windowScreenBounds.Width) * 0.1f);

              // ... ->> Scale and translate the controller render
              if (controllerIconSize.Height < controllerIconSize.Width) { controllerIconSize.Width  = (int) (controllerIconSize.Width  * (controllerSize / controllerIconSize.Height)); controllerIconSize.Height = (int) controllerSize; }
              else                                                      { controllerIconSize.Height = (int) (controllerIconSize.Height * (controllerSize / controllerIconSize.Width));  controllerIconSize.Width  = (int) controllerSize; }

              controllerIconSize.Height = (int) (controllerIconSize.Height * 0.575f);
              controllerIconSize.Width  = (int) (controllerIconSize.Width  * 0.575f);

              if (index % 2u != 0u) controllerCoordinates.X  = windowScreenBounds.Width - (controllerCoordinates.X + controllerSize);
              if (index > 1u)       controllerCoordinates.Y += controllerTitleMarginY + controllerTitleSize.Height + controllerMarginY + controllerPromptMarginY + controllerPromptSize.Height + controllerSize;

              // ... ->> Re-color the controller render
              controllerRender           = new Bitmap(controllerIcon, controllerIconSize);
              controllerRenderBitmapData = controllerRender.LockBits(new Rectangle(Point.Empty, controllerRender.Size), ImageLockMode.ReadWrite, controllerRender.PixelFormat);
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

              // ... ->> Draw either controller or player status
              if (null == player) {
                controllerPromptGraphicsPath.AddString(controllerPrompt, controllerPromptFontFamily, (Int32) controllerPromptFont.Style, GetFontSizeInPixels(controllerPromptFont, renderGraphics), new PointF(
                  controllerCoordinates.X + ((controllerSize - controllerPromptSize.Width) / 2.0f),
                  controllerCoordinates.Y + (controllerTitleMarginY + controllerTitleSize.Height + controllerPromptMarginY + controllerSize)
                ), new StringFormat());

                renderFullscreenGraphics.FillPath(renderControllerPromptBrush, controllerPromptGraphicsPath);
              }

              else {
                uint   playerBaseHealth = (uint) player.GetType().GetField("BaseHealth").GetValue(player);
                PointF playerCoordinates = new PointF(
                  controllerCoordinates.X + ((controllerSize - controllerPromptSize.Width) / 2.0f),
                  controllerCoordinates.Y + (controllerTitleMarginY + controllerTitleSize.Height + controllerPromptMarginY + controllerSize)
                );

                const float  playerHealthBarFrameBorderSize   = 1.675f;                                                                                                                                                                                                                                                                                                                     //
                SizeF        playerHealthBarFrameSize         = new SizeF(controllerSize, Math.Max(10.0f, controllerPromptSize.Height / 2.0f));                                                                                                                                                                                                                                             //
                Pen          playerHealthBarFramePen          = new Pen(Color.DarkGray, playerHealthBarFrameBorderSize);                                                                                                                                                                                                                                                                    // --> Pens.DarkGray
                GraphicsPath playerHealthBarFrameGraphicsPath = new GraphicsPath();                                                                                                                                                                                                                                                                                                         //
                Brush        playerHealthBarFrameBrush        = new SolidBrush(Color.Black) as Brush;                                                                                                                                                                                                                                                                                       // --> Brushes.Black
                Single       playerHealthBarFrameBorderRadius = Math.Min(playerHealthBarFrameSize.Height, playerHealthBarFrameSize.Width) / 2.0f;                                                                                                                                                                                                                                           //
                SizeF        playerHealthBarSize              = new SizeF((playerHealthBarFrameSize.Width - (playerHealthBarFrameBorderSize * 0.5f)) * (player.Health / (float) playerBaseHealth), playerHealthBarFrameSize.Height - (playerHealthBarFrameBorderSize * 0.5f));                                                                                                              //
                GraphicsPath playerHealthBarGraphicsPath      = new GraphicsPath();                                                                                                                                                                                                                                                                                                         //
                Brush        playerHealthBarBrush             = new LinearGradientBrush(new PointF(playerCoordinates.X + (playerHealthBarFrameBorderSize * 0.5f), playerHealthBarSize.Height / 2.0f), new PointF(playerCoordinates.X + playerHealthBarFrameSize.Width + (playerHealthBarFrameBorderSize * 1.0f), playerHealthBarSize.Height / 2.0f), Color.DarkGreen, Color.Lime) as Brush; //
                Single       playerHealthBarBorderRadius      = playerHealthBarFrameBorderRadius;                                                                                                                                                                                                                                                                                           //

                // ... ->> Draw health bar and its frame
                playerHealthBarGraphicsPath.AddArc(playerCoordinates.X + (playerHealthBarFrameBorderSize * 0.5f),                             playerCoordinates.Y + (playerHealthBarFrameBorderSize * 0.5f),                              playerHealthBarBorderRadius, playerHealthBarBorderRadius, 180.0f, 90.0f);
                playerHealthBarGraphicsPath.AddArc(playerCoordinates.X + (playerHealthBarFrameBorderSize * 0.5f) + playerHealthBarSize.Width, playerCoordinates.Y + (playerHealthBarFrameBorderSize * 0.5f),                              playerHealthBarBorderRadius, playerHealthBarBorderRadius, 270.0f, 90.0f);
                playerHealthBarGraphicsPath.AddArc(playerCoordinates.X + (playerHealthBarFrameBorderSize * 0.5f) + playerHealthBarSize.Width, playerCoordinates.Y + (playerHealthBarFrameBorderSize * 0.5f) + playerHealthBarSize.Height, playerHealthBarBorderRadius, playerHealthBarBorderRadius, 0.0f,   90.0f);
                playerHealthBarGraphicsPath.AddArc(playerCoordinates.X + (playerHealthBarFrameBorderSize * 0.5f),                             playerCoordinates.Y + (playerHealthBarFrameBorderSize * 0.5f) + playerHealthBarSize.Height, playerHealthBarBorderRadius, playerHealthBarBorderRadius, 90.0f,  90.0f);
                playerHealthBarGraphicsPath.CloseFigure();

                playerHealthBarFrameGraphicsPath.AddArc(playerCoordinates.X,                                  playerCoordinates.Y,                                   playerHealthBarFrameBorderRadius, playerHealthBarFrameBorderRadius, 180.0f, 90.0f);
                playerHealthBarFrameGraphicsPath.AddArc(playerCoordinates.X + playerHealthBarFrameSize.Width, playerCoordinates.Y,                                   playerHealthBarFrameBorderRadius, playerHealthBarFrameBorderRadius, 270.0f, 90.0f);
                playerHealthBarFrameGraphicsPath.AddArc(playerCoordinates.X + playerHealthBarFrameSize.Width, playerCoordinates.Y + playerHealthBarFrameSize.Height, playerHealthBarFrameBorderRadius, playerHealthBarFrameBorderRadius, 0.0f,   90.0f);
                playerHealthBarFrameGraphicsPath.AddArc(playerCoordinates.X,                                  playerCoordinates.Y + playerHealthBarFrameSize.Height, playerHealthBarFrameBorderRadius, playerHealthBarFrameBorderRadius, 90.0f,  90.0f);
                playerHealthBarFrameGraphicsPath.CloseFigure();

                renderFullscreenGraphics.FillPath(playerHealthBarFrameBrush, playerHealthBarFrameGraphicsPath);
                renderFullscreenGraphics.FillPath(playerHealthBarBrush,      playerHealthBarGraphicsPath);
                renderFullscreenGraphics.DrawPath(playerHealthBarFramePen,   playerHealthBarFrameGraphicsPath);

                // ...
                playerHealthBarBrush     .Dispose();
                playerHealthBarFrameBrush.Dispose();
                playerHealthBarFramePen  .Dispose();
              }

              // ... ->> Draw controller title
              controllerTitleGraphicsPath.AddString(controllerTitle, controllerTitleFontFamily, (Int32) controllerTitleFont.Style, GetFontSizeInPixels(controllerTitleFont, renderGraphics), new PointF(
                controllerCoordinates.X + ((controllerSize - controllerTitleSize.Width) / 2.0f),
                controllerCoordinates.Y + (controllerTitleMarginY + controllerSize)
              ), new StringFormat());

              renderFullscreenGraphics.FillPath(renderControllerTitleBrush, controllerTitleGraphicsPath);
              renderFullscreenGraphics.DrawPath(renderControllerTitlePen,   controllerTitleGraphicsPath);

              // ... ->> Draw controller icon and its bordered frame
              renderFullscreenGraphics.FillEllipse(renderControllerIconBrush, controllerCoordinates.X, controllerCoordinates.Y, controllerSize, controllerSize);
              renderFullscreenGraphics.DrawArc    (renderControllerIconPen,   controllerCoordinates.X, controllerCoordinates.Y, controllerSize, controllerSize, 0.0f, 360.0f);
              renderFullscreenGraphics.DrawImageUnscaled(controllerRender, (int) (controllerCoordinates.X + ((controllerSize - controllerIconSize.Width) / 2.0f)), (int) (controllerCoordinates.Y + ((controllerSize - controllerIconSize.Height) / 2.0f)));
            }
          }

          // ... ->> Draw gameplay graphics and its border
          renderFullscreenGraphics.DrawImageUnscaledAndClipped(render != renderFullscreen ? render : renderCopy, new Rectangle((windowScreenBounds.Width - windowViewportSize.Width) / 2, (windowScreenBounds.Height - windowViewportSize.Height) / 2, windowViewportSize.Width - 0, windowViewportSize.Height - 0));
          renderFullscreenGraphics.DrawRectangle              (renderFullscreenPen,                              new Rectangle((windowScreenBounds.Width - windowViewportSize.Width) / 2, (windowScreenBounds.Height - windowViewportSize.Height) / 2, windowViewportSize.Width - 2, windowViewportSize.Height - 2));

          renderGraphics.DrawImageUnscaled(renderFullscreen, 0, 0);

          // ...
          if (render == renderFullscreen) renderCopyGraphics      .Dispose();
          if (render != renderFullscreen) renderFullscreenGraphics.Dispose();
        }
      }

      // ...
      graphics.DrawImageUnscaled(render, 0, 0);
      renderGraphics.Dispose();
    }

    public static void Terminate() {
      if (0x00u != (byte) (state & State.TERMINATED)) return;
      state = State.TERMINATED;

      // ... ->> Cleanup reserved game memory
      cursorBrush                                  .Dispose();
      cursorPen                                    .Dispose();
      promptBrush                                  .Dispose();
      promptFontBrush                              .Dispose();
      promptSelectionBrush                         .Dispose();
      renderControllerIconBrush                    .Dispose();
      renderControllerIconPen                      .Dispose();
      renderControllerPromptBrush                  .Dispose();
      renderControllerPromptPen                    .Dispose();
      renderControllerTitleBrush                   .Dispose();
      renderControllerTitlePen                     .Dispose();
      renderFullscreenPen                          .Dispose();
      renderPostProcessorFullscreenRender          .Dispose();
      renderPostProcessorFullscreenRenderAllocation.Free();
      window                                       .Close();

      // ... ->> Exit the game
      if (Application.MessageLoop) {
        Application.Exit();
        return;
      }

      Environment.Exit(0x00);
    }

    public static void Update(object target, EventArgs arguments) {
      float    cursorSize         = null != Cursor.Current ? (Cursor.Current.Size.Height + Cursor.Current.Size.Width) / 2.0f : 0.0f;
      int      starsLength        = stars.Count;
      TimeSpan timestamp          = TimeSpan.FromTicks(DateTime.Now.Ticks);
      Size     windowViewportSize = window.ViewportSize;

      /* ... ->> Game logic unbounded by framerate ie: calculations, flags, … */ {
        // ... ->> Update cursor
        cursorBound.Height = cursorBound.Width = cursorSize * 0.75f;

        // ... ->> Remove fallen (excess) stars; update maximum star count based on viewport size
        starsMaximumLength = (ushort) ((windowViewportSize.Height + windowViewportSize.Width) / 20u);

        if (starsLength > starsMaximumLength) {
          stars.RemoveRange(starsMaximumLength, starsLength - starsMaximumLength);
          starsLength = starsMaximumLength;
        }

        for (int index = starsLength; 0 != index--; )
        if (stars[index].Delta >= 1.0f) starsLength -= stars.Remove(stars[index]) ? 1 : 0;
      }

      /* ... ->> Game logic unbounded by `Update(…)` framerate ie: calculations, flags, … */ {
        // ... ->> Spawn falling stars
        if (starsSpawnDelta < timestamp - starsSpawnTimestamp)
        if (starsLength != starsMaximumLength) {
          ushort starsSpawnCount = (ushort) Star.Randomizer.Next(starsSpawnCountDelta[0], starsSpawnCountDelta[1]);

          // ...
          starsSpawnCount     = (ushort) (starsLength + starsSpawnCount > starsMaximumLength ? starsMaximumLength - starsLength : starsSpawnCount);
          starsSpawnTimestamp = timestamp;

          while (0u != starsSpawnCount--) {
            Star  star               = new Star();
            float starFallCoordinate = (float) Star.Randomizer.NextDouble();

            // ...
            star.DestinationCoordinates.X = starFallCoordinate;
            star.DestinationCoordinates.Y = 1.0f;
            star.Opacity                  = (byte) Star.Randomizer.Next(127, 255);
            star.SourceCoordinates.X      = starFallCoordinate;
            star.SourceCoordinates.Y      = (float) Star.Randomizer.NextDouble() * 0.6500f;
            star.Speed                    = (float) Star.Randomizer.NextDouble() * 0.0025f;

            stars.Add(star);
          }
        }
      }

      /* Update ->> Game logic bounded by `Update(…)` framerate ie: animations, transitions, … */
      if (updateDelta < timestamp - updateTimestamp) {
        updateTimestamp = timestamp;

        // ... ->> Fell stars
        foreach (Star star in stars)
        star.Delta += star.Speed;
      }

      /* Render ->> Game render bounded by `Render(…)` */
      window.Invalidate();
    }

    /* Main */
    static void Main(String[] commandLineArguments) {
      const string backPromptText  = "ᐊ BACK";
      TimeSpan     delta           = TimeSpan.FromTicks(TimeSpan.TicksPerSecond / 60L);
      DEVMODE      deviceMode      = new DEVMODE();
      FontFamily[] fontFamilies    = {null, null}; // --> headingFontFamily, textFontFamily
      string[]     fontFilePaths   = {null, null};
      TimeSpan     timestamp       = TimeSpan.FromTicks(DateTime.Now.Ticks);
      Timer        updateTimer     = null;
      Screen       windowScreen    = null;
      Int32        windowSize      = 0;

      /* Update > ... ->> Setup game variables and such */
      if (EnumerateDisplaySettings(null, DEVMODE.ENUM_CURRENT_SETTINGS, ref deviceMode))
      delta = 0u != deviceMode.dmDisplayFrequency ? TimeSpan.FromTicks(TimeSpan.TicksPerSecond / (long) deviceMode.dmDisplayFrequency) : delta;

      creditsPromptStates         = new State[] {State.MENU};                                                                   //
      creditsPromptTexts          = new string[] {backPromptText};                                                              //
      cursorActivated             = false;                                                                                      //
      cursorBound                 = new RectangleF(0.0f, 0.0f, 0.0f, 0.0f);                                                     //
      cursorBrush                 = new SolidBrush(Color.FromArgb(255 / 3, 0xFF, 0xFF, 0xFF)) as Brush;                         //
      cursorPen                   = new Pen(Color.DodgerBlue);                                                                  // --> Pens.DodgerBlue
      cursorVisibility            = true;                                                                                       //
      cursorWithinWindow          = false;                                                                                      //
      difficulty                  = 1.0f;                                                                                       //
      fontFilePaths[0]            = "assets/fonts/panton.otf";                                                                  //
      fontFilePaths[1]            = "assets/fonts/randy-gg.ttf";                                                                //
      headingFont                 = SystemFonts.CaptionFont;                                                                    //
      helpPromptStates            = new State[] {State.MENU};                                                                   //
      helpPromptTexts             = new string[] {backPromptText};                                                              //
      keys                        = new List<Keys>();                                                                           //
      menuFooter                  = "Made with \uD83D\uDC99 by Lapys, 2023";                                                    //
      menuPromptStates            = new State[] {State.GAMEPLAY, State.HELP, State.SETTINGS, State.CREDITS, State.TERMINATED};  //
      menuPromptTexts             = new string[] {"PLAY", "HOW TO PLAY", "SETTINGS", "CREDITS", "EXIT"};                        //
      players[0]                  = new Infantry(Point.Empty);                                                                  //
      promptBrush                 = new SolidBrush(Color.FromArgb(85, 0x33, 0x33, 0x33)) as Brush;                              //
      promptFontBrush             = new SolidBrush(Color.White);                                                                // --> Brushes.White
      promptSelectionBrush        = new SolidBrush(Color.FromArgb(85,  0xCF, 0xCF, 0xCF)) as Brush;                             //
      renderControllerIconBrush   = new SolidBrush(Color.FromArgb(225, 0x00, 0x00, 0x00)) as Brush;                             //
      renderControllerIconPen     = new Pen(Color.DarkGray);                                                                    // --> Pens.DarkGray
      renderControllerIcons       = new Image[] {null, null, null, null};                                                       //
      renderControllerPromptBrush = new SolidBrush(Color.FromArgb(225, 0xFF, 0xFF, 0xFF)) as Brush;                             //
      renderControllerPromptPen   = new Pen(Color.Transparent);                                                                 // --> Pens.Transparent
      renderControllerTitleBrush  = new SolidBrush(Color.White) as Brush;                                                       // --> Brushes.White
      renderControllerTitlePen    = new Pen(Color.DarkGray);                                                                    // --> Pens.DarkGray
      renderDelta                 = delta;                                                                                      //
      renderFullscreenPen         = new Pen(Color.FromArgb(255, 0xFF, 0xFF, 0xFF), 1.5f);                                       //
      renderPostProcessor         = new Thread(new ThreadStart(PostProcessRender));                                             //
      renders                     = new Bitmap[] {null, null};                                                                  //
      renderTimestamp             = timestamp;                                                                                  //
      settingsPromptStates        = new State[] {State.MENU};                                                                   //
      settingsPromptTexts         = new string[] {backPromptText};                                                              //
      stars                       = new List<Star>();                                                                           //
      starsMaximumLength          = (ushort) 69u;                                                                               //
      starsSpawnCountDelta        = new ushort[] {(ushort) 1u, (ushort) 5u};                                                    //
      starsSpawnDelta             = TimeSpan.FromTicks(TimeSpan.TicksPerMillisecond * 600L);                                    //
      starsSpawnTimestamp         = timestamp;                                                                                  //
      state                       = State.MENU;                                                                                 //
      textFont                    = SystemFonts.DefaultFont;                                                                    //
      title                       = "Space Shooter";                                                                            //
      updateDelta                 = delta;                                                                                      //
      updateTimer                 = new Timer();                                                                                //
      updateTimestamp             = timestamp;                                                                                  //
      window                      = new Window();                                                                               //
      windowScreen                = Screen.FromControl(window);                                                                 //
      windowSize                  = (Int32) (Math.Min(windowScreen.WorkingArea.Height, windowScreen.WorkingArea.Width) * 0.8f); //

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

      creditsPromptBounds  = new RectangleF[creditsPromptStates .Length | creditsPromptTexts .Length];
      helpPromptBounds     = new RectangleF[helpPromptStates    .Length | helpPromptTexts    .Length];
      menuPromptBounds     = new RectangleF[menuPromptStates    .Length | menuPromptTexts    .Length];
      settingsPromptBounds = new RectangleF[settingsPromptStates.Length | settingsPromptTexts.Length];

      headingFontFamily = fontFamilies[0];
      textFontFamily    = fontFamilies[1];

      renderPostProcessorFullscreenRenderData       = new byte[windowScreen.Bounds.Height * windowScreen.Bounds.Width * sizeof(byte) * 4u];
      renderPostProcessorFullscreenRenderSubdata    = new byte[][] {new byte[renderPostProcessorFullscreenRenderData.Length], new byte[renderPostProcessorFullscreenRenderData.Length], new byte[renderPostProcessorFullscreenRenderData.Length]};
      renderPostProcessorFullscreenRenderAllocation = GCHandle.Alloc(renderPostProcessorFullscreenRenderData, GCHandleType.Pinned);
      renderPostProcessorFullscreenRender           = new Bitmap(windowScreen.Bounds.Width, windowScreen.Bounds.Height, windowScreen.Bounds.Width * sizeof(byte) * 4, PixelFormat.Format32bppPArgb, renderPostProcessorFullscreenRenderAllocation.AddrOfPinnedObject());

      for (int index = creditsPromptBounds .Length; 0 != index--; ) creditsPromptBounds [index] = RectangleF.Empty;
      for (int index = helpPromptBounds    .Length; 0 != index--; ) helpPromptBounds    [index] = RectangleF.Empty;
      for (int index = menuPromptBounds    .Length; 0 != index--; ) menuPromptBounds    [index] = RectangleF.Empty;
      for (int index = settingsPromptBounds.Length; 0 != index--; ) settingsPromptBounds[index] = RectangleF.Empty;

      /* Modification > ... */
      Application.Idle += new EventHandler(Update);

      renderPostProcessor.Priority = ThreadPriority.BelowNormal;

      updateTimer.Enabled  = true;
      updateTimer.Interval = (int) updateDelta.TotalMilliseconds / 2;
      updateTimer.Tick    += new EventHandler(Update);

      window.BackColor       = Color.Black;
      window.FormBorderStyle = FormBorderStyle.FixedSingle;
      window.MaximizeBox     = false;
      window.MinimizeBox     = false;
      window.KeyDown        += new KeyEventHandler  (delegate(object target, KeyEventArgs   arguments) { if (keys.Contains(arguments.KeyCode)) return; keys.Add(arguments.KeyCode);                  Input(null);                                                                                                                                                                                         });
      window.KeyUp          += new KeyEventHandler  (delegate(object target, KeyEventArgs   arguments) { int index = keys.IndexOf(arguments.KeyCode); if (index == -1) return; keys.RemoveAt(index); Input(arguments.KeyCode);                                                                                                                                                                            });
      window.MouseDown      += new MouseEventHandler(delegate(object target, MouseEventArgs arguments) { cursorActivated = true;  Input(null);                                                                                                                                                                                                                                                            });
      window.MouseEnter     += new EventHandler     (delegate(object target, EventArgs      arguments) { cursorWithinWindow = true;  if (false != cursorVisibility) { cursorVisibility = false; Cursor.Hide(); }                                                                                                                                                                                          });
      window.MouseLeave     += new EventHandler     (delegate(object target, EventArgs      arguments) { cursorWithinWindow = false; if (false == cursorVisibility) { cursorVisibility = true;  Cursor.Show(); }                                                                                                                                                                                          });
      window.MouseMove      += new MouseEventHandler(delegate(object target, MouseEventArgs arguments) { Window targetWindow = target as Window; cursorBound.Location = (PointF) arguments.Location; cursorBound.X -= (targetWindow.ClientSize.Width - targetWindow.ViewportSize.Width) / 2.0f; cursorBound.Y -= (targetWindow.ClientSize.Height - targetWindow.ViewportSize.Height) / 2.0f; Input(null); });

      window.MouseUp        += new MouseEventHandler(delegate(object target, MouseEventArgs arguments) { cursorActivated = false; Input(null); });
      window.Paint          += new PaintEventHandler(Render);
      window.Size            = new Size(windowSize, windowSize);
      window.StartPosition   = FormStartPosition.CenterScreen;
      window.Text            = title;

      foreach (string format in new string[] {"ico", "png", "bmp", "dib"}) {
        try { window.Icon = new Icon("favicon." + format); break; }
        catch (FileNotFoundException) {}
      }

      /* ... */
      ResetFocusIndex();
      renderPostProcessor.Start();

      if (DialogResult.OK != window.ShowDialog()) Terminate();
    }
  }
}
