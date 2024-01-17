from turtle import Screen, Turtle
import pandas

screen = Screen()
screen.title("Guess The States")
image = 'blank_states_img.gif'
screen.addshape(image)
turtle = Turtle(image)

writer = Turtle()
writer.hideturtle()
writer.penup()

states_data = pandas.read_csv("50_states.csv")

game_is_on = True

while game_is_on:
    user_guess = screen.textinput(title="Guess A State", prompt="Guess the name of a state!")
    guess_data = states_data[states_data.state == user_guess.title()]
    if len(guess_data) < 1:
        continue
    writer.goto(guess_data.x.values[0], guess_data.y.values[0])
    writer.write(user_guess.capitalize(), align="center", font=('Arial', 8, 'normal'))

screen.mainloop()
