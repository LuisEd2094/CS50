import cs50
# TODO


def main():
    while True:
        cc_num = cs50.get_int("Number: ")
        if not cc_check(cc_num):
            break
    sum_cc(cc_num)
    cc_type(cc_num)


def cc_type(cc_num):
    j = 0
    cc_count = cc_num
    while (cc_count > 100):
        cc_count = cc_count // 10
        j += 1
    if cc_count == 37 and j == 13:
        print("AMEX")
    elif (cc_count == 22 or cc_count == 55 or cc_count == 51) and j == 14:
        print("MASTERCARD")
    elif (cc_count == 40 or cc_count == 41 or cc_count == 42) and (j == 11 or j == 14):
        print("VISA")


def sum_cc(cc_num):
    i = 1
    sum = 0
    while (cc_num > 0):
        if (i % 2 == 1):
            sum += cc_num % 10
        else:
            j = cc_num % 10
            j *= 2
            if (j > 9):
                sum += j % 10
                sum += j // 10
            else:
                sum += j
        cc_num = cc_num // 10
        i += 1
    if (sum % 10 != 0):
        print("INVALID")
        exit(0)


def cc_check(cc_num):
    j = 0
    cc_count = cc_num
    while (cc_count > 100):
        cc_count = cc_count // 10
        j += 1

    if cc_count == 37 and j == 13:
        i = 1  # Amex
    elif (cc_count == 22 or cc_count == 55 or cc_count == 51) and j == 14:
        i = 1
    elif (cc_count == 40 or cc_count == 41 or cc_count == 42) and (j == 11 or j == 14):
        i = 1
    else:
        i = 0
        print("INVALID")
        exit(0)


main()