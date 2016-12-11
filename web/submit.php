 <?php

$page = "<!DOCTYPE html><html><head><title>Order Confirmation</title></head><body><center><h4 style = 'padding: 45px 0 0 0'>Thank you for your order<br>Order id: ".uniqid()."</h4></center>";

$page=$page."<table>
	<tr>
		<td>
			<center>
				Your Order Information:<br><br>
			</center>
		</td>
	</tr>
	<tr>
		<td colspan = 2>
			Expected Delivery: 
		</td>
	</tr>
	<tr>
		<td width = 32%	>
			Name: 
		</td>
		<td>
			".$_POST['name']."
		</td>
	</tr>
	<tr>
		<td>
			Email Address: 
		</td>
		<td>
			".$_POST['emailAddress']."
		</td>
	</tr>
	<tr>
		<td>
			Phone: 
		</td>
		<td>
			".$_POST['phoneNum']."
		</td>
	</tr>
	<tr>
		<td>
			Address: 
		</td>
		<td>
			".$_POST['address']."<br>".$_POST['city'].",&nbsp;".$_POST['state']."&nbsp;".$_POST['zip']."
		</td>
	</tr>
</table>";


$items = array();
$numItems = 0;

$myfile = fopen("cart.txt", "r") or die("Unable to open file!");

for($i = 0; !feof($myfile); $i++) {
	$items[] = ucfirst(fgets($myfile));
	$numItems += (strpos($items[$i], 'Add To Cart') !== false) ? 1 : 0;
}

$num = sizeof($items);
/*
for($a = 0; $a < $num; $a++){
	echo "items[".$a."] = ".$items[$a]."<br>";
}*/

if($num == 1){
	echo "<center style = 'padding: 180px 0 0 0'><h4>your cart is empty</h4>"."<img height = 150px width = 150px src = 'emptyCart.gif'><br></center>";
	exit;
}


/*echo "imageUrl = ".$imageUrl."<br>";
echo "pic = <img src = '".$imageUrl."'><br>";
echo "name = ".$itemName."<br>";
echo "type = ".$type."<br>";
echo "color = ".$color."<br>";*/


//
$page=$page."<table style = 'padding: 24px 0 24px 0' id = 'first item'>";
for($it = 1; $it / 8 <= $numItems; $it+= 9){
$orderTotal += $items[$it + 5];
$page=$page."	<tr>
		<td style = 'padding: 0 0 0 35px'>
			<img height = 85px width = 100px style = 'display: inline-block' src = '".$items[$it]."'>
		</td>	
			<td style = 'width: 40%'>"
				.$items[$it + 1]."</td><td style = 'width: 13%'>&nbsp;&nbsp;&nbsp;".$items[$it + 3]."</td><td style = 'width: 13%'>".$items[$it + 4]."</td><td><p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</p></td><td>$".$items[$it + 5]." 
			</td>
		</td>
	</tr>";
}

$page=$page."<tr><td colspan = 4 align = right>Total: $".$orderTotal;

$page=$page."</td></tr></table>";
$page=$page."<hr style = 'margin: 0 200px 0 200px'>";


//






$page=$page."</body></html>";
fclose($myfile);

echo $page;

	$url = "http://$_SERVER[HTTP_HOST]$_SERVER[REQUEST_URI]";
	$to = $_Post['emailAddress'];
	$subject = "Order Confirmation";
	$headers .= 'Content-type: text/html; charset=utf-8' . "\r\n";
	mail($to,$subject,$page,$headers);


?>










