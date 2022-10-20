FILENAME = open("items.txt")

def readFile(filename):
    
   #Get the list of lines read in from the file in raw form
    lines = None
    
    with open("items.txt", "r") as file:
        lines = file.readlines()

    #Return the list of lines 
    return lines   


def getInventory():
    '''
    Get the inventory read in from the file.
    @return - dictionary of inventory in the form {item : frequency}
    '''
   #Dictionary of {item : frequency} 
    inventory = {}

    #Read item from the item.txt file
    items =readFile(FILENAME)

   #Loop through the list of items
    for item in items:
        #Remove the newline character at end of line. 
        item = item.strip()
        #Update existing frequency; otherwise add item to dictionary
        if item in inventory:
            #Accumulate to the dictionary item
            inventory[item] +=1 
        else:
            inventory[item] =1
            
    return inventory

    
def determineInventory():
   #Get the inventory
   inventory = getInventory()
   
   #Loop through the dictionary's keys and values
   for item, frequency in inventory.items():
       # print the output
       print(item,":", frequency) 

def determineFrequency(item):
    #Get the inventory
    inventory = getInventory()
    #Return single item
    return inventory[item] 

def output():
    #Get the inventory
    inventory = getInventory()
   
    #Loop through the dictionary and write to the loop through the dictionary's keys and valuest file
    writeFile = open("frequency.dat", "w")
   
    for item, frequency in inventory.items():
    	writeFile.write(item + " " + str(frequency) + "\n")
    