/* Constant */
  // Components
  var Components = {
    isComponent: null
  };

  // Elements
  var Elements = {
    ROOT: null
  };

  // Events
  var Events = {
    LISTENERS: null,

    isEvent        : null,
    isEventListener: null
  };

  // Styles
  var Styles = {
    Cursor : {POINT: 0x01},
    Layout : {ABSOLUTE: 0x02, RELATIVE: 0x04},
    Margin : null,
    Padding: null,
    Ratio  : null,

    DEFAULT: 0x08,
    INHERIT: 0x10
  };

/* Class */
  // Bounds
  function Bounds(left, top, right, bottom) { if (+0 === arguments.length) return; this.bottom = bottom; this.left = left; this.right = right; this.top = top }
    Bounds.prototype = {bottom: +0, left: +0, right: +0, top: +0};

  // Styles > (Margin, Padding, Ratio)
  Styles.Margin  = function Margin(left, top, right, bottom) { Bounds.apply(this, arguments) };
  Styles.Padding = function Padding(left, top, right, bottom) { Bounds.apply(this, arguments) };
  Styles.Ratio   = function Ratio(ratio) { this.value = ratio / 100.0 };
    Styles.Margin.prototype  = Bounds.prototype;
    Styles.Padding.prototype = Bounds.prototype;
    Styles.Ratio.prototype   = {value: +0.0, valueOf: function valueOf() { return this.value }};

  // Component
  function Component() { this.style = new Style() }
    Component.prototype = {style: null};

    // Element ->> `Component`s in a layout listening to events
    function Element() {
      Component.apply(this, arguments);

      this.children     = new ComponentCollection();
      this.style.layout = Styles.RELATIVE
    }
      Element.prototype = {
        add: function add() {
          for (var index = +0, length = arguments.length; index !== length; ++index) {
            var argument = arguments[index];

            // ...
            if (Components.isComponent(argument)) {
              for (var subindex = this.children.length; ; ) {
                if (argument === this.children[--subindex]) break;
                if (+0 === subindex) { this.children[++this.children.length] = argument; break }
              }
            }

            else if (Events.isEventListener(argument)) {
              for (var subindex = Events.LISTENERS.length; ; )
              with (Events.LISTENERS[--subindex]) {
                if (handler === argument.handler && target === this && type === argument.type) break;
                if (+0 === subindex) {
                  var listener = new EventListener(argument.type, argument.handler);

                  // ...
                  listener.target = this;
                  Events.LISTENERS[++Events.LISTENERS.length] = listener;

                  break
                }
              }
            }

            else throw TypeError("`Element.prototype.add(...)` encountered non-`Component` or non-`Event` object")
          }
        },

        click: function click() {},
        focus: function focus() {},
        key: function key(key) {},

        remove: function remove() {
          for (var index = arguments.length; index; ) {
            var argument = arguments[--index];

            // ...
            if (Components.isComponent(argument)) {
              for (var subindex = this.children.length; subindex; )
              if (argument === this.children[--subindex]) {
                for (var sublength = --this.children.length; subindex !== sublength; ++subindex)
                this.children[subindex] = this.children[subindex + 1];

                break
              }
            }

            else if (Events.isEventListener(argument)) {
              for (var subindex = Events.LISTENERS.length; subindex; )
              with (Events.LISTENERS[--subindex]) if (handler === argument.handler && target === this && type === argument.type) {
                for (var sublength = --Events.LISTENERS.length; subindex !== sublength; ++subindex)
                Events.LISTENERS[subindex] = Events.LISTENERS[subindex + 1];

                break
              }
            }

            else throw TypeError("`Element.prototype.remove(...)` encountered non-`Component` or non-`Event` object")
          }
        },

        children: null,
        style   : Component.prototype.style
      };

      // Button
      function Button() { Element.apply(this, arguments) }
        Button.prototype = Element.prototype;

      // Image
      function Image() { Element.apply(this, arguments) }
        Image.prototype = {
          setURL: function setURL(url) {},

          add     : Element.prototype.add,
          children: Element.prototype.children,
          click   : Element.prototype.click,
          focus   : Element.prototype.focus,
          key     : Element.prototype.key,
          remove  : Element.prototype.remove,
          style   : Element.prototype.style
        };

      // Field
      function Field() {
        Element.apply(this, arguments);

        this.add(new EventListener(KeyEvent, function key(event) { this.setText(this.getText() + event.key) }));
        this.add(new Text())
      }
        Field.prototype = {
          add: function add() {
            Element.prototype.add.apply(this, arguments);
            this.children.length = 1
          },

          getText: function getText() {
            return this.children[0].value
          },

          remove: function remove() {
            var child = this.children[0];

            Element.prototype.remove.apply(this, arguments);
            this.children[0] = child;
            this.children.length = 1
          },

          setText: function setText(text) {
            this.children[0].value = text
          },

          children: Element.prototype.children,
          click   : Element.prototype.click,
          focus   : Element.prototype.focus,
          key     : Element.prototype.key,
          remove  : Element.prototype.remove,
          style   : Element.prototype.style
        };

      // Group
      function Group() {
        Element.apply(this, arguments);
        this.style.width = new Styles.Ratio(100.0)
      }
        Group.prototype = {
          add     : Element.prototype.add,
          children: Element.prototype.children,
          click   : Element.prototype.click,
          focus   : Element.prototype.focus,
          key     : Element.prototype.key,
          remove  : Element.prototype.remove,
          style   : Element.prototype.style
        };

      // Text
      function Text() {
        Element.apply(this, arguments)
      }
        Text.prototype = {
          add     : Element.prototype.add,
          children: Element.prototype.children,
          click   : Element.prototype.click,
          focus   : Element.prototype.focus,
          key     : Element.prototype.key,
          remove  : Element.prototype.remove,
          style   : Element.prototype.style
        };

    // Shape
    function Shape() {
      Component.apply(this, arguments)
    }
      Shape.prototype = {
        style: Component.prototype.style
      };

      // Line
      function Line() {
        Component.apply(this, arguments)
      }
        Line.prototype = {
          style: Shape.prototype.style
        };

        // Spline
        function Spline() {
          Component.apply(this, arguments)
        }
          Spline.prototype = {
            style: Line.prototype.style
          };

          // Ellipse
          function Ellipse() {
            Component.apply(this, arguments)
          }
            Ellipse.prototype = {
              style: Spline.prototype.style
            };

            // Circle
            function Circle() {
              Component.apply(this, arguments)
            }
              Circle.prototype = {
                style: Ellipse.prototype.style
              };

          // Polygon
          function Polygon() {
            Component.apply(this, arguments)
          }
            Polygon.prototype = {
              style: Spline.prototype.style
            };

            // Triangle
            function Triangle() {
              Component.apply(this, arguments)
            }
              Triangle.prototype = {
                style: Polygon.prototype.style
              };

          // Rectangle
          function Rectangle() {
            Component.apply(this, arguments)
          }
            Rectangle.prototype = {
              style: Spline.prototype.style
            };

            // Square
            function Square() {
              Component.apply(this, arguments)
            }
              Square.prototype = {
                style: Rectangle.prototype.style
              };

          // Star
          function Star() {
            Component.apply(this, arguments)
          }
            Star.prototype = {
              style: Spline.prototype.style
            };

    // Style
    function Style() {
      this.active  = this;
      this.blur    = this;
      this.focus   = this;
      this.hover   = this;
      this.margin  = new Styles.Margin();
      this.padding = new Styles.Padding()
    }
      Style.prototype = {
        active: null,
        blur  : null,
        focus : null,
        hover : null,

        height : Bounds.prototype.bottom - Bounds.prototype.top,
        layout : Styles.ABSOLUTE,
        margin : new Styles.Margin(),
        padding: new Styles.Padding(),
        left   : Bounds.prototype.left,
        top    : Bounds.prototype.top,
        width  : Bounds.prototype.right - Bounds.prototype.left
      };

  // Component Collection
  function ComponentCollection() {}
    ComponentCollection.prototype = {length: +0, 0: null, 1: null, 2: null, 3: null, 4: null, 5: null, 6: null, 7: null, 8: null, 9: null, 10: null, 11: null, 12: null, 13: null, 14: null, 15: null, 16: null, 17: null, 18: null, 19: null, 20: null, 21: null, 22: null, 23: null, 24: null, 25: null, 26: null, 27: null, 28: null, 29: null, 30: null, 31: null, 32: null, 33: null, 34: null, 35: null, 36: null, 37: null, 38: null, 39: null, 40: null, 41: null, 42: null, 43: null, 44: null, 45: null, 46: null, 47: null, 48: null, 49: null, 50: null, 51: null, 52: null, 53: null, 54: null, 55: null, 56: null, 57: null, 58: null, 59: null, 60: null, 61: null, 62: null, 63: null, 64: null, 65: null, 66: null, 67: null, 68: null, 69: null, 70: null, 71: null, 72: null, 73: null, 74: null, 75: null, 76: null, 77: null, 78: null, 79: null, 80: null, 81: null, 82: null, 83: null, 84: null, 85: null, 86: null, 87: null, 88: null, 89: null, 90: null, 91: null, 92: null, 93: null, 94: null, 95: null, 96: null, 97: null, 98: null, 99: null, 100: null, 101: null, 102: null, 103: null, 104: null, 105: null, 106: null, 107: null, 108: null, 109: null, 110: null, 111: null, 112: null, 113: null, 114: null, 115: null, 116: null, 117: null, 118: null, 119: null, 120: null, 121: null, 122: null, 123: null, 124: null, 125: null, 126: null, 127: null, 128: null, 129: null, 130: null, 131: null, 132: null, 133: null, 134: null, 135: null, 136: null, 137: null, 138: null, 139: null, 140: null, 141: null, 142: null, 143: null, 144: null, 145: null, 146: null, 147: null, 148: null, 149: null, 150: null, 151: null, 152: null, 153: null, 154: null, 155: null, 156: null, 157: null, 158: null, 159: null, 160: null, 161: null, 162: null, 163: null, 164: null, 165: null, 166: null, 167: null, 168: null, 169: null, 170: null, 171: null, 172: null, 173: null, 174: null, 175: null, 176: null, 177: null, 178: null, 179: null, 180: null, 181: null, 182: null, 183: null, 184: null, 185: null, 186: null, 187: null, 188: null, 189: null, 190: null, 191: null, 192: null, 193: null, 194: null, 195: null, 196: null, 197: null, 198: null, 199: null, 200: null, 201: null, 202: null, 203: null, 204: null, 205: null, 206: null, 207: null, 208: null, 209: null, 210: null, 211: null, 212: null, 213: null, 214: null, 215: null, 216: null, 217: null, 218: null, 219: null, 220: null, 221: null, 222: null, 223: null, 224: null, 225: null, 226: null, 227: null, 228: null, 229: null, 230: null, 231: null, 232: null, 233: null, 234: null, 235: null, 236: null, 237: null, 238: null, 239: null, 240: null, 241: null, 242: null, 243: null, 244: null, 245: null, 246: null, 247: null, 248: null, 249: null, 250: null, 251: null, 252: null, 253: null, 254: null, 255: null};

  // Event
  function Event() {}
    Event.prototype = {
      origin: null
    };

    // Add Event
    function AddEvent() {}
      AddEvent.prototype = {
        origin: Event.prototype.origin
      };

    // Animation Event
    function AnimationEvent() {}
      AnimationEvent.prototype = {
        origin: Event.prototype.origin
      };

      // Animation Start Event
      function AnimationStartEvent() {}
        AnimationStartEvent.prototype = {
          origin: AnimationEvent.prototype.origin
        };

      // Animation Stop Event
      function AnimationStopEvent() {}
        AnimationStopEvent.prototype = {
          origin: AnimationEvent.prototype.origin
        };

    // Blur Event
    function BlurEvent() {}
      BlurEvent.prototype = {
        origin: Event.prototype.origin
      };

      // Blur Start Event
      function BlurStartEvent() {}
        BlurStartEvent.prototype = {
          origin: BlurEvent.prototype.origin
        };

      // Blur Stop Event
      function BlurStopEvent() {}
        BlurStopEvent.prototype = {
          origin: BlurEvent.prototype.origin
        };

    // Drag Event
    function DragEvent() {}
      DragEvent.prototype = {
        origin: Event.prototype.origin
      };

      // Drag Start Event
      function DragStartEvent() {}
        DragStartEvent.prototype = {
          origin: DragEvent.prototype.origin
        };

      // Drag Stop Event
      function DragStopEvent() {}
        DragStopEvent.prototype = {
          origin: DragEvent.prototype.origin
        };

    // Focus Event
    function FocusEvent() {}
      FocusEvent.prototype = {
        origin: Event.prototype.origin
      };

      // Focus Start Event
      function FocusStartEvent() {}
        FocusStartEvent.prototype = {
          origin: FocusEvent.prototype.origin
        };

      // Focus Stop Event
      function FocusStopEvent() {}
        FocusStopEvent.prototype = {
          origin: FocusEvent.prototype.origin
        };

    // Key Event
    function KeyEvent() {}
      KeyEvent.prototype = {
        origin: Event.prototype.origin
      };

      // Key Start Event
      function KeyStartEvent() {}
        KeyStartEvent.prototype = {
          origin: KeyEvent.prototype.origin
        };

      // Key Stop Event
      function KeyStopEvent() {}
        KeyStopEvent.prototype = {
          origin: KeyEvent.prototype.origin
        };

    // Pointer Event
    function PointerEvent() {}
      PointerEvent.prototype = {
        origin: Event.prototype.origin
      };

      // Pointer Blur Event
      function PointerBlurEvent() {}
        PointerBlurEvent.prototype = {
          origin: PointerEvent.prototype.origin
        };

      // Pointer Focus Event
      function PointerFocusEvent() {}
        PointerFocusEvent.prototype = {
          origin: PointerEvent.prototype.origin
        };

      // Pointer Move Event
      function PointerMoveEvent() {}
        PointerMoveEvent.prototype = {
          origin: PointerEvent.prototype.origin
        };

      // Pointer Start Event
      function PointerStartEvent() {}
        PointerStartEvent.prototype = {
          origin: PointerEvent.prototype.origin
        };

        // Pointer Activate Event
        function PointerActivateEvent() {}
          PointerActivateEvent.prototype = {
            origin: PointerStartEvent.prototype.origin
          };

        // Pointer Sub-Activate Event
        function PointerSubactivateEvent() {}
          PointerSubactivateEvent.prototype = {
            origin: PointerStartEvent.prototype.origin
          };

      // Pointer Stop Event
      function PointerStopEvent() {}
        PointerStopEvent.prototype = {
          origin: PointerEvent.prototype.origin
        };

    // Remove Event
    function RemoveEvent() {}
      RemoveEvent.prototype = {
        origin: Event.prototype.origin
      };

    // Resize Event
    function ResizeEvent() {}
      ResizeEvent.prototype = {
        origin: Event.prototype.origin
      };

      // Resize Start Event
      function ResizeStartEvent() {}
        ResizeStartEvent.prototype = {
          origin: ResizeEvent.prototype.origin
        };

      // Resize Stop Event
      function ResizeStopEvent() {}
        ResizeStopEvent.prototype = {
          origin: ResizeEvent.prototype.origin
        };

    // Scroll Event
    function ScrollEvent() {}
      ScrollEvent.prototype = {
        origin: Event.prototype.origin
      };

      // Scroll Start Event
      function ScrollStartEvent() {}
        ScrollStartEvent.prototype = {
          origin: ScrollEvent.prototype.origin
        };

      // Scroll Stop Event
      function ScrollStopEvent() {}
        ScrollStopEvent.prototype = {
          origin: ScrollEvent.prototype.origin
        };

    // Transition Event
    function TransitionEvent() {}
      TransitionEvent.prototype = {
        origin: Event.prototype.origin
      };

      // Transition Start Event
      function TransitionStartEvent() {}
        TransitionStartEvent.prototype = {
          origin: TransitionEvent.prototype.origin
        };

      // Transition Stop Event
      function TransitionStopEvent() {}
        TransitionStopEvent.prototype = {
          origin: TransitionEvent.prototype.origin
        };

    // Update Event
    function UpdateEvent() {}
      UpdateEvent.prototype = {
        origin: Event.prototype.origin
      };

    // Wheel Event
    function WheelEvent() {}
      WheelEvent.prototype = {
        origin: Event.prototype.origin
      };

      // Wheel Start Event
      function WheelStartEvent() {}
        WheelStartEvent.prototype = {
          origin: WheelEvent.prototype.origin
        };

      // Wheel Stop Event
      function WheelStopEvent() {}
        WheelStopEvent.prototype = {
          origin: WheelEvent.prototype.origin
        };

  // Event Listener
  function EventListener(type, handler) {
    this.handler = handler;
    this.type    = type
  }
    EventListener.prototype = {
      handler: function() {},
      target : null,
      type   : Event
    };

  // Event Listener Collection
  function EventListenerCollection() {}
    EventListenerCollection.prototype = {length: +0, 0: null, 1: null, 2: null, 3: null, 4: null, 5: null, 6: null, 7: null, 8: null, 9: null, 10: null, 11: null, 12: null, 13: null, 14: null, 15: null, 16: null, 17: null, 18: null, 19: null, 20: null, 21: null, 22: null, 23: null, 24: null, 25: null, 26: null, 27: null, 28: null, 29: null, 30: null, 31: null, 32: null, 33: null, 34: null, 35: null, 36: null, 37: null, 38: null, 39: null, 40: null, 41: null, 42: null, 43: null, 44: null, 45: null, 46: null, 47: null, 48: null, 49: null, 50: null, 51: null, 52: null, 53: null, 54: null, 55: null, 56: null, 57: null, 58: null, 59: null, 60: null, 61: null, 62: null, 63: null, 64: null, 65: null, 66: null, 67: null, 68: null, 69: null, 70: null, 71: null, 72: null, 73: null, 74: null, 75: null, 76: null, 77: null, 78: null, 79: null, 80: null, 81: null, 82: null, 83: null, 84: null, 85: null, 86: null, 87: null, 88: null, 89: null, 90: null, 91: null, 92: null, 93: null, 94: null, 95: null, 96: null, 97: null, 98: null, 99: null, 100: null, 101: null, 102: null, 103: null, 104: null, 105: null, 106: null, 107: null, 108: null, 109: null, 110: null, 111: null, 112: null, 113: null, 114: null, 115: null, 116: null, 117: null, 118: null, 119: null, 120: null, 121: null, 122: null, 123: null, 124: null, 125: null, 126: null, 127: null, 128: null, 129: null, 130: null, 131: null, 132: null, 133: null, 134: null, 135: null, 136: null, 137: null, 138: null, 139: null, 140: null, 141: null, 142: null, 143: null, 144: null, 145: null, 146: null, 147: null, 148: null, 149: null, 150: null, 151: null, 152: null, 153: null, 154: null, 155: null, 156: null, 157: null, 158: null, 159: null, 160: null, 161: null, 162: null, 163: null, 164: null, 165: null, 166: null, 167: null, 168: null, 169: null, 170: null, 171: null, 172: null, 173: null, 174: null, 175: null, 176: null, 177: null, 178: null, 179: null, 180: null, 181: null, 182: null, 183: null, 184: null, 185: null, 186: null, 187: null, 188: null, 189: null, 190: null, 191: null, 192: null, 193: null, 194: null, 195: null, 196: null, 197: null, 198: null, 199: null, 200: null, 201: null, 202: null, 203: null, 204: null, 205: null, 206: null, 207: null, 208: null, 209: null, 210: null, 211: null, 212: null, 213: null, 214: null, 215: null, 216: null, 217: null, 218: null, 219: null, 220: null, 221: null, 222: null, 223: null, 224: null, 225: null, 226: null, 227: null, 228: null, 229: null, 230: null, 231: null, 232: null, 233: null, 234: null, 235: null, 236: null, 237: null, 238: null, 239: null, 240: null, 241: null, 242: null, 243: null, 244: null, 245: null, 246: null, 247: null, 248: null, 249: null, 250: null, 251: null, 252: null, 253: null, 254: null, 255: null};

