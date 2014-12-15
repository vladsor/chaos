; $Id: modfile.asm,v 1.1 2001/02/10 22:58:17 jojo Exp $

global 		modfile, modfile_end
section .data

modfile:
		incbin 		"AXELF.MOD"


modfile_end:
