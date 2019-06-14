# Import > Tool-Kit Interface
import tkinter

# Initialization > Window
window = tkinter.Tk()

# Function > Calculate Miles per Gallon
def calculate_miles_per_gallon():
    # Modification > Calculate Label > Text
    calculate_label["text"] = str(float(miles_input.get() or 0) / float(gallons_input.get() or 1))

# Initialization > (Gallons, Miles, Calculate) Frame
gallons_frame = tkinter.Frame(window); gallons_frame.pack()
miles_frame = tkinter.Frame(window); miles_frame.pack()
calculate_frame = tkinter.Frame(window); calculate_frame.pack()

# Initialization > Gallons (Header, Input)
gallons_header = tkinter.Label(gallons_frame, text="Gallons"); gallons_header.pack(side=tkinter.LEFT)
gallons_input = tkinter.Entry(gallons_frame); gallons_input.pack(side=tkinter.RIGHT)

# Initialization > Miles (Header, Input)
miles_header = tkinter.Label(miles_frame, text="Miles"); miles_header.pack(side=tkinter.LEFT)
miles_input = tkinter.Entry(miles_frame); miles_input.pack(side=tkinter.RIGHT)

# Initialization > Calculate (Button, Label)
calculate_button = tkinter.Button(calculate_frame, command=calculate_miles_per_gallon, text="Calculate Miles-per-Gallons"); calculate_button.pack()
calculate_label = tkinter.Label(calculate_frame); calculate_label.pack()

# Window > Main Loop
window.mainloop()
