# the **Why**:
i've been wanting to learn C/C++ for a good while and since i made a checklist website before thought i'd make something similar to learn the language 

# the **How**:
first things first sorry for the lack of comments in the code i'm not used to adding them so hopefully this can explain the logic behind it 😅
the way it works is the program starts by trying to load tasks from the storage file (storage.txt) then gives the user that crisp **WELCOME** bit 
afterwards it starts a main loop that
lists all the options **>** gets the user choice **>** run through a switch **>** run code 
**Functions:**
addTask : 
simple as getting a string from the user , make a new Task struct and adds it to an array of tasks 

listTasks :
simple as printing out all the task names along with completed or pending depending on if the iscompleted variable is true or false 

rmTask :
gets the task number from the user and removes it from the tasks array :D 

completeTask :
gets the task number from the user and sets the iscompleted proprety to true

editTaskName :
gets the task number from the user then the new name and replaces the old name 

saveTasks :
iterates on the tasks arrray : writes the task name then places a "|" then the iscompleted value and then places a "#" to seperate each task 
this is mainly to make reading the file easier :D 

loadTasks :
reads the storage file and adds each task to the tasks array 

**this fried my brain to make so hope it was useful for someone :D**
