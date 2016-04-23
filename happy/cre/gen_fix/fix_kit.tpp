READ_SHORT 0x244 kit0
READ_SHORT 0x246 kit1
kit = (kit0 BLSL 16) + kit1

LOOKUP_IDS_SYMBOL_OF_INT kit_id ~kit~ kit

PATCH_IF ((kit != 0) AND (~%kit_id%~ STRING_EQUAL ~%kit%~)) BEGIN
  PATCH_PRINT ~%SOURCE_FILE% issue: unknown kit %kit%. Changing to True Class.~
  WRITE_LONG 0x244 0x40000000
END
