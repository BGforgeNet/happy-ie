READ_BYTE 0x27b alignment

DEFINE_ASSOCIATIVE_ARRAY race_to_al BEGIN
  1 => 0x22
  2 => 0x22
  3 => 0x22
  4 => 0x22
  5 => 0x22
  6 => 0x22
  7 => 0x22 //first 7 are playable races, set to TN
  102 => 0x22 //basilisk, TN (most are)
  106 => 0x23 //doppelganer, NE
  111 => 0x33 //hobgoblin, CE
  113 => 0x33 //ogre, CE
  115 => 0x23 //skeleton, NE
  132 => 0x33 //shadow, CE
  134 => 0x13 //wraith, LE
  143 => 0x13 //orc, LE
  144 => 0x22 //golem, TN (most are)
END

PATCH_IF alignment = 0 BEGIN
  READ_BYTE 0x272 race
  LOOKUP_IDS_SYMBOL_OF_INT race_id ~race~ race
  PATCH_IF VARIABLE_IS_SET $race_to_al("%race%") BEGIN
    new_al = EVAL $race_to_al("%race%")
    LOOKUP_IDS_SYMBOL_OF_INT new_al_ids ~alignmen~ new_al
    PATCH_PRINT ~%SOURCE_FILE% issue: missing alignment for creature race %race_id%. Changing to True Neutral.~
    WRITE_BYTE 0x27b %new_al%
  END
  /*  ELSE BEGIN
    PATCH_PRINT ~%SOURCE_FILE% issue: missing alignment for creature race %race%=%race_id%. Not correcting~
  END */
END
