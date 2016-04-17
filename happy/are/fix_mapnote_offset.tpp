READ_LONG  0xc0 "rest_off" ELSE 0
READ_LONG  0xc4 "note_off" ELSE 0
READ_LONG  0xc8 "note_num" ELSE 213
PATCH_IF (("%note_num%" = 0) AND ("%note_off%" != ("%rest_off%" + 0xe4))) BEGIN
  WRITE_LONG 0xc4 ("%rest_off%" + 0xe4)
END
