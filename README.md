Platform Game Demo for MaRTE OS
==========================

Demo from 2009

Controls: wasd

Vídeo: https://www.youtube.com/watch?v=lpaYWefTiIE

---------------------------

Had to modify some files in the current version of MaRTE (marte_1.9_21Aug2014) to be able to build the program (I've copied my modified versions in the marte_modified_files folder):

drivers/svga/vga.h:

* add CPP_BEGIN_DECLS and CPP_END_DECLS
* make int SEQ01; extern
* make unsigned char CR11,CR38,CR39,CR40; extern


include/misc/timespec_operations.h:

* add CPP_BEGIN_DECLS and CPP_END_DECLS
* make char str_timespec_s[40]; extern


include/misc/console_management.h

* add CPP_BEGIN_DECLS and CPP_END_DECLS
