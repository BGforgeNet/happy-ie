FOR (i=0;i<100;i=i+1) BEGIN
  READ_LONG (0xa4 + i * 4) strref
  PATCH_IF (strref == 0) BEGIN
    PATCH_PRINT ~%SOURCE_FILE% issue: invalid sound reference in slot %i%. Nulling.~
    WRITE_LONG (0xa4 + i * 4) (0 - 1)
  END
END
