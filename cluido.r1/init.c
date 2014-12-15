/* $Id: init.c,v 1.2 2001/02/10 21:23:30 jojo Exp $ */
/* Abstract: Initialisation code. */
/* Authors: Per Lundberg <plundis@chaosdev.org>
            Henrik Hallin <hal@chaosdev.org> */

/* Copyright 1999-2000 chaos development. */

/* This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA. */

#include "cluido.h"

console_structure_type console_structure;
ipv4_structure_type ipv4_structure;
ipc_structure_type pci_structure;

tag_type empty_tag =
{
  0, 0, ""
};

bool has_net = FALSE;

/* Main function. */

int main (void)
{
  /* Set our names. */

  system_process_name_set ("cluido");
  system_thread_name_set ("Initialising");

  /* First of all, initiate a connection to the console service. */

  if (console_init (&console_structure, &empty_tag,
                    IPC_CONSOLE_CONNECTION_CLASS_CLIENT) !=
      CONSOLE_RETURN_SUCCESS)
  {
    return -1;
  }

  if (console_open (&console_structure, 80, 50, 4, VIDEO_MODE_TYPE_TEXT) !=
      CONSOLE_RETURN_SUCCESS)
  {
    return -1;
  }

  system_call_process_parent_unblock ();

  file_init (&vfs_structure, &empty_tag);
  memory_init ();
  pci_init (&pci_structure, &empty_tag);

  if (ipv4_init (&ipv4_structure, &empty_tag) == IPV4_RETURN_SUCCESS)
  {
    has_net = TRUE;
    ipv4_host_name_get (&ipv4_structure, host_name);
  }

  //  pci_init (&pci_structure, &empty_tag);

  console_use_keyboard (&console_structure, TRUE, CONSOLE_KEYBOARD_NORMAL);

  console_attribute_set (&console_structure, CONSOLE_COLOUR_GRAY,
                         CONSOLE_COLOUR_BLUE, CONSOLE_ATTRIBUTE_RESET);
  console_clear (&console_structure);

  /* FIXME: This should not be put in cluido, really... */

  console_print (&console_structure, "\

Внимание! Это пререлиз ОС chaos. Ожидайте системные крахи и необычное поведение. 
От вас, как от пользователя, не требуется исправлять незначительные 'баги' и
присылать нам 'патчи', обычно ошибки бывают исправлены, когда исправления 
доходят до нас. Если вы все таки нашли серьёзную ошибку, пожалуйста, пошлите
отчет на chaos-devel@lists.chaosdev.org и мы попытемся исправить её. Спасибо 
вам за интерес к нашему проекту.\n");

  console_print (&console_structure, "\

    \e[1mcluido версия 0.0.1, Copyright (C) 1998-2000 chaos development.
    cluido и остальные части chaos`а распространяются БЕЗ ВСЯКИХ ГАРАНТИЙ.
    Это свободно распространяемое программное обеспечение, и приветствуется его
    распространение на некоторых условиях; за дополнительной информацией 
    обращайтесь к GNU GPL.\e[0;44m\n");

  console_print (&console_structure, "\

Это cluido, (Command Line User Interface) Пользовательский Интерфейс Коммандной
Строки. Для получения дополнительной информации о доступных коммандах, наберите
'help' или '?'. Вы также можете переключаться между виртуальными консолями 
используя ALT+TAB. Чтобы 'привязать' консоль к функциональной клавише 
используйте CTRL+ALT+Fn. Позже на такую консоль можно переключиться нажатием 
ALT+Fn. Консоли с голубым фоном являются оболочками, точно как эта, а консоли с
чернам фоном - журнальными консолями (один для серверов и один для ядра). Если
tornado будет написан, то  он будет иметь собственную графическую консоль с
перемещаемым курсором 'мыши'.

Доступны некоторые 'связывания' Emacs (C-a, C-e, и т.д.) и аналогичные 
DOS`осовские (Home, End, стрелки). Вы можете перемещаться вперед и назад по 
истории команд с помощю клавиш 'вверх' и 'вниз'.\n\n"); 

  main_loop ();
  return 0;
}
