# Library > (Circle, Rectangle)
import circle
import rectangle

# {Circle} Print
print('CIRCLE')

# Initialization > Radius
radius = float(input('    Radius: '))

# Print
print(end='\n')
print('    Area:', circle.area(radius))
print('    Circumference:', circle.circumference(radius))
print(end='\n\n')

# {Rectangle} Print
print('RECTANGLE')

# Initialization > (Length, Width)
length = float(input('    Length: '))
width = float(input('    Width: '))

# Print
print(end='\n')
print('    Area:', rectangle.area(width, length))
print('    Perimeter:', rectangle.perimeter(width, length))
