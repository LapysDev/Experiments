 # Initialization > Number (...)
NUMBER_ONE = True
NUMBER_TWO = True
NUMBER_THREE = True

# Logic
if NUMBER_ONE:
    # Initialization > Number One (A, B)
    NUMBER_ONE_A = True
    NUMBER_ONE_B = True

    # Logic
    if NUMBER_ONE_A:
        # {Title} Print
        print('1A:\n')

        # Initialization > String
        string = 'Hello, World!'

        # Print
        print('String > Lower: ', string.lower()) # Converts a string to lowercase characters
        print('String > Upper: ', string.upper()) # Converts a string to uppercase characters

    # Logic
    if NUMBER_ONE_B:
        # {Title} Print
        print('\n\n1B:\n')

        # Import > Date-Time
        import datetime

        # Initialization > Date
        date = input("Input Date [yyyy/mm/dd] (separate values with '/'): ").split('/')

        # Print
        print('Output Date: {:%B %d, %Y}'.format(datetime.datetime(int(date[0]), int(date[1]), int(date[2]))))

# Logic
if NUMBER_TWO:
    # Initialization > Number Two (A, B)
    NUMBER_TWO_A = True
    NUMBER_TWO_B = True

    # Logic
    if NUMBER_TWO_A:
        # {Title} Print
        print('\n\n\n2A:\n')

        # Initialization > Days
        days = ['Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday']

        # Print
        print('Days:', days, end='\n\n')
        print('Days [-6:-1]:', days[-6:-1])
        print('Days [:1], Days[-1]:', days[:1], days[-1])

    # Logic
    if NUMBER_TWO_B:
        # {Title} Print
        print('\n\n2B:\n')

        # Function > Kinetic Energy
        def kinetic_energy(mass, velocity):
            # Return
            return .5 * mass * velocity * velocity

        # Update > (Mass, Velocity)
        mass = float(input('Mass: '))
        velocity = float(input('Velocity: '))

        # Print
        print('Kinetic Energy:', kinetic_energy(mass, velocity))

# Logic
if NUMBER_THREE:
    # Initialization > Number Three (A, B)
    NUMBER_THREE_A = True
    NUMBER_THREE_B = True

    # Logic
    if NUMBER_THREE_A:
        # {Title} Print
        print('\n\n\n3A:\n')

        # Initialization > Array
        array = [1, 0, 1]

        # (...)
        array.append(2); print('Array > Append [2]:', array) # Add an item to a list
        array.remove(2); print('Array > Remove [2]:', array) # Remove an item from a list
        print('Array > Index [0]:', array.index(0)) # Return the index of an item in a list

    # Logic
    if NUMBER_THREE_B:
        # {Title} Print
        print('\n\n3B:\n')

        # Initialization > (Number of Players to Record, Record)
        number_of_players_to_record = int(input('Number of players to record: '))
        record = open('golf.txt', 'a')

        # Logic
        if record:
            # Loop
            while number_of_players_to_record > 0:
                # Initialization > (Player Name, Golf Score)
                player_name = input('Player Name: ')#.split(0, 11)
                golf_score = input('Golf Score: ')

                # Print
                print('\n')

                # Record > Write
                record.write('\n' + player_name + ', ' + golf_score)

                # Update > Number of Players to Record
                number_of_players_to_record -= 1

        # Record > Close
        record.close()
