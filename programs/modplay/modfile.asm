; $Id: modfile.asm,v 1.3 2000/10/10 21:15:08 plundis Exp $

global 		modfile, modfile_end
section .data

modfile:
		incbin 		"AXELF.MOD"


modfile_end:
