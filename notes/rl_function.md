Function: void **rl_clear_history** _(void)_

Clear the history list by deleting all of the entries, in the same manner as the History library's `clear_history()` function. This differs from `clear_history` because it frees private data Readline saves in the history list.

Function: int **rl_on_new_line** _(void)_

Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.

Function: void **rl_replace_line** _(const char *text, int clear_undo)_

Replace the contents of `rl_line_buffer` with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.

Function: void **rl_redisplay** _(void)_

Change what's displayed on the screen to reflect the current contents of `rl_line_buffer`.

