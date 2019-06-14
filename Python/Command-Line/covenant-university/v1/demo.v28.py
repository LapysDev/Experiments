# Initialization > Numbers (1, 2)
numbers1 = list(range(100))
numbers2 = []

# Print
print('Program to copy a list onto another.', end='\n\n')

# Print
print('Numbers 1 (Former):\n    ', numbers2, sep='')
print('Numbers 2 (Former):\n    ', numbers2, sep='')

# Update > Numbers 2
numbers2 += numbers1

# Print
print('\n\n', end='')

# Print
print('Numbers 1 (Current):\n    ', numbers2, end='\n\n', sep='')
print('Numbers 2 (Current):\n    ', numbers2, sep='')
