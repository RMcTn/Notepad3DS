#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include "file.h"
#include "display.h"
#include "file_io.h"

//TODO: Saving file
//      Loading file (How to handle files with empty lines? Treat them as \n?)
//      Handling more than 28 lines. Display around 28 lines at a time so something like
//      for (int line = curr_line; line < (MAX_LINES + line); line++)
//      then print out vector[line] until max line hit 

#define BUFFER_SIZE 60
#define MAX_BOTTOM_SIZE 28
PrintConsole topScreen, bottomScreen;
int main(int argc, char **argv)
{
	gfxInitDefault();
	consoleInit(GFX_TOP, &topScreen);
    consoleInit(GFX_BOTTOM, &bottomScreen);
    consoleSelect(&bottomScreen);
    //Software keyboard thanks to fincs
	printf("Press A to select current line\n");
	printf("Press B to clear screen\n");
	printf("Press X to save file\n");
	printf("Press Y to open file\n");
	printf("Press START to exit\n");
    
    File file;      //Use as default file
    unsigned int curr_line = 0;

    update_screen(file, curr_line);

	while (aptMainLoop())
	{

		hidScanInput();

		u32 kDown = hidKeysDown();

		if (kDown & KEY_START)
			break;

		static SwkbdState swkbd;
		static char mybuf[BUFFER_SIZE];
		SwkbdButton button = SWKBD_BUTTON_NONE;
		bool didit = false;

        swkbdInit(&swkbd, SWKBD_TYPE_NORMAL, 1, -1);
        swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK, SWKBD_FILTER_DIGITS | SWKBD_FILTER_AT | SWKBD_FILTER_PERCENT | SWKBD_FILTER_BACKSLASH | SWKBD_FILTER_PROFANITY, 2);
        swkbdSetFeatures(&swkbd, SWKBD_MULTILINE);

        if (kDown & KEY_A) {
            //Select current line for editing
            swkbdSetHintText(&swkbd, "Input text here.");
            //Iterator to find current selected line
            auto line = file.lines.begin();
            if (curr_line < file.lines.size())
            {
                if (curr_line != 0)
                    advance(line, curr_line);
                
                //Need a char array to output to keyboard
                char current_text[BUFFER_SIZE] = "";
                copy(line->begin(), line->end(), current_text);
                swkbdSetInitialText(&swkbd, current_text);
            }
            didit = true;
            button = swkbdInputText(&swkbd, mybuf, sizeof(mybuf));
        }

        if (kDown & KEY_B) {
            //Clear screen
            clear_screen();
        }

        if (kDown & KEY_X) {
            //Save current file
            //Clear buffer
            memset(mybuf, '\0', BUFFER_SIZE);

            //Get file name
           
            swkbdSetHintText(&swkbd, "Input filename here."); 
            button = swkbdInputText(&swkbd, mybuf, sizeof(mybuf));
            std::string filename = "";
            for (int i = 0; mybuf[i] != '\0'; i++)
                filename.push_back(mybuf[i]);

            //Write out characters to file
            bool success = write_to_file(filename, file);
            
            if (success)
                std::cout << "File written to " << filename << std::endl;
            else
                std::cout << "Problem occured when writing to " << filename << std::endl;

        }

        if (kDown & KEY_Y) {
            //Open a file
            curr_line = 0;
            //Clear buffer
            memset(mybuf, '\0', BUFFER_SIZE);

            //Get file name
           
            swkbdSetHintText(&swkbd, "Input filename here."); 
            button = swkbdInputText(&swkbd, mybuf, sizeof(mybuf));
            std::string filename = "";
            for (int i = 0; mybuf[i] != '\0'; i++)
                filename.push_back(mybuf[i]);
            file = open_file(filename);
            if (file.read_success) {
                //display file
                update_screen(file, curr_line);
                //auto iter = file.lines.begin();
                //for (const auto& ch: *iter)
                   // std::cout << ch;
                std::cout << "success";
            } else {
                std::cout << "Unable to open " << filename << std::endl;
            }
        }

        if (kDown & KEY_DDOWN) {
            //Move a line down (towards bottom of screen)
            if (curr_line != MAX_BOTTOM_SIZE && curr_line < file.lines.size()) {
                curr_line++;
                update_screen(file, curr_line);
            }
        }

        if (kDown & KEY_DUP) {
            //Move a line up (towards top of screen)
            if (curr_line != 0) {
                curr_line--;
                update_screen(file, curr_line);
            }
        }


		if (didit)
		{
			if (button != SWKBD_BUTTON_NONE)
			{
                std::vector<char> new_text = char_arr_to_vector(mybuf);
                
                if (curr_line >= file.lines.size()) {
                    //Empty line, add a new one.
                    file.add_line(new_text);
                } else {
                    file.edit_line(new_text, curr_line);
                }
                update_screen(file, curr_line);
			} else
				printf("swkbd event: %d\n", swkbdGetResult(&swkbd));
		}

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		gspWaitForVBlank();
	}

	gfxExit();
	return 0;
}
