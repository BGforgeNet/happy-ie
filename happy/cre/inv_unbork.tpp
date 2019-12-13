READ_LONG  0x2b8 "slot_off" ELSE 0
READ_LONG  0x2bc "itm_off" ELSE 0
READ_SHORT 0x2c0 "itm_num" ELSE 0

PATCH_IF ("slot_off" > 0x2d3) BEGIN
  FOR (index = 0 ; index < 37 ; index = index + 1) BEGIN
    READ_SHORT ("%slot_off%" + (0x02 * "%index%")) "ref" ELSE 0xffff
    PATCH_IF ("%ref%" != 0xffff) BEGIN
      PATCH_IF ((%ref% + 1) > %itm_num%) BEGIN
        PATCH_PRINT "HI24: %SOURCE_FILE% - Inventory Item Slot #%index% refers to an item outside the Item Table! Setting to -1..."
        WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
      END
    END
  END
END
PATCH_IF (("slot_off" > 0x2d3) AND ("itm_off" > 0x2d3)) BEGIN
  FOR (index = 0 ; index < itm_num ; index = index + 1) BEGIN
    SET "critical" = 0
    SET "found" = 0
    SET "foundslot" = 0
    FOR (index1 = 0 ; index1 < 37 && found = 0 ; index1 = index1 + 1) BEGIN
      READ_SHORT ("%slot_off%" + (0x02 * "%index1%")) "ref" ELSE 0xffff
      PATCH_IF (%index% = %ref%) BEGIN
        SET "found" = 1
      END
    END
    PATCH_IF (%found% = 0) BEGIN
      READ_ASCII ("%itm_off%" + (0x14 * "%index%")) "item"
      PATCH_IF FILE_EXISTS_IN_GAME ~%item%.itm~ BEGIN
        INNER_PATCH_FILE ~%item%.itm~ BEGIN
          READ_BYTE  0x18 "flags"
          READ_SHORT 0x1c "type"
          READ_LONG  0x34 "price"
          PATCH_IF ("%item%" STRING_COMPARE_REGEXP "^[Rr][Nn][Dd].+$") AND ((("%flags%" BAND 0b00000001) = 0b00000001) OR ((%type% = 0) AND (%price% = 0))) BEGIN
            SET "critical" = 1
          END
        END
      END
      PATCH_IF %critical% = 1 BEGIN
        PATCH_PRINT "HE4: %SOURCE_FILE% - Inventory Item #%index% (%item%.ITM) is not actually in inventory! Potentially quest-breaking item! Removing..."
        REMOVE_CRE_ITEM ~%item%~
        SET "index" = 0 - 1
        READ_LONG  0x2b8 "slot_off" ELSE 0
        READ_LONG  0x2bc "itm_off" ELSE 0
        READ_SHORT 0x2c0 "itm_num" ELSE 0
      END ELSE
      BEGIN
        FOR (index1 = 21 ; index1 < 37 && foundslot = 0 ; index1 = index1 + 1) BEGIN
          READ_SHORT ("%slot_off%" + (0x02 * "%index1%")) "ref" ELSE 0xffff
          PATCH_IF ("%ref%" = 0xffff) BEGIN
            SET "foundslot" = "index1"
          END
        END
        PATCH_IF ("%foundslot%" > 0) BEGIN
          PATCH_PRINT "HW86: %SOURCE_FILE% - Inventory Item #%index% (%item%.ITM) is not actually in inventory! Adding to Inventory Slot #%foundslot%..."
          WRITE_SHORT ("%slot_off%" + (0x02 * "%foundslot%")) "index"
        END ELSE
        BEGIN
          FOR (index1 = 0 ; index1 < 22 && foundslot = 0 ; index1 = index1 + 1) BEGIN
            READ_SHORT ("%slot_off%" + (0x02 * "%index1%")) "ref" ELSE 0xffff
            PATCH_IF ("%ref%" = 0xffff) BEGIN
              SET "foundslot" = "index1"
            END
          END
          PATCH_PRINT "HW87: %SOURCE_FILE% - Inventory Item #%index% (%item%.ITM) is not actually in inventory! No free inventory slot found! Adding to Slot #%foundslot%..."
          WRITE_SHORT ("%slot_off%" + (0x02 * "%foundslot%")) "index"
        END
      END
    END
  END
END
