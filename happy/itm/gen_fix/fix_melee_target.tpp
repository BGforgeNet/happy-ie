GET_OFFSET_ARRAY h_array ITM_V10_HEADERS
PHP_EACH h_array AS int => h_off BEGIN
  READ_BYTE h_off attack_type
  READ_BYTE (h_off + 0xc) target
  PATCH_IF attack_type = 1 AND projectile != 1 BEGIN
    PATCH_PRINT ~HI42: %SOURCE_FILE% issue: melee header %int% uses target %target%. Changed to 1 (creature).~
    WRITE_SHORT (h_off + 0xc) 1
  END
END
