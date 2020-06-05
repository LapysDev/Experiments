# Import > Random
import random

# Initialization > Orange
orange = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

# Function > Get Random Position
def get_random_position():
    # Return
    return random.randint(0, len(orange))

# Initialization > Orange Slice
orange_slice = get_random_position()

# Print
print('Orange:', orange)
print('Slice:', orange[orange_slice : orange_slice + get_random_position()])
