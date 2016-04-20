CLEAR_ARRAY effects
GET_OFFSET_ARRAY effects CRE_V10_EFFECTS
PHP_EACH effects AS int => off BEGIN
  READ_LONG (off+0x8) opcode
  PATCH_IF (opcode = 206) BEGIN //protection from spell
    READ_ASCII (off+0x28) spell
    PATCH_IF NOT FILE_EXISTS_IN_GAME ~%spell%.spl~ BEGIN
      PATCH_PRINT ~%SOURCE_FILE% issue: protection from non-existent spell %spell%. Removing~
    END
  END
END
