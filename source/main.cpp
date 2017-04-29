#include <3ds.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

    //Software keyboard thanks to fincs
	printf("Press A to select current line\n");
	printf("Press B to clear screen\n");
	printf("Press X to save file\n");
	printf("Press Y to open file\n");
	printf("Press START to exit\n");

	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();

		if (kDown & KEY_START)
			break;

        if (kDown & KEY_A) {
            //Select current line for editing
        }

        if (kDown & KEY_B) {
            //Clear screen
        }

        if (kDown & KEY_X) {
            //Save current file
        }

        if (kDown & KEY_Y) {
            //Open a file
        }

        if (kDown & KEY_DDOWN) {
            //Move a line down (towards bottom of screen)
        }

        if (kDown & KEY_DUP) {
            //Move a line up (towards top of screen)
        }

		static SwkbdState swkbd;
		static char mybuf[60];
		static SwkbdStatusData swkbdStatus;
		SwkbdButton button = SWKBD_BUTTON_NONE;
		bool didit = false;

		if (didit)
		{
			if (button != SWKBD_BUTTON_NONE)
			{
				printf("You pressed button %d\n", button);
				printf("Text: %s\n", mybuf);
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
