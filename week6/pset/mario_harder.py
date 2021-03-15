def mario():
    '''Returns a staircase based on a height parameter specified by the user
    
        e.g. given height = 8 the function will return:
        
                 # #
                ## ##
               ### ###
              #### ####
             ##### #####
            ###### ######
           ####### #######
          ######## ########

        
    '''
    
    while True:
        height = int(input("Provide a height: "))
        if height < 1 or height > 8:
            continue
        else:
            break
    
    i = 0
    dec = height
    for i in range(height):
        i+=1
        dec -=1
        print(' '*dec, end = '')
        print("#"*i, end = '')
        print('', end = ' ')
        print("#"*i)

        