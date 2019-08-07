// Container Content Validator
READ_LONG  0x70 "cont_off" ELSE 0
READ_SHORT 0x74 "cont_num" ELSE 0
READ_SHORT 0x76 "itm_num"  ELSE 0
READ_LONG  0x78 "itm_off"  ELSE 0

PATCH_IF (cont_off > 0x11b) BEGIN
  FOR (index = 0 ; index < cont_num ; index = index + 1) BEGIN

    // Non-empty containers that aren't visible get their items dropped on the ground
    READ_SHORT ("%cont_off%" + 0x24 + (0xc0 * "%index%")) "cont_type"
    READ_SHORT ("%cont_off%" + 0x38 + (0xc0 * "%index%")) "bound_a"
    READ_SHORT ("%cont_off%" + 0x3a + (0xc0 * "%index%")) "bound_b"
    READ_SHORT ("%cont_off%" + 0x3c + (0xc0 * "%index%")) "bound_c"
    READ_SHORT ("%cont_off%" + 0x3e + (0xc0 * "%index%")) "bound_d"
    READ_LONG  ("%cont_off%" + 0x44 + (0xc0 * "%index%")) "cont_itm_num"
    PATCH_IF ("%bound_a%" = 0) AND ("%bound_b%" = 0) AND ("%bound_c%" = 0) AND ("%bound_d%" = 0) AND ("%cont_type%" != 4) AND ("%cont_itm_num%" > 0) BEGIN
      WRITE_SHORT ("%cont_off%" + 0x24 + (0xc0 * "%index%")) 4
      PATCH_PRINT "HW4: %SOURCE_FILE% - Container #%index% has no bounding box but contains items! Dropping all items to ground..."
    END

    // Invalid container content checker
    READ_LONG  ("%cont_off%" + 0x40 + (0xc0 * "%index%")) "cont_itm_idx"
    READ_LONG  ("%cont_off%" + 0x44 + (0xc0 * "%index%")) "cont_itm_num"
    FOR (index2 = 0 ; index2 < cont_itm_num ; index2 = index2 + 1) BEGIN
      READ_ASCII ("%itm_off%" + (("%index2%" + "%cont_itm_idx%") * 0x14)) "resref"
      SET "exists" = 0
      PATCH_IF FILE_EXISTS_IN_GAME ~%resref%.itm~ BEGIN
        SET "exists" = 1
      END
      PATCH_IF ("%exists%" = 0) BEGIN
        SET "converted" = 0
        PHP_EACH tutu_convert_itm AS tutu_itm => bgt_itm BEGIN
          PATCH_IF ("%resref%" STR_EQ "%tutu_itm%") AND (FILE_EXISTS_IN_GAME "%bgt_itm%.itm") BEGIN
            WRITE_ASCIIE ("%itm_off%" + (("%index2%" + "%cont_itm_idx%") * 0x14)) "%bgt_itm%" #8
            SET "converted" = 1
            PATCH_PRINT "HW5: %SOURCE_FILE% - Container #%index% Item #%index2% had Tutu item! (%resref% -> %bgt_itm%)!"
          END
        END
        PATCH_IF ("%converted%" = 0) BEGIN
          PATCH_PRINT "HI15: %SOURCE_FILE% - Container #%index% Item #%index2% does not exist (%resref%.itm)! Removing Item #%index2%..."
          LPF  ~fj_are_structure~
            INT_VAR fj_delete_mode    = "%index2%" + "%cont_itm_idx%"
            STR_VAR fj_structure_type = ~itm~
          END
          READ_LONG  0x70 "cont_off" ELSE 0
          READ_SHORT 0x74 "cont_num" ELSE 0
          READ_SHORT 0x76 "itm_num"  ELSE 0
          READ_LONG  0x78 "itm_off"  ELSE 0
          READ_LONG  ("%cont_off%" + 0x44 + (0xc0 * "%index%")) "cont_itm_num"
          SET index = 0 - 1
          SET index2 = cont_itm_num
        END
      END
    END

  END
END
