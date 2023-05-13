
def bubble(message):
    bubble_length = len(message) + 2
    return f"""
    {"_" * bubble_length}
    ( {message} )
    {"_" * bubble_length}
    """

SNAKE = r"""
             ____
            / . .\
MT          \  ---<
             \  /
   __________/ /
-=:___________/

"""    

def say(message):
    print(bubble(message))
    print(SNAKE)