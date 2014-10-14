#!/usr/bin/php -q
<?PHP
$names=Array( "SharebotNG_LevelPlate_Auto.gcode",  "SharebotNG_FilamentChange_L.gcode",  "SharebotNG_FilamentChange_R.gcode",  "SharebotNG_LevelPlate_Man.gcode",  "SharebotNG_Nozzles.gcode" );
$out=Array(   "sc_level_plate_a.h",            "sc_change_left.h",            "sc_change_right.h",            "sc_level_plate_m.h",            "sc_nozzles.h" );
$vars=Array(  "LEVEL_PLATE_A",		     "CHANGE_LEFT",		  "CHANGE_RIGHT",			"LEVEL_PLATE_M",		       "NOZZLES" );

print_r( $names );

foreach ( $names as $pos=>$name ) {
	$var_name=$vars[$pos];
	$output=$out[$pos];
	echo "$pos - $name -> $output ( $var_name)\n";
        $comment=false;
	$fp=fopen( $name, "rb" );
	$fpw=fopen( $output, "w+b" );
	$first=true;
	$cnt=0;
        $cnt_riga=0;
	if ( $fp != NULL ) {
   		echo "#ifndef SC_".$var_name."\n";
		fwrite ( $fpw, "#ifndef SC_".$var_name."\n" );
   		echo "#define SC_".$var_name."\n";
		fwrite ( $fpw, "#define SC_".$var_name."\n" );
   		echo "static uint8_t ".$var_name."[] = {";
		fwrite ( $fpw, "static uint8_t ".$var_name."[] = {" );
  	 	while ( !feof($fp) ) {
      			$c = fgetc($fp);
                        if ( $c == ';' ) { 
                           $comment = TRUE;
                        }
                        if ( $c == "\n" ) {
                           $comment = FALSE;
                           /* Se ci sono due righe vuote non salva la seconda */
                           if ( $cnt_riga == 0 )
                              continue;
                           $cnt_riga=-1;
                        }
                        if ( ( $comment ) || ( $c == "\r" ) || ( ord($c) == 0x00 ) )
                           continue;
      			$cnt++;
                        $cnt_riga++;
                        $last=$c;
      			if ( $cnt == 1 )
         			$first=false;
      			else {
         			#echo ",";
				fwrite ( $fpw, "," );
			}
      			#echo ord($c);
                        echo $c;
			fwrite ( $fpw, ord($c) );
   		}

                // Se l'ultima riga non termina con LF lo aggiunge
                if ( ord($last) != 10 ) {
   		   echo ",10,0 };\n";
		   fwrite ( $fpw, ",10,0 };\n" );
                   echo "#define ".$var_name."_LENGTH ".($cnt+1)."\n";
                   fwrite ( $fpw, "#define ".$var_name."_LENGTH ".($cnt+1)."\n" );
                } else {
                   $add=1;
                   echo ",0 };\n";
                   fwrite ( $fpw, ",0 };\n" );
                   echo "#define ".$var_name."_LENGTH ".($cnt)."\n";
                   fwrite ( $fpw, "#define ".$var_name."_LENGTH ".($cnt)."\n" );
                }
   		echo "#endif\n";
		fwrite ( $fpw, "#endif\n" );
	}
	fclose ( $fp );
	fclose ( $fpw );
}
?>
