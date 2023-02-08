READ_LONG  ITM_flags flags
READ_SHORT ITM_type type
READ_BYTE  ITM_weapon_proficiency proficiency
READ_LONG  ITM_enchantment enchantment

magic_flag = flags BAND BIT6

PATCH_IF (enchantment != 0 AND magic_flag = 0) AND VARIABLE_IS_SET $item_type(~%type%~) BEGIN
  PATCH_PRINT ~HI60: %SOURCE_FILE% - magical flag bit 6 and enchantment level %enchantment% are inconsistent. Setting magic flag.~
  new_flags = flags BOR BIT6
  WRITE_LONG ITM_flags new_flags
END
PATCH_IF enchantment = 0
  AND magic_flag != 0
  AND VARIABLE_IS_SET $item_type(~%type%~)
  AND NOT (GAME_IS "bg2ee eet" AND (~%SOURCE_FILE%~ STR_EQ ~ax1h07.itm~))  // bala's axe
  AND NOT ((GAME_IS "bgee eet" OR GAME_INCLUDES ~sod~) AND (~%SOURCE_FILE%~ STR_EQ ~staf25.itm~))  // ossifier
BEGIN
  PATCH_PRINT ~HI61: %SOURCE_FILE% - magical flag bit 6 and enchantment level %enchantment% are inconsistent.~
END
