#!/bin/bash
export PATH=/bin:/usr/bin:/sbin:/usr/sbin

VERSION="1.0.0"
DATE=$(date +%Y%m%d)

#rm ../firmware.xml
echo "<firmwares>" > ../firmware.xml

for hw in $(echo "34 80"); do
   for lang in $(echo "1 6 7"); do
      echo "Building for HW=$hw LANG=$lang"
      make clean
      make HARDWARE_MOTHERBOARD=$hw LANGUAGE_CHOICE=$lang EXTRUDERS=1
      if [ "$?" -ne 0 ]; then
         exit 1;
      fi
      cp applet/Marlin.hex ../fw-H$hw-L$lang-$VERSION_$DATE-11.hex
      make clean
      make HARDWARE_MOTHERBOARD=$hw LANGUAGE_CHOICE=$lang EXTRUDERS=2
      if [ "$?" -ne 0 ]; then
         exit 1;
      fi
      cp applet/Marlin.hex ../fw-H$hw-L$lang-$VERSION_$DATE-21.hex

      # XML definition
      case "$lang" in 
         1) lang_code="en"
            released="Released $(date +%m-%d-%Y)"
            ;;
         6) lang_code="ru"
            released="Released $(date +%m-%d-%Y)"
            ;;
         7) lang_code="it"
            released="Rilasciato il $(date +%d/%m/%Y)"
            ;;
      esac

      # Hardware
      case "$hw" in
         34) BOARD_ID="0"
             ;;
         80) BOARD_ID="1"
             ;;
      esac

      cat << END >> ../firmware.xml
<firmware>
        <Version>$VERSION</Version>
        <Description>$released.</Description>
        <link board="$BOARD_ID" ext="1" bed="1" lang="$lang_code">http://www.sharebot.eu/downloads/firmware/fw-H$hw-L$lang-$VERSION_$DATE-11.hex</link>
        <link board="$BOARD_ID" ext="2" bed="1" lang="$lang_code">http://www.sharebot.eu/downloads/firmware/fw-H$hw-L$lang-$VERSION_$DATE-21.hex</link>
</firmware>
END
   done
done

echo "</firmwares>" >> ../firmware.xml

exit
