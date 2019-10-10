# Import > Random
import random

# Print
print('Program to determine if an entry is within a list.', end='\n\n')

# Initialization > Names
names = ['Amethyst', 'Diamond', 'Garnet', 'Lapis Lazuli', 'Obsidian', 'Onyx', 'Pearl', 'Topaz']

# Logic > Update > Names
if random.random() < .5:
    names.append('Ruby')

# Update > Names
names.sort()

# Print
print('Names:', names)

# Logic > Print
if 'Ruby' in names:
    print('Message:', 'Hello Ruby')

else:
    print('Message:', 'No Ruby')
