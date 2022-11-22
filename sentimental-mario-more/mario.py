import cs50
# TODO


def main():
    while True:
        height = cs50.get_int("Height: ")
        if height > 0 and height <= 8:
            break
    width = height

    i = 0
    while (i < height):
        j = width
        left_colums(width, height, j)
        print("  ", end="")
        j = 0
        right_colums(width, height, j)
        print("\n", end="")
        height -= 1


def left_colums(width, height, j):
    while (j > (width - height + 1)):
        print(" ", end="")
        j -= 1
    while (j <= (width - height + 1) and j != 0):
        print("#", end="")
        j -= 1


def right_colums(width, height, j):
    while (j <= (width - height)):
        print("#", end="")
        j += 1


main()