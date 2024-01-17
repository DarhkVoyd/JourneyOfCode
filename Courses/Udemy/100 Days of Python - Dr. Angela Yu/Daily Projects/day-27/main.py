import tkinter

tk = tkinter.Tk()
tk.title('Mile to KM Converter')
tk.minsize(width=350, height=100)
tk.config(padx=20, pady=20)


def mile_to_km():
    mile = float(input.get())
    km.config(text=(mile * 1.6))


input = tkinter.Entry()
input.grid(column=1, row=0)
input.focus()

miles_label = tkinter.Label(text='Miles')
miles_label.grid(column=2, row=0)

is_equal_to = tkinter.Label(text='is equal to')
is_equal_to.grid(column=0, row=1)

km = tkinter.Label(text='0')
km.grid(column=1, row=1)

kilometer_label = tkinter.Label(text='Km')
kilometer_label.grid(column=2, row=1)

calculate_button = tkinter.Button(text="Calculate", command=mile_to_km)
calculate_button.grid(column=1, row=2)


tk.mainloop()