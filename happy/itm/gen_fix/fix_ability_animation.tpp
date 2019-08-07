// Animation and Ranged Ability Flag Fixer
READ_BYTE  0x18 "flags"
READ_LONG  0x64 "abil_off" ELSE 0
READ_SHORT 0x68 "abil_num" ELSE 0

PATCH_IF (abil_off > 0x71) BEGIN
  FOR (index = 0; index < abil_num; index = index + 1) BEGIN
    READ_SHORT ("%abil_off%" +        (0x38 * "%index%")) "abil_type"
    READ_SHORT ("%abil_off%" + 0x2c + (0x38 * "%index%")) "anim_overhand"
    READ_SHORT ("%abil_off%" + 0x2e + (0x38 * "%index%")) "anim_backhand"
    READ_SHORT ("%abil_off%" + 0x30 + (0x38 * "%index%")) "anim_thrust"
    READ_SHORT ("%abil_off%" + 0x32 + (0x38 * "%index%")) "is_arrow"
    READ_SHORT ("%abil_off%" + 0x34 + (0x38 * "%index%")) "is_bolt"
    READ_SHORT ("%abil_off%" + 0x36 + (0x38 * "%index%")) "is_bullet"
    PATCH_IF ((%anim_overhand% + %anim_backhand% + %anim_thrust%) > 0) AND (("%abil_type%" = 1) OR ("%abil_type%" = 2) OR ("%abil_type%" = 4)) AND ((%type% < 15) OR (%type% > 30)) BEGIN
      WRITE_SHORT ("%abil_off%" + 0x2c + (0x38 * "%index%")) 0
      WRITE_SHORT ("%abil_off%" + 0x30 + (0x38 * "%index%")) 0
      WRITE_SHORT ("%abil_off%" + 0x2e + (0x38 * "%index%")) 0
      PATCH_PRINT "HI27: %SOURCE_FILE% - Non weapon has animations!"
      PATCH_PRINT "  Overhand Swing: %anim_overhand% -> 0"
      PATCH_PRINT "  Backhand Swing: %anim_backhand% -> 0"
      PATCH_PRINT "  Thrust        : %anim_thrust% -> 0"
    END ELSE
    PATCH_IF ("%abil_type%" = 1) AND ((%anim_overhand% + %anim_backhand% + %anim_thrust%) != 100) BEGIN // Melee Ability
      PATCH_IF (("%type%" = 16)) AND // dagger
               (("%anim_overhand%" != 0) OR
                ("%anim_backhand%" != 20) OR
                ("%anim_thrust%" != 80)) BEGIN
        SET "anim_overhand_new" = 0
        SET "anim_backhand_new" = 20
        SET "anim_thrust_new" = 80
        WRITE_SHORT ("%abil_off%" + 0x2c + (0x38 * "%index%")) 0
        WRITE_SHORT ("%abil_off%" + 0x30 + (0x38 * "%index%")) 20
        WRITE_SHORT ("%abil_off%" + 0x2e + (0x38 * "%index%")) 80
        PATCH_PRINT "HW104: %SOURCE_FILE% - Melee Animations have wrong probabilities! Setting Dagger probabilities..."
        PATCH_PRINT "  Overhand Swing: %anim_overhand% -> %anim_overhand_new%"
        PATCH_PRINT "  Backhand Swing: %anim_backhand% -> %anim_backhand_new%"
        PATCH_PRINT "  Thrust        : %anim_thrust% -> %anim_thrust_new%"
      END
      PATCH_IF (("%type%" = 19)) AND // short sword
               (("%anim_overhand%" != 10) OR
                ("%anim_backhand%" != 25) OR
                ("%anim_thrust%" != 65)) BEGIN
        SET "anim_overhand_new" = 10
        SET "anim_backhand_new" = 25
        SET "anim_thrust_new" = 65
        WRITE_SHORT ("%abil_off%" + 0x2c + (0x38 * "%index%")) 10
        WRITE_SHORT ("%abil_off%" + 0x30 + (0x38 * "%index%")) 25
        WRITE_SHORT ("%abil_off%" + 0x2e + (0x38 * "%index%")) 65
        PATCH_PRINT "HW105: %SOURCE_FILE% - Melee Animations have wrong probabilities! Setting Short Sword probabilities..."
        PATCH_PRINT "  Overhand Swing: %anim_overhand% -> %anim_overhand_new%"
        PATCH_PRINT "  Backhand Swing: %anim_backhand% -> %anim_backhand_new%"
        PATCH_PRINT "  Thrust        : %anim_thrust% -> %anim_thrust_new%"
      END
      PATCH_IF (("%type%" = 17) OR // maces
                ("%type%" = 18) OR // sling
                ("%type%" = 20) OR // swords
                ("%type%" = 21) OR // hammer
                ("%type%" = 22) OR // morning stars
                ("%type%" = 23) OR // flail
                ("%type%" = 25) OR // axe
                ("%type%" = 28)) AND // hand to hand
               (("%flags%" BAND 0b00000010) != 0b00000010) AND // 1-handed
               (("%anim_overhand%" != 50) OR
                ("%anim_backhand%" != 50) OR
                ("%anim_thrust%" != 0)) BEGIN
        SET "anim_overhand_new" = 50
        SET "anim_backhand_new" = 50
        SET "anim_thrust_new" = 0
        WRITE_SHORT ("%abil_off%" + 0x2c + (0x38 * "%index%")) 50
        WRITE_SHORT ("%abil_off%" + 0x30 + (0x38 * "%index%")) 50
        WRITE_SHORT ("%abil_off%" + 0x2e + (0x38 * "%index%")) 0
        PATCH_PRINT "HW106: %SOURCE_FILE% - Melee Animations have wrong probabilities! Setting Generic 1-Hander probabilities..."
        PATCH_PRINT "  Overhand Swing: %anim_overhand% -> %anim_overhand_new%"
        PATCH_PRINT "  Backhand Swing: %anim_backhand% -> %anim_backhand_new%"
        PATCH_PRINT "  Thrust        : %anim_thrust% -> %anim_thrust_new%"
      END
      PATCH_IF (("%type%" = 17) OR // maces
                ("%type%" = 18) OR // sling
                ("%type%" = 20) OR // swords
                ("%type%" = 21) OR // hammer
                ("%type%" = 22) OR // morning stars
                ("%type%" = 23) OR // flail
                ("%type%" = 25) OR // axe
                ("%type%" = 28)) AND // hand to hand
               (("%flags%" BAND 0b00000010) = 0b00000010) AND // 2-handed
               (("%anim_overhand%" != 60) OR
                ("%anim_backhand%" != 40) OR
                ("%anim_thrust%" != 0)) BEGIN
        SET "anim_overhand_new" = 60
        SET "anim_backhand_new" = 40
        SET "anim_thrust_new" = 0
        WRITE_SHORT ("%abil_off%" + 0x2c + (0x38 * "%index%")) 60
        WRITE_SHORT ("%abil_off%" + 0x30 + (0x38 * "%index%")) 40
        WRITE_SHORT ("%abil_off%" + 0x2e + (0x38 * "%index%")) 0
        PATCH_PRINT "HW107: %SOURCE_FILE% - Melee Animations have wrong probabilities! Setting Generic 2-Hander probabilities..."
        PATCH_PRINT "  Overhand Swing: %anim_overhand% -> %anim_overhand_new%"
        PATCH_PRINT "  Backhand Swing: %anim_backhand% -> %anim_backhand_new%"
        PATCH_PRINT "  Thrust        : %anim_thrust% -> %anim_thrust_new%"
      END
      PATCH_IF (("%type%" = 30)) AND // halberd
               (("%anim_overhand%" != 0) OR
                ("%anim_backhand%" != 35) OR
                ("%anim_thrust%" != 65)) BEGIN
        SET "anim_overhand_new" = 0
        SET "anim_backhand_new" = 25
        SET "anim_thrust_new" = 65
        WRITE_SHORT ("%abil_off%" + 0x2c + (0x38 * "%index%")) 0
        WRITE_SHORT ("%abil_off%" + 0x30 + (0x38 * "%index%")) 35
        WRITE_SHORT ("%abil_off%" + 0x2e + (0x38 * "%index%")) 65
        PATCH_PRINT "HW108: %SOURCE_FILE% - Melee Animations have wrong probabilities! Setting Halberd probabilities..."
        PATCH_PRINT "  Overhand Swing: %anim_overhand% -> %anim_overhand_new%"
        PATCH_PRINT "  Backhand Swing: %anim_backhand% -> %anim_backhand_new%"
        PATCH_PRINT "  Thrust        : %anim_thrust% -> %anim_thrust_new%"
      END
      PATCH_IF (("%type%" = 29)) AND // spear
               (("%anim_overhand%" != 0) OR
                ("%anim_backhand%" != 0) OR
                ("%anim_thrust%" != 100)) BEGIN
        SET "anim_overhand_new" = 0
        SET "anim_backhand_new" = 0
        SET "anim_thrust_new" = 100
        WRITE_SHORT ("%abil_off%" + 0x2c + (0x38 * "%index%")) 0
        WRITE_SHORT ("%abil_off%" + 0x30 + (0x38 * "%index%")) 0
        WRITE_SHORT ("%abil_off%" + 0x2e + (0x38 * "%index%")) 100
        PATCH_PRINT "HW109: %SOURCE_FILE% - Melee Animations have wrong probabilities! Setting Spear probabilities..."
        PATCH_PRINT "  Overhand Swing: %anim_overhand% -> %anim_overhand_new%"
        PATCH_PRINT "  Backhand Swing: %anim_backhand% -> %anim_backhand_new%"
        PATCH_PRINT "  Thrust        : %anim_thrust% -> %anim_thrust_new%"
      END
      PATCH_IF (("%type%" = 26)) AND // staff
               (("%anim_overhand%" != 20) OR
                ("%anim_backhand%" != 70) OR
                ("%anim_thrust%" != 10)) BEGIN
        SET "anim_overhand_new" = 20
        SET "anim_backhand_new" = 70
        SET "anim_thrust_new" = 10
        WRITE_SHORT ("%abil_off%" + 0x2c + (0x38 * "%index%")) 20
        WRITE_SHORT ("%abil_off%" + 0x30 + (0x38 * "%index%")) 70
        WRITE_SHORT ("%abil_off%" + 0x2e + (0x38 * "%index%")) 10
        PATCH_PRINT "HW110: %SOURCE_FILE% - Melee Animations have wrong probabilities! Setting Stave probabilities..."
        PATCH_PRINT "  Overhand Swing: %anim_overhand% -> %anim_overhand_new%"
        PATCH_PRINT "  Backhand Swing: %anim_backhand% -> %anim_backhand_new%"
        PATCH_PRINT "  Thrust        : %anim_thrust% -> %anim_thrust_new%"
      END
    END ELSE
    PATCH_IF ("%abil_type%" = 2) BEGIN // Ranged Ability (No ammunition or ammunition itself)
      PATCH_IF (("%type%" = 15) OR // bow
                ("%type%" = 18) OR // sling
                ("%type%" = 27)) AND // xbow
               (("%anim_overhand%" != 0) OR
                ("%anim_backhand%" != 0) OR
                ("%anim_thrust%" != 0)) BEGIN
        SET "anim_overhand_new" = 0
        SET "anim_backhand_new" = 0
        SET "anim_thrust_new" = 0
        WRITE_SHORT ("%abil_off%" + 0x2c + (0x38 * "%index%")) 0
        WRITE_SHORT ("%abil_off%" + 0x30 + (0x38 * "%index%")) 0
        WRITE_SHORT ("%abil_off%" + 0x2e + (0x38 * "%index%")) 0
        PATCH_PRINT "HW110: %SOURCE_FILE% - Ranged Animations have wrong probabilities! Nulling probabilities..."
        PATCH_PRINT "  Overhand Swing: %anim_overhand% -> %anim_overhand_new%"
        PATCH_PRINT "  Backhand Swing: %anim_backhand% -> %anim_backhand_new%"
        PATCH_PRINT "  Thrust        : %anim_thrust% -> %anim_thrust_new%"
        PATCH_IF (("%type%" = 15) AND (("%is_arrow%" = 0) OR ("%is_bullet%" = 1) OR ("%is_bolt%" = 1))) BEGIN
          WRITE_SHORT ("%abil_off%" + 0x32 + (0x38 * "%index%")) 1
          WRITE_SHORT ("%abil_off%" + 0x34 + (0x38 * "%index%")) 0
          WRITE_SHORT ("%abil_off%" + 0x36 + (0x38 * "%index%")) 0
          PATCH_PRINT "HW111: %SOURCE_FILE% - Item is supposed to fire ARROWS!"
        END ELSE
        PATCH_IF (("%type%" = 18) AND (("%is_arrow%" = 1) OR ("%is_bullet%" = 0) OR ("%is_bolt%" = 1))) BEGIN
          WRITE_SHORT ("%abil_off%" + 0x32 + (0x38 * "%index%")) 0
          WRITE_SHORT ("%abil_off%" + 0x34 + (0x38 * "%index%")) 0
          WRITE_SHORT ("%abil_off%" + 0x36 + (0x38 * "%index%")) 1
          PATCH_PRINT "HW112: %SOURCE_FILE% - Item is supposed to fire BULLETS!"
        END ELSE
        PATCH_IF (("%type%" = 27) AND (("%is_arrow%" = 1) OR ("%is_bullet%" = 1) OR ("%is_bolt%" = 0))) BEGIN
          WRITE_SHORT ("%abil_off%" + 0x32 + (0x38 * "%index%")) 0
          WRITE_SHORT ("%abil_off%" + 0x34 + (0x38 * "%index%")) 1
          WRITE_SHORT ("%abil_off%" + 0x36 + (0x38 * "%index%")) 0
          PATCH_PRINT "HW113: %SOURCE_FILE% - Item is supposed to fire BOLTS!"
        END
      END
      PATCH_IF (("%type%" = 16) OR // dagger
                ("%type%" = 17) OR // maces
                ("%type%" = 19) OR // short sword
                ("%type%" = 20) OR // swords
                ("%type%" = 21) OR // hammer
                ("%type%" = 22) OR // morning stars
                ("%type%" = 23) OR // flail
                ("%type%" = 24) OR // darts
                ("%type%" = 25) OR // axe
                ("%type%" = 26) OR // staff
                ("%type%" = 28) OR // hand to hand
                ("%type%" = 29) OR // Spear
                ("%type%" = 30)) AND // halberd
               ((%anim_overhand% + %anim_backhand% + %anim_thrust%) != 100) BEGIN
        SET "anim_overhand_new" = 100
        SET "anim_backhand_new" = 0
        SET "anim_thrust_new" = 0
        WRITE_SHORT ("%abil_off%" + 0x2c + (0x38 * "%index%")) 100
        WRITE_SHORT ("%abil_off%" + 0x30 + (0x38 * "%index%")) 0
        WRITE_SHORT ("%abil_off%" + 0x2e + (0x38 * "%index%")) 0
        PATCH_PRINT "HW114: %SOURCE_FILE% - Ranged Animations have wrong probabilities! Setting Generic Ranged probabilities..."
        PATCH_PRINT "  Overhand Swing: %anim_overhand% -> %anim_overhand_new%"
        PATCH_PRINT "  Backhand Swing: %anim_backhand% -> %anim_backhand_new%"
        PATCH_PRINT "  Thrust        : %anim_thrust% -> %anim_thrust_new%"
        PATCH_IF (("%type%" != 18) AND (("%is_arrow%" = 1) OR ("%is_bullet%" = 1) OR ("%is_bolt%" = 1))) BEGIN
          WRITE_SHORT ("%abil_off%" + 0x32 + (0x38 * "%index%")) 0
          WRITE_SHORT ("%abil_off%" + 0x34 + (0x38 * "%index%")) 0
          WRITE_SHORT ("%abil_off%" + 0x36 + (0x38 * "%index%")) 0
          PATCH_PRINT "HW116: %SOURCE_FILE% - Item is not a BOW/SLING/XBOW!"
        END
      END
    END ELSE
    PATCH_IF ("%abil_type%" = 4) BEGIN // Launcher Ability
      PATCH_IF (("%type%" = 15) OR // bow
                ("%type%" = 18) OR // sling
                ("%type%" = 27)) AND // xbow
               (("%anim_overhand%" != 0) OR
                ("%anim_backhand%" != 0) OR
                ("%anim_thrust%" != 0)) BEGIN
        SET "anim_overhand_new" = 0
        SET "anim_backhand_new" = 0
        SET "anim_thrust_new" = 0
        WRITE_SHORT ("%abil_off%" + 0x2c + (0x38 * "%index%")) 0
        WRITE_SHORT ("%abil_off%" + 0x30 + (0x38 * "%index%")) 0
        WRITE_SHORT ("%abil_off%" + 0x2e + (0x38 * "%index%")) 0
        PATCH_PRINT "HW117: %SOURCE_FILE% - Launcher Animations have wrong probabilities! Nulling probabilities..."
        PATCH_PRINT "  Overhand Swing: %anim_overhand% -> %anim_overhand_new%"
        PATCH_PRINT "  Backhand Swing: %anim_backhand% -> %anim_backhand_new%"
        PATCH_PRINT "  Thrust        : %anim_thrust% -> %anim_thrust_new%"
        PATCH_IF ("%type%" = 15) AND (("%is_arrow%" = 0) OR ("%is_bullet%" = 1) OR ("%is_bolt%" = 1)) BEGIN
          WRITE_SHORT ("%abil_off%" + 0x32 + (0x38 * "%index%")) 1
          WRITE_SHORT ("%abil_off%" + 0x34 + (0x38 * "%index%")) 0
          WRITE_SHORT ("%abil_off%" + 0x36 + (0x38 * "%index%")) 0
          PATCH_PRINT "HW118: %SOURCE_FILE% - Item is supposed to fire ARROWS!"
        END ELSE
        PATCH_IF (("%type%" = 18) AND (("%is_arrow%" = 1) OR ("%is_bullet%" = 0) OR ("%is_bolt%" = 1))) BEGIN
          WRITE_SHORT ("%abil_off%" + 0x32 + (0x38 * "%index%")) 0
          WRITE_SHORT ("%abil_off%" + 0x34 + (0x38 * "%index%")) 0
          WRITE_SHORT ("%abil_off%" + 0x36 + (0x38 * "%index%")) 1
          PATCH_PRINT "HW119: %SOURCE_FILE% - Item is supposed to fire BULLETS!"
        END ELSE
        PATCH_IF ("%type%" = 27) AND (("%is_arrow%" = 1) OR ("%is_bullet%" = 1) OR ("%is_bolt%" = 0)) BEGIN
          WRITE_SHORT ("%abil_off%" + 0x32 + (0x38 * "%index%")) 0
          WRITE_SHORT ("%abil_off%" + 0x34 + (0x38 * "%index%")) 1
          WRITE_SHORT ("%abil_off%" + 0x36 + (0x38 * "%index%")) 0
          PATCH_PRINT "HW120: %SOURCE_FILE% - Item is supposed to fire BOLTS!"
        END
      END ELSE
      PATCH_IF (("%type%" = 16) OR // dagger
                ("%type%" = 17) OR // maces
                ("%type%" = 19) OR // short sword
                ("%type%" = 20) OR // swords
                ("%type%" = 21) OR // hammer
                ("%type%" = 22) OR // morning stars
                ("%type%" = 23) OR // flail
                ("%type%" = 24) OR // darts
                ("%type%" = 25) OR // axe
                ("%type%" = 26) OR // staff
                ("%type%" = 28) OR // hand to hand
                ("%type%" = 29) OR // Spear
                ("%type%" = 30)) AND // halberd
               ((%anim_overhand% + %anim_backhand% + %anim_thrust%) != 100) BEGIN
        SET "anim_overhand_new" = 100
        SET "anim_backhand_new" = 0
        SET "anim_thrust_new" = 0
        WRITE_SHORT ("%abil_off%" + 0x2c + (0x38 * "%index%")) 100
        WRITE_SHORT ("%abil_off%" + 0x30 + (0x38 * "%index%")) 0
        WRITE_SHORT ("%abil_off%" + 0x2e + (0x38 * "%index%")) 0
        PATCH_PRINT "HW121: %SOURCE_FILE% - Launcher Animations have wrong probabilities! Setting Generic Ranged probabilities..."
        PATCH_PRINT "  Overhand Swing: %anim_overhand% -> %anim_overhand_new%"
        PATCH_PRINT "  Backhand Swing: %anim_backhand% -> %anim_backhand_new%"
        PATCH_PRINT "  Thrust        : %anim_thrust% -> %anim_thrust_new%"
        PATCH_IF (("%type%" != 18) AND (("%is_arrow%" = 1) OR ("%is_bullet%" = 1) OR ("%is_bolt%" = 1))) BEGIN
          WRITE_SHORT ("%abil_off%" + 0x32 + (0x38 * "%index%")) 0
          WRITE_SHORT ("%abil_off%" + 0x34 + (0x38 * "%index%")) 0
          WRITE_SHORT ("%abil_off%" + 0x36 + (0x38 * "%index%")) 0
          PATCH_PRINT "HW122: %SOURCE_FILE% - Item is not a BOW/SLING/XBOW!"
        END
      END
    END ELSE
    PATCH_IF ((%anim_overhand% + %anim_backhand% + %anim_thrust%) != 0) AND
             ((%anim_overhand% + %anim_backhand% + %anim_thrust%) != 100) BEGIN
      WRITE_SHORT ("%abil_off%" + 0x2c + (0x38 * "%index%")) 0
      WRITE_SHORT ("%abil_off%" + 0x30 + (0x38 * "%index%")) 0
      WRITE_SHORT ("%abil_off%" + 0x2e + (0x38 * "%index%")) 0
      PATCH_PRINT "HW123: %SOURCE_FILE% - Improper Swing Probabilities! Setting to 0"
      PATCH_PRINT "  Overhand Swing: %anim_overhand% -> 0"
      PATCH_PRINT "  Backhand Swing: %anim_backhand% -> 0"
      PATCH_PRINT "  Thrust        : %anim_thrust% -> 0"
    END
  END
END
