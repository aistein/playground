import random


def get_random(floor, ceiling):
    return random.randrange(floor, ceiling + 1)

def shuffle(the_list):

    # Shuffle the input in place
    n = len(the_list)
    if n <= 1:
        return the_list

    for i in range(0, n-2):
        pick = get_random(i, n-1)
        tmp = the_list[i]
        the_list[i] = the_list[pick]
        the_list[pick] = tmp

    pass


sample_list = [1, 2, 3, 4, 5]
print ('Sample list:', sample_list)

print ('Shuffling sample list...')
shuffle(sample_list)
print (sample_list)
