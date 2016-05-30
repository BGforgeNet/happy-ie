GET_OFFSET_ARRAY h_array ITM_V10_HEADERS
PHP_EACH h_array AS int => h_off BEGIN
  READ_BYTE h_off attack_type
  READ_SHORT (h_off + 0x2a) projectile
  PATCH_IF attack_type = 1 AND projectile != 1 BEGIN
    PATCH_PRINT ~%SOURCE_FILE% issue: melee header %int% uses projectile %projectile%. Changed to 1 (none).~
    WRITE_SHORT (h_off + 0x2a) 1
  END
END
