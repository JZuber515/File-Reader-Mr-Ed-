# File-Reader-Mr-Ed-
A line-based editor maintains the concept
of the current line within a buffer that holds
the text. The ed editor stores the text line-by-line
as a sequence of text strings, and the
user can move the current line forward or back
one or more lines up to the limit of the
start and end of the buffer.

This uses a doubly linked list with a cursor that
holds a reference to one of its elements in order
to parse through the given file.

There are also 2 test files that test the doubly
linked list for functionality.
