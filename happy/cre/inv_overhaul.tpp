READ_LONG  0x2b8 "slot_off" ELSE 0
READ_LONG  0x2bc "itm_off" ELSE 0

// tracking variables
SET "2hweapon" = 0
SET "offhand" = 0
SET "bow" = 0
SET "arrows" = 0
SET "xbow" = 0
SET "bolts" = 0
SET "sling" = 0
SET "bullets" = 0
SET "helm" = 0
SET "armor" = 0
SET "gloves" = 0
SET "lring" = 0
SET "rring" = 0
SET "boots" = 0
SET "belt" = 0
SET "amulet" = 0
SET "weapon1" = 0
SET "weapon2" = 0
SET "weapon3" = 0
SET "weapon4" = 0
SET "quiver1" = 0
SET "quiver2" = 0
SET "quiver3" = 0
SET "quiver4" = 0
SET "cloak" = 0
SET "2handedequip" = 0
PATCH_IF (("slot_off" > 0x2d3) AND ("itm_off" > 0x2d3)) BEGIN
  FOR (index = 0 ; index < 36 ; index = index + 1) BEGIN
    READ_SHORT ("%slot_off%" + (0x02 * "%index%")) "ref"
    PATCH_IF ("%ref%" != 0xffff) BEGIN
      READ_ASCII ("%itm_off%" +        (0x14 * "%ref%")) "item"
      READ_BYTE  ("%itm_off%" + 0x10 + (0x14 * "%ref%")) "cre_flags"
      PATCH_IF FILE_EXISTS_IN_GAME ~%item%.itm~ BEGIN
        INNER_PATCH_FILE ~%item%.itm~ BEGIN
          READ_SHORT 0x1c "type"
          READ_BYTE  0x18 "flags"
        END
        PATCH_IF ("%index%" = 0) BEGIN // helm slot
          SET "helm" = 1
          PATCH_IF (("%type%" != 7) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND (("%cre_flags%" BAND 0b00001000) = 0b00000000) BEGIN // helm
            SET "ref2" = 1
            FOR (index3 = 21 ; ref2 != 0xffff && index3 < 37 ; index3 = index3 + 1) BEGIN
              READ_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref2"
            END
            SET "index3" = "index3" - 1
            PATCH_IF ("%ref2%" = 0xffff) BEGIN
              SET "slot" = "index3" - 20
              PATCH_PRINT ~HW35: %SOURCE_FILE% - Invalid HELM: %item%.itm! Moving to Inventory Slot #%slot%~
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref"
              WRITE_BYTE  ("%itm_off%" + 0x10 + (0x14 * "%ref%")) ("%cre_flags%" BOR 0b00000010)
              SET "helm" = 0
              SET "index" = 0 - 1
            END ELSE
            BEGIN
              PATCH_PRINT ~HW36: %SOURCE_FILE% - Invalid HELM: %item%.itm! Cannot move because Inventory full!~
            END
          END
        END
        PATCH_IF ("%index%" = 1) BEGIN // armor slot
          SET "armor" = 1
          PATCH_IF (("%type%" != 2) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND (("%cre_flags%" BAND 0b00001000) = 0b00000000) BEGIN // armor
            SET "ref2" = 1
            FOR (index3 = 21 ; ref2 != 0xffff && index3 < 37 ; index3 = index3 + 1) BEGIN
              READ_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref2"
            END
            SET "index3" = "index3" - 1
            PATCH_IF ("%ref2%" = 0xffff) BEGIN
              SET "slot" = "index3" - 20
              PATCH_PRINT ~HW37: %SOURCE_FILE% - Invalid ARMOR: %item%.itm! Moving to Inventory Slot #%slot%~
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref"
              WRITE_BYTE  ("%itm_off%" + 0x10 + (0x14 * "%ref%")) ("%cre_flags%" BOR 0b00000010)
              SET "armor" = 0
              SET "index" = 0 - 1
            END ELSE
            BEGIN
              PATCH_PRINT ~HW39: %SOURCE_FILE% - Invalid ARMOR: %item%.itm! Cannot move because Inventory full!~
            END
          END
        END
        PATCH_IF ("%index%" = 2) BEGIN // shield slot
          SET "offhand" = 1
          PATCH_IF (("%flags%" BAND 0b00010110) = 0b00000110) AND (("%cre_flags%" BAND 0b00001000) = 0b00000000) BEGIN // 2h, uncursed and droppable check
            SET "ref2" = 1
            FOR (index3 = 21 ; ref2 != 0xffff && index3 < 37 ; index3 = index3 + 1) BEGIN
              READ_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref2"
            END
            SET "index3" = "index3" - 1
            PATCH_IF ("%ref2%" = 0xffff) BEGIN
              SET "slot" = "index3" - 20
              PATCH_PRINT ~HW40: %SOURCE_FILE% - 2-HANDED OFFHAND: %item%.itm! Moving to Inventory Slot #%slot%~
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref"
              WRITE_BYTE  ("%itm_off%" + 0x10 + (0x14 * "%ref%")) ("%cre_flags%" BOR 0b00000010)
              SET "offhand" = 0
              SET "index" = 0 - 1
            END ELSE
            BEGIN
              PATCH_PRINT ~HW41: %SOURCE_FILE% - 2-HANDED OFFHAND: %item%.itm! Cannot move because Inventory full!~
            END
          END ELSE
          PATCH_IF (("%type%" != 12) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND (("%cre_flags%" BAND 0b00001000) = 0b00000000) BEGIN // if not shield, check for valid melee abilities
            SET "legit_offhand" = 0
            INNER_PATCH_FILE ~%item%.itm~ BEGIN
              READ_LONG  0x64 "abil_off"
              READ_SHORT 0x68 "abil_num"
              FOR (index3 = 0 ; index3 < abil_num ; index3 = index3 + 1) BEGIN
                READ_BYTE ("%abil_off%" + (0x38 * "%index3%")) "ability"
                PATCH_IF ("%ability%" = 1) AND (%type% > 14) AND (%type% < 31) BEGIN // only melee weapons allowed in offhand
                  SET "legit_offhand" = 1
                END
              END
            END
            PATCH_IF ("%legit_offhand%" = 0) BEGIN
              SET "ref2" = 1
              FOR (index3 = 21 ; ref2 != 0xffff && index3 < 37 ; index3 = index3 + 1) BEGIN
                READ_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref2"
              END
              SET "index3" = "index3" - 1
              PATCH_IF ("%ref2%" = 0xffff) BEGIN
                SET "slot" = "index3" - 20
                PATCH_PRINT ~HW42: %SOURCE_FILE% - Invalid OFFHAND: %item%.itm! Moving to Inventory Slot #%slot%~
                WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
                WRITE_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref"
                WRITE_BYTE  ("%itm_off%" + 0x10 + (0x14 * "%ref%")) ("%cre_flags%" BOR 0b00000010)
                SET "offhand" = 0
                SET "index" = 0 - 1
              END ELSE
              BEGIN
                PATCH_PRINT ~HW43: %SOURCE_FILE% - Invalid OFFHAND: %item%.itm! Cannot move because Inventory full!~
              END
            END
          END ELSE
          PATCH_IF ("%type%" = 12) AND (("%flags%" BAND 0b00010100) = 0b00000100) BEGIN
            READ_SHORT ("%slot_off%" + (0x02 * 9))  "refa"
            READ_SHORT ("%slot_off%" + (0x02 * 10)) "refb"
            READ_SHORT ("%slot_off%" + (0x02 * 11)) "refc"
            READ_SHORT ("%slot_off%" + (0x02 * 12)) "refd"
            PATCH_IF ("%refa%" != 0xffff) BEGIN
              READ_ASCII ("%itm_off%" + (0x14 * "%refa%")) "item1"
              PATCH_IF FILE_EXISTS_IN_GAME ~%item1%.itm~ BEGIN
                INNER_PATCH_FILE ~%item1%.itm~ BEGIN
                  READ_SHORT 0x1c "type1"
                  READ_BYTE  0x18 "flags1"
                  PATCH_IF (("%flags1%" BAND 0b00000010) = 0b00000010) AND ((%type1% > 14) AND (%type1% < 31)) BEGIN
                    SET "2handedequip" = 1
                  END
                END
              END
            END
            PATCH_IF ("%refb%" != 0xffff) BEGIN
              READ_ASCII ("%itm_off%" + (0x14 * "%refb%")) "item2"
              PATCH_IF FILE_EXISTS_IN_GAME ~%item2%.itm~ BEGIN
                INNER_PATCH_FILE ~%item2%.itm~ BEGIN
                  READ_SHORT 0x1c "type2"
                  READ_BYTE  0x18 "flags2"
                  PATCH_IF (("%flags2%" BAND 0b00000010) = 0b00000010) AND ((%type2% > 14) AND (%type2% < 31)) BEGIN
                    SET "2handedequip" = 1
                  END
                END
              END
            END
            PATCH_IF ("%refc%" != 0xffff) BEGIN
              READ_ASCII ("%itm_off%" + (0x14 * "%refc%")) "item3"
              PATCH_IF FILE_EXISTS_IN_GAME ~%item3%.itm~ BEGIN
                INNER_PATCH_FILE ~%item3%.itm~ BEGIN
                  READ_SHORT 0x1c "type3"
                  READ_BYTE  0x18 "flags3"
                  PATCH_IF (("%flags3%" BAND 0b00000010) = 0b00000010) AND ((%type3% > 14) AND (%type3% < 31)) BEGIN
                    SET "2handedequip" = 1
                  END
                END
              END
            END
            PATCH_IF ("%refd%" != 0xffff) BEGIN
              READ_ASCII ("%itm_off%" + (0x14 * "%refd%")) "item4"
              PATCH_IF FILE_EXISTS_IN_GAME ~%item4%.itm~ BEGIN
                INNER_PATCH_FILE ~%item4%.itm~ BEGIN
                  READ_SHORT 0x1c "type4"
                  READ_BYTE  0x18 "flags4"
                  PATCH_IF (("%flags4%" BAND 0b00000010) = 0b00000010) AND ((%type4% > 14) AND (%type4% < 31)) BEGIN
                    SET "2handedequip" = 1
                  END
                END
              END
            END
            PATCH_IF ("%2handedequip%" = 1) BEGIN
              SET "ref2" = 1
              FOR (index3 = 21 ; ref2 != 0xffff && index3 < 37 ; index3 = index3 + 1) BEGIN
                READ_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref2"
              END
              SET "index3" = "index3" - 1
              PATCH_IF ("%ref2%" = 0xffff) BEGIN
                SET "slot" = "index3" - 20
                PATCH_PRINT ~%SOURCE_FILE% - OFFHAND with 2-HAND: %item%.itm! Moving to Inventory Slot #%slot%~
                WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
                WRITE_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref"
                WRITE_BYTE  ("%itm_off%" + 0x10 + (0x14 * "%ref%")) ("%cre_flags%" BOR 0b00000010)
                SET "offhand" = 0
                SET "index" = 0 - 1
              END ELSE
              BEGIN
                PATCH_PRINT ~HW44: %SOURCE_FILE% - OFFHAND with 2-HAND: %item%.itm! Cannot move because Inventory full!~
              END
            END
          END
        END
        PATCH_IF ("%index%" = 3) BEGIN // glove slot
          SET "gloves" = 1
          PATCH_IF (("%type%" != 6) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND (("%cre_flags%" BAND 0b00001000) = 0b00000000) BEGIN // gloves
            SET "ref2" = 1
            FOR (index3 = 21 ; ref2 != 0xffff && index3 < 37 ; index3 = index3 + 1) BEGIN
              READ_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref2"
            END
            SET "index3" = "index3" - 1
            PATCH_IF ("%ref2%" = 0xffff) BEGIN
              SET "slot" = "index3" - 20
              PATCH_PRINT ~HW45: %SOURCE_FILE% - Invalid GLOVES: %item%.itm! Moving to Inventory Slot #%slot%~
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref"
              WRITE_BYTE  ("%itm_off%" + 0x10 + (0x14 * "%ref%")) ("%cre_flags%" BOR 0b00000010)
              SET "gloves" = 0
              SET "index" = 0 - 1
            END ELSE
            BEGIN
              PATCH_PRINT ~HW46: %SOURCE_FILE% - Invalid GLOVES: %item%.itm! Cannot move because Inventory full!~
            END
          END
        END
        PATCH_IF ("%index%" = 4) BEGIN // left ring slot
          SET "lring" = 1
          PATCH_IF (("%type%" != 10) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND (("%cre_flags%" BAND 0b00001000) = 0b00000000) BEGIN // rings
            SET "ref2" = 1
            FOR (index3 = 21 ; ref2 != 0xffff && index3 < 37 ; index3 = index3 + 1) BEGIN
              READ_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref2"
            END
            SET "index3" = "index3" - 1
            PATCH_IF ("%ref2%" = 0xffff) BEGIN
              SET "slot" = "index3" - 20
              PATCH_PRINT ~HW47: %SOURCE_FILE% - Invalid LRING: %item%.itm! Moving to Inventory Slot #%slot%~
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref"
              WRITE_BYTE  ("%itm_off%" + 0x10 + (0x14 * "%ref%")) ("%cre_flags%" BOR 0b00000010)
              SET "lring" = 0
              SET "index" = 0 - 1
            END ELSE
            BEGIN
              PATCH_PRINT ~HW48: %SOURCE_FILE% - Invalid LRING: %item%.itm! Cannot move because Inventory full!~
            END
          END
        END
        PATCH_IF ("%index%" = 5) BEGIN // right ring slot
          SET "rring" = 1
          PATCH_IF (("%type%" != 10) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND (("%cre_flags%" BAND 0b00001000) = 0b00000000) BEGIN // rings
            SET "ref2" = 1
            FOR (index3 = 21 ; ref2 != 0xffff && index3 < 37 ; index3 = index3 + 1) BEGIN
              READ_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref2"
            END
            SET "index3" = "index3" - 1
            PATCH_IF ("%ref2%" = 0xffff) BEGIN
              SET "slot" = "index3" - 20
              PATCH_PRINT ~HW49: %SOURCE_FILE% - Invalid RRING: %item%.itm! Moving to Inventory Slot #%slot%~
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref"
              WRITE_BYTE  ("%itm_off%" + 0x10 + (0x14 * "%ref%")) ("%cre_flags%" BOR 0b00000010)
              SET "rring" = 0
              SET "index" = 0 - 1
            END ELSE
            BEGIN
              PATCH_PRINT ~HW50: %SOURCE_FILE% - Invalid RRING: %item%.itm! Cannot move because Inventory full!~
            END
          END
        END
        PATCH_IF ("%index%" = 6) BEGIN // amulet slot
          SET "amulet" = 1
          PATCH_IF (("%type%" != 1) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND (("%cre_flags%" BAND 0b00001000) = 0b00000000) BEGIN // amulet
            SET "ref2" = 1
            FOR (index3 = 21 ; ref2 != 0xffff && index3 < 37 ; index3 = index3 + 1) BEGIN
              READ_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref2"
            END
            SET "index3" = "index3" - 1
            PATCH_IF ("%ref2%" = 0xffff) BEGIN
              SET "slot" = "index3" - 20
              PATCH_PRINT ~HW51: %SOURCE_FILE% - Invalid AMULET: %item%.itm! Moving to Inventory Slot #%slot%~
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref"
              WRITE_BYTE  ("%itm_off%" + 0x10 + (0x14 * "%ref%")) ("%cre_flags%" BOR 0b00000010)
              SET "amulet" = 0
              SET "index" = 0 - 1
            END ELSE
            BEGIN
              PATCH_PRINT ~HW52: %SOURCE_FILE% - Invalid AMULET: %item%.itm! Cannot move because Inventory full!~
            END
          END
        END
        PATCH_IF ("%index%" = 7) BEGIN // belt slot
          SET "belt" = 1
          PATCH_IF (("%type%" != 3) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND (("%cre_flags%" BAND 0b00001000) = 0b00000000) BEGIN // belt
            SET "ref2" = 1
            FOR (index3 = 21 ; ref2 != 0xffff && index3 < 37 ; index3 = index3 + 1) BEGIN
              READ_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref2"
            END
            SET "index3" = "index3" - 1
            PATCH_IF ("%ref2%" = 0xffff) BEGIN
              SET "slot" = "index3" - 20
              PATCH_PRINT ~HW53: %SOURCE_FILE% - Invalid BELT: %item%.itm! Moving to Inventory Slot #%slot%~
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref"
              WRITE_BYTE  ("%itm_off%" + 0x10 + (0x14 * "%ref%")) ("%cre_flags%" BOR 0b00000010)
              SET "belt" = 0
              SET "index" = 0 - 1
            END ELSE
            BEGIN
              PATCH_PRINT ~HW54: %SOURCE_FILE% - Invalid BELT: %item%.itm! Cannot move because Inventory full!~
            END
          END
        END
        PATCH_IF ("%index%" = 8) BEGIN // boot slot
          SET "boots" = 1
          PATCH_IF (("%type%" != 4) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND (("%cre_flags%" BAND 0b00001000) = 0b00000000) BEGIN // boot
            SET "ref2" = 1
            FOR (index3 = 21 ; ref2 != 0xffff && index3 < 37 ; index3 = index3 + 1) BEGIN
              READ_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref2"
            END
            SET "index3" = "index3" - 1
            PATCH_IF ("%ref2%" = 0xffff) BEGIN
              SET "slot" = "index3" - 20
              PATCH_PRINT ~HW55: %SOURCE_FILE% - Invalid BOOTS: %item%.itm! Moving to Inventory Slot #%slot%~
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref"
              WRITE_BYTE  ("%itm_off%" + 0x10 + (0x14 * "%ref%")) ("%cre_flags%" BOR 0b00000010)
              SET "boots" = 0
              SET "index" = 0 - 1
            END ELSE
            BEGIN
              PATCH_PRINT ~HW56: %SOURCE_FILE% - Invalid BOOTS: %item%.itm! Cannot move because Inventory full!~
            END
          END
        END
        PATCH_IF ("%index%" = 9) BEGIN // first weapon slot
          SET "weapon1" = 1
          SET "legit_weapon" = 0
          INNER_PATCH_FILE ~%item%.itm~ BEGIN
            READ_BYTE  0x18 "flags"
            READ_LONG  0x64 "abil_off"
            READ_SHORT 0x68 "abil_num"
            FOR (index3 = 0 ; index3 < abil_num ; index3 = index3 + 1) BEGIN
              READ_BYTE ("%abil_off%" + (0x38 * "%index3%")) "ability"
              PATCH_IF (("%ability%" = 1) OR ("%ability%" = 2) OR ("%ability%" = 4)) AND ("%type%" > 14) AND ("%type%" < 31) BEGIN // melee, ranged, or launcher
                SET "legit_weapon" = 1
              END
            END
            PATCH_IF (("%legit_weapon%" = 1) AND (("%flags%" BAND 0b00000010) = 0b00000010)) BEGIN // 2h check
                SET "2handedequip" = 1
            END
          END
          PATCH_IF (("%legit_weapon%" = 0) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND (("%cre_flags%" BAND 0b00001000) = 0b00000000) BEGIN
            SET "ref2" = 1
            FOR (index3 = 21 ; ref2 != 0xffff && index3 < 37 ; index3 = index3 + 1) BEGIN
              READ_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref2"
            END
            SET "index3" = "index3" - 1
            PATCH_IF ("%ref2%" = 0xffff) BEGIN
              SET "slot" = "index3" - 20
              PATCH_PRINT ~HW57: %SOURCE_FILE% - Invalid WEAPON1: %item%.itm! Moving to Inventory Slot #%slot%~
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref"
              WRITE_BYTE  ("%itm_off%" + 0x10 + (0x14 * "%ref%")) ("%cre_flags%" BOR 0b00000010)
              SET "weapon1" = 0
              SET "index" = 0 - 1
            END ELSE
            BEGIN
              PATCH_PRINT ~HW58: %SOURCE_FILE% - Invalid WEAPON1: %item%.itm! Cannot move because Inventory full!~
            END
          END
        END
        PATCH_IF ("%index%" = 10) BEGIN // second weapon slot
          SET "weapon2" = 1
          SET "legit_weapon" = 0
          INNER_PATCH_FILE ~%item%.itm~ BEGIN
            READ_BYTE  0x18 "flags"
            READ_LONG  0x64 "abil_off"
            READ_SHORT 0x68 "abil_num"
            FOR (index3 = 0 ; index3 < abil_num ; index3 = index3 + 1) BEGIN
              READ_BYTE ("%abil_off%" + (0x38 * "%index3%")) "ability"
              PATCH_IF (("%ability%" = 1) OR ("%ability%" = 2) OR ("%ability%" = 4)) AND ("%type%" > 14) AND ("%type%" < 31) BEGIN // melee, ranged, or launcher
                SET "legit_weapon" = 1
              END
            END
            PATCH_IF (("%legit_weapon%" = 1) AND (("%flags%" BAND 0b00000010) = 0b00000010)) BEGIN // 2h check
                SET "2handedequip" = 1
            END
          END
          PATCH_IF (("%legit_weapon%" = 0) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND (("%cre_flags%" BAND 0b00001000) = 0b00000000) BEGIN
            SET "ref2" = 1
            FOR (index3 = 21 ; ref2 != 0xffff && index3 < 37 ; index3 = index3 + 1) BEGIN
              READ_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref2"
            END
            SET "index3" = "index3" - 1
            PATCH_IF ("%ref2%" = 0xffff) BEGIN
              SET "slot" = "index3" - 20
              PATCH_PRINT ~HW59: %SOURCE_FILE% - Invalid WEAPON2: %item%.itm! Moving to Inventory Slot #%slot%~
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref"
              WRITE_BYTE  ("%itm_off%" + 0x10 + (0x14 * "%ref%")) ("%cre_flags%" BOR 0b00000010)
              SET "weapon2" = 0
              SET "index" = 0 - 1
            END ELSE
            BEGIN
              PATCH_PRINT ~HW60: %SOURCE_FILE% - Invalid WEAPON2: %item%.itm! Cannot move because Inventory full!~
            END
          END
        END
        PATCH_IF ("%index%" = 11) BEGIN // third weapon slot
          SET "weapon3" = 1
          SET "legit_weapon" = 0
          INNER_PATCH_FILE ~%item%.itm~ BEGIN
            READ_BYTE  0x18 "flags"
            READ_LONG  0x64 "abil_off"
            READ_SHORT 0x68 "abil_num"
            FOR (index3 = 0 ; index3 < abil_num ; index3 = index3 + 1) BEGIN
              READ_BYTE ("%abil_off%" + (0x38 * "%index3%")) "ability"
              PATCH_IF (("%ability%" = 1) OR ("%ability%" = 2) OR ("%ability%" = 4)) AND ("%type%" > 14) AND ("%type%" < 31) BEGIN // melee, ranged, or launcher
                SET "legit_weapon" = 1
              END
            END
            PATCH_IF (("%legit_weapon%" = 1) AND (("%flags%" BAND 0b00000010) = 0b00000010)) BEGIN // 2h check
                SET "2handedequip" = 1
            END
          END
          PATCH_IF (("%legit_weapon%" = 0) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND (("%cre_flags%" BAND 0b00001000) = 0b00000000) BEGIN
            SET "ref2" = 1
            FOR (index3 = 21 ; ref2 != 0xffff && index3 < 37 ; index3 = index3 + 1) BEGIN
              READ_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref2"
            END
            SET "index3" = "index3" - 1
            PATCH_IF ("%ref2%" = 0xffff) BEGIN
              SET "slot" = "index3" - 20
              PATCH_PRINT ~HW61: %SOURCE_FILE% - Invalid WEAPON3: %item%.itm! Moving to Inventory Slot #%slot%~
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref"
              WRITE_BYTE  ("%itm_off%" + 0x10 + (0x14 * "%ref%")) ("%cre_flags%" BOR 0b00000010)
              SET "weapon3" = 0
              SET "index" = 0 - 1
            END ELSE
            BEGIN
              PATCH_PRINT ~HW62: %SOURCE_FILE% - Invalid WEAPON3: %item%.itm! Cannot move because Inventory full!~
            END
          END
        END
        PATCH_IF ("%index%" = 12) BEGIN // fourth weapon slot
          SET "weapon4" = 1
          SET "legit_weapon" = 0
          INNER_PATCH_FILE ~%item%.itm~ BEGIN
            READ_BYTE  0x18 "flags"
            READ_LONG  0x64 "abil_off"
            READ_SHORT 0x68 "abil_num"
            FOR (index3 = 0 ; index3 < abil_num ; index3 = index3 + 1) BEGIN
              READ_BYTE ("%abil_off%" + (0x38 * "%index3%")) "ability"
              PATCH_IF (("%ability%" = 1) OR ("%ability%" = 2) OR ("%ability%" = 4)) AND ("%type%" > 14) AND ("%type%" < 31) BEGIN // melee, ranged, or launcher
                SET "legit_weapon" = 1
              END
            END
            PATCH_IF (("%legit_weapon%" = 1) AND (("%flags%" BAND 0b00000010) = 0b00000010)) BEGIN // 2h check
                SET "2handedequip" = 1
            END
          END
          PATCH_IF (("%legit_weapon%" = 0) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND (("%cre_flags%" BAND 0b00001000) = 0b00000000) BEGIN
            SET "ref2" = 1
            FOR (index3 = 21 ; ref2 != 0xffff && index3 < 37 ; index3 = index3 + 1) BEGIN
              READ_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref2"
            END
            SET "index3" = "index3" - 1
            PATCH_IF ("%ref2%" = 0xffff) BEGIN
              SET "slot" = "index3" - 20
              PATCH_PRINT ~HW63: %SOURCE_FILE% - Invalid WEAPON4: %item%.itm! Moving to Inventory Slot #%slot%~
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref"
              WRITE_BYTE  ("%itm_off%" + 0x10 + (0x14 * "%ref%")) ("%cre_flags%" BOR 0b00000010)
              SET "weapon4" = 0
              SET "index" = 0 - 1
            END ELSE
            BEGIN
              PATCH_PRINT ~HW64: %SOURCE_FILE% - Invalid WEAPON4: %item%.itm! Cannot move because Inventory full!~
            END
          END
        END
        PATCH_IF ("%index%" = 13) BEGIN // first quiver slot
          SET "quiver1" = 1
          PATCH_IF (NOT (("%type%" = 5) OR ("%type%" = 31) OR ("%type%" = 14)) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND (("%cre_flags%" BAND 0b00001000) = 0b00000000) BEGIN
            SET "ref2" = 1
            FOR (index3 = 21 ; ref2 != 0xffff && index3 < 37 ; index3 = index3 + 1) BEGIN
              READ_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref2"
            END
            SET "index3" = "index3" - 1
            PATCH_IF ("%ref2%" = 0xffff) BEGIN
              SET "slot" = "index3" - 20
              PATCH_PRINT ~HW65: %SOURCE_FILE% - Invalid QUIVER1: %item%.itm! Moving to Inventory Slot #%slot%~
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref"
              WRITE_BYTE  ("%itm_off%" + 0x10 + (0x14 * "%ref%")) ("%cre_flags%" BOR 0b00000010)
              SET "quiver1" = 0
              SET "index" = 0 - 1
            END ELSE
            BEGIN
              PATCH_PRINT ~HW66: %SOURCE_FILE% - Invalid QUIVER1: %item%.itm! Cannot move because Inventory full!~
            END
          END
        END
        PATCH_IF ("%index%" = 14) BEGIN // second quiver slot
          SET "quiver2" = 1
          PATCH_IF (NOT (("%type%" = 5) OR ("%type%" = 31) OR ("%type%" = 14)) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND (("%cre_flags%" BAND 0b00001000) = 0b00000000) BEGIN
            SET "ref2" = 1
            FOR (index3 = 21 ; ref2 != 0xffff && index3 < 37 ; index3 = index3 + 1) BEGIN
              READ_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref2"
            END
            SET "index3" = "index3" - 1
            PATCH_IF ("%ref2%" = 0xffff) BEGIN
              SET "slot" = "index3" - 20
              PATCH_PRINT ~HW67: %SOURCE_FILE% - Invalid QUIVER2: %item%.itm! Moving to Inventory Slot #%slot%~
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref"
              WRITE_BYTE  ("%itm_off%" + 0x10 + (0x14 * "%ref%")) ("%cre_flags%" BOR 0b00000010)
              SET "quiver2" = 0
              SET "index" = 0 - 1
            END ELSE
            BEGIN
              PATCH_PRINT ~HW68: %SOURCE_FILE% - Invalid QUIVER2: %item%.itm! Cannot move because Inventory full!~
            END
          END
        END
        PATCH_IF ("%index%" = 15) BEGIN // third quiver slot
          SET "quiver3" = 1
          PATCH_IF (NOT (("%type%" = 5) OR ("%type%" = 31) OR ("%type%" = 14)) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND (("%cre_flags%" BAND 0b00001000) = 0b00000000) BEGIN
            SET "ref2" = 1
            FOR (index3 = 21 ; ref2 != 0xffff && index3 < 37 ; index3 = index3 + 1) BEGIN
              READ_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref2"
            END
            SET "index3" = "index3" - 1
            PATCH_IF ("%ref2%" = 0xffff) BEGIN
              SET "slot" = "index3" - 20
              PATCH_PRINT ~HW69: %SOURCE_FILE% - Invalid QUIVER3: %item%.itm! Moving to Inventory Slot #%slot%~
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref"
              WRITE_BYTE  ("%itm_off%" + 0x10 + (0x14 * "%ref%")) ("%cre_flags%" BOR 0b00000010)
              SET "quiver3" = 0
              SET "index" = 0 - 1
            END ELSE
            BEGIN
              PATCH_PRINT ~HW70: %SOURCE_FILE% - Invalid QUIVER3: %item%.itm! Cannot move because Inventory full!~
            END
          END
        END
        PATCH_IF ("%index%" = 16) BEGIN // fourth quiver slot
          SET "quiver4" = 1
          PATCH_IF (NOT (("%type%" = 5) OR ("%type%" = 31) OR ("%type%" = 14)) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND (("%cre_flags%" BAND 0b00001000) = 0b00000000) BEGIN
            SET "ref2" = 1
            FOR (index3 = 21 ; ref2 != 0xffff && index3 < 37 ; index3 = index3 + 1) BEGIN
              READ_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref2"
            END
            SET "index3" = "index3" - 1
            PATCH_IF ("%ref2%" = 0xffff) BEGIN
              SET "slot" = "index3" - 20
              PATCH_PRINT ~HW71: %SOURCE_FILE% - Invalid QUIVER4: %item%.itm! Moving to Inventory Slot #%slot%~
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref"
              WRITE_BYTE  ("%itm_off%" + 0x10 + (0x14 * "%ref%")) ("%cre_flags%" BOR 0b00000010)
              SET "quiver4" = 0
              SET "index" = 0 - 1
            END ELSE
            BEGIN
              PATCH_PRINT ~HW72: %SOURCE_FILE% - Invalid QUIVER4: %item%.itm! Cannot move because Inventory full!~
            END
          END
        END
        PATCH_IF ("%index%" = 17) BEGIN // cloak
          SET "cloak" = 1
          PATCH_IF (("%type%" != 32) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND (("%cre_flags%" BAND 0b00001000) = 0b00000000) BEGIN // cloak
            SET "ref2" = 1
            FOR (index3 = 21 ; ref2 != 0xffff && index3 < 37 ; index3 = index3 + 1) BEGIN
              READ_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref2"
            END
            SET "index3" = "index3" - 1
            PATCH_IF ("%ref2%" = 0xffff) BEGIN
              SET "slot" = "index3" - 20
              PATCH_PRINT ~HW73: %SOURCE_FILE% - Invalid CLOAK: %item%.itm! Moving to Inventory Slot #%slot%~
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
              WRITE_SHORT ("%slot_off%" + (0x02 * "%index3%")) "ref"
              WRITE_BYTE  ("%itm_off%" + 0x10 + (0x14 * "%ref%")) ("%cre_flags%" BOR 0b00000010)
              SET "cloak" = 0
              SET "index" = 0 - 1
            END ELSE
            BEGIN
              PATCH_PRINT ~HW74: %SOURCE_FILE% - Invalid CLOAK: %item%.itm! Cannot move because Inventory full!~
            END
          END
        END
        PATCH_IF ((("%type%" =  2) AND ("%armor%" = 0)) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND ("%index%" > 17) BEGIN
          PATCH_PRINT ~HW75: %SOURCE_FILE% - Equippable items in inventory: %item%.itm! Equipping ARMOR~
          WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
          WRITE_SHORT ("%slot_off%" + (0x02))             "ref"
          SET "armor" = 1
        END ELSE
        PATCH_IF (((("%type%" =  5) OR
                    ("%type%" = 14) OR
                    ("%type%" = 31)) AND ("%quiver1%" = 0) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND ("%index%" > 17)) BEGIN
          PATCH_PRINT ~%SOURCE_FILE% - Equippable items in inventory: %item%.itm! Equipping QUIVER1~
          WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
          WRITE_SHORT ("%slot_off%" + (0x02 * 13))        "ref"
          SET "quiver1" = 1
        END ELSE
        PATCH_IF (((("%type%" =  5) OR
                    ("%type%" = 14) OR
                    ("%type%" = 31)) AND ("%quiver2%" = 0) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND ("%index%" > 17)) BEGIN
          PATCH_PRINT ~HW76: %SOURCE_FILE% - Equippable items in inventory: %item%.itm! Equipping QUIVER2~
          WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
          WRITE_SHORT ("%slot_off%" + (0x02 * 14))        "ref"
          WRITE_BYTE  ("%itm_off%" + 0x10 + (0x14 * "%ref%")) ("%cre_flags%" BOR 0b00000010)
          SET "quiver2" = 1
        END ELSE
        PATCH_IF (((("%type%" =  5) OR
                    ("%type%" = 14) OR
                    ("%type%" = 31)) AND ("%quiver3%" = 0) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND ("%index%" > 17)) BEGIN
          PATCH_PRINT ~HW77: %SOURCE_FILE% - Equippable items in inventory: %item%.itm! Equipping QUIVER3~
          WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
          WRITE_SHORT ("%slot_off%" + (0x02 * 15))        "ref"
          SET "quiver3" = 1
        END ELSE
        PATCH_IF (((("%type%" =  5) OR
                    ("%type%" = 14) OR
                    ("%type%" = 31)) AND ("%quiver4%" = 0)) AND (("%flags%" BAND 0b00010100) = 0b00000100) AND ("%index%" > 17)) BEGIN
          PATCH_PRINT ~HW78: %SOURCE_FILE% - Equippable items in inventory: %item%.itm! Equipping QUIVER4~
          WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
          WRITE_SHORT ("%slot_off%" + (0x02 * 16))        "ref"
          SET "quiver4" = 1
        END ELSE
        PATCH_IF ((("%type%" =  7) AND ("%helm%" = 0)) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND ("%index%" > 17) BEGIN
          PATCH_PRINT ~HW79: %SOURCE_FILE% - Equippable items in inventory: %item%.itm! Equipping HELM~
          WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
          WRITE_SHORT ("%slot_off%")                      "ref"
          SET "helm" = 1
        END ELSE
        PATCH_IF (((("%type%" = 15) OR // bow
                    ("%type%" = 16) OR // dagger
                    ("%type%" = 17) OR // maces
                    ("%type%" = 18) OR // sling
                    ("%type%" = 19) OR // short sword
                    ("%type%" = 20) OR // swords
                    ("%type%" = 21) OR // hammer
                    ("%type%" = 22) OR // morning stars
                    ("%type%" = 23) OR // flail
                    ("%type%" = 24) OR // darts
                    ("%type%" = 25) OR // axe
                    ("%type%" = 26) OR // staff
                    ("%type%" = 27) OR // xbow
                    ("%type%" = 28) OR // hand to hand
                    ("%type%" = 29) OR // Spear
                    ("%type%" = 30) OR // halberd
                    ("%type%" = 44)) AND ("%weapon1%" = 0) AND (("%flags%" BAND 0b00010100) = 0b00000100) AND ("%index%" > 17)))  BEGIN
          PATCH_IF ((("%flags%" BAND 0b00000010) != 0b00000010) AND ("%offhand%" = 0)) BEGIN
            PATCH_PRINT ~HW80: %SOURCE_FILE% - Equippable items in inventory: %item%.itm! Equipping WEAPON1~
            WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
            WRITE_SHORT ("%slot_off%" + (0x02 * 9))         "ref"
            SET "weapon1" = 1
          END
        END ELSE
        PATCH_IF (((("%type%" = 15) OR // bow
                    ("%type%" = 16) OR // dagger
                    ("%type%" = 17) OR // maces
                    ("%type%" = 18) OR // sling
                    ("%type%" = 19) OR // short sword
                    ("%type%" = 20) OR // swords
                    ("%type%" = 21) OR // hammer
                    ("%type%" = 22) OR // morning stars
                    ("%type%" = 23) OR // flail
                    ("%type%" = 24) OR // darts
                    ("%type%" = 25) OR // axe
                    ("%type%" = 26) OR // staff
                    ("%type%" = 27) OR // xbow
                    ("%type%" = 28) OR // hand to hand
                    ("%type%" = 29) OR // Spear
                    ("%type%" = 30) OR // halberd
                    ("%type%" = 44)) AND ("%weapon2%" = 0) AND (("%flags%" BAND 0b00010100) = 0b00000100) AND ("%index%" > 17)))  BEGIN
          PATCH_IF ((("%flags%" BAND 0b00000010) != 0b00000010) AND ("%offhand%" = 0)) BEGIN
            PATCH_PRINT ~HW81: %SOURCE_FILE% - Equippable items in inventory: %item%.itm! Equipping WEAPON2~
            WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
            WRITE_SHORT ("%slot_off%" + (0x02 * 10))        "ref"
            SET "weapon2" = 1
          END
        END ELSE
        PATCH_IF (((("%type%" = 15) OR // bow
                    ("%type%" = 16) OR // dagger
                    ("%type%" = 17) OR // maces
                    ("%type%" = 18) OR // sling
                    ("%type%" = 19) OR // short sword
                    ("%type%" = 20) OR // swords
                    ("%type%" = 21) OR // hammer
                    ("%type%" = 22) OR // morning stars
                    ("%type%" = 23) OR // flail
                    ("%type%" = 24) OR // darts
                    ("%type%" = 25) OR // axe
                    ("%type%" = 26) OR // staff
                    ("%type%" = 27) OR // xbow
                    ("%type%" = 28) OR // hand to hand
                    ("%type%" = 29) OR // Spear
                    ("%type%" = 30) OR // halberd
                    ("%type%" = 44)) AND ("%weapon3%" = 0) AND (("%flags%" BAND 0b00010100) = 0b00000100) AND ("%index%" > 17)))  BEGIN
          PATCH_IF ((("%flags%" BAND 0b00000010) != 0b00000010) AND ("%offhand%" = 0)) BEGIN
            PATCH_PRINT ~HW82: %SOURCE_FILE% - Equippable items in inventory: %item%.itm! Equipping WEAPON3~
            WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
            WRITE_SHORT ("%slot_off%" + (0x02 * 11))        "ref"
            SET "weapon3" = 1
          END
        END ELSE
        PATCH_IF (((("%type%" = 15) OR // bow
                    ("%type%" = 16) OR // dagger
                    ("%type%" = 17) OR // maces
                    ("%type%" = 18) OR // sling
                    ("%type%" = 19) OR // short sword
                    ("%type%" = 20) OR // swords
                    ("%type%" = 21) OR // hammer
                    ("%type%" = 22) OR // morning stars
                    ("%type%" = 23) OR // flail
                    ("%type%" = 24) OR // darts
                    ("%type%" = 25) OR // axe
                    ("%type%" = 26) OR // staff
                    ("%type%" = 27) OR // xbow
                    ("%type%" = 28) OR // hand to hand
                    ("%type%" = 29) OR // Spear
                    ("%type%" = 30) OR // halberd
                    ("%type%" = 44)) AND ("%weapon4%" = 0) AND (("%flags%" BAND 0b00010100) = 0b00000100) AND ("%index%" > 17)))  BEGIN
          PATCH_IF ((("%flags%" BAND 0b00000010) != 0b00000010) AND ("%offhand%" = 0)) BEGIN
            PATCH_PRINT ~HW83: %SOURCE_FILE% - Equippable items in inventory: %item%.itm! Equipping WEAPON4~
            WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
            WRITE_SHORT ("%slot_off%" + (0x02 * 12))        "ref"
            SET "weapon4" = 1
          END
        END ELSE
        PATCH_IF ((("%type%" = 12) AND ("%offhand%" = 0) AND ("2handedequip" = 0)) AND (("%flags%" BAND 0b00010100) = 0b00000100)) AND ("%index%" > 17) BEGIN
          PATCH_PRINT ~HW84: %SOURCE_FILE% - Equippable items in inventory: %item%.itm! Equipping SHIELD~
          WRITE_SHORT ("%slot_off%" + (0x02 * "%index%")) 0xffff
          WRITE_SHORT ("%slot_off%" + (0x02 * 2))         "ref"
          SET "offhand" = 1
        END
      END
    END
  END
END

//actually equip weapons
//    PATCH_PRINT ~%SOURCE_FILE%: checking selected weapon~
weapon_present = 0
weapon_selected = 0
selected_item_index = 0xffff
SPRINT selected_item ~~
READ_SHORT slot_off+38*0x2 selected_weapon_slot
//    PATCH_PRINT ~%SOURCE_FILE%: selected_weapon_slot=%selected_weapon_slot%~
PATCH_IF (selected_weapon_slot >= 0 AND selected_weapon_slot < 4) BEGIN
  READ_SHORT (slot_off + (selected_weapon_slot + 9) * 0x2) selected_item_index
//      PATCH_PRINT ~%SOURCE_FILE%: selected_item_index=%selected_item_index%~
END
PATCH_IF NOT (selected_item_index = 0xffff) BEGIN
  READ_ASCII (itm_off + selected_item_index * 0x14) selected_item
//      PATCH_PRINT ~%SOURCE_FILE%: selected_item=%selected_item%~
END
PATCH_IF (NOT ~%selected_item%~ STRING_EQUAL ~~) BEGIN //we're all good
  weapon_present = 1
  weapon_selected = 1
//      PATCH_PRINT ~%SOURCE_FILE%: weapons good~
END ELSE BEGIN
//      PATCH_PRINT ~%SOURCE_FILE%: looking for weapons in current slots~
  PATCH_FOR_EACH inv_slot IN 9 10 11 12 BEGIN
    READ_SHORT (slot_off + inv_slot * 0x2) item_index
//        PATCH_PRINT ~%SOURCE_FILE%: found item %item_index% in %inv_slot%. weapon_present=%weapon_present%~
    PATCH_IF ((weapon_present = 0) AND NOT (item_index = 0xffff)) BEGIN //there's a weapon, but it's not selected
      weapon_present = 1
      weapon_present_slot = inv_slot - 9
      PATCH_PRINT ~HW85: %SOURCE_FILE% - equipped weapon not selected! Selecting WEAPON%weapon_present_slot%~
      WRITE_LONG (slot_off+38*0x2) weapon_present_slot
      weapon_selected = 1
    END
  END
END
PATCH_IF ((weapon_selected = 0) AND (selected_weapon_slot != 1000)) BEGIN //still no weapon
  WRITE_LONG (slot_off+38*0x2) 1000
  PATCH_PRINT ~HI23: %SOURCE_FILE% - no weapons available. Selecting FIST~
END
