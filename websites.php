<?php
$f = fopen("websites.txt", "r") or die ("Unable to open file!");
echo fread($f,filesize("websites.txt"));
fclose($f);
?>
