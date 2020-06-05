# Initialization > Number (...)
NUMBER_1 = True
NUMBER_2 = True
NUMBER_3 = True
NUMBER_4 = True
NUMBER_5 = True
NUMBER_6 = True

# Function > Print Indent
def print_indent(*args, **dictionary):
    # Modification > Dictionary > (End, Flush, Indent, Separator)
    dictionary['end'] = dictionary.get('end', '\n')
    dictionary['flush'] = dictionary.get('flush', False)
    dictionary['indent'] = dictionary.get('indent', 0)
    dictionary['sep'] = dictionary.get('sep', ' ')

    # Initialization > (Indent Amount, Index, Length)
    indent_amount = dictionary['indent']
    index = 0
    length = len(args)

    # Print
    print('    ' * (indent_amount + 1), end='') if indent_amount > 0 else print('    ', end='')

    # Loop > Index Arguments
    for arg in args:
        # Update > Index
        index += 1

        # Print
        print(arg, end=dictionary['end'], flush=dictionary['flush'], sep=dictionary['sep']) if index == length else print(arg, end=dictionary['sep'], flush=dictionary['flush'])

# Function > Print Newline
def print_newline(amount=1):
    # Print
    print(end='\n' * amount)

# Logic
if NUMBER_1:
    # {Header} Print
    print('Number 1:')

    # Initialization > Number (...)
    NUMBER_1C = True
    NUMBER_1D = True
    NUMBER_1E = True

    # Logic
    if NUMBER_1C:
        # {Subheader} Print Indent
        print_indent('Number 1C:')

        # Initialization > (Denominator, Iterator, Sum)
        denominator = 1
        iterator = 10
        sum = 0

        # Print Indent
        print_indent(indent=2)

        # Loop
        while iterator:
            # Print
            print('(', 1, ' / ', denominator * denominator, ')', end='', sep='')

            # Logic
            if iterator != 1: print(' + ', end='')

            # Update > (Sum, Denominator, Iterator)
            sum += 1 / (denominator * denominator)
            denominator += 1
            iterator -= 1

        # Print
        print(' = ', sum, sep='')

        # {Margin} Print Newline
        print_newline()

    # Logic
    if NUMBER_1D:
        # {Subheader} Print Indent
        print_indent('Number 1D:')

        # Initialization > List
        list = [1, 0, 1]

        # Function > Middle
        def middle(list):
            # Return
            return list[1:len(list) - 1]

        # Print Indent
        print_indent('List         :', list, indent=2)
        print_indent('List [Middle]:', middle(list), indent=2)

        # {Margin} Print Newline
        print_newline()

    # Logic
    if NUMBER_1E:
        # {Subheader} Print Indent
        print_indent('Number 1E:')

        # Initialization > (Tuple, Tiny Tuple)
        tuple = ('abcd', 787, 2.24, 'john', 70.2)
        tinytuple = ('abcd', 787, 2.24, 'john', 70.2)

        # Print Indent
        print_indent('Tuple[0]         :', tuple[0], indent=2)
        print_indent('Tuple[1:3]       :', tuple[1:3], indent=2)
        print_indent('Tuple[2:]        :', tuple[2:], indent=2)
        print_indent('Tuple < TinyTuple:', tuple < tinytuple, indent=2)
        print_indent('Tuple + TinyTuple:', tuple + tinytuple, indent=2)

    # {Margin} Print Newline
    print_newline(amount=2)

# Logic
if NUMBER_2:
    # {Header} Print
    print('Number 2:')

    # Initialization > Number (...)
    NUMBER_2C = True

    # Logic
    if NUMBER_2C:
        # {Subheader} Print Indent
        print_indent('Number 2C:')

        # Error Handling
        try:
            # Initialization > (File, Line)
            file = open('ChapelServiceAttendance.txt', 'r')
            line = file.readline()

            # Loop
            while line:
                # Initialization > Line
                line = file.readline()

                # Initialization > Attendance (Percentage, Details)
                attendance_percentage = int(line[-2]) + int(line[-4]) + int(line[-6]) + int(line[-8])
                attendance_details = line[0:-18].replace('\t', ' ')[0:11] + 't' + line[-16:-8]

                # Print Indent
                print_indent(attendance_details, str(int(attendance_percentage / 4 * 100)) + '%', indent=2, end='\n', sep='')
        except: pass

    # {Margin} Print Newline
    print_newline(amount=2)

