
# fuck this stupid fucking problem stupid fuck
def boats(people, limit):
    boatCount = 0
    currentWeight = 0
    boats = [0] * limit
    d = {}
    leftovers = []
    
    # What if we sorted the array? Put all of the people together in the boats
    people = sorted(people)

    print('epopel', people)
    for p in reversed(people):
        if (currentWeight == 0):
            boatCount += 1
        fit = False
        print('leftovers', leftovers)
        for i in range(len(leftovers)):
            if leftovers[i] >= p:
                print('Found a leftover', p, leftovers[i])
                leftovers[i] -= p
                fit = True
        if not fit:
            currentWeight += p
            if currentWeight == limit:
                #boatCount += 1
                currentWeight = 0
            elif currentWeight > limit:
                boatCount += 1
                leftovers.append(limit - (currentWeight - p))
                currentWeight = p
        #import pdb; pdb.set_trace()

        print('Just counted', p)
        print('currentWeight', currentWeight)
        print('boatCount', boatCount)
        #elif currentWeight > limit:
          #  boatCount += 2
         #   currentWeight = p
    print('weight', currentWeight)
    if currentWeight == 0:
        boatCount += 1

    return boatCount

print('boaty', boats([1,2], 3))
#print()
print(boats([3,2,2,1], 3))
#print()
print(boats([3,5,3,4], 5))
#print()
print(boats([5,1,4,2], 6))
#print()
print(boats([3,2,3,2,2], 6))
