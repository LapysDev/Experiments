# Initialization > Test File
test_file = open('test.txt', 'w')

# Test File > Write
test_file.write('Lapys`s Memoir:\n')
test_file.write('"Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."\n')
test_file.write('    ~ Lapys')

# Test File > Close
test_file.close()

# Update > Test File
test_file = open('test.txt', 'r')

# Logic
if False:
    # Initialization > Test Content
    test_content = test_file.read()

elif False:
    # Initialization > Lines
    lines = ''

    # Loop > Update > Lines
    for line in test_file:
        lines += line

else:
    # Initialization > Test Content Line (1, 2, 3)
    test_content_line_1 = test_file.readline()
    test_content_line_2 = test_file.readline()
    test_content_line_3 = test_file.readline()

# Test File > Close
test_file.close()

# Print
print(
    'File (test.txt):\n\n',
    test_content_line_1,
    test_content_line_2,
    test_content_line_3,
    sep=''
)
