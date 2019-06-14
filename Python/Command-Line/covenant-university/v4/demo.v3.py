# Import > Tool-Kit Interface
import tkinter

# Initialization > Window
window = tkinter.Tk()

# ...
bottom_frame = tkinter.Frame(window); bottom_frame.pack(side=tkinter.BOTTOM)
top_frame = tkinter.Frame(window); top_frame.pack(side=tkinter.TOP)

# ...
address = tkinter.Label(top_frame); address.pack(side=tkinter.BOTTOM)
name = tkinter.Label(top_frame); name.pack(side=tkinter.TOP)

# Function > Display Information
def display_info():
    # Modification > (Address, Name) > Text
    address["text"] = "123, ABC Street"
    name["text"] = "Lapys"

# Function > Quit
def quit():
    # Deletion
    window.destroy()

# Initialization > (Show Information, Quit)
show_info = tkinter.Button(bottom_frame, command=display_info, text="Show Info"); show_info.pack(side=tkinter.LEFT)
quit = tkinter.Button(bottom_frame, command=quit, text="Quit"); quit.pack(side=tkinter.RIGHT)

# Window > Main Loop
window.mainloop()
