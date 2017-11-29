# Notepad3DS
Text editor for the Nintendo 3DS console.  

## Features
File opening/saving  
Search for terms in a file (Will only find the first occurence. Looking to change this in future)
Jump to beginning/end of a file  


## Usage
Instructions are provided on the bottom screen of the 3DS  
The bottom screen is also used to show information about the file and some error messages (file opening failure for example)  
Running Notepad3DS through the __Homebrew Launcher__ will mean all file saves/opens will start from the /3ds/ directory. Prefix '../' to your filename to access the root folder.  
Running Notepad3DS through a __.cia__ will mean all file saves/opens will start from the root '/' directory. You can access files in other directories from here. For example, 3ds/files/example.txt   
### Buttons
__A__ - Select the current line  
__B__ - Start a new file (with confirmation)  
__X__ - Save current file  
__Y__ - Open a new file  
__R__ - Search for a term in the file  
__DPad/CPad__ - Movement up/down  
__L__ - Hold with movement to jump to beginning/end  

__NOTE:__ Notepad3DS can access directories but cannot create them. Saving a file to a non existing directory will __NOT__ save the file correctly.  

## Further information
Each line can hold a maximum of 1024 characters when edited. If a line with more than 1024 characters is edited, it __WILL__ be truncated with no way of undoing this.