<?php
	$url = "http://$_SERVER[HTTP_HOST]$_SERVER[REQUEST_URI]";
	$to = "moshetrenk@gmail.com";
	$subject = "404 error at".$url;
	$txt = "Fix this";
	$headers = "From: webmaster@example.com" . "\r\n" .

	mail($to,$subject,$txt,$headers);
?>