/* Function */
  // Component > ...
  Components.isComponent = function isComponent(argument) {
    return argument instanceof Button || argument instanceof Circle || argument instanceof Element || argument instanceof Ellipse || argument instanceof Field || argument instanceof Group || argument instanceof Image || argument instanceof Line || argument instanceof Polygon || argument instanceof Rectangle || argument instanceof Shape || argument instanceof Spline || argument instanceof Square || argument instanceof Start || argument instanceof Text || argument instanceof Triangle
  };

  // Event > ...
  Events.isEvent = function isEvent(argument) {
    return argument instanceof AddEvent || argument instanceof AnimationEvent || argument instanceof AnimationStartEvent || argument instanceof AnimationStopEvent || argument instanceof BlurEvent || argument instanceof BlurStartEvent || argument instanceof BlurStopEvent || argument instanceof DragEvent || argument instanceof DragStartEvent || argument instanceof DragStopEvent || argument instanceof FocusEvent || argument instanceof FocusStartEvent || argument instanceof FocusStopEvent || argument instanceof KeyEvent || argument instanceof KeyStartEvent || argument instanceof KeyStopEvent || argument instanceof PointerActivateEvent || argument instanceof PointerBlurEvent || argument instanceof PointerEvent || argument instanceof PointerFocusEvent || argument instanceof PointerMoveEvent || argument instanceof PointerStartEvent || argument instanceof PointerStopEvent || argument instanceof PointerSubactivateEvent || argument instanceof RemoveEvent || argument instanceof ResizeEvent || argument instanceof ResizeStartEvent || argument instanceof ResizeStopEvent || argument instanceof ScrollEvent || argument instanceof ScrollStartEvent || argument instanceof ScrollStopEvent || argument instanceof TransitionEvent || argument instanceof TransitionStartEvent || argument instanceof TransitionStopEvent || argument instanceof UpdateEvent || argument instanceof WheelEvent || argument instanceof WheelStartEvent || argument instanceof WheelStopEvent
  };

  Events.isEventListener = function isEventListener(argument) {
    return argument instanceof EventListener
  };

/* Modification > ... */
Component.prototype.style  = new Style();
Element.prototype.children = new ComponentCollection();

/* Global > ... */
Elements.ROOT    = new Group();
Events.LISTENERS = new EventListenerCollection();
