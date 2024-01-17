def turn_right():
    turn_left()
    turn_left()
    turn_left()

no_rights = 0
while(not at_goal()):
    if (not wall_on_right() and no_rights > 0 and no_rights % 4 == 0):
        turn_left()
        if (front_is_clear()):
            move()
    if (not wall_on_right()):
        no_rights += 1
        turn_right()
        move()
    elif (wall_on_right() and front_is_clear()):
        no_rights = 0
        move()
    else:
        turn_left()
################################################################
# WARNING: Do not change this comment.
# Library Code is below.
################################################################


def pass_hurdle():
    turn_left()
    move()
    turn_right()
    move()
    turn_right()
    move()
    turn_left()
    
def overcome_hurdle():
    turn_left()
    while(wall_on_right()):
        move()
    turn_right()
    move()
    turn_right()
    while(not wall_in_front()):
        move()
    turn_left()
    
