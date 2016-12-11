 <?php

echo "<!DOCTYPE html><html><head><title>Cart</title>";

echo "<script type = 'text/javascript'>
	var verify = function(){
		var box = document.getElementById('cardNum')
		if(!v())
			box.setCustomValidity('Please Enter A Valid Card Number')
		else
			box.setCustomValidity('')
			
	}
	var v = function() {
		var cardNumber = document.getElementById('cardNum').value
		if(cardNumber.length != 16)
			return false
		var checkSum = 0;
	        for (var i = cardNumber.length - 2; i > -1; i -= 2)
	        	if (parseInt((cardNumber.charAt(i))) * 2 >= 10) {
	                	var number = parseInt((cardNumber.charAt(i))) * 2;
		                
				if (number % 9 === 0)
                        		checkSum += 9;
       	                	else
       		                	checkSum += number % 9;
       	             	}
       	             	else 
			{	
				checkSum += parseInt((cardNumber.charAt(i))) * 2;
       	             	}
       		
		for (var i = 0; i < cardNumber.length + 1; i += 2) {
                	if (i === 0 && cardNumber.length % 2 === 0)	
				i = 1;

       	        	checkSum += parseInt((cardNumber.charAt(i)));
       	         }
       	        	
		return checkSum % 10 === 0;
        }    
</script>";


echo "</head><body><center><p>Your shopping cart</p><hr style = 'margin: 0 200px 0 200px'>";

$items = array();
$numItems = 0;
$orderTotal = 0;

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
echo "<table style = 'padding: 24px 0 24px 0' id = 'first item'>";
for($it = 1; $it / 8 <= $numItems; $it+= 9){
$orderTotal += $items[$it + 5];
echo "	<tr>
		<td style = 'padding: 0 0 0 35px'>
			<img height = 85px width = 100px style = 'display: inline-block' src = '".$items[$it]."'>
		</td>	
			<td style = 'width: 40%'>"
				.$items[$it + 1]."</td><td style = 'width: 13%'>".$items[$it + 3]."</td><td style = 'width: 13%'>".$items[$it + 4]." &nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp</td><td>$".$items[$it + 5]." 
			</td>
		</td>
	</tr>";
}

echo "<tr><td colspan = 4 align = right>Total: $".$orderTotal;

echo "</td></tr></table>";
echo "<hr style = 'margin: 0 200px 0 200px'>";

//
echo "<datalist id='states'>
						<option value='Alabama'></option>
						<option value='Alaska'></option>
						<option value='Arizona'></option>
						<option value='Arkansas'></option>
						<option value='California'></option>
						<option value='Colorado'></option>
						<option value='Connecticut'></option>
						<option value='Delaware'></option>
						<option value='District of Columbia'></option>
						<option value='Florida'></option>
						<option value='Georgia'></option>
						<option value='Hawaii'></option>
						<option value='Idaho'></option>
						<option value='Illinois'></option>
						<option value='Indiana'></option>
						<option value='Iowa'></option>
						<option value='Kansas'></option>
						<option value='Kentucky'></option>
						<option value='Louisiana'></option>
						<option value='Maine'></option>
						<option value='Maryland'></option>
						<option value='Massachusetts'></option>
						<option value='Michigan'></option>
						<option value='Minnesota'></option>
						<option value='Mississippi'></option>
						<option value='Missouri'></option>
						<option value='Montana'></option>
						<option value='Nebraska'></option>
						<option value='Nevada'></option>
						<option value='New Hampshire'></option>
						<option value='New Jersey'></option>
						<option value='New Mexico'></option>
						<option value='New York'></option>
						<option value='North Carolina'></option>
						<option value='North Dakota'></option>
						<option value='Ohio'></option>
						<option value='Oklahoma'></option>
						<option value='Oregon'></option>
						<option value='Pennsylvania'></option>
						<option value='Rhode Island'></option>
						<option value='South Carolina'></option>
						<option value='South Dakota'></option>
						<option value='Tennessee'></option>
						<option value='Texas'></option>
						<option value='Utah'></option>
						<option value='Vermont'></option>
						<option value='Virginia'></option>
						<option value='Washington'></option>
						<option value='West Virginia'></option>
						<option value='Wisconsin'></option>
						<option value='Wyoming'></option>
					</datalist>
<form method = POST action = 'submitOrder.php'>
<table>
	<tr>
		<td>
			<p>
				Name: 
			</p>
		</td>
		<td>
			<input type = 'text' name = 'name' placeholder = 'Name' required>
		</td>
		<td>
			<p style = 'padding: 0 0 0 35px'>
				Email:
			</p>
		</td>
		<td>
			<input type = 'email' name = 'emailAddress' placeholder = 'name@domain.com' required />
		</td>
	</tr>
	<tr>
		<td>
			<p>
				Phone:
			</p>
		</td>
		<td>
			<input name = 'phoneNum' type = 'tel' placeholder = '###-###-####' pattern = '\d{3}-\d{3}-\d{4}' required />	
		</td>
		<td>
			<p style = 'padding: 0 0 0 35px'>
				Card#:
			</p>
		</td>
		<td>
			<p>
				<input onkeyup = 'verify()' id = 'cardNum' name = 'cardNum' placeholder = '1234567890123456' pattern = '\d{16}' required>
			</p>
		</td>
	</tr>
	<tr>
		<td>
			<p>
				Address:
			</p>
		</td>
		<td>
			<input type = 'text' name = 'address' placeholder = '1600 Pennslyvannia Ave' required>
		</td>
		<td>
			<p style = 'padding: 0 0 0 35px'>
				City:
			</p>
		</td>
		<td>
			<input type = 'text' name = 'city' placeholder = 'New York' required>
		</td>
	</tr>
	<tr>
		<td>
			<p>
				State:
			</p>
		</td>
		<td>
			<input placeholder = 'State' type = 'text' list = 'states' required />
		</td>
		<td>
			<p style = 'padding: 0 0 0 35px'>
				Zip Code:
			</p>
		</td>
		<td>
			<input type = 'number' name = 'zip' placeholder = '12345' required/>
		</td>
	</tr>
	<tr>
		<td colspan = 4>
			<center>
				<input  style = 'height: 25px; width: 125px; margin: 25px 0 0 0; background-color: #eee; border-radius: 12px' type = 'submit' value = 'Place Order'>
			</center>	
		</td>
	</tr>
</table>
</form>

";


echo "</body></html>";
fclose($myfile);


?>













