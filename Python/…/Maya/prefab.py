import maya.cmds as command

# ... ->> Clear the scene of objects
for object in (command.ls(long=True, selection=False) or []):
  try: command.delete(object)
  except: pass

# ... ->> Make a table
class Bounds:
  @property
  def depth(self): return self.bounds["depth"]

  @depth.setter
  def depth(self, value: float): self.bounds["depth"] = value

  # ...
  @property
  def height(self): return self.bounds["height"]

  @height.setter
  def height(self, value: float): self.bounds["height"] = value

  # ...
  @property
  def width(self): return self.bounds["width"]

  @width.setter
  def width(self, value: float): self.bounds["width"] = value

  # ...
  def __init__(self, width: float, height: float, depth: float):
    self.bounds = {"depth": depth, "height": height, "width": width}

class Coordinates:
  @property
  def x(self): return self.coordinates['x']

  @x.setter
  def x(self, value: float): self.coordinates['x'] = value

  # ...
  @property
  def y(self): return self.coordinates['y']

  @y.setter
  def y(self, value: float): self.coordinates['y'] = value

  # ...
  @property
  def z(self): return self.coordinates['z']

  @z.setter
  def z(self, value: float): self.coordinates['z'] = value

  # ...
  def __init__(self, x: float, y: float, z: float):
    self.coordinates = {'x': x, 'y': y, 'z': z}

class Object(Bounds, Coordinates):
  name = [None, None]

  # ...
  @property
  def nodeName(self): return self.name[1]

  @nodeName.setter
  def nodeName(self, value: str): self.name[1] = value

  # ...
  @property
  def objectName(self): return self.name[0]

  @objectName.setter
  def objectName(self, value: str): self.name[0] = value

  # ...
  def make(self, commandFunction, *arguments, **keywordArguments):
    if self.name[0] is not None and self.name[1] is not None:
      try: command.delete(self.name)
      except: pass

    self.name = commandFunction(*arguments, **keywordArguments)

  # ...
  def __init__(self, x: float = 0.0, y: float = 0.0, z: float = 0.0, width: float = 0.0, height: float = 0.0, depth: float = 0.0):
    Bounds     .__init__(self, width, height, depth)
    Coordinates.__init__(self, x, y, z)

class Table:
  class Leg(Object):
    @property
    def radius(self): return self.bounds["depth"] # self.bounds["width"]

    @radius.setter
    def radius(self, value: float): self.bounds["depth"] = self.bounds["width"] = value

    # ...
    def __init__(self, x: float = 0.0, y: float = 0.0, z: float = 0.0, radius: float = 0.0, height: float = 0.0, offset: float = 0.0):
      Object.__init__(self, x, y, z, radius, height, radius)
      self.offset = offset

  class Top(Object):
    pass

  # ...
  def make(self, commandFunction, *arguments, **keywordArguments):
    self.name = commandFunction(*arguments, **keywordArguments)

  # ...
  def __init__(self, top: Top = None, legs: list[Leg] = None, x: float = 0.0, y: float = 0.0, z: float = 0.0, width: float = 0.0, height: float = 0.0, depth: float = 0.0, legOffset: float = 0.0, legRadius: float = 0.0):
    Object.__init__(self)

    self.name = None
    self.top  = Table.Top(x, y, z, width, height, depth)                                                        if top  is None else top
    self.legs = list(map(lambda _: Table.Leg(height=self.top.y, offset=legOffset, radius=legRadius), range(4))) if legs is None else legs

# ...
table = Table(depth=5.00, height=0.65, legOffset=0.05, legRadius=0.45, width=7.50, y=4.00)

table.top.make(command.polyCube, constructionHistory=False, depth=table.top.depth, height=table.top.height, name="table_top", width=table.top.width)
command.move(table.top.x, table.top.y + (table.top.height / 2.0), table.top.z, table.top.name)

for index, leg in enumerate(table.legs):
  leg.make(command.polyCylinder, constructionHistory=False, height=leg.height, name="table_leg_" + str(index + 1), radius=leg.radius)
  command.move(
    ((table.top.width * 0.5) - leg.width) * (+(1.0 - leg.offset) if index + 1 > len(table.legs) / 2 else -(1.0 - leg.offset)),
    table.top.y - (leg.height / 2.0),
    ((table.top.depth * 0.5) - leg.depth) * (-(1.0 - leg.offset) if index % 2 else +(1.0 - leg.offset)),
    leg.name
  )

table.make(command.group, table.top.name, *list(map(lambda leg: leg.name, table.legs)), name="Table")
