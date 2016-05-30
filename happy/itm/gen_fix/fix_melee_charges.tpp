GET_OFFSET_ARRAY h_array ITM_V10_HEADERS
PHP_EACH h_array AS int => h_off BEGIN
  READ_BYTE h_off attack_type
  READ_SHORT (h_off + 0x22) charges
  READ_SHORT (h_off + 0x24) charge_behavior
  PATCH_IF attack_type = 1 BEGIN
/* staff of striking, neb's dagger, touch spell weapons
    PATCH_IF charges != 0 BEGIN
      PATCH_PRINT ~%SOURCE_FILE% issue: melee header %int% has non-zero charges. Changed to 0.~
      WRITE_SHORT (h_off + 0x22) 0
    END
*/
    PATCH_IF charge_behavior = 3 BEGIN
      PATCH_PRINT ~%SOURCE_FILE% issue: melee header %int% recharges daily. Changed to 1 (vanish).~
      WRITE_SHORT (h_off + 0x24) 1
    END
  END
END
