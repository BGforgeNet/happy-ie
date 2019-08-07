// Missing Container Store Linker
READ_SHORT 0x1c "type"

PATCH_IF ("%type%" = 36) BEGIN
  PATCH_IF NOT (FILE_EXISTS_IN_GAME ~%SOURCE_RES%.sto~) BEGIN
    PATCH_PRINT "HW100: %SOURCE_FILE% - Container missing corresponding STO file! Linking makeshift store..."
    INNER_ACTION BEGIN

      ACTION_DEFINE_ASSOCIATIVE_ARRAY lol_stores BEGIN
        1 => ~Big World Burgers~
        2 => ~Lollorian's Lulz~
        3 => ~Leonardo's Locks~
        4 => ~Jarno's Jams~
        5 => ~I AM ERROR!~
      END

      COPY_EXISTING ~BAG04.STO~ ~override/%SOURCE_RES%.STO~ // copy bag of holding's store
        SET rnb = RANDOM (1 5)
        PHP_EACH lol_stores AS random_num => random_store BEGIN
          PATCH_IF ("%rnb%" = "%random_num%") BEGIN
            SAY 0xc "%random_store%"
          END
        END
    END
  END
END
