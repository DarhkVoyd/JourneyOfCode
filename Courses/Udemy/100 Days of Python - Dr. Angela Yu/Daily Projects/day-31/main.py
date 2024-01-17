from tkinter import *
import pandas
import random

BACKGROUND_COLOR = "#B1DDC6"
DATA = pandas.read_csv('data/french_words.csv').to_dict(orient="records")

window = Tk()
window.title("Flash Card")
window.config(padx=50, pady=50, background=BACKGROUND_COLOR)

CARD_FRONT = PhotoImage(file='images/card_front.png')
CARD_BACK = PhotoImage(file='images/card_back.png')

def render_front_card():
    french = random.choice(DATA)["French"]
    canvas.create_image(400, 300, image=CARD_FRONT)
    canvas.create_text(400, 150, text='French', font=('Ariel', 40, 'italic'))
    canvas.create_text(400, 300, text=french, font=('Ariel', 60, 'bold'))


def render_back_card():
    english = random.choice(DATA)["English"]
    canvas.create_image(400, 300, image=CARD_BACK)
    canvas.create_text(400, 150, text='English', font=('Ariel', 40, 'italic'))
    canvas.create_text(400, 300, text=english, font=('Ariel', 60, 'bold'))


def check_answer():
    render_back_card()


canvas = Canvas(width=800, height=600, background=BACKGROUND_COLOR, highlightthickness=0)
canvas.grid(row=0, column=0, columnspan=2)

# render_front_card()

wrong = PhotoImage(file='images/wrong.png')
wrong_button = Button(image=wrong, highlightbackground=BACKGROUND_COLOR, command=check_answer)
wrong_button.grid(row=1, column=0)

right = PhotoImage(file='images/right.png')
right_button = Button(image=right, highlightbackground=BACKGROUND_COLOR, command=check_answer)
right_button.grid(row=1, column=1)

window.mainloop()