# Logic
if NUMBER_3:
    # {Header} Print
    print('Number 3:')

    NUMBER_3B = True
    NUMBER_3C = True

    # Logic
    if NUMBER_3B:
        # {Subheader} Print Indent
        print_indent('Number 3B:')

        # Initialization > List
        list = [1, 0, 1]

        # Function > Chop
        def chop(list):
            # Return
            return list[1:len(list) - 1]

        # Print Indent
        print_indent('List       :', list, indent=2)
        print_indent('List [Chop]:', middle(list), indent=2)

        # {Margin} Print Newline
        print_newline()

    # Logic
    if NUMBER_3C:
        # {Subheader} Print Indent
        print_indent('Number 3C:')

        # Print Indent
        print_indent(indent=2)

        # Logic
        if input('The following program is run on another interface, still execute (Y / N)? ').lower() == 'y':
            # Import > Toolkit Interface (> Message Box)
            import tkinter
            import tkinter.messagebox

            # Initialization > Window
            window = tkinter.Tk()

            # Window > (...)
            window.configure(background='white')
            window.geometry('500x300') #NOTE (Lapys) -> Width x Height format
            window.option_add('*Frame.Background', window['bg']) #NOTE (Lapys) -> Background of all frames
            window.option_add('*Label.Background', window['bg']) #NOTE (Lapys) -> Background of all labels
            window.resizable(0, 0) #NOTE (Lapys) -> Non-resizable
            window.title('User Validation')

            # Initialization > (Username, Password, Button) Frame
            usernameFrame = tkinter.Frame(window, padx=125)
            passwordFrame= tkinter.Frame(window, padx=125)
            buttonFrame = tkinter.Frame(window, padx=125, pady=10)

            # (Username, Password) Frame > (Pack, Update)
            usernameFrame.pack(fill=tkinter.X); usernameFrame.update()
            passwordFrame.pack(fill=tkinter.X); passwordFrame.update()
            buttonFrame.pack(fill=tkinter.X); passwordFrame.update()

            # Initialization > (Username, Password) Header
            usernameHeader = tkinter.Label(usernameFrame, text='Username:')
            passwordHeader = tkinter.Label(passwordFrame, text='Password:')

            # Initialization > (Username, Password) Input
            usernameInput = tkinter.Entry(usernameFrame, bg='white', width=usernameFrame.winfo_width())
            passwordInput = tkinter.Entry(passwordFrame, bg='white', show='*', width=passwordFrame.winfo_width())

            # (Username, Password) (Header, Input) > Pack
            usernameHeader.pack(); usernameInput.pack()
            passwordHeader.pack(); passwordInput.pack()

            # Function > Display Successful Login
            def displaySuccessfulLogin():
                # Logic
                if usernameInput.get() == 'user' and passwordInput.get() == 'pass':
                    # (Toolkit Interface > Message Box) > Show Information
                    tkinter.messagebox.showinfo('Title', 'Login Successful')

            # Initialization > Login Button
            loginButton = tkinter.Button(buttonFrame, bd=1, bg='white', command=displaySuccessfulLogin, padx=30, relief=tkinter.GROOVE, text='Login')

            # Login Button > Pack
            loginButton.pack()

            # Window > Main Loop
            window.mainloop()

    # {Margin} Print Newline
    print_newline(amount=2)

# Logic
if NUMBER_4:
    # {Header} Print
    print('Number 4:')

    # Initialization > Number (...)
    NUMBER_4B = True
    NUMBER_4C = True
    NUMBER_4D = True

    # Logic
    if NUMBER_4B:
        # {Subheader} Print Indent
        print_indent('Number 4B:')

        # Function > Maximum
        def Max(argA, argB, argC):
            # Logic > Return
            if argA > argB and argA > argC: return argA
            elif argB > argC: return argB
            else: return argC

        # Print Indent
        print_indent('Max [3, 1, 2]:', Max(3, 1, 2), indent=2)

        # {Margin} Print Newline
        print_newline()

    # Logic
    if NUMBER_4C:
        # {Subheader} Print Indent
        print_indent('Number 4C:')

        # Initialization > List (1, 2)
        list1 = [1, 2, 3, 4, 5, 6, 7, 8, 9]
        list2 = []

        # Loop
        for item1 in list1:
            # Logic
            if not item1 % 2:
                # Update > List 2
                list2.append(item1)

        # Print Indent
        print_indent('Sample List    :', list1, indent=2)
        print_indent('Expected Result:', list2, indent=2)

        # {Margin} Print Newline
        print_newline()

    # Logic
    if NUMBER_4D:
        # {Subheader} Print Indent
        print_indent('Number 4D:')

        # Print Indent
        print_indent(indent=2)

        # Loop > Print
        for item in range(0 + 3, 24 + 3, 3):
            print(item, ' ', end='')

    # {Margin} Print Newline
    print_newline(amount=2)

