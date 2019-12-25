PATCH_IF (SOURCE_SIZE > 0x71) BEGIN
  READ_BYTE  0x18 "flags"

  PATCH_IF (("%flags%" BAND 0b00000100) = 0b00000100) BEGIN  // droppable

    // Equipped Effect Fixer
    READ_LONG  0x64 "abil_off" ELSE 0
    READ_SHORT 0x68 "abil_num" ELSE 0
    READ_LONG  0x6a "fx_off" ELSE 0
    READ_SHORT 0x6e "fx_idx" ELSE 0
    READ_SHORT 0x70 "fx_num" ELSE 0

    PATCH_IF (fx_off > 0x71) BEGIN
      PATCH_IF (("%flags%" BAND 0b00010000) = 0b00010000) BEGIN  // cursed
        SET "found" = 0
        FOR (index = fx_idx ; index < fx_num ; index = index + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x08 + ("%index%" * 0x30)) "eff_param2"
          PATCH_IF ("%eff_opcode%" = 142) AND ("%eff_param2%" = 35) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW173: %SOURCE_FILE% - Adding Cursed Portrait..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 142
              target     = 1
              timing     = 2
              parameter2 = 35
          END
          READ_SHORT 0x70 "fx_num"
        END
      END

      FOR (index = fx_idx ; index < fx_num ; index = index + 1) BEGIN // check equipping effects
        READ_SHORT ("%fx_off%" +        ("%index%" * 0x30)) "opcode"
        READ_LONG  ("%fx_off%" + 0x04 + ("%index%" * 0x30)) "param1"
        READ_LONG  ("%fx_off%" + 0x08 + ("%index%" * 0x30)) "param2"

        PATCH_IF ("%opcode%" = 22) AND (((("%param2%" = 0) OR ("%param2%" = 1)) AND ("%param1%" < 0)) OR (("%param2%" = 2) AND ("%param1%" < 100))) BEGIN
          SET "found" = 0
          FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
            PATCH_IF ("%index1%" != "%index%") BEGIN
              READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
              READ_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) "eff_target"
              READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
              READ_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) "eff_timing"
              PATCH_IF ("%eff_opcode%" = 142) AND ("%eff_param2%" = 33) BEGIN
                SET "found" = 1
                PATCH_IF ("%eff_target%" != 1) BEGIN
                  PATCH_PRINT "HW174: %SOURCE_FILE% - Bad Luck Portrait now displays on Self..."
                  WRITE_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) 1
                END
                PATCH_IF ("%eff_timing%" != 2) BEGIN
                  PATCH_PRINT "HW175: %SOURCE_FILE% - Bad Luck Portrait now displays while equipped..."
                  WRITE_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) 2
                END
              END
            END
          END
          PATCH_IF ("%found%" = 0) BEGIN
            PATCH_PRINT "%SOURCE_FILE% - Adding Bad Luck Portrait..."
            LPF ADD_ITEM_EQEFFECT
              INT_VAR
                opcode     = 142
                target     = 1
                timing     = 2
                parameter2 = 33
            END
            READ_SHORT 0x70 "fx_num"
          END
        END

        PATCH_IF ("%opcode%" = 22) AND (((("%param2%" = 0) OR ("%param2%" = 1)) AND ("%param1%" > 0)) OR (("%param2%" = 2) AND ("%param1%" > 100))) BEGIN
          SET "found" = 0
          FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
            PATCH_IF ("%index1%" != "%index%") BEGIN
              READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
              READ_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) "eff_target"
              READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
              READ_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) "eff_timing"
              PATCH_IF ("%eff_opcode%" = 142) AND ("%eff_param2%" = 32) BEGIN
                SET "found" = 1
                PATCH_IF ("%eff_target%" != 1) BEGIN
                  PATCH_PRINT "HW176: %SOURCE_FILE% - Good Luck Portrait now displays on Self..."
                  WRITE_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) 1
                END
                PATCH_IF ("%eff_timing%" != 2) BEGIN
                  PATCH_PRINT "HW177: %SOURCE_FILE% - Good Luck Portrait now displays while equipped..."
                  WRITE_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) 2
                END
              END
            END
          END
          PATCH_IF ("%found%" = 0) BEGIN
            PATCH_PRINT "HW178: %SOURCE_FILE% - Adding Good Luck Portrait..."
            LPF ADD_ITEM_EQEFFECT
              INT_VAR
                opcode     = 142
                target     = 1
                timing     = 2
                parameter2 = 32
            END
            READ_SHORT 0x70 "fx_num"
          END
        END

        PATCH_IF ("%opcode%" = 27) AND (((("%param2%" = 0) OR ("%param2%" = 1)) AND ("%param1%" > 0)) OR (("%param2%" = 2) AND ("%param1%" > 100))) BEGIN
          SET "found" = 0
          FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
            PATCH_IF ("%index1%" != "%index%") BEGIN
              READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
              READ_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) "eff_target"
              READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
              READ_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) "eff_timing"
              PATCH_IF ("%eff_opcode%" = 142) AND ("%eff_param2%" = 24) BEGIN
                SET "found" = 1
                PATCH_IF ("%eff_target%" != 1) BEGIN
                  PATCH_PRINT "HW179: %SOURCE_FILE% - Protection from Acid Portrait now displays on Self..."
                  WRITE_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) 1
                END
                PATCH_IF ("%eff_timing%" != 2) BEGIN
                  PATCH_PRINT "HW180: %SOURCE_FILE% - Protection from Acid Portrait now displays while equipped..."
                  WRITE_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) 2
                END
              END
            END
          END
          PATCH_IF ("%found%" = 0) BEGIN
            PATCH_PRINT "HW181: %SOURCE_FILE% - Adding Protection from Acid Portrait..."
            LPF ADD_ITEM_EQEFFECT
              INT_VAR
                opcode     = 142
                target     = 1
                timing     = 2
                parameter2 = 24
            END
            READ_SHORT 0x70 "fx_num"
          END
        END

        PATCH_IF ("%opcode%" = 28) AND (((("%param2%" = 0) OR ("%param2%" = 1)) AND ("%param1%" > 0)) OR (("%param2%" = 2) AND ("%param1%" > 100))) BEGIN
          SET "foundboth" = 0
          SET "foundfireeffect" = 0
          SET "foundfireicon" = 0
          SET "foundcoldicon" = 0
          SET "coldiconindex" = 0
          SET "fireiconindex" = 0
          FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
            PATCH_IF ("%index1%" != "%index%") BEGIN
              READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
              READ_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) "eff_target"
              READ_LONG  ("%fx_off%" + 0x04 + ("%index1%" * 0x30)) "eff_param1"
              READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
              READ_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) "eff_timing"
              PATCH_IF ("%eff_opcode%" = 30) AND (((("%eff_param2%" = 0) OR ("%eff_param2%" = 1)) AND ("%eff_param1%" > 0)) OR (("%eff_param2%" = 2) AND ("%eff_param1%" > 100))) BEGIN
                SET "foundfireeffect" = 1
              END
              PATCH_IF ("%eff_opcode%" = 142) AND ("%eff_param2%" = 16) BEGIN
                SET "foundfireicon" = 1
                SET "fireiconindex" = "index1"
                PATCH_IF ("%eff_target%" != 1) BEGIN
                  PATCH_PRINT "HW182: %SOURCE_FILE% - Protection from Fire Portrait now displays on Self..."
                  WRITE_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) 1
                END
                PATCH_IF ("%eff_timing%" != 2) BEGIN
                  PATCH_PRINT "HW183: %SOURCE_FILE% - Protection from Fire Portrait now displays while equipped..."
                  WRITE_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) 2
                END
              END
              PATCH_IF ("%eff_opcode%" = 142) AND ("%eff_param2%" = 25) BEGIN
                SET "foundcoldicon" = 1
                SET "coldiconindex" = "index1"
                PATCH_IF ("%eff_target%" != 1) BEGIN
                  PATCH_PRINT "HW184: %SOURCE_FILE% - Protection from Cold Portrait now displays on Self..."
                  WRITE_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) 1
                END
                PATCH_IF ("%eff_timing%" != 2) BEGIN
                  PATCH_PRINT "HW185: %SOURCE_FILE% - Protection from Cold Portrait now displays while equipped..."
                  WRITE_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) 2
                END
              END
              PATCH_IF ("%eff_opcode%" = 142) AND ("%eff_param2%" = 26) BEGIN
                SET "foundboth" = 1
                PATCH_IF ("%eff_target%" != 1) BEGIN
                  PATCH_PRINT "HW186: %SOURCE_FILE% - Resist Fire/Cold Portrait now displays on Self..."
                  WRITE_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) 1
                END
                PATCH_IF ("%eff_timing%" != 2) BEGIN
                  PATCH_PRINT "HW187: %SOURCE_FILE% - Resist Fire/Cold Portrait now displays while equipped..."
                  WRITE_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) 2
                END
              END
            END
          END
          PATCH_IF ("%foundboth%" = 0) AND ("%foundfireeffect%" = 1) BEGIN
            PATCH_IF ("%foundfireicon%" = 1) BEGIN
              PATCH_PRINT "HW188: %SOURCE_FILE% - Removing Protection from Fire Portrait..."
              offset = "%fx_off%" + ("%fireiconindex%" * 0x30)
              value  = 0x30
              DELETE_BYTES offset value
              SOURCE_SIZE = SOURCE_SIZE - value
              PATCH_IF ("%abil_off%" > "%fx_off%") BEGIN
                SET "abil_off" = "abil_off" - 0x30
                WRITE_LONG 0x64 %abil_off%
              END
              FOR (index2 = 0 ; index2 < abil_num ; index2 = index2 + 1) BEGIN
                READ_SHORT  ("%abil_off%" + 0x20 + ("%index2%" * 0x38)) "abil_fx_idx"
                PATCH_IF ("%abil_fx_idx%" > "%fireiconindex%") BEGIN
                  SET "abil_fx_idx" = "abil_fx_idx" - 1
                  WRITE_SHORT ("%abil_off%" + 0x20 + ("%index2%" * 0x38)) "abil_fx_idx"
                END
              END
              PATCH_IF ("%coldiconindex%" > "%fireiconindex%") BEGIN
                SET "coldiconindex" = "coldiconindex" - 1
              END
              SET "index1" = 0 - 1
              SET "fx_num" = "fx_num" - 1
              WRITE_SHORT 0x70 %fx_num%
            END
            PATCH_IF ("%foundcoldicon%" = 1) BEGIN
              PATCH_PRINT "HW189: %SOURCE_FILE% - Removing Protection from Cold Portrait..."
              offset = "%fx_off%" + ("%coldiconindex%" * 0x30)
              value  = 0x30
              DELETE_BYTES offset value
              SOURCE_SIZE = SOURCE_SIZE - value
              PATCH_IF ("%abil_off%" > "%fx_off%") BEGIN
                SET "abil_off" = "abil_off" - 0x30
                WRITE_LONG 0x64 %abil_off%
              END
              FOR (index2 = 0 ; index2 < abil_num ; index2 = index2 + 1) BEGIN
                READ_SHORT  ("%abil_off%" + 0x20 + ("%index2%" * 0x38)) "abil_fx_idx"
                PATCH_IF ("%abil_fx_idx%" > "%coldiconindex%") BEGIN
                  SET "abil_fx_idx" = "abil_fx_idx" - 1
                  WRITE_SHORT ("%abil_off%" + 0x20 + ("%index2%" * 0x38)) "abil_fx_idx"
                END
              END
              PATCH_IF ("%fireiconindex%" > "%coldiconindex%") BEGIN
                SET "fireiconindex" = "fireiconindex" - 1
              END
              SET "index1" = 0 - 1
              SET "fx_num" = "fx_num" - 1
              WRITE_SHORT 0x70 %fx_num%
            END
            PATCH_PRINT "HW190: %SOURCE_FILE% - Adding Resist Fire/Cold Portrait..."
            LPF ADD_ITEM_EQEFFECT
              INT_VAR
                opcode     = 142
                target     = 1
                timing     = 2
                parameter2 = 26
            END
            READ_SHORT 0x70 "fx_num"
          END ELSE
          PATCH_IF ("%foundboth%" = 0) AND ("%foundcoldicon%" = 0) BEGIN
            PATCH_PRINT "HW191: %SOURCE_FILE% - Adding Protection from Cold Portrait..."
            LPF ADD_ITEM_EQEFFECT
              INT_VAR
                opcode     = 142
                target     = 1
                timing     = 2
                parameter2 = 25
            END
            READ_SHORT 0x70 "fx_num"
          END
        END

        PATCH_IF ("%opcode%" = 29) AND (((("%param2%" = 0) OR ("%param2%" = 1)) AND ("%param1%" > 0)) OR (("%param2%" = 2) AND ("%param1%" > 100))) BEGIN
          SET "found" = 0
          FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
            PATCH_IF ("%index1%" != "%index%") BEGIN
              READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
              READ_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) "eff_target"
              READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
              READ_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) "eff_timing"
              PATCH_IF ("%eff_opcode%" = 142) AND ("%eff_param2%" = 27) BEGIN
                SET "found" = 1
                PATCH_IF ("%eff_target%" != 1) BEGIN
                  PATCH_PRINT "HW192: %SOURCE_FILE% - Protection from Electricity Portrait now displays on Self..."
                  WRITE_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) 1
                END
                PATCH_IF ("%eff_timing%" != 2) BEGIN
                  PATCH_PRINT "HW193: %SOURCE_FILE% - Protection from Electricity Portrait now displays while equipped..."
                  WRITE_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) 2
                END
              END
            END
          END
          PATCH_IF ("%found%" = 0) BEGIN
            PATCH_PRINT "HW194: %SOURCE_FILE% - Adding Protection from Electricity Portrait..."
            LPF ADD_ITEM_EQEFFECT
              INT_VAR
                opcode     = 142
                target     = 1
                timing     = 2
                parameter2 = 27
            END
            READ_SHORT 0x70 "fx_num"
          END
        END

        PATCH_IF ("%opcode%" = 30) AND (((("%param2%" = 0) OR ("%param2%" = 1)) AND ("%param1%" > 0)) OR (("%param2%" = 2) AND ("%param1%" > 100))) BEGIN
          SET "foundboth" = 0
          SET "foundcoldeffect" = 0
          SET "foundcoldicon" = 0
          SET "foundfireicon" = 0
          SET "coldiconindex" = 0
          SET "fireiconindex" = 0
          FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
            PATCH_IF ("%index1%" != "%index%") BEGIN
              READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
              READ_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) "eff_target"
              READ_LONG  ("%fx_off%" + 0x04 + ("%index1%" * 0x30)) "eff_param1"
              READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
              READ_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) "eff_timing"
              PATCH_IF ("%eff_opcode%" = 28) AND (((("%eff_param2%" = 0) OR ("%eff_param2%" = 1)) AND ("%eff_param1%" > 0)) OR (("%eff_param2%" = 2) AND ("%eff_param1%" > 100))) BEGIN
                SET "foundcoldeffect" = 1
              END
              PATCH_IF ("%eff_opcode%" = 142) AND ("%eff_param2%" = 16) BEGIN
                SET "foundfireicon" = 1
                SET "fireiconindex" = "index1"
                PATCH_IF ("%eff_target%" != 1) BEGIN
                  PATCH_PRINT "HW195: %SOURCE_FILE% - Protection from Fire Portrait now displays on Self..."
                  WRITE_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) 1
                END
                PATCH_IF ("%eff_timing%" != 2) BEGIN
                  PATCH_PRINT "HW196: %SOURCE_FILE% - Protection from Fire Portrait now displays while equipped..."
                  WRITE_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) 2
                END
              END
              PATCH_IF ("%eff_opcode%" = 142) AND ("%eff_param2%" = 25) BEGIN
                SET "foundcoldicon" = 1
                SET "coldiconindex" = "index1"
                PATCH_IF ("%eff_target%" != 1) BEGIN
                  PATCH_PRINT "HW197: %SOURCE_FILE% - Protection from Cold Portrait now displays on Self..."
                  WRITE_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) 1
                END
                PATCH_IF ("%eff_timing%" != 2) BEGIN
                  PATCH_PRINT "HW198: %SOURCE_FILE% - Protection from Cold Portrait now displays while equipped..."
                  WRITE_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) 2
                END
              END
              PATCH_IF ("%eff_opcode%" = 142) AND ("%eff_param2%" = 26) BEGIN
                SET "foundboth" = 1
                PATCH_IF ("%eff_target%" != 1) BEGIN
                  PATCH_PRINT "HW199: %SOURCE_FILE% - Resist Fire/Cold Portrait now displays on Self..."
                  WRITE_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) 1
                END
                PATCH_IF ("%eff_timing%" != 2) BEGIN
                  PATCH_PRINT "HW200: %SOURCE_FILE% - Resist Fire/Cold Portrait now displays while equipped..."
                  WRITE_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) 2
                END
              END
            END
          END
          PATCH_IF ("%foundboth%" = 0) AND ("%foundcoldeffect%" = 1) BEGIN
            PATCH_IF ("%foundfireicon%" = 1) BEGIN
              PATCH_PRINT "HW200: %SOURCE_FILE% - Removing Protection from Fire Portrait..."
              offset = "%fx_off%" + ("%fireiconindex%" * 0x30)
              value  = 0x30
              DELETE_BYTES offset value
              SOURCE_SIZE = SOURCE_SIZE - value
              PATCH_IF ("%abil_off%" > "%fx_off%") BEGIN
                SET "abil_off" = "abil_off" - 0x30
                WRITE_LONG 0x64 %abil_off%
              END
              FOR (index2 = 0 ; index2 < abil_num ; index2 = index2 + 1) BEGIN
                READ_SHORT  ("%abil_off%" + 0x20 + ("%index2%" * 0x38)) "abil_fx_idx"
                PATCH_IF ("%abil_fx_idx%" > "%fireiconindex%") BEGIN
                  SET "abil_fx_idx" = "abil_fx_idx" - 1
                  WRITE_SHORT ("%abil_off%" + 0x20 + ("%index2%" * 0x38)) "abil_fx_idx"
                END
              END
              PATCH_IF ("%coldiconindex%" > "%fireiconindex%") BEGIN
                SET "coldiconindex" = "coldiconindex" - 1
              END
              SET "index1" = 0 - 1
              SET "fx_num" = "fx_num" - 1
              WRITE_SHORT 0x70 %fx_num%
            END
            PATCH_IF ("%foundcoldicon%" = 1) BEGIN
              PATCH_PRINT "HW201: %SOURCE_FILE% - Removing Protection from Cold Portrait..."
              offset = "%fx_off%" + ("%coldiconindex%" * 0x30)
              value  = 0x30
              DELETE_BYTES offset value
              SOURCE_SIZE = SOURCE_SIZE - value
              PATCH_IF ("%abil_off%" > "%fx_off%") BEGIN
                SET "abil_off" = "abil_off" - 0x30
                WRITE_LONG 0x64 %abil_off%
              END
              FOR (index2 = 0 ; index2 < abil_num ; index2 = index2 + 1) BEGIN
                READ_SHORT  ("%abil_off%" + 0x20 + ("%index2%" * 0x38)) "abil_fx_idx"
                PATCH_IF ("%abil_fx_idx%" > "%coldiconindex%") BEGIN
                  SET "abil_fx_idx" = "abil_fx_idx" - 1
                  WRITE_SHORT ("%abil_off%" + 0x20 + ("%index2%" * 0x38)) "abil_fx_idx"
                END
              END
              PATCH_IF ("%fireiconindex%" > "%coldiconindex%") BEGIN
                SET "fireiconindex" = "fireiconindex" - 1
              END
              SET "index1" = 0 - 1
              SET "fx_num" = "fx_num" - 1
              WRITE_SHORT 0x70 %fx_num%
            END
            PATCH_PRINT "HW202: %SOURCE_FILE% - Adding Resist Fire/Cold Portrait..."
            LPF ADD_ITEM_EQEFFECT
              INT_VAR
                opcode     = 142
                target     = 1
                timing     = 2
                parameter2 = 26
            END
            READ_SHORT 0x70 "fx_num"
          END ELSE
          PATCH_IF ("%foundboth%" = 0) AND ("%foundfireicon%" = 0) BEGIN
            PATCH_PRINT "HW203: %SOURCE_FILE% - Adding Protection from Fire Portrait..."
            LPF ADD_ITEM_EQEFFECT
              INT_VAR
                opcode     = 142
                target     = 1
                timing     = 2
                parameter2 = 16
            END
            READ_SHORT 0x70 "fx_num"
          END
        END

        PATCH_IF (("%opcode%" = 31) OR ("%opcode%" = 166)) AND (((("%param2%" = 0) OR ("%param2%" = 1)) AND ("%param1%" > 0)) OR (("%param2%" = 2) AND ("%param1%" > 100))) BEGIN
          SET "found" = 0
          FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
            PATCH_IF ("%index1%" != "%index%") BEGIN
              READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
              READ_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) "eff_target"
              READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
              READ_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) "eff_timing"
              PATCH_IF ("%eff_opcode%" = 142) AND (("%eff_param2%" = 28) OR ("%eff_param2%" = 63)) BEGIN
                SET "found" = 1
                PATCH_IF ("%eff_target%" != 1) BEGIN
                  PATCH_PRINT "HW204: %SOURCE_FILE% - Protection from Magic Portrait now displays on Self..."
                  WRITE_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) 1
                END
                PATCH_IF ("%eff_timing%" != 2) BEGIN
                  PATCH_PRINT "HW205: %SOURCE_FILE% - Protection from Magic Portrait now displays while equipped..."
                  WRITE_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) 2
                END
              END
            END
          END
          PATCH_IF ("%found%" = 0) BEGIN
            PATCH_PRINT "HW206: %SOURCE_FILE% - Adding Protection from Magic Portrait..."
            LPF ADD_ITEM_EQEFFECT
              INT_VAR
                opcode     = 142
                target     = 1
                timing     = 2
                parameter2 = 28
            END
            READ_SHORT 0x70 "fx_num"
          END
        END

        PATCH_IF ("%opcode%" = 48) BEGIN
          SET "found" = 0
          FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
            PATCH_IF ("%index1%" != "%index%") BEGIN
              READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
              READ_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) "eff_target"
              READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
              READ_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) "eff_timing"
              PATCH_IF ("%eff_opcode%" = 142) AND ("%eff_param2%" = 103) BEGIN
                SET "found" = 1
                PATCH_IF ("%eff_target%" != 1) BEGIN
                  PATCH_PRINT "HW207: %SOURCE_FILE% - Vocalize Portrait now displays on Self..."
                  WRITE_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) 1
                END
                PATCH_IF ("%eff_timing%" != 2) BEGIN
                  PATCH_PRINT "HW208: %SOURCE_FILE% - Vocalize Portrait now displays while equipped..."
                  WRITE_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) 2
                END
              END
            END
          END
          PATCH_IF ("%found%" = 0) BEGIN
            PATCH_PRINT "HW209: %SOURCE_FILE% - Adding Vocalize Portrait..."
            LPF ADD_ITEM_EQEFFECT
              INT_VAR
                opcode     = 142
                target     = 1
                timing     = 2
                parameter2 = 103
            END
            READ_SHORT 0x70 "fx_num"
          END
        END

        PATCH_IF ("%opcode%" = 63) BEGIN
          SET "found" = 0
          FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
            PATCH_IF ("%index1%" != "%index%") BEGIN
              READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
              READ_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) "eff_target"
              READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
              READ_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) "eff_timing"
              PATCH_IF ("%eff_opcode%" = 142) AND ("%eff_param2%" = 114) BEGIN
                SET "found" = 1
                PATCH_IF ("%eff_target%" != 1) BEGIN
                  PATCH_PRINT "HW210: %SOURCE_FILE% - Infravision Portrait now displays on Self..."
                  WRITE_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) 1
                END
                PATCH_IF ("%eff_timing%" != 2) BEGIN
                  PATCH_PRINT "HW211: %SOURCE_FILE% - Infravision Portrait now displays while equipped..."
                  WRITE_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) 2
                END
              END
            END
          END
          PATCH_IF ("%found%" = 0) BEGIN
            PATCH_PRINT "HW212: %SOURCE_FILE% - Adding Infravision Portrait..."
            LPF ADD_ITEM_EQEFFECT
              INT_VAR
                opcode     = 142
                target     = 1
                timing     = 2
                parameter2 = 114
            END
            READ_SHORT 0x70 "fx_num"
          END
        END

        PATCH_IF ("%opcode%" = 69) BEGIN
          SET "found" = 0
          FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
            PATCH_IF ("%index1%" != "%index%") BEGIN
              READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
              READ_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) "eff_target"
              READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
              READ_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) "eff_timing"
              PATCH_IF ("%eff_opcode%" = 142) AND ("%eff_param2%" = 31) BEGIN
                SET "found" = 1
                PATCH_IF ("%eff_target%" != 1) BEGIN
                  PATCH_PRINT "HW213: %SOURCE_FILE% - Non-detection Portrait now displays on Self..."
                  WRITE_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) 1
                END
                PATCH_IF ("%eff_timing%" != 2) BEGIN
                  PATCH_PRINT "HW214: %SOURCE_FILE% - Non-detection Portrait now displays while equipped..."
                  WRITE_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) 2
                END
              END
            END
          END
          PATCH_IF ("%found%" = 0) BEGIN
            PATCH_PRINT "HW215: %SOURCE_FILE% - Adding Non-detection Portrait..."
            LPF ADD_ITEM_EQEFFECT
              INT_VAR
                opcode     = 142
                target     = 1
                timing     = 2
                parameter2 = 31
            END
            READ_SHORT 0x70 "fx_num"
          END
        END

        PATCH_IF ("%opcode%" = 98) BEGIN
          SET "found" = 0
          FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
            PATCH_IF ("%index1%" != "%index%") BEGIN
              READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
              READ_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) "eff_target"
              READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
              READ_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) "eff_timing"
              PATCH_IF ("%eff_opcode%" = 142) AND (("%eff_param2%" = 42) OR ("%eff_param2%" = 56) OR ("%eff_param2%" = 87)) BEGIN
                SET "found" = 1
                PATCH_IF ("%eff_target%" != 1) BEGIN
                  PATCH_PRINT "HW216: %SOURCE_FILE% - Regeneration Portrait now displays on Self..."
                  WRITE_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) 1
                END
                PATCH_IF ("%eff_timing%" != 2) BEGIN
                  PATCH_PRINT "HW217: %SOURCE_FILE% - Regeneration Portrait now displays while equipped..."
                  WRITE_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) 2
                END
              END
            END
          END
          PATCH_IF ("%found%" = 0) BEGIN
            PATCH_PRINT "HW218: %SOURCE_FILE% - Adding Regeneration Portrait..."
            LPF ADD_ITEM_EQEFFECT
              INT_VAR
                opcode     = 142
                target     = 1
                timing     = 2
                parameter2 = 56
            END
            READ_SHORT 0x70 "fx_num"
          END
        END

        PATCH_IF ("%opcode%" = 101) AND ("%param2%" = 5) BEGIN
          SET "found" = 0
          FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
            PATCH_IF ("%index1%" != "%index%") BEGIN
              READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
              READ_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) "eff_target"
              READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
              READ_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) "eff_timing"
              PATCH_IF ("%eff_opcode%" = 142) AND ("%eff_param2%" = 52) BEGIN
                SET "found" = 1
                PATCH_IF ("%eff_target%" != 1) BEGIN
                  PATCH_PRINT "HW219: %SOURCE_FILE% - Mind Shield Portrait now displays on Self..."
                  WRITE_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) 1
                END
                PATCH_IF ("%eff_timing%" != 2) BEGIN
                  PATCH_PRINT "HW220: %SOURCE_FILE% - Mind Shield Portrait now displays while equipped..."
                  WRITE_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) 2
                END
              END
            END
          END
          PATCH_IF ("%found%" = 0) BEGIN
            PATCH_PRINT "HW221: %SOURCE_FILE% - Adding Mind Shield Portrait..."
            LPF ADD_ITEM_EQEFFECT
              INT_VAR
                opcode     = 142
                target     = 1
                timing     = 2
                parameter2 = 52
            END
            READ_SHORT 0x70 "fx_num"
          END
        END

        PATCH_IF ("%opcode%" = 163) BEGIN
          SET "found" = 0
          FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
            PATCH_IF ("%index1%" != "%index%") BEGIN
              READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
              READ_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) "eff_target"
              READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
              READ_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) "eff_timing"
              PATCH_IF ("%eff_opcode%" = 142) AND ("%eff_param2%" = 19) BEGIN
                SET "found" = 1
                PATCH_IF ("%eff_target%" != 1) BEGIN
                  PATCH_PRINT "HW222: %SOURCE_FILE% - Free Action Portrait now displays on Self..."
                  WRITE_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) 1
                END
                PATCH_IF ("%eff_timing%" != 2) BEGIN
                  PATCH_PRINT "HW223: %SOURCE_FILE% - Free Action Portrait now displays while equipped..."
                  WRITE_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) 2
                END
              END
            END
          END
          PATCH_IF ("%found%" = 0) BEGIN
            PATCH_PRINT "HW224: %SOURCE_FILE% - Adding Free Action Portrait..."
            LPF ADD_ITEM_EQEFFECT
              INT_VAR
                opcode     = 142
                target     = 1
                timing     = 2
                parameter2 = 19
            END
            READ_SHORT 0x70 "fx_num"
          END
        END

        PATCH_IF ("%opcode%" = 173) AND (((("%param2%" = 0) OR ("%param2%" = 1)) AND ("%param1%" > 0)) OR (("%param2%" = 2) AND ("%param1%" > 100))) BEGIN
          SET "found" = 0
          FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
            PATCH_IF ("%index1%" != "%index%") BEGIN
              READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
              READ_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) "eff_target"
              READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
              READ_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) "eff_timing"
              PATCH_IF ("%eff_opcode%" = 142) AND ("%eff_param2%" = 30) BEGIN
                SET "found" = 1
                PATCH_IF ("%eff_target%" != 1) BEGIN
                  PATCH_PRINT "HW225: %SOURCE_FILE% - Protection from Poison Portrait now displays on Self..."
                  WRITE_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) 1
                END
                PATCH_IF ("%eff_timing%" != 2) BEGIN
                  PATCH_PRINT "HW226: %SOURCE_FILE% - Protection from Poison Portrait now displays while equipped..."
                  WRITE_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) 2
                END
              END
            END
          END
          PATCH_IF ("%found%" = 0) BEGIN
            PATCH_PRINT "HW227: %SOURCE_FILE% - Adding Protection from Poison Portrait..."
            LPF ADD_ITEM_EQEFFECT
              INT_VAR
                opcode     = 142
                target     = 1
                timing     = 2
                parameter2 = 30
            END
            READ_SHORT 0x70 "fx_num"
          END
        END

        PATCH_IF ("%opcode%" = 176) AND (((("%param2%" = 0) OR ("%param2%" = 1)) AND ("%param1%" > 0)) OR (("%param2%" = 2) AND ("%param1%" > 100))) BEGIN
          SET "found" = 0
          FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
            PATCH_IF ("%index1%" != "%index%") BEGIN
              READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
              READ_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) "eff_target"
              READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
              READ_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) "eff_timing"
              PATCH_IF ("%eff_opcode%" = 142) AND ("%eff_param2%" = 38) BEGIN
                SET "found" = 1
                PATCH_IF ("%eff_target%" != 1) BEGIN
                  PATCH_PRINT "HW228: %SOURCE_FILE% - Haste Portrait now displays on Self..."
                  WRITE_BYTE  ("%fx_off%" + 0x02 + ("%index1%" * 0x30)) 1
                END
                PATCH_IF ("%eff_timing%" != 2) BEGIN
                  PATCH_PRINT "HW229: %SOURCE_FILE% - Haste Portrait now displays while equipped..."
                  WRITE_BYTE  ("%fx_off%" + 0x0c + ("%index1%" * 0x30)) 2
                END
              END
            END
          END
          PATCH_IF ("%found%" = 0) BEGIN
            PATCH_PRINT "HW230: %SOURCE_FILE% - Adding Haste Portrait..."
            LPF ADD_ITEM_EQEFFECT
              INT_VAR
                opcode     = 142
                target     = 1
                timing     = 2
                parameter2 = 38
            END
            READ_SHORT 0x70 "fx_num"
          END
        END

      END
    END
  END
END
