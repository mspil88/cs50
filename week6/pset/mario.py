def mario():
    '''Returns a staircase based on a height parameter specified by the user
    
        e.g. given height = 8 the function will return:
        
                 #
                ##
               ###
              ####
             #####
            ######
           #######
          ########

        
    '''
    while True:
        height = int(input("Height: "))
        if height < 1 or height > 8:
            print("Invalid intput")
        else:
            break    
    
    dec = height
    inc = 0
    
    for i in range(height):
        dec -= 1
        for j in range(dec):
            print(" ", end='')
        inc += 1
        for k in range(inc):
            print('#', end='')
        print("\n", end = '')