# Logic
if NUMBER_5:
    # {Header} Print
    print('Number 5:')

    # Initialization > Number (...)
    NUMBER_5C = True

    # Logic
    if NUMBER_5C:
        # {Subheader} Print Indent
        print_indent('Number 5C:')

        # Print Indent
        print_indent(indent=2)

        # Logic
        if input('The following program is run on another interface, still execute (Y / N)? ').lower() == 'y':
            # Import > Toolkit Interface
            import tkinter

            # Initialization > Window
            window = tkinter.Tk()

            # Window > (...)
            window.configure(background='white')
            window.geometry('600x300') #NOTE (Lapys) -> Width x Height format
            window.option_add('*Frame.Background', window['bg']) #NOTE (Lapys) -> Background of all frames
            window.option_add('*Label.Background', window['bg']) #NOTE (Lapys) -> Background of all labels
            window.resizable(0, 0) #NOTE (Lapys) -> Non-resizable
            window.title('Calculator')

            # Initialization > Header Frame
            headerFrame = tkinter.Frame(window)

            # Header Frame > Pack
            headerFrame.pack(fill=tkinter.X);

            # Initialization > Header
            header = tkinter.Label(headerFrame, text='Arithmetic Calculator')

            # Header > Pack
            header.pack()

            # Initialization > (First, Second) Number Frame
            firstNumberFrame = tkinter.Frame(window);
            secondNumberFrame = tkinter.Frame(window);

            # (First, Second) Number Frame > Pack
            firstNumberFrame.pack(fill=tkinter.X); secondNumberFrame.pack(fill=tkinter.X);

            # Initialization > (First, Second) Number
            firstNumber = 23; secondNumber = 7

            # Initialization > (First, Second) Number Header
            firstNumberHeader = tkinter.Label(firstNumberFrame, text='First Number:')
            secondNumberHeader = tkinter.Label(secondNumberFrame, text='Second Number:')

            # Initialization > (First, Second) Number Input
            firstNumberInput = tkinter.Entry(firstNumberFrame, bg='white')
            secondNumberInput = tkinter.Entry(secondNumberFrame, bg='white')

            # (First, Second) Number Input > Insert
            firstNumberInput.insert(0, firstNumber)
            secondNumberInput.insert(0, secondNumber)

            # (First, Second) Number (Header, Input) > Pack
            firstNumberHeader.pack(side=tkinter.LEFT); firstNumberInput.pack(side=tkinter.RIGHT)
            secondNumberHeader.pack(side=tkinter.LEFT); secondNumberInput.pack(side=tkinter.RIGHT)

            # Initialization > Result Frame
            resultFrame = tkinter.Frame(window)

            # Result Frame > Pack
            resultFrame.pack(fill=tkinter.X);

            # Initialization > (Result) (Header, Label)
            result = 30
            resultHeader = tkinter.Label(resultFrame, text='Result:')
            resultLabel = tkinter.Label(resultFrame, text=result)

            # Result (Header, Label) > Pack
            resultHeader.pack(side=tkinter.LEFT)
            resultLabel.pack(side=tkinter.RIGHT)

            # Initialization > Calculate Frame
            calculateFrame = tkinter.Frame(window)

            # Calculate Frame > Pack
            calculateFrame.pack(fill=tkinter.X);

            # Function > Calculate
            def calculate():
                # Update > (First, Second) Number
                firstNumber = float(firstNumberInput.get())
                secondNumber = float(secondNumberInput.get())

                # Update > Result
                result = firstNumber + secondNumber

                # Modification > Result Label > Text
                resultLabel['text'] = result

            # Initialization > Calculate Button
            calculateButton = tkinter.Button(calculateFrame, bd=1, bg='white', command=calculate, relief=tkinter.GROOVE, text='ADD', width=30)

            # Calculate Button > Pack
            calculateButton.pack()

            # Window > Main Loop
            window.mainloop()

    # {Margin} Print Newline
    print_newline(amount=2)

# Logic
if NUMBER_6:
    # {Header} Print
    print('Number 6:')

    # Initialization > Number (...)
    NUMBER_6A = True
    NUMBER_6B = True
    NUMBER_6C = False

    # Logic
    if NUMBER_6A:
        # {Subheader} Print Indent
        print_indent('Number 6A:')

        # Initialization > Bible Books
        BibleBooks = ['Matthew', 'Mark', 'Luke', 'John', 'Psalms', 'Romans']

        # Print Indent
        print_indent('Bible Books                          :', BibleBooks, indent=2)

        # Update > Bible Books, Print Indent
        BibleBooks.remove('Psalms'); print_indent("Bible Books -> Remove ['Psalms']     :", BibleBooks, indent=2)
        print_indent("Bible Books -> Index ['Luke']        :", BibleBooks.index('Luke'), indent=2)
        BibleBooks.insert(BibleBooks.index('John') + 1, 'Acts'); print_indent("Bible Books -> Insert [4, 'Acts']    :", BibleBooks, indent=2)
        BibleBooks.append('Corinthians'); print_indent("Bible Books -> Append ['Corinthians']:", BibleBooks, indent=2)
        BibleBooks.sort(); print_indent("Bible Books -> Sort []               :", BibleBooks, indent=2)

        # Print Newline
        print_newline()

        # Print Indent
        print_indent('Bible Books                          :', BibleBooks, indent=2)

        # {Margin} Print Newline
        print_newline(amount=2)

    # Logic
    if NUMBER_6B:
        # {Subheader} Print Indent
        print_indent('Number 6B:')

        # Print Indent
        print_indent(indent=2)

        # Initialization > String
        string = input('Given String: ')

        # Print Indent
        print_indent('Modified String: ', end='', indent=2)

        # Logic > Print
        if len(string) >= 3:
            if string[-3:] == 'ing': print(string + 'ly', end='')
            else: print(string + 'ing', end='')

        else: print(string, end='')

    # Logic --- UPDATE REQUIRED (Lapys) -> Python and SQLite database...
    if NUMBER_6C:
        pass

# {Margin} Print Newline
print_newline()
