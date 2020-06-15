READ_BYTE  0x18 flags //need only bit 6
READ_SHORT 0x1c type
READ_BYTE  0x31 proficiency
READ_LONG  0x60 enchantment
magic_flag = (flags BAND 0b01000000) >> 6
PATCH_IF (enchantment != 0 AND magic_flag = 0) AND VARIABLE_IS_SET $item_type(~%type%~) BEGIN
  PATCH_PRINT ~HI60: %SOURCE_FILE% - magic flag %magic_flag% and enchantment level %enchantment% are inconsistent. Setting magic flag.~
  new_flags = flags BOR 0b01000000
  WRITE_BYTE 0x18 new_flags
END
PATCH_IF enchantment = 0
  AND magic_flag != 0
  AND VARIABLE_IS_SET $item_type(~%type%~)
  AND NOT (~%SOURCE_FILE%~ STR_EQ ~aegis.itm~)
  AND NOT (~%SOURCE_FILE%~ STR_EQ ~aegis2.itm~) // skip aegis for now, see https://github.com/Gibberlings3/BG2-Fixpack/pull/7
BEGIN
  PATCH_PRINT ~HI61: %SOURCE_FILE% - magic flag %magic_flag% and enchantment level %enchantment% are inconsistent.~
END
