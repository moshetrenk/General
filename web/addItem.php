<?php


//for god's sake, please don't use this for any secure data. use the .sql




$fp = fopen("cart.txt","a");

if (!$fp)
{
	echo "Error: could not open cart.txt. Please try again later.";
	exit;
}

$i = 0;
 foreach ($_POST as $key => $value) {
	
        //echo $key." ->";

        fwrite($fp, $value."\n");

	$i++;
}

fwrite($fp, "\n");

fclose();

header($url);
die();

?>
