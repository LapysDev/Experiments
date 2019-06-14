# Import >  Tool-Kit Interface (> Message Box)
import tkinter
import tkinter.messagebox

# Initialization > Window
window = tkinter.Tk()

# Initialization > (Frame, Text, Message Box)
frame = tkinter.Frame(window); frame.pack()
text = tkinter.Label(frame, text="Programming is fun!"); text.pack()
message_box = tkinter.messagebox.showinfo("Program Paused", "Click OK when you are ready to continue.")

# Initialization > (Data Entry, Variable)
data_entry = tkinter.Entry(frame)
var = int(data_entry.get() or 0)

# Window > Main Loop
window.mainloop()
