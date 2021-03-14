def mario(height):
    '''Returns a staircase based on a heigh parameter
    
        e.g. given height = 10 the function will return:
        
                 #
                ##
               ###
              ####
             #####
            ######
           #######
          ########
         #########
        ##########
        
    '''
    height = dec = height
    inc = 0
    
    for i in range(height):
        dec -= 1
        for j in range(dec):
            print(" ", end='')
        inc += 1
        for k in range(inc):
            print('#', end='')
        print("\n", end = '')