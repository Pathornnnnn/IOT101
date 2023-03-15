<?php
$id=$_GET["id"];
$value=$_GET["value"];
$value=trim($value);
$fname=$id.".txt";

if($value=="?"){
    $f=fopen($fname,"r")or die("Unable to open file!");
    echo fread($f,filesize($fname));
    fclose($f);  
}
elseif($value=="ON" || $value=="OFF")
 {
  $f=fopen($fname,"w");          //don;t append
  fputs($f,"> = ".$value);
  fclose($f);
  //
  $f=fopen($fname,"r")or die("Unable to open file!");
  echo fread($f,filesize($fname));
  fclose($f);
}

?>
