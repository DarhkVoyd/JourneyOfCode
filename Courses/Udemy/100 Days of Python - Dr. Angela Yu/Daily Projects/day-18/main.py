from turtle import Turtle, Screen, colormode
import random
# import colorgram


turtle = Turtle()
turtle.shape("turtle")
colormode(255)
# for i in range(4):
#     turtle.forward(100)
#     turtle.right(90)
# def random_color():
#     r = random.randint(0, 255)
#     g = random.randint(0, 255)
#     b = random.randint(0, 255)
#     return tuple([r, g, b])


# for i in range(30):
#     turtle.pendown()
#     turtle.forward(5)
#     turtle.penup()
#     turtle.forward(5)
# colors = ["red", "blue", "cyan", "black", "brown", "purple", "orange", "teal", "green"]
# turtle.pensize(10)
# turtle.speed("fastest")
# for sides in range(3, 11):
#     turtle.color(colors[sides - 3])
#     for steps in range(sides):
#         turtle.forward(100)
#         turtle.right(360 / sides)
# directions = [0, 90, 180, 270]
# for _ in range(1000):
#     turtle.color(random_color())
#     turtle.forward(30)
#     turtle.setheading(random.choice(directions))
# for _ in range(90):
#     turtle.color(random_color())
#     turtle.circle(100)
#     turtle.right(4)
#
#

# rgb_colors = []
# colors = colorgram.extract("image.jpg", 12)
# for color in colors:
#     r = color.rgb.r
#     g = color.rgb.g
#     b = color.rgb.b
#     new_color = (r, g, b)
#     rgb_colors.append(new_color)
#
# print(rgb_colors)

# FINAL PROJECT : DAMIEN SPOT PAINTING
rgb_colors = [(199, 175, 117), (124, 36, 24), (210, 221, 213), (168, 106, 57), (186, 158, 53), (6, 57, 83),
              (109, 67, 85), (113, 161, 175), (22, 122, 174)]
inx = -300
iny = -300
turtle.speed("fastest")
turtle.penup()
turtle.setpos(inx, iny)
turtle.pendown()
# turtle.color()
for _ in range(10):
    for _ in range(10):
        turtle.color(random.choice(rgb_colors))
        turtle.pendown()
        turtle.dot(20)
        turtle.penup()
        turtle.forward(50)
    turtle.hideturtle()
    iny += 50
    turtle.setpos(inx, iny)
    turtle.showturtle()

screen = Screen()

screen.exitonclick()
