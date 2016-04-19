FOR (i=0;i<100;i=i+1) BEGIN
  READ_LONG (0xa4 + i * 4) strref
  PATCH_MATCH strref WITH
    0
    BEGIN
      PATCH_PRINT ~%SOURCE_FILE% issue: invalid soundset entry in slot %i%. Nulling.~
      WRITE_LONG (0xa4 + i * 4) (0 - 1)
    END
    (0 - 1) BEGIN END
    DEFAULT
      GET_STRREF_S strref sound
      PATCH_IF (~%sound%~ STRING_EQUAL ~~) BEGIN
        PATCH_PRINT ~%SOURCE_FILE% issue: invalid soundset entry in slot %i%. Nulling.~
        WRITE_LONG (0xa4 + i * 4) (0 - 1)
      END
  END
END
